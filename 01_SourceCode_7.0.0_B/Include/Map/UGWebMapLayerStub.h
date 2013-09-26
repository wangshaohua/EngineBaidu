// UGWebMapLayerStub.h: interface for the UGWebMapLayerStub class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_UGWEBMAPLAYERSTUB_H__66585C4A_9CBA_4EE8_98FB_AE9B0C1C2803__INCLUDED_)
#define AFX_UGWEBMAPLAYERSTUB_H__66585C4A_9CBA_4EE8_98FB_AE9B0C1C2803__INCLUDED_

#include "Toolkit/UGThread.h"
#include "Toolkit/UGPalette.h"
#include "CacheFile/UGCacheFileCommon.h"
#include "Toolkit/UGTaskProcessor.h"
#include "Engine/UGDatasetRasterWeb.h"
#include "Map/UGCacheTileDatas.h"

namespace UGC {

class UGGraphics;
class UGDrawing;
class UGLayer;
class UGWebMapLayerStub;
typedef UGArray<UGTile*> UGTiles;


//////////////////////////////////////////////////////////////////////////

//! \brief 瓦片绘制任务
class UGDataChangeTask : public UGTaskBase
{
public:
	UGDataChangeTask()
	{
		
	}

	UGDataChangeTask(const UGDataChangeTask* pTask)
	{
		m_ChangeInfo = pTask->m_ChangeInfo;
	}

	UGDataChangeTask(const UGDataChangeInfo& ChangeInfo)
	{
		m_ChangeInfo = ChangeInfo;
	}

	//! \brief 重载 ==
	UGbool operator == (const UGDataChangeTask& Task) const
	{
		if (m_ChangeInfo == Task.m_ChangeInfo)
		{
			return true;
		}

		return false;
	}

	//! \brief 重载=。
	void operator = (const UGDataChangeTask& Task)
	{
		m_ChangeInfo = Task.m_ChangeInfo;
	}

	//! \brief 获取任务名称
	virtual UGString GetClassName()
	{
		return _U("DataChangeTask");
	}

	//! \brief 实现任务类的具体操作
	virtual UGbool Execute()
	{
		return false;
	}

	//! \brief 克隆任务
	virtual UGTaskBase* Clone()
	{
		return new UGDataChangeTask(*this);
	}

public:
	//! \brief 数据变化信息
	UGDataChangeInfo m_ChangeInfo;

};

//! \brief 格网渲染任务辅助类
class UGDataChangeTaskHelper
{
public:
	static UGTaskBase* CreateTask(const UGDataChangeInfo& ChangeInfo)
	{
		return new UGDataChangeTask(ChangeInfo);
	}

	static UGDataChangeInfo& GetDataChange(UGTaskBase* pTask)
	{
		UGASSERT(pTask != NULL);
		return ((UGDataChangeTask*)pTask)->m_ChangeInfo;
	}

};

//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////

//! \brief 转换缓存瓦片任务
class UGUpdataCacheTask : public UGTaskBase
{
public:
	UGUpdataCacheTask(const UGUpdataCacheTask* pTask)
	{
		m_dScale = pTask->m_dScale;
		m_rcBounds = pTask->m_rcBounds;
		m_nExtTileSize = pTask->m_nExtTileSize;
		m_bRemoveAll = pTask->m_bRemoveAll;
	}

	UGUpdataCacheTask(UGdouble dScale, UGRect2D rcBounds, UGint nExtTileSize, UGbool bRemoveAll)
	{
		m_dScale = dScale;
		m_rcBounds = rcBounds;
		m_nExtTileSize = nExtTileSize;
		m_bRemoveAll = bRemoveAll;
	}

	//! \brief 重载 ==
	UGbool operator == (const UGUpdataCacheTask& Task) const
	{
		if (UGEQUAL(m_dScale, Task.m_dScale) && m_rcBounds == Task.m_rcBounds && 
			m_nExtTileSize == Task.m_nExtTileSize && m_bRemoveAll == Task.m_bRemoveAll)
		{
			return true;
		}

		return false;
	}

	//! \brief 获取任务名称
	virtual UGString GetClassName()
	{
		return _U("UpdataCacheTask");
	}

