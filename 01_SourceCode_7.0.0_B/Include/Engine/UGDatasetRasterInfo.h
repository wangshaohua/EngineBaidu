/*! \file	 UGDatasetRasterInfo.h
 *  \brief	 栅格数据集信息定义
 *  \author	 ugc team
 *  \attention 
 *  Copyright(c) 2000-2010  SuperMap GIS Technologies,Inc.<br>
 *  All Rights Reserved
 *  \version $Id: UGDatasetRasterInfo.h,v 1.20 2009/11/05 09:22:22 siyh Exp $
 */

#ifndef UGDATASETRASTERINFO_H
#define UGDATASETRASTERINFO_H

#include "Geometry/UGDataCodec.h"

#if !defined SYMBIAN60 && !defined OS_ANDROID && !defined (IOS)
#include "OGDC/OgdcDatasetRasterInfo.h"
#endif

namespace UGC {

class ENGINE_API UGBandInfo
{
public:
	UGBandInfo();
	
	//! \brief 析构函数
#ifdef SYMBIAN60
	~UGBandInfo();
#else
	virtual ~UGBandInfo();
#endif
	
	void operator=(const UGBandInfo& bInfo);

	//! \brief 波段数据库中索引
	UGint m_nBandID;
	//! \brief 波段索引
	UGint m_nIndex;
	//! \brief 波段的名字
	UGString m_strName;
	//! \brief 波段所在的列名
	UGString m_strFieldName;
	//!当前波段是否有效
	UGbool m_bAvail;
	//! \brief 波段的描述信息
	UGString m_strDescription;
	//! \brief 波段的附加信息
	UGString m_strExtInfo;
	//! \brief 波段的影像行字节数
	UGint m_nWidthBytes;
	//! \brief 选项信息
	UGint m_nOptions;
	//! \brief 数据编码类型
	UGDataCodec::CodecType m_nCodecType;
	//! \brief 三维Bounds的最小值
	UGdouble m_dMinZ;
	//! \brief 三维Bounds的最大值
	UGdouble m_dMaxZ;
	//! \brief 调色板
	UGColorset m_Colorset;
	//! \brief 最大blockSize
	UGint m_nMaxBlockSize;
 	//! \brief 当前波段保留字，主要用于新添加的像素格式
 	UGint m_nScalar;
	
	inline UGdouble GetNoValue() const { return m_dbNoValue; };

	void SetNoValue(UGdouble dNoValue, UGbool bCheck = FALSE);

	inline OGDC::PixelFormat GetPixelFormat() const { return m_ePixelFormat; };

	void SetPixelFormat(OGDC::PixelFormat pixelFormat);

private:

	//! \brief 无效值，如果某一点的值是m_NoValue,将认为这一点没有值
	UGdouble m_dbNoValue;

	//! \brief 标识用户是否设置了无值
	UGbool m_bIsSetNoValue;

	//! \brief 波段的像素格式
	OGDC::PixelFormat m_ePixelFormat;
};
	
//! \brief 栅格数据集信息
//##ModelId=48203054004E
class ENGINE_API UGDatasetRasterInfo  
{
public:
	
	//! \brief 影像块大小选项
	//##ModelId=48203054008F
	enum IBSizeOption 
	{
		//! \brief 64*64
		//##ModelId=482030540091
		IBS_64				= 64,
		//! \brief 128*128
		//##ModelId=48203054009C
		IBS_128				= 128,
		//! \brief 256*256
		//##ModelId=48203054009D
		IBS_256				= 256,
		//! \brief 512*512
		//##ModelId=48203054009E
		IBS_512				= 512,
		//! \brief 1024*1024
		//##ModelId=48203054009F
		IBS_1024			= 1024,
		//! \brief 2048*2048
		//##ModelId=4820305400A0
		IBS_2048			= 2048,	
		//! \brief 4096*4096
		//##ModelId=4820305400AB
		IBS_4096			= 4096,	
		//! \brief 8192*8192
		//##ModelId=4820305400AC
		IBS_8192			= 8192	
	};

	
public:
	//! \brief 构造函数
	//##ModelId=48203054004F
	UGDatasetRasterInfo();

	UGDatasetRasterInfo(UGString strName, UGString strTableName, UGint nType, UGint nWidth, UGint nHeight, 
		IBSizeOption eBlockSize, OGDC::PixelFormat ePixelFormat, UGDataCodec::CodecType nCodecType,
		UGRect2D rc2Bounds, UGint nBandCount = 1);

	//! \brief 析构函数
	//##ModelId=48203054005D
	~UGDatasetRasterInfo();

	//##ModelId=48203054005E
	void operator=(const UGDatasetRasterInfo& rInfo);

public:

#if !defined SYMBIAN60 && !defined OS_ANDROID && !defined (IOS)
	//##ModelId=483BB70B02FD
	UGbool ToOgdcDatasetRasterInfo(OgdcDatasetRasterInfo& OgdcInfo) const;

