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


#if !defined(AFX_UGMAPWORLDMAPSPARAMS_H__08BADC84_B1E9_40CA_B1AE_A7755CC63F16__INCLUDED_)
#define AFX_UGMAPWORLDMAPSPARAMS_H__08BADC84_B1E9_40CA_B1AE_A7755CC63F16__INCLUDED_

#include "MapServiceStub/UGMapServiceParams.h"
#include "MapServiceStub/UGMapServiceType.h"

namespace UGC {

	//! \brief 超图MapWorldMaps服务参数配置。
	class MAPSERVICESTUB_API UGMapWorldMapsParams : public UGMapServiceParams
	{
	public:
		//! \brief 构造函数
		//! \remarks 
		UGMapWorldMapsParams();

		//! \brief 析构函数
		//! \remarks 
		~UGMapWorldMapsParams();

	public:

		//! \brief 重载获取服务类型的函数
		//! \param  [in]
		//! \return 
		//! \remarks 
		//! \attention 
		virtual UGint GetServiceType() const	{ return UGMapServiceType::MapWorldMaps; }
        
		//! \brief 
		//! \param [in] 建立的数据集类型
		//! \return  true:Success  false:failure
		virtual UGbool InitParam(UGString strMapType);


		//! \brief 
		//! \param [in] 设置能力文档xml文件存储路径
        
		virtual UGbool SetCapAbilitiesPath(UGString & strPath);
        
		//! \brief 返回缓存文件路径
		virtual UGString getCapAbilitiesPath()const;

		virtual UGbool LoadFromLocalCache(UGString strPath);

	public:

		//! \brief MapWorld地图类型。
		//! \param  [in]
		UGString m_strMapType;
        

		//! \brief 能力文档存储路径
		UGString m_strCapAbilitiesPath;
        
    
	private: 
	   
	   //! \brief 加载所有天地图参数
	   UGbool LoadAllLayerParams(const UGString& strPathXML);

	};

} //namespace UGC
#endif // !defined(AFX_MAPWOLRDMAPS_H__08BADC84_B1E9_40CA_B1AE_A7755CC63F16__INCLUDED_)

