/*==========================================================                        
文件名：servercommunication.cpp
相关文件：
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
#include "../include/servercommon.h"
#include "../include/servercommunication.h"
#include "../include/servercreatefilelist.h"

using namespace std;

CServerApp g_CServerApp;

CFileInfo FileInfo;
CFileListInfo FileListInfo;
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
			OspLog(LOG_LVL_ERROR,"***初始化osp失败***");
			return ;
		}
	}

	// 在6682端口上创建本地监听结点 
//	u32 dwRetCreateTcpNode = OspCreateTcpNode( inet_addr("127.0.0.1"), SERVER_LISTEN_PORT );   
	u32 dwRetCreateTcpNode = OspCreateTcpNode( 0, SERVER_LISTEN_PORT );	
	if( dwRetCreateTcpNode == INVALID_SOCKET )
	{
		OspLog(LOG_LVL_ERROR,"***创建监听节点失败***");
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
    获取文件列表函数
*********************************************************************/
void CServerInstance::DaemonGetlist(CMessage *const pcMsg)
{
	FindFiles ff;
	vector<string> fileNames;
	fileNames = ff.findFiles( "E:\\测试文件夹" );//当前文件夹用"."，"\"要加\转义
	FileListInfo.m_wFileNum = fileNames.size();
	post(pcMsg->srcid,S_C_GETLIST_ACK, NULL,0,pcMsg->srcnode);
//    cout << FileListInfo.m_pbyFileInfo[500].m_pbyFileName << endl;

//	u16 wCount = 0;
//	for ( wCount =0; wCount<fileNames.size(); wCount++ )
// 	{      
		
//		cout << fileNames[wCount] <<endl;
		
//	}
}

/*********************************************************************
    文件校验函数
*********************************************************************/
void CServerInstance::ProcCheckFile(CMessage *const pcMsg)
{
//	cout << "进入check了吗？" << endl;
	FindFiles ff;
	vector<string> fileNames;
	fileNames = ff.findFiles( "E:\\测试文件夹" );
	u16 wCount = 0;
	for ( wCount =0; wCount<fileNames.size(); wCount++ )
	{    
		s8 achFileName[256];
		s8 achServerFileName[256];
		memcpy(&achFileName,pcMsg->content,pcMsg->length);
		memcpy(&achServerFileName,&fileNames[wCount][0u],256);
//		cout << achFileName << endl;
//		cout << achServerFileName << endl;
		if (0 == strcmp(achServerFileName,achFileName))
		{
			OspLog(LOG_LVL_DETAIL,"That's great!");
			break;
		}		
	}
	if (wCount >= fileNames.size())
	{
		OspLog(LOG_LVL_DETAIL,"文件不存在！");
	}
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
			g_CServerApp.m_dwNodeNum++;
//			OspLog(LOG_LVL_DETAIL,"连接请求进入daemon\n");
            DaemonDealClientConnect(pcMsg, pcApp);
            break;

		/* 获取文件列表请求 */
        case C_S_GETLIST_REQ:
			OspLog(LOG_LVL_DETAIL,"服务器测试文件列表生成\n");
            DaemonGetlist(pcMsg);
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

/*********************************************************************
    InstanceEntry函数
*********************************************************************/
void CServerInstance::InstanceEntry(CMessage *const pcMsg)
{
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

		/* 下载文件请求 */
		case C_S_FILENAME_REQ:
			cout << pcMsg->content << endl;
			ProcCheckFile(pcMsg);

             break;

		default:
            OspLog(LOG_LVL_DETAIL,".......**.....\n");
            break;


	}
}