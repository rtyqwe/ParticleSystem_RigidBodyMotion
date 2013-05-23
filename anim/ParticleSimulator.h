#ifndef MY_PARTICLE_SIMULATOR_H
#define MY_PARTICLE_SIMULATOR_H

#include <GLModel/GLModel.h>
#include <shared/defs.h>
#include <util/util.h>
#include "anim.h"
#include "animTcl.h"
#include "BaseSimulator.h"
#include "BaseSystem.h"
#include "ParticleSystem.h"
#include <vector>
#include <string>

// a sample simulator
struct Spring{
	struct Particle* p1;
	struct Particle* p2;
	double ks;		//elasiticity
	double kd;		//viscosity
	double len;		//resting length
	VectorObj force;	//force on spring
};
class ParticleSimulator : public BaseSimulator 
{
public:

	ParticleSimulator( const std::string& name, class ParticleSystem* target );
	

	int step(double time);
	int init(double time) 
	{ 
		
		return 0;
	};
	void computeForce(Particle* a, Particle* b, int sindex);
	int command(int argc, char **argv);

protected:
	std::vector<Spring> m_spring;
	class ParticleSystem* m_particle;
	int m_no_spring;
	int m_index;
	double m_gravity;
	std::string m_integration;
	struct Spring m_ground;
	double m_timestep;
	VectorObj _force; 
	VectorObj _vel;
	VectorObj m_prev_pos; //for verlet
};


#endif