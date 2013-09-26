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

#if !defined(AFX_UG_SDERASTER_FILEPARSERCONFIGPARAMS_H__INCLUDED_)
#define AFX_UG_SDERASTER_FILEPARSERCONFIGPARAMS_H__INCLUDED_

#include "FileParser/UGRasterConfigParams.h"
#include "FileParser/UGExchangeFileType.h"

namespace UGC
{
	//! \brief sde的导入参数配置。
	class FILEPARSER_API UGSdeRasterImportParams:public UGRasterImportParams
	{
	public:
		//! \brief 构造函数。
		UGSdeRasterImportParams(
				const UGString strServer,
				const UGString strDbName,
				const UGString strUser,
				const UGString strPassword,
				const UGString strPort);

		UGSdeRasterImportParams(const UGString strFilePath);

		UGSdeRasterImportParams();

		UGSdeRasterImportParams(const UGSdeRasterImportParams& params);

		virtual ~UGSdeRasterImportParams();
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

		//! \brief 重载获取文件格式类型的函数。
		virtual inline UGint GetFileType() const	{ return UGFileType::SDERaster; }

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
	};
}
#endif