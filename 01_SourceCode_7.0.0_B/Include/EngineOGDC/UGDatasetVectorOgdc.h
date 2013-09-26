// UGDatasetVectorOgdc.h: interface for the UGDatasetVectorOgdc class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_UGDATASETVECTOROGDC_H__296CEA92_1643_444F_82CC_1DA2F9B31DB7__INCLUDED_)
#define AFX_UGDATASETVECTOROGDC_H__296CEA92_1643_444F_82CC_1DA2F9B31DB7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "OGDC/OgdcDatasetVector.h"
#include "Engine/UGDatasetVector.h"
#include "UGRecordsetOgdc.h"

namespace UGC {

class UGDataSourceOgdc;

//##ModelId=483BB70A0157
class ENGINEOGDC_API UGDatasetVectorOgdc : public OgdcDatasetVector  
{
public:
	//##ModelId=483BB70A0168
	UGDatasetVectorOgdc();
	//##ModelId=483BB70A0169
	virtual ~UGDatasetVectorOgdc();

public:
	//##ModelId=483BB70A016B
	virtual OgdcBool Open();	
	
	//! \brief 关闭数据集。
	//! \return 是否成功关闭数据集，成功返回TRUE，失败返回FALSE。
	//##ModelId=483BB70A016D
	virtual void Close();	

	//! \brief 判断数据集是否已经打开。
	//! \return 打开返回TRUE，否则返回FALSE。
	//##ModelId=483BB70A0178
	virtual OgdcBool IsOpen() const;
	
	//! \brief 获取数据集类型。
	//! \return 数据集类型枚举值。
	//##ModelId=483BB70A017A
	virtual OgdcInt GetType() const;	
	
	//! \brief 获取数据集名。
	//! \return 数据集名。
	//! \remarks 数据集名可以和表名不同。
	//##ModelId=483BB70A017C
	virtual OgdcString GetName();
	
	//! \brief 重命名数据集。
	//! \param strNewName 新的数据集名[in]。
	//! \return 是否成功重命名数据集，成功返回TRUE，失败返回FALSE。
	//! \remarks 只改变数据集名,表名不变。
	//##ModelId=483BB70A0187
	virtual OgdcBool Rename(const OgdcString& strNewName);		

	//! \brief 判断当前数据集是否可编辑。
	//! \return 可编辑返回TRUE，不可返回FALSE。
	//##ModelId=483BB70A018A
	virtual OgdcBool CanUpdate();	
	
	//! \brief 返回数据集的风格维数。
	//! \return 数据集的维数。点、线、面风格为0、1、2维其他为-1维
	//##ModelId=483BB70A018C
	virtual OgdcInt GetStyleDimension();	
	
	//! \brief 判断数据集是否是栅格数据集
	//! \return 数据集是栅格数据集返回TRUE，否则返回FALSE。
	//##ModelId=483BB70A0197
	virtual OgdcBool IsRaster();	
	
	//! \brief 获取数据集的地理范围。
	//! \return 数据集的地理范围。
	//##ModelId=483BB70A0199
	virtual OgdcRect2D GetBounds();	
	
	//! \brief 设置数据集的地理范围。
	//! \param rc2Bounds 数据集的地理范围[in]。
	//##ModelId=483BB70A019B
	virtual void SetBounds(const OgdcRect2D& rc2Bounds);	
	
	//! \brief 将数据集各种信息保存到数据库中。
	//! \return 是否成功保存，成功返回TRUE，失败返回FALSE。
	//##ModelId=483BB70A01A5
	virtual OgdcBool SaveInfo();	
	
	//! \brief 刷新数据集信息。
	//! \return 是否成功刷新，成功返回TRUE，失败返回FALSE。
	//! \remarks 从数据库中读取数据集的各种属性，刷新当前数据集的信息。
	//##ModelId=483BB70A01A7
	virtual OgdcBool RefreshInfo();	

	//! \brief 获取数据集中对象个数。
	//! \param  [in]。
	//! \return 对象个数。
	//! \remarks 速度慢,但值比较正确。
	//! \attention 通过Register表获取。
	//##ModelId=483BB70A01A9
	virtual OgdcInt GetObjectCount();

