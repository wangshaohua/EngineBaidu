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
/*
所有网络服务管理插件的基类，内部采用下载队列实现多线程异步下载，下载之前用户需要
设置回调函数和本地缓存管理器，用户调用Request添加新的请求，再次调用Request会将新
请求加到下载队列头部，优先下载，原有的下载优先级降低。调用Stop停止所有的下载并清空
下载队列。
*/
//////////////////////////////////////////////////////////////////////////


#if !defined(AFX_UGMAPSERVICESTUB_H__F2ACB033_F582_4263_B9E9_DCA2E56F87DE__INCLUDED_)
#define AFX_UGMAPSERVICESTUB_H__F2ACB033_F582_4263_B9E9_DCA2E56F87DE__INCLUDED_

#include "MapServiceStub/UGMapServiceParams.h"
#include "MapServiceStub/UGLocalCacheManager.h"
#include "Stream/ugplatform.h"
#include "NetToolkit/UGDownloadQueue.h"
#include "MapServiceStub/UGMapDownloadQueue.h"
#include "CacheFile/UGAbstractCacheFile.h"

namespace UGC 
{

// typedef void (UGSTDCALL * DownloadResponseFunc) (UGDownloadTileInfo result, UGlong pWnd);

// typedef void (UGSTDCALL * DataChangedProc) (const UGDataChangeInfo& ChangeInfo, UGlong pWnd);

//! \brief 服务请求基类。
//! \remarks 所有有关服务请求的都要继承此类。
class MAPSERVICESTUB_API UGMapServiceStub 
{
public:
	//! \brief 构造函数。
	UGMapServiceStub();

	//! \brief 析构函数。
	virtual ~UGMapServiceStub();
	
public:

	//! \brief 设置本地缓存管理器。
	//! \param pLocalCacheManager [in]。
	//! \attention 打开服务之前必须设置本地缓存管理器
	UGbool SetLocalCacheManager(UGLocalCacheManager *pLocalCacheManager);

	//! \brief 获取本地缓存管理器。
	//! \param pLocalCacheManager [in]。
	//! \attention 打开服务之前必须设置本地缓存管理器
	UGLocalCacheManager* GetLocalCacheManager();

	//! \brief 打开服务。
	//! \param impParams [in]。
	//! \return 成功返回TRUE，失败返回FALSE。
	//! \attention 下载服务前调用。
	virtual UGbool Open(const UGMapServiceParams* pMapServiceParams, UGbool bReSave = TRUE) = 0;

	//! \brief 下载请求。
	//! \param dScale [in] 比例尺。
	//! \param bound [in] 范围。
	//! \param nSec [in] 下载超时时间，默认30秒
	//! \attention 通过bound请求，不提供回调，只使用多线程，只有全部下完或超时才返回主线程
	virtual UGbool Request(const UGdouble& dScale, const UGRect2D& bound, UGbool bCallBack = TRUE, const UGint& nSec = 0);
	
	//! \brief 关闭服务	
	virtual void Close();

	//! \brief 设置ClientID，暂时只有GoogleMaps使用
	virtual void SetUser(const UGString& strUser){}

	//! \brief 设置签名，暂时只有GoogleMaps使用
	virtual void SetPassword(const UGString& strPassword){}

	//! \brief 即时清空下载器的活动下载队列，并将下载器的活动线程释放掉，不再进行下载。
	void Stop();

	//! \brief 设置下载完成的回调函数
	//! \param pFunc 回调函数[in]。
	//! \param pWnd 句柄[in]。
	void SetDownloadResponseFunc(DownloadResponseFunc pFunc,UGlong pWnd);

	//! \brief 是否下载完成
	//! \return 所有请求全部下载完成，则返回true，否则返回false。
	UGbool IsComplete(){return (m_bLastTileRequest && m_DownloadQueue.IsComplete());}

	//! \brief 设置下载时启用的最大线程个数，最大不能超过10
	void SetThreadCount(UGint nThreadCount){m_DownloadQueue.SetMaxThreadCount(nThreadCount);}

	//! \brief 下载请求（超图云服务）。
	//! \param dScale [in] 比例尺。
	//! \param bound [in] 范围。
	//! \attention 调用后开启后台线程下载，以回调的方式范围下载信息。
	virtual UGbool Request(const UGuint& nScalePath, const TileArea& tileArea);

