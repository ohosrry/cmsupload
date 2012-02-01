// stdafx.cpp : 只包括标准包含文件的源文件
//  CMSUpload.pch 将作为预编译头
//  stdafx.obj 将包含预编译类型信息

#include "stdafx.h"
wfstream flog;
static int lock=0;
#include <curl/curl.h>
//ansi 字符串转宽字符
LPWSTR AS2WS(const LPCSTR  src){
	size_t len=MultiByteToWideChar(CP_UTF8,0,src,-1,NULL,NULL);
	LPWSTR nStr=new wchar_t[len+1];
	MultiByteToWideChar(CP_UTF8,0,src,-1,nStr,len);
	return nStr;
}
//宽字符转ansi字符串
LPCSTR WS2AS(const LPWSTR src){
	size_t len=WideCharToMultiByte(CP_UTF8,0,src,-1,NULL,NULL,NULL,FALSE);
	LPSTR nStr=new char[len+1];
	WideCharToMultiByte(CP_UTF8,0,src,-1,nStr,len,NULL,FALSE);
	return nStr;
} 
char g_buffer[1024*1024];
int wFunction(void *p){
	MBA((char*)p);
//sprintf(g_buffer,"%s",p);
return 0;
}
struct INIT{
	INIT(){
		//MBA("INIT");
		curl_global_init(CURL_GLOBAL_ALL);
	}
};
//INIT init;
int upload_file(const char *uploadpath,const char *filepath)
{
	struct curl_httppost *post = NULL;
	struct curl_httppost *last = NULL;
	CURLcode              code;
	CURL                  *curl;
	curl = curl_easy_init(); // init curl
	curl_formadd(&post, &last, CURLFORM_COPYNAME, "file", \
		CURLFORM_FILE, filepath, CURLFORM_END); // specify the file to upload
	curl_easy_setopt(curl, CURLOPT_HTTPPOST, post); // set HTTP POST data
	curl_easy_setopt(curl, CURLOPT_URL, uploadpath); // set URL
	curl_easy_setopt(curl,CURLOPT_WRITEFUNCTION,wFunction);
//	curl_easy_setopt(curl,CURLOPT_WRITEDATA,g_buffer);
	code = curl_easy_perform(curl); // perform request

	curl_formfree(post); // free post
	if (code)
	{
      // MBA("Failed");
	  // MBA(curl_easy_strerror(code));
		//perror(curl_easy_strerror(code));
		return 1;
	}
	MBA(g_buffer);
	return 0;
}
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