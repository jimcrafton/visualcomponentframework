// Uncomment this line to enable the use of GLEW (Must have GLEW installed).
// This will then calculate the particle geometry in a vertex program, if available.
//#define USE_GLEW

#ifdef USE_GLEW
#	include "glew.h"
#	ifdef WIN32
#		pragma comment(lib,"glew32.lib")
#	endif
#endif

#ifdef WIN32
#	pragma comment(lib,"opengl32.lib")
#	pragma comment(lib,"glu32.lib")
#endif

#include "ParticleRenderer.h"
#include "ParticleSystem.h"

#include <fstream>
#include <string>

using namespace VCF;

#ifdef USE_GLEW
GLuint loadVertexProgramFromString(std::string str, GLuint id);
GLuint loadVertexProgram(const char *filename, GLuint id);
#endif

ParticleRenderer::ParticleRenderer():OpenGLControl(){
	mParticleSystem=0;

	mInitialized=false;

	mViewDirVP=0;
	mVelDirVP=0;

	mUseVPs=false;

	mTimer=new TimerComponent();
	mTimer->getTimerPulse().addHandler(new TimerEventHandler<ParticleRenderer>(this,&ParticleRenderer::onTimer));
	mTimer->setTimeoutInterval(10);
	mTimer->setActivated(true);
	addComponent(mTimer);
}

ParticleRenderer::~ParticleRenderer(){
	delete mParticleSystem;
}

void ParticleRenderer::paint(GraphicsContext *context){
	OpenGLControl::paint(context);

	if(mInitialized==false){
#		ifdef USE_GLEW
			std::cout << "Initializing GLEW" << std::endl;

			glewInit();

			if(GLEW_ARB_vertex_program){
				mViewDirVP=loadVertexProgram("viewdir.vp",0);
				mVelDirVP=loadVertexProgram("veldir.vp",0);

				if(mViewDirVP && mViewDirVP){
					mUseVPs=true;
				}
			}
#		endif

		mInitialized=true;
	}

	glViewport(0,0,getWidth(),getHeight());

	glClearColor(0.4f,0.7f,0.7f,1.0f);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90,1,1,1000);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(mViewOrigin.x,mViewOrigin.y,mViewOrigin.z, 0,0,0, 0,0,1);

	glPushAttrib(GL_COLOR_BUFFER_BIT|GL_CURRENT_BIT);

	renderParticleSystem(mParticleSystem);

	glPopAttrib();

	OpenGLControl::swapBuffers();
}

void ParticleRenderer::renderParticleSystem(ParticleSystem *s){
	if(s->getBlending()==ParticleResource::BLEND_NONE){
		glDisable(GL_BLEND);
	}
	else if(s->getBlending()==ParticleResource::BLEND_COLOR){
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_COLOR,GL_ONE_MINUS_SRC_COLOR);
	}
	else if(s->getBlending()==ParticleResource::BLEND_COLOR_ADDITIVE){
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_COLOR,GL_ONE);
	}
	else if(s->getBlending()==ParticleResource::BLEND_ALPHA){
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	}
	else if(s->getBlending()==ParticleResource::BLEND_ALPHA_ADDITIVE){
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA,GL_ONE);
	}

	if(s->getParticleResource()->mDepthTest){
		glEnable(GL_DEPTH_TEST);
	}
	else{
		glDisable(GL_DEPTH_TEST);
	}

	glPushMatrix();
	glMultMatrixf(s->getTransformation().getData());
	if(mUseVPs){
		renderParticleSystemWithVPs(s);
	}
	else{
		if(s->getAlignment()==ParticleResource::ALIGN_VIEW){
			renderScreenAlignedParticleSystemWithoutVPs(s);
		}
		else{
			renderVelocityAlignedParticleSystemWithoutVPs(s);
		}
	}
	glPopMatrix();

	int i;
	for(i=0;i<s->getNumChildSystems();i++){
		renderParticleSystem(s->getChildSystem(i));
	}

	if(s->getParticleResource()->mTrailingSystem!=""){
		for(i=0;i<s->getAmount();i++){
			if(s->getParticle(i).mTrailingSystem){
				renderParticleSystem(s->getParticle(i).mTrailingSystem);
			}
		}
	}
}

