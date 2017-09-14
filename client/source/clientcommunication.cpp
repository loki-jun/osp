 /*==========================================================                        
�ļ�����clientcommunication.cpp
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
#include "../include/clientcommon.h"
#include "../include/clientcommunication.h"
#include "../include/clientinterface.h"
#include "../include/clientfilemanager.h"

using namespace std;

CClientApp g_CClientApp;

//CConfigData g_CConfigData;
CFileManager g_CFileManager;
//CBuffer g_CBuffer;
/*********************************************************************
    ��ʼ������
*********************************************************************/
void UserInit()
{

	if( !( IsOspInitd( ) ) )
	{
		// ��ʼ��Osp, �ڶ˿�2501����Telnet
		BOOL32 bRetOspinit = OspInit( TRUE, CLIENT_TELENT_PORT );         		
		if( !bRetOspinit )
		{	
			OspLog(LOG_LVL_ERROR,"***��ʼ��ospʧ��***");
			return ;
		}
	}
	
	//����APP	
	g_CClientApp.CreateApp( CLIENT_APP_NAME, 
		CLIENT_APP_NO,  
		CLIENT_APP_PRIO, 
		CLIENT_APP_QUE_SIZE);	
	
	
	OspLog(LOG_LVL_DETAIL,"***��ʼ���ɹ�***");

	return ;
}


/*********************************************************************
    DaemonConnectServer����
*********************************************************************/
void CClientInstance::DaemonConnectServer()
{	
    s32 dwRet = 0;
	dwRet = OspConnectTcpNode(g_CClientApp.m_dwIp,SERVER_LISTEN_PORT,TIME_WATING,NUM_WATING);
	if(dwRet != INVALID_NODE)
	{
	    OspLog(LOG_LVL_DETAIL,"�ɹ���ȡ������node\n");
		m_dwDstNode = dwRet;
		post(MAKEIID(SERVER_APP_NO, DAEMON), C_S_CONNECT_REQ,NULL,0,m_dwDstNode);
		OspSetHBParam(m_dwDstNode,NODE_TIME_WATING,NUM_WATING);
//		OspNodeDiscCBRegQ(g_CClientApp.m_dwDstNode,CLIENT_APP_NO,DAEMON);
	}
	else
	{
		OspLog(LOG_LVL_WARNING,"���ӳ�ʱ��\n");
//		SetTimer(CONNECT_TIME_EVENT, TIME_WATING);
	}
}

/*********************************************************************
    DaemonDisConnectServer����
*********************************************************************/
void CClientInstance::DaemonDisConnectServer()
{
	
}


/*********************************************************************
    �ͻ��˽��շ��������ݺ���
*********************************************************************/
void CClientInstance::ProcClientRecData(CMessage *const pcMsg,u32 dwBufferNum,u16 wIdCount)
{
	memcpy(&m_cPackageInfo,pcMsg->content,pcMsg->length);
	//����buffer�а���ƫ����
	u32 dwShift = m_cPackageInfo.m_wPackageId - (dwBufferNum-1)*PACKAGENUM_EACHBUFFER;

	memcpy(g_CFileManager.m_cBuffer[wIdCount].m_dwBuffer+dwShift,m_cPackageInfo.m_pbyPackageContent,TransferSize);
	OspLog(LOG_LVL_DETAIL,"����С��%d\n",sizeof(g_CFileManager.m_cBuffer[wIdCount].m_dwBuffer));

}

/*********************************************************************
    DaemonInstanceEntry����
*********************************************************************/

