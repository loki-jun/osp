/*==========================================================                        
文件名：macrodef.h
相关文件：
实现功能：客户端与服务器宏
作者：
版权：
------------------------------------------------------------
修改记录：
日  期	   	  版本		 修改人		  走读人      修改记录
  
===========================================================*/

#ifndef _MACRODEF_H_
#define _MACRODEF_H_

/* 状态 */
#define IDLE_STATE                  0
#define READY_STATE                 1
#define TRANSFER_STATE              2
#define PAUSEFLG_STATE              3
#define CONNECT_STATE               4 

#define SERVER_TELENT_PORT          (u16)2502
#define SERVER_LISTEN_PORT          (u16)6682

#define SERVER_APP_NO               1
#define STRING_LENGTH               256                 //文件名长度
#define TransferSize                (u32)28672          //每次传输的包大小，28k


// log等级定义
#define	LOG_LVL_ERROR				(u8)1				// 程序运行错误(逻辑或业务出错),必须输出
#define	LOG_LVL_WARNING				(u8)2				// 告警信息, 可能正确, 也可能错误
#define	LOG_LVL_KEYSTATUS			(u8)3				// 程序运行到一个关键状态时的信息输出
#define	LOG_LVL_DETAIL				(u8)4				// 普通信息, 最好不要写进log文件中
#define	LOG_LVL_REPEAT				(u8)5				// 更高级别打印

//设置log打印级别
#define	APP_ID                      0                   //全局
#define	FILE_LEVEL                  0                   //禁止输出到文件
#define	SCREEN_LEVEL                5                   //屏幕打印阈值

#endif
