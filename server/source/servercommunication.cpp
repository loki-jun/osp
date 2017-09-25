/*==========================================================                        
文件名：servercommunication.cpp
相关文件：
实现功能：负责消息处理以及调用文件管理模块接口
作者：
版权：
------------------------------------------------------------
修改记录：
日  期	   	  版本		 修改人		  走读人      修改记录
  
===========================================================*/
#include <io.h>
#include <direct.h>
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
    初始化函数
*********************************************************************/
void UserInit()
{
	if( !( IsOspInitd( ) ) )
	{
		// 初始化Osp, 在端口2502启动Telnet
		BOOL32 bRetOspinit = OspInit( TRUE, SERVER_TELENT_PORT );         		
		if( !bRetOspinit )
		{	
			OspLog(LOG_LVL_ERROR,"***初始化osp失败***");
			return ;
		}
	}

	// 在6682端口上创建本地监听结点 
//	u32 dwRetCreateTcpNode = OspCreateTcpNode( inet_addr("127.0.0.1"), SERVER_LISTEN_PORT );   
	u32 dwRetCreateTcpNode = OspCreateTcpNode( 0, SERVER_LISTEN_PORT );	
	if( dwRetCreateTcpNode == INVALID_SOCKET )
	{
		OspLog(LOG_LVL_ERROR,"***创建监听节点失败***");
		return;
	}
	
	//创建APP	
	g_CServerApp.CreateApp( SERVER_APP_NAME, 
		SERVER_APP_NO,  
		SERVER_APP_PRIO, 
		SERVER_APP_QUE_SIZE);	
	
	OspLog(LOG_LVL_DETAIL,"***初始化成功***");
	return ;
}


/*********************************************************************
    DaemonDealClientConnect函数
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
    获取文件列表函数
*********************************************************************/
void CServerInstance::DaemonGetlist(CMessage *const pcMsg)
{
	
	u32 file;
	struct _finddata_t find;
	
	_chdir("e:\\测试文件夹");
	if((file = _findfirst("*.*",&find)) == -1L)
	{
		OspPrintf(TRUE,FALSE,"空文件夹！");
		exit(0);
	}
	OspPrintf(TRUE,FALSE,"%s\n",find.name);

	CFileInfo cFileInfo;
	u32 dwFileNum = 0;
	while(_findnext(file,&find) == 0)
	{
		cFileInfo.clear();
		cFileInfo.setnetfilesize(find.size);
		cFileInfo.setfilename(find.name);
		m_cFileListInfo.setfileinfo(&cFileInfo,dwFileNum);
//		OspPrintf(TRUE,FALSE,"filename:%s size:%d\n",cFileInfo.getfilename(),cFileInfo.getfilesize());
		dwFileNum++;
	}
	_findclose(file);
	m_cFileListInfo.setfilenum(dwFileNum);
	post(pcMsg->srcid,S_C_GETLIST_ACK, &m_cFileListInfo,sizeof(m_cFileListInfo),pcMsg->srcnode);
	m_cFileListInfo.printf();
	OspLog(LOG_LVL_DETAIL,"文件列表大小：%d\n",sizeof(m_cFileListInfo));
	/*
	vector<string> fileNames;
	vector<u32> fileSizes;
	vector<u8> filemd5s;
	
	fileNames = m_cFindFiles.findFiles( "E:\\测试文件夹" );
	fileSizes = m_cFindSizes.findSizes("E:\\测试文件夹");
	filemd5s = m_cFindMd5.findMd5("E:\\\\测试文件夹");  //md5值没有get到，貌似计算的是字符串，待查……

	m_cFileListInfo.setfilenum(fileNames.size());

	u16 wCount = 0;
	CFileInfo cFileInfo;//此处定义局部变量，不需要存储

	for ( wCount =0; wCount<fileNames.size(); wCount++)
	{      
		cFileInfo.clear();
		cFileInfo.setnetfilesize(fileSizes[wCount]);
		cFileInfo.setfilename(&fileNames[wCount][0u]);
		m_cFileListInfo.setfileinfo(&cFileInfo);
		OspPrintf(TRUE,FALSE,"[DaemonGetlist] 3 fileSizes[%d].%d m_dwFileSize.%d \n", 
			wCount, fileSizes[wCount],cFileInfo.getfilesize());

	}	

	m_cFileListInfo.printf();
	post(pcMsg->srcid,S_C_GETLIST_ACK, &m_cFileListInfo,sizeof(m_cFileListInfo),pcMsg->srcnode);
	OspLog(LOG_LVL_DETAIL,"文件列表大小：%d\n",sizeof(m_cFileListInfo));
	*/
}

