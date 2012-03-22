// CMSFormView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CMSInterface.h"
#include "CMSFormView.h"
#include "lib_cms.h"
#include <afxcview.h>
#include "CMSUtils.h"
#include "json/json.h"
#include "json/reader.h"
#include "CMSInterfaceCtrl.h"
#include <atlimage.h>
#include <algorithm>
#include <functional>
#include "CPreview.h"
#include "CTools.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
using namespace Json;
using namespace std;
// CCMSFormView
char *getBaseName(const char* file,char *out_buff);
IMPLEMENT_DYNCREATE(CCMSFormView, CDialog)
CCriticalSection CCMSFormView::m_Section;
CCMSFormView::CCMSFormView()
	: CDialog(CCMSFormView::IDD),m_Pic_Id(0),m_bDraging(FALSE),m_Pic_Up_Id(0),m_Check_Lock(FALSE)
{
	//char buff[1024]={0};
	//char buff_decrypt[1024]={0};
	//int b_len,d_len;
 //passport_encrypt("mima123456","mbcms123456789",buff,&b_len);
 // passport_decrypt("B2sDPQtnVTRUYQYyAzFTNFFlXWFQZVc/D2U=","mbcms123456789",buff_decrypt,&d_len);
 //CMSBOX(buff);
 // CMSBOX(buff_decrypt);
}

CCMSFormView::~CCMSFormView()
{
	
	vector<CImage*>::iterator it=m_Image_Vector.begin();
	for (;it!=m_Image_Vector.end();++it)
	{
		if(NULL!=*it)
		{
            delete *it;
		}
	}
	vector<CBitmap*>::iterator it_bitmap=m_Bitmap_Vector.begin();
	while(it_bitmap!=m_Bitmap_Vector.end())
	{

		if(NULL!=*it_bitmap)
		{
			delete *it_bitmap;
		}
		++it_bitmap;
	}
	vector<INT*>::iterator it_pic=m_Pid_Vector.begin();
	while(it_pic!=m_Pid_Vector.end())
	{
		if(NULL!=*it_pic)
		{
			delete *it_pic;
		}
		++it_pic;
	}
	map<string,string*>::iterator it_map=m_Tree_Map.begin();
	while(it_map!=m_Tree_Map.end())
	{
		SAFE_DELETE(it_map->second);
		++it_map;
	}
}

void CCMSFormView::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCMSFormView) 
	DDX_Control(pDX, IDC_LIST_PIC, m_List_Pic);
	DDX_Control(pDX, IDC_LIST_UP, m_List_Up);
	DDX_Control(pDX, IDC_DIR, m_Tree);
	//}}AFX_DATA_MAP 
	//UpdateData(TRUE);
	DDX_Control(pDX, IDC_BUTTON_UP, m_Upload_Button);
	//DDX_Control(pDX, IDC_CHECK_ALL, m_Check_All);
}

void CCMSFormView::PostNcDestroy()
{
	if(IsWindow(m_hWnd))
	{
      DestroyWindow();
	}
}


BEGIN_MESSAGE_MAP(CCMSFormView, CDialog)
	ON_WM_CREATE()
	ON_NOTIFY(NM_CLICK, IDC_DIR, &CCMSFormView::OnNMClickDir)
	ON_NOTIFY(TVN_SELCHANGED, IDC_DIR, &CCMSFormView::OnTvnSelchangedDir)
	ON_WM_SIZE()
	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
	ON_NOTIFY(LVN_BEGINDRAG, IDC_LIST_PIC, &CCMSFormView::OnLvnBegindragListPic)
	ON_WM_MOUSEMOVE()
	ON_WM_MBUTTONUP()
	ON_WM_LBUTTONUP()
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_PIC, &CCMSFormView::OnNMDblclkListPic)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_UP, &CCMSFormView::OnNMDblclkListUp)
	ON_BN_CLICKED(IDC_CHECK_ALL, &CCMSFormView::OnBnClickedCheckAll)
	ON_BN_CLICKED(IDC_BUTTON_UP, &CCMSFormView::OnBnClickedButtonUp)
	ON_WM_MBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_PREVIEW,&CCMSFormView::OnPreview)
	ON_NOTIFY(NM_RCLICK, IDC_LIST_UP, &CCMSFormView::OnNMRClickListUp)
	ON_NOTIFY(NM_RCLICK, IDC_LIST_PIC, &CCMSFormView::OnNMRClickListPic)
