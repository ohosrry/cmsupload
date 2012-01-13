
// Mfc_WindowView.cpp : CMfc_WindowView ���ʵ��
//

#include "stdafx.h"
#include "Mfc_Window.h"

#include "Mfc_WindowDoc.h"
#include "Mfc_WindowView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMfc_WindowView

IMPLEMENT_DYNCREATE(CMfc_WindowView, CView)

BEGIN_MESSAGE_MAP(CMfc_WindowView, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CMfc_WindowView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CMfc_WindowView ����/����

CMfc_WindowView::CMfc_WindowView()
{
	// TODO: �ڴ˴���ӹ������

}

CMfc_WindowView::~CMfc_WindowView()
{
}

BOOL CMfc_WindowView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CMfc_WindowView ����

void CMfc_WindowView::OnDraw(CDC* /*pDC*/)
{
	CMfc_WindowDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
}


// CMfc_WindowView ��ӡ


void CMfc_WindowView::OnFilePrintPreview()
{
	AFXPrintPreview(this);
}

BOOL CMfc_WindowView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CMfc_WindowView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CMfc_WindowView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}

void CMfc_WindowView::OnRButtonUp(UINT nFlags, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CMfc_WindowView::OnContextMenu(CWnd* pWnd, CPoint point)
{
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
}


// CMfc_WindowView ���

#ifdef _DEBUG
void CMfc_WindowView::AssertValid() const
{
	CView::AssertValid();
}

void CMfc_WindowView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMfc_WindowDoc* CMfc_WindowView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMfc_WindowDoc)));
	return (CMfc_WindowDoc*)m_pDocument;
}
#endif //_DEBUG


// CMfc_WindowView ��Ϣ�������
