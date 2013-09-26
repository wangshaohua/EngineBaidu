/* 
	\file UGSpatialIndex.h
	\brief	负责管理索引的一切
			包括索引的创建，重建，删除
			包括创建索引之前对数据的分析，创建索引，管理索引以及对索引的应用
			包括引擎是否支持某种索引的控制

	\author zhouqin
	\attention
	Copyright(c) 2008 SuperMap GIS Technologies,Inc.<br>
	All Rights Reserved
	<b>更新说明：。</b>
	<em>1、第一条说明。</em>
*/
//////////////////////////////////////////////////////////////////////
#ifndef UGENGTOOLKIT_H
#define UGENGTOOLKIT_H

#include "Stream/ugdefs.h"
#include "Engine/UGEngDefs.h"
#include "Engine/UGDatasetVectorInfo.h"
#include "Engine/UGDataset.h"
#include "Engine/UGDatasetRasterInfo.h"
#include "Engine/UGDatasetRaster.h"
#include "Base/ogdccolordef.h"

#if !defined SYMBIAN60 && !defined  OS_ANDROID && !defined (IOS)
// #include "Engine/UGDatasetMultiBandRaster.h"
#endif
//#include "Workspace/UGWorkspace.h"
namespace UGC {

//##ModelId=48203051014A
class ENGINE_API UGEngineToolkit
{
private:
	//##ModelId=482030510157
	UGEngineToolkit();
	//##ModelId=482030510158
#ifdef SYMBIAN60
	~UGEngineToolkit();
#else
	virtual ~UGEngineToolkit();
#endif
	

public:
	//modified by macx 2008.8.4 工作空间加密
	//! \brief DsConnect ToXML
	//##ModelId=48203051015A
	static UGString DSConnectToXML(const UGDsConnection& dsc, UGint nVersion, UGString strRefPath=_U(""), const UGString& strPWD = (_U("")));
	
	//modified by macx 2008.8.4 工作空间解密
	//! \brief DsConnect FromXML
	//##ModelId=482030510168
	static UGbool DSConnectFromXML(UGDsConnection& dsc, const UGString& strXML,UGint nVersion, UGString strRefPath=_U(""), const UGString& strPWD = (_U("")));

	//##ModelId=483BB7090157
	static UGbool AppendBlock(UGImgBlock* pResBlock, UGImgBlock* pSrcBlock); 

	/////////////////////////////	FieldInfo 相关方法	////////////////////////////////////////////
	//! \brief 是否是几何字段
	//##ModelId=483BB709015B
	static UGbool IsGeoField(UGString strName);

	//! \brief 是否是系统字段
	//##ModelId=483BB7090167
	static UGbool IsSystemField(UGString strName);

	//! \brief 是否是SmID字段
	//##ModelId=483BB709016A
	static UGbool IsSmID( UGString strName);

	//! \brief 是否是系统UUID字段
	static UGbool IsUUID(UGString strName);

	//##ModelId=483BB709016D
	static void SetFieldSign(UGFieldInfo& fieldInfo);
	/////////////////////////////	FieldInfo 相关方法	////////////////////////////////////////////

	//! \brief 计算范围边界网格
	//! \param &rcBounds [in]。
	//! \param &aryGrids [out]。
	//! \return T
	//! \remarks 有几层就计算几层，aryGrids按照左下，右上记录
	//! \attention 。
	//##ModelId=483BB7090170
	static UGbool FindQueryGrids(UGDatasetVectorInfo* sInfo, UGRect2D &rcBounds,UGArray<UGPoint> &aryGrids);

	//! \brief	Colorset的存取
    //! \brief 低级错误啊
	//##ModelId=483BB709017B
	static UGbool ColorsetLoad(UGColorset& clrSet, UGStream& stream);
	
	//! \brief	Colorset的存取
	//##ModelId=483BB709017F
	static UGbool ColorsetSave(UGColorset& clrSet, UGStream& stream);

    //通过像素获取实际字节宽度
	static UGint  GetWidthBytes(OGDC::PixelFormat ePixelFormat, UGint nWidth);
	//修正像素的编码方式
	static UGbool ModifyEncType(OGDC::PixelFormat ePixelFormat,UGDataset::DatasetType nType,UGColorset &Colorset,UGDataCodec::CodecType& nEncType);


	//{{从SFC中移植过来	add by shuxl	08.12.11
	//创建字段，如果合法就创建
	static UGbool CreateValidField( UGDatasetVector * pDataSetV,  const UGFieldInfo & fieldinfo);
	//创建字段，如果合法就创建
	static UGbool CreateValidField( UGDatasetVector * pDataSetV,  const UGString &strName, UGint nType, UGint lSize, UGint lAttributes = 0);
	//创建字段，只创建合法字段
	static UGbool CreateValidFields( UGDatasetVector * pDataSetV,  const UGFieldInfos & fieldinfos);
	//}}从SFC中移植过来	add by shuxl	08.12.11