END_MESSAGE_MAP()


// CCMSFormView ���

#ifdef _DEBUG
void CCMSFormView::AssertValid() const
{
	//CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CCMSFormView::Dump(CDumpContext& dc) const
{
	//CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CCMSFormView ��Ϣ�������

int CCMSFormView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{

	return 0;
}

void CCMSFormView::OnNMClickDir(NMHDR *pNMHDR, LRESULT *pResult)
{
	*pResult = 0;
}
BOOL CCMSFormView::OnInitDialog(){
		USES_CONVERSION;
	CDialog::OnInitDialog();
	m_Menu.LoadMenu(IDR_MENU);
	//m_Menu.CreateMenu();
	m_brush.CreateSolidBrush(RGB(0xFa,0xFa,0xFa));
	m_List_Pic.SetBkColor(RGB(0xFa,0xFa,0xFa));
	m_List_Up.SetBkColor(RGB(0xFa,0xFa,0xFa));
	//m_Tree.SetBkColor(RGB(0,0,0));
	CString cs=CCMSUtils::doGetDriveFiles();
	CBitmap bmp;
	if (!bmp.LoadBitmap(IDB_FILE_VIEW_24))
	{
		TRACE(_T("�޷�����λͼ: %x\n"),IDB_FILE_VIEW_24);
		ASSERT(FALSE);
		return FALSE;
	}
	BITMAP bmpObj;
	bmp.GetBitmap(&bmpObj);
	UINT nFlags = ILC_MASK;
	nFlags |=  ILC_COLOR24;
	m_Image_List.Create(16, bmpObj.bmHeight, nFlags, 0, 0);
	m_Image_List.Add(&bmp,RGB(255,0,255));
	//m_Image_List.Create(IDB_FILE_VIEW_24,16,0,RGB(255,0,255));
	m_List_Pic.SetExtendedStyle(m_List_Pic.GetExtendedStyle()|LVS_EX_GRIDLINES);
    //m_List_Up.SetExtendedStyle(m_List_Up.GetExtendedStyle()|LVS_EX_ONECLICKACTIVATE |LVS_EX_TWOCLICKACTIVATE );
	//m_List_Up.SetExtendedStyle(m_List_Pic.GetExtendedStyle()|LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES|LVS_EX_SUBITEMIMAGES);
	CBitmap bitmap;
	//bitmap.LoadBitmap(IDB_BITMAP_HOME);
	m_Tree.SetImageList(&m_Image_List,TVSIL_NORMAL);
	Reader fr;
	Value paths;
	FastWriter fw;
	HTREEITEM root=m_Tree.InsertItem(L"�ҵĵ���");

	if(fr.parse(W2A(cs),paths))
	{
		if(paths.isObject()&&paths.size()>0){
			Value::iterator it=paths.begin();
			while(it!=paths.end())
			{
				HTREEITEM l_root;
				if(strcmp(it.memberName(),"images")!=0&&strncmp(it.memberName(),".",1)!=0)
				{  
					char base_buff[255]={0};
				    getBaseName(it.memberName(),base_buff);
                    string l_s(base_buff);
                    string *node_str=new string(it.memberName());
					l_root=m_Tree.InsertItem(A2W(it.memberName()),root);
				    m_Tree.SetItemData(l_root,(DWORD_PTR)node_str);
					m_Tree_Map[it.memberName()]=node_str;

				}else{
					it++;
					continue;
				}
				if((*it).isObject()&&(*it).size()>0){
					Value::iterator l_it=(*it).begin();
					for (;l_it!=(*it).end();++l_it)
					{
						if((*l_it).isString()&&strncmp((*l_it).asCString(),".",1)!=0){
							char base_buff[255]={0};
							getBaseName((*l_it).asCString(),base_buff);
							string l_s(base_buff);
							string *node_str=new string((*l_it).asCString());
							//l_root=m_Tree.InsertItem(A2W(l_s.c_str()),root);
							HTREEITEM lroot=m_Tree.InsertItem(A2W(l_s.c_str()),0,0,l_root);
							m_Tree.SetItemData(lroot,(DWORD_PTR)node_str);
							m_Tree_Map[it.memberName()]=node_str;

						}
					}
				}
				it++;
			}
		} 
	}
	return TRUE;
}
void CCMSFormView::OnTvnSelchangedDir(NMHDR *pNMHDR, LRESULT *pResult)
{
	USES_CONVERSION;
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	CString cs;
    Reader fr;
	Value paths;
	FastWriter fw;
 	HTREEITEM root=m_Tree.GetSelectedItem();
	string *p=(string*)m_Tree.GetItemData(root);
	if(NULL==p)
	{
		return;
	}
	cs= CCMSUtils::doGetPathFiles(A2W(p->c_str()));
    //cs.Replace(L'\\','/');

   if(fr.parse(W2A(cs),paths))
   {
	   if(paths.isObject()&&paths.size()>0)
	   {
		 
		   if(m_Tree.ItemHasChildren(root))
		   {
		     //return;
		   }
		   Value::iterator it=paths.begin();
		   for(;it!=paths.end();++it)
		   {
              if((*it).isString())
			  {
				  TVITEM tv={0};
				  tv.pszText=A2W((*it).asCString());
				 if(!m_Tree.GetItem(&tv)&&strncmp((*it).asCString(),".",1)!=0)
				 {
					 char base_buff[255]={0};
					 getBaseName((*it).asCString(),base_buff);
					 string l_s(base_buff);
					 string *node_str=new string((*it).asCString());
					 HTREEITEM lroot=m_Tree.InsertItem(A2W(l_s.c_str()),0,0,root);
					 m_Tree.SetItemData(lroot,(DWORD_PTR)node_str);
					 m_Tree_Map[it.memberName()]=node_str;
				 }
			  }
		   }
	   }
	   //if(paths.isMember("images"))
	   //{
    //     
	   //}
	   // CMSBOXW(cs);
	   if(paths.isMember("images")&&paths["images"].isObject()&&paths["images"].size()>0)
	   {
		   m_List_Pic.DeleteAllItems();
		   Value::iterator it=paths["images"].begin();
		   m_Image_Pic.DeleteImageList();
           if(!m_Image_Pic.Create(64,64,ILC_COLOR32|ILC_MASK,0,0))
		   {
              CMSBOX("m_Image_List.Create");
		   }
		   //m_Image_Pic.Add(AfxGetApp()->LoadIcon(IDR_JPG1));
           m_List_Pic.SetImageList(&m_Image_Pic,LVSIL_NORMAL );
		   m_List_Up.SetImageList(&m_Image_Pic,LVSIL_NORMAL);
		   m_Pic_Id=0;
		   for (;it!=paths["images"].end();++it)
		   {
			   Value lv=*it;
			   if(lv.isString()&&_file_exists(lv.asCString())==0)
			   {
                  CImage image;//=new CImage();
				  CImage smallImage;
				  BOOL retCreate= smallImage.Create(64,64,32,BI_RGB);
				  if(!retCreate)
				  {
					  CMSBOX("smallImage.Create failed");
				  }
				  HRESULT hr=image.Load(A2W(lv.asCString()));
				  
				  if(FAILED(hr))
				  {
					  CMSBOX("image->Load failed");
					  return;
				  }
				  INT lwidth= image.GetWidth();
                  INT lheight=image.GetHeight();
				  HDC hdc=smallImage.GetDC();
				  SetStretchBltMode(hdc,HALFTONE|BLACKONWHITE);
				  BOOL drawRet=FALSE;
                  if(smallImage.IsTransparencySupported())
				  {
					drawRet=image.TransparentBlt(hdc,0,0,64,64,0,0,lwidth,lheight,CLRBREAK);
				  }
				  smallImage.ReleaseDC();
				  if(!drawRet)
				  {
					CMSBOX("image.Draw failed");
				  }
				  HBITMAP hbitmap=smallImage.Detach();
                  CBitmap bmp;//=new CBitmap();
				  if(!bmp.Attach(hbitmap))
				  {
					CMSBOX("bmp->Attach failed");
					return;
				  }
				  m_Image_Pic.Add(&bmp, RGB(255, 255, 255));
                  LVFINDINFO lvFindInfo;
				  lvFindInfo.psz=A2W(lv.asCString());
				  lvFindInfo.flags=LVFI_STRING;
				  if(m_List_Pic.FindItem(&lvFindInfo)==-1){
					  m_List_Pic.InsertItem(m_Pic_Id,A2W(lv.asCString()),m_Pic_Id);
					  ++m_Pic_Id;
				  }else
				  {
				  }
			   }
		   }
	   }else{
         m_List_Pic.DeleteAllItems();
	   }
   }else{
	  // m_List_Pic.DeleteAllItems();
   }

	*pResult = 0;
}

void CCMSFormView::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);
}

