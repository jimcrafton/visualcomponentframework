//MicroTiles.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/GraphicsKit/GraphicsKit.h"


using namespace VCF;


#ifndef MIN
#define MIN(a,b) ((a) < (b) ? (a) : (b))
#endif

#ifndef MAX
#define MAX(a,b) ((a) > (b) ? (a) : (b))
#endif



MicroTileArray::MicroTileArray( const int32& x0, const int32& y0, const int32& x1, const int32& y1 )
{
	x0_ = x0;
	y0_ = y0;

	width_ = x1 - x0;
	height_ = y1 - y0;

	//this->UTiles_.resize( width_ * height_, NULL );
}

MicroTileArray::MicroTileArray( const int32& x0, const int32& y0, const int32& x1, const int32& y1, const int32 shiftBy )
{
	setNewCoords( x0, y0, x1, y1, shiftBy );
}

MicroTileArray::MicroTileArray( Rect* rect )
{
	if ( NULL != rect ){
		//ArtMicroTileBBox *utiles;
		MicroTileBBox bb;
		int32 width = 0;
		int32 height = 0;
		int32 x = 0;
		int32 y = 0;
		int32 xf0 = 0;
		int32 yf0 = 0;
		int32 xf1 = 0;
		int32 yf1 = 0;
		int32 ix = 0;

		//uta = art_new (ArtUta, 1);
		this->x0_ = ((int32)rect->left_) >> VCF_UTILE_SHIFT;
		this->y0_ = ((int32)rect->top_) >> VCF_UTILE_SHIFT;
		width = (((int32)(rect->right_) + VCF_UTILE_SIZE - 1) >> VCF_UTILE_SHIFT) - this->x0_;
		height = ((((int32)rect->bottom_) + VCF_UTILE_SIZE - 1) >> VCF_UTILE_SHIFT) - this->y0_;

		this->UTiles_.resize( width * height, NULL );
		//utiles = art_new (ArtMicroTileBBox, width * height);

		this->width_ = width;
		this->height_ = height;
		//this->utiles = utiles;

		xf0 = ((int32)rect->left_) & (VCF_UTILE_SIZE - 1);
		yf0 = ((int32)rect->top_) & (VCF_UTILE_SIZE - 1);
		xf1 = ((((int32)rect->right_) - 1) & (VCF_UTILE_SIZE - 1)) + 1;
		yf1 = ((((int32)rect->bottom_) - 1) & (VCF_UTILE_SIZE - 1)) + 1;
		if (height == 1) {
			if (width == 1){
				this->insertTileAt( 0, xf0, yf0, xf1, yf1 );//==>>utiles[0] = ART_UTA_BBOX_CONS (xf0, yf0, xf1, yf1);
			}
			else {
				this->insertTileAt( 0, xf0, yf0, VCF_UTILE_SIZE, yf1 );//==>>utiles[0] = ART_UTA_BBOX_CONS (xf0, yf0, VCF_UTILE_SIZE, yf1);
				//bb.setBBox( 0, yf0, VCF_UTILE_SIZE, yf1 );
				for (x = 1; x < width - 1; x++){
					this->insertTileAt( x, 0, yf0, VCF_UTILE_SIZE, yf1 );//==>>utiles[x] = bb;
				}
				this->insertTileAt( x, 0, yf0, xf1, yf1 );//==>>utiles[x] = ART_UTA_BBOX_CONS (0, yf0, xf1, yf1);
			}
		}
		else
		{
			if (width == 1)
			{
				insertTileAt( 0, xf0, yf0, xf1, VCF_UTILE_SIZE );//==>>utiles[0] = ART_UTA_BBOX_CONS (xf0, yf0, xf1, VCF_UTILE_SIZE);
				//bb.setBBox( xf0, 0, xf1, VCF_UTILE_SIZE );
				for (y = 1; y < height - 1; y++){
					insertTileAt( y, xf0, 0, xf1, VCF_UTILE_SIZE );//==>>utiles[y] = bb;
				}
				insertTileAt( y, xf0, 0, xf1, yf1 );
			}
			else
			{
				insertTileAt( 0, xf0, yf0, VCF_UTILE_SIZE, VCF_UTILE_SIZE );
				//bb.setBBox( 0, yf0, VCF_UTILE_SIZE, VCF_UTILE_SIZE );
				for (x = 1; x < width - 1; x++){
					insertTileAt( x, 0, yf0, VCF_UTILE_SIZE, VCF_UTILE_SIZE );
				}
				insertTileAt( x, 0, yf0, xf1, VCF_UTILE_SIZE );
				ix = width;
				for (y = 1; y < height - 1; y++) {
					insertTileAt( ix++, xf0, 0, VCF_UTILE_SIZE, VCF_UTILE_SIZE );
					//bb.setBBox( 0, 0, VCF_UTILE_SIZE, VCF_UTILE_SIZE );
					for (x = 1; x < width - 1; x++){
						insertTileAt( ix++, 0, 0, VCF_UTILE_SIZE, VCF_UTILE_SIZE );
					}
					insertTileAt( ix++, 0, 0, xf1, VCF_UTILE_SIZE );
				}
				insertTileAt( ix++, xf0, 0, VCF_UTILE_SIZE, yf1 );
				//bb.setBBox( 0, 0, VCF_UTILE_SIZE, yf1 );
				for (x = 1; x < width - 1; x++) {
					insertTileAt( ix++, 0, 0, VCF_UTILE_SIZE, yf1 );
				}
				insertTileAt( ix++, 0, 0, xf1, yf1 );
			}
		}
	}
}

