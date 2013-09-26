/*! \file	 UGDatasetVector.h
 *  \brief	 矢量数据集类
 *  \author	 ugc team
 *  \attention 
 *  Copyright(c) 2000-2010  SuperMap GIS Technologies,Inc.<br>
 *  All Rights Reserved
 *  \version $Id: UGDatasetVector.h,v 1.45 2010/03/22 06:00:57 wangmao Exp $
 */

#ifndef UGDATASETVECTOR_H
#define UGDATASETVECTOR_H

#include "Engine/UGDataset.h"
#include "Engine/UGRecordset.h"
#include "SpatialIndex/UGSpatialIndexInfo.h"	

#if !defined SYMBIAN60 /*&& !defined  OS_ANDROID */
//#ifndef OS_ANDROID
#include "Geometry/UGFeature.h"
//#endif
#include "SpatialIndex/UGDBRTreeNode.h"
#include "SpatialIndex/UGDBRTree.h"
#endif
#include "Engine/UGSpatialIndex.h"
#include "Toolkit/UGTextCodec.h"
#include "Engine/UGDatasetVectorInfo.h"

#if defined IOS
#include "Engine/UGDataHistory.h"
#endif

#include "Engine/UGTable.h"

namespace UGC {
	//class PATHANALYST_API	 UGEventProperty
	class ENGINE_API	 UGEventProperty  
	{
	public:
		 UGEventProperty();
		~UGEventProperty();
		UGbool operator == (const UGEventProperty& EventProperty);
		UGbool operator != (const UGEventProperty& EventProperty);
	public:		
	/*! 动态分段事件(Event)类型
	*
	*/
		enum EventType
		{
			PointEvent = 1, /// 点事件
			LineEvent  = 2, /// 线事件
		};		
		
		UGString	  m_strEventRouteIDFieldName; /// 事件表中RouteID字段名		
		EventType m_nEventType;			    /// 事件类型		
		UGString m_strFromMeasureFieldName; /// 线事件的起始Measure字段
		UGString m_strToMeasureFieldName;   /// 线事件的终止Measure字段
		UGString m_strMeasureFieldName;     /// 点事件的Measure
		
		UGlong m_nEventMeasureUnit;          /// Measure单位
		
		UGString m_strEventTableName;
		UGDatasetVector* m_pDatasetRoute;
		UGString m_strRouteDataSourceAlias; /// Route数据集所在的数据源别名
		UGString m_strRouteDtName;		   /// Route数据集名称	 
		UGString m_strRouteIDFieldName;	   /// RouteID字段	 
		UGString m_strOffsetField;		   /// 数据定位偏移字段	
		UGString m_strRouteWhereClause;	   /// Route数据集过滤条件

	};
#if !defined SYMBIAN60
class UGDataHistory;
#endif
class UGSpatialIndex;
//##ModelId=48203052029F
struct UG_DATA_CACHE_FILE_HEADER 
{
	//##ModelId=4820305202B0
	UGint nVersion;
	//##ModelId=4820305202B1
	UGint nRecordCount;
	//##ModelId=4820305202BF
	UGDataCodec::CodecType nCodecType;
	//##ModelId=4820305202CE
	UGint nDatasetID;
	//##ModelId=4820305202DE
	UGint nLibID;
	//##ModelId=4820305202DF
	UGint nOffBits;
	//##ModelId=4820305202EE
	UGRect2D rc2Bounds;
	//##ModelId=4820305202FD
	UGdouble dXGridSize;
	//##ModelId=4820305202FE
	UGdouble dYGridSize;
	//##ModelId=48203052030D
	UGint nReserved1;
	//##ModelId=48203052031C
	UGint nReserved2;

	//##ModelId=48203052031D
	void Save(UGStream& stream)
	{
		stream<<nVersion;
		stream<<nRecordCount;
		stream<<(UGint)nCodecType;
		stream<<(UGint)nDatasetID;
		stream<<nLibID;
		stream<<nOffBits;
		
		stream<<rc2Bounds.left;
		stream<<rc2Bounds.top;
		stream<<rc2Bounds.right;
		stream<<rc2Bounds.bottom;
		
		stream<<dXGridSize;
		stream<<dYGridSize;
		stream<<nReserved1;
		stream<<nReserved2;
	};

	//##ModelId=48203052032D
	void Load(UGStream& stream)
	{
		stream>>nVersion;
		stream>>nRecordCount;
		UGint nEnc = 0;
		stream>>nEnc;
		nCodecType = (UGDataCodec::CodecType)nEnc;
		stream>>nDatasetID;
		stream>>nLibID;
		stream>>nOffBits;
		
		stream>>rc2Bounds.left;
		stream>>rc2Bounds.top;
		stream>>rc2Bounds.right;
		stream>>rc2Bounds.bottom;
		
		stream>>dXGridSize;
		stream>>dYGridSize;
		stream>>nReserved1;
		stream>>nReserved2;
	};

	UGint GetSizeofLenth()
	{
		UGint nLenght=0;
		
		nLenght = sizeof(nVersion) + sizeof(nRecordCount) + sizeof(nCodecType) +
				  sizeof(nDatasetID) + sizeof(nLibID) + sizeof(nOffBits) +
				  4*sizeof(double) + sizeof(dXGridSize) + sizeof(dYGridSize) +
				  sizeof(nReserved1) + sizeof(nReserved2);
		return nLenght;
	}
};

//UG_SQ_MAYBEIDS
class ENGINE_API UGMaybeItem
{
public:
	UGMaybeItem()
	{
		pGeometry = NULL;
		aryIDs.RemoveAll();
	};
	
