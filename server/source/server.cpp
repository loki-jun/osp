/*==========================================================                        
�ļ�����server.cpp
����ļ���osp.h��servercommunication.h
ʵ�ֹ��ܣ����������
���ߣ�
��Ȩ��
------------------------------------------------------------
�޸ļ�¼��
��  ��	   	  �汾		 �޸���		  �߶���      �޸ļ�¼
  
===========================================================*/

#include "../../common/osp.h"
#include "../include/servercommunication.h"

int main()
{
	UserInit();
	OspSetLogLevel(APP_ID,FILE_LEVEL,SCREEN_LEVEL);
	while(1)
	{
		OspDelay(1000);
	}
	
}