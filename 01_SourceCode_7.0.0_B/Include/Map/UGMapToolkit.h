#if !defined(_UGMAPTOOLKIT_H_)
#define _UGMAPTOOLKIT_H_

#include "Map/UGMap.h"
#include "Engine/UGDatasetVector.h"
#include "Engine/UGDataSource.h"

namespace UGC {
	class MAP_API UGMapToolkit
	{
public:	
		//! \brief 把地图中的文本图层转为一个CAD数据集时的模式
		enum UGConvertOption
		{
			//! \brief  只转标签专题图图层
			UGThemeLabelOnly = 0,				
			//! \brief  只转文本图层
			UGTextLayerOnly = 1,				
			//! \brief  标签专题图和文本图层都转
			UGAll = 2					
		};
public:		
		//!brief 把地图中的所有文本图层转为一个CAD数据集,主要用于出缓存
		/**
		\param pMap						地图
		\param pDataSource				保存的数据源
		\param strDatasetName			数据集名称
		\param convertOption			转换选项
		\return 返回生成的数据集
		*/
		static UGDatasetVector* MapLabelToDataset(UGMap* pMap, UGDataSource* pDataSource, UGString strDatasetName,UGConvertOption convertOption);

		//!brief 把某个地图中的部分文本图层（包括标签）转为一个CAD数据集,主要用于出缓存
		/**
		\param pMap						地图
		\param arrLayers				文本图层集合
		\param pDataSource				保存的数据源
		\param strDatasetName			数据集名称
		\param bVisibleLayerOnly		为false时会考虑当前比例尺下不可见的图层
		\return 返回生成的数据集
		*/
		static UGDatasetVector* ThemeOrTextLayersToDataset(UGMap* pMap, UGArray<UGLayer*>* arrLayers, UGDataSource* pDataSource, UGString strDatasetName, UGbool bVisibleLayerOnly);

		//!brief 把某个地图中的文本图层（包括标签）获取出来
		/**
		\param pMap						地图
		\param convertOption			转换选项
		\return 返回文本图层集合
		*/
		static UGArray<UGLayer*>* GetLabelLayers(UGMap* pMap, UGConvertOption convertOption);

		//!brief 把某个地图中的点图层获取出来
		/**
		\param pMap						地图
		\param convertOption			转换选项
		\return 返回文本图层集合
		*/
		static UGArray<UGLayer*>* GetPointLayers(UGMap* pMap);
	};
}

#endif // _UGMAPTOOLKIT_H_