/*********************************************************************
    文件校验函数
*********************************************************************/
void CServerInstance::ProcCheckFile(CMessage *const pcMsg)
{
	//获取文件夹中的文件个数
	u32 filenum;
	struct _finddata_t findnum;
	_chdir("e:\\测试文件夹");
	if((filenum = _findfirst("*.*",&findnum)) == -1L)
	{
		OspPrintf(TRUE,FALSE,"空文件夹！");
		exit(0);
	}
	u32 dwFileNum = 0;
	while(_findnext(filenum,&findnum) == 0)
	{
		dwFileNum++;
	}
	_findclose(filenum);


	u32 file;
	struct _finddata_t find;	
	_chdir("e:\\测试文件夹");
	if((file = _findfirst("*.*",&find)) == -1L)
	{
		OspPrintf(TRUE,FALSE,"空文件夹！");
		exit(0);
	}

	u16 wCount = 0;
	_chdir("e:\\测试文件夹");
	while(_findnext(file,&find) == 0)
	{

		s8 achFileName[STRING_LENGTH];
		s8 achServerFileName[STRING_LENGTH];
		memcpy(achFileName,pcMsg->content,pcMsg->length);
		memcpy(achServerFileName,find.name,sizeof(achServerFileName));
		
        m_cFileInfo.setnetfilesize(find.size);
		m_cFileInfo.setfilename(find.name);
		if (0 == strcmp(achServerFileName,achFileName))
		{
			post(pcMsg->srcid,S_C_FILENAME_ACK,&m_cFileInfo,sizeof(m_cFileInfo),pcMsg->srcnode);
			break;
		}
		wCount++;
	}
	if (wCount == dwFileNum)
	{
		post(pcMsg->srcid,S_C_FILENAME_NACK,NULL,0,pcMsg->srcnode);
	}
	_findclose(file);



/*
	vector<string> fileNames;
	vector<u32> fileSizes;

	fileNames = m_cFindFiles.findFiles( "E:\\测试文件夹" );
	fileSizes = m_cFindSizes.findSizes("E:\\测试文件夹");

	u16 wCount = 0;
	for ( wCount =0; wCount<fileNames.size(); wCount++ )
	{   
		s8 achFileName[STRING_LENGTH];
		s8 achServerFileName[STRING_LENGTH];
		memcpy(achFileName,pcMsg->content,pcMsg->length);
		memcpy(achServerFileName,&fileNames[wCount][0u],sizeof(achServerFileName));

        m_cFileInfo.setnetfilesize(fileSizes[wCount]);
		m_cFileInfo.setfilename(&fileNames[wCount][0u]);

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
*/
}


/*********************************************************************
    服务器发送消息函数
*********************************************************************/

/*
void CServerInstance::ProcSendMsg(CMessage *const pcMsg)
{
	memcpy(&m_cPackageInfo,pcMsg->content,pcMsg->length);
	//计算buffer中包的偏移量
	u32 dwShift = (m_cPackageInfo.m_wPackageId - (m_dwBufferNum-1)*PACKAGENUM_EACHBUFFER)*TransferSize;
	//判断是否是最后一包，不是最后一包则以TransferSize拷贝，是则以最后一包大小拷贝
	if ( m_cPackageInfo.m_dwFileSize/TransferSize != m_cPackageInfo.m_wPackageId)
	{

		memset(m_cPackageInfo.m_pbyPackageContent,0x00,sizeof(m_cPackageInfo.m_pbyPackageContent));
		memcpy(m_cPackageInfo.m_pbyPackageContent,m_cFilemgr.m_Buffer+dwShift,TransferSize);
		post(pcMsg->srcid, S_C_DOWNLOADDATA_ACK, &m_cPackageInfo, sizeof(m_cPackageInfo), pcMsg->srcnode);
	}
	else
	{
		OspLog(LOG_LVL_DETAIL,"服务器发送最后一包数据\n");
		memset(m_cPackageInfo.m_pbyPackageContent,0x00,sizeof(m_cPackageInfo.m_pbyPackageContent));
		memcpy(m_cPackageInfo.m_pbyPackageContent,m_cFilemgr.m_Buffer+dwShift,m_cPackageInfo.m_dwFileSize%TransferSize);
		OspLog(LOG_LVL_DETAIL,"包大小：%d\n",m_cPackageInfo.m_dwFileSize%TransferSize);
		post(pcMsg->srcid, S_C_DOWNLOADDATA_ACK, &m_cPackageInfo, sizeof(m_cPackageInfo), pcMsg->srcnode);
		m_cPackageInfo.printf();
		NextState(READY_STATE);
	}
}
*/


