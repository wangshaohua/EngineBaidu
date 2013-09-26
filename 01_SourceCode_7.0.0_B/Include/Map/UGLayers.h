// UGLayers.h: interface for the UGLayers class.
//
//////////////////////////////////////////////////////////////////////

/*!
   **************************************************************************************
    \file     UGLayers.h
   **************************************************************************************
    \author   陈国雄
    \brief    图层集合类，负责图层的管理。                                                                       
    \attention   
   ----------------------------------------------------------------------------------<br>
    Copyright (c) 2000-2010 SuperMap Software Co., Ltd.                           <br>
    All Rights Reserved.                                                             <br>
   ----------------------------------------------------------------------------------<br> 
   
   **************************************************************************************
    \version 2005-05-20  陈国雄    初始化版本.                                       <br>
   **************************************************************************************
*/

#if !defined(AFX_UGLAYERS_H__4AF37668_F0B9_4C2D_B3A1_8E638AA1B00F__INCLUDED_)
#define AFX_UGLAYERS_H__4AF37668_F0B9_4C2D_B3A1_8E638AA1B00F__INCLUDED_

#include "Map/UGLayer.h"
#include "Workspace/UGWorkspace.h"
#include "Map/UGLayersRecordsetsManager.h"
#include "Toolkit/UGThread.h"
//#include <queue>

//#include "Map/UGMap.h"

namespace UGC {
class UGMap;
#if !defined OS_ANDROID && !defined IOS
class UGChartLayer;
#endif
//added by xielin 
//! \brief 图层绘制的报告，目前包括绘制之前的查询时间，绘制时间，绘制对象数,栅格数据查询时间就为0，全部算到绘制时间中,以毫秒为单位
struct LayerDrawReport
{
	UGint nQueryTime;
	UGint nDrawTime;
	UGint nGeometryCount;
	LayerDrawReport()
	{
		nQueryTime = 0;
		nDrawTime = 0;
		nGeometryCount = 0;
	}
};

typedef void (*LayersModifiedProc)(UGLayer* pLayer, UGuint nModifyLayerFlag, UGlong pData);
//! \brief BeforeLayerDraw 事件回调函数
typedef void (UGSTDCALL *BeforeLayerDrawProc)(UGlong pWnd,UGbool& bCancel,UGint nLayerIndex,UGGraphics* pGraphics);
//! \brief AfterLayerDraw 事件回调函数
typedef void (UGSTDCALL *AfterLayerDrawProc)(UGlong pWnd,UGint nLayerIndex,UGGraphics* pGraphics,LayerDrawReport& layerDrawReport);

//! \brief GeometrySelected 事件回调函数
typedef void (UGSTDCALL *LayersSelectedGeometryProc)(UGlong pWnd,UGint nSelectedGeometryCount);
//! \brief GeometrySelectChanged 事件回调函数
typedef void (UGSTDCALL *LayersSelectedGeometryChangedProc)(UGlong pWnd,UGint nSelectedGeometryCount);

struct LayersForSaveSFC 
{
	UGLayer* pLayer;
	UGbool bDel;
	LayersForSaveSFC()
	{
		pLayer = NULL;
		bDel = false;
	}
};

struct LayerDrawInfo {
};

class UGLayerDrawThread : public UGThread {
public:
	void SetLayerDrawInfo(const LayerDrawInfo &info) { drawInfo = info; }
	//void SetLayerDrawQueue(std::queue<LayerDrawInfo> *queueDrawInfo);
protected:
	UGint run(); 
private:
	LayerDrawInfo drawInfo;
};

struct LayerQueryInfo {
	UGList<UGLayer*> *pLayers;
	UGLayer* *pLayer;
	UGGraphics *pGraphics;
	UGDrawing *pDrawing;
	UGbool bTemp;
};

class UGLayerQueryThread : public UGThread {
public:
	void SetLayerQueryInfo(const LayerQueryInfo &info) { queryInfo = info; }
	//void SetLayerQueryQueue(std::queue<LayerQueryInfo> *queueQueryInfo);
protected:
	UGint run();
private:
	LayerQueryInfo queryInfo;
};

class MAP_API UGLayers  
{
	friend class UGMap;
	friend class UGLayer;
	friend class UGTrackingMap;
public:
	//! \brief 修改图层标识
	enum UGModifyLayerFlag	
	{
		//! \brief 添加图层
		mlAddLayer,			
		//! \brief 删除图层
		mlDeleteLayer,				
		//! \brief 可编辑图层改变
		mlChangeEditLayer,		
		//! \brief 图层编辑锁定改变
		mlChangeEditableLock	
	};

public:
	UGLayers();
#ifdef SYMBIAN60
	~UGLayers();
#else
	virtual ~UGLayers();
#endif

