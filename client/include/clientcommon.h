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

#ifndef _CLIENTCOMMON_H_
#define _CLIENTCOMMON_H_

#define CLIENT_TELENT_PORT   2501

#define CLIENT_APP_NAME      "ClientApp"
#define CLIENT_APP_NO        1
#define CLIENT_APP_PRIO      100
#define CLIENT_APP_QUE_SIZE  1000

#define CONNECT_TIME_EVENT   (u16)(OSP_USEREVENT_BASE+0x0014)
#define REGISTER_TIME_EVENT  (u16)(OSP_USEREVENT_BASE+0x0015)
#define TIME_WATING          1000

#define MAX_CLIENT_INS_NUM 3

#endif