	//! \brief 返回记录集个数。
	//! \return 记录集个数。
	//##ModelId=483BB70A01B5
	virtual OgdcInt GetRecordsetCount();	
	
	//! \brief 通过记录集指针释放记录集内存空间。
	//! \param *pRecordset 记录集指针[in]。
	//! \return 是否释放成功，成功返回TRUE，失败返回FALSE。
	//##ModelId=483BB70A01B7
	virtual OgdcBool ReleaseRecordset(OgdcRecordset *pRecordset);	

	//! \brief 释放所有记录集
	//##ModelId=483BB70A01BA
	virtual void ReleaseAllRecordsets();	

	//! \brief 取出数据集中某行特征要素。
	//! \param nID 数据集记录ID号[in]。
	//! \return 行特征要素指针。
	//##ModelId=483BB70A01BC
	virtual OgdcFeature* GetFeature(OgdcInt nID);	

	//! \brief 将特征要素更新到数据集中。
	//! \param pFeature 特征要素指针[in]。
	//! \return 是否保存成功，成功返回TRUE，失败返回FALSE。
	//##ModelId=483BB70A01C5
	virtual OgdcBool UpdateFeature(const OgdcFeature* pFeature);
	
	//! \brief 将特征要素追加到数据集未尾。
	//! \param pFeature 特征要素指针[in]。
	//! \return 是否追加成功，成功返回TRUE，失败返回FALSE。
	//! \remarks 追加时特征要素关联的数据集记录ID将不起作用。
	//##ModelId=483BB70A01C8
	virtual OgdcBool AddFeature(const OgdcFeature* pFeature);	

	//! \brief 将特征要素从数据集中删除。
	//! \param nID 数据集记录ID号[in]。
	//! \return 是否删除成功，成功返回TRUE，失败返回FALSE。
	//##ModelId=483BB70A01CB
	virtual OgdcBool DeleteFeature(OgdcInt nID);	
	
	//! \brief 通过ID数组删除数据集中的记录。
	//! \param pIDs ID数组指针[in]。
	//! \param nCount ID数组元素个数[in]。
	//! \return 成功删除返回TRUE，失败返回FALSE。
	//##ModelId=483BB70A01D4
	virtual OgdcBool DeleteFeatures(const OgdcInt* pIDs, OgdcInt nCount);	
	
	//! \brief 删除表中所有数据。
	//! \return 是否删除成功，成功返回TRUE，失败返回FALSE。
	//! \remarks 清空表后表中的字段仍然保留。
	//##ModelId=483BB70A01D8
	virtual OgdcBool Truncate();	

	//! \brief 根据当前索引状态重建索引
	//! \return 是否重建成功，成功返回TRUE，失败返回FALSE。
	//##ModelId=483BB70A01DA
	virtual OgdcBool BuildSpatialIndex();
	
	//! \brief 清除空间索引,为没有索引的状态
	//! \return 是否清除成功，成功返回TRUE，失败返回FALSE。
	//##ModelId=483BB70A01DC
	virtual OgdcBool DropSpatialIndex();
	
	//! \brief 是否需要重建空间索引
	//! \return 需要重建返回TRUE，不需要返回FALSE。
	//! \remarks 规定:如果没有索引返回FALSE,有索引看索引的情况
	//##ModelId=483BB70A01E4
	virtual OgdcBool IsSpatialIndexDirty();

	//! \brief 查询通用入口，得到记录集。
	//##ModelId=483BB70A01E6
	virtual OgdcRecordset* Query(const OgdcQueryDef& querydef);
	
	//! \brief 通过表达式更新字段值。
	//! \param strFieldName 更新的字段名[in]。
	//! \param strExpress 算术运算表达式字符串，
	//!        字段值是某个算术运算表达式的值，如strFieldName = Col1 + col2 * 2[in]。
	//! \param strFilter 更新字段时对数据行的过滤条件，
	//!        默认过滤条件置空，更新所有记录[in]。
	//! \return 是否更新字段值成功，成功返回TRUE，失败返回FALSE。
	//##ModelId=483BB70A01E9
	virtual OgdcBool UpdateField(
		const OgdcString& strFieldName,
		const OgdcString& strExpress,
		const OgdcString& strFilter = _U(""));	
	
