//////////////////////////////////////////////////////////////////////////
//                    _   _   ____   ____                    
//   Project         | | | | / ___) / ___)                   
//                   | | | || | __ | |                       
//                   | |_| || |_\ || \___                    
//                    \____/ \____| \ ___)     6.0           
//                                                           
//!  \file headerfile.h
//!  \brief Class 的接口定义。
//!  \details 该文件定义了栅格文件分析的主要接口。
//!  \author 李林。
//!  \attention 
//!   Copyright (c) 1996-2008 SuperMap Software Limited Company.  <br> 
//!   All Rights Reserved.
//!  \version 6.0
//////////////////////////////////////////////////////////////////////////

#if !defined(AFX_UGFileParseRaster_H__392553F8_7BF9_4668_BD97_4211091FEF20__INCLUDED_)
#define AFX_UGFileParseRaster_H__392553F8_7BF9_4668_BD97_4211091FEF20__INCLUDED_


#include "UGFileParse.h"
#include "Geometry/UGGeometry.h"
#include "Toolkit/UGPalette.h"
#include "FileParser/UGRasterConfigParams.h"
#include "Base3D/UGTextureData.h"
#include "Base/OgdcHistogram.h"

namespace UGC {
const UGint BAND_FIRST_INDEX = 0;
class UGImage;

//! \brief 栅格图像的统计信息
//! \remarks 参照引擎的定义
class RasterStatisticInfo
{
public:
	UGdouble m_dMax;//最大值
	UGdouble m_dMin;//最小值
	UGdouble m_dMiddle;//中值
	UGdouble m_dAverage;//平均值
	UGArray<UGdouble> m_arrMost;//众数
	UGArray<UGdouble> m_arrLeast;//稀数
	UGdouble m_dStddev;//标准差
	UGdouble m_dVariance;//方差

	RasterStatisticInfo()
	{
		m_bHasMin = FALSE;
		m_bHasMax = FALSE;
		m_bHasAverage  = FALSE;
		m_bHasLeast = FALSE;
		m_bHasMiddle = FALSE;
		m_bHasStddev = FALSE;
		m_bHasVariance = FALSE;
		m_bHasMost = FALSE;
	}
	void SetMax(UGdouble max)
	{
		m_dMax = max;
		m_bHasMax = TRUE;
	}
	void SetMin(UGdouble min)
	{
		m_dMin = min;
		m_bHasMin = TRUE;
	}
	void SetMiddle(UGdouble mid)
	{
		m_dMiddle = mid;
		m_bHasMiddle = TRUE;
	}
	void SetAverage(UGdouble average)
	{
		m_dAverage = average;
		m_bHasAverage = TRUE;
	}
	void SetMost(UGArray<UGdouble> most)
	{
		m_arrMost = most;
		m_bHasMost = TRUE;
	}
	void SetLeast(UGArray<UGdouble> least)
	{
		m_arrLeast = least;
		m_bHasLeast = TRUE;
	}
	void SetStddev(UGdouble stddev)
	{
		m_dStddev = stddev;
		m_bHasStddev = TRUE;
	}
	void SetVariance(UGdouble variance)
	{
		m_dVariance = variance;
		m_bHasVariance = TRUE;
	}
	UGbool HasMax()
	{
		return m_bHasMax;
	}
	UGbool HasMin()
	{
		return m_bHasMin;
	}
	UGbool HasMost()
	{
		return m_bHasMost;
	}
	UGbool HasLeast()
	{
		return m_bHasLeast;
	}
	UGbool HasStddev()
	{
		return m_bHasStddev;
	}
	UGbool HasVariance()
	{
		return m_bHasVariance;
	}
	UGbool HasMiddle()
	{
		return m_bHasMiddle;
	}
	UGbool HasAverage()
	{
		return m_bHasAverage;
	}

private:
	//! \brief 统计信息不一定都能取到，所以设置以下标识，用来判断哪些成员的信息是有效的
	UGbool m_bHasMin;      // 最小值是否有效
	UGbool m_bHasMax ;     // 最大值是否有效
	UGbool m_bHasMiddle;   // 中值是否有效
	UGbool m_bHasAverage;  // 平均值是否有效
	UGbool m_bHasMost;     // 众数是否有效
	UGbool m_bHasStddev;   // 标准差是否有效
	UGbool m_bHasVariance; // 方差是否有效
	UGbool m_bHasLeast;    // 稀数是否有效


};

class RasterStatisticInfoMngr :public UGArray<RasterStatisticInfo>
{
public:
	UGbool m_bNeedMin;      // 是否需要获取最小值
	UGbool m_bNeedMax ;     // 是否需要获取最大值
	UGbool m_bNeedMiddle;   // 是否需要获取中值
	UGbool m_bNeedAverage;  // 是否需要获取平均值
	UGbool m_bNeedMost;     // 是否需要获取众数
	UGbool m_bNeedStddev;   // 是否需要获取标准差
	UGbool m_bNeedVariance; // 是否需要获取方差
	UGbool m_bNeedLeast;    // 是否需要获取稀数
	
