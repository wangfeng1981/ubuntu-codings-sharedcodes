#include "wdirtools.h"


//
bool wDirTools::isDirExist( std::string& dirname ) 
{
	#ifdef __linux__
	struct stat buffer;
	return (stat (dirname.c_str(),&buffer)==0 );
	#endif
	return false;
}

//
bool wDirTools::mkDir( std::string& dirname ) 
{
	#ifdef __linux__
	if( mkdir(dirname.c_str(),0777) == -1 )
	{
		cout <<"Error : failed to make dir :"<<dirname<<endl;
		return false;
	}else
	{
		cout<<"Info : successfully make dir:"<<dirname<<endl;
		return true;
	}
	#endif
	return false;
}

//
string wDirTools::makeProductDir(string  rootdir,vector<string> subdirs, string& errorText)
{
	string outdir = rootdir;
	//cout<<outdir<<endl;
	if( isDirExist(outdir) )
	{
		for(int idir = 0 ; idir < subdirs.size() ; ++ idir )
		{
			if( subdirs[idir].length()== 0 )
			{
				errorText = "subdirs[idir] is empty string." ;
				return "" ;
			}
			//concat output dir 
			outdir += "/" + subdirs[idir] ;
			//cout<<outdir<<endl ;

			//test if output dir is ok.
			if( isDirExist(outdir) == false )
			{
				//not exist, then make it.
				if( mkDir( outdir ) ==false ) {
					//make failed , return nullstr.
					errorText = string("failed make dir:" )+ outdir ;
					return "" ;
				}
			}
		}
		return outdir ;
	}else
	{
		//cout<<"Error : root dir is not exist:"<<outdir<<endl;
		errorText = string("root dir is not exist:" )+ rootdir ;
		return "";
	}
	return "";
}


//use relative path
string wDirTools::extractRelativePath( string rootdir , string fullPath ) 
{
	if( fullPath.length() > rootdir.length() )
	{
		return fullPath.substr( rootdir.length() , fullPath.length() - rootdir.length() ) ;
	}else
	{
		return fullPath ;
	}
}


bool wDirTools::isFileExist( std::string filename ) {
	FILE* pf = fopen( filename.c_str() ,"rb" ) ;
	if( pf== 0 ){
		cout<<"Info : file not exist "<<filename<<endl ;
		return false ;
	}
	fclose(pf) ;
	return true ;
}
bool wDirTools::removeFile( std::string filename ) {
	if( remove( filename.c_str() ) != 0 ){
		cout<<"Error : failed to delete file:"<<filename <<endl ;
		return false ;
	}
	else{
		cout<<"Info : File successfully deleted:"<<filename <<endl ;
		return true ;
	}
}

//获取路径，结果带斜杠
std::string wDirTools::parentDir(std::string const & path)
{
	return path.substr(0 , path.find_last_of("/\\")+1 );
}


/// dir 可以为/结尾或者无/结尾 ， 这个函数只扫描一层目录
bool wDirTools::getDirFiles(string indir,string prefix,string tail, vector<string>& retfiles) 
{
    if( indir == "" ) return false ;
    //保证indir以/结尾
    if( indir[indir.length()-1] != '/' )
    {
        indir += "/" ;
    }
    
    if (auto dir = opendir(indir.c_str())) {
        while (auto f = readdir(dir)) {
            if (!f->d_name || f->d_name[0] == '.')
                continue; // Skip everything that starts with a dot
            
            string fname = f->d_name ;
            int prefixlen = prefix.length() ;
            int taillen = tail.length() ;
            if( fname.length() < prefixlen || fname.length() < taillen )
            {
                continue ;//skip this file
            }
            if( prefixlen>0 )
            {
                string part = fname.substr(0 , prefixlen) ;
                if( part != prefix ){
                    continue ;//skip
                }
            }
            if( taillen > 0 )
            {
                string part = fname.substr( fname.length() - taillen , taillen ) ;
                if( part != tail ){
                    continue ;//skip
                }
            }           
            retfiles.push_back( indir + fname) ;
        }
        closedir(dir);
        return true ;
    }else{
        return false ;
    }
}


void wDirTools::getDirFilesRecursive(std::string path,std::vector<std::string>& results) 
{
	if( path=="" ) return ;
	if( path[path.length()-1] != '/' )
    {
        path += "/" ;
    }
    if (auto dir = opendir(path.c_str())) {
        while (auto f = readdir(dir)) {
            if (!f->d_name || f->d_name[0] == '.') continue;
            if (f->d_type == DT_DIR) 
                wDirTools::getDirFilesRecursive(path + f->d_name + "/", results );

            if (f->d_type == DT_REG)
                results.push_back( path + f->d_name);
        }
        closedir(dir);
    }
}

/// 递归扫描子目录文件，增加了文件名前缀和后缀筛选
void wDirTools::getDirFilesRecursive2(std::string path,
	string prefix,string tail,
	std::vector<std::string>& results) 
{
	if( path=="" ) return ;
	if( path[path.length()-1] != '/' )
    {
        path += "/" ;
    }
    if (auto dir = opendir(path.c_str())) {
        while (auto f = readdir(dir)) {
            if (!f->d_name || f->d_name[0] == '.') continue;
            if (f->d_type == DT_DIR) 
                wDirTools::getDirFilesRecursive2(path + f->d_name + "/",prefix,tail, results );

            if (f->d_type == DT_REG){

            	string fname = f->d_name ;
	            int prefixlen = prefix.length() ;
	            int taillen = tail.length() ;
	            if( fname.length() < prefixlen || fname.length() < taillen )
	            {
	                continue ;//skip this file
	            }
	            if( prefixlen>0 )
	            {
	                string part = fname.substr(0 , prefixlen) ;
	                if( part != prefix ){
	                    continue ;//skip
	                }
	            }
	            if( taillen > 0 )
	            {
	                string part = fname.substr( fname.length() - taillen , taillen ) ;
	                if( part != tail ){
	                    continue ;//skip
	                }
	            }           
                results.push_back( path + fname);
            }
        }
        closedir(dir);
    }
}