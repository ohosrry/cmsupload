#pragma once



// CMSUploader

class CMSUploader : public CWinThread
{
	DECLARE_DYNCREATE(CMSUploader)

protected:
	CMSUploader();           // 动态创建所使用的受保护的构造函数
	virtual ~CMSUploader();

public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

protected:
	DECLARE_MESSAGE_MAP()
};


