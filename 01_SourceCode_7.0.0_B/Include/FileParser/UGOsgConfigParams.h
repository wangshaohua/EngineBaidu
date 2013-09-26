// UG3dsConfigParams.h: interface for the UGFileParserConfigParams class.
//////////////////////////////////////////////////////////////////////////
//                    _   _   ____   ____                    
//   Project         | | | | / ___) / ___)                   
//                   | | | || | __ | |                       
//                   | |_| || |_\ || \___                    
//                    \____/ \____| \ ___)     6.0           
//                                                           
//!  \file headerfile.h
//!  \brief Class osg以及osgb,osgt等模型文件导入导出参数
//!  \details 。
//!  \author zby,2012-8-6
//!  \attention 
//!   Copyright (c) 1996-2010 SuperMap Software Limited Company.  <br> 
//!   All Rights Reserved.
//!  \version 6.0
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_UG_OSG_FILEPARSERCONFIGPARAMS_H__INCLUDED_)
#define AFX_UG_OSG_FILEPARSERCONFIGPARAMS_H__INCLUDED_

#include "FileParser/UGFileParserConfigParams.h"
#include "FileParser/UGExchangeFileType.h"
#include "FileParser/UGModelConfigParams.h"

namespace UGC 
{	
class FILEPARSER_API UGOsgImportParams : public UGModelImportParams
{
public:
    
	//! \brief osg 构造函数
	UGOsgImportParams();
    
	//! \brief osg 析构函数
    virtual ~UGOsgImportParams();

	//! \brief 重载获取文件格式类型的函数
	virtual UGint GetFileType() const;
    
	//! \brief 设置模型的定位点
	//! \return
	void SetPosition(const UGPoint3D pntPosition3D);
    
	//! \brief 返回模型的定位地点
	UGPoint3D GetPosition()const;

private:
	//! \brief 模型导入的定位点；
	//! \attention 这个参数由用户来传递进来
	UGPoint3D m_pntPosition;
};


//! \brief OSG的导出参数配置。
class FILEPARSER_API UGOsgExportParams : public UGExportParams
{
public:
	//! \brief osg 导出设置参数构造函数
	UGOsgExportParams();

	//! \brief osg osg导出设置析构函数
	virtual ~UGOsgExportParams();

	//! \brief 重载获取文件格式类型的函数。
	virtual UGint GetFileType() const;
};

} //namespace UGC
#endif // !defined(AFX_UG_OSG_FILEPARSERCONFIGPARAMS_H__INCLUDED_)

