#ifndef _VCF_COMMONDIALOGPEER_H__
#define _VCF_COMMONDIALOGPEER_H__
//CommonDialogPeer.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCF {

class Color;

class Font;

/**
\class CommonDialogPeer CommonDialogPeer.h "vcf/ApplicationKit/CommonDialogPeer.h"
*/
class APPLICATIONKIT_API CommonDialogPeer : public Interface{
public:
	virtual ~CommonDialogPeer(){};

	virtual void setTitle( const String& title ) = 0;

	virtual bool execute() = 0;
};


/**
\class CommonFileDialog CommonDialogPeer.h "vcf/ApplicationKit/CommonDialogPeer.h"
*/
class APPLICATIONKIT_API CommonFileDialogPeer : public CommonDialogPeer{
public:
	virtual ~CommonFileDialogPeer(){};

	virtual void addFilter( const String & description, const String & extension ) = 0;

	virtual void setDirectory( const String & directory ) = 0;

	virtual void setFileName( const String & filename ) = 0;

	virtual String getFileName() = 0;

	virtual String getDirectory() = 0;

	virtual String getFileExtension() = 0;

	virtual uint32 getSelectedFileCount() = 0;

	virtual Enumerator<String>* getSelectedFiles() = 0;

	virtual void setAllowsMultiSelect( const bool& allowsMultiSelect ) = 0;

	virtual String getSelectedFilter() = 0;

	virtual void setSelectedFilter( const String& selectedFilter ) = 0;

	virtual void setFileMustExist( const bool& fileMustExist ) = 0;
};

/**
\class CommonFolderBrowseDialogPeer CommonDialogPeer.h "vcf/ApplicationKit/CommonDialogPeer.h"
*/
class APPLICATIONKIT_API CommonFolderBrowseDialogPeer : public CommonDialogPeer{
public:
	virtual ~CommonFolderBrowseDialogPeer(){};

	virtual void setDirectory( const String & directory ) = 0;

	virtual String getDirectory() = 0;

};

/**
\class CommonColorDialogPeer CommonDialogPeer.h "vcf/ApplicationKit/CommonDialogPeer.h"
*/
class APPLICATIONKIT_API CommonColorDialogPeer : public CommonDialogPeer {
public:
	virtual ~CommonColorDialogPeer(){};

	virtual Color* getSelectedColor() = 0;

	virtual void setSelectedColor( Color* selectedColor ) = 0;

};


/**
\class CommonPrintDialogPeer CommonDialogPeer.h "vcf/ApplicationKit/CommonDialogPeer.h"
*/
class APPLICATIONKIT_API CommonPrintDialogPeer : public CommonDialogPeer {
public:
	virtual ~CommonPrintDialogPeer(){};
	
	virtual void setPrintInfo( PrintInfoHandle info ) = 0;
	
	virtual PrintInfoHandle getPrintInfo() = 0;

	virtual void setNumberOfCopies( const uint32& val ) = 0;
	virtual uint32 getNumberOfCopies() = 0;
	
	virtual void setStartPage( const uint32& val ) = 0;
	virtual uint32 getStartPage() = 0;

	virtual void setEndPage( const uint32& val ) = 0;
	virtual uint32 getEndPage() = 0;

	virtual void setPrintJobType( PrintSession::PrintJob val ) = 0;
	virtual PrintSession::PrintJob getPrintJobType() = 0;
};


/**
\class CommonFontDialogPeer CommonDialogPeer.h "vcf/ApplicationKit/CommonDialogPeer.h"
*/
class APPLICATIONKIT_API CommonFontDialogPeer : public CommonDialogPeer {
public:
	virtual ~CommonFontDialogPeer(){};

	virtual Font* getSelectedFont() = 0;

	virtual void setSelectedFont( Font* selectedFont ) = 0;
};

};


#endif // _VCF_COMMONDIALOGPEER_H__

/**
$Id$
*/
