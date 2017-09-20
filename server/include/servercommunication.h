/*==========================================================                        
�ļ�����servertcommunication.h
����ļ���servercommon.h
ʵ�ֹ��ܣ���������ģ��APP�Լ��ඨ��
���ߣ�
��Ȩ��
------------------------------------------------------------
�޸ļ�¼��
��  ��	   	  �汾		 �޸���		  �߶���      �޸ļ�¼
  
===========================================================*/

#ifndef _SERVERCOMMUNICATION_H_
#define _SERVERCOMMUNICATION_H_

#include "../include/servercommon.h"
#include "../include/serverfilemanager.h"
#include "../include/servercreatefilelist.h"

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
	u32 m_dwBufferNum;
	CReadFile m_cFilemgr;
	CFileInfo m_cFileInfo;
	CFileListInfo m_cFileListInfo;
	CPackageInfo m_cPackageInfo;
	CFindFiles m_cFindFiles;
	CFindSizes m_cFindSizes;
	CFindMd5 m_cFindMd5;


public:
    CServerInstance()
    {
		clear();
    }
    ~CServerInstance()
    {
    }
	void clear()
	{
        m_dwDstIid = 0;
		m_dwDstNode = 0;
		m_dwBufferNum = 0;
	}
	
public:
    void InstanceEntry(CMessage *const pcMsg);
    void DaemonInstanceEntry(CMessage *const pcMsg,CApp* pcApp);
	void DaemonDealClientConnect(CMessage *const pcMsg, CApp* pcApp);
	void DaemonCheckConnect(){};
	void DaemonGetlist(CMessage *const pcMsg);
	void ProcCheckFile(CMessage *const pcMsg);
//	void ProcSendMsg(CMessage *const pcMsg);
	
};


typedef zTemplate<CServerInstance,MAX_SERVER_INS_NUM,CUserData>CServerApp;

void UserInit();

#endif