    //在导入数据集的时候 ，检查他们是否可以兼容
	static UGbool CheckRasterInfo(const UGArray<UGDatasetRasterInfo*>& rasterInfos);
	//判断strName是否合法，也就是在RasterInfo中是否存在，如果存在，返回TRUE,并将strName变成合法的
	//如果不存在则不变
	static UGbool GetAvailFieldName(const UGDatasetRasterInfo& RasterInfo,UGString& strName);
    
	//! \brief 去除srcAry中和exceptAry中一样的值
	//! \param &srcAry 源数组[in][out]。
	//! \param &exceptAry 过滤数组[in]。
	//! \return void
	static void Except(UGArray<UGint>& srcAry,UGArray<UGint>& exceptAry);

	//! \param nBandIndexSrc[in] 原数据波段索引值，默认为0
	//! \param nBandIndexDes[in] 波段索引值，默认为0
	static UGbool CopyDatasetRaster(UGDatasetRaster* RasterTarget, UGDatasetRaster* RasterSrc, UGint nBandIndexDes=0, UGint nBandIndexSrc = 0, UGint nProgresStartPos=0, UGint nProgresEndPos=100, UGProgress *pProgressSrc = NULL);
	//通过 RasterSrc 的第n波段构造一个RasterTarget 
	static UGbool GetRasterInfo(UGDatasetRasterInfo& RasterTarget, const UGDatasetRasterInfo& RasterSrc, UGint nBand);
#if !defined SYMBIAN60 && !defined  OS_ANDROID && !defined (IOS)
	//通过 RasterSrc 的信息提取出一个BandInfo
	static UGBandInfo GetBandInfo(const UGDatasetRasterInfo& RasterSrc);
#endif
	//! \brief 对含有表名的字符串进行表名替换,主要用于处理SQL语句。
	//! \param &strIn 传入的串[in]。
	//! \param &strTableSrc 源表名[in]。
	//! \param &strTableDest 目标表名[in]。
	//! \return 返回结果串。
	//! \remarks 主要用于处理SQL语句。
	static UGString ReplaceTableName(const UGString &strIn, const UGString &strTableSrc, const UGString &strTableDest);	

	//! \brief 判断字段的默认值是否合法，只对整形数据有效。 
	//! \param fieldInfo 字段信息。[in] 
	static UGbool IsDefaultValueAviable(UGFieldInfo fieldInfo);
    //! \brief 里面实现了不同的栅格数据集支持的像素格式
	// 同时定义了当前引擎的栅格支持那几种类型的数据集
	static UGbool GetSupportRaster(UGEngineType engType,UGDataset::DatasetType dataType,OGDC::PixelFormat ePixelFormat,UGbool IsMBRaster = FALSE);
	static UGbool GetSupportVector(UGEngineType engType,UGDataset::DatasetType dataType);
	static UGbool IsSupportPixelFormat(OGDC::PixelFormat ePixelFormat);
	//! \brief 里面实现了不同的像素格式在创建数据集的时候的初始化无值
	static UGdouble GetDefaultNoValue(OGDC::PixelFormat ePixelFormat);
    //! \brief 对IDs中重复的，小于和等于0的Id进行过滤

	//! \brief 获得合理的表名称
	static UGbool ExtractTableName(UGDataSource *pDS, UGString strName, 
		UGString strTableName, UGString& strResTabName);

	//! \brief 获得字符串的前nCount个字符	
	static UGString GetSubText(const UGString strString, UGint nCount);

    static UGbool FilterIDs(UGArray<UGint>& arrIDs);
	//! \brief 判断这个arrByte 是不是两个合法的字符串组合
	static UGbool IsValid(UGByteArray& arrByte);
#if !defined SYMBIAN60 && !defined  OS_ANDROID && !defined (IOS)
	//! \brief 返回多波段的所有波段
	static UGArray<UGint> GetArrayIndex(UGDatasetRaster* pRaster);
#endif
    //! \brief 获得不同数值到像素256位之间的比率
	static UGdouble GetRatioPixel(UGdouble dMaxZ,UGdouble dMinZ,OGDC::PixelFormat ePixelFormat);
    //! \brief 通过nColor来获取实际的RGB值
	static UGColor GetColor(UGint nColor,ImgColorSpace nColorSpace);
 
