// MSTree.cpp : 实现文件
//

#include "stdafx.h"
#include "CMSUpload.h"
#include "CMSUploadCtrl.h"
#include "MSTree.h"
#include <vector>
// CMSTree
IMPLEMENT_DYNAMIC(CMSTree, CTreeCtrl)

CMSTree::CMSTree():m_Image_Num(1)
{
	m_path=L"C:\\Users\\Public\\Pictures\\";
	
}

CMSTree::~CMSTree()
{
}
void CMSTree::initDir(){
	CFileFind cff;
	BOOL ret=cff.FindFile(m_path+L"*.*");
	ASSERT(ret);
	do{
		BOOL bret=cff.FindNextFile();
		if(bret){
			CString filename=cff.GetFileName();
			if(!cff.IsDots()&&GetFileAttributes(m_path+L"\\"+filename)==FILE_ATTRIBUTE_DIRECTORY)
				this->InsertItem(filename,NULL,NULL);
		}else{
			break;
		}
	}while(1);
	return ;
}
BOOL FileExist(CString strFileName)
{
	CFileFind fFind;
	return fFind.FindFile(strFileName);
}
void addSubDir(CMSTree &tree,CString &path,HTREEITEM *item){
	CFileFind cff;
	BOOL ret=cff.FindFile(path+L"\\*.*");
	if(!ret){
		return;
	}
	CString tt=L"";
	do{
		BOOL bret=cff.FindNextFile();
		if(bret){
			CString filename=cff.GetFileName();
			if(!cff.IsDots()){
			    HTREEITEM l_item=tree.InsertItem(filename,*item,NULL);
				//CString *data=new CString(path+(L"\\"+filename));
			    STJPG *jpg=new STJPG();
				jpg->m_path=CString(path+(L"\\"+filename));
                jpg->count=tree.m_Image_Num++;
				//tree.m_jpg.push_back(*data);
				
				tree.SetItemData(l_item,(DWORD_PTR)jpg);				
			   }
		}else{
			break;
		}
	}while(1);
	return ;
}
int CMSTree::OnCreate(LPCREATESTRUCT lpCreateStruct){

	return CTreeCtrl::OnCreate(lpCreateStruct);
}
void jpg(CString &cs){
//AfxMessageBox(cs);
}
void CMSTree::OnLButtonUp(UINT nFlags, CPoint point)
{
	HTREEITEM item=this->GetSelectedItem();
	CString finename=this->GetItemText(item);
	CString l_path=m_path+L"\\"+finename;
	
	BOOL bret=FileExist(l_path);
	//AfxMessageBox(l_path+(L""+bret));
	if(bret&&GetFileAttributes(l_path)==FILE_ATTRIBUTE_DIRECTORY){
		if(!this->ItemHasChildren(item))
		addSubDir(*this,l_path,&item);
	}else if(finename.Right(3)=="jpg"){
		if(this->GetItemData(item)){
           _AddImage(*(STJPG*)this->GetItemData(item));   
		   m_Image_Num++;
		}
		//_AddImage(*(CString*)this->GetItemData(item));
	}
}
BEGIN_MESSAGE_MAP(CMSTree, CTreeCtrl)
	ON_WM_CREATE()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()



// CMSTree 消息处理程序


void dp(CRect &cr)
{
	char b[128]={0};
	sprintf_s(b,"L=%d,R=%d,T=%d,B=%d\n",cr.left,cr.right,cr.top,cr.bottom);
	MBA(b);

}
void CMSTree::_AddImage(STJPG &jpg)
{
   /* CStatic *cs=new CStatic();
	TCHAR buff[1024]={0};
	static int l=400,r=800,t=0,b=400;
	AfxMessageBox(path);
	this->RedrawWindow();
	HBITMAP bitmap=(HBITMAP)::LoadImage(AfxGetInstanceHandle(),path,IMAGE_BITMAP,0,0,LR_DEFAULTCOLOR|LR_LOADFROMFILE);
	bitmap=(HBITMAP)::LoadImage(AfxGetInstanceHandle(),path,IMAGE_BITMAP,0,0,LR_DEFAULTCOLOR|LR_LOADFROMFILE);
	if(!bitmap){
	   wsprintf(buff,L"%d",GetLastError());
	   AfxMessageBox(buff);
	   SAFE_DELETE(cs);
	   return;
	}
    cs->Create(L"image",WS_VISIBLE|WS_CHILD|SS_BITMAP,CRect(200,0,400,200),cwd,0);
    MessageBoxA(NULL,cs->GetParent()->GetRuntimeClass()->m_lpszClassName,"",MB_OK);
	cs->SetBitmap(bitmap);
	cs->RedrawWindow();
	m_map[m_Image_Num]=cs;*/
    int size=cwd->m_Stimage.size();
	if(jpg.count>0&&jpg.count<size)
	{
		AfxMessageBox(L"Aready\n");
		return;
	}
	STIMAGE image;
	char b[64]={0};
	sprintf_s(b,"%d",jpg.count);
	CRect cr=cwd->PointRects()[jpg.count-1];
	//dp(cr);
	//MBA(b);

	//string s;
	//stringstream ss;
	//ss<<cr[1].Height();
	//ss>>s;
	//MBA(s.c_str());
	image.m_path=jpg.m_path;
	image.m_image=new CImage();
	image.m_image->Load(image.m_path);
	image.m_static=new CStatic();
	image.m_static->Create(
		L"IMAGE",
		WS_CHILD|WS_VISIBLE,
		cr
		,
		cwd,
		0
		);

	cwd->m_Stimage.push_back(image);
	cwd->RedrawWindow(); 
	//char pathbuffer[256]={0};
	//strcpy(pathbuffer,image.m_path)
	//image.m_path.Format("%s",)
    //LPCSTR file_path=WS2AS((const LPWSTR)image.m_path);
	upload_file("http://pstore/Index/Test/up",WS2AS(image.m_path.GetBuffer(0)));

	//m_static.Create(
	//	L"IMAGE",
	//	WS_CHILD|WS_VISIBLE,
	//	cr
	//	,
	//	cwd,
	//	0
	//	);
     
}
void CMSTree::SetWnd(CCMSUploadCtrl *cwnd){
	this->cwd=cwnd;
}