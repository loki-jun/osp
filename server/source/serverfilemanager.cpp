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


/**************************************************
���ļ����ݶ��뻺�棬
***************************************************/
void CReadFile::ReadCache(LPSTR lpstrFileName,u32 dwBufferNum)
{
	s8 achFileName[STRING_LENGTH] = SERVER_FILE_PATH;
	strcat(achFileName,"\\");
	strcat(achFileName,lpstrFileName);
	
//    u32 dwBufferNum =0;
//	u32 MaxBufferId = dwFileSize/SERVER_BUFFERSIZE;

	fstream out;
	out.open(achFileName,ios::in|ios::binary);
	u32 dwPosition = SERVER_BUFFERSIZE*dwBufferNum;
	out.seekg(dwPosition,ios::beg);

	out.getline(m_Buffer,SERVER_BUFFERSIZE,'\n');//getline(char *,int,char) ��ʾ�����ַ��ﵽ256�����������оͽ���
	out.close();
}


void CReadFile::FileRead(LPSTR lpstrFileName,u32 dwFileSize, u16 wPackageId)
{



    u32 dwBufferNum =0;
	u32 MaxBufferId = dwFileSize/SERVER_BUFFERSIZE;

	for (dwBufferNum = 0; dwBufferNum <= MaxBufferId; dwBufferNum++ )
	{

		fstream out;
		out.open(achFileName,ios::in|ios::binary);
		u32 dwPosition = SERVER_BUFFERSIZE*dwBufferNum;
		out.seekg(dwPosition,ios::beg);

//		while(!out.eof())
//		{
			out.getline(m_Buffer,SERVER_BUFFERSIZE,'\n');//getline(char *,int,char) ��ʾ�����ַ��ﵽ256�����������оͽ���

//		}
        out.close();

		ReadCache(LPSTR lpstrFileName,u32 dwFileSize,u32 dwBufferNum);


	}



}