#include "stdafx.h"
#include "CMSInterfaceCtrl.h"
#include <windows.h>
#include "lib_cms.h"
#include <iostream>
#include <locale.h>
#include <wchar.h>
#include <errno.h>
#include <cassert>
#include <io.h>
#include <fcntl.h>
#include <sys/stat.h>
#define HAVE_ICOVN
#include "curl/curl.h"
#include <vector>
#include <map>
#include <cmath>
#include <json/json.h>
#include <json/writer.h>
#include <algorithm> // sort
#ifndef LIB_CMS_H
#error "must include lib_cms.h"
#endif
using namespace std;
//LPWSTR A2W(const LPCSTR  src){
//	size_t len=MultiByteToWideChar(CP_UTF8,0,src,-1,NULL,NULL);
//	LPWSTR nStr=new wchar_t[len+1];
//	MultiByteToWideChar(CP_UTF8,0,src,-1,nStr,len);
//	return nStr;
//}

//LPCSTR W2A(const LPWSTR src){
//	size_t len=WideCharToMultiByte(CP_UTF8,0,src,-1,NULL,NULL,NULL,FALSE);
//	LPSTR nStr=new char[len+1];
//	WideCharToMultiByte(CP_UTF8,0,src,-1,nStr,len,NULL,FALSE);
//	return nStr;
//} 

char* basename(const char* file_name)
{
	char * local_file_name;
	size_t file_name_len=0;
	if(NULL==file_name)return NULL;
	local_file_name=(char*)file_name;
	
	file_name_len=strlen(local_file_name);
	
	while(*local_file_name++!='\0');

	while(*(local_file_name-1)!='\\'
		&&*(local_file_name-1)!='/'
		&&file_name_len--!=0
		)--local_file_name;

	return *local_file_name!='\0'?local_file_name:NULL;
}

char* filepath(const char* file_name,char *path_buffer)
{
	size_t path_len=0,copy_len=0;
	const char *lpath=NULL;
	if(NULL==file_name||NULL==path_buffer)return NULL;
	if(NULL==strstr(file_name,"\\")&&NULL==strstr(file_name,"/"))
	{
      return NULL;
	}
	path_len=strlen(file_name);
	lpath=file_name+path_len;
	while(*(lpath-1)!='\\'&&*(lpath-1)!='/')--lpath,--path_len;
	
	memcpy(path_buffer,file_name,path_len);
	//printf("%s\n",path_buffer);
	//CMSBOX(path_buffer);
	return path_buffer;
}

int _file_exists(const char *file)
{
	if(NULL==file)
	{
      return 1;
	}
	if(_access(file,0)!=-1)
	{
       return 0;
	}
	return 1;
}


static size_t read_callback(void *ptr, size_t size, size_t nmemb, void *stream)
{
	size_t retcode = fread(ptr, size, nmemb, (FILE*)stream);
	//fprintf(stderr, "*** We read %d bytes from file\n", retcode);
	return retcode;
}

/*
Ftp上传过程函数
void *clientp Js回调函数名 
double dltotal 下载总字节数
double dlnow   目前下载的字节数
double ultotal 上传总字节数
double ulnow   目前上传字节数
*/

int ftp_upload_progress(void *clientp,double dltotal,double dlnow,double ultotal,double ulnow){
	USES_CONVERSION;
	char * cb=(char*)clientp;
	if(ultotal>0&&ulnow>0&&ceil((ulnow/ultotal*100))<=100)
	{
	char b[1024]={0};
	sprintf_s(b,"%g",ulnow/ultotal*100);
	//CMSBOX(b);
	CComBSTR bstr(b); 
	DISPPARAMS params={0};
    params.cArgs=1;
	params.rgvarg=new VARIANT[params.cArgs];
    bstr.CopyTo(&params.rgvarg[0].bstrVal);
	params.rgvarg[0].vt=VT_BSTR;
	CCMSInterfaceCtrl::getInstance()->CallJs(A2W(cb),params);
	/* if(NULL!=cb){
      CMSBOX(cb);
	 }*/
    }
	return 0;
}
/*

http上传过程函数
void *clientp Js回调函数名 
double dltotal 下载总字节数
double dlnow   目前下载的字节数
double ultotal 上传总字节数
double ulnow   目前上传字节数
*/


