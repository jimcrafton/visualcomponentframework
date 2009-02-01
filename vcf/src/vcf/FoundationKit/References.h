#ifndef _VCF_REFERENCES_H__
#define _VCF_REFERENCES_H__
//References.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


//References.h

class RefCount {

public:
    RefCount(){
		refCount_ = 1; // initialize to one 
                   // so the first call to removeRef
                   // deletes the object
	};

    virtual ~RefCount() {
		//TRACE("goodbye(%d)\n", crefs);
	};

    void addRef() {
		++this->refCount_;
	};

    void removeRef(){
		if (--refCount_ == 0){
			delete this;
		}
		else{

		}
	};

private:
	int refCount_;
};

//template <class T> itNew


#endif // _VCF_REFERENCES_H__

/**
$Id$
*/