	//! \brief 实现任务类的具体操作
	virtual UGbool Execute()
	{
		return false;
	}

	//! \brief 克隆任务
	virtual UGTaskBase* Clone()
	{
		return new UGUpdataCacheTask(*this);
	}

	UGdouble GetScale()
	{
		return m_dScale;
	}

	UGRect2D GetBounds()
	{
		return m_rcBounds;
	}

	UGint GetExtTileSize()
	{
		return m_nExtTileSize;
	}

	UGbool IsRemoveAll()
	{
		return m_bRemoveAll;
	}

public:
	//! \brief 更新缓存参数
	UGdouble m_dScale;
	UGRect2D m_rcBounds;
	UGint m_nExtTileSize;
	UGbool m_bRemoveAll;

};

//! \brief 格网渲染任务辅助类
class UGUpdataCacheTaskkHelper
{
public:
	static UGTaskBase* CreateTask(UGdouble dScale, UGRect2D rcBounds, UGint nExtTileSize, UGbool bRemoveAll)
	{
		return new UGUpdataCacheTask(dScale, rcBounds, nExtTileSize, bRemoveAll);
	}

	static UGdouble GetScale(UGTaskBase* pTask)
	{
		UGASSERT(pTask != NULL);
		return ((UGUpdataCacheTask*)pTask)->GetScale();
	}

	static UGRect2D GetBounds(UGTaskBase* pTask)
	{
		UGASSERT(pTask != NULL);
		return ((UGUpdataCacheTask*)pTask)->GetBounds();
	}

	static UGint GetExtTileSize(UGTaskBase* pTask)
	{
		UGASSERT(pTask != NULL);
		return ((UGUpdataCacheTask*)pTask)->GetExtTileSize();
	}

	static UGbool IsRemoveAll(UGTaskBase* pTask)
	{
		UGASSERT(pTask != NULL);
		return ((UGUpdataCacheTask*)pTask)->IsRemoveAll();
	}

};

class UGWebMapStub;

//! \brief 发送下载请求线程管理(由于直接调用引擎RequestTile接口可能会耗费时间，这里改成线程发送)
class UGUpdataCacheStub : public UGTaskProcessor
{
public:
	UGUpdataCacheStub();
	~UGUpdataCacheStub();

public:
	void InitUpdataCache(UGWebMapStub* pWebMapStub);
	void UnInitUpdataCache();
	void ResetUpdataCache();

	//! \brief 添加任务到任务处理中心
	UGbool AddTask(UGTaskBase* pTask, UGbool bTail = true);

	//! \brief 清空所有任务
	UGint RemoveAllTask();

protected:
	//! \brief 处理任务(子线程处理函数)
	virtual UGbool ProcessTask(UGTaskBase* pTask);

private:
	UGWebMapStub* m_pWebMapStub;

	//! \brief 绘制任务管理
	UGTaskManager m_TaskManager;

};

//////////////////////////////////////////////////////////////////////////

class UGWebMapStub;

//! \brief 瓦片转换缓存线程管理
class UGTileDataCache : public UGTaskProcessor, public UGTaskFilter
{
public:
	UGTileDataCache();
	~UGTileDataCache();

public:
	void InitDataCache(UGWebMapStub* pWebMapStub);
	void UnInitDataCache();
	void ResetDataCache();

	//! \brief 添加任务到任务处理中心
	UGbool AddTask(UGTaskBase* pTask, UGbool bTail = true);

	//! \brief 清空所有任务
	UGint RemoveAllTask();

protected:
	//! \brief 处理渲染任务(子线程处理函数)
	virtual UGbool ProcessTask(UGTaskBase* pTask);

	//! \brief 过滤渲染任务(子线程处理函数)
	virtual UGbool PreTranslateTask(UGTaskBase::TaskState eTaskState, UGTaskBase* pTask, UGbool& bHandle);

private:
	UGWebMapStub* m_pWebMapStub;

	//! \brief 绘制任务管理
	UGTaskManager m_TaskManager;

};

//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////

//! \brief 请求下载瓦片任务
class UGRequestTileTask : public UGTaskBase
{
public:
	UGRequestTileTask()
	{
		m_dScale = 0.0;
		m_rcBounds.SetEmpty();
	}

