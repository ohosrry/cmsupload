// CMSTree.cpp : 实现文件
//

#include "stdafx.h"
#include "CMSInterface.h"
#include "CMSTree.h"
#include "lib_cms.h"

// CCMSTree

IMPLEMENT_DYNAMIC(CCMSTree, CTreeCtrl)

CCMSTree::CCMSTree()
{

}

CCMSTree::~CCMSTree()
{
}

int CCMSTree::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	//const DWORD dwViewStyle = WS_CHILD | WS_VISIBLE | TVS_HASLINES | TVS_LINESATROOT | TVS_HASBUTTONS;
 //   lpCreateStruct->style=dwViewStyle;
	//lpCreateStruct->x=0;
	//lpCreateStruct->y=0;

    return 0;
}

BEGIN_MESSAGE_MAP(CCMSTree, CTreeCtrl)
	ON_WM_CREATE()
END_MESSAGE_MAP()



// CCMSTree 消息处理程序


