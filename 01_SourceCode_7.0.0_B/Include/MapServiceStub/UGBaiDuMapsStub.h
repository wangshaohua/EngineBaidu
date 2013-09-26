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


#if !defined(AFX_UGBAIDUMAPSSTUB_H__F2ACB033_F582_4263_B9E9_DCA2E56F87DE__INCLUDED_)
#define AFX_UGBAIDUMAPSSTUB_H__F2ACB033_F582_4263_B9E9_DCA2E56F87DE__INCLUDED_

#include "MapServiceStub/UGMapServiceStub.h"

namespace UGC 
{
	class UGHMACSHA1;
//! \brief 服务请求基类。
//! \remarks 所有有关服务请求的都要继承此类。
class MAPSERVICESTUB_API UGBaiDuMapsStub : public UGMapServiceStub 
{
public:
	//! \brief 构造函数。
	UGBaiDuMapsStub();

	//! \brief 析构函数。
	virtual ~UGBaiDuMapsStub();
	
public:
	//! \brief 打开服务。
	//! \param impParams [in]。
	//! \return 成功返回TRUE，失败返回FALSE。
	//! \attention 下载服务前调用。
	virtual UGbool Open(const UGMapServiceParams* impParams, UGbool bReSave = TRUE);

protected:

	//! \brief 生成URL数组
	//! \param tileInfo[in]产生URL的瓦片
	//! \param strURL[out]请求的URL
	virtual void GenerateURL(const UGTileInfo& tileInfo, UGString& strURL);
    
	//! \brief 生成URL时是否采用TileInfo来计算
	virtual UGbool IsGenerateURLByTileInfo(){return TRUE;}
    
    //! \brief 当前请求地图类型
	UGString m_strMapType;
    
    //! \brief 获得地图比例尺级别
	 UGint GetBaiDuMapsZoom( UGdouble dScale);
    
	//! \brief 获取数据集名称
    //! \param strResName 获取的数据集名称
    //! \param nMapType 地图类型
    //! \param nDataVersion 数据版本 
	void GetResDataName(UGString strMapType, UGString &strResName, UGint &nMapType,UGint& nDataVersion);
private:
	//! \brief  生成3dlayer URl
	//! \Param tileInfo[in] 产生URL的瓦片信息
	//! \ Param strURL[out] 生成的URL
	void GenerateURL3D(const UGTileInfo& tileInfo,UGString & strURL);
	//! \brief 是否是三维城市地图
	//!\ \return 如果是三维地图返回为true,否则返回为false

	UGbool Is3DCityMap(const UGString& strMapType);

private: 

	//! \brief 城市名称标识
	UGString m_strCityMark;
	//! \brief 城市编号
    UGint m_nNumber;

};

} //namespace UGC

#endif // !defined(AFX_UGBAIDUSTUB_H__F2ACB033_F582_4263_B9E9_DCA2E56F87DE__INCLUDED_)

