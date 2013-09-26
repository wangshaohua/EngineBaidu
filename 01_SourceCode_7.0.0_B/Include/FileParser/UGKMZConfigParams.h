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

#ifndef __UGKMZIMPORTPARAMS_H__
#define __UGKMZIMPORTPARAMS_H__

#include "FileParser/UGVectorConfigParams.h"
#include "FileParser/UGExchangeFileType.h"

namespace UGC 
{
//! \brief Dxf的导入参数配置。
//! \remarks 备注信息。
class FILEPARSER_API UGKMZImportParams : public UGVectorImportParams
{
public:
	//! \brief 构造函数。
	//! \remarks 。
	UGKMZImportParams();

	//! \brief 析构函数。
	//! \remarks 。
	~UGKMZImportParams();

public:

	//! \brief 重载获取文件格式类型的函数。
	//! \param  [in]。
	//! \return 。
	//! \remarks 。
	//! \attention 。
	virtual inline UGint GetFileType() const	{ return UGFileType::KMZ; }

	//! \brief 设置是否导入可见对象标志
	//! \param  [in]。
	//! \return 。
	//! \remarks 。
	//! \attention 。
	inline void SetImportVisible(UGbool bImport) { m_bImportVisible = bImport; }

	//! \brief 获取是否导入可见对象标志
	//! \param  [in]。
	//! \return 。
	//! \remarks 。
	//! \attention 。
	inline UGbool GetImportVisible() const	{ return m_bImportVisible; }
	//! \brief 设置导入导出编码，某些文件类型是不允许修改的，依据文件类型而定。
	virtual UGbool SetImportOrExportCharset(UGString::Charset Charset){ return FALSE;};
	virtual UGString::Charset GetFileCharset(){return UGString::UTF8;};
protected:
	//! \brief 是否导入可见对象，默认为TUE.
	UGbool m_bImportVisible;//
};

//! \brief Dxf的导出参数配置。
//! \remarks 备注信息。
class FILEPARSER_API UGKMZExportParams : public UGVectorExportParams
{
public:
	//! \brief 构造函数。
	//! \remarks 。
	UGKMZExportParams();

	//! \brief 析构函数。
	//! \remarks 。
	~UGKMZExportParams();
public:
	//! \brief 重载获取文件格式类型的函数。
	//! \param  [in]。
	//! \return 。
	//! \remarks 。
	//! \attention 。
	virtual inline UGint GetFileType() const	{ return UGFileType::KMZ; }
public:
	
	//! \brief 获取要导出的矢量数据版本号。
	//! \param  [in]。
	//! \return 。
	//! \remarks 。
	//! \attention 。
	UGdouble GetVersion() const;	

	//! \brief 设置要导出的矢量数据版本号。
	//! \param  nVer [in] 设置的版本号。
	//! \return 。
	//! \remarks 。
	//! \attention 。
	void SetVersion(UGdouble nVer = 0.1);
	//! \brief 获取要导出的矢量数据集名称数组。
	//! \param  [in]。
	//! \return 。
	//! \remarks 数据集名称数组。
	//! \attention 为了多个数据集导出使用。
	//! 注意此接口是虚函数, 支持多数据集导出功能的格式需要重载
	virtual UGbool GetDtNamesBeExported(UGStrings& arrNames) const;

	//! \brief 设置要导出的矢量数据集名称数组。
	//! \param  name [in] 设置的名称。
	//! \return 。
	//! \remarks 。
	//! \attention 为了多个数据集导出使用。
	//! 注意此接口是虚函数, 支持多数据集导出功能的格式需要重载
	virtual void SetDtNamesBeExported(const UGStrings& arrNames);
	//! \brief 设置导入导出编码，某些文件类型是不允许修改的，依据文件类型而定。
	virtual UGbool SetImportOrExportCharset(UGString::Charset Charset){ return FALSE;};
protected:
	//! \brief 矢量数据要导出的文件版本号。
	//! \remarks 。	
	UGdouble m_dFileVersion;
	//! \brief 需要导出的数据集名字
	UGStrings m_strDatasetNames;
};
} //namespace UGC
#endif // !defined(AFX_UG_PNG_FILEPARSERCONFIGPARAMS_H__INCLUDED_)

