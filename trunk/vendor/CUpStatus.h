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
	map<CString,ST_STATUS> m_Status_Map;
	CProgressCtrl m_Prog;
    BOOL m_Can_Exit;
	BOOL m_Can_Create;
	BOOL m_Need_Init;
	BOOL m_Update_Thread_Exit;
	CFont m_Font;
	BOOL m_Update_Ok;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg BOOL OnInitDialog();
	void DoInit();
	void DoCleanUp();
	void DoUpdate();
	static UINT _cdecl UpdateThread(LPVOID lp);
	virtual BOOL OnSetObjectRects(LPCRECT lpRectPos, LPCRECT lpRectClip);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnPaint();
	afx_msg void OnClose();
};
