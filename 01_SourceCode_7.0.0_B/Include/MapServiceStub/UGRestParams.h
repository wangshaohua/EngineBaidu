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


#if !defined(AFX_UGRESTPARAMS_H__08BADC84_B1E9_40CA_B1AE_A7755CC63F16__INCLUDED_)
#define AFX_UGRESTPARAMS_H__08BADC84_B1E9_40CA_B1AE_A7755CC63F16__INCLUDED_

#include "MapServiceStub/UGMapServiceParams.h"
#include "MapServiceStub/UGMapServiceType.h"

namespace UGC {

	//! \brief 超图GoogleMaps服务参数配置。
	class MAPSERVICESTUB_API UGRestParams : public UGMapServiceParams
	{
	public:
		//! \brief 构造函数。
		//! \remarks 。
		UGRestParams();

		//! \brief 析构函数。
		//! \remarks 。
		~UGRestParams();

	public:

		//! \brief 重载获取服务类型的函数。
		//! \param  [in]。
		//! \return 。
		//! \remarks 。
		//! \attention 。
		virtual UGint GetServiceType() const	{ return UGMapServiceType::Rest; }

		//! \brief 通过URL初始化地图参数
		virtual UGbool InitParams();

		//! \brief 通过本地sci文件初始化地图参数
		virtual UGbool FromLocalCache(const UGString& strCacheFile);

		//! \brief 获取本地缓存的相对目录，即webcache之后的目录
		virtual UGString GetRelativePath();

	private:
		UGbool ParseURL();

	public:
		//! \brief 是否设置可见比例尺
		UGbool m_bVisibleScalesEnabled;

		//! \brief 服务器域名
		UGString m_strHost;

		//! \brief 服务器端口号
		UGString m_strPort;

		//! \brief 服务名称
		UGString m_strServer;

	};

} //namespace UGC
#endif // !defined(AFX_UGRESTPARAMS_H__08BADC84_B1E9_40CA_B1AE_A7755CC63F16__INCLUDED_)