	RasterStatisticInfoMngr()
	{
		m_bNeedMin = FALSE;
		m_bNeedMax = FALSE;
		m_bNeedMiddle = FALSE;
		m_bNeedAverage = FALSE;
		m_bNeedMost  = FALSE;
		m_bNeedStddev = FALSE;
		m_bNeedVariance = FALSE;
		m_bNeedLeast = FALSE;		
	}
};

//! \brief 实现栅格的属性表。
class UGRasterAttributeTable//: public OgdcRecordset
{
public:
	//! \brief 从颜色表初始化属性表。
	//! \param colorset  颜色表。[in]
	UGbool InitFromColorset(const UGColorset& colorset)	;

	//! \brief 用值来分割颜色范围，来创建属性表行。
	//! \param values  用值来分割颜色范围。[in]
	UGbool SplitRows(UGdouble* values);	

	//! \brief 从属性表推出颜色表。
	//! \param colorset  颜色表。[out]
	void ToColorset(UGColorset& colorset);	

	//! \brief 获取值所对应的颜色。
	//! \param dfValue  值。[in]
	//! \param color  值对应的颜色。[out]
	UGbool GetColorOfValue(UGdouble dfValue, UGColor& color);

	//! \brief 获取值所在的行。
	//! \param dfValue  值。[in]
	//! \param iRow  所在行。[out]
	UGbool GetRowOfValue(UGdouble dfValue, UGint& iRow)	;

	//! \brief 获取一个颜色范围的上下限。
	//! \param iRow [in] 第几个颜色范围。
	UGbool GetRowRange(UGint iRow, UGdouble& rowMin, UGdouble& rowMax);

};

class UGFileParseRaster;
class FILEPARSER_API UGRasterFileLayer: public UGFileLayer
{
public:
	UGRasterFileLayer(UGFileParseRaster* pFP){m_pFP = pFP;}

	UGFileParseRaster* GetRasterFileParser(){return m_pFP;}

public:
	virtual FILELAYER_TYPE GetType(){return UGFileLayer::FL_RASTER;}

private:
	UGFileParseRaster* m_pFP;

};

typedef UGbool (UGSTDCALL * BandGetTileFunc) (UGByteArray*, UGlong);

// 金字塔也是一个图片。同样是按块存储的。
struct PyramidInfo
{	
	PyramidInfo()
	{	
		m_nWidth  = 0;
		m_nHeight = 0;
		m_nIndex  = 0;
		m_nBlockWidth   = 0;
		m_nBlockHeight  = 0;
		m_nBlocksPerRow = 0;
		m_nBlocksPerColumn = 0;
		m_nGDALDataType = 8;
		m_ePixelFormat  = IPF_UBYTE;
	}
	UGint m_nWidth;           //图片宽 这个的单位要根据像素格式来确定
	UGint m_nHeight;          //图片高
	UGint m_nIndex;           //金字塔层索引
	UGint m_nBlockWidth;      //块的宽
	UGint m_nBlockHeight;     //块的高
	UGint m_nBlocksPerColumn; //每行的块数 
	UGint m_nBlocksPerRow;    //每列的块数
	UGint m_nGDALDataType;    //GDAL中的数据类型，还不是很清楚，是不是指的像素格式
	UGPixelFormat m_ePixelFormat; // 像素格式
};



//! \brief 本类主要是定义栅格文件格式的解析基类。
//! \remarks 所有有关栅格文件解析具体格式的类都必须继承此类。
class FILEPARSER_API UGFileParseRaster : public UGFileParser  
{
	//采样方式 
	enum EmSamplingPattern
	{
		NONE             = 0, 
		NEAREST          = 1,  
		AVERAGE          = 2,
		GAUSS            = 3,
		AVERAGE_MAGPHASE = 4
	};

public:

