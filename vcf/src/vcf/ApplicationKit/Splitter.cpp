//Splitter.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


//Splitter.h
#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/Splitter.h"


using namespace VCF;


Splitter::Splitter( const AlignmentType& alignment/*=AlignLeft*/ ):
	CustomControl(true)
{
	init();
	setAlignment( alignment );
}

void Splitter::init()
{
	attachedControl_ = NULL;
	//setCursorID( (long)Cursor::SCT_SPLIT_VERT );
	//setAlignment( AlignLeft );
	dragPoint_.x_ = 0.0;
	dragPoint_.y_ = 0.0;
	attachedControlAlt_ = NULL;
	outmostControl_ = NULL;
	deltaRestore_ = 0.0;
	deltaRestoreAlt_ = 0.0;
	minimumWidth_ = 5.0;
	dblClickEnabled_ = true;

	setWidth( getPreferredWidth() );
	setHeight( getPreferredHeight() );
}

Splitter::~Splitter()
{

}

void Splitter::setAlignment( const AlignmentType& alignment )
{
	Control::setAlignment( alignment );
	if ( AlignTop == alignment || AlignBottom == alignment ) {
		this->setCursorID( (long)Cursor::SCT_SPLIT_HORZ );
	} else {
		this->setCursorID( (long)Cursor::SCT_SPLIT_VERT );
	}
}

void Splitter::setMinimumWidth( const double& _minimumWidth )
{
	// if 0 then resizeChidrenUsingBounds would make the control disapperar
	minimumWidth_ = VCF::maxVal<double>( 0.5, _minimumWidth );
}

double Splitter::getMinimumWidth()
{
	return minimumWidth_;
}

void Splitter::mouseDown( MouseEvent* e )
{
 	Container* container = getParent()->getContainer();
	if ( NULL == container ) {
		return;
	}

	Enumerator<Control*>* children = NULL;
	Control* child = NULL;

	CustomControl::mouseDown( e );
	keepMouseEvents();
	dragPoint_ = *(e->getPoint());
	Point tmp = dragPoint_;
	switch ( this->getAlignment() ) {
		case AlignLeft : {
			tmp.x_ = this->getLeft() - 1.0;
		}
		break;

		case AlignTop : {
			tmp.y_ = this->getTop() - 1.0;
		}
		break;

		case AlignRight : {
			tmp.x_ = this->getLeft() + this->getWidth() + 1.0;
		}
		break;

		case AlignBottom : {
			tmp.y_ = this->getTop() + this->getHeight() + 1.0;
		}
		break;
	}


	this->attachedControl_ = NULL;
	children = container->getChildren();
	while ( children->hasMoreElements() ) {
		child = children->nextElement();
		if ( true == (child->getBounds().containsPt( &tmp )) ) {
			this->attachedControl_ = child;
			//StringUtils::traceWithArgs( "attachedControl_.toolTip_: \"%s\"\r\n", child->getToolTipText().c_str() );
			break;
		}
	}

	//if ( e->hasShiftKey() )
	//{
		tmp = dragPoint_;
		switch ( this->getAlignment() ) {
			case AlignLeft : {
				tmp.x_ = this->getLeft() + this->getWidth() + 1.0;
			}
			break;

			case AlignTop : {
				tmp.y_ = this->getTop() + this->getHeight() + 1.0;
			}
			break;

			case AlignRight : {
				tmp.x_ = this->getLeft() - 1.0;
			}
			break;

			case AlignBottom : {
				tmp.y_ = this->getTop() - 1.0;
			}
			break;
		}
		this->attachedControlAlt_ = NULL;
		children = container->getChildren();
		while ( children->hasMoreElements() ) {
			child = children->nextElement();
			if ( true == (child->getBounds().containsPt( &tmp )) ) {
				this->attachedControlAlt_ = child;
				//StringUtils::traceWithArgs( "attachedControlAlt_.toolTip_: \"%s\"\r\n", child->getToolTipText().c_str() );
				break;
			}
		}
	//}
}

