//wstringreplacer.cpp

#include "wstringreplacer.h"

/// <summary>
/// 
/// </summary>
/// <param name="str">should be like {{{...}}}</param>
wStringReplacerVar::wStringReplacerVar(string str) 
{
	this->key2index = 0;
	this->key2offset = 0 ;
	this->keyindex = 0;
	this->keyoffset = 0;
	this->keylen = 0 ;
	this->type = 0 ;

	this->vtext = str;

	vector<string> substrvec;

	string innertext = vtext.substr(3, vtext.length()-6 ) ;

	int i0 = 0 ; 
	while( i0 < innertext.length() )
	{
		string::size_type pos = innertext.find(",", i0 ) ;
		if( pos != string::npos )
		{
			string part1 = innertext.substr(i0, pos-i0);
			if( part1.length() > 0 )
			{
				substrvec.push_back(part1);
			}
			i0 = pos+1;
		}else
		{
			string lastpart = innertext.substr(i0) ;
			if( lastpart.length() > 0 )
			{
				substrvec.push_back(lastpart) ;
			}
			break;
		}
	}

	if( substrvec.size() == 1 )
	{
		type= 0;
	}else if( substrvec.size() == 5)
	{
		type= 1;
	}else if( substrvec.size()==7)
	{
		type=2 ;
	}

	for(int i = 0 ; i < substrvec.size();++i )
	{
		this->parse( substrvec[i] ) ;
	}
}

/// {{{IN}}}
/// {{{V:IN,K:FY3D,I:0,O:0,L:5}}}
/// {{{V:IN,K:FY3D,I:0,O:4,K2:L2,I2:2,O2:-1}}}
void wStringReplacerVar::parse(string part) 
{
	if(part.length()>0)
	{
		string::size_type pos = part.find(":") ;
		if( pos != string::npos )
		{
			string part0 = part.substr(0, pos ) ;
			string part1 = part.substr(pos+1, part.length() - pos -1 ) ;
			if (part0 == "V")
			{
				this->vname = part1;
			}
			else if (part0 == "K")
			{
				this->key = part1;
			}
			else if (part0 == "I")
			{
				this->keyindex = (int)atof(part1.c_str());
			}
			else if (part0 == "O")
			{
				this->keyoffset = (int)atof(part1.c_str());
			}
			else if (part0 == "L")
			{
				this->keylen = (int)atof(part1.c_str());
			}
			else if (part0 == "K2")
			{
				this->key2 = part1;
			}
			else if (part0 == "I2")
			{
				this->key2index = (int)atof(part1.c_str());
			}
			else if (part0 == "O2")
			{
				this->key2offset = (int)atof(part1.c_str());
			}
		}else
		{
			this->vname = part;
		}
	}
}

wStringReplacer::wStringReplacer(string temstr) 
{
	templateStr = temstr;

	int i0 = 0;
	while( i0 < templateStr.length() )
	{
		string::size_type posleft = templateStr.find("{{{",i0) ;
		if( posleft != string::npos )
		{//find one.

			string::size_type posright = templateStr.find("}}}",i0+4) ;
			if( posright != string::npos )
			{
				int len = posright+3 - posleft;
				string substr = templateStr.substr(posleft,len) ;
				wStringReplacerVar var(substr) ;
				this->varVec.push_back(var) ;
				i0 = i0 + len ;//go next
			}else
			{
				//no }}}
				break ;
			}
		}else
		{
			//no find any one.
			break;
		}
	}
}
void wStringReplacer::setKV(string k,string v) 
{
	for(int i = 0 ; i<this->kvVec.size();++i )
	{
		if( kvVec[i].key == k )
		{
			kvVec[i].val = v ;
			return ;
		}
	}
	wStringReplacerKV kv ;
	kv.key = k;
	kv.val = v;
	this->kvVec.push_back(kv);
}
bool wStringReplacer::buildString(string& outstr, string& error )
{
	outstr = templateStr;
	for (int ivar = 0; ivar < this->varVec.size(); ++ivar)
	{
		wStringReplacerVar& var = this->varVec[ivar];
		string varValue = "";
		bool varvalueok = this->getValue(var.vname , varValue);
		if ( varvalueok==false )
		{
			error = string("can not find var-value of var-name:")+ var.vname ;
			cout << "Error : can not find var-value of var-name " << var.vname << endl;
			return false;
		}
		string varValueReformated = "";
		if (var.type == 0)
		{
			varValueReformated = varValue;
		}
		else if (var.type == 1)
		{
			string::size_type pos0 = varValue.find(var.key);
			if (pos0 != string::npos)
			{
				string::size_type pos1 = pos0 + var.keyoffset;
				string substr1 = varValue.substr(pos1, var.keylen);
				varValueReformated = substr1;
			}
			else
			{
				error = string("no var.key find:") + var.key;
				cout << "Error : no var.key find " << var.key << endl;
				return false;
			}
		}
		else if (var.type == 2)
		{
			string::size_type pos0 = varValue.find(var.key);
			string::size_type pos00 = varValue.find(var.key2);
			if (pos0 != string::npos && pos00 != string::npos )
			{
				string::size_type pos1 = pos0 + var.keyoffset;
				string::size_type pos11 = pos00 + var.key2offset;
				int len = pos11 - pos1 + 1;
				if (len > 0)
				{
					string substr1 = varValue.substr(pos1, len);
					varValueReformated = substr1;
				}
				else
				{
					char errorbuff[128];
					sprintf(errorbuff, "bad pos1(%d) , pos11(%d)", (int)pos1, pos11);
					error = string(errorbuff);
					cout << "Error : bad pos1, pos11 " << pos1 << "," << pos11 << endl;
					return false;
				}
			}
			else
			{
				error = string("no var.key or var.key2 find ")+var.key+","+var.key2 ;
				cout << "Error : no var.key or var.key2 find " << var.key << "," << var.key2 << endl;
				return false;
			}
		}
		if(varValueReformated=="")
		{
			error = string("varValueReformated is empty, may be no valid var with type, vtext:") + var.vtext ;
			cout << "varValueReformated is empty, may be no valid var with type " << var.type << endl;
			return false;
		}
		else
		{
			//do replacement
			outstr = this->replaceString(outstr, var.vtext, varValueReformated);
		}
	}
	return true;
}


bool wStringReplacer::getValue(string k, string& retval)
{
	for (int ik = 0; ik < this->kvVec.size(); ++ik)
	{
		if (this->kvVec[ik].key == k)
		{
			retval = this->kvVec[ik].val;
			return true;
		}
	}

	return false;
}

//Ìæ»»×Ö·û´®
std::string wStringReplacer::replaceString(std::string str, const std::string& from, const std::string& to) {
	size_t start_pos = 0;
	while ((start_pos = str.find(from, start_pos)) != std::string::npos) {
		str.replace(start_pos, from.length(), to);
		start_pos += to.length(); // Handles case where 'to' is a substring of 'from'
	}
	return str;
}
