#ifndef _VCF_MICROTILES_H__
#define _VCF_MICROTILES_H__
//MicroTiles.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCF {

#define VCF_UTA_BBOX_CONS(x0, y0, x1, y1) (((x0) << 24) | ((y0) << 16) | \
				       ((x1) << 8) | (y1))

#define VCF_UTA_BBOX_X0(ub) ((ub) >> 24)
#define VCF_UTA_BBOX_Y0(ub) (((ub) >> 16) & 0xff)
#define VCF_UTA_BBOX_X1(ub) (((ub) >> 8) & 0xff)
#define VCF_UTA_BBOX_Y1(ub) ((ub) & 0xff)

#define VCF_UTILE_SHIFT 5
#define VCF_UTILE_SIZE (1 << VCF_UTILE_SHIFT)

class GRAPHICSKIT_API MicroTileBBox {
public:
	MicroTileBBox( const int32& x0=0, const int32& y0=0, const int32& x1=0, const int32& y1=0 ){
		bbox_ = VCF_UTA_BBOX_CONS(x0,y0,x1,y1);
	}

	MicroTileBBox( const MicroTileBBox& bbox ){
		bbox_ = bbox.bbox_;
	}

	virtual ~MicroTileBBox(){};

	int32 getX0() const {
		return VCF_UTA_BBOX_X0(bbox_);
	}

	int32 getY0() const {
		return VCF_UTA_BBOX_Y0(bbox_);
	}

	int32 getX1() const {
		return VCF_UTA_BBOX_X1(bbox_);
	}

	int32 getY1() const {
		return VCF_UTA_BBOX_Y1(bbox_);
	}

	operator uint32 () const{
		return bbox_;
	}

	operator Rect () const{
		Rect result( VCF_UTA_BBOX_X0(bbox_),
			         VCF_UTA_BBOX_Y0(bbox_),
					 VCF_UTA_BBOX_X1(bbox_),
					 VCF_UTA_BBOX_Y1(bbox_) );
		return result;
	}

	operator= ( const int32& bbox ){
		bbox_ = (uint32)bbox;
	}

	operator= ( const uint32& bbox ){
		bbox_ = bbox;
	}

	operator= ( const Rect& rect ){
		bbox_ = VCF_UTA_BBOX_CONS( (int32)rect.left_,
			                        (int32)rect.top_,
									(int32)rect.right_,
									(int32)rect.bottom_ );
	}

	operator= ( Rect* rect ){
		if ( NULL != rect ){
			bbox_ = VCF_UTA_BBOX_CONS( (int32)rect->left_,
				                        (int32)rect->top_,
										(int32)rect->right_,
										(int32)rect->bottom_ );
		}
	}

	void setBBox( const int32& x0, const int32& y0, const int32& x1, const int32& y1 ){
		bbox_ = VCF_UTA_BBOX_CONS(x0,y0,x1,y1);
	}
private:
	uint32 bbox_;
};


class VectorPath;

/**
*micro tile arrays
*!!!!!!WARNING !!!!!
*currently implemented using a vector of MicroTileBBox. This is extremely slow
*and should be replaced with an array of MicroTileBBox[] allocated a construction or
*if resizing takes place.
*/
class GRAPHICSKIT_API MicroTileArray {
public:
	MicroTileArray( const int32& x0, const int32& y0, const int32& x1, const int32& y1 );

	MicroTileArray( const int32& x0, const int32& y0, const int32& x1, const int32& y1, const int32 shiftBy );

	MicroTileArray( Rect* rect );

	MicroTileArray( VectorPath* path );

	virtual ~MicroTileArray();

	int32 getX0(){
		return x0_;
	}

	int32 getY0(){
		return y0_;
	}

	int32 getWidth(){
		return width_;
	}

	int32 getHeight(){
		return height_;
	}

	void setWidth( const int32& width ){
		width_ = width;
	}

	void setHeight( const int32& height ){
		height_ = height;
	}

	void setX0( const int32& x0 ){
		x0_ = x0;
	}

	void setY0( const int32& y0 ){
		y0_ = y0;
	}

	void setNewCoords( const int32& x0, const int32& y0, const int32& x1, const int32& y1, const int32 shiftBy=VCF_UTILE_SHIFT );

	MicroTileBBox* addMicroTile( const int32& x0, const int32& y0, const int32& x1, const int32& y1 );

	void addMicroTile( MicroTileBBox* bbox );

	MicroTileArray* unionOf( MicroTileArray* tileArray );

	void addLine( double x0, double y0, double x1, double y1,
		          std::vector<int32>& rbuf, int rbuf_rowstride );

	MicroTileBBox* operator[] ( const int32& pos ){
		return UTiles_[pos];
	}

	uint32 getTileCount(){
		return UTiles_.size();
	}

	/**
	*this sets the tile a the requested index. If the index is out of bounds, then the array is resized
	*by the delta, and a new MicroTileBBox is created. If the index is in bounds, then
	*if there is alread data at that index, the data is freed, and then a new MicroTileBBox is created
	*otherwise the existing MicroTileBBox's setBBox() is called
	*/
	void insertTileAt( const uint32& index, const int32& x0, const int32& y0, const int32& x1, const int32& y1 );

	void insertTileAt( const uint32& index, const MicroTileBBox& bbox );
private:
	int32 x0_;
	int32 y0_;
	int32 width_;
	int32 height_;
	std::vector<MicroTileBBox*> UTiles_;
};

}; //end of namespace VCF


/**
*CVS Log info
*$Log$
*Revision 1.2  2004/08/07 02:49:17  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.2  2004/04/29 04:10:27  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 03:40:31  ddiego
*migration towards new directory structure
*
*Revision 1.9.8.1  2004/04/26 21:58:40  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.9  2003/05/17 20:37:10  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.8.2.1  2003/03/12 03:10:28  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.8  2003/02/26 04:30:39  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.7.20.1  2003/01/08 00:19:44  marcelloptr
*mispellings and newlines at the end of all source files
*
*Revision 1.7  2002/01/24 01:46:48  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


#endif // _VCF_MICROTILES_H__