	~UGMaybeItem()
	{
		if(pGeometry)
		{
		}
		aryIDs.RemoveAll();
	};
	
public:
	UGGeometry *pGeometry;
	UGArray<UGint> aryIDs;
};

class ENGINE_API UGMaybeItems : public UGArray<UGMaybeItem >
{
public:
	void ReleaseAll()
	{
		for(UGint n=0; n < this->GetSize(); n++)
		{
			delete GetAt(n).pGeometry;
			//			GetAt(n).pGeometry = NULL;
		}
	};
};
typedef UGArray<UGint> UG_MayIDs;

//##ModelId=48203052033C
struct UG_INDEX_CACHE_FILE_HEADER 
{
	//##ModelId=48203052034C
	UGint nReserved1;
	//##ModelId=48203052034D
	UGint nReserved2;
	//##ModelId=48203052035B
	UGint nOffBits;

	//##ModelId=48203052036B
	void Save(UGStream& stream)
	{
		stream<<nReserved1;
		stream<<nReserved2;
		stream<<nOffBits;
	};

	//##ModelId=48203052036D
	void Load(UGStream& stream)
	{
		stream>>nReserved1;
		stream>>nReserved2;
		stream>>nOffBits;
	};

	UGint GetSizeofLenth()
	{
		UGint nLenght=0;
		
		nLenght = sizeof(nReserved1) + sizeof(nReserved2) + sizeof(nOffBits);
		return nLenght;
	}
};	


#ifdef OS_ANDROID
	class UGDataHistory;
#endif
//记录历史对象指针和是否指针有效的结构
//##ModelId=48203052037A
	struct ValidDataHistory
	{
		#if !defined SYMBIAN60 /*&& !defined  OS_ANDROID && !defined (IOS)*/
		//##ModelId=48203052038B
		UGDataHistory* pDataHistory;
		#endif
		//##ModelId=48203052038C
		UGbool bValid ;
	};

//##ModelId=482030520399
class  ENGINE_API UGSubDtArray : public UGArray<UGDatasetVector *>
{
public:
	//##ModelId=4820305203B9
	UGSubDtArray()
	{
	};

