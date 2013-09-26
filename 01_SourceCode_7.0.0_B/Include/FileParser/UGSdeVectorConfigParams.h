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

#if !defined(AFX_UG_SDEVECTOR_FILEPARSERCONFIGPARAMS_H__INCLUDED_)
#define AFX_UG_SDEVECTOR_FILEPARSERCONFIGPARAMS_H__INCLUDED_

#include "FileParser/UGVectorConfigParams.h"
#include "FileParser/UGExchangeFileType.h"

namespace UGC 
{	
//  目前此参数没有使用  内部是判断如果用户填写了文件路径  那就是按文件路径的方式
// 	enum SDEImportMode // 内部是sde的2种打开方式
// 	{
// 		SDE_Parms,  // 通过参数打开
// 		SDE_File,   // 通过文件打开
// 	};
	//! \brief shp的导入参数配置。
	class FILEPARSER_API UGSdeVectorImportParams : public UGVectorImportParams
	{	
	public:
		//! \brief 构造函数。
		UGSdeVectorImportParams(const UGString strServer,
								const UGString strDbName,
								const UGString strUser,
								const UGString strPassword,
								const UGString strPort);

		UGSdeVectorImportParams(const UGString strFilePath);

		UGSdeVectorImportParams();

		//! \brief 析构函数。
		virtual ~UGSdeVectorImportParams();

	public:
		//! \brief 设置服务器名称或Ip。
		void SetServer(const UGString strServer){m_strServer = strServer;}
		
		//! \brief 获取服务器名称或Ip。
		UGString GetServer() const {return m_strServer;}
		
		//! \brief 设置SDE数据库名称。
		void SetDbName(const UGString strDbName){m_strDbName = strDbName;}
		
		//! \brief 获取SDE数据库名称。
		UGString GetDbName() const {return m_strDbName;}
		
		//! \brief 设置SDE数据库用户名。
		void SetUser(const UGString strUser){m_strUser = strUser;}
		
		//! \brief 获取SDE数据库用户名。
		UGString GetUser() const {return m_strUser;}
		
		//! \brief 设置SDE数据库密码。
		void SetPassword(const UGString strPassword){m_strPassword = strPassword;}
		
		//! \brief 获取SDE数据库密码。
		UGString GetPasswrod() const {return m_strPassword;}
        
		//! \brief 获取SDE端口名称。
		//! \param strPortName [in]。
		//! \attention 形式是port:+端口号  默认为port:5151
		void SetPortName(const UGString strPortName){m_strPortName = strPortName;}
		
		//! \brief 获取SDE端口名称。
		UGString GetPortName() const {return m_strPortName;}

// 		//! \brief 设置sde导入的方式。
// 		void SetSDEImportMode(const UGint nImportMode){m_nImportMode = nImportMode;}
// 
// 		//! \brief 获取sde导入的方式。
// 		UGint GetSDEImportMode() const {return m_nImportMode;}
		
		//! \brief 重载获取文件格式类型的函数。
		virtual inline UGint GetFileType() const	{ return UGFileType::SDEVector; }

		//! \brief 判断导入以全图或者多层导入。
		//! \param  [in]。
		//! \return 。
		//! \remarks 。
		//! \attention 。
		virtual UGbool GetImportByLayer() const{return TRUE;}
	protected:
		UGString m_strServer;
		UGString m_strDbName;
		UGString m_strUser;
		UGString m_strPassword;
		UGString m_strPortName;
/*		UGint    m_nImportMode;*/
	};


	//! \brief shp的导出参数配置。
	class FILEPARSER_API UGSdeVectorExportParams : public UGVectorExportParams
	{

	public:
		//! \brief 构造函数。
		UGSdeVectorExportParams();

		//! \brief 析构函数。
		~UGSdeVectorExportParams();

		//! \brief 重载获取文件格式类型的函数。
		virtual inline UGint GetFileType() const	{ return UGFileType::Shape; }

	};

} //namespace UGC
#endif // !defined(AFX_UG_SDEVector_FILEPARSERCONFIGPARAMS_H__INCLUDED_)

