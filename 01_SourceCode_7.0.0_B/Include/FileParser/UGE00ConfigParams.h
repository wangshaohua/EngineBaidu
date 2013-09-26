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
//!  \author 。
//!  \attention 
//!   Copyright (c) 1996-2008 SuperMap Software Limited Company.  <br> 
//!   All Rights Reserved.
//!  \version 6.0
//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_UG_E00_FILEPARSERCONFIGPARAMS_H__INCLUDED_)
#define AFX_UG_E00_FILEPARSERCONFIGPARAMS_H__INCLUDED_

#include "FileParser/UGVectorConfigParams.h"
#include "FileParser/UGExchangeFileType.h"

namespace UGC 
{


	//! \brief shp的导入参数配置。
	class FILEPARSER_API UGE00ImportParams : public UGVectorImportParams
	{
	public:
		//! \brief 构造函数。
		UGE00ImportParams();

		//! \brief 析构函数。
		~UGE00ImportParams();

	public:

		//! \brief 重载获取文件格式类型的函数。
		virtual inline UGint GetFileType() const	{ return UGFileType::E00; }

		//! \brief 设置是否导入3D数据集的标志。
		void SetImportAs3DDataset(UGbool bImport3D);

		//! \brief 获取导入3D数据集的标志。
		UGbool GetImportAs3DDataset();	

		//! \brief 判断导入以全图或者多层导入。
		//! \param  [in]。
		//! \return 。
		//! \remarks 。
		//! \attention 。
		virtual UGbool GetImportByLayer() const{return TRUE;}

	protected:
		UGbool m_bImportAs3DData;
	};


	//! \brief shp的导出参数配置。
	class FILEPARSER_API UGE00ExportParams : public UGVectorExportParams
	{

	public:
		//! \brief 构造函数。
		UGE00ExportParams();

		//! \brief 析构函数。
		~UGE00ExportParams();

		//! \brief 重载获取文件格式类型的函数。
		virtual inline UGint GetFileType() const	{ return UGFileType::E00; }

	};

} //namespace UGC
#endif // !defined(AFX_UG_PNG_FILEPARSERCONFIGPARAMS_H__INCLUDED_)

