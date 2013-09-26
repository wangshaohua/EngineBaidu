//////////////////////////////////////////////////////////////////////////
//                    _   _   ____   ____                    
//   Project         | | | | / ___) / ___)                   
//                   | | | || | __ | |                       
//                   | |_| || |_\ || \___                    
//                    \____/ \____| \ ___)     6.0           
//                                                           
//!  \file SmWebDataSource.h
//!  \brief WMSEngine 的数据源的接口定义。
//!  \details 文件详细信息。
//!  \author duxiaomin。
//!  \attention 
//!   Copyright (c) 1996-2008 SuperMap Software Limited Company.  <br> 
//!   All Rights Reserved.
//!  \version 6.0
//////////////////////////////////////////////////////////////////////////

#ifndef UGDATASOURCEOGC_H
#define UGDATASOURCEOGC_H

#include "Stream/ugexports.h"
#include "Engine/UGDataSource.h"

namespace UGC
{
class UGWebLayersInfos;
class OGCCapabilities;

class ENGINEOGC_API UGDataSourceOGC : public UGDataSource 
{
	
public:
	//! \brief  默认的构造函数
	UGDataSourceOGC();
    //! \brief  带有形参的的构造函数
	UGDataSourceOGC(UGDsConnection dsConn);
	// 基类的纯虚函数,在OGC Web引擎中不实现
	virtual ~UGDataSourceOGC();

public:
	//! \brief 打开数据源,需要预先设置好连接信息。
	//! \return 返回成功或失败。
	virtual UGbool Open();
	
	//! \brief 创建数据源，需要设定好连接信息。
	//! \return 创建成功返回TRUE,失败返回False。
	virtual UGbool Create();
	
	//! \brief 数据源是否和数据连接
	//! \return 是否连接
	virtual UGbool IsConnected();
	
	//!  \brief 仅仅连接数据库,不刷新数据集等
	//! \return 连接
	virtual UGbool Connect();
	
	//! \brief 关闭数据源。
	//! \return 返回成功或失败。
	virtual void Close();
	
	//! \brief 判断数据源是否打开。
	//! \return 数据源状态。
	virtual UGbool IsOpen();
	
	//! \brief 是否有执行某些操作的能力。
	//! \param nAbility 引擎支持的能力[in]。
	//! \return 是否支持，是返加TRUE 否则返回FALSE。
	virtual UGbool HasAbility(UGEngAbility nAbility) const ;
	
	//! \brief 是否支持特定的操作。
	//! \param nAction 引擎支的操作[in]。
	//! \return 是否支持，是返加TRUE 否则返回FALSE。
	virtual UGbool IsSupport(UGEngAction nAction) const ;
	
	//! \brief 获取最后更新时间。
	//! \return 最后更新时间。
	virtual UGTime GetDateLastUpdated() const ;
	
	//! \brief 获取创建时间
	//! \return 最后创建时间。
	virtual UGTime GetDateCreated() const;
	
	//! \brief 得到引擎名称。
	//! \return 引擎名称。
	virtual UGString GetEngineName() const;
	
	//! \brief 保存数据信息。
	//! \return 是否保存成功，是返加TRUE 否则返回FALSE。。
	virtual UGbool SaveInfo();
	
	//! \brief 修改密码。
	//! \param strNewPassword [in]。
	//! \return 是否修改成功，是返加TRUE 否则返回FALSE。
	virtual UGbool ChangePassword(const UGString& strNewPassword);		
	
	//! \brief 开始事务。
	//! \return 是否操作成功，是返加TRUE 否则返回FALSE。
	virtual UGbool BeginTrans();
	
	//! \brief 提交事务。
	//! \return 是否操作成功，是返加TRUE 否则返回FALSE。
	virtual void Commit();
	
	//! \brief 撤消事务。
	//! \return 是否操作成功，是返加TRUE 否则返回FALSE。
	virtual void Rollback();
	
	//! \brief 创建失量数据集。
	//! \param vInfo 失量数据集信息[in]。
	//! \return 失量数据集。
	virtual UGDatasetVector* CreateDatasetVector(
		const UGDatasetVectorInfo& vInfo);
#if !defined SYMBIAN60 && !defined OS_ANDROID && !defined (IOS)
	//! \brief 创建拓扑数据集。
	//! \param strName 拓扑数据集名[in]。
	//! \return 拓扑数据集。
	virtual UGDatasetTopo* CreateDatasetTopo(UGString strName);
#endif
	//! \brief 创建栅格数据集。
	//! \param rInfo 栅格数据集信息[in]。
	//! \return 栅格数据集。
	virtual UGDatasetRaster* CreateDatasetRaster(
		const UGDatasetRasterInfo& rInfo);
	
