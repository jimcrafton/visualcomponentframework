/*	Math.h: the vrtoad::Math classes
	Author: Alan Fischer
	Email: siralanf_at_lightningtoads_dot_com
	Date: 9/21/03
	Note: These are untemplated because VC6 fails to optimized templates effectivly.
*/

#ifndef VRTOAD_MATH_H
#define VRTOAD_MATH_H

#if defined(WIN32) && defined(_MSC_VER)
#	define inline __forceinline
#	pragma warning(disable:4244)
#endif

#ifdef __BORLANDC__
#include <cstdlib>
#include <cmath>
using std::srand;
using std::rand;
using std::sqrt;
using std::acos;
using std::asin;
using std::cos;
using std::sin;
using std::atan2;
using std::exp;
using std::log;
using std::fabs;
using std::itoa;
using std::putenv;
using std::ultoa;
using std::swab;
#define _itoa itoa
#define _ultoa ultoa
#define _putenv putenv
#define _swab swab
#else
#include <math.h>
#include <stdlib.h>
#endif
#include <vector>

#ifdef VRTOAD_MATH_DOUBLE
#	define cos cos
#	define sin sin
#	define sqrt sqrt
#	define vrReal double
#else
#ifndef __BORLANDC__
#	define cos cosf
#	define sin sinf
#	if 1
#		define sqrt sqrtf
#	else
#		define sqrt fastsqrt
#	endif
#endif
#	define vrReal float
#endif

namespace vrtoad{

//Constants
const vrReal vrEpsilon=		(vrReal)0.001;
const vrReal vrInfinity=	(vrReal)100000000;
const vrReal vrSqrt2=		(vrReal)1.41421356237309504880168;
const vrReal vrPi=			(vrReal)3.14159265358979323846264;

template<class T> inline T Max(const T &t1,const T &t2){
	return ((t1>t2)?t1:t2);
}

template<class T> inline T Min(const T &t1,const T &t2){
	return ((t1<t2)?t1:t2);
}

template<class T> inline T abs(const T &t1){
	return ((t1>0)?t1:-t1);
}

template<class T> inline T square(const T &t1){
	return t1*t1;
}

template<class T> inline T linearInterpolate(const T &t1,const T &t2,vrReal time){
	return t1*(1-time)+t2*time;
}

template<class T1,class T2,class T3> inline T3 clamp(const T1 low,const T2 high,const T3 value){
        if(value<low)
                return low;
        if(value>high)
                return high;
        return value;
}

template<class T> inline bool finite(const T &t){
	return t==t;
}

//These two methods aren't templated, because otherwise if you call toRad(90), it will treat it as an integer, which is BAD
inline vrReal toRad(vrReal deg){
	return vrReal(deg*(vrReal)(vrPi/180.0));
}

inline vrReal toDeg(vrReal rad){
	return vrReal(rad*(vrReal)(180.0/vrPi));
}

#define setBit(v,b) (v|=b)
#define clearBit(v,b) (v&=~b)
#define isBitSet(v,b) (v&b)

inline void setRandomSeed(unsigned int seed){
	srand(seed);
}

//For some reason it appears that the random number functions sometime return numbers equal to upper
inline float randomFloat(float lower,float upper){
	float r=(float)rand()/(float)RAND_MAX*(upper-lower)+lower;
	if(r>=upper){r=lower;}
	return r;
}

inline int randomInt(int lower,int upper){
	int r=(int)((float)rand()/(float)RAND_MAX*(float)(upper-lower))+lower;
	if(r>=upper){r=lower;}
	return r;
}

float fastsqrt(float n);

//Vector2
class Vector2{
public:
	vrReal x,y;

	inline Vector2():x(0),y(0){}

	inline Vector2(vrReal x1,vrReal y1):x(x1),y(y1){}

	inline vrReal *getData(){return (vrReal*)&x;}
	inline const vrReal *getData() const{return (vrReal*)&x;}

	inline bool operator==(const Vector2 &vec) const{
		return (vec.x==x && vec.y==y);
	}

	inline bool operator!=(const Vector2 &vec) const{
		return (vec.x!=x || vec.y!=y);
	}

	inline Vector2 operator+(const Vector2 &vec) const{
		return Vector2(x+vec.x,y+vec.y);
	}

	inline void operator+=(const Vector2 &vec){
		x+=vec.x;
		y+=vec.y;
	}

	inline Vector2 operator-(const Vector2 &vec) const{
		return Vector2(x-vec.x,y-vec.y);
	}

	inline void operator-=(const Vector2 &vec){
		x-=vec.x;
		y-=vec.y;
	}

	inline Vector2 operator*(vrReal f) const{
		return Vector2(x*f,y*f);
	}

	inline void operator*=(vrReal f){
		x*=f;
		y*=f;
	}

	inline Vector2 operator*(const Vector2 &vec) const{
		return Vector2(x*vec.x,y*vec.y);
	}

	inline void operator*=(const Vector2 &vec){
		x*=vec.x;
		y*=vec.y;
	}

	inline Vector2 operator/(vrReal f) const{
		f=1/f;
		return Vector2(x*f,y*f);
	}

	inline void operator/=(vrReal f){
		f=1/f;
		x*=f;
		y*=f;
	}

	inline Vector2 operator/(const Vector2 &vec) const{
		return Vector2(x/vec.x,y/vec.y);
	}

	inline void operator/=(const Vector2 &vec){
		x/=vec.x;
		y/=vec.y;
	}

	inline Vector2 operator-() const{
		return Vector2(-x,-y);
	}

	inline vrReal &operator[](int i){
		return *(&x+i);
	}

	inline vrReal operator[](int i) const{
		return *(&x+i);
	}

	//TODO: Remove these on the vectors.  They're not "well defined" operations
	inline bool operator>(const Vector2 &vec) const{
		return (x>vec.x && y>vec.y);
	}

	inline bool operator<(const Vector2 &vec) const{
		return (x<vec.x && y<vec.y);
	}

	inline bool operator>=(const Vector2 &vec) const{
		return (x>=vec.x && y>=vec.y);
	}

	inline bool operator<=(const Vector2 &vec) const{
		return (x<=vec.x && y<=vec.y);
	}
};

inline Vector2 operator*(vrReal scalar,const Vector2 &vector){
	return Vector2(vector.x*scalar,vector.y*scalar);
}

inline vrReal lengthSquared(const Vector2 &vec){
	return vec.x*vec.x+vec.y*vec.y;
}

inline vrReal length(const Vector2 &vec){
	return (vrReal)sqrt((vrReal)(vec.x*vec.x+vec.y*vec.y));
}

// TODO: return void?
inline Vector2 normalize(Vector2 &vec){
	vrReal l=1/length(vec);
	vec.x*=l;
	vec.y*=l;
	return vec;
}

inline Vector2 normalize(const Vector2 &vec){
	vrReal l=1/length(vec);
	Vector2 vec2;
	vec2.x=vec.x*l;
	vec2.y=vec.y*l;
	return vec2;
}

//Vector3
class Vector3{
public:
	vrReal x,y,z;

	inline Vector3():x(0),y(0),z(0){}

	inline Vector3(vrReal x1,vrReal y1,vrReal z1):x(x1),y(y1),z(z1){}

	inline Vector3(const Vector2 &vec,vrReal z1){
		x=vec.x;y=vec.y;z=z1;
	}

	inline vrReal *getData(){return (vrReal*)&x;}
	inline const vrReal *getData() const{return (vrReal*)&x;}

	inline bool operator==(const Vector3 &vec) const{
		return (vec.x==x && vec.y==y && vec.z==z);
	}

	inline bool operator!=(const Vector3 &vec) const{
		return (vec.x!=x || vec.y!=y || vec.z!=z);
	}

