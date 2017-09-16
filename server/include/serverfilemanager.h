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

class CReadFile
{
public://后续改为private，使用set,get接口调用
	//开辟缓存
	s8 m_Buffer[SERVER_BUFFERSIZE] ;
	s8 m_pbyFileName[STRING_LENGTH];
	//缓存计数
//	u32 m_dwBufferNum;
	u32 m_wPackageId;
	u16 m_wPackageSize;

public:
    CReadFile()
    {
        memset(m_Buffer,0,sizeof(m_Buffer));
//		m_dwBufferNum = 0;
		m_wPackageId = 0;
		
    }
    ~CReadFile()
    {
    }
	
public:
//	void FileRead(u16 m_wNameLen,s8* m_pbyFileName,u16 m_wPackageId,u16 m_wPackageSize,s8* m_pbyPackageContent){};
	void FileRead(LPSTR lpstrFileName,u32 dwBufferId,u32 dwFileSize);

private:
	void ReadCache(){};
	
};





#endif