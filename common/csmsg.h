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

class CFileInfo
{
public:
	s8 m_pbyFileName[260];
	u32 m_dwFileSize;
	u32 m_dwMD5Value[32];
	
public:
    CFileInfo()
    {
        m_dwFileSize = 0;
		memset(m_dwMD5Value,0,32);
		memset(m_pbyFileName,0,260);
    }
    ~CFileInfo()
    {
    }
};

class CFileListInfo
{
public:
	u16 m_wFileNum;
	CFileInfo *m_pbyFileInfo[500];

public:
    CFileListInfo()
    {
        m_wFileNum = 0;
		memset(m_pbyFileInfo,0,500);
    }
    ~CFileListInfo()
    {
    }
};



#endif