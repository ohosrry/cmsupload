// CMSInterfaceCtrl.cpp : CCMSInterfaceCtrl ActiveX 控件类的实现。

#define _CRT_DBG_MAP_ALLOC
#include "stdafx.h"
#include "CMSConstant.h"
#include "CMSInterface.h"
#include "CMSInterfaceCtrl.h"
#include "CMSInterfacePropPage.h"
#include <atlbase.h>
#include <atlcom.h>
#include "lib_cms.h"
#include <iostream>
#include <cstring>
#include <vector>
#include<direct.h>
#include <crtdbg.h>
#include <map>
#include <cstdio>
#include <cstdlib>
#include <json/json.h>
#include <json/writer.h>
#include <algorithm> // sort
#include <Mshtml.h>
#include "CMSTree.h"
using namespace std;
using namespace Json;
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
CComDispatchDriver call_back;
map<string,BSTR> strMap;
IStream*   pStream;
IWebBrowser2 *pweb2;
IMPLEMENT_DYNCREATE(CCMSInterfaceCtrl, COleControl)
// 消息映射
BEGIN_MESSAGE_MAP(CCMSInterfaceCtrl, COleControl)
	ON_MESSAGE(OCM_COMMAND, &CCMSInterfaceCtrl::OnOcmCommand)
	ON_OLEVERB(AFX_IDS_VERB_PROPERTIES, OnProperties)
	ON_WM_CREATE()
	ON_WM_WINDOWPOSCHANGED()


	ON_WM_ERASEBKGND()
	//ON_WM_PAINT()
END_MESSAGE_MAP()
// 调度映射
BEGIN_DISPATCH_MAP(CCMSInterfaceCtrl, COleControl)
	DISP_FUNCTION_ID(CCMSInterfaceCtrl, "doFtpUpload", DISPID_DO_FTP_UPLOAD, doFtpUpload, VT_BSTR, VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR)
	DISP_FUNCTION_ID(CCMSInterfaceCtrl, "doHttpUpload", DISPID_DO_HTTP_UPLOAD, doHttpUpload, VT_BSTR, VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR)
	DISP_FUNCTION_ID(CCMSInterfaceCtrl, "doOpenDialog", DISPID_DO_OPEN_FILE_DIALOG, doOpenDialog, VT_BSTR, VTS_BSTR)
	DISP_FUNCTION_ID(CCMSInterfaceCtrl, "doGetPathFiles", DISPID_DO_GET_PATH_FILES, doGetPathFiles, VT_BSTR, VTS_BSTR)
	DISP_FUNCTION_ID(CCMSInterfaceCtrl, "doGetDriveFiles", DISPID_DO_GET_DRIVE_FILES, doGetDriveFiles, VT_BSTR, VTS_NONE)
	DISP_PROPERTY_NOTIFY_ID(CCMSInterfaceCtrl, "TBstr", dispidTBstr, m_TBstr, OnTBstrChanged, VT_BSTR)
	DISP_FUNCTION_ID(CCMSInterfaceCtrl, "registerCallBack", dispidregisterCallBack, registerCallBack, VT_BSTR, VTS_DISPATCH)
	DISP_FUNCTION_ID(CCMSInterfaceCtrl, "CallJs", dispidCallJs, CallJs, VT_BSTR, VTS_BSTR)
END_DISPATCH_MAP()
// 事件映射
BEGIN_EVENT_MAP(CCMSInterfaceCtrl, COleControl)
	EVENT_STOCK_CLICK()
	EVENT_STOCK_DBLCLICK()
	EVENT_STOCK_ERROREVENT()
	EVENT_STOCK_KEYDOWN()
	EVENT_STOCK_KEYPRESS()
	EVENT_STOCK_KEYUP()
	EVENT_STOCK_MOUSEDOWN()
	EVENT_STOCK_MOUSEMOVE()
	EVENT_STOCK_MOUSEUP()
	EVENT_STOCK_READYSTATECHANGE()
END_EVENT_MAP()
// 属性页
// TODO: 按需要添加更多属性页。请记住增加计数!
BEGIN_PROPPAGEIDS(CCMSInterfaceCtrl, 1)
PROPPAGEID(CCMSInterfacePropPage::guid)
END_PROPPAGEIDS(CCMSInterfaceCtrl)
BEGIN_PROP_MAP(CCMSInterfaceCtrl)
	//PROP_DATA_ENTRY("ftpUrl", ftpUrl, VT_BSTR)
	//PROP_DATA_ENTRY("httpUrl", httpUrl, VT_BSTR)
	//PROP_DATA_ENTRY("ftpUser", ftpUser, VT_BSTR)
	//PROP_DATA_ENTRY("ftpPwd", ftpPwd, VT_BSTR)
	//PROP_DATA_ENTRY("httpUser", httpUser, VT_BSTR)
	//PROP_DATA_ENTRY("httpPwd", httpPwd, VT_BSTR)
