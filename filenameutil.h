#ifndef W_FILENAMEUTIL_H
#define W_FILENAMEUTIL_H

#include <string>

using std::string;

//
struct wFilenameUtil
{
	static string extractFilepathWithoutExtname(string filepath) ;
    static string extractFileDir(string filepath) ;
    static string int2str(int val) ;
    static string baseName(string filepath) ;
    //如果文件名不满足datePos与dateLen限制返回false,反正返回true,y,m,d, dateLen不足使用0填充到8位
    static bool extractYearMonthDayFromFilename(string filepath,int datePos,int dateLen,int& y,int& m,int& d) ;
};


#endif
