//20201-3-2 update

#ifndef W_DATETIME_H

#define W_DATETIME_H
#include <ctime>
#include <string>
#include <chrono>
#include <stdexcept>
using std::string;

struct wDatetime{

    //2020-01-01 00:00:00
	static std::string currentDateTimeStr();
    //2020-01-01 00:00:00 CST
    static std::string currentDateTimeStrCST();
    
    //获取之前多少天的日期 yyyy-MM-dd   beforedays should >= 0
    //返回yyyy-MM-dd格式字符串，resymd为yyyyMMdd整形数字
    static std::string dateStrBeforeNDays(int beforedays,int& resymd) ;
    
    
	//yyyyMMddhhmmss
	static std::string currentDateTimeStrTight() ;
    
    //return current milliseconds
    static int64_t currentMilliSeconds() ;
    
    //yyyyMMdd -> yyyy-MM-dd
    static string slimDate2FatDate( string date1 );
    //yyyyMMdd -> yyyy年MM月dd日
    static string slimDate2FatDateCN( string date1 ) ;
    
    //hhmmss -> hh:mm:ss
    static string slimTime2FatTime( string time1 ) ;
    
    //utm convert into beijing time
    static bool convertUtmTimeStr2BeijingTimeStr( string utmdate, string utmtime, string& bjdate, string& bjtime ) ;
    
    //date time string to seconds
    static bool convertDatetimeStr2Timestamp(string datestr, string timestr , time_t & retSeconds ) ;

    //convert yyyyMMdd -> yyyyddd
    static int convertYmd8toYmd7(int ymd8) ;
    static int convertYmd7toYmd8(int ymd7) ;
    static bool isLeapYear(int ymd8) ;//是否闰年（2月29天）
    
};

    
    
#endif
