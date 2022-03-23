/// Hseg tlv 数据对象
/// 2022-3-23 1059
///
#ifndef W_HSEG_GEOTIFF_WRITER_H
#define W_HSEG_GEOTIFF_WRITER_H

#include <vector>
#include "whsegline.h"
#include <string>
#include <cmath>
#include "wlevelhseg.h"

using std::string;
using std::vector;
using std::ofstream;


struct TLV{
	char tag[4];
	vector<unsigned char> bytes ;
	void print() ;
} ;


struct WHsegTlvObject {
	vector<wLevelHseg> allLevelHsegs ;
	bool readFromFile(string hsegtlvfile,string& error) ;
	//从内存数组读取对象内容
	bool readFromBinaryData(vector<unsigned char>& binarydata,string& error) ;
	bool writeToFile( string hsegtlvfile,string& error) ;

	//瓦片是否与HSeg ROI有重叠区域,只判断第0级
	bool isTileOverlay( int tilez,int tiley,int tilex) ;
	//2022-3-23 计算hseg四角范围 只计算level0
	bool computeExtent(double& left,double& right,double& top,double& bottom) ;

private:
	void readTLV(FILE* pf,TLV& r_tlv) ;
	//newoffset表示读取以后新的偏移值
	void readTLV(vector<unsigned char>& binarydata,int readoffset,TLV& r_tlv,int& newoffset) ;
} ;

#endif

