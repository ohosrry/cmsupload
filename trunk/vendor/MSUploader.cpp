// MSUploader.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CMSInterface.h"
#include "MSUploader.h"


// CMSUploader

IMPLEMENT_DYNCREATE(CMSUploader, CWinThread)

CMSUploader::CMSUploader()
{
}

CMSUploader::~CMSUploader()
{
}

BOOL CMSUploader::InitInstance()
{
	// TODO: �ڴ�ִ���������̳߳�ʼ��
	return TRUE;
}

int CMSUploader::ExitInstance()
{
	// TODO: �ڴ�ִ���������߳�����
	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(CMSUploader, CWinThread)
END_MESSAGE_MAP()


// CMSUploader ��Ϣ�������
