// MSTree.cpp : 实现文件
//

#include "stdafx.h"
#include "CMSUpload.h"
#include "MSTree.h"
// CMSTree
IMPLEMENT_DYNAMIC(CMSTree, CTreeCtrl)

CMSTree::CMSTree()
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
			if(!cff.IsDots())
			this->InsertItem(filename,NULL,NULL);
		}else{
			break;
		}
	}while(1);
	return ;
}

void addSubDir(CMSTree &tree,CString &path,HTREEITEM *item=NULL){
	CFileFind cff;
	BOOL ret=cff.FindFile(path+L"\\*.*");
	ASSERT(ret);
	do{
		BOOL bret=cff.FindNextFile();
		if(bret){
			CString filename=cff.GetFileName();
			if(!cff.IsDots())
			tree.InsertItem(filename,*item,NULL);
		}else{
			break;
		}
	}while(1);
	return ;
}
int CMSTree::OnCreate(LPCREATESTRUCT lpCreateStruct){
	
	return CTreeCtrl::OnCreate(lpCreateStruct);
}
void CMSTree::OnLButtonUp(UINT nFlags, CPoint point){
 HTREEITEM item=this->GetSelectedItem();
 CString finename=this->GetItemText(item);
 CString l_path=m_path;
 BOOL bret=::CreateDirectory(l_path+L"\\"+finename,NULL);
 if(!bret){
    addSubDir(*this,l_path+L"\\"+finename,&item);
 }
 
}
BEGIN_MESSAGE_MAP(CMSTree, CTreeCtrl)
	ON_WM_CREATE()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()



// CMSTree 消息处理程序


