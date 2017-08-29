/*==========================================================
文件名：clientinterface.cpp
功能：接收用户指令
算法实现：
参数说明：
返回值说明：
-------------------------------------------------------------------------------------------------------
修改记录：
日  期		版本		修改人		走读人        修改记录

===========================================================*/

#include "iostream"
#include "io.h"
#include "../../common/kdvtype.h"
#include "../../common/osp.h"
#include "../../common/kdvdef.h"
#include "../include/client.h"
#include "../include/clientinterface.h"

using namespace std;

extern CClientApp g_CClientApp;

void clientinterface()
{
    cout << "您可以有如下操作：" << endl;
	cout << "connect       连接服务器" <<endl;
	cout << "dealpartfile  处理断点续传" <<endl;
	cout << "getfilelist   获取文件列表" <<endl;
	cout << "downloadfile  下载文件" <<endl;
	cout << "pausetask     暂停下载" <<endl;
	cout << "resumetask    恢复下载" <<endl;
	cout << "canceltask    取消下载" <<endl;
	cout << "disconnect    断开服务器" <<endl;
	cout << "help          打印帮助信息" <<endl;

    s8 achUserInput[20] ={0};

	while (1)
	{
		cin.get(achUserInput,20);

		if(!strcmp(achUserInput,"connect"))
		{
			cout << "请输入ip地址：" << endl;

			cin.clear();
            cin.sync();

			cin.get(&g_CClientApp.m_achIp,20);

			OspPost(MAKEIID(CLIENT_APP_NO, CInstance::DAEMON), U_C_CONNECT_CMD);

			break;
		}
		else if (!strcmp(achUserInput,"dealpartfile"))
		{
			
		}
		else if (!strcmp(achUserInput,"getfilelist"))
		{
			
		}
		else if (!strcmp(achUserInput, "downloadfile"))
		{
			
		}
		else if (!strcmp(achUserInput,"pausetask"))
		{
			
		}
		else if (!strcmp(achUserInput,"resumetask"))
		{
			
		}
		else if (!strcmp(achUserInput,"canceltask"))
		{
			
		}
		else if (!strcmp(achUserInput,"resumetask"))
		{
			
		}
		else if (!strcmp(achUserInput, "disconnect"))
		{
			
		}
		else if (!strcmp(achUserInput,"help"))
		{
			cout << "connect       连接服务器" <<endl;
			cout << "dealpartfile  处理断点续传" <<endl;
			cout << "getfilelist   获取文件列表" <<endl;
			cout << "downloadfile  下载文件" <<endl;
			cout << "pausetask     暂停下载" <<endl;
			cout << "resumetask    恢复下载" <<endl;
			cout << "canceltask    取消下载" <<endl;
			cout << "disconnect    断开服务器" <<endl;
			cout << "help          打印帮助信息" <<endl;
			break;
		}
		else
		{
			cout << "输入错误，请重新输入" <<endl;
		}
        cin.clear();
        cin.sync();
	}
}