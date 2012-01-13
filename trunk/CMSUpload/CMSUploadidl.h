

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 7.00.0500 */
/* at Thu Jan 12 17:09:27 2012
 */
/* Compiler settings for .\CMSUpload.idl:
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


#ifndef __CMSUploadidl_h__
#define __CMSUploadidl_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef ___DCMSUpload_FWD_DEFINED__
#define ___DCMSUpload_FWD_DEFINED__
typedef interface _DCMSUpload _DCMSUpload;
#endif 	/* ___DCMSUpload_FWD_DEFINED__ */


#ifndef ___DCMSUploadEvents_FWD_DEFINED__
#define ___DCMSUploadEvents_FWD_DEFINED__
typedef interface _DCMSUploadEvents _DCMSUploadEvents;
#endif 	/* ___DCMSUploadEvents_FWD_DEFINED__ */


#ifndef __CMSUpload_FWD_DEFINED__
#define __CMSUpload_FWD_DEFINED__

#ifdef __cplusplus
typedef class CMSUpload CMSUpload;
#else
typedef struct CMSUpload CMSUpload;
#endif /* __cplusplus */

#endif 	/* __CMSUpload_FWD_DEFINED__ */


#ifdef __cplusplus
extern "C"{
#endif 



#ifndef __CMSUploadLib_LIBRARY_DEFINED__
#define __CMSUploadLib_LIBRARY_DEFINED__

/* library CMSUploadLib */
/* [control][helpstring][helpfile][version][uuid] */ 


EXTERN_C const IID LIBID_CMSUploadLib;

#ifndef ___DCMSUpload_DISPINTERFACE_DEFINED__
#define ___DCMSUpload_DISPINTERFACE_DEFINED__

/* dispinterface _DCMSUpload */
/* [helpstring][uuid] */ 


EXTERN_C const IID DIID__DCMSUpload;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("63572DDD-A45A-4864-BC84-012B89E78868")
    _DCMSUpload : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _DCMSUploadVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _DCMSUpload * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _DCMSUpload * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _DCMSUpload * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _DCMSUpload * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _DCMSUpload * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _DCMSUpload * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _DCMSUpload * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } _DCMSUploadVtbl;

    interface _DCMSUpload
    {
        CONST_VTBL struct _DCMSUploadVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _DCMSUpload_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define _DCMSUpload_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define _DCMSUpload_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define _DCMSUpload_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define _DCMSUpload_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define _DCMSUpload_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define _DCMSUpload_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___DCMSUpload_DISPINTERFACE_DEFINED__ */


#ifndef ___DCMSUploadEvents_DISPINTERFACE_DEFINED__
#define ___DCMSUploadEvents_DISPINTERFACE_DEFINED__

/* dispinterface _DCMSUploadEvents */
/* [helpstring][uuid] */ 


EXTERN_C const IID DIID__DCMSUploadEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("5E794A69-D4C4-4BEA-9ABC-2BE1C59641A7")
    _DCMSUploadEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _DCMSUploadEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _DCMSUploadEvents * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _DCMSUploadEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _DCMSUploadEvents * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _DCMSUploadEvents * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _DCMSUploadEvents * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _DCMSUploadEvents * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _DCMSUploadEvents * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } _DCMSUploadEventsVtbl;

    interface _DCMSUploadEvents
    {
        CONST_VTBL struct _DCMSUploadEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _DCMSUploadEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define _DCMSUploadEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define _DCMSUploadEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define _DCMSUploadEvents_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define _DCMSUploadEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define _DCMSUploadEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define _DCMSUploadEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___DCMSUploadEvents_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_CMSUpload;

#ifdef __cplusplus

class DECLSPEC_UUID("C79D3A60-1BD0-419B-8840-8E2CC4778569")
CMSUpload;
#endif
#endif /* __CMSUploadLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


