//ComponentInfo.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/ApplicationKit/ApplicationKit.h"


using namespace VCF;


ComponentInfo::ComponentInfo( const String& componentUUID, const String& author, const String& company,
			  const String& copyright, const String& additionalInfo,
			  const String& packageName, const String& packageUUID,
			  Image* componentImage )
{
	author_ = author;
	copyright_ = copyright;
	company_ = company;
	additionalInfo_ = additionalInfo;
	componentUUID_ = componentUUID;
	componentImage_ = componentImage;
	packageName_ = packageName;
	packageUUID_ = packageUUID;

	reqNamespacesContainer_.initContainer( requiredNamespaces_ );
	reqHeadersContainer_.initContainer( requiredHeaders_ );
}

ComponentInfo::~ComponentInfo()
{
	if ( NULL != componentImage_ ) {
		delete componentImage_;
	}
}

Enumerator<String>* ComponentInfo::getRequiredHeaders()
{
	return reqHeadersContainer_.getEnumerator();
}

Enumerator<String>* ComponentInfo::getRequiredNamespaces()
{
	return reqNamespacesContainer_.getEnumerator();
}

void ComponentInfo::addHeader( const String& header )
{
	requiredHeaders_.push_back( header );
}

void ComponentInfo::removeHeader( const String& header )
{
	std::vector<String>::iterator found = std::find( requiredHeaders_.begin(), requiredHeaders_.end(), header );
	if ( found != requiredHeaders_.end() ) {
		requiredHeaders_.erase( found );
	}
}

void ComponentInfo::removeAllHeaders()
{
	requiredHeaders_.clear();
}

void ComponentInfo::addNamespace( const String& aNamespace )
{
	requiredNamespaces_.push_back( aNamespace );
}

void ComponentInfo::removeNamespace( const String& aNamespace )
{
	std::vector<String>::iterator found = std::find( requiredNamespaces_.begin(), requiredNamespaces_.end(), aNamespace );
	if ( found != requiredNamespaces_.end() ) {
		requiredNamespaces_.erase( found );
	}
}

void ComponentInfo::removeAllNamespaces()
{
	requiredNamespaces_.clear();
}


/**
*CVS Log info
*$Log$
*Revision 1.2  2004/08/07 02:49:06  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.2  2004/04/29 03:43:13  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 00:28:15  ddiego
*migration towards new directory structure
*
*Revision 1.8  2003/08/09 02:56:45  ddiego
*merge over from the devmain-0-6-1 branch
*Changes
*Features:
*-Added additional implementation to better support the MVC architecture in
*the VCF
*
*-Added a Document/View architecure that is similar to MFC's or NextSteps's
*Doc/View architectures
*
*-Integrated the Anti Grain Graphics library into the GraphicsKit. There is
*now basic support for it in terms of drawing vector shapes
*(fills and strokes). Image support will come in the next release
*
*-Added several documented graphics tutorials
*
*Bugfixes:
*
*[ 775744 ] wrong buttons on a dialog
*[ 585239 ] Painting weirdness in a modal dialog ?
*[ 585238 ] Modal dialog which makes a modal Dialog
*[ 509004 ] Opening a modal Dialog causes flicker
*[ 524878 ] onDropped not called for MLTcontrol
*
*Plus an issue with some focus and getting the right popup window to activate
*has also been fixed
*
*Revision 1.7.2.1  2003/05/25 19:07:15  ddiego
*fixed bug [ 524878 ] onDropped not called for MLTcontrol. This
*was due to errors in the drag-drop implementation for WIn32 and is
*now fixed.
*Also cleaned up the drag-drop implementation and moved/deleted a number of
*irrelevant files for COM support. The vcf/include/com and vcf/src/COM
*directories are now gotten rid of.
*
*Revision 1.7  2003/05/17 20:37:47  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.6.2.2  2003/03/23 03:24:00  marcelloptr
*3 empty lines at the end of the files
*
*Revision 1.6.2.1  2003/03/12 03:13:03  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.6  2003/02/26 04:30:55  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.5.14.1  2003/01/08 00:19:59  marcelloptr
*mispellings and newlines at the end of all source files
*
*Revision 1.5  2002/05/09 03:10:45  ddiego
*merged over code from development branch devmain-0-5-1a into the main CVS trunk
*
*Revision 1.4.4.1  2002/04/08 20:55:31  zzack
*changed include style
*
*Revision 1.4  2002/01/24 01:46:50  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


