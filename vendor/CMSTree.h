#pragma once


// CCMSTree

class CCMSTree : public CTreeCtrl
{
	DECLARE_DYNAMIC(CCMSTree)

public:
	CCMSTree();
	virtual ~CCMSTree();

protected:
	DECLARE_MESSAGE_MAP()
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};


