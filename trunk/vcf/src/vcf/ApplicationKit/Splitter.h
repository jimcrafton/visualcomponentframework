#ifndef _VCF_SPLITTER_H__
#define _VCF_SPLITTER_H__
//Splitter.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


#define SPLITTER_CLASSID		"e06c4170-04d7-4ba5-84ff-d1718d7b2a9d"


namespace VCF  {

/**
\class Splitter Splitter.h "vcf/ApplicationKit/Splitter.h"
*Class Splitter documentation
*/
class APPLICATIONKIT_API Splitter : public CustomControl {
public:

	Splitter( const AlignmentType& alignment = AlignLeft );
	virtual ~Splitter();

	void init();

	virtual void mouseDown( MouseEvent* e );

	virtual void mouseMove( MouseEvent* e );

	virtual void mouseUp( MouseEvent* e );

	virtual void mouseDblClick( MouseEvent* e );

	virtual void paint( GraphicsContext* ctx );

	bool getDblClickEnabled() {
		return dblClickEnabled_;
	}
	void setDblClickEnabled( const bool& dblClickEnabled ) {
		dblClickEnabled_ = dblClickEnabled;
	}

	void setAlignment( const AlignmentType& alignment );

	void setMinimumWidth( const double& _minimumWidth );
	double getMinimumWidth();

	virtual double getPreferredHeight();
	virtual double getPreferredWidth();

protected:
	/**
	this is the function doing the real job
	*/
	void updateAttachedControl( Point& pt, const bool& shiftAll = false );

	/**
	this is the function doing the real job when double clicking with the mouse
	*/
	void updateAttachedControlJump( Point& pt, const bool& shiftAll = false );

protected:
	Control* attachedControl_;
	Point dragPoint_;
	Light3DBorder bdr_;
	Control* attachedControlAlt_;
	Control* outmostControl_;
	double deltaRestore_;
	double deltaRestoreAlt_;
	double minimumWidth_;
	bool dblClickEnabled_;

private:
};


}; //end of namespace VCF


#endif // _VCF_SPLITTER_H__

/**
$Id$
*/
