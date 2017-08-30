/*==========================================================                       
�ļ�����csmsg.h
����ļ���
ʵ�ֹ��ܣ�����ͻ����������֮�����Ϣ
���ߣ�
��Ȩ��
------------------------------------------------------------
�޸ļ�¼��
��  ��	   	  �汾		 �޸���		  �߶���      �޸ļ�¼
  
===========================================================*/

#ifndef _CSMSG_H_
#define _CSMSG_H_

/* ���ӷ����� */
#define C_S_CONNECT_REQ              (u16)(OSP_USEREVENT_BASE+0x0001)
#define S_C_CONNECT_ACK              (u16)(OSP_USEREVENT_BASE+0x0002)
#define S_C_CONNECT_NACK             (u16)(OSP_USEREVENT_BASE+0x0003)

/* ����ע�� */
#define C_S_REGISTER_REQ             (u16)(OSP_USEREVENT_BASE+0x0004)
#define S_C_REGISTER_ACK             (u16)(OSP_USEREVENT_BASE+0x0005)
#define S_C_REGISTER_NACK            (u16)(OSP_USEREVENT_BASE+0x0006)

/* ��ȡ�ļ��б� */
#define C_S_GETLIST_REQ              (u16)(OSP_USEREVENT_BASE+0x0007)
#define S_C_GETLIST_ACK              (u16)(OSP_USEREVENT_BASE+0x0008)
#define S_C_GETLIST_NACK             (u16)(OSP_USEREVENT_BASE+0x0009)

/* �ļ����� */
#define C_S_FILENAME_REQ             (u16)(OSP_USEREVENT_BASE+0x000A) /*�����ļ�����*/
#define S_C_FILENAME_ACK             (u16)(OSP_USEREVENT_BASE+0x000B) /*�ļ�����ȷ��*/
#define S_C_FILENAME_NACK            (u16)(OSP_USEREVENT_BASE+0x000C)

#define C_S_DOWNLOADDATA_REQ         (u16)(OSP_USEREVENT_BASE+0x000D) /*���ݰ���������*/
#define S_C_DOWNLOADDATA_ACK         (u16)(OSP_USEREVENT_BASE+0x000E) /*�������ݰ�������*/
#define S_C_DOWNLOADDATA_NACK        (u16)(OSP_USEREVENT_BASE+0x000F)

/* ȡ���ļ����� */
#define C_S_CANCELFILE_REQ           (u16)(OSP_USEREVENT_BASE+0x0010)
#define S_C_CANCELFILE_ACK           (u16)(OSP_USEREVENT_BASE+0x0011)
#define S_C_CANCELFILE_NACK          (u16)(OSP_USEREVENT_BASE+0x0012)

#endif