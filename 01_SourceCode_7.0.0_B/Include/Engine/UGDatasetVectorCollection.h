#ifndef UGDATASETVECTORCOLLECTION_H
#define UGDATASETVECTORCOLLECTION_H

#include "Engine/UGDataset.h"
#include "Engine/UGDatasetVector.h"

namespace UGC
{
	class UGRecordset;
	class ENGINE_API UGDatasetVectorCollection : public UGDatasetVector
	{

	public:
		
		UGDatasetVectorCollection();

		UGDatasetVectorCollection(UGDataSource *pDataSource);

		virtual ~UGDatasetVectorCollection();

	public:

		//! \brief 添加数据集。
		//! \param strName 数据集名字[in]。
		//! \param nState 状态，默认为正常[in]
		//! \return 是否添加成功，成功返回TRUE，失败返回FALSE。
		//##ModelId=4820305301AB
		virtual UGbool AddSubDataset(const UGString &strName,CollectionState nState = normal);

		//! \brief 移除数据集。
		//! \param strName 数据集名字[in]。
		//! \return 是否删除成功，成功返回TRUE，失败返回FALSE。
		//##ModelId=4820305301AB
		virtual UGbool RemoveDataSet(const UGString &strName);

		//! \brief 改变集合顺序。
		//! \param strName 数据集名字[in]。
		//! \param position 要改变的位置[in]
		//! \return 是否改变成功，成功返回TRUE，失败返回FALSE。
		//##ModelId=4820305301AB
		virtual UGbool ChangeOrder(const UGString &name,UGint position);

		//! \brief 合并数据集。
		//! \param strName 数据集名字[in]。
		//! \param bkill 是否要删除原集合[in]
		//! \return 是否合并成功，成功返回TRUE，失败返回FALSE。
		//##ModelId=4820305301AB
		virtual UGbool CombineCollection(const UGString &strName,UGbool bKill);

		//! \brief 得到数据集数量。
		//! \return 返回个数。
		//##ModelId=4820305301AB
		UGint GetDatasetCount();

		//! \brief 返回集合数组。
		//! \return 集合数组
		//##ModelId=4820305301AB
		UGArray<UGDatasetState> GetStates();

	public:
		//! \brief 为集合创建字段。
		//! \param info 字段信息[in]。
		//! \return 是否创建成功，成功返回TRUE，失败返回FALSE。
		//##ModelId=4820305301AB
		virtual UGbool CreateField(const UGFieldInfo &info);

		//! \brief 修改字段。
		//! \param strName 字段名[in]。
		//! \param info 字段信息[in]。
		//! \return 是否修改成功，成功返回TRUE，失败返回FALSE。
		//##ModelId=4820305301AB
		virtual UGbool SetFieldInfo(const UGString &strName,const UGFieldInfo &info);

		//! \brief 删除字段。
		//! \param name 字段名[in]。
		//! \return 是否删除成功，成功返回TRUE，失败返回FALSE。
		//##ModelId=4820305301AB
		virtual UGbool DeleteField(const UGString &name);

		//! \brief 得到数据集指针。
		//! \param name 数据集名字[in]。
		//! \return 数据集指针
		//##ModelId=4820305301AB
		virtual UGDataset* GetDataset(const UGString &name);

		//! \brief 刷新数据集状态。
		//! \param strDatasetName 数据集名字[in]。
		//! \return 是否刷新成功，成功返回TRUE，失败返回FALSE。
		//##ModelId=4820305301AB
		virtual UGbool RefreshDatasetState(const UGString & strDatasetName);

		//! \brief 刷新所有数据集。
		//! \return 是否刷新成功，成功返回TRUE，失败返回FALSE。
		//##ModelId=4820305301AB
		virtual UGbool RefreshDatasetStates();
		
		//! \brief 查询。
		//! \param def 查询定义[in]。
		//! \return 记录集指针
		//##ModelId=4820305301AB
		virtual UGRecordset* Query(const UGQueryDef &def);

		//! \brief 设置子数据集投影。
		//! \param PrjCoordSys 投影参数[in]。
		//! \return 是否设置成功，成功返回TRUE，失败返回FALSE。
		//##ModelId=4820305301AB
		virtual UGbool UpdateSubProjection(const UGPrjCoordSys &PrjCoordSys);
		
		//! \brief 得到状态。
		//! \param name 数据集名字[in]。
		//! \return 数据及状态
		//##ModelId=4820305301AB
		virtual CollectionState GetDatasetState(const UGString& name);

		//! \brief 判断数据集是否能够添加进集合。
		//! \param strName 数据集名字[in]。
		//! \return 是否能够添加，成功返回TRUE，失败返回FALSE。
		//##ModelId=4820305301AB
		virtual UGbool CanAdd(const UGString &strName);

		//! \brief 得到数据集指针。
		//! \param index 索引[in]。
		//! \return 数据集指针
		//##ModelId=4820305301AB
		virtual UGDataset* GetDataset(UGint index);//内部使用

		//! \brief 是否能够添加。
		//! \param strName 数据集名字[in]。
		//! \return 数据集指针
		//##ModelId=4820305301AB
		virtual UGbool IsMatch(const UGString &strName);

		//! \brief 得到存储的类型。
		//! \param nType 类型[in]。
		//! \return 类型是否获取成功，成功返回TRUE，失败返回FALSE
		//##ModelId=4820305301AB
		virtual UGbool GetStoredType(DatasetType &nType);

		//! \brief 得到表名。
		//! \return 表名
		//##ModelId=4820305301AB
		virtual UGString GetTableName();

		//! \brief 添加数据集，用于复制。
		//! \param strName 数据集名字[in]。
		//! \param nState 数据及状态[in]。
		//! \param nSrcID 复制的数据集ID[in]。
		//! \return 是否添加成功，成功返回TRUE，失败返回FALSE
		//##ModelId=4820305301AB
		virtual UGbool AddForCopy(const UGString &strName,CollectionState nState,UGint nSrcID);

		//##ModelId=4820305301B5
		void ReleaseAllRecordsets();

		//! \brief 通过记录集序号释放记录集内存空间。
		//! \param nIndex 记录集序号[in]。
		//! \return 是否释放成功，成功返回TRUE，失败返回FALSE。
		//##ModelId=4820305301AB
		virtual UGbool ReleaseRecordset(UGint nIndex);

		//! \brief 通过记录集指针释放记录集内存空间。
		//! \param *pRecordset 记录集指针[in]。
		//! \return 是否释放成功，成功返回TRUE，失败返回FALSE。
		//##ModelId=4820305301AB
		virtual UGbool ReleaseRecordset(UGRecordset *pRecordset);

	protected:

		void GetSubDatasetNames(UGStrings &dts);

	protected:
		//存储数据集的状态
		UGArray<UGDatasetState> m_arrDatasetState;

	};

}
#endif