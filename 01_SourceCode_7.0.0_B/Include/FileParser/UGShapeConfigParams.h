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

#if !defined(AFX_UG_SHAPE_FILEPARSERCONFIGPARAMS_H__INCLUDED_)
#define AFX_UG_SHAPE_FILEPARSERCONFIGPARAMS_H__INCLUDED_

#include "FileParser/UGVectorConfigParams.h"
#include "FileParser/UGExchangeFileType.h"

namespace UGC 
{


//! \brief shp的导入参数配置。
class FILEPARSER_API UGShapeImportParams : public UGVectorImportParams
{
public:
	//! \brief 构造函数。
	UGShapeImportParams();

	//! \brief 析构函数。
	~UGShapeImportParams();

public:

	//! \brief 重载获取文件格式类型的函数。
	virtual inline UGint GetFileType() const	{ return UGFileType::Shape; }

	//! \brief 设置是否导入3D数据集的标志。
	void SetImportAs3DDataset(UGbool bImport3D);

	//! \brief 获取导入3D数据集的标志。
	UGbool GetImportAs3DDataset();	

protected:
	UGbool m_bImportAs3DData;
};


//! \brief shp的导出参数配置。
class FILEPARSER_API UGShapeExportParams : public UGVectorExportParams
{

public:
	//! \brief 构造函数。
	UGShapeExportParams();

	//! \brief 析构函数。
	~UGShapeExportParams();

	//! \brief 重载获取文件格式类型的函数。
	virtual inline UGint GetFileType() const	{ return UGFileType::Shape; }
	
};

typedef UGShapeImportParams UGShpImportParams;
typedef UGShapeExportParams UGShpExportParams;

} //namespace UGC
#endif // !defined(AFX_UG_PNG_FILEPARSERCONFIGPARAMS_H__INCLUDED_)

