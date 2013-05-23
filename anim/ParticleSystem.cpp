#include "ParticleSystem.h"
using namespace std;


ParticleSystem::ParticleSystem( const std::string& name ):
	BaseSystem( name )
{ 
	m_p.clear();
	m_no = 0;
	m_p_rad = 0.5;
	m_p.clear();
}	// ParticleSystem

void ParticleSystem::getState( int i, double* p )
{ 
	
	

}	// ParticleSystem::getState

void ParticleSystem::setState( int i, double  *p )
{ 


}	// ParticleSystem::setState

void ParticleSystem::reset( double time ) 
{ 

	m_no = 0;
	m_p.clear();
}	// ParticleSystem::Reset

int ParticleSystem::setParticle(int i, double m, double x, double y, double z, double vx, double vy, double vz){
	if(i<0)
		return TCL_ERROR;
	else if(i>=m_p.size()){
		Particle temp_p ={i,m,VectorObj(x,y,z),VectorObj(vx,vy,vz), VectorObj(0.0,0.0,0.0)};
		m_p.push_back(temp_p);
		return TCL_OK;
	}
	else{
		m_p[i].mass = m;
		m_p[i].pos = VectorObj(x,y,z);
		m_p[i].vel = VectorObj(vx,vy,vz);
		m_p[i].force = VectorObj(0.0,0.0,0.0);
		return TCL_OK;
	}
}
void ParticleSystem::setAllVelo(double vx, double vy, double vz){
	for (std::vector<Particle>::iterator it = m_p.begin() ; it != m_p.end(); ++it){
		(*it).vel = VectorObj(vx,vy,vz);
	}
}
int ParticleSystem::command(int argc, char **argv) 
{
	if( argc < 1 )
	{
		animTcl::OutputMessage("system %s: wrong number of params.", m_name) ;
		return TCL_ERROR ;
	}
	else if( strcmp(argv[0], "dim") == 0 )
	{
		if( argc == 2 )
		{
			m_p.clear();
			m_no = atoi(argv[1]);
			for(int i = 0; i < m_no; i++)
				setParticle(i,0,0,0,0,0,0,0);
			return TCL_OK ;
		}
		else 
		{
			animTcl::OutputMessage("Usage: dim <Number of Particles>") ;
			return TCL_ERROR ;
		}
	}
	else if( strcmp(argv[0], "particle") == 0 )
	{
		if( argc == 9 )
		{
			int return_v = setParticle(atof(argv[1]),
						atof(argv[2]),
						atof(argv[3]),
						atof(argv[4]),
						atof(argv[5]),
						atof(argv[6]),
						atof(argv[7]), 
						atof(argv[8]));

			if(return_v != TCL_OK)
				return TCL_ERROR;

		}
		else
		{
			animTcl::OutputMessage("Usage: particle <index> <mass> <x> <y> <z> <vx> <vy> <vz>") ;
			return TCL_ERROR ;

		}
	}
	else if( strcmp(argv[0], "all_velocities") == 0 )
	{
		if( argc == 4 )
		{
			setAllVelo(atof(argv[1]), atof(argv[2]), atof(argv[3]));
		}
		else
		{
			animTcl::OutputMessage("Usage: all_velocities <vx> <vy> <vz> ") ;
			return TCL_ERROR ;

		}
	}
	
	return TCL_OK ;

}	// ParticleSystem::command

void ParticleSystem::display( GLenum mode ) 
{

	double GridSizeX = 40;
	double GridSizeY = 30;

	glMatrixMode(GL_MODELVIEW) ;

	glPushMatrix() ;
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	glEnable(GL_LIGHTING);
	
	
	for(int i = 0; i < m_no; i++){
		glPushMatrix();
		glTranslatef(m_p[i].pos.x(),m_p[i].pos.y(),m_p[i].pos.z());
	
		glutSolidSphere(m_p_rad,8, 8);
		glPopMatrix();
	}
	glColor3f(1.0f,1.0f,0.0f);
	for(int i = 1; i< m_no; i++){
		glBegin(GL_LINES);
		
		if(m_p[i].sp.size()>0){
			for(int j = 0; j< m_p[i].sp.size(); j++){
				glVertex3f(m_p[i].pos.x(),m_p[i].pos.y(),m_p[i].pos.z());
				if(m_p[i].sp[j]->p1==&(m_p[i])){
					glVertex3f(m_p[i].sp[j]->p2->pos.x(),m_p[i].sp[j]->p2->pos.y(),m_p[i].sp[j]->p2->pos.z());
				}
				else if (m_p[i].sp[j]->p2==&(m_p[i]))
					glVertex3f(m_p[i].sp[j]->p1->pos.x(),m_p[i].sp[j]->p1->pos.y(),m_p[i].sp[j]->p1->pos.z());
			}
		}
		glEnd();
	}
	
	glDisable(GL_LIGHTING);
	glBegin(GL_POLYGON);
	
			glVertex3f(    GridSizeX,-0.5f,    GridSizeY);
			glVertex3f(GridSizeX, -0.5f,   -GridSizeY);
			glVertex3f(-GridSizeX,-0.5f,-GridSizeY);
			glVertex3f(    -GridSizeX,-0.5f,GridSizeY);
 
	glEnd();
	
			glColor3f(0.5f,0.5f,0.5f);
	glPopMatrix();
	glPopAttrib();

}	// ParticleSystem::display
