/// Hseg tlv 数据对象
/// 2022-3-23 1059


#include "whsegtlvobject.h"
#include <stdio.h>
#include <string.h>
#include <fstream>

using std::ofstream;

void TLV::print() {
	printf("tag:%c%c%c%c, blen:%d\n" , tag[0],tag[1],tag[2],tag[3],bytes.size()) ;
}


void WHsegTlvObject::readTLV(FILE* pf,TLV& r_tlv)
{
	r_tlv.bytes.clear() ;
	fread( r_tlv.tag , 1 , 4 ,  pf ) ;
	int blen = 0 ;
	fread( &blen , 4 , 1 , pf) ;
	r_tlv.bytes.resize( blen ) ;
	fread( r_tlv.bytes.data() , 1 , blen , pf) ;
}

void WHsegTlvObject::readTLV(vector<unsigned char>& binarydata,int readoffset,TLV& r_tlv,int& newoffset)
{
    r_tlv.bytes.clear() ;
    r_tlv.tag[0] = binarydata[readoffset+0] ;
    r_tlv.tag[1] = binarydata[readoffset+1] ;
    r_tlv.tag[2] = binarydata[readoffset+2] ;
    r_tlv.tag[3] = binarydata[readoffset+3] ;

    int blen = 0 ;
    unsigned char* dataPtr = binarydata.data() ;
    memcpy( &blen , dataPtr+readoffset+4 , 4 ) ;
    r_tlv.bytes.resize( blen ) ;

    memcpy( r_tlv.bytes.data() ,  dataPtr+readoffset+8 , blen ) ;
    newoffset = readoffset+8+blen ;

}


bool WHsegTlvObject::readFromFile(string hsegtlvfile,string& error)
{
	allLevelHsegs.clear() ;
	FILE* pf = fopen( hsegtlvfile.c_str() , "rb" ) ;
	if( pf==0 ){
		error = "Failed to read file " + hsegtlvfile ;
		return false ;
	}

	//00
	{
		TLV tlv ;
		readTLV( pf , tlv) ;
		tlv.print() ;
		if( tlv.bytes.size() != 1 ){
			error = "tlv00 len is not 1." ;
			return false ;
		}
		allLevelHsegs.resize( (int)tlv.bytes[0] ) ;
		cout<<"level num:"<<allLevelHsegs.size()<<endl ;
	}

	//
	for(int il = 0 ; il < allLevelHsegs.size() ; ++ il ){
		TLV tlv ;
		readTLV(pf,tlv) ;
		tlv.print() ;
		int nhseg = tlv.bytes.size()/12 ;
		cout<<"level:"<<il<<", num hseg:"<<nhseg<<endl ;
		allLevelHsegs[il].ilevel = il ;
		if( nhseg>0 ){
			int* intDataPtr = (int*)tlv.bytes.data() ;
			allLevelHsegs[il].hsegs.resize( nhseg ) ;
			for(int ih = 0 ; ih < nhseg; ++ ih )
			{
				allLevelHsegs[il].hsegs[ih].x0 = intDataPtr[ih*3+0] ;
				allLevelHsegs[il].hsegs[ih].y  = intDataPtr[ih*3+1] ;
				allLevelHsegs[il].hsegs[ih].x1 = intDataPtr[ih*3+2] ;
			}
		}
	}

	fclose(pf) ;
	return true ;

}


bool WHsegTlvObject::readFromBinaryData(vector<unsigned char>& binarydata,string& error)
{
    allLevelHsegs.clear() ;
	if( binarydata.size()==0 ){
		error = "binarydata is empty.";
		return false ;
	}

    int offset = 0 ;

	//00
	{
		TLV tlv ;
		readTLV( binarydata , offset , tlv , offset);
		tlv.print() ;
		if( tlv.bytes.size() != 1 ){
			error = "tlv00 len is not 1." ;
			return false ;
		}
		allLevelHsegs.resize( (int)tlv.bytes[0] ) ;
		cout<<"level num:"<<allLevelHsegs.size()<<endl ;
	}

	//
	for(int il = 0 ; il < allLevelHsegs.size() ; ++ il ){
		TLV tlv ;
		readTLV( binarydata , offset , tlv , offset);
		tlv.print() ;
		int nhseg = tlv.bytes.size()/12 ;
		cout<<"level:"<<il<<", num hseg:"<<nhseg<<endl ;
		allLevelHsegs[il].ilevel = il ;
		if( nhseg>0 ){
			int* intDataPtr = (int*)tlv.bytes.data() ;
			allLevelHsegs[il].hsegs.resize( nhseg ) ;
			for(int ih = 0 ; ih < nhseg; ++ ih )
			{
				allLevelHsegs[il].hsegs[ih].x0 = intDataPtr[ih*3+0] ;
				allLevelHsegs[il].hsegs[ih].y  = intDataPtr[ih*3+1] ;
				allLevelHsegs[il].hsegs[ih].x1 = intDataPtr[ih*3+2] ;
			}
		}
	}
	return true ;
}



