/*
 *   Find and generate a file list of the folder.
**/

#ifndef _SERVERCREATEFILELIST_H_
#define _SERVERCREATEFILELIST_H_

#include <vector>
#include <string>
#include "../../common/osp.h"

using namespace std;

class CFindFiles
{
public:
//    CFindFiles(){}
//    ~CFindFiles(){}
	
    vector<string> findFiles( LPCSTR lpstrPath, LPCSTR lpstrName = ".*" );
	
private:
    vector<string> file_lists;
	vector<string> file_names;
};

class CFindSizes
{
public:
//    CFindSizes(){}
//    ~CFindSizes(){}
	
    vector<u32> findSizes( LPCSTR lpstrPath, LPCSTR lpstrName = ".*" );
	
private:
	vector<u32> file_sizes;
};

class CFindMd5
{
public:
 //   CFindMd5(){}
 //   ~CFindMd5(){}
	
    vector<u32> findMd5( LPCSTR lpstrPath, LPCSTR lpstrName = ".*" );
	
private:
	vector<u32> file_md5values;
};
#endif