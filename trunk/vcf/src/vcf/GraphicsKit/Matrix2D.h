#ifndef _VCF_MATRIX2D_H__
#define _VCF_MATRIX2D_H__
//Matrix2D.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif

#ifndef AGG_TRANS_AFFINE_INCLUDED
#include "thirdparty/common/agg/include/agg_trans_affine.h"
#endif 





namespace VCF {
const double MatrixEpsilon = 1e-14; // About of precision of doubles

/**
\class Matrix2D Matrix2D.h "vcf/GraphicsKit/Matrix2D.h"
The Matrix2D is used for transforming 2D shapes or images. This class is 
intended to represent an affine matrix made up of a 3X3 array of doubles.
@see GraphicsContext
@see Path
*/
class GRAPHICSKIT_API Matrix2D : public Object {
public:
	

	/**
	Use the values of these enums to
	reference a value of the matrix
	*/
	enum MatrixElementIndex{
		/**
		references element at 0,0 in matrix
		*/
		mei00 = 0,

		/**
		references element at 0,1 in matrix
		*/
		mei01 = 1,

		/**
		references element at 0,2 in matrix
		*/
		mei02 = 2,

		/**
		references element at 1,0 in matrix
		*/
		mei10 = 3,

		/**
		references element at 1,1 in matrix
		*/
		mei11 = 4,

		/**
		references element at 1,2 in matrix
		*/
		mei12 = 5,

		/**
		references element at 2,0 in matrix
		*/
		mei20 = 6,

		/**
		references element at 2,1 in matrix
		*/
		mei21 = 7,

		/**
		references element at 2,2 in matrix
		*/
		mei22 = 8
	};


	Matrix2D();

	Matrix2D ( const Matrix2D& matrix );

	Matrix2D ( const agg::trans_affine& matrix );
	

	virtual ~Matrix2D();

	/**
	*transposes the matrix
	*@param Matrix2D dest the matrix that is transposed by this
	*matrix.
	*/
    void transpose( Matrix2D* dest );

	/**
	*creates a reflection matrix
	*@param bool reflectX whether or not to reflect on the X axis
	*@param bool reflectY whether or not to reflect on the Y axis
	*/
    void reflect( const bool& reflectX, const bool& reflectY );

	/**
	*creates a rotation matrix
	*@param double the angle of the newly created rotation matrix
	*from 0.0..360.0
	*/
    void rotate( const double& theta );

	/**
	*creates a shear matrix
	*@param double shearX the amount to shear along the X axis ranges in degrees
	*from 0.0...360.0
	*@param double shearY the amount to shear along the Y axis ranges in degrees
	*from 0.0...360.0
	*/
    void shear( const double& shearX, const double& shearY );

	/**
	*creates a scale matrix
	*<code>
	*|0|scaleX|0|
	*|scaleY|0|0|
	*|0|0|1|
	*</code>
	*@param double scaleX the amount of scaling to apply along the x axis
	*@param double scaleY the amount of scaling to apply along the Y axis
	*/
    void scale( const double& scaleX, const double& scaleY );

	/**
	*Creates an identity matrix
	*<code>
	*|1|0|0|
	*|0|1|0|
	*|0|0|1|
	*</code>
	*/
    void identity();

	/**
	*multiply m1 X this instance
	*@return Matrix2D a reference to the current instance
	*/
    Matrix2D& multiply( const Matrix2D& rhs );


	Matrix2D& premultiply( const Matrix2D& rhs ) {
		Matrix2D tmp = rhs;
		*this = tmp.multiply(*this);
		return *this;	
	}

	/**
	*creates a translation matrix
	*@param double transX the amount to translate along the X axis
	*@param double transY the amount to translate along the Y axis
	*/
    void translate( const double& transX, const double& transY );

	/**
	*inverts the current matrix
	*/
	void invert();

	Point apply( Point* point ) const;

	void apply( double& x, double& y ) const;

	Rect apply( Rect* rect ) const;

	/**
	*is the current matrix instance equal to the object passed in ?
	*where hopefully the object is a pointer to a Matrix2D instance.
	@return  bool true if the two Matrix2D's matrix_ data is equal in
	*value, otherwise false
	*/
	virtual bool isEqual( Object* object )const;

	/**
	*copy the data in the Matrix2D source into the current
	*instance.
	*/
	virtual void copy( Object* source );


	Matrix2D& operator= ( const Matrix2D& matrix );

	Matrix2D& operator= ( const agg::trans_affine& matrix );
	
	operator agg::trans_affine () const;

	bool operator == ( const Matrix2D& matrix )const;

	/**
	*subscript operator overload for conveniently accessing the matrix
	*elements. Access is provided by using the #defines above, where M_00
	*represents the double value at matrix_[0][0], and M_01 represents
	*the double value at matrix_[0][1], and so forth.
	*/
	double& operator[]( MatrixElementIndex index );

	double operator[]( MatrixElementIndex index ) const;

	Matrix2D& operator *= (const Matrix2D& rhs ) {

		return multiply( rhs );
	}

	Matrix2D& operator /= (const Matrix2D& rhs ) {
		Matrix2D tmp = rhs;
        tmp.invert();
        return multiply(tmp);
	}

	Matrix2D operator * (const Matrix2D& rhs ) {
		Matrix2D result(*this);
		result.multiply( rhs );
		return result;
	}

	Matrix2D operator / (const Matrix2D& rhs ) {
		Matrix2D result(*this);
		Matrix2D tmp = rhs;
		tmp.invert();
		result.multiply( tmp );
		return result;
	}

	Matrix2D operator ~ () const{
		Matrix2D result(*this);
		result.invert();
		return result;
	}


	bool isIdentity(double epsilon = MatrixEpsilon) const;

	bool isTranslationOnly(double epsilon = MatrixEpsilon) const;

	double getRotation() const;
	double getScaleX() const ;
	double getScaleY() const ;
	double getTranslateX() const ;
	double getTranslateY() const ;
	double getShearX() const ;
	double getShearY() const ;

	void getScale( double& x, double& y ) const;
	void getTranslation( double& x, double& y ) const;
	void getShear( double& x, double& y ) const;

	
	static Matrix2D rotation(const double& theta) {
		Matrix2D m;
		m.rotate(theta);
		return m;
	}

	static Matrix2D translation(const double& x, const double& y) {
		Matrix2D m;
		m.translate(x,y);
		return m;
	}

	static Matrix2D scaling(const double& sx, const double& sy) {
		Matrix2D m;
		m.scale(sx,sy);
		return m;
	}

	static Matrix2D shearing(const double& shx, const double& shy) {
		Matrix2D m;
		m.shear(shx,shy);
		return m;
	}


protected:
	double matrix_[3][3];

};



};


#endif // _VCF_MATRIX2D_H__

/**
$Id$
*/
