#ifndef _CLIENT_H_
#define _CLIENT_H_

#define CLIENT_TELENT_PORT   2501
#define CLIENT_LISTEN_PORT   6682

#define CLIENT_APP_NAME      "ClientApp"
#define CLIENT_APP_NO        1
#define CLIENT_APP_PRIO      100
#define CLIENT_APP_QUE_SIZE  1000



#define CONNECT_TIME_EVENT   (u16)(OSP_USEREVENT_BASE+0x0014)
#define REGISTER_TIME_EVENT  (u16)(OSP_USEREVENT_BASE+0x0015)
#define TIME_WATING          1000

#define MAX_CLIENT_INS_NUM 3

void clientinterface(void);

class CUserData
{
	public:
	s8 m_achIp[20];

    public:
    CUserData()
    {
        memset();
    }
    ~CUserData()
    {
    }

};


class CClientInstance : public CInstance{
private:
	u16 m_wNormalPackageId[3];
	u16 m_wDownloadState;
	u32 m_dwDstIid;
	u32 m_dwDstNode;
 
public:
    void InstanceEntry(CMessage *const pMsg){};
    void DaemonInstanceEntry(CMessage *const pMsg,CApp* pcApp);
	void DaemonConnectServer(CMessage *const pcMsg);
	void DaemonDisConnectServer(){};
	
};


typedef zTemplate<CClientInstance,MAX_CLIENT_INS_NUM,CUserData>CClientApp;


#endif

