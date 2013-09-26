/////////////////////////////////////////////////////////////////////////
//                    _   _   ____   ____                    
//   Project         | | | | / ___) / ___)                   
//                   | | | || | __ | |                       
//                   | |_| || |_\ || \___                    
//                    \____/ \____| \ ___)     6.0           
//                                                           
//!  \file headerfile.h
//!  \brief Class 。
//!  \details 。
//!  \author conversion。
//!  \attention 
//!   Copyright (c) 1996-2010 SuperMap Software Limited Company.  <br> 
//!   All Rights Reserved.
//!  \version 6.0
//////////////////////////////////////////////////////////////////////////

#ifndef UGFILEGDBRasterPARAMS_H
#define UGFILEGDBRasterPARAMS_H

#include "FileParser/UGRasterConfigParams.h"
#include "FileParser/UGExchangeFileType.h"

namespace UGC
{
	class FILEPARSER_API UGGDBFRasterImportParams : public UGRasterImportParams
	{	
	public:

		//! \brief 构造函数。
		UGGDBFRasterImportParams();

		//! \brief 析构函数
		virtual ~UGGDBFRasterImportParams();

		//! \brief 返回当前格式转换参数类型。
		virtual UGint GetFileType() const { return UGFileType::GDBFRaster; }

		//! \brief 判断导入以全图或者多层导入。
		//! \param  [in]。
		//! \return 。
		//! \remarks 。
		//! \attention 。
		virtual UGbool GetImportByLayer() const{return TRUE;}
	};
}

#endif