	//##ModelId=4820305203BA
	~UGSubDtArray()
	{
	};
public:
	//##ModelId=4820305203C8
	UGDatasetVector * operator [](UGint nIndex) const;
	//##ModelId=4820305203CB
	UGDatasetVector * operator [](UGString strName) const;
};

//! \brief 修改图层标识
enum UGModifyDatasetFlag	
{
	//! \brief 添加对象
	mdAddGeometry,			
	//! \brief 删除删除
	mdDeleteGeometry,				
	//! \brief 修改对象
	mdEditGeometry,		

};
//! \brief ModifyDatasetProc 回调函数
//!param[in] pLayerDataset 数据集图层指针
//!param[in] nID 修改对象的ID
//!param[in] pnt2D 修改对象的内点
//!param[in] flag修改标识
typedef  void (UGSTDCALL *AffterDatasetModifiedProc)(void* pLayerDataset,UGint nID,UGPoint2D pnt2D,UGModifyDatasetFlag flg);

//##ModelId=48203053006D
#ifdef SYMBIAN60
class ENGINE_APIC UGDatasetVector : public UGTable
#else
class ENGINE_API UGDatasetVector : public UGTable
#endif
{
friend class UGSpatialIndex;

#if !defined SYMBIAN60 && !defined  OS_ANDROID && !defined (IOS)
friend class UGDBRTreeBranch;
friend class UGDBRTreeLeaf;
#endif

public:
	//! \brief 构造函数
	//##ModelId=48203053007D
	ENGINE_APIF UGDatasetVector();
	//! \brief 析构函数
	//##ModelId=48203053007E
	virtual ENGINE_APIF ~UGDatasetVector();

	//! \brief 基类UGDataset定义的纯虚函数
public:

	//! \brief 追加记录,属性字段有对应关系,空间字段不处理
	//##ModelId=48203053017F
	virtual ENGINE_APIF UGbool Append(UGRecordset* pSrcRecordset,
		UGArray<UGString> &strSrcFieldNames,
		UGArray<UGString> &strDesFieldNames,
		UGbool bShowProgress = TRUE,
		UGString strTileName = _U(""));

	//! \brief 向数据集追加记录。
	//! \param pSrcRecordset 源记录集指针[in]。
	//! \return 追加成功返回TRUE，失败返回FALSE。
	//##ModelId=48203053017A
	virtual ENGINE_APIF UGbool Append(UGRecordset* pSrcRecordset, 
		UGbool bShowProgress = TRUE,UGString strTileName = _U(""),
		UGArray<UGString> arrSrcFieldNames = UGArray<UGString>(), 
		UGArray<UGString> arrDesFieldNames = UGArray<UGString>());

	//CHENZhao 2009.03.19 重新实现的Append族，速度慢，不可靠，慎用
	//! \brief 向数据集追加记录。
	virtual ENGINE_APIF UGbool AppendGeoOnly(UGRecordset* pSrcRcdset);
	//! \brief 向数据集追加记录。
	virtual ENGINE_APIF UGbool AppendNormal(UGRecordset* pSrcRcdset);
	//! \brief 向数据集追加记录。保留SmID，如冲突则删掉之前的。
	virtual ENGINE_APIF UGbool AppendWithSmID(UGRecordset* pSrcRcdset);
	//! \brief 向数据集追加记录。可选择不同列对应关系。
	virtual ENGINE_APIF UGbool AppendFields(UGRecordset* pSrcRcdset, UGStrings& dstFields, UGStrings& srcFields);
	//! \brief 向数据集追加记录,按列。已废弃。
	virtual ENGINE_APIF UGbool AppendByColumn(UGRecordset* pSrcRcdset, UGStrings& dstFields, UGStrings& srcFields);

	//! \brief 向数据集中追加列
	//! \param pSrcDataset		源数据集
	//! \param strSrcLinkField	源数据集与目标数据集所关联的字段
	//! \param strDestLinkField 
	//! \param arrSrcFields		源数据集要追加到目标数据集的列名称
	//! \param arrDestFields	所追加列在目标数据集中的名称
	//! \return 追加成功返回TRUE，失败返回FALSE
	virtual ENGINE_APIF UGbool AppendFields(UGDatasetVector* pSrcDataset, UGString strSrcLinkField,
		UGString strDestLinkField, UGArray<UGString>& arrSrcFields, 
		UGArray<UGString>& arrDestFields, UGbool bShowProgress = FALSE);
	
	//! \brief 检查在数据集追加行时指定的源和目标字段名集合是否合法
	//! \param pSrcDataset			源数据集
	//! \param arrSrcFieldNames		源数据集要追加到目标数据集的列名称
	//! \param arrDesFieldNames		所追加列在目标数据集中的名称
	//! \param srcCopyFieldInfos	得到源数据集中合法字段信息
	//! \param desCopyFieldInfos	得到目标数据集中合法字段信息
	//! \param arrBinaryFieldIndex	合法字段中二进制字段的索引
	//! \return	指定的源和目标列名集合合法返回TRUE，否则返回FALSE
	virtual ENGINE_APIF UGbool FieldsAppendAble(UGRecordset* pSrcRecordset,
		UGArray<UGString>& arrSrcFieldNames, UGArray<UGString>& arrDesFieldNames, 
		UGFieldInfos& srcCopyFieldInfos, UGFieldInfos& desCopyFieldInfos,	
		UGArray<UGint>& arrBinaryFieldIndex);

	//! \brief 检查源字段类型是否与目标字段相匹配，在矢量数据集追加时使用
	//! \brief srcField 源字段类型
	//! \brief desField 目标字段类型
	//! \return 返回检查结果
	virtual ENGINE_APIF UGbool CheckFieldTypeIsMatch(UGFieldInfo::FieldType srcFieldType, 
		UGFieldInfo::FieldType desFieldType);
	
	ENGINE_APIF UGint  GetEventType();
	const ENGINE_APIF UGEventProperty& GetEventProperty();
	ENGINE_APIF void SetEventProperty(const UGEventProperty& EventProperty);


	//! \brief 返回记录集个数。
	//! \return 记录集个数。
	//##ModelId=482030530199
	virtual ENGINE_APIF UGint GetRecordsetCount();

	//! \brief 通过记录集序号释放记录集内存空间。
	//! \param nIndex 记录集序号[in]。
	//! \return 是否释放成功，成功返回TRUE，失败返回FALSE。
	//##ModelId=4820305301A8
	virtual ENGINE_APIF UGbool ReleaseRecordset(UGint nIndex);
	
	//! \brief 通过记录集指针释放记录集内存空间。s
	//! \param *pRecordset 记录集指针[in]。
	//! \return 是否释放成功，成功返回TRUE，失败返回FALSE。
	//##ModelId=4820305301AB
	virtual ENGINE_APIF UGbool ReleaseRecordset(UGRecordset *pRecordset);
#if !defined SYMBIAN60 /*&& !defined  OS_ANDROID && !defined (IOS)*/
	//! \brief 取出数据集中某行特征要素。
	//! \param nID 数据集记录ID号[in]。
	//! \param pFeature 特征要素指针[in|out]在函数内分配内存,外面负责删除，否则会有内存泄漏。
	//! \return 成功返回Ture，失败返回 False。
	//##ModelId=48203053012A
	virtual ENGINE_APIF UGbool GetFeature(UGint nID, UGFeature*& pFeature);	

	//! \brief 将特征要素更新到数据集中。
	//! \param pFeature 特征要素指针[in]。
	//! \return 是否保存成功，成功返回TRUE，失败返回FALSE。
	//##ModelId=48203053012D
	virtual ENGINE_APIF UGbool UpdateFeature(const UGFeature* pFeature);
	
	//! \brief 将特征要素追加到数据集未尾。
	//! \param pFeature 特征要素指针[in]。
	//! \return 是否追加成功，成功返回TRUE，失败返回FALSE。
	//! \remarks 追加时特征要素关联的数据集记录ID将不起作用。
	//##ModelId=482030530139
	virtual ENGINE_APIF UGbool AddFeature(const UGFeature* pFeature);
	
	//! \brief 将特征要素从数据集中删除。
	//! \param nID 数据集记录ID号[in]。
	//! \return 是否删除成功，成功返回TRUE，失败返回FALSE。
	//##ModelId=48203053013C
	virtual ENGINE_APIF UGbool DeleteFeature(UGint nID);

	//! \brief 矢量数据集能力描述：Provider本身是否支持相关查询
	virtual UGbool IsSupportQueryType(UGQueryDef::QueryType queryType) const;


#endif

public:

	//! \brief 建立空间索引
	//! \remarks 此方法只能用来建立四叉树索引和R树索引,图幅索引见其他的函数,如果是IDXNone
	//!          那么默认重建四叉树索引和R树索引
	//##ModelId=482030530261
	virtual ENGINE_APIF UGbool BuildSpatialIndex(UGSpatialIndexInfo  &spatial);
	
	//! \brief 清除空间索引,为没有索引的状态
	//##ModelId=482030530268
	virtual ENGINE_APIF UGbool DropSpatialIndex();

	//! \brief 根据当前索引状态重建索引
	//! \param *pDataset [in]。
	//! \return
	//! \remarks
	//! \attention 
	//##ModelId=482030530264
	virtual ENGINE_APIF UGbool ReBuildSpatialIndex();
	
	//! \brief 脏数据的空间索引更新
	//! \param *pDataset [in]。
	//! \return 。
	//! \remarks 。
	//! \attention 。
	//##ModelId=482030530266
	virtual ENGINE_APIF UGbool UpdateSpatialIndex();
	
	//! \brief 是否需要重建空间索引
	//! \remarks 规定:如果没有索引返回FALSE,有索引看索引的情况
	//##ModelId=482030530280
	virtual ENGINE_APIF UGbool IsSpatialIndexDirty();

	//! \brief 对面数据集中所有的Geometry对象计算顶点序列，并存储为二进制字段（系统字段）；并设置数据集的顶点索引标记为"可用"
	//! \remarks 仅支持二维面、三维面数据集
	virtual UGbool ReBuildVertexSeq();

	//! \brief 对面数据集中顶点序列值为空的Geometry对象计算顶点序列，并存储；并设置数据集的顶点索引标记为"可用"
	//! \remarks 仅支持二维面、三维面数据集
	virtual UGbool BuildVertexSeq();

	//! \brief 删除顶点序列后，数据集删除存储顶点索引的二进制字段，并设置数据集的顶点索引标记为"无"
	//! \remarks 仅支持二维面、三维面数据集
	virtual UGbool DropVertexSeq();

public:

	virtual ENGINE_APIF UGbool CanBeClose();
	//! \brief 返回数据集类型
	//##ModelId=483BB70B00BB
	virtual ENGINE_APIF UGDataset::DatasetType GetType() const;

	//! \brief 返回数据集的维数
	//##ModelId=48203053008C
	virtual ENGINE_APIF UGint GetDimension();

	//! \brief 返回数据集名(可以和表名不同)
	//##ModelId=48203053009C
	virtual ENGINE_APIF UGString GetName();

	//! \brief 返回数据集对应表名
	//##ModelId=48203053009E
	virtual ENGINE_APIF UGString GetTableName();

	//! \brief 设置数据集对应的数据表的名字
	//##ModelId=4820305300AB
	ENGINE_APIF void SetTableName(const UGString& strTableName);
	
	//! \brief 获取数据集描述信息
	//##ModelId=4820305300AD
	virtual ENGINE_APIF UGString GetDescription() const;

	//! \brief 设置数据集描述信息
	//##ModelId=4820305300BB
	virtual ENGINE_APIF UGbool SetDescription(const UGString& /*strDesc*/);

	//! \brief 获取数据集附加信息
	//##ModelId=4820305300AD
	virtual ENGINE_APIF UGString GetExtInfo() const;

	//! \brief 设置数据集附加信息
	//##ModelId=4820305300BB
	virtual ENGINE_APIF UGbool SetExtInfo(const UGString& /*strExtInfo*/);


	//! \brief 返回最小高程
	//##ModelId=4820305300BE
	virtual ENGINE_APIF UGdouble GetMinZ();
	
	//! \brief 设置最小高程
	//##ModelId=4820305300CB
	virtual ENGINE_APIF void SetMinZ(UGdouble d);
	
	//! \brief 返回最大高程
	//##ModelId=4820305300CE
	virtual ENGINE_APIF UGdouble GetMaxZ();
	
	//! \brief 设置最大高程
	//##ModelId=4820305300DA
	virtual ENGINE_APIF void SetMaxZ(UGdouble d);
	
	//! \brief 判断是否是矢量数据集
	//##ModelId=4820305300DD
	virtual ENGINE_APIF UGbool IsVector();

	//##ModelId=4820305300EA
	virtual ENGINE_APIF UGbool IsLinkTable();

	//通过某些关键字判断是否是静态查询
	//##ModelId=483BB70802FC
	ENGINE_APIF UGbool IsStatisticalQuery(const UGQueryDef& querydef);

	//! \brief 判断是否是topo数据集
	//##ModelId=4820305300EC
	virtual ENGINE_APIF UGbool IsTopoDataset();

	//! \brief 判断是否是栅格数据集
	//##ModelId=4820305300EE
	virtual ENGINE_APIF UGbool IsRaster();

	//! \brief 判断是否是网络矢量数据集
	//##ModelId=4820305401D4
	virtual ENGINE_APIF UGbool IsWebVector();

	//! \brief 判断是否是关系类数据集
	virtual ENGINE_APIF UGbool IsRelClass();

	//! \brief 返回数据集的范围
	//##ModelId=4820305300FA
	virtual ENGINE_APIF const UGRect2D& GetBounds();
	
	//! \brief 设置数据集的范围
	//##ModelId=4820305300FC
	virtual ENGINE_APIF void SetBounds(const UGRect2D& r);

	//! \brief 直接从内存中返回对象个数,速度比较快,
	//!        但不能保证正确,通过DatsetInfo获取
	//##ModelId=48203053010E
	virtual ENGINE_APIF UGint GetObjectCountDirectly();
	
	//! \brief 返回数据集中对象个数,速度慢,但值比较正确,
	//!        通过Register表获取
	//##ModelId=48203053011A
	virtual ENGINE_APIF UGint GetObjectCount();

	//! \brief 返回数据集中对象个数,速度慢,但值比较正确,
	//!        通过Register表获取
	//##ModelId=48203053011C
	virtual ENGINE_APIF void SetObjectCount(UGint nCount);

	//! \brief 检查记录数与Register表中的是否一致，如果不一致会自动修复。
	virtual ENGINE_APIF UGbool CheckObjectCount();

	enum TileIndexStatus{INDEX_TYPE_NOT_MATCH, INDEX_TABLE_NOT_EXIST, INDEX_DATASET_NOT_EXIST};
	//! \brief 检查图库索引情况。返回状态的数组，为空说明没有问题。
	virtual ENGINE_APIF UGArray<TileIndexStatus> CheckTileIndex();

	//! \brief 得到未被占用的字段名
	//##ModelId=4820305301C6
	virtual ENGINE_APIF UGString GetUnoccupiedFieldName(const UGString& strFieldName);

	//! \brief 获取矢量数据集信息
	//! \return UGDatasetVectorInfo *
	//##ModelId=482030530148
	ENGINE_APIF UGDatasetVectorInfo * GetInfo();

	//! \brief 释放所有记录集
	//##ModelId=4820305301B5
	ENGINE_APIF void ReleaseAllRecordsets();

	//! \brief 根据给定的ID数组删除记录。
	//! \param pIDs 给定的ID[in]。
	//! \param nCount 要删除的ID的个数[in]。
	//! \return 是否成功删除。
	virtual UGbool DeleteRecords(const UGint* pIDs,UGint nCount);	
	
	//! \brief 真正的SQL查询记录个数,更新Register表
	//##ModelId=4820305301F5
	virtual ENGINE_APIF UGbool ComputeRecCount();

	//CHENZhao 在VAT里用到，设置一个数据集为子数据集
	//! \brief 设置一个数据集为子数据集
	virtual ENGINE_APIF UGbool SetIsSub(UGbool isSub);
	//! \brief 设置子数据集的ParentID
	virtual ENGINE_APIF UGbool SetParentID(UGint id);

	//! \brief 删除表中所有数据。
	//! \return 是否删除成功，成功返回TRUE，失败返回FALSE。
	//! \remarks 清空表后表中的字段仍然保留。
	//##ModelId=482030500131
	virtual ENGINE_APIF UGbool Truncate();


	//! \brief 精确计算经纬度下的面积
	//! \param 保存计算结果的字段,如果不存在则会创建,如果已存在,则需要字段类型为Double,否则计算失败
	//! \remark 仅适用于面数据集,且为经纬度坐标系的数据,否则返回失败
	virtual UGbool CalcGeographicArea(const UGString &strFieldName);

	//! \brief 精确计算经纬度下的长度(面数据集为周长)
	//! \param 保存计算结果的字段,如果不存在则会创建,如果已存在,则需要字段类型为Double,否则计算失败
	//! \remark 仅适用于线和面数据集,且为经纬度坐标系的数据,否则返回失败
	virtual UGbool CalcGeographicLength(const UGString &strFieldName);


//////////////////////////////////////////////////////////////////////////
//		以下是在 OGDC 的基础上增加的方法
//////////////////////////////////////////////////////////////////////////
public:
	
	//! \brief  返回空间数据编码方式
	//##ModelId=482030530109
	virtual ENGINE_APIF UGDataCodec::CodecType GetCodecType();
	
	//! \brief  设置空间数据编码方式,创建数据集的时候设置,如果有数据操作不能修改
	//##ModelId=48203053010B
	virtual ENGINE_APIF UGbool SetCodecType(UGDataCodec::CodecType c);

	//! \brief  返回数据集的选项信息(用四字节的整型数据代表一些属性)
	//##ModelId=482030530128
	virtual ENGINE_APIF UGint GetOptions();

	//! \brief  判断数据集是否有某个选项信息
	//##ModelId=482030530149
	virtual ENGINE_APIF UGbool HasFlag(UGint nOption) const;

	//! \brief  设置数据集的属性,一般不可以直接修改
	//##ModelId=482030530157
	virtual ENGINE_APIF void SetFlag(UGint nOption,UGbool bHas);

	//! \brief  自定义版本查询 add by jinagzb
	//! \remarks 只支持静态查询
	virtual ENGINE_APIF UGRecordset* CustomVersionQuery(UGint nSeriesID, UGint nLastActionID, const UGQueryDef& querydef);

	//! \brief  查询通用入口
	//##ModelId=482030530167
	virtual ENGINE_APIF UGRecordset* Query(const UGQueryDef& querydef);

	//! \brief  外挂属性表查询
	//##ModelId=48203053016A
	virtual ENGINE_APIF UGRecordset* Query2(UGLinkItem &linkitem);

	//! \brief  获取最大空间对象的字节大小
	//##ModelId=48203053016D
	virtual ENGINE_APIF UGint GetMaxGeoSize();

	//! \brief  设置最大空间对象的字节大小
	//##ModelId=482030530177
	virtual ENGINE_APIF UGbool SetMaxGeoSize(UGint nMaxGeoSize);


	//! \brief 获取当前数据集中的最大SMID信息
	virtual ENGINE_APIF UGint GetMaxID(){return GetObjectCount();};

	//! \breif 获取一个新的SMID资源
	virtual ENGINE_APIF UGint GetNewID(){return GetMaxID() + 1;};

	//! \brief  获取父数据集指针
	//##ModelId=48203053018C
	ENGINE_APIF UGDataset* GetParentDataset() const;

	//! \brief  获取子数据集指针
	//##ModelId=48203053018E
	ENGINE_APIF UGDatasetVector * GetChildDataset() const;

	//! \brief  设置父数据集指针
	//##ModelId=482030530197
	ENGINE_APIF void SetParentDataset(UGDatasetVector* pDatasetVector);

	//! \brief  返回指定索引的数据集指针
	//##ModelId=4820305301A5
	virtual ENGINE_APIF UGRecordset* GetRecordsetAt(UGint nIndex);

	//UGSpatialQuery中，通过OGDC查出来的Recordset需要数据集统一管理
	UGbool AddRecordset(UGRecordset *pRecordset);

	//! \brief  得到数据集中空间索引的BOUNDS
	//##ModelId=4820305301B6
	ENGINE_APIF UGRect2D GetIndexBounds() const;

	//! \brief  设置数据集中索引的BOUNDS
	//##ModelId=4820305301B8
	ENGINE_APIF void SetIndexBounds(const UGRect2D& rc2Bounds);

	//! \brief  得到图库索引图的名字	
	//##ModelId=4820305301C9
	virtual ENGINE_APIF UGString GetMiniatureDtName();

	//! \brief  设置数据集字符编码方式
	//##ModelId=4820305301DA
	virtual ENGINE_APIF UGbool SetCharset(UGString::Charset c);
	
	//##ModelId=4820305301E4
	ENGINE_APIF UGbool PJConvert( UGRefTranslator *pRefTranslator );		//投影转换
	//##ModelId=4820305301E6
	ENGINE_APIF UGbool PJForward( UGPrjCoordSys *pPrjCoordSys );			//地理坐标到投影坐标,假定Datum相同.
	//##ModelId=4820305301E8
	ENGINE_APIF UGbool PJInverse( UGPrjCoordSys *pPrjCoordSys );			//投影坐标到地理坐标,假定Datum相同.

	//! \brief  获取缓存文件的临时路径
	//##ModelId=4820305301FB
	ENGINE_APIF UGString GetCacheTempPath() const;

	//! \brief  设置缓存文件的临时路径
	//##ModelId=482030530203
	ENGINE_APIF void SetCacheTempPath(const UGString& strTempPath);

	//! \brief  返回索引表的名字
	//##ModelId=482030530205
	virtual ENGINE_APIF UGString GetIndexTableName();

	//! \brief  设置索引表的名字
	//##ModelId=482030530207
	ENGINE_APIF void SetIndexTableName(const UGString& strIndexTable);
	
	//! \brief  容限是否空(0.0) 
	//##ModelId=482030530209
	ENGINE_APIF UGbool IsToleranceEmpty() const ;

	//! \brief  使用默认容限
	//##ModelId=482030530213
	//CHENZhao 08.12.01 改所有设置容限的函数返回值类型为UGbool
	virtual ENGINE_APIF UGbool SetToleranceToDefault();

	//! \brief  设置容限为空
	//##ModelId=482030530215
	ENGINE_APIF void EmptyTolerance();

	//! \brief  设置最小多边形面积的范围
	//##ModelId=482030530216
	ENGINE_APIF UGbool SetToleranceSmallPolygon(UGdouble dNewValue);

	//! \brief  得到最小多边形面积的范围
	//##ModelId=482030530218
	ENGINE_APIF UGdouble GetToleranceSmallPolygon() const ;

	//! \brief  设置短悬线容限
	//##ModelId=482030530222
	ENGINE_APIF UGbool SetToleranceDangle(UGdouble dNewValue);

	//! \brief  得到短悬线容限
	//##ModelId=482030530224
	ENGINE_APIF UGdouble GetToleranceDangle() const;

	//! \brief  设置节点容限
	//##ModelId=482030530226
	ENGINE_APIF UGbool SetToleranceNodeSnap(UGdouble dNewValue);

	//! \brief  得到节点容限
	//##ModelId=482030530228
	ENGINE_APIF UGdouble GetToleranceNodeSnap() const;

	//! \brief  设置曲线容限
	//##ModelId=48203053022A
	ENGINE_APIF UGbool SetToleranceGrain(UGdouble dNewValue);

	//! \brief  得到曲线容限
	//##ModelId=482030530232
	ENGINE_APIF UGdouble GetToleranceGrain() const;

	//! \brief  设置合并假节点容限
	//##ModelId=482030530234
	ENGINE_APIF UGbool SetToleranceExtend(UGdouble dNewValue);

	//! \brief  得到合并假节点容限
	//##ModelId=482030530236
	ENGINE_APIF UGdouble GetToleranceExtend() const;
	
	//! \brief  设置数据集的选项信息
	//##ModelId=482030530238
	ENGINE_APIF void SetOptions(UGint nOptions);
#if !defined SYMBIAN60 /*&& !defined  OS_ANDROID && !defined (IOS)*/
	//added by xielin 2007-05-23 
	//##ModelId=48203053023A
	//! \brief  设置数据集的选项信息
	void RegisterToDataset(UGDataHistory* pDataHistory);
	//##ModelId=482030530242
	//! \brief  设置数据集的选项信息
	void UnRegisterFromDataset(UGDataHistory* pDataHistory);
#endif

	//! \brief  如果参与了topo 可以获得topo数据集指针
	//##ModelId=482030530244
	virtual ENGINE_APIF UGDataset * GetTopoAdscriptionDT();

	//! \brief  For Tin 数据集
	//##ModelId=482030530246
	virtual ENGINE_APIF UGbool CreateSubDataset(UGDatasetVectorInfo & vInfo);

	//! \brief 通过子数据集名称删除子数据集
	//##ModelId=482030530249
	virtual ENGINE_APIF UGbool DeleteSubDataset(UGString &strName);

	//! \brief 通过真实宽度，和设备宽度，来计算显示Tin金字塔的那一层数据
	//##ModelId=48203053024C
	ENGINE_APIF UGDatasetVector * GetTinLayer(UGint nWidth,UGint nDeviceWidth);
#if !defined SYMBIAN60 /*&& !defined  OS_ANDROID */
	//! \brief 获取R树
	//##ModelId=483BB70B0157
	UGDBRTree* GetDBRTree();
#endif
	//! \brief 查询大表图库中一个图幅的数据
	//! \param nLibTileID [in]。
	//! \param arFields [in]。
	//! \param dGranule [in]。
	//! \return UGRecordset
	//! \remarks 如果dGraunle<=0，那么就不采用过滤方式,反之过滤
	//! \attention 。
	//##ModelId=48203053026A
	virtual ENGINE_APIF UGRecordset* QueryWithLibTileID(UGint nLibTileID,
		UGArray<UGString> & arFields,UGdouble dGranule);

	//! \brief 通过矩形范围查询图幅序号
	//! \param rc2Bounds [in]。
	//! \param arLibTileIDs [out]。
	//! \return UGbool
	//! \remarks 。
	//! \attention 。
	//##ModelId=482030530274
	virtual ENGINE_APIF UGbool GetLibTileIDs(const UGRect2D& rc2Bounds,
		UGArray<UGint>& arLibTileIDs);
	
	//! \brief 得到一个图幅的信息
	//! \param nTileID [in]。
	//! \param rc2TileBounds [out]。
	//! \param nRecCount [out]。
	//! \param nVersion [out]。
	//! \return 。
	//! \remarks 。
	//! \attention 。
	//##ModelId=482030530278
	virtual ENGINE_APIF UGbool GetLibTileInfo(UGint nTileID,UGRect2D& rc2TileBounds,
		UGint& nRecCount,UGint& nVersion);

	//SpatialIndex需要用到的方法
	//! \brief 从数据库中读取当前数据集的Bounds信息
	//! \remarks 此函数与CDatasetVector::GetBounds有所区别，此函数是从数据库中读取，得到的是最新的Bounds，而后者是直接从内存中读取m_DatasetInfo中存储的Bounds信息，速度要快得多
	//! \sa	CDatasetVector::GetBounds
	//##ModelId=483BB70B015E
 	virtual ENGINE_APIF UGRect2D GetBoundsDirectly();

	//! \brief 开放空间索引对象
	//! \param nOption	   查询选项[in]
	//! \param dbTolerance 容限[in]
	//! \param pGeo        查询范围对象[in]
	//! \param aryInnerIDs 所有在查询范围内的对象ID[out]
	//! \param aryOuterIDs 所有在查询范围外的对象ID[out]
	//! \param aryMaybeIDs 所有与查询范围相交的对象ID[out]
	//! \return
	//! \remarks
	//! \attention
	ENGINE_APIF UGbool IndexbagQuery(SpatialQueryOption nOption,UGdouble dbTolerance,UGGeometry *pGeo,
		UGArray<UGint> &aryInnerIDs,UGArray<UGint> &aryOuterIDs,UGMaybeItems &aryMaybeItems);
	//! \brief 判断追加时是不是属性表到几何
	//! \param 目标数据集
	//! \param 源记录集
	virtual ENGINE_APIF UGbool TabularAppendMatch(UGDatasetVector* dst, UGRecordset* src);

	UGSpatialIndex* GetSpaitalIndexObect(){return m_pSpatialIndex;};

	//! \brief 计算极值
	//! \param strExpression		查询的字段表达式[in]
	//! \param JoinItems			查询的外部关联条件[in]
	//! \param bIsSupportNegative	是否支持负值[in]
	//! \param dMinSum				查询的最小值[in/out]
	//! \param dMaxSum				查询的最大值[in/out]
	//! \remarks 二三维中计算字段极值，共用接口，放到Engine来处理吧
	UGbool CalculateExtremum(const UGArray<UGString>& strExpression,const UGArray<UGJoinItem>& JoinItems,UGbool bIsSupportNegative,UGdouble& dMinSum,UGdouble& dMaxSum);

	//! \brief 设置修改数据集后的回调函数地址
	void SetAffterDatasetModifiedFunction(AffterDatasetModifiedProc pffterDatasetModifiedProc,void* pLayerDataset);

	//! \brief 获取修改数据集后的回调函数地址
    AffterDatasetModifiedProc GetAffterDatasetModifiedFunction();

	//\brief 获取回调函数所用的数据集图层的地址
	void* GetLayerDatasetPointer();
	//! \brief 通过索引进行粗查询
	//! \param *pBounds 查询bounds[in]
	//! \param aryInnerIDs 落在bounds范围内的对象id数组[out]
	//! \param aryMaybeItems 和bounds相交的对象的id数组[out]
	//! \param aryOuterIDs 落在bounds外的对象的id数组 [out]
	//! \param bNeedOuterIDs 是否返回落在bounds外的对象的id数组[in]
	//! \param dbTolerance 容限[in]
	virtual ENGINE_APIF UGbool QueryBySpatialIndex(UGGeoRegion& geoRegion,
		UGArray<UGint>& aryInnerIDs,UGArray<UGint>& aryMaybeIDs,
		UGArray<UGint>& aryOuterIDs,UGbool bNeedOuterIDs);
protected:
	//! brief 初始化空间索引对象
	//##ModelId=483BB70B0160
	virtual ENGINE_APIF UGbool InitSpatialIndex();

	//!brief 刷新数据集的选项信息
	virtual ENGINE_APIF UGbool RefreshOption();

	//! \brief 图幅索引空间查询 
	//! \param pGeo 面对象[in]
	//! \param aryInnerIDs  [out]
	//! \param aryMaybeItems	[out]
	//! \param aryOuterIDs	[out]
	//! \param nOption	[in]
    virtual ENGINE_APIF UGbool LibTileSpatialQuery(UGGeometry *pGeo,
		UGArray<UGint> &aryInnerIDs, UGMaybeItems &aryMaybeItems,
		UGArray<UGint> &aryOuterIDs, SpatialQueryOption nOption, 
		UGdouble dbTolerance);
	
	//! \brief R树索引空间查询 
	//! \param pGeo 面对象[in]
	//! \param aryInnerIDs  [out]
	//! \param aryMaybeItems	[out]
	//! \param aryOuterIDs	[out]
	//! \param nOption	[in]
	virtual ENGINE_APIF UGbool RTreeSpatialQuery(UGGeometry *pGeo,
		UGArray<UGint> &aryInnerIDs, UGMaybeItems &aryMaybeItems,
		UGArray<UGint> &aryOuterIDs, SpatialQueryOption nOption,
		UGdouble dbTolerance);
	
	//! \brief 多级网格索引空间查询 
	//! \param pGeo 面对象[in]
	//! \param aryInnerIDs  [out]
	//! \param aryMaybeItems	[out]
	//! \param aryOuterIDs	[out]
	//! \param nOption	[in]
	//! \remarks pGeo为二维对象时，aryInnerIDs是被pGeo完全包含的对象ID；aryMaybeIDs是与pGeo相交的ID，关系需要进一步判断；aryOuterIDs是一定在pGe外部的对象ID
	//!          pGeo为一维对象时，aryInnerIDs为空；aryMaybeIDs是与pGeo相交的ID，关系需要进一步判断；aryOuterIDs是与pGeo没有交点对象ID
	//!          pGeo为零维对象时，aryInnerIDs为空；aryMaybeIDs是点落在对象范围内的对象ID，aryOuterIDs是点落在对象范围外的对象ID
	virtual ENGINE_APIF UGbool DynamicSpatialQuery(UGGeometry *pGeo,
		UGArray<UGint> &aryInnerIDs, UGMaybeItems &aryMaybeItems,
		UGArray<UGint> &aryOuterIDs, SpatialQueryOption nOption, 
		UGdouble dbTolerance);
public:
	//! \brief  优化器记录数优化参数
	//##ModelId=482030530285
	UGint m_nOptimizeCount;
	//! \brief  优化器面积优化参数
	//##ModelId=482030530286
	UGdouble m_dOptimizeRatio;
	//! \brief  最大空间对象的字节大小
	//##ModelId=482030530290
	UGint m_nMaxGeometrySize;
	//! \brief  最大符号的字节大小
	//##ModelId=482030530291
	UGint m_nMaxSymbolSize;
	//! \brief  数据集的子数据集指针
	//##ModelId=482030530292
	UGSubDtArray m_arySubDataset;
	//! \brief  矢量数据集信息
	//##ModelId=482030530293
	UGDatasetVectorInfo m_DatasetInfo;
	//! \brief  TIN数据集子数据集指针

	//! \brief  数据集关联查询的外部数据源
	//##ModelId=482030530294
	UGArray<UGDataSource *> m_aryLinkDatasource;

	UGEventProperty* m_pEventProperty; 
protected:
	//! \brief 记录集指针的集合，打开的所有记录集必须放在这里，
	//!        否则不知道怎么释放
	//##ModelId=482030530295
	UGArray<UGRecordset*> m_Recordsets;
	//! \brief 缓存文件的临时路径
	//##ModelId=48203053029F
	UGString m_strCacheTempPath;

	//! \brief 父数据集的指针
	//##ModelId=4820305302A1
	UGDataset * m_pParentDataset;

	//! \brief 索引表的名字
	//##ModelId=4820305302AF
	UGString m_strIndexTable;

	//added by xielin 2007-05-22
	//##ModelId=4820305302B0
	UGArray<ValidDataHistory> m_aryValidDataHistory;

	//##ModelId=4820305302B2
	UGSpatialIndex* m_pSpatialIndex;

	AffterDatasetModifiedProc ms_pAffterDatasetModifiedProc;

	void* m_pLayerDataset;
};

}

#endif

