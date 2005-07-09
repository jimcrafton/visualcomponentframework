
#ifndef _HORIZONTALLAYOUTCONTAINER_H__
#define _HORIZONTALLAYOUTCONTAINER_H__


/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/



#if _MSC_VER > 1000
#   pragma once
#endif





namespace VCF {

#define HORIZONTALLAYOUTCONTAINER_CLASSID		"11aab5e2-36d2-47c7-9391-c40b185d6b9e"

class HorizontalLayoutContainer : public StandardContainer {
public:

	HorizontalLayoutContainer() :
		maximizeLastRow_(false),
		equalizeHeights_(false),
		averageHeights_(false),
		keepControlsWidth_(false) {

		setBorderWidth( UIToolkit::getUIMetricsManager()->getPreferredSpacingFor(UIMetricsManager::stContainerBorderDelta) );

		setNumberOfColumns(2);

		setColumnWidth( 0, 100 );

		setColumnWidth( 1, 100 );

		setColumnTweenWidth( 0, UIToolkit::getUIMetricsManager()->getPreferredSpacingFor(UIMetricsManager::stControlHorizontalSpacing) );


		setMaxRowHeight( UIToolkit::getUIMetricsManager()->getDefaultHeightFor( UIMetricsManager::htLabelHeight ) );

		setRowSpacerHeight( UIToolkit::getUIMetricsManager()->getPreferredSpacingFor(UIMetricsManager::stControlVerticalSpacing) );
	}

	HorizontalLayoutContainer( Component* owner ):
		StandardContainer(owner),
		maximizeLastRow_(false)
	{

		setBorderWidth( UIToolkit::getUIMetricsManager()->getPreferredSpacingFor(UIMetricsManager::stContainerBorderDelta) );

		setNumberOfColumns(2);

		setColumnWidth( 0, 100 );

		setColumnWidth( 1, 100 );

		setColumnTweenWidth( 0, UIToolkit::getUIMetricsManager()->getPreferredSpacingFor(UIMetricsManager::stControlHorizontalSpacing) );


		setMaxRowHeight( UIToolkit::getUIMetricsManager()->getDefaultHeightFor( UIMetricsManager::htLabelHeight ) );

		setRowSpacerHeight( UIToolkit::getUIMetricsManager()->getPreferredSpacingFor(UIMetricsManager::stControlVerticalSpacing) );

	}


	void setNumberOfColumns( int numColumns ) {
		columns_.clear();
		columnTweens_.clear();

		columns_.resize( numColumns, 0.0 );

		columnTweens_.resize( numColumns-1, 0.0 );
	}

	int getNumberOfColumns() const {
		return columns_.size();
	}

	void setColumnWidth( int index, double width ) {
		columns_[index] = width;
	}

	int getColumnWidth( int index ) const {
		return columns_[index];
	}

	void setColumnTweenWidth( int index, double width ) {
		columnTweens_[index] = width;
	}

	int getColumnTweenWidth( int index ) const {
		return columnTweens_[index];
	}

	void setMaxRowHeight( double val ) {
		maxRowHeight_ = val;
	}

	/**
	sets if we want all the row heights to be the same
	as the hightest one. The default is false;
	This flag excludes setEqualizeHeights().
	*/
	void setEqualizeHeights( bool equalize ) {
		equalizeHeights_ = equalize;
	}
	bool getEqualizeHeights() {
		return equalizeHeights_;
	}

	/**
	sets if we want all the row heights to be the same
	as the average height that fills the parent control. The default is false;
	*/
	void setAverageHeights( bool average ) {
		averageHeights_ = average;
	}
	bool getAverageHeights() {
		return averageHeights_;
	}

	/**
	sets if we want the controls to keep their width or,
	as it is by default, resizing their width to the one of
	the column where they are located.
	*/
	void setKeepControlsWidth( bool keep ) {
		keepControlsWidth_ = keep;
	}
	bool getKeepControlsWidth() {
		return keepControlsWidth_;
	}

	double getMinimumVisibleHeight() {

		double result = 0.0;
		std::vector<Control*>::iterator it = controls_.begin();
		int colCount = columns_.size();

		int col = 0;

		result = maxRowHeight_;

		while ( it != controls_.end() ) {
			Control* control = *it;
			col ++;
			if ( col >= colCount ) {
				col = 0;
				result += (maxRowHeight_ + rowSpacerHeight_);
			}
			it ++;
		}

		return result;
	}


