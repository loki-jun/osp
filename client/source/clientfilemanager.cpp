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
	fp=fopen(FileName,"w+");
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

void CFileManager::FileWrite(LPSTR lpstrFileName,u16 dwBufferId,u32 PackageNum,u32 PackageId)
{
	s8 achFileName[STRING_LENGTH] = CLIENT_FILE_PATH;
	strcat(achFileName,"\\");
	strcat(achFileName,lpstrFileName);


	ofstream out(lpstrFileName, ios::binary|ios::app);
	//判断是否是最后一包，不是最后一包则以TransferSize写到文件，是则以最后一包大小写到文件
	if ( PackageNum != PackageId)
	{
		out.write(g_CFileManager.m_cBuffer[dwBufferId].m_dwBuffer,TransferSize);
	}
	else
	{
		out.write(g_CFileManager.m_cBuffer[dwBufferId].m_dwBuffer,(PackageNum*TransferSize)%TransferSize);
	}
	memset(g_CFileManager.m_cBuffer[dwBufferId].m_dwBuffer,0x00,sizeof(g_CFileManager.m_cBuffer[dwBufferId].m_dwBuffer));
	out.close();
}
