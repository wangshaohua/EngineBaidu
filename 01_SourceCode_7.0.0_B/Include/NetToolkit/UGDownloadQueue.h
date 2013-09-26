////////////////////////////////////////////////////////////////////////////////
//!  Project UGC
//! \file UGDownloadQueue.h
//! \author UGC Group
//! \brief  下载请求队列，内部调用下载器完成下载，用于多线程后台批量下载请求或者前台下载单个请求
//! \attention 目前仅在三维类库中使用过
//!  Copyright (c)copy;  1997-2009 SuperMap Software Co., Ltd.<br> 
//!  All Rights Reserved.
//! \version 6.0
//! \date 2009年8月28日
////////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_UGDOWNLOADQUEUE_H__60981696_A715_41E9_9E8A_0E555E41284B__INCLUDED_)
#define AFX_UGDOWNLOADQUEUE_H__60981696_A715_41E9_9E8A_0E555E41284B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Stream/ugexports.h"
#include "Stream/ugdefs.h"
#include "Toolkit/UGThread.h"

#include "NetToolkit/UGGeoSpatialDownloadRequest.h"

namespace UGC
{
	class UGCacheFile;
	class UGWebDownload;

	typedef void (UGSTDCALL * DownloadQueueCompleteFunc) (UGArray<UGGeoSpatialDownloadRequest> CompleteDownloads, UGlong pWnd);

	//! \brief class UGDownloadQueue
	//! \brief 下载队列
class NETTOOLKIT_API UGDownloadQueue  
{
public:

    //! \fn UGDownloadQueue();

    //! \brief 构造函数
	UGDownloadQueue();

	//! \fn virtual ~UGDownloadQueue();

    //! \brief 析构函数
	virtual ~UGDownloadQueue();

    //! \fn		void Clear();

    //! \brief 即时清空下载器的活动下载队列，并将下载器的活动线程释放掉，不再进行下载。
	void Stop();

    //! \fn UGbool Add(const UGGeoSpatialDownloadRequest& newRequest, UGbool bTail = TRUE);

    //! \brief 将下载请求加载到下载队列中
    //! \param const UGGeoSpatialDownloadRequest& newRequest [in] 下载请求对象
    //! \param UGCacheFile* pCacheFile [in] 如果是大文件格式，则用于判断在大文件中是否存在
    //! \param const UGString& strpath [in]
    //! \param UGbool bTail [in] 是否加到队列的末尾，默认为true
	//! \remarks 若该下载请求已经存在于队列中或者下载器的队列中则不再进行加载，
	//! 若下载请求队列已经满员，则丢掉该请求，不再加入。
    //! \return 成功加入返回true。
	UGbool Add(const UGGeoSpatialDownloadRequest& newRequest, UGCacheFile* pCacheFile = NULL, const UGString& strpath = _U(""), UGbool bTail = TRUE);

    //! \fn UGbool Remove( const UGGeoSpatialDownloadRequest& geoRequest);

    //! \brief 将指定请求对象从下载请求队列中移除。
    //! \param const UGGeoSpatialDownloadRequest& geoRequest [in] 指定的请求对象
    //! \remarks 若下载请求队列不为空且指定请求对象存在于队列中，则可以进行移除。 
    //! \return 移除成功返回true。 
	UGbool Remove( const UGGeoSpatialDownloadRequest& geoRequest);

    //! \fn void OnComplete();

    //! \brief 下载器下载线程完成后会进行回调。
    //! \remarks 可以在此函数中完成下载线程结束后的收尾工作或者其他上层消息回调函数。 
	void OnComplete();

	//! \fn void OnProgress();

	//! \brief 下载器下载过程中记录下载进度。 
	void OnProgress(UGint completeNum);

    //! \fn void BackgroundDownloadFile();

    //! \brief 调用下载器进行后台多线程下载。
    //! \remarks 若请求队列不为空，且下载器已经完成下载则将请求队列中的请求放入下载器进行多线程下载。
	void BackgroundDownloadFile();

    //! \fn void DownloadQueueInForeground();

    //! \brief 调用下载器进行前台下载。
    //! \remarks 内部不启用多线程，尚不支持与后台下载同时使用，暂不开放。
//	void DownloadQueueInForeground();


    //! \fn void DownloadFileInForeground(const UGGeoSpatialDownloadRequest& request);

