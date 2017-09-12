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

#define C_C_CONNECTSUCCESS_CMD          (u16)(OSP_USEREVENT_BASE+0x001E) //客户端连接服务器成功，准备注册命令，client(daemon->instance)
#define C_C_DOWNLOADFILE_CMD            (u16)(OSP_USEREVENT_BASE+0x0020) //下载文件指令，client(daemon->instance)，消息体内容为0 or 1，表示断点和正常下载

class CUserData
{
public:
	u32 m_dwIp;

	
public:
    CUserData()
    {
        m_dwIp = 0;

    }
    ~CUserData()
    {
    }
	
};


class CClientInstance : public CInstance{
private:
	u16 m_wNormalPackageId[MAX_CLIENT_INS_NUM];
	u16 m_wDownloadState;
	u32 m_dwDstId;
	u32 m_dwDstNode;
	CFileInfo m_cFileInfo;
	CFileListInfo m_cFileListInfo;
	CPackageInfo m_cPackageInfo;
	
public:
    void InstanceEntry(CMessage *const pMsg);
    void DaemonInstanceEntry(CMessage *const pMsg,CApp* pcApp);
	void DaemonConnectServer();
	void DaemonDisConnectServer();
	
};


typedef zTemplate<CClientInstance,MAX_CLIENT_INS_NUM,CUserData>CClientApp;

void UserInit();

#endif