MicroTileArray::MicroTileArray( VectorPath* path )
{
	Rect bbox;
	//int32* rbuf = NULL;
	int32 i = 0;
	double x = 0.0;
	double y = 0.0;
	int32 sum = 0;
	int32 xt = 0;
	int32 yt = 0;
	//ArtUtaBbox *utiles;
	MicroTileBBox bb;
	int width = 0;
	int height = 0;
	int ix = 0;

	bbox = *(path->getBounds());//==>>art_vpath_bbox_irect (vec, &bbox);

	this->setNewCoords( bbox.left_, bbox.top_, bbox.right_, bbox.bottom_ );//=>>uta = art_uta_new_coords (bbox.x0, bbox.y0, bbox.x1, bbox.y1);

	width = this->width_;
	height = this->height_;

	//resize the tile array
	this->UTiles_.resize( width * height, NULL );

	std::vector<int32> intList;
	for (i = 0; i < width * height; i++)
		intList.push_back(0);

	x = 0;
	y = 0;
	int size = path->getPointCount();
	bool quitloop = false;
	for (i = 0; i<size; i++)  {
		VectorPathPoint* pt = (*path)[i];
		switch (pt->code_)	{
		case PCT_END: {
				quitloop = true;
			};
			break;

			case PCT_MOVETO:{
				x = pt->x_;
				y = pt->y_;
			}
			break;

			case PCT_LINETO: {
				this->addLine( pt->x_, pt->y_, x, y, intList, width );//==>>art_uta_add_line (uta, vec[i].x, vec[i].y, x, y, rbuf, width);
				x = pt->x_;
				y = pt->y_;
			}
			break;
		}
		if ( true == quitloop ){
			break;
		}
    }

	/* now add in the filling from rbuf */
	ix = 0;
	for (yt = 0; yt < height; yt++) {
		sum = 0;
		for (xt = 0; xt < width; xt++){

			sum += intList[ix];
			/* Nonzero winding rule - others are possible, but hardly
			worth it. */
			if (sum != 0) {
				MicroTileBBox newBB(0);

				newBB = ((int32)newBB) & 0xffff0000;
				newBB = ((int32)newBB) | ((VCF_UTILE_SIZE << 8) | VCF_UTILE_SIZE);
				//utiles[ix] = bb;
				this->insertTileAt( ix, newBB );
				if (xt != width - 1) {
					newBB = 0;
					//bb = *(this->UTiles_[ix + 1]);

					newBB = ((int32)newBB) & 0xffff00;
					newBB = ((int32)newBB) | VCF_UTILE_SIZE;
					this->insertTileAt(ix + 1, newBB );
				}
				if (yt != height - 1){
					MicroTileBBox* bb = this->UTiles_[ix + width];
					if ( NULL != bb ){
						*bb = ((int32)*bb) & 0xff0000ff;
						*bb = ((int32)*bb) | VCF_UTILE_SIZE << 8;
						//this->insertTileAt(ix + 1, bb );
						//utiles[ix + width] = bb;
					}
					if (xt != width - 1)
					{
						bb = this->UTiles_[ix + width];
						if ( NULL != bb ){
							*bb = ((int32)*bb) & 0xffff;
						}
					}

				}
			}
			ix++;
		}
    }

	//art_free (rbuf);

	//return uta;
}