	inline Vector3 operator+(const Vector3 &vec) const{
		return Vector3(x+vec.x,y+vec.y,z+vec.z);
	}

	inline void operator+=(const Vector3 &vec){
		x+=vec.x;
		y+=vec.y;
		z+=vec.z;
	}

	inline Vector3 operator-(const Vector3 &vec) const{
		return Vector3(x-vec.x,y-vec.y,z-vec.z);
	}

	inline void operator-=(const Vector3 &vec){
		x-=vec.x;
		y-=vec.y;
		z-=vec.z;
	}

	inline Vector3 operator*(vrReal f) const{
		return Vector3(x*f,y*f,z*f);
	}

	inline void operator*=(vrReal f){
		x*=f;
		y*=f;
		z*=f;
	}

	inline Vector3 operator*(const Vector3 &vec) const{
		return Vector3(x*vec.x,y*vec.y,z*vec.z);
	}

	inline void operator*=(const Vector3 &vec){
		x*=vec.x;
		y*=vec.y;
		z*=vec.z;
	}

	inline Vector3 operator/(vrReal f) const{
		f=1/f;
		return Vector3(x*f,y*f,z*f);
	}

	inline void operator/=(vrReal f){
		f=1/f;
		x*=f;
		y*=f;
		z*=f;
	}

	inline Vector3 operator/(const Vector3 &vec) const{
		return Vector3(x/vec.x,y/vec.y,z/vec.z);
	}

	inline void operator/=(const Vector3 &vec){
		x/=vec.x;
		y/=vec.y;
		z/=vec.z;
	}

	inline Vector3 operator-() const{
		return Vector3(-x,-y,-z);
	}

	inline vrReal &operator[](int i){
		return *(&x+i);
	}

	inline vrReal operator[](int i) const{
		return *(&x+i);
	}

	inline bool operator>(const Vector3 &vec) const{
		return (x>vec.x && y>vec.y && z>vec.z);
	}

	inline bool operator<(const Vector3 &vec) const{
		return (x<vec.x && y<vec.y && z<vec.z);
	}

	inline bool operator>=(const Vector3 &vec) const{
		return (x>=vec.x && y>=vec.y && z>=vec.z);
	}

	inline bool operator<=(const Vector3 &vec) const{
		return (x<=vec.x && y<=vec.y && z<=vec.z);
	}
};

const Vector3 vrRight(1,0,0);
const Vector3 vrForward(0,1,0);
const Vector3 vrUp(0,0,1);

inline vrReal lengthSquared(const Vector3 &vec){
	return vec.x*vec.x+vec.y*vec.y+vec.z*vec.z;
}

inline vrReal length(const Vector3 &vec){
	return (vrReal)sqrt((vrReal)(vec.x*vec.x+vec.y*vec.y+vec.z*vec.z));
}

// TODO: return void?
inline Vector3 normalize(Vector3 &vec){
	vrReal l=1/length(vec);
	vec.x*=l;
	vec.y*=l;
	vec.z*=l;
	return vec;
}

inline Vector3 normalize(const Vector3 &vec){
	vrReal l=1/length(vec);
	Vector3 vec2;
	vec2.x=vec.x*l;
	vec2.y=vec.y*l;
	vec2.z=vec.z*l;
	return vec2;
}

// To keep code clean, use this for an XYZ Euler angle, instead of a Vector
typedef Vector3 EulerAngle;

inline EulerAngle toRad(const EulerAngle &deg){
	return EulerAngle(toRad(deg.x),toRad(deg.y),toRad(deg.z));
}

inline EulerAngle toDeg(const EulerAngle &deg){
	return EulerAngle(toDeg(deg.x),toDeg(deg.y),toDeg(deg.z));
}

inline Vector3 cross(const Vector3 &vec1,const Vector3 &vec2){
	return Vector3(vec1.y*vec2.z-vec1.z*vec2.y,vec1.z*vec2.x-vec1.x*vec2.z,vec1.x*vec2.y-vec1.y*vec2.x);
}

inline Vector3 operator*(vrReal scalar,const Vector3 &vector){
	return Vector3(vector.x*scalar,vector.y*scalar,vector.z*scalar);
}

inline vrReal dot(const Vector3 &vec1,const Vector3 &vec2){
	return vec1.x*vec2.x+vec1.y*vec2.y+vec1.z*vec2.z;
}

inline Vector3 reflectVector(const Vector3 &vec,const Vector3 &norm){
	return norm*(2*dot(vec,norm))-vec;
}

void setVectorsFromEulerAngles(const EulerAngle &angles,Vector3 &forward,Vector3 &up,Vector3 &right);

vrReal getXYAngle(const Vector3 &vec1,const Vector3 &vec2);

inline vrReal angleBetween(const Vector3 &vec1,const Vector3 &vec2){
	return acos(dot(vec1,vec2));
}

//Vector4
class Vector4{
public:
	vrReal x,y,z,w;

	inline Vector4():x(0),y(0),z(0),w(0){}

	inline Vector4(vrReal x1,vrReal y1,vrReal z1,vrReal w1):x(x1),y(y1),z(z1),w(w1){}

	inline Vector4(const Vector3 &vec,vrReal w1){
		x=vec.x;y=vec.y;z=vec.z;w=w1;
	}

	inline vrReal *getData(){return (vrReal*)&x;}
	inline const vrReal *getData() const{return (vrReal*)&x;}

	inline bool operator==(const Vector4 &vec) const{
		return (vec.x==x && vec.y==y && vec.z==z && vec.w==w);
	}

	inline bool operator!=(const Vector4 &vec) const{
		return (vec.x!=x || vec.y!=y || vec.z!=z || vec.w!=w);
	}

	inline Vector4 operator+(const Vector4 &vec) const{
		return Vector4(x+vec.x,y+vec.y,z+vec.z,w+vec.w);
	}

	inline void operator+=(const Vector4 &vec){
		x+=vec.x;
		y+=vec.y;
		z+=vec.z;
		w+=vec.w;
	}

	inline Vector4 operator-(const Vector4 &vec) const{
		return Vector4(x-vec.x,y-vec.y,z-vec.z,w-vec.w);
	}

	inline void operator-=(const Vector4 &vec){
		x-=vec.x;
		y-=vec.y;
		z-=vec.z;
		w-=vec.w;
	}

	inline Vector4 operator*(vrReal f) const{
		return Vector4(x*f,y*f,z*f,w*f);
	}

	inline void operator*=(vrReal f){
		x*=f;
		y*=f;
		z*=f;
		w*=f;
	}

	inline Vector4 operator*(const Vector4 &vec) const{
		return Vector4(x*vec.x,y*vec.y,z*vec.z,w*vec.w);
	}

	inline void operator*=(const Vector4 &vec){
		x*=vec.x;
		y*=vec.y;
		z*=vec.z;
		w*=vec.w;
	}

	inline Vector4 operator/(vrReal f) const{
		f=1/f;
		return Vector4(x*f,y*f,z*f,w*f);
	}

	inline void operator/=(vrReal f){
		f=1/f;
		x*=f;
		y*=f;
		z*=f;
		w*=f;
	}

	inline void operator/=(const Vector4 &vec){
		x/=vec.x;
		y/=vec.y;
		z/=vec.z;
		w/=vec.w;
	}

	inline Vector4 operator-() const{
		return Vector4(-x,-y,-z,-w);
	}

	inline vrReal &operator[](int i){
		return *(&x+i);
	}