	//! \brief 发送下载完成消息
	//! \return 。
	//! \remarks 。
	//! \attention 。
	void SendDownloadResponseFunc(const UGDownloadTileInfo& tileDownloadInfo);

	//! \brief 设置取到数据并把数据区域的外接矩形返回给用户的回调函数
	//! \param pFunc 回调函数[in]。
	//! \param pWnd 句柄[in]。
	void SetDataChangedFunc(DataChangedProc pFunc,UGlong pWnd);

	//! \brief 设置告诉用户下载完成的回调函数
	//! \param pFunc 回调函数[in]。
	//! \param pWnd 句柄[in]。
	void SetRequestFinishedFunc(RequestFinishedProc pFunc,UGlong pWnd){m_DownloadQueue.SetRequestFinishedFunc(pFunc, pWnd);}

	//! \brief 发送下载完成消息
	//! \return 。
	//! \remarks 。
	//! \attention 。
	void SendDataChangedFunc(const UGDataChangeInfo& ChangeInfo);

	//! \brief 根据范围和比例尺，查询记录集。
	//! \param rcMapBounds [in] 范围。
	//! \param dScale [in] 比例尺。
	//! \return 
	UGTiles* QueryWithBounds(const UGRect2D& rcMapBounds, UGdouble dScale) const;

	//! \brief 根据范围和比例尺，判断该范围内的瓦片是否全都存在。
	//! \param rcMapBounds [in] 范围。
	//! \param dScale [in] 比例尺。
	//! \return 
	UGbool IsAllTilesExist(const UGRect2D& rcMapBounds, UGdouble dScale) const;


	//! \brief 得到服务类型。
	//! \param  [in]。
	//! \return 服务类型。
	//! \remarks 各个子类自己实现。
	virtual UGint GetServiceType() const {return 0;}


	//! brief 得到随机数
	//! param [in]  传入的种子数字
	//! param [out] 传出的随机数字
	void GeneRandNumber(const UGint nSeedNumber, UGint & nServerNumber);

protected:

	//! \brief 生成URL时是否采用TileInfo来计算
	virtual UGbool IsGenerateURLByTileInfo() = 0;

	//! \brief 生成URL
	//! \param tileInfo[in]产生URL的瓦片
	//! \param strURL[out]请求的URL
	virtual void GenerateURL(const UGTileInfo& tileInfo, UGString& strURL){}

	//! \brief 生成URL（超图的Web服务生成URL的方式）
	//! \param nScalePath[in]产生URL的比例尺
	//! \param nRow[in]产生URL的行
	//! \param nCol[in]产生URL的列
	//! \param strURL[out]请求的URL
	//! \attention 自己的服务就直接用行列号来请求吧
	virtual void GenerateURL(const UGuint& nScalePath, const UGint& nRow, const UGint& nCol, UGString& strURL){}

	//! \brief 调用下载器进行后台多线程下载。
	//! \remarks 若请求队列不为空，且下载器已经完成下载则将请求队列中的请求放入下载器进行多线程下载。
	void BackgroundDownloadFile();

	//! \brief 请求一张瓦片
	void RequestTile(UGMapCacheFile* pCacheFile, UGuint nScalePath, UGdouble dScale, UGint nRow, UGint nCol, UGbool bCallBack);
	


public:
	//! \brief 服务是否打开。
	//! \param  [in]。
	UGbool IsOpen() const;	
	
protected:
	//! \brief 服务的基地址标志。
	UGString m_strBaseURL;

	//! \brief 服务打开标志。
	UGbool m_bOpen;

	//! \brief 下载队列，在构造函数中完成初始化
	UGMapDownloadQueue m_DownloadQueue;

	//! \brief 负责与缓存IO交互
	UGLocalCacheManager* m_pLocalCacheManager;

	//! \brief 回调函数句柄
	UGDict<UGlong, DownloadResponseFunc> m_dictDownloadRF;

	//! \brief 是否已经是处理最后一张瓦片
	UGbool m_bLastTileRequest;

	//! \brief 回调函数句柄
	UGDict<UGlong, DataChangedProc> m_dictDataCF;

};

} //namespace UGC

#endif // !defined(AFX_UGMAPSERVICESTUB_H__F2ACB033_F582_4263_B9E9_DCA2E56F87DE__INCLUDED_)

