/*==========================================================                        
�ļ�����servercommunication.cpp
����ļ���
ʵ�ֹ��ܣ�������Ϣ�����Լ������ļ�����ģ��ӿ�
���ߣ�
��Ȩ��
------------------------------------------------------------
�޸ļ�¼��
��  ��	   	  �汾		 �޸���		  �߶���      �޸ļ�¼
  
===========================================================*/

#include <stdio.h>
#include <iostream>
#include <fstream> 
#include "../../common/kdvtype.h"
#include "../../common/osp.h"
#include "../../common/kdvdef.h"
#include "../../common/csmsg.h"
#include "../../common/macrodef.h"
#include "../include/servercommon.h"
#include "../include/servercommunication.h"
#include "../include/servercreatefilelist.h"

using namespace std;

CServerApp g_CServerApp;

CFileInfo FileInfo;
CFileListInfo FileListInfo;
/*********************************************************************
    ��ʼ������
*********************************************************************/
void UserInit()
{
	if( !( IsOspInitd( ) ) )
	{
		// ��ʼ��Osp, �ڶ˿�2502����Telnet
		BOOL32 bRetOspinit = OspInit( TRUE, SERVER_TELENT_PORT );         		
		if( !bRetOspinit )
		{	
			OspLog(LOG_LVL_ERROR,"***��ʼ��ospʧ��***");
			return ;
		}
	}

	// ��6682�˿��ϴ������ؼ������ 
//	u32 dwRetCreateTcpNode = OspCreateTcpNode( inet_addr("127.0.0.1"), SERVER_LISTEN_PORT );   
	u32 dwRetCreateTcpNode = OspCreateTcpNode( 0, SERVER_LISTEN_PORT );	
	if( dwRetCreateTcpNode == INVALID_SOCKET )
	{
		OspLog(LOG_LVL_ERROR,"***���������ڵ�ʧ��***");
		return;
	}
	
	//����APP	
	g_CServerApp.CreateApp( SERVER_APP_NAME, 
		SERVER_APP_NO,  
		SERVER_APP_PRIO, 
		SERVER_APP_QUE_SIZE);	
	
	OspLog(LOG_LVL_DETAIL,"***��ʼ���ɹ�***");
	return ;
}


/*********************************************************************
    DaemonDealClientConnect����
*********************************************************************/

void CServerInstance::DaemonDealClientConnect(CMessage *const pcMsg, CApp* pcApp)
{
	if ( g_CServerApp.m_dwNodeNum <= MAX_SERVER_NODE_SIZE)
	{
		post(pcMsg->srcid, S_C_CONNECT_ACK,NULL,0,pcMsg->srcnode);
	}
	else
	{
        post(pcMsg->srcid, S_C_CONNECT_NACK,NULL,0,pcMsg->srcnode);
	}
	/*
    u16 curEvent = pcMsg->event;
	CServerInstance* pCInstance = NULL;
    u32 dwInsCout=0;

    for( dwInsCout = 1; dwInsCout <= MAX_SERVER_INS_NUM; dwInsCout++)
    {
        pCInstance = (CServerInstance* )pcApp->GetInstance(dwInsCout);
        if ( IDLE_STATE == pCInstance->CurState() )
        {
            post(pcMsg->srcid, S_C_CONNECT_ACK,NULL,0,pcMsg->srcnode);
            pCInstance->NextState(READY_STATE);
            break;
        }
    }
    if ( MAX_SERVER_INS_NUM < dwInsCout )
    {
        OspPost(MAKEIID(pcMsg->srcid, DAEMON), S_C_CONNECT_NACK, pcMsg->content, sizeof(u32));
    }
	*/
}

/*********************************************************************
    ��ȡ�ļ��б���
*********************************************************************/
void CServerInstance::DaemonGetlist(CMessage *const pcMsg)
{
	FindFiles ff;
	FindSizes ss;
	FindMd5   mm;
	vector<string> fileNames;
	vector<u32> fileSizes;
	vector<u32> filemd5s;
	
	fileNames = ff.findFiles( "E:\\�����ļ���" );
	fileSizes = ss.findSizes("E:\\�����ļ���");
	filemd5s = mm.findMd5("E:\\\\�����ļ���");  //md5ֵû��get����ò�Ƽ�������ַ��������顭��

	FileListInfo.m_wFileNum = fileNames.size();

//    cout << FileListInfo.m_pbyFileInfo[500].m_pbyFileName << endl;

	u16 wCount = 0;
	for ( wCount =0; wCount<fileNames.size(); wCount++ )
 	{      
		
		memcpy(&FileInfo.m_dwFileSize,&fileSizes[wCount],sizeof(FileInfo.m_dwFileSize));
		memcpy(&FileInfo.m_pbyFileName,&fileNames[wCount][0u],sizeof(FileInfo.m_pbyFileName));

		post(pcMsg->srcid,S_C_GETLIST_ACK, (u8 *)&FileInfo,sizeof(FileInfo),pcMsg->srcnode);
		
	}	
//	cout << FileListInfo.m_pbyFileInfo << endl;
}

