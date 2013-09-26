////////////////////////////////////////////////////////////////////////////////
//!  Project UGC
//! \file UGWebDownloadCurl.h
//! \author UGC Group
//! \brief 依赖libCurl实现的网络下载器
//! \attention 目前仅在三维类库中使用过
//!  Copyright (c)copy;  1997-2009 SuperMap Software Co., Ltd.<br> 
//!  All Rights Reserved.
//! \version 6.0
//! \date 2009年8月28日
////////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_UGWEBDOWNLOADCURL_H__12D804A9_E79A_4E43_A93B_5FF0B6D39920__INCLUDED_)
#define AFX_UGWEBDOWNLOADCURL_H__12D804A9_E79A_4E43_A93B_5FF0B6D39920__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "NetToolkit/UGWebDownload.h"
namespace UGC
{
	//class UGWebDownloadCurl
	//! \brief 依赖libCurl实现的网络下载器
class NETTOOLKIT_API UGWebDownloadCurl : public UGWebDownload  
{
public:

    //! \fn UGWebDownloadCurl();
    //! \brief 默认构造函数
	UGWebDownloadCurl();
	
    //! \fn virtual ~UGWebDownloadCurl();
    //! \brief 默认析构函数
	virtual ~UGWebDownloadCurl();


    //! \fn virtual UGbool Download();
	//! \brief 下载执行，若是异步下载，则在线程中回调
	//! \remarks 如果下载失败则创建dat占位符，依赖libcurl实现下载，下载成功直接在文件全路径下生成文件
	//! \return 下载完毕返回true 
	virtual UGbool Download();

    //! \fn virtual void Cancel();
	//! \brief 取消掉正在进行的异步下载
	//! \remarks 释放掉下载线程，将下载队列清空
	virtual void Cancel();

    //! \fn virtual void DownloadSingleInForeground(const UGGeoSpatialDownloadRequest& request);
	//! \brief 同步下载一个指定的请求
	//! \param const UGGeoSpatialDownloadRequest& request [in] 单个下载请求
	//! \remarks 适用于影像，地形，模型缓存文件，索引文件或者配置文件。
	virtual void DownloadSingleInForeground(UGGeoSpatialDownloadRequest& request);

// 	virtual void BackgroundDownloadFile( DownloadCompleteHandler completeCallback );
// 
// 	virtual void BackgroundDownloadFile( UGDownloadType dlType );

// 	void BackgroundDownloadMemory();
// 
// 	void BackgroundDownloadMemory( DownloadCompleteHandler completeCallback );
// 
// 	void BackgroundDownloadMemory( UGDownloadType dlType );
// 
// 	void DownloadMemory();
// 
// 	void DownloadMemory( UGDownloadType dlType );
// 
// 	void DownloadMemory( DownloadProgressHandler progressCallback );

//	void SaveMemoryDownloadToFile(UGString destinationFilePath );
	
	//! \fn void void OnProgressCallback(UGint completeNum);
	//! \brief 用于回调显示下载进度
	//! \param UGint completeNum [in] 已经完成的下载数据量
	void OnProgressCallback(UGint completeNum);
    
	//! \fn void OnCompleteCallback();
    //! \brief 用于回调从下载队列向下载器中添加新的请求
	void OnCompleteCallback();

protected:
	//! \fn virtual void BackgroundDownloadFile();
	//! \brief 异步下载HTTP协议的文件
	//! \remarks 如果没有异步下载线程则内部创建
	virtual void BackgroundDownloadFile();

private:

    //! \fn void HttpHelperPerform();
    //! \brief 开始下载单个文件，内部会对zip文件进行解压。
	void HttpHelperPerform(UGGeoSpatialDownloadRequest& request);

	//! \fn void DownloadIntoSmCahe();
	//! \brief 下载成为混合文件缓存。
	void DownloadIntoMixedFiles();

	//! \fn void DownloadIntoSmCahe();
	//! \brief 下载成为单文件缓存。
	void DownloadIntoSingleFile();

	//! \brief 下载成为普通文件。
	void DownloadIntoPureFiles();

	//! \brief 打包下载成为单文件缓存。
	void DownloadIntoZipFiles();

// 	static void OnDownloadEnded(UGWebDownload* pwd, void* pCaller);

};

}

#endif // !defined(AFX_UGWEBDOWNLOADCURL_H__12D804A9_E79A_4E43_A93B_5FF0B6D39920__INCLUDED_)

