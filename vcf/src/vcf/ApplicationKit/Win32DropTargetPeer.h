#ifndef _VCF_WIN32DROPTARGETPEER_H__
#define _VCF_WIN32DROPTARGETPEER_H__
//Win32DropTargetPeer.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCFCOM {
	class DropTarget;
};

namespace VCF {



class Win32DropTargetPeer :	public DropTargetPeer, public Object  {
public:
	Win32DropTargetPeer();

	virtual ~Win32DropTargetPeer();

	virtual void registerTarget( Control* control );

	virtual void unregisterTarget( Control* control );

	virtual DropTarget* getDropTarget();

	virtual void setDropTarget( DropTarget* dropTarget );


	class COMDropTarget : public IDropTarget {


	public:
		COMDropTarget(Win32DropTargetPeer* owningPeer):owningPeer_(owningPeer){};

		~COMDropTarget(){};

		virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID iid, void** ppvObj) {
			if ( iid == IID_IUnknown ) {
				*ppvObj = (IUnknown*)(this);
				((IUnknown*)(*ppvObj))->AddRef();
				return S_OK;
			}
			else if ( iid == IID_IDropTarget ) {
				*ppvObj = (IDropTarget*)(this);
				((IUnknown*)(*ppvObj))->AddRef();
				return S_OK;
			}
			return E_NOINTERFACE;
		}

		virtual ULONG STDMETHODCALLTYPE AddRef(void) {

			return 1;
		}

		virtual ULONG STDMETHODCALLTYPE Release(void) {

			return 1;
		}

		STDMETHOD(DragEnter)( LPDATAOBJECT dataObject, DWORD keyState, POINTL point, LPDWORD effect ) {
			return owningPeer_->DragEnter( dataObject, keyState, point, effect );
		}

		STDMETHOD(DragOver)( DWORD keyState, POINTL point, LPDWORD effect ){
			return owningPeer_->DragOver( keyState, point, effect );
		}

		STDMETHOD(DragLeave)(void){
			return owningPeer_->DragLeave();
		}

		STDMETHOD(Drop)( LPDATAOBJECT dataObject, DWORD keyState, POINTL point, LPDWORD effect ){
			return owningPeer_->Drop( dataObject, keyState, point, effect );
		}


	private:
		Win32DropTargetPeer* owningPeer_;
	};

protected:

	friend class COMDropTarget;

	HRESULT DragEnter( LPDATAOBJECT dataObject, DWORD keyState, POINTL point, LPDWORD effect );
	HRESULT DragOver( DWORD keyState, POINTL point, LPDWORD effect );
	HRESULT DragLeave(void);
	HRESULT Drop( LPDATAOBJECT dataObject, DWORD keyState, POINTL point, LPDWORD effect );

private:
	VCF::DataObject* currentDataObj_;
	IDataObject* dataObject_;
	DropTarget* dropTarget_;
	COMDropTarget* comDropTarget_;

};


};


#endif // _VCF_WIN32DROPTARGETPEER_H__

/**
$Id$
*/
