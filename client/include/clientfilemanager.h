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
	u32 m_dwBufferNum;
public:
    CBuffer()
    {
        m_wBufferState = 0;
		m_dwBufferNum = 0;
		memset(m_dwBuffer,0,sizeof(m_dwBuffer));
		
    }
    ~CBuffer()
    {
    }

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
	void FileWrite(LPSTR lpstrFileName,u16 dwBufferId,u32 FileSize,u32 PackageId,u32 PackageNum,u16 IdCount);
//	void ReadAndGetConfigData(u16 m_wNameLen,s8* m_pbyFileName,struct m_tConfigData){};
	void CreateSpace(LPSTR lpstrFileName,u32 dwFileSize);

private:
	void CheckSpace(){};
	void WriteEmptyFile(){};
	void FileDelete(){};

};





#endif