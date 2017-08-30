/*==========================================================
模块名：交互模块                        
文件名：clientinterface.cpp
相关文件：osp.h,clientcommon.h,clientinterface.h
实现功能：接收用户输入
作者：
版权：
------------------------------------------------------------
修改记录：
日  期	   	  版本		 修改人		  走读人      修改记录
  
===========================================================*/

#include "iostream"
#include "io.h"
#include "../../common/kdvtype.h"
#include "../../common/osp.h"
#include "../../common/kdvdef.h"
#include "../include/clientcommon.h"
#include "../include/clientinterface.h"

using namespace std;


/*********************************************************************
    help函数
*********************************************************************/
void help()
{
	cout << "connectserver 连接服务器    参数：u32 ip " <<endl;
	cout << "dealpartfile  处理断点续传  参数：num[]" <<endl;
	cout << "getfilelist   获取文件列表  参数：NULL" <<endl;
	cout << "downloadfile  下载文件      参数：u16 FileIndex" <<endl;
	cout << "pausetask     暂停下载      参数：u16 taskID" <<endl;
	cout << "resumetask    恢复下载      参数：u16 taskID" <<endl;
	cout << "canceltask    取消下载      参数：u16 taskID" <<endl;
	cout << "disconnect    断开服务器    参数：NULL" <<endl;
	cout << "help          打印帮助信息  参数：NULL" <<endl;
	
}

/*********************************************************************
    连接函数
*********************************************************************/
void connect()
{
	cout << "请输入ip地址：" << endl;

	cin.clear();
	cin.sync();

	s8 achIp[20];
    cin.get(achIp,20);

	if(!OspPost(MAKEIID(CLIENT_APP_NO, CInstance::DAEMON), U_C_CONNECT_CMD,achIp,sizeof(achIp)))
	{
		cout << "succeed" << endl;
	}


}

/*==========================================================
函数名：clientinterface
功能：交互模块函数入口
算法实现：
参数说明：
返回值说明：
-------------------------------------------------------------------------------------------------------
修改记录：
日  期		版本		修改人		走读人        修改记录

===========================================================*/

void clientinterface()
{
    cout << "您可以有如下操作：" << endl;
	help();

	while (1)
	{
		s8 achUserInput[20];
		cin.get(achUserInput,20);

		if(!strcmp(achUserInput,"connect"))
		{
			connect();
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
			help();
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

