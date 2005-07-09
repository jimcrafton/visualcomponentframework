#ifndef _VCF_COLUMNLAYOUTCONTAINER_H__
#define _VCF_COLUMNLAYOUTCONTAINER_H__
//ColumnLayoutContainer.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCF {


#define COLUMNLAYOUTCONTAINER_CLASSID		"3df1d3a5-d362-4d33-8b49-2ce693c72006"

class ColumnLayoutContainer : public StandardContainer {
public:
	ColumnLayoutContainer(): columnCount_(0) {
		UIMetricsManager* metricsMgr = UIToolkit::getUIMetricsManager();
		setBorderWidth( metricsMgr->getPreferredSpacingFor(UIMetricsManager::stWindowBorderDelta) );

	}

	ColumnLayoutContainer(Component* owner): StandardContainer(owner), columnCount_(0) {
		UIMetricsManager* metricsMgr = UIToolkit::getUIMetricsManager();
		setBorderWidth( metricsMgr->getPreferredSpacingFor(UIMetricsManager::stWindowBorderDelta) );

	}

	enum {
		ColumnWidthResize = -1
	};


	virtual void resizeChildren( Control* control ) {
		Rect clientBounds = controlContainer_->getClientBounds();

		if ( clientBounds.isEmpty() ) {
			return; //nothing to do, so just exit the function
		}

		clientBounds.setRect( clientBounds.left_ + leftBorderWidth_,
								clientBounds.top_ + topBorderHeight_,
								clientBounds.right_ - rightBorderWidth_,
								clientBounds.bottom_ - bottomBorderHeight_ );

		int col = 0;

		int width = clientBounds.getWidth();
		Rect controlBounds = clientBounds;

		std::vector<int> rows;
		double maxHeight = 0;
		std::vector<Control*>::iterator it = controls_.begin();

		int row = 0;
		rows.push_back( maxHeight );

		while ( it != controls_.end() ) {
			if ( (*it)->isIgnoredForLayout() ) {
				it ++;
				continue;
			}

			maxHeight = maxVal<>(maxHeight,(*it)->getHeight());

			if ( col >= columnCount_ ) {
				col = 0;
				row ++;
				rows.push_back( maxHeight );
			}
			else {
				rows[row] = maxHeight;
			}

			col ++;

			it ++;
		}


		row = 0;
		col = 0;
		it = controls_.begin();
		while ( it != controls_.end() ) {
			if ( (*it)->isIgnoredForLayout() ) {
				it ++;
				continue;
			}

			if ( ((columnCount_-1) == col) &&
					(ColumnWidthResize == columnWidths_[col]) ) {

				controlBounds.right_ = clientBounds.right_;
			}
			else{
				controlBounds.right_ = controlBounds.left_ + columnWidths_[col];
			}

			controlBounds.bottom_ = controlBounds.top_ + rows[row];

			(*it)->setBounds( &controlBounds );


			controlBounds.left_ = controlBounds.right_;
			controlBounds.left_ +=
					UIToolkit::getUIMetricsManager()->getPreferredSpacingFor(UIMetricsManager::stControlHorizontalSpacing);

			col ++;
			if ( col >= columnCount_ ) {
				controlBounds.top_ = controlBounds.bottom_;
				controlBounds.top_ +=
					UIToolkit::getUIMetricsManager()->getPreferredSpacingFor(UIMetricsManager::stControlVerticalSpacing);


				controlBounds.left_ = clientBounds.left_;
				controlBounds.right_ = clientBounds.left_;

				col = 0;
				row ++;
			}
			it ++;
		}
	}

	void setColumnCount( int val ) {
		columnCount_ = val;
		columnWidths_.resize(columnCount_,ColumnLayoutContainer::ColumnWidthResize);
	}

	void setColumnWidth( int col, int val ) {
		columnWidths_[col] = val;
	}


	int columnCount_ ;
	std::vector<int> columnWidths_;

};


};


/**
*CVS Log info
*$Log$
*Revision 1.3  2005/07/09 23:14:51  ddiego
*merging in changes from devmain-0-6-7 branch.
*
*Revision 1.2.4.2  2005/03/20 04:29:20  ddiego
*added ability to set image lists for list box control.
*
*Revision 1.2.4.1  2005/03/06 22:50:58  ddiego
*overhaul of RTTI macros. this includes changes to various examples to accommadate the new changes.
*
*Revision 1.2  2004/08/07 02:49:05  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.2  2004/04/29 03:43:12  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*/


#endif // _VCF_COLUMNLAYOUTCONTAINER_H__


