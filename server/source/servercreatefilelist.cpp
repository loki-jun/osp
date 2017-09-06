#include "../include/servercreatefilelist.h"
#include <iostream>
#include <fstream>
#include <stdlib.h>  
#include <stdio.h> 
#include "../../common/osp.h"
#include "../../common/csmsg.h"

using namespace std;
//extern CFileInfo g_CFileInfo;
/*********************************************************************
    Windows平台获取文件列表
*********************************************************************/
#ifdef WIN32

#include <Windows.h>
#include <direct.h>

vector<string> FindFiles::findFiles( LPCSTR lpstrPath, LPCSTR lpstrName /*= ".*" */ )
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
        cout << "Empty folder!" << endl;
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
                string filePath = lpstrPath;//变量类型有待修改……
                filePath += "\\";
                filePath += FindFileData.cFileName;
				file_lists.push_back(filePath);
				u32 file_size = (FindFileData.nFileSizeHigh * (MAXDWORD+1.0)) + FindFileData.nFileSizeLow;
				cout << FindFileData.cFileName << "  大小："<< file_size <<endl;
				OspPrintf(TRUE,FALSE,"%s  文件大小：%u\n",FindFileData.cFileName,file_size);
//				g_CFileInfo.m_pbyFileName = FindFileData.cFileName;
//				g_CFileInfo.m_dwFileSize = file_size;

            }
            else
            {
                string filePath = achFile;
                filePath += FindFileData.cFileName;              				
				file_lists.push_back(filePath);
				u32 file_size = (FindFileData.nFileSizeHigh * (MAXDWORD+1.0)) + FindFileData.nFileSizeLow;
				cout << FindFileData.cFileName << "  大小："<< file_size <<endl;
				OspPrintf(TRUE,FALSE,"%s  文件大小：%d\n",FindFileData.cFileName,file_size);
//				g_CFileInfo.m_pbyFileName = FindFileData.cFileName;
//				g_CFileInfo.m_dwFileSize = file_size;
            }
        }

    }while(::FindNextFile(hFind,&FindFileData));

    ::FindClose(hFind);
    return file_lists;
}

/*********************************************************************
    Linux平台获取文件列表
*********************************************************************/
#else

#include <dirent.h>
#include <string.h>
#include <queue>

vector<string> FindFiles::findFiles( const char *lpPath, const char *secName /*= ".*" */ )
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