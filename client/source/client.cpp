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
		// ��ʼ��Osp, �ڶ˿�2501����Telnet
		BOOL32 bRetOspinit = OspInit( TRUE, CLIENT_TELENT_PORT );         		
		if( !bRetOspinit )
		{	
			cout << "****��ʼ��Ospʧ��****" <<endl;
		}
	}

	// ��6682�˿��ϴ������ؼ������ 
	u32 dwRetCreateTcpNode = OspCreateTcpNode( 0, CLIENT_LISTEN_PORT );   

	if( dwRetCreateTcpNode == INVALID_SOCKET )
	{
		cout << "***���������ڵ�ʧ��***" <<endl;
	}

	//����APP
	g_CClientApp.CreateApp( CLIENT_APP_NAME, 
		CLIENT_APP_NO,  
		CLIENT_APP_PRIO, 
		CLIENT_APP_QUE_SIZE);	

	Sleep(5000);
	cout << "***��ʼ���ɹ�***" <<endl;
	OspPrintf(TRUE,FALSE,"��ʼ���ɹ�\n");


    void clientinterface(void);
    clientinterface();
//	OspQuit();

    return 0;
//	while(1)
//	{

//	}
	
}