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
	clientinterface();

	while(1)
	{

	}
	return 0;
	
}

/* ��������ӿ�*/
API void h()
{
	OspPrintf( TRUE, FALSE, "connect       ���ӷ�����    ������u32 ip \n");
	OspPrintf( TRUE, FALSE, "dealpartfile  ����ϵ�����  ������num[]\n");
	OspPrintf( TRUE, FALSE, "getfilelist   ��ȡ�ļ��б�  ������NULL\n");
	OspPrintf( TRUE, FALSE, "downloadfile  �����ļ�      ������u16 FileIndex\n");
	OspPrintf( TRUE, FALSE, "pausetask     ��ͣ����      ������u16 taskID\n");
	OspPrintf( TRUE, FALSE, "resumetask    �ָ�����      ������u16 taskID\n");
	OspPrintf( TRUE, FALSE, "canceltask    ȡ������      ������u16 taskID\n");
	OspPrintf( TRUE, FALSE, "disconnect    �Ͽ�������    ������NULL\n");
	OspPrintf( TRUE, FALSE, "help          ��ӡ������Ϣ  ������NULL\n");
}

/* ���ӷ����� */
API void c(LPSTR ip)
{
	OspPost(MAKEIID(CLIENT_APP_NO, CInstance::DAEMON), U_C_CONNECT_CMD,ip,20);
}


