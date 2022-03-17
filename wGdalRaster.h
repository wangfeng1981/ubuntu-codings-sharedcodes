/// v1.10.0 之前没有版本信息，统一使用1.10开始计 2022-1-20
/// v1.11.0 增加save函数的无效值设置
/// v1.12.0 2022-3-12 增加 wGdalRasterFactory::Create(int xsize,int ysize,int nband, GDALDataType outtype);
/// v1.13.0 2022-3-17 增加输出压缩选项

#ifndef WGDALRASTER_H

#define WGDALRASTER_H

//use #define WGDALRASTER_H_IMPLEMENTATION for cpp file

#include "gdal_priv.h"
#include <string>
#include <vector>
#include <iostream>
using std::vector ;
using std::string;
using std::cout;
using std::endl;


enum wGdalRasterState
{
	wGdalRasterStateNone ,
	wGdalRasterStateOpen , 
	wGdalRasterStateCreate 
} ;

class wGdalRaster
{
public:
	const int getXSize() const ;
	const int getYSize() const ;
	int getNBand() ;

	virtual float getValuef(int ix,int iy,int ib )const =0;
	virtual float getValuef(int it ,int ib )const =0;
	virtual int getValuei(int ix,int iy,int ib )const =0 ;
	virtual int getValuei(int it , int ib  )const =0;

	virtual void setValuef(int ix,int iy,int ib,float val)=0 ;
	virtual void setValuei(int ix,int iy,int ib,int val) =0;
	virtual void setValuef(int it,int ib,float val) =0;
	virtual void setValuei(int it,int ib,int val) =0;

	virtual bool open(string filepath)=0 ;
	bool save(string filepath) ; 
	bool save(string filepath,double filldata) ;
    bool save(string filepath,double filldata,bool compress) ; 
	virtual bool create(int nxsize,int nysize,int nband )=0 ;
 
	virtual void fill(int iband,int fillval) =0;
    virtual GDALDataType getDataType() =0 ;

    // Double
    virtual double getValued(int it,int ib) const =0;
    virtual double getValued(int ix,int iy,int ib) const =0 ;
    virtual void   setValued(int ix,int iy,int ib,double val) =0 ;
    virtual void   setValued(int it , int ib, double val)  =0;

	wGdalRaster() ;
	wGdalRasterState getState() ;
	virtual ~wGdalRaster() ;

	void copyProj( const char* projstr ) ;
	void copyTrans(const double* trans ) ;
	char* getProj() ;
	const double* getTrans() const;
	inline double getNoDataValue() { return mNoDataValue; } //2022-1-20
	
protected:
	wGdalRasterState mState ;
	int mXSize , mYSize , mNBand ;
	char mProj[1024] ;
	double mTrans[6] ;
	double mNoDataValue ;//2022-1-20
	virtual bool save_pr(string filepath,bool usefilldata,double filldata,bool compress)=0 ;
} ;


////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//
//                                       BYTE
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////


class wGdalRasterByte:public wGdalRaster
{
public:
    virtual float getValuef(int ix,int iy,int ib ) const;
    virtual float getValuef(int it ,int ib )  const;
    virtual int getValuei(int ix,int iy,int ib )  const;
    virtual int getValuei(int it , int ib  )  const;

    virtual void setValuef(int ix,int iy,int ib,float val)  ;
    virtual void setValuei(int ix,int iy,int ib,int val)    ;
    virtual void setValuef(int it,int ib,float val)  ;
    virtual void setValuei(int it,int ib,int val) ;

    virtual bool open(string filepath)  ;
    virtual bool create(int nxsize,int nysize,int nband )  ;

    //new
    virtual void fill(int iband,int fillval) ;
    virtual inline GDALDataType getDataType() {return GDALDataType::GDT_Byte; }

    // Double
    virtual double getValued(int it,int ib) const ;
    virtual double getValued(int ix,int iy,int ib) const ;
    virtual void   setValued(int ix,int iy,int ib,double val) ;
    virtual void   setValued(int it , int ib, double val) ;


    void release() ;
    virtual ~wGdalRasterByte() ;
protected:
    vector<unsigned char*> mptrVec ;
    virtual bool save_pr(string filepath,bool usefilldata,double filldata,bool compress);
} ;


////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//
//                                       U16
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////
class wGdalRasterU16:public wGdalRaster
{
public:
    virtual float getValuef(int ix,int iy,int ib )  const;
    virtual float getValuef(int it ,int ib )   const;
    virtual int getValuei(int ix,int iy,int ib )  const;
    virtual int getValuei(int it , int ib  )   const;

    virtual void setValuef(int ix,int iy,int ib,float val)  ;
    virtual void setValuei(int ix,int iy,int ib,int val)    ;
    virtual void setValuef(int it,int ib,float val)  ;
    virtual void setValuei(int it,int ib,int val) ;

    virtual bool open(string filepath)  ;
    virtual bool create(int nxsize,int nysize,int nband )  ;
    void release() ;

    unsigned short getValueU16(int it,int ib)  const;
    unsigned short getValueU16(int ix,int iy,int ib)  const;

    //new
    virtual void fill(int iband,int fillval) ;
    virtual inline GDALDataType getDataType() {return GDALDataType::GDT_UInt16; }

    // Double
    virtual double getValued(int it,int ib) const ;
    virtual double getValued(int ix,int iy,int ib) const ;
    virtual void   setValued(int ix,int iy,int ib,double val) ;
    virtual void   setValued(int it , int ib, double val) ;

    virtual ~wGdalRasterU16() ;

protected:
    vector<unsigned short*> mptrVec ;
    virtual bool save_pr(string filepath,bool usefilldata,double filldata,bool compress);
} ;



////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//
//                                       I16
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////
class wGdalRasterI16:public wGdalRaster
{
public:
    virtual float getValuef(int ix,int iy,int ib ) const;
    virtual float getValuef(int it ,int ib )  const ;
    virtual int getValuei(int ix,int iy,int ib )  const ;
    virtual int getValuei(int it , int ib  )  const ;

    virtual void setValuef(int ix,int iy,int ib,float val)  ;
    virtual void setValuei(int ix,int iy,int ib,int val)    ;
    virtual void setValuef(int it,int ib,float val)  ;
    virtual void setValuei(int it,int ib,int val) ;

    virtual bool open(string filepath)  ;
    virtual bool create(int nxsize,int nysize,int nband )  ;

    //new
    virtual void fill(int iband,int fillval) ;
    virtual inline GDALDataType getDataType() {return GDALDataType::GDT_Int16; }

    // Double
    virtual double getValued(int it,int ib) const ;
    virtual double getValued(int ix,int iy,int ib) const ;
    virtual void   setValued(int ix,int iy,int ib,double val) ;
    virtual void   setValued(int it , int ib, double val) ;


    void release() ;
    virtual ~wGdalRasterI16() ;
protected:
    vector<short*> mptrVec ;
    virtual bool save_pr(string filepath,bool usefilldata,double filldata,bool compress);
} ;



////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//
//                                       I32
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////
class wGdalRasterI32:public wGdalRaster
{
public:
    virtual float getValuef(int ix,int iy,int ib ) const;
    virtual float getValuef(int it ,int ib )   const;
    virtual int getValuei(int ix,int iy,int ib )  const;
    virtual int getValuei(int it , int ib  )   const;

    virtual void setValuef(int ix,int iy,int ib,float val)  ;
    virtual void setValuei(int ix,int iy,int ib,int val)    ;
    virtual void setValuef(int it,int ib,float val)  ;
    virtual void setValuei(int it,int ib,int val) ;

    virtual bool open(string filepath)  ;
    virtual bool create(int nxsize,int nysize,int nband )  ;

    //new
    virtual void fill(int iband,int fillval) ;
    virtual inline GDALDataType getDataType() {return GDALDataType::GDT_Int32; }

    // Double
    virtual double getValued(int it,int ib) const ;
    virtual double getValued(int ix,int iy,int ib) const ;
    virtual void   setValued(int ix,int iy,int ib,double val) ;
    virtual void   setValued(int it , int ib, double val) ;


    void release() ;
    virtual ~wGdalRasterI32() ;
protected:
    vector<int*> mptrVec ;
    virtual bool save_pr(string filepath,bool usefilldata,double filldata,bool compress);
} ;


