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

#include "iostream"
#include "io.h"
#include "../../common/kdvtype.h"
#include "../../common/osp.h"
#include "../../common/kdvdef.h"
#include "../include/clientcommon.h"
#include "../include/clientinterface.h"

using namespace std;


/*********************************************************************
    help����
*********************************************************************/
void help()
{
	cout << "connectserver ���ӷ�����    ������u32 ip " <<endl;
	cout << "dealpartfile  ����ϵ�����  ������num[]" <<endl;
	cout << "getfilelist   ��ȡ�ļ��б�  ������NULL" <<endl;
	cout << "downloadfile  �����ļ�      ������u16 FileIndex" <<endl;
	cout << "pausetask     ��ͣ����      ������u16 taskID" <<endl;
	cout << "resumetask    �ָ�����      ������u16 taskID" <<endl;
	cout << "canceltask    ȡ������      ������u16 taskID" <<endl;
	cout << "disconnect    �Ͽ�������    ������NULL" <<endl;
	cout << "help          ��ӡ������Ϣ  ������NULL" <<endl;
	
}

/*********************************************************************
    ���Ӻ���
*********************************************************************/
void connect()
{
	cout << "������ip��ַ��" << endl;

	cin.clear();
	cin.sync();

	s8 achIp[20];
    cin.get(achIp,20);

	if(!OspPost(MAKEIID(CLIENT_APP_NO, CInstance::DAEMON), U_C_CONNECT_CMD,achIp,sizeof(achIp)))
	{
		cout << "succeed" << endl;
	}


}

/*==========================================================
��������clientinterface
���ܣ�����ģ�麯�����
�㷨ʵ�֣�
����˵����
����ֵ˵����
-------------------------------------------------------------------------------------------------------
�޸ļ�¼��
��  ��		�汾		�޸���		�߶���        �޸ļ�¼

===========================================================*/

void clientinterface()
{
    cout << "�����������²�����" << endl;
	help();

	while (1)
	{
		s8 achUserInput[20];
		cin.get(achUserInput,20);

		if(!strcmp(achUserInput,"connect"))
		{
			connect();
			break;
		}
		else if (!strcmp(achUserInput,"dealpartfile"))
		{
			
		}
		else if (!strcmp(achUserInput,"getfilelist"))
		{
			
		}
		else if (!strcmp(achUserInput, "downloadfile"))
		{
			
		}
		else if (!strcmp(achUserInput,"pausetask"))
		{
			
		}
		else if (!strcmp(achUserInput,"resumetask"))
		{
			
		}
		else if (!strcmp(achUserInput,"canceltask"))
		{
			
		}
		else if (!strcmp(achUserInput,"resumetask"))
		{
			
		}
		else if (!strcmp(achUserInput, "disconnect"))
		{
			
		}
		else if (!strcmp(achUserInput,"help"))
		{
			help();
			break;
		}
		else
		{
			cout << "�����������������" <<endl;
		}

		cin.clear();
		cin.sync();
	}

}

