/*==========================================================                       
文件名：csmsg.h
相关文件：
实现功能：定义客户端与服务器之间的消息以及公共类定义
作者：
版权：
------------------------------------------------------------
修改记录：
日  期	   	  版本		 修改人		  走读人      修改记录
  
===========================================================*/

#ifndef _CSMSG_H_
#define _CSMSG_H_

#include "../../common/macrodef.h"

/* 连接服务器 */
#define C_S_CONNECT_REQ              (u16)(OSP_USEREVENT_BASE+0x0001) //客户端连接请求，client(daemon)->server(daemon)
#define S_C_CONNECT_ACK              (u16)(OSP_USEREVENT_BASE+0x0002) //服务器响应连接请求，server(daemon)->client(daemon)
#define S_C_CONNECT_NACK             (u16)(OSP_USEREVENT_BASE+0x0003) //服务器拒接客户端连接请求，server(daemon)->client(daemon)

/* 请求注册 */
#define C_S_REGISTER_REQ             (u16)(OSP_USEREVENT_BASE+0x0004) //客户端instance注册请求，client(instance)->server(instance)
#define S_C_REGISTER_ACK             (u16)(OSP_USEREVENT_BASE+0x0005) //服务器响应客户端注册请求，server(instance)->client(instance)
#define S_C_REGISTER_NACK            (u16)(OSP_USEREVENT_BASE+0x0006) //服务器拒绝客户端注册请求，server(instance)->client(instance)

/* 获取文件列表 */
#define C_S_GETLIST_REQ              (u16)(OSP_USEREVENT_BASE+0x0007) //客户端获取文件列表请求，client(daemon)->server(daemon)
#define S_C_GETLIST_ACK              (u16)(OSP_USEREVENT_BASE+0x0008) //服务器响应客户端文件列表请求，server(daemon)->client(daemon)，消息体为CFileListInfo
#define S_C_GETLIST_NACK             (u16)(OSP_USEREVENT_BASE+0x0009) //服务器拒绝客户端获取文件列表，server(daemon)->client(daemon)

/* 文件下载 */
#define C_S_FILENAME_REQ             (u16)(OSP_USEREVENT_BASE+0x000A) //客户端文件下载请求，client(instance)->server(instance)，消息体为s8(pbyFilename[256])
#define S_C_FILENAME_ACK             (u16)(OSP_USEREVENT_BASE+0x000B) //服务器响应客户端文件下载请求，server(instance)->client(instance)，消息体为CFileInfo
#define S_C_FILENAME_NACK            (u16)(OSP_USEREVENT_BASE+0x000C) //服务器拒绝客户端文件下载请求，server(instance)->client(instance)

#define C_S_DOWNLOADDATA_REQ         (u16)(OSP_USEREVENT_BASE+0x000D) //客户端数据包下载请求，client(instance)->server(instance)，消息体为CPackageInfo
#define S_C_DOWNLOADDATA_ACK         (u16)(OSP_USEREVENT_BASE+0x000E) //服务器返回数据包的数据给客户端，server(instance)->client(instance)，消息体为CPackageInfo
#define S_C_DOWNLOADDATA_NACK        (u16)(OSP_USEREVENT_BASE+0x000F) //服务器拒绝数据包传输，server(instance)->client(instance)

/* 取消文件下载 */
#define C_S_CANCELFILE_REQ           (u16)(OSP_USEREVENT_BASE+0x0010) //客户端取消文件下载请求，client(instance)->server(instance)，消息体为s8(pbyFilename[256])
#define S_C_CANCELFILE_ACK           (u16)(OSP_USEREVENT_BASE+0x0011) //服务器响应客户端取消文件下载，server(instance)->client(instance)
#define S_C_CANCELFILE_NACK          (u16)(OSP_USEREVENT_BASE+0x0012) //服务器拒绝取消下载请求，server(instance)->client(instance)

//#define OSP_DISCONNECT               (u16)(OSP_USEREVENT_BASE+0x001F) //断链提示


class CFileInfo
{
private:
	s8 m_pbyFileName[STRING_LENGTH];
	u32 m_dwFileSize;
	u8 m_dwMD5Value[32];

public:
    CFileInfo()
    {
        clear();
    }
    ~CFileInfo()
    {
    }
	void clear()
	{
        m_dwFileSize = 0;
		memset(m_dwMD5Value,0,32);
		memset(m_pbyFileName,0,STRING_LENGTH);
	}
	void printf()
	{
		OspPrintf(TRUE,FALSE,"size:%d,filename:%s\n",
			getfilesize(),m_pbyFileName);//,Md5:%s
	}

	s8* getfilename()
	{
		return m_pbyFileName;
	}
	void setfilename(s8* filename)
	{
		memcpy(m_pbyFileName,filename,sizeof(m_pbyFileName));
//		return m_pbyFileName[STRING_LENGTH];
	}

