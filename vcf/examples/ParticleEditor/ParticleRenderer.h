#ifndef PARTICLERENDERER_H
#define PARTICLERENDERER_H

#include "vcf/OpenGLKit/OpenGLKit.h"
#include "vcf/OpenGLKit/VCFOpenGL.h"

#include "vrtoad/Math.h"

class ParticleSystem;

class ParticleRenderer:public VCF::OpenGLControl{
public:
	ParticleRenderer();
	~ParticleRenderer();

	virtual void paint(VCF::GraphicsContext *context);

	virtual void setParticleSystem(ParticleSystem *ps);

	void setViewPoint(const vrtoad::Vector3 &origin){
		mViewOrigin=origin;
	}

	void renderParticleSystem(ParticleSystem *s);

protected:
	void renderVelocityAlignedParticleSystemWithoutVPs(ParticleSystem *s);

	inline void calculateRightUp(const vrtoad::Vector3 &velocity,vrtoad::Vector3 &right,vrtoad::Vector3 &up){
		right=vrtoad::cross(velocity,vrtoad::Vector3(0,0,-1));
		right=vrtoad::normalize(right);
		up=vrtoad::normalize(-velocity);
	}

	void renderScreenAlignedParticleSystemWithoutVPs(ParticleSystem *s);
	void renderParticleSystemWithVPs(ParticleSystem *s);

	void onTimer(VCF::TimerEvent *e);

	bool mInitialized;
	vrtoad::Vector3 mViewOrigin;
	double mLastTime;
	ParticleSystem *mParticleSystem;
	VCF::TimerComponent *mTimer;

	int mViewDirVP;
	int mVelDirVP;
	bool mUseVPs;
};

#endif

/**
$Id$
*/
