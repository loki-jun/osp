 /*==========================================================                        
文件名：clientcommunication.cpp
实现功能：负责消息处理以及调用文件处理模块接口
作者：
版权：
------------------------------------------------------------
修改记录：
日  期	   	  版本		 修改人		  走读人      修改记录
  
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
    初始化函数
*********************************************************************/
void UserInit()
{

	if( !( IsOspInitd( ) ) )
	{
		// 初始化Osp, 在端口2501启动Telnet
		BOOL32 bRetOspinit = OspInit( TRUE, CLIENT_TELENT_PORT );         		
		if( !bRetOspinit )
		{	
			OspLog(LOG_LVL_ERROR,"***初始化osp失败***");
			return ;
		}
	}
	
	//创建APP	
	g_CClientApp.CreateApp( CLIENT_APP_NAME, 
		CLIENT_APP_NO,  
		CLIENT_APP_PRIO, 
		CLIENT_APP_QUE_SIZE);	
	
	
	OspLog(LOG_LVL_DETAIL,"***初始化成功***");

	return ;
}


/*********************************************************************
    DaemonConnectServer函数
*********************************************************************/
void CClientInstance::DaemonConnectServer()
{	
    s32 dwRet = 0;
	dwRet = OspConnectTcpNode(g_CClientApp.m_dwIp,SERVER_LISTEN_PORT);
	if(dwRet != INVALID_NODE)
	{
	    OspLog(LOG_LVL_DETAIL,"成功获取服务器node\n");
		g_CClientApp.m_dwDstNode = dwRet;
		post(MAKEIID(SERVER_APP_NO, DAEMON), C_S_CONNECT_REQ,NULL,0,g_CClientApp.m_dwDstNode);

	}
//	else
//	{
//		SetTimer(CONNECT_TIME_EVENT, TIME_WATING);
//	}
}


/*********************************************************************
    DaemonInstanceEntry函数
*********************************************************************/

void CClientInstance::DaemonInstanceEntry(CMessage *const pcMsg, CApp* pcApp)
{

    //u32 curState = CurState();
    u16 curEvent = pcMsg->event;
	CClientInstance* pCInstance = NULL;
	u32 dwInsCout = 0;

    switch(curEvent)
    {
        /* 连接服务器 */
//        case CONNECT_TIME_EVENT:
        case U_C_CONNECT_CMD:
			s8 achIp[20];
			memcpy(achIp,pcMsg->content,pcMsg->length);
			g_CClientApp.m_dwIp = inet_addr(achIp);

            DaemonConnectServer();
            break;
        /* 断开连接 */
        case U_C_DISCONNECT_CMD:
            DaemonDisConnectServer();
            break;
		/* 获取文件列表 */
        case U_C_GETLIST_CMD:

            break;
         /* 下载文件 */
         case U_C_DOWNLOADFILE_CMD:
            
             break;
         /* 暂停下载 */
         case U_C_PAUSETASK_CMD:
           
            break;
		/* 恢复下载 */
         case U_C_RESUMETASK_CMD:
			 
            break;
		/* 取消下载 */
         case U_C_CANCELTASK_CMD:
			 
            break;
		/* 下载断点续传文件 */
         case U_C_DOWNLOADPARTFILE_CMD:
			 
            break;
		/* 取消断点续传文件 */
         case U_C_CANCELPARTFILE_CMD:
			 
            break;
		 case S_C_CONNECT_ACK:
			 OspLog(LOG_LVL_DETAIL,"服务器连接成功\n");

			 for( dwInsCout = 1; dwInsCout <= MAX_CLIENT_INS_NUM; dwInsCout++)
			 {	 
				 //获取实例对象指针
				 pCInstance = (CClientInstance*)pcApp->GetInstance(dwInsCout);
				 pCInstance->NextState(IDLE_STATE);
				 OspPost(MAKEIID(CLIENT_APP_NO, dwInsCout), C_C_CONNECTSUCCESS_CMD,&g_CClientApp.m_dwDstNode,sizeof(u32));
			 }
			 break;

        default:
            OspLog(LOG_LVL_DETAIL,".......**.....\n");
            break;
    }

}

/*********************************************************************
    InstanceEntry函数
*********************************************************************/

void CClientInstance::InstanceEntry(CMessage *const pcMsg)
{
	u16 curEvent = pcMsg->event;

	switch(curEvent)
	{
		/* 服务器连接成功，请求注册instance */
	    case  C_C_CONNECTSUCCESS_CMD:			
			post(MAKEIID(SERVER_APP_NO, PENDING), C_S_REGISTER_REQ,NULL,0,g_CClientApp.m_dwDstNode);
			break;

		case S_C_REGISTER_ACK:
			NextState(READY_STATE);
			OspLog(LOG_LVL_DETAIL,"注册成功\n");
			break;

		default:
            OspLog(LOG_LVL_DETAIL,".......**.....\n");
            break;
	}
}
