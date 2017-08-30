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
			cout << "****��ʼ��Ospʧ��****" <<endl;
			return ;
		}
	}
	
	//����APP	
	g_CClientApp.CreateApp( CLIENT_APP_NAME, 
		CLIENT_APP_NO,  
		CLIENT_APP_PRIO, 
		CLIENT_APP_QUE_SIZE);	
	
	
	cout <<"***��ʼ���ɹ�***" <<endl;
	return ;
}


/*********************************************************************
    DaemonConnectServer����
*********************************************************************/
void CClientInstance::DaemonConnectServer()
{	
	cout << "DaemonConnectServer  ok " <<endl;
    s32 dwRet = -1;
	dwRet = OspConnectTcpNode(g_CClientApp.m_achIp,SERVER_LISTEN_PORT);
//	cout << dwRet << endl;
	if(dwRet != INVALID_NODE)
	{
		cout << "CONNECT  ok " <<endl;

//		OspPost(MAKEIID(SERVER_APP_ID, DAEMON), C_S_CONNECT_REQ,&m_dwDstNode,sizeof(u32));

	}
//	else
//	{
//		SetTimer(CONNECT_TIME_EVENT, TIME_WATING);
//	}
}





/*********************************************************************
    DaemonInstanceEntry����
*********************************************************************/

void CClientInstance::DaemonInstanceEntry(CMessage *const pcMsg, CApp* pcApp)
{

    //u32 curState = CurState();
    u16 curEvent = pcMsg->event;
	s8 achIp[20];
	memcpy(achIp,pcMsg->content,sizeof(pcMsg->content));
	g_CClientApp.m_achIp = inet_addr(achIp);
    s32 dwRet = -1;

    switch(curEvent)
    {
        /* ���ӷ����� */
//        case CONNECT_TIME_EVENT:
        case U_C_CONNECT_CMD:
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
        default:
            printf(".......**.....\n");
            break;
    }

}


