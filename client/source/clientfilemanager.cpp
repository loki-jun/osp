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

#include "../include/clientfilemanager.h"
#include "../../common/osp.h"
#include <WINDOWS.H>
#include <iostream>
#include "../../common/macrodef.h"
#include <stdio.h>

using namespace std;

void CheckSpace()
{

}


void WriteEmptyFile()
{
	
}

void CFileManager::CreateSpace(LPSTR lpstrFileName,u32 dwFileSize)
{
	s8 FileName[STRING_LENGTH] = "E:\\�ͻ��˲����ļ���\\";
	strcat(FileName,lpstrFileName);
	FILE *fp;	
	fp=fopen(FileName,"w+");
	fseek(fp, dwFileSize,SEEK_END);
	putw(0,fp);
    fclose(fp);

/*
	������
	s8 end=EOF;
	s8 FileName[STRING_LENGTH] = "E:\\�ͻ��˲����ļ���\\";
	strcat(FileName,lpstrFileName);
	FILE *fp=fopen(FileName,"w+"); 
	fseek(fp,dwFileSize-1,SEEK_SET);   //���ļ�λ��ָ���ƶ����ļ�ĩβ,-1��Ϊ�˸�����Ҫд��ġ�������־�����ռ�
	fwrite(&end,1,1,fp);
	fclose(fp);
*/


/*
   �������޷�ʵ��system���������
	system("fsutil file createnew E:\\�ͻ��˲����ļ���\\lpstrFileName 1dwFileSize");
*/

}
