/*==========================================================                      
文件名：clientcommunication.h
相关文件：clientcommon.h
实现功能：声明交互模块APP以及类定义
作者：
版权：
------------------------------------------------------------
修改记录：
日  期	   	  版本		 修改人		  走读人      修改记录
  
===========================================================*/

#ifndef _CLIENTCOMMUNICATION_H_
#define _CLIENTCOMMUNICATION_H_

#include "../include/clientcommon.h"

#define C_C_CONNECTSUCCESS_CMD          (u16)(OSP_USEREVENT_BASE+0x001E)

class CUserData
{
public:
	u32 m_achIp;
	u32 m_dwDstNode;
	
public:
    CUserData()
    {
        m_achIp = 0;
		m_dwDstNode = 0;
    }
    ~CUserData()
    {
    }
	
};


class CClientInstance : public CInstance{
private:
	u16 m_wNormalPackageId[MAX_CLIENT_INS_NUM];
	u16 m_wDownloadState;
	u32 m_dwDstIid;
//	u32 m_dwDstNode;
	
public:
    void InstanceEntry(CMessage *const pMsg);
    void DaemonInstanceEntry(CMessage *const pMsg,CApp* pcApp);
	void DaemonConnectServer();
	void DaemonDisConnectServer(){};
	
};


typedef zTemplate<CClientInstance,MAX_CLIENT_INS_NUM,CUserData>CClientApp;

void UserInit();

#endif