void Splitter::updateAttachedControl( Point* pt, const bool& shiftAll/*=false*/ )
{
	//StringUtils::trace( "updateAttachedControl\r\n" );

	double parentWidth = getParent()->getWidth()-1;
	double parentHeight = getParent()->getHeight()-1;

 	Container* container = getParent()->getContainer();
	if ( NULL == container ) {
		return;
	}

	Control* controlLast = (dynamic_cast<StandardContainer*>(container))->getControlInAlignmentList( this->getAlignment(), false );
	if ( NULL == controlLast ) {
		return;
	}

	// This doesn't seems to make a difference though for the minor flickering (?) problem
	// This doesn't really seems to be a flickering problem, but instead the fact that the
	// scrollbars don't move with the control ( immediately ) as they should
	// If that is the problem then beginSetBounds / endSetBounds should be removed from here
	container->getContainerControl()->getPeer()->beginSetBounds( 2 );	// 2 or 3 ? I think 2

	bool shouldResize = true;
	double delta, deltaAlt, width, widthMax, newWidth, widthAlt, newWidthAlt;

	switch ( this->getAlignment() ) {
		case AlignLeft : {
			delta = pt->x_ - dragPoint_.x_;
			if ( 0 < delta && controlLast->getWidth() < minimumWidth_ ) {
				//too complicated and it does not work right: delta -= ( minimumWidth_ - controlLast->getWidth() );
				shouldResize = false;
			}
			if ( NULL != attachedControl_ ) {
				width = attachedControl_->getWidth();
				widthMax = parentWidth - attachedControl_->getLeft() - minimumWidth_ - this->getWidth();
				newWidth =  VCF::minVal<double>( widthMax, VCF::maxVal<double>( minimumWidth_, width + delta ) );
				if ( width != newWidth ) {
					if ( !shiftAll && NULL != attachedControlAlt_ ) {
						delta = ( newWidth - width );
						widthAlt = attachedControlAlt_->getWidth();
						widthMax = attachedControlAlt_->getRight() - minimumWidth_ - this->getWidth();
						newWidthAlt =  VCF::minVal<double>( widthMax, VCF::maxVal<double>( minimumWidth_, widthAlt - delta ) );
						deltaAlt = ( newWidthAlt - widthAlt );
						if ( !shouldResize && minimumWidth_ < newWidthAlt ) {
							shouldResize = true;	// let the splitter to resize even if the last control is already at the minimum size
						}
						if ( shouldResize ) {
							attachedControlAlt_->setLeft( attachedControlAlt_->getLeft() - deltaAlt );
							attachedControlAlt_->setWidth( newWidthAlt );
							//StringUtils::traceWithArgs( "updateAttachedControl newWidthAlt: %3.1f  deltaAlt: [%.3f]\r\n" ,newWidthAlt, deltaAlt );
						}
					}
					if ( shouldResize ) {
						attachedControl_->setWidth( newWidth );
						//StringUtils::traceWithArgs( "updateAttachedControl newWidth: %3.1f  delta: [%.3f]\r\n" ,newWidth, delta );
					}
				}
			}
		}
		break;

		case AlignTop : {
			delta = pt->y_ - dragPoint_.y_;
			if ( 0 < delta && controlLast->getHeight() < minimumWidth_ ) {
				//too complicated and it does not work right: delta -= ( minimumWidth_ - controlLast->getHeight() );
				shouldResize = false;
			}
			if ( NULL != attachedControl_ ) {
				width = attachedControl_->getHeight();
				widthMax = parentHeight - attachedControl_->getTop() - minimumWidth_ - this->getHeight();
				newWidth = VCF::minVal<double>( widthMax, VCF::maxVal<double>( minimumWidth_, width + delta ) );
				if ( width != newWidth ) {
					if ( !shiftAll && NULL != attachedControlAlt_ ) {
						delta = ( newWidth - width );
						widthAlt = attachedControlAlt_->getHeight();
						widthMax = attachedControlAlt_->getBottom() - minimumWidth_ - this->getHeight();
						newWidthAlt =  VCF::minVal<double>( widthMax, VCF::maxVal<double>( minimumWidth_, widthAlt - delta ) );
						deltaAlt = ( newWidthAlt - widthAlt );
						if ( !shouldResize && minimumWidth_ < newWidthAlt ) {
							shouldResize = true;	// let the splitter to resize even if the last control is already at the minimum size
						}
						if ( shouldResize ) {
							attachedControlAlt_->setTop( attachedControlAlt_->getTop() - deltaAlt );
							attachedControlAlt_->setHeight( newWidthAlt );
							//StringUtils::traceWithArgs( "updateAttachedControl newHeightAlt: %3.1f  deltaAlt: [%.3f]\r\n" ,newWidthAlt, deltaAlt );
						}
					}
					if ( shouldResize ) {
						attachedControl_->setHeight( newWidth );
						//StringUtils::traceWithArgs( "updateAttachedControl newHeight: %3.1f  delta: [%.3f]\r\n" ,newWidth, delta );
					}
				}
			}
		}
		break;

		case AlignRight : {
			//delta_ = dragPoint_.x_ - pt->x_;
			delta = -(pt->x_ - dragPoint_.x_);
			if ( 0 < delta && controlLast->getWidth() < minimumWidth_ ) {
				//too complicated and it does not work right: delta -= ( minimumWidth_ - controlLast->getWidth() );
				shouldResize = false;
			}
			if ( NULL != attachedControl_ ) {
				width = attachedControl_->getWidth();
				widthMax = attachedControl_->getRight() - minimumWidth_ - this->getWidth();	//2ch
				newWidth =  VCF::minVal<double>( widthMax, VCF::maxVal<double>( minimumWidth_, width + delta ) );
				if ( width != newWidth ) {
					if ( !shiftAll && NULL != attachedControlAlt_ ) {
						delta = ( newWidth - width );
						widthAlt = attachedControlAlt_->getWidth();
						widthMax = parentWidth - attachedControlAlt_->getLeft() - minimumWidth_ - this->getWidth();	//2ch
						newWidthAlt =  VCF::minVal<double>( widthMax, VCF::maxVal<double>( minimumWidth_, widthAlt - delta ) );
						deltaAlt = ( newWidthAlt - widthAlt );
						if ( !shouldResize && minimumWidth_ < newWidthAlt ) {
							shouldResize = true;	// let the splitter to resize even if the last control is already at the minimum size
						}
						if ( shouldResize ) {
							attachedControlAlt_->setRight( attachedControlAlt_->getRight() - deltaAlt );	//2ch
							attachedControlAlt_->setWidth( newWidthAlt );
							//StringUtils::traceWithArgs( "updateAttachedControl newWidthAlt: %3.1f  deltaAlt: [%.3f]\r\n" ,newWidthAlt, deltaAlt );
						}
					}
					if ( shouldResize ) {
						attachedControl_->setWidth( newWidth );
						//StringUtils::traceWithArgs( "updateAttachedControl newWidth: %3.1f  delta: [%.3f]\r\n" ,newWidth, delta );
					}
				}
			}
		}
		break;

		case AlignBottom : {
			//delta_ = dragPoint_.y_ - pt->y_;
			delta = -(pt->y_ - dragPoint_.y_);
			if ( 0 < delta && controlLast->getHeight() < minimumWidth_ ) {
				//too complicated and it does not work right: delta -= ( minimumWidth_ - controlLast->getHeight() );
				shouldResize = false;
			}
			if ( NULL != attachedControl_ ) {
				width = attachedControl_->getHeight();
				widthMax = attachedControl_->getBottom() - minimumWidth_ - this->getHeight();	//2ch
				newWidth = VCF::minVal<double>( widthMax, VCF::maxVal<double>( minimumWidth_, width + delta ) );
				if ( width != newWidth ) {
					if ( !shiftAll && NULL != attachedControlAlt_ ) {
						delta = ( newWidth - width );
						widthAlt = attachedControlAlt_->getHeight();
						widthMax = parentHeight - attachedControlAlt_->getTop() - minimumWidth_ - this->getHeight();	//2ch
						newWidthAlt =  VCF::minVal<double>( widthMax, VCF::maxVal<double>( minimumWidth_, widthAlt - delta ) );
						deltaAlt = ( newWidthAlt - widthAlt );
						if ( !shouldResize && minimumWidth_ < newWidthAlt ) {
							shouldResize = true;	// let the splitter to resize even if the last control is already at the minimum size
						}
						if ( shouldResize ) {
							attachedControlAlt_->setBottom( attachedControlAlt_->getBottom() - deltaAlt );	//2ch
							attachedControlAlt_->setHeight( newWidthAlt );
							//StringUtils::traceWithArgs( "updateAttachedControl newHeightAlt: %3.1f  deltaAlt: [%.3f]\r\n" ,newWidthAlt, deltaAlt );
						}
					}
					if ( shouldResize ) {
						attachedControl_->setHeight( newWidth );
						//StringUtils::traceWithArgs( "updateAttachedControl newHeight: %3.1f  delta: [%.3f]\r\n" ,newWidth, delta );
					}
				}
			}
		}
		break;

	}

	// This doesn't seems to make a difference though for the minor flickering (?) problem
	// This doesn't really seems to be a flickering problem, but instead the fact that the
	// scrollbars don't move with the control ( immediately ) as they should
	// If that is the problem then beginSetBounds / endSetBounds should be removed from here
	container->getContainerControl()->getPeer()->endSetBounds();

 	//Container* container = getParent()->getContainer();
	//if ( NULL != container ) {
	container->resizeChildren( NULL );
	//}
}

