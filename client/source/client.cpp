/*==========================================================                        
�ļ�����client.cpp
����ļ���osp.h��clientcommunication.h��clientinterface.h
ʵ�ֹ��ܣ����������
���ߣ�
��Ȩ��
------------------------------------------------------------
�޸ļ�¼��
��  ��	   	  �汾		 �޸���		  �߶���      �޸ļ�¼
  
===========================================================*/

#include "../../common/osp.h"
#include "../../common/macrodef.h"
#include "../include/clientcommunication.h"
#include "../include/clientinterface.h"
#include "../include/clientcommon.h"

int main()
{

	UserInit();
	OspSetLogLevel(APP_ID,FILE_LEVEL,SCREEN_LEVEL);
//	clientinterface();

	while(1)
	{
		OspDelay(1000);
	}
	return 0;
	
}

/*********************************************************************
    ��׼API�ӿ�
*********************************************************************/

/* ��������ӿ�*/
API void help()
{
	OspPrintf( TRUE, FALSE, "connect       ���ӷ�����    ������u32 ip \n");
	OspPrintf( TRUE, FALSE, "dealpartfile  ����ϵ�����  ������num[]\n");
	OspPrintf( TRUE, FALSE, "getfilelist   ��ȡ�ļ��б�  ������NULL\n");
	OspPrintf( TRUE, FALSE, "downloadfile  �����ļ�      ������u16 FileIndex\n");
	OspPrintf( TRUE, FALSE, "pausetask     ��ͣ����      ������u16 taskID\n");
	OspPrintf( TRUE, FALSE, "resumetask    �ָ�����      ������u16 taskID\n");
	OspPrintf( TRUE, FALSE, "canceltask    ȡ������      ������u16 taskID\n");
	OspPrintf( TRUE, FALSE, "disconnect    �Ͽ�������    ������NULL\n");
	OspPrintf( TRUE, FALSE, "help          ��ӡ������Ϣ  ������NULL");
}

/* ���ӷ������ӿ� */
API void connectserver(LPSTR ip)
{
	//Ip�Ϸ��Լ���
	if (INADDR_NONE == inet_addr(ip))
	{
		OspPrintf(TRUE,FALSE,"ip��ַ���Ϸ������������룺");
	}
	else
	{
		OspPost(MAKEIID(CLIENT_APP_NO, CInstance::DAEMON), U_C_CONNECT_CMD,ip,20);
	}
}

/* ��ȡ�ļ��б�ӿ� */
API void getfilelist()
{
	OspPost(MAKEIID(CLIENT_APP_NO, CInstance::DAEMON), U_C_GETLIST_CMD);
}

/* �Ͽ����� */
API void disconnect()
{
	OspPost(MAKEIID(CLIENT_APP_NO, CInstance::DAEMON), U_C_DISCONNECT_CMD);
}


/* �����ļ� */
API void downloadfile(s8* FileName[256])
{
	OspPost(MAKEIID(CLIENT_APP_NO, CInstance::DAEMON), U_C_DOWNLOADFILE_CMD,FileName,256);
}

/* ��ͣ�ļ����� */
API void pausetask(u16 wTaskId)
{
	OspPost(MAKEIID(CLIENT_APP_NO, CInstance::DAEMON), U_C_PAUSETASK_CMD,&wTaskId,sizeof(wTaskId));
}


/* �ָ��ļ����� */
API void resumetask(u16 wTaskId)
{
	OspPost(MAKEIID(CLIENT_APP_NO, CInstance::DAEMON), U_C_RESUMETASK_CMD,&wTaskId,sizeof(wTaskId));
}

/* �ָ��ļ����� */
API void canceltask(u16 wTaskId)
{
	OspPost(MAKEIID(CLIENT_APP_NO, CInstance::DAEMON), U_C_CANCELTASK_CMD,&wTaskId,sizeof(wTaskId));
}

/*********************************************************************
    ����ĸ���Խӿ�
*********************************************************************/
API void h()
{
	help();
}

//API void c(LPSTR ip)
API void c()
{
//	connectserver(ip);
	connectserver("127.0.0.1");
}

API void l()
{
	getfilelist();
}

API void dis()
{
	disconnect();
}

API void d(s8* FileName[256])
{
	downloadfile(FileName);
}

API void p(u16 wTaskId)
{
	pausetask(wTaskId);
}

API void r(u16 wTaskId)
{
	resumetask(wTaskId);
}

API void ct(u16 wTaskId)
{
	canceltask(wTaskId);
}