	//! \brief 构造函数。
	UGFileParseRaster();	

	//! \brief 析构函数。
	virtual ~UGFileParseRaster();
	
public:	

	virtual UGFileType::EmGroup GetFileGroup() const;
	
	////////////////////////////////////////////////////////////////////////
	//
	// 常用基本属性
	//
	////////////////////////////////////////////////////////////////////////
	//! \brief 创建影像金字塔  支持任意格式    注:此方法仅用于影像插件。
	//! \return 返回是否创建金字塔是否成功。
	//! \remarks 如果是ERDAS的IMG文件我们希望和ArcMap一样建立外挂的rrd文件
	//! 但是现在的问题是貌似GDAL 1.6并不支持，可以通过改变第三方库来修改，
	//! 但是方法并不好，寻求新的解决之道。
	virtual UGbool BuildPyramid(UGbool bShhowProgress = FALSE);

	//! \brief 返回影像宽度。
	//! \return 图像的宽。
	virtual UGint GetWidth() const;	

	//! \brief 返回影像高度。
	virtual UGint GetHeight() const;	


	//! \brief 是否是扫描行存贮。
	//! \return 判断是否是扫描行。
	virtual UGbool IsScanline() const;	
	
	//! \brief 是否是按像素的方式读取
	//! \return 判断是否是像素读取方式。
	virtual UGbool IsReadPixel() const;


	//! \brief 获取存储影像分块的宽（像素单位）。
	//! \return 返回像素单位的影像分块的宽。
	virtual UGint GetBlockWidth() const;	

	//! \brief 获取存储影像分块的高（像素单位）。
	//! \return 返回像素单位的影像分块的高。
	virtual UGint GetBlockHeight() const;
	

	//! \brief 获取横向的block数量。
	//! \return 返回横向block数。
	virtual UGint GetColBlocks() const;	

	//! \brief 获取纵向的block数量。
	//! \return 返回纵向block数量。
	virtual UGint GetRowBlocks() const;	
	
	//! \brief 得到目标影像数据的基本信息。
	RasterInfo GetRasterInfo() const {return m_tarInfo;}	
	
	//! \brief 得到原始影像数据的基本信息
	RasterInfo GetSrcRasterInfo() const {return m_srcInfo;}	
	
	//! \brief 得到目标影像数据的基本信息的引用。
	RasterInfo& GetRasterInfoRef() {return m_tarInfo;}	

	//! \brief 得到是否可以导入成合成波段。
	UGbool GetForceAsOneBand() {return m_bForceAsOneBand;}	

	void SetDTName(const UGString strDTName){m_tarInfo.m_strDTName = strDTName;}
	
	//! \brief 得到目标影像数据的基本信息集合。
	virtual RasterInfos GetRasterInfos();

	//! \brief 得到原始影像数据的基本信息集合。
	virtual RasterInfos GetSrcRasterInfos();

	//##ModelId=482030540261
	//! \brief 是否需要上下反向。
	//! \return 返回是否需要上下方向。
	//! \remarks 我们的图片的原点是左上角 而部分的Tga数据的原点坐标是左下的。
	virtual UGbool IsReverseReadOrWrite() const {return FALSE;}

	//////////////////////////////////////////////////////////////////////////
	// 波段相关
	//////////////////////////////////////////////////////////////////////////

	//! \brief 是否多波段
	virtual UGbool IsMultiBand() const;

	//! \brief 得到波段的个数。
	//! \return 返回波段的个数。
	virtual UGint GetBandCount() const;	

	//! \brief 获取波段信息列表。
	//! \param bandInfos  要输出的波段信息列表。[out]
	//! \attention 导入多波段时用。
	virtual UGbool GetBandInfos(UGArray<BandInfo>& bandInfos);

	//! \brief 设置波段信息，去真正读取波段信息
    //UGbool  SetBandInfos(UGArray<BandInfo>& bandInfos);

	//===================================================
	//! \brief  获取金字塔数据集信息列表。
	//! \param  rasterInfos[out]要输出的金字塔信息集合列表
	//! \return   
	//! \remarks 
	//! \attention 导入多波段时用。
	virtual UGbool GetPyramidInfos(UGArray<PyramidInfo>& pyramidInfos);

	///////////////////////////////////////////////////
	// 像素深度相关
	///////////////////////////////////////////////////

