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


/* Generated by Together */



namespace VCF{


/**
The Matrix2D is used for transforming 2D shapes or images. This class is 
intended to represent an affine matrix made up of a 3X3 array or doubles.
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
	*multiply m1 X m2 and store the result in the current instance
	*@return Matrix2D a pointer to the current instance
	*/
    Matrix2D* multiply( Matrix2D* m1, Matrix2D* m2 );

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

	Point* apply( Point* point );

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

	bool operator == ( const Matrix2D& matrix )const;

	/**
	*subscript operator overload for conveniently accessing the matrix
	*elements. Access is provided by using the #defines above, where M_00
	*represents the double value at matrix_[0][0], and M_01 represents
	*the double value at matrix_[0][1], and so forth.
	*/
	double& operator[]( MatrixElementIndex index );

	double operator[]( MatrixElementIndex index ) const;

protected:

	double matrix_[3][3];

private:

};

};


/**
*CVS Log info
*$Log$
*Revision 1.4  2004/12/02 04:11:10  ddiego
*removed some old, extraneous files from graphics kit dir.
*
*Revision 1.3  2004/12/02 02:26:24  ddiego
*removed some old, extraneous files from graphics kit dir.
*
*Revision 1.2  2004/08/07 02:49:17  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.2  2004/04/29 04:10:27  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 03:40:31  ddiego
*migration towards new directory structure
*
*Revision 1.9.4.1  2004/04/26 21:58:40  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.9  2003/12/18 05:15:58  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.8.2.1  2003/10/28 04:06:11  ddiego
*updated the GraphicsContext and ContextPeer classes to support
*slider control drawing. adjusted the Slider control accordingly.
*Also changed some of the GraphicsKit headers to conform to the
*current header style.
*
*Revision 1.8  2003/08/09 02:56:43  ddiego
*merge over from the devmain-0-6-1 branch
*Changes
*Features:
*-Added additional implementation to better support the MVC architecture in
*the VCF
*
*-Added a Document/View architecure that is similar to MFC's or NextSteps's
*Doc/View architectures
*
*-Integrated the Anti Grain Graphics library into the GraphicsKit. There is
*now basic support for it in terms of drawing vector shapes
*(fills and strokes). Image support will come in the next release
*
*-Added several documented graphics tutorials
*
*Bugfixes:
*
*[ 775744 ] wrong buttons on a dialog
*[ 585239 ] Painting weirdness in a modal dialog ?
*[ 585238 ] Modal dialog which makes a modal Dialog
*[ 509004 ] Opening a modal Dialog causes flicker
*[ 524878 ] onDropped not called for MLTcontrol
*
*Plus an issue with some focus and getting the right popup window to activate
*has also been fixed
*
*Revision 1.7.2.1  2003/07/05 04:04:45  ddiego
*added more AGG support
*  added a common AGG header to use when accessing the AGG API directly
*  see the graphics/AggCommon.h header for this
*  Made some minor changes to Path to work a bit simpler
*  Implemented Polygon completely,
*  Implemented BasicFill and BasicStroke - using AGG
*
*Revision 1.7  2003/05/17 20:37:10  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.6.10.3  2003/04/07 03:39:31  ddiego
*did some documentation work, and got everything to compile cleanly with some
*of the new additions, particularly the chnages inteh Image/ImageBits classes.
*
*Revision 1.6.10.2  2003/03/23 03:23:48  marcelloptr
*3 empty lines at the end of the files
*
*Revision 1.6.10.1  2003/03/12 03:10:27  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.6  2002/09/12 03:26:04  ddiego
*merged over the changes from the devmain-0-5-5b branch
*
*Revision 1.5.12.1  2002/08/06 02:57:35  ddiego
*added base X11 files for GraphicsKit and made sure that the GraphicsKit compiles
*under linux (GCC). There is now a new dir under build/xmake called GraphicsKit
*where the xmake build script lives. This checkin also includes the base X11
*include (as part of GraphicsKitPrivate.h), as well as linking to the X11 libs
*
*Revision 1.5  2002/01/24 01:46:48  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


#endif // _VCF_MATRIX2D_H__