END_PROP_MAP()
// 初始化类工厂和 guid
IMPLEMENT_OLECREATE_EX(CCMSInterfaceCtrl, "CMSINTERFACE.CMSInterfaceCtrl.1",
					   0xc3f95086, 0x97b7, 0x47e7, 0x95, 0xbd, 0xeb, 0x3d, 0x63, 0x45, 0xb2, 0xd1)
					   // 键入库 ID 和版本
					   IMPLEMENT_OLETYPELIB(CCMSInterfaceCtrl, _tlid, _wVerMajor, _wVerMinor)
					   // 接口 ID
					   const IID BASED_CODE IID_DCMSInterface =
{ 0x259F2DB9, 0x9280, 0x46E4, { 0xA1, 0xF4, 0x7E, 0xC1, 0x40, 0x5E, 0xBF, 0x71 } };
const IID BASED_CODE IID_DCMSInterfaceEvents =
{ 0xBF457155, 0xD9A3, 0x44D1, { 0x82, 0x9B, 0xD4, 0x7D, 0x1E, 0x9F, 0x1E, 0x88 } };
// 控件类型信息
static const DWORD BASED_CODE _dwCMSInterfaceOleMisc =
OLEMISC_SETCLIENTSITEFIRST |
OLEMISC_INSIDEOUT |
OLEMISC_CANTLINKINSIDE |
OLEMISC_RECOMPOSEONRESIZE;
IMPLEMENT_OLECTLTYPE(CCMSInterfaceCtrl, IDS_CMSINTERFACE, _dwCMSInterfaceOleMisc)
// CCMSInterfaceCtrl::CCMSInterfaceCtrlFactory::UpdateRegistry -
// 添加或移除 CCMSInterfaceCtrl 的系统注册表项
 CCMSInterfaceCtrl* CCMSInterfaceCtrl::thisCtr=NULL;
BOOL CCMSInterfaceCtrl::CCMSInterfaceCtrlFactory::UpdateRegistry(BOOL bRegister)
{
	// TODO: 验证您的控件是否符合单元模型线程处理规则。
	// 有关更多信息，请参考 MFC 技术说明 64。
	// 如果您的控件不符合单元模型规则，则
	// 必须修改如下代码，将第六个参数从
	// afxRegApartmentThreading 改为 0。
	if (bRegister)
		return AfxOleRegisterControlClass(
		AfxGetInstanceHandle(),
		m_clsid,
		m_lpszProgID,
		IDS_CMSINTERFACE,
		IDB_CMSINTERFACE,
		afxRegApartmentThreading,
		_dwCMSInterfaceOleMisc,
		_tlid,
		_wVerMajor,
		_wVerMinor);
	else
		return AfxOleUnregisterClass(m_clsid, m_lpszProgID);
}
// 授权字符串
static const TCHAR BASED_CODE _szLicFileName[] = _T("CMSInterface.lic");

static const WCHAR BASED_CODE _szLicString[] =
L"Copyright (c) 2012 ";