	//! \brief 复制字段值,strSrcField和。
	//! \param strSrcFieldName 源字段名称[in]。
	//! \param strDestFieldName 目的字段名称[in]。
	//! \return 是否复制字段成功，成功返回TRUE，失败返回FALSE。
	//! \attention 目的字段名必须都存在且目的字段要与源字段类型匹配。
	//##ModelId=483BB70A01EE
	virtual OgdcBool CopyField(
		const OgdcString& strSrcFieldName,
		const OgdcString& strDestFieldName);	
	
	//! \brief 创建普通索引。
	//! \param strFieldNameList 创建索引的字段列表，多个字段中间用","隔开[in]。
	//! \param strIndexName 索引名[in]。
	//! \return 创建普通索引是否成功，成功返回TRUE，失败返回FALSE。
	//##ModelId=483BB70A01F5
	virtual OgdcBool CreateFieldIndex(
		const OgdcString& strFieldNameList,
		const OgdcString& strIndexName);	

	//! \brief 删除索引。
	//! \param strIndexName 索引名[in]。
	//! \return 删除索引是否成功，成功返回TRUE，失败返回FALSE。
	//##ModelId=483BB70A01F9
	virtual OgdcBool DropFieldIndex(const OgdcString& strIndexName);	

	//! \brief 查找获得索引。
	//! \param 无。
	//! \return 索引值--索引所在字段对应Map。
	virtual std::map<OgdcString,OgdcString> GetFieldIndexes();	

	//! \brief 创建多个字段。
	//! \param fieldInfos 字段描述信息数组引用[in]。
	//! \return 创建多个字段是否成功，成功返回TRUE，失败返回FALSE。
	//##ModelId=483BB70A01FC
	virtual OgdcBool CreateFields(const OgdcFieldInfos& fieldInfos);	
		
	//! \brief 通过字段名称删除字段。
	//! \param strFieldName 字段名[in]。
	//! \return 是否删除成功，成功返回TRUE，失败返回FALSE。
	//##ModelId=483BB70A01FF
	virtual OgdcBool DeleteField(const OgdcString& strFieldName);
	
	//! \brief 获取数据表中所有字段的描述信息。
	//! \param fieldInfos 数据表中所有字段的描述信息数组[out]。
	//! \param bSystemFieldExcluded 是否获取系统字段，默认不取[in]。
	//! \return 是否获取成功，成功返回TRUE，失败返回FALSE。
	//##ModelId=483BB70A0204
	virtual OgdcBool GetFieldInfos(
		OgdcFieldInfos& fieldInfos,
		OgdcBool bSystemFieldExcluded = FALSE);	
	
	//! \brief 通过字段名获取字段描述信息。
	//! \param strFieldName 字段名[in]。
	//! \param fieldInfo 字段描述信息[out]。
	//! \return 是否获取成功，成功返回TRUE，失败返回FALSE。
	//##ModelId=483BB70A0208
	virtual OgdcBool GetFieldInfo(
		const OgdcString& strFieldName,
		OgdcFieldInfo& fieldInfo);
	
	//! \brief 通过字段名设置字段信息。
	//! \param strFieldName 字段名[in]。
	//! \param fieldInfo 字段描述信息对象引用[in]。
	//! \return 是否设置成功，成功返回TRUE，失败返回FALSE。
	//##ModelId=483BB70A020C
	virtual OgdcBool SetFieldInfo(
		const OgdcString& strFieldName,
		const OgdcFieldInfo& fieldInfo);	
	
	//! \brief 统计字段值。
	//! \param strFieldName 字段名[in]。
	//! \param nMode 统计模式[in]。
	//! \return 统计值。
	//##ModelId=483BB70A0213
	virtual OgdcVariant Statistic(
		const OgdcString& strFieldName,
		OgdcRecordset::OgdcStatisticMode nMode);	
	
	//! \brief 返回数据源指针
	virtual OgdcDataSource* GetDataSource() const;
	
	//! \brief 设置数据源指针
	virtual void SetDataSource(UGDataSourceOgdc* pDataSource);

public:
	//! \brief 返回数据集对应表名
	//##ModelId=483BB70A0217
	virtual OgdcString GetTableName();	
	