	//! \brief 删除数据集。
	//! \param strName 数据集名称[in]。
	//! \return 是否操作成功，是返加TRUE 否则返回FALSE。
	virtual UGbool DeleteDataset(const UGString& strName);
	
	//! \brief 是否支持此种数据集类型。
	//! \param nDtType 数据集类型[in]。
	//! \return 是否支持。
	virtual UGbool IsSupport(UGDataset::DatasetType nDtType) const;	
public:
	
	// 得到解析用的临时文件，调用函数负责删除
	void AutoPatchURL();

	//! \brief 通过 GetCapabilities 的URL检查此服务器能力描述的三位数字版本号。
	//! \param strGetCapbilityURL GetCapabilities请求的URL地址[in]。
	//! \return 三位数字版本号。
	int CheckGetCapbility(UGString strGetCapbilityURL);	
	
	//! \brief 得到服务器能力。
	//! \return 是否成功获取。
	UGbool GetCapabilities();	

	//! \brief 版本协商。
	//! \return 是否成功协商得到可用版本。
	UGbool VersionNegotiate();	

	//! \brief 通过EPSG坐标参考系统字符串得到SuperMap坐标参考系统。
	//! \param Prj SuperMap坐标参考系统[out]。
	//! \param strSRS EPSG坐标参考系统字符串[in]。
	//! \return 是否成功进行匹配转化。
	UGbool GetProjectionByName(UGPrjCoordSys& Prj, const UGString& strCRS);	

	//! \brief 设置数据集是否打开缓冲机制。
	//! \param bIsCached 是否打开缓冲机制[in]。
	//! \return TRUE为打开缓冲。
	void SetCached(const UGbool& bIsCached){m_bIsCached = bIsCached;}

	//! \brief 数据集是否打开缓冲机制。
	//! \return TRUE为打开缓冲。
	UGbool IsCached(){return m_bIsCached;}
protected:
	//! \brief 将请求关键字字典载入内存。
	void LoadOGCDict();	

	//! \brief 去除URL中的OGC关键字。
	//! \param strURL URL字符串[in]。
	UGString TrimKeyWord(const UGString& strURL);	

#if (defined(_MSC_VER) && _MSC_VER > 1200) || OS_ANDROID
	//! \brief  打开WMTS数据源
	UGbool OpenDataSourceWMTS();
#endif

public:
	// 用于版本协商的变量
	//! \brief GetCapabilities请求的URL地址。
	//! \remarks URL:http://maps.supermap.com:7070/ogc3/smwms?REQUEST=GetCapabilities&SERVICE=WMS&VERSION=1.3.0
	UGString m_strURL;
	
	//! \brief WMS、WCS或WFS规范的版本号。
	//! \remarks 截到2007年6月18日，WMS规范的最新版本是1.3.0 , WFS的最新版本版本是 1.1.1 。
	//! \brief VERSION=1.3.0&
	UGString m_strVersion;

	//! \brief 数据源能力。
	//! \remarks 有WMS, WCS ,WFS 三种服务器能力。
	OGCCapabilities* m_pCapabilities;
	
	//! \brief 是否缓冲网络数据。
	//! \remarks 备注信息。
	UGbool m_bIsCached;

	//! \breif 用户指定坐标
	UGString m_strCoordinate;
protected:
	// 定义一个OGC URL 请求的关键字字典
	UGDict<UGString,UGint>  m_dictOGCKeyWords;
};

#if !defined OS_ANDROID && !defined (IOS)
extern "C" ENGINEOGC_API UGDataSource* CreateDataSource();
extern "C" ENGINEOGC_API OgdcDataSource* CreateOgdcDataSource();
extern "C" ENGINEOGC_API OgdcFeature* CreateOgdcFeature();
#else
extern "C" ENGINEOGC_API UGDataSource* CreateOGCDataSource();
#endif

}
#endif // !defined(UGDATASOURCEOGC_H)

