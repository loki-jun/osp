#include <stdio.h>
#include <iostream>
#include <fstream> 
#include "../../common/kdvtype.h"
#include "../../common/osp.h"
#include "../../common/kdvdef.h"
#include "../../common/csmsg.h"
#include "../../common/macrodef.h"
#include "../include/Server.h"

using namespace std;

CServerApp g_CServerApp;

int main()
{
	if( !( IsOspInitd( ) ) )
	{
		// 初始化Osp, 在端口2502启动Telnet
		BOOL32 bRetOspinit = OspInit( TRUE, SERVER_TELENT_PORT );         		
		if( !bRetOspinit )
		{	
			cout << "****初始化Osp失败****" <<endl;
			return;
		}
	}
	
	// 在6682端口上创建本地监听结点 
	u32 dwRetCreateTcpNode = OspCreateTcpNode( inet_addr("127.0.0.1"), SERVER_LISTEN_PORT );   
	
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
	
	cout << "***初始化成功***" <<endl;
	OspPrintf(TRUE,FALSE,"初始化成功\n");
	
	

	//	OspQuit();
	
//    return 0;
		while(1)
		{
	
		}
	
}