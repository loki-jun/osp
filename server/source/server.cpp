/*==========================================================                        
文件名：server.cpp
相关文件：osp.h，servercommunication.h
实现功能：主函数入口
作者：
版权：
------------------------------------------------------------
修改记录：
日  期	   	  版本		 修改人		  走读人      修改记录
  
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