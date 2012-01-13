#pragma once


// CMSTree

class CMSTree : public CTreeCtrl
{
	DECLARE_DYNAMIC(CMSTree)

public:
	
	CMSTree();
	virtual ~CMSTree();
	void initDir();
	void OnLButtonUp(UINT nFlags, CPoint point);
protected:
	int OnCreate(LPCREATESTRUCT lpCreateStruct);

	
	DECLARE_MESSAGE_MAP()
private:
	CString m_path;
};


