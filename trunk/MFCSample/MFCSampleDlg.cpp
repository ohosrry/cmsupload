
// MFCSampleDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MFCSample.h"
#include "MFCSampleDlg.h"
#include "DlgProxy.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	EnableActiveAccessibility();
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CMFCSampleDlg 对话框




IMPLEMENT_DYNAMIC(CMFCSampleDlg, CDialog);

CMFCSampleDlg::CMFCSampleDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMFCSampleDlg::IDD, pParent)
{
	EnableActiveAccessibility();
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_pAutoProxy = NULL;
}

CMFCSampleDlg::~CMFCSampleDlg()
{
	// 如果该对话框有自动化代理，则
	//  将此代理指向该对话框的后向指针设置为 NULL，以便
	//  此代理知道该对话框已被删除。
	if (m_pAutoProxy != NULL)
		m_pAutoProxy->m_pDialog = NULL;
}

void CMFCSampleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCSampleDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_CLOSE()
	ON_WM_PAINT()
	
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_WM_ACTIVATE()
//	ON_WM_CHAR()
	ON_WM_CREATE()
	ON_WM_CHAR()
	ON_WM_SYSCHAR()
END_MESSAGE_MAP()

//void CMFCSampleDlg::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags){
//AfxMessageBox(_T("char"));
//}

// CMFCSampleDlg 消息处理程序

BOOL CMFCSampleDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);
    
	CMenu* pSysMenu = GetSystemMenu(FALSE);

	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	

	// TODO: 在此添加额外的初始化代码
    cb=new CButton();
	
	cb->Create(_T("Button"),WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON,CRect(100,100,50,100),this,1);
	
	ShowWindow(SW_MINIMIZE);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMFCSampleDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMFCSampleDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMFCSampleDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

// 当用户关闭 UI 时，如果控制器仍保持着它的某个
//  对象，则自动化服务器不应退出。这些
//  消息处理程序确保如下情形: 如果代理仍在使用，
//  则将隐藏 UI；但是在关闭对话框时，
//  对话框仍然会保留在那里。

void CMFCSampleDlg::OnClose()
{
	if (CanExit())
		CDialog::OnClose();
}

void CMFCSampleDlg::OnOK()
{
	if (CanExit())
		CDialog::OnOK();
}

void CMFCSampleDlg::OnCancel()
{
	if (CanExit())
		CDialog::OnCancel();
}

BOOL CMFCSampleDlg::CanExit()
{
	// 如果代理对象仍保留在那里，则自动化
	//  控制器仍会保持此应用程序。
	//  使对话框保留在那里，但将其 UI 隐藏起来。
	if (m_pAutoProxy != NULL)
	{
		ShowWindow(SW_HIDE);
		return FALSE;
	}

	return TRUE;
}


void CMFCSampleDlg::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized)
{
	//AfxMessageBox(_T("Active"));
	CDialog::OnActivate(nState, pWndOther, bMinimized);

	// TODO: 在此处添加消息处理程序代码
}

int CMFCSampleDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{

	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码

	return 0;
}

void CMFCSampleDlg::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
   AfxMessageBox(_T("MESSAGE"));
	CDialog::OnChar(nChar, nRepCnt, nFlags);
}

void CMFCSampleDlg::OnSysChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
AfxMessageBox(_T("MESSAGE"));
	CDialog::OnSysChar(nChar, nRepCnt, nFlags);
}
