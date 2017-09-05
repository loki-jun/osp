/*==========================================================                       
文件名：csmsg.h
相关文件：
实现功能：定义客户端与服务器之间的消息
作者：
版权：
------------------------------------------------------------
修改记录：
日  期	   	  版本		 修改人		  走读人      修改记录
  
===========================================================*/

#ifndef _CSMSG_H_
#define _CSMSG_H_

/* 连接服务器 */
#define C_S_CONNECT_REQ              (u16)(OSP_USEREVENT_BASE+0x0001)
#define S_C_CONNECT_ACK              (u16)(OSP_USEREVENT_BASE+0x0002)
#define S_C_CONNECT_NACK             (u16)(OSP_USEREVENT_BASE+0x0003)

/* 请求注册 */
#define C_S_REGISTER_REQ             (u16)(OSP_USEREVENT_BASE+0x0004)
#define S_C_REGISTER_ACK             (u16)(OSP_USEREVENT_BASE+0x0005)
#define S_C_REGISTER_NACK            (u16)(OSP_USEREVENT_BASE+0x0006)

/* 获取文件列表 */
#define C_S_GETLIST_REQ              (u16)(OSP_USEREVENT_BASE+0x0007)
#define S_C_GETLIST_ACK              (u16)(OSP_USEREVENT_BASE+0x0008)
#define S_C_GETLIST_NACK             (u16)(OSP_USEREVENT_BASE+0x0009)

/* 文件下载 */
#define C_S_FILENAME_REQ             (u16)(OSP_USEREVENT_BASE+0x000A) /*下载文件请求*/
#define S_C_FILENAME_ACK             (u16)(OSP_USEREVENT_BASE+0x000B) /*文件存在确认*/
#define S_C_FILENAME_NACK            (u16)(OSP_USEREVENT_BASE+0x000C)

#define C_S_DOWNLOADDATA_REQ         (u16)(OSP_USEREVENT_BASE+0x000D) /*数据包下载请求*/
#define S_C_DOWNLOADDATA_ACK         (u16)(OSP_USEREVENT_BASE+0x000E) /*返回数据包的数据*/
#define S_C_DOWNLOADDATA_NACK        (u16)(OSP_USEREVENT_BASE+0x000F)

/* 取消文件下载 */
#define C_S_CANCELFILE_REQ           (u16)(OSP_USEREVENT_BASE+0x0010)
#define S_C_CANCELFILE_ACK           (u16)(OSP_USEREVENT_BASE+0x0011)
#define S_C_CANCELFILE_NACK          (u16)(OSP_USEREVENT_BASE+0x0012)

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