	u32 getfilesize()
	{
		return ntohl(m_dwFileSize);
	}
	void setnetfilesize(u32 hostfilesize)
	{
		m_dwFileSize = htonl(hostfilesize);
	}
	void setfilesize(u32 filesize)
	{
		m_dwFileSize = filesize;
	}


	void setfilemd5(u8* md5)
	{
		memcpy(m_dwMD5Value,md5,sizeof(m_dwMD5Value));
	}

};

class CFileListInfo
{
private:
	u8 m_wFileNum;
	CFileInfo m_pbyFileInfo[MAX_FILELIST_NUM];	

public:
	CFileListInfo()
    {
        clear();
    }
    ~CFileListInfo()
    {
    }
	void clear()
	{
        m_wFileNum = 0;
		memset(m_pbyFileInfo,0,sizeof(m_pbyFileInfo));
	}
	void printf()
	{
		for (u16 i=0;i<m_wFileNum;i++)
		{
			OspPrintf(TRUE,FALSE,"file[%d]:",i);
			m_pbyFileInfo[i].printf();	
		}
	}

	//文件列表中的文件个数
	u8 getfilenum()
	{
		return m_wFileNum;
	}
	void setfilenum(u8 filenum)
	{
		m_wFileNum = filenum;
	}

	//文件列表信息
	CFileInfo* getfileinfo()
	{
		return m_pbyFileInfo;
	}


	void setfileinfo(CFileInfo* fileinfo,u32 fileid)
	{
		memcpy(&m_pbyFileInfo[fileid],fileinfo,sizeof(m_pbyFileInfo[fileid]));
	}


	//文件列表信息
/*
	CFileInfo getfileinfo()
	{
		return m_pbyFileInfo;
	}
	void setfileinfo(CFileInfo fileinfo)
	{
		memcpy(m_pbyFileInfo,fileinfo,sizeof(m_pbyFileInfo));
	}
*/
};

class CPackageInfo
{
private:
	s8 m_pbyCFileName[STRING_LENGTH];
	s8 m_pbySFileName[STRING_LENGTH];
	u32 m_dwFileSize;
	u16 m_wPackageId;
	u16 m_wPackageSize;
	s8 m_pbyPackageContent[TransferSize];
	u8 m_wDownloadState;

public:
	CPackageInfo()
    {
        clear();
    }
    ~CPackageInfo()
    {
    }
	void clear()
	{
        m_dwFileSize = 0;
		m_wPackageId = 0;
		m_wPackageSize = 0;
		m_wDownloadState = 0;
		memset(m_pbyPackageContent,0,sizeof(m_pbyPackageContent));
		memset(m_pbyCFileName,0,sizeof(m_pbyCFileName));
		memset(m_pbySFileName,0,sizeof(m_pbySFileName));
	}
	void printf()
	{
		OspPrintf(TRUE,FALSE,"SFileName:%s\n,PackageId:%d\n,FileSize:%d\n,PackageContent:%s\n,DownloadState:%d\n",
			m_pbySFileName,m_wPackageId,m_dwFileSize,m_pbyPackageContent,m_wDownloadState);
	}	

	//客户端文件名
	s8* getcfilename()
	{
		return m_pbyCFileName;
	}
	void setcfilename(s8* cfilename)
	{
		memcpy(m_pbyCFileName,cfilename,sizeof(m_pbyCFileName));
	}

	//服务器文件名
	s8* getsfilename()
	{
		return m_pbySFileName;
	}
	void setsfilename(s8* sfilename)
	{
		memcpy(m_pbySFileName,sfilename,sizeof(m_pbySFileName));
	}

	//文件大小
	u32 getfilesize()
	{
		return ntohl(m_dwFileSize);
	}
	void setnetfilesize(u32 hostfilesize)
	{
		m_dwFileSize = htonl(hostfilesize);
	}
	void setfilesize(u32 filesize)
	{
		m_dwFileSize = filesize;
	}	

	//包id
	u16 getpackageid()
	{
		return ntohs(m_wPackageId);
	}
	void setnetpackageid(u16 hostpackageid)
	{
		m_wPackageId = htons(hostpackageid);
	}
	void setpackageid(u16 packageid)
	{
		m_wPackageId = packageid;
	}
	//包大小
	u16 getpackagesize()
	{
		return ntohs(m_wPackageSize);
	}
	void setnetpackagesize(u16 hostpackagesize)
	{
		m_wPackageSize = htons(hostpackagesize);
	}
	void setpackagesize(u16 packagesize)
	{
		m_wPackageSize= packagesize;
	}

	//包内容
	s8* getpackagecontent()
	{
		return m_pbyPackageContent;
	}
	void setpackagecontent(s8* packagecontent)
	{
		memcpy(m_pbyPackageContent,packagecontent,sizeof(m_pbyPackageContent));
	}


	//下载状态
	u8 getdownloadstate()
	{
		return m_wDownloadState;
	}

	void setdownloadstate(u8 downloadstate)
	{
		m_wDownloadState = downloadstate;
	}

	
};


#endif