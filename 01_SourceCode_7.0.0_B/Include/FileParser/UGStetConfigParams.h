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
//!  \author zby。
//!  \attention 
//!   Copyright (c) 1996-2008 SuperMap Software Limited Company.  <br> 
//!   All Rights Reserved.
//!  \version 6.0
//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////

#ifndef AFX_UG_STET_FILEPARSERCONFIGPARAMS_H__INCLUDED_
#define AFX_UG_STET_FILEPARSERCONFIGPARAMS_H__INCLUDED_

#include "FileParser/UGRasterConfigParams.h"
#include "FileParser/UGExchangeFileType.h"

namespace UGC 
{

//! \brief stet的导入参数配置。
class FILEPARSER_API UGStetImportParams : public UGRasterImportParams
{
	
public:
	//! \brief 重载获取文件格式类型的函数。
	UGStetImportParams(){}
	~UGStetImportParams(){}

	virtual UGint GetFileType() const	{ return UGFileType::STET; }
};


//! \brief stet的导出参数配置。
class FILEPARSER_API UGStetExportParams : public UGRasterExportParams
{

public:
	//! 构造函数
	UGStetExportParams(){m_nType=-1;}

	//! 析构函数
	~UGStetExportParams(){}

	//! \brief 重载获取文件格式类型的函数。
	virtual UGint GetFileType() const	{ return UGFileType::STET; }

	//! \brief 设置编码类型
	void SetEncodeType(UGint enType){ this->m_nType = enType;}

	//! \brief 获取编码类型
	UGint GetEncodeType(){return m_nType;}

private:
	//! brief 编码类型
	//! remark 初始值为-1
	UGint m_nType;
};

} //namespace UGC
#endif // !defined(AFX_UG_STET_FILEPARSERCONFIGPARAMS_H__INCLUDED_)

