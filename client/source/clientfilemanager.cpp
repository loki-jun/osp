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
	fp=fopen(FileName,"w+");
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

void CFileManager::FileWrite(LPSTR lpstrFileName,u16 dwBufferId,u32 PackageNum,u32 PackageId)
{
	s8 achFileName[STRING_LENGTH] = CLIENT_FILE_PATH;
	strcat(achFileName,"\\");
	strcat(achFileName,lpstrFileName);


	ofstream out(lpstrFileName, ios::binary|ios::app);
	//�ж��Ƿ������һ�����������һ������TransferSizeд���ļ������������һ����Сд���ļ�
	if ( PackageNum != PackageId)
	{
		out.write(g_CFileManager.m_cBuffer[dwBufferId].m_dwBuffer,TransferSize);
	}
	else
	{
		out.write(g_CFileManager.m_cBuffer[dwBufferId].m_dwBuffer,(PackageNum*TransferSize)%TransferSize);
	}
	memset(g_CFileManager.m_cBuffer[dwBufferId].m_dwBuffer,0x00,sizeof(g_CFileManager.m_cBuffer[dwBufferId].m_dwBuffer));
	out.close();
}