void CClientInstance::DaemonInstanceEntry(CMessage *const pcMsg, CApp* pcApp)
{
    u32 curState = CurState();
    u16 curEvent = pcMsg->event;
	CClientInstance* pCInstance = NULL;
	u32 dwInsCout = 0;

    switch(pcMsg->event)
    {
//        case OSP_DISCONNECT:
//			OspLog(LOG_LVL_WARNING,"�������Ѷ����������С���\n");
//			NextState(IDLE_STATE);
//			break;

		/* ���ӷ����� */
        case U_C_CONNECT_CMD:
			if (IDLE_STATE == CurState())
			{
				s8 achIp[20];
				memcpy(achIp,pcMsg->content,pcMsg->length);
				g_CClientApp.m_dwIp = inet_addr(achIp);
                DaemonConnectServer();
			}
			else
			{
				OspLog(LOG_LVL_WARNING,"������������У������ظ���������Ҫ���������ȶϿ���\n");
			}
            break;
        /* �Ͽ����� */
        case U_C_DISCONNECT_CMD:
			if (CONNECT_STATE == CurState())
			{
				for( dwInsCout = 1; dwInsCout <= MAX_CLIENT_INS_NUM; dwInsCout++)
				{	 
					//��ȡʵ������ָ��
					pCInstance = (CClientInstance*)pcApp->GetInstance(dwInsCout);
					pCInstance->NextState(IDLE_STATE);
				}  
				OspDisconnectTcpNode(m_dwDstNode);
				NextState(IDLE_STATE);
				OspLog(LOG_LVL_WARNING,"�������ѶϿ���\n");
			}
			else
			{
				OspLog(LOG_LVL_WARNING,"δ���ӣ��������ӷ�������\n");
			}
            break;
		/* ��ȡ�ļ��б� */
        case U_C_GETLIST_CMD:
			if (CONNECT_STATE == CurState())
			{
				post(MAKEIID(SERVER_APP_NO, DAEMON), C_S_GETLIST_REQ,NULL,0,m_dwDstNode);
			}
			else
			{ 
				OspLog(LOG_LVL_WARNING,"δ���ӣ��������ӷ�������\n");
			}
            break;

         /* �����ļ� */
         case U_C_DOWNLOADFILE_CMD:
			 if (CONNECT_STATE == CurState())   //�ж�daemon״̬
			 {
				 for( dwInsCout = 1; dwInsCout <= MAX_CLIENT_INS_NUM; dwInsCout++)
				 {	 
					 //��ȡʵ������ָ��
					 pCInstance = (CClientInstance*)pcApp->GetInstance(dwInsCout);
					 if (READY_STATE == pCInstance->CurState())
					 {
						 pCInstance->NextState(TRANSFER_STATE);   //daemon��instance״̬Ϊ����̬
						 post(MAKEIID(CLIENT_APP_NO, dwInsCout), C_C_DOWNLOADFILE_CMD,pcMsg->content,pcMsg->length);
//						 cout << pcMsg->content << endl;
						 break;
					 }										 
				 }
				 if (dwInsCout > MAX_CLIENT_INS_NUM)
				 {
					 OspLog(LOG_LVL_WARNING,"���޿���instance���ã�");
				 }
			 }
			 else
			 {
				 OspLog(LOG_LVL_WARNING,"δ���ӣ��������ӷ�������\n");
			 }
            
             break;
         /* ��ͣ���� */
         case U_C_PAUSETASK_CMD:
           
            break;
		/* �ָ����� */
         case U_C_RESUMETASK_CMD:
			 
            break;
		/* ȡ������ */
         case U_C_CANCELTASK_CMD:
			 
            break;
		/* ���ضϵ������ļ� */
         case U_C_DOWNLOADPARTFILE_CMD:
			 
            break;
		/* ȡ���ϵ������ļ� */
         case U_C_CANCELPARTFILE_CMD:
			 
            break;
			
		/* ����������ȷ�� */
		 case S_C_CONNECT_ACK:
			 OspLog(LOG_LVL_DETAIL,"���������ӳɹ�\n");
			 NextState(CONNECT_STATE);
			 OspLog(LOG_LVL_DETAIL,"daemon״̬��%u\n",CurState());

			 for( dwInsCout = 1; dwInsCout <= MAX_CLIENT_INS_NUM; dwInsCout++)
			 {	 
				 //��ȡʵ������ָ��
				 pCInstance = (CClientInstance*)pcApp->GetInstance(dwInsCout);
				 pCInstance->NextState(IDLE_STATE);
				 OspPost(MAKEIID(CLIENT_APP_NO, dwInsCout), C_C_CONNECTSUCCESS_CMD,(u32 *)&m_dwDstNode,sizeof(m_dwDstNode));
			 }
			 break;

		/* �������ļ��б��� */
        case S_C_GETLIST_ACK:
			OspPrintf(TRUE,FALSE,"�����ļ��б�ͻ��˽���\n");
			memcpy(&m_cFileListInfo,pcMsg->content,pcMsg->length);
			m_cFileListInfo.printf();
			break;

        default:
            OspLog(LOG_LVL_DETAIL,".......**.....\n");
            break;
    }

}

/*********************************************************************
    InstanceEntry����
*********************************************************************/

