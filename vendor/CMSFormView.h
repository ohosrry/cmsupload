#include "Resource.h"
#pragma once
#include <afxmt.h>
#include <afxcmn.h>
#include <vector>
#include <map>
#include <atlimage.h>
#include <afxwin.h>
using namespace std;
class CCMSFormView;
struct ST_DRAG
{
	CImageList *m_image;
	INT m_drag_index;
	CString m_String;
	CPoint m_pt_point_drag;
	CPoint m_pt_origin;
	CPoint m_pt_hotspot;
	CPoint m_pt_item;
	CPoint m_pt_action;
	CPoint m_pt_image;
	/*~ST_DRAG(){
		SAFE_DELETE(m_image);
	}*/
};

struct ST_THREAD_PARAM{
	ST_THREAD_PARAM(){}
CCMSFormView *m_Main;
INT count;
};

// CCMSFormView 窗体视图

class CCMSFormView : public CDialog
{
	DECLARE_DYNCREATE(CCMSFormView)

public:
	friend class CCMSInterfaceCtrl;
public:
	CCMSFormView();           // 动态创建所使用的受保护的构造函数
	virtual ~CCMSFormView();
	virtual void PostNcDestroy();

public:
	enum { IDD = IDD_FORMVIEW };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg BOOL OnInitDialog();
	BOOL m_bDraging;
	CListCtrl m_List_Pic;
	CListCtrl m_List_Up;
	CTreeCtrl m_Tree;
	CImageList m_Image_List;
	CImageList m_Image_Pic;
	CImageList m_Image_Up;
	CString m_DragItemString;
	INT m_Item_Drag;
	INT m_Image_Up_Id;
	CPoint m_Pt_Origin;
	CPoint m_ptHotSpot;
	CImageList *m_Drag_Image;
	CImage m_Big_Drag_Image;
	CBrush m_brush;
    vector<CImage*> m_Image_Vector;
	vector<CBitmap*> m_Bitmap_Vector;
	vector<CImageList*> m_Drag_Vector;
	vector<INT> m_Selected_Index;
	vector<INT*> m_Pid_Vector;
	vector<ST_DRAG> m_St_Drag;
	CImageList m_Big_Drag;
	INT m_Pic_Id;
	INT m_Pic_Up_Id;
	CButton m_Upload_Button;
    CMenu m_Menu;
	map<string,string *> m_Tree_Map;

	CCheckListBox m_Check_All;

    BOOL m_Check_Lock;
	static CCriticalSection m_Section;
	std::map<std::string,std::string> m_Up_Map;
	vector<CWinThread*> m_Up_Thread;
	vector<CBitmap*> m_BitMap_Vector;
	afx_msg void OnNMClickDir(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnTvnSelchangedDir(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPaint();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnLvnBegindragListPic(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnMButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnNMDblclkListPic(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblclkListUp(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedCheckAll();
	static UINT _cdecl UploadThread(LPVOID lp);
	afx_msg void OnBnClickedButtonUp();
	afx_msg void OnMButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
	void OnPreview();
	afx_msg void OnNMRClickListUp(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMRClickListPic(NMHDR *pNMHDR, LRESULT *pResult);
};


