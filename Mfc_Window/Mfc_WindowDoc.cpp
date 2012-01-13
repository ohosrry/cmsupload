
// Mfc_WindowDoc.cpp : CMfc_WindowDoc 类的实现
//

#include "stdafx.h"
#include "Mfc_Window.h"

#include "Mfc_WindowDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMfc_WindowDoc

IMPLEMENT_DYNCREATE(CMfc_WindowDoc, CDocument)

BEGIN_MESSAGE_MAP(CMfc_WindowDoc, CDocument)
END_MESSAGE_MAP()


// CMfc_WindowDoc 构造/析构

CMfc_WindowDoc::CMfc_WindowDoc()
{
	// TODO: 在此添加一次性构造代码

}

CMfc_WindowDoc::~CMfc_WindowDoc()
{
}

BOOL CMfc_WindowDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)

	return TRUE;
}




// CMfc_WindowDoc 序列化

void CMfc_WindowDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 在此添加存储代码
	}
	else
	{
		// TODO: 在此添加加载代码
	}
}


// CMfc_WindowDoc 诊断

#ifdef _DEBUG
void CMfc_WindowDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMfc_WindowDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CMfc_WindowDoc 命令
