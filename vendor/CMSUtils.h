
#pragma once

class CCMSUtils
{
public:
	CCMSUtils(void);
	~CCMSUtils(void);
	static BSTR doGetPathFiles(BSTR path_name);
	static BSTR doGetDriveFiles(void);
};
