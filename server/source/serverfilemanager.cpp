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
#include "../include/servercommunication.h"
#include "../include/serverfilemanager.h"

using namespace std;
extern CServerApp g_CServerApp;
/**************************************************
���ļ����ݶ��뻺�棬
***************************************************/

/*
void CReadFile::ReadCache()
{

	
    if ((!in.eof())||(in.gcount() != 0))
    {
		
        if( OSP_OK != post(pMsg->srcid, SERVER_CLIENT_SENDFILEINFO_REQ, m_chFileStr, in.gcount(), pMsg->srcnode) )
        {
            OspPrintf( TRUE , FALSE , "CAliasInstance::InstanceEntry post  failed.\n" );
        }
        in.close();
        //OspDelay(1000);
    }
    else
    {
        printf("download file sucess \n");
        dwPosition = 0;
        post(pMsg->srcid, SERVER_CLIENT_ENDSEND_NOTIFY, NULL, 0, pMsg->srcnode);
        in.close();
        NextState(READY_STATE);
	}


}
*/


void CReadFile::FileRead(s8* m_pbySFileName,u32 m_dwFileSize,u16 m_wPackageId,u16 &m_wPackageSize,s8* pbyPackageContent)
{
	s8 achFileName[STRING_LENGTH] = SERVER_FILE_PATH;
	strcat(achFileName,"\\");
	strcat(achFileName,m_pbySFileName);

	ifstream in;
	
    in.open(achFileName,ios::in|ios::binary);
//	OspLog(LOG_LVL_DETAIL,"��������ȡ�ļ��ɹ�\n");



	while(0 == m_dwBufferNum)
	{
		m_cFilemgr.FileRead(m_cPackageInfo.m_pbySFileName,m_dwBufferNum,m_cPackageInfo.m_dwFileSize);
		m_dwBufferNum++;
	}
	
	//�жϰ�id�Ƿ��ڵ�ǰ�Ļ������������ȡ���ݲ����ͣ�����д��һ�����棬Ȼ����
	if (m_cPackageInfo.m_wPackageId >= (m_dwBufferNum-1)*PACKAGENUM_EACHBUFFER && 
		m_cPackageInfo.m_wPackageId < m_dwBufferNum*PACKAGENUM_EACHBUFFER)
	{
		ProcSendMsg(pcMsg);
	}
	else
	{
		//						OspLog(LOG_LVL_DETAIL,"���ڵ�ǰ������\n");
		//m_dwBufferNum++;
		OspPrintf(TRUE,FALSE,"�����������µĻ��棬buffer��Ϊ��%d\n",m_dwBufferNum);
		m_cFilemgr.FileRead(m_cPackageInfo.m_pbySFileName,m_cPackageInfo.m_wPackageId,&m_cPackageInfo.m_dwFileSize,&m_cPackageInfo.m_pbyPackageContent);
		m_dwBufferNum++;
		ProcSendMsg(pcMsg);				
	}
	
    u32 dwPosition = SERVER_BUFFERSIZE*dwBufferId;
	
    in.seekg(dwPosition,ios::beg);
    memset(m_Buffer,0x00,sizeof(CServerInstance::m_cFilemgr.m_Buffer));
//	if (dwBufferId != dwFileSize/SERVER_BUFFERSIZE)
//	{
		in.read(CServerInstance::m_cFilemgr.m_Buffer,sizeof(CServerInstance::m_cFilemgr.m_Buffer));
//	}
//	else
//	{
//		in.read(m_Buffer,sizeof(dwFileSize-dwBufferId*SERVER_BUFFERSIZE));
//	}
    
	in.close();
}