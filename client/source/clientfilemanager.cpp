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
#include "../include/clientcommon.h"
#include "../include/clientfilemanager.h"

using namespace std;

extern CConfigData g_CConfigData;
extern CFileManager g_CFileManager;

void CheckSpace()
{

}


void WriteEmptyFile()
{
	
}

void CFileManager::CreateSpace(LPSTR lpstrFileName,u32 dwFileSize)
{
	s8 FileName[STRING_LENGTH] = CLIENT_FILE_PATH;
	strcat(FileName,"\\");
	strcat(FileName,lpstrFileName);
	FILE *fp;	
	fp=fopen(FileName,"wb+");
	fseek(fp, dwFileSize,SEEK_END);
	putw(0,fp);
    fclose(fp);


/*
//	方法二
	s8 end=EOF;
	s8 FileName[STRING_LENGTH] = "E:\\客户端测试文件夹\\";
	strcat(FileName,lpstrFileName);
	FILE *fp=fopen(FileName,"wb+"); 
	fseek(fp,dwFileSize-1,SEEK_SET);   //将文件位置指针移动到文件末尾,-1是为了给后面要写入的“结束标志”留空间
	fwrite(&end,1,1,fp);
	fclose(fp);
*/


/*
   方法三无法实现system中输入变量
	system("fsutil file createnew E:\\客户端测试文件夹\\lpstrFileName 1dwFileSize");
*/

}

void CFileManager::FileWrite(s8* m_pbySFileName,u32 m_dwFileSize,u16 m_wPackageId,u16 m_wPackageSize,s8* m_pbyPackageContent)
{
	
/*

	
	//判断buffer是否写满，写满则将buffer写到文件中，否则应该是最后一个buffer的情况
	if ( PackageId == ((dwBufferId+1)*PACKAGENUM_EACHBUFFER-1))
	{
		out.write(g_CFileManager.m_cBuffer[IdCount].m_dwBuffer,sizeof(g_CFileManager.m_cBuffer[IdCount].m_dwBuffer));
	}
	else
	{
		out.write(g_CFileManager.m_cBuffer[IdCount].m_dwBuffer,FileSize-dwBufferId*CLIENT_BUFFERSIZE);
//		OspPrintf(TRUE,FALSE,"文件大小:%d,传输大小:%d,最后一个buffer大小:%d\n",FileSize,TransferSize,FileSize-dwBufferId*CLIENT_BUFFERSIZE);
	}
	memset(g_CFileManager.m_cBuffer[IdCount].m_dwBuffer,0x00,sizeof(g_CFileManager.m_cBuffer[IdCount].m_dwBuffer));
	out.close();
*/
//    OspLog(LOG_LVL_DETAIL,"客户端开始写文件！\n");
	
	//计算buffer中包的偏移量
	u32 dwShift = (m_wPackageId%PACKAGENUM_EACHBUFFER)*TransferSize;
	//判断是否是最后一包，不是最后一包则以TransferSize拷贝，是则以最后一包大小拷贝
	if ( m_dwFileSize/TransferSize != m_wPackageId)
	{
		
		g_CFileManager.setbufferone(m_pbyPackageContent,dwShift,TransferSize);
		OspLog(LOG_LVL_DETAIL,"包偏移量：%d\n", dwShift);
//		OspLog(LOG_LVL_DETAIL,"内容长度：%d\n", sizeof(m_pbyPackageContent));
//		OspLog(LOG_LVL_DETAIL,"包内容：%s\n", m_pbyPackageContent);
		//		post(pcMsg->srcid, S_C_DOWNLOADDATA_ACK, &m_cPackageInfo, sizeof(m_cPackageInfo), pcMsg->srcnode);
	}
	else
	{
		OspLog(LOG_LVL_DETAIL,"客户端接收最后一包数据\n");
//		m_wPackageSize = m_dwFileSize%TransferSize;
		g_CFileManager.setbufferone(m_pbyPackageContent,dwShift,m_dwFileSize%TransferSize);
		OspLog(LOG_LVL_DETAIL,"包偏移量：%d\n", dwShift);
//		OspLog(LOG_LVL_DETAIL,"包内容长度：%d\n", sizeof(m_pbyPackageContent));
//		OspLog(LOG_LVL_DETAIL,"包内容：%s\n", m_pbyPackageContent);
		//		post(pcMsg->srcid, S_C_DOWNLOADDATA_ACK, &m_cPackageInfo, sizeof(m_cPackageInfo), pcMsg->srcnode);
		//		m_cPackageInfo.printf();
		//		NextState(READY_STATE);
	}



	if ((PACKAGENUM_EACHBUFFER == m_wPackageId) || (m_dwFileSize/TransferSize == m_wPackageId))
	{
		s8 achFileName[STRING_LENGTH] = CLIENT_FILE_PATH;
		strcat(achFileName,"\\");
		strcat(achFileName,m_pbySFileName);
	    ofstream cBufferToFile(achFileName, ios::binary|ios::app);
		cBufferToFile.write(g_CFileManager.getbufferone(),sizeof(g_CFileManager.getbufferone()));
		memset(g_CFileManager.getbufferone(),0x00,sizeof(g_CFileManager.getbufferone()));
		OspLog(LOG_LVL_DETAIL,"客户端buffer计数\n");
		cBufferToFile.close();
	}
	
	
}
