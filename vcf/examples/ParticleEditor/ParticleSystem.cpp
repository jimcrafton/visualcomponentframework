#include "ParticleSystem.h"

#include "vcf/FoundationKit/FoundationKit.h"
#include "ParticleResourceManager.h"

#include <fstream>

ParticleSystem::ParticleSystem(){
	mParticleResource=0;
	mFinished=false;
	mTotalTime=0;
}

ParticleSystem::~ParticleSystem(){
	int i;
	for(i=0;i<mParticles.size();i++){
		Particle &p=mParticles[i];
		if(p.mTrailingSystem){
			delete p.mTrailingSystem;
			p.mTrailingSystem=0;
		}
	}
}

void ParticleSystem::setParticleResource(ParticleResource *pr){
	mParticleResource=pr;
}

void ParticleSystem::update(float dt){
	int i;

	mTotalTime+=dt;

	if(mParticles.size()>mParticleResource->getAmount()){
		mParticles.resize(mParticleResource->getAmount());
	}
	else if(mParticles.size()<mParticleResource->getAmount()){
		int i=mParticles.size();
		mParticles.resize(mParticleResource->getAmount());
		for(;i<mParticles.size();i++){
			resetParticle(mParticles[i],mParticleResource->getGradualStart());
		}
	}

	bool stopSpawning=false;

	if(mParticleResource->getSystemLife()!=0 && mStartTime+mParticleResource->getSystemLife()<mTotalTime){
		stopSpawning=true;
	}

	for(i=0;i<mParticles.size();i++){
		Particle &p=mParticles[i];

		if(p.mLife<mTotalTime){
			if(p.mDead==false){
				if(mParticleResource->mEndingSystem!=""){
					ParticleResource *r=ParticleResourceManager::loadResource(mParticleResource->mEndingSystem);
					if(r){
						ParticleSystem *system=new ParticleSystem();
						system->setParticleResource(r);
						system->setTransformation(vrtoad::makeMatrix4x4(p.mPosition));
						mChildSystems.push_back(system);
					}
				}
			}

			if(stopSpawning==false){
				resetParticle(p);
			}
			else{
				p.mDead=true;
			}
		}
		else{
			float r=mParticleResource->getGravityVariance();
			vrtoad::Vector3 grav(vrtoad::randomFloat(-r,r),vrtoad::randomFloat(-r,r),vrtoad::randomFloat(-r,r)-mParticleResource->getGravity());
			grav*=800;
			p.mVelocity+=grav*dt*dt;
			p.mPosition+=mParticles[i].mVelocity*dt;
			if(p.mLife>0){
				float f=1.0f-(mParticles[i].mLife-mTotalTime)/mParticleResource->getParticleLife();
				p.mColor=vrtoad::linearInterpolate(mParticleResource->mStartColor,mParticleResource->mEndColor,f);
			}

			if(p.mTrailingSystem){
				p.mTrailingSystem->setTransformation(vrtoad::makeMatrix4x4(p.mPosition));
				p.mTrailingSystem->update(dt);
			}
		}
	}

	for(i=0;i<mChildSystems.size();i++){
		mChildSystems[i]->update(dt);
		if(mChildSystems[i]->isFinished()){
			delete mChildSystems[i];
			mChildSystems.erase(mChildSystems.begin()+i);
			i--;
		}
	}
}

void ParticleSystem::reset(){
	int i;

	// Clean out child systems
	while(mChildSystems.size()>0){
		delete mChildSystems[0];
		mChildSystems.erase(mChildSystems.begin()+0);
	}

	for(i=0;i<mParticles.size();i++){
		resetParticle(mParticles[i],mParticleResource->getGradualStart());
	}

	mStartTime=mTotalTime;
}

void ParticleSystem::resetParticle(Particle &p,bool gradual){
	float v=mParticleResource->getInitialVariance();
 
	p.mPosition=vrtoad::Vector3();
	p.mVelocity=vrtoad::Vector3(vrtoad::randomFloat(-v*10,v*10),vrtoad::randomFloat(-v*10,v*10),vrtoad::randomFloat(-v*10,v*10)+mParticleResource->getInitialSpeed()*10);
	p.mColor=mParticleResource->getStartColor();
	if(gradual){
		p.mDead=true;
		p.mLife=mTotalTime+vrtoad::randomFloat(0,1)*mParticleResource->getParticleLife();
	}
	else{
		p.mDead=false;
		p.mLife=mTotalTime+mParticleResource->getParticleLife();
	}

	if(p.mTrailingSystem){
		delete p.mTrailingSystem;
		p.mTrailingSystem=0;
	}
	if(mParticleResource->mTrailingSystem!=""){
		ParticleResource *r=ParticleResourceManager::loadResource(mParticleResource->mTrailingSystem);
		if(r){
			ParticleSystem *system=new ParticleSystem();
			system->setParticleResource(r);
			p.mTrailingSystem=system;
		}
	}
}

/**
*CVS Log info
*$Log$
*Revision 1.2  2004/12/01 04:15:10  ddiego
*merged over devmain-0-6-6 code. Marcello did a kick ass job
*of fixing a nasty bug (1074768VCF application slows down modal dialogs.)
*that he found. Many, many thanks for this Marcello.
*
*Revision 1.1.2.2  2004/11/01 17:19:00  marcelloptr
*just added few lines at the end of file
*
*Revision 1.1.2.1  2004/11/01 14:38:59  pallindo
*Initial checkin of the particle editor example.  Just shows off a more complex opengl application using the VCF.
*
*/



