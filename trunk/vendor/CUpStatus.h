#pragma once
#include <map>
using namespace std;
// CCUpStatus �Ի���

class CCUpStatus : public CDialog
{
	DECLARE_DYNAMIC(CCUpStatus)

public:
	CCUpStatus(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CCUpStatus();
     
// �Ի�������
	enum { IDD = IDD_FORM_STATUS };
    map<CString,CString> m_Map;
    BOOL m_Can_Exit;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg BOOL OnInitDialog();
	static UINT _cdecl UpdateThread(LPVOID lp);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnPaint();
};