	UGLayers(const UGLayers &Layers);
	UGLayers& operator =(const UGLayers &Layers);

public:
	//! \brief 设置绘制参数
	void SetDrawParam(UGDrawParamaters *pDrawParam);
	//! \brief 绘制图层
	UGbool OnDraw(UGGraphics* pGraphics, UGDrawing *pDrawing, UGbool *pbBlank = NULL, UGProgress* pProgress = NULL);

	//! \brief 更改图层中数据集名称
	/**
	\param strOldName    原数据集名称[in]
	\param strNewName    修改的数据集名称[in]
	\remarks 是否有修改
	*/
	UGbool OnDatasetNameChanged(const UGString &strOldName, const UGString &strNewName);
	//! \brief 更改图层中数据源别名名称
	/**
	\param strOldAlias    原数据源别名[in]
	\param strNewAlias    修改的数据源别名[in]
	\remarks 是否有修改
	*/
	UGbool OnDataSourceAliasChanged(const UGString &strOldAlias, const UGString &strNewAlias);

	//! \brief 将图层中指定数据源别名的数据集设置为空
	/**
	\param strDataSourceAlias    原数据源别名[in]
	*/
	void OnDataSourceClose(const UGString &strDataSourceAlias);
	//! \brief 将图层中指定数据源别名的数据集打开
	/**
	\param strDataSourceAlias    指定图层数据源别名[in]
	\param pDataSource			 指定的数据源[in]
	*/
	void OnDataSourceOpen(const UGString &strDataSourceAlias,UGDataSource* pDataSource);

	//! \brief  是否有图层修改
	UGbool IsModified()const;
	//! \brief  设置图层修改标志
	void SetModifiedFlag(UGbool bModified = true);	

	//! \brief  指定图层是否存在
	UGbool IsLayerExisted(const UGString &strName)const;
	//! \brief  指定图层是否存在
	UGbool IsLayerExisted(UGLayer *pLayer)const;
	//! \brief  计算图层的范围
	UGRect2D ComputeBounds(UGbool bComputeDatasetBounds = false);
	//! \brief  得到图层的范围
	UGRect2D GetBounds()const;

	//! \brief  设置图层为可编辑
	//modified by xielin 2007-8-9 加一个参数，可以设置图层编辑状态为false
	UGbool SetEditableLayer(UGint nIndex,UGbool bEditable = true);
	//! \brief  得到指定图层名的索引
	UGint GetLayerIndex(const UGString &strName) const;
	//modified by dongfei 2007-04-24 改为返回图层数目，并修改传入的图层数组
	//! \brief  得到指定图层数据集的所有图层
	/**
	\param pDataset		指定数据集[in]
	\param layersArr    符合条件的图层数组[in/out]
	\remarks 符合的图层数目
	*/
	UGint FindLayerWithDataset(UGDataset *pDataset,UGArray<UGLayer*>& layersArr) const;
	//! \brief  得到指定图层索引
	/**
	\param pLayer		指定图层[in]
	\remarks 图层索引
	*/
	UGint FindLayer(UGLayer *pLayer) const;

	//! \brief  得到图层个数
	UGint GetCount()const;
	//! \brief  清空所有图层
	void Clear();
	//modified by dongfei 2004-04-24 增加一个默认参数参如图层名	
	//modified by xielin 2007-7-26 数据源别名就不传入了，自己从数据集取吧
	//! \brief  添加图层
	/**
	\param pDataset			指定数据集[in]
	\param bAddToHead		是否置顶[in]
	\param nType			图层类型[in]
	\param strLayerName		图层名[in]
	\param pTheme			图层的专题图[in]
	\remarks 创建的该图层
	*/
	UGLayer* AddDataset(UGDataset *pDataset,UGbool bAddToHead = true,UGLayer::UGLayerType nType = UGLayer::UG_Layer_Normal,UGString strLayerName = _U(""),UGTheme *pTheme = NULL);
#if !defined OS_ANDROID && !defined IOS
	////! \brief  添加海图图层
	////! \param pDataset			指定数据集[in]
	////! \param nType			图层类型[in]
	////! \param strLayerName		图层名[in]
	////! \return 创建的该图层
	////! \remarks 若指定数据集非海图数据集，那么返回的图层也没有海图风格
	//UGLayer* AddChartDataset(UGArray<UGDataset*> pDataset, UGbool bAddToHead = true, UGString strLayerName = "");

