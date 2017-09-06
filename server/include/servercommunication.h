/*==========================================================                        
文件名：servertcommunication.h
相关文件：servercommon.h
实现功能：声明交互模块APP以及类定义
作者：
版权：
------------------------------------------------------------
修改记录：
日  期	   	  版本		 修改人		  走读人      修改记录
  
===========================================================*/

#ifndef _SERVERCOMMUNICATION_H_
#define _SERVERCOMMUNICATION_H_

#include "../include/servercommon.h"

class CUserData
{
public:
	u32 m_dwNodeNum;
	
public:
    CUserData()
    {
		m_dwNodeNum = 0;
    }
    ~CUserData()
    {
    }
	
};


class CServerInstance : public CInstance{
private:
	u32 m_dwDstIid;
	u32 m_dwDstNode;
public:
    CServerInstance()
    {
        m_dwDstIid = 0;
		m_dwDstNode = 0;
    }
    ~CServerInstance()
    {
    }
	
public:
    void InstanceEntry(CMessage *const pMsg);
    void DaemonInstanceEntry(CMessage *const pMsg,CApp* pcApp);
	void DaemonDealClientConnect(CMessage *const pcMsg, CApp* pcApp);
	void DaemonCheckConnect(){};
	void DaemonGetlist(CMessage *const pcMsg);
	
};


typedef zTemplate<CServerInstance,MAX_SERVER_INS_NUM,CUserData>CServerApp;

void UserInit();

#endif