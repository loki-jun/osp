#include <stdio.h>
#include <iostream>
#include <fstream> 
#include "../../common/kdvtype.h"
#include "../../common/osp.h"
#include "../../common/kdvdef.h"
#include "../../common/csmsg.h"
#include "../../common/macrodef.h"
#include "../include/client.h"

using namespace std;

CClientApp g_CClientApp;

int main()
{
	if( !( IsOspInitd( ) ) )
	{
		// 初始化Osp, 在端口2501启动Telnet
		BOOL32 bRetOspinit = OspInit( TRUE, CLIENT_TELENT_PORT );         		
		if( !bRetOspinit )
		{	
			cout << "****初始化Osp失败****" <<endl;
		}
	}

	// 在6682端口上创建本地监听结点 
	u32 dwRetCreateTcpNode = OspCreateTcpNode( 0, CLIENT_LISTEN_PORT );   

	if( dwRetCreateTcpNode == INVALID_SOCKET )
	{
		cout << "***创建监听节点失败***" <<endl;
	}

	//创建APP
	g_CClientApp.CreateApp( CLIENT_APP_NAME, 
		CLIENT_APP_NO,  
		CLIENT_APP_PRIO, 
		CLIENT_APP_QUE_SIZE);	

	Sleep(5000);
	cout << "***初始化成功***" <<endl;
	OspPrintf(TRUE,FALSE,"初始化成功\n");


    void clientinterface(void);
    clientinterface();
//	OspQuit();

    return 0;
//	while(1)
//	{

//	}
	
}