void CCMSFormView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
}

HBRUSH CCMSFormView::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
   return (HBRUSH)m_brush.GetSafeHandle();
}

void CCMSFormView::OnLvnBegindragListPic(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	CPoint ptItem,ptAction,ptImage;
	CPoint first,last,bounds;
	NM_LISTVIEW* plist_view=(NM_LISTVIEW*)pNMHDR;
	POSITION pos;
	BOOL next=TRUE,b_first=TRUE;
	ASSERT(!m_bDraging);
	m_bDraging=TRUE;
	pos=m_List_Pic.GetFirstSelectedItemPosition();
	while(pos)
	{
		INT l_index=m_List_Pic.GetNextSelectedItem(pos);
		if(b_first)
		{
			m_List_Pic.GetItemPosition(l_index,&first);
			b_first=FALSE;
		}
        if(NULL==pos)
		{
           m_List_Pic.GetItemPosition(l_index,&last);
		}
	} 
	pos=m_List_Pic.GetFirstSelectedItemPosition();
	bounds=last-first;
	m_Big_Drag.DeleteImageList();
	m_Big_Drag.Create(bounds.x+64,bounds.y+64,ILC_COLOR32|ILC_MASK,1,1);
	m_Big_Drag_Image.Create(bounds.x+64,bounds.y+64,32,BI_RGB);
	while(pos)
	{
	     ST_DRAG l_st_drag;
         INT select_item_index=m_List_Pic.GetNextSelectedItem(pos);
	     m_Selected_Index.push_back(select_item_index);
	     l_st_drag.m_drag_index=select_item_index;
	     l_st_drag.m_String=m_List_Pic.GetItemText(select_item_index,0);
	     m_Item_Drag=plist_view->iItem;
	     CImageList *l_drag;
	     l_st_drag.m_pt_action=plist_view->ptAction;
	     m_List_Pic.GetItemPosition(select_item_index,&l_st_drag.m_pt_action);
	     m_DragItemString=m_List_Pic.GetItemText(plist_view->iItem,0);
	     l_st_drag.m_pt_action=plist_view->ptAction;
	     m_List_Pic.GetItemPosition(select_item_index,&l_st_drag.m_pt_item);
	     m_List_Pic.GetOrigin(&l_st_drag.m_pt_origin);
	     l_drag=m_List_Pic.CreateDragImage(select_item_index,&l_st_drag.m_pt_image);
		 CString item_String=m_List_Pic.GetItemText(select_item_index,0);
		 CImage l_image;
		 if(item_String!=L"")
		 {
			  HRESULT hr=l_image.Load(item_String);

			  if(SUCCEEDED(hr))
			  {
				 HDC hdc=m_Big_Drag_Image.GetDC();
				 CPoint cp(l_st_drag.m_pt_item-first);
				 l_image.TransparentBlt(hdc,cp.x,cp.y,64,64,1);
				 m_Big_Drag_Image.ReleaseDC();
			  }
		 }
	     l_st_drag.m_image=l_drag;
         m_St_Drag.push_back(l_st_drag);
	   
	}
	HBITMAP bitmap=m_Big_Drag_Image.Detach();
	CBitmap bmp;
	bmp.Attach(bitmap);
	m_Big_Drag.Add(&bmp,RGB(255,255,255));
    m_Big_Drag.BeginDrag(0,CPoint(0,0));
    m_Big_Drag.DragEnter(this,CPoint(0,0));
	SetCapture();
	CRect rect;
	GetClientRect(&rect);
	ClientToScreen(&rect);
	ClipCursor(&rect);
	*pResult = 0;
}

