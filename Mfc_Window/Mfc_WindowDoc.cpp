
// Mfc_WindowDoc.cpp : CMfc_WindowDoc ���ʵ��
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


// CMfc_WindowDoc ����/����

CMfc_WindowDoc::CMfc_WindowDoc()
{
	// TODO: �ڴ����һ���Թ������

}

CMfc_WindowDoc::~CMfc_WindowDoc()
{
}

BOOL CMfc_WindowDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)

	return TRUE;
}




// CMfc_WindowDoc ���л�

void CMfc_WindowDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: �ڴ���Ӵ洢����
	}
	else
	{
		// TODO: �ڴ���Ӽ��ش���
	}
}


// CMfc_WindowDoc ���

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


// CMfc_WindowDoc ����
