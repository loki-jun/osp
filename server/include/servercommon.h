/*==========================================================                       
文件名：servercommon.h
相关文件：
实现功能：服务器端宏定义
作者：
版权：
------------------------------------------------------------
修改记录：
日  期	   	  版本		 修改人		  走读人      修改记录
  
===========================================================*/

#ifndef _SERVERCOMMON_H_
#define _SERVERCOMMON_H_

#define SERVER_APP_NAME      "ServerApp"
#define SERVER_APP_PRIO      100
#define SERVER_APP_QUE_SIZE  1000

#define CONNECT_TIME_EVENT   (u16)(OSP_USEREVENT_BASE+0x0014)
#define REGISTER_TIME_EVENT  (u16)(OSP_USEREVENT_BASE+0x0015)
#define TIME_WATING          1000

#define MAX_SERVER_INS_NUM   60
#define MAX_SERVER_NODE_SIZE 20

#define BUFFERSIZE            (u32)1045504                        //缓存大小1M

#define SERVER_FILE_PATH       "E:\\测试文件夹"         //服务器文件存储路径

#endif