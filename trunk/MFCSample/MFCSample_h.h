

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 7.00.0500 */
/* at Wed Jan 11 14:05:43 2012
 */
/* Compiler settings for .\MFCSample.idl:
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


#ifndef __MFCSample_h_h__
#define __MFCSample_h_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IMFCSample_FWD_DEFINED__
#define __IMFCSample_FWD_DEFINED__
typedef interface IMFCSample IMFCSample;
#endif 	/* __IMFCSample_FWD_DEFINED__ */


#ifndef __MFCSample_FWD_DEFINED__
#define __MFCSample_FWD_DEFINED__

#ifdef __cplusplus
typedef class MFCSample MFCSample;
#else
typedef struct MFCSample MFCSample;
#endif /* __cplusplus */

#endif 	/* __MFCSample_FWD_DEFINED__ */


#ifdef __cplusplus
extern "C"{
#endif 



#ifndef __MFCSample_LIBRARY_DEFINED__
#define __MFCSample_LIBRARY_DEFINED__

/* library MFCSample */
/* [version][uuid] */ 


EXTERN_C const IID LIBID_MFCSample;

#ifndef __IMFCSample_DISPINTERFACE_DEFINED__
#define __IMFCSample_DISPINTERFACE_DEFINED__

/* dispinterface IMFCSample */
/* [uuid] */ 


EXTERN_C const IID DIID_IMFCSample;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("79036F14-928F-4393-8915-A7DA2FCC0658")
    IMFCSample : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct IMFCSampleVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IMFCSample * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IMFCSample * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IMFCSample * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IMFCSample * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IMFCSample * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IMFCSample * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IMFCSample * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } IMFCSampleVtbl;

    interface IMFCSample
    {
        CONST_VTBL struct IMFCSampleVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMFCSample_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IMFCSample_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IMFCSample_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IMFCSample_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IMFCSample_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IMFCSample_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IMFCSample_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __IMFCSample_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_MFCSample;

#ifdef __cplusplus

class DECLSPEC_UUID("7101368D-BCCC-4519-B397-565559D64C2C")
MFCSample;
#endif
#endif /* __MFCSample_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


