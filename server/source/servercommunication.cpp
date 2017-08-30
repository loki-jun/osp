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
	u32 dwRetCreateTcpNode = OspCreateTcpNode( inet_addr("127.0.0.1"), SERVER_LISTEN_PORT );   
	//	u32 dwRetCreateTcpNode = OspCreateTcpNode( inet_addr("172.16.80.200"), SERVER_LISTEN_PORT );	
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
