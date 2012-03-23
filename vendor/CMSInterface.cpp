// CMSInterface.cpp : CCMSInterfaceApp 和 DLL 注册的实现。

#include "stdafx.h"
#include <curl/curl.h>
#include "CMSInterface.h"
#include <iostream>
#include <cstring>
#include <vector>
#include <map>
#include "comcat.h"
#include <strsafe.h>
#include "Objsafe.h"
using namespace std;
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
extern map<string,BSTR> strMap;

CCriticalSection g_Map_Lock;
CCMSInterfaceApp theApp;

const GUID CDECL BASED_CODE _tlid =
		{ 0x821AE153, 0xD15E, 0x4372, { 0xB4, 0x30, 0xA5, 0xBB, 0x99, 0xA5, 0x88, 0xC3 } };
const GUID CDECL BASED_CODE CLSID_SafeItem =
{0x821AE153, 0xD15E, 0x4372, { 0xB4, 0x30, 0xA5, 0xBB, 0x99, 0xA5, 0x88, 0xC3 }};
const WORD _wVerMajor = 1;
const WORD _wVerMinor = 0;
// CCMSInterfaceApp::InitInstance - DLL 初始化

BOOL CCMSInterfaceApp::InitInstance()
{
	BOOL bInit = COleControlModule::InitInstance();

	if (bInit)
	{
		// TODO: 在此添加您自己的模块初始化代码。
      curl_global_init(CURL_GLOBAL_WIN32);
	 // g_Map_Lock.Init();
	}

	return bInit;
}



// CCMSInterfaceApp::ExitInstance - DLL 终止

int CCMSInterfaceApp::ExitInstance()
{
	// TODO: 在此添加您自己的模块终止代码。
    curl_global_cleanup();
    
	return COleControlModule::ExitInstance();
}


HRESULT CreateComponentCategory(CATID catid, WCHAR *catDescription)
{
	ICatRegister *pcr = NULL ;
	HRESULT hr = S_OK ;

	hr = CoCreateInstance(CLSID_StdComponentCategoriesMgr, 
		NULL, CLSCTX_INPROC_SERVER, IID_ICatRegister, (void**)&pcr);
	if (FAILED(hr))
		return hr;

	// Make sure the HKCR\Component Categories\{..catid...}
	// key is registered.
	CATEGORYINFO catinfo;
	catinfo.catid = catid;
	catinfo.lcid = 0x0409 ; // english
	int len;
	// Make sure the provided description is not too long.
	// Only copy the first 127 characters if it is.
	// The second parameter of StringCchLength is the maximum
	// number of characters that may be read into catDescription.
	// There must be room for a NULL-terminator. The third parameter
	// contains the number of characters excluding the NULL-terminator.
	hr = StringCchLength(catDescription, STRSAFE_MAX_CCH, (size_t*)&len);
	if (SUCCEEDED(hr))
	{
		if (len>127)
		{
			len = 127;
		}
	}   
	else
	{
//TODO: Write an error handler;
	}
	// The second parameter of StringCchCopy is 128 because you need 
	// room for a NULL-terminator.    
	hr = StringCchCopy(catinfo.szDescription, len + 1, 
		catDescription);
	// Make sure the description is null terminated.
	catinfo.szDescription[len + 1] = '\0';

	hr = pcr->RegisterCategories(1, &catinfo);
	pcr->Release();

	return hr;
}

HRESULT UnRegisterCLSIDInCategory(REFCLSID clsid, CATID catid)
{
	ICatRegister *pcr = NULL ;
	HRESULT hr = S_OK ;

	hr = CoCreateInstance(CLSID_StdComponentCategoriesMgr, 
		NULL, CLSCTX_INPROC_SERVER, IID_ICatRegister, (void**)&pcr);
	if (SUCCEEDED(hr))
	{
		// Unregister this category as being "implemented" by the class.
		CATID rgcatid[1] ;
		rgcatid[0] = catid;
		hr = pcr->UnRegisterClassImplCategories(clsid, 1, rgcatid);
	}

	if (pcr != NULL)
		pcr->Release();

	return hr;
}


HRESULT RegisterCLSIDInCategory(REFCLSID clsid, CATID catid)
{
	// Register your component categories information.
	ICatRegister *pcr = NULL ;
	HRESULT hr = S_OK ;
	hr = CoCreateInstance(CLSID_StdComponentCategoriesMgr, 
		NULL, CLSCTX_INPROC_SERVER, IID_ICatRegister, (void**)&pcr);
	if (SUCCEEDED(hr))
	{
		// Register this category as being "implemented" by the class.
		CATID rgcatid[1] ;
		rgcatid[0] = catid;
		hr = pcr->RegisterClassImplCategories(clsid, 1, rgcatid);
	}

	if (pcr != NULL)
		pcr->Release();

	return hr;
}

// DllRegisterServer - 将项添加到系统注册表

STDAPI DllRegisterServer(void)
{
	HRESULT hr;
	AFX_MANAGE_STATE(_afxModuleAddrThis);

	if (!AfxOleRegisterTypeLib(AfxGetInstanceHandle(), _tlid))
		return ResultFromScode(SELFREG_E_TYPELIB);

	if (!COleObjectFactoryEx::UpdateRegistryAll(TRUE))
		return ResultFromScode(SELFREG_E_CLASS);

	hr = CreateComponentCategory(CATID_SafeForInitializing, L"Controls safely initializable from persistent data!");
		if (FAILED(hr))
			return hr;

	hr = RegisterCLSIDInCategory(CLSID_SafeItem, CATID_SafeForInitializing);
	if (FAILED(hr))
		return hr;

	// Mark the control as safe for scripting.

	hr = CreateComponentCategory(CATID_SafeForScripting, L"Controls safely scriptable!");
		if (FAILED(hr))
			return hr;

	hr = RegisterCLSIDInCategory(CLSID_SafeItem, CATID_SafeForScripting);
	if (FAILED(hr))
		return hr;

	return NOERROR;
}



// DllUnregisterServer - 将项从系统注册表中移除

STDAPI DllUnregisterServer(void)
{   
	HRESULT hr;
	AFX_MANAGE_STATE(_afxModuleAddrThis);

	if (!AfxOleUnregisterTypeLib(_tlid, _wVerMajor, _wVerMinor))
		return ResultFromScode(SELFREG_E_TYPELIB);

	if (!COleObjectFactoryEx::UpdateRegistryAll(FALSE))
		return ResultFromScode(SELFREG_E_CLASS);
	hr=UnRegisterCLSIDInCategory(CLSID_SafeItem, CATID_SafeForInitializing);
	if (FAILED(hr))
		return hr;

	hr=UnRegisterCLSIDInCategory(CLSID_SafeItem, CATID_SafeForScripting);
	if (FAILED(hr))
		return hr;

	return NOERROR;
}