MicroTileArray::~MicroTileArray()
{
	std::vector<MicroTileBBox*>::iterator it = this->UTiles_.begin();
	while ( it != UTiles_.end() ){
		MicroTileBBox* bbox = *it;
		delete bbox;
		bbox = NULL;
		it++;
	}
	UTiles_.clear();
}

void MicroTileArray::addLine( double x0, double y0, double x1, double y1,
							 std::vector<int32>& rbuf, int rbuf_rowstride )
{

	int32 xmin = 0;
	int32 ymin = 0;
	double xmax = 0.0;
	double ymax = 0.0;
	int32 xmaxf = 0;
	int32 ymaxf = 0;
	int32 xmaxc = 0;
	int32 ymaxc = 0;
	int xt0 = 0;
	int yt0 = 0;
	int xt1 = 0;
	int yt1 = 0;
	int xf0 = 0;
	int yf0 = 0;
	int xf1 = 0;
	int yf1 = 0;
	int ix = 0;
	int ix1 = 0;
	MicroTileBBox bb(0);

	xmin = floor (MIN(x0, x1));
	xmax = MAX(x0, x1);
	xmaxf = floor (xmax);
	xmaxc = ceil (xmax);
	ymin = floor (MIN(y0, y1));
	ymax = MAX(y0, y1);
	ymaxf = floor (ymax);
	ymaxc = ceil (ymax);
	xt0 = (xmin >> VCF_UTILE_SHIFT) - this->x0_;
	yt0 = (ymin >> VCF_UTILE_SHIFT) - this->y0_;
	xt1 = (xmaxf >> VCF_UTILE_SHIFT) - this->x0_;
	yt1 = (ymaxf >> VCF_UTILE_SHIFT) - this->y0_;
	MicroTileBBox* tile = NULL;
	if (xt0 == xt1 && yt0 == yt1) {
		// entirely inside a microtile, this is easy!
		xf0 = xmin & (VCF_UTILE_SHIFT - 1);
		yf0 = ymin & (VCF_UTILE_SHIFT - 1);
		xf1 = (xmaxf & (VCF_UTILE_SHIFT - 1)) + xmaxc - xmaxf;
		yf1 = (ymaxf & (VCF_UTILE_SHIFT - 1)) + ymaxc - ymaxf;

		ix = yt0 * this->width_ + xt0;

		tile = this->UTiles_[ix];
		//insertTileAt( ix,
		if ( NULL != tile ) {
			if (*tile == 0) {
				tile->setBBox(xf0, yf0, xf1, yf1);
			}
			else {
				tile->setBBox( MIN(tile->getX0(), xf0),
					MIN(tile->getY0(), yf0),
					MAX(tile->getX1(), xf1),
					MAX(tile->getY1(), yf1));
			}
		}
		else {
			insertTileAt( ix, xf0, yf0, xf1, yf1 );
		}

		//uta->utiles[ix] = bb;
	}
	else  {
		double dx, dy;
		int sx, sy;

		dx = x1 - x0;
		dy = y1 - y0;
		sx = dx > 0 ? 1 : dx < 0 ? -1 : 0;
		sy = dy > 0 ? 1 : dy < 0 ? -1 : 0;
		if (ymin == ymaxf)	{
			// special case horizontal (dx/dy slope would be infinite)
			xf0 = xmin & (VCF_UTILE_SIZE - 1);
			yf0 = ymin & (VCF_UTILE_SIZE - 1);
			xf1 = (xmaxf & (VCF_UTILE_SIZE - 1)) + xmaxc - xmaxf;
			yf1 = (ymaxf & (VCF_UTILE_SIZE - 1)) + ymaxc - ymaxf;

			ix = yt0 * this->width_ + xt0;
			ix1 = yt0 * this->width_ + xt1;
			while (ix != ix1){
				tile = this->UTiles_[ix];
				if ( NULL != tile ) {
					if (*tile == 0) {
						tile->setBBox(xf0, yf0, xf1, yf1);
					}
					else {
						tile->setBBox( MIN(tile->getX0(), xf0),
							MIN(tile->getY0(), yf0),
							MAX(tile->getX1(), xf1),
							MAX(tile->getY1(), yf1));
					}
				}
				else {
					insertTileAt( ix, xf0, yf0, xf1, yf1 );
				}
				xf0 = 0;
				ix++;
			}
			tile = this->UTiles_[ix];
			//bb = uta->utiles[ix];
			if ( NULL != tile ){
				if ( 0 == *tile ){
					tile->setBBox( 0, yf0, xf1, yf1 );
				}
				else {
					tile->setBBox( 0,
									MIN(tile->getY0(), yf0),
									MAX(tile->getX1(), xf1),
									MAX(tile->getY1(), yf1) );
				}
			}
			else {
				insertTileAt( ix, 0, yf0, xf1, yf1 );
			}
		}
		else {
			// Do a Bresenham-style traversal of the line
			double dx_dy;
			double x, y;
			double xn, yn;

			// normalize coordinates to uta origin
			x0 -= this->x0_ << VCF_UTILE_SHIFT;
			y0 -= this->y0_ << VCF_UTILE_SHIFT;
			x1 -= this->x0_ << VCF_UTILE_SHIFT;
			y1 -= this->y0_ << VCF_UTILE_SHIFT;
			if (dy < 0)	{
				double tmp;

				tmp = x0;
				x0 = x1;
				x1 = tmp;

				tmp = y0;
				y0 = y1;
				y1 = tmp;

				dx = -dx;
				sx = -sx;
				dy = -dy;
				// we leave sy alone, because it would always be 1,
				//and we need it for the rbuf stuff.
			}
			xt0 = ((int)floor (x0) >> VCF_UTILE_SHIFT);
			xt1 = ((int)floor (x1) >> VCF_UTILE_SHIFT);
			// now [xy]0 is above [xy]1

			ix = yt0 * this->width_ + xt0;
			ix1 = yt1 * this->width_ + xt1;


			dx_dy = dx / dy;
			x = x0;
			y = y0;
			while (ix != ix1) {
				int dix;

				// figure out whether next crossing is horizontal or vertical

				yn = (yt0 + 1) << VCF_UTILE_SHIFT;
				xn = x0 + dx_dy * (yn - y0);
				if (xt0 != (int)floor (xn) >> VCF_UTILE_SHIFT) {
					// horizontal crossing
					xt0 += sx;
					dix = sx;
					if (dx > 0) {
						xn = xt0 << VCF_UTILE_SHIFT;
						yn = y0 + (xn - x0) / dx_dy;

						xf0 = (int)floor (x) & (VCF_UTILE_SHIFT - 1);
						xf1 = VCF_UTILE_SIZE;
					}
					else {
						xn = (xt0 + 1) << VCF_UTILE_SHIFT;
						yn = y0 + (xn - x0) / dx_dy;

						xf0 = 0;
						xmaxc = (int)ceil (x);
						xf1 = xmaxc - ((xt0 + 1) << VCF_UTILE_SHIFT);
					}
					ymaxf = (int)floor (yn);
					ymaxc = (int)ceil (yn);
					yf1 = (ymaxf & (VCF_UTILE_SIZE - 1)) + ymaxc - ymaxf;
				}
				else {
					// vertical crossing
					dix = this->width_;
					xf0 = (int)floor (MIN(x, xn)) & (VCF_UTILE_SIZE - 1);
					xmax = MAX(x, xn);
					xmaxc = (int)ceil (xmax);
					xf1 = xmaxc - (xt0 << VCF_UTILE_SHIFT);
					yf1 = VCF_UTILE_SIZE;

					if ( false == rbuf.empty() )
						rbuf[yt0 * rbuf_rowstride + xt0] += sy;

					yt0++;
				}
				yf0 = (int)floor (y) & (VCF_UTILE_SIZE - 1);

				tile = this->UTiles_[ix];

				if ( NULL != tile ){
					if ( 0 == *tile ){
						tile->setBBox( xf0, yf0, xf1, yf1 );
					}
					else {
						tile->setBBox( MIN(tile->getX0(), xf0),
										MIN(tile->getY0(), yf0),
										MAX(tile->getX1(), xf1),
										MAX(tile->getY1(), yf1) );
					}
				}
				else {
					insertTileAt( ix, xf0, yf0, xf1, yf1 );
				}

				/*bb = uta->utiles[ix];
				if (bb == 0)
					bb = ART_UTA_BBOX_CONS(xf0, yf0, xf1, yf1);
				else
					bb = ART_UTA_BBOX_CONS(MIN(ART_UTA_BBOX_X0(bb), xf0),
					MIN(ART_UTA_BBOX_Y0(bb), yf0),
					MAX(ART_UTA_BBOX_X1(bb), xf1),
					MAX(ART_UTA_BBOX_Y1(bb), yf1));
				uta->utiles[ix] = bb;
				*/

				x = xn;
				y = yn;
				ix += dix;
			}
			xmax = MAX(x, x1);
			xmaxc = ceil (xmax);
			ymaxc = ceil (y1);
			xf0 = (int)floor (MIN(x1, x)) & (VCF_UTILE_SIZE - 1);
			yf0 = (int)floor (y) & (VCF_UTILE_SIZE - 1);
			xf1 = xmaxc - (xt0 << VCF_UTILE_SHIFT);
			yf1 = ymaxc - (yt0 << VCF_UTILE_SHIFT);
			//bb = uta->utiles[ix];
			tile = this->UTiles_[ix];
			if ( NULL != tile ){
				if ( 0 == *tile ){
					tile->setBBox( xf0, yf0, xf1, yf1 );
				}
				else {
					tile->setBBox( MIN( tile->getX0(), xf0),
									MIN( tile->getY0(), yf0),
									MAX(tile->getX1(), xf1),
									MAX(tile->getY1(), yf1) );
				}
			}
			else {
				insertTileAt( ix, xf0, yf0, xf1, yf1 );
			}
		}
	}
}


