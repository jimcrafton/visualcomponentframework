#ifndef _VCF_OSXCOMMONFONTDIALOG_H__
#define _VCF_OSXCOMMONFONTDIALOG_H__
/*
 Copyright 2000-3004 The VCF Project.
 Please see License.txt in the top level directory
 where you installed the VCF.
 */


namespace VCF {
	
	class Control;
	
	class OSXFontDialog : public CommonFontDialogPeer  {
	public:
		OSXFontDialog( Control* owner );
		
		virtual ~OSXFontDialog();
		
		virtual void setTitle( const String& title );
		
		virtual bool execute();
		
		virtual Font* getSelectedFont();
		
		virtual void setSelectedFont( Font* selectedFont );
		
	private:
		Font font_;
		Control* owner_;
	};
	
	
};

#endif //_VCF_OSXCOMMONFONTDIALOG_H__