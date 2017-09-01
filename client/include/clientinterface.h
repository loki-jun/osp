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

#define U_C_CONNECT_CMD            (u16)(OSP_USEREVENT_BASE+0x0013)
#define U_C_DISCONNECT_CMD         (u16)(OSP_USEREVENT_BASE+0x0016)
#define U_C_GETLIST_CMD            (u16)(OSP_USEREVENT_BASE+0x0017)
#define U_C_DOWNLOADFILE_CMD       (u16)(OSP_USEREVENT_BASE+0x0018)
#define U_C_PAUSETASK_CMD          (u16)(OSP_USEREVENT_BASE+0x0019)
#define U_C_RESUMETASK_CMD         (u16)(OSP_USEREVENT_BASE+0x001A)
#define U_C_CANCELTASK_CMD         (u16)(OSP_USEREVENT_BASE+0x001B)
#define U_C_DOWNLOADPARTFILE_CMD   (u16)(OSP_USEREVENT_BASE+0x001C)
#define U_C_CANCELPARTFILE_CMD     (u16)(OSP_USEREVENT_BASE+0x001D)

void clientinterface(void);

#endif
 