/*********************************************************************
    �ļ�У�麯��
*********************************************************************/
void CServerInstance::ProcCheckFile(CMessage *const pcMsg)
{
//	cout << "����check����" << endl;
	FindFiles ff;
	FindSizes ss;

	vector<string> fileNames;
	vector<u32> fileSizes;

	fileNames = ff.findFiles( "E:\\�����ļ���" );
	fileSizes = ss.findSizes("E:\\�����ļ���");

	u16 wCount = 0;
	for ( wCount =0; wCount<fileNames.size(); wCount++ )
	{   
		s8 achFileName[STRING_LENGTH];
		s8 achServerFileName[STRING_LENGTH];
		memcpy(&achFileName,pcMsg->content,pcMsg->length);
		memcpy(&achServerFileName,&fileNames[wCount][0u],STRING_LENGTH);

		memcpy(&FileInfo.m_dwFileSize,&fileSizes[wCount],sizeof(FileInfo.m_dwFileSize));
		memcpy(&FileInfo.m_pbyFileName,&fileNames[wCount][0u],sizeof(FileInfo.m_pbyFileName));


//		memcpy(FileInfo.m_pbyFileName,achServerFileName,256);
//		memcpy(FileInfo.m_dwFileSize,achServerFileName,256);

//		cout << achFileName << endl;
//		cout << achServerFileName << endl;

		if (0 == strcmp(achServerFileName,achFileName))
		{
			post(pcMsg->srcid,S_C_FILENAME_ACK,(u8 *)&FileInfo,sizeof(FileInfo),pcMsg->srcnode);
			break;
		}		
	}
	if (wCount >= fileNames.size())
	{
		post(pcMsg->srcid,S_C_FILENAME_NACK,NULL,0,pcMsg->srcnode);
	}
}





/*********************************************************************
    DaemonInstanceEntry����
*********************************************************************/

void CServerInstance::DaemonInstanceEntry(CMessage *const pcMsg, CApp* pcApp)
{
    //u32 curState = CurState();
    u16 curEvent = pcMsg->event;
	u32 dwInsCout = 0;
	CServerInstance* pCInstance = NULL;

    switch(curEvent)
    {
        /* �������� */
//        case CONNECT_TIME_EVENT:
        case C_S_CONNECT_REQ:
			g_CServerApp.m_dwNodeNum++;
//			OspLog(LOG_LVL_DETAIL,"�����������daemon\n");
            DaemonDealClientConnect(pcMsg, pcApp);
            break;

		/* ��ȡ�ļ��б����� */
        case C_S_GETLIST_REQ:
			OspLog(LOG_LVL_DETAIL,"�����������ļ��б�����\n");
            DaemonGetlist(pcMsg);
            break;


		
		/* �����ļ��������� */
		case C_S_DOWNLOADDATA_REQ:

			 break;

		/* ȡ������ */
		case C_S_CANCELFILE_REQ:
			 
            break;

        default:
            OspLog(LOG_LVL_DETAIL,".......**.....\n");
            break;
    }
//	OspSetHBParam();
//	OspNodeDiscCBReg();
}

/*********************************************************************
    InstanceEntry����
*********************************************************************/
void CServerInstance::InstanceEntry(CMessage *const pcMsg)
{
	u16 curEvent = pcMsg->event;
	u32 dwInsCout = 0;

	switch(curEvent)
	{
		/* ע������ */
	    case C_S_REGISTER_REQ:
			for( dwInsCout = 1; dwInsCout <= MAX_SERVER_INS_NUM; dwInsCout++)
			{	 
				//��ȡʵ������ָ��
				if (IDLE_STATE == CurState())
				{
					NextState(READY_STATE);
					post(pcMsg->srcid, S_C_REGISTER_ACK,NULL,0,pcMsg->srcnode);
					break;
				}
				
			}
			break;

		/* �����ļ����� */
		case C_S_FILENAME_REQ:
//			cout << pcMsg->content << endl;
			ProcCheckFile(pcMsg);
             break;

		default:
            OspLog(LOG_LVL_DETAIL,".......**.....\n");
            break;


	}
}