void CCMSFormView::OnMouseMove(UINT nFlags, CPoint point)
{
    if(m_bDraging)
	{
		ASSERT(m_Drag_Image!=NULL);
        m_Big_Drag.DragMove(point);
	}
	CDialog::OnMouseMove(nFlags, point);
}

void CCMSFormView::OnMButtonUp(UINT nFlags, CPoint point)
{
   if(m_bDraging)
   {
    ASSERT(m_Drag_Image!=NULL);
	m_Drag_Image->DragLeave(this);
    m_Drag_Image->EndDrag();
	SAFE_DELETE(m_Drag_Image);
	ReleaseCapture();
	m_bDraging=FALSE;
	Invalidate();
	ClipCursor(NULL);
   }
	CDialog::OnMButtonUp(nFlags, point);
}

void CCMSFormView::OnLButtonUp(UINT nFlags, CPoint point)
{
	if(m_bDraging)
	{
		ASSERT(m_Drag_Image!=NULL);
		m_Drag_Image->DragLeave(this);
		m_Drag_Image->EndDrag();
        LVHITTESTINFO lvHitInfo;
		lvHitInfo.pt=point;
		INT res;
		res=m_List_Pic.HitTest(&lvHitInfo);
		CRect rect;
		m_List_Up.GetWindowRect(&rect);
		ClientToScreen(&rect);
		ClientToScreen(&point);
		if(rect.PtInRect(point))
		{
				m_List_Up.SetImageList(&m_Image_Pic,LVSIL_NORMAL);
				vector<ST_DRAG>::iterator it=m_St_Drag.begin();
				while(it!=m_St_Drag.end())
				{
					LVFINDINFO lvInfo;
					lvInfo.psz=(*it).m_String;
					lvInfo.flags=LVFI_STRING;
					if(m_List_Up.FindItem(&lvInfo)==-1)
					{
					m_List_Up.InsertItem(m_Pic_Up_Id,(*it).m_String,(*it).m_drag_index);
					m_Pic_Up_Id++;
			        }
                    SAFE_DELETE((*it).m_image);
					++it;
				}
				m_St_Drag.clear();
		}
		vector<ST_DRAG>::iterator it_st=m_St_Drag.begin();
		while(it_st!=m_St_Drag.end())
		{
			SAFE_DELETE((*it_st).m_image);
			++it_st;
			//return ;
		}
		m_St_Drag.clear();
		vector<CImageList*>::iterator it=m_Drag_Vector.begin();
		while(it!=m_Drag_Vector.end())
		{
		    SAFE_DELETE(*it);
			++it;
			//return ;
		}
		m_Drag_Vector.clear();
		ReleaseCapture();
		m_bDraging=FALSE;
		Invalidate();
		ClipCursor(NULL);
	}
	CDialog::OnLButtonUp(nFlags, point);
}