	//! \brief  添加海图图层
	//! \param pDatasetGroup	指定海图数据集组[in]
	//! \param strLayerName		图层名[in]
	//! \return 创建的该图层
	//! \remarks 若指定数据集非海图数据集，那么返回的图层也没有海图风格
	UGLayer* AddChart(UGDatasetGroup* pDatasetGroup, UGbool bAddToHead = true, UGString strLayerName = _U(""));

	//! \brief  判断是否包含海图图层
	UGbool ContainLayerChart()const;

	//! \brief  得到当前地图中的海图图层
	//! \param arrChartLayer	海图图层数组[out]
	//! \return 海图图层的个数
	UGint GetChartLayers(UGArray<UGChartLayer*> &arrChartLayer);

	void SortChartLayer(UGChartLayer *pChartLayer);
#endif
	//! \brief  添加图层
	/**
	\param pDataset			      指定数据集[in]
	\param bAddToHead		      是否置顶[in]
	\param nType			      图层类型[in]
	\param strLayerName		      图层名[in]
	\param pTemplateDataset		  模板数据集[in]
	\remarks 创建的该图层
	*/
	UGbool AddDataset(UGDataset *pDataset,UGDataset *pTemplateDataset,UGbool bAddToHead = true,UGLayer::UGLayerType nType = UGLayer::UG_Layer_Normal,UGString strLayerName = _U(""));

	//! \brief  添加图层
	/**
	\param index	图层插入的位置[in]
	\param xml	指定的图层xml信息[in]
	\remarks 根据XML字符串插入图层，只接受最新的版本，暂不考虑海图,实现用于图层树上的复制功能
	*/
	UGLayer* InsertFromXML(UGint index,UGString& xml);

//	UGLayer *AddDataset(UGDatasetVector *pDatasetV, const UGEventProperty& RouteEvent, UGbool bAddToHead = TRUE);
	//! \brief  删除指定图层
	UGint RemoveAt(UGint nIndex, UGint nCount = 1, UGbool bComputeBounds = true);
	//! \brief  删除所有图层
	void RemoveAll();

	//modified by xielin 2007-05-16 引入多图层编辑，修改返回的可编辑图层为一个List
	//! \brief  获取编辑图层对了
	UGList<UGLayer*> GetEditableLayer()const;
	//! \brief  获取指定索引图层
	UGLayer* GetLayerAt(UGint nIndex)const;
	//! \brief  获取指定名称的图层
	UGLayer* GetLayer(const UGString &strName)const;
	//added by dongfei 2004-04-24 
	//! \brief 获取图层名对应的一组图层 即'#'前面的名称相同
	UGint GetLayers(const UGString &strName,UGArray<UGLayer*>& pLayers)const;

	//! \brief 移动图层位置
	/**
	\param nIndexFrom		起始位[in]
	\param nIndexTo			终点位[in]
	*/
	UGbool MoveTo(UGint nIndexFrom, UGint nIndexTo);
	//! \brief 指定索引移动到底部
	UGbool MoveBottom(UGint nIndex);
	//! \brief 指定索引下移一位
	UGbool MoveDown(UGint nIndex);
	//! \brief 指定索引上移一位
	UGbool MoveUp(UGint nIndex);
	//! \brief 指定索引移至顶部
	UGbool MoveTop(UGint nIndex);

	//! \brief 设置对应的工作空间
	void SetWorkspace(UGWorkspace* pWorkspace);
	//! \brief 得到对应的工作空间
	UGWorkspace* GetWorkspace()const;

	//! \brief 使图层中的数据集生效
	UGbool ValidateDatasets();
//	void (UGLayers::*m_pLayersModified)(UGLayer* pLayer, UGuint nModifyLayerFlag);

	//! \brief 导出成XML
	UGString ToXML(UGint nVersion = 0)const;
	//! \brief 读取XML信息
	UGbool FromXML(const UGString& strXML,UGbool bIgnoreCaption = true, UGint nVersion = 0);

	//! \brief 回调函数，在图层修改时调用
	void SetLayersModifiedFunc(LayersModifiedProc pLayersModifiedFunc, UGlong pMapWnd);

	//added by dongfei 2007-04-24
	//! \brief 找出一个与图层集合中所有图层不同的名字
	UGbool FindAvailableName(UGString& strLayerName)const;

	//! \brief 找出一个与图层集合中所有专题图图层不同的专题图名字，用于绘制专题图的时候根据这个名字获取字段别名
	UGbool FindAvailableThemeName(UGString& strThemeName);

