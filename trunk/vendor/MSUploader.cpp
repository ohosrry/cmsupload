// MSUploader.cpp : 实现文件
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
	// TODO: 在此执行任意逐线程初始化
	return TRUE;
}

int CMSUploader::ExitInstance()
{
	// TODO: 在此执行任意逐线程清理
	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(CMSUploader, CWinThread)
END_MESSAGE_MAP()


// CMSUploader 消息处理程序
