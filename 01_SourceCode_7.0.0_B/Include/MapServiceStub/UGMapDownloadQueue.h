////////////////////////////////////////////////////////////////////////////////
//!  Project UGC
//! \file UGMapDownloadQueue.h
//! \author 数组转换组
//! \brief  下载请求队列，内部使用多线程后台批量下载
//! \attention 
//!  Copyright (c)copy;  1997-2009 SuperMap Software Co., Ltd.<br> 
//!  All Rights Reserved.
//! \version 6.0
//! \date 2011年10月18日
/*
用于后台下载网络服务，内部用下载队列和下载线程池实现，现在的要求是下载线程池的大小
不超过10，下载队列的大小不超过200（如果达到200后，用户添加新的请求，添加到尾部，
则去掉头部的请求，如果加到头部，则去掉尾部的请求）。用户继续添加新请求时，如果需要优先下载，
则添加到队列头部，否则添加到队列尾部。如果需要判断是否下载完成，需要在调用BackgroundDownloadFile()
之后进行判断，否则会有未知的错误。目前只有在网络服务管理插件中使用。
*/
////////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_UGMAPDOWNLOADQUEUE_H__60981696_A715_41E9_9E8A_0E555E41284B__INCLUDED_)
#define AFX_UGMAPDOWNLOADQUEUE_H__60981696_A715_41E9_9E8A_0E555E41284B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Stream/ugexports.h"
#include "Stream/ugdefs.h"
#include "Toolkit/UGThread.h"

#include "MapServiceStub/UGMapDownloadThread.h"
#include "FileParser/UGImagePlugin.h"

namespace UGC
{

typedef void (UGSTDCALL * MapDownloadCompleteFunc) (const UGMapDownloadRequest*, const UGByteArray*, UGint, UGlong);

typedef void (UGSTDCALL * RequestFinishedProc) (UGlong pWnd);

class MAPSERVICESTUB_API UGMapDownloadRequests:public UGList<UGMapDownloadRequest>
{
public:

	//! \brief 构造函数
	UGMapDownloadRequests();

	//!  \brief 析构函数
	~UGMapDownloadRequests();

	//! \brief 获取下载任务
	UGbool GetTask(UGMapDownloadRequest& request);

	//! \brief 增加一个任务
	//! \return 如果加入任务，且没有替换原有任务则为True，否则为false
	UGbool AddTask(const UGMapDownloadRequest& newRequest, UGbool bTail);

	//! \brief 删除一个任务
	UGbool RemoveTask(const UGMapDownloadRequest& request);

	//! \brief清空所有任务
	void RemoveAll();

	//! \brief 增加n个资源,在stop的时候用
	void PostTask(UGint nTaskCount);
public:
	//! \brief 下载请求队列最大长度，默认是200
	static UGint ms_nMaxQueueLength;
private:
	//! \brief 只针对请求队列和下载队列的操作枷锁
	UGMutex m_mutex;

	UGSemaphore m_semDownloadTasks;

};

class MAPSERVICESTUB_API UGMapDownloadQueue
{
public:
	//! \brief 构造
	UGMapDownloadQueue();

	//! \brief 析构
	~UGMapDownloadQueue();

	//! \brief 设置瓦片下载完成的回调函数
	//! \param pFunc 回调函数[in]。
	//! \param pWnd 句柄[in]。
	//! \return 。
	//! \remarks 。
	//! \attention 。
	void SetMapDownloadCompleteFunc(MapDownloadCompleteFunc pFunc,UGlong pWnd);

	//! \brief 设置告诉用户所有瓦片下载完成的回调函数
	//! \param pFunc 回调函数[in]。
	//! \param pWnd 句柄[in]。
	void SetRequestFinishedFunc(RequestFinishedProc pFunc,UGlong pWnd);

	//! \brief 获取下载请求队列 供外部调用修改下载请求优先级。
	//! \return 得到下载请求队列
	//UGList<UGMapDownloadRequest>* GetRequests();