	UGRequestTileTask(const UGRequestTileTask* pTask)
	{
		m_dScale = pTask->m_dScale;
		m_rcBounds = pTask->m_rcBounds;
	}

	UGRequestTileTask(UGdouble dScale, UGRect2D rcBounds)
	{
		m_dScale = dScale;
		m_rcBounds = rcBounds;
	}

	//! \brief 重载 ==
	UGbool operator == (const UGRequestTileTask& Task) const
	{
		if (UGEQUAL(m_dScale, Task.m_dScale) && m_rcBounds == Task.m_rcBounds)
		{
			return true;
		}

		return false;
	}

	//! \brief 获取任务名称
	virtual UGString GetClassName()
	{
		return _U("RequestTileTask");
	}

	//! \brief 实现任务类的具体操作
	virtual UGbool Execute()
	{
		return false;
	}

	//! \brief 克隆任务
	virtual UGTaskBase* Clone()
	{
		return new UGRequestTileTask(*this);
	}

	UGdouble GetScale()
	{
		return m_dScale;
	}

	UGRect2D GetBounds()
	{
		return m_rcBounds;
	}

private:
	//! \brief 请求参数
	UGdouble m_dScale;
	UGRect2D m_rcBounds;

};

//! \brief 格网渲染任务辅助类
class UGRequestTileTaskHelper
{
public:
	static UGTaskBase* CreateTask(UGdouble dScale, UGRect2D rcBounds)
	{
		return new UGRequestTileTask(dScale, rcBounds);
	}

	static UGdouble GetScale(UGTaskBase* pTask)
	{
		UGASSERT(pTask != NULL);
		return ((UGRequestTileTask*)pTask)->GetScale();
	}

	static UGRect2D GetBounds(UGTaskBase* pTask)
	{
		UGASSERT(pTask != NULL);
		return ((UGRequestTileTask*)pTask)->GetBounds();
	}

};


class UGWebMapStub;

//! \brief 发送下载请求线程管理(由于直接调用引擎RequestTile接口可能会耗费时间，这里改成线程发送)
class UGRequestTileStub : public UGTaskProcessor
{
public:
	UGRequestTileStub();
	~UGRequestTileStub();

public:
	void InitRequestStub(UGWebMapStub* pWebMapStub);
	void UnInitRequestStub();
	void ResetRequestStub();

	//! \brief 添加任务到任务处理中心
	UGbool AddTask(UGTaskBase* pTask, UGbool bTail = true);

	//! \brief 清空所有任务
	UGint RemoveAllTask();

protected:
	//! \brief 处理任务(子线程处理函数)
	virtual UGbool ProcessTask(UGTaskBase* pTask);

private:
	UGWebMapStub* m_pWebMapStub;

	//! \brief 绘制任务管理
	UGTaskManager m_TaskManager;

};

//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////

class UGWebMapStub
{
	friend class UGUpdataCacheStub;
	friend class UGTileDataCache;
	friend class UGRequestTileStub;
public:
	UGWebMapStub();
	virtual ~UGWebMapStub();

public:
	//! \brief 初始化网络地图相关信息
	virtual void InitWebMapInfo(UGLayer *pLayer);

	//! \brief 反初始化网络地图相关信息
	virtual void UnInitWebMapInfo();

	//! \brief 重新设置网络地图相关信息
	virtual void ResetWebMapInfo();

	//! \brief 图层向数据集请求瓦片
	virtual void RequestTile(UGdouble dScale, UGRect2D& rcViewBounds, UGbool bPanMode = false, UGbool bForceUpdate = false);

	//! \brief 根据当前的视图范围把m_pDrawTileImage绘制到pGraphics上
	virtual UGbool OnDrawTileImage(UGDrawing* pDrawing, UGbool bIsPrinting);

public:
	//! \brief 是否是异步模式绘制地图
	UGbool IsAsyncMode() const;

	//! \brief 判断是否出图
	UGbool IsPrintToFile();

	//! \brief 更新缓存的ImageData
	UGbool UpdateCacheTile(UGint nExtTileSize = 1, UGbool bRemoveAll = true);

