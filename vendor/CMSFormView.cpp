// CMSFormView.cpp : 实现文件
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
CCMSFormView* CCMSFormView::m_Instance=NULL;
CCMSFormView::CCMSFormView()
	: CDialog(CCMSFormView::IDD),m_Pic_Id(0),m_bDraging(FALSE),m_Pic_Up_Id(0),m_Check_Lock(FALSE)
{

CCMSFormView::m_Instance=this;
m_Error_Msg.insert(pair<string,CString>("0",L"上传失败!"));
m_Error_Msg.insert(pair<string,CString>("1",L"更新图片成功(不含颜色码)!"));
m_Error_Msg.insert(pair<string,CString>("2",L"新增图片成功(不含颜色码)!"));
m_Error_Msg.insert(pair<string,CString>("3",L"更新图片成功(含颜色码)!"));
m_Error_Msg.insert(pair<string,CString>("4",L"新增图片成功(含颜色码)!"));
m_Error_Msg.insert(pair<string,CString>("5",L"上传图片规则不符合!"));
m_Error_Msg.insert(pair<string,CString>("6",L"上传图片名字中的六位码和选择的商品6位码不一致!"));
m_Error_Msg.insert(pair<string,CString>("7",L"图片不存在!"));
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
		SAFE_DELETE(*it_pic);
		++it_pic;
	}
	map<string,string*>::iterator it_map=m_Tree_Map.begin();
	while(it_map!=m_Tree_Map.end())
	{
		SAFE_DELETE(it_map->second);
		++it_map;
	}
	vector<CBitmap*>::iterator it_bit_map=m_Bitmap_Vector.begin();
	while(it_bit_map!=m_Bitmap_Vector.end())
	{
        SAFE_DELETE(*it_bit_map)
		++it_bit_map;
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
	ON_NOTIFY(LVN_KEYDOWN, IDC_LIST_PIC, &CCMSFormView::OnLvnKeydownListPic)
	ON_WM_CHAR()
	ON_BN_CLICKED(IDC_CHECK_PIC, &CCMSFormView::OnBnClickedCheckPic)
END_MESSAGE_MAP()


// CCMSFormView 诊断

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


// CCMSFormView 消息处理程序

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
		TRACE(_T("无法加载位图: %x\n"),IDB_FILE_VIEW_24);
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
	HTREEITEM root=m_Tree.InsertItem(L"我的电脑");
    //CMSBOXW(cs);
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
	}else{
	 //   CMSBOXW(cs);
		//fstream fs("D:\\log.txt",ios::app);
		//string ssx=fr.getFormatedErrorMessages();
		//CMSBOX(ssx.c_str());
	 //   fs<<W2A(cs.AllocSysString())<<endl;
		//fs<<ssx<<endl;
		//fs.close();
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
   // CMSBOXW(cs);
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
					 TVITEM tv={0};
					 tv.pszText=A2W(l_s.c_str());
					 if(m_Tree.GetItem(&tv))
					 {
						 string *node_str=new string((*it).asCString());
						 HTREEITEM lroot=m_Tree.InsertItem(A2W(l_s.c_str()),0,0,root);
						 m_Tree.SetItemData(lroot,(DWORD_PTR)node_str);
						 m_Tree_Map[it.memberName()]=node_str;
					 }
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
		   //m_List_Up.SetImageList(&m_Image_Pic,LVSIL_NORMAL);
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
	INT left=65535,right=0,top=65535,bottom=0;
	CPoint first,last,bounds;
	NM_LISTVIEW* plist_view=(NM_LISTVIEW*)pNMHDR;
	POSITION pos;
	BOOL next=TRUE,b_first=TRUE;
	ASSERT(!m_bDraging);
	m_bDraging=TRUE;
	pos=m_List_Pic.GetFirstSelectedItemPosition();
    
	while(pos)
	{
		CRect l_Rect;
		INT l_index=m_List_Pic.GetNextSelectedItem(pos);
        m_List_Pic.GetItemRect(l_index,l_Rect,0);
		left=l_Rect.left<left?l_Rect.left:left;
		right=l_Rect.right>right?l_Rect.right:right;
		top=l_Rect.top<top?l_Rect.top:top;
		bottom=l_Rect.bottom>bottom?l_Rect.bottom:bottom;
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
	m_Big_Drag.Create(right-left,bottom-top,ILC_COLOR32|ILC_MASK,1,1);
	m_Big_Drag_Image.Create(right-left,bottom-top,32,BI_RGB);
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
	m_Big_Drag.Add(&bmp,RGB(0,0,0));
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
		//ClientToScreen(&rect);
		//ClientToScreen(&point);
		ScreenToClient(&rect);
		if(rect.PtInRect(point))
		{
			   
                if(m_Image_Up.m_hImageList==NULL)
				{
				  //m_Image_Up.DeleteImageList();
                  m_Image_Up.Create(64,64,ILC_COLOR32|ILC_MASK,1,1);
				 // m_Pic_Up_Id=0;
				 // CMSBOX("Create")
                  m_Image_Up_Id=0;
				}
                
				m_List_Up.SetImageList(&m_Image_Up,LVSIL_NORMAL);
				
				vector<ST_DRAG>::iterator it=m_St_Drag.begin();
				while(it!=m_St_Drag.end())
				{
					LVFINDINFO lvInfo;
					lvInfo.psz=(*it).m_String;
					lvInfo.flags=LVFI_STRING;
					if(m_List_Up.FindItem(&lvInfo)==-1)
					{
						CImage l_image;
						CImage l_small;
                        INT l_w,l_h;
						CBitmap l_btmp;
						l_small.Create(64,64,32,BI_RGB);
                        HRESULT hr=l_image.Load((*it).m_String);
						if(FAILED(hr))
						{
							CMSBOX("l_image.Load((*it).m_String) failed");
						}
						l_w=l_image.GetWidth();
						l_h=l_image.GetHeight();
                        HDC l_hdc=l_small.GetDC();
					    SetStretchBltMode(l_hdc,HALFTONE|BLACKONWHITE);
						BOOL drawRet=FALSE;
                        if(l_image.IsTransparencySupported())
						{
							drawRet=l_image.TransparentBlt(l_hdc,0,0,64,64,0,0,l_w,l_h,CLRBREAK);
						}
						if(!drawRet)
						{
							CMSBOX("l_image.TransparentBlt failed");
							
						}
						l_small.ReleaseDC();
						HBITMAP l_bmp=l_small.Detach();
						BOOL l_bAttach=FALSE;

                        l_bAttach=l_btmp.Attach(l_bmp);
						if(!l_bAttach)
						{
							CMSBOX("l_btmp.Attach failed");
						}
						//m_Bitmap_Vector.push_back(l_btmp);
					    INT l_iAdd_ret=m_Image_Up.Add(&l_btmp,RGB(255,255,255));
						//CString cs;
						//cs.Format(L"%d %d %d %d",m_Image_Up.GetImageCount(),l_iAdd_ret,GetLastError(),m_Pic_Up_Id);
						//CMSBOXW(cs);
					    m_List_Up.InsertItem(m_Pic_Up_Id,(*it).m_String,m_Image_Up_Id++);
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
		//SetDlgItemInt(IDC_CHECK_ALL,1);
	    ((CButton*)GetDlgItem(IDC_CHECK_ALL))->SetCheck(TRUE);
        OnBnClickedCheckAll();
	}
	CDialog::OnLButtonUp(nFlags, point);
}

void CCMSFormView::OnNMDblclkListPic(NMHDR *pNMHDR, LRESULT *pResult)
{
	USES_CONVERSION;
	CString cs;
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
    cs=m_List_Pic.GetItemText(pNMItemActivate->iItem,0);
	

	if(m_Image_Up.m_hImageList==NULL)
	{
		//m_Image_Up.DeleteImageList();
		m_Image_Up.Create(64,64,ILC_COLOR32|ILC_MASK,1,1);
		// m_Pic_Up_Id=0;
		// CMSBOX("Create")
		m_Image_Up_Id=0;
		m_List_Up.SetImageList(&m_Image_Up,TVSIL_NORMAL);
		//return;
	}
	//return ;
//	m_List_Up.SetImageList(&m_Image_Pic,LVSIL_NORMAL);
	LVFINDINFO lvInfo;
	lvInfo.psz=cs;
	lvInfo.flags=LVFI_STRING;
	//INT index=m_List_Up.HitTest(pNMItemActivate->ptAction);
	//CMSBOXW(cs);

	if(m_List_Up.FindItem(&lvInfo)==-1&&_file_exists(W2A(cs))==0)
	{
		CImage l_image;
		CImage l_small;
		INT l_w,l_h;
		CBitmap l_btmp;
		l_small.Create(64,64,32,BI_RGB);
		HRESULT hr=l_image.Load(cs);
		if(FAILED(hr))
		{
			CMSBOX("l_image.Load((*it).m_String) failed");
		}
		l_w=l_image.GetWidth();
		l_h=l_image.GetHeight();
		HDC l_hdc=l_small.GetDC();
		SetStretchBltMode(l_hdc,HALFTONE|BLACKONWHITE);
		BOOL drawRet=FALSE;
		if(l_image.IsTransparencySupported())
		{
			drawRet=l_image.TransparentBlt(l_hdc,0,0,64,64,0,0,l_w,l_h,CLRBREAK);
		}
		if(!drawRet)
		{
			CMSBOX("l_image.TransparentBlt failed");

		}
		l_small.ReleaseDC();
		HBITMAP l_bmp=l_small.Detach();
		BOOL l_bAttach=FALSE;

		l_bAttach=l_btmp.Attach(l_bmp);
		if(!l_bAttach)
		{
			CMSBOX("l_btmp.Attach failed");
		}
		//m_Bitmap_Vector.push_back(l_btmp);
		INT l_iAdd_ret=m_Image_Up.Add(&l_btmp,RGB(255,255,255));
		//CString cs1;
		//cs1.Format(L"%d %d %d",l_iAdd_ret,m_Image_Up.GetImageCount(),GetLastError());
		//CMSBOXW(cs1);
		m_List_Up.InsertItem(m_Pic_Up_Id,cs,m_Image_Up_Id++);
		m_Pic_Up_Id++;
		((CButton*)GetDlgItem(IDC_CHECK_ALL))->SetCheck(TRUE);
		OnBnClickedCheckAll();
	}
    //INT *pid=(INT*)m_List_Up.GetItemData(pNMItemActivate->iItem);
	//cs.Format(L"%d %d",pNMItemActivate->iItem,pNMItemActivate->iSubItem);
	//CMSBOXW(cs);
    //CMSBOXW(cs);
	// TODO: 在此添加控件通知处理程序代码
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
		if(BST_CHECKED==IsDlgButtonChecked(IDC_CHECK_ALL))
		{
			m_List_Up.SetItemState(i,LVIS_SELECTED,LVIS_SELECTED);
		}else{
			m_List_Up.SetItemState(i,0,LVIS_SELECTED);
		}
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
	CString brand_code=CCMSInterfaceCtrl::getInstance()->brand_code;
	CString goods_sn=CCMSInterfaceCtrl::getInstance()->goods_sn;
	SYSTEMTIME systime;
	::GetSystemTime(&systime);
	CTime ct(systime);
	CString destDir=ct.Format("%Y/%m/%d/");
    //CString uploadName=uploadDir+destDir;
	CString uploadName=uploadDir;
	CCMSFormView * pMain=param->m_Main;
	INT i=param->count;
	CString l_file_name=pMain->m_List_Up.GetItemText(i,0);
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
    if(0==_doFtpUpload(W2A(ftpUrl.AllocSysString()),buf,W2A(uploadName.AllocSysString()),W2A(ftpUser.AllocSysString()),W2A(ftpPwd.AllocSysString()),W2A(l_file_name.AllocSysString())))
	{
      //CString msg;
	  //msg.Format(L"%s 上传成功",A2W(file_name));
	 // CMSBOXW(msg);
	  LVFINDINFO lvinfo={0};
	  lvinfo.psz=A2W(buf);
	  INT fixItemIndex=pMain->m_List_Up.FindItem(&lvinfo);
	  if(fixItemIndex>=0){
		pMain->m_List_Up.DeleteItem(fixItemIndex);
		pMain->UpdateWindow();
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
		  string l_brand_code=ctool::URLEncode(W2A(brand_code));
		  string l_goods_sn=ctool::URLEncode(W2A(goods_sn));
		  upload_url.append("?files="+param);
		  upload_url.append("&brand_code="+l_brand_code);
		  upload_url.append("&goods_sn="+l_goods_sn);
		  //fstream fs("D:\\log.txt",ios::app);


		  //CMSBOX(upload_url.c_str());
		  //fs<<upload_url.c_str()<<endl;
		  //fs.close();
		  char *http_buff=new char[102400];
		  INT ret=_doHttpGet(upload_url.c_str(),http_buff);
		  if(ret==0)
		  { 
		     //pMain->m_Status.m_Can_Exit=TRUE;
             Value l_value;
			 Reader fr;
			 //CMSBOX(http_buff);
			 char * l_buff=W2A((wchar_t*)http_buff);
			// CMSBOX(http_buff);
			 //sprintf_s(http_buff,102300,"%s","{\"code\":\"0\",\"msg\":\"好额\"}");
			 if(fr.parse(http_buff,l_value))
			 {
				 if(l_value.isMember("code")&&l_value.isMember("msg"))
				 {
                    if(strcmp(l_value["code"].asCString(),"0")==0)
					{
						map<CString,ST_STATUS>::iterator l_it_status=pMain->m_Status.m_Status_Map.find(l_file_name);
						if(l_it_status!=pMain->m_Status.m_Status_Map.end())
						{
                           if(pMain->m_Error_Msg.find(l_value["code"].asCString())!=pMain->m_Error_Msg.end())
						   {
                              //l_it_status->second.next->SetWindowText(pMain->m_Error_Msg[l_value["code"].asCString()]);
							//  CMSBOXW(pMain->m_Error_Msg[l_value["code"].asCString()]);
                               //g_Map_Lock.Lock();

							   l_it_status->second.s_percent=pMain->m_Error_Msg[l_value["code"].asCString()];
                               INT l_ret=_doFtpDelete(W2A(ftpUrl.AllocSysString()),W2A(uploadName.AllocSysString()),W2A(ftpUser.AllocSysString()),W2A(ftpPwd.AllocSysString()));
                                if(l_ret==0)
								{
                                //  CMSBOX("delete success");
								}
						      // g_Map_Lock.Unlock();
						   }
						}
					}else{
						map<CString,ST_STATUS>::iterator l_it_status=pMain->m_Status.m_Status_Map.find(l_file_name);
						if(l_it_status!=pMain->m_Status.m_Status_Map.end())
						{
                             string csx=l_value["code"].asString();
							 if(csx=="5"||csx=="6"||csx=="7")
							 {
								 INT l_ret=_doFtpDelete(W2A(ftpUrl.AllocSysString()),W2A(uploadName.AllocSysString()),W2A(ftpUser.AllocSysString()),W2A(ftpPwd.AllocSysString()));
								 if(l_ret==0)
								 {
									 //CMSBOX("delete success");
								 }
							 }
							if(pMain->m_Error_Msg.find(l_value["code"].asCString())!=pMain->m_Error_Msg.end())
							{
								//l_it_status->second.next->SetWindowText(pMain->m_Error_Msg[l_value["code"].asCString()]);
								//CMSBOXW(pMain->m_Error_Msg[l_value["code"].asCString()]);
								g_Map_Lock.Lock();
								l_it_status->second.s_percent=pMain->m_Error_Msg[l_value["code"].asCString()];
								g_Map_Lock.Unlock();
							}
						}
					}
				 }

			 }
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
		::MessageBox(NULL,L"没有选择文件",L"没有选择文件",MB_OK);
	}
    for(;i<count;++i)
	{
		ST_THREAD_PARAM* st_param=new ST_THREAD_PARAM();
        st_param->m_Main=this;
		st_param->count=i;
	    CString csx=m_List_Up.GetItemText(i,0);
		pair<CString,CString> l_p(csx,csx);
		ST_STATUS * st_status=new ST_STATUS();
		st_status->percent=0;
		st_status->m_Progress=new CProgressCtrl();
		st_status->pre=new CStatic();
		st_status->next=new CStatic();
		pair<CString,ST_STATUS> l_ps(csx,*st_status);
		m_Status.m_Map.insert(l_p);
		m_Status.m_Status_Map.insert(l_ps);
		CWinThread* theThread=AfxBeginThread(&CCMSFormView::UploadThread,st_param,0,0,NULL,NULL);  
        m_Up_Thread.push_back(theThread);

		//return;
	}
	if(count>0)
	{
		
		
		//CDC *p_CDC=m_Status.GetDC();
        //p_CDC->DrawText(L"HI",0,CRect(0,0,10,10),0);
  //      CClientDC dc(&m_Status);
		//dc.TextOut(10,10,L"HI");
		//CString css;
		//css.Format(L"%d",GetLastError());
		//CMSBOXW(css);
        m_Status.m_Can_Exit=FALSE;
		m_Status.Create(IDD_FORM_STATUS,NULL);
		//m_Status.DoModal();
		//CMSBOXW(L"asdsad");
//CWinThread* theThread=AfxBeginThread(&CCMSFormView::UploadStatusThread,this,0,0,NULL,NULL); 
		//SetFocus();
		//m_Status.EnableWindow();
	}else{
		m_Status.m_Map.clear();
	}
 
}

UINT _cdecl CCMSFormView::UploadStatusThread(LPVOID lp)
{
	//CCMSFormView* thisView=(CCMSFormView*)lp;
	/*if(NULL==thisView)
	{
        CMSBOX("NO");
		return 1;
	}*/
	/* CMSBOX("HERE");
	thisView->m_Status.Create(IDD_FORM_STATUS,thisView);
    thisView->m_Status.ShowWindow(SW_SHOW);*/
   return 0;
}


void CCMSFormView::OnMButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
    if(MK_RBUTTON==nFlags)
	{
     m_Menu.TrackPopupMenu(nFlags,point.x,point.y,this);

	}
	CDialog::OnMButtonDown(nFlags, point);
}

void CCMSFormView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if(MK_RBUTTON==nFlags)
	{
       CMenu * l_menu=m_Menu.GetSubMenu(0);
        CRect cr;
	    GetWindowRect(&cr);
		 CString cs;
		 cs.Format(L"%d %d %d %d",cr.left,cr.right,cr.top,cr.bottom);
	   if(l_menu){
		l_menu->TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON,point.x+cr.left,cr.top+point.y,this);
	   }
	   
	}
	CDialog::OnRButtonDown(nFlags, point);
}

void CCMSFormView::OnContextMenu(CWnd* pWnd, CPoint point)
{

	//CMSBOX("HERE");
	// TODO: 在此处添加消息处理程序代码
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
	// TODO: 在此添加控件通知处理程序代码
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
	// TODO: 在此添加控件通知处理程序代码
	CPoint cp;
	GetCursorPos(&cp);
	//ClientToScreen(&cp);
	ScreenToClient(&cp);
	OnRButtonDown(MK_RBUTTON,cp);
	*pResult = 0;
}

CCMSFormView* CCMSFormView::getInstance()
{
	if(m_Instance==NULL)
	{
		CMSBOX("CRASH");
      m_Instance=new CCMSFormView();
 	}
    return m_Instance;
}
void CCMSFormView::UpdateUpLoadStatus(TCHAR *clientp,DOUBLE dltotal,DOUBLE dlnow,DOUBLE ultotal,DOUBLE ulnow)
{
   CString cs;

   cs.Format(L"%s 上传进度 %g%s",clientp,ceil(ulnow/ultotal*100),L"%");
   //CMSBOXW(cs);
   g_Map_Lock.Lock();
   //m_Status.m_Map[clientp]=cs;
   map<CString,ST_STATUS>::iterator it_find=m_Status.m_Status_Map.find(clientp);
   if(it_find!=m_Status.m_Status_Map.end())
   {
	  m_Status.m_Status_Map[clientp].percent=(INT)ceil(ulnow/ultotal*100);
	  CString css;
	  css.Format(L"%d%s",(INT)ceil(ulnow/ultotal*100),L"%");
	  m_Status.m_Status_Map[clientp].s_percent=css;
   }
   g_Map_Lock.Unlock();
   //m_Status.DoUpdate();
   //CMSBOXW(cs);

}
void CCMSFormView::OnLvnKeydownListPic(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLVKEYDOWN pLVKeyDow = reinterpret_cast<LPNMLVKEYDOWN>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	
	*pResult = 0;
}

void CCMSFormView::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CDialog::OnChar(nChar, nRepCnt, nFlags);
	CWnd *l_Is_Focus=m_List_Up.GetFocus();
	if(l_Is_Focus==NULL)
	{
        return;
	}
	if(0x8000==GetAsyncKeyState(VK_LCONTROL))
	{
         CMSBOX("CTR");
	}
}

void CCMSFormView::OnBnClickedCheckPic()
{

	INT i=0,count=m_List_Pic.GetItemCount();
	BOOL b_check=FALSE;
	for(;i<count;++i)
	{
		LVITEMW lvw;
		lvw.state=LVIS_SELECTED;
		if(BST_CHECKED==IsDlgButtonChecked(IDC_CHECK_PIC))
		{
			m_List_Pic.SetItemState(i,LVIS_SELECTED,LVIS_SELECTED);
		}else{
			m_List_Pic.SetItemState(i,0,LVIS_SELECTED);
		}
	}

	m_List_Pic.SetFocus();

	// TODO: 在此添加控件通知处理程序代码
}