void MicroTileArray::insertTileAt( const uint32& index, const int32& x0, const int32& y0, const int32& x1, const int32& y1 )
{
	int size = this->UTiles_.size();
	if ( index >= size ) {
		//resize the array
		UTiles_.resize( index, NULL );
	}

	MicroTileBBox* bbox = UTiles_[index];
	if ( NULL == bbox ){
		UTiles_[index] = new MicroTileBBox( x0, y0, x1, y1 );
	}
	else {
		bbox->setBBox( x0, y0, x1, y1 );
	}

}

void MicroTileArray::insertTileAt( const uint32& index, const MicroTileBBox& bbox )
{
	int size = this->UTiles_.size();
	if ( index >= size ) {
		//resize the array
		UTiles_.resize( index, NULL );
	}

	MicroTileBBox* tile = UTiles_[index];
	if ( NULL == tile ){
		UTiles_[index] = new MicroTileBBox( bbox );
	}
	else {
		*tile = bbox;
	}
}

void MicroTileArray::setNewCoords( const int32& x0, const int32& y0, const int32& x1, const int32& y1, const int32 shiftBy )
{
	x0_ = x0 >> shiftBy;
	y0_ = y0 >> shiftBy;
	int32 x = 1 + (x1 >> shiftBy);
	int32 y = 1 + (y1 >> shiftBy);

	width_ = x - x0;
	height_ = y - y0;
	this->UTiles_.clear();
}

