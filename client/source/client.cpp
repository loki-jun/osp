/*==========================================================                        
文件名：client.cpp
相关文件：osp.h，clientcommunication.h，clientinterface.h
实现功能：主函数入口
作者：
版权：
------------------------------------------------------------
修改记录：
日  期	   	  版本		 修改人		  走读人      修改记录
  
===========================================================*/

#include "../../common/osp.h"
#include "../../common/macrodef.h"
#include "../include/clientcommunication.h"
#include "../include/clientinterface.h"
#include "../include/clientcommon.h"

int main()
{

	UserInit();
	OspSetLogLevel(APP_ID,FILE_LEVEL,SCREEN_LEVEL);
	clientinterface();

	while(1)
	{

	}
	return 0;
	
}

/* 帮助命令接口*/
API void h()
{
	OspPrintf( TRUE, FALSE, "connect       连接服务器    参数：u32 ip \n");
	OspPrintf( TRUE, FALSE, "dealpartfile  处理断点续传  参数：num[]\n");
	OspPrintf( TRUE, FALSE, "getfilelist   获取文件列表  参数：NULL\n");
	OspPrintf( TRUE, FALSE, "downloadfile  下载文件      参数：u16 FileIndex\n");
	OspPrintf( TRUE, FALSE, "pausetask     暂停下载      参数：u16 taskID\n");
	OspPrintf( TRUE, FALSE, "resumetask    恢复下载      参数：u16 taskID\n");
	OspPrintf( TRUE, FALSE, "canceltask    取消下载      参数：u16 taskID\n");
	OspPrintf( TRUE, FALSE, "disconnect    断开服务器    参数：NULL\n");
	OspPrintf( TRUE, FALSE, "help          打印帮助信息  参数：NULL\n");
}

/* 连接服务器 */
API void c(LPSTR ip)
{
	OspPost(MAKEIID(CLIENT_APP_NO, CInstance::DAEMON), U_C_CONNECT_CMD,ip,20);
}


