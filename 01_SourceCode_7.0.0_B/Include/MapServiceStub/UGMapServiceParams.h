//////////////////////////////////////////////////////////////////////////
//                    _   _   ____   ____                    
//   Project         | | | | / ___) / ___)                   
//                   | | | || | __ | |                       
//                   | |_| || |_\ || \___                    
//                    \____/ \____| \ ___)     6.0           
//                                                           
//!  \file headerfile.h
//!  \brief Class 的接口定义。
//!  \details 文件详细信息。
//!  \author 数据转换组。
//!  \attention 
//!   Copyright (c) 1996-2008 SuperMap Software Limited Company.  <br> 
//!   All Rights Reserved.
//!  \version 6.0
//////////////////////////////////////////////////////////////////////////


#if !defined(AFX_UGMAPSERVICEPARAMS_H__08BADC84_B1E9_40CA_B1AE_A7755CC63F16__INCLUDED_)
#define AFX_UGMAPSERVICEPARAMS_H__08BADC84_B1E9_40CA_B1AE_A7755CC63F16__INCLUDED_

#include "MapServiceStub/UGMapServiceType.h"
#include "FileParser/UGExchangeFileType.h"
#include "Projection/UGPrjCoordSys.h"

namespace UGC {

//! \brief 转换参数基类。
class MAPSERVICESTUB_API UGMapServiceParams  
{

public:
	
	//! \brief 构造函数。
	UGMapServiceParams();
	
	//! \brief 析构函数。
	virtual ~UGMapServiceParams();

public:
	//! \brief 得到服务类型。
	//! \param  [in]。
	//! \return 服务类型。
	//! \remarks 各个子类自己实现。
	virtual UGint GetServiceType() const {return 0;}
	
public:
	UGString m_strBaseURL;						// 服务基地址,如:http://maps.googlemap.com	
	UGString m_strMapName;					    // 地图名称。该名称用作缓存作为数据源方式进行加载时的数据源名称
	UGPrjCoordSys m_prjCoordSys;				// 投影信息。将地图缓存加载到三维场景中的必须信息。
	UGFileType::EmType m_nImageType;			// 图片格式
	UGint m_nTileSize;							// 瓦片像素边长。默认 256 像素
	UGPoint2D m_pntCenter;						// 默认显示的中心点，默认值（0，0）
	UGdouble m_dCoordRatio;						// LP/DP的映射关系。
	UGPoint2D m_pntOrigin;						// 整个缓存相对这个原点出缓存，默认值（0，0）
	std::vector<UGdouble> m_vectOutputScales;		// 比例尺数组
	UGbool m_bCompactCache;						// 是否是紧凑缓存
	UGRect2D m_rcBounds;
	UGint m_nLevel;								//缓存的总层数

};

} //namespace UGC
#endif // !defined(AFX_UGMAPSERVICEPARAMS_H__08BADC84_B1E9_40CA_B1AE_A7755CC63F16__INCLUDED_)

