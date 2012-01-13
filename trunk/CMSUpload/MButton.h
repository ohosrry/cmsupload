#pragma once
#include "afxwin.h"

class MButton :
	public CButton
{
		DECLARE_DYNCREATE(MButton)
public:
	MButton(void);
	~MButton(void);
	virtual void OnLButtonUp(
		UINT nFlags,
		CPoint point 
		);
protected:
	DECLARE_MESSAGE_MAP()
	
};
