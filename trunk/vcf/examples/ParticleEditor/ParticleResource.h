#ifndef PARTICLERESOURCE_H
#define PARTICLERESOURCE_H

#include <vector>
#include <string>
#include <vrtoad/Math.h>

class ParticleResource{
public:
	enum ParticleType{
		TYPE_POINTS=0,
		TYPE_LINES,
		TYPE_TRIANGLES,
		TYPE_QUADS,
	};

	enum Alignment{
		ALIGN_VIEW=0,
		ALIGN_VELOCITY,
	};

	enum Blending{
		BLEND_NONE=0,
		BLEND_COLOR,
		BLEND_COLOR_ADDITIVE,
		BLEND_ALPHA,
		BLEND_ALPHA_ADDITIVE,
	};

	ParticleResource(){
		mType=TYPE_POINTS;
		mAlignment=ALIGN_VIEW;
		mAmount=10;
		mParticleLife=5;
		mSystemLife=0;
		mGradualStart=true;
		mBlending=BLEND_NONE;
		mStartColor=vrtoad::Vector4(1,1,1,1);
		mEndColor=vrtoad::Vector4(1,1,1,1);
		mInitialSpeed=1.0f;
		mInitialVariance=0.1f;
		mGravity=1.0f;
		mGravityVariance=0.1f;
		mDepthTest=false;
		mTriangles=false;
	}

	inline void setType(ParticleType type){mType=type;}
	inline ParticleType getType() const{return mType;}

	inline void setAlignment(Alignment align){mAlignment=align;}
	inline Alignment getAlignment() const{return mAlignment;}

	inline void setAmount(int amt){mAmount=amt;}
	inline int getAmount() const{return mAmount;}

	inline void setParticleLife(float life){mParticleLife=life;}
	inline float getParticleLife() const{return mParticleLife;}

	inline void setSystemLife(float life){mSystemLife=life;}
	inline float getSystemLife() const{return mSystemLife;}

	inline void setGradualStart(bool b){mGradualStart=b;}
	inline bool getGradualStart() const{return mGradualStart;}

	inline void setBlending(Blending b){mBlending=b;}
	inline Blending getBlending() const{return mBlending;}

	inline void setStartColor(const vrtoad::Vector4 &c){mStartColor=c;}
	inline const vrtoad::Vector4 &getStartColor() const{return mStartColor;}

	inline void setEndColor(const vrtoad::Vector4 &c){mEndColor=c;}
	inline const vrtoad::Vector4 &getEndColor() const{return mEndColor;}

	inline void setInitialSpeed(float s){mInitialSpeed=s;}
	inline float getInitialSpeed() const{return mInitialSpeed;}

	inline void setInitialVariance(float v){mInitialVariance=v;}
	inline float getInitialVariance() const{return mInitialVariance;}

	inline void setGravity(float v){mGravity=v;}
	inline float getGravity() const{return mGravity;}

	inline void setGravityVariance(float v){mGravityVariance=v;}
	inline float getGravityVariance() const{return mGravityVariance;}

	std::string mName;
	ParticleType mType;
	Alignment mAlignment;
	int mAmount;
	float mParticleLife;
	float mSystemLife;
	bool mGradualStart;
	float mInitialSpeed;
	float mInitialVariance;
	float mGravity;
	float mGravityVariance;
	Blending mBlending;
	bool mDepthTest;
	vrtoad::Vector4 mStartColor;
	vrtoad::Vector4 mEndColor;
	std::vector<std::string> mTextures;
	std::string mTrailingSystem;
	std::string mEndingSystem;
	bool mTriangles;
};

#endif

/**
$Id$
*/
