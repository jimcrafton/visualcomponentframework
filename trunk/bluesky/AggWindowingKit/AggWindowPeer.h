#ifndef _VCF_AGGWINDOWPEER_H__
#define _VCF_AGGWINDOWPEER_H__

/*
Copyright 2000-2006 The VCF Project, Orhun Birsoy.
Please see License.txt in the top level directory
where you installed the VCF.
*/

#include "vcf/ApplicationKit/WindowPeer.h"
#include "AggAbstractControl.h"

namespace VCF {

	class AggWindowPeer : public WindowPeer, public AggAbstractControl {
	public:
        AggWindowPeer( Control* component, Control* owner );

		virtual Rect getClientBounds();

		virtual void setClientBounds( Rect* bounds );

		virtual void close();

		virtual void setFrameStyle( const FrameStyleType& frameStyle );

		virtual void setFrameTopmost( const bool& isTopmost );

		virtual bool isMaximized();

		virtual void setMaximized( const bool maximised );

		virtual bool isMinimized();

		virtual void setMinimized( const bool& minimized );

		virtual void restore();

		virtual void setIconImage( Image* icon );

		virtual bool isActiveWindow();

		virtual void setBorderPath( Path* path ) ;

		////////////////////////////////////////////////////////
		virtual void create( Control* owningControl );

		virtual void destroyControl();

		virtual OSHandleID getHandleID();

		virtual String getText();

		virtual void setText( const String& text );

		virtual void setBounds( Rect* rect );

		virtual bool beginSetBounds( const uint32& numberOfChildren );

		virtual void endSetBounds();

		virtual Rect getBounds();

		virtual void setVisible( const bool& visible );

		virtual bool getVisible();

		virtual void setCursor( Cursor* cursor );

		virtual bool isFocused();

		virtual void setFocused();

		virtual bool isEnabled();

		virtual void setEnabled( const bool& enabled );

		virtual void setFont( Font* font );

		virtual void repaint( Rect* repaintRect, const bool& immediately );

		virtual void keepMouseEvents();

		virtual void releaseMouseEvents();

		virtual void translateToScreenCoords( Point* pt );

		virtual void translateFromScreenCoords( Point* pt );

		virtual void setBorder( Border* border );

		virtual void preChildPaint( GraphicsContext* graphicsContext, Control* child, Rect* childClipRect );

		virtual void postChildPaint( GraphicsContext* graphicsContext, Control* child, Rect* oldClipRect );

		/////////////////////////////////////////////////////////////////////
		
	protected:
        Rect clientBounds_;
		bool internalClose_;

		GraphicsContext* windowCtx_;
#ifdef VCF_WIN
#pragma pack(push,1)
		struct _WndProcThunk
		{
			DWORD	movInstr;
			DWORD	thisPtr;
			BYTE	jmpInstr;
			DWORD	relproc;
		};
#pragma pack(pop)

		class WndThunk {
		public:

			_WndProcThunk thunk;
			void init( WNDPROC proc, void* thisPtr ) {
				thunk.movInstr	= 0x042444c7;// mov dword ptr [esp+4]
				thunk.thisPtr	= (DWORD)thisPtr;
				thunk.jmpInstr	= 0xe9;		  // jmp WndProc
				thunk.relproc = 	
					(int)proc - ((int)this+sizeof(_WndProcThunk));
			}
		};

		WndThunk thunker_;
		HWND hwnd_;
		HDC memDC_;
		HBITMAP memBMP_;
		void* memDataPtr_;
		static LRESULT CALLBACK InitialWndProc( HWND, UINT, WPARAM, LPARAM );
		static LRESULT CALLBACK WndProc( HWND, UINT, WPARAM, LPARAM );
#endif
	};
};

#endif //_VCF_AGGWINDOWPEER_H__

/**
$Id$
*/

