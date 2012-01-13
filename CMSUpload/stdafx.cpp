// stdafx.cpp : 只包括标准包含文件的源文件
//  CMSUpload.pch 将作为预编译头
//  stdafx.obj 将包含预编译类型信息

#include "stdafx.h"
wfstream flog;
static int lock=0;
void initLog(){
	if(lock==0){
		flog.open(L"D:\\cmslog",ios::out|ios::app);
		lock=1;
	}
}

void log(TCHAR *function,TCHAR *message){
	TCHAR buff[2048]={0};
	TCHAR t[128]={0};
	time_t tt;
	if(0==lock){
		initLog();
	}
	tt=time(NULL);
	tm t_m;
	localtime_s(&t_m,&tt);
	wcsftime(t,128,L"%Y-%m-%d %H:%M:%S",&t_m);
	wsprintf(buff,L"%s %s %s",t,function,message);
	flog<<buff<<endl;
}