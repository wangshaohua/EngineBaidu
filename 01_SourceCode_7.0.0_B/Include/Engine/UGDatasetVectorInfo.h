/*! \file	 UGDatasetVectorInfo.h
 *  \brief	 矢量数据集信息定义
 *  \author	 ugc team
 *  \attention 
 *  Copyright(c) 2000-2010  SuperMap GIS Technologies,Inc.<br>
 *  All Rights Reserved
 *  \version $Id: UGDatasetVectorInfo.h,v 1.15 2010/05/12 06:46:34 zhouqin Exp $
 */

#ifndef UGDATASETVECTORINFO_H
#define UGDATASETVECTORINFO_H

#include "Engine/UGDataset.h"
#include "SpatialIndex/UGSpatialIndexInfo.h"

#if !defined SYMBIAN60 && !defined  OS_ANDROID && !defined (IOS)
#include "OGDC/OgdcDatasetVectorInfo.h"
#endif

namespace UGC {

//! \brief 矢量数据集信息类
//##ModelId=482030520233
class ENGINE_API UGDatasetVectorInfo  
{
public:
	//! \brief  构造函数
	//##ModelId=482030520242
	UGDatasetVectorInfo();
	//! \brief  析构函数
	//##ModelId=482030520243
	~UGDatasetVectorInfo();

	//##ModelId=482030520244
	void SetToleranceToDefault();

	//! \brief  得到当前的索引类型
	//##ModelId=482030520245
	UGint GetIndexType()
	{
		return m_nIndexType;
	};
	//##ModelId=482030520246
	void SetIndexType(IndexType nIdxType)
	{
		m_nIndexType = nIdxType;
	};

	// 设置数据集信息的数据集编码
	// param nCharset[in] 字符集编码
	void SetCharset(UGString::Charset nCharset);

	// 得到数据集信息的数据集编码
	// return 数据集信息的编码
	UGString::Charset GetCharset();

#if !defined SYMBIAN60 && !defined  OS_ANDROID && !defined (IOS)
public:
	//! \brief 与 OgdcDatasetVectorInfo 的转换：将 UGDatasetVectorInfo 转换为 OgdcDatasetVectorInfo
	//##ModelId=483BB70A0271
	OgdcDatasetVectorInfo ToOgdcDatasetVectorInfo() const;

	//! \brief 与 OgdcDatasetVectorInfo 的转换：从 OgdcDatasetVectorInfo 得到 UGDatasetVectorInfo
	//##ModelId=483BB70A0273
	UGbool FromOgdcDatasetVectorInfo(const OgdcDatasetVectorInfo& OgdcInfo);
#endif
public:
	//!  \brief 数据集表名
	//##ModelId=482030520248
	UGString m_strTableName;

	//!  \brief 数据集名称
	//##ModelId=482030520248
	UGString m_strName;

	//! \brief  数据集类型
	//##ModelId=482030520252
	UGDataset::DatasetType m_nType;

	//!  \brief 选项信息
	//##ModelId=482030520256
	UGint m_nOptions;
	
	//! \brief  对象个数
	//##ModelId=482030520257
	UGint m_nObjectCount;

	//! \brief  索引类型 
	//##ModelId=482030520258
	UGint	m_nIndexType;
	
	//!  \brief 网格索引标志
	//##ModelId=482030520259
	UGint	m_nDynamicIndex;
	
	//!  \brief 网格索引专用参数
	//##ModelId=482030520261
	UGPoint2D m_pntIdxCenter;
	//##ModelId=482030520262
	UGdouble  m_dbGridRatio;
	//##ModelId=482030520263
	UGdouble  m_dbdGrid0;
	//##ModelId=482030520264
	UGdouble  m_dbdGrid1;
	//##ModelId=482030520265
	UGdouble  m_dbdGrid2;
		
	//! \brief  空间索引层数
	//##ModelId=482030520271
	UGint m_nSpatialIndexLevel;
		
	//!  \brief 数据集的Bounds
	//##ModelId=482030520272
	UGRect2D m_rc2Bounds;

	//! \brief  三维Bounds的最小值
	//##ModelId=482030520273
	UGdouble m_dMinZ;

	//! \brief  三维Bounds的最大值
	//##ModelId=482030520274
	UGdouble m_dMaxZ;
	
	//!  \brief 数据集中索引所设置的Bounds
	//##ModelId=482030520275
	UGRect2D m_rc2IndexedBounds;	

	//! \brief  以下的容限为建立拓扑关系、编辑时使用
	//UGdouble m_dToleranceFuzzy;
	//长悬线容限），只在长悬线延伸中使用，应对应SFC中的NodeSnap
	UGdouble m_dToleranceExtend;
	
	//（结点捕捉容限），大量使用，应对应SFC中的Fuzzy
	UGdouble m_dToleranceNodeSnap;

	//##ModelId=482030520281
	UGdouble m_dToleranceDangle;	
	
	//##ModelId=482030520283
	UGdouble m_dToleranceSmallPolygon;
	//##ModelId=482030520284
	UGdouble m_dToleranceGrain;

	//! \brief  Tin数据集里，金字塔层使用
	//##ModelId=482030520285
	UGdouble m_dTinTolerance;

	//! \brief  长事务、锁定　及状态
	//##ModelId=482030520290
	UGint m_nCheckedUserID;
	//##ModelId=482030520291
	UGint m_nLockedUserID;
	//##ModelId=482030520292
	UGint m_nState;

	//! \brief  数据编码类型
	//##ModelId=482030520293
	UGint m_nCodecType;	

	//! \brief 数据集的描述信息
	//##ModelId=482030520294
	UGString m_strDescription;	

	//! \brief 数据集的附加信息
	//##ModelId=482030520294
	UGString m_strExtInfo;	

	//! \brief 父数据集的ID
	UGint m_nParentID;

	//! \brief 标识网络数据集是否是3D Network
	UGbool m_bIs3DNetwork;
};

}

#endif


