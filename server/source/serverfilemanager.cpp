/*==========================================================                        
文件名：serverfilemanager.cpp
相关文件：
实现功能：实现服务器文件管理功能
作者：
版权：
------------------------------------------------------------
修改记录：
日  期	   	  版本		 修改人		  走读人      修改记录
  
===========================================================*/
#include <iostream>
#include <stdio.h>
#include <fstream>
#include "../include/servercommon.h"
#include "../include/serverfilemanager.h"

using namespace std;

extern CPackageInfo PackageInfo;

void CReadFile::FileRead(LPSTR lpstrFileName,u32 dwFileSize, u16 wPackageId)
{

	s8 achFileName[STRING_LENGTH] = SERVER_FILE_PATH;
	strcat(achFileName,"\\");
	strcat(achFileName,lpstrFileName);

    u32 dwBufferNum =0;
	u32 MaxBufferId = dwFileSize/SERVER_BUFFERSIZE;

	for (dwBufferNum = 0; dwBufferNum <= MaxBufferId; dwBufferNum++ )
	{

		fstream out;
		out.open(achFileName,ios::in|ios::binary);
		u32 dwPosition = SERVER_BUFFERSIZE*dwBufferNum;
		out.seekg(dwPosition,ios::beg);

		while(!out.eof())
		{
			out.getline(m_Buffer,SERVER_BUFFERSIZE,'\n');//getline(char *,int,char) 表示该行字符达到256个或遇到换行就结束

		}
        out.close();

		u32 dwPackageNumber;
		u32 MaxPackageNum = SERVER_BUFFERSIZE/TransferSize;
		for (dwPackageNumber=0; dwPackageNumber < MaxPackageNum; dwPackageNumber++)
		{
			    OspLog(LOG_LVL_DETAIL,"测试服务器文件写功能");

		}
	}



}