    //! \brief 调用下载器进行前台下载
    //! \param const UGGeoSpatialDownloadRequest& request [in] 要进行前台下载的请求对象
    //! \remarks 内部不启用多线程，下载器去下载单个请求对象 
	void DownloadFileInForeground(UGGeoSpatialDownloadRequest& request);


    //! \fn void SetWebDownloader(UGWebDownload* pwd);

    //! \brief 下载器绑定。
    //! \param UGWebDownload* pwd [in] 外部new出来的下载器
    //! \remarks 目标支持运行时绑定，可以在运行时绑定上不同的下载器 
    //! \return void 
	void SetWebDownloader(UGWebDownload* pwd);
	

    //! \fn void SetSmCacheAccessPW(const UGString& strpw);
    //! \brief 设置下载器中访问大文件缓存时的缓存密码
    //! \param const UGString& strpw 缓存密码
    //! \return void 
	void SetSmCacheAccessPW(const UGString& strpw);

	void SetDownloadType(UGint type);

    //! \fn UGbool IsComplete() {return m_bIsComplete;};

    //! \brief 供外部调用判断内部下载线程是否下载完成。
    //! \return 返回下载线程是否完成
	UGbool IsComplete() {return m_bIsComplete;};

	//! \brief 供外部调用得到下载进度。
	//! \return 得到已完成的请求个数和下载请求个数
	void GetProgress(UGint& completeRequestNum, UGint& totalRequestNum);

	//! \brief 供外部调用得到下载进度。
	//UGfloat GetDataStreamingProgress();

	//! \brief 设置下载完成的回调函数
	//! \param pFunc 回调函数[in]。
	//! \param pWnd 句柄[in]。
	//! \return 。
	//! \remarks 。
	//! \attention 。
	void SetDownloadQueueCompleteFunc(DownloadQueueCompleteFunc pFunc,UGlong pWnd);

	//! \brief 获取下载请求队列 供外部调用修改下载请求优先级。
	//! \return 得到下载请求队列
	UGList<UGGeoSpatialDownloadRequest>* GetRequests();

	//! \brief 加锁，对下载请求队列进行操作时必须加锁。
	void Lock();

	//! \brief 解锁。
	void Unlock();

	//! \brief 设置每次下载的请求个数。
	void SetTurnRequestNum(UGint turnRequestNum);

public:

//! \brief 下载请求队列最大长度，默认是200
	static UGint ms_nMaxQueueLength;

//! \brief 预留
//	static UGint ms_nMaxConcurrentDownloads;

protected:

	//! \brief 重载函数用于下载完成的回调。
	//! \param 无效参数纯粹为了函数重载
	void BackgroundDownloadFile(char invalid);

    //! \fn virtual void ServiceDownloadQueue();
    //! \brief 预留
//	virtual void ServiceDownloadQueue();

	//! \brief 发送下载完成消息
	//! \return 。
	//! \remarks 。
	//! \attention 。
	void SendDownloadQueueCompleteFunc(const UGArray<UGGeoSpatialDownloadRequest>& CompleteDownloads);

protected:

	//! \brief 下载队列完成时也是所有下载完成时的回调函数
	DownloadQueueCompleteFunc m_pDownloadQueueCompleteHandler;

	//! \brief 事件相关变量。
	UGlong m_pEventView;  //调用事件回调函数的对象指针，统一为一个吧，节省内存

	// 由于一些插入，删除，添加操作发生在这个成员上，所以用list比用array好些
	//! \brief 下载请求队列
	UGList<UGGeoSpatialDownloadRequest> m_Requests;

//! \brief 内部下载器，必须有，否则无法进行下载。
	UGWebDownload* m_pWebDownload;

//! \brief 只针对请求队列和下载队列的操作枷锁
	UGMutex m_mutex;

//! \brief 若下载线程已经完成一批量的下载，则置为true
	UGbool m_bIsComplete;

//! \brief 已完成的下载请求
	UGint m_nCompleteRequest;

//! \brief 总共的下载请求
	UGint m_nTotalRequest;
	
	//! \brief 阶段完成的下载请求
	UGint m_nStageCompleteRequest;

	//! \brief 每次从从队列里拿到下载器中下载的个数
	UGint m_nTurnRequest;

};

}
#endif // !defined(AFX_UGDOWNLOADQUEUE_H__60981696_A715_41E9_9E8A_0E555E41284B__INCLUDED_)

