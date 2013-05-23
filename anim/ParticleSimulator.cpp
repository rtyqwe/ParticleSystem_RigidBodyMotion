#include "ParticleSimulator.h"
#define SPRING_TOLERANCE (0.05)
ParticleSimulator::ParticleSimulator( const std::string& name, ParticleSystem* target ):
	BaseSimulator( name ),
	m_particle( target )
{
	m_gravity = 0;
	m_integration = "euler";
	m_no_spring = 0;
	m_index = 0;
	m_prev_pos = VectorObj(0,0,0);
	m_spring.clear();
}	// ParticleSimulator


void ParticleSimulator::computeForce(Particle* a, Particle* b, int sindex){
	_force = b->pos - a->pos;
	_vel = b->vel - a->vel;

	if(abs(_force.length()-m_spring[sindex].len) < SPRING_TOLERANCE)
	{	
		_force = VectorObj(0,0,0);
		return;
	}
	double cur_length =_force.length();
	VectorObj norm_force = _force.normalize();

	_force = -(m_spring[sindex].ks*(cur_length-m_spring[sindex].len)+
		m_spring[sindex].kd*(_vel.dot(_force)/cur_length))*norm_force;
}
int ParticleSimulator::step(double time)
{
	Vector pos;
	double fg;
	for(int i = 0; i < m_particle->m_p.size(); i++){
		m_particle->getState(i, pos);
		//m_particle->m_p[i].force=VectorObj(0,0,0);
		fg = m_gravity * m_particle->m_p[i].mass;
		m_particle->m_p[i].force[1] = fg;
	}
	for(int i = 0; i < m_particle->m_p.size(); i++){
		for(int j = 0; j < m_no_spring; j++){
			if(m_spring[j].p1!=NULL && m_spring[j].p2!=NULL){
			if( m_particle->m_p.size()!=0 && m_spring[j].p1 == &m_particle->m_p[i]){
				computeForce(m_spring[j].p2, m_spring[j].p1, j);
				m_spring[j].p1->force+=_force;
				//animTcl::OutputMessage("force p1: %lf %lf %lf", m_spring[j].p1->force.x(), m_spring[j].p1->force.y(), m_spring[j].p1->force.z());
			}
			else if( m_spring[j].p2 == &m_particle->m_p[i]){
				computeForce(m_spring[j].p1, m_spring[j].p2, j);
				
			//	animTcl::OutputMessage("force p2: %lf %lf %lf", m_spring[j].p2->force.x(), m_spring[j].p2->force.y(), m_spring[j].p2->force.z());
				m_spring[j].p2->force+=_force;
			}
			}
			
		}
	}
	VectorObj Pg(0,-0.5,0);
	VectorObj T(1,0,0);
	VectorObj N(0,1,0);
	for(int i = 0; i < m_particle->m_p.size(); i++){
		if((m_particle->m_p[i].pos-Pg).dot(N)<=1 ){
			//if collision with ground
			m_particle->m_p[i].force = VectorObj(0,0,0);
		
			VectorObj force_n = m_ground.ks*N.dot(Pg-m_particle->m_p[i].pos)*N-
				m_ground.kd*m_particle->m_p[i].vel.normalize().dot(N)*N;
		//VectorObj force_n = m_ground.ks*N.dot(Pg-m_particle->m_p[i].pos)*N-m_ground.kd*m_particle->m_p[i].vel.dot(N)*N;
			
			//animTcl::OutputMessage("force_n dot N: %lf", force_n.dot(N));
		
		if(force_n.dot(N)>0){
			m_particle->m_p[i].force+=force_n;
			//vt = |a|cos(theta)*b
			VectorObj VN = N.normalize().dot(m_particle->m_p[i].vel)*N.normalize();
			VectorObj VT = m_particle->m_p[i].vel - VN;
			m_particle->m_p[i].vel = VT-m_ground.kd*VN;
		}
		else{
			m_particle->m_p[i].force-=force_n;
			//m_particle->m_p[i].force = -m_particle->m_p[i].force;
		}
		
			//animTcl::OutputMessage("force p2: %lf %lf %lf", m_particle->m_p[i].force.x(), m_particle->m_p[i].force.y(), m_particle->m_p[i].force.z());
		}
		if(m_integration=="euler"){
		//forward Euler
			VectorObj cur_vel = m_particle->m_p[i].vel;
			m_particle->m_p[i].vel += (m_particle->m_p[i].force/m_particle->m_p[i].mass)*m_timestep;
			m_particle->m_p[i].pos += cur_vel*m_timestep;
		}
		//symplectic
		else if(m_integration=="symplectic"){
			m_particle->m_p[i].vel += (m_particle->m_p[i].force/m_particle->m_p[i].mass)*m_timestep;
			m_particle->m_p[i].pos += m_timestep* m_particle->m_p[i].vel;
		}
		//verlet
		else if(m_integration=="verlet"){
			m_particle->m_p[i].vel += (m_particle->m_p[i].force/m_particle->m_p[i].mass)*m_timestep;
			m_prev_pos = m_particle->m_p[i].pos-m_timestep*m_particle->m_p[i].vel;
			m_particle->m_p[i].pos = 2*m_particle->m_p[i].pos-m_prev_pos+pow(m_timestep,2)/m_particle->m_p[i].mass*m_particle->m_p[i].force;
				
		}
		else{
			animTcl::OutputMessage("Wrong integration method!");
			return TCL_ERROR;
		}
		
		m_particle->setState(i, pos);
	}
	return TCL_OK;

}// ParticleSimulator::step
int ParticleSimulator::command(int argc, char **argv) { 
	if(argc<1){
		animTcl::OutputMessage("system %s: wrong number of params.", m_name) ;
		return TCL_ERROR;
	}
	else if( strcmp(argv[0], "link") == 0 )
	{
		if( argc == 3 )
		{
			m_spring.clear();
			m_index = 0;
			// get the linked particle system
			m_particle = (ParticleSystem*) GlobalResourceManager::use()->getSystem("partSys");
			// make sure it was registered successfully
			if(m_particle==NULL)
				return TCL_ERROR;
			m_no_spring = atoi(argv[2]);
			for(int i = 0; i< m_no_spring; i++){
				Spring temp_s={NULL,NULL,0,0, 0, VectorObj(0,0,0)};
				m_spring.push_back(temp_s);
			}
		}
		else 
		{
			animTcl::OutputMessage("Usage: link <sys name> <Number of Springs>") ;
			return TCL_ERROR ;
		}
	}
	else if( strcmp(argv[0], "spring") == 0 )
	{
		if( argc == 6 )
		{
			Particle* p1 = &(m_particle->m_p[atoi(argv[1])]);
			Particle* p2 = &(m_particle->m_p[atoi(argv[2])]);
			
			double ks =atof(argv[3]);
			double kd = atof(argv[4]);
			
			double length = atof(argv[5]);
			if(length < 0){
				length = (p1->pos-p2->pos).length();
			}
			VectorObj force(0,0,0);
			m_spring[m_index].p1 =p1;
			m_spring[m_index].p2 = p2;
			m_spring[m_index].ks = ks;
			m_spring[m_index].kd = kd;
			m_spring[m_index].len = length;
			m_spring[m_index].force = force;
			p1 -> sp.push_back(&m_spring[m_index]);
			p2 -> sp.push_back(&m_spring[m_index]);
			m_index++;
		}
		else if( argc == 7 )
		{
			int index = atof(argv[1]);
			Particle* p1 = &(m_particle->m_p[atoi(argv[2])]);
			Particle* p2 = &(m_particle->m_p[atoi(argv[3])]);
			double ks =atof(argv[4]);
			double kd = atof(argv[5]);
			double length = atof(argv[6]);
			if(length < 0){
				length = (p1->pos-p2->pos).length();
			}
			
			m_spring[index].p1 = p1;
			m_spring[index].p2 = p2;
			m_spring[index].ks = ks;
			m_spring[index].kd = kd;
			m_spring[index].len = length;
			VectorObj force = ks*(p1->pos-p2->pos)-kd*(p1->vel-p2->vel);
			m_spring[index].force = force;
			
		}
		else
		{
			animTcl::OutputMessage("Usage: spring |<sindex>| <pindex1> <pindex2> <ks> <kd> <length>") ;
			return TCL_ERROR ;

		}
	}
	else if( strcmp(argv[0], "integration") == 0 )
	{
		if( argc == 3 )
		{
			//set integration method
			m_integration = argv[1];
			m_timestep = atof(argv[2]);
		}
		else 
		{
			animTcl::OutputMessage("Usage: integration <euler | symplectic | verlet> <timestep>") ;
			return TCL_ERROR ;
		}
	}
	else if( strcmp(argv[0], "ground") == 0 )
	{
		if( argc == 3 )
		{
			//set integration method
			m_ground.ks = atof(argv[1]);
			m_ground.kd = atof(argv[2]);
		}
		else 
		{
			animTcl::OutputMessage("Usage: ground <ks> <kd>") ;
			return TCL_ERROR ;
		}
	}
	else if( strcmp(argv[0], "gravity") == 0 )
	{
		if( argc == 2 )
		{
			//set integration method
			m_gravity = atof(argv[1]);
		}
		else 
		{
			animTcl::OutputMessage("Usage: gravity <g>") ;
			return TCL_ERROR ;
		}
	}
	else if( strcmp(argv[0], "show") == 0 ){
		for(int i = 0; i<m_particle->m_p.size(); i++){
			animTcl::OutputMessage("Point %d: %lf, %lf, %lf", i, m_particle->m_p[i].pos.x(), m_particle->m_p[i].pos.y(), m_particle->m_p[i].pos.z());
		}
		for(int i = 0; i<m_no_spring; i++){
			animTcl::OutputMessage("Spring %d: %f", i,m_spring[i].len);
		}
	}
	return TCL_OK; 
}
