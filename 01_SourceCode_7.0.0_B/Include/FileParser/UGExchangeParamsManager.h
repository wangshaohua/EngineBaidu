////////////////////////////////////////////////////////////////////////////
//                    _   _   ____   ____                    
//   Project         | | | | / ___) / ___)                   
//                   | | | || | __ | |                       
//                   | |_| || |_\ || \___                    
//                    \____/ \____| \ ___)     6.0           
//                                                           
//!  \brief Class 。
//!  \details 格式转换组。
//!  \author linwenyu。
//!  \attention 
//!   Copyright (c) 1996-2010 SuperMap Software Limited Company.  <br> 
//!   All Rights Reserved.
//!  \version 6.0
//////////////////////////////////////////////////////////////////////////

#ifndef AFX_UGEXCHANGEPARAMSMANAGER_H__INCLUDED_
#define AFX_UGEXCHANGEPARAMSMANAGER_H__INCLUDED_

//#if _MSC_VER > 1000
//#pragma once
//#endif // _MSC_VER > 1000

#include "Stream/ugdefs.h"
#include "FileParser/UGFileParserConfigParams.h"


namespace UGC {

//! \brief 转换参数管理。	
class FILEPARSER_API UGExchangeParamsManager  
{
public:

	//! \brief 构造函数。
	UGExchangeParamsManager();

	//! \brief 析构函数。
	virtual ~UGExchangeParamsManager();

public:

	//! \brief 得到对应格式的导入\读取参数。
	//! \param nType [in]文件类型。
	//! \return 失败返回NULL。
	//! \remarks 用户释需放内存。
	//! \attention 文件类型敏感。
	static UGImportParams* MakeImportParams(UGint nType);	

	//! \brief 得到对应格式的导出\创建参数。
	//! \param nType [in]文件类型。
	//! \return 失败返回NULL。
	//! \remarks 用户需释放内存。
	//! \attention 文件类型敏感。
	static UGExportParams* MakeExportParams(UGint nType);


	//! \brief 释放导入参数类对象
	//! \param pFileParser 释放传入对象
	//! \return void 
	static void DestoryImportParams(UGImportParams* &pImportParams);
    
	//! \brief 释放导入参数类对象
	//! \param pFileParser 释放传入对象
	//! \return void 
	static void DestoryExportParams(UGExportParams* &pExportParams);


	//! \brief 导入参数有效性检查。
	static UGbool IsValidImportParams(UGint nFileType, const UGImportParams& impParams);	

	//! \brief 导出参数有效性检查。
	static UGbool IsValidExportParams(UGint nFileType, const UGExportParams& expParams);

};

};

#endif // !defined(AFX_UGEXCHANGEPARAMSMANAGER_H__AB19AA8C_B64E_42F0_BFF3_DDE67CDBA62F__INCLUDED_)