	inline vrReal operator[](int i) const{
		return *(&x+i);
	}
};

inline vrReal length(const Vector4 &vec){
	return (vrReal)sqrt((vrReal)(vec.x*vec.x+vec.y*vec.y+vec.z*vec.z+vec.w*vec.w));
}

// TODO: return void?
inline Vector4 normalize(Vector4 &vec){
	vrReal l=1/length(vec);
	vec.x*=l;
	vec.y*=l;
	vec.z*=l;
	vec.w*=l;
	return vec;
}

inline Vector4 normalize(const Vector4 &vec){
	vrReal l=1/length(vec);
	Vector4 vec2;
	vec2.x=vec.x*l;
	vec2.y=vec.y*l;
	vec2.z=vec.z*l;
	vec2.w=vec.w*l;
	return vec2;
}

inline Vector4 operator*(vrReal scalar,const Vector4 &vector){
	return Vector4(vector.x*scalar,vector.y*scalar,vector.z*scalar,vector.w*scalar);
}

inline vrReal dot(const Vector4 &vec1,const Vector4 &vec2){
	return vec1.x*vec2.x+vec1.y*vec2.y+vec1.z*vec2.z+vec1.w*vec2.w;
}

//Matrix3x3
class Matrix3x3{
public:
	vrReal data[9];

	class RowAccessor{
	public:
		inline RowAccessor(Matrix3x3 *m,int r){
			matrix=m;
			row=r;
		}

		inline vrReal &operator[](int col){
			return matrix->at(row,col);
		}

		inline vrReal operator[](int col) const{
			return matrix->at(row,col);
		}

		Matrix3x3 *matrix;
		int row;
	};

	inline Matrix3x3(){
		data[0]=1;data[3]=0;data[6]=0;
		data[1]=0;data[4]=1;data[7]=0;
		data[2]=0;data[5]=0;data[8]=1;
	}

	inline Matrix3x3(vrReal x1,vrReal x2,vrReal x3,vrReal y1,vrReal y2,vrReal y3,vrReal z1,vrReal z2,vrReal z3){
		data[0]=x1;data[3]=x2;data[6]=x3;
		data[1]=y1;data[4]=y2;data[7]=y3;
		data[2]=z1;data[5]=z2;data[8]=z3;
	}

	inline RowAccessor operator[](int row){
		return RowAccessor(this,row);
	}

	inline vrReal at(int row,int col) const{
		return data[col*3+row];
	}

	inline vrReal &at(int row,int col){
		return data[col*3+row];
	}

	inline vrReal *getData(){return (vrReal*)data;}
	inline const vrReal *getData() const{return (vrReal*)data;}

	inline bool operator==(const Matrix3x3 &m2) const{
		return	data[0]==m2.data[0] && data[1]==m2.data[1] && data[2]==m2.data[2] &&
				data[3]==m2.data[3] && data[4]==m2.data[4] && data[5]==m2.data[5] &&
				data[6]==m2.data[6] && data[7]==m2.data[7] && data[8]==m2.data[8];
	}

	inline bool operator!=(const Matrix3x3 &m2) const{
		return	!(*this==m2);
	}

	Matrix3x3 operator*(const Matrix3x3 &m2) const{
		Matrix3x3 dest;

#define A(row,col)  at(row,col)
#define B(row,col)  m2.at(row,col)
#define D(row,col)  dest.at(row,col)

		D(0,0)=A(0,0)*B(0,0)+A(0,1)*B(1,0)+A(0,2)*B(2,0);
		D(0,1)=A(0,0)*B(0,1)+A(0,1)*B(1,1)+A(0,2)*B(2,1);
		D(0,2)=A(0,0)*B(0,2)+A(0,1)*B(1,2)+A(0,2)*B(2,2);

		D(1,0)=A(1,0)*B(0,0)+A(1,1)*B(1,0)+A(1,2)*B(2,0);
		D(1,1)=A(1,0)*B(0,1)+A(1,1)*B(1,1)+A(1,2)*B(2,1);
		D(1,2)=A(1,0)*B(0,2)+A(1,1)*B(1,2)+A(1,2)*B(2,2);

		D(2,0)=A(2,0)*B(0,0)+A(2,1)*B(1,0)+A(2,2)*B(2,0);
		D(2,1)=A(2,0)*B(0,1)+A(2,1)*B(1,1)+A(2,2)*B(2,1);
		D(2,2)=A(2,0)*B(0,2)+A(2,1)*B(1,2)+A(2,2)*B(2,2);

#undef A
#undef B
#undef D

		return dest;
	}

	inline Vector3 operator*(const Vector3 &vec) const{
		return Vector3(	at(0,0)*vec.x+at(0,1)*vec.y+at(0,2)*vec.z,
						at(1,0)*vec.x+at(1,1)*vec.y+at(1,2)*vec.z,
						at(2,0)*vec.x+at(2,1)*vec.y+at(2,2)*vec.z);
	}

