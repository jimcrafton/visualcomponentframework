//BasicStroke.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/GraphicsKit/GraphicsKit.h"
#include "vcf/GraphicsKit/AggCommon.h"
#include "thirdparty/common/agg/include/agg_scanline_p.h"
#include "thirdparty/common/agg/include/agg_conv_dash.h"


using namespace VCF;


BasicStroke::BasicStroke():
	width_(0.0),
	opacity_(1.0),
	color_ (*Color::getColor( VCF::ColorNames::at( VCF::ColorNames::black ) )),
	context_(NULL),		
	antiAlias_(true),
	dashed_(false),
	dashStart_(0.0)
{

}

BasicStroke::~BasicStroke()
{

}


void BasicStroke::setContext( GraphicsContext* context )
{
	context_ = context;
}




void BasicStroke::render( Path * path )
{
	if ( (NULL != context_) && (NULL != path) ){
		context_->setColor( &color_ );


		//JC - we don't need to grab the current transform since it's 
		//applied to the points any how
		//Matrix2D* currentXFrm = context_->getCurrentTransform();
		std::vector<PathPoint> points;
		/**
		JC - changing the Path API a bit here
		*/
		path->getPoints( points, NULL );

		/**
		JC:
		Thanks to Marcello, we have resolved the VC7/7.1 stack corruption
		bug! Apparently, due to some trickery on my part which involved
		const PathPoint& pt = points->nextElement();
		This was causing some weird problems due to referencing a temporary
		copy of the PathPoint. Marcello found this and discovered that if we replaced
		that with the a simply assignment to the variables below, we have no more
		problems! Many, many, many thanks to Marcello for tracking this down and
		fixing it!!!
		*/
		PathPoint pt, p2, c1, c2;

		agg::rendering_buffer* renderingBuffer = context_->getRenderingBuffer();
		std::vector<PathPoint>::iterator pathIt = points.begin();
		
		if ( (NULL == renderingBuffer) || (!antiAlias_) ){
			context_->setStrokeWidth( width_ );

			while ( pathIt != points.end() ) {
				pt = *pathIt;

				switch ( pt.type_ ){
					case PathPoint::ptMoveTo: {
						context_->moveTo( pt.point_.x_, pt.point_.y_ );
					}
					break;

					case PathPoint::ptLineTo: {
						context_->lineTo( pt.point_.x_, pt.point_.y_ );
					}
					break;

					case PathPoint::ptQuadTo: {
						pathIt ++;
						
						c1 = *pathIt;
						
						pathIt ++;
						c2 = *pathIt;

						pathIt++;
						p2 = *pathIt;

						context_->curve( pt.point_.x_, pt.point_.y_,
											c1.point_.x_, c1.point_.y_,
											c2.point_.x_, c2.point_.y_,
											p2.point_.x_, p2.point_.y_ );
					}
					break;

					case PathPoint::ptCubicTo: {

					}
					break;

					case PathPoint::ptClose: {
						context_->lineTo( pt.point_.x_, pt.point_.y_ );
					}
					break;
				}
				
				pathIt ++;
			}
			context_->strokePath();
		}
		else {

			typedef agg::renderer_base<pixfmt> ren_base;
			typedef agg::renderer_scanline_aa_solid<ren_base> renderer_solid;			

			pixfmt pixf(*renderingBuffer);
			ren_base renb(pixf);

			renderer_solid renderer( renb );


			agg::path_storage strokePath;

			agg::rasterizer_scanline_aa<> rasterizer;
			agg::scanline_p8 scanline;

			while ( pathIt != points.end() ) {
				pt = *pathIt;

				switch ( pt.type_ ){
					case PathPoint::ptMoveTo: {
						strokePath.move_to( pt.point_.x_, pt.point_.y_ );
					}
					break;

					case PathPoint::ptLineTo: {
						strokePath.line_to( pt.point_.x_, pt.point_.y_ );
					}
					break;

					case PathPoint::ptQuadTo: {

						strokePath.move_to( pt.point_.x_, pt.point_.y_ );
						
						pathIt++;
						c1 = *pathIt;
						
						pathIt++;
						c2 = *pathIt;
						
						pathIt++;
						p2 = *pathIt;
						
						strokePath.curve4( c1.point_.x_, c1.point_.y_,
										c2.point_.x_, c2.point_.y_,
										p2.point_.x_, p2.point_.y_ );
					}
					break;

					case PathPoint::ptCubicTo: {

					}
					break;

					case PathPoint::ptClose: {
						strokePath.close_polygon();
					}
					break;
				}
				
				pathIt++;
			}

			Matrix2D& currentXFrm = *context_->getCurrentTransform();

			agg::trans_affine mat( currentXFrm[Matrix2D::mei00],
									currentXFrm[Matrix2D::mei01],
									currentXFrm[Matrix2D::mei10],
									currentXFrm[Matrix2D::mei11],
									currentXFrm[Matrix2D::mei20],
									currentXFrm[Matrix2D::mei21] );
			

			//JC
			//I added this to account for anti-aliasing "defects"
			//that occur with thin lines (1-2 pixels wide)
			//See http://antigrain.com/tips/line_alignment/line_alignment.agdoc.html
			//for more information about why this happens, and why this 
			//may not be the optimal solution
			mat*=agg::trans_affine_translation(0.5,0.5);
			

			agg::conv_curve< agg::path_storage > smooth(strokePath);

			agg::conv_transform< agg::conv_curve< agg::path_storage > > xfrmedPath(smooth,mat);

			if( dashed_ ) {
				
				agg::conv_dash< agg::conv_transform< agg::conv_curve< agg::path_storage > > > dash(xfrmedPath);
				
				for(unsigned int j=0; j<dashGapLen_.size(); ++j) {
					dash.add_dash( dashGapLen_[j].first, dashGapLen_[j].second );
				}

				dash.dash_start(dashStart_);				
				
				agg::conv_stroke< agg::conv_dash< agg::conv_transform< agg::conv_curve< agg::path_storage > > > >  stroke(dash);
				
				stroke.width( maxVal<>( 0.5, width_ ) );
				
				rasterizer.add_path( stroke );
			}
			else {

				agg::conv_stroke< agg::conv_transform< agg::conv_curve< agg::path_storage > > >  stroke(xfrmedPath);
				
				stroke.width( maxVal<>( 0.5, width_ ) );
				
				rasterizer.add_path( stroke );
			}			


			renderer.color(agg::rgba(color_.getRed(),color_.getGreen(),color_.getBlue(),opacity_));

			agg::render_scanlines(rasterizer, scanline, renderer);
			//rasterizer.render(scanline,renderer);
		}
	}

}