void ParticleRenderer::renderVelocityAlignedParticleSystemWithoutVPs(ParticleSystem *s){
	if(s->getType()==ParticleResource::TYPE_POINTS){
		glBegin(GL_POINTS);
		int i;
		for(i=0;i<s->getAmount();i++){
			const ParticleSystem::Particle &p=s->getParticle(i);
			if(p.mDead==false){
				glColor4fv(p.mColor.getData());
				glVertex3fv(p.mPosition.getData());
			}
		}
		glEnd();
	}
	else if(s->getType()==ParticleResource::TYPE_LINES){
		glBegin(GL_LINES);
		int i;
		for(i=0;i<s->getAmount();i++){
			const ParticleSystem::Particle &p=s->getParticle(i);
			if(p.mDead==false){
				vrtoad::Vector3 right,up;
				calculateRightUp(p.mVelocity,right,up);

				glColor4fv(p.mColor.getData());
				glVertex3fv(p.mPosition.getData());
				glVertex3fv((p.mPosition+up*p.mSize).getData());
			}
		}
		glEnd();
	}
	else if(s->getType()==ParticleResource::TYPE_TRIANGLES){
		glBegin(GL_TRIANGLES);
		int i;
		for(i=0;i<s->getAmount();i++){
			const ParticleSystem::Particle &p=s->getParticle(i);
			if(p.mDead==false){
				vrtoad::Vector3 right,up;
				calculateRightUp(p.mVelocity,right,up);

				glColor4fv(p.mColor.getData());
				glVertex3fv((p.mPosition-right*p.mSize).getData());
				glVertex3fv((p.mPosition-up*p.mSize).getData());
				glVertex3fv((p.mPosition+right*p.mSize).getData());
			}
		}
		glEnd();
	}
	else if(s->getType()==ParticleResource::TYPE_QUADS){
		glBegin(GL_QUADS);
		int i;
		for(i=0;i<s->getAmount();i++){
			const ParticleSystem::Particle &p=s->getParticle(i);
			if(p.mDead==false){
				vrtoad::Vector3 right,up;
				calculateRightUp(p.mVelocity,right,up);

				glColor4fv(p.mColor.getData());
				glVertex3fv((p.mPosition+(-up-right)*p.mSize).getData());
				glVertex3fv((p.mPosition+(up-right)*p.mSize).getData());
				glVertex3fv((p.mPosition+(up+right)*p.mSize).getData());
				glVertex3fv((p.mPosition+(-up+right)*p.mSize).getData());
			}
		}
		glEnd();
	}
}

void ParticleRenderer::renderScreenAlignedParticleSystemWithoutVPs(ParticleSystem *s){
	vrtoad::Matrix4x4 mv;

	glGetFloatv(GL_MODELVIEW_MATRIX,mv.getData());

	vrtoad::Vector3 right(mv.at(0,0),mv.at(0,1),mv.at(0,2));
	vrtoad::Vector3 up(mv.at(1,0),mv.at(1,1),mv.at(1,2));

	if(s->getType()==ParticleResource::TYPE_POINTS){
		glBegin(GL_POINTS);
		int i;
		for(i=0;i<s->getAmount();i++){
			const ParticleSystem::Particle &p=s->getParticle(i);
			if(p.mDead==false){
				glColor4fv(p.mColor.getData());
				glVertex3fv(p.mPosition.getData());
			}
		}
		glEnd();
	}
	else if(s->getType()==ParticleResource::TYPE_LINES){
		glBegin(GL_LINES);
		int i;
		for(i=0;i<s->getAmount();i++){
			const ParticleSystem::Particle &p=s->getParticle(i);
			if(p.mDead==false){
				glColor4fv(p.mColor.getData());
				glVertex3fv(p.mPosition.getData());
				glVertex3fv((p.mPosition+up*p.mSize).getData());
			}
		}
		glEnd();
	}
	else if(s->getType()==ParticleResource::TYPE_TRIANGLES){
		glBegin(GL_TRIANGLES);
		int i;
		for(i=0;i<s->getAmount();i++){
			const ParticleSystem::Particle &p=s->getParticle(i);
			if(p.mDead==false){
				glColor4fv(p.mColor.getData());
				glVertex3fv((p.mPosition-right*p.mSize).getData());
				glVertex3fv((p.mPosition-up*p.mSize).getData());
				glVertex3fv((p.mPosition+right*p.mSize).getData());
			}
		}
		glEnd();
	}
	else if(s->getType()==ParticleResource::TYPE_QUADS){
		glBegin(GL_QUADS);
		int i;
		for(i=0;i<s->getAmount();i++){
			const ParticleSystem::Particle &p=s->getParticle(i);
			if(p.mDead==false){
				glColor4fv(p.mColor.getData());
				glVertex3fv((p.mPosition+(-up-right)*p.mSize).getData());
				glVertex3fv((p.mPosition+(up-right)*p.mSize).getData());
				glVertex3fv((p.mPosition+(up+right)*p.mSize).getData());
				glVertex3fv((p.mPosition+(-up+right)*p.mSize).getData());
			}
		}
		glEnd();
	}
}

