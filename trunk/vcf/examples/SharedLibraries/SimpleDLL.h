#ifndef _SIMPLEDLL_H__
#define _SIMPLEDLL_H__


#ifdef _MSC_VER
#define SIMPLEDLL_API	__declspec(dllexport)
#else
#define SIMPLEDLL_API
#endif


class SIMPLEDLL_API HelloWorld {
public:
	 HelloWorld(){};
		virtual ~HelloWorld(){};
	void hello();

};

extern "C" {
	SIMPLEDLL_API int getAnInteger( int val1, double d );

}



#endif //_SIMPLEDLL_H__