// CCMSInterfaceCtrl::CCMSInterfaceCtrlFactory::VerifyUserLicense -
// 检查是否存在用户许可证
//BOOL CCMSInterfaceCtrl::CCMSInterfaceCtrlFactory::VerifyUserLicense()
//{
//	return AfxVerifyLicFile(AfxGetInstanceHandle(), _szLicFileName,
//		_szLicString);
//}
// CCMSInterfaceCtrl::CCMSInterfaceCtrlFactory::GetLicenseKey -
// 返回运行时授权密钥
//BOOL CCMSInterfaceCtrl::CCMSInterfaceCtrlFactory::GetLicenseKey(DWORD dwReserved,
//	BSTR FAR* pbstrKey)
//{
//	if (pbstrKey == NULL)
//		return FALSE;
//	*pbstrKey = SysAllocString(_szLicString);
//	return (*pbstrKey != NULL);
//}
// CCMSInterfaceCtrl::CCMSInterfaceCtrl - 构造函数
CCMSInterfaceCtrl::CCMSInterfaceCtrl()
{
	InitializeIIDs(&IID_DCMSInterface, &IID_DCMSInterfaceEvents);
	CCMSInterfaceCtrl::thisCtr=this;
	// TODO: 在此初始化控件的实例数据。
}
// CCMSInterfaceCtrl::~CCMSInterfaceCtrl - 析构函数
CCMSInterfaceCtrl::~CCMSInterfaceCtrl()
{
	// TODO: 在此清理控件的实例数据。
}
// CCMSInterfaceCtrl::OnDraw - 绘图函数
void CCMSInterfaceCtrl::OnDraw(
							   CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid)
{
	if (!pdc)
		return;
	DoSuperclassPaint(pdc, rcBounds);
	if(m_formView.IsFrameWnd()){
		m_formView.MoveWindow(rcBounds,TRUE);
	}
	
}
// CCMSInterfaceCtrl::DoPropExchange - 持久性支持
void CCMSInterfaceCtrl::DoPropExchange(CPropExchange* pPX)
{
	ExchangeVersion(pPX, MAKELONG(_wVerMinor, _wVerMajor));
	COleControl::DoPropExchange(pPX);
	if (pPX->GetVersion() == (DWORD)MAKELONG(_wVerMinor, _wVerMajor))
	{
		//接受param 参数
		PX_String(pPX,_T("ftpUrl"),ftpUrl); 
		PX_String(pPX,_T("httpUrl"),httpUrl); 
		PX_String(pPX,_T("ftpUser"),ftpUser); 
		PX_String(pPX,_T("ftpPwd"),ftpPwd); 
		PX_String(pPX,_T("httpUser"),httpUser); 
		PX_String(pPX,_T("httpPwd"),httpPwd);
		PX_String(pPX,_T("callBackUrl"),callBackUrl); 
		PX_String(pPX,_T("uploadDir"),uploadDir); 
		PX_String(pPX,_T("brand_code"),brand_code); 
		PX_String(pPX,_T("goods_sn"),goods_sn); 
		//PX_String(pPX,_T("myproperty1"),m_property1);
	}
	// TODO: 为每个持久的自定义属性调用 PX_ 函数。
}
// CCMSInterfaceCtrl::OnResetState - 将控件重置为默认状态
void CCMSInterfaceCtrl::OnResetState()
{
	COleControl::OnResetState();  // 重置 DoPropExchange 中找到的默认值
	// TODO: 在此重置任意其他控件状态。
}
// CCMSInterfaceCtrl::PreCreateWindow - 修改 CreateWindowEx 的参数
BOOL CCMSInterfaceCtrl::PreCreateWindow(CREATESTRUCT& cs)
{
	cs.lpszClass = _T("STATIC");
	return COleControl::PreCreateWindow(cs);
}
// CCMSInterfaceCtrl::IsSubclassedControl - 这是一个子类控件
BOOL CCMSInterfaceCtrl::IsSubclassedControl()
{
	return TRUE;
}
// CCMSInterfaceCtrl::OnOcmCommand - 处理命令消息
LRESULT CCMSInterfaceCtrl::OnOcmCommand(WPARAM wParam, LPARAM lParam)
{
#ifdef _WIN32
	WORD wNotifyCode = HIWORD(wParam);
#else
	WORD wNotifyCode = HIWORD(lParam);
#endif
	return 0;
}
// CCMSInterfaceCtrl 消息处理程序
struct UploadStruct{
   char uploadUrl[128];
   char file_name[64];
   char new_name[64];
   char user[64];
   char pwd[64];
   char cb[64];
};
UINT AFX_CDECL _ftpUploadThread(LPVOID up){
	::CoInitializeEx(NULL,   COINIT_APARTMENTTHREADED);
	IWebBrowser2   * ppBrower;
	::CoGetInterfaceAndReleaseStream(pStream,   IID_IWebBrowser2,   (void**)&ppBrower); 
	UploadStruct* lup=NULL;
	lup=(UploadStruct*)up;
    INT ret=0;
    if(NULL==lup||NULL==ppBrower)
	{
		ret=1;
	}else{
		//char b[32]={0};
		//sprintf_s(b,"%d",strlen(lup->uploadUrl));
		//CMSBOX(b);
    //ret=_doFtpUpload(ppBrower,lup->uploadUrl,lup->file_name,lup->new_name,lup->user,lup->pwd,lup->cb);
	}
SAFE_DELETE(lup);

	return ret;
}