void CCMSFormView::OnNMDblclkListPic(NMHDR *pNMHDR, LRESULT *pResult)
{
	CString cs;
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
    cs=m_List_Pic.GetItemText(pNMItemActivate->iItem,0);

//	m_List_Up.SetImageList(&m_Image_Pic,LVSIL_NORMAL);
	LVFINDINFO lvInfo;
	lvInfo.psz=cs;
	lvInfo.flags=LVFI_STRING;
	INT index=m_List_Up.HitTest(pNMItemActivate->ptAction);
	//CMSBOXW(cs);
	if(m_List_Up.FindItem(&lvInfo)==-1)
	{
		m_List_Up.InsertItem(m_Pic_Up_Id,cs,pNMItemActivate->iItem);
		m_Pic_Up_Id++;
	}
    //INT *pid=(INT*)m_List_Up.GetItemData(pNMItemActivate->iItem);
	//cs.Format(L"%d %d",pNMItemActivate->iItem,pNMItemActivate->iSubItem);
	//CMSBOXW(cs);
    //CMSBOXW(cs);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
}

void CCMSFormView::OnNMDblclkListUp(NMHDR *pNMHDR, LRESULT *pResult)
{
	USES_CONVERSION;
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	CString cs;
	cs=m_List_Up.GetItemText(pNMItemActivate->iItem,0);
	LVFINDINFO lvfind={0};
	lvfind.psz=cs.AllocSysString();
	INT find_index=m_List_Up.FindItem(&lvfind);
	if(find_index>=0)
	{
       m_List_Up.DeleteItem(find_index);
	}
    

 //   if(!cs.IsEmpty()&&_file_exists(W2A(cs))==0)
	//{
 //       
	//	CString upload_Path=CCMSInterfaceCtrl::getInstance()->uploadDir;
	//	CFile cf(cs,CFile::modeRead);
 //       upload_Path+=L"/"+cf.GetFileName();
	//	upload_Path+=L"up.jpg";
	//	CMSBOXW(upload_Path);
	//	return;
	//	CString ftpUrl=CCMSInterfaceCtrl::getInstance()->ftpUrl;
	//	CString ftpUser=CCMSInterfaceCtrl::getInstance()->ftpUser;
	//	CString ftpPwd=CCMSInterfaceCtrl::getInstance()->ftpPwd;
	//	char base_name_buff[255]={0};
	//	char *filename=basename(W2A(cs));
	//	SYSTEMTIME systime;
	//	::GetSystemTime(&systime);
	//	CTime ct(systime);
	//	CString destDir=ct.Format("%Y/%m/%d/");
	//	memcpy(base_name_buff,filename,strlen(filename));
	//	upload_Path+=destDir+A2W(base_name_buff);
	//	
	//	CMSBOXW(upload_Path);
	//	upload_Path+=L"up.jpg";
	//	return;
	//	CMSBOXW(ftpUser);
	//	INT ret=_doFtpUpload(W2A(ftpUrl.AllocSysString()),
	//		W2A(cs.AllocSysString()),
	//		W2A(upload_Path.AllocSysString()),
	//		W2A(ftpUser.AllocSysString()),
	//		W2A(ftpPwd.AllocSysString())
	//		);
	//	if(ret==0)
	//	{
	//		char *buff=new char[102400];
	//		Value root;
	//		Value values;
	//		FastWriter fw;
	//		char tmp[255]={0};
	//		sprintf_s(tmp,32,"1");
	//		getBaseName(W2A(cs.AllocSysString()),tmp);
	//		values[tmp]=W2A(upload_Path.AllocSysString());
	//		root["uploaded_files"]=values;
	//		string param=fw.write(values);
	//		string callBackUrl=W2A(CCMSInterfaceCtrl::getInstance()->callBackUrl);
 //           callBackUrl.append("?files="+param);
	//	    ret=_doHttpGet(callBackUrl.c_str(),buff);
 //           if(ret==0)
	//		{ 
 //               CMSBOXW(A2W(buff));
	//			CMSBOXW(cs);
	//			LVFINDINFO lvinfo={0};
	//			lvinfo.psz=cs.AllocSysString();
	//			INT fixItemIndex=m_List_Up.FindItem(&lvinfo);
	//			if(fixItemIndex>=0){
	//				m_List_Up.DeleteItem(fixItemIndex);

	//			}
	//		}
	//		SAFE_DELETE(buff);
	//	}
	//}
	*pResult = 0;
}



