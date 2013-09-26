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

#if !defined(AFX_UG_BMP_FILEPARSERCONFIGPARAMS_H__INCLUDED_)
#define AFX_UG_BMP_FILEPARSERCONFIGPARAMS_H__INCLUDED_

#include "FileParser/UGRasterConfigParams.h"
#include "FileParser/UGExchangeFileType.h"

namespace UGC {

//! \brief BMP的导入参数配置。
class FILEPARSER_API UGBmpImportParams : public UGRasterImportParams
{	
public:
	
	//! \brief 返回当前格式转换参数类型。
	virtual inline UGint GetFileType() const { return UGFileType::BMP; }


	//! \brief 设置生成的地理坐标文件的路径。
	//! \param strWorldFile [in]。
	void SetWorldFilePath(const UGString& strWorldFile) { m_strWorldFile = strWorldFile; }

	//! \brief 得到地理坐标文件路径
	//! \param strWorldFile [in]。
	UGString GetWorldFilePath() const { return m_strWorldFile; }

protected:

	UGString m_strWorldFile;


};


//! \brief BMP的导出参数配置。
class FILEPARSER_API UGBmpExportParams : public UGRasterExportParams
{
public:

	UGBmpExportParams() {}
	~UGBmpExportParams() {}	
	
public:
	//! \brief 返回当前格式转换参数类型。
	virtual inline UGint GetFileType() const { return UGFileType::BMP; }


	//! \brief 设置生成的地理坐标文件的路径。
	//! \param strWorldFile [in]。
	void SetWorldFilePath(const UGString& strWorldFile) { m_strWorldFile = strWorldFile;}

	//! \brief 得到地理坐标文件路径
	//! \param strWorldFile [in]。
	UGString GetWorldFilePath() const { return m_strWorldFile; }

protected:

	UGString m_strWorldFile;

};

} //namespace UGC
#endif // !defined(AFX_UG_BMP_FILEPARSERCONFIGPARAMS_H__INCLUDED_)

