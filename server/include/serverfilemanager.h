/*==========================================================                      
�ļ�����serverfilemanager.h
����ļ���servercommon.h
ʵ�ֹ��ܣ��ļ�����ģ��ͷ�ļ�
���ߣ�
��Ȩ��
------------------------------------------------------------
�޸ļ�¼��
��  ��	   	  �汾		 �޸���		  �߶���      �޸ļ�¼
  
===========================================================*/

#ifndef _SERVERFILEMANAGER_H_
#define _SERVERFILEMANAGER_H_

#include "../include/servercommon.h"

class CReadFile
{
public://������Ϊprivate��ʹ��set,get�ӿڵ���
	//���ٻ���
	s8 m_Buffer[SERVER_BUFFERSIZE] ;
	s8 m_pbyFileName[STRING_LENGTH];
	//�������
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