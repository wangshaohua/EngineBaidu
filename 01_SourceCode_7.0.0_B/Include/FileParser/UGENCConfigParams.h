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
//!  \author zhongdz
//!  \attention 
//!   Copyright (c) 1996-2008 SuperMap Software Limited Company.  <br> 
//!   All Rights Reserved.
//!  \version 6.0
//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_UG_ENC_FILEPARSERCONFIGPARAMS_H__INCLUDED_)
#define AFX_UG_ENC_FILEPARSERCONFIGPARAMS_H__INCLUDED_

#include "FileParser/UGVectorConfigParams.h"
#include "FileParser/UGExchangeFileType.h"

namespace UGC {




//! \brief ENC(电子海图)的导入参数配置。
//! \remarks 备注信息。
class FILEPARSER_API UGENCImportParams : public UGVectorImportParams
{	
public:
	//! \brief 构造函数。
	//! \param 。
	UGENCImportParams();

public:
	enum emOptions
	{
		UPDATES					 = 0x01,
		//LNAM_REFS                = 0x02, // 不开放控制
		//SPLIT_MULTIPOINT         = 0x04, // 不开放控制
		//ADD_SOUNDG_DEPTH         = 0x08, // 不开放控制
		//PRESERVE_EMPTY_NUMBERS   = 0x10, // 不开放控制
		//RETURN_PRIMITIVES        = 0x20,
		//RETURN_LINKAGES          = 0x40, // 不开放控制
		//RETURN_DSID              = 0x80,
	};

	//! \brief 返回当前格式转换参数类型。
	//! \param  [in]。
	//! \return 。
	//! \remarks 。
	//! \attention 。
	virtual inline UGint GetFileType() const { return UGFileType::ENC; }

	//! \brief 得到是否导入更新数据
	//! \return TRUE 导入更新
	//! \return FALSE 不导入更新
	UGbool GetImportUpdate()
	{
		return ( (m_nOption & UPDATES ) != 0 );
	}
	
	//! \brief 设置是否导入更新数据
	//! \param [in] 是否导入更新数据
	void SetImportUpdate(UGbool bUpdate = TRUE)
	{
		if(bUpdate)
			m_nOption |= UPDATES;
		else 
			m_nOption &= ~UPDATES;
	}

// 	//! \brief 得到是否添加一个记录深度的字段
// 	//! \return TRUE 添加字段
// 	//! \return FALSE 不添加字段
// 	UGbool GetAddSoundDepth()
// 	{
// 		return ( (m_nOption & ADD_SOUNDG_DEPTH ) != 0 );
// 	}
// 	
// 	//! \brief 设置是否添加一个记录深度的字段
// 	//! \param [in] 是否添加字段
// 	void SetAddSoundDepth(UGbool bAdd)
// 	{
// 		if(bAdd)
// 			m_nOption |= ADD_SOUNDG_DEPTH;
// 		else 
// 			m_nOption &= ~ADD_SOUNDG_DEPTH;
// 	}

// 	//! \brief 得到是否保留空字段
// 	//! \return TRUE 保留
// 	//! \return FALSE 不保留
// 	UGbool GetPreserveEmptyNumbers()
// 	{
// 		return ( (m_nOption & PRESERVE_EMPTY_NUMBERS ) != 0 );
// 	}
// 	
// 	//! \brief 设置是否保留空字段
// 	//! \param [in] 是否保留
// 	void SetPreserveEmptyNumbers(UGbool bPreserve)
// 	{
// 		if(bPreserve)
// 			m_nOption |= PRESERVE_EMPTY_NUMBERS;
// 		else
// 			m_nOption &= ~PRESERVE_EMPTY_NUMBERS;
// 	}

// 	//! \brief 得到是否导入空间物标数据
// 	//! \return TRUE 导入
// 	//! \return FALSE 不导入
// 	UGbool GetReturnPrimitives()
// 	{
// 		return ( (m_nOption & RETURN_PRIMITIVES ) != 0 );
// 	}
// 	
// 	//! \brief 设置是否导入空间物标数据
// 	//! \param [in] 是否导入
// 	void SetReturnPrimitives(UGbool bReturn)
// 	{
// 		if( bReturn )
// 			m_nOption |= RETURN_PRIMITIVES;
// 		else
// 			m_nOption &= ~RETURN_PRIMITIVES;
// 	}

// 	//! \brief 得到是否导入数据集基本信息（数据集是S57的概念，一般指的是一个文件）
// 	//! \return TRUE 导入
// 	//! \return FALSE 不导入
// 	UGbool GetReturnDSID()
// 	{
// 		return ( (m_nOption & RETURN_DSID ) != 0 );
// 	}
// 	
// 	//! \brief 设置是否导入数据集基本信息
// 	//! \param [in] 是否导入
// 	void SetReturnDSID(UGbool bReturn = TRUE )
// 	{
// 		if( bReturn )
// 			m_nOption |= RETURN_DSID;
// 		else 
// 			m_nOption &= RETURN_DSID;
// 	}

