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
//!  \author linwenyu。
//!  \attention 
//!   Copyright (c) 1996-2008 SuperMap Software Limited Company.  <br> 
//!   All Rights Reserved.
//!  \version 6.0
//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_UG_MITAB_FILEPARSERCONFIGPARAMS_H__INCLUDED_)
#define AFX_UG_MITAB_FILEPARSERCONFIGPARAMS_H__INCLUDED_

#include "FileParser/UGVectorConfigParams.h"
#include "FileParser/UGWorkSpaceConfigParams.h"
#include "FileParser/UGExchangeFileType.h"

namespace UGC {

class FILEPARSER_API UGMiWorImportParams : public UGWorkspaceImportParams
{	
public:

	//! \brief 构造函数。
	UGMiWorImportParams();

	//! \brief 返回当前格式转换参数类型。

	//! \param  [in]。
	//! \return 符号库的路径。
	//! \remarks 。
	//! \attention 。
	virtual inline UGint GetFileType() const { return UGFileType::WOR; }

	//! \brief 返回点符号库的路径。
	//! \param  [in]。
	//! \return 符号库的路径。
	//! \remarks 。
	//! \attention 。
	UGString GetMarkerStyleLibPath() const {return m_markerStyleLibPath;}

	//! \brief 返回线符号库的路径。
	//! \param  [in]。
	//! \return 符号库的路径。
	//! \remarks 。
	//! \attention 。
	UGString GetLineStyleLibPath() const {return m_lineStyleLibPath;}

	//! \brief 返回填充符号库的路径。
	//! \param  [in]。
	//! \return 。
	//! \remarks 。
	//! \attention 。
	UGString GetFillStyleLibPath() const {return m_fillStyleLibPath;}

	//! \brief 设置点符号库的路径。
	//! \param path [in] 符号库的路径。
	//! \return 。
	//! \remarks 不设置或为空程序默认找Bin目录下的MapInfo.sym。
	//! \attention 。
	void SetMarkerStyleLibPath(UGString path) {m_markerStyleLibPath = path;}

	//! \brief 设置线符号库的路径。
	//! \param path [in] 符号库的路径。
	//! \return 。
	//! \remarks 不设置或为空程序默认找Bin目录下的MapInfo.lsl。
	//! \attention 。
	void SetLineStyleLibPath(UGString path) {m_lineStyleLibPath = path;}

	//! \brief 设置填充符号库的路径。
	//! \param path [in] 符号库的路径。
	//! \return 。
	//! \remarks 不设置或为空程序默认找Bin目录下的MapInfo.bru。
	//! \attention 。
	void SetFillStyleLibPath(UGString path) {m_fillStyleLibPath = path;}

	//! \brief 设置风格对照表的路径。
	//! \param [in] 。
	//! \return 风格对照表的路径。
	//! \remarks 不设置或为空程序默认找Bin目录下的MiStyMap.conf。
	//! \attention 。
	UGString GetStyleMapFilePath() {return m_StyleMapFilePath;}

	//! \brief 设置填风格对照表的路径。
	//! \param path [in] 风格对照表的路径。
	//! \return 。
	//! \remarks 不设置或为空程序默认找Bin目录下的MiStyMap.conf。
	//! \attention 。
	void SetStyleMapFilePath(UGString path) {m_StyleMapFilePath = path;}

private:
	//点符号库的路径
	UGString m_markerStyleLibPath;

	//线符号库的路径
	UGString m_lineStyleLibPath;

	//填充符号库的路径
	UGString m_fillStyleLibPath;


	//风格对照表路径
	UGString m_StyleMapFilePath;
};

//! \brief MapInfo(TAB)的导入参数配置。
class FILEPARSER_API UGMitabImportParams : public UGVectorImportParams
{	
public:

	//! \brief 构造函数。
	UGMitabImportParams();

	//! \brief 返回当前格式转换参数类型。
	virtual inline UGint GetFileType() const { return UGFileType::TAB; }

	//! \brief 是否导入成CAD格式（默认是简单数据集格式）。
	//UGbool IsImportToCAD() const {return m_bImToCAD;}

	//! \brief 设置是否导入成CAD格式（默认是简单数据集格式）。
	//void SetImportToCAD(UGbool toCAD){m_bImToCAD = toCAD;}

	//! \brief 设置风格对照表的路径。
	//! \param [in] 。
	//! \return 风格对照表的路径。
	//! \remarks 不设置或为空程序默认找Bin目录下的MiStyMap.conf。
	//! \attention 。
	UGString GetStyleMapFilePath() {return m_StyleMapFilePath;}

	//! \brief 设置填风格对照表的路径。
	//! \param path [in] 风格对照表的路径。
	//! \return 。
	//! \remarks 不设置或为空程序默认找Bin目录下的MiStyMap.conf。
	//! \attention 。
	void SetStyleMapFilePath(UGString path) {m_StyleMapFilePath = path;}

private:
	//UGbool m_bImToCAD;

	//风格对照表路径
	UGString m_StyleMapFilePath;
};

//! \brief MapInfo(MIF)的导入参数配置。
class FILEPARSER_API UGMifImportParams : public UGVectorImportParams
{	
public:

	//! \brief 构造函数。
	UGMifImportParams(){}

	//! \brief 返回当前格式转换参数类型。
	virtual inline UGint GetFileType() const { return UGFileType::MIF; }

	//! \brief 设置风格对照表的路径。
	//! \param [in] 。
	//! \return 风格对照表的路径。
	//! \remarks 不设置或为空程序默认找Bin目录下的MiStyMap.conf。
	//! \attention 。
	UGString GetStyleMapFilePath() {return m_StyleMapFilePath;}

	//! \brief 设置填风格对照表的路径。
	//! \param path [in] 风格对照表的路径。
	//! \return 。
	//! \remarks 不设置或为空程序默认找Bin目录下的MiStyMap.conf。
	//! \attention 。
	void SetStyleMapFilePath(UGString path) {m_StyleMapFilePath = path;}

private:

	//风格对照表路径
	UGString m_StyleMapFilePath;
};


//! \brief MapInfo(TAB)的导出参数配置。
class FILEPARSER_API UGMitabExportParams : public UGVectorExportParams
{
public:

	//! \brief 构造函数。
	UGMitabExportParams();

	//! \brief 返回当前格式转换参数类型。
	virtual inline UGint GetFileType() const { return UGFileType::TAB; }

	//现在直接按照扩展名来辨别，不用设置参数。下面两个参数取消
	//! \brief 是否导出成mif格式（默认是Mif格式）。
	//UGbool IsExportToMif() const {return m_bExpToMif;}

	//! \brief 设置是否导出成mif格式（默认是Mif格式）。
	//void SetExportToMif(UGbool toMif){m_bExpToMif = toMif;}

private:
	//UGbool m_bExpToMif;
	
};

//! \brief MapInfo(MIF)的导出参数配置。
class FILEPARSER_API UGMifExportParams : public UGVectorExportParams
{
public:

	//! \brief 构造函数。
	UGMifExportParams(){}

	//! \brief 返回当前格式转换参数类型。
	virtual inline UGint GetFileType() const { return UGFileType::MIF; }

private:

};

} //namespace UGC
#endif // !defined(AFX_UG_MITAB_FILEPARSERCONFIGPARAMS_H__INCLUDED_)

