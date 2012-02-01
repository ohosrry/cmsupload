#pragma once
#include <map>
#include <vector>
#include <algorithm>
// CMSTree
struct STJPG{
  CString m_path;
  int count;
};

class CMSTree : public CTreeCtrl
{
	DECLARE_DYNAMIC(CMSTree)

public:
	
	CMSTree();
	virtual ~CMSTree();
	void initDir();
	void SetWnd(CCMSUploadCtrl *cwd);
	void OnLButtonUp(UINT nFlags, CPoint point);
	friend void addSubDir(CMSTree &tree,CString &path,HTREEITEM *item=NULL);
protected:
	int OnCreate(LPCREATESTRUCT lpCreateStruct);

	
	DECLARE_MESSAGE_MAP()
private:
	CString m_path;
	CStatic m_static;
	map<int,CStatic*> m_map; 
	map<CString,CString> m_map_jpg;
	vector<CString> m_jpg;
	int m_Image_Num;
	CCMSUploadCtrl *cwd;
	virtual void _AddImage(STJPG &jpg);
};