	//! \brief 根据当前的视图范围把本地的瓦片拼接起来绘制到pGraphics上
	UGbool OnDrawLocaleTileImage(UGDrawing* pDrawing);

	//! \brief 回调刷新地图
	void RefreshMapCallBack(UGdouble dMapScale, const UGRect2D &rcBounds);

	//! \brief 添加转换任务
	UGbool AddDataCacheTask(UGTaskBase* pTask, UGbool bTail = true);

	//! \brief 清空所有转换任务
	UGint RemoveAllDataCacheTask();
	
protected:
	//! \brief 线程转换本地缓存的瓦片到像素矩阵
	UGbool ProcessUpdateCacheTask(UGdouble dMapScale, const UGRect2D rcBounds, UGint nExtTileSize = 1, UGbool bRemoveAll = true);

	UGImageData* ConvertTileImageData(UGDatasetRasterWeb* pDatasetWeb, UGTile* pTile, UGColorTable* pColorTable);

	void PaintImageDataByColorTable( UGImageData* pImageDataDest,UGImageData* pImageDataSrc, UGColorTable *pColorTable);

	//! \brief 线程转换本地缓存的瓦片到像素矩阵
	UGbool ProcessTileCacheTask(UGTaskBase* pTask);

	UGImageData* CreateTileImageData(UGint nWidth, UGint nHeight);
	UGbool DeleteTileImageData(UGImageData* pTileImageData);
	UGbool FillTileImageData(UGImageData* pTileImageData, UGColor color = UGRGBA(255, 255, 255, 0));
	UGbool DrawTileImageData(UGImageData* pImageDataDest, UGint x, UGint y, UGint nWidth, UGint nHeight, UGImageData* pImageDataSrc, UGint xSrc, UGint ySrc);
	UGbool StretchTileImageData(UGImageData* pImageDataDest, UGint x, UGint y, UGint nWidth, UGint nHeight, UGImageData* pImageDataSrc, UGint xSrc, UGint ySrc, UGint nSrcWidth, UGint nSrcHeight);

	//! \brief 根据当前的视图范围把缓存的CacheTileImage绘制到pGraphics上
	UGbool OnDrawCacheTileImage(UGDrawing* pDrawing, UGRect2D& rcTileImageBounds, UGImageData* pTileImageData);

protected:
	//! \brief 图层向数据集请求瓦片
	UGbool Request(UGdouble dScale, UGRect2D rcBounds);

private:
	static UGbool GetViewDPSize(UGDrawing* pDrawing, UGint& nViewWidth, UGint& nViewHeight);

	static UGbool TransparentBitbltDraw(UGDrawing* pDrawing, UGint x, UGint y, UGint nWidth, UGint nHeight, 
		UGImageData* pImageData, UGint xSrc, UGint ySrc, UGbool bAlphaMask);

	static UGbool TransparentOrRotateDraw(UGDrawing* pDrawing, UGint x, UGint y, UGint nWidth, UGint nHeight, 
		UGImageData* pImageData, UGRect2D& rcImageBounds, UGbool bAlphaMask);

	// 处理每个像素的透明，亮度和对比度等
	static void ProcessPixelModify(const UGbyte& btBitsPixelSrc, UGbyte* pPixelBitsSrc,
		const UGbyte& btBitsPixelDest, UGbyte* pPixelBitsDest,
		const UGbool& bBackTransparent, const UGColor& clrTransparent, const UGbyte& btColorTolerance, 
		const UGchar& btBrightness, const UGchar& btContrast, 
		const UGdouble& dTransPercentRate, const UGdouble& dTransPercentRateRemain, 
		const UGbool& bAlphaMask);

	static void GetPixel(const UGbyte& btBitsPixel, const UGbyte* pPixelBits, UGbyte& r, UGbyte& g, UGbyte& b, UGbyte& a);
	static void SetPixel(const UGbyte& btBitsPixel, UGbyte* pPixelBits, const UGbyte& r, const UGbyte& g, const UGbyte& b, const UGbyte& a);

	static void Brightness(UGbyte& r, UGbyte& g, UGbyte& b, UGint nPercentage);
	static void Contrast(UGbyte& r, UGbyte& g, UGbyte& b, UGint nPercentage);

protected:
	UGLayer* m_pLayer;

