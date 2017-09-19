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
#include "../include/clientcommon.h"
#include "../include/clientcommunication.h"
#include "../include/clientinterface.h"
#include "../include/clientfilemanager.h"

using namespace std;

CClientApp g_CClientApp;

CConfigData g_CConfigData;
CFileManager g_CFileManager;
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
    客户端接收服务器数据函数
*********************************************************************/
/*
void CClientInstance::ProcClientRecData(CMessage *const pcMsg,u32 dwBufferNum,u16 wIdCount)
{
	memcpy(&m_cPackageInfo,pcMsg->content,pcMsg->length);
	//计算buffer中包的偏移量
	u32 dwShift = (m_cPackageInfo.m_wPackageId - dwBufferNum*PACKAGENUM_EACHBUFFER)*TransferSize;

	memcpy(g_CFileManager.m_cBuffer[wIdCount].m_dwBuffer+dwShift,m_cPackageInfo.m_pbyPackageContent,TransferSize);
//	OspLog(LOG_LVL_DETAIL,"包大小：%d\n",sizeof(g_CFileManager.m_cBuffer[wIdCount].m_dwBuffer));

}
*/

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
			 if (CONNECT_STATE == CurState())   //判断daemon状态
			 {
				 for( dwInsCout = 1; dwInsCout <= MAX_CLIENT_INS_NUM; dwInsCout++)
				 {	 
					 //获取实例对象指针
					 pCInstance = (CClientInstance*)pcApp->GetInstance(dwInsCout);
					 if (READY_STATE == pCInstance->CurState())
					 {
						 pCInstance->NextState(TRANSFER_STATE);   //daemon改instance状态为传输态
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
			 if (CONNECT_STATE == CurState())   //判断daemon状态
			 {
				 u16 wTaskId = 0;
			     memcpy(&wTaskId,pcMsg->content,sizeof(wTaskId));
				 pCInstance = (CClientInstance*)pcApp->GetInstance(wTaskId);
				 if (TRANSFER_STATE == pCInstance->CurState())
				 {
					 post(MAKEIID(CLIENT_APP_NO, wTaskId), C_C_PAUSETASK_CMD,pcMsg->content,pcMsg->length);
				 }
				 else
				 {
					 OspLog(LOG_LVL_DETAIL,"instance状态：%d\n",pCInstance->CurState());
				 }
			 }
			 else
			 {
				 OspLog(LOG_LVL_WARNING,"未连接，请先连接服务器！\n");
			 }
            break;

		/* 恢复下载 */
         case U_C_RESUMETASK_CMD:
			 if (CONNECT_STATE == CurState())   //判断daemon状态
			 {
				 u16 wTaskId = 0;
				 memcpy(&wTaskId,pcMsg->content,sizeof(wTaskId));
				 pCInstance = (CClientInstance*)pcApp->GetInstance(wTaskId);
				 if (PAUSE_STATE == pCInstance->CurState())
				 {
					 post(MAKEIID(CLIENT_APP_NO, wTaskId), C_C_RESUMETASK_CMD,pcMsg->content,pcMsg->length);
				 }
				 else
				 {
					 OspLog(LOG_LVL_DETAIL,"instance状态：%d\n",pCInstance->CurState());
				 }
			 }
			 else
			 {
				 OspLog(LOG_LVL_WARNING,"未连接，请先连接服务器！\n");
			 }
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
			OspPrintf(TRUE,FALSE,"测试文件列表客户端接收\n");
			memcpy(&m_cFileListInfo,pcMsg->content,pcMsg->length);
			m_cFileListInfo.printf();
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
			m_dwDstId = pcMsg->srcid;
            m_dwDstNode = pcMsg->srcnode;

			memcpy(&m_cFileInfo,pcMsg->content,pcMsg->length);
			OspLog(LOG_LVL_DETAIL,"服务器文件存在，放心大胆地下载吧，骚年！！\n");
//			g_CFileManager.CreateSpace(m_cFileInfo.m_pbyFileName,m_cFileInfo.m_dwFileSize);
			if ( TRANSFER_STATE == CurState() )
			{
				m_cPackageInfo.setdownloadstate(0);
				//下载的文件名跟配置文件中的文件去对比，若文件在配置中，则m_cPackageInfo.m_wDownloadState设为1，反之为0
				//后续还需加上文件重命名
				if (0 == m_cPackageInfo.getdownloadstate()) 
				{
					u32 idcount = 0;
					u32 MaxId = m_cFileInfo.getfilesize()/TransferSize;
					OspLog(LOG_LVL_DETAIL,"包的总数目为：%u\n",MaxId);
					m_cPackageInfo.setsfilename(m_cFileInfo.getfilename());
//					memcpy(m_cPackageInfo.m_pbySFileName,m_cFileInfo.getfilename(),sizeof(m_cPackageInfo.m_pbySFileName));
					m_cPackageInfo.setnetfilesize(m_cFileInfo.getfilesize());
					m_cPackageInfo.setpackageid(idcount);//若为断点续传，此值为配置中读取的ID值
//					post(m_dwDstId, C_S_DOWNLOADDATA_REQ,&m_cPackageInfo,sizeof(m_cPackageInfo),m_dwDstNode);
					m_cPackageInfo.setnetpackagesize(TransferSize);
					post(pcMsg->srcid, C_S_DOWNLOADDATA_REQ,&m_cPackageInfo,sizeof(m_cPackageInfo),pcMsg->srcnode);
				}
				else
				{
					OspLog(LOG_LVL_DETAIL,"1断点续传功能待开发……\n");
				}
			}
				
			break;

		/* 服务器返回文件包数据 */
		case S_C_DOWNLOADDATA_ACK:
//			m_cPackageInfo.printf();
			memcpy(&m_cPackageInfo,pcMsg->content,pcMsg->length);
			OspLog(LOG_LVL_DETAIL,"文件大小：%d\n",m_cPackageInfo.getfilesize());
			if (TRANSFER_STATE == CurState())
			{
				//判断是正常下载还是断点续传
				if (0 == m_cPackageInfo.getdownloadstate())
				{
					u16 wIdCount =0;
					u32 MaxId =0;
					//将instance与buffer绑定
					//wIdCount = GetInsID()-1;
					MaxId = m_cPackageInfo.getfilesize()/TransferSize;
					
					
					OspLog(LOG_LVL_DETAIL,"客户端下载的包id：%d\n",m_cPackageInfo.getpackageid());
					if (MaxId != m_cPackageInfo.getpackageid())
					{
						g_CFileManager.FileWrite(m_cPackageInfo.getsfilename(),m_cPackageInfo.getfilesize(),m_cPackageInfo.getpackageid(),m_cPackageInfo.getpackagesize(),m_cPackageInfo.getpackagecontent());
					    m_cPackageInfo.setnetpackageid(m_cPackageInfo.getpackageid()+1);
						post(pcMsg->srcid, C_S_DOWNLOADDATA_REQ,&m_cPackageInfo,sizeof(m_cPackageInfo),pcMsg->srcnode);
//						OspLog(LOG_LVL_DETAIL,"客户端下载的包内容：%s\n",m_cPackageInfo.getpackagecontent());
					}
					else
					{
						g_CFileManager.FileWrite(m_cPackageInfo.getsfilename(),m_cPackageInfo.getfilesize(),m_cPackageInfo.getpackageid(),m_cPackageInfo.getpackagesize(),m_cPackageInfo.getpackagecontent());
//						OspLog(LOG_LVL_DETAIL,"客户端下载的包内容：%s\n",m_cPackageInfo.getpackagecontent());
						OspLog(LOG_LVL_DETAIL,"客户端下载任务结束！\n");
						NextState(READY_STATE);
					}
				}
				else
				{
					OspLog(LOG_LVL_DETAIL,"2断点续传功能待开发……\n");
				}
			}
			break;

			/* 暂停文件下载 */
		case C_C_PAUSETASK_CMD:
			NextState(READY_STATE);
			break;

			/* 恢复文件下载指令 */
		case C_C_RESUMETASK_CMD:
			NextState(TRANSFER_STATE);
			post(m_dwDstId, C_S_DOWNLOADDATA_REQ,&m_cPackageInfo,sizeof(m_cPackageInfo),m_dwDstNode);
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
