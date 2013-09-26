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
//!  \author 张朔。
//!  \attention 
//!   Copyright (c) 1996-2010 SuperMap Software Limited Company.  <br> 
//!   All Rights Reserved.
//!  \version 6.0
//////////////////////////////////////////////////////////////////////////

#ifndef UGSCVCONFIGPARAMS_H
#define UGSCVCONFIGPARAMS_H

#include "FileParser/UGVectorConfigParams.h"
#include "FileParser/UGExchangeFileType.h"

namespace UGC {
	
//! \brief GeoTiff的导入参数配置。
class FILEPARSER_API UGSCVImportParams : public UGVectorImportParams
{	
public:
	
	//! \brief 构造函数。
	UGSCVImportParams();
	
	//! \brief 返回当前格式转换参数类型。
	virtual inline UGint GetFileType() const { return UGFileType::SCV; }

	//! \brief 得到密码字符串。
	UGString GetPassword() const { return m_strPassword; }

	//! \brief 设置密码字符串。
	void SetPassword(UGString val) { m_strPassword = val; }

private:
	UGString m_strPassword;
};


//! \brief GeoTIFF的导出参数配置。
class FILEPARSER_API UGSCVExportParams : public UGVectorExportParams
{
public:
	
	//! \brief 构造函数。
	UGSCVExportParams();
	
	//! \brief 返回当前格式转换参数类型。
	virtual inline UGint GetFileType() const { return UGFileType::SCV; }
	};
	
} //namespace UGC
#endif // !defined(UGSCVCONFIGPARAMS_H)