void Splitter::mouseMove( MouseEvent* e )
{
	CustomControl::mouseMove( e );
	if ( e->hasLeftButton() ) {
		updateAttachedControl( e->getPoint(), e->hasShiftKey() );
	}
}

void Splitter::mouseUp( MouseEvent* e )
{
	//StringUtils::trace( "mouseUp\r\n" );

	CustomControl::mouseUp( e );
	this->releaseMouseEvents();

	updateAttachedControl( e->getPoint(), e->hasShiftKey() );
}

void Splitter::mouseDblClick( MouseEvent* e )
{
	if ( !dblClickEnabled_ ) {
		return;
	}

	//StringUtils::trace( "mouseDblClick\r\n" );

	CustomControl::mouseDblClick( e );
	if ( e->hasLeftButton() ) {
		Point pt = *(e->getPoint());

		double parentWidth = getParent()->getWidth()-1;
		double parentHeight = getParent()->getHeight()-1;
		double width, widthMax;
		double newWidth = 0.0;

		switch ( this->getAlignment() ) {
			case AlignLeft : {
				if ( e->hasShiftKey() )
				{
					if ( NULL != attachedControl_ ) {
						width = attachedControl_->getWidth();// - minimumWidth_ - this->getWidth();
						widthMax = parentWidth - attachedControl_->getLeft() - minimumWidth_ - this->getWidth();
						newWidth =  VCF::minVal<double>( widthMax, VCF::maxVal<double>( minimumWidth_, width ) );
						if ( newWidth == minimumWidth_ ) {
							pt.x_ += deltaRestore_;
						} else {
							pt.x_ -= newWidth - minimumWidth_;
							deltaRestore_ = newWidth - minimumWidth_;
						}
					}
				}
				else
				{
					if ( NULL != attachedControlAlt_ ) {
						width = attachedControlAlt_->getWidth() - minimumWidth_ - this->getWidth();
						widthMax = attachedControlAlt_->getRight() - minimumWidth_ - this->getWidth();
						newWidth =  VCF::minVal<double>( widthMax, VCF::maxVal<double>( minimumWidth_, width ) );
						if ( newWidth == minimumWidth_ ) {
							pt.x_ -= deltaRestore_;
						} else {
							pt.x_ += newWidth;
							deltaRestore_ = newWidth /*+ minimumWidth_ + this->getWidth()*/;
						}
					}
				}
				//StringUtils::traceWithArgs( "mouseDblClick delta_: %3.1f\r\n" ,delta_ );
			}
			break;

			case AlignTop : {
				if ( e->hasShiftKey() )
				{
					if ( NULL != attachedControl_ ) {
						width = attachedControl_->getHeight();
						widthMax = parentHeight - attachedControl_->getTop();// - minimumWidth_ - this->getHeight();
						newWidth =  VCF::minVal<double>( widthMax, VCF::maxVal<double>( minimumWidth_, width ) );
						if ( newWidth == minimumWidth_ ) {
							pt.y_ += deltaRestore_;
						} else {
							pt.y_ -= newWidth - minimumWidth_;
							deltaRestore_ = newWidth - minimumWidth_;
						}
					}
				}
				else
				{
					if ( NULL != attachedControlAlt_ ) {
						width = attachedControlAlt_->getHeight() - minimumWidth_ - this->getHeight();
						widthMax = attachedControlAlt_->getBottom() - minimumWidth_ - this->getHeight();
						newWidth =  VCF::minVal<double>( widthMax, VCF::maxVal<double>( minimumWidth_, width ) );
						if ( newWidth == minimumWidth_ ) {
							pt.y_ -= deltaRestore_;
						} else {
							pt.y_ += newWidth;
							deltaRestore_ = newWidth /*+ minimumWidth_ + this->getWidth()*/;
						}
					}
				}
			}
			break;

			case AlignRight : {
				if ( e->hasShiftKey() )
				{
					if ( NULL != attachedControl_ ) {
						width = attachedControl_->getWidth();// - minimumWidth_ - this->getWidth();
						widthMax = attachedControl_->getRight() - minimumWidth_ - this->getWidth();
						newWidth =  VCF::minVal<double>( widthMax, VCF::maxVal<double>( minimumWidth_, width ) );
						if ( newWidth == minimumWidth_ ) {
							pt.x_ -= deltaRestore_;
						} else {
							pt.x_ += newWidth - minimumWidth_;
							deltaRestore_ = newWidth - minimumWidth_;
						}
					}
				}
				else
				{
					if ( NULL != attachedControlAlt_ ) {
						width = attachedControlAlt_->getWidth() - minimumWidth_ - this->getWidth();
						widthMax = parentWidth - attachedControlAlt_->getLeft() - minimumWidth_ - this->getWidth();
						newWidth =  VCF::minVal<double>( widthMax, VCF::maxVal<double>( minimumWidth_, width ) );
						if ( newWidth == minimumWidth_ ) {
							pt.x_ += deltaRestore_;
						} else {
							pt.x_ -= newWidth;
							deltaRestore_ = newWidth;
						}
					}
				}
			}
			break;

			case AlignBottom : {
				if ( e->hasShiftKey() )
				{
					if ( NULL != attachedControl_ ) {
						width = attachedControl_->getHeight();// - minimumWidth_ - this->getHeight();	//2ch
						widthMax = attachedControl_->getBottom() - minimumWidth_ - this->getHeight();	//2ch
						newWidth =  VCF::minVal<double>( widthMax, VCF::maxVal<double>( minimumWidth_, width ) );
						if ( newWidth == minimumWidth_ ) {
							pt.y_ -= deltaRestore_;
						} else {
							pt.y_ += newWidth - minimumWidth_;
							deltaRestore_ = newWidth - minimumWidth_;
						}
					}
				}
				else
				{
					if ( NULL != attachedControlAlt_ ) {
						width = attachedControlAlt_->getHeight() - minimumWidth_ - this->getHeight();	//2ch
						widthMax = parentWidth - attachedControlAlt_->getTop() - minimumWidth_ - this->getHeight();	//2ch
						newWidth =  VCF::minVal<double>( widthMax, VCF::maxVal<double>( minimumWidth_, width ) );
						if ( newWidth == minimumWidth_ ) {
							pt.y_ += deltaRestore_;
						} else {
							pt.y_ -= newWidth;
							deltaRestore_ = newWidth;
						}
					}
				}
			}
			break;

		}

		updateAttachedControl( &pt, e->hasShiftKey() );
	}
}

