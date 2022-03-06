#include "wstringutils.h"


string wStringUtils::int2str( int val ) 
{
	char buff[1024] ;
	sprintf(buff , "%d" , val ) ;
	return string(buff) ;
}

string wStringUtils::double2str(double val) 
{
    char buff[256] ;
    sprintf(buff,"%.3f" , val) ;
    return string(buff) ;
}

string wStringUtils::long2str( int64_t val ) 
{
	char buff[1024] ;
	sprintf(buff , "%ld" , val ) ;
	return string(buff) ;
}

std::vector<std::string> wStringUtils::splitString(const string wholeString, const string sep) 
{
	std::vector<std::string> result;

	int pos0 = 0;
	while (pos0 < wholeString.length())
	{
		int pos1 = wholeString.find(sep,pos0);
		if (pos1 == std::string::npos)
		{
			std::string substr = wholeString.substr(pos0);
			if (substr.length() > 0) result.push_back(substr);
			break;
		}
		else {
			int len1 = pos1 - pos0;
			std::string substr = wholeString.substr(pos0 , len1);
			if (substr.length() > 0) result.push_back(substr);
			pos0 = pos1 + 1;
		}
	}
	return result;
}

std::string wStringUtils::getFileNameFromFilePath(string filepath)
{
	return filepath.substr(filepath.find_last_of("/\\") + 1);
}

bool wStringUtils::stringContains(string wholeStr , string subStr) {
	if (wholeStr.find(subStr) != std::string::npos) {
	    return true;
	}else{
		return false;
	}
}

// 替换字符串
std::string wStringUtils::replaceString(std::string str, const std::string& from, const std::string& to) {
	size_t start_pos = 0;
	while ((start_pos = str.find(from, start_pos)) != std::string::npos) {
		str.replace(start_pos, from.length(), to);
		start_pos += to.length(); // Handles case where 'to' is a substring of 'from'
	}
	return str;
}

// 查找子串在大串中第index出现的位置
size_t wStringUtils::findStrPosWithIndex(const string fullstr,const string findstr,const int index) 
{
    if( findstr == "" ){
        return  std::string::npos;
    }else
    {
        size_t findpos = std::string::npos ;
        size_t findstart = 0 ;
        for(int ifind = 0 ; ifind <= index ; ++ ifind )
        {
            findpos = fullstr.find( findstr , findstart ) ;
            if( findpos == std::string::npos ){
                break ;
            }else{
                findstart = findpos + findstr.length() ;
            }
        }
        return findpos ;
    }
}


bool wStringUtils_descStrComp( const string& lstr , const string& rstr )
{
	if( lstr.compare(rstr) > 0 ) return true ;
	else return false ;
}

bool wStringUtils_ascStrComp( const string& lstr , const string& rstr )
{
	if( lstr.compare(rstr) < 0 ) return true ;
	else return false ;
}

//降序排序
void wStringUtils::sortDesc( vector<string>& strvec ) 
{
	sort( strvec.begin() , strvec.end() , wStringUtils_descStrComp ) ;
}


//升序排序
void wStringUtils::sortAsc( vector<string>& strvec ) 
{
	sort( strvec.begin() , strvec.end() , wStringUtils_ascStrComp ) ;
}


//转大写字母 2022-1-7
string wStringUtils::toUpper(string instr)
{
	for (auto& c : instr) c = toupper(c);
	return instr;
}

//转小写字母 2022-1-7
string wStringUtils::toLower(string instr)
{
	for (auto& c : instr) c = tolower(c);
	return instr;
}

//字符串是否全部是数字
bool wStringUtils::isAllNumber(string instr)
{
	if (instr.size() == 0) return false;
	int n = 0;
	for (size_t i = 0; i < instr.size(); ++i)
	{
		if (isdigit(instr[i]))
		{
			++n;
		}
	}
	if (n == instr.size()) {
		return true;
	}
	else {
		return false;
	}

}