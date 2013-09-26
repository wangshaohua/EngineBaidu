//////////////////////////////////////////////////////////////////////////
//                    _   _   ____   ____                    
//   Project         | | | | / ___) / ___)                   
//                   | | | || | __ | |                       
//                   | |_| || |_\ || \___                    
//                    \____/ \____| \ ___)     6.0           
//                                                           
//!  \file headerfile.h
//!  \brief Class 。
//!  \details 。
//!  \author 数据转换组。
//!  \attention 
//!   Copyright (c) 1996-2010 SuperMap Software Limited Company.  <br> 
//!   All Rights Reserved.
//!  \version 6.0

#if !defined(AFX_UGDATASETVECTORWEB_H__7681AA6D_BDCB_4A18_A9A3_EC39CEBB7BE4__INCLUDED_)
#define AFX_UGDATASETVECTORWEB_H__7681AA6D_BDCB_4A18_A9A3_EC39CEBB7BE4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Engine/UGDatasetVector.h"
namespace UGC
{
	class UGDownloadTileInfo;

	typedef void (UGSTDCALL * DownloadResponseFunc) (UGDownloadTileInfo result, UGlong pWnd);

	class ENGINE_API UGDatasetVectorWeb : public UGDatasetVector  
	{
	public:
		UGDatasetVectorWeb();
		virtual ~UGDatasetVectorWeb();

	public:

		//! \brief 打开数据集
		virtual UGbool Open() = 0;

		//! \brief 关闭数据集
		virtual void Close() = 0;	

		//! \brief 判断是否是网络栅格数据集
		virtual UGbool IsWebVector();

		//!	\brief	设置缓存文件的位置
		virtual UGbool SetBufferPath(const UGString& strBuffPath);

		//! \brief 获取缓存文件的位置
		virtual UGString GetBufferPath() const;	

		//! \brief 设置回调函数
		virtual void SetDownloadResponseFunc(DownloadResponseFunc pFunc, UGlong pWnd) = 0;

		//! \brief 判断一次请求是否已经完成，Request之后调用
		//! \return 完成返回True，否则返回False
		virtual UGbool IsComplete() = 0;

		//! \brief 请求下载瓦片块
		//! \brief 设置请求参数
		//! \dScale param[in] 当前地图的比例尺
		//! \bound param[in] 当前地图范围
		//! \bCallBack 本地瓦片存在时是否回调
		virtual UGbool Request(const UGdouble& dScale, const UGRect2D& bound, UGbool bCallBack = TRUE) = 0;

	private:
		//! \brief 缓存文件的位置
		UGString m_strBufferPath;
	};

}

#endif // !defined(AFX_UGDATASETRASTERWEB_H__7681AA6D_BDCB_4A18_A9A3_EC39CEBB7BE4__INCLUDED_)