#ifdef USE_GLEW
void ParticleRenderer::renderParticleSystemWithVPs(ParticleSystem *s){
	int count=0;

	glPushMatrix();
	glLoadIdentity();
	if(s->getAlignment()==ParticleResource::ALIGN_VIEW){
		glLightfv(GL_LIGHT0,GL_POSITION,vrtoad::Vector4(0,0,1,0).getData());
		glBindProgramARB(GL_VERTEX_PROGRAM_ARB,mViewDirVP);
	}
	else if(s->getAlignment()==ParticleResource::ALIGN_VELOCITY){
		glLightfv(GL_LIGHT0,GL_POSITION,vrtoad::Vector4(0,0,1,0).getData());
		glBindProgramARB(GL_VERTEX_PROGRAM_ARB,mVelDirVP);
	}
	glPopMatrix();

	glProgramLocalParameter4fARB(GL_VERTEX_PROGRAM_ARB,8,0,0,-1,0);
	glEnable(GL_VERTEX_PROGRAM_ARB);

	if(s->getType()==ParticleResource::TYPE_POINTS){
		glProgramLocalParameter4fARB(GL_VERTEX_PROGRAM_ARB,0,0,0,0,0);

		glBegin(GL_POINTS);
		count=1;
	}
	else if(s->getType()==ParticleResource::TYPE_LINES){
		// TODO: Figure out why this has to be 0.01 and not 0
		glProgramLocalParameter4fARB(GL_VERTEX_PROGRAM_ARB,0,0.001f,-1,0,0);
		glProgramLocalParameter4fARB(GL_VERTEX_PROGRAM_ARB,1,0.001f, 1,0,0);

		glBegin(GL_LINES);
		count=2;
	}
	else if(s->getType()==ParticleResource::TYPE_TRIANGLES){
		// TODO: Figure out why this has to be 0.01 and not 0
		glProgramLocalParameter4fARB(GL_VERTEX_PROGRAM_ARB,0,-1,1,0,0);
		glProgramLocalParameter4fARB(GL_VERTEX_PROGRAM_ARB,1,0.001f,-1,0,0);
		glProgramLocalParameter4fARB(GL_VERTEX_PROGRAM_ARB,2,1, 1,0,0);

		glBegin(GL_TRIANGLES);
		count=3;
	}
	else if(s->getType()==ParticleResource::TYPE_QUADS){
		glProgramLocalParameter4fARB(GL_VERTEX_PROGRAM_ARB,0,-1,-1,0,0);
		glProgramLocalParameter4fARB(GL_VERTEX_PROGRAM_ARB,1,-1, 1,0,0);
		glProgramLocalParameter4fARB(GL_VERTEX_PROGRAM_ARB,2, 1, 1,0,0);
		glProgramLocalParameter4fARB(GL_VERTEX_PROGRAM_ARB,3, 1,-1,0,0);

		glBegin(GL_QUADS);
		count=4;
	}

	int i;
	for(i=0;i<s->getAmount();i++){
		const ParticleSystem::Particle &p=s->getParticle(i);
		if(p.mDead==false){
			glVertexAttrib3fvARB(1,p.mPosition.getData());
			glVertexAttrib3fvARB(2,p.mVelocity.getData());
			glVertexAttrib4fvARB(3,p.mColor.getData());
			glVertexAttrib3fvARB(4,p.mSize.getData());
//			glVertexAttrib3fvARB(5,p.mPositionB.getData());
//			glVertexAttrib3fvARB(6,p.mVelocityB.getData());

			int j;
			for(j=0;j<count;j++){
				glVertexAttrib1fARB(0,j);
			}
		}
	}

	glEnd();

	glDisable(GL_VERTEX_PROGRAM_ARB);
}
#else
void ParticleRenderer::renderParticleSystemWithVPs(ParticleSystem *s){;}
#endif

