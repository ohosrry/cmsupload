// CMSUploadCtrl.cpp : CCMSUploadCtrl ActiveX �ؼ����ʵ�֡�

#include "stdafx.h"
#include "CMSUpload.h"
#include "CMSUploadCtrl.h"
#include "CMSUploadPropPage.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


IMPLEMENT_DYNCREATE(CCMSUploadCtrl, COleControl)

// ��Ϣӳ��

BEGIN_MESSAGE_MAP(CCMSUploadCtrl, COleControl)
	ON_MESSAGE(OCM_COMMAND, &CCMSUploadCtrl::OnOcmCommand)
	ON_OLEVERB(AFX_IDS_VERB_EDIT, OnEdit)
	ON_OLEVERB(AFX_IDS_VERB_PROPERTIES, OnProperties)
	ON_WM_CREATE()
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSEHOVER()
	ON_WM_LBUTTONUP()
	ON_WM_KEYUP()
	ON_WM_KEYDOWN()
	ON_WM_LBUTTONDBLCLK()
	
END_MESSAGE_MAP()



// ����ӳ��

BEGIN_DISPATCH_MAP(CCMSUploadCtrl, COleControl)
	DISP_FUNCTION_ID(CCMSUploadCtrl, "AboutBox", DISPID_ABOUTBOX, AboutBox, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION_ID(CCMSUploadCtrl, "DoClick", DISPID_DOCLICK, DoClick, VT_EMPTY, VTS_NONE)
END_DISPATCH_MAP()



// �¼�ӳ��

BEGIN_EVENT_MAP(CCMSUploadCtrl, COleControl)
EVENT_STOCK_CLICK()
EVENT_STOCK_MOUSEUP()
EVENT_STOCK_KEYDOWN()
EVENT_STOCK_DBLCLICK()
EVENT_STOCK_MOUSEMOVE()
END_EVENT_MAP()
// ����ҳ

// TODO: ����Ҫ��Ӹ�������ҳ�����ס���Ӽ���!
BEGIN_PROPPAGEIDS(CCMSUploadCtrl, 1)
	PROPPAGEID(CCMSUploadPropPage::guid)
END_PROPPAGEIDS(CCMSUploadCtrl)



// ��ʼ���๤���� guid

IMPLEMENT_OLECREATE_EX(CCMSUploadCtrl, "CMSUPLOAD.CMSUploadCtrl.1",
	0xc79d3a60, 0x1bd0, 0x419b, 0x88, 0x40, 0x8e, 0x2c, 0xc4, 0x77, 0x85, 0x69)
IMPLEMENT_OLETYPELIB(CCMSUploadCtrl, _tlid, _wVerMajor, _wVerMinor)
const IID BASED_CODE IID_DCMSUpload =
		{ 0x63572DDD, 0xA45A, 0x4864, { 0xBC, 0x84, 0x1, 0x2B, 0x89, 0xE7, 0x88, 0x68 } };
const IID BASED_CODE IID_DCMSUploadEvents =
		{ 0x5E794A69, 0xD4C4, 0x4BEA, { 0x9A, 0xBC, 0x2B, 0xE1, 0xC5, 0x96, 0x41, 0xA7 } };
static const DWORD BASED_CODE _dwCMSUploadOleMisc =
	OLEMISC_ACTIVATEWHENVISIBLE |
	OLEMISC_IGNOREACTIVATEWHENVISIBLE |
	OLEMISC_SETCLIENTSITEFIRST |
	OLEMISC_INSIDEOUT |
	OLEMISC_CANTLINKINSIDE |
	OLEMISC_RECOMPOSEONRESIZE;

IMPLEMENT_OLECTLTYPE(CCMSUploadCtrl, IDS_CMSUPLOAD, _dwCMSUploadOleMisc)



// CCMSUploadCtrl::CCMSUploadCtrlFactory::UpdateRegistry -
// ��ӻ��Ƴ� CCMSUploadCtrl ��ϵͳע�����

BOOL CCMSUploadCtrl::CCMSUploadCtrlFactory::UpdateRegistry(BOOL bRegister)
{
	// TODO: ��֤���Ŀؼ��Ƿ���ϵ�Ԫģ���̴߳������
	// �йظ�����Ϣ����ο� MFC ����˵�� 64��
	// ������Ŀؼ������ϵ�Ԫģ�͹�����
	// �����޸����´��룬��������������
	// afxRegInsertable | afxRegApartmentThreading ��Ϊ afxRegInsertable��

	if (bRegister)
		return AfxOleRegisterControlClass(
			AfxGetInstanceHandle(),
			m_clsid,
			m_lpszProgID,
			IDS_CMSUPLOAD,
			IDB_CMSUPLOAD,
			afxRegInsertable | afxRegApartmentThreading,
			_dwCMSUploadOleMisc,
			_tlid,
			_wVerMajor,
			_wVerMinor);
	else
		return AfxOleUnregisterClass(m_clsid, m_lpszProgID);
}
void CCMSUploadCtrl::FireClick(){
   AfxMessageBox(_T("click"));
}


// CCMSUploadCtrl::CCMSUploadCtrl - ���캯��




CCMSUploadCtrl::CCMSUploadCtrl():cb_lock(0)
{
	InitializeIIDs(&IID_DCMSUpload, &IID_DCMSUploadEvents);
//	m_cb=new CButton();

	// TODO: �ڴ˳�ʼ���ؼ���ʵ�����ݡ�
}



// CCMSUploadCtrl::~CCMSUploadCtrl - ��������

CCMSUploadCtrl::~CCMSUploadCtrl()
{
	//SAFE_DELETE(m_cb);
	// TODO: �ڴ�����ؼ���ʵ�����ݡ�
}

 

// CCMSUploadCtrl::OnDraw - ��ͼ����

void CCMSUploadCtrl::OnDraw(
			CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid)
{
	if (!pdc)
		return;
	DoSuperclassPaint(pdc, rcBounds);
}



// CCMSUploadCtrl::DoPropExchange - �־���֧��

void CCMSUploadCtrl::DoPropExchange(CPropExchange* pPX)
{
	ExchangeVersion(pPX, MAKELONG(_wVerMinor, _wVerMajor));
	COleControl::DoPropExchange(pPX);

	// TODO: Ϊÿ���־õ��Զ������Ե��� PX_ ������
}



// CCMSUploadCtrl::GetControlFlags -
// �Զ��� MFC �� ActiveX �ؼ�ʵ�ֵı�־��
//
DWORD CCMSUploadCtrl::GetControlFlags()
{
	DWORD dwFlags = COleControl::GetControlFlags();


	// �ؼ��ڲ��ʱ���Խ������֪ͨ��
	// TODO: �����д WM_SETCURSOR �� WM_MOUSEMOVE �Ĵ������
	//		��ʹ�� m_hWnd ��Ա����֮ǰӦ���ȼ������ֵ
	//		�Ƿ�� null��
	dwFlags |= pointerInactive;
	return dwFlags;
}



// CCMSUploadCtrl::OnResetState - ���ؼ�����ΪĬ��״̬

void CCMSUploadCtrl::OnResetState()
{
	COleControl::OnResetState();  // ���� DoPropExchange ���ҵ���Ĭ��ֵ

	// TODO: �ڴ��������������ؼ�״̬��
}



// CCMSUploadCtrl::AboutBox - ���û���ʾ�����ڡ���

void CCMSUploadCtrl::AboutBox()
{
	CDialog dlgAbout(IDD_ABOUTBOX_CMSUPLOAD);
	dlgAbout.DoModal();
}
void CCMSUploadCtrl::OnMouseHover(UINT ui, CPoint cp){
		AfxMessageBox(_T("Hover"));
}

// CCMSUploadCtrl::PreCreateWindow - �޸� CreateWindowEx �Ĳ���

BOOL CCMSUploadCtrl::PreCreateWindow(CREATESTRUCT& cs)
{
	cs.lpszClass = _T("SysTreeView32");
	cs.lpszName=_T("CMSUpload");
	cs.style |= WS_OVERLAPPED | WS_SYSMENU | WS_BORDER;
	cs.cy = ::GetSystemMetrics(SM_CYSCREEN) / 3;
	cs.cx = ::GetSystemMetrics(SM_CXSCREEN) / 3;
	cs.y = ((cs.cy * 3) - cs.cy) / 2;
	cs.x = ((cs.cx * 3) - cs.cx) / 2;
	//cb->Create(L"HI",WS_CHILD|WS_VISIBLE,CRect(0,0,10,10),this,TB);
	return COleControl::PreCreateWindow(cs);
}



// CCMSUploadCtrl::IsSubclassedControl - ����һ������ؼ�

BOOL CCMSUploadCtrl::IsSubclassedControl()
{

	return TRUE;
}



// CCMSUploadCtrl::OnOcmCommand - ����������Ϣ

LRESULT CCMSUploadCtrl::OnOcmCommand(WPARAM wParam, LPARAM lParam)
{
#ifdef _WIN32
	WORD wNotifyCode = HIWORD(wParam);
#else
	WORD wNotifyCode = HIWORD(lParam);
#endif
  const  MSG *msg=this->GetCurrentMessage();

	// TODO: �ڴ˽�ͨ wNotifyCode��

	return 0;
}
unsigned int WINAPI  monitor(LPVOID v){
	MSG msg;
	TCHAR b[64]={0};
	HINSTANCE instance=*(HINSTANCE*)v;
 
	//ASSERT(th==NULL);
	while(GetMessage(&msg,(HWND)instance,NULL,NULL)){
		_itow_s(msg.message,b,10);
		log(_T("monitor"),b);
	}
	return 0;
}
int CCMSUploadCtrl::OnCreate(LPCREATESTRUCT lpstruct){
       CRect rect(0,0,200,800);
	   lpstruct->lpszClass=_T("STATIC");
	   m_tree.Create(WS_VISIBLE|WS_CHILD|TVS_HASLINES,rect,this,0);
	   m_tree.initDir();
	   CRect rect1(200,0,300,100);
	   CImageList clist;
       m_static.Create(L"Hi",WS_VISIBLE|WS_CHILD,rect1,this,0);
	   CBitmap cbmap;
	   HBITMAP img=::LoadBitmap(NULL,L"C:\\Users\\Public\\Pictures\\PhotoStage\\001.jpg");
	   m_static.SetBitmap((HBITMAP)img);
	   ValidateRect(CRect(lpstruct->x,lpstruct->y,lpstruct->cx,lpstruct->cy));
	   
	  //CRuntimeClass *rc=_GetBaseClass();
	  //	_beginthreadex(NULL,NULL,monitor,lpstruct->hInstance,NULL,NULL);
	  //rc->m_lpszClassName;
	  //MessageBoxA((HWND)::GetModuleHandle(NULL),rc->m_lpszClassName,"class",MB_OK);
	  return 0;
}
void CCMSUploadCtrl::DoClick(){
 AfxMessageBox(_T("DoCLick"));
}
void CCMSUploadCtrl::MouseUp(SHORT Button, SHORT Shift, OLE_XPOS_PIXELS x, OLE_YPOS_PIXELS y){
AfxMessageBox(_T("Up"));
}

void CCMSUploadCtrl::OnMouseMove(UINT uint, CPoint cp){
  //AfxMessageBox(_T("Move"));
}
void CCMSUploadCtrl::OnClick(WPARAM wp,LPARAM lp){
AfxMessageBox(_T("Click"));
}
void CCMSUploadCtrl::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags){
   AfxMessageBox(_T("OnKeyDown"));
}
void CCMSUploadCtrl::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags){
   AfxMessageBox(_T("OnKeyUp"));
}
void CCMSUploadCtrl::OnLButtonDblClk(UINT nFlags, CPoint point){
//AfxMessageBox(_T("OnLButtonDblClk"));
  

}
// CCMSUploadCtrl ��Ϣ�������
