/*==========================================================                       
文件名：clientinterface.h
相关文件：
实现功能：定义交互模块与通信模块的消息
作者：
版权：
------------------------------------------------------------
修改记录：
日  期	   	  版本		 修改人		  走读人      修改记录
  
===========================================================*/

#ifndef _CLIENTINTERFACE_H_
#define _CLIENTINTERFACE_H_

#define U_C_CONNECT_CMD            (u16)(OSP_USEREVENT_BASE+0x0013) //连接命令，user->client(daemon)，消息体为u32 Ip
#define U_C_DISCONNECT_CMD         (u16)(OSP_USEREVENT_BASE+0x0016) //断开连接，user->client(daemon)
#define U_C_GETLIST_CMD            (u16)(OSP_USEREVENT_BASE+0x0017) //获取文件列表命令，user->client(daemon)
#define U_C_DOWNLOADFILE_CMD       (u16)(OSP_USEREVENT_BASE+0x0018) //下载文件命令，user->client(daemon)，消息体为s8(pbyFilename)
#define U_C_PAUSETASK_CMD          (u16)(OSP_USEREVENT_BASE+0x0019) //暂停下载，user->client(daemon)，消息体为u16 taskID
#define U_C_RESUMETASK_CMD         (u16)(OSP_USEREVENT_BASE+0x001A) //恢复下载，user->client(daemon)，消息体为u16 taskID
#define U_C_CANCELTASK_CMD         (u16)(OSP_USEREVENT_BASE+0x001B) //取消下载，user->client(daemon)，消息体为u16 taskID
#define U_C_DOWNLOADPARTFILE_CMD   (u16)(OSP_USEREVENT_BASE+0x001C) //下载断点续传文件，user->client(daemon)，消息体为CConfigData
#define U_C_CANCELPARTFILE_CMD     (u16)(OSP_USEREVENT_BASE+0x001D) //取消断点续传文件下载，user->client(daemon)，消息体为s8(pbyFilename)

void clientinterface(void);
void showlist(CMessage *const pcMsg);

#endif
 

