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

#endif