	inline void mult(const Vector3 &vec,Vector3 &dest) const{
		dest.x=at(0,0)*vec.x+at(0,1)*vec.y+at(0,2)*vec.z;
		dest.y=at(1,0)*vec.x+at(1,1)*vec.y+at(1,2)*vec.z;
		dest.z=at(2,0)*vec.x+at(2,1)*vec.y+at(2,2)*vec.z;
	}
};

inline void setTranspose(Matrix3x3 &res,const Matrix3x3 &src){
	res.at(0,0)=src.at(0,0);
	res.at(0,1)=src.at(1,0);
	res.at(0,2)=src.at(2,0);
	res.at(1,0)=src.at(0,1);
	res.at(1,1)=src.at(1,1);
	res.at(1,2)=src.at(2,1);
	res.at(2,0)=src.at(0,2);
	res.at(2,1)=src.at(1,2);
	res.at(2,2)=src.at(2,2);
}

inline Matrix3x3 makeTranspose(const Matrix3x3 &src){
	Matrix3x3 res;
	setTranspose(res,src);
	return res;
}

inline double determinant(const Matrix3x3 &src){
	return -src.at(0,0)*src.at(1,1)*src.at(2,2)+src.at(0,0)*src.at(2,1)*src.at(1,2)+src.at(0,1)*src.at(1,0)*src.at(2,2)-src.at(0,1)*src.at(2,0)*src.at(1,2)-src.at(0,2)*src.at(1,0)*src.at(2,1)+src.at(0,2)*src.at(2,0)*src.at(1,1);
}

inline bool setInverse(Matrix3x3 &res,const Matrix3x3 src){
	double det=1.0/determinant(src);
	if(det==0){
		return false;
	}
	else{
		res.at(0,0)=-(src.at(1,1)*src.at(2,2)-src.at(2,1)*src.at(1,2))*det;
		res.at(1,0)=(src.at(1,0)*src.at(2,2)-src.at(2,0)*src.at(1,2))*det;
		res.at(2,0)=-(src.at(1,0)*src.at(2,1)-src.at(2,0)*src.at(1,1))*det;

		res.at(0,1)=(src.at(0,1)*src.at(2,2)-src.at(2,1)*src.at(0,2))*det;
		res.at(1,1)=-(src.at(0,0)*src.at(2,2)-src.at(2,0)*src.at(0,2))*det;
		res.at(2,1)=(src.at(0,0)*src.at(2,1)-src.at(2,0)*src.at(0,1))*det;
		
		res.at(0,2)=-(src.at(0,1)*src.at(1,2)-src.at(1,1)*src.at(0,2))*det;
		res.at(1,2)=(src.at(0,0)*src.at(1,2)-src.at(1,0)*src.at(0,2))*det;
		res.at(2,2)=-(src.at(0,0)*src.at(1,1)-src.at(1,0)*src.at(0,1))*det;
		
		return true;
	}
}

inline Matrix3x3 makeInverse(const Matrix3x3 &src){
	Matrix3x3 res;
	setInverse(res,src);
	return res;
}

inline EulerAngle makeEulerAngle(const Matrix3x3 &mat){
	EulerAngle euler;

	euler.y=asin(-mat.at(2,0));

	if(euler.y<vrPi/2){
		if(euler.y>-vrPi/2){
			euler.z=atan2(mat.at(1,0),mat.at(0,0));
			euler.x=atan2(mat.at(2,1),mat.at(2,2));
		}
		else{
			euler.z=-atan2(-mat.at(0,1),mat.at(0,2));
			euler.x=0;
		}
	}
	else{
		euler.z=atan2(-mat.at(0,1),mat.at(0,2));
		euler.x=0;
	}

	return euler;
}

inline Matrix3x3 makeMatrix3x3FromX(vrReal z){
	return Matrix3x3(	1,0,0,
						0,(vrReal)cos(z),-(vrReal)sin(z),
						0,(vrReal)sin(z),(vrReal)cos(z));
}

inline Matrix3x3 makeMatrix3x3FromY(vrReal y){
	return Matrix3x3(	(vrReal)cos(y),0,(vrReal)sin(y),
						0,1,0,
						-(vrReal)sin(y),0,(vrReal)cos(y));
}

inline Matrix3x3 makeMatrix3x3FromZ(vrReal x){
	return Matrix3x3(	(vrReal)cos(x),-(vrReal)sin(x),0,
						(vrReal)sin(x),(vrReal)cos(x),0,
						0,0,1);
}

inline Matrix3x3 makeMatrix3x3(const EulerAngle &angles){
	return makeMatrix3x3FromX(angles.x)*makeMatrix3x3FromY(angles.y)*makeMatrix3x3FromZ(angles.z);
}

inline void setMatrix3x3FromDirCos(Matrix3x3 &res,const Vector3 &xDest,const Vector3 &yDest,const Vector3 &zDest,const Vector3 &xSrc,const Vector3 &ySrc,const Vector3 &zSrc){
	vrReal Xa,Xb,Xc;
	vrReal Ya,Yb,Yc;
	vrReal Za,Zb,Zc;

	Xa=dot(xDest,xSrc);Xb=dot(xDest,ySrc);Xc=dot(xDest,zSrc);
	Ya=dot(yDest,xSrc);Yb=dot(yDest,ySrc);Yc=dot(yDest,zSrc);
	Za=dot(zDest,xSrc);Zb=dot(zDest,ySrc);Zc=dot(zDest,zSrc);

	res.at(0,0)=Xa;res.at(0,1)=Ya;res.at(0,2)=Za;
	res.at(1,0)=Xb;res.at(1,1)=Yb;res.at(1,2)=Zb;
	res.at(2,0)=Xc;res.at(2,1)=Yc;res.at(2,2)=Zc;
}

inline Matrix3x3 makeMatrix3x3FromDirCos(const Vector3 &xDest,const Vector3 &yDest,const Vector3 &zDest,const Vector3 &xSrc,const Vector3 &ySrc,const Vector3 &zSrc){
	Matrix3x3 res;
	setMatrix3x3FromDirCos(res,xDest,yDest,zDest,xSrc,ySrc,zSrc);
	return res;
}

inline void setMatrix3x3FromAxis(Matrix3x3 &res,const Vector3 &xAxis,const Vector3 &yAxis,const Vector3 &zAxis){
	res.at(0,0)=xAxis[0];
	res.at(1,0)=xAxis[1];
	res.at(2,0)=xAxis[2];

	res.at(0,1)=yAxis[0];
	res.at(1,1)=yAxis[1];
	res.at(2,1)=yAxis[2];

	res.at(0,2)=zAxis[0];
	res.at(1,2)=zAxis[1];
	res.at(2,2)=zAxis[2];
}

inline Matrix3x3 makeMatrix3x3FromAxis(const Vector3 &xAxis,const Vector3 &yAxis,const Vector3 &zAxis){
	Matrix3x3 res;
	setMatrix3x3FromAxis(res,xAxis,yAxis,zAxis);
	return res;
}

class Matrix4x4{
public:
	vrReal data[16];

	class RowAccessor{
	public:
		inline RowAccessor(Matrix4x4 *m,int r){
			matrix=m;
			row=r;
		}

		inline vrReal &operator[](int col){
			return matrix->at(row,col);
		}

		inline vrReal operator[](int col) const{
			return matrix->at(row,col);
		}

		Matrix4x4 *matrix;
		int row;
	};

	inline Matrix4x4(){
		data[0]=1;data[4]=0;data[8]=0;data[12]=0;
		data[1]=0;data[5]=1;data[9]=0;data[13]=0;
		data[2]=0;data[6]=0;data[10]=1;data[14]=0;
		data[3]=0;data[7]=0;data[11]=0;data[15]=1;
	}

	inline Matrix4x4(vrReal x1,vrReal x2,vrReal x3,vrReal x4,vrReal y1,vrReal y2,vrReal y3,vrReal y4,vrReal z1,vrReal z2,vrReal z3,vrReal z4,vrReal w1,vrReal w2,vrReal w3,vrReal w4){
		data[0]=x1;data[4]=x2;data[8]=x3;data[12]=x4;
		data[1]=y1;data[5]=y2;data[9]=y3;data[13]=y4;
		data[2]=z1;data[6]=z2;data[10]=z3;data[14]=z4;
		data[3]=w1;data[7]=w2;data[11]=w3;data[15]=w4;
	}

	inline RowAccessor operator[](int row){
		return RowAccessor(this,row);
	}

	inline vrReal at(int row,int col) const{
		return data[col*4+row];
	}

	inline vrReal &at(int row,int col){
		return data[col*4+row];
	}

	inline vrReal *getData(){return (vrReal*)data;}
	inline const vrReal *getData() const{return (vrReal*)data;}

	Matrix4x4 operator*(const Matrix4x4 &m2) const{
		Matrix4x4 dest;

#define A(row,col)  at(row,col)
#define B(row,col)  m2.at(row,col)
#define D(row,col)  dest.at(row,col)

	D(0,0)=A(0,0)*B(0,0)+A(0,1)*B(1,0)+A(0,2)*B(2,0)+A(0,3)*B(3,0);
	D(0,1)=A(0,0)*B(0,1)+A(0,1)*B(1,1)+A(0,2)*B(2,1)+A(0,3)*B(3,1);
	D(0,2)=A(0,0)*B(0,2)+A(0,1)*B(1,2)+A(0,2)*B(2,2)+A(0,3)*B(3,2);
	D(0,3)=A(0,0)*B(0,3)+A(0,1)*B(1,3)+A(0,2)*B(2,3)+A(0,3)*B(3,3);

	D(1,0)=A(1,0)*B(0,0)+A(1,1)*B(1,0)+A(1,2)*B(2,0)+A(1,3)*B(3,0);
	D(1,1)=A(1,0)*B(0,1)+A(1,1)*B(1,1)+A(1,2)*B(2,1)+A(1,3)*B(3,1);
	D(1,2)=A(1,0)*B(0,2)+A(1,1)*B(1,2)+A(1,2)*B(2,2)+A(1,3)*B(3,2);
	D(1,3)=A(1,0)*B(0,3)+A(1,1)*B(1,3)+A(1,2)*B(2,3)+A(1,3)*B(3,3);

	D(2,0)=A(2,0)*B(0,0)+A(2,1)*B(1,0)+A(2,2)*B(2,0)+A(2,3)*B(3,0);
	D(2,1)=A(2,0)*B(0,1)+A(2,1)*B(1,1)+A(2,2)*B(2,1)+A(2,3)*B(3,1);
	D(2,2)=A(2,0)*B(0,2)+A(2,1)*B(1,2)+A(2,2)*B(2,2)+A(2,3)*B(3,2);
	D(2,3)=A(2,0)*B(0,3)+A(2,1)*B(1,3)+A(2,2)*B(2,3)+A(2,3)*B(3,3);

	D(3,0)=A(3,0)*B(0,0)+A(3,1)*B(1,0)+A(3,2)*B(2,0)+A(3,3)*B(3,0);
	D(3,1)=A(3,0)*B(0,1)+A(3,1)*B(1,1)+A(3,2)*B(2,1)+A(3,3)*B(3,1);
	D(3,2)=A(3,0)*B(0,2)+A(3,1)*B(1,2)+A(3,2)*B(2,2)+A(3,3)*B(3,2);
	D(3,3)=A(3,0)*B(0,3)+A(3,1)*B(1,3)+A(3,2)*B(2,3)+A(3,3)*B(3,3);

#undef D
#undef B
#undef A

		return dest;
	}

