
#if     _MSC_VER > 1000
#pragma once
#endif

#ifndef _STATUSBARCONTROL_H__
#define _STATUSBARCONTROL_H__

namespace VCF {
class StatusBarControl : public CustomControl {
public:
	StatusBarControl();


	class Container : public StandardContainer {
	public:
		virtual void resizeChildren( Control* control );
	};

	void addStatusPane( const double& width=-1.0, const String& text=""  );

	void removeStatusPane( ulong32 index );

	void setStatusText( int index, const String& text );

	Control* getStatusPaneControl( ulong32 index );

	virtual void paint( GraphicsContext* ctx );
};
};

#endif //_STATUSBARCONTROL_H__



