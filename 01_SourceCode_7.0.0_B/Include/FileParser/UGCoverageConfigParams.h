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

#ifndef AFX_UG_CONVERAGR_FILEPARSERCONFIGPARAMS_H__INCLUDED_
#define AFX_UG_CONVERAGR_FILEPARSERCONFIGPARAMS_H__INCLUDED_

#include "FileParser/UGVectorConfigParams.h"
#include "FileParser/UGExchangeFileType.h"

namespace UGC
{
	class FILEPARSER_API UGCoverageImportParams:public UGVectorImportParams
	{
	public:
		UGCoverageImportParams();
		virtual ~UGCoverageImportParams();

	public:
		//! \brief 重载获取文件格式类型的函数。
		virtual inline UGint GetFileType() const {return UGFileType::AIBinCov;}

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
		UGbool m_bImportAs3DDataset;

	};
}

#endif