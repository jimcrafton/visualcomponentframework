#ifndef _VCF_FLOWLAYOUTCONTAINTER_H__
#define _VCF_FLOWLAYOUTCONTAINTER_H__
//FlowLayoutContainer.h

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

enum HorizontalFlowAlignment {
	hfLeftAlign,
	hfCenterAlign,
	hfRightAlign
};


enum VerticalFlowAlignment {
	vfTopAlign,
	vfCenterAlign,
	vfBottomAlign
};

static String FlowDirectionNames[] = { "fdVertical",
                                         "fdHorizontal" };

static String HorizontalFlowAlignmentNames[] = { "hfLeftAlign",
													"hfCenterAlign",
													 "hfRightAlign" };

static String VerticalFlowAlignmentNames[] = { "vfTopAlign",
													"vfCenterAlign",
													 "vfBottomAlign" };



	class APPLICATIONKIT_API FlowLayoutContainer : public StandardContainer {
	public:

		FlowLayoutContainer():allowContentsToWrap_(true),keepChildDimensions_(false),direction_(fdHorizontal),childSpacer_(0),horzAlign_(hfLeftAlign),vertAlign_(vfTopAlign) {
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

		bool getKeepChildDimensions() {
			return keepChildDimensions_;
		}

		void setKeepChildDimensions( const bool& val ) {
			if ( val != keepChildDimensions_ ) {
				keepChildDimensions_ = val;
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

		HorizontalFlowAlignment getHorizontalAlign() {
			return horzAlign_;		
		}

		void setHorizontalAlign( const HorizontalFlowAlignment& val ) {
			if ( val != horzAlign_ ) {
				horzAlign_ = val;
				resizeChildren(NULL);
			}
		}

		VerticalFlowAlignment getVerticalAlign() {
			return vertAlign_;		
		}

		void setVerticalAlign( const VerticalFlowAlignment& val ) {
			if ( val != vertAlign_ ) {
				vertAlign_ = val;
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

			std::vector<double> hoffsets(1);
			std::vector<double> voffsets(1);

			hoffsets[0] = 0;
			voffsets[0] = 0;

			while ( it != controls_.end() ) {
				Control* child = *it;
				Rect r = child->getBounds();
				
				if ( fdHorizontal == direction_ ) {

					maxChildHeight = minVal( clientBounds.getHeight(), maxVal(maxChildHeight,r.getHeight()) );

					if ( horzAlign_ == hfCenterAlign ) {						
						if ( allowContentsToWrap_ ) {							
							if ( hoffsets.back() > clientBounds.getWidth() ) {
								hoffsets.push_back( minVal(1.0,r.getWidth() + childSpacer_) );								
							}
							else {
								hoffsets.back() += r.getWidth() + childSpacer_;
							}
						}
						else {
							hoffsets.back() += r.getWidth() + childSpacer_;
						}						
					}
				}
				else {
					maxChildWidth = minVal( clientBounds.getWidth(), maxVal(maxChildWidth,r.getWidth()) );

					if ( vertAlign_ == vfCenterAlign ) {						
						if ( allowContentsToWrap_ ) {							
							if ( voffsets.back() > clientBounds.getHeight() ) {
								voffsets.push_back( minVal(1.0,r.getHeight() + childSpacer_) );								
							}
							else {
								voffsets.back() += r.getHeight() + childSpacer_;
							}
						}
						else {
							voffsets.back() += r.getHeight() + childSpacer_;
						}						
					}
				}				
				

				
				++it;
			}

			childRect = clientBounds;
			if ( fdHorizontal == direction_ ) {
				switch ( vertAlign_ ) {
					case vfTopAlign : {
						//nothing to do here
					}
					break;

					case vfCenterAlign : {
						childRect.top_ = clientBounds.top_ + (clientBounds.getHeight()/2.0) - (maxChildHeight/2.0);
					}
					break;

					case vfBottomAlign : {
						childRect.top_ = childRect.bottom_ - 1;
					}
					break;
				}

				childRect.bottom_ = childRect.top_ + maxChildHeight;				

				switch ( horzAlign_ ) {
					case hfLeftAlign : {
						childRect.right_ = childRect.left_ + 1;
					}
					break;

					case hfCenterAlign : {						
						childRect.left_ = clientBounds.left_ + (clientBounds.getWidth()/2.0) - (hoffsets[0]/2.0);
						childRect.right_ = childRect.left_ + 1;
					}
					break;

					case hfRightAlign : {						
						childRect.left_ = childRect.right_ - 1;
					}
					break;
				}
				
			}
			else {

				childRect = clientBounds;

				switch ( horzAlign_ ) {
					case hfLeftAlign : {
						//nothing to do here
					}
					break;

					case hfCenterAlign : {
						childRect.left_ = clientBounds.left_  + (clientBounds.getWidth()/2.0) - (maxChildWidth/2.0);
					}
					break;

					case hfRightAlign : {
						childRect.left_ = childRect.right_ - 1;
					}
					break;
				}

				childRect.right_ = childRect.left_ + maxChildWidth;

				

				switch ( vertAlign_ ) {
					case vfTopAlign : {
						childRect.bottom_ = childRect.top_ + 1;
					}
					break;

					case vfCenterAlign : {						
						childRect.top_ = clientBounds.top_ + (clientBounds.getHeight()/2.0) - (voffsets[0]/2.0);
						childRect.bottom_ = childRect.top_ + 1;
					}
					break;

					case vfBottomAlign : {						
						childRect.top_ = childRect.bottom_ - 1;
					}
					break;
				}
			}

			
			it = controls_.begin();
			while ( it != controls_.end() ) {
				Control* child = *it;
				Rect r = child->getBounds();
				Rect adjChildRect = childRect;

				if ( allowContentsToWrap_ && (it != controls_.begin()) ) {
					if ( fdHorizontal == direction_ ) {
						switch ( horzAlign_ ) {
							case hfLeftAlign : {
								if ( (childRect.left_ + r.getWidth()) > clientBounds.right_ ) {
									childRect.left_ = clientBounds.left_;
									childRect.offset( 0, maxChildHeight + childSpacer_ );
								}
								
								childRect.right_ = childRect.left_ + r.getWidth();
							}
							break;

							case hfCenterAlign : {
								if ( (childRect.left_ + r.getWidth()) > clientBounds.right_ ) {
									hoffsets.erase( hoffsets.begin() );

									childRect.left_ = (clientBounds.getWidth()/2.0) - (hoffsets[0]/2.0);

									childRect.offset( 0, maxChildHeight + childSpacer_ );
								}
								childRect.right_ = childRect.left_ + r.getWidth();								
							}
							break;

							case hfRightAlign : {
								if ( (childRect.right_ - r.getWidth()) < clientBounds.left_ ) {
									childRect.right_ = clientBounds.right_;
									childRect.offset( 0, maxChildHeight + childSpacer_ );
								}
								childRect.left_ = childRect.right_ - r.getWidth();
							}
							break;
						}

						adjChildRect = childRect;

						if ( keepChildDimensions_ ) {
							adjChildRect.bottom_ = adjChildRect.top_ + r.getHeight();
						}
					}
					else {
						switch ( vertAlign_ ) {
							case vfTopAlign : {
								if ( (childRect.top_ + r.getHeight()) > clientBounds.bottom_ ) {
									childRect.top_ = clientBounds.top_;
									childRect.offset( maxChildWidth + childSpacer_, 0 );
								}
								
								childRect.bottom_ = childRect.top_ + r.getHeight();
							}
							break;

							case vfCenterAlign : {
								if ( (childRect.top_ + r.getHeight()) > clientBounds.bottom_ ) {
									voffsets.erase( voffsets.begin() );

									childRect.top_ = (clientBounds.getHeight()/2.0) - (voffsets[0]/2.0);

									childRect.offset( maxChildWidth + childSpacer_, 0 );
								}
								childRect.bottom_ = childRect.top_ + r.getHeight();								
							}
							break;

							case vfBottomAlign : {
								if ( (childRect.bottom_ - r.getHeight()) < clientBounds.top_ ) {
									childRect.bottom_ = clientBounds.bottom_;
									childRect.offset( maxChildWidth + childSpacer_, 0 );
								}
								childRect.top_ = childRect.bottom_ - r.getHeight();
							}
							break;
						}

						adjChildRect = childRect;
						if ( keepChildDimensions_ ) {
							adjChildRect.right_ = adjChildRect.left_ + r.getWidth();
						}
					}
				}
				else {
					if ( fdHorizontal == direction_ ) {
						switch ( horzAlign_ ) {
							case hfLeftAlign : case hfCenterAlign : {
								childRect.right_ = childRect.left_ + r.getWidth();
							}
							break;

							case hfRightAlign : {
								childRect.left_ = childRect.right_ - r.getWidth();
							}
							break;
						}

						adjChildRect = childRect;
						if ( keepChildDimensions_ ) {
							adjChildRect.bottom_ = adjChildRect.top_ + r.getHeight();
						}
					}
					else {
						switch ( vertAlign_ ) {
							case vfTopAlign : case vfCenterAlign : {
								childRect.bottom_ = childRect.top_ + r.getHeight();
							}
							break;

							case vfBottomAlign : {
								childRect.top_ = childRect.bottom_ - r.getHeight();
							}
							break;
						}

						adjChildRect = childRect;

						switch ( horzAlign_ ) {
							case hfLeftAlign : {
								if ( keepChildDimensions_ ) {
									adjChildRect.right_ = childRect.left_ + r.getWidth();
								}								
							}
							break;

							case hfCenterAlign : {
								if ( keepChildDimensions_ ) {
									adjChildRect.left_ = (clientBounds.left_ + 
										(clientBounds.getWidth()/2.0)) - (r.getWidth()/2.0);
									adjChildRect.right_ = adjChildRect.left_ + r.getWidth();								
								}
							}
							break;

							case hfRightAlign : {
								if ( keepChildDimensions_ ) {
									adjChildRect.left_ = childRect.right_ - r.getWidth();
								}
							}
							break;
						}
					}
				}


				child->setBounds( &adjChildRect );
								
				
				if ( fdHorizontal == direction_ ) {					

					switch ( horzAlign_ ) {
						case hfLeftAlign : case hfCenterAlign : {
							childRect.offset( childRect.getWidth() + childSpacer_, 0 );
						}
						break;

						//case hfCenterAlign : {

						//}
						//break;

						case hfRightAlign : {
							childRect.offset( -(childRect.getWidth() + childSpacer_), 0 );
						}
						break;
					}
				}
				else {
					switch ( vertAlign_ ) {
						case vfTopAlign : case vfCenterAlign : {
							childRect.offset( 0, childRect.getHeight() + childSpacer_ );
						}
						break;

						case vfBottomAlign : {
							childRect.offset( 0, -(childRect.getHeight() + childSpacer_) );
						}
						break;
					}
				}

				

				
				++it;
			}
			
		}
	protected:
		bool allowContentsToWrap_;
		bool keepChildDimensions_;
		FlowDirection direction_;
		double childSpacer_;
		HorizontalFlowAlignment horzAlign_;
		VerticalFlowAlignment vertAlign_;
	};


};


#endif //_VCF_FLOWLAYOUTCONTAINTER_H__
