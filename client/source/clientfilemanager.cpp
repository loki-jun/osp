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

#include "../include/clientfilemanager.h"
#include "../../common/osp.h"
#include <WINDOWS.H>
#include <iostream>
#include "../../common/macrodef.h"

using namespace std;

void CheckSpace()
{

}


void WriteEmptyFile()
{
	
}

void CFileManager::CreateSpace(LPSTR lpstrFileName,u32 dwFileSize)
{
	s8 FileName[STRING_LENGTH];
	memcpy(FileName,&lpstrFileName,sizeof(FileName));
	cout << FileName << endl;
//	cout << dwFileSize << endl;
	system("fsutil file createnew FileName dwFileSize");
}