int http_upload_progress(void *clientp,double dltotal,double dlnow,double ultotal,double ulnow)
{
	USES_CONVERSION;
	char * cb=(char*)clientp;
	if(ultotal>0&&ulnow>0&&ceil((ulnow/ultotal*100))<=100)
	{
		char b[1024]={0};
		sprintf_s(b,"%g",ulnow/ultotal*100);
		//CMSBOX(b);
		CComBSTR bstr(b); 
		DISPPARAMS params={0};
		params.cArgs=1;
		params.rgvarg=new VARIANT[params.cArgs];
		bstr.CopyTo(&params.rgvarg[0].bstrVal);
		params.rgvarg[0].vt=VT_BSTR;
		CCMSInterfaceCtrl::getInstance()->CallJs(A2W(cb),params);
		/* if(NULL!=cb){
		CMSBOX(cb);
		}*/
	}
	return 0;
}

/**
const char * file_name 上传文件绝对路径
const char * new_name  重命名文件名
const char* user       ftp用户名
const char* pwd        ftp密码
const char* call_back  js回调函数
*/
int _doFtpUpload(const char* ftpurl,const char* file_name,const char* new_name,const char* user,const char* pwd,const char* call_back){
    USES_CONVERSION;
	CURL *curl=NULL;
	//CURL *query_curl=NULL;
	CURLcode res;
	//CURLcode qres;
	FILE *hd_src;
    vector<string> dirVector;
	char *file_base_name=NULL;
	char *new_file_base_name=NULL;
	struct stat file_info;
	curl_off_t fsize;
	errno_t err;
	static  char buf_1 [128] ={0};
	static  char buf_2 [128] ={0};
	static  char buf_3 [16]={0};
	static char buf_error[32]={0};
	static char buf_remote_url [1024]={0};
	static char buf_usr_pwd[128]={0};
	static char buf_mkdir[64]={0};
	static char buf_type[64]={0};
	static char new_file_path[255]={0};
	//static char query_buffer[64]={0};
	struct curl_slist *headerlist=NULL;
	//struct curl_slist *mkdirlist=NULL;
	//struct curl_slist *querylist=NULL;
	if((file_base_name=basename(file_name))==NULL){
		CMSBOX(file_base_name);
		return 1;
	}
	//CMSBOX("ok");
	//MessageBoxA(NULL,file_base_name,file_base_name,MB_OK);
	sprintf_s(buf_remote_url,"%s%s",ftpurl,file_base_name);
	
	//printf("%s\n",buf_remote_url);
	if(NULL!=new_name)
	{
       if(NULL==filepath(new_name,new_file_path))
	   {
          CMSBOX("new file no path");
	      //return 1;
	   }else{
		   //CMSBOX(new_file_path);
		   char *token=NULL;
		   char *next_token=NULL;
		   sprintf_s(buf_remote_url,"%s%s%s",ftpurl,new_file_path+1,file_base_name);
		/*   sprintf_s(query_buffer,"NLST  %s",new_file_path+1);
		   CMSBOX(query_buffer);*/
		   //curl_slist_append(querylist,query_buffer);
		  // token=strtok_s(new_file_path,"/",&next_token);
    //       if(NULL!=token)
		  // {
				//dirVector.push_back(token);
		  // }
		  // while((token=strtok_s(NULL,"/",&next_token))!=NULL){
    //            dirVector.push_back(token);
		  // }
	   }
	   if((new_file_base_name=basename(new_name))==NULL)
	   {
            CMSBOX("new file no basename");
		   //return 1;
	   }else
	   {
		  // CMSBOX(new_file_base_name);
	   }
	}

	if(NULL==new_name)new_name=file_name;
	curl = curl_easy_init();
	//query_curl=curl_easy_init();

	if(new_file_base_name!=NULL){
		sprintf_s(buf_1,"RNFR %s", file_base_name);
		sprintf_s(buf_2,"RNTO %s", new_name);
	}
	sprintf_s(buf_3,"MODE S");
    sprintf_s(buf_type,"TYPE I");
	if(stat(file_name, &file_info)) {
		char b_err[128]={0};
		CMSBOX(b_err);
		//sprintf_s(b_err,"Couldnt open '%s': %s\n", file_name, strerror_s(buf_error,32,errno));
		//MessageBoxA(NULL,b_err,b_err,MB_OK);
		return 1;
	}
	fsize = (curl_off_t)file_info.st_size;
	//printf("Local file size: %" CURL_FORMAT_CURL_OFF_T " bytes.\n", fsize);
	/* get a FILE * of the same file */
	err=fopen_s(&hd_src,file_name, "rb");
	if(err)
	{
		strerror_s(buf_error,32,err);
		CMSBOX(buf_error);
	//	printf("Couldnt open '%s': %s\n", file_name, strerror_s(buf_error,32,err));
		return 1;

	}
   /* if(strlen(new_file_path)!=0)
	{
		vector<string>::iterator it=dirVector.begin();
		while(it!=dirVector.end()){
            string mk_str("MKD ");
			mk_str.append(*it);
			mkdirlist=curl_slist_append(mkdirlist,mk_str.c_str());
			mk_str.clear();
			mk_str="CWD ";
            mk_str.append(*it);
			mkdirlist=curl_slist_append(mkdirlist,mk_str.c_str());
			it++;
		}
	}*/
	if(_stricmp(file_name,new_name)!=0)
	{
		headerlist = curl_slist_append(headerlist, buf_1);
		headerlist = curl_slist_append(headerlist, buf_2);
	}
	headerlist = curl_slist_append(headerlist, buf_3);
	/* we want to use our own read function */
	//curl_easy_setopt(curl, CURLOPT_READFUNCTION, read_callback);
	if(NULL!=user&&NULL!=pwd)
	{
		sprintf_s(buf_usr_pwd,"%s:%s",user,pwd);
		curl_easy_setopt(curl,CURLOPT_USERPWD,buf_usr_pwd);
		//curl_easy_setopt(query_curl,CURLOPT_USERPWD,buf_usr_pwd);
	}
   // curl_easy_setopt(query_curl,CURLOPT_URL, buf_remote_url);
	//curl_easy_setopt(query_curl,CURLOPT_POSTQUOTE,querylist);
    //qres=curl_easy_perform(query_curl);

	//if(qres){
	//	char curl_error[128]={0};
	//	sprintf_s(curl_error,"%s\n",curl_easy_strerror(qres));
	//	CMSBOX(curl_error);
	//}
	//curl_easy_cleanup(query_curl);
	curl_easy_setopt(curl, CURLOPT_UPLOAD, 1L);
	curl_easy_setopt(curl,CURLOPT_URL, buf_remote_url);
	curl_easy_setopt(curl,CURLOPT_PROGRESSFUNCTION,ftp_upload_progress);
	//CMSBOX(call_back);
	curl_easy_setopt(curl,CURLOPT_PROGRESSDATA,call_back);
	curl_easy_setopt(curl,CURLOPT_NOPROGRESS,0L);
	//curl_easy_setopt(curl,CURLOPT_PREQUOTE,
	//curl_easy_setopt(curl,CURLOPT_PREQUOTE,mkdirlist);
	curl_easy_setopt(curl,CURLOPT_FTP_CREATE_MISSING_DIRS,1L);
	curl_easy_setopt(curl, CURLOPT_POSTQUOTE, headerlist);
	curl_easy_setopt(curl, CURLOPT_READDATA, hd_src);
	curl_easy_setopt(curl, CURLOPT_INFILESIZE_LARGE,(curl_off_t)fsize);
	
	res = curl_easy_perform(curl);
	if(res)
	{
		char curl_error[128]={0};
		sprintf_s(curl_error,"%s\n",curl_easy_strerror(res));
		CMSBOX(curl_error);
		curl_slist_free_all (headerlist);
		curl_easy_cleanup(curl);
		fclose(hd_src);
		return 1;
	}
	curl_slist_free_all (headerlist);
	curl_easy_cleanup(curl);
	//CMSBOX(call_back);
	//CCMSInterfaceCtrl::getInstance()->CallJs(web2,A2W(call_back));
	fclose(hd_src); /* close the local file */
	return 0;
}
static int write_call_back(char *buffer,size_t size,size_t nitems,void *outstream)
{
	//fwrite(buffer,size,nitems,(FILE*)outstream);
	 sprintf_s((char*)outstream,102400,"%s",buffer);
	//wcout<<A2W(buffer)<<endl;
//	wcout<<(L"搜索啊啊啊三大")<<endl;
	return size*nitems;
}
static size_t http_read_callback(char *buffer, size_t size,size_t nitems,void *instream)
{

	// wcout<<(L"搜索啊啊啊三大")<<endl;
	return 0;
}
/**
const char * file_name 上传文件绝对路径
const char * new_name  重命名文件名
const char * user      用户名 
const char * pwd       密码
const char * call_back js回调函数
*/
int _doHttpUpload(const char* httpurl,const char* file_name,const char* new_name,const char*user,const char* pwd,const char* call_back)
{
    
	
	struct curl_httppost *post = NULL;
	struct curl_httppost *last = NULL;
	CURLcode              code;
	CURL                  *curl;
	char * file_base_name=NULL;
	static  char buf_1 [128] ={0};
	static  char buf_2 [128] ={0};
	static  char buf_3 [16]={0};
	static char buf_remote_url [128]={0};
	static char buf_usr_pwd[128]={0};
	if((file_base_name=basename(file_name))==NULL){
		return 1;
	}
	curl = curl_easy_init(); // init curl
	curl_formadd(&post, &last, CURLFORM_COPYNAME, "file", \
		CURLFORM_FILE, file_name, CURLFORM_END); // specify the file to upload
	curl_easy_setopt(curl, CURLOPT_HTTPPOST, post); // set HTTP POST data
	curl_easy_setopt(curl, CURLOPT_URL, httpurl); // set URL
	//curl_easy_setopt(curl,CURLOPT_WRITEFUNCTION,write_call_back);
	//curl_easy_setopt(curl,CURLOPT_WRITEDATA,http_read_data);		
	curl_easy_setopt(curl, CURLOPT_PROGRESSFUNCTION, http_upload_progress);
	curl_easy_setopt(curl,CURLOPT_PROGRESSDATA,call_back);
	code = curl_easy_perform(curl); // perform request
	curl_formfree(post); // free post
	if (code)
	{
		//perror(curl_easy_strerror(code));
        CMSBOX(curl_easy_strerror(code));
		return 1;
	}
	return 0;
}
int _doHttpGet(const char* httpurl,char* result_buffer)
{

	CURLcode              code;
	CURL                  *curl;
	curl = curl_easy_init(); // init curl
	curl_easy_setopt(curl, CURLOPT_URL, httpurl); // set URL
	curl_easy_setopt(curl,CURLOPT_WRITEFUNCTION,write_call_back);
	curl_easy_setopt(curl,CURLOPT_WRITEDATA,result_buffer);
	//curl_easy_setopt(curl,CURLOPT_READDATA,result_buffer);
	code = curl_easy_perform(curl); // perform request
	if (code)
	{
		//perror(curl_easy_strerror(code));
		  CMSBOX(curl_easy_strerror(code));
		return 1;
	}
	return 0;
}