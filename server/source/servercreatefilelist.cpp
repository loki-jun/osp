/*==========================================================                        
文件名：servercreatefilelist.cpp
相关文件：
实现功能：生成文件列表
作者：
版权：
------------------------------------------------------------
修改记录：
日  期	   	  版本		 修改人		  走读人      修改记录
  
===========================================================*/
#include <iostream>
#include <fstream>
#include <stdlib.h>  
#include <stdio.h> 
#include "../include/md5.h"
#include "../include/servercommon.h"
#include "../include/servercreatefilelist.h"

using namespace std;


//MD5 md5;
//extern CFileInfo FileInfo;
//extern CFileListInfo FileListInfo;
/*********************************************************************
    Windows平台获取文件列表
*********************************************************************/
#ifdef WIN32

#include <Windows.h>
#include <direct.h>


/*********************************************************************
    返回文件名
*********************************************************************/
vector<string> CFindFiles::findFiles( LPCSTR lpstrPath, LPCSTR lpstrName /*= ".*" */ )
{
    s8 achFind[MAX_PATH];//MAX_PATH
    s8 achFile[MAX_PATH];

    WIN32_FIND_DATA FindFileData;

    strcpy(achFind,lpstrPath);
    strcat(achFind,"\\*");
    strcat(achFind,lpstrName);

    HANDLE hFind=::FindFirstFile(achFind,&FindFileData);

    if(INVALID_HANDLE_VALUE == hFind)
    {
		OspLog(LOG_LVL_WARNING,"Empty folder!");
        return vector<string>();
    }

    do
    {
        if(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
        {
            if(FindFileData.cFileName[0]!='.')
            {
                strcpy(achFile,lpstrPath);
                strcat(achFile,"\\");
                strcat(achFile,FindFileData.cFileName);
                findFiles(achFile);
				
            }
        }
        else
        {
            if ( achFile[0] )
            {
                string filePath= lpstrPath;//变量类型有待修改……
                filePath += "\\";
                filePath += FindFileData.cFileName;
				file_lists.push_back(filePath);
				u32 file_size = (FindFileData.nFileSizeHigh * (MAXDWORD+1.0)) + FindFileData.nFileSizeLow;
				file_names.push_back(FindFileData.cFileName);

//				cout << FindFileData.cFileName <<endl;
//				OspPrintf(TRUE,FALSE,"%s  文件大小：%u\n",FindFileData.cFileName,file_size);
//		        memcpy(FileInfo.m_pbyFileName,FindFileData.cFileName,sizeof(FileListInfo.m_pbyFileInfo->m_pbyFileName));
//				memcpy(FileListInfo.m_pbyFileInfo,FileInfo,sizeof(FileListInfo.m_pbyFileInfo[500]));
//                OspPrintf(TRUE,FALSE,"文件md5值：%u\n",file_md5values);


            }
            else
            {
                string filePath = achFile;
                filePath += FindFileData.cFileName;              				
				file_lists.push_back(filePath);
				u32 file_size = (FindFileData.nFileSizeHigh * (MAXDWORD+1.0)) + FindFileData.nFileSizeLow;
				file_names.push_back(FindFileData.cFileName); 


//				cout << FindFileData.cFileName << "  大小："<< file_size <<endl;
//				OspPrintf(TRUE,FALSE,"%s  文件大小：%d\n",FindFileData.cFileName,file_size);
//		        memcpy(FileInfo.m_pbyFileName,FindFileData.cFileName,sizeof(FileListInfo.m_pbyFileInfo->m_pbyFileName));
//				memcpy(FileListInfo.m_pbyFileInfo,FileInfo,sizeof(FileListInfo.m_pbyFileInfo[500]));
//				FileListInfo.m_pbyFileInfo[500].m_dwFileSize = file_size;
//                OspPrintf(TRUE,FALSE,"文件md5值：%u\n",file_md5values);

            }
        }

    }while(::FindNextFile(hFind,&FindFileData));
    ::FindClose(hFind);
	
//	return file_lists;
    return file_names;
//	return file_sizes;
//	return file_md5values;

}

/*********************************************************************
    返回文件大小
*********************************************************************/

vector<u32> CFindSizes::findSizes( LPCSTR lpstrPath, LPCSTR lpstrName /*= ".*" */ )
{
    s8 achFind[MAX_PATH];//MAX_PATH
    s8 achFile[MAX_PATH];
	
    WIN32_FIND_DATA FindFileData;
	
    strcpy(achFind,lpstrPath);
    strcat(achFind,"\\*");
    strcat(achFind,lpstrName);
	
    HANDLE hFind=::FindFirstFile(achFind,&FindFileData);
	
    if(INVALID_HANDLE_VALUE == hFind)
    {
        OspLog(LOG_LVL_WARNING,"Empty folder!");
        return vector<u32>();
    }
	
    do
    {
        if(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
        {
            if(FindFileData.cFileName[0]!='.')
            {
                strcpy(achFile,lpstrPath);
                strcat(achFile,"\\");
                strcat(achFile,FindFileData.cFileName);
                findSizes(achFile);
				
            }
        }
        else
        {
            if ( achFile[0] )
            {
				u32 file_size = (FindFileData.nFileSizeHigh * (MAXDWORD+1.0)) + FindFileData.nFileSizeLow;
				file_sizes.push_back(file_size);
//				OspPrintf(TRUE,FALSE,"文件大小：%d\n",file_size);
            }
            else
            {

				u32 file_size = (FindFileData.nFileSizeHigh * (MAXDWORD+1.0)) + FindFileData.nFileSizeLow;
				file_sizes.push_back(file_size);
//				OspPrintf(TRUE,FALSE,"文件大小：%d\n",file_size);
            }
        }
		
    }while(::FindNextFile(hFind,&FindFileData));
    ::FindClose(hFind);
	

	return file_sizes;	
}

/*********************************************************************
    返回MD5值
*********************************************************************/


vector<u32> CFindMd5::findMd5( LPCSTR lpstrPath, LPCSTR lpstrName /*= ".*" */ )
{
    s8 achFind[MAX_PATH];//MAX_PATH
    s8 achFile[MAX_PATH];
	
    WIN32_FIND_DATA FindFileData;
	
    strcpy(achFind,lpstrPath);
    strcat(achFind,"\\\\*");
    strcat(achFind,lpstrName);
	
    HANDLE hFind=::FindFirstFile(achFind,&FindFileData);
	
    if(INVALID_HANDLE_VALUE == hFind)
    {
        OspLog(LOG_LVL_WARNING,"Empty folder!");
        return vector<u32>();
    }
	
    do
    {
        if(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
        {
            if(FindFileData.cFileName[0]!='.')
            {
                strcpy(achFile,lpstrPath);
                strcat(achFile,"\\\\");
                strcat(achFile,FindFileData.cFileName);
                findMd5(achFile);
				
            }
        }
        else
        {
            if ( achFile[0] )
            {
				string filePath = lpstrPath;//变量类型有待修改……
                filePath += "\\\\";
                filePath += FindFileData.cFileName;
				s8 filepath_md5[STRING_LENGTH];
				memcpy(&filepath_md5,&filePath[0u],STRING_LENGTH);
//				cout << filepath_md5 << endl;
//				u32 file_md5 = puts( md5.digestString( filepath_md5 ) ) ;
//				file_md5values.push_back(file_md5);

//				OspPrintf(TRUE,FALSE,"文件md5值：%u\n",file_md5);
				
            }
            else
            {
				string filePath = achFile;  
                filePath += FindFileData.cFileName; 
				s8 filepath_md5[STRING_LENGTH];
				memcpy(&filepath_md5,&filePath[0u],STRING_LENGTH);
//				cout << filepath_md5 << endl;
//				u32 file_md5 = puts( md5.digestString( filepath_md5 ) ) ;
//				file_md5values.push_back(file_md5);

//				OspPrintf(TRUE,FALSE,"文件md5值：%u\n",file_md5);
            }
        }
		
    }while(::FindNextFile(hFind,&FindFileData));
    ::FindClose(hFind);
	
	
	return file_md5values;	
}


/*********************************************************************
    Linux平台获取文件列表
*********************************************************************/
#else

#include <dirent.h>
#include <string.h>
#include <queue>

vector<string> CFindFiles::findFiles( const char *lpPath, const char *secName /*= ".*" */ )
{
    (void)secName;

    vector<string> result;
    queue<string> queue;
    string dirname;

    DIR *dir;
    if ( !(dir = opendir ( lpPath )) ) {
        return result;
    }
    queue.push( lpPath );

    struct dirent *ent;
    while ( !queue.empty() )
    {

        dirname = queue.front();
        dir = opendir( dirname.c_str() );
        queue.pop();
        if ( !dir ) { continue; }

        while( ent = readdir( dir ) )
        {

            if ( strcmp(".", ent->d_name) == 0 || strcmp("..", ent->d_name) == 0 )
            {
                continue;
            }
            if ( ent->d_type == DT_DIR )
            {
                queue.push( dirname+"/"+ent->d_name );
            }
            else
            {
                result.push_back( dirname+"/"+ent->d_name );
            }

        }

        closedir( dir );

    }

    return result;
}

#endif