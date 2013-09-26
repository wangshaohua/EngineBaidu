/*! \file	 UGDatasetRaster.h
 *  \brief	 栅格数据集定义文件
 *  \author	 ugc team
 *  \attention 
 *  Copyright(c) 2000-2010  SuperMap GIS Technologies,Inc.<br>
 *  All Rights Reserved
 *  \version $Id: UGDatasetRaster.h,v 1.62 2010/05/07 08:58:18 zhouqin Exp $
 */

//////////////////////////////////////////////////////////////////////////
//!  \file UGDatasetRaster.h
//!  \brief UGDatasetRaster 的接口定义。
//!  \details UGC关于影像数据集的接口定义。
//!  \Modified Date: 2013-4-7
//!  \Modified Author:Conversion-zby
//!  \Details Comments:调整UGC接口参数开放形式以及接口组成，主要目的是在UGC接口中添加多波段栅格数据集的扩展支持;
//!  \Details Comments:本次调整主要包含两方面内容:(1) 对于原有接口增加波段索引参数支持;(2) 增加多波段栅格数据集特有接口
//!  \Details Comments:此次调整涉及整个栅格数据集结构的调整，由于技术人员水平所限以及时间的仓促，难免会产生这样那样的问题,有问题
//!  \Details Comments:请与Conversion-zby联系!
//!  \Version 1-1-1(2013-4-7)



#ifndef UGDATASETRASTER_H
#define UGDATASETRASTER_H

#include "Engine/UGDataset.h"
#include "Element/OgdcRasterScanline.h"
#include "Element/OgdcRasterBlock.h"
#include "Engine/UGDatasetRasterInfo.h"
#include "Geometry/UGGeoRegion.h"
#include "Engine/UGRecordset.h"
#include "Toolkit/UGToolkit.h"
#include "Toolkit/UGThread.h"
#include "Toolkit/UGProgress.h"
#include "Toolkit/UGMarkup.h"
#include "Engine/UGImgBlocksManager.h"
#include "Engine/UGImgBlockRef.h"

#define PYRAMID_ONCECACHECOUNT		256			//创建金字塔时一次缓存的块个数

namespace UGC {

//支持栅格显示的取消 在UGDrawing::PaintRaster中设置 http://192.168.115.2:8090/browse/UGOVI-1015 
typedef UGbool (UGSTDCALL *GETVIEWBLOCKCALLBACKPROC)(UGlong pDrawingH, UGlong pWnd);

struct UGColorSpaceBand
{

	UGColorSpaceBand()
	{
		m_nColorSpaceSelected = ICS_UNKNOW;

	};
	//当前组合色彩的模式
	ImgColorSpace	m_nColorSpaceSelected;