	//! \brief 返回象素的深度。
	//! \param  [in]。
	//! \return 返回图像的深度。
	//! \remarks 图像深度表示数据像素位数。
	virtual UGPixelFormat GetPixelFormat() const;	

	//////////////////////////////////////////////////
	// 颜色表/颜色空间格式相关
	//////////////////////////////////////////////////	

	//! \brief 获取栅格的色彩空间格式。
	//! \param  [in]。
	//! \return 返回栅格的色彩空间格式。
	//! \remarks 分成RGB,RGBA,CMY,CMYK,YIQ,YUV,YCC。
	virtual ImgColorSpace GetImgColorSpace();	

	//! \brief 转换栅格的色彩空间格式。
	//! \param nImgColorSpace 要设置的色彩空间[in]。
	//! \remarks 分成RGB,RGBA,CMY,CMYK,YIQ,YUV,YCC。通过转换公式把现有的颜色模式转换成对应的颜色模式
	virtual void ConvertColorSpace(ImgColorSpace nImgColorSpace);

	//! \brief 设置调色板。
	//! \param Palette  要设置的颜色表。[in]
	//! \return 设置颜色表。
	virtual void SetColorset(const UGColorset& Palette);	

	//! \brief 得到调色板。
	//! \return 返回颜色表。
	virtual UGbool GetColorset(UGColorset& Palette) const;	

	////////////////////////////////////////////////////////
	// 地理相关
	////////////////////////////////////////////////////////

	//! \brief 得到影象的Bounds(有空间范围，返回空间范围，没有空间范围，返回图像长宽范围)。
	//! \return 返回影像四角的坐标范围。
	virtual UGRect2D GetBounds() const;	

	//! \brief 获取空间参考。
	virtual const UGPrjCoordSys* GetSpatialRef() const;

	////////////////////////////////////////////////////////
	// 无效值相关
	////////////////////////////////////////////////////////
	
	//##ModelId=482030540261
	//! \brief 获取无效值。
	//! \param  [in]。
	//! \return 返回无效值。
	//! \remarks 如果没有无效值，那么返回的。
	virtual UGbool GetNoValue(UGNoValue& nodata) const;

	/////////////////////////////////////////////////////////
	// 属性表相关
	/////////////////////////////////////////////////////////
	//! \brief 获取属性表。
	//! \param table  要返回的栅格属性表。[out]
	//! \param iBand  查看第几个波段有没有属性表信息。[in]
	virtual UGbool GetAttributeTable(UGRasterAttributeTable& table, UGint iBand=BAND_FIRST_INDEX);	

	//! \brief 设置属性表。
	//! \param table  栅格的属性表。[in]
	//! \param iBand  查看第几个波段有没有属性表信息。[in]
	//! \remarks 属性表应该让外部可以设置。
	virtual void SetAttributeTable(const UGRasterAttributeTable& table, UGint iBand=BAND_FIRST_INDEX);	
	
	/////////////////////////////////////////////////////////
	// 存储相关
	/////////////////////////////////////////////////////////
	
	//////////////////////////////////////////////////////////////////////////
	// 读出函数
	//////////////////////////////////////////////////////////////////////////
	//! \brief 准备开始读取栅格数据,在调用ReadData之前必须调用
	//! \param 1 [in] 从第几行开始。
	virtual UGbool BeginRead(UGint nIndex = 1)	;

	//! \brief 准备一个扫描行的数据
	//! \param imgScanline 扫描行数据。[out]
	//! \return 是否成功。
	virtual UGbool PrepareScanLine(UGImgScanline& imgScanline);

	//! \brief 准备一个瓦片的数据
	//! \param imgScanline 瓦片数据。[out]
	//! \return 是否成功。
	virtual UGbool PrepareBlock(UGImgBlock& imgBlock);

	//! \brief 读取DEM或GRID数据的高程值
	//! \param nRowPixIndex 高程的第几个行。[in]
	//! \param nColPixIndex 高程的第几个列。[in]
	//! \param dValue	高程值。[out]
	//! \param nBand=0  第几个波段 [in]。
	//! \attention 注意：目前只在DEM或GRID的数据是按列存储时使用。
	virtual UGbool ReadGridValue(UGint nRowPixIndex, UGint nColPixIndex, UGdouble& dValue, UGint nBand=0) {return FALSE;}
	