UINT AFX_CDECL CCMSInterfaceCtrl::_httpUploadThread(LPVOID up){
	UploadStruct *lup=NULL;
	INT ret=0;
   if(NULL==lup)
	{
		ret=1;
	}else{
		char b[32]={0};
		sprintf_s(b,"%d",strlen(lup->uploadUrl));
		CMSBOX(b);
		
		ret=_doHttpUpload(lup->uploadUrl,lup->file_name,lup->new_name,lup->user,lup->pwd,lup->cb);
	}
   SAFE_DELETE(lup);
	return ret;
}

BSTR CCMSInterfaceCtrl::doFtpUpload(BSTR file_name, BSTR new_name, BSTR user, BSTR pwd,BSTR cb)
{
	USES_CONVERSION;
	int ret;
    char *lftpUrl,*lfile_name=NULL,*lnew_name=NULL,*luser=NULL,*lpwd=NULL,*lcb=NULL;
	UploadStruct *upStruct=new UploadStruct;
    memset(upStruct,0,sizeof(UploadStruct));
	if(NULL==user)
	{
		user=ftpUser.AllocSysString();
	}
	if(NULL==pwd)
	{
		pwd=ftpPwd.AllocSysString();
	}
    
	if(L""!=ftpUrl){
		lfile_name=W2A(file_name);
		lnew_name=W2A(new_name);
		luser=W2A(user);
		lpwd=W2A(pwd);
		lcb=W2A(cb);
		
		lftpUrl=W2A(ftpUrl);
        memcpy(upStruct->uploadUrl,lftpUrl,strlen(lftpUrl));
        memcpy(upStruct->file_name,lfile_name,strlen(lfile_name));
		memcpy(upStruct->new_name,lnew_name,strlen(lnew_name));
		memcpy(upStruct->user,luser,strlen(luser));
		memcpy(upStruct->pwd,lpwd,strlen(lpwd));
		memcpy(upStruct->cb,lcb,strlen(lcb));
	    ret= _doFtpUpload(W2A(ftpUrl.AllocSysString()),W2A(file_name),W2A(new_name),W2A(user),W2A(pwd),W2A(cb));
	  // AfxBeginThread(_ftpUploadThread,upStruct,0,0,0,0);
	   //ret=_doFtpUpload(W2A(ftpUrl),W2A(file_name),W2A(new_name),W2A(user),W2A(pwd),W2A(cb));
	    ret=0;
	  }else{
		ret=1;
    	}
	char b[64]={0};
	_itoa_s(ret,b,64,10);
	CString retStr(b);
	SysFreeString(user);
	SysFreeString(pwd);
	return retStr.AllocSysString();
}
BSTR CCMSInterfaceCtrl::doHttpUpload( BSTR file_name, BSTR new_name, BSTR user, BSTR pwd,BSTR cb)
{   int ret;
	USES_CONVERSION;
	if(NULL==user)
	{
		user=ftpUser.AllocSysString();
	}
	if(NULL==pwd)
	{
		pwd=ftpPwd.AllocSysString();
	}
	if(L""!=httpUrl){
		ret= _doHttpUpload(W2A(httpUrl.AllocSysString()),W2A(file_name),W2A(new_name),W2A(user),W2A(pwd),W2A(cb));
	}else
	{
		ret=1;
	}
	char b[64]={0};
	_itoa_s(ret,b,64,10);
	CString retStr(b);
	SysFreeString(user);
	SysFreeString(pwd);
	return retStr.AllocSysString();
}
BSTR CCMSInterfaceCtrl::doOpenDialog(BSTR path)
{
	USES_CONVERSION;
	CString fileName;
	TCHAR filter[]=L"JPG Files (*.jpg)\0*.jpg\0JPEG Files (*.jpeg)\0*.jpg\0GIF Files (*.gif)\0*.gif\0PNG Files (*.png)\0*.png\0";
	const int c_cMaxFiles = 1024;
	const int c_cbBuffSize = (c_cMaxFiles * (MAX_PATH + 1)) + 1;
	CFileDialog cfd(TRUE);
	cfd.GetOFN().lpstrFile = fileName.GetBuffer(c_cbBuffSize);
	cfd.GetOFN().nMaxFile=c_cMaxFiles;
	cfd.GetOFN().Flags|=OFN_ALLOWMULTISELECT|OFN_FILEMUSTEXIST;
	cfd.GetOFN().lpstrFilter=filter;
	if(_file_exists(W2A(path))==0)
	{
		cfd.GetOFN().lpstrInitialDir=path;
	}
	cfd.DoModal();
	POSITION pos=cfd.GetStartPosition();
	CString res;
	while(NULL!=pos)
	{
		res.Append(cfd.GetNextPathName(pos));
		res.Append(L",");
	}
	int last=res.ReverseFind(L',');
	if(res[last]==L',')
	{
		res.SetAt(last,L'\0');
	}
	if(res!=L"")return SysAllocString(res.GetBuffer());
	return NULL;
}
BSTR CCMSInterfaceCtrl::doGetPathFiles( BSTR path_name)
{
	USES_CONVERSION;
	Value root;
	FastWriter fw;
	string retStr;
	CString pattern(path_name);
	pattern+=L"\\*.*";
	//CMSBOXW(pattern);
	Value images;
	int dir_index=0;
	int image_index=0;
	CString res;
	if(NULL!=path_name&&_file_exists(W2A(path_name))==0)
	{
		SetCurrentDirectory(path_name);
		CFileFind cff;
		BOOL found=cff.FindFile(pattern);
		while(found)
		{   
			found=cff.FindNextFile();
            //res+=L"  "+cff.GetFilePath();
			if(cff.IsDirectory()&&!cff.IsDots()){
				CString full_path=cff.GetFilePath();
				//full_path.Append(cff.GetFileName());
				if(!full_path.IsEmpty())
				{ 
				    //res+=L"--"+full_path+L"--";
                    char *file=W2A(full_path.AllocSysString());
					if(NULL!=file)
					{
						char buff[128]={0};
                         _itoa_s(dir_index++,buff,128,10);
						root[buff]=file;
					}
				}
			}
			if(cff.GetFileName().Find(L".jpg")!=-1||
				cff.GetFileName().Find(L".gif")!=-1||
				cff.GetFileName().Find(L".png")!=-1)
			{
				/*		  CMSBOX("image");
				return NULL;*/
				//CMSBOXW(cff.GetFilePath());
				char l_buff[128]={0};
				_itoa_s(image_index++,l_buff,128,10);
				images[l_buff]=W2A(cff.GetFilePath());
			}
		}
		cff.Close();
	}

	if(images.size()>=1)
	{
	  root["images"]=images;
	}
	retStr=fw.write(root);
	//CMSBOXW(res);
	if(retStr.length()>0)
	{
		return SysAllocString(A2W(retStr.c_str()));
	}
	return CString("1").AllocSysString();	
}
BSTR CCMSInterfaceCtrl::doGetDriveFiles()
{
	USES_CONVERSION;
	INT drive_current=0;
	ULONG uDriveMask=0;
	INT drive=1;
	INT last=0;
	Value root;
	Value images;
	Reader reader;
	FastWriter fw;
	string retStr;
	TCHAR g_szDrvMsg[] = _T("A:\\");
	static char drive_buff[_MAX_PATH]={0};
	drive_current = _getdrive();
	string drive_str;
	uDriveMask=_getdrives();
	if(uDriveMask==0){
		CMSBOXW(L"函数返回没有磁盘");
	}else{
		while(uDriveMask)
		{
			if(uDriveMask&1)
			{
				Value lv;
				Value image;
				Value lnone;
				char *path_files=NULL;
				path_files=W2A(doGetPathFiles(g_szDrvMsg));
				if(NULL!=path_files&&reader.parse(path_files,lv)==TRUE)
				{
					if(lv.isMember("images"))
				  {
					 Value::iterator it=lv["images"].begin();
					 
					 while(it!=lv["images"].end())
					 {   

						 images.append(*it);
						 ++it;
					 }
					 
				 }
					root[W2A(g_szDrvMsg)]=lv;
				}
			}
			++g_szDrvMsg[0];
			uDriveMask >>= 1;
		}
	}
	//for(;drive<=26;++drive)
	//{
	// if(!_chdrive(drive))
	// {
	//  if( _getdcwd( drive, drive_buff, _MAX_PATH ) != NULL ){
	//   CString  files=doGetPathFiles(A2W(drive_buff));
	//           // files.Replace(L"\\\\",L"\\");
	//   drive_str+=drive_buff;
	//   root[drive_buff]=W2A(files);
	//  }
	// }
	//}
	//_chdrive( drive_current );
	if(images.isArray()&&images.size()>=1)
	{
		root["images"]=images;
	}
	retStr=fw.write(root);
	CString cs(A2W(retStr.c_str()));
	//cs.Replace(L"\\\\",L"\\");
	//CMSBOXW(cs);
	//cs.Replace(L"\\n",L"");
	if(cs.GetLength()>0)
	{ 
		/*   CMSBOXW(cs);
		CMSBOX(drive_str.c_str());*/
		return cs.AllocSysString();
	}
	//if(GetLogicalDriveStrings(1024,drive_buff)!=0){
	//   CMSBOXW(drive_buff);
	//}
	return NULL;
}
void CCMSInterfaceCtrl::OnTBstrChanged(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: 在此添加属性处理程序代码

	SetModifiedFlag();
}

