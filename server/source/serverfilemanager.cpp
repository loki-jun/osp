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


/**************************************************
将文件内容读入缓存，
***************************************************/

/*
void CReadFile::ReadCache()
{

	
    if ((!in.eof())||(in.gcount() != 0))
    {
		
        if( OSP_OK != post(pMsg->srcid, SERVER_CLIENT_SENDFILEINFO_REQ, m_chFileStr, in.gcount(), pMsg->srcnode) )
        {
            OspPrintf( TRUE , FALSE , "CAliasInstance::InstanceEntry post  failed.\n" );
        }
        in.close();
        //OspDelay(1000);
    }
    else
    {
        printf("download file sucess \n");
        dwPosition = 0;
        post(pMsg->srcid, SERVER_CLIENT_ENDSEND_NOTIFY, NULL, 0, pMsg->srcnode);
        in.close();
        NextState(READY_STATE);
	}


}
*/


void CReadFile::FileRead(LPSTR lpstrFileName,u32 dwBufferId,u32 dwFileSize)
{
	s8 achFileName[STRING_LENGTH] = SERVER_FILE_PATH;
	strcat(achFileName,"\\");
	strcat(achFileName,lpstrFileName);

	ifstream in;
	
    in.open(achFileName,ios::in|ios::binary);
//	OspLog(LOG_LVL_DETAIL,"服务器读取文件成功\n");
	
    u32 dwPosition = SERVER_BUFFERSIZE*dwBufferId;
	
    in.seekg(dwPosition,ios::beg);
    memset(m_Buffer,0x00,sizeof(m_Buffer));
//	if (dwBufferId != (dwFileSize/SERVER_BUFFERSIZE+1))
//	{
		in.read(m_Buffer,sizeof(m_Buffer));
//	}
//	else
//	{
//		in.read(m_Buffer,sizeof(dwFileSize-dwBufferId*SERVER_BUFFERSIZE));
//	}
    
	in.close();
}