	//##ModelId=483BB70B0300
	UGbool FromOgdcDatasetRasterInfo(const OgdcDatasetRasterInfo& OgdcInfo);
#endif

public:
	//! \brief 数据集名称
	//##ModelId=482030540060
	UGString m_strName;

	//! \brief 底层表名称
	//##ModelId=482030540061
	UGString m_strTableName;
	
	//! \brief 数据集类型
	//##ModelId=482030540062
	UGint m_nType;

	//! \brief 选项信息
	//##ModelId=482030540063
	UGint m_nOptions;

	//! \brief 影像宽度
	//##ModelId=48203054006E
	UGint m_nWidth;

	//! \brief 影像高度
	//##ModelId=48203054006F
	UGint m_nHeight;

	//! \brief 影像分块边长
	//##ModelId=482030540071
	IBSizeOption m_eBlockSize;

	//! \brief 数据集的Bounds
	//##ModelId=482030540072
	UGRect2D m_rc2Bounds;
		
	//! \brief 横向分块总数(包含余数)
	//##ModelId=48203054007E
	UGint m_nColBlocks;		
	
	//! \brief 纵向分块总数(包含余数)
	//##ModelId=48203054007F
	UGint m_nRowBlocks;		
	
	//##ModelId=48203054008E
	UGString m_strDescription;	//对数据集的描述信息

	//##ModelId=48203054008E
	UGString m_strExtInfo;	//数据集附加信息

	void Add(const UGBandInfo& BandInfo);
	//! \brief 返回当前波段的在Array数组中的索引
	//! \remarks 不成功返回-1。
	UGint Get(UGint nBandIndex,UGBandInfo &bandInfo) const;
	//! \brief 返回当前波段的在Array数组中的索引
	//! \remarks 不成功返回-1。
	UGint Get(UGint nBandIndex) const;
	//! \brief 移除某个波段
	UGbool Remove(UGint nBandIndex);
	//! \brief 移除所有波段
	void RemoveAll();
	//! \brief 获取在UGArray 中 nIndex位置
	UGBandInfo& GetAt(UGint nIndex);
	const UGBandInfo& GetAt(UGint nIndex) const;

	inline UGint GetBandCount() const { return m_arrBandInfo.GetSize(); }

	UGdouble GetNoValue(UGint nBandIndex = 0) const;

	void SetNoValue(UGdouble dNoValue, UGint nBandIndex = 0, UGbool bCheck = FALSE);

	OGDC::PixelFormat GetPixelFormat(UGint nBandIndex = 0) const;

	void SetPixelFormat(OGDC::PixelFormat pixelFormat, UGint nBandIndex = 0);

private:

	UGArray<UGBandInfo> m_arrBandInfo;

	// 以下是调整后要删除的属性
// public:
// 	//! \brief 影像行字节数
// 	//##ModelId=482030540070
// 	UGint m_nWidthBytes;
// 
// 	//! \brief 数据编码类型
// 	//##ModelId=48203054007D
// 	UGDataCodec::CodecType m_nCodecType;	
// 	
// 	//! \brief 三维Bounds的最小值
// 	//##ModelId=482030540080
// 	UGdouble m_dMinZ;
// 	
// 	//! \brief 三维Bounds的最大值
// 	//##ModelId=482030540081
// 	UGdouble m_dMaxZ;	
// 	//! \brief 调色板
// 	//##ModelId=48203054008C
// 	UGColorset m_Colorset;
// 
// 	//##ModelId=483BB70B030D
// 	//! \brief 多波段数据集的波段数。
// 	//! \attention 波段的个数已经在内部维护，外面不要进行管理
// 	UGint m_nBandCount;
// 
// 	//! \brief 波段数据集的波段序号，Base 0。
// 	UGint m_nBandIndex;
// 	
// 	//! \brief 波段所在数据表的列名称。
// 	UGString m_strFieldName;
// // 	inline OGDC::PixelFormat GetPixelFormat() const { return m_ePixelFormat; };
// // 
// // 	void SetPixelFormat(OGDC::PixelFormat pixelFormat);
// 
// private:
// // 	UGArray<UGBandInfo> m_arrBandInfo;
// 
// 	//! \brief 无效值，如果某一点的值是m_NoValue,将认为这一点没有值
// 	//##ModelId=48203054008D
// 	UGdouble m_dbNoValue;
// 
// 	//! \brief 标识用户是否设置了无值
// 	UGbool m_bIsSetNoValue;
// 
// 	//! \brief 象素的格式
// 	//##ModelId=48203054006D
// 	OGDC::PixelFormat m_ePixelFormat;
};

//  [added by zhangshuo at 6/8/2010]
//NetCDF维度类
//每个维度的设置,bX_Axis、bY_Axis和bOptionalDim只能有一个为真
//并且nEndIndex - nStartIndex一定要 >= 0, = 0 时不获取数据
class ENGINE_API UGNetCDFDim
{
	friend class UGDataSourceNetCDF;
public:
	UGNetCDFDim()
	{
		m_strDimName = _U("");
		m_nStartIndex = 0;
		m_nEndIndex = 1;
		m_nDimSize = 0;
		m_bX_Axis = FALSE;
		m_bY_Axis = FALSE;
		m_bOptionalDim = FALSE;
	}
	~UGNetCDFDim(){};

public:
	UGString GetName()
	{
		return m_strDimName;
	};