	//! \brief 判断图层名是否与图层集合中其它图层名不同
	UGbool IsvalidName(const UGString& strLayerName);

	//added by xielin 2007-04-13
	//! \brief 设置是否允许多图层编辑模式 
	void SetMultiLayerEditEnable(UGbool bMultiLayerEditEnable);
	//added by xielin 2007-04-13
	//! \brief 返回是否允许多图层编辑模式 
	UGbool IsMultiLayerEditEnable();

	//added by xielin 2007-04-13
	//! \brief 设置当前图层，用于多图层编辑，在多图层编辑中，因为允许多个图层同时编辑，如果设定当前图层后，添加的对象就放到
	//设置的当前图层中，如果不设置当前图层，默认就是可编辑的第一个图层 
	//! \brief 目前进行调整，无论CurrentLayer是否为空都不加判断，满足组件需要！！！
	void SetCurrentLayer(UGLayer* pLayer);

	//added by xielin 2007-04-13
	//! \brief 获取当前图层，用于多图层编辑，在多图层编辑中，因为允许多个图层同时编辑，如果设定当前图层后，添加的对象就放到
	//设置的当前图层中，如果不设置当前图层，默认就是可编辑的第一个图层 
	//! \brief 目前进行调整，无论CurrentLayer是否为空都不加判断，满足组件需要！！！
	UGLayer* GetCurrentLayer();
	
	//added by xielin 2007-05-16
	//! \brief 清空所有图层的选择集
	void ClearLayersSelection();

	//added by xielin 2007-05-16
	//! \brief 获取所有选中对象的个数
	UGint GetSelectedGeometryCount();

	//added by lugw 2007-05-31
	//! \brief 兼容以前的标签专题图置顶功能，将专题图图层放在前面
	/**
	\remarks 调整了一下，符合当前SFC专题图置顶的特点：置顶是对单个专题图的属性，而不是对所有同类型的专题图的属性起作用，这样，其实输入参数是没有作用的！
	*/
	void AdjustableLayers(UGuint unOnTop);

	//! \brief 设置是否发送事件，默认为true
	void SetNeedSendEvent(UGbool bNeedSendEvent = true);
	//! \brief 返回是否设置了发送事件
	UGbool IsNeedSendEvent();

	void SetBeforeLayerDrawFunc(BeforeLayerDrawProc pBeforeLayerDrawFunc,UGlong pWnd);
	void SetAfterLayerDrawFunc(AfterLayerDrawProc pAfterLayerDrawFunc,UGlong pWnd);

	void SetLayersSelectedGeometryFunc(LayersSelectedGeometryProc pGeometrySelectedFunc,UGlong pWnd);
	void SetLayersSelectedGeometryChangedFunc(LayersSelectedGeometryChangedProc pGeometrySelectChangedFunc,UGlong pWnd);
		
	void SendBeforeLayerDrawFunc(UGbool& bCancel,UGint nLayerIndex,UGGraphics* pGraphics);
	void SendAfterLayerDrawFunc(UGint nLayerIndex,UGGraphics* pGraphics,LayerDrawReport& layerDrawReport);

	void SendLayersSelectedGeometryFunc(UGint nSelectedGeometryCount);
	void SendLayersSelectedGeometryChangedFunc(UGint nSelectedGeometryCount);

	//! \brief 设置所有图层的填充方式，返回原有设置
	UGGraphics::BrushOrgMode SetBrushOrgMode(UGGraphics::BrushOrgMode brushOrgMode);

	//! \brief 设置使用Layers的填充方式设置覆盖各个图层的填充方式设置，返回原有设置
	UGbool SetOverwriteLayerBrushOrgMode(UGbool bOverwriteBrushOrgMode);

#if !defined SYMBIAN60 && !defined  OS_ANDROID && !defined (IOS)
	UGDataset* GetTopoLayerDs(UGDatasetTopo* pParentDataset, UGString strDatasetName)const;
#endif

	//! \brief 是否图层的记录集
	void ReleaseRecordset();

	UGbool m_bIsDisplayClip;
	//! \brief 存储地图的裁剪区域,在不用时最好置空吧,以免在下次设置时还显示以前的裁剪区域
	UGGeoRegion m_DisplayClipRegion;

	//! \brief 用于打印时的裁剪区域设置
	UGbool m_bPrintClip;
	UGRect m_rcPrintClipRect;

