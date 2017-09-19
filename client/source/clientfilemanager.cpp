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
#include "../include/clientcommon.h"
#include "../include/clientfilemanager.h"

using namespace std;

extern CConfigData g_CConfigData;
extern CFileManager g_CFileManager;

void CheckSpace()
{

}


void WriteEmptyFile()
{
	
}

void CFileManager::CreateSpace(LPSTR lpstrFileName,u32 dwFileSize)
{
	s8 FileName[STRING_LENGTH] = CLIENT_FILE_PATH;
	strcat(FileName,"\\");
	strcat(FileName,lpstrFileName);
	FILE *fp;	
	fp=fopen(FileName,"wb+");
	fseek(fp, dwFileSize,SEEK_END);
	putw(0,fp);
    fclose(fp);


/*
//	������
	s8 end=EOF;
	s8 FileName[STRING_LENGTH] = "E:\\�ͻ��˲����ļ���\\";
	strcat(FileName,lpstrFileName);
	FILE *fp=fopen(FileName,"wb+"); 
	fseek(fp,dwFileSize-1,SEEK_SET);   //���ļ�λ��ָ���ƶ����ļ�ĩβ,-1��Ϊ�˸�����Ҫд��ġ�������־�����ռ�
	fwrite(&end,1,1,fp);
	fclose(fp);
*/


/*
   �������޷�ʵ��system���������
	system("fsutil file createnew E:\\�ͻ��˲����ļ���\\lpstrFileName 1dwFileSize");
*/

}

void CFileManager::FileWrite(s8* m_pbySFileName,u32 m_dwFileSize,u16 m_wPackageId,u16 m_wPackageSize,s8* m_pbyPackageContent)
{
	
/*

	
	//�ж�buffer�Ƿ�д����д����bufferд���ļ��У�����Ӧ�������һ��buffer�����
	if ( PackageId == ((dwBufferId+1)*PACKAGENUM_EACHBUFFER-1))
	{
		out.write(g_CFileManager.m_cBuffer[IdCount].m_dwBuffer,sizeof(g_CFileManager.m_cBuffer[IdCount].m_dwBuffer));
	}
	else
	{
		out.write(g_CFileManager.m_cBuffer[IdCount].m_dwBuffer,FileSize-dwBufferId*CLIENT_BUFFERSIZE);
//		OspPrintf(TRUE,FALSE,"�ļ���С:%d,�����С:%d,���һ��buffer��С:%d\n",FileSize,TransferSize,FileSize-dwBufferId*CLIENT_BUFFERSIZE);
	}
	memset(g_CFileManager.m_cBuffer[IdCount].m_dwBuffer,0x00,sizeof(g_CFileManager.m_cBuffer[IdCount].m_dwBuffer));
	out.close();
*/
//    OspLog(LOG_LVL_DETAIL,"�ͻ��˿�ʼд�ļ���\n");
	
	//����buffer�а���ƫ����
	u32 dwShift = (m_wPackageId%PACKAGENUM_EACHBUFFER)*TransferSize;
	//�ж��Ƿ������һ�����������һ������TransferSize���������������һ����С����
	if ( m_dwFileSize/TransferSize != m_wPackageId)
	{
		
		g_CFileManager.setbufferone(m_pbyPackageContent,dwShift,TransferSize);
		OspLog(LOG_LVL_DETAIL,"��ƫ������%d\n", dwShift);
//		OspLog(LOG_LVL_DETAIL,"���ݳ��ȣ�%d\n", sizeof(m_pbyPackageContent));
//		OspLog(LOG_LVL_DETAIL,"�����ݣ�%s\n", m_pbyPackageContent);
		//		post(pcMsg->srcid, S_C_DOWNLOADDATA_ACK, &m_cPackageInfo, sizeof(m_cPackageInfo), pcMsg->srcnode);
	}
	else
	{
		OspLog(LOG_LVL_DETAIL,"�ͻ��˽������һ������\n");
//		m_wPackageSize = m_dwFileSize%TransferSize;
		g_CFileManager.setbufferone(m_pbyPackageContent,dwShift,m_dwFileSize%TransferSize);
		OspLog(LOG_LVL_DETAIL,"��ƫ������%d\n", dwShift);
//		OspLog(LOG_LVL_DETAIL,"�����ݳ��ȣ�%d\n", sizeof(m_pbyPackageContent));
//		OspLog(LOG_LVL_DETAIL,"�����ݣ�%s\n", m_pbyPackageContent);
		//		post(pcMsg->srcid, S_C_DOWNLOADDATA_ACK, &m_cPackageInfo, sizeof(m_cPackageInfo), pcMsg->srcnode);
		//		m_cPackageInfo.printf();
		//		NextState(READY_STATE);
	}



	if ((PACKAGENUM_EACHBUFFER == m_wPackageId) || (m_dwFileSize/TransferSize == m_wPackageId))
	{
		s8 achFileName[STRING_LENGTH] = CLIENT_FILE_PATH;
		strcat(achFileName,"\\");
		strcat(achFileName,m_pbySFileName);
	    ofstream cBufferToFile(achFileName, ios::binary|ios::app);
		cBufferToFile.write(g_CFileManager.getbufferone(),sizeof(g_CFileManager.getbufferone()));
		memset(g_CFileManager.getbufferone(),0x00,sizeof(g_CFileManager.getbufferone()));
		OspLog(LOG_LVL_DETAIL,"�ͻ���buffer����\n");
		cBufferToFile.close();
	}
	
	
}