	//! \brief 加锁，对下载请求队列进行操作时必须加锁。
	void Lock();

	//! \brief 解锁。
	void Unlock();

	//! \brief 设置最大的下载线程数。
	//! \param nMaxThreadCount[in] 最大不能超过10，超过10，设置成10
	void SetMaxThreadCount(UGint nMaxThreadCount);

	//! \brief 即时清空下载器的活动下载队列，并将下载器的活动线程释放掉，不再进行下载。
	void Stop();

	//! \brief 将下载请求加载到下载队列中
	//! \param const UGMapDownloadRequest& newRequest [in] 下载请求对象
	//! \param UGbool bTail [in] 是否加到队列的末尾，默认为true
	//! \remarks 若该下载请求已经存在于队列中或者下载器的队列中则不再进行加载，
	//! 若下载请求队列已经满员，则丢掉该请求，不再加入。
	//! \return 成功加入返回true。
	UGbool Add(const UGMapDownloadRequest& newRequest, UGbool bTail = TRUE);

	//! \brief 将指定请求对象从下载请求队列中移除。
	//! \param mapRequest [in] 指定的请求对象
	//! \remarks 若下载请求队列不为空且指定请求对象存在于队列中，则可以进行移除。 
	//! \return 移除成功返回true。 
	UGbool Remove( const UGMapDownloadRequest& mapRequest);

	//! \brief 清除下载请求队列。
	void RemoveAll( );

	//! \brief 调用下载器进行后台多线程下载。
	//! \remarks 若请求队列不为空，且下载器已经完成下载则将请求队列中的请求放入下载器进行多线程下载。
	void BackgroundDownloadFile();

	//! \brief 下载完成时回调
	//! \remarks 当下载线程中有下载完成时会调用这个函数。
	void OnComplete(UGuint threadID);

	//! \brief 供外部调用判断是否所有下载完成。
	//! \return 返回下载线程是否完成
	UGbool IsComplete();

protected:
	//! \brief 发送瓦片下载完成消息
	void SendMapDownloadCompleteFunc(const UGMapDownloadRequest* CompleteRequest, const UGByteArray* pByteArrayData, const UGint& eErrorType);

	//! \brief 发送所有瓦片下载完成消息
	void SendRequestFinishedFunc();

	//! \brief 释放线程池中所有的线程
	//! \attention 正在下载的线程会取消下载。
	void ReleaseWorkThread();

	//! \brief 释放线程池中完成下载的线程
	//! \attention 没有完成的线程会等待完成。
	void ReleaseCompleteThread();

protected:

	//! \brief 下载队列中有下载线程完成时，调用的回调函数
	MapDownloadCompleteFunc m_pMapDownloadCompleteHandler;

	//! \brief 事件相关变量。
	UGlong m_pEventView;

	//! \brief 全部瓦片下载完成时，调用的回调函数
	RequestFinishedProc m_RequestFinishHandler;

	//! \brief 全部瓦片下载完成事件相关变量。
	UGlong  m_RequestFinishEnv;

	// 由于一些插入，删除，添加操作发生在这个成员上，所以用list比用array好些
	//! \brief 下载请求队列
	UGMapDownloadRequests m_mapRequests;

	//! \brief 只针对请求队列和下载队列的操作枷锁
	UGMutex m_mutex;

	//! \brief 已完成的下载请求
	UGint m_nCompleteRequest;

	//! \brief 总共的下载请求
	UGint m_nTotalRequest;

	//! \brief 下载时启动的最大线程数
	UGint m_nMaxThreadCount;

	//! \brief 异步下载线程池
	UGArray<UGMapDownloadThread*> m_pdlThreadPool;

	UGbool m_bComplete;

};
}
#endif // !defined(AFX_UGMAPDOWNLOADQUEUE_H__60981696_A715_41E9_9E8A_0E555E41284B__INCLUDED_)