BSTR CCMSInterfaceCtrl::registerCallBack(IDispatch* dispatch)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	CString strResult;
	EXCEPINFO    exInfo;
	UINT err=0U;
	CComBSTR funname("TestFunction");
	DISPID dispid;
	HRESULT hr;
	hr=dispatch->GetIDsOfNames(IID_NULL,&funname,1,LOCALE_SYSTEM_DEFAULT,&dispid);
	if(FAILED(hr))
	{
		switch(hr) 
		{ 
		case   E_OUTOFMEMORY: 
			MessageBoxA(NULL, "E_OUTOFMEMORY ", "outputParam   Err ",0); 
			break; 
		case   DISP_E_UNKNOWNNAME: 
			MessageBoxA(NULL, "DISP_E_UNKNOWNNAME ", "outputParam   Err ",0); 
			break; 
		case   DISP_E_UNKNOWNLCID: 
			MessageBoxA(NULL, "DISP_E_UNKNOWNLCID ", "outputParam   Err ",0); 
			break; 
		} 
		return   NULL; 

	}
	//CMSBOX("HI");
	hr=dispatch->Invoke(dispid,IID_NULL,LOCALE_SYSTEM_DEFAULT,DISPATCH_METHOD,NULL,NULL,&exInfo,&err);
	if(S_OK == hr){       
	 
	}else{
      
	}

	// TODO: 在此添加调度处理程序代码

	return strResult.AllocSysString();
}

