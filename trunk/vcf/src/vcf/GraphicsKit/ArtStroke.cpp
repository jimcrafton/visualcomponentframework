//ArtStroke.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/GraphicsKit/GraphicsKit.h"

using namespace VCF;

ArtStroke::ArtStroke()
{
	init();
}

ArtStroke::~ArtStroke()
{

}

void ArtStroke::init()
{
	context_ = NULL;
	width_  = 21.0;
	color_ = *Color::getColor( RED );
}

void ArtStroke::render( Path * path ){
	if ( (NULL != context_) && (NULL != path) ){

		Matrix2D* currentXFrm = context_->getCurrentTransform();
		PathEnumerator* pathEnum = path->getPathEnumerator( currentXFrm );
		Rect* pathBounds = pathEnum->getBounds();
		ArtVpath *vec = art_new(ArtVpath,1);
		Point lastPt;
		int totPts = 1;
		int i = 0;
		if ( NULL != pathEnum ){
			while ( true == pathEnum->hasMoreSegments() ){
				ulong32 count = pathEnum->getPointCount();
				Point* pts = NULL;
				if ( count > 0 ){
					pts = new Point[count];
					//totPts+= count;
				}
				PathEnumerator::SegmentType type = pathEnum->getSegment( pts );
				switch ( type ){
				case PathEnumerator::SEGMENT_MOVETO: {
					if ( i == 0 ) {
						vec[0].code = ART_MOVETO;
						vec[0].x = pts[0].x_;
						vec[0].y = pts[0].y_;
						i++;
					}
					else {
						art_vpath_add_point( &vec, &i, &totPts, ART_MOVETO, pts[0].x_, pts[0].y_ );
						totPts = i;
					}
					lastPt = pts[0];

													 }
					break;

				case PathEnumerator::SEGMENT_LINETO: {
					if ( i == 0 ) {
						vec[0].code = ART_LINETO;
						vec[0].x = pts[0].x_;
						vec[0].y = pts[0].y_;
						i++;
					}
					else {
						art_vpath_add_point( &vec, &i, &totPts, ART_LINETO, pts[0].x_, pts[0].y_ );
						totPts = i;
					}
					lastPt = pts[0];
													 }
					break;

				case PathEnumerator::SEGMENT_QUADTO: {

													 }
					break;

				case PathEnumerator::SEGMENT_CUBICTO: {

													  }
					break;

				case PathEnumerator::SEGMENT_CLOSE: {

													}
					break;
				}
				pathEnum->next();
				delete [] pts;
			}
			art_vpath_add_point( &vec, &i, &totPts, ART_END, lastPt.x_, lastPt.y_ );


			ArtDRect r = {0};
			art_vpath_bbox_drect( vec, &r );

			//
			double mat[6];
			art_affine_identity( mat );
			art_affine_translate( mat, -r.x0, -r.y0 );

			ArtVpath* xFrmedVec = art_vpath_affine_transform( vec, mat );

			ArtSVP *svp = art_svp_vpath_stroke (xFrmedVec,
				ART_PATH_STROKE_JOIN_ROUND,
				ART_PATH_STROKE_CAP_ROUND, width_, 4, 1.0);

			art_drect_svp( &r, svp );
			//art_affine_translate
			Rect rr( r.x0, r.y0, r.x1, r.y1 );

			//UIGraphicsToolkit::getDefaultGraphicsToolkit()->createImage( rr.getWidth(), rr.getHeight() );

			Image* image = GraphicsToolkit::getDefaultGraphicsToolkit()->createImage( context_, pathBounds );

			if ( NULL != image ) {
				int w = image->getWidth();
				int h = image->getHeight();
				unsigned char* buf = (unsigned char*)image->getImageBits()->bits_;// new unsigned char[(h * w) * 3];
				RGBAVals * tmp = image->getImageBits()->bits_;
				//bgra
				ulong32 c = h * w;
				unsigned char tmpByte = 0;
				for ( ulong32 i=0;i<c;i++){
					tmp[i].a = 255;
					tmpByte = tmp[i].b;
					tmp[i].b = tmp[i].r;
					tmp[i].r = tmpByte;
				}

				//art_rgb_svp_aa( svp, 0, 0, w, h, 0xFF0000, 0x00FFff, buf, w * 3, NULL );

				art_rgb_svp_alpha( svp, 0, 0, w, h, 0xFF00FF20, buf, w*4, NULL );


				//unsigned long c = h * w;
				for ( i=0;i<c;i++){
					/*
					tmp[i].b = buf[i * 3];
					tmp[i].g = buf[i * 3 + 1];
					tmp[i].r = buf[i * 3 + 2];
					*/
					tmpByte = tmp[i].r;
					tmp[i].r = tmp[i].b;
					tmp[i].b = tmpByte;
				}

				context_->drawImage( pathBounds->left_, pathBounds->top_, image );
				delete image;
				//delete []buf;
			}
			context_->setColor( &color_ );
			context_->rectangle( pathBounds );
			context_->strokePath();

			art_free(vec);
			art_free(xFrmedVec);
			art_free(svp);
			}
		}
		//context_->strokePath();
	}


/**
*CVS Log info
*$Log$
*Revision 1.2  2004/08/07 02:49:16  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.2  2004/04/29 04:10:26  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 03:40:30  ddiego
*migration towards new directory structure
*
*Revision 1.7  2003/05/17 20:37:19  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.6.2.2  2003/03/23 03:23:55  marcelloptr
*3 empty lines at the end of the files
*
*Revision 1.6.2.1  2003/03/12 03:11:58  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.6  2003/02/26 04:30:46  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.5.14.1  2003/01/08 00:19:50  marcelloptr
*mispellings and newlines at the end of all source files
*
*Revision 1.5  2002/05/09 03:10:44  ddiego
*merged over code from development branch devmain-0-5-1a into the main CVS trunk
*
*Revision 1.4.4.2  2002/04/27 15:52:22  ddiego
*Changed a bunch of files include and made it a bit faster and added better include
*guards in the common headers
*
*Revision 1.4.4.1  2002/04/03 19:37:17  zzack
*include style changed
*
*Revision 1.4  2002/01/24 01:46:49  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