////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//
//                                       FLOAT
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////
class wGdalRasterFloat:public wGdalRaster
{
public:
    virtual float getValuef(int ix,int iy,int ib ) const;
    virtual float getValuef(int it ,int ib )   const;
    virtual int getValuei(int ix,int iy,int ib )  const;
    virtual int getValuei(int it , int ib  )  const;

    virtual void setValuef(int ix,int iy,int ib,float val)  ;
    virtual void setValuei(int ix,int iy,int ib,int val)    ;
    virtual void setValuef(int it,int ib,float val)  ;
    virtual void setValuei(int it,int ib,int val) ;

    virtual bool open(string filepath)  ;
    virtual bool create(int nxsize,int nysize,int nband )  ;

    //new
    virtual void fill(int iband,int fillval) ;
    virtual inline GDALDataType getDataType() {return GDALDataType::GDT_Float32; }

    // Double
    virtual double getValued(int it,int ib) const ;
    virtual double getValued(int ix,int iy,int ib) const ;
    virtual void   setValued(int ix,int iy,int ib,double val) ;
    virtual void   setValued(int it , int ib, double val) ;


    void release() ;
    virtual ~wGdalRasterFloat() ;
protected:
    vector<float*> mptrVec ;
    virtual bool save_pr(string filepath,bool usefilldata,double filldata,bool compress);
} ;




////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//
//                                       DOUBLE
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////
class wGdalRasterDouble:public wGdalRaster
{
public:
    virtual float getValuef(int ix,int iy,int ib ) const;
    virtual float getValuef(int it ,int ib )   const;
    virtual int getValuei(int ix,int iy,int ib )  const;
    virtual int getValuei(int it , int ib  )  const;

    virtual void setValuef(int ix,int iy,int ib,float val)  ;
    virtual void setValuei(int ix,int iy,int ib,int val)    ;
    virtual void setValuef(int it,int ib,float val)  ;
    virtual void setValuei(int it,int ib,int val) ;

    virtual bool open(string filepath)  ;
    virtual bool create(int nxsize,int nysize,int nband )  ;

    //new
    virtual void fill(int iband,int fillval) ;
    virtual inline GDALDataType getDataType() {return GDALDataType::GDT_Float64; }

    // Double
    virtual double getValued(int it,int ib) const ;
    virtual double getValued(int ix,int iy,int ib) const ;
    virtual void   setValued(int ix,int iy,int ib,double val) ;
    virtual void   setValued(int it , int ib, double val) ;


    void release() ;
    virtual ~wGdalRasterDouble() ;
protected:
    vector<double*> mptrVec ;
    virtual bool save_pr(string filepath,bool usefilldata,double filldata,bool compress);
} ;



////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//
//                                       uint32
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////
class wGdalRasterU32:public wGdalRaster
{
public:
    virtual float getValuef(int ix,int iy,int ib ) const;
    virtual float getValuef(int it ,int ib )   const;
    virtual int getValuei(int ix,int iy,int ib )  const;
    virtual int getValuei(int it , int ib  )  const;

    virtual void setValuef(int ix,int iy,int ib,float val)  ;
    virtual void setValuei(int ix,int iy,int ib,int val)    ;
    virtual void setValuef(int it,int ib,float val)  ;
    virtual void setValuei(int it,int ib,int val) ;

    virtual bool open(string filepath)  ;
    virtual bool create(int nxsize,int nysize,int nband )  ;

    //new
    virtual void fill(int iband,int fillval) ;
    virtual inline GDALDataType getDataType() {return GDALDataType::GDT_UInt32; }

    // Double
    virtual double getValued(int it,int ib) const ;
    virtual double getValued(int ix,int iy,int ib) const ;
    virtual void   setValued(int ix,int iy,int ib,double val) ;
    virtual void   setValued(int it , int ib, double val) ;


    void release() ;
    virtual ~wGdalRasterU32() ;
protected:
    vector<unsigned int*> mptrVec ;
    virtual bool save_pr(string filepath,bool usefilldata,double filldata,bool compress);
} ;



////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//
//
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////
class wGdalRasterFactory
{
public:
	//调用者负责维护指针
    static wGdalRaster* OpenFile(string filename) ;
	//2022-3-12 调用者负责维护指针
	static wGdalRaster* Create(int xsize,int ysize,int nband, GDALDataType outtype);

};

#endif // WGDALRASTER_H



#ifdef WGDALRASTER_H_IMPLEMENTATION

wGdalRaster::~wGdalRaster()
{
}

wGdalRaster::wGdalRaster()
{
	mNoDataValue = 0 ;
	mXSize = 0 ;
	mYSize = 0 ; 
	mNBand = 0 ;
	mProj[0]='\0' ;
	mTrans[0] = mTrans[1] = mTrans[2] = mTrans[3] = mTrans[4] = mTrans[5] = 0 ;
	mState = wGdalRasterStateNone ;
}

void wGdalRaster::copyProj(const char* projstr ) 
{
	strcpy( this->mProj , projstr ) ;
}
void  wGdalRaster::copyTrans(const double* trans ) 
{
	for(int i = 0 ; i<6 ; ++i ) mTrans[i] = trans[i] ;
}
char* wGdalRaster::getProj() 
{
	return mProj ;
}
const double* wGdalRaster::getTrans() const
{
	return mTrans ;
}

wGdalRasterState wGdalRaster::getState()
{
	return mState ;
} 
const int wGdalRaster::getXSize() const
{
	return mXSize ;
}

const int wGdalRaster::getYSize() const
{
	return mYSize ;
}

int wGdalRaster::getNBand()
{
	return mNBand ;
}

bool wGdalRaster::save(string filepath)  
{
	return save_pr(filepath,false,0      ,false); 
} 
bool wGdalRaster::save(string filepath,double filldata)
{
	return save_pr(filepath,true,filldata,false); 
}
bool wGdalRaster::save(string filepath,double filldata,bool compress)
{
    return save_pr(filepath,true,filldata,compress); 
}
 
//------------------------------------------------------------------------------------------------------





///////////////////////////////////////////////////////////////////////////////////////////////
/// \brief wGdalRasterByte::fill
/// \param iband
/// \param fillval
///
void wGdalRasterByte::fill( int iband , int fillval )
{
	if( this->mState == wGdalRasterStateOpen ||  this->mState == wGdalRasterStateCreate )
	{
		if( iband < this->mptrVec.size() )
		{
			unsigned char* bandPtr = (unsigned char*)this->mptrVec[iband] ;
			int asize = this->mXSize * this->mYSize ;
			for(int it = 0 ; it < asize ; ++ it )
			{
				bandPtr[it] = fillval ;
			}
		}else
		{
			cout<<"wGdalRaster::fill error 1."<<endl ;
		}
	}else
	{
		cout<<"wGdalRaster::fill error 2."<<endl ;
	}
}

wGdalRasterByte::~wGdalRasterByte()
{
	this->release() ;
}
void wGdalRasterByte::release()
{
	cout<<"release byte"<<endl ;
	this->mState = wGdalRasterStateNone ;
	for(int i = 0 ; i<mptrVec.size() ; ++ i )
	{
		if( mptrVec[i] )
		{
			delete[] mptrVec[i] ;
			mptrVec[i] = 0 ;
		}
	}
}
float wGdalRasterByte::getValuef(int ix,int iy,int ib ) const
{
	unsigned char* ptr = mptrVec[ib] ;
	return (float)( ptr[ix+iy*mXSize] ) ;
}
float wGdalRasterByte::getValuef(int it ,int ib ) const
{
	unsigned char* ptr = mptrVec[ib] ;
	return (float)( ptr[it] ) ;
}
int wGdalRasterByte::getValuei(int ix,int iy,int ib ) const
{
	unsigned char* ptr = mptrVec[ib] ;
	return (int)( ptr[ix+iy*mXSize] ) ;
}
int wGdalRasterByte::getValuei(int it , int ib  ) const
{
	unsigned char* ptr = mptrVec[ib] ;
	return (int)( ptr[it] ) ;
}
void wGdalRasterByte::setValuef(int ix,int iy,int ib,float val)  
{
	unsigned char* ptr = mptrVec[ib] ;
	ptr[ix+iy*mXSize] = (int)val ;
}
void wGdalRasterByte::setValuei(int ix,int iy,int ib,int val)    
{
	unsigned char* ptr = mptrVec[ib] ;
	ptr[ix+iy*mXSize] = (int)val ;
}
void wGdalRasterByte::setValuef(int it,int ib,float val)  
{
	unsigned char* ptr = mptrVec[ib] ;
	ptr[it] = (int)val ;
}
void wGdalRasterByte::setValuei(int it,int ib,int val) 
{
	unsigned char* ptr = mptrVec[ib] ;
	ptr[it] = (int)val ;
}

