
// MFCSample.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CMFCSampleApp:
// �йش����ʵ�֣������ MFCSample.cpp
//

class CMFCSampleApp : public CWinAppEx
{
public:
	CMFCSampleApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CMFCSampleApp theApp;