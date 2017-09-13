/*==========================================================                      
文件名：clientfilemanager.h
相关文件：clientcommon.h
实现功能：文件管理模块头文件
作者：
版权：
------------------------------------------------------------
修改记录：
日  期	   	  版本		 修改人		  走读人      修改记录
  
===========================================================*/

#ifndef _CLIENTFILEMANAGER_H_
#define _CLIENTFILEMANAGER_H_

#include "../include/clientcommon.h"

class CBuffer
{
private:
	s8 m_dwBuffer[CLIENT_BUFFERSIZE];
	u16 m_wBufferState;
};

class CConfigData
{
private:
	u16 m_wFileId;
	u16 m_wNameLen;
	s8 m_pbyCFileName[256];
	s8 m_pbySFileName[256];
	u16 m_wPartPackageId;
	u32 m_dwPackageSize;
};

class CFileManager
{
private:
	u16 m_wFileNumber;
	CBuffer m_cBuffer[3];
	CConfigData m_cConfigInfo[3];

public:
	void FileWrite(u16 m_wNameLen,s8* m_pbyFileName,u16 m_wPackageId,u16 m_wPackageSize,s8* m_pbyPackageContent){};
//	void ReadAndGetConfigData(u16 m_wNameLen,s8* m_pbyFileName,struct m_tConfigData){};
	void CreateSpace(LPSTR lpstrFileName,u32 dwFileSize);

private:
	void CheckSpace(){};
	void WriteEmptyFile(){};
	void FileDelete(){};

};





#endif