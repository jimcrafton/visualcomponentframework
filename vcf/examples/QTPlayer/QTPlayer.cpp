//QTPlayer.cpp


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/ControlsKit.h"
#include "vcf/ApplicationKit/ModelViewKit.h"
#include "vcf/ApplicationKit/EtchedBorder.h"

/**
Include this file to access the various RTTI macros
for declaring RTTI information for your class(es)
*/
#include "vcf/FoundationKit/RTTIMacros.h"



using namespace VCF;



class QTPlayerApp : public SDIDocumentBasedApplication {
public:

	QTPlayerApp( int argc, char** argv ) : SDIDocumentBasedApplication(argc, argv) {
		
	}

	virtual bool initRunningApplication(){	
		
//		REGISTER_CLASSINFO_EXTERNAL( CircleModel );
//		REGISTER_CLASSINFO( DocViewBasicsWindow );

		bool result = SDIDocumentBasedApplication::initRunningApplication();
		
		return result;
	}

};


int main(int argc, char *argv[])
{
	return ApplicationKitMain<QTPlayerApp>(argc, argv);
}

