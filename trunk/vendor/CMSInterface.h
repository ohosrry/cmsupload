#pragma once

// CMSInterface.h : CMSInterface.DLL ����ͷ�ļ�

#if !defined( __AFXCTL_H__ )
#error "�ڰ������ļ�֮ǰ������afxctl.h��"
#endif

#include "resource.h"       // ������

// CCMSInterfaceApp : �й�ʵ�ֵ���Ϣ������� CMSInterface.cpp��

class CCMSInterfaceApp : public COleControlModule
{
public:
	BOOL InitInstance();
	int ExitInstance();
};

extern const GUID CDECL _tlid;
extern const WORD _wVerMajor;
extern const WORD _wVerMinor;