	//! \brief 读取一个扫描行的数据（在该函数中，imgScanline数据类型大小不进行分配，准备工作全都在PrepareScanLine里做掉）
	//! \param imgScanline 扫描行数据。[out]
	//! \param nRowIndex  第几个扫描行。[in]
	//! \param nBand=0 [in]第几个波段的扫描行。
	//! \param nColIndex[in]从第几列开始扫描
	virtual UGbool ReadScanLine(UGImgScanline& imgScanline, UGint nRowIndex, UGint nBand=0, UGint nColIndex=0)	{return FALSE;}


	//! \brief 读取一行中任意指定的2列之间的数据（imgScanline数据类型大小会在函数内部重新分配，传入时不需要做任何工作）
	//! param  imgScanline [out] nColEnd-nColStart直接的数据
	//! param  nRowIndex   [in]  第几行
	//! param  lColStart   [in]  开始列
	//! param  lColEnd     [in]  终止列
	//! param  nBand       [in]  第几个波段
	virtual UGbool ReadScanLine(UGImgScanline& imgScanline, UGint nRowIndex, UGlong nColStart, UGlong nColEnd, UGint nBand)	{return FALSE;}
	
	//! \brief 读取一个Block数据
	//! \param pImgBlock 返回读取的block数据。[out]
	//! \param nRowBlockIndex 要读取的block处于第几行。[in]
	//! \param nColBlockIndex 要读取的block处于第几列。[in]
	//! \param nBand=0 要读取第几个波段的block。[in]
	//! \return 读取是否成功。
	virtual UGbool ReadBlock(UGImgBlock& pImgBlock, UGint nRowBlockIndex, UGint nColBlockIndex, UGint nBand=0)	{return FALSE;}
	
	// 获取多帧影像数据 [6/10/2011 林文玉]
	//! \brief 读取影像数据各帧数据，静态函数。
	//! \param strGifFile [in] 文件路径。
	//! \param arrPicture [out] 返回影像数据。
	//! \param 图像数据是否翻转。
	//! \return 是否读取成功。
	virtual UGbool GetDynamicIMGData(const UGString& strFile, UGArray<UGGeoPicture*>& arrPicture,UGbool bReverse){return FALSE;}


	// 保存多帧影像数据
	//! \brief 保存影像数据各帧数据，静态函数。
	//! \param strGifFile [in] 文件路径。
	//! \param arrPicture [in] 纹理信息。
	//! \return 是否保存成功。
	virtual UGbool SetDynamicIMGData(const UGString& strFile,UGTextureDataAnimation *pTextureDataAnimation){return FALSE;}


	//! \brief 结束读取栅格数据,在调用ReadData之后必须调用(释放东东)
	virtual void EndRead();

	//////////////////////////////////////////////////////////////////////////
	// 与金字塔相关的函数 
	//////////////////////////////////////////////////////////////////////////
	//! \brief 是否存在金字塔文件
	virtual UGbool IsExistPyramid();

	//! \brief 读取金字塔的个数
	//! \得到第几波段的金字塔的个数
	virtual UGint GetPyramidCount(UGint nBand);

	//! \brief 得到特定波段的特定金字塔的特定块的数据
	//! \param pDataBuffer 要存放的数据
	//! \param nSize 数据的大小 有GetPyramidBlockSize确定
	//! \param nBand某个波段
	//! \param nTierIndex金字塔索引
	//! \param nXBlock块的X位置
	//! \param nYBlock块的Y位置
	virtual UGbool GetPyramidBlockData(unsigned char* pDataBuffer, UGint nSize, UGint nBand, UGint nTierIndex, UGint nXBlock, UGint nYBlock);

    
	//! \brief 得到特定波段的特定位置的数据
	//! \param pDataBuffer 要存放的数据
	//! \param nSize 数据的大小
    //! \parma nBand 波段索引
	//! \param xBlock 块行号
	//! \param YBlock 块列号
	virtual UGbool GetRawRasterData(void * pDataBuffer,UGRect rectView,UGint nBandIndex);
	
	//! brief 得到显示该金字塔时单个块所需要的内存大小(字节)
	//! param nBand 波段
	//! param nTierIndex 金字塔索引
	virtual UGint GetPyramidBlockSize(UGint nBand, UGint nTierIndex){return 0;}
	
	//! brief 得到一个金字塔中存储块的总个数
	//! param nBand 波段
	//! param nTierIndex 金字塔索引
	virtual UGint GetPyramidBlockCount(UGint nBand, UGint nTierIndex){return 0;}