void ParticleRenderer::setParticleSystem(ParticleSystem *ps){
	mParticleSystem=ps;
}

void ParticleRenderer::onTimer(VCF::TimerEvent *e){
	static long last=DateTime::now().getMilliseconds();
	long current=DateTime::now().getMilliseconds();
	float dt=(current-last)*0.001;

	if(dt>0){
		last=current;
		mParticleSystem->update(dt);
		repaint();
	}
}

#ifdef USE_GLEW
using namespace std;

GLuint loadVertexProgram(const char *filename, GLuint id)
{
	ifstream in(filename);
    string str;
    
    if(!in.good())
    {
        cerr << "Error opening " << filename << endl;
        return 0;
    }
    
    const int bufsize = 100;
    char buf[bufsize];
  
    do
    {
        in.read(buf, bufsize);
        str.append(buf, in.gcount());
    }
    while(!in.eof());

    in.close();

    cout << "VP loaded from " << filename << endl;

    return loadVertexProgramFromString(str, id);
} 

GLuint loadVertexProgramFromString(string str, GLuint id)
{
    GLuint prog;
    
    if(id == 0)
    {
        glGenProgramsARB(1, &prog);
    }
    else
        prog = id;
    
    GLenum err = glGetError();
    if (err != GL_NO_ERROR)
    {
        cerr << "glProgramStringARB precheck failed:"
                 << gluErrorString(err) << endl;
        return 0;
    }
       
    glBindProgramARB(GL_VERTEX_PROGRAM_ARB, prog);
    
    glProgramStringARB(GL_VERTEX_PROGRAM_ARB, GL_PROGRAM_FORMAT_ASCII_ARB,
                            (GLsizei)str.size(), str.c_str());
    
    err = glGetError();

    if(err == GL_INVALID_OPERATION)
    {
        // print compiler error
        GLint pos;   
        glGetIntegerv(GL_PROGRAM_ERROR_POSITION_ARB, &pos);

        cerr << "Error " << glGetString(GL_PROGRAM_ERROR_STRING_ARB)
             << " at " << pos << " compiling vertex program!" << endl;
             
        int start = 0, end, line = 0;

        for(end = 0; end < static_cast<int>(str.size()); ++end)
        {
            if(str[end] == '\n')
            {
                ++line;

                if(pos < end)
                    break;

                start = end + 1;
            }
        }

        std::string mesg;
        std::string loc;

        for(int i = start; i < end; ++i)
        {
            if(i == pos)
            {
                loc += '^';
            }
            else if(i < pos)
                loc += '-';
            else
                loc += ' ';

            mesg += str[i];
        }

        cerr << mesg << endl << loc << endl;
        return 0;
    }
    else if (err != GL_NO_ERROR) {
        cerr << "glProgramStringARB postcheck failed:"
                 << gluErrorString(err) << endl;
        return 0;
    }
    
    return prog;
}
#endif

/**
*CVS Log info
*$Log$
*Revision 1.2  2004/12/01 04:15:09  ddiego
*merged over devmain-0-6-6 code. Marcello did a kick ass job
*of fixing a nasty bug (1074768VCF application slows down modal dialogs.)
*that he found. Many, many thanks for this Marcello.
*
*Revision 1.1.2.3  2004/11/04 14:26:59  pallindo
*Fixed screen aligned particles when not using GLEW
*
*Revision 1.1.2.2  2004/11/01 17:19:00  marcelloptr
*just added few lines at the end of file
*
*Revision 1.1.2.1  2004/11/01 14:38:59  pallindo
*Initial checkin of the particle editor example.  Just shows off a more complex opengl application using the VCF.
*
*/


