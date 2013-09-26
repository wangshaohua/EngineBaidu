// UGSgmConfigParams.h: interface for the UGFileParserConfigParams class.
//////////////////////////////////////////////////////////////////////////
//                    _   _   ____   ____                    
//   Project         | | | | / ___) / ___)                   
//                   | | | || | __ | |                       
//                   | |_| || |_\ || \___                    
//                    \____/ \____| \ ___)     6.0           
//                                                           
//!  \file headerfile.h
//!  \brief Class SGM模型导入导出参数
//!  \details 。
//!  \author sunye。
//!  \attention 
//!   Copyright (c) 1996-2010 SuperMap Software Limited Company.  <br> 
//!   All Rights Reserved.
//!  \version 6.0
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_UG_SGM_FILEPARSERCONFIGPARAMS_H__INCLUDED_)
#define AFX_UG_SGM_FILEPARSERCONFIGPARAMS_H__INCLUDED_

#include "FileParser/UGFileParserConfigParams.h"
#include "FileParser/UGExchangeFileType.h"

namespace UGC 
{
//! \brief SGM的导入参数配置。
class FILEPARSER_API UGSgmImportParams : public UGImportParams
{
public:
	//! \brief 重载获取文件格式类型的函数。
	virtual UGint GetFileType() const	{ return UGFileType::SGM; }
};

//! \brief SGM的导出参数配置。
class FILEPARSER_API UGSgmExportParams : public UGExportParams
{
public:
	//! \brief 重载获取文件格式类型的函数。
	virtual UGint GetFileType() const	{ return UGFileType::SGM; }
};

} //namespace UGC
#endif // !defined(AFX_UG_SGM_FILEPARSERCONFIGPARAMS_H__INCLUDED_)

