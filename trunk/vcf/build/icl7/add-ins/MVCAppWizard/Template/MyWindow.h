#ifndef _$$ROOT$$WINDOW_H__
#define _$$ROOT$$WINDOW_H__


#define $$ROOT$$WINDOW_CLASSID		"$$WINDOWUUID$$"


/**
class $$Root$$Window documentation
*/
class $$Root$$Window  : public VCF::Window{
public: 
	BEGIN_CLASSINFO( $$Root$$Window, "$$Root$$Window", "VCF::Window", $$ROOT$$WINDOW_CLASSID )
	END_CLASSINFO( $$Root$$Window )

	$$Root$$Window();
	virtual ~$$Root$$Window();


protected:
	void onDocInitialized( VCF::Event* e ) ;
};




#endif //_$$ROOT$$WINDOW_H__



