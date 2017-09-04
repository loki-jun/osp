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


class CServerInstance : public CInstance{
private:
	u32 m_dwDstIid;
	u32 m_dwDstNode;
	u32 m_dwNodeNum;
public:
    CServerInstance()
    {
        m_dwNodeNum = 0;
    }
    ~CServerInstance()
    {
    }
	
public:
    void InstanceEntry(CMessage *const pMsg);
    void DaemonInstanceEntry(CMessage *const pMsg,CApp* pcApp);
	void DaemonDealClientConnect(CMessage *const pcMsg, CApp* pcApp);
	void DaemonCheckConnect(){};
	void CreateFileList(){};
	
};


typedef zTemplate<CServerInstance,MAX_SERVER_INS_NUM>CServerApp;

void UserInit();

#endif