#ifndef W_STRING_UTILS_H
#define W_STRING_UTILS_H
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

using std::cout ;
using std::endl ;
using std::string;
using std::vector ;
using std::sort ;

struct wStringUtils{

	static std::vector<std::string> splitString(const string wholeString, const string sep) ;
	static std::string getFileNameFromFilePath(string filepath);
	static bool stringContains(string wholeStr , string subStr) ;
	static string replaceString(std::string str, const std::string& from, const std::string& to);
	static string int2str( int val ) ;
    static string double2str(double val) ;
    static string long2str( int64_t val) ;
    //查找子串在大串中第index出现的位置
    static size_t findStrPosWithIndex(const string fullstr,const string findstr,const int index) ;

    //降序排序2021-5-15
    static void sortDesc( vector<string>& strvec ) ;
    //升序排序2021-5-15
    static void sortAsc( vector<string>& strvec ) ;

    //转大写字母 2022-1-7
    static string toUpper(string instr);

    //转小写字母 2022-1-7
    static string toLower(string instr);

    //字符串是否全部是数字 2022-1-7
    static bool isAllNumber(string instr);

    
} ;


#endif
