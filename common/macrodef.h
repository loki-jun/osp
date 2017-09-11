/*==========================================================                        
�ļ�����macrodef.h
����ļ���
ʵ�ֹ��ܣ��ͻ������������
���ߣ�
��Ȩ��
------------------------------------------------------------
�޸ļ�¼��
��  ��	   	  �汾		 �޸���		  �߶���      �޸ļ�¼
  
===========================================================*/

#ifndef _MACRODEF_H_
#define _MACRODEF_H_

/* ״̬ */
#define IDLE_STATE                  0
#define READY_STATE                 1
#define TRANSFER_STATE              2
#define PAUSEFLG_STATE              3
#define CONNECT_STATE               4 

#define SERVER_TELENT_PORT          (u16)2502
#define SERVER_LISTEN_PORT          (u16)6682

#define SERVER_APP_NO               1
#define STRING_LENGTH               256                 //�ļ�������
#define TransferSize                (u32)28672          //ÿ�δ���İ���С��28k


// log�ȼ�����
#define	LOG_LVL_ERROR				(u8)1				// �������д���(�߼���ҵ�����),�������
#define	LOG_LVL_WARNING				(u8)2				// �澯��Ϣ, ������ȷ, Ҳ���ܴ���
#define	LOG_LVL_KEYSTATUS			(u8)3				// �������е�һ���ؼ�״̬ʱ����Ϣ���
#define	LOG_LVL_DETAIL				(u8)4				// ��ͨ��Ϣ, ��ò�Ҫд��log�ļ���
#define	LOG_LVL_REPEAT				(u8)5				// ���߼����ӡ

//����log��ӡ����
#define	APP_ID                      0                   //ȫ��
#define	FILE_LEVEL                  0                   //��ֹ������ļ�
#define	SCREEN_LEVEL                5                   //��Ļ��ӡ��ֵ

#endif
