
#pragma warning( disable: 4049 )  /* more than 64k source lines */

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 6.00.0347 */
/* at Wed Jul 20 00:11:36 2005
 */
/* Compiler settings for f:\code\vcfdev\stable\vcf\build\vc60\add-ins\COMToVCFClassWizard\COMToVCFClassWizard.idl:
    Oicf, W1, Zp8, env=Win32 (32b run)
    protocol : dce , ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
//@@MIDL_FILE_HEADING(  )


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 440
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __COMTOVCFCLASSWIZARD_h__
#define __COMTOVCFCLASSWIZARD_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __ICommands_FWD_DEFINED__
#define __ICommands_FWD_DEFINED__
typedef interface ICommands ICommands;
#endif 	/* __ICommands_FWD_DEFINED__ */


#ifndef __Commands_FWD_DEFINED__
#define __Commands_FWD_DEFINED__

#ifdef __cplusplus
typedef class Commands Commands;
#else
typedef struct Commands Commands;
#endif /* __cplusplus */

#endif 	/* __Commands_FWD_DEFINED__ */


#ifndef __COMToVCFClassWizard_FWD_DEFINED__
#define __COMToVCFClassWizard_FWD_DEFINED__

#ifdef __cplusplus
typedef class COMToVCFClassWizard COMToVCFClassWizard;
#else
typedef struct COMToVCFClassWizard COMToVCFClassWizard;
#endif /* __cplusplus */

#endif 	/* __COMToVCFClassWizard_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 

void * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void * ); 


#ifndef __COMTOVCFCLASSWIZARDLib_LIBRARY_DEFINED__
#define __COMTOVCFCLASSWIZARDLib_LIBRARY_DEFINED__

/* library COMTOVCFCLASSWIZARDLib */
/* [helpstring][version][uuid] */ 


DEFINE_GUID(LIBID_COMTOVCFCLASSWIZARDLib,0xb398ee76,0xe839,0x487c,0xba,0xfd,0x72,0x25,0xe8,0xbe,0xbd,0xad);

#ifndef __ICommands_INTERFACE_DEFINED__
#define __ICommands_INTERFACE_DEFINED__

/* interface ICommands */
/* [object][dual][oleautomation][uuid] */ 


DEFINE_GUID(IID_ICommands,0x4abb8ee9,0xb42b,0x42cb,0x99,0x3f,0x98,0x55,0x54,0xf4,0x1e,0x61);

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("4abb8ee9-b42b-42cb-993f-985554f41e61")
    ICommands : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ConvertCOMTypeLib( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ConvertActiveXControl( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ICommandsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ICommands * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ICommands * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ICommands * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ICommands * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ICommands * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ICommands * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ICommands * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ConvertCOMTypeLib )( 
            ICommands * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ConvertActiveXControl )( 
            ICommands * This);
        
        END_INTERFACE
    } ICommandsVtbl;

    interface ICommands
    {
        CONST_VTBL struct ICommandsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICommands_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ICommands_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ICommands_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ICommands_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ICommands_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ICommands_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ICommands_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ICommands_ConvertCOMTypeLib(This)	\
    (This)->lpVtbl -> ConvertCOMTypeLib(This)

#define ICommands_ConvertActiveXControl(This)	\
    (This)->lpVtbl -> ConvertActiveXControl(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICommands_ConvertCOMTypeLib_Proxy( 
    ICommands * This);


void __RPC_STUB ICommands_ConvertCOMTypeLib_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ICommands_ConvertActiveXControl_Proxy( 
    ICommands * This);


void __RPC_STUB ICommands_ConvertActiveXControl_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ICommands_INTERFACE_DEFINED__ */


DEFINE_GUID(CLSID_Commands,0x9ff50665,0x30a0,0x4e5d,0xbd,0x3f,0x8b,0x66,0x72,0xa0,0xc7,0x92);

#ifdef __cplusplus

class DECLSPEC_UUID("9ff50665-30a0-4e5d-bd3f-8b6672a0c792")
Commands;
#endif

DEFINE_GUID(CLSID_COMToVCFClassWizard,0x1973ab9d,0xdc6e,0x4f1f,0x84,0x06,0x81,0x8b,0x16,0xe1,0xda,0x79);

#ifdef __cplusplus

class DECLSPEC_UUID("1973ab9d-dc6e-4f1f-8406-818b16e1da79")
COMToVCFClassWizard;
#endif
#endif /* __COMTOVCFCLASSWIZARDLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


