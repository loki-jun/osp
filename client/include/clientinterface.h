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

#define U_C_CONNECT_CMD            (u16)(OSP_USEREVENT_BASE+0x0013) //�������user->client(daemon)����Ϣ��Ϊu32 Ip
#define U_C_DISCONNECT_CMD         (u16)(OSP_USEREVENT_BASE+0x0016) //�Ͽ����ӣ�user->client(daemon)
#define U_C_GETLIST_CMD            (u16)(OSP_USEREVENT_BASE+0x0017) //��ȡ�ļ��б����user->client(daemon)
#define U_C_DOWNLOADFILE_CMD       (u16)(OSP_USEREVENT_BASE+0x0018) //�����ļ����user->client(daemon)����Ϣ��Ϊs8(pbyFilename)
#define U_C_PAUSETASK_CMD          (u16)(OSP_USEREVENT_BASE+0x0019) //��ͣ���أ�user->client(daemon)����Ϣ��Ϊu16 taskID
#define U_C_RESUMETASK_CMD         (u16)(OSP_USEREVENT_BASE+0x001A) //�ָ����أ�user->client(daemon)����Ϣ��Ϊu16 taskID
#define U_C_CANCELTASK_CMD         (u16)(OSP_USEREVENT_BASE+0x001B) //ȡ�����أ�user->client(daemon)����Ϣ��Ϊu16 taskID
#define U_C_DOWNLOADPARTFILE_CMD   (u16)(OSP_USEREVENT_BASE+0x001C) //���ضϵ������ļ���user->client(daemon)����Ϣ��ΪCConfigData
#define U_C_CANCELPARTFILE_CMD     (u16)(OSP_USEREVENT_BASE+0x001D) //ȡ���ϵ������ļ����أ�user->client(daemon)����Ϣ��Ϊs8(pbyFilename)

void clientinterface(void);
void showlist(CMessage *const pcMsg);

#endif
 

