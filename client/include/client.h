#ifndef _CLIENT_H_
#define _CLIENT_H_

#define CLIENT_TELENT_PORT   2501
#define CLIENT_LISTEN_PORT   6682

#define CLIENT_APP_NAME      "ClientApp"
#define CLIENT_APP_NO        1
#define CLIENT_APP_PRIO      100
#define CLIENT_APP_QUE_SIZE  1000

#define MAX_CLIENT_INS_NUM   3

#define SERVER_PORT          5444



class CUserData
{
	public:
	s8 m_achIp;

    public:
    CUserData()
    {
        s8 m_achIp[20]  = {0};
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
 
private:
    void InstanceEntry(CMessage *const pMsg){};
    void DaemonInstanceEntry(CMessage *const pMsg,CApp* pcApp){};
	
};


typedef zTemplate<CClientInstance,MAX_CLIENT_INS_NUM,CUserData>CClientApp;


#endif

