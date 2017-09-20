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
private:
	//开辟缓存
	s8 m_Buffer[SERVER_BUFFERSIZE] ;
//	s8 m_pbyFileName[STRING_LENGTH];
//	u32 m_wPackageId;
//	u16 m_wPackageSize;

public:
    CReadFile()
    {
        clear();
//		m_dwBufferNum = 0;
//		m_wPackageId = 0;
		
    }
    ~CReadFile()
    {
    }
	void clear()
	{
		memset(m_Buffer,0,sizeof(m_Buffer));
	}

	s8* getbuffer()
	{
		return m_Buffer;
	}
//	void setbuffer(s8* buffer)
//	{
//		memcpy(m_Buffer,buffer,sizeof(m_Buffer));
//	}

	
public:
//	void FileRead(u16 m_wNameLen,s8* m_pbyFileName,u16 m_wPackageId,u16 m_wPackageSize,s8* m_pbyPackageContent){};
	void FileRead(s8* m_pbySFileName,u32 m_dwFileSize,u16 m_wPackageId,u16 m_wPackageSize,s8* m_pbyPackageContent);

private:
	void ReadCache(){};
	
};





#endif