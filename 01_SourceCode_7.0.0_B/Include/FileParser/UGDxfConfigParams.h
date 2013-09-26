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

#if !defined(AFX_UG_DXF_FILEPARSERCONFIGPARAMS_H__INCLUDED_)
#define AFX_UG_DXF_FILEPARSERCONFIGPARAMS_H__INCLUDED_

#include "FileParser/UGAcadConfigParams.h"
#include "FileParser/UGExchangeFileType.h"

namespace UGC 
{
//! \brief Dxf的导入参数配置。
class FILEPARSER_API UGDxfImportParams : public UGAcadImportParams
{
public:
	//! \brief 构造函数。
	UGDxfImportParams();

	//! \brief 析构函数。
	~UGDxfImportParams();

public:

	//! \brief 重载获取文件格式类型的函数。
	virtual inline UGint GetFileType() const	{ return UGFileType::DXF; }	
	//! \brief 设置导入导出编码，某些文件类型是不允许修改的，依据文件类型而定。
	virtual UGbool SetImportOrExportCharset(UGString::Charset Charset){ return FALSE;};
	virtual UGString::Charset GetFileCharset(){return UGString::UCS2LE;};
};


//! \brief Dxf的导出参数配置。
class FILEPARSER_API UGDxfExportParams : public UGAcadExportParams
{
public:
	//! \brief 构造函数。
	UGDxfExportParams();

	//! \brief 析构函数。
	~UGDxfExportParams();

public:
	//! \brief 重载获取文件格式类型的函数。
	virtual inline UGint GetFileType() const	{ return UGFileType::DXF; }
	//! \brief 设置导入导出编码，某些文件类型是不允许修改的，依据文件类型而定。
	virtual UGbool SetImportOrExportCharset(UGString::Charset Charset){ return FALSE;};
	virtual UGString::Charset GetFileCharset(){return UGString::UCS2LE;};
};
} //namespace UGC
#endif // !defined(AFX_UG_PNG_FILEPARSERCONFIGPARAMS_H__INCLUDED_)

