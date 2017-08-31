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
    初始化函数
*********************************************************************/
void UserInit()
{
	if( !( IsOspInitd( ) ) )
	{
		// 初始化Osp, 在端口2502启动Telnet
		BOOL32 bRetOspinit = OspInit( TRUE, SERVER_TELENT_PORT );         		
		if( !bRetOspinit )
		{	
			cout << "****初始化Osp失败****" <<endl;
			return ;
		}
	}

	// 在6682端口上创建本地监听结点 
//	u32 dwRetCreateTcpNode = OspCreateTcpNode( inet_addr("127.0.0.1"), SERVER_LISTEN_PORT );   
	u32 dwRetCreateTcpNode = OspCreateTcpNode( inet_addr("172.16.80.200"), SERVER_LISTEN_PORT );	
	if( dwRetCreateTcpNode == INVALID_SOCKET )
	{
		cout << "***创建监听节点失败***" <<endl;
		return;
	}
	
	//创建APP	
	g_CServerApp.CreateApp( SERVER_APP_NAME, 
		SERVER_APP_NO,  
		SERVER_APP_PRIO, 
		SERVER_APP_QUE_SIZE);	
	
	
	cout <<"***初始化成功***" <<endl;
	return ;
}


/*********************************************************************
    DaemonDealClientConnect函数
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
    DaemonInstanceEntry函数
*********************************************************************/

void CServerInstance::DaemonInstanceEntry(CMessage *const pcMsg, CApp* pcApp)
{

    //u32 curState = CurState();
    u16 curEvent = pcMsg->event;

    switch(curEvent)
    {
        /* 连接请求 */
//        case CONNECT_TIME_EVENT:
        case C_S_CONNECT_REQ:
//            DaemonClientConnect();
            break;

		/* 注册请求 */
		case C_S_REGISTER_REQ:

			break;

		/* 获取文件列表请求 */
        case C_S_GETLIST_REQ:
            
            break;

         /* 下载文件请求 */
		case C_S_FILENAME_REQ:
            
             break;
		
		/* 下载文件数据请求 */
		case C_S_DOWNLOADDATA_REQ:

			 break;

		/* 取消下载 */
		case C_S_CANCELFILE_REQ:
			 
            break;

        default:
            printf(".......**.....\n");
            break;
    }

}