bool wGdalRasterByte::open(string filepath) 
{
	if( this->mState != wGdalRasterStateNone)
	{
		return false ;
	}
	GDALDataset* ds = (GDALDataset*)GDALOpen( filepath.c_str() , GA_ReadOnly ) ;
	if( ds==0 )
	{
		return false ;
	}

	strcpy( mProj , ds->GetProjectionRef() ) ;
	ds->GetGeoTransform( mTrans ) ;
	
	mXSize = ds->GetRasterXSize() ;
	mYSize = ds->GetRasterYSize() ;
	mNBand = ds->GetRasterCount() ;
	if( mNBand>0 ){//2022-1-20
		mNoDataValue = ds->GetRasterBand(1)->GetNoDataValue() ;
	}

	for(int i = 0 ; i<mNBand ; ++ i )
	{
		unsigned char* ptr = new unsigned char[mXSize*mYSize] ;
		ds->GetRasterBand(i+1)->RasterIO( GF_Read ,
			0,0,mXSize,mYSize,
			ptr , 
			mXSize,mYSize,GDT_Byte , 
			0,0,0) ;
		mptrVec.push_back(ptr) ;
	}
	GDALClose(ds) ;
	this->mState = wGdalRasterStateOpen ;
	return true ;
}

bool wGdalRasterByte::save_pr(string filepath,bool usefilldata,double filldata,bool compress) 
{
	if( this->mState == wGdalRasterStateNone)
	{
		return false   ;
	}
	string last3char = "" ;
	if( filepath.length() > 5 )
	{
		last3char = filepath.substr( filepath.length() - 3 , 3 ) ;
	}

	GDALDriver* driver = 0;
	if( last3char == "png" || last3char=="PNG" )
	{
		driver = GetGDALDriverManager()->GetDriverByName("MEM");
	}else
	{
		driver = GetGDALDriverManager()->GetDriverByName("GTiff");
	}

    CPLStringList opt ;
    if( compress==true ) opt.SetNameValue("COMPRESS" , "Deflate") ;

	GDALDataset* ds = driver->Create( filepath.c_str() , mXSize, mYSize , mNBand,GDT_Byte,opt.List()) ;
	if( ds==0 )
	{
		return false  ;
	}
	for(int i = 0 ; i<mNBand ; ++ i )
	{
		unsigned char* ptr = mptrVec[i] ;
		ds->GetRasterBand(i+1)->RasterIO( GF_Write,
			0,0,mXSize,mYSize,
			ptr , 
			mXSize,mYSize,GDT_Byte , 
			0,0,0) ;
		if( usefilldata ) ds->GetRasterBand(i+1)->SetNoDataValue(filldata);
	}
	if( strlen( mProj ) > 1 && mTrans[1] > 0 )
	{
		ds->SetProjection( mProj ) ;
		ds->SetGeoTransform( mTrans ) ;
	}
	

	if( last3char == "png" || last3char=="PNG" )
	{
		GDALDriver* driverpng = GetGDALDriverManager()->GetDriverByName("PNG");
		GDALDataset* dspng = driverpng->CreateCopy( filepath.c_str() , ds , 0 , 0 , 0 , 0 ) ;
		GDALClose(dspng) ;
	}

	GDALClose(ds) ;
	return true ;
}
bool wGdalRasterByte::create(int nxsize,int nysize,int nband ) 
{
	if( this->mState != wGdalRasterStateNone)
	{
		return false ;
	}
	mXSize = nxsize ;
	mYSize = nysize ;
	mNBand = nband ;
	for(int i = 0 ; i<mNBand ; ++ i )
	{
		unsigned char* ptr = new unsigned char[mXSize*mYSize] ;
		memset(ptr , 0 , mXSize*mYSize ) ;
		mptrVec.push_back(ptr) ;
	}
	this->mState = wGdalRasterStateCreate ;
	return true ;
}
double wGdalRasterByte::getValued(int it,int ib) const
{
    unsigned char* ptr = mptrVec[ib] ;
    return ptr[it] ;
}
double wGdalRasterByte::getValued(int ix,int iy,int ib) const
{
    unsigned char* ptr = mptrVec[ib] ;
    return  ptr[ix+iy*mXSize]  ;
}

void   wGdalRasterByte::setValued(int ix,int iy,int ib,double val)
{
    unsigned char* ptr = mptrVec[ib] ;
    ptr[ix+iy*mXSize] = val ;
}
void   wGdalRasterByte::setValued(int it , int ib, double val)
{
    unsigned char* ptr = mptrVec[ib] ;
    ptr[it] = val ;
}



////////////////////////////////////////////////////////////////////////////////////////////
/// \brief wGdalRasterFloat::fill
/// \param iband
/// \param fillval
///
void wGdalRasterFloat::fill( int iband , int fillval )
{
	if( this->mState == wGdalRasterStateOpen ||  this->mState == wGdalRasterStateCreate )
	{
		if( iband < this->mptrVec.size() )
		{
			float* bandPtr = (float*)this->mptrVec[iband] ;
			int asize = this->mXSize * this->mYSize ;
			for(int it = 0 ; it < asize ; ++ it )
			{
				bandPtr[it] = fillval ;
			}
		}else
		{
			cout<<"wGdalRaster::fill error 1."<<endl ;
		}
	}else
	{
		cout<<"wGdalRaster::fill error 2."<<endl ;
	}
}

wGdalRasterFloat::~wGdalRasterFloat() 
{
	this->release() ;
}

void wGdalRasterFloat::release()
{
	cout<<"release float"<<endl ;
	this->mState = wGdalRasterStateNone ;
	for(int i = 0 ; i<mptrVec.size() ; ++ i )
	{
		if( mptrVec[i] )
		{
			delete[] mptrVec[i] ;
			mptrVec[i] = 0 ;
		}
	}
}
float wGdalRasterFloat::getValuef(int ix,int iy,int ib )  const
{
	float* ptr = mptrVec[ib] ;
	return   ptr[ix+iy*mXSize]  ;
}
float wGdalRasterFloat::getValuef(int it ,int ib )  const
{
	float* ptr = mptrVec[ib] ;
	return   ptr[it]  ;
}
int wGdalRasterFloat::getValuei(int ix,int iy,int ib )  const
{
	float* ptr = mptrVec[ib] ;
	return (int)( ptr[ix+iy*mXSize] ) ;
}
int wGdalRasterFloat::getValuei(int it , int ib  )  const
{
	float* ptr = mptrVec[ib] ;
	return (int)( ptr[it] ) ;
}
void wGdalRasterFloat::setValuef(int ix,int iy,int ib,float val)  
{
	float* ptr = mptrVec[ib] ;
	ptr[ix+iy*mXSize] = val ;
}
void wGdalRasterFloat::setValuei(int ix,int iy,int ib,int val)    
{
	float* ptr = mptrVec[ib] ;
	ptr[ix+iy*mXSize] = val ;
}
void wGdalRasterFloat::setValuef(int it,int ib,float val)  
{
	float* ptr = mptrVec[ib] ;
	ptr[it] = val ;
}
void wGdalRasterFloat::setValuei(int it,int ib,int val) 
{
	float* ptr = mptrVec[ib] ;
	ptr[it] = val ;
}

