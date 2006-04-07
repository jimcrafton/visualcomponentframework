/** \file 
 * comtype<> definitions for interfaces in the COM header file OLEIDL.H.
 * \author Gabriel Barta
 */
/*
 * Copyright © 2002 Gabriel Barta
 *
 * This material is provided "as is", with absolutely no warranty 
 * expressed or implied. Any use is at your own risk. Permission to 
 * use or copy this software for any purpose is hereby granted without 
 * fee, provided the above notices are retained on all copies. 
 * Permission to modify the code and to distribute modified code is 
 * granted, provided the above notices are retained, and a notice that 
 * the code was modified is included with the above copyright notice. 
 *
 * This header is part of comet.
 * http://www.lambdasoft.dk/comet
 */

#ifndef COMET_OLEIDL_COMTYPES_H
#define COMET_OLEIDL_COMTYPES_H

#include <comet/interface.h>

namespace comet {
	template<> struct comtype<::IOleAdviseHolder> 
		: public uuid_comtype<IID_IOleAdviseHolder, ::IUnknown> {} ;
	template<> struct comtype<::IOleCache> 
		: public uuid_comtype<IID_IOleCache, ::IUnknown> {} ;
	template<> struct comtype<::IOleCache2> 
		: public uuid_comtype<IID_IOleCache2, ::IOleCache> {} ;
	template<> struct comtype<::IOleCacheControl> 
		: public uuid_comtype<IID_IOleCacheControl, ::IUnknown> {} ;
	template<> struct comtype<::IParseDisplayName> 
		: public uuid_comtype<IID_IParseDisplayName, ::IUnknown> {} ;
	template<> struct comtype<::IOleContainer> 
		: public uuid_comtype<IID_IOleContainer, ::IParseDisplayName> {} ;
	template<> struct comtype<::IOleClientSite> 
		: public uuid_comtype<IID_IOleClientSite, ::IUnknown> {} ;
	template<> struct comtype<::IOleObject> 
		: public uuid_comtype<IID_IOleObject, ::IUnknown> {} ;
	template<> struct comtype<::IOleWindow> 
		: public uuid_comtype<IID_IOleWindow, ::IUnknown> {} ;
	template<> struct comtype<::IOleLink> 
		: public uuid_comtype<IID_IOleLink, ::IUnknown> {} ;
	template<> struct comtype<::IOleItemContainer> 
		: public uuid_comtype<IID_IOleItemContainer, ::IOleContainer> {} ;
	template<> struct comtype<::IOleInPlaceUIWindow> 
		: public uuid_comtype<IID_IOleInPlaceUIWindow, ::IOleWindow> {} ;
	template<> struct comtype<::IOleInPlaceActiveObject> 
		: public uuid_comtype<IID_IOleInPlaceActiveObject, ::IOleWindow> {} ;
	template<> struct comtype<::IOleInPlaceFrame> 
		: public uuid_comtype<IID_IOleInPlaceFrame, ::IOleInPlaceUIWindow> {} ;
	template<> struct comtype<::IOleInPlaceObject> 
		: public uuid_comtype<IID_IOleInPlaceObject, ::IOleWindow> {} ;
	template<> struct comtype<::IOleInPlaceSite> 
		: public uuid_comtype<IID_IOleInPlaceSite, ::IOleWindow> {} ;
	template<> struct comtype<::IContinue> 
		: public uuid_comtype<IID_IContinue, ::IUnknown> {} ;
	template<> struct comtype<::IViewObject> 
		: public uuid_comtype<IID_IViewObject, ::IUnknown> {} ;
	template<> struct comtype<::IViewObject2> 
		: public uuid_comtype<IID_IViewObject2, ::IViewObject> {} ;
	template<> struct comtype<::IDropSource> 
		: public uuid_comtype<IID_IDropSource, ::IUnknown> {} ;
	template<> struct comtype<::IDropTarget> 
		: public uuid_comtype<IID_IDropTarget, ::IUnknown> {} ;
	template<> struct comtype<::IEnumOLEVERB> 
		: public uuid_comtype<IID_IEnumOLEVERB, ::IUnknown> {} ;
};

#endif //COMET_OLEIDL_COMTYPES_H
