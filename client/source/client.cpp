/*==========================================================                        
文件名：client.cpp
相关文件：osp.h，clientcommunication.h，clientinterface.h
实现功能：主函数入口
作者：
版权：
------------------------------------------------------------
修改记录：
日  期	   	  版本		 修改人		  走读人      修改记录
  
===========================================================*/

#include "../../common/osp.h"
#include "../include/clientcommunication.h"
#include "../include/clientinterface.h"

int main()
{
	UserInit();

	clientinterface();

	return 0;
	
}




