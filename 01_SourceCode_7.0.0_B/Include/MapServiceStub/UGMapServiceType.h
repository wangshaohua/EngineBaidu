//////////////////////////////////////////////////////////////////////////
//                    _   _   ____   ____                    
//   Project         | | | | / ___) / ___)                   
//                   | | | || | __ | |                       
//                   | |_| || |_\ || \___                    
//                    \____/ \____| \ ___)     6.0           
//                                                           
//!  \file headerfile.h
//!  \brief Class 。
//!  \details 。
//!  \author 数据转换组。
//!  \attention 请不要随便修改下面的常量定义。
//!   Copyright (c) 1996-2010 SuperMap Software Limited Company.  <br> 
//!   All Rights Reserved.
//!  \version 6.0
//////////////////////////////////////////////////////////////////////////

#if !defined(AFX_UGMAPSERVICETYPE_H__EAB125D4_D53A_4784_A77E_5A8636BC43BD__INCLUDED_)
#define AFX_UGMAPSERVICETYPE_H__EAB125D4_D53A_4784_A77E_5A8636BC43BD__INCLUDED_

#include "Stream/ugdefs.h"

namespace UGC {

//! \brief 数据转换支持的文件类型。
class MAPSERVICESTUB_API UGMapServiceType
{
public:

	// 服务格式类型	
	// 用户自定义从100开始
	enum EmType
	{
		// 不认识	
		none					= 0, 

		WMTS					= 26,
        
		//谷歌地图服务
		GoogleMaps				= 223,
		// 超图云服务
		SuperMapCloud			= 224,
        
		//rest 地图服务
		Rest					= 225,
        
		//天地图
		MapWorldMaps		    = 226,
		
		//百度地图
		BaiDu                   = 227,
		//开放街道地图
		OpenStreetMaps          = 228

	};

};

} //namespace UGC

#endif // !defined(AFX_UGMAPSERVICETYPE_H__EAB125D4_D53A_4784_A77E_5A8636BC43BD__INCLUDED_)


