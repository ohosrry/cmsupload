
// Mfc_WindowView.cpp : CMfc_WindowView 类的实现
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
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CMfc_WindowView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CMfc_WindowView 构造/析构

CMfc_WindowView::CMfc_WindowView()
{
	// TODO: 在此处添加构造代码

}

CMfc_WindowView::~CMfc_WindowView()
{
}

BOOL CMfc_WindowView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CMfc_WindowView 绘制

void CMfc_WindowView::OnDraw(CDC* /*pDC*/)
{
	CMfc_WindowDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}


// CMfc_WindowView 打印


void CMfc_WindowView::OnFilePrintPreview()
{
	AFXPrintPreview(this);
}

BOOL CMfc_WindowView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CMfc_WindowView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CMfc_WindowView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
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


// CMfc_WindowView 诊断

#ifdef _DEBUG
void CMfc_WindowView::AssertValid() const
{
	CView::AssertValid();
}

void CMfc_WindowView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMfc_WindowDoc* CMfc_WindowView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMfc_WindowDoc)));
	return (CMfc_WindowDoc*)m_pDocument;
}
#endif //_DEBUG


// CMfc_WindowView 消息处理程序
