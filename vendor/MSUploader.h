#pragma once



// CMSUploader

class CMSUploader : public CWinThread
{
	DECLARE_DYNCREATE(CMSUploader)

protected:
	CMSUploader();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CMSUploader();

public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

protected:
	DECLARE_MESSAGE_MAP()
};