	//! \brief 获取目录表存放的路径
	virtual const UGString& GetCatoFileDir() const { return m_CatoFileDir ;}

	//! \brief 获取目录表存放的路径
	virtual void SetCatoFileDir(const UGString &strDir )
	{ 
		m_CatoFileDir =  strDir;
	}

// 	//! \biref 获取是否使用本地化的数据集名称
// 	UGbool IsUseNativeDatasetName() const{ return m_bUseNativeDatasetName; }
// 	//! \biref 设置使用本地化的数据集名称
// 	void UseNativeDatasetName(UGbool bNativeDatasetName)
// 	{
// 		m_bUseNativeDatasetName = bNativeDatasetName;
// 	}

	UGbool IsConvertToMercatorProjection() const;
	void ConvertToMercatorProjection(UGbool bMercator);

private:
	//! \brief 目录表存放的目录
	UGString m_CatoFileDir; //物标目录表
	//! \brief 
	UGuint m_nOption;

	//! \brief 是否使用本地语言的数据集名称
	//! \remarks S57导入使用
	// UGbool m_bUseNativeDatasetName;
	//! \brief DSNM值对应的一个标识码
	//! \remarks S57使用
	UGushort m_nDSNMCode;
	//! 是否在导入时将数据转换成墨卡托投影。
	UGbool m_bConvertToMercator;
};


//! \brief ENC(电子海图)的导出参数配置。
//! \remarks 备注信息。
class FILEPARSER_API UGENCExportParams : public UGVectorExportParams
{
public:

	//! \brief 构造函数。
	//! \param 。
	UGENCExportParams();

	//! \brief 返回当前格式转换参数类型。
	//! \param  [in]。
	//! \return 。
	//! \remarks 。
	//! \attention 。
	virtual inline UGint GetFileType() const { return UGFileType::ENC; }

	//! \brief 获取目录表存放的路径
	virtual const UGString& GetCatoFileDir() const { return m_CatoFileDir ;}

	//! \brief 获取目录表存放的路径
	virtual void SetCatoFileDir(const UGString &strDir )
	{ 
		m_CatoFileDir =  strDir;
	}

	//! \brief
	virtual void SetDtNameToBeExported(const UGString& name);

	//! \brief 获取要导出的矢量数据集名称数组。
	//! \param  [in]。
	//! \return 。
	//! \remarks 数据集名称数组。
	//! \attention 为了多个数据集导出使用。
	virtual UGbool GetDtNamesBeExported(UGStrings& arrNames) const ;

	//! \brief 设置要导出的矢量数据集名称数组。
	//! \param  name [in] 设置的名称。
	//! \return 。
	//! \remarks 。
	//! \attention 为了多个数据集导出使用。
	virtual void SetDtNamesBeExported(const UGStrings& arrNames);

private:
	//! \brief 要导出的数据集名称数组
	UGStrings m_arrNames;

	//! \brief 目录表存放的目录
	UGString m_CatoFileDir; //物标目录表
	
};

} //namespace UGC
#endif // !defined(AFX_UG_MITAB_FILEPARSERCONFIGPARAMS_H__INCLUDED_)