void Splitter::paint( GraphicsContext* ctx )
{
	CustomControl::paint( ctx );
	Rect r( 0, 0, getWidth(), getHeight() );
	bdr_.paint( &r, ctx );
}

double Splitter::getPreferredHeight()
{
	return UIToolkit::getUIMetricsManager()->getDefaultHeightFor( UIMetricsManager::htSeparatorHeight ) * 3;
}

double Splitter::getPreferredWidth()
{
	return UIToolkit::getUIMetricsManager()->getDefaultHeightFor( UIMetricsManager::htSeparatorHeight ) * 3;
}


/**
*CVS Log info
*$Log$
*Revision 1.2  2004/08/07 02:49:09  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.3  2004/07/11 18:45:34  ddiego
*some toolbar fixes, plus some other minor glithches fixed
*
*Revision 1.1.2.2  2004/04/29 03:43:14  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 00:28:19  ddiego
*migration towards new directory structure
*
*Revision 1.13  2003/12/18 05:16:00  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.12.4.4  2003/12/02 05:50:06  ddiego
*added preliminary support for teh Action class. This will make it easier
*to hook up complimentary UI elements (such as a "copy" menu item, and a
*"copy" toolbar item) and have tehm respond to update and actions via a
*single source.
*Got rid of the old toolbar button and separator class. Merged in Marcellos
*new fixes for the Container and Splitter classes.
*Some misc fixes to the Toolbar, groups and checks now work correctly.
*
*Revision 1.12.4.3  2003/10/12 06:34:13  ddiego
*added some fixes to standard container layout algorithms - thisstill needs
*to be tested, but it looks like it may fix some outstanding issues
*with the layout logic
*
*Revision 1.12.4.2  2003/08/26 21:41:17  ddiego
*miscellanesous stuff, minor bugs
*
*Revision 1.12.4.1  2003/08/18 19:52:37  ddiego
*changed the Container from being a class you derive from to a separate
*intance that is created and assigned dynamically to any Control.
*
*Revision 1.12  2003/05/17 20:37:49  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.11.2.1  2003/03/12 03:13:21  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.11  2003/02/26 04:30:57  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.10.14.1  2003/01/08 00:20:01  marcelloptr
*mispellings and newlines at the end of all source files
*
*Revision 1.10  2002/05/09 03:10:46  ddiego
*merged over code from development branch devmain-0-5-1a into the main CVS trunk
*
*Revision 1.9.4.2  2002/04/27 15:52:51  ddiego
*Changed a bunch of files include and made it a bit faster and added better include
*guards in the common headers
*
*Revision 1.9.4.1  2002/04/08 20:55:31  zzack
*changed include style
*
*Revision 1.9  2002/01/24 01:46:50  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


