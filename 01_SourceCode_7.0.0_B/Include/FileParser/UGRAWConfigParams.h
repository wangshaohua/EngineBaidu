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
//!  \author linwenyu。
//!  \attention 
//!   Copyright (c) 1996-2008 SuperMap Software Limited Company.  <br> 
//!   All Rights Reserved.
//!  \version 6.0
//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////

#ifndef AFX_UG_RAW_FILEPARSERCONFIGPARAMS_H__INCLUDED_
#define AFX_UG_RAW_FILEPARSERCONFIGPARAMS_H__INCLUDED_

#include "FileParser/UGRasterConfigParams.h"
#include "FileParser/UGExchangeFileType.h"

namespace UGC {

//! \brief RAW的导入参数配置。
class FILEPARSER_API UGRAWImportParams : public UGRasterImportParams
{	
public:
	//! \brief 构造函数。
	UGRAWImportParams();
	
	//! \brief 析构函数。
	virtual ~UGRAWImportParams();

	//! \brief 返回当前格式转换参数类型。
	virtual inline UGint GetFileType() const { return UGFileType::RAW; }
	
};


//! \brief TGA的导出参数配置。
class FILEPARSER_API UGRAWExportParams : public UGRasterExportParams
{
public:

	//! \brief 返回当前格式转换参数类型。
	virtual inline UGint GetFileType() const { return UGFileType::RAW; }
	
};

} //namespace UGC
#endif // !defined(AFX_UG_RAW_FILEPARSERCONFIGPARAMS_H__INCLUDED_)

