#include "stdafx.h"
#include "lib_cms.h"
#include "CMSUtils.h"
#include <iostream>
#include <cstring>
#include <map>
#include<direct.h>
#include <cstdio>
#include <cstdlib>
#include "json/json.h"
using namespace Json;
using namespace std;
CCMSUtils::CCMSUtils(void)
{
}

CCMSUtils::~CCMSUtils(void)
{
}

BSTR CCMSUtils::doGetPathFiles(BSTR path_name)
{
	USES_CONVERSION;
	Value root;
	FastWriter fw;
	string retStr;
	CString pattern(path_name);
	pattern+=L"\\*.*";
	//CMSBOXW(pattern);
	Value images;
	int dir_index=0;
	int image_index=0;
	CString res;
	if(NULL!=path_name&&_file_exists(W2A(path_name))==0)
	{
		SetCurrentDirectory(path_name);
		CFileFind cff;
		BOOL found=cff.FindFile(pattern);
		while(found)
		{   
			found=cff.FindNextFile();
			//res+=L"  "+cff.GetFilePath();
			if(cff.IsDirectory()&&!cff.IsDots()){
				CString full_path=cff.GetFilePath();
				//full_path.Append(cff.GetFileName());
				if(!full_path.IsEmpty())
				{ 
					//res+=L"--"+full_path+L"--";
					char *file=W2A(full_path.AllocSysString());
					if(NULL!=file)
					{
						char buff[128]={0};
						_itoa_s(dir_index++,buff,128,10);
						root[buff]=file;
					}
				}
			}
			if( cff.GetFileName().Find(L".jpg")>0||
				cff.GetFileName().Find(L".gif")>0||
				cff.GetFileName().Find(L".png")>0||
				cff.GetFileName().Find(L".bmp")>0
				)
			{
				/*		  CMSBOX("image");
				return NULL;*/
				//CMSBOXW(cff.GetFilePath());
				char l_buff[128]={0};
				_itoa_s(image_index++,l_buff,128,10);
				images[l_buff]=W2A(cff.GetFilePath());
			}
		}
		cff.Close();
	}

	if(images.size()>=1)
	{
		root["images"]=images;
	}
	retStr=fw.write(root);
	//CMSBOXW(res);
	if(retStr.length()>0)
	{
		return SysAllocString(A2W(retStr.c_str()));
	}
	return CString("1").AllocSysString();
}

BSTR CCMSUtils::doGetDriveFiles(void)
{
	USES_CONVERSION;
	INT drive_current=0;
	ULONG uDriveMask=0;
	INT drive=1;
	INT last=0;
	Value root;
	Value images;
	Reader reader;
	FastWriter fw;
	string retStr;
	TCHAR g_szDrvMsg[] = _T("A:\\");
	static char drive_buff[_MAX_PATH]={0};
	drive_current = _getdrive();
	string drive_str;
	uDriveMask=_getdrives();
	if(uDriveMask==0){
		CMSBOXW(L"函数返回没有磁盘");
	}else{
		while(uDriveMask)
		{
			if(uDriveMask&1)
			{
				Value lv;
				Value image;
				Value lnone;
				char *path_files=NULL;
				path_files=W2A(doGetPathFiles(g_szDrvMsg));
				if(NULL!=path_files&&reader.parse(path_files,lv)==TRUE)
				{
					if(lv.isMember("images"))
					{
						Value::iterator it=lv["images"].begin();

						while(it!=lv["images"].end())
					 {   

						 images.append(*it);
						 ++it;
					 }

				 }
					root[W2A(g_szDrvMsg)]=lv;
				}
			}
			++g_szDrvMsg[0];
			uDriveMask >>= 1;
		}
	}
	//for(;drive<=26;++drive)
	//{
	// if(!_chdrive(drive))
	// {
	//  if( _getdcwd( drive, drive_buff, _MAX_PATH ) != NULL ){
	//   CString  files=doGetPathFiles(A2W(drive_buff));
	//           // files.Replace(L"\\\\",L"\\");
	//   drive_str+=drive_buff;
	//   root[drive_buff]=W2A(files);
	//  }
	// }
	//}
	//_chdrive( drive_current );
	if(images.isArray()&&images.size()>=1)
	{
		root["images"]=images;
	}
	retStr=fw.write(root);
	CString cs(A2W(retStr.c_str()));
	//cs.Replace(L"\\\\",L"\\");
	//CMSBOXW(cs);
	cs.Replace(L"\\n",L"");
	if(cs.GetLength()>0)
	{ 
		/*   CMSBOXW(cs);
		CMSBOX(drive_str.c_str());*/
		return cs.AllocSysString();
	}
	//if(GetLogicalDriveStrings(1024,drive_buff)!=0){
	//   CMSBOXW(drive_buff);
	//}
	return NULL;
}
