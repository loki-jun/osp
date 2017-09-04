/*==========================================================                       
�ļ�����clientinterface.h
����ļ���
ʵ�ֹ��ܣ����彻��ģ����ͨ��ģ�����Ϣ
���ߣ�
��Ȩ��
------------------------------------------------------------
�޸ļ�¼��
��  ��	   	  �汾		 �޸���		  �߶���      �޸ļ�¼
  
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
void showlist(CMessage *const pMsg);

#endif
 

