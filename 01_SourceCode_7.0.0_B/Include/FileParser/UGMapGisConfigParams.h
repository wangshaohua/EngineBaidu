// UGFileParserConfigParams.h: interface for the UGFileParserConfigParams class.
//////////////////////////////////////////////////////////////////////////
//                    _   _   ____   ____                    
//   Project         | | | | / ___) / ___)                   
//                   | | | || | __ | |                       
//                   | |_| || |_\ || \___                    
//                    \____/ \____| \ ___)     6.0           
//                                                           
//!  \file headerfile.h
//!  \brief Class 的接口定义。
//!  \details 文件详细信息。
//!  \author 唐争强。
//!  \attention 
//!   Copyright (c) 1996-2008 SuperMap Software Limited Company.  <br> 
//!   All Rights Reserved.
//!  \version 6.0
//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////

#ifndef __UGMAPGISIMPORTPARAMS_H__
#define __UGMAPGISIMPORTPARAMS_H__

#include "FileParser/UGVectorConfigParams.h"
#include "FileParser/UGExchangeFileType.h"

namespace UGC 
{
//! \brief Dxf的导入参数配置。
//! \remarks 备注信息。
class FILEPARSER_API UGMapGisImportParams : public UGVectorImportParams
{
public:
	//! \brief 构造函数。
	//! \remarks 。
	UGMapGisImportParams();

	//! \brief 析构函数。
	//! \remarks 。
	~UGMapGisImportParams();

public:

	//! \brief 重载获取文件格式类型的函数。
	//! \param  [in]。
	//! \return 。
	//! \remarks 。
	//! \attention 。
	virtual inline UGint GetFileType() const	{ return UGFileType::MAPGIS; }
public:
	//! \brief 获取MAPGIS颜色索引文件路径。
	//! \param  [in]。
	//! \return 。
	//! \remarks 。
	//! \attention 。
	UGString GetColorIndexFilePath()const;
	//! \brief 设置MAPGIS颜色索引文件路径。
	//! \param  [in]。
	//! \return 。
	//! \remarks 。
	//! \attention 。
	void SetColorIndexFilePath(const UGString & strPath);
protected:
	//! \brief MAPGIS颜色索引文件路径，默认为BinD下的"\MapGISColor.wat"文件
	UGString m_strColorIndexFilePath;
};

//! \brief Dxf的导出参数配置。
//! \remarks 备注信息。
class FILEPARSER_API UGMapGisExportParams : public UGVectorExportParams
{
public:
	//! \brief 构造函数。
	//! \remarks 。
	UGMapGisExportParams();

	//! \brief 析构函数。
	//! \remarks 。
	~UGMapGisExportParams();
public:
	//! \brief 重载获取文件格式类型的函数。
	//! \param  [in]。
	//! \return 。
	//! \remarks 。
	//! \attention 。
	virtual inline UGint GetFileType() const	{ return UGFileType::MAPGIS; }
public:
	
	//! \brief 获取要导出的矢量数据版本号。
	//! \param  [in]。
	//! \return 。
	//! \remarks 。
	//! \attention 。
	UGint GetVersion() const;	

	//! \brief 设置要导出的矢量数据版本号。
	//! \param  nVer [in] 设置的版本号。
	//! \return 。
	//! \remarks 。
	//! \attention 。
	void SetVersion(UGint nVer);
protected:
	//! \brief 矢量数据要导出的文件版本号。
	//! \remarks 。	
	UGint m_dFileVersion;
};
} //namespace UGC
#endif // !defined(AFX_UG_PNG_FILEPARSERCONFIGPARAMS_H__INCLUDED_)