	virtual void resizeChildren( Control* control ) {
		VCF::Rect clientBounds = controlContainer_->getClientBounds();

		if ( clientBounds.isEmpty() ) {
			return; //nothing to do, so just exit the function
		}

		clientBounds.setRect( clientBounds.left_ + leftBorderWidth_,
			clientBounds.top_ + topBorderHeight_,
			clientBounds.right_ - rightBorderWidth_,
			clientBounds.bottom_ - bottomBorderHeight_ );


		std::vector<Control*>::iterator it = controls_.begin();

		int colCount = columns_.size();
		int tweenCount = columnTweens_.size();

		int col = 0;
		int tween = 0;
		VCF::Rect cell = clientBounds;
		cell.right_ = cell.left_ + columns_[col];

		//cell.bottom_ = cell.top_ + maxRowHeight_;



		

		int rowCount = (controls_.size() / columns_.size()) + (controls_.size() % columns_.size());
		int row = 0;

		//calculate row heights so that things don't get "scrunched" together
		std::vector<double> rowHeights(rowCount);
		double h = 0;//maxRowHeight_;
		while ( it != controls_.end() ) {
			Control* control = *it;

			if ( control->isIgnoredForLayout() ) {
				it ++;
				continue;
			}

			h = maxVal<>( h, maxVal<>( control->getHeight(), control->getPreferredHeight() ) );

			if ( h > maxRowHeight_ ) {
				maxRowHeight_ = h;
			}
			col ++;

 			// this stays here: we do not always have all the controls in all the columns.
			rowHeights[row] = h;

			if ( col >= colCount ) {
				col = 0;

				h = 0;
				row ++;
			}

			++ it;
		}

		if ( equalizeHeights_ ) {
			row = 0;
			std::vector<double>::iterator it = rowHeights.begin();
			while ( it != rowHeights.end() ) {
				rowHeights[row] = maxRowHeight_;
				row ++;
				++ it;
			}
		}
		else if ( averageHeights_ && ( 0 < row ) ) {
			maxRowHeight_ = ( clientBounds.getHeight() - (rowSpacerHeight_*(row-1)) ) / row;
			row = 0;
			std::vector<double>::iterator it = rowHeights.begin();
			while ( it != rowHeights.end() ) {
				rowHeights[row] = maxRowHeight_;
				row ++;
				++ it;
			}
		}

		row = 0;
		col = 0;

		it = controls_.begin();

		while ( it != controls_.end() ) {

			Control* control = *it;


			if ( control->isIgnoredForLayout() ) {
				it ++;
				continue;
			}

			if ( !keepControlsWidth_ &&  ( col == (colCount-1) ) ) {

				cell.right_ = clientBounds.right_;
			}

			cell.bottom_ = cell.top_ + rowHeights[row];

			if ( (row == (rowCount-1)) && maximizeLastRow_ ) {
				cell.bottom_ = clientBounds.bottom_;
			}

			control->setBounds( &cell );


			col ++;



			if ( col >= colCount ) {
				col = 0;
				tween = 0;

				cell.offset( 0, rowHeights[row] + rowSpacerHeight_ );

				cell.left_ = clientBounds.left_;

				cell.right_ = cell.left_ + columns_[col];

				row ++;
			}
			else {
				cell.offset( cell.getWidth() + columnTweens_[tween], 0 );
				tween ++;
			}


			++ it;
		}
	}


	bool getMaximizeLastRow() {
		return maximizeLastRow_;
	}

	void setMaximizeLastRow( bool val ) {
		maximizeLastRow_ = val;
	}

	void setRowSpacerHeight( double val ) {
		rowSpacerHeight_ = val;
	}

	std::vector<double> columns_;
	std::vector<double> columnTweens_;

	double maxRowHeight_;
	double rowSpacerHeight_;
	bool maximizeLastRow_;
	bool equalizeHeights_;
	bool averageHeights_;
	bool keepControlsWidth_;
};


}; // namespace VCF







/**
*CVS Log info
*$Log$
*Revision 1.4  2005/07/09 23:14:53  ddiego
*merging in changes from devmain-0-6-7 branch.
*
*Revision 1.3  2005/02/26 14:44:03  ddiego
*checked in changes from dev for horz container.
*

*Revision 1.2.2.8  2005/06/26 01:34:37  marcelloptr
*[bugfix 1227549] HorizontalLayoutContainer set the heights in the wrong rows.
*AbstractContainer::add() needs to resizeChildren *after* the child control has been added.
*
*Revision 1.2.2.6  2005/05/22 04:05:43  ddiego
*more text edit fixes.
*
*Revision 1.2.2.5  2005/04/25 00:11:57  ddiego
*added more advanced text support. fixed some memory leaks. fixed some other miscellaneous things as well.
*
*Revision 1.2.2.4  2005/04/20 02:26:00  ddiego
*fixes for single line text and formatting problems in text window creation.
*
*Revision 1.2.2.3  2005/03/20 04:29:21  ddiego
*added ability to set image lists for list box control.
*
*Revision 1.2.2.2  2005/03/06 22:50:59  ddiego
*overhaul of RTTI macros. this includes changes to various examples to accommadate the new changes.
*
*Revision 1.2.2.1  2005/02/10 20:59:37  ddiego
*fixed a layout error in horz layout container
*
*Revision 1.2  2004/12/01 04:31:21  ddiego
*merged over devmain-0-6-6 code. Marcello did a kick ass job
*of fixing a nasty bug (1074768VCF application slows down modal dialogs.)
*that he found. Many, many thanks for this Marcello.
*
*Revision 1.1.2.3  2004/11/17 04:52:48  ddiego
*added some minor fixes to win32 resource loading, and added 2 new examples that demonstrate basic resource loading and basic usage of dialogs.
*
*Revision 1.1.2.2  2004/09/07 03:57:04  ddiego
*misc tree control update
*
*Revision 1.1.2.1  2004/08/31 04:12:12  ddiego
*cleaned up the GraphicsContext class - made more pervasive use
*of transformation matrix. Added common print dialog class. Fleshed out
*printing example more.
*
*/



#endif //_HORIZONTALLAYOUTCONTAINER_H__






