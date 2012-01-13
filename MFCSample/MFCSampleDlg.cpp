
// MFCSampleDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MFCSample.h"
#include "MFCSampleDlg.h"
#include "DlgProxy.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CMFCSampleDlg �Ի���




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
	// ����öԻ������Զ���������
	//  ���˴���ָ��öԻ���ĺ���ָ������Ϊ NULL���Ա�
	//  �˴���֪���öԻ����ѱ�ɾ����
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

// CMFCSampleDlg ��Ϣ�������

BOOL CMFCSampleDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
    cb=new CButton();
	
	cb->Create(_T("Button"),WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON,CRect(100,100,50,100),this,1);
	
	ShowWindow(SW_MINIMIZE);
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CMFCSampleDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CMFCSampleDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

// ���û��ر� UI ʱ������������Ա���������ĳ��
//  �������Զ�����������Ӧ�˳�����Щ
//  ��Ϣ�������ȷ����������: �����������ʹ�ã�
//  ������ UI�������ڹرնԻ���ʱ��
//  �Ի�����Ȼ�ᱣ�������

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
	// �����������Ա�����������Զ���
	//  �������Իᱣ�ִ�Ӧ�ó���
	//  ʹ�Ի���������������� UI ����������
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

	// TODO: �ڴ˴������Ϣ����������
}

int CMFCSampleDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{

	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������

	return 0;
}

void CMFCSampleDlg::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
   AfxMessageBox(_T("MESSAGE"));
	CDialog::OnChar(nChar, nRepCnt, nFlags);
}

void CMFCSampleDlg::OnSysChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
AfxMessageBox(_T("MESSAGE"));
	CDialog::OnSysChar(nChar, nRepCnt, nFlags);
}
