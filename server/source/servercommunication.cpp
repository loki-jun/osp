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

using namespace std;

CServerApp g_CServerApp;

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
			cout << "****��ʼ��Ospʧ��****" <<endl;
			return ;
		}
	}

	// ��6682�˿��ϴ������ؼ������ 
//	u32 dwRetCreateTcpNode = OspCreateTcpNode( inet_addr("127.0.0.1"), SERVER_LISTEN_PORT );   
	u32 dwRetCreateTcpNode = OspCreateTcpNode( inet_addr("172.16.80.200"), SERVER_LISTEN_PORT );	
	if( dwRetCreateTcpNode == INVALID_SOCKET )
	{
		cout << "***���������ڵ�ʧ��***" <<endl;
		return;
	}
	
	//����APP	
	g_CServerApp.CreateApp( SERVER_APP_NAME, 
		SERVER_APP_NO,  
		SERVER_APP_PRIO, 
		SERVER_APP_QUE_SIZE);	
	
	
	cout <<"***��ʼ���ɹ�***" <<endl;
	return ;
}


/*********************************************************************
    DaemonDealClientConnect����
*********************************************************************/
/*
void CServerInstance::DaemonDealClientConnect(CMessage *const pcMsg, CApp* pcApp)
{
	u32 curState = CurState();
    u16 curEvent = pcMsg->event;
    CServerInstance* pCInstance = NULL;
    u32 dwInsCout=0;
    s8 bystr[MAX_SERVER_NODE_SIZE];
	
    for( dwInsCout = 1; dwInsCout <= MAX_SERVER_INS_NUM; dwInsCout++)
    {
        pCInstance = (CServerInstance* )pcApp->GetInstance(dwInsCout);
        if ( IDLE_STATE == pCInstance->CurState() )
        {
            memset(bystr,0x00,sizeof(bystr));
            sprintf(bystr,"%u\n%u",pcMsg->srcid,pcMsg->srcnode);
            OspPost(MAKEIID(SERVER_APP_NO, dwInsCout), C_S_CONNECT_REQ, bystr, strlen(bystr));
            pCInstance->NextState(READY_STATE);
            break;
        }
    }
    if ( MAX_SERVER_INS_NUM < dwInsCout )
    {
        post(pcMsg->srcid, SERVER_CLIENT_REGIST_NACK, NULL, 0, pcMsg->srcnode);
    }
}

*/

/*********************************************************************
    DaemonInstanceEntry����
*********************************************************************/

void CServerInstance::DaemonInstanceEntry(CMessage *const pcMsg, CApp* pcApp)
{

    //u32 curState = CurState();
    u16 curEvent = pcMsg->event;

    switch(curEvent)
    {
        /* �������� */
//        case CONNECT_TIME_EVENT:
        case C_S_CONNECT_REQ:
//            DaemonClientConnect();
            break;

		/* ע������ */
		case C_S_REGISTER_REQ:

			break;

		/* ��ȡ�ļ��б����� */
        case C_S_GETLIST_REQ:
            
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
            printf(".......**.....\n");
            break;
    }

}

