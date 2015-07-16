## cms断点上传activex插件 ##

---

## How To Use ##
```
<div>
<object name="cms" id="cms"  width="1024px" height="600px"  classid="clsid:C3F95086-97B7-47E7-95BD-EB3D6345B2D1">
       <PARAM NAME="ftpUrl" VALUE="ftp://127.0.0.1/" />
	   <PARAM NAME="ftpUser" VALUE="cms" />
	   <PARAM NAME="ftpPwd" VALUE="cms" />
	   <PARAM NAME="httpUrl" VALUE="http://127.0.0.1/Index/Test/up" />
	   <PARAM NAME="httpUser" VALUE="cms" />
	   <PARAM NAME="httpPwd" VALUE="cms" />
	   <PARAM NAME="uploadDir" VALUE="/cms/" />
	   <PARAM NAME="callBackUrl" VALUE="http://127.0.0.1/Test/Up" />
	  </object>
    </div>
```

---

## APIS ##
```
doGetDriveFiles()//return the disk directoris as JSON format
doGetPathFiles(path_name)//get the files in the specific folder
doFtpUpload(path_to_file,new_name,user_name,passwd,call_back_js_function_name)//
perform ftp upload an call the callback function if success 
```