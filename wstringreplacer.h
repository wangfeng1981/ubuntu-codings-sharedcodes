//wstringreplacer.h

#ifndef W_STRING_REPLACER_H
#define W_STRING_REPLACER_H

#include <vector>
#include <string>
#include <iostream>

using std::cout;
using std::endl;

using std::vector;
using std::string;

//替换变量
struct wStringReplacerVar
{
	int type;// 0-normal , 1-fixlen , 2-range 

	string vtext;// {{{...}}}

	string vname;//0,1,2
	string key;  //1,2
	int keyindex; //1,2
	int keyoffset; //1,2
	int keylen ;   //1

	string key2;//2
	int key2index;//2
	int key2offset;//2

	wStringReplacerVar(string str) ;//should be {{{...}}}
private:
	void parse(string part) ;
};

//键值对
struct wStringReplacerKV
{
	string key,val;
};


struct wStringReplacer
{
private:
	vector<wStringReplacerVar> varVec ;
	vector<wStringReplacerKV> kvVec;

	string templateStr ;
public:
	wStringReplacer(string temstr) ;
	void setKV(string k,string v) ;
	bool buildString(string& outstr, string& error );
	bool getValue(string k, string& retval);
	string replaceString(std::string str, const std::string& from, const std::string& to);
} ;







#endif