	inline Vector4 operator*(const Vector4 &vec) const{
		return Vector4(	at(0,0)*vec.x+at(0,1)*vec.y+at(0,2)*vec.z+at(0,3)*vec.w,
						at(1,0)*vec.x+at(1,1)*vec.y+at(1,2)*vec.z+at(1,3)*vec.w,
						at(2,0)*vec.x+at(2,1)*vec.y+at(2,2)*vec.z+at(2,3)*vec.w,
						at(3,0)*vec.x+at(3,1)*vec.y+at(3,2)*vec.z+at(3,3)*vec.w);
	}

	inline void mult(const Vector4 &vec,Vector4 &dest) const{
		dest.x=at(0,0)*vec.x+at(0,1)*vec.y+at(0,2)*vec.z+at(0,3)*vec.w;
		dest.y=at(1,0)*vec.x+at(1,1)*vec.y+at(1,2)*vec.z+at(1,3)*vec.w;
		dest.z=at(2,0)*vec.x+at(2,1)*vec.y+at(2,2)*vec.z+at(2,3)*vec.w;
		dest.z=at(3,0)*vec.x+at(3,1)*vec.y+at(3,2)*vec.z+at(3,3)*vec.w;
	}
};

inline void setMatrix3x3(Matrix3x3 &res,const Matrix4x4 &src){
	for(int i=0;i<3;i++){
		res.at(0,i)=src.at(0,i);
		res.at(1,i)=src.at(1,i);
		res.at(2,i)=src.at(2,i);
	}
}

inline Matrix3x3 makeMatrix3x3(const Matrix4x4 &src){
	Matrix3x3 res;
	setMatrix3x3(res,src);
	return res;
}

inline void setVector3(Vector3 &res,const Matrix4x4 &src){
	res.x=src.at(0,3);
	res.y=src.at(1,3);
	res.z=src.at(2,3);
}

inline Vector3 makeVector3(const Matrix4x4 &src){
	Vector3 res;
	setVector3(res,src);
	return res;
}

inline void setTranspose(Matrix4x4 &res,const Matrix4x4 &src){
	res.at(0,0)=src.at(0,0);
	res.at(0,1)=src.at(1,0);
	res.at(0,2)=src.at(2,0);
	res.at(0,3)=src.at(3,0);

	res.at(1,0)=src.at(0,1);
	res.at(1,1)=src.at(1,1);
	res.at(1,2)=src.at(2,1);
	res.at(1,3)=src.at(3,1);

	res.at(2,0)=src.at(0,2);
	res.at(2,1)=src.at(1,2);
	res.at(2,2)=src.at(2,2);
	res.at(2,3)=src.at(3,2);

	res.at(3,0)=src.at(0,3);
	res.at(3,1)=src.at(1,3);
	res.at(3,2)=src.at(2,3);
	res.at(3,3)=src.at(3,3);
}

inline Matrix4x4 makeTranspose(const Matrix4x4 &src){
	Matrix4x4 res;
	setTranspose(res,src);
	return res;
}

inline double determinant(const Matrix4x4 &src){
	double det1 = src.at(1,2) * src.at(2,3) - src.at(2,2) * src.at(1,3);
	double det2 = src.at(1,1) * src.at(2,3) - src.at(2,1) * src.at(1,3);
	double det3 = src.at(1,1) * src.at(2,2) - src.at(2,1) * src.at(1,2);
	double det4 = src.at(1,0) * src.at(2,3) - src.at(2,0) * src.at(1,3);
	double det5 = src.at(1,0) * src.at(2,2) - src.at(2,0) * src.at(1,2);
	double det6 = src.at(1,0) * src.at(2,1) - src.at(2,0) * src.at(1,1);

	return -src.at(3,0) * (src.at(0,1) * det1 - src.at(0,2) * det2 + src.at(0,3) * det3) +
			src.at(3,1) * (src.at(0,0) * det1 - src.at(0,2) * det4 + src.at(0,3) * det5) -
			src.at(3,2) * (src.at(0,0) * det2 - src.at(0,1) * det4 + src.at(0,3) * det6) +
			src.at(3,3) * (src.at(0,0) * det3 - src.at(0,1) * det5 + src.at(0,2) * det6);
}

inline bool setInverse(Matrix4x4 &res,const Matrix4x4 &src){
	double det=determinant(src);

	if(fabs(det)<vrEpsilon){
		return false;
	}
	else{
		// calculate (transposed cofactor matrix / determinant of given matrix)
		det=(double)1.0/det;
		res.at(0,0) = det * (src.at(1,1) * (src.at(2,2) * src.at(3,3) - src.at(2,3) * src.at(3,2)) + src.at(1,2) * (src.at(2,3) * src.at(3,1) - src.at(2,1) * src.at(3,3)) + src.at(1,3) * (src.at(2,1) * src.at(3,2) - src.at(2,2) * src.at(3,1)));
		res.at(0,1) = det * (src.at(2,1) * (src.at(0,2) * src.at(3,3) - src.at(0,3) * src.at(3,2)) + src.at(2,2) * (src.at(0,3) * src.at(3,1) - src.at(0,1) * src.at(3,3)) + src.at(2,3) * (src.at(0,1) * src.at(3,2) - src.at(0,2) * src.at(3,1)));
		res.at(0,2) = det * (src.at(3,1) * (src.at(0,2) * src.at(1,3) - src.at(0,3) * src.at(1,2)) + src.at(3,2) * (src.at(0,3) * src.at(1,1) - src.at(0,1) * src.at(1,3)) + src.at(3,3) * (src.at(0,1) * src.at(1,2) - src.at(0,2) * src.at(1,1)));
		res.at(0,3) = det * (src.at(0,1) * (src.at(1,3) * src.at(2,2) - src.at(1,2) * src.at(2,3)) + src.at(0,2) * (src.at(1,1) * src.at(2,3) - src.at(1,3) * src.at(2,1)) + src.at(0,3) * (src.at(1,2) * src.at(2,1) - src.at(1,1) * src.at(2,2)));

		res.at(1,0) = det * (src.at(1,2) * (src.at(2,0) * src.at(3,3) - src.at(2,3) * src.at(3,0)) + src.at(1,3) * (src.at(2,2) * src.at(3,0) - src.at(2,0) * src.at(3,2)) + src.at(1,0) * (src.at(2,3) * src.at(3,2) - src.at(2,2) * src.at(3,3)));
		res.at(1,1) = det * (src.at(2,2) * (src.at(0,0) * src.at(3,3) - src.at(0,3) * src.at(3,0)) + src.at(2,3) * (src.at(0,2) * src.at(3,0) - src.at(0,0) * src.at(3,2)) + src.at(2,0) * (src.at(0,3) * src.at(3,2) - src.at(0,2) * src.at(3,3)));
		res.at(1,2) = det * (src.at(3,2) * (src.at(0,0) * src.at(1,3) - src.at(0,3) * src.at(1,0)) + src.at(3,3) * (src.at(0,2) * src.at(1,0) - src.at(0,0) * src.at(1,2)) + src.at(3,0) * (src.at(0,3) * src.at(1,2) - src.at(0,2) * src.at(1,3)));
		res.at(1,3) = det * (src.at(0,2) * (src.at(1,3) * src.at(2,0) - src.at(1,0) * src.at(2,3)) + src.at(0,3) * (src.at(1,0) * src.at(2,2) - src.at(1,2) * src.at(2,0)) + src.at(0,0) * (src.at(1,2) * src.at(2,3) - src.at(1,3) * src.at(2,2)));
		
		res.at(2,0) = det * (src.at(1,3) * (src.at(2,0) * src.at(3,1) - src.at(2,1) * src.at(3,0)) + src.at(1,0) * (src.at(2,1) * src.at(3,3) - src.at(2,3) * src.at(3,1)) + src.at(1,1) * (src.at(2,3) * src.at(3,0) - src.at(2,0) * src.at(3,3)));
		res.at(2,1) = det * (src.at(2,3) * (src.at(0,0) * src.at(3,1) - src.at(0,1) * src.at(3,0)) + src.at(2,0) * (src.at(0,1) * src.at(3,3) - src.at(0,3) * src.at(3,1)) + src.at(2,1) * (src.at(0,3) * src.at(3,0) - src.at(0,0) * src.at(3,3)));
		res.at(2,2) = det * (src.at(3,3) * (src.at(0,0) * src.at(1,1) - src.at(0,1) * src.at(1,0)) + src.at(3,0) * (src.at(0,1) * src.at(1,3) - src.at(0,3) * src.at(1,1)) + src.at(3,1) * (src.at(0,3) * src.at(1,0) - src.at(0,0) * src.at(1,3)));
		res.at(2,3) = det * (src.at(0,3) * (src.at(1,1) * src.at(2,0) - src.at(1,0) * src.at(2,1)) + src.at(0,0) * (src.at(1,3) * src.at(2,1) - src.at(1,1) * src.at(2,3)) + src.at(0,1) * (src.at(1,0) * src.at(2,3) - src.at(1,3) * src.at(2,0)));
		
		res.at(3,0) = det * (src.at(1,0) * (src.at(2,2) * src.at(3,1) - src.at(2,1) * src.at(3,2)) + src.at(1,1) * (src.at(2,0) * src.at(3,2) - src.at(2,2) * src.at(3,0)) + src.at(1,2) * (src.at(2,1) * src.at(3,0) - src.at(2,0) * src.at(3,1)));
		res.at(3,1) = det * (src.at(2,0) * (src.at(0,2) * src.at(3,1) - src.at(0,1) * src.at(3,2)) + src.at(2,1) * (src.at(0,0) * src.at(3,2) - src.at(0,2) * src.at(3,0)) + src.at(2,2) * (src.at(0,1) * src.at(3,0) - src.at(0,0) * src.at(3,1)));
		res.at(3,2) = det * (src.at(3,0) * (src.at(0,2) * src.at(1,1) - src.at(0,1) * src.at(1,2)) + src.at(3,1) * (src.at(0,0) * src.at(1,2) - src.at(0,2) * src.at(1,0)) + src.at(3,2) * (src.at(0,1) * src.at(1,0) - src.at(0,0) * src.at(1,1)));
		res.at(3,3) = det * (src.at(0,0) * (src.at(1,1) * src.at(2,2) - src.at(1,2) * src.at(2,1)) + src.at(0,1) * (src.at(1,2) * src.at(2,0) - src.at(1,0) * src.at(2,2)) + src.at(0,2) * (src.at(1,0) * src.at(2,1) - src.at(1,1) * src.at(2,0)));

		return true;
	}
}

inline Matrix4x4 makeInverse(const Matrix4x4 &src){
	Matrix4x4 res;
	setInverse(res,src);
	return res;
}

inline void setMatrix4x4(Matrix4x4 &res,const Matrix3x3 &src){
	for(int i=0;i<3;i++){
		res.at(0,i)=src.at(0,i);
		res.at(1,i)=src.at(1,i);
		res.at(2,i)=src.at(2,i);
	}
}

inline Matrix4x4 makeMatrix4x4(const Matrix3x3 &src){
	Matrix4x4 res;
	setMatrix4x4(res,src);
	return res;
}

inline void setMatrix4x4(Matrix4x4 &res,const Vector3 &src){
	res.at(0,3)=src[0];
	res.at(1,3)=src[1];
	res.at(2,3)=src[2];
}

inline Matrix4x4 makeMatrix4x4(const Vector3 &src){
	Matrix4x4 res;
	setMatrix4x4(res,src);
	return res;
}

inline void setMatrix4x4(Matrix4x4 &res,const Matrix3x3 &rotate,const Vector3 &trans){
	setMatrix4x4(res,rotate);
	setMatrix4x4(res,trans);
}	

inline Matrix4x4 makeMatrix4x4(const Matrix3x3 &rotate,const Vector3 &trans){
	Matrix4x4 res;
	setMatrix4x4(res,rotate,trans);
	return res;
}

inline void setMatrix4x4FromScale(Matrix4x4 &mat,const Vector3 &scale){
	mat.data[0]=scale[0];	mat.data[4]=0;			mat.data[8]=0;			mat.data[12]=0;
	mat.data[1]=0;			mat.data[5]=scale[1];	mat.data[9]=0;			mat.data[13]=0;
	mat.data[2]=0;			mat.data[6]=0;			mat.data[10]=scale[2];	mat.data[14]=0;
	mat.data[3]=0;			mat.data[7]=0;			mat.data[11]=0;			mat.data[15]=1;
}

inline Matrix4x4 makeMatrix4x4FromScale(const Vector3 &scale){
	Matrix4x4 res;
	setMatrix4x4FromScale(res,scale);
	return res;
}

// Quaternion
class Quaternion{
public:
	vrReal x,y,z,w;

