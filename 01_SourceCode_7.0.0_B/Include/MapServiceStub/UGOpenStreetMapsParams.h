//////////////////////////////////////////////////////////////////////////
//                    _   _   ____   ____                    
//   Project         | | | | / ___) / ___)                   
//                   | | | || | __ | |                       
//                   | |_| || |_\ || \___                    
//                    \____/ \____| \ ___)     6.0           
//                                                           
//!  \file headerfile.h
//!  \brief Class 的接口定义。
//!  \details 服务参数详细信息。
//!  \author  数据转换组。
//!  \attention 
//!   Copyright (c) 1996-2008 SuperMap Software Limited Company.  <br> 
//!   All Rights Reserved.
//!  \version 6.0
//////////////////////////////////////////////////////////////////////////


#if !defined(AFX_UGOPENSTREETMAPSPARAMS_H__08BADC84_B1E9_40CA_B1AE_A7755CC63F16__INCLUDED_)
#define AFX_UGOPENSTREETMAPSPARAMS_H__08BADC84_B1E9_40CA_B1AE_A7755CC63F16__INCLUDED_

#include "MapServiceStub/UGMapServiceParams.h"
#include "MapServiceStub/UGMapServiceType.h"

namespace UGC {

	//! \brief 超图OpenStreetMaps服务参数配置。(osm开放街道地图配置)
	class MAPSERVICESTUB_API UGOpenStreetMapsParams : public UGMapServiceParams
	{
	public:
		//! \brief 构造函数
		//! \remarks 
		UGOpenStreetMapsParams();

		//! \brief 析构函数
		//! \remarks 
		~UGOpenStreetMapsParams();

	public:

		//! \brief 重载获取服务类型的函数
		//! \param  [in]
		//! \return 
		//! \remarks 
		//! \attention 
		virtual UGint GetServiceType() const	{ return UGMapServiceType::OpenStreetMaps; }
        
		//! \brief   初始化地图参数
		//! \return  true:Success  false:failure
		virtual UGbool InitParam();

	public:

		//! \brief MapWorld地图类型。
		//! \param  [in]
		UGString m_strMapType;

	};

} //namespace UGC
#endif // !defined(AFX_OPENSTREETMAPS_H__08BADC84_B1E9_40CA_B1AE_A7755CC63F16__INCLUDED_)