	//! \brief 缓存的TileImage对应的地理范围
	UGRect2D m_rcCacheTileSetBounds;
	//! \brief 记录当前请求的比例尺
	UGdouble m_dCacheTileScale;
	//! \brief 用于同步m_pCacheTileImage
	UGMutex	m_MutexCacheTileImage;

	//! \brief 缓存的TileImageData
	UGImageData* m_pCacheTileImageData;

	//! \brief 缓存已经访问过的网络地图瓦片数据
	UGCacheTileDatas m_CacheTileDatas;
	//! \brief 转换瓦片的线程管理类
	UGTileDataCache m_DataCache;

	//! \brief 发送瓦片下载请求类
	UGRequestTileStub m_RequestStub;

	//! \brief 发送转换当前区域数据
	UGUpdataCacheStub m_UpdataCacheStub;

};

//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////

class UGWebMapLayerStub;

//! \brief 绘制数据变化区域的线程管理
class UGDrawDataChange : public UGTaskProcessor, public UGTaskFilter
{
public:
	UGDrawDataChange();
	virtual ~UGDrawDataChange();

	void InitDataChange(UGWebMapLayerStub* pWebMapStub);
	void UnInitDataChange();
	void ResetDataChange();

	//! \brief 添加任务到任务处理中心
	UGbool AddTask(UGTaskBase* pTask, UGbool bTail = true);

	//! \brief 清空所有任务
	UGint RemoveAllTask();

protected:
	//! \brief 处理渲染任务(子线程处理函数)
	virtual UGbool ProcessTask(UGTaskBase* pTask);

	//! \brief 过滤渲染任务(子线程处理函数)
	virtual UGbool PreTranslateTask(UGTaskBase::TaskState eTaskState, UGTaskBase* pTask, UGbool& bHandle);

private:
	UGWebMapLayerStub* m_pWebMapStub;

	//! \brief 绘制任务管理
	UGTaskManager m_TaskManager;

};

//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////

class UGWebMapLayerStub : public UGWebMapStub 
{
	friend class UGDrawDataChange;
public:
	UGWebMapLayerStub();
	virtual ~UGWebMapLayerStub();

public:
	//! \brief 初始化网络地图相关信息
	virtual void InitWebMapInfo(UGLayer *pLayer);

	//! \brief 反初始化网络地图相关信息
	virtual void UnInitWebMapInfo();

	//! \brief 重新设置网络地图相关信息
	virtual void ResetWebMapInfo();

	//! \brief 图层向数据集请求瓦片
	virtual void RequestTile(UGdouble dScale, UGRect2D& rcViewBounds, UGbool bPanMode = false, UGbool bForceUpdate = false);

	//! \brief 根据当前的视图范围把m_pDrawTileImage绘制到pGraphics上
	virtual UGbool OnDrawTileImage(UGDrawing* pDrawing, UGbool bIsPrinting);

public:
	//! \brief 添加绘制任务
	UGbool AddDataChangeTask(UGTaskBase* pTask, UGbool bTail = true);

	//! \brief 清空所有绘制任务
	UGint RemoveAllDataCacheTask();

protected:
	//! \brief 线程把变化区域内的Tile绘制到m_pCacheTileImageData上
	UGbool ProcessDataChangeTask(UGTaskBase* pTask);

	UGbool CreatePanCacheTileImage(const UGDataChangeInfo& ChangeInfo, UGRect2D& rcTileIntersect);
	UGbool CreateZoomCacheTileImage(const UGDataChangeInfo& ChangeInfo);
	UGbool DrawTiles(UGTiles* pTiles, int nTileSize, const UGDataChangeInfo& ChangeInfo, const UGRect2D* pTilesIntersect = NULL);

protected:
	//! \brief 绘制瓦片的线程管理类
	UGDrawDataChange m_DataChange;

};

//////////////////////////////////////////////////////////////////////////

}

#endif // !defined(AFX_UGWEBMAPLAYERSTUB_H__66585C4A_9CBA_4EE8_98FB_AE9B0C1C2803__INCLUDED_)