	//! brief 得到金字塔的长宽
	//! nBand 波段
	//! nTierIndex 金字塔索引
	//! nWidth 金字塔的宽
	//! nHeight 金字塔的高
	virtual void GetPyramidSize(UGint nBand, UGint nTierIndex, UGint &nWidth, UGint &nHeight);

	//! brief 得到金字塔中每行存储的块的个数
	//! param nBand 波段
	//! param nTierIndex 金字塔索引
	virtual UGint GetPyramidBlocksPerRow(UGint nBand, UGint nTierIndex);

	//! brief 得到金字塔中每列存储的块的个数
	//! param nBand 波段
	//! param nTierIndex 金字塔索引
	virtual UGint GetPyramidBlocksPerColumn(UGint nBand, UGint nTierIndex);

	//! brief 得到金字塔中块的长度(字节)
	//! param nBand 波段
	//! param nTierIndex 金字塔索引
	virtual UGint GetPyramidBlockXSize(UGint nBand, UGint nTierIndex);

	//! brief 得到金字塔中块的高度(字节)
	//! param nBand 波段
	//! param nTierIndex 金字塔索引
	virtual UGint GetPyramidBlockYSize(UGint nBand, UGint nTierIndex);

	//! brief  得到金字塔的一共有几个波段
	//! return 金字塔个数
	virtual UGint GetPyramidBandCount();

	//! brief得到Img文件的地理范围
	//! param ImgBounds 接受的地理范围
	virtual UGbool GetImgBounds(UGRect2D &ImgBounds){return FALSE;}

	//! brief 得到金字塔文件的像素格式
	//! remarks 由于在HFA中有一个3波段融合为一个波段的过程，现在想
	//! 在外面支持这个融合的过程所以要得到原始图像的像素格式
	virtual UGPixelFormat GetPyramidPixelFormat();

	//! brief 得到金字塔像素格式用的位数
	//! remark 从HFA里得到的是一片数据，在从HFA中得到一片数据时要用到
	virtual UGint GetDataTypeBits();

	//! brief 初始化金字塔信息
	//! param nBand 波段
	//! param nTierIndex 金字塔索引
	virtual UGbool InitPyramidInfo();

	virtual UGint GetSamplingPattern() const;

	virtual void SetSamplingPattern(const UGint nSampling);
	//////////////////////////////////////////////////////////////////////////
	// 写入函数
	//////////////////////////////////////////////////////////////////////////
	
	virtual void SetBandGetTileFunc(BandGetTileFunc pFunc, UGlong pWnd){return ;}
	
	//! \brief 创建一个外部数据文件以便导出。
	//! \param info  要创建的栅格的基本属性。[in]
	//! \param exchangeParams  导出参数。[in]
	//! \return 是否成功。
	//! \remarks 调用这个前后都不能调用Open。
	virtual UGbool Create(const RasterInfo& info, const UGExportParams& exchangeParams) = 0;
	
	//! \brief 准备开始写数据,在调用WriteData之前必须调用
	//! \return 是否成功。
	virtual UGbool BeginWrite();
	
	//! \brief 写入一个扫描行的数据
	//! \param imgScanline  要写入的数据。[in]
	//! \param nRowIndex  第几个扫描行。[in]
	//! \param 0  把扫描行写入第几个波段。[in]
	//! \return 是否成功。
	virtual UGbool WriteScanLine(const UGImgScanline& imgScanline, UGint nRowIndex, UGint nBandIndex = 0)	{return FALSE;};
	
	//! \brief 写入一个瓦片数据。
	//! \param pImgBlock  写入的瓦片数据。[in]
	//! \param nRowBlockIndex  第几行的瓦片。[in]
	//! \param nColBlockIndex  第几列的瓦片。[in]
	//! \param nBandIndex  第几波段的瓦片。[in]
	//! \return 是否成功。
	virtual UGbool WriteBlock(const UGImgBlock& pImgBlock, UGint nRowBlockIndex, UGint nColBlockIndex, UGint nBandIndex = 0) 	{return FALSE;};
	
	//! \brief 结束写数据,在调用WriteData之后必须调用
	virtual void EndWrite();
	
	
	//! \brief 关闭数据。
	virtual void Close();


