

/* this ALWAYS GENERATED file contains the IIDs and CLSIDs */

/* link this file in with the server and any clients */


 /* File created by MIDL compiler version 7.00.0500 */
/* at Tue Jan 31 18:22:10 2012
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

MIDL_DEFINE_GUID(IID, LIBID_CMSUploadLib,0xE9FA885A,0xEA4D,0x474A,0xB4,0xD4,0xC1,0xC9,0xA6,0x42,0x29,0xA6);


MIDL_DEFINE_GUID(IID, DIID__DCMSUpload,0x63572DDD,0xA45A,0x4864,0xBC,0x84,0x01,0x2B,0x89,0xE7,0x88,0x68);


MIDL_DEFINE_GUID(IID, DIID__DCMSUploadEvents,0x5E794A69,0xD4C4,0x4BEA,0x9A,0xBC,0x2B,0xE1,0xC5,0x96,0x41,0xA7);


MIDL_DEFINE_GUID(CLSID, CLSID_CMSUpload,0xC79D3A60,0x1BD0,0x419B,0x88,0x40,0x8E,0x2C,0xC4,0x77,0x85,0x69);

#undef MIDL_DEFINE_GUID

#ifdef __cplusplus
}
#endif



