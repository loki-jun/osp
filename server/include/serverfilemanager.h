/*==========================================================                      
文件名：serverfilemanager.h
相关文件：servercommon.h
实现功能：文件管理模块头文件
作者：
版权：
------------------------------------------------------------
修改记录：
日  期	   	  版本		 修改人		  走读人      修改记录
  
===========================================================*/

#ifndef _SERVERFILEMANAGER_H_
#define _SERVERFILEMANAGER_H_

#include "../include/servercommon.h"
#include "../../common/osp.h"
#include "../../common/macrodef.h"


class CReadFile
{
private:
	u32 m_dwBuffSize;
	s8 m_pbyFileName[STRING_LENGTH];
	u16 m_wPackageId;
	u16 m_wPackageSize;
	
public:
//	void FileRead(u16 m_wNameLen,s8* m_pbyFileName,u16 m_wPackageId,u16 m_wPackageSize,s8* m_pbyPackageContent){};
	void FileRead(LPSTR lpstrFileName,u32 dwFileSize, u16 wPackageId);

private:
	void ReadCache(){};
	
};





#endif