// CMSUpload.cpp : CCMSUploadApp 和 DLL 注册的实现。

#include "stdafx.h"
#include "CMSUpload.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CCMSUploadApp theApp;

const GUID CDECL BASED_CODE _tlid =
		{ 0xE9FA885A, 0xEA4D, 0x474A, { 0xB4, 0xD4, 0xC1, 0xC9, 0xA6, 0x42, 0x29, 0xA6 } };
const WORD _wVerMajor = 1;
const WORD _wVerMinor = 0;



// CCMSUploadApp::InitInstance - DLL 初始化

BOOL CCMSUploadApp::InitInstance()
{
	BOOL bInit = COleControlModule::InitInstance();

	if (bInit)
	{
		// TODO: 在此添加您自己的模块初始化代码。
	}
	return bInit;
}



// CCMSUploadApp::ExitInstance - DLL 终止

int CCMSUploadApp::ExitInstance()
{
	// TODO: 在此添加您自己的模块终止代码。
	return COleControlModule::ExitInstance();
}



// DllRegisterServer - 将项添加到系统注册表

STDAPI DllRegisterServer(void)
{
	AFX_MANAGE_STATE(_afxModuleAddrThis);

	if (!AfxOleRegisterTypeLib(AfxGetInstanceHandle(), _tlid))
		return ResultFromScode(SELFREG_E_TYPELIB);

	if (!COleObjectFactoryEx::UpdateRegistryAll(TRUE))
		return ResultFromScode(SELFREG_E_CLASS);

	return NOERROR;
}



// DllUnregisterServer - 将项从系统注册表中移除

STDAPI DllUnregisterServer(void)
{
	AFX_MANAGE_STATE(_afxModuleAddrThis);

	if (!AfxOleUnregisterTypeLib(_tlid, _wVerMajor, _wVerMinor))
		return ResultFromScode(SELFREG_E_TYPELIB);

	if (!COleObjectFactoryEx::UpdateRegistryAll(FALSE))
		return ResultFromScode(SELFREG_E_CLASS);

	return NOERROR;
}
