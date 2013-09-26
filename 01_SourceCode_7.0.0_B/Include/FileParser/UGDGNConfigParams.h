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

#ifndef  __UGDGNIMPORTPARAMS_H__
#define  __UGDGNIMPORTPARAMS_H__

#include "FileParser/UGVectorConfigParams.h"
#include "FileParser/UGExchangeFileType.h"

namespace UGC
{
	//                         导入
	//----------------------------------------------------------------------->
	//! \brief DGN导入参数配置
	class FILEPARSER_API UGDGNImportParams : public UGVectorImportParams
	{
	public:
		//! \brief 构造函数。
		//! \remarks 。
		UGDGNImportParams();

		//! \brief 析构函数。
		//! \remarks 。
		virtual ~UGDGNImportParams();

	public:
		//! \brief 重载获取文件格式类型的函数。
		//! \param  [in]。
		//! \return 。
		//! \remarks 。
		//! \attention 。
		virtual inline UGint GetFileType()const {return UGFileType::DGN;}

		//! \brief 以CAD模式导入时，设置是否以原始CAD分层结构导入
		//! \param  [in]。
		//! \return 。
		//! \remarks 。
		//! \attention 。
		virtual void SetImportByLayer(UGbool bByLayer = FALSE);

		//! \brief 判断CAD导入以全图或者多层导入。
		//! \param  [in]。
		//! \return 。
		//! \remarks 。
		//! \attention 。
		virtual UGbool GetImportByLayer() const;

		//! \brief 设置是否将Cell对象仅导入其Cell hearder（以点的形式）,和CAD中的块对象相对应。
		//! \param bResolve [in]。
		//! \return 。
		//! \remarks 设置为TRUE时，Cell对象几何信息忽略，Cell对象值导入Cell header以点的形式显示       
		//! \attention 。
		virtual void SetCellAsPoint(UGbool bAsPoint = FALSE);

		//! \brief 获取是否将Cell对象仅导入其Cell hearder（以点的形式）。
		//! \param  [in]。
		//! \return 。
		//! \remarks 。
		//! \attention 。
		virtual UGbool GetCellAsPoint()const ;

		//! \brief 设置是否忽略Polyline、LWPline的宽度、凸度信息
		//! \param bResolve [in]。
		//! \return 。
		//! \remarks 设置为TRUE时，多段线的“凸度”、“宽度”信息丢失，仅保留“中心线”。
		//! \attention 。
		void SetIgnoreLwplineWidth(UGbool bIgnore = FALSE);

		//! \brief 得到是否忽略Polyline、LWPline的宽度、凸度信息
		//! \param bResolve [in]。
		//! \return 。
		//! \remarks 
		//! \attention 。
		UGbool GetIgnoreLwplineWidth() const;

		//! \brief 设置风格对照路径。
		//! \param  [in]。
		//! \return 。
		//! \remarks 。
		//! \attention 。
		void SetStyleMapFilePath(const UGString& strPath);
		
		//! \brief 获取风格对照路径。
		//! \param  [in]。
		//! \return 。
		//! \remarks 。
		//! \attention 。
		UGString GetStyleMapFilePath() const;
		
	protected:
		//! \brief 标识CAD数据以全图导入换是多层导入。
		//! \remarks m_bMLayerImport = FALSE,全图导入
		UGbool m_bMLayerImport;

		//! \brief Cell对象是否导入为点（Cell header）设置
		UGbool m_bAsPoint;
        
		//! \brief 风格对照表文件路径
		UGString m_strStyleMapPath;

		//! \brief 忽略优化多段线的线宽。
		//! \remarks 。
		UGbool m_bIgnoreLwplineWidth;
	};

	//                                导出
	//----------------------------------------------------------------->
	class FILEPARSER_API UGDGNExportParams : public UGVectorExportParams
	{
		//! \brief DGN 版本。
		//! \remarks 。
		enum EmVersion
		{
			DGNV7 = 0, //DGN v7版本
			DGNV8 = 1  //DGN v8版本
		};

	public:
		//! \brief 构造函数。
		//! \remarks 。
		UGDGNExportParams();

		//! \brief 析构函数。
		//! \remarks 。
		virtual ~UGDGNExportParams();
	public:
		//! \brief 重载获取文件格式类型的函数。
		//! \param  [in]。
		//! \return 。
		//! \remarks 。
		//! \attention 。
		virtual  UGint GetFileType() const { return UGFileType::DGN; }

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
		//! \brief GML版本设置,默认为GMLSF
		//! 默认为v8版本 
		UGint m_nVersion;
	};
}
#endif