/*==========================================================                        
�ļ�����servercommunication.cpp
����ļ���
ʵ�ֹ��ܣ�������Ϣ�����Լ������ļ�����ģ��ӿ�
���ߣ�
��Ȩ��
------------------------------------------------------------
�޸ļ�¼��
��  ��	   	  �汾		 �޸���		  �߶���      �޸ļ�¼
  
===========================================================*/

#include <stdio.h>
#include <iostream>
#include <fstream> 
#include "../include/servercommon.h"
#include "../include/servercommunication.h"
//#include "../include/servercreatefilelist.h"
//#include "../include/serverfilemanager.h"

using namespace std;

CServerApp g_CServerApp;

/*********************************************************************
    ��ʼ������
*********************************************************************/
void UserInit()
{
	if( !( IsOspInitd( ) ) )
	{
		// ��ʼ��Osp, �ڶ˿�2502����Telnet
		BOOL32 bRetOspinit = OspInit( TRUE, SERVER_TELENT_PORT );         		
		if( !bRetOspinit )
		{	
			OspLog(LOG_LVL_ERROR,"***��ʼ��ospʧ��***");
			return ;
		}
	}

	// ��6682�˿��ϴ������ؼ������ 
//	u32 dwRetCreateTcpNode = OspCreateTcpNode( inet_addr("127.0.0.1"), SERVER_LISTEN_PORT );   
	u32 dwRetCreateTcpNode = OspCreateTcpNode( 0, SERVER_LISTEN_PORT );	
	if( dwRetCreateTcpNode == INVALID_SOCKET )
	{
		OspLog(LOG_LVL_ERROR,"***���������ڵ�ʧ��***");
		return;
	}
	
	//����APP	
	g_CServerApp.CreateApp( SERVER_APP_NAME, 
		SERVER_APP_NO,  
		SERVER_APP_PRIO, 
		SERVER_APP_QUE_SIZE);	
	
	OspLog(LOG_LVL_DETAIL,"***��ʼ���ɹ�***");
	return ;
}


/*********************************************************************
    DaemonDealClientConnect����
*********************************************************************/

void CServerInstance::DaemonDealClientConnect(CMessage *const pcMsg, CApp* pcApp)
{
	if ( g_CServerApp.m_dwNodeNum <= MAX_SERVER_NODE_SIZE)
	{
		post(pcMsg->srcid, S_C_CONNECT_ACK,NULL,0,pcMsg->srcnode);
	}
	else
	{
        post(pcMsg->srcid, S_C_CONNECT_NACK,NULL,0,pcMsg->srcnode);
	}
	/*
    u16 curEvent = pcMsg->event;
	CServerInstance* pCInstance = NULL;
    u32 dwInsCout=0;

    for( dwInsCout = 1; dwInsCout <= MAX_SERVER_INS_NUM; dwInsCout++)
    {
        pCInstance = (CServerInstance* )pcApp->GetInstance(dwInsCout);
        if ( IDLE_STATE == pCInstance->CurState() )
        {
            post(pcMsg->srcid, S_C_CONNECT_ACK,NULL,0,pcMsg->srcnode);
            pCInstance->NextState(READY_STATE);
            break;
        }
    }
    if ( MAX_SERVER_INS_NUM < dwInsCout )
    {
        OspPost(MAKEIID(pcMsg->srcid, DAEMON), S_C_CONNECT_NACK, pcMsg->content, sizeof(u32));
    }
	*/
}

