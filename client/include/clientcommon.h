/*==========================================================
ģ����������ģ��                        
�ļ�����clientinterface.cpp
����ļ���osp.h,clientcommon.h,clientinterface.h
ʵ�ֹ��ܣ������û�����
���ߣ�
��Ȩ��
------------------------------------------------------------
�޸ļ�¼��
��  ��	   	  �汾		 �޸���		  �߶���      �޸ļ�¼
  
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