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

#ifndef AFX_UG_SIT_FILEPARSERCONFIGPARAMS_H__INCLUDED_
#define AFX_UG_SIT_FILEPARSERCONFIGPARAMS_H__INCLUDED_

#include "FileParser/UGRasterConfigParams.h"
#include "FileParser/UGExchangeFileType.h"

namespace UGC 
{


//! \brief GeoTiff的导入参数配置。
class FILEPARSER_API UGSitImportParams : public UGRasterImportParams
{
	
public:

	//! \brief 重载获取文件格式类型的函数。
	virtual UGint GetFileType() const	{ return UGFileType::SIT; }
	
	//! \brief 获取打开密码。
	UGString GetPassWord() const {return m_strPassWord;}

	//! \brief 设置打开密码。
	//! \param password  [in] 设置打开密码。
	void SetPassWord(UGString password){m_strPassWord = password;}

private:
	//! 密码
	UGString m_strPassWord;
};


//! \brief GeoTIFF的导出参数配置。
class FILEPARSER_API UGSitExportParams : public UGRasterExportParams
{

public:
	//! 构造函数
	UGSitExportParams();

	//! 析构函数
	~UGSitExportParams();

	//! \brief 重载获取文件格式类型的函数。
	virtual UGint GetFileType() const	{ return UGFileType::SIT; }

	//! \brief 设置编码类型
	void SetEncodeType(UGint enType){ this->m_nType = enType;}

	//! \brief 获取编码类型
	UGint GetEncodeType(){return m_nType;}

	void SetPassword(const UGString strPasswrod);

	UGString GetPassword() const;
	
private:
	//! brief 编码类型
	//! remark 初始值为-1
	UGint m_nType;

	UGString m_strPassword;
};

} //namespace UGC
#endif // !defined(AFX_UG_SIT_FILEPARSERCONFIGPARAMS_H__INCLUDED_)