bool wGdalRasterFloat::open(string filepath) 
{
	if( this->mState != wGdalRasterStateNone)
	{
		return false ;
	}
	GDALDataset* ds = (GDALDataset*)GDALOpen( filepath.c_str() , GA_ReadOnly ) ;
	if( ds==0 )
	{
		return false ;
	}

	strcpy( mProj , ds->GetProjectionRef() ) ;
	ds->GetGeoTransform( mTrans ) ;

	mXSize = ds->GetRasterXSize() ;
	mYSize = ds->GetRasterYSize() ;
	mNBand = ds->GetRasterCount() ;
	if( mNBand>0 ){//2022-1-20
		mNoDataValue = ds->GetRasterBand(1)->GetNoDataValue() ;
	}

	for(int i = 0 ; i<mNBand ; ++ i )
	{
		float* ptr = new float[mXSize*mYSize] ;
		ds->GetRasterBand(i+1)->RasterIO( GF_Read ,
			0,0,mXSize,mYSize,
			ptr , 
			mXSize,mYSize,GDT_Float32 , 
			0,0,0) ;
		mptrVec.push_back(ptr) ;
	}
	GDALClose(ds) ;
	this->mState = wGdalRasterStateOpen ;
	return true ;
}
bool wGdalRasterFloat::save_pr(string filepath,bool usefilldata,double filldata,bool compress) 
{
	if( this->mState == wGdalRasterStateNone)
	{
		return false   ;
	}
	GDALDriver* driver = GetGDALDriverManager()->GetDriverByName("GTiff");

    CPLStringList opt ;
    if( compress==true ) opt.SetNameValue("COMPRESS" , "Deflate") ;

	GDALDataset* ds = driver->Create( filepath.c_str() , mXSize, mYSize , mNBand,GDT_Float32 ,opt.List()) ;
	if( ds==0 )
	{
		return false  ;
	}
	for(int i = 0 ; i<mNBand ; ++ i )
	{
		float* ptr = mptrVec[i] ;
		ds->GetRasterBand(i+1)->RasterIO( GF_Write,
			0,0,mXSize,mYSize,
			ptr , 
			mXSize,mYSize,GDT_Float32 , 
			0,0,0) ;
		if( usefilldata ) ds->GetRasterBand(i+1)->SetNoDataValue(filldata);
	}
	if( strlen( mProj ) > 1 && mTrans[1] > 0 )
	{
		ds->SetProjection( mProj ) ;
		ds->SetGeoTransform( mTrans ) ;
	}
	GDALClose(ds) ;
	return true ;
}
bool wGdalRasterFloat::create(int nxsize,int nysize,int nband ) 
{
	if( this->mState != wGdalRasterStateNone)
	{
		return false ;
	}
	mXSize = nxsize ;
	mYSize = nysize ;
	mNBand = nband ;
	int asize = mXSize*mYSize ;
	for(int i = 0 ; i<mNBand ; ++ i )
	{
		float* ptr = new float[mXSize*mYSize] ;
		for(int it = 0 ; it<asize;++it) ptr[it] = 0.f ;
		mptrVec.push_back(ptr) ;
	}
	this->mState = wGdalRasterStateCreate ;
	return true ;
}
double wGdalRasterFloat::getValued(int it,int ib) const
{
    float* ptr = mptrVec[ib] ;
    return ptr[it] ;
}
double wGdalRasterFloat::getValued(int ix,int iy,int ib) const
{
    float* ptr = mptrVec[ib] ;
    return  ptr[ix+iy*mXSize]  ;
}

void   wGdalRasterFloat::setValued(int ix,int iy,int ib,double val)
{
    float* ptr = mptrVec[ib] ;
    ptr[ix+iy*mXSize] = val ;
}
void   wGdalRasterFloat::setValued(int it , int ib, double val)
{
    float* ptr = mptrVec[ib] ;
    ptr[it] = val ;
}









///////////////////////////////////////////////////////////////////////////////////////////////
/// \brief wGdalRasterU16::fill
/// \param iband
/// \param fillval
///
void wGdalRasterU16::fill( int iband , int fillval )
{
	if( this->mState == wGdalRasterStateOpen ||  this->mState == wGdalRasterStateCreate )
	{
		if( iband < this->mptrVec.size() )
		{
			unsigned short* bandPtr = (unsigned short*)this->mptrVec[iband] ;
			int asize = this->mXSize * this->mYSize ;
			for(int it = 0 ; it < asize ; ++ it )
			{
				bandPtr[it] = fillval ;
			}
		}else
		{
			cout<<"wGdalRaster::fill error 1."<<endl ;
		}
	}else
	{
		cout<<"wGdalRaster::fill error 2."<<endl ;
	}
}

wGdalRasterU16::~wGdalRasterU16() 
{
	this->release() ;
}

void wGdalRasterU16::release()
{
	cout<<"release u16"<<endl ;
	this->mState = wGdalRasterStateNone ;
	for(int i = 0 ; i<mptrVec.size() ; ++ i )
	{
		if( mptrVec[i] )
		{
			delete[] mptrVec[i] ;
			mptrVec[i] = 0 ;
		}
	}
}
unsigned short wGdalRasterU16::getValueU16(int ix,int iy,int ib)  const
{
	unsigned short* ptr = mptrVec[ib] ;
	return   ptr[ix+iy*mXSize]  ;
}

unsigned short wGdalRasterU16::getValueU16(int it,int ib)  const
{
	unsigned short* ptr = mptrVec[ib] ;
	return   ptr[it]  ;
}


float wGdalRasterU16::getValuef(int ix,int iy,int ib )  const
{
	unsigned short* ptr = mptrVec[ib] ;
	return  (float) ptr[ix+iy*mXSize]  ;
}
float wGdalRasterU16::getValuef(int it ,int ib )  const
{
	unsigned short* ptr = mptrVec[ib] ;
	return  (float)ptr[it]  ;
}
int wGdalRasterU16::getValuei(int ix,int iy,int ib )  const
{
	unsigned short* ptr = mptrVec[ib] ;
	return (int)( ptr[ix+iy*mXSize] ) ;
}
int wGdalRasterU16::getValuei(int it , int ib  )  const
{
	unsigned short* ptr = mptrVec[ib] ;
	return (int)( ptr[it] ) ;
}
void wGdalRasterU16::setValuef(int ix,int iy,int ib,float val)  
{
	unsigned short*ptr = mptrVec[ib] ;
	ptr[ix+iy*mXSize] = val ;
}
void wGdalRasterU16::setValuei(int ix,int iy,int ib,int val)    
{
	unsigned short* ptr = mptrVec[ib] ;
	ptr[ix+iy*mXSize] = val ;
}
void wGdalRasterU16::setValuef(int it,int ib,float val)  
{
	unsigned short* ptr = mptrVec[ib] ;
	ptr[it] = val ;
}
void wGdalRasterU16::setValuei(int it,int ib,int val) 
{
	unsigned short* ptr = mptrVec[ib] ;
	ptr[it] = val ;
}

bool wGdalRasterU16::open(string filepath) 
{
	if( this->mState != wGdalRasterStateNone)
	{
		return false ;
	}
	GDALDataset* ds = (GDALDataset*)GDALOpen( filepath.c_str() , GA_ReadOnly ) ;
	if( ds==0 )
	{
		return false ;
	}

	strcpy( mProj , ds->GetProjectionRef() ) ;
	ds->GetGeoTransform( mTrans ) ;

	mXSize = ds->GetRasterXSize() ;
	mYSize = ds->GetRasterYSize() ;
	mNBand = ds->GetRasterCount() ;
	if( mNBand>0 ){//2022-1-20
		mNoDataValue = ds->GetRasterBand(1)->GetNoDataValue() ;
	}

	for(int i = 0 ; i<mNBand ; ++ i )
	{
		unsigned short* ptr = new unsigned short[mXSize*mYSize] ;
		ds->GetRasterBand(i+1)->RasterIO( GF_Read ,
			0,0,mXSize,mYSize,
			ptr , 
			mXSize,mYSize,GDT_UInt16 , 
			0,0,0) ;
		mptrVec.push_back(ptr) ;
	}
	GDALClose(ds) ;
	this->mState = wGdalRasterStateOpen ;
	return true ;
}
bool wGdalRasterU16::save_pr(string filepath,bool usefilldata,double filldata,bool compress) 
{
	if( this->mState == wGdalRasterStateNone)
	{
		return false   ;
	}
	GDALDriver* driver = GetGDALDriverManager()->GetDriverByName("GTiff");

    CPLStringList opt ;
    if( compress==true ) opt.SetNameValue("COMPRESS" , "Deflate") ;

	GDALDataset* ds = driver->Create( filepath.c_str() , mXSize, mYSize , mNBand,GDT_UInt16 ,opt.List()) ;
	if( ds==0 )
	{
		return false  ;
	}
	for(int i = 0 ; i<mNBand ; ++ i )
	{
		unsigned short* ptr = mptrVec[i] ;
		ds->GetRasterBand(i+1)->RasterIO( GF_Write,
			0,0,mXSize,mYSize,
			ptr , 
			mXSize,mYSize,GDT_UInt16 , 
			0,0,0) ;
		if( usefilldata ) ds->GetRasterBand(i+1)->SetNoDataValue(filldata);
	}
	if( strlen( mProj ) > 1 && mTrans[1] > 0 )
	{
		ds->SetProjection( mProj ) ;
		ds->SetGeoTransform( mTrans ) ;
	}
	GDALClose(ds) ;
	return true ;
}
bool wGdalRasterU16::create(int nxsize,int nysize,int nband ) 
{
	if( this->mState != wGdalRasterStateNone)
	{
		return false ;
	}
	mXSize = nxsize ;
	mYSize = nysize ;
	mNBand = nband ;
	int asize = mXSize*mYSize ;
	for(int i = 0 ; i<mNBand ; ++ i )
	{
		unsigned short* ptr = new unsigned short[mXSize*mYSize] ;
		for(int it = 0 ; it<asize;++it) ptr[it] = 0.f ;
		mptrVec.push_back(ptr) ;
	}
	this->mState = wGdalRasterStateCreate ;
	return true ;
}
double wGdalRasterU16::getValued(int it,int ib) const
{
    unsigned short* ptr = mptrVec[ib] ;
    return ptr[it] ;
}
double wGdalRasterU16::getValued(int ix,int iy,int ib) const
{
    unsigned short* ptr = mptrVec[ib] ;
    return  ptr[ix+iy*mXSize]  ;
}