MicroTileBBox* MicroTileArray::addMicroTile( const int32& x0, const int32& y0, const int32& x1, const int32& y1 )
{
	MicroTileBBox* result = new MicroTileBBox( x0, y0, x1, y1 );
	this->UTiles_.push_back( result );
	return result;
}

void MicroTileArray::addMicroTile( MicroTileBBox* bbox )
{
	this->UTiles_.push_back( bbox );
}


MicroTileArray* MicroTileArray::unionOf( MicroTileArray* tileArray )
{
	MicroTileArray* result = NULL;

	int32 x0, y0, x1, y1;
	int32 x, y;
	int32 ix, ix1, ix2;
	MicroTileBBox bb;
	MicroTileBBox bb1;
	MicroTileBBox bb2;

	x0 = MIN(this->x0_, tileArray->getX0());
	y0 = MIN(this->y0_, tileArray->getY0());
	x1 = MAX(this->x0_ + this->width_, tileArray->getX0() + tileArray->getWidth() );
	y1 = MAX(this->y0_ + this->height_, tileArray->getY0() + tileArray->getHeight() );

	result = new MicroTileArray( x0, y0, x1, y1 );

	/* could move the first two if/else statements out of the loop */
	ix = 0;
	for (y = y0; y < y1; y++) {
		ix1 = (y - this->y0_) * this->width_ + x0 - this->x0_;
		ix2 = (y - tileArray->getY0()) * tileArray->getWidth() + x0 - tileArray->getX0();
		for (x = x0; x < x1; x++) {
			if ( (x < this->x0_) || (y < this->y0_) ||
				 (x >= this->x0_ + this->width_) || (y >= this->y0_ + this->height_) ){
				bb1 = 0;
			}
			else {
				bb1 = *this->UTiles_[ix1];
			}
			if ( (x < tileArray->getX0()) || (y < tileArray->getY0()) ||
				 (x >= tileArray->getX0() + tileArray->getWidth()) || (y >= tileArray->getY0() + tileArray->getHeight()) ) {
				bb2 = 0;
			}
			else {
				bb2 = *((*tileArray)[ix2]);
			}
			if (bb1 == 0) {
				bb = bb2;
			}
			else if (bb2 == 0) {
				bb = bb1;
			}
			else {
				bb = VCF_UTA_BBOX_CONS( MIN( bb1.getX0(), bb2.getX0() ),
										MIN( bb1.getY0(), bb2.getY1() ),
										MAX( bb1.getX1(), bb2.getX1() ),
										MAX( bb1.getY1(), bb2.getY1() ) );
			}
			result->addMicroTile( new MicroTileBBox(bb) );
			//uta->utiles[ix] = bb;
			ix++;
			ix1++;
			ix2++;
		}
    }
	return result;
}


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
*Revision 1.10  2003/05/17 20:37:22  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.9.2.1  2003/03/12 03:12:04  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.9  2003/02/26 04:30:46  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.8.20.1  2003/01/08 00:19:50  marcelloptr
*mispellings and newlines at the end of all source files
*
*Revision 1.8  2002/01/24 01:46:49  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


