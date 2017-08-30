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
			cout << "****初始化Osp失败****" <<endl;
			return ;
		}
	}
	
	//创建APP	
	g_CClientApp.CreateApp( CLIENT_APP_NAME, 
		CLIENT_APP_NO,  
		CLIENT_APP_PRIO, 
		CLIENT_APP_QUE_SIZE);	
	
	
	cout <<"***初始化成功***" <<endl;
	return ;
}


/*********************************************************************
    DaemonConnectServer函数
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
    DaemonInstanceEntry函数
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
        /* 连接服务器 */
//        case CONNECT_TIME_EVENT:
        case U_C_CONNECT_CMD:
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
        default:
            printf(".......**.....\n");
            break;
    }

}