void   wGdalRasterU16::setValued(int ix,int iy,int ib,double val)
{
    unsigned short* ptr = mptrVec[ib] ;
    ptr[ix+iy*mXSize] = val ;
}
void   wGdalRasterU16::setValued(int it , int ib, double val)
{
    unsigned short* ptr = mptrVec[ib] ;
    ptr[it] = val ;
}








///////////////////////////////////////////////////////////////////////////
/// \brief wGdalRasterI16::fill
/// \param iband
/// \param fillval
///
void wGdalRasterI16::fill( int iband , int fillval )
{
	if( this->mState == wGdalRasterStateOpen ||  this->mState == wGdalRasterStateCreate )
	{
		if( iband < this->mptrVec.size() )
		{
			short* bandPtr = (short*)this->mptrVec[iband] ;
			int asize = this->mXSize * this->mYSize ;
			for(int it = 0 ; it < asize ; ++ it )
			{
				bandPtr[it] = fillval ;
			}
		}else
		{
			cout<<"wGdalRaster::fill error 1."<<endl ;
		}
	}else
	{
		cout<<"wGdalRaster::fill error 2."<<endl ;
	}
}


wGdalRasterI16::~wGdalRasterI16() 
{
	this->release() ;
}


void wGdalRasterI16::release()
{
	cout<<"release i16"<<endl ;
	this->mState = wGdalRasterStateNone ;
	for(int i = 0 ; i<mptrVec.size() ; ++ i )
	{
		if( mptrVec[i] )
		{
			delete[] mptrVec[i] ;
			mptrVec[i] = 0 ;
		}
	}
}
float wGdalRasterI16::getValuef(int ix,int iy,int ib ) const 
{
	short* ptr = mptrVec[ib] ;
	return  (float) ptr[ix+iy*mXSize]  ;
}
float wGdalRasterI16::getValuef(int it ,int ib ) const
{
	short* ptr = mptrVec[ib] ;
	return  (float)ptr[it]  ;
}
int wGdalRasterI16::getValuei(int ix,int iy,int ib ) const
{
	short* ptr = mptrVec[ib] ;
	return (int)( ptr[ix+iy*mXSize] ) ;
}
int wGdalRasterI16::getValuei(int it , int ib  ) const
{
	short* ptr = mptrVec[ib] ;
	return (int)( ptr[it] ) ;
}
void wGdalRasterI16::setValuef(int ix,int iy,int ib,float val)  
{
	short*ptr = mptrVec[ib] ;
	ptr[ix+iy*mXSize] = val ;
}
void wGdalRasterI16::setValuei(int ix,int iy,int ib,int val)    
{
	short* ptr = mptrVec[ib] ;
	ptr[ix+iy*mXSize] = val ;
}
void wGdalRasterI16::setValuef(int it,int ib,float val)  
{
	short* ptr = mptrVec[ib] ;
	ptr[it] = val ;
}
void wGdalRasterI16::setValuei(int it,int ib,int val) 
{
	short* ptr = mptrVec[ib] ;
	ptr[it] = val ;
}

bool wGdalRasterI16::open(string filepath) 
{
	if( this->mState != wGdalRasterStateNone)
	{
		return false ;
	}
	GDALDataset* ds = (GDALDataset*)GDALOpen( filepath.c_str() , GA_ReadOnly ) ;
	if( ds==0 )
	{
		return false ;
	}

	strcpy( mProj , ds->GetProjectionRef() ) ;
	ds->GetGeoTransform( mTrans ) ;

	mXSize = ds->GetRasterXSize() ;
	mYSize = ds->GetRasterYSize() ;
	mNBand = ds->GetRasterCount() ;
	if( mNBand>0 ){//2022-1-20
		mNoDataValue = ds->GetRasterBand(1)->GetNoDataValue() ;
	}

	for(int i = 0 ; i<mNBand ; ++ i )
	{
		short* ptr = new short[mXSize*mYSize] ;
		ds->GetRasterBand(i+1)->RasterIO( GF_Read ,
			0,0,mXSize,mYSize,
			ptr , 
			mXSize,mYSize,GDT_Int16 , 
			0,0,0) ;
		mptrVec.push_back(ptr) ;
	}
	GDALClose(ds) ;
	this->mState = wGdalRasterStateOpen ;
	return true ;
}
bool wGdalRasterI16::save_pr(string filepath,bool usefilldata,double filldata,bool compress) 
{
	if( this->mState == wGdalRasterStateNone)
	{
		return false   ;
	}
	GDALDriver* driver = GetGDALDriverManager()->GetDriverByName("GTiff");

    CPLStringList opt ;
    if( compress==true ) opt.SetNameValue("COMPRESS" , "Deflate") ;

	GDALDataset* ds = driver->Create( filepath.c_str() , mXSize, mYSize , mNBand,GDT_Int16 ,opt.List()) ;
	if( ds==0 )
	{
		return false  ;
	}
	for(int i = 0 ; i<mNBand ; ++ i )
	{
		short* ptr = mptrVec[i] ;
		ds->GetRasterBand(i+1)->RasterIO( GF_Write,
			0,0,mXSize,mYSize,
			ptr , 
			mXSize,mYSize,GDT_Int16 , 
			0,0,0) ;
		if( usefilldata ) ds->GetRasterBand(i+1)->SetNoDataValue(filldata);
	}
	if( strlen( mProj ) > 1 && mTrans[1] > 0 )
	{
		ds->SetProjection( mProj ) ;
		ds->SetGeoTransform( mTrans ) ;
	}
	GDALClose(ds) ;
	return true ;
}
bool wGdalRasterI16::create(int nxsize,int nysize,int nband ) 
{
	if( this->mState != wGdalRasterStateNone)
	{
		return false ;
	}
	mXSize = nxsize ;
	mYSize = nysize ;
	mNBand = nband ;
	int asize = mXSize*mYSize ;
	for(int i = 0 ; i<mNBand ; ++ i )
	{
		short* ptr = new short[mXSize*mYSize] ;
		memset(ptr , 0 , sizeof(short)*mXSize*mYSize ) ;
		mptrVec.push_back(ptr) ;
	}
	this->mState = wGdalRasterStateCreate ;
	return true ;
}
double wGdalRasterI16::getValued(int it,int ib) const
{
    short* ptr = mptrVec[ib] ;
    return ptr[it] ;
}
double wGdalRasterI16::getValued(int ix,int iy,int ib) const
{
    short* ptr = mptrVec[ib] ;
    return  ptr[ix+iy*mXSize]  ;
}

