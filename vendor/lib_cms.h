#ifndef LIB_CMS_H
#define LIB_CMS_H
#define LOCAL_FILE      "D:\\local\\upload.txt"
#define UPLOAD_FILE_AS  "remote2.txt"
#define REMOTE_URL      "ftp://192.168.117.129/"
#define RENAME_FILE_TO  "remote1.txt"
#define LOCAL_FILE_HTTP      "D:\\local\\upload.txt"
#define UPLOAD_FILE_HTTP_AS  "remote2.txt"
#define REMOTE_URL_HTTP      "http://www.pstore.com/Index/Test"
#define RENAME_FILE_HTTP_TO  "remote1.txt"
#define UPLOAD_URL "http://www.pstore.com/Index/Test/up"
#define CMSDEBUG
#ifdef CMSDEBUG
#define CMSBOX(msg) MessageBoxA(NULL,msg,msg,MB_OK); 
#define CMSBOXW(msg) AfxMessageBox(msg); 
#else

#endif
//LPWSTR A2W(const LPCSTR  src);
//LPCSTR W2A(const LPWSTR src);
 static char http_read_data[1024];
 char* basename(const char* file_name);
 char* filepath(const char* file_name,char *path_buffer);
 size_t read_callback(void *ptr, size_t size, size_t nmemb, void *stream);
 int write_call_back(char *buffer,size_t size,size_t nitems,void *outstream);
 size_t http_read_callback(char *buffer, size_t size,size_t nitems,void *instream);
int _file_exists(const char *file);
int _doFtpUpload(const char* ftpurl,const char* file_name,const char* new_name=NULL,const char* user="cms",const char* pwd="cms",const char* call_back=NULL);
int _doHttpUpload(const char* httpurl,const char* file_name,const char* new_name=NULL,const char*user=NULL,const char* pwd=NULL,const char* call_back=NULL);
int _doHttpGet(const char* httpurl,char* result_buffer);

#endif
