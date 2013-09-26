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
//!  \author 数据转换小组。
//!  \attention 
//!   Copyright (c) 1996-2008 SuperMap Software Limited Company.  <br> 
//!   All Rights Reserved.
//!  \version 6.0
//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////

#ifndef __UGGMLIMPORTPARAMS_H__
#define __UGGMLIMPORTPARAMS_H__

#include "FileParser/UGVectorConfigParams.h"
#include "FileParser/UGExchangeFileType.h"

namespace UGC
{
	//                           导入
	//-------------------------------------------------------------------->
	//! \brief GMl导入参数配置
	class FILEPARSER_API UGGMLImportParams : public UGVectorImportParams
	{
	public:

		//! \brief GML 版本。
		//! \remarks 。
		enum EmVersion
		{
			GML    = 0, //支持点、线、面数据集以及复合数据集，不支持文本数据的写但支持读
			GMLSF  = 1, //支持点、线、面数据集以及复合数据集，不支持文本数据的写但支持读
			GML212 = 2  //支持点、线、面、文本以及复合数据集（文本，复合数据集必须以Fixed Mode导出，FMEObject默认为Fixed Mode）
		};

		//! \brief 构造函数。
		//! \remarks 。
		UGGMLImportParams();

		//! \brief 析构函数。
		//! \remarks 。
		virtual ~UGGMLImportParams();
	public:
		//! \brief 重载获取文件格式类型的函数。
		//! \param  [in]。
		//! \return 。
		//! \remarks 。
		//! \attention 。
		virtual inline UGint GetFileType()const {return UGFileType::GML;}

		//! \brief 设置是否导入3D数据集的标志。
		//! \param  [in]。
		//! \return 。
		//! \remarks 。
		//! \attention 。
		virtual void SetImportAs3DDataset(UGbool bImport3D);

		//! \brief 获取导入3D数据集的标志。
		//! \param  [in]。
		//! \return 。
		//! \remarks 。
		//! \attention 。
		virtual UGbool GetImportAs3DDataset();	

		//! \brief 获取版本
		//! \param  [in]。
		//! \return 。
		//! \remarks 。
		//! \attention 。
		virtual UGint GetVersion()const{return m_nVersion;} 

		//! \brief 设置版本
		//! \param  [in]。
		//! \return 。
		//! \remarks 。
		//! \attention 。
		virtual  void SetVersion(UGint nVersion){m_nVersion=nVersion;}

		//! \brief 以CAD模式导入时，设置是否以原始CAD分层结构导入
		//! \param  [in]。
		//! \return 。
		//! \remarks 。
		//! \attention 。
		void SetImportByLayer(UGbool bByLayer = FALSE);

		//! \brief 判断CAD导入以全图或者多层导入。
		//! \param  [in]。
		//! \return 。
		//! \remarks 。
		//! \attention 。
		UGbool GetImportByLayer() const;

	protected:
		//! \brief 3D数据集的标志，默认为TRUE.
		UGbool m_bImportAs3DData;

		//! \brief GML版本设置,默认为GMLSF
		//! 注：本来默认版本想设置为GML即最高版本到由于最高版本打开最低版本创建的text格式有问题
		//!     姑且设置默认版本为GMLSF，等解决了版本之间的兼容问题，将重新设置默认版本为GML
		UGint m_nVersion;

		//! \brief 标识CAD数据以全图导入换是多层导入。
		//! \remarks m_bMLayerImport = FALSE,全图导入
		UGbool m_bMLayerImport;
	};

	//                                      导出
	//------------------------------------------------------------------------------>
	class FILEPARSER_API UGGMLExportParams : public UGVectorExportParams
	{
		//! \brief GML 版本。
		//! \remarks 。
		enum EmVersion
		{
			GML    = 0, //支持点、线、面数据集以及复合数据集，不支持文本数据的写但支持读
			GMLSF  = 1, //支持点、线、面数据集以及复合数据集，不支持文本数据的写但支持读
			GML212 = 2  //支持点、线、面、文本以及复合数据集（文本，复合数据集必须以Fixed Mode导出，FMEObject默认为Fixed Mode）
		};

	public:
		//! \brief 构造函数。
		//! \remarks 。
		UGGMLExportParams();

		//! \brief 析构函数。
		//! \remarks 。
		virtual ~UGGMLExportParams();

	public:
		//! \brief 重载获取文件格式类型的函数。
		//! \param  [in]。
		//! \return 。
		//! \remarks 。
		//! \attention 。
		virtual inline UGint GetFileType()const {return UGFileType::GML;}

		//! \brief 获取版本
		//! \param  [in]。
		//! \return 。
		//! \remarks 。
		//! \attention 。
		virtual UGint GetVersion()const{return m_nVersion;} 

		//! \brief 设置版本
		//! \param  [in]。
		//! \return 。
		//! \remarks 。
		//! \attention 。
		virtual  void SetVersion(UGint nVersion){m_nVersion=nVersion;}

	protected:
		//! \brief GML版本设置,默认为GML
		UGint m_nVersion;
	};
}

#endif