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
//extern CReadFile m_cFilemgr;

/**************************************************
将文件内容读入缓存，
***************************************************/

void CReadFile::FileRead(s8* m_pbySFileName,u32 m_dwFileSize,u16 m_wPackageId,u16 m_wPackageSize,s8* m_pbyPackageContent)
//void CReadFile::FileRead(LPSTR lpstrFileName,u32 dwBufferId,u32 dwFileSize)
{
	s8 achFileName[STRING_LENGTH] = SERVER_FILE_PATH;
	strcat(achFileName,"\\");
	strcat(achFileName,m_pbySFileName);
	
    
//	OspLog(LOG_LVL_DETAIL,"服务器读取文件成功\n");
	
    
	
	if ((0 == m_wPackageId%PACKAGENUM_EACHBUFFER) || (0 == m_wPackageId))
	{
//		OspLog(LOG_LVL_DETAIL,"服务器开始读取文件\n");
		ifstream cFileToBuffer;
		cFileToBuffer.open(achFileName,ios::in|ios::binary);
		u32 dwPosition = m_wPackageId*TransferSize;
		cFileToBuffer.seekg(dwPosition,ios::beg);
//		CFilemgr.setbuffer(0x00);
//		memset(m_Buffer,0x00,sizeof(m_Buffer));
		cFileToBuffer.read(getbuffer(),SERVER_BUFFERSIZE);
//		cout << sizeof(getbuffer()) << endl; //直接sizeof取大小值为4，出错
		cFileToBuffer.close();
	}
	
	//计算buffer中包的偏移量
	u32 dwShift = (m_wPackageId%PACKAGENUM_EACHBUFFER)*TransferSize;
	//判断是否是最后一包，不是最后一包则以TransferSize拷贝，是则以最后一包大小拷贝
	if ( m_dwFileSize/TransferSize != m_wPackageId)
	{
//		OspLog(LOG_LVL_DETAIL,"服务器发送包数据\n");
		memset(m_pbyPackageContent,0x00,sizeof(m_pbyPackageContent));
		memcpy(m_pbyPackageContent,getbuffer()+dwShift,TransferSize);
	}
	else
	{
		OspLog(LOG_LVL_DETAIL,"服务器发送最后一包数据\n");
		m_wPackageSize = m_dwFileSize%TransferSize;
		memset(m_pbyPackageContent,0x00,sizeof(m_pbyPackageContent));
		memcpy(m_pbyPackageContent,getbuffer()+dwShift,m_dwFileSize%TransferSize);
		OspLog(LOG_LVL_DETAIL,"包大小：%d\n",m_dwFileSize%TransferSize);
	}
    
//	if (dwBufferId != (dwFileSize/SERVER_BUFFERSIZE+1))
//	{
		
//	}
//	else
//	{
//		in.read(m_Buffer,sizeof(dwFileSize-dwBufferId*SERVER_BUFFERSIZE));
//	}
    
	
}