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

using namespace std;

//CUserData g_CUserData;

void clientinterface()
{
    cout << "�����������²�����connect,dealpartfile,getfilelist,downloadfile,pausetask,resumetask,canceltask,disconnect,help" << endl;
    s8 achUserInput[20] ={0};
	//	s8 achUserInput[100] = {"connect","dealpartfile","getfilelist","downloadfile","pausetask","resumetask","canceltask","disconnect","help"};


//	u8 flag
	while (1)
	{
		cin.get(achUserInput,20);
		if(!strcmp(achUserInput,"connect"))
		{
			cout << "������ip��ַ��" << endl;
			cin.clear();
            cin.sync();
			s8 m_achIp[20]  = {0};
			cin.get(m_achIp,20);
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
			
		}
		else
		{
			cout << "�����������������" <<endl;
		}
        cin.clear();
        cin.sync();
	}
}