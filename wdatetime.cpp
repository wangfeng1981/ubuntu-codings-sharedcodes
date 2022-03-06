//20201-3-2 update

#include "wdatetime.h"

//yyyyMMdd -> yyyy-MM-dd
string wDatetime::slimDate2FatDate( string date1 )
{
    if( date1.length() == 8 ){
        string newtime ;
        newtime = date1.substr(0,4) + "-" + date1.substr(4,2) + "-" + date1.substr(6,2) ;
        return newtime ;
    }else{
        return date1 ;
    }
        
}

//hhmmss -> hh:mm:ss
string wDatetime::slimTime2FatTime( string time1 ) {
    if( time1.length() == 6 ){
        string newtime ;
        newtime = time1.substr(0,2) + ":" + time1.substr(2,2) + ":" + time1.substr(4,2) ;
        return newtime ;
    }else{
        return time1 ;
    }
    
}

//yyyyMMdd -> yyyy-MM-dd
string wDatetime::slimDate2FatDateCN( string date1 )
{
    if( date1.length() == 8 ){
        string newtime ;
        newtime = date1.substr(0,4) + "年" + date1.substr(4,2) + "月" + date1.substr(6,2)+"日";
        return newtime ;
    }else{
        return date1 ;
    }
        
}


std::string wDatetime::currentDateTimeStr()
{
	time_t theTime = time(NULL);
	struct tm *aTime = localtime(&theTime);
	int day = aTime->tm_mday;
	int month = aTime->tm_mon + 1;
	int year = aTime->tm_year + 1900;

	int hour = aTime->tm_hour;
	int minu = aTime->tm_min;
	int sec = aTime->tm_sec;

	char buff[30];
	sprintf(buff, "%04d-%02d-%02d %02d:%02d:%02d", year, month, day , hour ,minu , sec );
	return std::string(buff);
}

std::string wDatetime::currentDateTimeStrCST()
{
	time_t theTime = time(NULL);
	struct tm *aTime = localtime(&theTime);
	int day = aTime->tm_mday;
	int month = aTime->tm_mon + 1;
	int year = aTime->tm_year + 1900;

	int hour = aTime->tm_hour;
	int minu = aTime->tm_min;
	int sec = aTime->tm_sec;

	char buff[30];
	sprintf(buff, "%04d-%02d-%02d %02d:%02d:%02d CST", year, month, day , hour ,minu , sec );
	return std::string(buff);
}

std::string wDatetime::currentDateTimeStrTight()
{
	time_t theTime = time(NULL);
	struct tm *aTime = localtime(&theTime);
	int day = aTime->tm_mday;
	int month = aTime->tm_mon + 1;
	int year = aTime->tm_year + 1900;

	int hour = aTime->tm_hour;
	int minu = aTime->tm_min;
	int sec = aTime->tm_sec;

	char buff[30];
	sprintf(buff, "%04d%02d%02d%02d%02d%02d", year, month, day , hour ,minu , sec );
	return std::string(buff);
}


//return current milliseconds
int64_t wDatetime::currentMilliSeconds() 
{
    unsigned long now = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
	return now ;
}


bool wDatetime::convertDatetimeStr2Timestamp(string datestr, string timestr , time_t & retSeconds ) 
{
    try{
        int ymd = std::stoi( datestr ) ;
        int hms = std::stoi( timestr ) ;
        
        tm tm1 ;
        tm1.tm_year = ymd/10000 - 1900 ;
        tm1.tm_mon =  (ymd%10000)/100 - 1 ;
        tm1.tm_mday = ymd%100 ;
        tm1.tm_hour=  hms / 10000 ;
        tm1.tm_min = (hms%10000)/100 ;
        tm1.tm_sec = hms%100 ;
        tm1.tm_isdst = 0 ;
        //cout<<"debug "<<tm1.tm_hour<<endl ;
        
        time_t tt = mktime( &tm1 ) ;
        retSeconds = tt ;
        return true;
    }catch(std::invalid_argument &e )
    {
        return false ;
    }catch(std::out_of_range & e ){
        return false ;
    }
}


//utm convert into beijing time input should be YYYYMMDD , HHmmss
bool wDatetime::convertUtmTimeStr2BeijingTimeStr( string utmdate, string utmtime, string& bjdate, string& bjtime ) 
{
    time_t utmtt ;
    bool ok1 = convertDatetimeStr2Timestamp( utmdate , utmtime , utmtt) ;
    if( ok1 == false ){
        return false ;
    }
    //add 8 hours
    time_t bjtt = utmtt + 8 * 3600 ;
    
    struct tm *aTime = localtime(&bjtt);
	int day = aTime->tm_mday;
	int month = aTime->tm_mon + 1;
	int year = aTime->tm_year + 1900;

	int hour = aTime->tm_hour;
	int minu = aTime->tm_min;
	int sec = aTime->tm_sec;

	char buff[32];
	sprintf(buff, "%04d%02d%02d", year, month, day );
    bjdate = string(buff) ;
    
    sprintf(buff, "%02d%02d%02d", hour, minu, sec );
    bjtime = string(buff) ;
    
    return true ;
    
}
    
    
//获取之前多少天的日期 yyyy-MM-dd   beforedays should >= 0
std::string wDatetime::dateStrBeforeNDays(int beforedays,int& resymd) 
{
    time_t currTime = time(NULL);
	time_t t0 = currTime - beforedays * 60 * 60 * 24;
	struct tm * time0 = localtime(&t0);
	int day0 =  time0->tm_mday;
	int mon0 =  time0->tm_mon + 1;
	int year0 = time0->tm_year + 1900;
    resymd = year0 * 10000 + mon0 * 100 + day0 ;
    char res[24] ;
    sprintf(res,"%04d-%02d-%02d", year0,mon0,day0) ;
	return string(res) ;
}



//convert yyyyMMdd -> yyyyddd
int wDatetime::convertYmd8toYmd7(int ymd8) 
{
    int year = ymd8/10000 ;
    int mon =  (ymd8%10000)/100 ;
    int day = ymd8%100 ;
    if( mon<1 || mon > 12 ) return 0 ;
    
    int leap = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);

    int mondays[12] = { 31,28,31,30,     31,30,31,31,   30,31,30,31 } ;
    if( leap == 1 ){
        mondays[1] = 29 ;
    }

    if( day<1 || day > mondays[mon-1] ) return 0 ;

    int daycnt = day ;
    for(int imon=1;imon<mon;++imon ){ // bugfixed //for(int imon = 1 ; imon < mon-1 ; ++ imon ){
        daycnt += mondays[imon-1] ;
    }
    return year*1000 + daycnt ;
}

int wDatetime::convertYmd7toYmd8(int ymd7) 
{
    int year = ymd7/1000 ;
    int jday = ymd7%1000 ;
    int month = 0;
    int day = 0;
    int days[2][13] = {
        { 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334 , 367 },
        { 0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335 , 367 }
    };
    int leap = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
    for (int imon = 1; imon <= 12; ++imon)
    {
        if (jday <= days[leap][imon])
        {
            month = imon;
            day = jday - days[leap][imon - 1];
            int ymd8 = year * 10000 + month * 100 + day  ;
            return ymd8;
        }
    }
    return 0 ;
}

bool wDatetime::isLeapYear(int ymd8) //是否闰年（2月29天）
{
    int year = ymd8/10000 ;
    int leap = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
    if( leap==1 ) return true ;
    else return false ;
}