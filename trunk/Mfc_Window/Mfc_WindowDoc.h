
// Mfc_WindowDoc.h : CMfc_WindowDoc ��Ľӿ�
//


#pragma once


class CMfc_WindowDoc : public CDocument
{
protected: // �������л�����
	CMfc_WindowDoc();
	DECLARE_DYNCREATE(CMfc_WindowDoc)

// ����
public:

// ����
public:

// ��д
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// ʵ��
public:
	virtual ~CMfc_WindowDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
};


