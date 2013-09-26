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
//!  \author conversion。
//!  \attention 
//!   Copyright (c) 1996-2010 SuperMap Software Limited Company.  <br> 
//!   All Rights Reserved.
//!  \version 6.0
//////////////////////////////////////////////////////////////////////////

#ifndef UGFILEGDBVECTORPARAMS_H
#define UGFILEGDBVECTORPARAMS_H

#include "FileParser/UGVectorConfigParams.h"
#include "FileParser/UGExchangeFileType.h"

namespace UGC {

	//! \brief GeoTiff的导入参数配置。
	class FILEPARSER_API UGGDBFVectorImportParams : public UGVectorImportParams
	{	
	public:

		//! \brief 构造函数。
		UGGDBFVectorImportParams();

		//! \brief 返回当前格式转换参数类型。
		virtual inline UGint GetFileType() const { return UGFileType::GDBFVector; }

		//! \brief 判断导入以全图或者多层导入。
		//! \param  [in]。
		//! \return 。
		//! \remarks 。
		//! \attention 。
		virtual UGbool GetImportByLayer() const{return TRUE;}

	};


	//! \brief GeoTIFF的导出参数配置。
	class FILEPARSER_API UGGDBFVectorExportParams : public UGVectorExportParams
	{
	public:

		//! \brief 构造函数。
		UGGDBFVectorExportParams();

		//! \brief 返回当前格式转换参数类型。
		virtual inline UGint GetFileType() const { return UGFileType::GDBFVector; }
	};

} //namespace UGC
#endif // !defined(UGSCVCONFIGPARAMS_H)