/*********************************************************************
    ��ȡ�ļ��б���
*********************************************************************/
void CServerInstance::DaemonGetlist(CMessage *const pcMsg)
{
	vector<string> fileNames;
	vector<u32> fileSizes;
	vector<u8> filemd5s;
	
	fileNames = m_cFindFiles.findFiles( "E:\\�����ļ���" );
	fileSizes = m_cFindSizes.findSizes("E:\\�����ļ���");
	filemd5s = m_cFindMd5.findMd5("E:\\\\�����ļ���");  //md5ֵû��get����ò�Ƽ�������ַ��������顭��

	m_cFileListInfo.setfilenum(fileNames.size());

	u16 wCount = 0;
	CFileInfo cFileInfo;//�˴�����ֲ�����������Ҫ�洢

	for ( wCount =0; wCount<fileNames.size(); wCount++)
	{      
		cFileInfo.clear();
		cFileInfo.setnetfilesize(fileSizes[wCount]);
		cFileInfo.setfilename(&fileNames[wCount][0u]);
		m_cFileListInfo.setfileinfo(&cFileInfo);
//		memcpy(&cFileInfo.getfilename(),&fileNames[wCount][0u],sizeof(cFileInfo.getfilename()));//��[0u]���Խ����������
//		memcpy(&m_cFileListInfo.m_pbyFileInfo[wCount],&cFileInfo,sizeof(cFileInfo));
		OspPrintf(TRUE,FALSE,"[DaemonGetlist] 3 fileSizes[%d].%d m_dwFileSize.%d \n", 
			wCount, fileSizes[wCount],cFileInfo.getfilesize());

	}	

	m_cFileListInfo.printf();
	post(pcMsg->srcid,S_C_GETLIST_ACK, &m_cFileListInfo,sizeof(m_cFileListInfo),pcMsg->srcnode);
	OspLog(LOG_LVL_DETAIL,"�ļ��б��С��%d\n",sizeof(m_cFileListInfo));
}

/*********************************************************************
    �ļ�У�麯��
*********************************************************************/
void CServerInstance::ProcCheckFile(CMessage *const pcMsg)
{
	vector<string> fileNames;
	vector<u32> fileSizes;

	fileNames = m_cFindFiles.findFiles( "E:\\�����ļ���" );
	fileSizes = m_cFindSizes.findSizes("E:\\�����ļ���");

	u16 wCount = 0;
	for ( wCount =0; wCount<fileNames.size(); wCount++ )
	{   
		s8 achFileName[STRING_LENGTH];
		s8 achServerFileName[STRING_LENGTH];
		memcpy(achFileName,pcMsg->content,pcMsg->length);
		memcpy(achServerFileName,&fileNames[wCount][0u],sizeof(achServerFileName));

        m_cFileInfo.setnetfilesize(fileSizes[wCount]);
//		memcpy(&m_cFileInfo.m_dwFileSize,&fileSizes[wCount],sizeof(m_cFileInfo.m_dwFileSize));
		m_cFileInfo.setfilename(&fileNames[wCount][0u]);
//		memcpy(&m_cFileInfo.getfilename(),&fileNames[wCount][0u],sizeof(m_cFileInfo.getfilename()));

		if (0 == strcmp(achServerFileName,achFileName))
		{
			post(pcMsg->srcid,S_C_FILENAME_ACK,&m_cFileInfo,sizeof(m_cFileInfo),pcMsg->srcnode);
			break;
		}		
	}
	if (wCount >= fileNames.size())
	{
		post(pcMsg->srcid,S_C_FILENAME_NACK,NULL,0,pcMsg->srcnode);
	}
}


/*********************************************************************
    ������������Ϣ����
*********************************************************************/

/*
void CServerInstance::ProcSendMsg(CMessage *const pcMsg)
{
	memcpy(&m_cPackageInfo,pcMsg->content,pcMsg->length);
	//����buffer�а���ƫ����
	u32 dwShift = (m_cPackageInfo.m_wPackageId - (m_dwBufferNum-1)*PACKAGENUM_EACHBUFFER)*TransferSize;
	//�ж��Ƿ������һ�����������һ������TransferSize���������������һ����С����
	if ( m_cPackageInfo.m_dwFileSize/TransferSize != m_cPackageInfo.m_wPackageId)
	{

		memset(m_cPackageInfo.m_pbyPackageContent,0x00,sizeof(m_cPackageInfo.m_pbyPackageContent));
		memcpy(m_cPackageInfo.m_pbyPackageContent,m_cFilemgr.m_Buffer+dwShift,TransferSize);
		post(pcMsg->srcid, S_C_DOWNLOADDATA_ACK, &m_cPackageInfo, sizeof(m_cPackageInfo), pcMsg->srcnode);
	}
	else
	{
		OspLog(LOG_LVL_DETAIL,"�������������һ������\n");
		memset(m_cPackageInfo.m_pbyPackageContent,0x00,sizeof(m_cPackageInfo.m_pbyPackageContent));
		memcpy(m_cPackageInfo.m_pbyPackageContent,m_cFilemgr.m_Buffer+dwShift,m_cPackageInfo.m_dwFileSize%TransferSize);
		OspLog(LOG_LVL_DETAIL,"����С��%d\n",m_cPackageInfo.m_dwFileSize%TransferSize);
		post(pcMsg->srcid, S_C_DOWNLOADDATA_ACK, &m_cPackageInfo, sizeof(m_cPackageInfo), pcMsg->srcnode);
		m_cPackageInfo.printf();
		NextState(READY_STATE);
	}
}
*/


