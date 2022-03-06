#include "filenameutil.h"

string wFilenameUtil::extractFilepathWithoutExtname(string filepath)
{
	std::size_t found = filepath.rfind(".") ;
	if(found == std::string::npos ) {
		return filepath ;
	}else{
		string newstr = filepath.substr(0 , found) ;
		return newstr ;
	}
}

//
string wFilenameUtil::extractFileDir(string filepath)
{
     size_t pos = filepath.find_last_of("\\/");
     return (std::string::npos == pos)
         ? ""
         : filepath.substr(0, pos);

}

string wFilenameUtil::int2str(int val)
{
    char buff[64] ;
    sprintf(buff,"%d" , val) ;
    return string(buff) ;
}

string wFilenameUtil::baseName(string filepath)
{
    return filepath.substr(filepath.find_last_of("/\\") + 1);
}


//如果文件名不满足datePos与dateLen限制返回false,反正返回true,y,m,d, dateLen不足使用0填充到8位
bool wFilenameUtil::extractYearMonthDayFromFilename(string filepath,int datePos,int dateLen,int& y,int& m,int& d)
{
    string fname = baseName(filepath) ;
    if(dateLen<=0 || dateLen>8) return false;
    if( datePos + dateLen > fname.length() ) return false;
    string subymd = fname.substr(datePos,dateLen) ;
    for(int i = subymd.length(); i< 8; ++ i )
    {
        subymd = subymd+"0" ;
    }
    y = atof( subymd.substr(0,4).c_str()) ;
    m = atof( subymd.substr(4,2).c_str()) ;
    d = atof( subymd.substr(6,2).c_str()) ;
    return true ;
}
