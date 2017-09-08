 /*==========================================================                        
文件名：clientcommunication.cpp
实现功能：负责消息处理以及调用文件管理模块接口
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
#include "../include/clientfilemanager.h"

using namespace std;

CClientApp g_CClientApp;

CFileInfo FileInfo;
CFileListInfo FileListInfo;
CFileManager FileManager;

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
	dwRet = OspConnectTcpNode(g_CClientApp.m_dwIp,SERVER_LISTEN_PORT,TIME_WATING,NUM_WATING);
	if(dwRet != INVALID_NODE)
	{
	    OspLog(LOG_LVL_DETAIL,"成功获取服务器node\n");
		m_dwDstNode = dwRet;
		post(MAKEIID(SERVER_APP_NO, DAEMON), C_S_CONNECT_REQ,NULL,0,m_dwDstNode);
		OspSetHBParam(m_dwDstNode,NODE_TIME_WATING,NUM_WATING);
//		OspNodeDiscCBRegQ(g_CClientApp.m_dwDstNode,CLIENT_APP_NO,DAEMON);
	}
	else
	{
		OspLog(LOG_LVL_WARNING,"连接超时！\n");
//		SetTimer(CONNECT_TIME_EVENT, TIME_WATING);
	}
}

/*********************************************************************
    DaemonDisConnectServer函数
*********************************************************************/
void CClientInstance::DaemonDisConnectServer()
{
	
}


/*********************************************************************
    DaemonInstanceEntry函数
*********************************************************************/

void CClientInstance::DaemonInstanceEntry(CMessage *const pcMsg, CApp* pcApp)
{
    u32 curState = CurState();
    u16 curEvent = pcMsg->event;
	CClientInstance* pCInstance = NULL;
	u32 dwInsCout = 0;

    switch(pcMsg->event)
    {
//        case OSP_DISCONNECT:
//			OspLog(LOG_LVL_WARNING,"服务器已断链，重连中……\n");
//			NextState(IDLE_STATE);
//			break;

		/* 连接服务器 */
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
				OspLog(LOG_LVL_WARNING,"与服务器连接中，请勿重复操作！若要重连，请先断开。\n");
			}
            break;
        /* 断开连接 */
        case U_C_DISCONNECT_CMD:
			if (CONNECT_STATE == CurState())
			{
				for( dwInsCout = 1; dwInsCout <= MAX_CLIENT_INS_NUM; dwInsCout++)
				{	 
					//获取实例对象指针
					pCInstance = (CClientInstance*)pcApp->GetInstance(dwInsCout);
					pCInstance->NextState(IDLE_STATE);
				}  
				OspDisconnectTcpNode(m_dwDstNode);
				NextState(IDLE_STATE);
				OspLog(LOG_LVL_WARNING,"服务器已断开！\n");
			}
			else
			{
				OspLog(LOG_LVL_WARNING,"未连接，请先连接服务器！\n");
			}
            break;
		/* 获取文件列表 */
        case U_C_GETLIST_CMD:
			if (CONNECT_STATE == CurState())
			{
				post(MAKEIID(SERVER_APP_NO, DAEMON), C_S_GETLIST_REQ,NULL,0,m_dwDstNode);
			}
			else
			{
				OspLog(LOG_LVL_WARNING,"未连接，请先连接服务器！\n");
			}
            break;

         /* 下载文件 */
         case U_C_DOWNLOADFILE_CMD:
			 if (CONNECT_STATE == CurState())
			 {
				 for( dwInsCout = 1; dwInsCout <= MAX_CLIENT_INS_NUM; dwInsCout++)
				 {	 
					 //获取实例对象指针
					 pCInstance = (CClientInstance*)pcApp->GetInstance(dwInsCout);
					 if (READY_STATE == pCInstance->CurState())
					 {
						 pCInstance->NextState(TRANSFER_STATE);
						 post(MAKEIID(CLIENT_APP_NO, dwInsCout), C_C_DOWNLOADFILE_CMD,pcMsg->content,pcMsg->length);
//						 cout << pcMsg->content << endl;
						 break;
					 }										 
				 }
				 if (dwInsCout > MAX_CLIENT_INS_NUM)
				 {
					 OspLog(LOG_LVL_WARNING,"暂无空闲instance可用！");
				 }
			 }
			 else
			 {
				 OspLog(LOG_LVL_WARNING,"未连接，请先连接服务器！\n");
			 }
            
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
			
		/* 服务器连接确认 */
		 case S_C_CONNECT_ACK:
			 OspLog(LOG_LVL_DETAIL,"服务器连接成功\n");
			 NextState(CONNECT_STATE);
			 OspLog(LOG_LVL_DETAIL,"daemon状态：%u\n",CurState());

			 for( dwInsCout = 1; dwInsCout <= MAX_CLIENT_INS_NUM; dwInsCout++)
			 {	 
				 //获取实例对象指针
				 pCInstance = (CClientInstance*)pcApp->GetInstance(dwInsCout);
				 pCInstance->NextState(IDLE_STATE);
				 OspPost(MAKEIID(CLIENT_APP_NO, dwInsCout), C_C_CONNECTSUCCESS_CMD,(u32 *)&m_dwDstNode,sizeof(m_dwDstNode));
			 }
			 break;

		/* 服务器文件列表反馈 */
        case S_C_GETLIST_ACK:
			memcpy(&FileInfo,pcMsg->content,pcMsg->length);
			OspPrintf(TRUE,FALSE,"%s 文件大小：%d\n",FileInfo.m_pbyFileName,FileInfo.m_dwFileSize);
//			cout << FileInfo.m_pbyFileName <<"  size:" << FileInfo.m_dwFileSize << endl;
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
	    case C_C_CONNECTSUCCESS_CMD:
            memcpy(&m_dwDstNode, pcMsg->content,pcMsg->length);
			post(MAKEIID(SERVER_APP_NO, PENDING), C_S_REGISTER_REQ,NULL,0,m_dwDstNode);
			break;

		/* 服务器注册成功反馈 */
		case S_C_REGISTER_ACK:
			m_dwDstId = pcMsg->srcid;
			NextState(READY_STATE);
			break;

		/* daemon给instance发送下载指令 */
		case C_C_DOWNLOADFILE_CMD:
			post(m_dwDstId, C_S_FILENAME_REQ,pcMsg->content,pcMsg->length,m_dwDstNode);
			break;

		/* 服务器返回文件存在响应 */
		case S_C_FILENAME_ACK:
			memcpy(&FileInfo,pcMsg->content,pcMsg->length);
			OspLog(LOG_LVL_DETAIL,"服务器文件存在，放心大胆地下载吧，骚年！！\n");
			FileManager.CreateSpace(FileInfo.m_pbyFileName,FileInfo.m_dwFileSize);
			break;

		/* 服务器返回文件不存在响应 */
		case S_C_FILENAME_NACK:
			OspLog(LOG_LVL_WARNING,"骚年，文件被丢到火星了，重新选一个吧！\n");
			break;

		default:
            OspLog(LOG_LVL_DETAIL,".......**.....\n");
            break;
	}
}
