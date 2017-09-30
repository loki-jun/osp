/*==========================================================                        
文件名：clientfilemanager.cpp
相关文件：
实现功能：实现客户端文件管理功能
作者：
版权：
------------------------------------------------------------
修改记录：
日  期	   	  版本		 修改人		  走读人      修改记录
  
===========================================================*/
#include <iostream>
#include <stdio.h>
#include <fstream>
//#include <direct.h>  
#include <io.h> 
#include "../include/clientcommon.h"
#include "../include/clientfilemanager.h"

using namespace std;

//extern CConfigData g_CConfigData;
extern CFileManager g_CFileManager;

void CheckSpace()
{

}


void WriteEmptyFile()
{
	
}


void CFileManager::FileDelete(s8* m_pbySFileName)
{
	s8 FileName[STRING_LENGTH] = CLIENT_FILE_PATH;
	strcat(FileName,"\\");
	strcat(FileName,m_pbySFileName);
	remove(FileName);


}


void CFileManager::CreateSpace(s8* m_pbySFileName,u32 m_dwFileSize)
{
	/*
	s8 FileName[STRING_LENGTH] = CLIENT_FILE_PATH;

	CreateDirectory(FileName, NULL);

	strcat(FileName,"\\");
	strcat(FileName,m_pbySFileName);
	FILE *fp;	
	fp=fopen(FileName,"wb+");
	fseek(fp, m_dwFileSize,SEEK_END);
	putw(0,fp);
    fclose(fp);
	*/



//	方法二
	s8 end=EOF;
	s8 FileName[STRING_LENGTH] = CLIENT_FILE_PATH;

    CreateDirectory(FileName, NULL);
	
	strcat(FileName,"\\");
	strcat(FileName,m_pbySFileName);

	OspLog(LOG_LVL_WARNING,"文件名：%s",m_pbySFileName);
	
	FILE *fp=fopen(FileName,"wb+"); 
	if(fp == NULL)
	{
		OspLog(LOG_LVL_WARNING,"开始创建空文件！");
	}
	
	fseek(fp,m_dwFileSize-1,SEEK_SET);   //将文件位置指针移动到文件末尾,-1是为了给后面要写入的“结束标志”留空间
	OspLog(LOG_LVL_WARNING,"seek有问题？");
	fwrite(&end,1,1,fp);
	OspLog(LOG_LVL_WARNING,"write有问题？");
	if(!fclose(fp))
	{
		OspLog(LOG_LVL_WARNING,"文件关闭失败！");
	}

	return;

/*
   方法三无法实现system中输入变量
	system("fsutil file createnew E:\\客户端测试文件夹\\lpstrFileName 1dwFileSize");
*/

}

void CFileManager::ReadAndGetConfigData(s8* pbyConfigName)//CConfigData m_cConfigInfo
{
	OspLog(LOG_LVL_DETAIL,"配置文件:%s\n",pbyConfigName);
	s8 achFileName[STRING_LENGTH] = CLIENT_FILE_PATH;

    CreateDirectory(achFileName, NULL);

	strcat(achFileName,"\\");
	strcat(achFileName, pbyConfigName);
	strcat(achFileName,".ini");

	FILE *fp;	
	fp=fopen(achFileName,"ab+");

	fclose(fp);


}

