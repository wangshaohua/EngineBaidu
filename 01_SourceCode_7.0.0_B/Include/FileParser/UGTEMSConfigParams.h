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
//!  \author zhongdz。
//!  \attention 
//!   Copyright (c) 1996-2008 SuperMap Software Limited Company.  <br> 
//!   All Rights Reserved.
//!  \version 6.0
//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_UG_TEMS_FILEPARSERCONFIGPARAMS_H__INCLUDED_)
#define AFX_UG_TEMS_FILEPARSERCONFIGPARAMS_H__INCLUDED_

#include "FileParser/UGVectorConfigParams.h"
#include "FileParser/UGExchangeFileType.h"
#include "FileParser/UGRasterConfigParams.h"

namespace UGC 
{


//! \brief 电信数据Vector的导入参数配置。
//! \remarks 备注信息。
class FILEPARSER_API UGTemsVectorImportParams : public UGVectorImportParams
{
public:
	//! \brief 构造函数。
	//! \remarks 。
	UGTemsVectorImportParams();

	//! \brief 析构函数。
	//! \remarks 。
	~UGTemsVectorImportParams();

public:
	//! \brief 重载获取文件格式类型的函数。
	//! \param  [in]。
	//! \return 。
	//! \remarks 。
	//! \attention 。
	virtual inline UGint GetFileType() const	{ return UGFileType::TEMSVector; }

	//! \brief 判断导入以全图或者多层导入。
	//! \param  [in]。
	//! \return 。
	//! \remarks 。
	//! \attention 。
	virtual UGbool GetImportByLayer() const{return TRUE;}

};


//! \brief 电信数据Vector的导出参数配置。
//! \remarks 备注信息。
class FILEPARSER_API UGTemsVectorExportParams : public UGVectorExportParams
{
public:
	//! \brief 构造函数。
	//! \remarks 。
	UGTemsVectorExportParams();

	//! \brief 析构函数。
	//! \remarks 。
	~UGTemsVectorExportParams();

	//! \brief 重载获取文件格式类型的函数。
	//! \param  [in]。
	//! \return 。
	//! \remarks 。
	//! \attention 。
	virtual inline UGint GetFileType() const	{ return UGFileType::TEMSVector;}

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

protected:
	//! \brief 需要导出的数据集名字
	UGStrings m_strDatasetNames;

};



//! \brief 电信数据Building vector的导入参数配置。
//! \remarks 备注信息。
class FILEPARSER_API UGTemsBldngVctrImportParams : public UGVectorImportParams
{
public:
	//! \brief 构造函数。
	//! \remarks 。
	UGTemsBldngVctrImportParams();

	//! \brief 析构函数。
	//! \remarks 。
	~UGTemsBldngVctrImportParams();

	//! \brief 判断导入以全图或者多层导入。
	//! \param  [in]。
	//! \return 。
	//! \remarks 。
	//! \attention 。
	virtual UGbool GetImportByLayer() const{return TRUE;}

public:
	//! \brief 重载获取文件格式类型的函数。
	//! \param  [in]。
	//! \return 。
	//! \remarks 。
	//! \attention 。
	virtual inline UGint GetFileType() const	{ return UGFileType::TEMSBldngVctr;}

};


//! \brief 电信数据Building vector的导出参数配置。
//! \remarks 备注信息。
class FILEPARSER_API UGTemsBldngVctrExportParams : public UGVectorExportParams
{
public:
	//! \brief 构造函数。
	//! \remarks 。
	UGTemsBldngVctrExportParams();

	//! \brief 析构函数。
	//! \remarks 。
	~UGTemsBldngVctrExportParams();

	//! \brief 重载获取文件格式类型的函数。
	//! \param  [in]。
	//! \return 。
	//! \remarks 。
	//! \attention 。
	virtual inline UGint GetFileType() const	{ return UGFileType::TEMSBldngVctr ;}

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

protected:
	//! \brief 需要导出的数据集名字
	UGStrings m_strDatasetNames;

};



//! \brief 电信数据Clutter的导入参数配置。
//! \remarks 备注信息。
class FILEPARSER_API UGTemsClutterImportParams : public UGRasterImportParams
{
public:
	//! \brief 构造函数。
	//! \remarks 。
	UGTemsClutterImportParams();

	//! \brief 析构函数。
	//! \remarks 。
	~UGTemsClutterImportParams();

public:
	//! \brief 重载获取文件格式类型的函数。
	//! \param  [in]。
	//! \return 。
	//! \remarks 。
	//! \attention 。
	virtual inline UGint GetFileType() const	{ return UGFileType::TEMSClutter; }

	//! \brief 设置生成的地理坐标文件的路径。
	//! \param strWorldFile [in]。
	void SetWorldFilePath(const UGString& strWorldFile) { m_strWorldFile = strWorldFile; }

	//! \brief 得到地理坐标文件路径
	//! \param strWorldFile [in]。
	UGString GetWorldFilePath() const { return m_strWorldFile; }

protected:

	UGString m_strWorldFile;

};


//! \brief 电信数据Clutter的导出参数配置。
//! \remarks 备注信息。
class FILEPARSER_API UGTemsClutterExportParams : public UGRasterExportParams
{
public:
	//! \brief 构造函数。
	//! \remarks 。
	UGTemsClutterExportParams();

	//! \brief 析构函数。
	//! \remarks 。
	~UGTemsClutterExportParams();

	//! \brief 重载获取文件格式类型的函数。
	//! \param  [in]。
	//! \return 。
	//! \remarks 。
	//! \attention 。
	virtual inline UGint GetFileType() const	{ return UGFileType::TEMSClutter; }

	//! \brief 设置生成的地理坐标文件的路径。
	//! \param strWorldFile [in]。
	void SetWorldFilePath(const UGString& strWorldFile) { m_strWorldFile = strWorldFile; }

	//! \brief 得到地理坐标文件路径
	//! \param strWorldFile [in]。
	UGString GetWorldFilePath() const { return m_strWorldFile; }

protected:

	UGString m_strWorldFile;

};


} //namespace UGC

#endif // !defined(AFX_UG_TEMS_FILEPARSERCONFIGPARAMS_H__INCLUDED_)