	inline Quaternion():x(0),y(0),z(0),w(0){}

	inline Quaternion(vrReal x1,vrReal y1,vrReal z1,vrReal w1):x(x1),y(y1),z(z1),w(w1){}

	inline vrReal *getData(){return (vrReal*)&x;}
	inline const vrReal *getData() const{return (vrReal*)&x;}

	inline Quaternion operator*(const Quaternion &q) const{
		return Quaternion(
			+x*q.w+y*q.z-z*q.y+w*q.x,
			-x*q.z+y*q.w+z*q.x+w*q.y,
			+x*q.y-y*q.x+z*q.w+w*q.z,
			-x*q.x-y*q.y-z*q.z+w*q.w);        
	}

	inline Quaternion operator+(const Quaternion &q) const{
		return Quaternion(x+q.x,y+q.y,z+q.z,w+q.w);
	}

	inline void operator+=(const Quaternion &q){
		x+=q.x;
		y+=q.y;
		z+=q.z;
		w+=q.w;
	}

	inline Quaternion operator-(const Quaternion &q) const{
		return Quaternion(x-q.x,y-q.y,z-q.z,w-q.w);
	}

	inline void operator-=(const Quaternion &q){
		x-=q.x;
		y-=q.y;
		z-=q.z;
		w-=q.w;
	}

	inline Quaternion operator*(vrReal f) const{
		return Quaternion(x*f,y*f,z*f,w*f);
	}

	inline Quaternion operator/(vrReal f) const{
		f=1/f;
		return Quaternion(x*f,y*f,z*f,w*f);
	}

	inline vrReal &operator[](int i){
		return *(&x+i);
	}

