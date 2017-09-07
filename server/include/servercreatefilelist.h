/*
 *   Find and generate a file list of the folder.
**/

#ifndef _SERVERCREATEFILELIST_H_
#define _SERVERCREATEFILELIST_H_

#include <vector>
#include <string>
#include "../../common/osp.h"

using namespace std;

class FindFiles
{
public:
    FindFiles(){}
    ~FindFiles(){}
	
    vector<string> findFiles( LPCSTR lpstrPath, LPCSTR lpstrName = ".*" );
	
private:
    vector<string> file_lists;
	vector<string> file_names;
};

class FindSizes
{
public:
    FindSizes(){}
    ~FindSizes(){}
	
    vector<u32> findSizes( LPCSTR lpstrPath, LPCSTR lpstrName = ".*" );
	
private:
	vector<u32> file_sizes;
};

class FindMd5
{
public:
    FindMd5(){}
    ~FindMd5(){}
	
    vector<u32> findMd5( LPCSTR lpstrPath, LPCSTR lpstrName = ".*" );
	
private:
	vector<u32> file_md5values;
};
#endif