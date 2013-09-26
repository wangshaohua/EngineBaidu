// UGAllTypeConfigParams.h: interface for the UGFileParserConfigParams class.
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
//!  \author Conversion。
//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////

#ifndef FILEPARSER_UG_ALLTYPE_CONFIGPARAMS_H
#define FILEPARSER_UG_ALLTYPE_CONFIGPARAMS_H

#include "FileParser/UGFileParserConfigParams.h"
#include "FileParser/UGExchangeFileType.h"

namespace UGC {

	//! \brief BMP的导入参数配置。
	class FILEPARSER_API UGSimpleImportParams : public UGImportParams
	{	
	public:
			UGSimpleImportParams();

			virtual ~UGSimpleImportParams();

			virtual UGint GetFileType() const	{ return UGFileType::FMEWorkBench; }

			virtual void SetSourceFileType(const UGFileType::EmType fileType);

			virtual UGFileType::EmType GetSourceFileType() const;
	private:
		UGFileType::EmType m_FileType;

	};
}

#endif