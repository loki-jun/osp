/*==========================================================                      
文件名：clientcommon.h
相关文件：
实现功能：客户端宏定义
作者：
版权：
------------------------------------------------------------
修改记录：
日  期	   	  版本		 修改人		  走读人      修改记录
  
===========================================================*/

#ifndef _CLIENTCOMMON_H_
#define _CLIENTCOMMON_H_

#define CLIENT_TELENT_PORT   (u16)2501

#define CLIENT_APP_NAME      "ClientApp"
#define CLIENT_APP_NO        1
#define CLIENT_APP_PRIO      100
#define CLIENT_APP_QUE_SIZE  1000

#define CONNECT_TIME_EVENT   (u16)(OSP_USEREVENT_BASE+0x0014)
#define REGISTER_TIME_EVENT  (u16)(OSP_USEREVENT_BASE+0x0015)
#define TIME_WATING          10
#define NODE_TIME_WATING      5
#define NUM_WATING            3

#define BUFFERSIZE            (u32)1045504                        //缓存大小1M

#define MAX_CLIENT_INS_NUM     3

#define CLIENT_FILE_PATH       "E:\\客户端测试文件夹"         //客户端下载文件存储路径

#endif