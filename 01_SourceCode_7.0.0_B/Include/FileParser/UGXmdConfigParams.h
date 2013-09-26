// UG3dsConfigParams.h: interface for the UGFileParserConfigParams class.
//////////////////////////////////////////////////////////////////////////
//                    _   _   ____   ____                    
//   Project         | | | | / ___) / ___)                   
//                   | | | || | __ | |                       
//                   | |_| || |_\ || \___                    
//                    \____/ \____| \ ___)     6.0           
//                                                           
//!  \file headerfile.h
//!  \brief Class x模型导入导出参数
//!  \details 。
//!  \author zby,2012-8-6
//!  \attention 
//!   Copyright (c) 1996-2010 SuperMap Software Limited Company.  <br> 
//!   All Rights Reserved.
//!  \version 6.0
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_UG_XMD_FILEPARSERCONFIGPARAMS_H__INCLUDED_)
#define AFX_UG_XMD_FILEPARSERCONFIGPARAMS_H__INCLUDED_

#include "FileParser/UGFileParserConfigParams.h"
#include "FileParser/UGModelConfigParams.h"

namespace UGC 
{	
class FILEPARSER_API UGXmdImportParams : public UGModelImportParams
{
public:
	UGXmdImportParams();
	virtual ~UGXmdImportParams();
	virtual UGint GetFileType() const;
};

//! \brief x模型的导出参数配置。
class FILEPARSER_API UGXmdExportParams : public UGModelExportParams
{
public:
    UGXmdExportParams();
	virtual~UGXmdExportParams();
	virtual UGint GetFileType() const;

};

} //namespace UGC
#endif // !defined(AFX_UG_XMD_FILEPARSERCONFIGPARAMS_H__INCLUDED_)

