#ifndef UGDATASETRELCLASSMANAGER_H
#define UGDATASETRELCLASSMANAGER_H


#include "Engine/UGDatasetRelClass.h"


namespace UGC {

#define	RELCLASS_SYS_TABLE_NAME		_U("SmRelations")
#define RELRULE_SYS_TABLE_NAME		_U("SmRelRules")
#define EXCLUSION_SYS_TABLE_NAME	_U("SmExclusion")

class UGDataSource;

// 数据源不直接操作 关系类数据集，而是 通过UGDatasetRelationMananger 来操作
class ENGINE_API UGDatasetRelClassManager
{
public:
	//! \brief	用 数据源 构造，可以从数据源获取UGDatasetRelationMananger
	UGDatasetRelClassManager(UGDataSource *pDataSource);
	
	//! \brief	析构函数
	virtual ~UGDatasetRelClassManager();

public:
	//! \brief	创建关系类数据集
	UGDatasetRelClass* CreateDatasetRelClass(const UGRelClassInfo &rsInfo);
	UGDatasetRelClass* CreateDatasetRelClass(const UGRelClassInfo &rsInfo, const UGFieldInfos &fldInfos);

	//! \brief	删除关系类数据集
	virtual UGbool DeleteDatasetRelClass(const UGString &strName);

	//! \brief	通过数据源 读取 注册表里的 关系类数据集，填充m_datasets 
	virtual UGbool InitDatasets() { return FALSE; }

	//!	\brief	清掉所有的关系类指针
	void RemoveAllRelClass() { m_RelClasses.RemoveAll(); }


	//!	\brief	关系合法性检查
	//	\param	errMsgs[OUT]	返回分类统计后的错误信息
	//	\return	如果检查函数成功被执行则返回TRUE，否则，返回FALSE
	UGbool CheckValid(const UGArray<UGRelObjects> &arrRelObjects, UGArray<UGIllegalMsg> &errMsgs);
	UGbool CheckValid(UGArray<UGRecordset*> &arrRecordset, UGArray<UGIllegalMsg> &errMsgs);

	//!	\brief	关系设置例外
	//	\return	如果检查函数成功被执行则返回TRUE，否则，返回FALSE
	UGbool SetException(UGint nObjectID, UGString strDtName);

	//!	\brief	关系删除例外
	//	\return	如果检查函数成功被执行则返回TRUE，否则，返回FALSE
	UGbool RemoveException(UGint nObjectID, UGString strDtName);


	//! \brief	获取关系类
	UGDatasetRelClass* GetDatasetRelClass(const UGString &strName);
	UGDatasetRelClass* GetDatasetRelClass(UGint nIndex);

	//! \brief	根据源和目标数据集来获取关系类
	UGDatasetRelClass* GetDatasetRelClass(const UGString &strOrgDtName, const UGString &strDestDtName);


	//! \brief	读取关系类的相关注册信息
	virtual UGbool ReadInfos() = 0;

	//! \brief	创建与关系类相关的系统表
	virtual UGbool CreateRelSysTables() = 0;

	

	//! \brief	检查某个数据集是否已加入关系类中
	UGbool IsJoinRelClass(const UGString &strDtName);

	//! \brief  删除以某数据集为源或者目标的所有关系类；
	//! \param strDatasetName[IN] 数据集名字；
	//! \param bOrg[IN]　TRUE则strDatasetName对应源数据集，FALSE则strDatasetName对应目标数据集；
	UGbool DeleteAllDirectRelClsByDtName(UGString strDatasetName, UGbool bOrg);

	//! \brief  查询出所有目标或者源数据集中的关联对象；
	//! \param relObjects[IN] 包含数据集名字与ID集合；
	//! \param aryResults[OUT] 
	//! \param bOrg[IN] TRUE则从源找目标，FALSE则从目标找源；
	UGbool GetDirectRelObjectses(const UGRelObjects &relObjects, \
		UGArray<UGRelObjects> &aryResults, UGbool bOrg);
	
	//! \brief  获取能够响应此对象的关联动作的关联对象的集合，包括间接的；
	//! \param relObjectsOrg[IN]  作为源的关联对象集合；
	//! \param aryRelObjects[OUT]  与之为源的关联对象集合的集合，包括直接关联与间接关联，
	//! \attention *****************aryRelObjects[0]为relObjectsOrg的一个考贝；******************8
	UGbool GetRelObjectsesForAction(const UGRelObjects &relObjectsOrg, \
		UGArray<UGRelObjects> &aryRelObjects);

	//! \brief  处理能够响应传入对象关联的所有对象，包括间接关系的；
	//  \param  relObjects[IN]			作为源的关联对象集合；
	//  \param  msg[IN]					需要做的动作；
	//	\param	aryImpactObjects[OUT]	返回受影响的对象(相关数据集中受影响的对象）
	//  \param  isModified[in]          源本身是否已经被修改过，如果没有被修改过，内部就作修改；
	UGbool DealRelObjectsesRecursion(const UGRelObjects &relObjects, \
		const UGGeoAction &msg, UGArray<UGRelObjects> &aryImpactObjs, UGbool isModified);

	//! \brief  取出此数据集参与的所有直接关系类；
	//! \param strName [IN] 数据集名；
	//! \param aryRelClass[OUT] 关系类数组；
	UGbool GetAllDirectRelClasses(const UGString &strName, \
	UGArray<UGDatasetRelClass*> &aryRelClassP);


private:
	//! \brief  查询以传入名字对应的数据集作为源或者目标数据集的关系类指针数组(无嵌套传递)；
	//! \param strName [IN] 数据集名；
	//! \param aryRelClass[OUT] 关系类数组；
	//! \param bOrg[IN] 传入名字是否是对应关系类中的源数据集（TRUE则strName为源数据集名字，FALSE则strName为目标数据集名字）；
	UGbool GetDirectRelClasses(const UGString &strName, \
		UGArray<UGDatasetRelClass*> &aryRelClassP, UGbool bOrg = TRUE);

	//! \brief  获取传入名字对应的数据集直接作为源或目标，并且另一端的数据集能够响应此数据集消息的所有关系类，注意：仅直接关系类，不包括间接的；
	//! \param strName [IN] 数据集名；
	//! \param aryRelClass[OUT] 关系类数组；
	UGbool GetAllDirectRelClassesForAction(const UGString &strName, \
		UGArray<UGDatasetRelClass*> &aryRelClassP);

	//! \brief  获取能响应此数据集动作的所有关系类，包括间接的，没有作断环处理，但结果集的成员都唯一，不重复；
	//! \param  strSrcDtName[IN] 数据集名字；
	//! \param  aryRelClassP[OUT] 关系类数组；
	UGbool GetRelClassesForAction(UGString strSrcDtName, UGArray<UGDatasetRelClass*> &aryRelClassP);


protected:
	//! \brief	各子类中new一个关系类数据集对象
	virtual UGDatasetRelClass* GetNewRelClass() = 0;

	//!	\brief	删除关系类在数据库中的信息
	virtual UGbool DeleteDtRelClassFromTable(UGDatasetRelClass *pRelClass) = 0;

protected:
	//! \brief	关联的数据源指针
	UGDataSource *m_pDataSource;

	//! \brief	关系类数据集指针数组
	UGArray<UGDatasetRelClass*> m_RelClasses;
};

}

#endif
