/*==========================================================
�ļ�����clientinterface.cpp
���ܣ������û�ָ��
�㷨ʵ�֣�
����˵����
����ֵ˵����
-------------------------------------------------------------------------------------------------------
�޸ļ�¼��
��  ��		�汾		�޸���		�߶���        �޸ļ�¼

===========================================================*/

#include "iostream"
#include "io.h"
#include "../../common/kdvtype.h"
#include "../../common/osp.h"
#include "../../common/kdvdef.h"
#include "../include/client.h"
#include "../include/clientinterface.h"

using namespace std;

extern CClientApp g_CClientApp;

void help()
{
	cout << "connect       ���ӷ�����  ������ip " <<endl;
	cout << "dealpartfile  �����ϵ�����  " <<endl;
	cout << "getfilelist   ��ȡ�ļ��б�" <<endl;
	cout << "downloadfile  �����ļ�" <<endl;
	cout << "pausetask     ��ͣ����" <<endl;
	cout << "resumetask    �ָ�����" <<endl;
	cout << "canceltask    ȡ������" <<endl;
	cout << "disconnect    �Ͽ�������" <<endl;
	cout << "help          ��ӡ������Ϣ" <<endl;

}

void connect()
{

}

void clientinterface()
{
    cout << "�����������²�����" << endl;
	help();

    
	while (1)
	{
		s8 achUserInput[20] ={0};

		cin.clear();
        cin.sync();

		cin.get(achUserInput,20);

		if(!strcmp(achUserInput,"connect"))
		{
			cout << "������ip��ַ��" << endl;

			getchar();

			cin.get(&g_CClientApp.m_achIp,20);

			if(!OspPost(MAKEIID(CLIENT_APP_NO, CInstance::DAEMON), U_C_CONNECT_CMD))
			{
				cout << "succeed " << endl;
			}

//			break;
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
			cout << "connect       ���ӷ�����" <<endl;
			cout << "dealpartfile  �����ϵ�����" <<endl;
			cout << "getfilelist   ��ȡ�ļ��б�" <<endl;
			cout << "downloadfile  �����ļ�" <<endl;
			cout << "pausetask     ��ͣ����" <<endl;
			cout << "resumetask    �ָ�����" <<endl;
			cout << "canceltask    ȡ������" <<endl;
			cout << "disconnect    �Ͽ�������" <<endl;
			cout << "help          ��ӡ������Ϣ" <<endl;
			break;
		}
		else
		{
			cout << "�����������������" <<endl;
		}


	}
}