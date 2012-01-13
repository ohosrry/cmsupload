
// Mfc_WindowDoc.h : CMfc_WindowDoc 类的接口
//


#pragma once


class CMfc_WindowDoc : public CDocument
{
protected: // 仅从序列化创建
	CMfc_WindowDoc();
	DECLARE_DYNCREATE(CMfc_WindowDoc)

// 属性
public:

// 操作
public:

// 重写
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// 实现
public:
	virtual ~CMfc_WindowDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
};


