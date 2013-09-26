// UG3dsConfigParams.h: interface for the UGFileParserConfigParams class.
//////////////////////////////////////////////////////////////////////////
//                    _   _   ____   ____                    
//   Project         | | | | / ___) / ___)                   
//                   | | | || | __ | |                       
//                   | |_| || |_\ || \___                    
//                    \____/ \____| \ ___)     6.0           
//                                                           
//!  \file headerfile.h
//!  \brief Class dae模型导入导出参数
//!  \details 。
//!  \author zby,2012-8-6
//!  \attention 
//!   Copyright (c) 1996-2010 SuperMap Software Limited Company.  <br> 
//!   All Rights Reserved.
//!  \version 6.0
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_UG_DAE_FILEPARSERCONFIGPARAMS_H__INCLUDED_)
#define AFX_UG_DAE_FILEPARSERCONFIGPARAMS_H__INCLUDED_

#include "FileParser/UGModelConfigParams.h"

namespace UGC 
{	
class FILEPARSER_API UGDAEImportParams : public UGModelImportParams
{
public:
	
	UGDAEImportParams();
	virtual ~UGDAEImportParams();

	virtual UGint GetFileType() const;
};



class FILEPARSER_API UGDAEExportParams : public UGModelExportParams
{
public:

	UGDAEExportParams();
	virtual ~UGDAEExportParams();
	virtual UGint GetFileType() const;
};

} //namespace UGC
#endif // !defined(AFX_UG_DAE_FILEPARSERCONFIGPARAMS_H__INCLUDED_)

