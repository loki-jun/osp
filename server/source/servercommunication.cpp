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

//extern CFileListInfo g_CFileListInfo;
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
void getlist()
{
	FindFiles ff;
	vector<string> fileNames;
	fileNames = ff.findFiles( "E:\\ѧϰ����" );//��ǰ�ļ�����"."��"\"Ҫ��\ת��
//	g_CFileListInfo.m_wFileNum = fileNames.size();
//	u16 wCount = 0;
//	for ( wCount =0; wCount<fileNames.size(); wCount++ )
// 	{      
		
//		cout << fileNames[wCount] <<endl;
		
//	}
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
            getlist();
            break;

         /* �����ļ����� */
		case C_S_FILENAME_REQ:
            
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

		default:
            OspLog(LOG_LVL_DETAIL,".......**.....\n");
            break;


	}
}