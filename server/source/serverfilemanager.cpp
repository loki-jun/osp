/*==========================================================                        
�ļ�����serverfilemanager.cpp
����ļ���
ʵ�ֹ��ܣ�ʵ�ַ������ļ�������
���ߣ�
��Ȩ��
------------------------------------------------------------
�޸ļ�¼��
��  ��	   	  �汾		 �޸���		  �߶���      �޸ļ�¼
  
===========================================================*/
#include <iostream>
#include <stdio.h>
#include <fstream>
#include "../include/servercommon.h"
#include "../include/serverfilemanager.h"

using namespace std;
//extern CReadFile m_cFilemgr;

/**************************************************
���ļ����ݶ��뻺�棬
***************************************************/

void CReadFile::FileRead(s8* m_pbySFileName,u32 m_dwFileSize,u16 m_wPackageId,u16 m_wPackageSize,s8* m_pbyPackageContent)
//void CReadFile::FileRead(LPSTR lpstrFileName,u32 dwBufferId,u32 dwFileSize)
{
	s8 achFileName[STRING_LENGTH] = SERVER_FILE_PATH;
	strcat(achFileName,"\\");
	strcat(achFileName,m_pbySFileName);
	
    
//	OspLog(LOG_LVL_DETAIL,"��������ȡ�ļ��ɹ�\n");
	
    
	
	if ((0 == m_wPackageId%PACKAGENUM_EACHBUFFER) || (0 == m_wPackageId))
	{
//		OspLog(LOG_LVL_DETAIL,"��������ʼ��ȡ�ļ�\n");
		ifstream cFileToBuffer;
		cFileToBuffer.open(achFileName,ios::in|ios::binary);
		u32 dwPosition = m_wPackageId*TransferSize;
		cFileToBuffer.seekg(dwPosition,ios::beg);
//		CFilemgr.setbuffer(0x00);
//		memset(m_Buffer,0x00,sizeof(m_Buffer));
		cFileToBuffer.read(getbuffer(),SERVER_BUFFERSIZE);
//		cout << sizeof(getbuffer()) << endl; //ֱ��sizeofȡ��СֵΪ4������
		cFileToBuffer.close();
	}
	
	//����buffer�а���ƫ����
	u32 dwShift = (m_wPackageId%PACKAGENUM_EACHBUFFER)*TransferSize;
	//�ж��Ƿ������һ�����������һ������TransferSize���������������һ����С����
	if ( m_dwFileSize/TransferSize != m_wPackageId)
	{
//		OspLog(LOG_LVL_DETAIL,"���������Ͱ�����\n");
		memset(m_pbyPackageContent,0x00,sizeof(m_pbyPackageContent));
		memcpy(m_pbyPackageContent,getbuffer()+dwShift,TransferSize);
	}
	else
	{
		OspLog(LOG_LVL_DETAIL,"�������������һ������\n");
		m_wPackageSize = m_dwFileSize%TransferSize;
		memset(m_pbyPackageContent,0x00,sizeof(m_pbyPackageContent));
		memcpy(m_pbyPackageContent,getbuffer()+dwShift,m_dwFileSize%TransferSize);
		OspLog(LOG_LVL_DETAIL,"����С��%d\n",m_dwFileSize%TransferSize);
	}
    
//	if (dwBufferId != (dwFileSize/SERVER_BUFFERSIZE+1))
//	{
		
//	}
//	else
//	{
//		in.read(m_Buffer,sizeof(dwFileSize-dwBufferId*SERVER_BUFFERSIZE));
//	}
    
	
}