	UGbool m_bIsUserEntireBounds;
	UGRect2D m_rc2UserEntireBounds;	
	UGbool m_bRealeaseRecordSet;

	UGbool IsInflateBounds();
	void SetInflateBounds(UGbool bIsInflateBounds);

	//! \brief  判断数据集是否为同一个数据集
	/**
	\param pDataset1			  数据集1[in]
	\param pDataset2		      数据集2[in]
	\remarks 是否为同一个数据集
	*/
	static UGbool IsSameDataset(UGDataset *pDataset1,UGDataset *pDataset2);


	void SetDatasetName(const UGString &strDatasetName);
	
protected:
	void CheckBounds(UGLayer *pLayer, UGbool bComputeDatasetBounds);
#if !defined OS_ANDROID && !defined IOS
	//! 海图图层没有它自己的数据集，Bounds是图层内部计算出的 add by liufang
	void CheckBounds_ChartLayer(UGChartLayer *pChartLayer, UGbool bDisplayClip);
#endif
	void DrawCachedLayer(UGLayer *pLayer, UGGraphics* pGraphics, UGDrawing *pDrawing, UGbool *pbBlank, UGProgress* pProgress, clock_t& dbQueryEnd, UGbool& bResult, UGint& nGeometryCount);

public:
	//主要用于标签与点一起过滤
	void Preprocess();

	//还原预处理
	void UnPreprocess();

protected:
	LayersModifiedProc m_pLayersModifiedFunc;
	UGlong m_pMapWnd;
	//added by xielin 主要是图层的绘制事件
	//! \brief 是否需要发送控件的事件消息。
	UGbool m_bFireMapEvent;

	//! \brief 所有图层的填充方式设置
	UGGraphics::BrushOrgMode m_brushOrgMode;

	//! \brief 是否使用Layers的填充方式设置覆盖各个图层的填充方式设置
	UGbool m_bOverwriteBrushOrgMode;

protected:
	//delete by xielin 这个变量不用了，删除吧
	//UGList<UGLayer*> m_EditableLayers;
	UGList<UGLayer*> m_Layers;
	UGArray<LayersForSaveSFC> m_LayersForSaveSFC;
	//! \brief 是否修改
	UGbool m_bModified;			

	UGRect2D m_rcBounds;	
	//! \brief 图层们的Bounds之和是否为空.m_rc2Bounds是显示时候调用的。
	//! \attention 一定要注意：m_rc2Bounds不为空时，m_bIsBoundsNull仍然可能为空.
	UGbool m_bIsBoundsNull;			
									
	UGWorkspace* m_pWorkspace;
	UGDrawParamaters *m_pDrawParam;
	
	//added by xielin 2007-04-13
	//! \brief 允许多图层编辑模式 
	UGbool m_bMultiLayerEditEnable;
	//added by xielin 2007-04-13
	//! \brief 当前图层，用于多图层编辑，在多图层编辑中，因为允许多个图层同时编辑，如果设定当前图层后，添加的对象就放到设置的当前图层中，如果不设置当前图层，默认就是可编辑的第一个图层 
	UGLayer* m_pCurrentLayer;        

	UGLayersRecordsetsManager m_RecordsetsManager;

	//保存点和标签一起过滤时，处理过的图层，方便最后恢复
	UGArray<UGint> m_preprocessLayers;
	//保存点和标签一起过滤时，处理过的标签图层的查询条件，方便最后恢复
	UGDict<UGLayer*, UGQueryDef*> m_dicOldLabelQueryDef;
	
	BeforeLayerDrawProc m_pBeforeLayerDrawFunc;
	AfterLayerDrawProc m_pAfterLayerDrawFunc;

	LayersSelectedGeometryProc m_pLayersSelectedGeometryFunc;
	LayersSelectedGeometryProc m_pLayersSelectedGeometryChangedFunc;

private:
	UGString m_strDatasetName; // 地图输出为影像数据集时的数据集名称

public:
	//! \brief 调用事件回调函数的对象指针，统一为一个吧，节省内存
	UGlong m_pEventView;

	//! \brief 调用事件回调函数的对象指针
	UGlong m_pHandleView;

	//added by xielin 2008-8-27 处理一下地图的投影，判断如果就一个数据集，那么数据集投影和数据集投影一致,这里增加一个指针指向map
	UGMap* m_pMap;
	UGbool m_bVisibleSelected;
	LayerDrawReport m_LayerDrawReport;

};

}

#endif // !defined(AFX_UGLAYERS_H__4AF37668_F0B9_4C2D_B3A1_8E638AA1B00F__INCLUDED_)