	//当前如果为组合色彩，要显示的波段索引
	UGArray<UGint>	m_arrBandSelected;
};

//陈昭，栅格数据集统计信息
typedef struct RasterStatistics 
{
	UGbool IsDirty;
	UGdouble Max;//最大值
	UGdouble Min;//最小值
	UGdouble Middle;//中值
	UGdouble Average;//平均值
	UGArray<UGdouble> Most;//众数
	UGArray<UGdouble> Least;//稀数
	UGdouble Stddev;//标准差
	UGdouble Variance;//方差

	RasterStatistics()
	{
		IsDirty = 1;
		Max = 0.0;
		Min = 0.0;
		Middle = 0.0;
		Average = 0.0;
		Stddev = 0.0;
		Variance = 0.0;
	}

} UGRasterStatisticsInfo;

#if !defined SYMBIAN60 && !defined OS_ANDROID && !defined (IOS)
class UGRasterBand;
#endif
//! \brief 栅格数据集
//##ModelId=482030540119
#ifdef SYMBIAN60
class ENGINE_APIC UGDatasetRaster : public UGDataset
#else
class ENGINE_API UGDatasetRaster : public UGDataset
#endif
{
	friend class UGDataSource;
public:	
	enum UGImageAccessMode
	{
		//单波段显示模式 
		SingleBand	=1,
		// 组合色彩
		CombineColor=2
	};
	
	enum MultiSpectralFile
	{
		GeoTiff =1,
		MrSID   =2,
		Image   =3,
		ArcGrid =4
	};

public:
	//! \brief 构造函数
	//##ModelId=482030540129
	ENGINE_APIF UGDatasetRaster();

	//! \brief 析构函数
	//##ModelId=482030540157
	virtual ENGINE_APIF ~UGDatasetRaster();

public:
	//! \brief 打开数据集
	//##ModelId=483BB70C009C
	virtual ENGINE_APIF UGbool Open();

	//! \brief 在多线程中用于判断关闭当前数据集是否安全，矢量主要依据是否还有打开的记录集，栅格主要依据是否可以释放所有数据块
	virtual ENGINE_APIF UGbool CanBeClose();

	//! \brief 关闭数据集
	//##ModelId=483BB70C009E
	virtual ENGINE_APIF void Close();

	//! \brief 返回数据集的维数
	//##ModelId=4820305401C5
	virtual ENGINE_APIF UGint GetDimension();

	//! \brief 判断是否是矢量数据集
	//##ModelId=4820305401C7
	virtual ENGINE_APIF UGbool IsVector();
	//! \brief 判断是否是topo数据集
	//##ModelId=4820305401C9
	virtual ENGINE_APIF UGbool IsTopoDataset();

	//! \brief 判断是否是栅格数据集
	//##ModelId=4820305401D4
	virtual ENGINE_APIF UGbool IsRaster();

	//! \brief 判断是否为多波段栅格数据集
	virtual ENGINE_APIF UGbool IsMBRaster();

	//! \brief 判断是否是网络栅格数据集
	//##ModelId=4820305401D4
	virtual ENGINE_APIF UGbool IsWebRaster();

	//! \brief 判断是否是关系类数据集
	virtual ENGINE_APIF UGbool IsRelClass();

	//! \brief 判断是否是表
	//##ModelId=4820305401D6
	virtual ENGINE_APIF UGbool IsLinkTable();

	//! \brief 获取颜色表		
	//! \return 	UGColorTable*
	//! \remarks 		
	//##ModelId=482030550157
	virtual ENGINE_APIF UGColorTable* GetColorTable();

	//! \brief 		设置分层设色颜色表
	//##ModelId=482030550158
	virtual ENGINE_APIF UGbool SetGridColorTable(UGColorTable* pColorTable=NULL);

	//! \brief 返回数据集字符编码方式
	//##ModelId=483BB70C0138
	virtual ENGINE_APIF UGString::Charset GetCharset() const;

	//! \brief 设置数据集字符编码方式
	//##ModelId=483BB70C013A
	virtual ENGINE_APIF UGbool SetCharset(UGString::Charset c);

	//! \brief 得到RasterInfo的指针
	//##ModelId=4820305401F9
	virtual ENGINE_APIF UGDatasetRasterInfo* GetInfo();

	//##ModelId=483BB70C0119
	virtual ENGINE_APIF UGint GetBandCount() const;

	//! \brief 获取当前数据集的表名字。
	virtual ENGINE_APIF UGString GetTableName();	

	//! \brief 返回数据集类型
	//##ModelId=482030540177
	virtual ENGINE_APIF DatasetType GetType() const;

	//! \brief 返回数据集名(可以和表名不同)
	//##ModelId=482030540187
	virtual ENGINE_APIF UGString GetName() ;

	//! \brief 获取宽度
	//##ModelId=482030540222
	ENGINE_APIF UGint GetWidth() const ;

	//! \brief 获取高度
	//##ModelId=482030540224
	ENGINE_APIF UGint GetHeight() const;

	//! \brief 返回数据集的范围
	//##ModelId=482030540226
	virtual ENGINE_APIF const UGRect2D& GetBounds();

	//! \brief 设置数据集的范围
	//##ModelId=482030540232
	virtual ENGINE_APIF void SetBounds(const UGRect2D& r) ;

	//! \brief Image横向的Block列数
	//##ModelId=482030540235
	ENGINE_APIF UGint GetRowBlockCount() const ;

	//! \brief Image纵向的Block列数
	//##ModelId=482030540237
	ENGINE_APIF UGint GetColBlockCount() const ;

	//! \brief 获取裁减区域
	//##ModelId=4820305500DA
	virtual ENGINE_APIF UGGeoRegion* GetClipRegion();

	//! \brief 设置裁减区域
	//##ModelId=4820305500DC
	virtual ENGINE_APIF void SetClipRegion(UGGeoRegion* pClipRgn);

	//! \brief 判断数据集是否有某个选项信息
	//! \param nBandIndex[in] 波段索引值，默认为0
	//##ModelId=48203055000F
	virtual ENGINE_APIF UGbool HasFlag(UGint nOption) const;

	//! \brief 得到Options
	//! \param nBandIndex[in] 波段索引值，默认为0
	//##ModelId=4820305401F7
	virtual ENGINE_APIF UGint GetOptions();

	//##ModelId=482030550179
	//! \param nBandIndex[in] 获取颜色数值所在的波段索引值，默认为0 
	//! \brief 设置数据集的选项信息
	virtual ENGINE_APIF void SetOptions(UGint nOptions);

	//! \brief 获取数据集描述信息
	//! \param nBandIndex[in] 波段索引值，默认为0
	//##ModelId=4820305401A8
	virtual ENGINE_APIF UGString GetDescription() const;

	//! \brief 设置数据集描述信息
	//! \param nBandIndex[in] 波段索引值，默认为0
	//##ModelId=4820305401B5
	virtual ENGINE_APIF UGbool SetDescription(const UGString& strDesc);

	//! \brief 获取数据集附加信息
	//! \param nBandIndex[in] 波段索引值，默认为0
	//##ModelId=4820305401A8
	virtual ENGINE_APIF UGString GetExtInfo() const;

	//! \brief 设置数据集附加信息
	//! \param nBandIndex[in] 波段索引值，默认为0
	//##ModelId=4820305401B5
	virtual ENGINE_APIF UGbool SetExtInfo(const UGString& strExtInfo);

	//! \brief 返回空间数据编码方式
	//! \param nBandIndex[in] 波段索引值，默认为0
	//##ModelId=4820305401E6
	virtual ENGINE_APIF UGDataCodec::CodecType GetCodecType(UGint nBandIndex) ;
	virtual ENGINE_APIF UGDataCodec::CodecType GetCodecType() ;

	//! \brief 设置空间数据编码方式
	//! \param nBandIndex[in] 波段索引值，默认为0
	//##ModelId=4820305401F4
	virtual ENGINE_APIF UGbool SetCodecType(UGDataCodec::CodecType c,UGint nBandIndex);
	virtual ENGINE_APIF UGbool SetCodecType(UGDataCodec::CodecType c);

	//! \brief 返回最小高程
	//! \param nBandIndex[in] 波段索引值，默认为0,取出数据集最小值
	//! \在GetMinZ中调用bandIndex参数为0的接口GetMinZ;
	//##ModelId=482030540189
	virtual ENGINE_APIF UGdouble GetMinZ(UGint nBandIndex);
	virtual ENGINE_APIF UGdouble GetMinZ();
	
	//! \brief 设置最小高程
	//! \param nBandIndex[in] 波段索引值
	//! \在SetMinZ中调用bandIndex参数为0的接口setMinZ;
	//##ModelId=482030540196
	virtual ENGINE_APIF void SetMinZ(UGdouble d,UGint nBandIndex);
	virtual ENGINE_APIF void SetMinZ(UGdouble d);
	
	//! \brief 返回最大高程
	//! \param nBandIndex[in] 波段索引值，默认为0
	//! \在GetMaxZ中调用bandIndex参数为0的接口GetMaxZ;
	//##ModelId=482030540199
	virtual ENGINE_APIF UGdouble GetMaxZ(UGint nBandIndex);
	virtual ENGINE_APIF UGdouble GetMaxZ();
	
	//! \brief 设置最大高程
	//! \param nBandIndex[in] 波段索引值，默认为0
	//! \在SetMinZ中调用bandIndex参数为0的接口setMinZ
	//##ModelId=4820305401A5
	virtual ENGINE_APIF void SetMaxZ(UGdouble d,UGint nBandIndex) ;
	virtual ENGINE_APIF void SetMaxZ(UGdouble d) ;

	//! \brief 获取无效值
	//! \param nBandIndex[in] 波段索引值，默认为0
	//##ModelId=482030540261
	virtual ENGINE_APIF UGdouble GetNoValue(UGint nBandIndex=0);

	//! \brief brief 设置无值
	//! \param nBandIndex[in] 波段索引值，默认为0
	//##ModelId=482030540263
	virtual ENGINE_APIF UGbool SetNoValue(UGdouble dbNoValue,UGint nBandIndex=0);

	//! \brief Image的象素格式
	//! \param nBandIndex[in]波段索引值，默认为0
	//##ModelId=482030540265
	virtual ENGINE_APIF OGDC::PixelFormat GetPixelFormat(UGint nBandIndex=0);

	//! \brief 得到调色板
	//! \param nBandIndex[in] 波段索引值，默认为0
	//##ModelId=4820305401D8
	virtual ENGINE_APIF UGColorset GetColorset(UGint nBandIndex=0);

	//! \brief 设置调色板
	//! \param nBandIndex[in] 波段索引值，默认为0
	//##ModelId=4820305401E4
	virtual ENGINE_APIF void SetColorset(const UGColorset& Colorset,UGint nBandIndex=0);

	inline UGArray<UGImgBlocksManager>* GetImgBlocksManager() { return &m_arrImgManager; }

	//! \param nBandIndex[in] 波段索引值，默认为0
	UGint GetMaxBlockSize(UGint nBandIndex=0) const;

	//! \param nBandIndex[in] 波段索引值，默认为0
	void SetMaxBlockSize(UGint nMaxBlockSize,UGint nBandIndex=0);

	//获取波段所在的列名
	//! \param nBandIndex[in] 获取颜色数值所在的波段索引值，默认为0
	UGString GetFieldName(UGint nBandIndex = 0) const;

	//获取波段的名字
	//! \param nBandIndex[in] 获取颜色数值所在的波段索引值，默认为0
	UGString GetBandName(UGint nBandIndex = 0) const;
 
	//! \brief Block的边长
	//##ModelId=482030540271
	ENGINE_APIF UGDatasetRasterInfo::IBSizeOption GetBlockSize() const ;

	//! \brief 获取缓冲区的地址
	//##ModelId=482030540273
	virtual ENGINE_APIF UGbyte * GetBlockCache() const;

	//! \brief 获取Block的Byte容量
	//##ModelId=482030540275
	virtual ENGINE_APIF UGint GetBlockByteSize(UGint nBandIndex = 0);

	//! \brief 获取Value
	//##ModelId=4820305402AF
	//! \param bIsNeedLock 是否内部需要加锁  频繁调用发现性能在加锁上损失太大 
	// 故对没必要多线程并且频繁调用此接口的提供bIsNeedLock参数来做控制
	//! \param nBandIndex[in] 波段索引值，默认为0
	virtual ENGINE_APIF UGdouble GetValue(UGint X,UGint Y, UGint nBandIndex=0, UGbool bIsNeedLock = TRUE);

	//! \brief 设置Value
	//! \param nBandIndex[in] 波段索引值，默认为0
	//##ModelId=4820305402CE
	virtual ENGINE_APIF void SetValue(UGint X,UGint Y,UGdouble dValue,UGint nBandIndex =0);

	//! \brief 得到扫描线
	//! \param nBandIndex[in] 波段索引值，默认为0
	//##ModelId=4820305402DE
	virtual ENGINE_APIF UGbool GetScanline(UGint nRowIndex,UGImgScanline& ScanLine, UGint nStartCol = 0, UGint nWidth=0,UGint nBandIndex=0);

	//! \brief 通过行列索引设置扫描线
	//! \param nBandIndex[in] 波段索引值，默认为0
	//##ModelId=4820305402EE
	virtual ENGINE_APIF UGbool SetScanline(UGint nRowIndex,UGint nColIndex,
		const UGImgScanline& ScanLine,UGint nBandIndex=0) ;

	//! \brief 通过Block缓存数据
	//! \param nBandIndex[in] 波段索引值，默认为0
	//##ModelId=48203054034B
	virtual ENGINE_APIF UGbool CacheByBlock(UGint nLeft,UGint nTop,
		UGint nWidth,UGint nHeight,UGint nBandIndex=0) ;

	ENGINE_APIF UGbool CacheByBlock(UGint nLeft,UGint nTop,
		UGint nWidth,UGint nHeight, UGArray<UGImgBlockRef>& arrRefImgBlock, UGint nBandIndex=0);

	//! \brief 获取Block,pImgBlock内存在这个函数中分配，系统自动释放数据块
	//! \param nBandIndex[in] 波段索引值，默认为0
	//##ModelId=48203054030D
	virtual ENGINE_APIF UGbool GetBlockAt( UGint nBlockRow,UGint nBlockCol, UGImgBlockRef &refImgBlock,UGint nBandIndex=0);

	//! \brief 获取Block,pImgBlock内存在这个函数中分配，系统自动释放数据块
	//! \attention 为了支持线程案例，将此方法改为Protected
	//! \param nBandIndex[in] 获取颜色数值所在的波段索引值，默认为0
	//##ModelId=48203054030D
	virtual ENGINE_APIF UGbool GetBlockAt(UGint nBlockRow,UGint nBlockCol,
		UGImgBlock*& pImgBlock,UGint nBandIndex=0);

	//! \brief 读入指定块数据
	//! \param nBandIndex[in] 波段索引值，默认为0
	//##ModelId=48203055002E
 	virtual ENGINE_APIF UGImgBlock* LoadBlock(UGint nRowBlock,UGint nColBlock,UGint nBandIndex=0);

	//! \brief  从数据源取影像块
	//! \param lRowBlock  影像块的行索引
	//! \param lColBlock 影像块的列索引
	//! \param pImgBlock  返回影像块的指针
	//! \param nBandIndex[in] 获取颜色数值所在的波段索引值，默认为0
	//! \return 是否正确取得影像块，返回值为FALSE时pImgBlock应该为空指针
	virtual ENGINE_APIF UGbool LoadBlock(UGint lRowBlock,UGint lColBlock,
		UGImgBlock* pImgBlock,UGint nBandIndex=0){ return FALSE; };

	//! \brief  一次缓存多行多列影像块
	//! \param nLeft  起始列
	//! \param nTop   起始行
	//! \param nWidth  缓存列宽
	//! \param nHeight 缓存行高
	//! \param dictImgBlock 预先开辟的影像块内存
	//! \param nBandIndex[in] 波段索引值，默认为0
	//! \return 是否正确取得影像块，返回值为FALSE时pImgBlock应该为空指针
	virtual ENGINE_APIF UGbool LoadBlock(UGint nLeft, UGint nTop, UGint nWidth, UGint nHeight, 
		UGDict<UGint, UGImgBlock*>& dictImgBlock, UGint nBandIndex);

	//! \brief pImgBlock存盘
	//! \param nBandIndex[in] 波段索引值，默认为0
	//##ModelId=482030550032
	virtual ENGINE_APIF UGbool SaveBlock(UGImgBlock* pImgBlock,UGint nBandIndex=0);

	//! \param nBandIndex[in] 波段索引值，默认为0
	virtual ENGINE_APIF UGbool SaveAllBlocks(UGint nBandIndex=0);

	//! \brief 多个pImgBlock存盘
	//##ModelId=482030550032
	virtual ENGINE_APIF UGbool SaveBlocks(UGArray<UGImgBlock*>& pAryImgBlock, UGint nBandIndex = 0);

	//! \brief 卸载指定Block
	//! \param nBandIndex[in] 波段索引值，默认为0
	//##ModelId=482030540242
	virtual ENGINE_APIF UGbool ReleaseBlock(UGint nIndex,UGint nBandIndex=0);

	//! \brief 卸载所有已放入内存的块
	//! \param nBandIndex[in]波段索引值，默认为0
	//##ModelId=482030540251
	virtual ENGINE_APIF void ReleaseAllBlock(UGint nBandIndex=0, UGbool bPyramdLevel=TRUE);

	ENGINE_APIF void ReleaseBlockRef(UGImgBlock* pImgBlock, UGint nBandIndex);

#if PACKAGE_TYPE==PACKAGE_UGC
	//##ModelId=482030550012
	//! \brief 建立影像金字塔。
	//! \param bShhowProgress 是否显示进程条[in]。
	//! \return 是否建立成功。
	virtual ENGINE_APIF UGbool BuildPyramid(UGbool bShhowProgress);	

	virtual ENGINE_APIF UGbool BuildPyramidTiersOnly(bool bShowProgress){return false;};

	//按范围更新金字塔
	virtual ENGINE_APIF UGbool UpdatePyramid(const UGRect2D &rect);	
	UGbool UpdatePyramidIner(const UGRect2D& rcRect);

	//##ModelId=482030550015
	//! \brief 移除金字塔。
	//! \return 是否移除成功。
	virtual ENGINE_APIF UGbool RemovePyramids();	

	//##ModelId=483BB70C0102
	//! \brief 是否建立了影像金字塔。
	//! \return 是否建立成功。
	virtual ENGINE_APIF UGbool IsBuildPyramid() const;	

	//! \brief  从数据源取得如下所示的四个相邻的影像块
	//!
	//!                   			 nColIndex
	//!                  	   	+------------+------------+
	//!       		   	|    LT	|    RT           |
	//!                              	|        		|  	           |
	//!        	nRowIndex  |------------+------------|
	//!                 		|    LB       	|    RB	|
	//!                 		|          	|  	           |
	//!                  		+------------+------------+
	//!   \mark 如果获取为数据集的边界，内部应该设置好影像块的合法宽度和高度，
	//!   	         倘若获取的影像块完全超过了数据集的范围，合法高宽均为0，但影像块指针不为空
	//! \param nBandIndex[in] 波段索引值，默认为0
	virtual ENGINE_APIF void LoadRectBlocks(UGint nRowIndex,UGint nColIndex,
		UGImgBlock*&pImgBlockLT,UGImgBlock*&pImgBlockRT,
		UGImgBlock*&pImgBlockLB,UGImgBlock*&pImgBlockRB,UGint nBandIndex=0);

	//! \brief   创建影像金字塔的层级子数据集
	//! \param rInfo    创建子数据集的相关信息
	//! \param nLevel   为数据集创建第几层的金字塔，数据集自身为0层，依次递增
	//! \return  返回创建的子数据集指针
	virtual ENGINE_APIF UGDatasetRaster* Tier1(UGDatasetRasterInfo &rInfo,UGint nLevel){ return NULL; };

	//! \brief   创建影像金字塔的层级子数据集
	//! \param nLevel   为数据集创建第几层的金字塔，数据集自身为0层，依次递增
	//! \param lWidth   创建子数据集的影像块宽度
	//! \param lHeight    创建子数据集的影像块高度
	//! \param eBlockSize    创建子数据集的影像块大小
	//! \param nOptions    创建子数据集的选项信息
	//! \return	 返回创建的子数据集指针
	//! \param nBandIndex[in] 波段索引值，默认为0
	virtual ENGINE_APIF UGDatasetRaster* Tier(UGint nLevel, UGint lWidth, UGint lHeight, 
		UGDatasetRasterInfo::IBSizeOption eBlockSize, UGint nOptions){ return NULL; };

	//!	\brief	清除掉创建不完全的金字塔
	virtual ENGINE_APIF void ClearIncompletePyramid(){};

	//##ModelId=482030550001
	//! \brief	得到某层金字塔数据集
	//! \remarks 这个函数原来是私有函数，public只用做动态投影时调用，其它若需使用请询问作者
	ENGINE_APIF  virtual UGDatasetRaster * GetPyramidTier(UGint nImgWidth,UGint nDeviceWidth);

	//##ModelId=482030550000
	//! \brief 当前数据集的影像金字塔的各层指针数组
	//! \remarks 这个函数原来是私有函数，public只用做动态投影时调用，其它若需使用请询问作者
	ENGINE_APIF UGDatasets& GetPyramidDatasets();

#endif 

	//! \brief 得到栅格数据的极值。
	//注意：如果栅格数据的值发生变化，此函数不会重新计算极值，
	//必须先调用CalculateExtremum，重新计算极值才可以。
	//! \param nBandIndex[in] 波段索引值，默认为0
	//##ModelId=4820305401B8
	virtual ENGINE_APIF void GetExtremum(UGdouble& dMax, UGdouble& dMin,UGint nBandIndex=0);

	//##ModelId=482030550148
	//! \param nBandIndex[in] 波段索引值，默认为0
	//! \计算所有波段的极值
	virtual ENGINE_APIF UGbool CalculateExtremum(
		UGDatasetRaster * pDtGrid, 
		UGdouble &dMax, 
		UGdouble& dMin, 
		UGPoint * pMaxPt = NULL, 
		UGPoint * pMinPt = NULL,
		UGProgress* pProgress = NULL,UGint nBandIndex=0);

	//##ModelId=48203055014E
	//! \param nBandIndex[in] 波段索引值，默认为0
	//! \计算所有波段的极值
	virtual ENGINE_APIF UGbool CalculateExtremum(
		UGdouble &dMax,
		UGdouble& dMin, 
		UGRecordset * pRsRegion = NULL,
		UGPoint * pMaxPt = NULL, 
		UGPoint * pMinPt = NULL,
		UGProgress* pProgress = NULL,UGint nBandIndex=0);

	//!	\brief	栅格数据集的追加
	//##ModelId=482030550138
	virtual ENGINE_APIF UGbool Append(UGDatasetRaster *pSrcRaster);

	//栅格数据快速复制
	virtual ENGINE_APIF UGbool CopyFromFile(UGDatasetRaster *pSrcDataset);

	//! \brief 设置是否在SaveBlock时计算极值,设置为TRUE时，SaveBlock时会自动计算极值，否则由用户自己维护数据集的极值
	virtual ENGINE_APIF void SetAutoCalculateExtremum(UGbool bAutoComputeExtremum){m_bAutoComputeExtremum = bAutoComputeExtremum; };

	//! \brief 		获取影像的地理坐标索引
	//! \return 	UGRect2D
	//! \remarks 		
	//##ModelId=482030550109
	ENGINE_APIF UGRect2D GetGeoReference();	

	//! \brief 		设置影像的地理坐标索引
	//! \return 	void
	//! \param 		&rc2GeoReference
	//! \remarks 		
	//##ModelId=4820305500EC
	virtual ENGINE_APIF void SetGeoReference(const UGRect2D &rc2GeoReference);

	//视口变换.===========================================================
	//##ModelId=482030550035
	ENGINE_APIF void PrepareGeoRefrence();		//初始化GeoRefernce

	//! \brief 象素坐标转为地理坐标
	//##ModelId=48203055004E
	ENGINE_APIF void ImgToXY(const UGPoint& pntImg,UGPoint2D& pntXY);

	//! \brief 象素坐标转为地理坐标
	//##ModelId=48203055007D
	ENGINE_APIF void ImgToXY(const UGRect& rectImg,UGRect2D& rectXY);

	//! \brief 地理坐标转为象素坐标
	//##ModelId=48203055009C
	ENGINE_APIF void XYToImg(const UGPoint2D& pntXY,UGPoint& pntImg);

	//! \brief 地理坐标转为象素坐标
	//##ModelId=4820305500BB
	ENGINE_APIF void XYToImg(const UGRect2D& rectXY,UGRect& rectImg);

	//栅格与影像是类似但是不同的
	//##ModelId=482030550196
	ENGINE_APIF void GridToXY(const UGPoint& pntImg,UGPoint2D& pntXY);

	//##ModelId=4820305501B5
	ENGINE_APIF void XYToGrid(const UGPoint2D& pntXY,UGPoint& pntImg);

	//##ModelId=4820305500EA
	ENGINE_APIF UGDatasetRaster* GetParentDataset() const;

	//##ModelId=482030550167
	ENGINE_APIF void SetParentDataset(UGDatasetRaster* pParent) ;

	//! 计算像素边长的移位操作位数
	ENGINE_APIF UGbool ComDivAndMod();

	//! \brief 栅格数据集投影转换
	//pSrcDatasetRaster Input  栅格数据 
	//pDesDataSource Output 栅格数据源 	
	//pClipRegion 裁减区域
	//strDesRasterName Output 栅格数据 	
	ENGINE_APIF UGDatasetRaster* PJConvert(UGRefTranslator *pRefTranslator,
		const UGString& strDesRasterName, UGdouble dResolution = 0.0, 
		UGGeoRegion* pClipRegion=NULL, UGDataSource* pDesDataSource = NULL,
		UGbool bShowProgress = TRUE);

	ENGINE_APIF UGDatasetRaster* PJForward(UGPrjCoordSys* pPJCoordsys,
		const UGString& strDesRasterName, UGdouble dResolution = 0.0, 
		UGGeoRegion* pClipRegion=NULL, UGDataSource* pDesDataSource = NULL,
		UGbool bShowProgress = TRUE);

	ENGINE_APIF UGDatasetRaster* PJInverse(UGPrjCoordSys* pPJCoordsys,
		const UGString& strDesRasterName, UGdouble dResolution = 0.0, 
		UGGeoRegion* pClipRegion=NULL, UGDataSource* pDesDataSource = NULL,
		UGbool bShowProgress = TRUE);

	//计算栅格数据集的ValueTable
	ENGINE_APIF UGDatasetVector* BuildValueTable(UGDataSource* pOutputDs,UGString& strName);

public:

	// 得到栅格信息
	virtual ENGINE_APIF UGDict<UGint, UGRasterStatisticsInfo> GetStatisticsInfo();

	//! 统计栅格信息
	//! \param nBandIndex[in] 波段索引值，默认为0
	//! \默认统计所有极值
	virtual ENGINE_APIF UGDict<UGint, UGRasterStatisticsInfo> BuildStatistics();

	//从数据库查询并返回
	//! \param nBandIndex[in] 波段索引值，默认为0
	virtual ENGINE_APIF UGbool GetDistinctValue(UGArray<UGdouble> &valueArray, UGArray<UGint> &countArray,UGint nBandIndex=0);
	//删除数据库中的相关记录
// 	virtual ENGINE_APIF UGbool ClearDistinctValueCount();

	// 栅格信息格式化成XML
	ENGINE_APIF UGString StatisticsInfoToXML();

	ENGINE_APIF void StatisticsInfoFromXML(const UGString& strXML);

protected:

	//! \param nBandIndex[in] 波段索引值，默认为0
	void GetCurBandStatInfo(UGRasterStatisticsInfo& rsi,UGint nBandIndex=0);

	//! \获取当前波段索引的统计信息
	//! \param nBandIndex[in] 波段索引值，默认为0
	//! \param info 栅格统计信息
	ENGINE_APIF void GetBaseStatisticsInfo(UGRasterStatisticsInfo& info,UGint nBandIndex=0);

// 	StaticsticsStatus m_staticsticsStatus;
	UGDict<UGint, UGRasterStatisticsInfo> m_dictRasterStatInfo;

	void ParserStatInfoXML(UGMarkup& strXML, UGRasterStatisticsInfo& statInfo, UGbool isToXML);

// 	virtual ENGINE_APIF UGbool CreateStatistics();
// 	virtual ENGINE_APIF UGRecordset *GetArrtibuteTable();
// 	virtual ENGINE_APIF UGRecordset *GetStatistics();

	UGdouble CalcAvgValue(UGdouble a, UGdouble b, UGdouble c, UGdouble d);

protected:

	//##ModelId=482030550169
	//! \brief 将指定的影像块编码加载到本地缓存。
	//! \param pImgBlock 指定的影像块[in]。
	//! \return 返回本地缓存的大小。
	ENGINE_APIF UGint EncodeBlock(UGImgBlock * pImgBlock,UGint nBandIndex=0);

	//##ModelId=48203055016B
	//! \brief 将指定的字节流经过解码加载到影像块当中。
	//! \param pImgBlock 获取的影像块[in]。
	//! \param pByte 字节流指针[in]。
	//! \param nRawSize 字节流大小[in]。
	ENGINE_APIF UGbool DecodeBlock(UGImgBlock * pImgBlock, const UGbyte * pByte,UGint nRawSize,UGint nBandIndex=0);	

	//! \brief 初始化一个空块
	ENGINE_APIF UGbool InitBlock(UGint nRow,UGint nCol,UGint nBandIndex = 0);

	//! \brief 
	ENGINE_APIF UGbool InitBlock(UGint nRow,UGint nCol, UGImgBlock* pImgBlock,UGint nBandIndex = 0);

	//! \brief 获取BlockManager中所有的被修改过还未保存的块分成已存在和未存在的两组
	UGbool StatisticsBlocks(UGArray<UGImgBlock*> & updateBlocks ,
		UGArray<UGImgBlock*> & insertBlocks, UGint nBandIndex = 0);

public:

	//! \brief 向当前的多波段栅格数据集增加波段。
	//! \param arrRaster 要增加的栅格数据集指针数组[in]。
	//! \return 。
	//! \remarks 增加的数据集指针数组指向的是UGC原来的栅格数据集。
	//! \attention arrRaster和当前数据集必须在宽度，高度，数据集类型，影像分块变长，影像行数，影像列数严格要求一致。
	ENGINE_APIF UGbool AppendRaster(const UGArray<UGDatasetRaster *>& arrRaster);	

	//! \brief 向多波段栅格数据集追加多个波段。
	//! \param &BandRaster [in] 要追加的波段所在的多波段栅格数据集。
	//! \param nBandIndex [in] 要追加的波段索引。
	//! \attention pBandRaster和当前数据集必须在宽度，高度，数据集类型，影像分块边长，影像行数，影像列数，数据集范围严格要求一致。。
	virtual ENGINE_APIF UGbool AppendBand(UGDatasetRaster* pBandRaster,const UGArray<UGint>& arrBandIndex);

	//! \brief 删除某个波段。
	//! \param nBandIndex [in] 波段索引。
	//! \remarks 如果删除的是当前制定波段，自动移动到第一个波段。
	virtual ENGINE_APIF UGbool DeleteBand(UGint nBandIndex);  	

	//! \brief 导出多个栅格数据集。
	//! \param arrBandIndex 导出的波段索引[in]。
	//! \param arrRaster 导出的栅格数据集列表[in]。
	//! \param arrName 导出的栅格数据集类的名字列表[in]。
	//! \remarks 这里的数据集是指UGC原来的栅格数据集，。
	//! \attention arrName的数量如果小于arrBandIndex，则采用默认的名字。
	//!            如果 arrBandIndex如果没有设置，则导出当前数据集的所有波段。
	virtual ENGINE_APIF UGbool ExportRaster(const UGArray<UGint>& arrBandIndex, UGArray<UGDatasetRaster *>& arrRaster,
		UGArray<UGString>& arrName, UGDataSource* pOutputDatasource = NULL);

public:

	//! \brief 创建MrSID的外部连接,
	//! \brief bFileMode是指以文件共享的方式还是存储在数据库中的方式
	//##ModelId=48203055001F
	ENGINE_APIF UGbool CreateMrSIDLink(const UGString& strImgPathName,
		UGbool bFileMode = TRUE);

	//! \brief 创建ECW的外部连接
	//##ModelId=482030550022
	ENGINE_APIF UGbool CreateECWLink(const UGString& strImgPathName,
		UGbool bFileMode = TRUE);

	//! \brief 合法关联文件检查
	//##ModelId=482030550025
	ENGINE_APIF UGbool IsValidExternalFileLink() ;

	//! \brief 取得关联文件名
	//##ModelId=482030550026
	ENGINE_APIF UGString GetLinkFileName() const;


public:

	//! \brief 获取Pixel
	//! \remarks 对于多波段，如果当前索引小于0，则跟据当前BandCombineMode获取当前的像素颜色
	//! \param nBandIndex[in] 波段索引值，默认为0
	//##ModelId=482030540277
	virtual ENGINE_APIF UGColor GetPixel(UGint X,UGint Y ,UGint nBandIndex=0);

	//! \brief 获取Pixel
	virtual ENGINE_APIF UGColor GetPixel(UGint X,UGint Y,UGArray<UGint>& nIndex, ImgColorSpace nColorSpace = ICS_RGB);
	
	//! \brief 设置Pixel
	//! \remarks 对于多波段，如果当前索引小于0，则跟据当前BandCombineMode
	//! \param nBandIndex[in] 波段索引值，默认为0
	//设置
	//##ModelId=482030540290
	virtual ENGINE_APIF void SetPixel(UGint X,UGint Y,UGColor nColor,UGint nBandIndex=0);
		
	//! \brief 通过地理范围缓存数据
	//##ModelId=48203054032C
	virtual ENGINE_APIF UGbool CacheByGeoRef(const UGRect2D& rc2FocusedArea);

	//! \brief 通过Pixel缓存数据
	//! \param nBandIndex[in] 波段索引值，默认为0
	//##ModelId=48203054035C
	virtual ENGINE_APIF UGbool CacheByPixel(UGint nLeft,UGint nTop,
		UGint nWidth,UGint nHeight,UGint nBandIndex=0);

	//! \brief 根据不同的像素格式计算金字塔像素值
	ENGINE_APIF void GetImgPyramidValue(OGDC::PixelFormat ipf, UGbool bIndexedColor, UGuint a,
		UGuint b, UGuint c, UGuint d, UGuint& e);

	//! \brief 通过地理范围估计缓存数据的大小
	//##ModelId=48203054037A
	ENGINE_APIF UGint EstimateCachSizeByGeoRef(const UGRect2D& rc2FocusedArea);

	//! \brief 通过Block估计缓存数据的大小
	//##ModelId=482030540399
	virtual ENGINE_APIF UGint EstimateCachSizeByBlock(UGint nLeft,UGint nTop,
		UGint nWidth,UGint nHeight);

	//! \brief 通过Pixel估计缓存数据的大小
	//##ModelId=4820305403B9
	virtual ENGINE_APIF UGint EstimateCachSizeByPixel(UGint nLeft,UGint nTop,
		UGint nWidth,UGint nHeight) ;

	//##ModelId=483BB70C012C
	//! \brief 获取显示的影像块。
	//! \param rcView 获取的显示的影像块大小[in]。
	//! \param nDeviceWidth 设备宽度[in]。
	//! \param nDeviceHeight 设备高度[in]。
	//! \return 返回显示的影像块。
	virtual ENGINE_APIF UGImgBlock* GetViewBlock(const UGRect2D& rcView, UGint nDeviceWidth, UGint nDeviceHeight);	

	//! \brief 设置像素采样是否是闭区间
	virtual ENGINE_APIF void SetSamClosedInterfal(UGbool bValue);

	//! \brief 获取显示的影像块。
	//! \param rcView 获取的显示的影像块大小[in]。
	//! \param nDeviceWidth 设备宽度[in]。
	//! \param nDeviceHeight 设备高度[in]。
	//! \param bFinished 当前此次获取影像块是否已经得到全部数据[out]。
	//! \return 返回显示的影像块。
	virtual ENGINE_APIF UGImgBlock* GetViewBlock(const UGRect2D& rcView, UGint nDeviceWidth, UGint nDeviceHeight, UGbool &bFinished) { bFinished = TRUE; return GetViewBlock(rcView, nDeviceWidth, nDeviceHeight); }

	//! \brief 获取显示的影像块。
	//! \param rcView 获取的显示的影像块大小[in]。
	//! \param nDeviceWidth 设备宽度[in]。
	//! \param nDeviceHeight 设备高度[in]。
	//! \param nDeviceHeight 指定波段索引号（由SetBandIndex指定），仅对多波段起作用[in]。
	//! \return 返回显示的影像块。
	virtual ENGINE_APIF UGImgBlock* GetViewBlock(const UGRect2D& rcView, UGint nDeviceWidth, UGint nDeviceHeight, UGint nBandIndex);

	//! \brief 返回当前影像的色彩空间
	virtual ENGINE_APIF ImgColorSpace GetColorSpace() const;
	
	//! \brief 设置当前影像的色彩空间
	virtual ENGINE_APIF void SetColorSpace(ImgColorSpace nColorSpace);

//{{modified by qianjn in 2008-11-24 18:59:19 修改原因：

	//  [added by zhangshuo at 6/8/2010]
	virtual ENGINE_APIF UGDatasetRaster* GetMemDataset(){return NULL;};

	//供更新金字塔使用：数据表是否为空
	virtual ENGINE_APIF UGbool IsBlockTableEmpty();
	//供更新金字塔使用：清空数据表表
	virtual ENGINE_APIF UGbool Truncate();

// 	//##ModelId=482030550001
// 	//! \brief	得到某层金字塔数据集
// 	//! \remarks 这个函数原来是私有函数，public只用做动态投影时调用，其它若需使用请询问作者
// 	ENGINE_APIF UGDatasetRaster * GetPyramidTier(UGRect2D rectView,UGint nDeviceWidth,UGint nDeviceHeigth){return NULL;}
//     
	//栅格数据支持显示取消
	void SetGetViewBlockCallBackProc(GETVIEWBLOCKCALLBACKPROC pFun, UGlong pDrawing, UGlong pWndH);

protected:

//}}{modified by qianjn in 2008-11-24 18:59:19 修改原因：
	
	//##ModelId=48203055017C
	//! \brief 获取指定位置的的影像块
	//! \param nIndex [in]。
    //UGImgBlock * GetBlockByPos(UGint nIndex);	

	//##ModelId=482030550186
	//! \brief 设置某个位置影像块块。
	//! \param nIndex 影像块的位置，主要指在blockmanager[in]。
	//! \param *pImgBlock 影像块指针[in]。
	ENGINE_APIF UGbool	SetBlockByPos(UGint nIndex,UGImgBlock *pImgBlock, UGint nBandIndex = 0);	
	//! \brief 获取影像的列数
	//##ModelId=483BB70C0148
	ENGINE_APIF UGint GetColBlocks();	
	//! \brief 获取影像的行数
	//##ModelId=483BB70C0149
	ENGINE_APIF UGint GetRowBlocks();	

	// 得到缺省的变换后的栅格大小
	ENGINE_APIF double GetPJConvertCellSize(UGRefTranslator* pPJTranslator);

	ENGINE_APIF UGGeoRegion* GetPJConvertRegion(UGRefTranslator* pPJTranslator,
		UGGeoRegion* pClipRegion);

public:
	//CHENZhao UGC.USR.104.017 栅格数据集属性表。统计信息功能
// 	virtual ENGINE_APIF StaticsticsStatus GetStatisticsStatus();
// 	virtual ENGINE_APIF void SetStatisticsStatus(StaticsticsStatus ss);
// 	virtual ENGINE_APIF StaticsticsStatus RefreshStatisticsStatus();

// 	enum StaticsticsStatus{STATISTICS_OK= 1,STATISTICS_NO= 0,STATISTICS_DIRTY= 2};
// 
// 	//计算栅格值统计,会删掉之前的值，写到数据库中
// 	virtual ENGINE_APIF UGbool RefreshDistinctValueCount();
// 	//根据实际情况计算并返回
// 	virtual ENGINE_APIF UGbool CountDistinctValue(UGArray<UGdouble> &valueArray, UGArray<UGint> &countArray);
// 

public:	

	//! \brief 修改当前波段的索引
	//! \param nBandIndex nBandIndex为修改后索引
	//! \remarks 注意，这个接口在单用户下面用，尤其在多用户的情况下对同一个数据集操作，可能会有错误
	//!          如果当前索引不合法，或者这个索引重复，则修改失败
	virtual ENGINE_APIF UGbool ModifyBandIndex(UGint nBandIndex);
	
	//##ModelId=483BB70C0120
	//! \brief 设置当前线程的色彩空间模式。
	//! \param aryBand 色彩空间模式的波段选择[in]。
	//! \param nColorSpace 色彩空间模式[in]。
// 	virtual ENGINE_APIF void SetBandCombineMode(const UGArray<UGint>& aryBand, ImgColorSpace nColorSpace);
	
	//##ModelId=483BB70C0128
	//! \brief 获取当前线程的色彩空间模式。
	//! \param aryBand 波段选择[in]。
	//! \param nColorSpace 色彩空间模式[in]。
	//! \remarks 必须提前设置能获取到当前的色彩空间模式。
// 	virtual ENGINE_APIF UGbool GetBandCombineMode(UGArray<UGint>& aryBand, ImgColorSpace& nColorSpace);	

	//! \brief 获得色彩显示模式。
// 	ENGINE_APIF UGImageAccessMode GetReadMode() const;	
	//! \brief 设置色彩显示模式。
	//! \param ReadMode [in]。
	//! \remarks 当它是单波段显示模式的时候，他会根据 当前波段索引m_nIndexBand。
	//           只显示当前波段信息，
	//           当它是混合色彩显示模式的时候，他会根据当前的色彩格式和显示的
	//            波段进行显示
	//! \attention
// 	ENGINE_APIF void SetReadMode(UGImageAccessMode ReadMode);

	//! \brief 对于bit1,bit4,bit8在创建时需要加上默认的调色板。
	//! \param &srcInfo [in]UGDatasetRasterInfo 对象。
	//! \param &destInfo [in]UGDatasetRasterInfo 对象。
	//! \attention 根据srcInfo的象素类型不同,填充destInfo颜色值。
	ENGINE_APIF void FillColorset(const UGDatasetRasterInfo &srcInfo,UGDatasetRasterInfo &destInfo);
	

private:
	//##ModelId=482030550189
	//! \param nBandIndex[in] 获取颜色数值所在的波段索引值，默认为0
	ENGINE_APIF UGbool CalculateExtremumByRegion(UGdouble &dMax,
		UGdouble& dMin,
		UGGeoRegion * pRegion = NULL, 
		UGPoint * pMaxPt = NULL, 
		UGPoint * pMinPt = NULL,
		UGProgress* pProgress = NULL,UGint nBandIndex=0) ;
public:	

public:
	//! \brief 当前地理坐标到影像坐标的映射比例.
	//##ModelId=4820305501D4
	UGSize2D m_imgRatio;

 #if PACKAGE_TYPE==PACKAGE_UGC

	//##ModelId=482030550216
	UGColor m_NoDataStyle;

	//##ModelId=482030550224
	UGbyte m_btBackColorTolerance;

	//##ModelId=482030550225
	UGColor m_BackColor;

	// 获取是否初始背景透明
	virtual bool IsTransparentBack() { return false; }

#endif // end declare ugc sdk

	//!\brief 标识栅格数据集之间的复制是否为同一编码，如果编码相同，则直接读块
	UGbool m_bCopyWithSameCodecType;
	
	//! \brief 是否是以释放内存的方式修改缓存大小
	UGbool m_bChangeCacheByDel;

	//! \brief 定义blockmanager缓存block大小，默认是100块
	UGint m_nCacheSize;

protected:

	UGArray<UGImgBlocksManager> m_arrImgManager;

 	//! \brief 栅格分层设色颜色集
	//##ModelId=4820305501D5
 	UGColorTable m_ColorTable;

	//! \brief Raster信息
	//##ModelId=4820305501D6
	UGDatasetRasterInfo m_RasterInfo;
	
	//! \brief 本地内存中缓存的Block集合
	//##ModelId=4820305501D7
// 	UGImgBlocksManager m_ImgManager; 
	
	//! \brief 裁减区域
	//##ModelId=4820305501E4
	UGGeoRegion* m_pClipRgn;
	
	//##ModelId=4820305501E5
	UGRect2D m_rcViewGeoRef;	//显示参考坐标

	//##ModelId=4820305501E6
	UGbool m_bGeoReferencePrepared;	//地理参考坐标是否以

	//##ModelId=4820305501E7
// 	UGMutex m_mutexBlock;

	//! \brief 如果金字塔影像库，必须填充各层影像数据集
	//##ModelId=4820305501F4
	UGDatasets m_PyramidDatasets;

	//! \brief 如果是本数据集是金字塔的一层，必须给父图层的指针
	//##ModelId=4820305501F5
	UGDatasetRaster* m_pParentDataset;

	//! \brief 文件的相对路径,连接外部文件使用
	//##ModelId=4820305501F6
	UGString m_strLinkFileName;
	
	//! \brief 存放当前Block的指针
	//##ModelId=4820305501F7
	UGImgBlock *m_pBlock; 
	
	//! \brief 用于压缩的缓存区
	//##ModelId=482030550203
	UGbyte * m_pBlockCache;

	//! \brief 缓存区的大小
	//##ModelId=482030550204
	UGuint m_nBlockCacheSize;

	//##ModelId=483BB70C0167
	UGString::Charset m_nCharset;

	//##ModelId=483BB70C0157
// 	UGint m_nBandIndex;

	//! \brief 关于读取影像时的读取模式和选取的波段
//	UGImageAccessMode m_nReadMode;

	//! \brief 当前影像的默认色彩空间
	ImgColorSpace  m_nColorSpace;

	//! GetValue中去掉了除法和取余用移位操作代替
	UGuint m_nDiv;
	//! GetValue中去掉了除法和取余用移位操作代替
	UGuint m_nMod;
	//! 记录着m_nDiv,m_nMod是否准备好
	UGbool m_bInitImg;

	//栅格数据集显示支持取消 回调
	GETVIEWBLOCKCALLBACKPROC m_pGetViewBlockCallBackFunc;
	//栅格数据集显示支持取消 回调参数
	UGlong m_pWndH;
	//栅格数据集显示支持取消 回调参数
	UGlong m_pDrawingH;
	//! \brief 栅格属性表数据集
// 	UGDatasetVector *m_pVATDataset;

	//!\brief GetViewBlock时是否使用闭区间，目前像素获取使用左闭右开区间，不适合三维应用
	UGbool m_bSampleClosedInterval;

	//! \brief 该属性控制在SaveBlock是否计算极值,当对栅格进行修改时，知道数据集的极值可以直接设置，不需要在保存是再计算一遍，提供保存的效率	
	UGbool m_bAutoComputeExtremum;

};

}

#endif

