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
//!  \author 数据转换组。
//!  \attention 
//!   Copyright (c) 1996-2008 SuperMap Software Limited Company.  <br> 
//!   All Rights Reserved.
//!  \version 6.0
//////////////////////////////////////////////////////////////////////////


#if !defined(AFX_UGBAIDUPARAMS_H__08BADC84_B1E9_40CA_B1AE_A7755CC63F16__INCLUDED_)
#define AFX_UGBAIDUPARAMS_H__08BADC84_B1E9_40CA_B1AE_A7755CC63F16__INCLUDED_

#include "MapServiceStub/UGMapServiceParams.h"
#include "MapServiceStub/UGMapServiceType.h"

namespace UGC {

	//! \brief 超图GoogleMaps服务参数配置。
	class MAPSERVICESTUB_API UGBaiDuMapsParams : public UGMapServiceParams
	{
	public:
		//! \brief 构造函数。
		//! \remarks 。
		UGBaiDuMapsParams();

		//! \brief 析构函数。
		//! \remarks 。
		~UGBaiDuMapsParams();

	public:

		//! \brief 重载获取服务类型的函数。
		//! \param  [in]。
		//! \return 。
		//! \remarks 。
		//! \attention 。
		virtual UGint GetServiceType() const	{ return UGMapServiceType::BaiDu; }
	
	public:

		//! \brief BaiDu地图类型。
		//! \param  [in]。
		UGString m_strMapType;
	    
		// 特殊说明：下面的这两个参数用来作为百度2.5维地图URL的配置项
		//! \brief URL城市标示
        UGString m_strCityMark;

		//! \brief URL城市数据编码
		UGint m_nCityNumber;

	};

} //namespace UGC
#endif // !defined(AFX_UGBAIDUPARAMS_H__08BADC84_B1E9_40CA_B1AE_A7755CC63F16__INCLUDED_)

