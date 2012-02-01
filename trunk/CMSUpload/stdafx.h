#pragma once

// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // �� Windows ͷ���ų�����ʹ�õ�����
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // ĳЩ CString ���캯��������ʽ��

#include <afxctl.h>         // ActiveX �ؼ��� MFC ֧��
#include <afxext.h>         // MFC ��չ
#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // MFC �� Internet Explorer 4 �����ؼ���֧��
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>                     // MFC �� Windows �����ؼ���֧��
#endif // _AFX_NO_AFXCMN_SUPPORT

// �����ϣ��ʹ�� MFC ���ݿ��࣬
//  ��ɾ����������������ļ�
#ifndef _WIN64

#ifndef _AFX_NO_DB_SUPPORT
#include <afxdb.h>                      // MFC ODBC ���ݿ���
#endif // _AFX_NO_DB_SUPPORT

#ifndef _AFX_NO_DAO_SUPPORT
#include <afxdao.h>                     // MFC DAO ���ݿ���
#endif // _AFX_NO_DAO_SUPPORT

#endif // _WIN64
#define SAFE_DELETE(p) if(p!=NULL)\
{\
	delete p;\
	p=NULL;\
}
#include <process.h>
#include <map>
#include <fcntl.h>
#include <fstream>
#include <sstream>
#include <algorithm>
#include "atlimage.h"
#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <locale.h>
#include <wchar.h>
#include <errno.h>
#include <cassert>
#include <fcntl.h>
#include <sys/stat.h>
#include <WinNT.h>
using namespace std;
#define MB(T) ::MessageBoxW(NULL,T,T,MB_OK);
#define MBA(T) ::MessageBoxA(NULL,T,T,MB_OK);
void log(TCHAR *function,TCHAR *message);
int upload_file(const char *uploadpath,const char *filepath);
LPCSTR WS2AS(const LPWSTR src);
LPWSTR AS2WS(const LPCSTR  src);
struct STIMAGE{
	CImage *m_image;
	CStatic *m_static;
	CString m_path;
	int m_image_num;
	~STIMAGE(){
        SAFE_DELETE(m_image)
		SAFE_DELETE(m_static)
	}
};
class CCMSUploadCtrl;

