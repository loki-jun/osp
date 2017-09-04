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
			OspLog(LOG_LVL_DETAIL,"***初始化osp失败***");
			return ;
		}
	}

	// 在6682端口上创建本地监听结点 
//	u32 dwRetCreateTcpNode = OspCreateTcpNode( inet_addr("127.0.0.1"), SERVER_LISTEN_PORT );   
	u32 dwRetCreateTcpNode = OspCreateTcpNode( inet_addr("172.16.80.200"), SERVER_LISTEN_PORT );	
	if( dwRetCreateTcpNode == INVALID_SOCKET )
	{
		OspLog(LOG_LVL_DETAIL,"***创建监听节点失败***");
		return;
	}
	
	//创建APP	
	g_CServerApp.CreateApp( SERVER_APP_NAME, 
		SERVER_APP_NO,  
		SERVER_APP_PRIO, 
		SERVER_APP_QUE_SIZE);	
	
	OspLog(LOG_LVL_DETAIL,"***初始化成功***");
	return ;
}


/*********************************************************************
    DaemonDealClientConnect函数
*********************************************************************/

void CServerInstance::DaemonDealClientConnect(CMessage *const pcMsg, CApp* pcApp)
{
	if ( m_dwNodeNum <= MAX_SERVER_NODE_SIZE)
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
    DaemonInstanceEntry函数
*********************************************************************/

void CServerInstance::DaemonInstanceEntry(CMessage *const pcMsg, CApp* pcApp)
{
    //u32 curState = CurState();
    u16 curEvent = pcMsg->event;
	u32 dwInsCout = 0;
	CServerInstance* pCInstance = NULL;

    switch(curEvent)
    {
        /* 连接请求 */
//        case CONNECT_TIME_EVENT:
        case C_S_CONNECT_REQ:
			m_dwNodeNum++;
			OspLog(LOG_LVL_DETAIL,"连接请求进入daemon\n");
            DaemonDealClientConnect(pcMsg, pcApp);
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
            OspLog(LOG_LVL_DETAIL,".......**.....\n");
            break;
    }
//	OspSetHBParam();
//	OspNodeDiscCBReg();
}

void CServerInstance::InstanceEntry(CMessage *const pcMsg)
{
//	cout << "测试服务器注册成功" << endl;
	u16 curEvent = pcMsg->event;
	u32 dwInsCout = 0;

	switch(curEvent)
	{
		/* 注册请求 */
	    case C_S_REGISTER_REQ:
			for( dwInsCout = 1; dwInsCout <= MAX_SERVER_INS_NUM; dwInsCout++)
			{	 
				//获取实例对象指针
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