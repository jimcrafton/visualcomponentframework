#ifndef _VCF_SIZE_H__
#define _VCF_SIZE_H__
//Size.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCF {

/**
\class Size Size.h "vcf/GraphicsKit/Size.h"
*/
class GRAPHICSKIT_API Size : public Object {
public:

	Size( const double& w, const double& h ){
		this->init();
		width_ = w;
		height_ = h;
	}

	Size(){
		this->init();
	}

	virtual ~Size(){}

	virtual void init(){
		width_ = 0.0;
		height_ = 0.0;
	}

	void set( const double& width, const double& height ){
		width_ = width;
		height_ = height;
	}

	virtual String toString(){
		return Object::toString();
	}

	Size& operator= ( const Size& sz ) {
		width_ = sz.width_;
		height_ = sz.height_;
		return *this;
	}

	bool operator== ( const Size& sizeToCompare ) const {
		bool result = false;

		result = (this->width_ == sizeToCompare.width_) &&
			     (this->height_ == sizeToCompare.height_);

		return result;
	}

public:
	double width_;
    double height_;
};

}


#endif // _VCF_SIZE_H__

/**
$Id$
*/