	//! \brief 获取影像数据的一些统计信息
	//! \param statiInfoMngr [in] 需要获取的统计信息
	//! \param statiInfoMngr [out] 图像的统计信息
	//! \remarks 在调用这个函数之前，RasterStaticsticInfoMngr需要设置好成员bNeedXXX,表明需要获取哪些统计信息
	virtual UGbool GetStatisticInfos(RasterStatisticInfoMngr &statiInfoMngr);

	//===================================================
	//! \brief  获取波段最大值
	//! \param  nBandIndex 波段索引数值
	//! \return 返回对应波段的最大数值
	virtual UGdouble GetMax(UGint nBandIndex);

	//===================================================
	//! \brief  获取波段最小值
	//! \param  nBandIndex 波段索引数值
	//! \return 返回对应波段的最小数值
	virtual UGdouble GetMin(UGint nBandIndex);

	//===================================================
	//! \brief  获取对应波段的最大最小值
	//! \param  nBandIndex[I] 波段索引值
	//! \param  dMin[O]       最小值 
	//! \param  dMax[O]       最大值
	//! \return   
	//! \remarks 此接口返回具体波段的极值
	//! \attention
	virtual UGbool GetMaxMin(UGint nBandIndex,UGdouble &dMin,UGdouble &dMax);

	//===================================================
	//! \brief  得到栅格信息
	//! \param 
	//! \return   
	//! \remarks 
	//! \attention
	virtual RasterStatisticInfo* GetStatisticsInfo(UGint nBandIndex);

	//===================================================
	//! \brief  统计栅格信息
	//! \param 
	//! \return   
	//! \remarks 
	//! \attention
	virtual RasterStatisticInfo* BuildStatistic(UGint nBandIndex);

	//===================================================
	//! \brief  获取统计直方图
	//! \param  dMin[I]       最小值
	//! \param  dMax[I]       最大值
	//! \param  nBandIndex[I] 波段索引
	//! \param  nBuckets[I]   段数，其和极值共同决定步长
	//! \return   
	//! \remarks 返回直方图信息
	//! \attention
	virtual UGHistogram* GetHistogram(
		UGdouble dMin, 
		UGdouble dMax,
		UGint nBandIndex = 0,
		UGint nBuckets = 256);

	//! \brief 根据类型和文件名获取ImageData，数据量较小时使用，比如网络瓦片数据
	//! \param strFilePath[in] 文件路径
	//! \return 数据的ImageData
	virtual UGImageData* LoadImageData(const UGString& strFilePath){return NULL;}

	//! \brief 根据内存流获取ImageData，数据量较小时使用，比如网络瓦片数据
	//! \param ImageBytes[in] 文件内存流
	//! \return 数据的ImageData
	virtual UGImageData* LoadImageData(const UGByteArray& ImageBytes){return NULL;}

	//! \brief 输出UGImageData内容到内存(简易接口，数据量较小的时候使用，比如出缓存瓦片使用)。
	//! \param ImageBytes [inout] 图片输出的内存流。
	//! \param nfileType [in] 要输出的Image类型。
	//! \param imageData [in] 要输出的Image数据。
	//! \param bIsSavaAs8Bit [in] 是否是8位图片(暂时只支持png)。
	//! \return 返回转换后的图像数据
	//! \attention imageData.pBits 不能为空。
	virtual UGbool SaveImageDataToMemory(UGByteArray& ImageBytes, UGint nfileType, const UGImageData* pImageData, UGbool bTransparentBack = FALSE, UGColor cTransColor = UGRGB(1, 2, 3), UGint nQuality = 75, UGbool bIsSavaAs8Bit = false, UGint ndpi = 96){return false;}

protected:

	UGint RePrepareBlock(UGImgBlock& imgBlock, UGint nRowBlockIndex, UGint nColBlockIndex, UGint nBand);

	void ModifyTargetInfo(UGbool bIsImportAsOneBand);
	
protected:
	
	/*! brief  注：栅格结构上的重大调整  modified by jiangrs 2012/10/11
	**************************************************
	由于我们在打开栅格数据时或者的信息改变了原始的栅格信息
	(如3波段8位变成了1波段24位)
	而用户需要知道原始的栅格信息 & 在直接打开影像时浏览金字塔时也需要知道原始的栅格信息
	故调整为：
	修改 m_info ----> m_tarInfo   
	增加 m_srcInfo
	增加 m_bForceAsOneBand 
	修改 GetRasterInfo()、GetRasterInfoRef() 返回值m_info ----> m_tarInfo
	增加 GetSrcRasterInfo() 返回值 m_srcInfo
	*/

