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

using namespace std;

void CheckSpace()
{

}


void WriteEmptyFile()
{
	
}

void CFileManager::CreateSpace(LPSTR lpstrFileName,u32 dwFileSize)
{
	s8 FileName[STRING_LENGTH];
	memcpy(FileName,&lpstrFileName,sizeof(FileName));
	cout << FileName << endl;
//	cout << dwFileSize << endl;
	system("fsutil file createnew FileName dwFileSize");
}