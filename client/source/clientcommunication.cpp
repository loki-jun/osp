 /*==========================================================                        
�ļ�����clientcommunication.cpp
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
#include "../include/clientcommon.h"
#include "../include/clientcommunication.h"
#include "../include/clientinterface.h"

using namespace std;

CClientApp g_CClientApp;

CFileInfo CFileInfo;
CFileListInfo CFileListInfo;

/*********************************************************************
    ��ʼ������
*********************************************************************/
void UserInit()
{

	if( !( IsOspInitd( ) ) )
	{
		// ��ʼ��Osp, �ڶ˿�2501����Telnet
		BOOL32 bRetOspinit = OspInit( TRUE, CLIENT_TELENT_PORT );         		
		if( !bRetOspinit )
		{	
			OspLog(LOG_LVL_ERROR,"***��ʼ��ospʧ��***");
			return ;
		}
	}
	
	//����APP	
	g_CClientApp.CreateApp( CLIENT_APP_NAME, 
		CLIENT_APP_NO,  
		CLIENT_APP_PRIO, 
		CLIENT_APP_QUE_SIZE);	
	
	
	OspLog(LOG_LVL_DETAIL,"***��ʼ���ɹ�***");

	return ;
}


/*********************************************************************
    DaemonConnectServer����
*********************************************************************/
void CClientInstance::DaemonConnectServer()
{	
    s32 dwRet = 0;
	dwRet = OspConnectTcpNode(g_CClientApp.m_dwIp,SERVER_LISTEN_PORT,TIME_WATING,NUM_WATING);
	if(dwRet != INVALID_NODE)
	{
	    OspLog(LOG_LVL_DETAIL,"�ɹ���ȡ������node\n");
		g_CClientApp.m_dwDstNode = dwRet;
		post(MAKEIID(SERVER_APP_NO, DAEMON), C_S_CONNECT_REQ,NULL,0,g_CClientApp.m_dwDstNode);
		OspSetHBParam(g_CClientApp.m_dwDstNode,NODE_TIME_WATING,NUM_WATING);
//		OspNodeDiscCBRegQ(g_CClientApp.m_dwDstNode,CLIENT_APP_NO,DAEMON);
	}
	else
	{
		OspLog(LOG_LVL_WARNING,"���ӳ�ʱ��\n");
//		SetTimer(CONNECT_TIME_EVENT, TIME_WATING);
	}
}

/*********************************************************************
    DaemonDisConnectServer����
*********************************************************************/
void CClientInstance::DaemonDisConnectServer()
{
	
}


/*********************************************************************
    DaemonInstanceEntry����
*********************************************************************/

void CClientInstance::DaemonInstanceEntry(CMessage *const pcMsg, CApp* pcApp)
{
    u32 curState = CurState();
    u16 curEvent = pcMsg->event;
	CClientInstance* pCInstance = NULL;
	u32 dwInsCout = 0;

	cout << curEvent << "1111111" << S_C_GETLIST_ACK << endl;
    switch(pcMsg->event)
    {
//        case OSP_DISCONNECT:
//			OspLog(LOG_LVL_WARNING,"�������Ѷ����������С���\n");
//			NextState(IDLE_STATE);
//			break;

		/* ���ӷ����� */
        case U_C_CONNECT_CMD:
			if (IDLE_STATE == CurState())
			{
				s8 achIp[20];
				memcpy(achIp,pcMsg->content,pcMsg->length);
				g_CClientApp.m_dwIp = inet_addr(achIp);
                DaemonConnectServer();
			}
			else
			{
				OspLog(LOG_LVL_WARNING,"������������У������ظ���������Ҫ���������ȶϿ���\n");
			}
            break;
        /* �Ͽ����� */
        case U_C_DISCONNECT_CMD:
			if (CONNECT_STATE == CurState())
			{
				for( dwInsCout = 1; dwInsCout <= MAX_CLIENT_INS_NUM; dwInsCout++)
				{	 
					//��ȡʵ������ָ��
					pCInstance = (CClientInstance*)pcApp->GetInstance(dwInsCout);
					pCInstance->NextState(IDLE_STATE);
				}  
				OspDisconnectTcpNode(g_CClientApp.m_dwDstNode);
				NextState(IDLE_STATE);
				OspLog(LOG_LVL_WARNING,"�������ѶϿ���\n");
			}
			else
			{
				OspLog(LOG_LVL_WARNING,"δ���ӣ��������ӷ�������\n");
			}
            break;
		/* ��ȡ�ļ��б� */
        case U_C_GETLIST_CMD:
			if (CONNECT_STATE == CurState())
			{
				post(MAKEIID(SERVER_APP_NO, DAEMON), C_S_GETLIST_REQ,NULL,0,g_CClientApp.m_dwDstNode);
			}
			else
			{
				OspLog(LOG_LVL_WARNING,"δ���ӣ��������ӷ�������\n");
			}
            break;
         /* �����ļ� */
         case U_C_DOWNLOADFILE_CMD:
            
             break;
         /* ��ͣ���� */
         case U_C_PAUSETASK_CMD:
           
            break;
		/* �ָ����� */
         case U_C_RESUMETASK_CMD:
			 
            break;
		/* ȡ������ */
         case U_C_CANCELTASK_CMD:
			 
            break;
		/* ���ضϵ������ļ� */
         case U_C_DOWNLOADPARTFILE_CMD:
			 
            break;
		/* ȡ���ϵ������ļ� */
         case U_C_CANCELPARTFILE_CMD:
			 
            break;
			
		/* ����������ȷ�� */
		 case S_C_CONNECT_ACK:
			 OspLog(LOG_LVL_DETAIL,"���������ӳɹ�\n");
			 NextState(CONNECT_STATE);
			 OspLog(LOG_LVL_DETAIL,"daemon״̬��%u\n",CurState());

			 for( dwInsCout = 1; dwInsCout <= MAX_CLIENT_INS_NUM; dwInsCout++)
			 {	 
				 //��ȡʵ������ָ��
				 pCInstance = (CClientInstance*)pcApp->GetInstance(dwInsCout);
				 pCInstance->NextState(IDLE_STATE);
				 OspPost(MAKEIID(CLIENT_APP_NO, dwInsCout), C_C_CONNECTSUCCESS_CMD,&g_CClientApp.m_dwDstNode,sizeof(u32));
			 }
			 break;

		/* �������ļ��б��� */
        case S_C_GETLIST_ACK:
			OspLog(LOG_LVL_DETAIL,"�����ļ��б����\n");
			memcpy(&CFileListInfo,pcMsg->content,pcMsg->length);
			cout << pcMsg->content << endl;
			OspPrintf(TRUE,FALSE,"�ļ��б�����Ϊ��%d\n",CFileListInfo.m_wFileNum);
			break;

        default:
            OspLog(LOG_LVL_DETAIL,".......**.....\n");
            break;
    }

}

/*********************************************************************
    InstanceEntry����
*********************************************************************/

void CClientInstance::InstanceEntry(CMessage *const pcMsg)
{
	u16 curEvent = pcMsg->event;

	switch(curEvent)
	{
		/* ���������ӳɹ�������ע��instance */
	    case C_C_CONNECTSUCCESS_CMD:			
			post(MAKEIID(SERVER_APP_NO, PENDING), C_S_REGISTER_REQ,NULL,0,g_CClientApp.m_dwDstNode);
			break;

		case S_C_REGISTER_ACK:
			NextState(READY_STATE);
			OspLog(LOG_LVL_DETAIL,"instanceע��ɹ�\n");
			break;

		default:
            OspLog(LOG_LVL_DETAIL,".......**.....\n");
            break;
	}
}
