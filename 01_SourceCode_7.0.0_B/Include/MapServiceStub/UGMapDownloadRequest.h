////////////////////////////////////////////////////////////////////////////////
//!  Project UGC
//! \file UGMapDownloadThread.h
//! \author 数据转换组
//! \brief 下载线程，从网络上将内容下载到内存中
//! \attention 
//!  Copyright (c)copy;  1997-2009 SuperMap Software Co., Ltd.<br> 
//!  All Rights Reserved.
//! \version 6.0
//! \date 2011年10月18日
////////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_UGMAPDOWNLOADREQUEST_H__4A50E4DC_4371_4DAA_AF32_76DD8B65566E__INCLUDED_)
#define AFX_UGMAPDOWNLOADREQUEST_H__4A50E4DC_4371_4DAA_AF32_76DD8B65566E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Stream/ugexports.h"
#include "Stream/ugdefs.h"
#include "Stream/ugplatform.h"

namespace UGC
{

class MAPSERVICESTUB_API UGMapDownloadRequest
{
public:
	//! \brief 构造
	UGMapDownloadRequest();

	~UGMapDownloadRequest();

	//! \brief 重载 ==
	//! \param const UGMapDownloadRequest& request
	//! \return	 若两个请求相等则返回true
	UGbool operator==(const UGMapDownloadRequest& request) const;

	//! \brief 重载=。
	//! \param &request [in]。
	void operator = (const UGMapDownloadRequest &request);

public:

	//! \brief 请求瓦片的URL地址
	UGString m_strURL;

	//! \brief 请求瓦片的存储路径
	UGString m_strFileName;

	//! \brief 请求瓦片的级别或文件目录
	UGuint m_nScalePath;

	//! \brief 请求瓦片的比例尺
	UGdouble m_dScale;

	//! \brief 请求瓦片的行号
	UGint m_nRow;

	//! \brief 请求瓦片的列号
	UGint m_nCol;
};

}
#endif // !defined(AFX_UGMAPDOWNLOADREQUEST_H__4A50E4DC_4371_4DAA_AF32_76DD8B65566E__INCLUDED_)