	UGlong GetSize()
	{
		return m_nDimSize;
	};

	UGbool IsXAxis()
	{
		return m_bX_Axis;
	};

	UGbool IsYAxis()
	{
		return m_bY_Axis;
	};

	UGbool IsOptionalDim()
	{
		return m_bOptionalDim;
	};

	void SetXAxis(UGbool b = TRUE)
	{
		m_bX_Axis = b;
	};

	void SetYAxis(UGbool b = TRUE)
	{
		m_bY_Axis = b;
	};

	void SetOptionalDim(UGbool b = TRUE)
	{
		m_bOptionalDim = b;
	};

protected:
	void SetName(UGString strName)
	{
		m_strDimName = strName;
	};

	void SetSize(UGlong nSize)
	{
		m_nDimSize = nSize;
	};

public:
	//! \brief 维度的起始值在其数值数组中的索引。
	//! \remarks 。
	UGint m_nStartIndex;
	//! \brief 维度的终止值在其数值数组中的索引。
	//! \remarks 。
	UGint m_nEndIndex;

private:
	//! \brief 。维度名
	//! \remarks 。
	UGString m_strDimName;
	//! \brief 判断当前维度作为X轴显示。
	//! \remarks 。
	UGbool m_bX_Axis;
	//! \brief 判断当前维度作为Y轴显示。
	//! \remarks 。
	UGbool m_bY_Axis;
	//! \brief 判断当前维度作为optional轴显示。
	//! \remarks 。
	UGbool m_bOptionalDim;
	//! \brief 。维度长度
	//! \remarks 。
	UGlong m_nDimSize;
};

class ENGINE_API UGNetCDFDatasetRasterInfo : public UGDatasetRasterInfo
{
	friend class UGDataSourceNetCDF;
	friend class UGDatasetRasterNetCDF;
public:
	//! \brief 构造函数。
	//! \remarks 。
	UGNetCDFDatasetRasterInfo()
	{
		m_strVarName = _U("");
		m_arrDims.RemoveAll();
		X_AxisIndex = -1;
		Y_AxisIndex = -1;
		OptionalDimIndex = -1;
		m_strVarType = 0;//ncNoType;
		m_nType = 83;//UGDataset::Grid;
		m_strUnit = _U("");
		m_strLongName = _U("");
	};

	//! \brief 析构函数。
	//! \remarks 。
	~UGNetCDFDatasetRasterInfo(){};

public:
	UGString GetVarName()
	{
		return m_strVarName;
	};

	void SetVarName(UGString name)
	{
		m_strVarName = name;
	};

	// 	UGbool UGNetCDFDatasetRasterInfo::operator==(const UGNetCDFDatasetRasterInfo &info)
	// 	{
	// 		if(	this->m_strVarName == info.m_strVarName &&
	// 			this->X_AxisIndex == info.X_AxisIndex &&
	// 			this->m_arrDims[this->X_AxisIndex].m_nStartIndex == info.m_arrDims[info.X_AxisIndex].m_nStartIndex &&
	// 			this->m_arrDims[this->X_AxisIndex].m_nEndIndex == info.m_arrDims[info.X_AxisIndex].m_nEndIndex &&
	// 			this->Y_AxisIndex == info.Y_AxisIndex &&
	// 			this->m_arrDims[this->Y_AxisIndex].m_nStartIndex == info.m_arrDims[info.Y_AxisIndex].m_nStartIndex &&
	// 			this->m_arrDims[this->Y_AxisIndex].m_nEndIndex == info.m_arrDims[info.Y_AxisIndex].m_nEndIndex &&
	// 			this->OptionalDimIndex == info.OptionalDimIndex &&
	// 			this->m_arrDims[this->OptionalDimIndex].m_nStartIndex == info.m_arrDims[info.OptionalDimIndex].m_nStartIndex)
	// 		{
	// 			return TRUE;
	// 		}
	// 		return FALSE;
	// 	}

public:
	//! \brief 。X axis index
	//! \remarks 。
	UGint X_AxisIndex;

	//! \brief 。Y axis index
	//! \remarks 。
	UGint Y_AxisIndex;

	//! \brief 。optional dim index
	//! \remarks 。
	UGint OptionalDimIndex;

	//! \brief 。dim array
	//! \remarks 。
	UGArray<UGNetCDFDim> m_arrDims;

	//! \brief 。the var unit
	//! \remarks 。
	UGString m_strUnit;

	//! \brief 。the var longname
	//! \remarks 。
	UGString m_strLongName;
protected:
	//! \brief 。the var name
	//! \remarks 。
	UGString m_strVarName;

	//! \brief 。the var type
	//! \remarks 。
	UGint m_strVarType;
};

}

#endif