	UGString m_strFilePath;
	//! \brief 是否有金字塔 
	UGbool m_bHasPyramid;
	//! \brief 栅格的基本信息(通过用户给定的参数(ImportParms)生成的)
	RasterInfo m_tarInfo;
	//! \brief 栅格的基本信息(原始的)
	RasterInfo m_srcInfo;
	//! brief 金字塔信息
	UGArray<PyramidInfo> m_PyramidInfos;
	//! \brief 数据为3波段，每波段8位时，可以按照24位单波段导入（RGB）
	//         数据为4波段，每波段8位时，可以按照32为单波段导入（RGBA）
	//         jpg时，内部导入单波段
	//! \brief 是否能够合成为一个波段
	//! \remarks 在每个子类调用Open时维护它 
	//! \remarks 在导入时会判断如果用户是合成波段 而此参数为FALSE 则不会进行导入
	UGbool m_bForceAsOneBand;
	

	//! brief 采样方式
	UGString m_strSampling;

public:

	//! \brief 通过索引得到源数据中的一个数据集。
	//! \param nlayer [in]。
	virtual UGFileLayer* GetLayer(UGint nlayer);

	//! \brief 设置文件名称。
	virtual void SetFilePath(const UGString& strFilePath);	

private:

	//===================================================
	//! \brief  将栅格统计信息保存到XML
	//! \param 
	//! \return   
	//! \remarks 
	//! \attention
	UGString StatisticsInfosToXML(const RasterStatisticInfo &statisticInfo, UGint nBandIndex);

	//===================================================
	//! \brief  从XML中读出栅格统计信息
	//! \param  strXML[in]
	//! \return   
	//! \remarks 
	//! \attention
	RasterStatisticInfo* StatisticsInfosFromXML(const UGString &strXML, UGint nBandIndex);

	//===================================================
	//! \brief  保存极值到XML文件
	//! \param  nBandIndex[I] 波段索引
	//! \param  dMin[O]       最小值
	//! \param  dMax[O]       最大值
	//! \return   
	//! \remarks 
	//! \attention
	UGString ExtremumToXML(UGint nBandIndex,UGdouble &dMin, UGdouble &dMax);

	//===================================================
	//! \brief  从XML中获取极值
	//! \param  strXML[I] XML路径
	//! \param  dMin[I]   最小值
	//! \param  dMax[I]   最大值
	//! \return 读取成功返回true 
	//! \remarks 
	//! \attention
	UGbool ExtremumFromXML(UGint nBandIndex, const UGString &strXML, UGdouble &dMin, UGdouble &dMax);

	//===================================================
	//! \brief  计算极值
	//! \param 
	//! \return   
	//! \remarks 
	//! \attention
    UGbool ComputeExtremum(UGint nBandIndex, UGdouble &dMin, UGdouble &dMax);

	//===================================================
	//! \brief  保存直方图信息到XML
	//! \param  nBandIndex[I] 波段索引
	//! \param  histogram[I]  直方图信息
	//! \return   
	//! \remarks 
	//! \attention
	UGString HistogramToXML(UGdouble dMin, UGdouble dMax, UGint nBuckets, UGint nBandIndex, OgdcHistogram &histogram);

	//===================================================
	//! \brief  从XML中获取直方图信息
	//! \param  strXML[I]    XML路径
	//! \param  histogram[O] 直方图信息
	//! \return 获取成功返回true  
	//! \remarks 
	//! \attention
	UGbool HistogramFromXML(UGdouble dMin, UGdouble dMax, UGint nBuckets,UGint nBandIndex, const UGString &strXML, OgdcHistogram &histogram);

	//===================================================
	//! \brief  计算统计直方图
	//! \param 
	//! \return   
	//! \remarks 
	//! \attention
	virtual UGbool ComputeHistogram(
		UGHistogram &histogram, 
		UGdouble dMin, 
		UGdouble dMax,
		UGint nBandIndex = 0,
		UGint nBuckets = 256);

private:

	UGRasterFileLayer* m_layer;

	UGMutex m_mutex;

	void*  m_hDataset;
};

} //namespace UGC

#endif // !defined(AFX_UGFileParseRaster_H__392553F8_7BF9_4668_BD97_4211091FEF20__INCLUDED_)

