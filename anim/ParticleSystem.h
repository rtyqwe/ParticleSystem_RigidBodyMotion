#ifndef MY_PARTICLESYSTEM_H
#define MY_PARTICLESYSTEM_H

/*

	This is a the Particle System.

*/


#include "BaseSystem.h"
#include "anim.h"
#include <shared/defs.h>
#include <util/util.h>
#include "animTcl.h"
#include <GLmodel/GLmodel.h>
#include <GL/glut.h>
#include <vector>
#include "ParticleSimulator.h"
// a sample system
struct Particle{
		int index;
		double mass;
		VectorObj pos;
		VectorObj vel;
		VectorObj force;
		std::vector<struct Spring*> sp;
};

class ParticleSystem : public BaseSystem
{ 

public:
	ParticleSystem( const std::string& name );
	
	
	virtual void getState( int i, double *p );
	virtual void setState( int i, double *p );
	void reset( double time );

	void display( GLenum mode = GL_RENDER );

	int setParticle(int i, double m, double x, double y, double z, double vx, double vy, double vz);
	void setAllVelo(double vx, double vy, double vz);

	
	int command(int argc, char **argv);

	std::vector<Particle> m_p;
	int m_no;	//Number of Particles
	double m_p_rad;
protected:
	
	GLMmodel m_model;
	
} ;
#endif