	inline vrReal operator[](int i) const{
		return *(&x+i);
	}
};

inline void setQuaternion(Quaternion &quat,const Matrix3x3 &mat){
	vrReal w=0.5*(vrReal)sqrt(mat.at(0,0)+mat.at(1,1)+mat.at(2,2)+1);
	vrReal s=0.25/w;
	quat[0]=(mat.at(1,2)-mat.at(2,1))*s;
	quat[1]=(mat.at(2,0)-mat.at(0,2))*s;
	quat[2]=(mat.at(0,1)-mat.at(1,0))*s;
	quat[3]=w;
}

inline Quaternion makeQuaternion(const Matrix3x3 &mat){
	Quaternion quat;
	setQuaternion(quat,mat);
	return quat;
}

inline void setMatrix3x3(Matrix3x3 &mat,const Quaternion &quat){
	//WARNING: STATIC VARS
	static vrReal xx;
	static vrReal xy;
	static vrReal yy;
	static vrReal xz;
	static vrReal yz;
	static vrReal zz;
	static vrReal xw;
	static vrReal yw;
	static vrReal zw;
	static vrReal ww;

	xx=quat.x*quat.x;
	xy=quat.x*quat.y;
	yy=quat.y*quat.y;
	xz=quat.x*quat.z;
	yz=quat.y*quat.z;
	zz=quat.z*quat.z;
	xw=quat.x*quat.w;
	yw=quat.y*quat.w;
	zw=quat.z*quat.w;
	ww=quat.w*quat.w;

	mat=Matrix3x3(
		+xx-yy-zz+ww, +xy-zw+xy-zw, +xz+yw+xz+yw,
		+xy+zw+xy+zw, -xx+yy-zz+ww, +yz-xw+yz-xw,
		+xz-yw+xz-yw, +yz+xw+yz+xw, -xx-yy+zz+ww);
}

inline Matrix3x3 makeMatrix3x3(const Quaternion &quat){
	Matrix3x3 mat;
	setMatrix3x3(mat,quat);
	return mat;
}

inline vrReal norm(const Quaternion &quat){
	return quat.x*quat.x+quat.y*quat.y+quat.z*quat.z+quat.w*quat.w;
}

inline vrReal length(const Quaternion &quat){
	return sqrt(norm(quat));
}

inline Quaternion normalize(Quaternion &quat){
	vrReal l=1/length(quat);
	quat.x*=l;
	quat.y*=l;
	quat.z*=l;
	quat.w*=l;
	return quat;
}

inline Quaternion normalize(const Quaternion &quat){
	vrReal l=1/length(quat);
	Quaternion quat2;
	quat2.x=quat.x*l;
	quat2.y=quat.y*l;
	quat2.z=quat.z*l;
	quat2.w=quat.w*l;
	return quat2;
}

inline Quaternion makeConjugate(const Quaternion &quat){
	return Quaternion(-quat.x,-quat.y,-quat.z,-quat.w);
}

inline void setInverse(Quaternion &res,const Quaternion &src){
	res=makeConjugate(src)/norm(src);
}

inline Quaternion makeInverse(const Quaternion &src){
	Quaternion quat;
	setInverse(quat,src);
	return quat;
}

inline Quaternion makeExp(const Quaternion &quat){
	vrReal r  = sqrt(quat.x*quat.x+quat.y*quat.y+quat.z*quat.z);
	vrReal et = exp(quat.w);
	vrReal s  = r>=0.00001f? et*sin(r)/r: 0.f;
	return Quaternion(s*quat.x,s*quat.y,s*quat.z,et*cos(r));
}

inline Quaternion makeLn(const Quaternion &quat){
	vrReal r  = sqrt(quat.x*quat.x+quat.y*quat.y+quat.z*quat.z);
	vrReal t  = r>0.00001f? atan2(r,quat.w)/r: 0.f;
	return Quaternion(t*quat.x,t*quat.y,t*quat.z,0.5*log(norm(quat)));
}

inline vrReal dot(const Quaternion &quat1,const Quaternion &quat2){
	return quat1.x*quat2.x+quat1.y*quat2.y+quat1.z*quat2.z+quat1.w*quat2.w;
}

inline Quaternion slerp(const Quaternion &quat1,const Quaternion &quat2,vrReal t){
	Quaternion l1;
	Quaternion l2;
		
	l1=makeLn(quat1);

	if(dot(quat1,quat2)<0)
		l2=makeLn(quat2*(-1));
	else
		l2=makeLn(quat2);

	Quaternion r=linearInterpolate(l1,l2,t);

	return makeExp(r);
}

inline Quaternion fastSlerp(const Quaternion &quat1,const Quaternion &quat2,vrReal t){
	if(dot(quat1,quat2)<0)
		return linearInterpolate(quat1,quat2*(-1),t);
	else
		return linearInterpolate(quat1,quat2,t);
}

inline Quaternion makeQuaternionFromVectorToVector(const Vector3 &vec1,const Vector3 &vec2){
	Vector3 axis=normalize(cross(vec1,vec2));
	vrReal angle=acos(dot(vec1,vec2));
	Vector4 angleAxis(axis,angle);

	// Now make a Quaternion from AngleAxis
	vrReal s = (vrReal)sin(angleAxis.w/2.0);
	vrReal c = (vrReal)cos(angleAxis.w/2.0);
	return normalize(Quaternion(angleAxis.x*s,angleAxis.y*s,angleAxis.z*s,c));
}

// Segment
class Segment{
public:
	inline Segment(const Vector3 &paramStart,const Vector3 &paramEnd):origin(paramStart),direction(paramEnd-paramStart){}

	static inline Segment makeSegmentStartDir(const Vector3 &paramStart,const Vector3 &paramDir){return Segment(paramStart,paramStart+paramDir);}

	inline const Vector3& getOrigin() const{
		return origin;
	}

	inline Vector3& Origin(){
		return origin;
	}

	inline const Vector3& getDirection() const{
		return direction;
	}
	
	inline Vector3& Direction(){
		return direction;
	}

	inline Vector3 getEndPoint() const{
		return origin+direction;
	}

private:
	Vector3 origin;
	Vector3 direction;
};

// Plane
class Plane;
Plane normalize(Plane &plane);

class Plane{
public:
	inline Plane(){}

	inline Plane(const Vector3 &norm,vrReal dist):normal(norm),d(dist){
	}

	inline Plane(const Vector3 &point,const Vector3 &norm){
		normal=norm;
		d=dot(normal,point);
	}

	inline Plane(const Vector3 &point1,const Vector3 &point2,const Vector3 &point3){
		Vector3 v1,v2;

		v1=point3-point1;
		v2=point2-point1;

		normal=cross(v2,v1);

		d=dot(normal,point1);

		normalize(*this);
	}

	Segment getLineOfIntersection(const Plane &plane2){
		vrReal determinant=lengthSquared(normal) * lengthSquared(plane2.normal) - (dot(normal,plane2.normal)*dot(normal,plane2.normal));

		vrReal c1=(d*lengthSquared(plane2.normal) - plane2.d*dot(normal,plane2.normal))/determinant;
		vrReal c2=(plane2.d*lengthSquared(normal) - d*dot(normal,plane2.normal))/determinant;

		Vector3 dir=cross(normal,plane2.normal);
		Vector3 orig=c1*normal+c2*plane2.normal;

		return Segment::makeSegmentStartDir(orig,dir);
	}

	inline bool isPointOutside(const Vector3 &point) const{
		return normal.x*point.x+normal.y*point.y+normal.z*point.z-d>0;//(normal.dot(point)-d>0);
	}

	inline bool traceLine(const Vector3 &start,const Vector3 &end,Vector3 &result,bool infinite) const{
		vrReal t=(dot(normal,normal*d-start))/(dot(normal,end-start));

		result=linearInterpolate(start,end,t);

		return true;
	}

	inline bool traceLine(const Vector3 &start,const Vector3 &end,Vector3 &result) const{
		vrReal t=(dot(normal,normal*d-start))/(dot(normal,end-start));

		if(t<0 || t>1)
			return false;

		result=linearInterpolate(start,end,t);

		return true;
	}