/*********************************************************************
    DaemonInstanceEntry函数
*********************************************************************/

void CServerInstance::DaemonInstanceEntry(CMessage *const pcMsg, CApp* pcApp)
{
    //u32 curState = CurState();
    u16 curEvent = pcMsg->event;
	u32 dwInsCout = 0;
	CServerInstance* pCInstance = NULL;

    switch(curEvent)
    {
        /* 连接请求 */
//        case CONNECT_TIME_EVENT:
        case C_S_CONNECT_REQ:
			g_CServerApp.m_dwNodeNum++;
//			OspLog(LOG_LVL_DETAIL,"连接请求进入daemon\n");
            DaemonDealClientConnect(pcMsg, pcApp);
            break;

		/* 获取文件列表请求 */
        case C_S_GETLIST_REQ:
			OspLog(LOG_LVL_DETAIL,"服务器测试文件列表生成\n");
            DaemonGetlist(pcMsg);
            break;

        default:
            OspLog(LOG_LVL_DETAIL,".......**.....\n");
            break;
    }
//	OspSetHBParam();
//	OspNodeDiscCBReg();
}

/*********************************************************************
    InstanceEntry函数
*********************************************************************/
void CServerInstance::InstanceEntry(CMessage *const pcMsg)
{
	u16 curEvent = pcMsg->event;
	u32 dwInsCout = 0;

	switch(curEvent)
	{
		/* 注册请求 */
	    case C_S_REGISTER_REQ:
			for( dwInsCout = 1; dwInsCout <= MAX_SERVER_INS_NUM; dwInsCout++)
			{	 
				//获取实例对象指针
				if (IDLE_STATE == CurState())
				{
					NextState(READY_STATE);
					post(pcMsg->srcid, S_C_REGISTER_ACK,NULL,0,pcMsg->srcnode);
					break;
				}
				
			}
			break;

		/* 下载文件请求 */
		case C_S_FILENAME_REQ:
//			cout << pcMsg->content << endl;
			ProcCheckFile(pcMsg);
			NextState(TRANSFER_STATE);//此处有问题，用户若不请求下载数据则此操作占用instance，后期加到C_S_DOWNLOADDATA_REQ中
            break;

			 /* 下载文件数据请求 */
		case C_S_DOWNLOADDATA_REQ:
//			OspLog(LOG_LVL_DETAIL,"客户端数据请求进来了\n");
			if (TRANSFER_STATE == CurState())
			{
				memcpy(&m_cPackageInfo,pcMsg->content,pcMsg->length);
				//判断为正常下载还是断点续传
				if (0 == m_cPackageInfo.getdownloadstate()) 
				{
//					OspLog(LOG_LVL_DETAIL,"正常下载请求\n");
					m_cFilemgr.FileRead(m_cPackageInfo.getsfilename(),m_cPackageInfo.getfilesize(),m_cPackageInfo.getpackageid(),m_cPackageInfo.getpackagesize(),m_cPackageInfo.getpackagecontent());
					post(pcMsg->srcid, S_C_DOWNLOADDATA_ACK, &m_cPackageInfo, sizeof(m_cPackageInfo), pcMsg->srcnode);
					OspLog(LOG_LVL_DETAIL,"服务器传输的包Id:%d\n",m_cPackageInfo.getpackageid());
					if (m_cPackageInfo.getfilesize()/TransferSize == m_cPackageInfo.getpackageid())
					{
						NextState(READY_STATE);
						OspLog(LOG_LVL_DETAIL,"服务器文件传输完毕\n");
					}
				}
				else
				{
					//断点续传
				}
			}
			else
			{
				OspLog(LOG_LVL_WARNING,"%d号instance状态不对！！\n",GetInsID());
			}
			
			 break;

			 /* 客户端取消文件下载请求  */
		case C_S_CANCELFILE_REQ:
			NextState(READY_STATE);
			post(pcMsg->srcid, S_C_CANCELFILE_ACK, &m_cPackageInfo, sizeof(m_cPackageInfo), pcMsg->srcnode);
			OspLog(LOG_LVL_DETAIL,"******客户端取消文件下载******\n");
			clear();
			m_cFilemgr.clear();
			m_cFileInfo.clear();
			m_cFileListInfo.clear();
			m_cPackageInfo.clear();
			break;


		default:
            OspLog(LOG_LVL_DETAIL,".......**.....\n");
            break;


	}
}