void CClientInstance::InstanceEntry(CMessage *const pcMsg)
{
	u16 curEvent = pcMsg->event;
	switch(curEvent)
	{
		/* ���������ӳɹ�������ע��instance */
	    case C_C_CONNECTSUCCESS_CMD:
            memcpy(&m_dwDstNode, pcMsg->content,pcMsg->length);
			post(MAKEIID(SERVER_APP_NO, PENDING), C_S_REGISTER_REQ,NULL,0,m_dwDstNode);
			break;

		/* ������ע��ɹ����� */
		case S_C_REGISTER_ACK:
			m_dwDstId = pcMsg->srcid;
			NextState(READY_STATE);
			break;

		/* daemon��instance��������ָ�� */
		case C_C_DOWNLOADFILE_CMD:
			post(m_dwDstId, C_S_FILENAME_REQ,pcMsg->content,pcMsg->length,m_dwDstNode);
			break;

		/* �����������ļ�������Ӧ */
		case S_C_FILENAME_ACK:
			memcpy(&m_cFileInfo,pcMsg->content,pcMsg->length);
			OspLog(LOG_LVL_DETAIL,"�������ļ����ڣ����Ĵ󵨵����ذɣ�ɧ�꣡��\n");
//			cout << FileInfo.m_pbyFileName << endl;
			g_CFileManager.CreateSpace(m_cFileInfo.m_pbyFileName,m_cFileInfo.m_dwFileSize);
			if ( TRANSFER_STATE == CurState() )
			{
				m_cPackageInfo.m_wDownloadState = 0;
				//���ص��ļ����������ļ��е��ļ�ȥ�Աȣ����ļ��������У���m_cPackageInfo.m_wDownloadState��Ϊ1����֮Ϊ0
				//������������ļ�������
				if (0 == m_cPackageInfo.m_wDownloadState) 
				{
					u32 idcount = 0;
					u32 MaxId = m_cFileInfo.m_dwFileSize/TransferSize;
					OspLog(LOG_LVL_DETAIL,"��������ĿΪ��%u\n",MaxId+1);

					memcpy(m_cPackageInfo.m_pbySFileName,m_cFileInfo.m_pbyFileName,sizeof(m_cPackageInfo.m_pbySFileName));
					m_cPackageInfo.m_dwFileSize = m_cFileInfo.m_dwFileSize;
					m_cPackageInfo.m_wPackageId = idcount;//��Ϊ�ϵ���������ֵΪ�����ж�ȡ��IDֵ
//					post(m_dwDstId, C_S_DOWNLOADDATA_REQ,&m_cPackageInfo,sizeof(m_cPackageInfo),m_dwDstNode);
					post(pcMsg->srcid, C_S_DOWNLOADDATA_REQ,&m_cPackageInfo,sizeof(m_cPackageInfo),pcMsg->srcnode);
				}
				else
				{
					OspLog(LOG_LVL_DETAIL,"1�ϵ��������ܴ���������\n");
				}
			}
				
			break;

		/* �����������ļ������� */
		case S_C_DOWNLOADDATA_ACK:
			OspLog(LOG_LVL_DETAIL,"�ͻ����յ���һ������\n");
			m_cPackageInfo.printf();
			memcpy(&m_cPackageInfo,pcMsg->content,pcMsg->length);
			//�ж����������ػ��Ƕϵ�����
			if (0 == m_cPackageInfo.m_wDownloadState)
			{
				u16 wIdCount;
				//��instance��buffer��
				wIdCount = GetInsID()-1;
				u32 MaxId = m_cFileInfo.m_dwFileSize/TransferSize;
				//�ж����ݰ��Ƿ���
				if (m_cPackageInfo.m_wPackageId <= MaxId)
				{
					u32 dwBufferNum = g_CFileManager.m_cBuffer[wIdCount].m_dwBufferNum;
					//�жϰ�id�Ƿ��ڵ�ǰ�Ļ�����������д���棬������ǰһ������д���ļ��У���д��һ������
					if (m_cPackageInfo.m_wPackageId >= (dwBufferNum-1)*PACKAGENUM_EACHBUFFER && 
						m_cPackageInfo.m_wPackageId < dwBufferNum*PACKAGENUM_EACHBUFFER)
					{
						ProcClientRecData(pcMsg,dwBufferNum,wIdCount);
						//������Ŀ��1
						m_cPackageInfo.m_wPackageId++;
						//������д��ֹͣ��������������
						if (m_cPackageInfo.m_wPackageId <= MaxId)
						{
							post(pcMsg->srcid, C_S_DOWNLOADDATA_REQ,&m_cPackageInfo,sizeof(m_cPackageInfo),pcMsg->srcnode);
						}						
					}
				    else
					{
						g_CFileManager.FileWrite(m_cPackageInfo.m_pbySFileName,wIdCount,MaxId,m_cPackageInfo.m_wPackageId);
						g_CFileManager.m_cBuffer[wIdCount].m_dwBufferNum++;
						//dwBufferNum = g_CFileManager.m_cBuffer[wIdCount].m_dwBufferNum;
						ProcClientRecData(pcMsg,dwBufferNum,wIdCount);	
								
						m_cPackageInfo.m_wPackageId++;
						if (m_cPackageInfo.m_wPackageId <= MaxId)
						{
							post(pcMsg->srcid, C_S_DOWNLOADDATA_REQ,&m_cPackageInfo,sizeof(m_cPackageInfo),pcMsg->srcnode);
						}
					}
				}
				else
				{
					//post(C_U_DOWNLOAD_NOTIFY);
					NextState(READY_STATE);
				}
			}
			else
			{
				OspLog(LOG_LVL_DETAIL,"2�ϵ��������ܴ���������\n");
			}
			
			break;



		/* �����������ļ���������Ӧ */
		case S_C_FILENAME_NACK:
			OspLog(LOG_LVL_WARNING,"ɧ�꣬�ļ������������ˣ�����ѡһ���ɣ�\n");
			break;

		default:
            OspLog(LOG_LVL_DETAIL,".......**.....\n");
            break;
	}
}
