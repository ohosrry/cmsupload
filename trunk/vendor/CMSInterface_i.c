

/* this ALWAYS GENERATED file contains the IIDs and CLSIDs */

/* link this file in with the server and any clients */


 /* File created by MIDL compiler version 7.00.0500 */
/* at Mon Mar 19 08:56:40 2012
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


#ifdef __cplusplus
extern "C"{
#endif 


#include <rpc.h>
#include <rpcndr.h>

#ifdef _MIDL_USE_GUIDDEF_

#ifndef INITGUID
#define INITGUID
#include <guiddef.h>
#undef INITGUID
#else
#include <guiddef.h>
#endif

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        DEFINE_GUID(name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8)

#else // !_MIDL_USE_GUIDDEF_

#ifndef __IID_DEFINED__
#define __IID_DEFINED__

typedef struct _IID
{
    unsigned long x;
    unsigned short s1;
    unsigned short s2;
    unsigned char  c[8];
} IID;

#endif // __IID_DEFINED__

#ifndef CLSID_DEFINED
#define CLSID_DEFINED
typedef IID CLSID;
#endif // CLSID_DEFINED

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        const type name = {l,w1,w2,{b1,b2,b3,b4,b5,b6,b7,b8}}

#endif !_MIDL_USE_GUIDDEF_

MIDL_DEFINE_GUID(IID, LIBID_CMSInterfaceLib,0x821AE153,0xD15E,0x4372,0xB4,0x30,0xA5,0xBB,0x99,0xA5,0x88,0xC3);


MIDL_DEFINE_GUID(IID, DIID__DCMSInterface,0x259F2DB9,0x9280,0x46E4,0xA1,0xF4,0x7E,0xC1,0x40,0x5E,0xBF,0x71);


MIDL_DEFINE_GUID(IID, DIID__DCMSInterfaceEvents,0xBF457155,0xD9A3,0x44D1,0x82,0x9B,0xD4,0x7D,0x1E,0x9F,0x1E,0x88);


MIDL_DEFINE_GUID(CLSID, CLSID_CMSInterface,0xC3F95086,0x97B7,0x47E7,0x95,0xBD,0xEB,0x3D,0x63,0x45,0xB2,0xD1);

#undef MIDL_DEFINE_GUID

#ifdef __cplusplus
}
#endif