/*********************************************************************
    DaemonInstanceEntry����
*********************************************************************/

void CServerInstance::DaemonInstanceEntry(CMessage *const pcMsg, CApp* pcApp)
{
    //u32 curState = CurState();
    u16 curEvent = pcMsg->event;
	u32 dwInsCout = 0;
	CServerInstance* pCInstance = NULL;

    switch(curEvent)
    {
        /* �������� */
//        case CONNECT_TIME_EVENT:
        case C_S_CONNECT_REQ:
			g_CServerApp.m_dwNodeNum++;
//			OspLog(LOG_LVL_DETAIL,"�����������daemon\n");
            DaemonDealClientConnect(pcMsg, pcApp);
            break;

		/* ��ȡ�ļ��б����� */
        case C_S_GETLIST_REQ:
			OspLog(LOG_LVL_DETAIL,"�����������ļ��б�����\n");
            DaemonGetlist(pcMsg);
            break;
		
	

		/* ȡ������ */
		case C_S_CANCELFILE_REQ:
			 
            break;

        default:
            OspLog(LOG_LVL_DETAIL,".......**.....\n");
            break;
    }
//	OspSetHBParam();
//	OspNodeDiscCBReg();
}

/*********************************************************************
    InstanceEntry����
*********************************************************************/
void CServerInstance::InstanceEntry(CMessage *const pcMsg)
{
	u16 curEvent = pcMsg->event;
	u32 dwInsCout = 0;

	switch(curEvent)
	{
		/* ע������ */
	    case C_S_REGISTER_REQ:
			for( dwInsCout = 1; dwInsCout <= MAX_SERVER_INS_NUM; dwInsCout++)
			{	 
				//��ȡʵ������ָ��
				if (IDLE_STATE == CurState())
				{
					NextState(READY_STATE);
					post(pcMsg->srcid, S_C_REGISTER_ACK,NULL,0,pcMsg->srcnode);
					break;
				}
				
			}
			break;

		/* �����ļ����� */
		case C_S_FILENAME_REQ:
//			cout << pcMsg->content << endl;
			ProcCheckFile(pcMsg);
			NextState(TRANSFER_STATE);//�˴������⣬�û�������������������˲���ռ��instance�����ڼӵ�C_S_DOWNLOADDATA_REQ��
            break;

			 /* �����ļ��������� */
		case C_S_DOWNLOADDATA_REQ:
//			OspLog(LOG_LVL_DETAIL,"�ͻ����������������\n");
			if (TRANSFER_STATE == CurState())
			{
				memcpy(&m_cPackageInfo,pcMsg->content,pcMsg->length);
				//�ж�Ϊ�������ػ��Ƕϵ�����
				if (0 == m_cPackageInfo.getdownloadstate()) 
				{
//					OspLog(LOG_LVL_DETAIL,"������������\n");
					m_cFilemgr.FileRead(m_cPackageInfo.getsfilename(),m_cPackageInfo.getfilesize(),m_cPackageInfo.getpackageid(),m_cPackageInfo.getpackagesize(),m_cPackageInfo.getpackagecontent());
					post(pcMsg->srcid, S_C_DOWNLOADDATA_ACK, &m_cPackageInfo, sizeof(m_cPackageInfo), pcMsg->srcnode);
//					cout << m_cPackageInfo.getpackagecontent() <<endl;
					if (m_cPackageInfo.getfilesize()/TransferSize == m_cPackageInfo.getpackageid())
					{
						NextState(READY_STATE);
						OspLog(LOG_LVL_DETAIL,"�������ļ��������\n");
					}
				}
				else
				{
					//�ϵ�����
				}
			}
			else
			{
				OspLog(LOG_LVL_WARNING,"%d��instance״̬���ԣ���\n",GetInsID());
			}
			
			 break;

		default:
            OspLog(LOG_LVL_DETAIL,".......**.....\n");
            break;


	}
}