void CFileManager::FileWrite(s8* m_pbySFileName,u32 m_dwFileSize,u16 m_wPackageId,u16 m_wPackageSize,s8* m_pbyPackageContent,u16 wInstanceId)
{
	if (1 == wInstanceId)
	{
		//计算buffer中包的偏移量
		u32 dwShift = (m_wPackageId%PACKAGENUM_EACHBUFFER)*TransferSize;
		//判断是否是最后一包，不是最后一包则以TransferSize拷贝，是则以最后一包大小拷贝
		if ( m_dwFileSize/TransferSize != m_wPackageId)
		{
			
			g_CFileManager.setbufferone(m_pbyPackageContent,dwShift,TransferSize);
//			OspLog(LOG_LVL_DETAIL,"包偏移量：%d\n", dwShift);
//			OspLog(LOG_LVL_DETAIL,"包大小：%d\n", m_wPackageSize);
		}
		else
		{
//			OspLog(LOG_LVL_DETAIL,"********客户端接收最后一包数据*********\n");
			g_CFileManager.setbufferone(m_pbyPackageContent,dwShift,m_dwFileSize%TransferSize);
//			OspLog(LOG_LVL_DETAIL,"包偏移量：%d\n", dwShift);
//			OspLog(LOG_LVL_DETAIL,"包大小：%d\n", m_dwFileSize%TransferSize);
		}
		
		if (0 == (m_wPackageId+1)%PACKAGENUM_EACHBUFFER)
		{
			s8 achFileName[STRING_LENGTH] = CLIENT_FILE_PATH;
			//检查文件夹是否存在，不存在则创建
			CreateDirectory(achFileName, NULL);

			strcat(achFileName,"\\");
			strcat(achFileName,m_pbySFileName);
			ofstream cBufferToFile(achFileName, ios::binary|ios::app);
			cBufferToFile.write(g_CFileManager.getbufferone(),CLIENT_BUFFERSIZE);
			memset(g_CFileManager.getbufferone(),0x00,CLIENT_BUFFERSIZE);
//			OspLog(LOG_LVL_DETAIL,"***************客户端buffer计数****************\n");
			cBufferToFile.close();
		}
		else if (m_dwFileSize/TransferSize == m_wPackageId)
		{
			s8 achFileName[STRING_LENGTH] = CLIENT_FILE_PATH;

			CreateDirectory(achFileName, NULL);

			strcat(achFileName,"\\");
			strcat(achFileName,m_pbySFileName);
			ofstream cBufferToFile(achFileName, ios::binary|ios::app);
			cBufferToFile.write(g_CFileManager.getbufferone(),m_dwFileSize%CLIENT_BUFFERSIZE);
			memset(g_CFileManager.getbufferone(),0x00,CLIENT_BUFFERSIZE);
//			OspLog(LOG_LVL_DETAIL,"***************客户端buffer计数****************\n");
			cBufferToFile.close();
		}
	}
	else if (2 == wInstanceId)
	{
		//计算buffer中包的偏移量
		u32 dwShift = (m_wPackageId%PACKAGENUM_EACHBUFFER)*TransferSize;
		//判断是否是最后一包，不是最后一包则以TransferSize拷贝，是则以最后一包大小拷贝
		if ( m_dwFileSize/TransferSize != m_wPackageId)
		{
			
			g_CFileManager.setbuffertwo(m_pbyPackageContent,dwShift,TransferSize);
//			OspLog(LOG_LVL_DETAIL,"包偏移量：%d\n", dwShift);
//			OspLog(LOG_LVL_DETAIL,"包大小：%d\n", m_wPackageSize);
		}
		else
		{
//			OspLog(LOG_LVL_DETAIL,"********客户端接收最后一包数据*********\n");
			g_CFileManager.setbuffertwo(m_pbyPackageContent,dwShift,m_dwFileSize%TransferSize);
//			OspLog(LOG_LVL_DETAIL,"包偏移量：%d\n", dwShift);
//			OspLog(LOG_LVL_DETAIL,"包大小：%d\n", m_dwFileSize%TransferSize);
		}
		
		if (0 == (m_wPackageId+1)%PACKAGENUM_EACHBUFFER)
		{
			s8 achFileName[STRING_LENGTH] = CLIENT_FILE_PATH;

			CreateDirectory(achFileName, NULL);

			strcat(achFileName,"\\");
			strcat(achFileName,m_pbySFileName);
			ofstream cBufferToFile(achFileName, ios::binary|ios::app);
			cBufferToFile.write(g_CFileManager.getbuffertwo(),CLIENT_BUFFERSIZE);
			memset(g_CFileManager.getbuffertwo(),0x00,CLIENT_BUFFERSIZE);
//			OspLog(LOG_LVL_DETAIL,"***************客户端buffer计数****************\n");
			cBufferToFile.close();
		}
		else if (m_dwFileSize/TransferSize == m_wPackageId)
		{
			s8 achFileName[STRING_LENGTH] = CLIENT_FILE_PATH;

			CreateDirectory(achFileName, NULL);

			strcat(achFileName,"\\");
			strcat(achFileName,m_pbySFileName);
			ofstream cBufferToFile(achFileName, ios::binary|ios::app);
			cBufferToFile.write(g_CFileManager.getbuffertwo(),m_dwFileSize%CLIENT_BUFFERSIZE);
			memset(g_CFileManager.getbuffertwo(),0x00,CLIENT_BUFFERSIZE);
//			OspLog(LOG_LVL_DETAIL,"***************客户端buffer计数****************\n");
			cBufferToFile.close();
		}
	}
	else
	{
		//计算buffer中包的偏移量
		u32 dwShift = (m_wPackageId%PACKAGENUM_EACHBUFFER)*TransferSize;
		//判断是否是最后一包，不是最后一包则以TransferSize拷贝，是则以最后一包大小拷贝
		if ( m_dwFileSize/TransferSize != m_wPackageId)
		{
			
			g_CFileManager.setbufferthree(m_pbyPackageContent,dwShift,TransferSize);
//			OspLog(LOG_LVL_DETAIL,"包偏移量：%d\n", dwShift);
//			OspLog(LOG_LVL_DETAIL,"包大小：%d\n", m_wPackageSize);
		}
		else
		{
//			OspLog(LOG_LVL_DETAIL,"********客户端接收最后一包数据*********\n");
			g_CFileManager.setbufferthree(m_pbyPackageContent,dwShift,m_dwFileSize%TransferSize);
//			OspLog(LOG_LVL_DETAIL,"包偏移量：%d\n", dwShift);
//			OspLog(LOG_LVL_DETAIL,"包大小：%d\n", m_dwFileSize%TransferSize);
		}
		
		if (0 == (m_wPackageId+1)%PACKAGENUM_EACHBUFFER)
		{
			s8 achFileName[STRING_LENGTH] = CLIENT_FILE_PATH;


			CreateDirectory(achFileName, NULL);

			strcat(achFileName,"\\");
			strcat(achFileName,m_pbySFileName);
			ofstream cBufferToFile(achFileName, ios::binary|ios::app);
			cBufferToFile.write(g_CFileManager.getbufferthree(),CLIENT_BUFFERSIZE);
			memset(g_CFileManager.getbufferthree(),0x00,CLIENT_BUFFERSIZE);
//			OspLog(LOG_LVL_DETAIL,"***************客户端buffer计数****************\n");
			cBufferToFile.close();
		}
		else if (m_dwFileSize/TransferSize == m_wPackageId)
		{
			s8 achFileName[STRING_LENGTH] = CLIENT_FILE_PATH;

			CreateDirectory(achFileName, NULL);

			strcat(achFileName,"\\");
			strcat(achFileName,m_pbySFileName);
			ofstream cBufferToFile(achFileName, ios::binary|ios::app);
			cBufferToFile.write(g_CFileManager.getbufferthree(),m_dwFileSize%CLIENT_BUFFERSIZE);
			memset(g_CFileManager.getbufferthree(),0x00,CLIENT_BUFFERSIZE);
//			OspLog(LOG_LVL_DETAIL,"***************客户端buffer计数****************\n");
			cBufferToFile.close();
		}
	}


}
