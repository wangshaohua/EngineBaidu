//UGAiGridConfigParams.h: interface for the UGAiGridConfigParams class.
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
//!  \author liyq。
//!  \attention 
//!   Copyright (c) 1996-2010 SuperMap Software Limited Company.  <br> 
//!   All Rights Reserved.
//!  \version 6.0
//////////////////////////////////////////////////////////////////////////

#ifndef AFX_UG_AIGRID_FILEPARSERCONFIGPARAMS_H__INCLUDED_
#define AFX_UG_AIGRID_FILEPARSERCONFIGPARAMS_H__INCLUDED_

#include "FileParser/UGRasterConfigParams.h"
#include "FileParser/UGExchangeFileType.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

namespace UGC
{
	class FILEPARSER_API UGAiGridImportParams : public UGRasterImportParams
	{
	public:
		//! \breif 构造函数
		UGAiGridImportParams();

		//! \breif 析构函数
		virtual ~UGAiGridImportParams();

	public:
		//! \brief 重载获取文件格式类型的函数。
		virtual UGint GetFileType() const	{return UGFileType::AIBinGrid;}
	};
}

#endif