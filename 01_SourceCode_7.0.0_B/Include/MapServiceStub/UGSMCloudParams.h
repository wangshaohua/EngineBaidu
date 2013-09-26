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


#if !defined(AFX_UGSMICLOUDPARAMS_H__08BADC84_B1E9_40CA_B1AE_A7755CC63F16__INCLUDED_)
#define AFX_UGSMICLOUDPARAMS_H__08BADC84_B1E9_40CA_B1AE_A7755CC63F16__INCLUDED_

#include "MapServiceStub/UGMapServiceParams.h"
#include "MapServiceStub/UGMapServiceType.h"

namespace UGC {

//! \brief 超图云服务参数配置。
class MAPSERVICESTUB_API UGSMCloudParams : public UGMapServiceParams
{
public:
	//! \brief 构造函数。
	//! \remarks 。
	UGSMCloudParams();

	//! \brief 析构函数。
	//! \remarks 。
	~UGSMCloudParams();

public:

	//! \brief 重载获取服务类型的函数。
	//! \param  [in]。
	//! \return 。
	//! \remarks 。
	//! \attention 。
	virtual UGint GetServiceType() const	{ return UGMapServiceType::SuperMapCloud; }

};

} //namespace UGC
#endif // !defined(AFX_UGSMICLOUDPARAMS_H__08BADC84_B1E9_40CA_B1AE_A7755CC63F16__INCLUDED_)

