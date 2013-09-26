/**  \file UGLayersRecordsetsManager.h
   \brief 实现Layers中记录集的管理
   \author lugw
   \attention 
   Copyright(c) 2000-2010 SuperMap Software Co., Ltd.<br>
   All Rights Reserved.
 */ 

#if !defined(AFX_UGLAYERSRECORDSETSMANAGER_H__EE094C5F_85C5_441B_9AB8_CCA855D24FEE__INCLUDED_)
#define AFX_UGLAYERSRECORDSETSMANAGER_H__EE094C5F_85C5_441B_9AB8_CCA855D24FEE__INCLUDED_

#include "Stream/ugdefs.h"
#include "Map/UGLayer.h"


namespace UGC
{
	//{{zhouping 2010/12/27 bNullRecordset为true时表示pLayer用到的记录集为空
	struct UGLayerIsNullRecordset
	{
		UGLayer* pLayer;
		UGbool bNullRecordset;
		UGLayerIsNullRecordset()
		{
			pLayer = NULL;
			bNullRecordset = false;
		};
	};
	//zhouping 2010/12/27}}

	struct UGRecordsetWithLayer 
	{
		UGRecordset* pRecordset;
		//{{zhouping 2010/12/22  layerArray中的每个元素表示图层对应的记录集是否为空（字段表达式错误造成）
		//pLastNotNullRecordsetLayer 表示layerIsNullRecordsetArray中最后一个相应记录集不为空的图层
		//修改之后，pRecordset表示得到的记录集结果不为空的图层（都对应一个数据集）共有的结果记录集
		//bNullRecordsetWithCurLayer表示当前图层对应的记录集是否为空
		//pCurNotNullRecordsetLayer表示当前绘制查询的图层，记录下来主要是为了解决多个图层共享数据集时由谁
		//释放的问题，原来的pLastNotNullRecordsetLayer满足不了要求了，比如绘制的过程取消的时候会有图层没有
		//释放
		UGArray<UGLayerIsNullRecordset> pLayerArray;
		UGLayer* pLastNotNullRecordsetLayer;
		UGLayer* pCurNotNullRecordsetLayer;
		UGbool bNullRecordsetWithCurLayer;
		//zhouping 2010/12/22}}
		UGRecordsetWithLayer()
		{
			pRecordset = NULL;
			pLayerArray.RemoveAll();
			pLastNotNullRecordsetLayer = NULL;
			pCurNotNullRecordsetLayer = NULL;
			bNullRecordsetWithCurLayer = false;
		};
	};

	struct UGDatasetWithRecordset
	{
		UGDatasetVector* pDv;
		UGArray<UGRecordsetWithLayer> pRecordsetArray;
		UGDatasetWithRecordset()
		{
			pDv = NULL;
			pRecordsetArray.RemoveAll();
		};
	};

class MAP_API UGLayersRecordsetsManager  
{
public:
	UGLayersRecordsetsManager();
#ifdef SYMBIAN60
	~UGLayersRecordsetsManager();
#else
	virtual ~UGLayersRecordsetsManager();
#endif
	//! \brief 得到对应图层的Recordset，内部负责管理Recordset
	/**
	函数功能详细描述
	\param Layers       该Layers下的所有图层[in] 
	\param pos          当前绘制层位置[in]
	\param pLayer       当前绘制层[in]
	\param pGraphics    当前显示引擎[in]
	\param pDrawing     当前绘制参数[in]
	\param bTemp        该记录集是否为临时[in/out]
	\return 该层记录集
	*/
	UGRecordset* FindRecordsetWithLayer(UGList<UGLayer*> Layers, UGLayer* pLayer, UGGraphics* pGraphics, UGDrawing *pDrawing, UGbool& bTemp);

	//! \brief 获取当前地图保存的记录集大小
	UGuint GetSize()const;
	//! \brief 清空地图所有的记录集
	void RemoveAll();

	UGbool AppendQueryDefFields(UGQueryDef& qfTo,UGQueryDef& qfFrom);

	UGbool m_bIsflateBounds;

protected:

	UGbool GetQueryDef(UGList<UGLayer*> Layers, UGLayer* pLayer, UGGraphics* pGraphics, UGDrawing *pDrawing, UGRecordsetWithLayer& RecordsetWithLayerTemp);
	UGbool AddRecordsetWithLayer(UGRecordsetWithLayer& RecordsetWithLayerTemp,UGbool bFindDv);

private:
	UGArray<UGDatasetWithRecordset> m_pDatasetWithRecordset;
	UGArray<UGDatasetVector*> m_pDifDatasetsVector;
	UGuint m_nSize;
};

}

#endif // !defined(AFX_UGLAYERSRECORDSETSMANAGER_H__EE094C5F_85C5_441B_9AB8_CCA855D24FEE__INCLUDED_)

