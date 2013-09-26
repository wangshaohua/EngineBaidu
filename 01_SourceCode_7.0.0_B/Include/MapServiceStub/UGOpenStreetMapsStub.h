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
//!  \attention 
//!   Copyright (c) 1996-2010 SuperMap Software Limited Company.  <br> 
//!   All Rights Reserved.
//!  \version 6.0
//////////////////////////////////////////////////////////////////////////


#if !defined(AFX_UGOPENSTREETMAPSSTUB_H__F2ACB033_F582_4263_B9E9_DCA2E56F87DE__INCLUDED_)
#define AFX_UGOPENSTREETMAPSSTUB_H__F2ACB033_F582_4263_B9E9_DCA2E56F87DE__INCLUDED_

#include "MapServiceStub/UGMapServiceStub.h"

namespace UGC 
{
	//! \brief 服务请求基类。
	//! \remarks 所有有关服务请求的都要继承此类。
	class MAPSERVICESTUB_API UGOpenStreetMapsStub : public UGMapServiceStub 
	{
	public:
		//! \brief 构造函数。
		UGOpenStreetMapsStub();

		//! \brief 析构函数。
		virtual ~UGOpenStreetMapsStub();

	public:
		//! \brief 打开服务。
		//! \param impParams [in]。
		//! \return 成功返回TRUE，失败返回FALSE。
		//! \attention 下载服务前调用。
		virtual UGbool Open(const UGMapServiceParams* impParams, UGbool bReSave = TRUE);

		//! \brief 重载获取服务类型的函数
		//! \param  [in]
		//! \return 
		//! \remarks 
		//! \attention 
		virtual UGint GetServiceType() const	{ return UGMapServiceType::OpenStreetMaps; }

	protected:
        

		// Function list

		//! \brief 生成URL数组
		//! \param tileInfo[in]产生URL的瓦片
		//! \param strURL[out]请求的URL
		//! \return  void
		virtual void GenerateURL(const UGTileInfo& tileInfo, UGString& strURL);

		//! \brief 生成URL时是否采用TileInfo来计算
		virtual UGbool IsGenerateURLByTileInfo(){return TRUE;}
        
		//!brief   得到title数据所在比例尺级别
		//!param[in]   titledata比例尺
	    UGint GetOpenStreetMapsZoom(const UGdouble dScale);
      




		//Attribute List

		//!brief     数据集类型
		UGString m_strMapType;


	private:
        
		//! \brief 由随机数字产生随机服务器名称
		//! \param[in] 传入的随机服务器编号
		//! \param 是否是Questlayer图层，默认不是
		void GeneRandServerName(UGint nServerNumber,UGString &strServerName,UGbool bQuestlayer);
        
	};

} //namespace UGC

#endif // !defined(AFX_UGSMCLOUDSTUB_H__F2ACB033_F582_4263_B9E9_DCA2E56F87DE__INCLUDED_)