	//! \brief 获取最后更新数据集的时刻。
	//! \return 最后更新数据集的时刻。
	//##ModelId=483BB70A0219
	virtual OgdcTime GetDateLastUpdated();	
	
	//! \brief 获取创建数据集的时刻。
	//! \return 创建数据集的时刻。
	//##ModelId=483BB70A021B
	virtual OgdcTime GetDateCreated();	
	
	//! \brief 判断数据集是否在打开后有过修改。
	//! \return 有过修改返回TRUE，没有返回FALSE。
	//##ModelId=483BB70A021D
	virtual OgdcBool IsModified() const;
	
	//! \brief 设置数据集是否有过修改。
	//! \param bModified 数据集是否有过修改，默认有修改[in]。
	//##ModelId=483BB70A021F
	virtual void SetModifiedFlag(OgdcBool bModified = TRUE);
	
	//! \brief 设置数据集字符编码方式
	//! \param textCodec 数据集字符编码方式[in]。
	//##ModelId=483BB70A0223
	virtual void SetCharset(OgdcString::Charset nCharset);

	//! \brief 获取数据集字符编码方式。
	//! \return 数据集字符集枚举。
	//##ModelId=483BB70A0226
	virtual OgdcString::Charset GetCharset() const;

	//! \brief 设置投影坐标系。
	//! \param coordSys [in]。
	//##ModelId=483BB70A0228
	virtual OgdcBool SetCoordSys(const OgdcCoordSys& coordSys);	

	//! \brief 得到投影坐标系。
	//##ModelId=483BB70A022B
	virtual OgdcBool GetCoordSys(OgdcCoordSys& coordSys) const;		

	//! \brief 获取数据集描述信息。
	//! \return 数据集描述信息。
	//##ModelId=483BB70A022E
	virtual OgdcString GetDescription() const;	
	
	//! \brief 设置数据集描述信息
	//! \param strDesc [数据集描述信息in]。
	//##ModelId=483BB70A0232
	virtual void SetDescription(const OgdcString& strDesc);	

	//! \brief 得到未被占用的字段名。
	//! \param strFieldName 指定的一个字段名[in]。
	//! \return 未被占用的字段名。
	//##ModelId=483BB70A0235
	virtual OgdcString GetUnoccupiedFieldName(const OgdcString& strFieldName);

	//! \brief 判断字段名是否有效。
	//! \param strFieldName 字段名[in]。
	//! \return 有效返回TRUE，无效返回FALSE。
	//##ModelId=483BB70A0238
	virtual OgdcBool IsAvailableFieldName(const OgdcString& strFieldName);

	//! \brief 获取子数据集
	//! \return 如果有子数据集则填充数据集指针数组，否则数组为空
	virtual OgdcBool GetChildDataset(OgdcArray<OgdcDatasetVector *>& arrSubDatasets) const;

	//! \brief  获取父数据集指针
	//! \return 如果有父数据集，则返回父数据集指针；否则返回NULL
	virtual OgdcDatasetVector* GetParentDataset() const;

	//! \brief 矢量数据集能力描述：Provider本身是否支持相关查询
	virtual UGbool IsSupportQueryType(UGQueryDef::QueryType queryType) const;

	//##ModelId=483BB70A023B
	UGDatasetVector* GetDatasetVector() const;	
	
	//##ModelId=483BB70A023D
	void SetDatasetVector(UGDatasetVector* pDatasetVector);

	void SetParentDatasetVector(OgdcDatasetVector* pDatasetVector);

protected:	
	UGDataSourceOgdc* m_pDsOgdc;
	//##ModelId=483BB70A0243
	UGDatasetVector* m_pDatasetVector;
	//##ModelId=483BB70A0245
	UGArray<UGRecordsetOgdc*> m_Recordsets;

	OgdcArray<OgdcDatasetVector *> m_SubDatasets;

	OgdcDatasetVector *m_pParentDataset;
};

}

#endif // !defined(AFX_UGDATASETVECTOROGDC_H__296CEA92_1643_444F_82CC_1DA2F9B31DB7__INCLUDED_)

