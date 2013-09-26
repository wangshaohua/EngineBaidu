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


#if !defined(AFX_UGSMCLOUDSTUB_H__F2ACB033_F582_4263_B9E9_DCA2E56F87DE__INCLUDED_)
#define AFX_UGSMCLOUDSTUB_H__F2ACB033_F582_4263_B9E9_DCA2E56F87DE__INCLUDED_

#include "MapServiceStub/UGMapServiceStub.h"

namespace UGC 
{
//! \brief 服务请求基类。
//! \remarks 所有有关服务请求的都要继承此类。
class MAPSERVICESTUB_API UGSMCloudStub : public UGMapServiceStub 
{
public:
	//! \brief 构造函数。
	UGSMCloudStub();

	//! \brief 析构函数。
	virtual ~UGSMCloudStub();
	
public:
	//! \brief 打开服务。
	//! \param impParams [in]。
	//! \return 成功返回TRUE，失败返回FALSE。
	//! \attention 下载服务前调用。
	virtual UGbool Open(const UGMapServiceParams* pMapServiceParams, UGbool bReSave = TRUE);

	//! \brief 重载获取服务类型的函数。
	//! \param  [in]。
	//! \return 。
	//! \remarks 。
	//! \attention 。
	virtual UGint GetServiceType() const	{ return UGMapServiceType::SuperMapCloud; }

protected:

	//! \brief 生成URL（超图的云服务生成URL的方式）
	//! \param nScalePath[in]产生URL的比例尺
	//! \param nRow[in]产生URL的行
	//! \param nCol[in]产生URL的列
	//! \param strURL[out]请求的URL
	//! \attention 自己的服务就直接用行列号来请求吧
	virtual void GenerateURL(const UGuint& nScalePath, const UGint& nRow, const UGint& nCol, UGString& strURL);

	//! \brief 生成URL时是否采用TileInfo来计算
	virtual UGbool IsGenerateURLByTileInfo(){return FALSE;}

private:
	//! \brief 计算比例尺所对应的地图级别
	//! \return 返回地图所在的级别
	UGint GetMapWorldMapsZoom(const UGdouble dScale);
	//! \brief 是否是私有云服务
	//! 非固定IP的都是私有的云地图服务
	inline UGbool IsPrivateCloud()const
	{return !m_strBaseURL.CompareNoCase(_U("http://supermapcloud.com"))==0;}
	//! \brief 修改超图云服务的基地址
    void GenerateBaseURL(UGString &strBaseURL);
    //! \brief 地图名称
	UGString m_strMapName;
	
};

} //namespace UGC

#endif // !defined(AFX_UGSMCLOUDSTUB_H__F2ACB033_F582_4263_B9E9_DCA2E56F87DE__INCLUDED_)

