#pragma once

// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // 从 Windows 头中排除极少使用的资料
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // 某些 CString 构造函数将是显式的

#include <afxctl.h>         // ActiveX 控件的 MFC 支持
#include <afxext.h>         // MFC 扩展
#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // MFC 对 Internet Explorer 4 公共控件的支持
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>                     // MFC 对 Windows 公共控件的支持
#endif // _AFX_NO_AFXCMN_SUPPORT

// 如果不希望使用 MFC 数据库类，
//  请删除下面的两个包含文件
#ifndef _WIN64

#ifndef _AFX_NO_DB_SUPPORT
#include <afxdb.h>                      // MFC ODBC 数据库类
#endif // _AFX_NO_DB_SUPPORT

#ifndef _AFX_NO_DAO_SUPPORT
#include <afxdao.h>                     // MFC DAO 数据库类
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

