#ifndef _VCF_PAGEDCONTAINER_H__
#define _VCF_PAGEDCONTAINER_H__
//PagedContainer.h

/*
Copyright 2000-3004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCF  {





class PagedContainer : public StandardContainer {
public:

	void first() {
		if ( !pages_.empty() ) {
			//resort the pages_
			Control* control = controls_.front();

			while ( control != pages_.front() ) {
				Control* tmp = pages_.front();
				pages_.pop_front();
				pages_.push_back( tmp );
			}


			std::deque<Control*>::iterator it = pages_.begin();
			while ( it != pages_.end() ) {
				if ( *it != control ) {
					(*it)->setVisible( false );
				}
				it ++;
			}

			control->setVisible( true );
		}
	}

	void last() {
		if ( !pages_.empty() ) {
			Control* control = controls_.back();

			while ( control != pages_.front() ) {
				Control* tmp = pages_.front();
				pages_.pop_front();
				pages_.push_back( tmp );
			}

			std::deque<Control*>::iterator it = pages_.begin();
			while ( it != pages_.end() ) {
				if ( *it != control ) {
					(*it)->setVisible( false );
				}
				it ++;
			}

			control->setVisible( true );
		}
	}

	void next() {
		if ( !pages_.empty() ) {
			Control* control = pages_.front();
			pages_.pop_front();
			pages_.push_back( control );

			control = pages_.front();

			std::deque<Control*>::iterator it = pages_.begin();
			while ( it != pages_.end() ) {
				if ( *it != control ) {
					(*it)->setVisible( false );
				}
				it ++;
			}

			control->setVisible( true );
		}
	}

	virtual void resizeChildren( Control* control ) {
		//controlContainer_ is the control that this container is attached to
		Rect clientBounds = controlContainer_->getClientBounds();

		if ( clientBounds.isEmpty() ) {
			return; //nothing to do, so just exit the function
		}

		clientBounds.setRect( clientBounds.left_ + leftBorderWidth_,
								clientBounds.top_ + topBorderHeight_,
								clientBounds.right_ - rightBorderWidth_,
								clientBounds.bottom_ - bottomBorderHeight_ );



		bool controlJustAdded = false;
		if ( NULL != control ) {
			//we may have to position this separately - if it is the first time it
			//has been added then it will not be in the child control list
			//search for the control
			std::vector<Control*>::iterator found = std::find( controls_.begin(), controls_.end(), control );

			//if found equals the controls_.end, then control has not been added yet, and this is the first time
			//this control has been positioned for this container
			controlJustAdded = ( found == controls_.end() );
		}


		if ( controlJustAdded ) {
			control->setBounds( &clientBounds );
			pages_.push_back( control );
		}
		else {
			//note: we could have used the containers vector - this would be ever so slightly faster,
			//but this is a bit cleaner for the sake of an example.
			Enumerator<Control*>* children = AbstractContainer::getChildren();

			while ( children->hasMoreElements() ) {
				Control* child = children->nextElement();
				if ( child->getVisible() ) {
					child->setBounds( &clientBounds );
				}
			}
		}
	}

protected:
	std::deque<Control*> pages_;
};


};


#endif //_VCF_PAGEDCONTAINER_H__