	//! \brief 线性拉伸算法 影像块拉伸
	//	BilinearInterpolation	CubicConvolution NearestNeighbor
	static UGbool BilinearInterpolation(UGImgBlock *pResBlock, UGArray<UGImgBlock*>& arrImgBlock
		, ImgColorSpace nColorSpace,UGArray<UGdouble>&dMinZs,

		UGArray<UGdouble>&dMaxZs,UGint nBandCount , UGbool bMaxMinStretch=true);

	//! \brief 线性拉伸算法 像素拉伸
	static UGbool BilinearInterpolation(UGColor& nColor ,UGArray<UGdouble>& arrValue
		, ImgColorSpace nColorSpace,UGArray<UGdouble>&dMinZs,
		UGArray<UGdouble>&dMaxZs,UGint nBandCount );
	
	//!\brief 线性拉伸的反算法
	static UGbool BilinearInterpolationR(UGArray<UGdouble>& arrValue,UGColor nColor, 
		ImgColorSpace nColorSpace,UGArray<UGdouble>&dMinZs,
		UGArray<UGdouble>&dMaxZs,UGint nBandCount );

	//! \brief 对于rcRsBounds，如果接近于rcDtBounds，则放大一些，
	static void InflateBounds(const UGRect2D& rcDtBounds,UGRect2D& rcRsBounds,UGdouble dTolerance = 0);
    
	//! \brief 检查当前字段是否允许删除，允许删除，返回TRUE;
	static UGbool CheckField(const UGFieldInfo&filedInfo);

	//! \brief 计算平均值
	static UGdouble CalcAvgValue(UGdouble a, UGdouble b, UGdouble c, UGdouble d,UGdouble dNoValue);
	static UGuint GetImgPyramidValue(OGDC::PixelFormat ipf, UGbool bIndexedColor, UGuint a,
		UGuint b, UGuint c, UGuint d);

	//! \brief 判断目标字段是否兼容源字段
	//! \param &srcInfo 源字段
	//! \param &destInfo 目标字段
	//! \return 返回兼容判断结果
	static UGbool IsFiledTypeCompatible(const UGFieldInfo &srcInfo, const UGFieldInfo &destInfo);

	//! \brief 得到可以从源记录集中追加到目标数据集的字段
	//! \param *pSrcRcd	源记录集
	//! \param *pDataset 目标数据集
	//! \param &fieldsAppendable 需要被追加的目标数据集的字段数组
	//! \return 
	static void FieldsAppendable(UGRecordset *pSrcRcd, UGDatasetVector *pDataset, UGFieldInfos &fieldsAppendable);

	//! \brief 得到支持的编码类型
	//!\ param nType 数据集类型
	//!\ param ePixelFormat 像素格式
	//!\ param &colorset 颜色表
	static UGArray<UGDataCodec::CodecType> GetSupportEncType(UGDataset::DatasetType nType, OGDC::PixelFormat ePixelFormat, const UGColorset &colorset);

	//! \brief 统计函数（最大值、最小值、平均值、总和、标准差、方差）
	//! \param *pData 数据
	//! \param nCount 数据个数
	//! \parma emode 统计类型
	static UGdouble Statistic(UGint *pData, UGint nCount, UGStatisticMode eMode);
	static UGdouble Statistic(UGdouble *pData, UGint nCount, UGStatisticMode eMode);

	//! \brief 检查是否是数据库的关键字
	//! \brief 所有的数据库关键字合集
	//! \return 返回验证结果
	static UGbool CheckIsKeyword(UGString strWord);

	static UGString GetDatasetCachePath();

	//! \brief 处理传入的字符串，如果串包括带引号的子串，则为其添加N
	//! \brief 解决使用SQL访问数据库时，SQL中如果有多国语言的字符串，需要添加N标记
	//! \Sample "Name in 'China', 'American'", 处理后为 "Name in N'China', N'American'"
	static void SQLWideCharSupport(UGString &strContent);

	//! \brief获得数据集类型的字符串
	static UGString GetStrType(const UGDataset::DatasetType type);

	//! \判断是否符合追加要求，并且通过参数返回正确的字段匹配关系
	static UGbool IsMatchingAppend(UGDatasetVector *pVector, UGRecordset *pRcd, UGArray<UGString> &strSrcFieldNames, UGArray<UGString> &strDesFieldNames);

	static UGbool IsMatchingJoint( UGDatasetVector *pVector, UGRecordset *pRcd, UGArray<UGString> &strSrcFieldNames, UGArray<UGString> &strDesFieldNames, UGFieldInfos &outSrcInfos, UGFieldInfos &outDestInfos);

	static UGbool IsFieldSignExist(UGDatasetVector *pVector, UGFieldInfo::FieldSign fieldSign);

	static UGString ConvertDateTimeToString( UGTime timeValue,UGEngineType engineType );
};
}

#endif // !defined(UGENGTOOLKIT_H)

