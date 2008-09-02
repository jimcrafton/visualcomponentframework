#ifndef _VCF_FLOWLAYOUTCONTAINTER_H__
#define _VCF_FLOWLAYOUTCONTAINTER_H__
//FlowLayoutContainter.h

/*
Copyright 2000-3004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCF {

	

enum FlowDirection {
	fdVertical = 0,
	fdHorizontal
};



static String FlowDirectionNames[] = { "fdVertical",
                                         "fdHorizontal" };



	class APPLICATIONKIT_API FlowLayoutContainter : public StandardContainer {
	public:

		FlowLayoutContainter():allowContentsToWrap_(true),direction_(fdHorizontal),childSpacer_(0) {
			childSpacer_ = UIToolkit::getUIMetricValue( UIMetricsManager::mtControlHorizontalSpacing );
		}

		bool allowContentsToWrap() {
			return allowContentsToWrap_;
		}

		void setAllowContentsToWrap( const bool& val ) {
			if ( val != allowContentsToWrap_ ) {
				allowContentsToWrap_ = val;
				resizeChildren(NULL);
			}
		}

		FlowDirection getFlowDirection() {
			return direction_;
		}

		void setFlowDirection( const FlowDirection& val ) {
			if ( val != direction_ ) {
				direction_ = val;
				resizeChildren(NULL);
			}
		}

		double getChildSpacer() {
			return childSpacer_;
		}

		void setChildSpacer( const double& val ) {
			if ( val != childSpacer_ ) {
				childSpacer_ = val;
				resizeChildren(NULL);
			}
		}

		virtual void resizeChildren( Control* control ) {
			if ( NULL == controlContainer_ ) {
				return;
			}

			Rect clientBounds = controlContainer_->getClientBounds();

			if ( clientBounds.isEmpty() ) {
				return; //nothing to do, so just exit the function
			}

			if ( controls_.empty() ) {
				return; //nothing to do, so just exit the function
			}

			clientBounds.setRect( clientBounds.left_ + leftBorderWidth_,
									clientBounds.top_ + topBorderHeight_,
									clientBounds.right_ - rightBorderWidth_,
									clientBounds.bottom_ - bottomBorderHeight_ );



			

			std::vector<Control*>::iterator it = controls_.begin();


			double maxChildWidth = 0;
			double maxChildHeight = 0;

			Rect childRect;


			while ( it != controls_.end() ) {
				Control* child = *it;
				
				if ( fdHorizontal == direction_ ) {
					maxChildHeight = minVal( clientBounds.getHeight(), maxVal(maxChildHeight,child->getHeight()) );
				}
				else {
					maxChildWidth = minVal( clientBounds.getWidth(), maxVal(maxChildWidth,child->getWidth()) );
				}				
				
				++it;
			}

			if ( fdHorizontal == direction_ ) {
				childRect = clientBounds;			
				childRect.bottom_ = childRect.top_ + maxChildHeight;
				childRect.right_ = childRect.left_ + 1;
			}
			else {
				childRect = clientBounds;			
				childRect.right_ = childRect.left_ + maxChildWidth;
				childRect.bottom_ = childRect.top_ + 1;
			}

			
			it = controls_.begin();
			while ( it != controls_.end() ) {
				Control* child = *it;
				Rect r = child->getBounds();

				if ( allowContentsToWrap_ && (it != controls_.begin()) ) {
					if ( fdHorizontal == direction_ ) {
						if ( (childRect.left_ + r.getWidth()) > clientBounds.right_ ) {
							childRect.left_ = clientBounds.left_;
							childRect.offset( 0, maxChildHeight + childSpacer_ );
						}
						
						childRect.right_ = childRect.left_ + r.getWidth();					
					}
					else {
						if ( (childRect.top_ + r.getHeight()) > clientBounds.bottom_ ) {
							childRect.top_ = clientBounds.top_;
							childRect.offset( maxChildWidth + childSpacer_, 0 );
						}
						
						childRect.bottom_ = childRect.top_ + r.getHeight();
					}
				}
				else {
					if ( fdHorizontal == direction_ ) {
						childRect.right_ = childRect.left_ + r.getWidth();
					}
					else {
						childRect.bottom_ = childRect.top_ + r.getHeight();
					}
				}


				child->setBounds( &childRect );
								
				
				if ( fdHorizontal == direction_ ) {
					childRect.offset( childRect.getWidth() + childSpacer_, 0 );
				}
				else {
					childRect.offset( 0, childRect.getHeight() + childSpacer_ );
				}

				++it;
			}
			
		}
	protected:
		bool allowContentsToWrap_;
		FlowDirection direction_;
		double childSpacer_;
	};


};


#endif //_VCF_FLOWLAYOUTCONTAINTER_H__