void   wGdalRasterI16::setValued(int ix,int iy,int ib,double val)
{
    short* ptr = mptrVec[ib] ;
    ptr[ix+iy*mXSize] = val ;
}
void   wGdalRasterI16::setValued(int it , int ib, double val)
{
    short* ptr = mptrVec[ib] ;
    ptr[it] = val ;
}





///////////////////////////////////////////////////////////////////////////////////////////
/// \brief wGdalRasterI32::fill
/// \param iband
/// \param fillval
///
///
void wGdalRasterI32::fill( int iband , int fillval )
{
	if( this->mState == wGdalRasterStateOpen ||  this->mState == wGdalRasterStateCreate )
	{
		if( iband < this->mptrVec.size() )
		{
			int* bandPtr = (int*)this->mptrVec[iband] ;
			int asize = this->mXSize * this->mYSize ;
			for(int it = 0 ; it < asize ; ++ it )
			{
				bandPtr[it] = fillval ;
			}
		}else
		{
			cout<<"wGdalRaster::fill error 1."<<endl ;
		}
	}else
	{
		cout<<"wGdalRaster::fill error 2."<<endl ;
	}
}


wGdalRasterI32::~wGdalRasterI32() 
{
	this->release() ;
}

void wGdalRasterI32::release()
{
	cout<<"release i32"<<endl ;
	this->mState = wGdalRasterStateNone ;
	for(int i = 0 ; i<mptrVec.size() ; ++ i )
	{
		if( mptrVec[i] )
		{
			delete[] mptrVec[i] ;
			mptrVec[i] = 0 ;
		}
	}
}
float wGdalRasterI32::getValuef(int ix,int iy,int ib )  const
{
	int* ptr = mptrVec[ib] ;
	return  (float) ptr[ix+iy*mXSize]  ;
}
float wGdalRasterI32::getValuef(int it ,int ib )  const
{
	int* ptr = mptrVec[ib] ;
	return  (float)ptr[it]  ;
}
int wGdalRasterI32::getValuei(int ix,int iy,int ib )  const
{
	int* ptr = mptrVec[ib] ;
	return  ptr[ix+iy*mXSize]   ;
}
int wGdalRasterI32::getValuei(int it , int ib  )  const
{
	int* ptr = mptrVec[ib] ;
	return   ptr[it]  ;
}
void wGdalRasterI32::setValuef(int ix,int iy,int ib,float val)  
{
	int*ptr = mptrVec[ib] ;
	ptr[ix+iy*mXSize] = val ;
}
void wGdalRasterI32::setValuei(int ix,int iy,int ib,int val)    
{
	int* ptr = mptrVec[ib] ;
	ptr[ix+iy*mXSize] = val ;
}
void wGdalRasterI32::setValuef(int it,int ib,float val)  
{
	int* ptr = mptrVec[ib] ;
	ptr[it] = val ;
}
void wGdalRasterI32::setValuei(int it,int ib,int val) 
{
	int* ptr = mptrVec[ib] ;
	ptr[it] = val ;
}

bool wGdalRasterI32::open(string filepath) 
{
	if( this->mState != wGdalRasterStateNone)
	{
		return false ;
	}
	GDALDataset* ds = (GDALDataset*)GDALOpen( filepath.c_str() , GA_ReadOnly ) ;
	if( ds==0 )
	{
		return false ;
	}

	strcpy( mProj , ds->GetProjectionRef() ) ;
	ds->GetGeoTransform( mTrans ) ;

	mXSize = ds->GetRasterXSize() ;
	mYSize = ds->GetRasterYSize() ;
	mNBand = ds->GetRasterCount() ;
	if( mNBand>0 ){//2022-1-20
		mNoDataValue = ds->GetRasterBand(1)->GetNoDataValue() ;
	}

	for(int i = 0 ; i<mNBand ; ++ i )
	{
		int* ptr = new int[mXSize*mYSize] ;
		ds->GetRasterBand(i+1)->RasterIO( GF_Read ,
			0,0,mXSize,mYSize,
			ptr , 
			mXSize,mYSize,GDT_Int32 , 
			0,0,0) ;
		mptrVec.push_back(ptr) ;
	}
	GDALClose(ds) ;
	this->mState = wGdalRasterStateOpen ;
	return true ;
}
bool wGdalRasterI32::save_pr(string filepath,bool usefilldata,double filldata,bool compress) 
{
	if( this->mState == wGdalRasterStateNone)
	{
		return false   ;
	}
	GDALDriver* driver = GetGDALDriverManager()->GetDriverByName("GTiff");

    CPLStringList opt ;
    if( compress==true ) opt.SetNameValue("COMPRESS" , "Deflate") ;

	GDALDataset* ds = driver->Create( filepath.c_str() , mXSize, mYSize , mNBand,GDT_Int32 ,opt.List()) ;
	if( ds==0 )
	{
		return false  ;
	}
	for(int i = 0 ; i<mNBand ; ++ i )
	{
		int* ptr = mptrVec[i] ;
		ds->GetRasterBand(i+1)->RasterIO( GF_Write,
			0,0,mXSize,mYSize,
			ptr , 
			mXSize,mYSize,GDT_Int32 , 
			0,0,0) ;
		if( usefilldata ) ds->GetRasterBand(i+1)->SetNoDataValue(filldata);
	}
	if( strlen( mProj ) > 1 && mTrans[1] > 0 )
	{
		ds->SetProjection( mProj ) ;
		ds->SetGeoTransform( mTrans ) ;
	}
	GDALClose(ds) ;
	return true ;
}
bool wGdalRasterI32::create(int nxsize,int nysize,int nband ) 
{
	if( this->mState != wGdalRasterStateNone)
	{
		return false ;
	}
	mXSize = nxsize ;
	mYSize = nysize ;
	mNBand = nband ;
	int asize = mXSize*mYSize ;
	for(int i = 0 ; i<mNBand ; ++ i )
	{
		int* ptr = new int[mXSize*mYSize] ;
		memset(ptr,0,sizeof(int)*mXSize*mYSize) ;
		mptrVec.push_back(ptr) ;
	}
	this->mState = wGdalRasterStateCreate ;
	return true ;
}

double wGdalRasterI32::getValued(int it,int ib) const
{
    int* ptr = mptrVec[ib] ;
    return ptr[it] ;
}
double wGdalRasterI32::getValued(int ix,int iy,int ib) const
{
    int* ptr = mptrVec[ib] ;
    return  ptr[ix+iy*mXSize]  ;
}

void   wGdalRasterI32::setValued(int ix,int iy,int ib,double val)
{
    int* ptr = mptrVec[ib] ;
    ptr[ix+iy*mXSize] = val ;
}
void   wGdalRasterI32::setValued(int it , int ib, double val)
{
    int* ptr = mptrVec[ib] ;
    ptr[it] = val ;
}




/////////////////////////////////////////////////////////////////////////////////////////////////////
/// \brief wGdalRasterFactory::OpenFile
/// \param filename
/// \return
//

wGdalRaster* wGdalRasterFactory::OpenFile(string filename)
{
    GDALDataset* ds = (GDALDataset*)GDALOpen(filename.c_str(),GA_ReadOnly) ;
    if(ds==0) return 0 ;
    GDALDataType dataType = ds->GetRasterBand(1)->GetRasterDataType() ;
    GDALClose(ds) ;
    ds = 0 ;

    if( dataType==GDT_Byte ){
        wGdalRasterByte* raster = new wGdalRasterByte() ;
        if( raster==0 ) return 0 ;
        bool ok = raster->open(filename) ;
        if( ok ){
            return raster ;
        }else{
            return 0 ;
        }
    }
    else if( dataType==GDT_UInt16){
        wGdalRasterU16* raster = new wGdalRasterU16() ;
        if( raster==0 ) return 0 ;
        bool ok = raster->open(filename) ;
        if( ok ){
            return raster ;
        }else{
            return 0 ;
        }

    }else if( dataType==GDT_Int16 )
    {
        wGdalRasterI16* raster = new wGdalRasterI16() ;
        if( raster==0 ) return 0 ;
        bool ok = raster->open(filename) ;
        if( ok ){
            return raster ;
        }else{
            return 0 ;
        }
    }
    else if( dataType==GDT_UInt32 )
    {
        wGdalRasterU32* raster = new wGdalRasterU32() ;//2022-1-9
        if( raster==0 ) return 0 ;
        bool ok = raster->open(filename) ;
        if( ok ){
            return raster ;
        }else{
            return 0 ;
        }
    }
    else if( dataType==GDT_Int32)
    {
        wGdalRasterI32* raster = new wGdalRasterI32() ;
        if( raster==0 ) return 0 ;
        bool ok = raster->open(filename) ;
        if( ok ){
            return raster ;
        }else{
            return 0 ;
        }

    }
    else if( dataType==GDT_Float32 )
    {
        wGdalRasterFloat* raster = new wGdalRasterFloat() ;
        if( raster==0 ) return 0 ;
        bool ok = raster->open(filename) ;
        if( ok ){
            return raster ;
        }else{
            return 0 ;
        }
    }
    else if( dataType==GDT_Float64 )
    {
        wGdalRasterDouble* raster = new wGdalRasterDouble() ;
        if( raster==0 ) return 0 ;
        bool ok = raster->open(filename) ;
        if( ok ){
            return raster ;
        }else{
            return 0 ;
        }
    }else{
        return 0 ;
    }

}