bool WHsegTlvObject::writeToFile( string hsegtlvfile,string& error)
{
	if( allLevelHsegs.size() == 0 ){
		error = "Zero allLevelHsegs." ;
		return false ;
	}
	if( allLevelHsegs.size() > 21 ){
		error = "AllLevelHsegs.size greater 21." ;
		return false ;
	}

	ofstream ofs( hsegtlvfile.c_str() , std::ios::out|std::ios::binary);
	if( ofs.good()==false ){
		error = "Failed to open output file:" + hsegtlvfile ;
		return false ;
	}

	char tag[5]="NLVL" ;
	int value00size = 1 ;//1Byte
	unsigned char lvlNum = (unsigned char)allLevelHsegs.size();
	ofs.write( tag , 4) ;
	ofs.write( (char*)&value00size , 4) ;
	ofs.write( (char*)&lvlNum , 1) ;

	for(int il = 0 ; il < allLevelHsegs.size() ; ++ il ){
		sprintf(tag,"L%03d",il) ;
		ofs.write( tag , 4) ;
		int valbytes = allLevelHsegs[il].hsegs.size()*12;
		ofs.write( (char*)&valbytes , 4) ;
		if( valbytes > 0 ) {
			vector<WHseg>& hsegvec = allLevelHsegs[il].hsegs ;
			vector<int> datavec; datavec.resize(3*hsegvec.size()) ;
			for(int ih = 0 ; ih < hsegvec.size() ; ++ ih ){
				datavec[ih*3+0] = hsegvec[ih].x0 ;
				datavec[ih*3+1] = hsegvec[ih].y ;
				datavec[ih*3+2] = hsegvec[ih].x1 ;
			}
			cout<<"write int "<<datavec.size()<<" as Bytes(KB) "<<datavec.size()*4/1024.0<<endl ;
			ofs.write( (char*)datavec.data() , datavec.size() * 4) ;
		}
	}

	ofs.close() ;

	return true ;
}


//瓦片是否与HSeg ROI有重叠区域,只判断第0级
bool WHsegTlvObject::isTileOverlay( int tilez,int tiley,int tilex)
{
    if( allLevelHsegs.size()==0 ){
        return false ;
    }
    if( allLevelHsegs[0].hsegs.size()==0 ){
        return false;
    }
    if( tilez==0 ) return true ;
    if( tilez < 0 ){
        return false;
    }

    int x0 = tilex * 256 ;
    int x1 = x0 + 256 ;//bugfixed 2022-3-6
    int y0 = tiley * 256 ;
    int y1 = y0 + 256 ;//bugfixed 2022-3-6

    for(int iz=0; iz< tilez; ++ iz )
    {
        x0 = x0/2 ;
        x1 = x1/2.0+0.5 ;//bugfixed
        y0 = y0/2 ;
        y1 = y1/2.0+0.5 ;//bugfixed
    }
    y0 = std::max(0,y0-1) ;
    y1 = std::min(127,y1+1) ;
    x0 = std::max(0,x0-1) ;
    x1 = std::min(255,x1+1) ;

    if( allLevelHsegs[0].hsegs[0].y > y1 ) return false ;
    if( allLevelHsegs[0].hsegs.back().y < y0 ) return false ;

    for(int ih = 0 ; ih < allLevelHsegs[0].hsegs.size() ; ++ ih )
    {
        if( allLevelHsegs[0].hsegs[ih].y >= y0 && allLevelHsegs[0].hsegs[ih].y < y1 )
        {
            if( allLevelHsegs[0].hsegs[ih].x0 > x1 || allLevelHsegs[0].hsegs[ih].x1 < x0 )
            {
                //tile outside hseg, skip , do nothing
            }else{
                return true ;//do overlay
            }
        }
    }
    return false;
}


//2022-3-23 计算hseg四角范围 只计算level0
bool WHsegTlvObject::computeExtent(double& left,double& right,double& top,double& bottom) 
{
	if( allLevelHsegs.size()==0 ){
        return false ;
    }
    if( allLevelHsegs[0].hsegs.size()==0 ){
        return false;
    }
    const double resoLevel0 = 360.0 / 256 ;
    int ytop = allLevelHsegs[0].hsegs[0].y ;
    int ybottom = allLevelHsegs[0].hsegs.back().y ;
    int xleft = 255 ;
    int xright = 0 ;
    for(int i = 0 ; i<allLevelHsegs[0].hsegs.size() ; ++ i )
    {
    	xleft  = std::min( xleft  ,allLevelHsegs[0].hsegs[i].x0 ) ;
    	xright = std::max( xright ,allLevelHsegs[0].hsegs[i].x1 ) ;
    }
    left = -180 + xleft * resoLevel0  ;
    right = -180 + xright * resoLevel0 + resoLevel0; 
    top = 90.0 - ytop * resoLevel0 ;
    bottom = 90.0 - ybottom * resoLevel0 - resoLevel0 ; 

    return true ;
}