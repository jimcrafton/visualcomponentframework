#ifndef _VCF_WIN32HRESULT_H__
#define _VCF_WIN32HRESULT_H__
/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif



namespace VCF {


class hresult {
public:
	hresult():hr(0){}
	hresult( const HRESULT& rhs ): hr(rhs) {}


	hresult& operator= ( const HRESULT& rhs ) {
		hr = rhs;
		return *this;
	}

	operator HRESULT () const {
		return hr;
	}

	operator bool () const {
		return ok();
	}

	bool ok() const {
		return SUCCEEDED(hr) ? true : false;
	}

	operator std::string () const {
		return toString();
	}

	std::string toString() const {
		std::string result;

		char* tmp = NULL;
		::FormatMessage( FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
							NULL, hr, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (char*)&tmp, 0, NULL );

		if ( NULL != tmp ) {
			result = tmp;
		}

		::LocalFree( tmp );

		return result;
	}

	int code() const {
		return HRESULT_CODE(hr);
	}

	int facility() const {
		return HRESULT_FACILITY(hr);
	}


	bool operator==( const HRESULT& rhs ) const {
		return hr == rhs;
	}	

	bool operator!=( const HRESULT& rhs ) const {
		return hr != rhs;
	}

	bool operator > ( const HRESULT& rhs ) const {
		return hr > rhs;
	}

	bool operator < ( const HRESULT& rhs ) const {
		return hr < rhs;
	}

	bool operator >= ( const HRESULT& rhs ) const {
		return hr >= rhs;
	}

	bool operator <= ( const HRESULT& rhs ) const {
		return hr <= rhs;
	}
private:
	HRESULT hr;
};

};



#endif //_VCF_WIN32HRESULT_H__