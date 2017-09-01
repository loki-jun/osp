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
			OspLog(LOG_LVL_DETAIL,"***��ʼ��ospʧ��***");
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
    s32 dwRet = -1;
	dwRet = OspConnectTcpNode(g_CClientApp.m_achIp,SERVER_LISTEN_PORT);
	if(dwRet != INVALID_NODE)
	{
	    OspLog(LOG_LVL_DETAIL,"���ӳɹ�\n");
		m_dwDstNode = dwRet;
		post(MAKEIID(SERVER_APP_NO, DAEMON), C_S_CONNECT_REQ,NULL,0,m_dwDstNode);

	}
//	else
//	{
//		SetTimer(CONNECT_TIME_EVENT, TIME_WATING);
//	}
}

/*********************************************************************
    Instanceע�ắ��
*********************************************************************/
void CClientInstance::ProcRegister()
{

}


/*********************************************************************
    DaemonInstanceEntry����
*********************************************************************/

void CClientInstance::DaemonInstanceEntry(CMessage *const pcMsg, CApp* pcApp)
{

    //u32 curState = CurState();
    u16 curEvent = pcMsg->event;

    switch(curEvent)
    {
        /* ���ӷ����� */
//        case CONNECT_TIME_EVENT:
        case U_C_CONNECT_CMD:
			s8 achIp[20];
			memcpy(achIp,pcMsg->content,pcMsg->length);
			g_CClientApp.m_achIp = inet_addr(achIp);

            DaemonConnectServer();
            break;
        /* �Ͽ����� */
        case U_C_DISCONNECT_CMD:
            DaemonDisConnectServer();
            break;
		/* ��ȡ�ļ��б� */
        case U_C_GETLIST_CMD:
            
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
		 case S_C_CONNECT_ACK:
			 cout << "���������ӳɹ�\n" << endl;
			 OspLog(LOG_LVL_DETAIL,"���������ӳɹ�\n");

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
		/* ���������ӳɹ���ע��instance����*/
	    case  C_C_CONNECTSUCCESS_CMD:
			ProcRegister();
			break;

		default:
            OspLog(LOG_LVL_DETAIL,".......**.....\n");
            break;
	}
}