wGdalRaster* wGdalRasterFactory::Create(int xsize, int ysize, int nband, GDALDataType outtype)
{
	if (outtype == GDT_Byte) {
		wGdalRasterByte* ptr = new wGdalRasterByte();
		if (ptr == 0) return 0;
		bool ok = ptr->create(xsize, ysize, nband);
		if (ok == false) return 0;
		else return ptr;
	}
	else if (outtype == GDT_Int16) {
		wGdalRasterI16* ptr = new wGdalRasterI16();
		if (ptr == 0) return 0;
		bool ok = ptr->create(xsize, ysize, nband);
		if (ok == false) return 0;
		else return ptr;
	}
	else if (outtype == GDT_UInt16) {
		wGdalRasterU16* ptr = new wGdalRasterU16();
		if (ptr == 0) return 0;
		bool ok = ptr->create(xsize, ysize, nband);
		if (ok == false) return 0;
		else return ptr;
	}
	else if (outtype == GDT_Int32) {
		wGdalRasterI32* ptr = new wGdalRasterI32();
		if (ptr == 0) return 0;
		bool ok = ptr->create(xsize, ysize, nband);
		if (ok == false) return 0;
		else return ptr;
	}
	else if (outtype == GDT_UInt32) {
		wGdalRasterU32* ptr = new wGdalRasterU32();
		if (ptr == 0) return 0;
		bool ok = ptr->create(xsize, ysize, nband);
		if (ok == false) return 0;
		else return ptr;
	}
	else if (outtype == GDT_Float32) {
		wGdalRasterFloat* ptr = new wGdalRasterFloat();
		if (ptr == 0) return 0;
		bool ok = ptr->create(xsize, ysize, nband);
		if (ok == false) return 0;
		else return ptr;
	}
	else if (outtype == GDT_Float64) {
		wGdalRasterDouble* ptr = new wGdalRasterDouble();
		if (ptr == 0) return 0;
		bool ok = ptr->create(xsize, ysize, nband);
		if (ok == false) return 0;
		else return ptr;
	}
	else {
		return 0;
	}
}









/////////////////////////////////////////////////////////////////////////////////////////
//                                     Double
/////////////////////////////////////////////////////////////////////////////////////////

//new
void wGdalRasterDouble::fill( int iband , int fillval )
{
        if( this->mState == wGdalRasterStateOpen ||  this->mState == wGdalRasterStateCreate )
        {
                if( iband < this->mptrVec.size() )
                {
                        double* bandPtr = (double*)this->mptrVec[iband] ;
                        int asize = this->mXSize * this->mYSize ;
                        for(int it = 0 ; it < asize ; ++ it )
                        {
                                bandPtr[it] = fillval ;
                        }
                }else
                {
                        cout<<"wGdalRaster::fill error 1."<<endl ;
                }
        }else
        {
                cout<<"wGdalRaster::fill error 2."<<endl ;
        }
}

wGdalRasterDouble::~wGdalRasterDouble()
{
        this->release() ;
}

void wGdalRasterDouble::release()
{
        cout<<"release double"<<endl ;
        this->mState = wGdalRasterStateNone ;
        for(int i = 0 ; i<mptrVec.size() ; ++ i )
        {
                if( mptrVec[i] )
                {
                        delete[] mptrVec[i] ;
                        mptrVec[i] = 0 ;
                }
        }
}
float wGdalRasterDouble::getValuef(int ix,int iy,int ib )  const
{
        double* ptr = mptrVec[ib] ;
        return   (float)ptr[ix+iy*mXSize]  ;
}
float wGdalRasterDouble::getValuef(int it ,int ib )  const
{
        double* ptr = mptrVec[ib] ;
        return   (float)ptr[it]  ;
}
int wGdalRasterDouble::getValuei(int ix,int iy,int ib )  const
{
        double* ptr = mptrVec[ib] ;
        return (int)( ptr[ix+iy*mXSize] ) ;
}
int wGdalRasterDouble::getValuei(int it , int ib  )  const
{
        double* ptr = mptrVec[ib] ;
        return (int)( ptr[it] ) ;
}
void wGdalRasterDouble::setValuef(int ix,int iy,int ib,float val)
{
        double* ptr = mptrVec[ib] ;
        ptr[ix+iy*mXSize] = val ;
}
void wGdalRasterDouble::setValuei(int ix,int iy,int ib,int val)
{
        double* ptr = mptrVec[ib] ;
        ptr[ix+iy*mXSize] = val ;
}
void wGdalRasterDouble::setValuef(int it,int ib,float val)
{
        double* ptr = mptrVec[ib] ;
        ptr[it] = val ;
}
void wGdalRasterDouble::setValuei(int it,int ib,int val)
{
        double* ptr = mptrVec[ib] ;
        ptr[it] = val ;
}

double wGdalRasterDouble::getValued(int it,int ib) const
{
    double* ptr = mptrVec[ib] ;
    return ptr[it] ;
}
double wGdalRasterDouble::getValued(int ix,int iy,int ib) const
{
    double* ptr = mptrVec[ib] ;
    return  ptr[ix+iy*mXSize]  ;
}

void   wGdalRasterDouble::setValued(int ix,int iy,int ib,double val)
{
    double* ptr = mptrVec[ib] ;
    ptr[ix+iy*mXSize] = val ;
}
void   wGdalRasterDouble::setValued(int it , int ib, double val)
{
    double* ptr = mptrVec[ib] ;
    ptr[it] = val ;
}


bool wGdalRasterDouble::open(string filepath)
{
        if( this->mState != wGdalRasterStateNone)
        {
                return false ;
        }
        GDALDataset* ds = (GDALDataset*)GDALOpen( filepath.c_str() , GA_ReadOnly ) ;
        if( ds==0 )
        {
                return false ;
        }

        strcpy( mProj , ds->GetProjectionRef() ) ;
        ds->GetGeoTransform( mTrans ) ;

        mXSize = ds->GetRasterXSize() ;
        mYSize = ds->GetRasterYSize() ;
        mNBand = ds->GetRasterCount() ;
		if( mNBand>0 ){//2022-1-20
			mNoDataValue = ds->GetRasterBand(1)->GetNoDataValue() ;
		}

        for(int i = 0 ; i<mNBand ; ++ i )
        {
                double* ptr = new double[mXSize*mYSize] ;
                ds->GetRasterBand(i+1)->RasterIO( GF_Read ,
                        0,0,mXSize,mYSize,
                        ptr ,
                        mXSize,mYSize,GDT_Float64 ,
                        0,0,0) ;
                mptrVec.push_back(ptr) ;
        }
        GDALClose(ds) ;
        this->mState = wGdalRasterStateOpen ;
        return true ;
}
bool wGdalRasterDouble::save_pr(string filepath,bool usefilldata,double filldata,bool compress)
{
        if( this->mState == wGdalRasterStateNone)
        {
                return false   ;
        }
        GDALDriver* driver = GetGDALDriverManager()->GetDriverByName("GTiff");

        CPLStringList opt ;
        if( compress==true ) opt.SetNameValue("COMPRESS" , "Deflate") ;

        GDALDataset* ds = driver->Create( filepath.c_str() , mXSize, mYSize , mNBand,GDT_Float64 ,opt.List()) ;
        if( ds==0 )
        {
                return false  ;
        }
        for(int i = 0 ; i<mNBand ; ++ i )
        {
            double* ptr = mptrVec[i] ;
            ds->GetRasterBand(i+1)->RasterIO( GF_Write,
                    0,0,mXSize,mYSize,
                    ptr ,
                    mXSize,mYSize,GDT_Float64 ,
                    0,0,0) ;
            if( usefilldata ) ds->GetRasterBand(i+1)->SetNoDataValue(filldata);
        }
        if( strlen( mProj ) > 1 && mTrans[1] > 0 )
        {
                ds->SetProjection( mProj ) ;
                ds->SetGeoTransform( mTrans ) ;
        }
        GDALClose(ds) ;
        return true ;
}
bool wGdalRasterDouble::create(int nxsize,int nysize,int nband )
{
        if( this->mState != wGdalRasterStateNone)
        {
                return false ;
        }
        mXSize = nxsize ;
        mYSize = nysize ;
        mNBand = nband ;
        int asize = mXSize*mYSize ;
        for(int i = 0 ; i<mNBand ; ++ i )
        {
                double* ptr = new double[mXSize*mYSize] ;
                for(int it = 0 ; it<asize;++it) ptr[it] = 0.0 ;
                mptrVec.push_back(ptr) ;
        }
        this->mState = wGdalRasterStateCreate ;
        return true ;
}




