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


#ifndef __FILEPARSE_UGCSVCONFIGPARAMS_H_INCLUDE_
#define __FILEPARSE_UGCSVCONFIGPARAMS_H_INCLUDE_


#include "FileParser/UGVectorConfigParams.h"
#include "FileParser/UGExchangeFileType.h"

namespace UGC 
{


//! \brief csv的导入参数配置。
class FILEPARSER_API UGCSVImportParams : public UGVectorImportParams
{
public:
	//! \brief 构造函数。
	UGCSVImportParams() {
		//m_bHasFieldInFirstLine=FALSE;
		m_strSeparator		= _U(",");
		m_bHasFieldInFirstRow = FALSE;
		m_bSetTargetFieldInfosByUse = FALSE;
	}

	//! \brief 析构函数。
	virtual ~UGCSVImportParams() {};

public:

	//! \brief 重载获取文件格式类型的函数。
	virtual inline UGint GetFileType() const	{ return UGFileType::CSV; }

	UGbool GetHasTargetFieldInfosByUse() const { return m_bSetTargetFieldInfosByUse;}
	void SetHasTargetFieldInfosByUse(UGbool bhasField) {m_bSetTargetFieldInfosByUse = bhasField;}

	UGString GetSeparator() const { return m_strSeparator;};
	void SetSeparator(const UGString& strSeparator) { m_strSeparator = strSeparator;};
	
	void SetHasFieldInFirstRow(const UGbool bHasFieldInFirstRow)  {m_bHasFieldInFirstRow = bHasFieldInFirstRow;}
	UGbool GetHasFieldInFirstRow() const {return m_bHasFieldInFirstRow;}

	virtual UGString::Charset GetFileCharset();

protected:

	// 首行是否有字段
	UGbool m_bHasFieldInFirstRow;
	UGString m_strSeparator;
	// 是否组件层的SetTargetFieldInfos被使用了
	UGbool m_bSetTargetFieldInfosByUse;
};


//! \brief shp的导出参数配置。
class FILEPARSER_API UGCSVExportParams : public UGVectorExportParams
{

public:
	//! \brief 构造函数。
	UGCSVExportParams(){};

	//! \brief 析构函数。
	virtual ~UGCSVExportParams(){};

	//! \brief 重载获取文件格式类型的函数。
	virtual inline UGint GetFileType() const	{ return UGFileType::CSV; }
	
};


} //namespace UGC
#endif // !defined(__FILEPARSE_UGCSVCONFIGPARAMS_H_INCLUDE_)


