#ifndef __VCF_OSHANDLEPEER_H__
#define __VCF_OSHANDLEPEER_H__

//OSHandlePeer.h

/*
Copyright 2000-2007 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCF {


	/**
	\class OSHandlePeer OSHandlePeer.h "vcf/FoundationKit/OSHandlePeer.h"	
	This is used to as a generic wrapper around native OS objects or "handles".
	Things like threads, files, graphics objects, controls, all (usually)
	have some sort of native OS representation, which this class is used
	to provide access to. The OS handle is represented by a 32 bit value,
	whose meaning is entirely platform dependant. For example, this value
	is equivalent to a Win32 HANDLE, HDC, or HWND, depending on the 
	exact context of it's usage. On othe systems, this may very 
	well be an actual class instance, and must be type casted to the 
	relevant platform dependant type before being used.

	With this class you can get access to current handle id. In addition you 
	may attach to existing handles, and detach from the current handle. If 
	you attach to an existing handle, the internals of the implementation 
	should reset it's current state to match that of the current handle.
	For example, if you attach to an existing HWND, then the current 
	ControlPeer implementation should hook into the HWND's WndProc, and reset
	it's state accordingly. 
	If you detach the handle, then you are disassociating the link between the
	specific VCF peer C++ implementation instance and the current handle. At this
	point you can safely destroy the VCF instance, with absolutely no effect on
	the returned handle. For example, if a the handle is a HWND, then if you
	detach from it, the current HWND is returned, and if the peer is destroyed,
	the HWND is \em not destroyed with it (as would typically be the case).
	
	@see OSHandleID
	*/
	class FOUNDATIONKIT_API OSHandlePeer {
	public:
		virtual ~OSHandlePeer(){};

		virtual OSHandleID getHandleID() = 0;

		virtual void attach( OSHandleID handleID ) = 0;

		virtual OSHandleID detach() = 0;
	};
};

#endif //__VCF_OSHANDLEPEER_H__


