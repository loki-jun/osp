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

void CFileManager::FileWrite(LPSTR lpstrFileName,u16 dwBufferId,u32 FileSize,u32 PackageId,u32 PackageNum,u16 IdCount)
{
	s8 achFileName[STRING_LENGTH] = CLIENT_FILE_PATH;
	strcat(achFileName,"\\");
	strcat(achFileName,lpstrFileName);

//	OspPrintf(TRUE,FALSE,"bufferid:%d,�ļ���С:%d,��id:%d\n",dwBufferId,FileSize,PackageId);

	ofstream out(achFileName, ios::binary|ios::app);
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
}