void CCMSInterfaceCtrl::OnSetClientSite()
{
	char error_buff[128]={0};
	try{
     IOleClientSite *psite=NULL;
	 psite=GetClientSite();
	 if(NULL==psite)
	 {
	    //sprintf_s(error_buff,"%s %d %d","GetClientSite FAILD",GetLastError(),psite);
		//CMSBOX(error_buff);
		return ;
	 }else{
		// sprintf_s(error_buff,"%s %d %d","GetClientSite OK",GetLastError(),psite);
		// CMSBOX(error_buff);
	 }
	 IServiceProvider *isp=NULL;
     HRESULT hr=psite->QueryInterface(IID_IServiceProvider, reinterpret_cast<void **>(&isp));
	 if(FAILED(hr))
	 {
		 //CMSBOX("psite->QueryInterface failed");
        return;
	 }else{
		 //sprintf_s(error_buff,"%s %d %d","psite->QueryInterface OK",GetLastError(),isp);
		 //CMSBOX(error_buff);
	 }
	 IServiceProvider *isp2=NULL;
	 hr=isp->QueryService(SID_STopLevelBrowser,IID_IServiceProvider,reinterpret_cast<void **>(&isp2));
	 isp->Release();
	 if(FAILED(hr))
	 {
		 //CMSBOX("isp->QueryService failed");
		 return;
	 }else{
		// sprintf_s(error_buff,"%s %d %d","isp->QueryService OK",GetLastError(),isp2);
		// CMSBOX(error_buff);
	 }
	 IWebBrowser2 *web2=NULL;
	 hr=isp2->QueryService(SID_SWebBrowserApp,IID_IWebBrowser2,reinterpret_cast<void **>(&web2));
	 if(FAILED(hr))
	 {
		// CMSBOX("isp2->QueryService failed");
		 return;
	 }else{
		 pweb2=web2;
		 ::CoMarshalInterThreadInterfaceInStream(IID_IWebBrowser2,web2,&pStream);
		// sprintf_s(error_buff,"%s %d %d","isp2->QueryService OK",GetLastError(),web2);
		// CMSBOX(error_buff);
	 }
  //   IHTMLDocument *doc=NULL;
	 //hr=web2->get_Document((IDispatch**)&doc);
	 //if(FAILED(hr))
	 //{
		// //CMSBOX("web2->get_Document failed");
		// return;
	 //}else{
		//// sprintf_s(error_buff,"%s %d %d","web2->get_Document OK",GetLastError(),doc);
		// //CMSBOX(error_buff);
	 //}
	 //IDispatch *script=NULL;
	 //hr=doc->get_Script(&script);
	 //if(FAILED(hr))
	 //{
		// //CMSBOX("doc->get_Script failed");
		// return;
	 //}else{
		// m_script=script;
		//// sprintf_s(error_buff,"%s %d %d","doc->get_Script OK",GetLastError(),script);
		//// CMSBOX(error_buff);
	 //}
	 //doc->Release();
  //   BSTR f_name=L"TestFunction";
	 //DISPID did;
	 //hr=script->GetIDsOfNames(IID_NULL,&f_name,1,LOCALE_SYSTEM_DEFAULT,&did);
	 //if(FAILED(hr))
	 //{
		//// CMSBOX("script->GetIDsOfNames failed");
		// return;
	 //}else{
		//// sprintf_s(error_buff,"%s %d %d","script->GetIDsOfNames OK",GetLastError(),did);
		//// CMSBOX(error_buff);
	 //}
	 //DISPPARAMS params={NULL,NULL,0,0};
	 //hr=script->Invoke(did,IID_NULL,0,DISPATCH_METHOD,&params,NULL,NULL,NULL);
  //   script->Release();
	 //if(FAILED(hr))
	 //{
		//// sprintf_s(error_buff,"%s %d %d %d","script->Invoke failed",GetLastError(),script,did);
		//// CMSBOX(error_buff);

		// return;
	 //}else{
		// //sprintf_s(error_buff,"%s %d %d","script->Invoke OK",GetLastError(),did);
		//// CMSBOX(error_buff);
	 //}
	}catch(exception &e)
	{

		CMSBOX(e.what());
	}
	
}
int CCMSInterfaceCtrl::_call_js(BSTR function_name,DISPPARAMS params,INT param_count)
{
	USES_CONVERSION;
	DISPID dispid;
	IDispatch *script=NULL;
	IDispatch *doc1=NULL;
	DISPPARAMS lpramas={NULL,NULL,0,0};
	IHTMLDocument2 *doc2=NULL;
	char error_buff[128]={0};
	HRESULT hr;
	INT ret=0;
	if(NULL==function_name)
	{
       CMSBOX("NO function name found");
	   ret=1;
	}
	if(NULL==pweb2){
      CMSBOX("web2 is null");
      ret=1;
	}
	
	hr=pweb2->get_Document((IDispatch**)&doc1);
	if(FAILED(hr))
	{
		CMSBOX("pweb2->get_Document failed");
		return 1;
	}else{
		 sprintf_s(error_buff,"%s %d %d","web2->get_Document OK",GetLastError(),doc1);
		// CMSBOX(error_buff);

	}
	hr=doc1->QueryInterface(IID_IHTMLDocument2,reinterpret_cast<void**>(&doc2));
	if(FAILED(hr))
	{
		CMSBOX("doc1->QueryInterface failed");
		return 1;
	}else{
		sprintf_s(error_buff,"%s %d %d","doc1->QueryInterface OK",GetLastError(),doc1);
		//CMSBOX(error_buff);

	}
	if(NULL!=doc2&&NULL!=doc1)
	{
		hr=doc2->get_Script((IDispatch**)&script);
		if(FAILED(hr))
		{
			CMSBOX("doc->get_Script failed");
			return 1;
		}else{
			 sprintf_s(error_buff,"%s %d %d","doc->get_Script OK",GetLastError(),script);
			 //CMSBOX(error_buff);
		}
		doc2->Release();
		doc1->Release();
	}
	if(NULL!=script)
	{
        hr=script->GetIDsOfNames(IID_NULL,&function_name,1,LOCALE_SYSTEM_DEFAULT,&dispid);
		if(FAILED(hr)){
           sprintf_s(error_buff,"no js function named %d found",W2A(function_name));
		   ret=1;
		}
		hr=script->Invoke(dispid,IID_NULL,0,DISPATCH_METHOD,&params,NULL,NULL,NULL);
		if(FAILED(hr))
		{
			sprintf_s(error_buff,"call js function %s failed",W2A(function_name));
			ret=1;
		}else{
			ret=0;
		}
	}else{
      CMSBOX("NO m_script");
	}
	if(ret)
	{
		CMSBOX(error_buff);
	}
    return ret;

}
BSTR CCMSInterfaceCtrl::CallJs(LPCTSTR function_name,DISPPARAMS params,INT params_count)
{
	USES_CONVERSION;
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	
	CString strResult;
    
	if(NULL!=function_name&&_call_js((BSTR)function_name,params,params_count)==0)
	{
       strResult=L"0";
	 //  CMSBOX("Call OK");
	}else{
       strResult=L"1";
	   // CMSBOX("Call FAILED");
	}
	
    OnSetClientSite();
	return strResult.AllocSysString();
}

 CCMSInterfaceCtrl* CCMSInterfaceCtrl::getInstance()
{
	if(NULL==thisCtr){
		CCMSInterfaceCtrl::thisCtr=new CCMSInterfaceCtrl;
	}
	return thisCtr;
}
 int CCMSInterfaceCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct){
  /*  lpCreateStruct->style=WS_BORDER;
	CRect c(0,0,200,400);
	if(tree.Create(WS_CHILD|WS_VISIBLE|TVS_HASLINES,c,this,0)==-1){
	 CMSBOX("tree create failed");
	}
	COLORREF crBkColor = ::GetSysColor(COLOR_3DFACE);
	CreateSolidBrush(crBkColor);*/
	 if(COleControl::OnCreate(lpCreateStruct)==-1)
	 {
		return -1;
	 }
     BOOL ret=m_formView.Create(IDD_FORMVIEW,this);
   //   if(ret!=0)
	  //{
   //    CMSBOX("m_formView create Success");
	  //}else if(ret==0)
	  //{
	  // CMSBOX("m_formView create Success");
	  //}
     return 0;
 }
 void CCMSInterfaceCtrl::OnWindowPosChanged(WINDOWPOS* lpwndpos)
 {
   //CMSBOX("OnWindowPosChanged");
   UpdateWindow();
 }
 void CCMSInterfaceCtrl::OnPaint()
 {
 //  CMSBOX("OnPaint");
	 CRect rc;
	 CPaintDC dc(this);
	 GetClientRect(rc);
     dc.FillSolidRect(rc,RGB(0,255,0));
 }
 BOOL CCMSInterfaceCtrl::OnSetObjectRects(LPCRECT lprcPosRect, LPCRECT lprcClipRect)
{
//	/*ASSERT(lprcPosRect != NULL);
//
//	 Remember the position rectangle.
//	m_rcPos = *lprcPosRect;
//
//	 Calculate complete rectangle, include the tracker if it is present.
//	CRect rectPos = m_rcPos;
//	if (m_bUIActive && m_pRectTracker != NULL)
//	{
//		 Save new clipping rectangle (for DestroyTracker).
//		if (lprcClipRect != NULL)
//			m_pRectTracker->m_rectClip = *lprcClipRect;
//
//		 Adjust tracker rectangle to new dimensions.
//		CRect rectTmp = rectPos;
//		rectTmp.OffsetRect(-rectTmp.left, -rectTmp.top);
//		m_pRectTracker->m_rect = rectTmp;
//
//		 Adjust the "true" rectangle to include handles/hatching.
//		UINT nHandleSize = m_pRectTracker->m_nHandleSize - 1;
//		rectPos.InflateRect(nHandleSize, nHandleSize);
//	}
//
//	 Now clip the rectangle as appropriate.
//	CRect rectClip;
//	MyGetClippingCoordinates(rectPos, lprcClipRect, rectClip, &m_ptOffset);
//
//	 Move the outer window first, and then move the inner window.
//
//	if (!m_bInPlaceSiteWndless)
//	{
//		CWnd* pWndOuter = GetOuterWindow();
//
//		BEGIN CHANGE.
//		if (pWndOuter != NULL)
//		{
//			static CRect oldClipRect(0, 0, 0, 0);
//			if (oldClipRect != rectClip)
//				::MoveWindow(pWndOuter->m_hWnd,
//				rectClip.left, rectClip.top,
//				rectClip.Width(), rectClip.Height(),
//				TRUE);
//			oldClipRect = rectClip;
//		}
//		END CHANGE.
//		if (pWndOuter != this)
//			MoveWindow(m_ptOffset.x, m_ptOffset.y,
//			rectPos.Width(), rectPos.Height());
//	}*/
//	//char b[64]={0};
//	//sprintf_s(b,"%d",GetLastError());
//	//CMSBOX(b);
	return TRUE;
}
 BOOL CCMSInterfaceCtrl::OnEraseBkgnd(CDC* pDC)
 {
	//COLORREF ref=0x000000;
    //CMSBOX("here");
	 COLORREF crBkColor = ::GetSysColor(COLOR_3DFACE);
	 pDC->SetBkColor(crBkColor);
	 return TRUE;
 }
 HBRUSH CCMSInterfaceCtrl::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
 {
     CBrush brush;
	 brush.CreateSolidBrush(RGB(0,255,0));
	 return CreateSolidBrush(RGB(0,255,0));
 }