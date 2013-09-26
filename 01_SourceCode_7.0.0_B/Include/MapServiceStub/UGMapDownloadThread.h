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

#if !defined(AFX_UGMAPDOWNLOADTHREAD_H__4A50E4DC_4371_4DAA_AF32_76DD8B65566E__INCLUDED_)
#define AFX_UGMAPDOWNLOADTHREAD_H__4A50E4DC_4371_4DAA_AF32_76DD8B65566E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Toolkit/UGThread.h"
#include "Stream/UGByteArray.h"
#include "MapServiceStub/UGMapDownloadRequest.h"
namespace UGC
{

//! \brief 定义下载完成后的回调函数
typedef void (UGSTDCALL * MapDownloadFunc)(void* , UGuint);

//! \brief 下载线程
class MAPSERVICESTUB_API UGMapDownloadThread : public UGThread  
{
public:

	UGMapDownloadThread(UGuint nGlobalID);

	~UGMapDownloadThread();

	//! \brief 设置下载完成后的回调函数的句柄，用于下载完成后回调，来做后续处理
	//! \param void* pHandeler [in] 函数句柄
	void SetMapDownloadFunc(MapDownloadFunc pFunc);

	//! \brief 设置外部对象的句柄，用于下载完成后回调，来做后续处理
	//! \param void* pHandeler [in] 对象句柄
	void SetHandeler(void* pHandle);

	//! \brief 设置线程的下载任务
	void SetRequest(const UGMapDownloadRequest& pRequest);

	//! \brief 获取线程执行的下载任务
	UGMapDownloadRequest* GetRequest();

	//! \brief 获取线程中使用的curl_easy
	void* GetCurl();

protected:

	//! \brief 重写基类run函数。
	//! \return 线程正常退出返回0，失败则返回-1。
	virtual UGint run();	

private:
	//! \brief 回调函数指针
	MapDownloadFunc m_pRunHandler;

	//! \brief 外部对象句柄
	void* m_pHandler;

	//下载请求
	UGMapDownloadRequest m_mapRequest;

	UGuint m_nGlobalID;

	void* m_curl;
};

}

#endif // !defined(AFX_UGMapDOWNLOADTHREAD_H__4A50E4DC_4371_4DAA_AF32_76DD8B65566E__INCLUDED_)

