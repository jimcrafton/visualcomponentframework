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


/**
*CVS Log info
*$Log$
*Revision 1.2  2004/08/07 02:49:10  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.2  2004/04/29 03:43:15  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 00:28:20  ddiego
*migration towards new directory structure
*
*Revision 1.10.2.1  2004/04/26 21:58:43  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.10  2004/04/03 15:48:42  ddiego
*Merged over code from the 0-6-3 branch.
*
*Revision 1.9.2.1  2004/03/26 01:38:10  ddiego
*added Marcello's suggestion for the additional VCF_ASSERT
*macro. So we now have one which takes a single parameter, and another
*which takes 2 parameters, the assert condition, and a message.
*
*Revision 1.9  2003/12/18 05:15:58  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.8.2.2  2003/09/12 00:09:33  ddiego
*added better tabbing behaviour - fixed an earlier bug.
*Code is easier to understand and it simplified the implementation
*a bit as well
*Moved around the RTTI definitions for various Appkit classes to a
*single inline and stripped them from the various class headers
*
*Revision 1.8.2.1  2003/09/02 02:11:14  ddiego
*fixed some glitches in drag drop. also cleaned up the drag drop event
*classes. Began some fixes to the html browser implementation on Win32
*
*Revision 1.8  2003/08/09 02:56:44  ddiego
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
*Revision 1.7.2.2  2003/05/25 20:35:29  ddiego
*fixed another bug related to drag drop. This time in allowing the
*IEnumFORMATETC impl to ignore NULL value passed in instead of
*returning an error.
*
*Revision 1.7.2.1  2003/05/25 19:07:11  ddiego
*fixed bug [ 524878 ] onDropped not called for MLTcontrol. This
*was due to errors in the drag-drop implementation for WIn32 and is
*now fixed.
*Also cleaned up the drag-drop implementation and moved/deleted a number of
*irrelevant files for COM support. The vcf/include/com and vcf/src/COM
*directories are now gotten rid of.
*
*Revision 1.7  2003/05/17 20:37:12  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.6.22.2  2003/03/23 03:23:50  marcelloptr
*3 empty lines at the end of the files
*
*Revision 1.6.22.1  2003/03/12 03:11:17  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.6  2002/01/24 01:46:48  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


#endif // _VCF_WIN32DROPTARGETPEER_H__


