////////////////////////////////////////////////////////////////////////////
//                    _   _   ____   ____                    
//   Project         | | | | / ___) / ___)                   
//                   | | | || | __ | |                       
//                   | |_| || |_\ || \___                    
//                    \____/ \____| \ ___)     6.0           
//                                                           
//!  \brief Class 。
//!  \details 数据转换组。
//!  \author 数据转换组。
//!  \attention 
//!   Copyright (c) 1996-2010 SuperMap Software Limited Company.  <br> 
//!   All Rights Reserved.
//!  \version 6.0
//////////////////////////////////////////////////////////////////////////

#ifndef AFX_UGMAPSERVICEPARAMSMANAGER_H__INCLUDED_
#define AFX_UGMAPSERVICEPARAMSMANAGER_H__INCLUDED_

//#if _MSC_VER > 1000
//#pragma once
//#endif // _MSC_VER > 1000

#include "Stream/ugdefs.h"
#include "MapServiceStub/UGMapServiceParams.h"


namespace UGC {

//! \brief 转换参数管理。	
class MAPSERVICESTUB_API UGMapServiceParamsManager  
{
public:

	//! \brief 构造函数。
	UGMapServiceParamsManager();

	//! \brief 析构函数。
	virtual ~UGMapServiceParamsManager();

public:

	//! \brief 得到对应格式的导入\读取参数。
	//! \param nType [in]文件类型。
	//! \return 失败返回NULL。
	//! \remarks 用户释需放内存。
	//! \attention 文件类型敏感。
	static UGMapServiceParams* MakeParams(UGint nType);	

	//! \brief 导入参数有效性检查。
	static UGbool IsValidParams(UGint nFileType, const UGMapServiceParams& impParams);	

};

};

#endif // !defined(AFX_UGMAPSERVICEPARAMSMANAGER_H__AB19AA8C_B64E_42F0_BFF3_DDE67CDBA62F__INCLUDED_)

