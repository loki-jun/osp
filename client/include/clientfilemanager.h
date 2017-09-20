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

#include "../include/clientcommon.h"


class CConfigData
{
private:
	u16 m_wFileId;
	u16 m_wNameLen;
	s8 m_pbyCFileName[STRING_LENGTH];
	s8 m_pbySFileName[STRING_LENGTH];
	u16 m_wPartPackageId;
	u32 m_dwPackageSize;
};

class CFileManager
{
private:
	s8 m_Bufferone[CLIENT_BUFFERSIZE];
	s8 m_Buffertwo[CLIENT_BUFFERSIZE];
	s8 m_Bufferthree[CLIENT_BUFFERSIZE];
	u16 m_wFileNumber;
	CConfigData m_cConfigInfo[MAX_CLIENT_INS_NUM];

public:
    CFileManager()
    {
		memset(m_Bufferone,0,sizeof(m_Bufferone));
		memset(m_Buffertwo,0,sizeof(m_Buffertwo));
		memset(m_Bufferthree,0,sizeof(m_Bufferthree));
    }
    ~CFileManager()
    {
    }
	s8* getbufferone()
	{
		return m_Bufferone;
	}
	s8* getbuffertwo()
	{
		return m_Buffertwo;
	}
	s8* getbufferthree()
	{
		return m_Bufferthree;
	}

	void setbufferone(s8* bufferone,u32 dwshiftone,u32 dwsizeone)
	{
		memcpy(m_Bufferone+dwshiftone,bufferone,dwsizeone);
	}
	void setbuffertwo(s8* buffertwo,u32 dwshifttwo,u32 dwsizetwo)
	{
		memcpy(m_Buffertwo+dwshifttwo,buffertwo,dwsizetwo);
	}
	void setbufferthree(s8* bufferthree,u32 dwshiftthree,u32 dwsizethree)
	{
		memcpy(m_Bufferthree+dwshiftthree,bufferthree,dwsizethree);
	}
public:
	void FileWrite(s8* m_pbySFileName,u32 m_dwFileSize,u16 m_wPackageId,u16 m_wPackageSize,s8* m_pbyPackageContent,u16 wInstanceId);
//	void ReadAndGetConfigData(u16 m_wNameLen,s8* m_pbyFileName,struct m_tConfigData){};
	void CreateSpace(s8* m_pbySFileName,u32 m_dwFileSize);


private:
	void CheckSpace(){};
	void WriteEmptyFile(){};
	void FileDelete(){};

};





#endif