/*==========================================================                        
�ļ�����clientfilemanager.cpp
����ļ���
ʵ�ֹ��ܣ�ʵ�ֿͻ����ļ�������
���ߣ�
��Ȩ��
------------------------------------------------------------
�޸ļ�¼��
��  ��	   	  �汾		 �޸���		  �߶���      �޸ļ�¼
  
===========================================================*/
#include <iostream>
#include <stdio.h>
#include <fstream>
//#include <direct.h>  
#include <io.h> 
#include "../include/clientcommon.h"
#include "../include/clientfilemanager.h"

using namespace std;

//extern CConfigData g_CConfigData;
extern CFileManager g_CFileManager;

void CheckSpace()
{

}


void WriteEmptyFile()
{
	
}


void CFileManager::FileDelete(s8* m_pbySFileName)
{
	s8 FileName[STRING_LENGTH] = CLIENT_FILE_PATH;
	strcat(FileName,"\\");
	strcat(FileName,m_pbySFileName);
	remove(FileName);


}


void CFileManager::CreateSpace(s8* m_pbySFileName,u32 m_dwFileSize)
{
	/*
	s8 FileName[STRING_LENGTH] = CLIENT_FILE_PATH;

	CreateDirectory(FileName, NULL);

	strcat(FileName,"\\");
	strcat(FileName,m_pbySFileName);
	FILE *fp;	
	fp=fopen(FileName,"wb+");
	fseek(fp, m_dwFileSize,SEEK_END);
	putw(0,fp);
    fclose(fp);
	*/



//	������
	s8 end=EOF;
	s8 FileName[STRING_LENGTH] = CLIENT_FILE_PATH;

    CreateDirectory(FileName, NULL);
	
	strcat(FileName,"\\");
	strcat(FileName,m_pbySFileName);

	OspLog(LOG_LVL_WARNING,"�ļ�����%s",m_pbySFileName);
	
	FILE *fp=fopen(FileName,"wb+"); 
	if(fp == NULL)
	{
		OspLog(LOG_LVL_WARNING,"��ʼ�������ļ���");
	}
	
	fseek(fp,m_dwFileSize-1,SEEK_SET);   //���ļ�λ��ָ���ƶ����ļ�ĩβ,-1��Ϊ�˸�����Ҫд��ġ�������־�����ռ�
	OspLog(LOG_LVL_WARNING,"seek�����⣿");
	fwrite(&end,1,1,fp);
	OspLog(LOG_LVL_WARNING,"write�����⣿");
	if(!fclose(fp))
	{
		OspLog(LOG_LVL_WARNING,"�ļ��ر�ʧ�ܣ�");
	}

	return;

/*
   �������޷�ʵ��system���������
	system("fsutil file createnew E:\\�ͻ��˲����ļ���\\lpstrFileName 1dwFileSize");
*/

}

void CFileManager::ReadAndGetConfigData(s8* pbyConfigName)//CConfigData m_cConfigInfo
{
	OspLog(LOG_LVL_DETAIL,"�����ļ�:%s\n",pbyConfigName);
	s8 achFileName[STRING_LENGTH] = CLIENT_FILE_PATH;

    CreateDirectory(achFileName, NULL);

	strcat(achFileName,"\\");
	strcat(achFileName, pbyConfigName);
	strcat(achFileName,".ini");

	FILE *fp;	
	fp=fopen(achFileName,"ab+");

	fclose(fp);


}

