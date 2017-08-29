#ifndef _SERVER_H_
#define _SERVER_H_

#define SERVER_APP_NAME      "ServerApp"
#define SERVER_APP_PRIO      100
#define SERVER_APP_QUE_SIZE  1000

#define MAX_SERVER_INS_NUM    60


class CServerInstance : public CInstance{
private:
	u16 m_wFileId;
	s8  m_pbyFilename[256];
	u16 m_wDownloadState;
	u32 m_dwDstIid;
	u32 m_dwDstNode;
	
private:
    void InstanceEntry(CMessage *const pMsg){};
    void DaemonInstanceEntry(CMessage *const pMsg,CApp* pcApp){};
	
};


typedef zTemplate<CServerInstance,MAX_SERVER_INS_NUM>CServerApp;

#endif

