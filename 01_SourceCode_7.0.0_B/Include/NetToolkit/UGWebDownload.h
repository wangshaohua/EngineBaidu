////////////////////////////////////////////////////////////////////////////////
//!  Project UGC
//! \file UGWebDownload.h
//! \author UGC Group
//! \brief 网络数据下载器虚基类，目前实现了libcurl的，将来可以再考虑实现数据流的
//! \attention 目前仅在三维类库中使用过
//!  Copyright (c)copy;  1997-2009 SuperMap Software Co., Ltd.<br> 
//!  All Rights Reserved.
//! \version 6.0
//! \date 2009年8月28日
////////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_UGWEBDOWNLOAD_H__1F98835A_D61F_43AE_A290_E23BB63021D8__INCLUDED_)
#define AFX_UGWEBDOWNLOAD_H__1F98835A_D61F_43AE_A290_E23BB63021D8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Stream/ugexports.h"
#include "Stream/ugdefs.h"
#include "Stream/ugplatform.h"

#include "NetToolkit/UGGeoSpatialDownloadRequest.h"

namespace UGC
{
class UGWebDownloadThread;
class UGMemoryStream;

typedef void (UGSTDCALL * DownloadProgressHandler) (void* pfeedback, UGint completeNum);
typedef void (UGSTDCALL * DownloadCompleteHandler) (void* pfeedback);

//! \brief class UGWebDownload 
//! \brief 网络数据下载器虚基类
class NETTOOLKIT_API UGWebDownload  
{
public:	

	friend class UGDownloadQueue;

	enum UGDownloadType
	{
		Unspecified = -1,
		WMS = 0,
		WFS = 1,
		Custom = 99,
		SMCacheMixedFiles = 1001,
		SMCacheSingleFile = 1002,

		SMZipFiles2SingleFile = 2001,
	};
	
    //! \fn UGWebDownload();

    //! \brief 默认构造函数
	UGWebDownload();

    //! \fn virtual ~UGWebDownload();
    //! \brief 默认析构函数
	virtual ~UGWebDownload();
	
    //! \fn virtual UGbool Download() = 0;
    //! \brief 下载执行，若是异步下载，则在线程中回调
    //! \return 下载完毕返回true 
	// 这个是外部回调函数需要调用，没办法改成public了
	virtual UGbool Download() = 0; 

//	virtual void Release();

    //! \fn virtual void Cancel();
    //! \brief 取消掉正在进行的异步下载
    //! \remarks 释放掉下载线程，将下载队列清空
	virtual void Cancel();

    //! \fn virtual void DownloadSingleInForeground(const UGGeoSpatialDownloadRequest& request);
    //! \brief 运用下载器的实现，同步下载一个指定的请求
    //! \param const UGGeoSpatialDownloadRequest& request [in] 单个下载请求
    //! \remarks 适用于影像，地形，模型缓存文件，索引文件或者配置文件。
	virtual void DownloadSingleInForeground(UGGeoSpatialDownloadRequest& request);

//	UGbool AddRequest(const UGGeoSpatialDownloadRequest& request);

//	UGbool RemoveRequest(const UGGeoSpatialDownloadRequest& request);

    //! \fn void SetFeedBack(void* pfeedback);
    //! \brief 设置
    //! \param void* pfeedback [in]
    //! \remarks void 
	void SetFeedBack(void* pfeedback);

	//! \brief 创建占位符文件
	static void CreatePlaceHolderFile(UGString strDatFilePath);

protected:

    //! \fn void ReleaseWorkThread();
	//! \brief 释放工作线程
	void ReleaseWorkThread();

	// 可将UGDownloadType扩展进去
	//! \fn virtual void BackgroundDownloadFile();
	//! \brief 异步下载
	virtual void BackgroundDownloadFile();
	
// Static proxy properties
// public:
// 	static UGbool ms_bLog404Errors;
// 	
// 	static UGbool ms_buseWindowsDefaultProxy;
// 	
// 	static UGString ms_strproxyUrl;
// 	
// 	static UGbool ms_buseDynamicProxy;
// 	
// 	static UGString ms_strproxyUserName;
// 	
// 	static UGString ms_strproxyPassword;
// 	
// 	static UGString ms_strUserAgent;

public:


//! \brief 下载过程中回调控制进度条进度，目前尚未使用
	DownloadProgressHandler m_pProgressCallback;

//! \brief 下载完成后，回调函数指针
	DownloadCompleteHandler m_pCompleteCallback;

//! \brief 用于判断是否是大文件缓存类型还是普通文件类型，默认是普通文件类型。
	UGDownloadType m_DownloadType;
	
//! \brief 目前尚未用到，预留
	UGString m_strContentType;

//! \brief 下载时访问服务端用到的用户名，默认是空
	UGString m_strUser;

//! \brief 下载时访问服务端用到的密码，默认是空
	UGString m_strPasswd;

	//! \brief 使用大文件缓存时的缓存密码
	UGString m_strCachePassword;

protected:
	
//	UGbool m_IsComplete;	

	// 连续内存，遍历快速，没有复杂的中间插入，删除元素的操作所以用array
	// 当这里的下载每完成一个就可以将进度条前进了
//! \brief 正在进行下载的请求数组
	UGArray<UGGeoSpatialDownloadRequest> m_arrActiveDownloads;

//! \brief 预留，标识已下载数据量
	UGint m_nBytesProcessed;

//! \brief 预留
	UGint m_nContentLength;

//! \brief 预留，是否数据流有压缩
	UGbool m_bCompressed;

//! \brief 预留，数据流压缩编码
	UGString m_strContentEncoding;

//! \brief 预留，异步下载开始时间
	UGlong m_lDownloadStartTime;

//! \brief 预留，处理将内存流数据保存为文件流数据
	UGMemoryStream* m_pContentStream;
	
// 	static DownloadCompleteHandler ms_pDebugCallback;
// 
// 	static DownloadCompleteHandler ms_pDownloadEnded;

//! \brief 预留，是否是下载到内存
	UGbool m_IsMemoryDownload;

//! \brief 标识是否取消或者停止了异步下载
	UGbool m_bstopFlag;

//! \brief 异步下载线程
	UGWebDownloadThread* m_pdlThread;

//! \brief 保留下载器的调用者，作为进度条或者完成后信息的反馈对象
	void* m_pFeedback;

};


}

#endif // !defined(AFX_UGWEBDOWNLOAD_H__1F98835A_D61F_43AE_A290_E23BB63021D8__INCLUDED_)

