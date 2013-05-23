////////////////////////////////////////////////////
// // Template code for  CS 174C
////////////////////////////////////////////////////

#ifdef WIN32
#include <windows.h>
#endif


#include <GL/gl.h>
#include <GL/glu.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


#ifndef WIN32
#include <GL/glut.h>
#endif
#ifdef WIN32
#include "GL/glut.h"
#endif

#include <shared/defs.h>
#include <string.h>
#include <util/util.h>
#include <GLModel/GLModel.h>
#include "anim.h"
#include "animTcl.h"
#include "myScene.h"
#include "SampleParticle.h"
#include "SampleGravitySimulator.h"
#include "ParticleSimulator.h"
#include "ParticleSystem.h"
#include <util/jama/tnt_stopwatch.h>
#include <util/jama/jama_lu.h>
#include <util/Picker.h>

// register a sample variable with the shell.
// Available types are:
// - TCL_LINK_INT 
// - TCL_LINK_FLOAT

int g_testVariable = 10;

static const int PICK_BUFFER_SIZE = 10;
static const int PICK_HEIGHT = 5;
static const int PICK_WIDTH = 5;

const int ID_RECT = 0;
const int ID_TRI = 1;
const int ID_NONE = -1;

unsigned int g_width;
unsigned int g_height;

int m_selPartIdx;
double m_selPartX;
double m_selPartY ;
double m_selPartZ;
bool m_bPartSelected;


SETVAR myScriptVariables[] = {
	"testVariable", TCL_LINK_INT, (char *) &g_testVariable,
	"",0,(char *) NULL
};


//---------------------------------------------------------------------------------
//			Hooks that are called at appropriate places within anim.cpp
//---------------------------------------------------------------------------------

void pickObject(int mouseX, int mouseY, GLint *pickedObject, ParticleSystem* p)
{
	GLdouble modelMatrix[16];
    GLdouble projMatrix[16];
    GLint    viewport[4];

	glGetDoublev(GL_MODELVIEW_MATRIX, modelMatrix);
    if (glGetError())
    {
        animTcl::OutputMessage("Error: glGetDoublev(GL_MODELVIEW_MATRIX,*).\n");
        return;
    }
	glGetDoublev(GL_PROJECTION_MATRIX, projMatrix);
    if (glGetError())
    {
        animTcl::OutputMessage("Error: glGetDoublev(GL_PROJECTION_MATRIX,*).\n");
        return;
    }

    glGetIntegerv(GL_VIEWPORT, viewport);
    if (glGetError())
    {
        animTcl::OutputMessage("Error: glGetIntegerv(GL_VIEWPORT,*).\n");
        return;
    }    
	
	//
    // Mouse x- and y-coordinate
    //
	mouseY=(viewport[2]-mouseY);
	
	//animTcl::OutputMessage("(%d, %d)", mouseX, mouseY);
    
    VectorObj pos;
    VectorObj w;
    VectorObj w2;

    m_selPartIdx = 0;
    m_selPartX = mouseX;
    m_selPartY = mouseY;
    m_selPartZ = 0;
    m_bPartSelected = false;

    //
    // Find topmost selected particle
    //
//	animTcl::OutputMessage("m_no %d", p->m_no);
    for (size_t i(0); i<p->m_no; i++)
    {
        //
        // Get i-th particle position
        //
        pos = p->m_p[i].pos;

        //
        // Transform the center of particle into window coordinates
        //
        if (gluProject(pos[0], pos[1], pos[2], modelMatrix, projMatrix, viewport, &w[0], &w[1], &w[2]) == GL_FALSE)
        {
            // animTcl::OutputMessage("gluProject() has failed. Particle %d.\n", i);
            continue;
        }

        //
        // Transform a point on the surface of particle into window coordinates
        //
		if (gluProject(pos[0]+p->m_p_rad, pos[1], pos[2], modelMatrix, projMatrix, viewport, &w2[0], &w2[1], &w2[2]) == GL_FALSE)
        {
            //animTcl::OutputMessage("gluProject() has failed. Particle %d.\n", i);
            continue;
        }

        //
        // Find the radius of particle in window coordiantes
        //
        VectorObj wndRadiusVect;
        wndRadiusVect = w2-w;
        double radius = wndRadiusVect.length();
		
        //
        // Find the distance of mouse from the center of particle in window coordinates
        //
        double dx = w[0] - (double)mouseX;
        double dy = (double)mouseY-w[1];
		
        double dist = sqrt(dx*dx + dy*dy);
		

        if (dist <= 8*radius)
        {
            if (!m_bPartSelected)
            {
                m_selPartIdx = i;
                m_selPartZ = w[2];
                m_bPartSelected = true;
				animTcl::OutputMessage("Particle %d selected.",i);
            }
            else
            {
                if (w[2] < m_selPartZ)
                {
                    m_selPartIdx = i;
                    m_selPartZ = w[2];
					animTcl::OutputMessage("Particle %d selected.",i);
                }
            }
        }
	}
	int hits = glRenderMode(GL_RENDER);
	//processHits(hits,  &buffer[0], pickedObject);

}	// pickObject
// start or end interaction
void myMouse(int button, int state, int x, int y)
{

	// let the global resource manager know about the new state of the mouse 
	// button
	GlobalResourceManager::use()->setMouseButtonInfo( button, state );
	
	if( button == GLUT_LEFT_BUTTON && state == GLUT_DOWN )
	{
		animTcl::OutputMessage(
			"My mouse received a mouse button press event\n");
		BaseObject* obj = GlobalResourceManager::use()->getObject("partSys");
		if(obj!=NULL){
			GLint pickedObject;
			ParticleSystem * particle = (ParticleSystem*) obj;
			pickObject(x, y, &pickedObject,  particle);
		}

	}
	if( button == GLUT_LEFT_BUTTON && state == GLUT_UP )
	{
		animTcl::OutputMessage(
			"My mouse received a mouse button release event\n") ;
		BaseObject* obj = GlobalResourceManager::use()->getObject("partSys");
		if(obj!=NULL){
			ParticleSystem * particle = (ParticleSystem*) obj;
			if(m_bPartSelected){
				m_bPartSelected = false;
				m_selPartIdx = 999999;
				m_selPartX = m_selPartY = m_selPartZ = 0;
			}
		}
	}
}	// myMouse

