/*==========================================================                      
�ļ�����clientcommunication.h
����ļ���clientcommon.h
ʵ�ֹ��ܣ���������ģ��APP�Լ��ඨ��
���ߣ�
��Ȩ��
------------------------------------------------------------
�޸ļ�¼��
��  ��	   	  �汾		 �޸���		  �߶���      �޸ļ�¼
  
===========================================================*/

#ifndef _CLIENTCOMMUNICATION_H_
#define _CLIENTCOMMUNICATION_H_

#include "../include/clientcommon.h"

#define C_C_CONNECTSUCCESS_CMD          (u16)(OSP_USEREVENT_BASE+0x001E) //�ͻ������ӷ������ɹ���׼��ע�����client(daemon->instance)
#define C_C_DOWNLOADFILE_CMD            (u16)(OSP_USEREVENT_BASE+0x0020) //�����ļ�ָ�client(daemon->instance)����Ϣ������Ϊ0 or 1����ʾ�ϵ����������

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