#pragma once
#include <map>
using namespace std;
// CCUpStatus 对话框

class CCUpStatus : public CDialog
{
	DECLARE_DYNAMIC(CCUpStatus)

public:
	CCUpStatus(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CCUpStatus();
     
// 对话框数据
	enum { IDD = IDD_FORM_STATUS };
    map<CString,CString> m_Map;
	map<CString,ST_STATUS> m_Status_Map;
	CProgressCtrl m_Prog;
    BOOL m_Can_Exit;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg BOOL OnInitDialog();
	void DoCleanUp();
	void DoUpdate();
	static UINT _cdecl UpdateThread(LPVOID lp);
	virtual BOOL OnSetObjectRects(LPCRECT lpRectPos, LPCRECT lpRectClip);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnPaint();
	afx_msg void OnClose();
};
