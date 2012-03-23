#include "CMSTree.h"
#include "CMSFormView.h"
#pragma once

// CMSInterfaceCtrl.h : CCMSInterfaceCtrl ActiveX 控件类的声明。


// CCMSInterfaceCtrl : 有关实现的信息，请参阅 CMSInterfaceCtrl.cpp。

class CCMSInterfaceCtrl : public COleControl
{
	DECLARE_DYNCREATE(CCMSInterfaceCtrl)

// 构造函数
public:
	static CCMSInterfaceCtrl* thisCtr;
	CCMSInterfaceCtrl();

// 重写
public:
	virtual void OnDraw(CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void DoPropExchange(CPropExchange* pPX);
	virtual void OnResetState();
	virtual BSTR doFtpUpload( BSTR file_name, BSTR new_name, BSTR user, BSTR pwd,BSTR cb);
	virtual BSTR doHttpUpload( BSTR file_name, BSTR new_name, BSTR user, BSTR pwd,BSTR cb);
	virtual BSTR doOpenDialog(BSTR path);
	virtual BSTR doGetPathFiles( BSTR path_name);
	virtual BSTR doGetDriveFiles();
	virtual void OnSetClientSite();
	virtual int OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual void OnWindowPosChanged(WINDOWPOS* lpwndpos);
	virtual void OnPaint();
  //  virtual BOOL OnSetObjectRects(LPCRECT lpRectPos, LPCRECT lpRectClip);
	virtual BOOL OnEraseBkgnd(CDC* pDC);
	virtual HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
    static CCMSInterfaceCtrl* getInstance();
	static UINT AFX_CDECL _httpUploadThread(LPVOID up);
// 实现
protected:
	~CCMSInterfaceCtrl();

	BEGIN_OLEFACTORY(CCMSInterfaceCtrl)        // 类工厂和 guid
		//virtual BOOL VerifyUserLicense();
		//virtual BOOL GetLicenseKey(DWORD, BSTR FAR*);
	END_OLEFACTORY(CCMSInterfaceCtrl)

	DECLARE_OLETYPELIB(CCMSInterfaceCtrl)      // GetTypeInfo
	DECLARE_PROPPAGEIDS(CCMSInterfaceCtrl)     // 属性页 ID
	DECLARE_OLECTLTYPE(CCMSInterfaceCtrl)		// 类型名称和杂项状态

	// 子类控件支持
	BOOL IsSubclassedControl();
	LRESULT OnOcmCommand(WPARAM wParam, LPARAM lParam);

// 消息映射
	DECLARE_MESSAGE_MAP()

// 调度映射
	DECLARE_DISPATCH_MAP()

// 事件映射
	DECLARE_EVENT_MAP()

// 调度和事件 ID
public:
	enum {
		dispidCallJs = 3L,
		dispidregisterCallBack = 2L,
		dispidRegCallBack = 1L,
		dispidTBstr = 1
	};
	CString ftpUrl;
	CString httpUrl;
	CString ftpUser;
	CString ftpPwd;
	CString httpUser;
	CString httpPwd;
	CString callBackUrl;
	CString uploadDir;
	CString brand_code;
	CString goods_sn;
	IDispatch *m_script;
	CCMSTree tree;
	CCMSFormView m_formView;
protected:
	void OnTBstrChanged(void);
	CString m_TBstr;
	BSTR registerCallBack(IDispatch* dispatch);
private:
	int _call_js(BSTR function_name,DISPPARAMS params,INT param_count);
public:
	BSTR CallJs(LPCTSTR function_name,DISPPARAMS params,INT param_count=0);
};

