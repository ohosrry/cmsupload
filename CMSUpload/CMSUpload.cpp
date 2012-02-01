// CMSUpload.cpp : CCMSUploadApp �� DLL ע���ʵ�֡�

#include "stdafx.h"
#include "CMSUpload.h"
#include <curl/curl.h>
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CCMSUploadApp theApp;

const GUID CDECL BASED_CODE _tlid =
		{ 0xE9FA885A, 0xEA4D, 0x474A, { 0xB4, 0xD4, 0xC1, 0xC9, 0xA6, 0x42, 0x29, 0xA6 } };
const WORD _wVerMajor = 1;
const WORD _wVerMinor = 0;



// CCMSUploadApp::InitInstance - DLL ��ʼ��

BOOL CCMSUploadApp::InitInstance()
{
	BOOL bInit = COleControlModule::InitInstance();

	if (bInit)
	{ 
			curl_global_init(CURL_GLOBAL_WIN32);
		// TODO: �ڴ�������Լ���ģ���ʼ�����롣
	}
	return bInit;
}



// CCMSUploadApp::ExitInstance - DLL ��ֹ

int CCMSUploadApp::ExitInstance()
{
	// TODO: �ڴ�������Լ���ģ����ֹ���롣
	curl_global_cleanup();
	return COleControlModule::ExitInstance();
}



// DllRegisterServer - ������ӵ�ϵͳע���

STDAPI DllRegisterServer(void)
{
	AFX_MANAGE_STATE(_afxModuleAddrThis);

	if (!AfxOleRegisterTypeLib(AfxGetInstanceHandle(), _tlid))
		return ResultFromScode(SELFREG_E_TYPELIB);

	if (!COleObjectFactoryEx::UpdateRegistryAll(TRUE))
		return ResultFromScode(SELFREG_E_CLASS);

	return NOERROR;
}



// DllUnregisterServer - �����ϵͳע������Ƴ�

STDAPI DllUnregisterServer(void)
{
	AFX_MANAGE_STATE(_afxModuleAddrThis);

	if (!AfxOleUnregisterTypeLib(_tlid, _wVerMajor, _wVerMinor))
		return ResultFromScode(SELFREG_E_TYPELIB);

	if (!COleObjectFactoryEx::UpdateRegistryAll(FALSE))
		return ResultFromScode(SELFREG_E_CLASS);

	return NOERROR;
}