/////////////////////////////////////////////////////////////////////////////////////////
//                                     uint32
/////////////////////////////////////////////////////////////////////////////////////////

//new
void wGdalRasterU32::fill( int iband , int fillval )
{
        if( this->mState == wGdalRasterStateOpen ||  this->mState == wGdalRasterStateCreate )
        {
                if( iband < this->mptrVec.size() )
                {
                        unsigned int* bandPtr = (unsigned int*)this->mptrVec[iband] ;
                        int asize = this->mXSize * this->mYSize ;
                        for(int it = 0 ; it < asize ; ++ it )
                        {
                                bandPtr[it] = fillval ;
                        }
                }else
                {
                        cout<<"wGdalRaster::fill error 1."<<endl ;
                }
        }else
        {
                cout<<"wGdalRaster::fill error 2."<<endl ;
        }
}

wGdalRasterU32::~wGdalRasterU32()
{
        this->release() ;
}

void wGdalRasterU32::release()
{
        //cout<<"release double"<<endl ;
        this->mState = wGdalRasterStateNone ;
        for(int i = 0 ; i<mptrVec.size() ; ++ i )
        {
                if( mptrVec[i] )
                {
                        delete[] mptrVec[i] ;
                        mptrVec[i] = 0 ;
                }
        }
}
float wGdalRasterU32::getValuef(int ix,int iy,int ib )  const
{
        unsigned int* ptr = mptrVec[ib] ;
        return   (float)ptr[ix+iy*mXSize]  ;
}
float wGdalRasterU32::getValuef(int it ,int ib )  const
{
        unsigned int* ptr = mptrVec[ib] ;
        return   (float)ptr[it]  ;
}
int wGdalRasterU32::getValuei(int ix,int iy,int ib )  const
{
        unsigned int* ptr = mptrVec[ib] ;
        return (int)( ptr[ix+iy*mXSize] ) ;
}
int wGdalRasterU32::getValuei(int it , int ib  )  const
{
        unsigned int* ptr = mptrVec[ib] ;
        return (int)( ptr[it] ) ;
}
void wGdalRasterU32::setValuef(int ix,int iy,int ib,float val)
{
        unsigned int* ptr = mptrVec[ib] ;
        ptr[ix+iy*mXSize] = val ;
}
void wGdalRasterU32::setValuei(int ix,int iy,int ib,int val)
{
        unsigned int* ptr = mptrVec[ib] ;
        ptr[ix+iy*mXSize] = val ;
}
void wGdalRasterU32::setValuef(int it,int ib,float val)
{
        unsigned int* ptr = mptrVec[ib] ;
        ptr[it] = val ;
}
void wGdalRasterU32::setValuei(int it,int ib,int val)
{
        unsigned int* ptr = mptrVec[ib] ;
        ptr[it] = val ;
}

double wGdalRasterU32::getValued(int it,int ib) const
{
    unsigned int* ptr = mptrVec[ib] ;
    return (double)ptr[it] ;
}
double wGdalRasterU32::getValued(int ix,int iy,int ib) const
{
    unsigned int* ptr = mptrVec[ib] ;
    return  (double)ptr[ix+iy*mXSize]  ;
}

void   wGdalRasterU32::setValued(int ix,int iy,int ib,double val)
{
    unsigned int* ptr = mptrVec[ib] ;
    ptr[ix+iy*mXSize] = val ;
}
void   wGdalRasterU32::setValued(int it , int ib, double val)
{
    unsigned int* ptr = mptrVec[ib] ;
    ptr[it] = val ;
}


bool wGdalRasterU32::open(string filepath)
{
        if( this->mState != wGdalRasterStateNone)
        {
                return false ;
        }
        GDALDataset* ds = (GDALDataset*)GDALOpen( filepath.c_str() , GA_ReadOnly ) ;
        if( ds==0 )
        {
                return false ;
        }

        strcpy( mProj , ds->GetProjectionRef() ) ;
        ds->GetGeoTransform( mTrans ) ;

        mXSize = ds->GetRasterXSize() ;
        mYSize = ds->GetRasterYSize() ;
        mNBand = ds->GetRasterCount() ;
		if( mNBand>0 ){//2022-1-20
			mNoDataValue = ds->GetRasterBand(1)->GetNoDataValue() ;
		}

        for(int i = 0 ; i<mNBand ; ++ i )
        {
                unsigned int* ptr = new unsigned int[mXSize*mYSize] ;
                ds->GetRasterBand(i+1)->RasterIO( GF_Read ,
                        0,0,mXSize,mYSize,
                        ptr ,
                        mXSize,mYSize,GDT_UInt32 ,
                        0,0,0) ;
                mptrVec.push_back(ptr) ;
        }
        GDALClose(ds) ;
        this->mState = wGdalRasterStateOpen ;
        return true ;
}
bool wGdalRasterU32::save_pr(string filepath,bool usefilldata,double filldata,bool compress)
{
        if( this->mState == wGdalRasterStateNone)
        {
                return false   ;
        }
        GDALDriver* driver = GetGDALDriverManager()->GetDriverByName("GTiff");

        CPLStringList opt ;
        if( compress==true ) opt.SetNameValue("COMPRESS" , "Deflate") ;

        GDALDataset* ds = driver->Create( filepath.c_str() , mXSize, mYSize , mNBand,GDT_UInt32 ,opt.List() ) ;
        if( ds==0 )
        {
                return false  ;
        }
        for(int i = 0 ; i<mNBand ; ++ i )
        {
            unsigned int* ptr = mptrVec[i] ;
            ds->GetRasterBand(i+1)->RasterIO( GF_Write,
                    0,0,mXSize,mYSize,
                    ptr ,
                    mXSize,mYSize,GDT_UInt32 ,
                    0,0,0) ;
            if( usefilldata ) ds->GetRasterBand(i+1)->SetNoDataValue(filldata);
        }
        if( strlen( mProj ) > 1 && mTrans[1] > 0 )
        {
                ds->SetProjection( mProj ) ;
                ds->SetGeoTransform( mTrans ) ;
        }
        GDALClose(ds) ;
        return true ;
}
bool wGdalRasterU32::create(int nxsize,int nysize,int nband )
{
        if( this->mState != wGdalRasterStateNone)
        {
                return false ;
        }
        mXSize = nxsize ;
        mYSize = nysize ;
        mNBand = nband ;
        int asize = mXSize*mYSize ;
        for(int i = 0 ; i<mNBand ; ++ i )
        {
                unsigned int* ptr = new unsigned int[mXSize*mYSize] ;
                for(int it = 0 ; it<asize;++it) ptr[it] = 0.0 ;
                mptrVec.push_back(ptr) ;
        }
        this->mState = wGdalRasterStateCreate ;
        return true ;
}




#endif // WGDALRASTER_H_IMPLEMENTATION