void CCMSFormView::OnBnClickedCheckAll()
{

	  INT i=0,count=m_List_Up.GetItemCount();
      BOOL b_check=FALSE;
	  for(;i<count;++i)
	  {
		LVITEMW lvw;
		lvw.state=LVIS_SELECTED;
		if(!m_Check_Lock){
			m_List_Up.SetItemState(i,LVIS_SELECTED,LVIS_SELECTED);
			b_check=TRUE;
		}else{
            m_List_Up.SetItemState(i,0,LVIS_SELECTED);
		}
	  }
	  if(b_check){
		  m_Check_Lock=TRUE;
	  }else{
		  m_Check_Lock=FALSE;
	  }
	  m_List_Up.SetFocus();

}
char *getBaseName(const char* file,char *out_buff){

    size_t last_slash_pos,last_dot_pos;
	string str(file);
	string base_name;
	last_dot_pos=str.find('.');
    last_slash_pos=str.find_last_of('\\');
    if(last_slash_pos==-1)
	{

		last_slash_pos=str.find_last_of('/');
	}
	char t[64]={0};
	//sprintf_s(t,64,"last_slash_pos=%d last_dot_pos-last_slash_pos=%d",last_slash_pos,last_dot_pos-last_slash_pos);
	//CMSBOX(t);
	if(last_dot_pos==-1)
	{
      base_name= str.substr(last_slash_pos+1,str.size()-last_slash_pos-1);
	}else{
	  base_name= str.substr(last_slash_pos+1,last_dot_pos-last_slash_pos-1);
	}
   // base_name.copy(out_buff,base_name.size());
	//CMSBOX(base_name.c_str());
	strcpy_s(out_buff,255,base_name.c_str());
	return out_buff;
}
UINT CCMSFormView::UploadThread(LPVOID lp){
	USES_CONVERSION;
	ST_THREAD_PARAM *param=(ST_THREAD_PARAM*)lp;

	if(NULL==param)
	{
		CMSBOX("wrong param");
		return 1UL;
	}
	
	char buf[255]={0};
	CString ftpUrl=CCMSInterfaceCtrl::getInstance()->ftpUrl;
	CString ftpUser=CCMSInterfaceCtrl::getInstance()->ftpUser;
	CString ftpPwd=CCMSInterfaceCtrl::getInstance()->ftpPwd;
	CString uploadDir=CCMSInterfaceCtrl::getInstance()->uploadDir;
	SYSTEMTIME systime;
	::GetSystemTime(&systime);
	CTime ct(systime);
	CString destDir=ct.Format("%Y/%m/%d/");
    CString uploadName=uploadDir+destDir;
	CCMSFormView * pMain=param->m_Main;
	INT i=param->count;
    char* file_name=W2A(pMain->m_List_Up.GetItemText(i,0));
    strcpy_s(buf,255,file_name);
    char *file_base_name=basename(buf);
    if(NULL==file_base_name)
	{
		CMSBOX("no base name");
	}
	uploadName+=A2W(file_base_name);
	//CMSBOXW(uploadName);
	//return 0UL;
	m_Section.Lock();
    if(0==_doFtpUpload(W2A(ftpUrl.AllocSysString()),buf,W2A(uploadName.AllocSysString()),W2A(ftpUser.AllocSysString()),W2A(ftpPwd.AllocSysString())))
	{
	
      //CString msg;
	  //msg.Format(L"%s �ϴ��ɹ�",A2W(file_name));
	 // CMSBOXW(msg);
	  LVFINDINFO lvinfo={0};
	  lvinfo.psz=A2W(buf);
	  INT fixItemIndex=pMain->m_List_Up.FindItem(&lvinfo);
	  if(fixItemIndex>=0){
		pMain->m_List_Up.DeleteItem(fixItemIndex);
	  }
	  char base_name[255]={0};
	  getBaseName(buf,base_name);
      pMain->m_Up_Map[base_name]=buf;
	  CWinThread *theThread=AfxGetThread();
	  vector<CWinThread*>::iterator it;
	  it=find(pMain->m_Up_Thread.begin(),pMain->m_Up_Thread.end(),theThread);
	  if(it!=pMain->m_Up_Thread.end())
	  {
		pMain->m_Up_Thread.erase(it);
	  }
	  CString css;
	  css.Format(L"%d",pMain->m_Up_Thread.size());
	  size_t size=pMain->m_Up_Thread.size();
	  //if(size==0)
	//  {
		  Value values;
		  FastWriter fw;
		  //map<string,string>::iterator it=pMain->m_Up_Map.begin();
		  //while(it!=pMain->m_Up_Map.end())
		  //{
		  //  values[it->first.c_str()]=it->second.c_str();
    //        ++it;
		  //}
		  values[base_name]=W2A(uploadName.AllocSysString());
		  string upload_url=W2A(CCMSInterfaceCtrl::getInstance()->callBackUrl);
		  string param=fw.write(values);
		  //param.replace('\\','/');
		  param=ctool::URLEncode(param);
		  upload_url.append("?files="+param);
		  //CMSBOX(upload_url.c_str());
		  char *http_buff=new char[102400];
		  INT ret=_doHttpGet(upload_url.c_str(),http_buff);
		  if(ret==0)
		  {
			 // CMSBOX(http_buff);
		  }
          SAFE_DELETE(http_buff);
	 // }
	//  CMSBOXW(css);

	}
	m_Section.Unlock();
	//SAFE_DELETE(pMain);
	SAFE_DELETE(param);
	return 0UL;
}


