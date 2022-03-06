#ifndef W_DIR_TOOLS_H
#define W_DIR_TOOLS_H

#ifdef __linux__
#include <sys/stat.h>
#include <dirent.h>

#endif

#include <string>
#include <iostream>
#include <cstdio>
#include <vector>
using std::vector ;
using std::cout;
using std::endl;
using std::string;

//
class wDirTools
{
public:
	bool isDirExist( std::string& dirname ) ;
	/// dirname 可以/，也可以无/
	bool mkDir( std::string& dirname ) ;
	string makeProductDir(string  rootdir,vector<string> subdirs, string& errorText) ;

	static string extractRelativePath( string rootdir , string fullPath ) ;
	static bool isFileExist( std::string filename ) ;
	static bool removeFile( std::string filename ) ;
	static std::string parentDir(std::string const & path);
    
    /// dir 可以为/结尾或者无/结尾 ， 这个函数只扫描一层目录
    bool getDirFiles(string dir,string prefix,string tail, vector<string>& retfiles) ;
    /// path 可以/结尾，也可以无/结尾，程序会自己加上/
    static void getDirFilesRecursive(std::string path,std::vector<std::string>& results) ;

    /// 递归扫描子目录文件，增加了文件名前缀和后缀筛选
    static void getDirFilesRecursive2(std::string path,string prefix,string tail,std::vector<std::string>& results) ;
};


#endif
