

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 7.00.0500 */
/* at Sun Mar 04 15:45:45 2012
 */
/* Compiler settings for .\CMSInterface.idl:
    Oicf, W1, Zp8, env=Win32 (32b run)
    protocol : dce , ms_ext, c_ext, robust
    error checks: stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
//@@MIDL_FILE_HEADING(  )

#pragma warning( disable: 4049 )  /* more than 64k source lines */


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__


#ifndef __CMSInterfaceidl_h__
#define __CMSInterfaceidl_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef ___DCMSInterface_FWD_DEFINED__
#define ___DCMSInterface_FWD_DEFINED__
typedef interface _DCMSInterface _DCMSInterface;
#endif 	/* ___DCMSInterface_FWD_DEFINED__ */


#ifndef ___DCMSInterfaceEvents_FWD_DEFINED__
#define ___DCMSInterfaceEvents_FWD_DEFINED__
typedef interface _DCMSInterfaceEvents _DCMSInterfaceEvents;
#endif 	/* ___DCMSInterfaceEvents_FWD_DEFINED__ */


#ifndef __CMSInterface_FWD_DEFINED__
#define __CMSInterface_FWD_DEFINED__

#ifdef __cplusplus
typedef class CMSInterface CMSInterface;
#else
typedef struct CMSInterface CMSInterface;
#endif /* __cplusplus */

#endif 	/* __CMSInterface_FWD_DEFINED__ */


#ifdef __cplusplus
extern "C"{
#endif 


/* interface __MIDL_itf_CMSInterface_0000_0000 */
/* [local] */ 

#pragma once


extern RPC_IF_HANDLE __MIDL_itf_CMSInterface_0000_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_CMSInterface_0000_0000_v0_0_s_ifspec;


#ifndef __CMSInterfaceLib_LIBRARY_DEFINED__
#define __CMSInterfaceLib_LIBRARY_DEFINED__

/* library CMSInterfaceLib */
/* [control][helpstring][helpfile][version][uuid] */ 


EXTERN_C const IID LIBID_CMSInterfaceLib;

#ifndef ___DCMSInterface_DISPINTERFACE_DEFINED__
#define ___DCMSInterface_DISPINTERFACE_DEFINED__

/* dispinterface _DCMSInterface */
/* [helpstring][uuid] */ 


EXTERN_C const IID DIID__DCMSInterface;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("259F2DB9-9280-46E4-A1F4-7EC1405EBF71")
    _DCMSInterface : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _DCMSInterfaceVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _DCMSInterface * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _DCMSInterface * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _DCMSInterface * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _DCMSInterface * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _DCMSInterface * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _DCMSInterface * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _DCMSInterface * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } _DCMSInterfaceVtbl;

    interface _DCMSInterface
    {
        CONST_VTBL struct _DCMSInterfaceVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _DCMSInterface_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define _DCMSInterface_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define _DCMSInterface_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define _DCMSInterface_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define _DCMSInterface_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define _DCMSInterface_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define _DCMSInterface_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___DCMSInterface_DISPINTERFACE_DEFINED__ */


#ifndef ___DCMSInterfaceEvents_DISPINTERFACE_DEFINED__
#define ___DCMSInterfaceEvents_DISPINTERFACE_DEFINED__

/* dispinterface _DCMSInterfaceEvents */
/* [helpstring][uuid] */ 


EXTERN_C const IID DIID__DCMSInterfaceEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("BF457155-D9A3-44D1-829B-D47D1E9F1E88")
    _DCMSInterfaceEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _DCMSInterfaceEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _DCMSInterfaceEvents * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _DCMSInterfaceEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _DCMSInterfaceEvents * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _DCMSInterfaceEvents * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _DCMSInterfaceEvents * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _DCMSInterfaceEvents * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _DCMSInterfaceEvents * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } _DCMSInterfaceEventsVtbl;

    interface _DCMSInterfaceEvents
    {
        CONST_VTBL struct _DCMSInterfaceEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _DCMSInterfaceEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define _DCMSInterfaceEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define _DCMSInterfaceEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define _DCMSInterfaceEvents_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define _DCMSInterfaceEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define _DCMSInterfaceEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define _DCMSInterfaceEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___DCMSInterfaceEvents_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_CMSInterface;

#ifdef __cplusplus

class DECLSPEC_UUID("C3F95086-97B7-47E7-95BD-EB3D6345B2D1")
CMSInterface;
#endif
#endif /* __CMSInterfaceLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