void CCMSFormView::OnBnClickedButtonUp()
{
	char buff[64]={0};
	INT i=0,count=m_List_Up.GetSelectedCount();
	if(count==0)
	{
		//CString ccs(NO_FILE_SELECT);
		
		::MessageBox(NULL,L"û��ѡ���ļ�",L"û��ѡ���ļ�",MB_OK);
	}
    for(;i<count;++i)
	{
		ST_THREAD_PARAM* st_param=new ST_THREAD_PARAM();
        st_param->m_Main=this;
		st_param->count=i;
		CWinThread* theThread=AfxBeginThread(&CCMSFormView::UploadThread,st_param,0,0,NULL,NULL);  
        m_Up_Thread.push_back(theThread);
		//return;
	}
 //   sprintf_s(buff,"%d",count);
	//CMSBOX(buff);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}

void CCMSFormView::OnMButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
    if(MK_RBUTTON==nFlags)
	{
     m_Menu.TrackPopupMenu(nFlags,point.x,point.y,this);

	}
	CDialog::OnMButtonDown(nFlags, point);
}

void CCMSFormView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if(MK_RBUTTON==nFlags)
	{
		//m_Menu.TrackPopupMenu(TPM_CENTERALIGN,point.x,point.y,this);
       CMenu * l_menu=m_Menu.GetSubMenu(0);
	  // CString cs;
	  // cs.Format(L"%d",m_Menu.GetMenuItemCount());
	  // CMSBOXW(cs);
        CRect cr;
	    GetWindowRect(&cr);
		//ClientToScreen(&point);
		 CString cs;
		 cs.Format(L"%d %d %d %d",cr.left,cr.right,cr.top,cr.bottom);
		 //CMSBOXW(cs);
	   if(l_menu){
		l_menu->TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON,point.x+cr.left,cr.top+point.y,this);
	   }
	   
	}
	CDialog::OnRButtonDown(nFlags, point);
}

