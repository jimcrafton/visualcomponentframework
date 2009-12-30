//OpenGLKit.cpp
#include "vcf/OpenGLKit/OpenGLKit.h"
#include "vcf/FoundationKit/RTTIMacros.h"


namespace VCF {
_class_rtti_(OpenGLControl, "VCF::CustomControl", OPENGLCONTROL_CLASSID)
_class_rtti_end_
}


using namespace VCF;




void OpenGLKit::init( int argc, char** argv )
{
	REGISTER_CLASSINFO_EXTERNAL(OpenGLControl);
}

void OpenGLKit::terminate()
{

}