double BasicStroke::getWidth()
{
	return width_;
}

void BasicStroke::setWidth( double width )
{
	width_ = width;
}

Color* BasicStroke::getColor()
{
	return &color_;
}

void BasicStroke::setColor( Color* color )
{
	color_ = *color;
}

void BasicStroke::line( const double& x1, const double& y1,
		                const double& x2, const double& y2 )
{

}


/**
*CVS Log info
*$Log$
*Revision 1.5  2006/04/07 02:35:41  ddiego
*initial checkin of merge from 0.6.9 dev branch.
*
*Revision 1.4.2.3  2005/11/10 02:02:39  ddiego
*updated the osx build so that it
*compiles again on xcode 1.5. this applies to the foundationkit and graphicskit.
*
*Revision 1.4.2.2  2005/10/17 01:36:34  ddiego
*some more under the hood image stuff. updated agg.
*
*Revision 1.4.2.1  2005/10/06 23:45:52  ddiego
*fixed a small display bug in the BasicStroke class when rendering lines.
*
*Revision 1.4  2005/07/09 23:05:56  ddiego
*added missing gtk files
*
*Revision 1.3.2.1  2005/02/01 19:43:50  dougtinkham
*added dash support for AGG rendering
*
*Revision 1.3  2004/12/01 04:31:42  ddiego
*merged over devmain-0-6-6 code. Marcello did a kick ass job
*of fixing a nasty bug (1074768VCF application slows down modal dialogs.)
*that he found. Many, many thanks for this Marcello.
*
*Revision 1.2.2.2  2004/09/06 03:33:21  ddiego
*updated the graphic context code to support image transforms.
*
*Revision 1.2.2.1  2004/08/31 04:12:13  ddiego
*cleaned up the GraphicsContext class - made more pervasive use
*of transformation matrix. Added common print dialog class. Fleshed out
*printing example more.
*
*Revision 1.2  2004/08/07 02:49:16  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.3  2004/07/09 03:39:30  ddiego
*merged in changes from the OSX branch for new theming API. Added
*support for controlling the use of locale translated strings in components.
*
*Revision 1.1.2.2.2.1  2004/07/06 03:27:13  ddiego
*more osx updates that add proper support
*for lightweight controls, some fixes to text layout, and some window painting issues. Also a fix
*so that controls and windows paint either their default theme background or their background
*color.
*
*Revision 1.1.2.2  2004/04/29 04:10:26  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 03:40:30  ddiego
*migration towards new directory structure
*
*Revision 1.14  2004/04/06 00:01:46  ddiego
*Marcellos fix for the VC7/7.1 stack corruption bug
*caused by my code. Many, many, many thanks to Marcello for
*spending the time to track this down and fix it.
*
*Revision 1.13  2003/12/18 05:16:01  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.12.2.1  2003/10/02 04:50:52  ddiego
*changes to ensure the code compiles on linux. made a bunch of updates to
*the makefiles
*
*Revision 1.12  2003/08/09 02:56:45  ddiego
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
*Revision 1.11.2.7  2003/07/28 23:49:58  ddiego
*check in of the weekend's work from July 25
*learned how to use agg image renedering, now have to integrate it into the
*GraphicsKit - alos enabled setting a viewable bounds that sets the agg cliprect
*as well, useful for later optimizations
*
*Revision 1.11.2.6  2003/07/21 03:08:30  ddiego
*added bezier curve editing to Sketchit, fixed a bug in not saving
*bitmaps, added PackageInfo to the ApplicationKit
*
*Revision 1.11.2.5  2003/07/16 04:59:07  ddiego
*added some changes to the fil and stroke classes to allow changing whether
*they use anti-aliasing or not. Also implemented Matrix2D::invert(),
*plus properly implemented clone() on the DefaultMenuItem class.
*
*Revision 1.11.2.4  2003/07/05 04:04:45  ddiego
*added more AGG support
*  added a common AGG header to use when accessing the AGG API directly
*  see the graphics/AggCommon.h header for this
*  Made some minor changes to Path to work a bit simpler
*  Implemented Polygon completely,
*  Implemented BasicFill and BasicStroke - using AGG
*
*Revision 1.11.2.3  2003/07/03 03:14:51  ddiego
*made some changes to the Path interface, and got rid of the PathEnumerator
*class
*
*Revision 1.11.2.2  2003/06/17 03:54:25  ddiego
*further agg integration - took out the getImage/putImage from GraphicsContext -
*this was too slow. now have an alternate solution that seems to work OK
*
*Revision 1.11.2.1  2003/06/16 03:09:39  ddiego
*beginning to add support for AGG into the VCF GraphicsKit
*added some missing files
*added some changes to the new version of xmake
*
*Revision 1.11  2003/05/17 20:37:19  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.10.2.3  2003/04/17 04:29:50  ddiego
*updated scintilla, added gtk support for the application kit, with stubs
*for the basic peers.
*
*Revision 1.10.2.2  2003/03/23 03:23:55  marcelloptr
*3 empty lines at the end of the files
*
*Revision 1.10.2.1  2003/03/12 03:11:59  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.10  2003/02/26 04:30:46  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.9.8.1  2003/01/08 04:25:56  marcelloptr
*ColorNames static map and Color::s_ now use String instead than String* - VCF_LARGE_COLOR_LIST introduced
*
*Revision 1.9  2002/09/12 03:26:05  ddiego
*merged over the changes from the devmain-0-5-5b branch
*
*Revision 1.8.6.1  2002/08/06 02:57:36  ddiego
*added base X11 files for GraphicsKit and made sure that the GraphicsKit compiles
*under linux (GCC). There is now a new dir under build/xmake called GraphicsKit
*where the xmake build script lives. This checkin also includes the base X11
*include (as part of GraphicsKitPrivate.h), as well as linking to the X11 libs
*
*Revision 1.8  2002/05/09 03:10:44  ddiego
*merged over code from development branch devmain-0-5-1a into the main CVS trunk
*
*Revision 1.7.4.1  2002/04/03 19:37:17  zzack
*include style changed
*
*Revision 1.7  2002/01/24 01:46:49  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


