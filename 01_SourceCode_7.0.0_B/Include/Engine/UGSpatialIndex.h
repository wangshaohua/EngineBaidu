/* 
	\file UGSpatialIndex.h
	\brief	负责管理索引的一切
			包括索引的创建，重建，删除
			包括创建索引之前对数据的分析，创建索引，管理索引以及对索引的应用
			包括引擎是否支持某种索引的控制

	\author 李文龙
	\attention
	Copyright(c) 1996-2007 SuperMap GIS Technologies,Inc.<br>
	All Rights Reserved
	<b>更新说明：。</b>
	<em>1、第一条说明。</em>
*/
	// UGSpatialIndex.h: interface for the UGSpatialIndex class.
//
//////////////////////////////////////////////////////////////////////
#ifndef UGSPATIALINDEX_H
#define UGSPATIALINDEX_H

#include "Stream/ugdefs.h"
#include "Engine/UGDatasetVector.h"
#include "SpatialIndex/UGSpatialIndexInfo.h"
#include "Toolkit/UGProgress.h"

namespace UGC {
#if !defined SYMBIAN60 && !defined  OS_ANDROID 
class UGDBRTree;
#endif
//##ModelId=482030500148
#ifdef SYMBIAN60
class ENGINE_APIC UGSpatialIndex
#else
class ENGINE_API UGSpatialIndex
#endif
{
	friend class UGDatasetVector;
#if !defined SYMBIAN60 /*&& !defined  OS_ANDROID */
	friend class UGDBRTreeBranch;
	friend class UGDBRTreeLeaf;	
#endif
public:
	//##ModelId=482030500149
	ENGINE_APIF UGSpatialIndex();

	//##ModelId=48203050014A
	ENGINE_APIF UGSpatialIndex(UGDatasetVector *pDataset);
	//##ModelId=482030500157
	virtual ENGINE_APIF ~UGSpatialIndex();

public:	
	///////////////////////	DatasetVecotor调用的方法 ///////////////////////////////////////////////////

	//! \brief 建立索引
	//! \param *pDataset [in]。
	//! \return
	//! \remarks
	//! \attention 
	//##ModelId=482030500159
	ENGINE_APIF UGbool BuildSpatialIndex(UGSpatialIndexInfo &spatial);

	//! \brief 删除索引
	//! \param *pDataset [in]。
	//! \return 。
	//! \remarks 。
	//! \attention 。
	//##ModelId=482030500168
	ENGINE_APIF UGbool DropSpatialIndex();
#if !defined SYMBIAN60 /*&& !defined  OS_ANDROID */
	//! \brief 根据当前索引状态重建索引
	//! \param *pDataset [in]。
	//! \return
	//! \remarks
	//! \attention 
	//##ModelId=48203050015B
	ENGINE_APIF UGbool ReBuildSpatialIndex();

	//! \brief 脏数据的空间索引更新
	//! \param *pDataset [in]。
	//! \return 。
	//! \remarks 。
	//! \attention 。
	//##ModelId=482030500167
	ENGINE_APIF UGbool UpdateSpatialIndex();

	//! \brief 索引是否赃了
	//! \param *pDataset [in]。
	//! \return 。
	//! \remarks TRUE 表示脏；否则，不脏
	//! \attention 。
	//##ModelId=48203050016A
	ENGINE_APIF UGbool IsSpatialIndexDirty();
	
	//! \brief 加载 RTree
	//##ModelId=483BB70800DA
	ENGINE_APIF UGbool LoadDBRTree(UGMemoryStream& stream);

	//! \brief 设置目标数据集
	//##ModelId=48203050016B
	ENGINE_APIF UGbool SetDataset(UGDatasetVector* pDataset);
	
	//##ModelId=482030500178
	ENGINE_APIF UGDatasetVector* GetDataset();

	//! \brief 编辑后对索引的更新入口, pGeometry 只在多级网格索引时传入非空，其它传入NULL
	//##ModelId=483BB70800EA
	ENGINE_APIF UGbool UpdateIndexItem(UGint nID, const UGint nEditState, UGGeometry *pGeometry,
			   const UGRect2D &rc2Org, const UGRect2D &rc2New);

	//! \brief R树索引的大小
	ENGINE_APIF UGint GetMaxIndexSize();

	ENGINE_APIF UGbool SetMaxIndexSize(UGint nMaxSize);
	///////////////////////	DatasetVecotor调用的方法 ///////////////////////////////////////////////////
	
	//! \brief 当前数据集是否此索引支持
	//! \param *pDataset [in]。
	//! \param nIdxType [in]。
	//! \return 
	//! \remarks 
	//! \attention 
	//##ModelId=482030500179
	virtual ENGINE_APIF UGbool IsSupported(IndexType nIdxType);

	//##ModelId=482030500186
	ENGINE_APIF UGbool AnalyzeDataset(UGSpatialIndexInfo &info);
	
	//##ModelId=482030500188
	ENGINE_APIF UGshort RecommendSpatialIndexLevel();

	// fansc Add 2011-12-16
	//! \brief 查询R树索引包的对象ID
	//! \brief nLeafID    索引包的ID[in]
	//! \brief aryIDs     索引包的对象ID[out]
	virtual ENGINE_APIF UGbool GetIDsInLeaf(UGint nLeafID, UGArray<UGint>& aryIDs);


protected:
	//! \brief R树操作函数
	//! \remarks 不需要重载
	//##ModelId=483BB70800F0
	ENGINE_APIF UGbool StoreRTreeTrunk(UGStream &stream);

	//! \brief 取R树叶子结点
	//##ModelId=483BB70800FA
	virtual ENGINE_APIF UGint LoadRTreeLeaf(UGint nID,UGStream &stream);
	
	//! \brief 存储R树叶子结点
	//##ModelId=483BB70800FE
	virtual ENGINE_APIF UGbool StoreRTreeLeaf(UGint nID,UGStream &stream);
		
	//! \brief 取得所有Geometry的ID和四至并清空R树索引表，在建立R树索引时调用
	//##ModelId=483BB7080109
	virtual ENGINE_APIF void GetAllNodeItems(UGDBRTreeNodeItems &NodeItems,
		UGProgress *pProgress,UGString strSort);
	
	//! \brief 通过指定图幅的大小来建立三级索引
	//##ModelId=483BB708010E
	virtual ENGINE_APIF UGbool RegisterLibraryByGridSize(UGdouble dWidth, UGdouble dHeight);
	
	//! \brief 通过指定名称的字段来建立三级索引
	//##ModelId=483BB708011A
	virtual ENGINE_APIF UGbool RegisterLibraryByField(const UGString &strFieldName);

	//! \brief 建立多级网格索引
	//##ModelId=483BB708011D
	virtual ENGINE_APIF UGbool BuildSpatialIndexDynamic(UGSpatialIndexInfo &spatial);
	
	//! \brief 建立四叉树索引
	//##ModelId=483BB7080120
	virtual ENGINE_APIF UGbool BuildSpatialIndexQTree(UGSpatialIndexInfo &spatial);
	
	//! \brief 保存索引信息
	//##ModelId=483BB708012A
	virtual ENGINE_APIF UGbool SaveIndexInfo();

	//! \brief 返回空间索引脏的记录的数目，为是否需要重建空间索引提供参考
	//##ModelId=483BB708012C
 	virtual ENGINE_APIF UGint GetDirtyRecordCount();

	//! \brief Drop空间索引时使用
	//##ModelId=483BB708012E
	virtual ENGINE_APIF UGbool ClearDynamicIndex();

	//##ModelId=483BB7080139
	virtual ENGINE_APIF UGbool ClearRTreeIndex();

	//##ModelId=483BB708013B
	virtual ENGINE_APIF UGbool ClearQTreeIndex();

	////////////////	编辑时更新索引	//////////////////////////
	//! \brief				更新RTree索引叶节点
	//! \param nID			更新的记录的ID
	//! \param nEditState	对记录所作的更新操作	
	//! \param rc2Org		记录原来的Bounds
	//! \param rc2Des		记录新的Bounds，只在SetGeometry时rc2Org和rc2Dest不同
	//! \return				更新索引的操作成功与否
	//##ModelId=483BB708013D
	virtual ENGINE_APIF UGbool UpdateRTreeItem(	UGint nID, const UGint nEditState, 
		const UGRect2D &rc2Org, const UGRect2D &rc2New);

	//! \brief 更新图幅索引的图幅信息
	//##ModelId=483BB708014D
	virtual ENGINE_APIF UGbool UpdateLibVersion(const UGuint dwLibID, const UGint nID, 
		const UGint nEditMode, const UGRect2D &rc2New);
	
	//! \brief 更新多级网格索引
	//##ModelId=483BB7080159
	virtual ENGINE_APIF UGbool UpdateDynamicIdx(UGint nID, const UGint nEditMode, UGGeometry *pGeometry);
	
	//! \brief 更新纯四叉树索引
	//##ModelId=483BB708015E
	virtual ENGINE_APIF UGbool UpdateQTreeIdx(UGint nID, const UGint nEditMode, const UGRect2D &rc2New);

	//以下方法在 BuildSpatialIndex 中调用，用于建立不同类型的索引	
	//! \brief 建立R树索引
	//##ModelId=483BB708016A
	virtual ENGINE_APIF UGbool BuildSpatialIndexRTree(UGSpatialIndexInfo &spatial);

	////////////////	编辑时更新索引	//////////////////////////
private:
	//##ModelId=482030500189
	ENGINE_APIF UGbool IsNeedBuiltIndex();

	//! \brief 建立图幅索引
	//##ModelId=483BB7080178
	ENGINE_APIF UGbool BuildSpatialIndexTile(UGSpatialIndexInfo &spatial);
	
	//##ModelId=48203050018A
	ENGINE_APIF UGbool ConfigIndexByDataDistributing(UGSpatialIndexInfo &info);

public:
	//##ModelId=483BB70801A6
	UGDBRTree* m_pRTreeIndex;

protected:
	//##ModelId=483BB70801B5
	UGint m_nMaxIndexSize;	
#endif

protected:
	//##ModelId=482030500196
	UGDatasetVector* m_pDataset;
};
}

#endif // !defined(AFX_UGSPATIALINDEX_H__AAA6D3A9_BE41_415A_8BB9_122FF427F2D0__INCLUDED_)