	inline bool traceLine(const Segment &seg,Vector3 &result) const{
		vrReal t=(dot(normal,normal*d-seg.getOrigin()))/(dot(normal,seg.getDirection()));

		if(t<0)
			return false;

		result=linearInterpolate(seg.getOrigin(),seg.getEndPoint(),t);

		return true;
	}

	inline Vector3 projectPoint(const Vector3 &point) const{
		Vector3 t=point-normal*d;

		vrReal f=dot(normal,t);

		return point-normal*f;
	}

	static bool getIntersectionOfThreePlanes(const Plane &p1,const Plane &p2,const Plane &p3,Vector3 &result){
		// Either one of these should work, but the second is quicker, no inverse
#if 0
		Matrix4x4 m,m2;

		m.at(0,0)=p1.normal.x;
		m.at(1,0)=p1.normal.y;
		m.at(2,0)=p1.normal.z;
		m.at(3,0)=p1.d;

		m.at(0,1)=p2.normal.x;
		m.at(1,1)=p2.normal.y;
		m.at(2,1)=p2.normal.z;
		m.at(3,1)=p2.d;

		m.at(0,2)=p3.normal.x;
		m.at(1,2)=p3.normal.y;
		m.at(2,2)=p3.normal.z;
		m.at(3,2)=p3.d;

		m.at(0,3)=0;
		m.at(1,3)=0;
		m.at(2,3)=0;
		m.at(3,3)=1;

		if(m.getInverse(m2)==false){
			return false;
		}
		else{
			result=Vector3(m2.at(3,0),m2.at(3,1),m2.at(3,2))*-1;
			return true;
		}
#else
		float den=dot(p1.normal,cross(p2.normal,p3.normal));
		if(den==0){
			return false;
		}
		else{
			result=-1*(-p1.d*cross(p2.normal,p3.normal) - p2.d*cross(p3.normal,p1.normal) - p3.d*cross(p1.normal,p2.normal))/den;
			return true;
		}
#endif
	}

	Vector3 normal;
	vrReal d;
};

inline Plane normalize(Plane &plane){
	vrReal l=1/length(plane.normal);
	plane.normal.x*=l;
	plane.normal.y*=l;
	plane.normal.z*=l;
	plane.d*=l;
	return plane;
}

inline Plane normalize(const Plane &plane){
	Plane plane2;
	vrReal l=1/length(plane.normal);
	plane2.normal.x=plane.normal.x*l;
	plane2.normal.y=plane.normal.y*l;
	plane2.normal.z=plane.normal.z*l;
	plane2.d=plane.d*l;
	return plane2;
}

//AABox
class AABox{
public:
	inline AABox(){}

	inline AABox(const Vector3 &paramMins,const Vector3 &paramMaxs):mins(paramMins),maxs(paramMaxs){}

	inline Vector3& Mins(){
		return mins;
	}

	inline Vector3 getMins() const{
		return mins;
	}

	inline Vector3& Maxs(){
		return maxs;
	}

	inline Vector3 getMaxs() const{
		return maxs;
	}

	inline void setMins(const Vector3 &min){
		mins=min;
	}

	inline void setMaxs(const Vector3 &max){
		maxs=max;
	}

	inline void getVertexes(Vector3 *vertexes) const{
		vertexes[0]=Vector3(mins.x,mins.y,mins.z);
		vertexes[1]=Vector3(maxs.x,mins.y,mins.z);
		vertexes[2]=Vector3(mins.x,maxs.y,mins.z);
		vertexes[3]=Vector3(maxs.x,maxs.y,mins.z);
		vertexes[4]=Vector3(mins.x,mins.y,maxs.z);
		vertexes[5]=Vector3(maxs.x,mins.y,maxs.z);
		vertexes[6]=Vector3(mins.x,maxs.y,maxs.z);
		vertexes[7]=Vector3(maxs.x,maxs.y,maxs.z);
	}

	inline void mergeWith(const AABox &box){
		if(box.mins.x<mins.x)mins.x=box.mins.x;
		if(box.mins.y<mins.y)mins.y=box.mins.y;
		if(box.mins.z<mins.z)mins.z=box.mins.z;
		if(box.maxs.x>maxs.x)maxs.x=box.maxs.x;
		if(box.maxs.y>maxs.y)maxs.y=box.maxs.y;
		if(box.maxs.z>maxs.z)maxs.z=box.maxs.z;
	}

	inline void mergeWith(const Vector3 &vec){
		if(vec.x<mins.x)mins.x=vec.x;
		if(vec.y<mins.y)mins.y=vec.y;
		if(vec.z<mins.z)mins.z=vec.z;
		if(vec.x>maxs.x)maxs.x=vec.x;
		if(vec.y>maxs.y)maxs.y=vec.y;
		if(vec.z>maxs.z)maxs.z=vec.z;
	}

	void rotate(const Matrix3x3 &rotation){
		int i;
		Vector3 vertexes[8];

		getVertexes(vertexes);

		for(i=0;i<8;i++){
			vertexes[i]=rotation*vertexes[i];
		}

		mins=vertexes[0];
		maxs=vertexes[0];

		for(i=1;i<8;i++){
			if(mins.x>vertexes[i].x)
				mins.x=vertexes[i].x;
			if(mins.y>vertexes[i].y)
				mins.y=vertexes[i].y;
			if(mins.z>vertexes[i].z)
				mins.z=vertexes[i].z;
			if(maxs.x<vertexes[i].x)
				maxs.x=vertexes[i].x;
			if(maxs.y<vertexes[i].y)
				maxs.y=vertexes[i].y;
			if(maxs.z<vertexes[i].z)
				maxs.z=vertexes[i].z;
		}
	}

	inline bool operator!=(const AABox &box) const{
		return (box.mins!=mins || box.maxs!=maxs);
	}

	inline AABox operator+(const Vector3 &vec) const{
		return AABox(mins+vec,maxs+vec);
	}

	inline void operator+=(const Vector3 &vec){
		mins+=vec;
		maxs+=vec;
	}

	inline AABox operator-(const Vector3 &vec) const{
		return AABox(mins-vec,maxs-vec);
	}

	inline void operator-=(const Vector3 &vec){
		mins-=vec;
		maxs-=vec;
	}

	inline AABox operator*(const Vector3 &vec) const{
		return AABox(mins*vec,maxs*vec);
	}

	inline AABox operator/(const Vector3 &vec) const{
		return AABox(mins/vec,maxs/vec);
	}

	//Scalar operations
	inline void operator*=(vrReal f){
		mins*=f;
		maxs*=f;
	}

	inline void operator/=(vrReal f){
		mins/=f;
		maxs/=f;
	}

	Vector3 mins,maxs;
};

//Sphere
class Sphere{
public:
	inline Sphere():radius(0){}
	inline Sphere(const Vector3 &paramOrigin,vrReal paramRadius):origin(paramOrigin),radius(paramRadius){}

	inline Vector3& getOrigin(){
		return origin;
	}

	inline const Vector3& getOrigin() const{
		return origin;
	}

	inline vrReal getRadius() const{
		return radius;
	}

	Vector3 origin;
	vrReal radius;
};

//Miscellanious
AABox calculateTightBox(const std::vector<Vector3> &vertexes);
AABox calculateLooseBox(const std::vector<Vector3> &vertexes);
Sphere makeBoundingSphere(AABox &box);

inline bool fuzzyEqual(vrReal a,vrReal b,vrReal epsilon){
	return(abs(a-b)<epsilon);
}

inline bool fuzzyEqual(const Vector3 &a,const Vector3 &b,vrReal epsilon){
	return(fuzzyEqual(a.x,b.x,epsilon) && fuzzyEqual(a.y,b.y,epsilon) && fuzzyEqual(a.z,b.z,epsilon));
}

}

#endif