void CFileManager::FileWrite(s8* m_pbySFileName,u32 m_dwFileSize,u16 m_wPackageId,u16 m_wPackageSize,s8* m_pbyPackageContent,u16 wInstanceId)
{
	if (1 == wInstanceId)
	{
		//����buffer�а���ƫ����
		u32 dwShift = (m_wPackageId%PACKAGENUM_EACHBUFFER)*TransferSize;
		//�ж��Ƿ������һ�����������һ������TransferSize���������������һ����С����
		if ( m_dwFileSize/TransferSize != m_wPackageId)
		{
			
			g_CFileManager.setbufferone(m_pbyPackageContent,dwShift,TransferSize);
//			OspLog(LOG_LVL_DETAIL,"��ƫ������%d\n", dwShift);
//			OspLog(LOG_LVL_DETAIL,"����С��%d\n", m_wPackageSize);
		}
		else
		{
//			OspLog(LOG_LVL_DETAIL,"********�ͻ��˽������һ������*********\n");
			g_CFileManager.setbufferone(m_pbyPackageContent,dwShift,m_dwFileSize%TransferSize);
//			OspLog(LOG_LVL_DETAIL,"��ƫ������%d\n", dwShift);
//			OspLog(LOG_LVL_DETAIL,"����С��%d\n", m_dwFileSize%TransferSize);
		}
		
		if (0 == (m_wPackageId+1)%PACKAGENUM_EACHBUFFER)
		{
			s8 achFileName[STRING_LENGTH] = CLIENT_FILE_PATH;
			//����ļ����Ƿ���ڣ��������򴴽�
			CreateDirectory(achFileName, NULL);

			strcat(achFileName,"\\");
			strcat(achFileName,m_pbySFileName);
			ofstream cBufferToFile(achFileName, ios::binary|ios::app);
			cBufferToFile.write(g_CFileManager.getbufferone(),CLIENT_BUFFERSIZE);
			memset(g_CFileManager.getbufferone(),0x00,CLIENT_BUFFERSIZE);
//			OspLog(LOG_LVL_DETAIL,"***************�ͻ���buffer����****************\n");
			cBufferToFile.close();
		}
		else if (m_dwFileSize/TransferSize == m_wPackageId)
		{
			s8 achFileName[STRING_LENGTH] = CLIENT_FILE_PATH;

			CreateDirectory(achFileName, NULL);

			strcat(achFileName,"\\");
			strcat(achFileName,m_pbySFileName);
			ofstream cBufferToFile(achFileName, ios::binary|ios::app);
			cBufferToFile.write(g_CFileManager.getbufferone(),m_dwFileSize%CLIENT_BUFFERSIZE);
			memset(g_CFileManager.getbufferone(),0x00,CLIENT_BUFFERSIZE);
//			OspLog(LOG_LVL_DETAIL,"***************�ͻ���buffer����****************\n");
			cBufferToFile.close();
		}
	}
	else if (2 == wInstanceId)
	{
		//����buffer�а���ƫ����
		u32 dwShift = (m_wPackageId%PACKAGENUM_EACHBUFFER)*TransferSize;
		//�ж��Ƿ������һ�����������һ������TransferSize���������������һ����С����
		if ( m_dwFileSize/TransferSize != m_wPackageId)
		{
			
			g_CFileManager.setbuffertwo(m_pbyPackageContent,dwShift,TransferSize);
//			OspLog(LOG_LVL_DETAIL,"��ƫ������%d\n", dwShift);
//			OspLog(LOG_LVL_DETAIL,"����С��%d\n", m_wPackageSize);
		}
		else
		{
//			OspLog(LOG_LVL_DETAIL,"********�ͻ��˽������һ������*********\n");
			g_CFileManager.setbuffertwo(m_pbyPackageContent,dwShift,m_dwFileSize%TransferSize);
//			OspLog(LOG_LVL_DETAIL,"��ƫ������%d\n", dwShift);
//			OspLog(LOG_LVL_DETAIL,"����С��%d\n", m_dwFileSize%TransferSize);
		}
		
		if (0 == (m_wPackageId+1)%PACKAGENUM_EACHBUFFER)
		{
			s8 achFileName[STRING_LENGTH] = CLIENT_FILE_PATH;

			CreateDirectory(achFileName, NULL);

			strcat(achFileName,"\\");
			strcat(achFileName,m_pbySFileName);
			ofstream cBufferToFile(achFileName, ios::binary|ios::app);
			cBufferToFile.write(g_CFileManager.getbuffertwo(),CLIENT_BUFFERSIZE);
			memset(g_CFileManager.getbuffertwo(),0x00,CLIENT_BUFFERSIZE);
//			OspLog(LOG_LVL_DETAIL,"***************�ͻ���buffer����****************\n");
			cBufferToFile.close();
		}
		else if (m_dwFileSize/TransferSize == m_wPackageId)
		{
			s8 achFileName[STRING_LENGTH] = CLIENT_FILE_PATH;

			CreateDirectory(achFileName, NULL);

			strcat(achFileName,"\\");
			strcat(achFileName,m_pbySFileName);
			ofstream cBufferToFile(achFileName, ios::binary|ios::app);
			cBufferToFile.write(g_CFileManager.getbuffertwo(),m_dwFileSize%CLIENT_BUFFERSIZE);
			memset(g_CFileManager.getbuffertwo(),0x00,CLIENT_BUFFERSIZE);
//			OspLog(LOG_LVL_DETAIL,"***************�ͻ���buffer����****************\n");
			cBufferToFile.close();
		}
	}
	else
	{
		//����buffer�а���ƫ����
		u32 dwShift = (m_wPackageId%PACKAGENUM_EACHBUFFER)*TransferSize;
		//�ж��Ƿ������һ�����������һ������TransferSize���������������һ����С����
		if ( m_dwFileSize/TransferSize != m_wPackageId)
		{
			
			g_CFileManager.setbufferthree(m_pbyPackageContent,dwShift,TransferSize);
//			OspLog(LOG_LVL_DETAIL,"��ƫ������%d\n", dwShift);
//			OspLog(LOG_LVL_DETAIL,"����С��%d\n", m_wPackageSize);
		}
		else
		{
//			OspLog(LOG_LVL_DETAIL,"********�ͻ��˽������һ������*********\n");
			g_CFileManager.setbufferthree(m_pbyPackageContent,dwShift,m_dwFileSize%TransferSize);
//			OspLog(LOG_LVL_DETAIL,"��ƫ������%d\n", dwShift);
//			OspLog(LOG_LVL_DETAIL,"����С��%d\n", m_dwFileSize%TransferSize);
		}
		
		if (0 == (m_wPackageId+1)%PACKAGENUM_EACHBUFFER)
		{
			s8 achFileName[STRING_LENGTH] = CLIENT_FILE_PATH;


			CreateDirectory(achFileName, NULL);

			strcat(achFileName,"\\");
			strcat(achFileName,m_pbySFileName);
			ofstream cBufferToFile(achFileName, ios::binary|ios::app);
			cBufferToFile.write(g_CFileManager.getbufferthree(),CLIENT_BUFFERSIZE);
			memset(g_CFileManager.getbufferthree(),0x00,CLIENT_BUFFERSIZE);
//			OspLog(LOG_LVL_DETAIL,"***************�ͻ���buffer����****************\n");
			cBufferToFile.close();
		}
		else if (m_dwFileSize/TransferSize == m_wPackageId)
		{
			s8 achFileName[STRING_LENGTH] = CLIENT_FILE_PATH;

			CreateDirectory(achFileName, NULL);

			strcat(achFileName,"\\");
			strcat(achFileName,m_pbySFileName);
			ofstream cBufferToFile(achFileName, ios::binary|ios::app);
			cBufferToFile.write(g_CFileManager.getbufferthree(),m_dwFileSize%CLIENT_BUFFERSIZE);
			memset(g_CFileManager.getbufferthree(),0x00,CLIENT_BUFFERSIZE);
//			OspLog(LOG_LVL_DETAIL,"***************�ͻ���buffer����****************\n");
			cBufferToFile.close();
		}
	}


}