// interaction (mouse motion)
void myMotion(int x, int y)
{

	GLMouseButtonInfo updatedMouseButtonInfo = 
		GlobalResourceManager::use()->getMouseButtonInfo();

	if( updatedMouseButtonInfo.button == GLUT_LEFT_BUTTON )
	{
		animTcl::OutputMessage(
			"My mouse motion callback received a mousemotion event\n") ;
		BaseObject* obj = GlobalResourceManager::use()->getObject("partSys");
		if(obj!=NULL){
			ParticleSystem * particle = (ParticleSystem*) obj;
			if(m_bPartSelected){
				Vector result;
				pickFromXYPlane(result, x, y);
				particle -> m_p[m_selPartIdx].pos.assign(result[0], result[1], particle->m_p[m_selPartIdx].pos.z());
				glutPostRedisplay();
			}
		}
	}

}	// myMotion


void MakeScene(void)
{

	/* 
	
	This is where you instantiate all objects, systems, and simulators and 
	register them with the global resource manager

	*/

	/* Particle Scene */

	bool success;
	/*
	// register a system
	SampleParticle* sphere1 = new SampleParticle( "sphere1" );

	success = GlobalResourceManager::use()->addSystem( sphere1, true );

	// make sure it was registered successfully
	assert( success );
	*/
	// register a system
	ParticleSystem* partSys = new ParticleSystem( "partSys" );

	success = GlobalResourceManager::use()->addSystem( partSys, true );

	// make sure it was registered successfully
	assert( success );



	// register a simulator
	ParticleSimulator* partSim = 
		new ParticleSimulator( "partSim", partSys );

	success = GlobalResourceManager::use()->addSimulator( partSim );

	// make sure it was registered successfully
	assert( success );

	/* END SAMPLE SCENE */

	// the following code shows you how to retrieve a system that was registered 
	// with the resource manager. 

	/*
	//retrieve Sample System
	BaseSystem* sampleSystemRetrieval;

	// retrieve the system
	sampleSystemRetrieval = 
		GlobalResourceManager::use()->getSystem( "sphere1" );

	// make sure you got it
	assert( sampleSystemRetrieval );
	*/
	BaseSystem* particleSystemRetrieval;

	// retrieve the particle system
	particleSystemRetrieval = 
		GlobalResourceManager::use()->getSystem( "partSys" );

	// make sure you got it
	assert( particleSystemRetrieval );



	BaseSimulator* particleSimulatorRetrieval;

	// retrieve the particlesimulator
	particleSimulatorRetrieval = 
		GlobalResourceManager::use()->getSimulator( "partSim" );

	// make sure you got it
	assert( particleSimulatorRetrieval );

}	// MakeScene

// OpenGL initialization
void myOpenGLInit(void)
{
	animTcl::OutputMessage("Initialization routine was called.");

}	// myOpenGLInit

void myIdleCB(void)
{
	
	return;

}	// myIdleCB

void myKey(unsigned char key, int x, int y)
{
	 animTcl::OutputMessage("My key callback received a key press event\n");
	return;

}	// myKey

int testGlobalCommand(ClientData clientData, Tcl_Interp *interp, int argc,	char **argv)
{
	 animTcl::OutputMessage("This is a test command!");
	return TCL_OK;

}	// testGlobalCommand

void mySetScriptCommands(Tcl_Interp *interp)
{

	// here you can register additional generic (they do not belong to any object) 
	// commands with the shell

	Tcl_CreateCommand(interp, "test",(Tcl_CmdProc*) testGlobalCommand, (ClientData) NULL,
					  (Tcl_CmdDeleteProc *)	NULL);

}	// mySetScriptCommands
