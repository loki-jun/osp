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
#include "../include/servercommunication.h"
#include "../include/serverfilemanager.h"

using namespace std;
extern CServerApp g_CServerApp;
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


void CReadFile::FileRead(s8* m_pbySFileName,u32 m_dwFileSize,u16 m_wPackageId,u16 &m_wPackageSize,s8* pbyPackageContent)
{
	s8 achFileName[STRING_LENGTH] = SERVER_FILE_PATH;
	strcat(achFileName,"\\");
	strcat(achFileName,m_pbySFileName);

	ifstream in;
	
    in.open(achFileName,ios::in|ios::binary);
//	OspLog(LOG_LVL_DETAIL,"服务器读取文件成功\n");



	while(0 == m_dwBufferNum)
	{
		m_cFilemgr.FileRead(m_cPackageInfo.m_pbySFileName,m_dwBufferNum,m_cPackageInfo.m_dwFileSize);
		m_dwBufferNum++;
	}
	
	//判断包id是否在当前的缓存区，在则读取数据并发送，不在写下一个缓存，然后发送
	if (m_cPackageInfo.m_wPackageId >= (m_dwBufferNum-1)*PACKAGENUM_EACHBUFFER && 
		m_cPackageInfo.m_wPackageId < m_dwBufferNum*PACKAGENUM_EACHBUFFER)
	{
		ProcSendMsg(pcMsg);
	}
	else
	{
		//						OspLog(LOG_LVL_DETAIL,"不在当前缓存中\n");
		//m_dwBufferNum++;
		OspPrintf(TRUE,FALSE,"服务器开辟新的缓存，buffer号为：%d\n",m_dwBufferNum);
		m_cFilemgr.FileRead(m_cPackageInfo.m_pbySFileName,m_cPackageInfo.m_wPackageId,&m_cPackageInfo.m_dwFileSize,&m_cPackageInfo.m_pbyPackageContent);
		m_dwBufferNum++;
		ProcSendMsg(pcMsg);				
	}
	
    u32 dwPosition = SERVER_BUFFERSIZE*dwBufferId;
	
    in.seekg(dwPosition,ios::beg);
    memset(m_Buffer,0x00,sizeof(CServerInstance::m_cFilemgr.m_Buffer));
//	if (dwBufferId != dwFileSize/SERVER_BUFFERSIZE)
//	{
		in.read(CServerInstance::m_cFilemgr.m_Buffer,sizeof(CServerInstance::m_cFilemgr.m_Buffer));
//	}
//	else
//	{
//		in.read(m_Buffer,sizeof(dwFileSize-dwBufferId*SERVER_BUFFERSIZE));
//	}
    
	in.close();
}