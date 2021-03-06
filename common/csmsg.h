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
#define C_S_FILENAME_REQ             (u16)(OSP_USEREVENT_BASE+0x000A)
#define S_C_FILENAME_ACK             (u16)(OSP_USEREVENT_BASE+0x000B)
#define S_C_FILENAME_NACK            (u16)(OSP_USEREVENT_BASE+0x000C)

#define C_S_DOWNLOADDATA_REQ         (u16)(OSP_USEREVENT_BASE+0x000D)
#define S_C_DOWNLOADDATA_ACK         (u16)(OSP_USEREVENT_BASE+0x000E)
#define S_C_DOWNLOADDATA_NACK        (u16)(OSP_USEREVENT_BASE+0x000F)

/* 取消文件下载 */
#define C_S_CANCELFILE_REQ           (u16)(OSP_USEREVENT_BASE+0x0010)
#define S_C_CANCELFILE_ACK           (u16)(OSP_USEREVENT_BASE+0x0011)
#define S_C_CANCELFILE_NACK          (u16)(OSP_USEREVENT_BASE+0x0012)

#endif