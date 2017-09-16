/*==========================================================                       
�ļ�����csmsg.h
����ļ���
ʵ�ֹ��ܣ�����ͻ����������֮�����Ϣ�Լ������ඨ��
���ߣ�
��Ȩ��
------------------------------------------------------------
�޸ļ�¼��
��  ��	   	  �汾		 �޸���		  �߶���      �޸ļ�¼
  
===========================================================*/

#ifndef _CSMSG_H_
#define _CSMSG_H_

#include "../../common/macrodef.h"

/* ���ӷ����� */
#define C_S_CONNECT_REQ              (u16)(OSP_USEREVENT_BASE+0x0001) //�ͻ�����������client(daemon)->server(daemon)
#define S_C_CONNECT_ACK              (u16)(OSP_USEREVENT_BASE+0x0002) //��������Ӧ��������server(daemon)->client(daemon)
#define S_C_CONNECT_NACK             (u16)(OSP_USEREVENT_BASE+0x0003) //�������ܽӿͻ�����������server(daemon)->client(daemon)

/* ����ע�� */
#define C_S_REGISTER_REQ             (u16)(OSP_USEREVENT_BASE+0x0004) //�ͻ���instanceע������client(instance)->server(instance)
#define S_C_REGISTER_ACK             (u16)(OSP_USEREVENT_BASE+0x0005) //��������Ӧ�ͻ���ע������server(instance)->client(instance)
#define S_C_REGISTER_NACK            (u16)(OSP_USEREVENT_BASE+0x0006) //�������ܾ��ͻ���ע������server(instance)->client(instance)

/* ��ȡ�ļ��б� */
#define C_S_GETLIST_REQ              (u16)(OSP_USEREVENT_BASE+0x0007) //�ͻ��˻�ȡ�ļ��б�����client(daemon)->server(daemon)
#define S_C_GETLIST_ACK              (u16)(OSP_USEREVENT_BASE+0x0008) //��������Ӧ�ͻ����ļ��б�����server(daemon)->client(daemon)����Ϣ��ΪCFileListInfo
#define S_C_GETLIST_NACK             (u16)(OSP_USEREVENT_BASE+0x0009) //�������ܾ��ͻ��˻�ȡ�ļ��б�server(daemon)->client(daemon)

/* �ļ����� */
#define C_S_FILENAME_REQ             (u16)(OSP_USEREVENT_BASE+0x000A) //�ͻ����ļ���������client(instance)->server(instance)����Ϣ��Ϊs8(pbyFilename[256])
#define S_C_FILENAME_ACK             (u16)(OSP_USEREVENT_BASE+0x000B) //��������Ӧ�ͻ����ļ���������server(instance)->client(instance)����Ϣ��ΪCFileInfo
#define S_C_FILENAME_NACK            (u16)(OSP_USEREVENT_BASE+0x000C) //�������ܾ��ͻ����ļ���������server(instance)->client(instance)

#define C_S_DOWNLOADDATA_REQ         (u16)(OSP_USEREVENT_BASE+0x000D) //�ͻ������ݰ���������client(instance)->server(instance)����Ϣ��ΪCPackageInfo
#define S_C_DOWNLOADDATA_ACK         (u16)(OSP_USEREVENT_BASE+0x000E) //�������������ݰ������ݸ��ͻ��ˣ�server(instance)->client(instance)����Ϣ��ΪCPackageInfo
#define S_C_DOWNLOADDATA_NACK        (u16)(OSP_USEREVENT_BASE+0x000F) //�������ܾ����ݰ����䣬server(instance)->client(instance)

/* ȡ���ļ����� */
#define C_S_CANCELFILE_REQ           (u16)(OSP_USEREVENT_BASE+0x0010) //�ͻ���ȡ���ļ���������client(instance)->server(instance)����Ϣ��Ϊs8(pbyFilename[256])
#define S_C_CANCELFILE_ACK           (u16)(OSP_USEREVENT_BASE+0x0011) //��������Ӧ�ͻ���ȡ���ļ����أ�server(instance)->client(instance)
#define S_C_CANCELFILE_NACK          (u16)(OSP_USEREVENT_BASE+0x0012) //�������ܾ�ȡ����������server(instance)->client(instance)

//#define OSP_DISCONNECT               (u16)(OSP_USEREVENT_BASE+0x001F) //������ʾ


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
		OspPrintf(TRUE,FALSE,"size:%d,filename:%s,Md5:%s\n",
			m_dwFileSize,m_pbyFileName,m_dwMD5Value);
	}

	s8 getfilename()
	{
		return ntohl(m_pbyFileName);
	}
	void setfilename(s8* filename)
	{
		m_pbyFileName = htonl(filename);
	}

	u32 getfilesize()
	{
		return ntohl(m_pbyFileName);
	}
	void setfilesize(u32 filesize)
	{
		m_pbyFileName = htonl(filesize);
	}

	u8 getfilemd5()
	{
		return ntohl(m_dwMD5Value);
	}
	void setfilemd5(u8 filemd5)
	{
		memcpy(m_dwMD5Value,htonl(filemd5),sizeof(m_dwMD5Value));
	}
};

class CFileListInfo
{
private:
	u16 m_wFileNum;
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

	//�ļ��б��е��ļ�����
	u16 getfilenum()
	{
		return ntohl(m_wFileNum);
	}
	void setfilenum(u16 filenum)
	{
		m_wFileNum = htonl(filenum);
	}

	//�ļ��б���Ϣ
	CFileInfo getfileinfo()
	{
		return ntohl(m_pbyFileInfo);
	}
	void setfileinfo(CFileInfo fileinfo)
	{
		memcpy(m_pbyFileInfo,htonl(fileinfo),sizeof(m_pbyFileInfo));
	}

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
	u16 m_wDownloadState;

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

	//�ͻ����ļ���
	s8 getcfilename()
	{
		return ntohl(m_pbyCFileName);
	}
	void setfilename(s8* cfilename)
	{
		memcpy(m_pbyCFileName,htonl(cfilename),sizeof(m_pbyCFileName));
	}

	//�������ļ���
	s8 getsfilename()
	{
		return ntohl(m_pbySFileName);
	}
	void setfilename(s8* sfilename)
	{
		memcpy(m_pbySFileName,htonl(sfilename),sizeof(m_pbySFileName));
	}

	//�ļ���С
	u32 getfilesize()
	{
		return ntohl(m_dwFileSize);
	}
	void setfilesize(u32 filesize)
	{
		m_dwFileSize = htonl(filesize);
	}

	//��id
	u16 getpackageid()
	{
		return ntohl(m_wPackageId);
	}
	void setpackageid(u16 packageid)
	{
		m_wPackageId = htonl(packageid);
	}

	//����С
	u16 getpackagesize()
	{
		return ntohl(m_wPackageSize);
	}
	void setpackagesize(u16 packagesize)
	{
		m_wPackageSize = htonl(packagesize);
	}

	//������
	s8 getpackagecontent()
	{
		return ntohl(m_pbyPackageContent);
	}
	void setpackagecontent(m_pbyPackageContent)
	{
		memcpy(m_pbyPackageContent,htonl(m_pbyPackageContent),sizeof(m_pbyPackageContent));
	}
	
};


#endif