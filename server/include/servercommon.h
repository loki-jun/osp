/*==========================================================                       
�ļ�����servercommon.h
����ļ���
ʵ�ֹ��ܣ��������˺궨��
���ߣ�
��Ȩ��
------------------------------------------------------------
�޸ļ�¼��
��  ��	   	  �汾		 �޸���		  �߶���      �޸ļ�¼
  
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

#endif