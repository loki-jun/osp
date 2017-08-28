/*==========================================================
文件名：clientinterface.cpp
功能：接收用户指令
算法实现：
参数说明：
返回值说明：
-------------------------------------------------------------------------------------------------------
修改记录：
日  期		版本		修改人		走读人        修改记录

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
    cout << "您可以有如下操作：connect,dealpartfile,getfilelist,downloadfile,pausetask,resumetask,canceltask,disconnect,help" << endl;
    s8 achUserInput[20] ={0};
	//	s8 achUserInput[100] = {"connect","dealpartfile","getfilelist","downloadfile","pausetask","resumetask","canceltask","disconnect","help"};


//	u8 flag
	while (1)
	{
		cin.get(achUserInput,20);
		if(!strcmp(achUserInput,"connect"))
		{
			cout << "请输入ip地址：" << endl;
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
			cout << "输入错误，请重新输入" <<endl;
		}
        cin.clear();
        cin.sync();
	}
}