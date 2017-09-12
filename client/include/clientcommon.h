/*==========================================================                      
�ļ�����clientcommon.h
����ļ���
ʵ�ֹ��ܣ��ͻ��˺궨��
���ߣ�
��Ȩ��
------------------------------------------------------------
�޸ļ�¼��
��  ��	   	  �汾		 �޸���		  �߶���      �޸ļ�¼
  
===========================================================*/

#include "../../common/kdvtype.h"
#include "../../common/osp.h"
#include "../../common/kdvdef.h"
#include "../../common/csmsg.h"
#include "../../common/macrodef.h"

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

#define CLIENT_BUFFERSIZE     (u32)2560000                       //�����С

#define MAX_CLIENT_INS_NUM     3

#define CLIENT_FILE_PATH       "E:\\�ͻ��˲����ļ���"         //�ͻ��������ļ��洢·��

#endif