#ifndef _$$ROOT$$VIEW_H__
#define _$$ROOT$$VIEW_H__



#define $$ROOT$$VIEW_CLASSID		"$$VIEWUUID$$"


/**
class $$Root$$View documentation
*/
class $$Root$$View : public VCF::Object, public VCF::AbstractView {
public: 
	BEGIN_CLASSINFO( $$Root$$View, "$$Root$$View", "VCF::Object", $$ROOT$$VIEW_CLASSID )
	END_CLASSINFO( $$Root$$View )
	$$Root$$View();

	virtual ~$$Root$$View();


	virtual void paintView( VCF::GraphicsContext* ctx );
protected:

};



#endif //_$$ROOT$$VIEW_H__