void CCMSFormView::OnContextMenu(CWnd* pWnd, CPoint point)
{

	//CMSBOX("HERE");
	// TODO: �ڴ˴������Ϣ����������
}

void CCMSFormView::OnPreview(){
    // INT count=m_List_Pic.GetSelectedCount();
    BOOL b_next=TRUE;
	POSITION pos=m_List_Pic.GetFirstSelectedItemPosition();
    CString cs;
   while(pos)
   {
    
      INT next_index=m_List_Pic.GetNextSelectedItem(pos);
      if(next_index!=-1)
	  {
         cs=m_List_Pic.GetItemText(next_index,0);
	  }
   }
   pos=m_List_Up.GetFirstSelectedItemPosition();
   while(pos)
   {
     INT next_index=m_List_Up.GetNextSelectedItem(pos);
	 if(next_index!=-1)
	 {
		 cs=m_List_Up.GetItemText(next_index,0);
	 }
   }
    if(cs!=L"")
	{
		CCPreview cpv;
		cpv.m_Pic_Path=cs;
		//CMSBOXW(cs);
		cpv.DoModal();
	}

	

}
void CCMSFormView::OnNMRClickListUp(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CPoint cp;
	GetCursorPos(&cp);
	//ClientToScreen(&cp);
	ScreenToClient(&cp);
	OnRButtonDown(MK_RBUTTON,cp);
	*pResult = 0;
}

void CCMSFormView::OnNMRClickListPic(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CPoint cp;
	GetCursorPos(&cp);
	//ClientToScreen(&cp);
	ScreenToClient(&cp);
	OnRButtonDown(MK_RBUTTON,cp);
	*pResult = 0;
}
