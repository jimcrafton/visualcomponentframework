#ifndef PARTICLESYSTEM_H
#define PARTICLESYSTEM_H

#include "ParticleResource.h"
#include <vrtoad/Math.h>

class ParticleSystem{
public:
	class Particle{
	public:
		Particle(){
			mColor=vrtoad::Vector4(1,1,1,1);
			mSize=vrtoad::Vector3(1,1,1);
			mLife=0;
			mDead=false;
			mTrailingSystem=0;
		}

		vrtoad::Vector3 mPosition;
		vrtoad::Vector3 mVelocity;
		vrtoad::Vector4 mColor;
		vrtoad::Vector3 mSize;
		float mLife;
		bool mDead;
		ParticleSystem *mTrailingSystem;
	};

	ParticleSystem();
	~ParticleSystem();

	void setParticleResource(ParticleResource *pr);

	void update(float dt);

	inline ParticleResource::ParticleType getType() const{
		return mParticleResource->getType();
	}

	inline ParticleResource::Blending getBlending() const{
		return mParticleResource->getBlending();
	}

	inline int getAmount() const{
		return mParticles.size();
	}

	inline ParticleResource::Alignment getAlignment() const{
		return mParticleResource->getAlignment();
	}

	inline const Particle &getParticle(int i) const{
		return mParticles[i];
	}

	void reset();

	inline void resetParticle(Particle &p,bool gradual=false);

	inline bool isFinished() const{return mFinished;}

	inline void setTransformation(const vrtoad::Matrix4x4 &trans){mTransformation=trans;}
	inline const vrtoad::Matrix4x4 &getTransformation() const{return mTransformation;}

	inline int getNumChildSystems(){return mChildSystems.size();}
	inline ParticleSystem *getChildSystem(int i){return mChildSystems[i];}

	ParticleResource *getParticleResource(){return mParticleResource;}

protected:
	ParticleResource *mParticleResource;
	std::vector<Particle> mParticles;
	bool mFinished;
	float mStartTime;
	float mTotalTime;
	std::vector<ParticleSystem*> mChildSystems;
	vrtoad::Matrix4x4 mTransformation;
};

#endif


/**
$Id$
*/
