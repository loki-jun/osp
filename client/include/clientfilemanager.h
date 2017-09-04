/*==========================================================                      
�ļ�����clientfilemanager.h
����ļ���clientcommon.h
ʵ�ֹ��ܣ��ļ�����ģ��ͷ�ļ�
���ߣ�
��Ȩ��
------------------------------------------------------------
�޸ļ�¼��
��  ��	   	  �汾		 �޸���		  �߶���      �޸ļ�¼
  
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

