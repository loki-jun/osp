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

class CFileManager
{
private:
	u16 m_wFileNumber;
	u32 m_dwBuffSize;
	u32 m_dwBuffOne[dwBuffSize];
	u32 m_dwBuffTwo[dwBuffSize];
	u32 m_dwBuffThree[dwBuffSize];
	CConfigData *m_tConfigInfo[3];

public:
	boolean FileWrite(u16 m_wNameLen,s8* m_pbyFileName,u16 m_wPackageId,u16 m_wPackageSize,s8* m_pbyPackageContent){};
	boolean ReadAndGetConfigData(u16 m_wNameLen,s8* m_pbyFileName,struct m_tConfigData){};
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

