#ifndef UGDDRRELATION_H
#define UGDDRRELATION_H

#include "Engine/UGEngDefs.h"


namespace UGC {

#define	DDR_DYNSEG_SYS_TABLE_NAME	_U("SmDDRDynSeg")

class UGDataset;
class UGRecordset;
class UGDatasetVector;

//! \brief	定义数据集到数据集关系的基类，用于记录数据集间的关系
//			（DDR means Dataset to dataset relationship）
class ENGINE_API UGDDRBase
{
public:
	UGDDRBase(UGDataset *pOrgDt, UGDataset *pDestDt, \
		const UGString &strOrgPK, const UGString &strOrgFK) : m_pOrgDataset(pOrgDt), \
		m_pDestDataset(pDestDt) { m_strOrgPK = strOrgPK, m_strOrgFK = strOrgFK; }

	UGDDRBase(const UGDDRBase &ddr) : m_pOrgDataset(ddr.m_pOrgDataset), \
		m_pDestDataset(ddr.m_pDestDataset)
	{ m_strOrgPK = ddr.m_strOrgPK, m_strOrgFK = ddr.m_strOrgFK; }

	virtual ~UGDDRBase() {}

protected:
	//!	\brief	禁用默认构造
	UGDDRBase() {}

public:
	//!	\brief	以下接口获取基本信息
	UGDataset* GetOrgDataset() const { return m_pOrgDataset; }
	UGDataset* GetDestDataset() const { return m_pDestDataset; }
	const UGString& GetOrgPrimaryKey() const { return m_strOrgPK; }
	const UGString& GetOrgForeignKey() const { return m_strOrgFK; }

protected:
	//!	\brief	源数据集
	UGDataset *m_pOrgDataset;

	//!	\brief	目标数据集
	UGDataset *m_pDestDataset;

	//!	\brief	源数据集中标识关系的关联字段
	UGString m_strOrgPK;

	//!	\brief	目标数据集中标识关系的关联字段
	UGString m_strOrgFK;
};


//!	\brief	定义动态分段的DDR
class ENGINE_API UGDDRDynSeg : public UGDDRBase
{
public:
	//!	\brief	描述数据集在动态分段DDR中充当的角色
	enum DynSegDatasetRole
	{
		dsdrNoneRole = -1,		// 无角色，用来标识未参与动态分段关系的数据集
		dsdrRouteDataset = 0,	// 路由数据集，即LineM
		dsdrEventTable = 1,		// 事件表，通常为Tabular属性表
		dsdrEventResult = 2		// 分段结果集（点或线数据集）
	};

	enum DirectionType
	{
		dirOneSide = 0,			// 单向关系（关系描述只能是从源到目标）
		dirBothSide = 1			// 双向关系
	};

public:
	UGDDRDynSeg(UGDataset *pOrgDt, DynSegDatasetRole eOrgDtRole, \
		UGDataset *pDestDt, DynSegDatasetRole eDestDtRole, \
		const UGString &strOrgPK, const UGString &strOrgFK, \
		DirectionType eDirType) : UGDDRBase(pOrgDt, pDestDt, strOrgPK, strOrgFK), \
		m_eOrgDtRole(eOrgDtRole), m_eDestDtRole(eDestDtRole), \
		m_eDirType(eDirType) {}

	UGDDRDynSeg(const UGDDRDynSeg &ddrDynSeg) { *this = ddrDynSeg; }

	virtual ~UGDDRDynSeg() {}

protected:
	//!	\brief	禁用默认构造
	UGDDRDynSeg() {}

public:
	const UGDDRDynSeg& operator =(const UGDDRDynSeg &ddrDynSeg);

	//!	\brief	获取源或目标数据集在动态分段DDR中的角色
	DynSegDatasetRole GetOrgDatasetRole() const { return m_eOrgDtRole; }
	DynSegDatasetRole GetDestDatasetRole() const { return m_eDestDtRole; }

	//!	\brief	获取关系在传递方向上的类型
	DirectionType GetDirectionType() const { return m_eDirType; }

	//!	\brief	设置和获取FromMeasure跟ToMeasure
	void SetFMField(const UGString &strFldName) { m_strFromM = strFldName; }
	void SetTMField(const UGString &strFldName) { m_strToM = strFldName; }

	const UGString& GetFMField() const { return m_strFromM; }
	const UGString& GetTMField() const { return m_strToM; }

	//!	\brief	设置和获取ET或ER中的RouteID字段
	void SetRouteIDField(const UGString &strFldName) { m_strRouteIDFld = strFldName; }
	const UGString& GetRouteIDField() const { return m_strRouteIDFld; }

protected:
	//!	\brief	源以及目标数据集在DDR中的角色
	DynSegDatasetRole m_eOrgDtRole;
	DynSegDatasetRole m_eDestDtRole;

	//!	\brief	指示ET和ER表中的FromMeasure和ToMeasure字段，
	//			当事件为点事件时，ToMeasure描述无效
	UGString m_strFromM;
	UGString m_strToM;

	//!	\brief	指示ET和ER中的RouteID字段
	UGString m_strRouteIDFld;

	//!	\brief	标识DDR是单向还是双向关系
	DirectionType m_eDirType;	
};


class ENGINE_API UGRelatedObjects
{
public:
	UGRelatedObjects(UGDataset *pDt, const UGArray<UGint> &objIDs, UGDataset *pDtFrom) : \
		m_pDataset(pDt), m_pDtSearchFrom(pDtFrom)
	{
		m_arrObjIDs.Copy(objIDs);
	}

	UGRelatedObjects(const UGRelatedObjects &objects) { *this = objects; }

	UGRelatedObjects() : m_pDataset(NULL), m_pDtSearchFrom(NULL) {}

public:
	const UGRelatedObjects& operator =(const UGRelatedObjects &objects)
	{
		m_pDataset = objects.m_pDataset;
		m_arrObjIDs.Copy(objects.m_arrObjIDs);
		m_pDtSearchFrom = objects.m_pDtSearchFrom;

		return *this;
	}

public:
	//!	\brief	关联对象所属数据集
	UGDataset *m_pDataset;

	//!	\brief	关联对象ID集
	UGArray<UGint> m_arrObjIDs;

	//!	\brief	指明是通过哪个直接的数据集搜索到的
	UGDataset *m_pDtSearchFrom;
};


class UGOORMasterBase;
class UGDynSegInfo;
class UGDDRDynSeg;

//!	\brief	定义DDR操控者基类，负责DDR的创建、存储、管理和搜索等相关功能
class ENGINE_API UGDDRMasterBase
{
	friend class UGDynSegInfo;

public:
	//!	\brief	用于子类对自身的描述
	enum DDRType
	{
		ddrForDynSeg = 0,	// 描述UGDDRMasterDynSeg子类
		ddrForRelClass = 1	// 描述关系类的DDRMaster子类（用于扩展）
	};

public:
	virtual ~UGDDRMasterBase();

protected:
	//!	\brief	禁用拷贝构造和默认构造
	UGDDRMasterBase() {}
	UGDDRMasterBase(DDRType eClassType) : m_eClassType(eClassType) {}
	UGDDRMasterBase(const UGDDRMasterBase &ddrM) {}

public:
	//!	\brief	获取自身描述
	DDRType GetClassType() const { return m_eClassType; }


	//!	\brief	创建DDR
	//!	\param	pDDR[IN]	DDR的描述	
	virtual UGbool BuildDDR(const UGDDRBase *pDDR) = 0;

	//!	\brief	删除指定关系的DDR
	virtual UGbool RemoveDDR(const UGDataset *pOrgDt, const UGDataset *pDestDt) { return FALSE; }

	//!	\brief	删除与指定数据集有关的所有DDR
	virtual UGbool RemoveDDR(const UGDataset *pDt) { return FALSE; }

	//!	\brief	清除所有DDR
	virtual UGbool RemoveAllDDRs() { return FALSE; }

	//!	\brief	获取指定关系的DDR描述
	virtual UGDDRDynSeg* GetDDR(const UGDataset *pOrgDt, const UGDataset *pDestDt) const { return NULL; }



	//!	\brief	获取与指定目标有直接关系的关联对象
	virtual void GetDirRelatedObjects(const UGDataset *pDt, const UGArray<UGint> &arrObjIDs, \
		UGArray<UGRelatedObjects> &result) const {}

	//!	\brief	获取与指定目标相关的所有关联对象（包括直接的和间接的）
	virtual void GetAllRelatedObjects(const UGDataset *pDt, const UGArray<UGint> &arrObjIDs, \
		UGArray<UGRelatedObjects> &result) const {}

	//!	\brief	获取与指定数据集直接相关的数据集
	virtual void GetDirRelatedDataset(const UGDataset *pDt, UGArray<UGDataset*> &result) const {}

	//!	\brief	获取与指定数据集相关的所有数据集（包括直接的和间接的）
	virtual void GetAllRelatedDataset(const UGDataset *pDt, UGArray<UGDataset*> &result) const {}

	//! \brief  获取所有包含指定数据集的动态分段信息对象
	virtual void GetDynSegInfo(const UGDataset *pDataset,UGArray<UGDynSegInfo*> &arrDynSegInfo) const {}
	//! \brief  获取所有动态分段对象信息对象集合，这些对象集合通常在数据源Open的时候初始化
	virtual void GetAllDynSegInfo(UGArray<UGDynSegInfo*> &arrDynSegInfo) const {}

	//! \brief  根据数据集pDataset和指定的ID号ugIds，查找出某一特定的动态分段对象中的Route数据集所对应的recordset
	virtual UGRecordset* QueryRouteDataset(UGDataset *pDataset,UGDataset *pRouteDataset,UGDataset *pETDataset,UGDataset *pRtDatset,UGArray<UGint> &ugIds) { return NULL; }
	//! \brief  根据数据集pDataset和指定的ID号ugIds，查找出某一特定的动态分段对象中的EventTable数据集所对应的recordset
	virtual UGRecordset* QueryETDataset(UGDataset *pDataset,UGDataset *pLineMDataset,UGDataset *pETDataset,UGDataset *pRtDatset,UGArray<UGint> &ugIds) { return NULL; }
	//! \brief  根据数据集pDataset和指定的ID号ugIds，查找出某一特定的动态分段对象中的EventResult数据集所对应的recordset
	virtual UGRecordset* QueryERDataset(UGDataset *pDataset,UGDataset *pLineMDataset,UGDataset *pETDataset,UGDataset *pRtDatset,UGArray<UGint> &ugIds) { return NULL; }

protected:
	//!	\brief	DDR描述及其隐含的OOR描述信息
	UGArray<UGOORMasterBase*> m_arrOORMasters;

	//!	\brief	对类自身的描述
	DDRType m_eClassType;
};


class UGOORMasterDynSeg;
class UGDynSegInfo;

//!	\brief	定义动态分段的DDR操控者，主要针对动态分段的特定实现
class ENGINE_API UGDDRMasterDynSeg : public UGDDRMasterBase
{
public:
	UGDDRMasterDynSeg() : UGDDRMasterBase(UGDDRMasterBase::ddrForDynSeg) {}
	virtual ~UGDDRMasterDynSeg();

protected:
	//!	\brief	禁用拷贝构造
	UGDDRMasterDynSeg(const UGDDRMasterDynSeg &ddrMDynSeg) {}

public:
	//!	\brief	创建DDR
	//!	\param	pDDR[IN]	DDR的描述	
	virtual UGbool BuildDDR(const UGDDRBase *pDDR);

	//!	\brief	删除指定关系的DDR
	virtual UGbool RemoveDDR(const UGDataset *pOrgDt, const UGDataset *pDestDt);

	//!	\brief	删除与指定数据集有关的所有DDR
	virtual UGbool RemoveDDR(const UGDataset *pDt);

	//!	\brief	清除所有DDR
	virtual UGbool RemoveAllDDRs();

	//!	\brief	获取指定关系的DDR描述
	virtual UGDDRDynSeg* GetDDR(const UGDataset *pOrgDt, const UGDataset *pDestDt) const;


	//!	\brief	获取与指定目标有直接关系的关联对象，会过滤单向关系
	virtual void GetDirRelatedObjects(const UGDataset *pDt, const UGArray<UGint> &arrObjIDs, \
		UGArray<UGRelatedObjects> &result) const;

	//!	\brief	获取与指定目标相关的所有关联对象（包括直接的和间接的），会过滤单向关系
	virtual void GetAllRelatedObjects(const UGDataset *pDt, const UGArray<UGint> &arrObjIDs, \
		UGArray<UGRelatedObjects> &result) const;

	//!	\brief	获取与指定数据集直接相关的数据集，会过滤单向关系
	virtual void GetDirRelatedDataset(const UGDataset *pDt, UGArray<UGDataset*> &result) const;

	//!	\brief	获取与指定数据集相关的所有数据集（包括直接的和间接的），会过滤单向关系
	virtual void GetAllRelatedDataset(const UGDataset *pDt, UGArray<UGDataset*> &result) const;

	//!	\brief	获取需要进行处理的关联对象（需要处理的对象参考设计文档中关于搜索方式的描述）
	void GetRelObjsToProc(const UGDataset *pDt, const UGArray<UGint> &arrObjIDs, \
		UGArray<UGRelatedObjects> &result) const;

	//!	\brief	为ER中的目标搜索对应的LineM中的路线对象，此种情况一般为反向搜索
	void GetRouteForERObj(const UGDataset *pDt, const UGArray<UGint> &arrObjIDs, \
		UGRelatedObjects &result) const;

	//! \brief  获取所有包含指定数据集的动态分段信息对象
	virtual void GetDynSegInfo(const UGDataset *pDataset,UGArray<UGDynSegInfo*> &arrDynSegInfo) const;
	//! \brief  获取所有动态分段对象信息对象集合，这些对象集合通常在数据源Open的时候初始化
	virtual void GetAllDynSegInfo(UGArray<UGDynSegInfo*> &arrDynSegInfo) const;

	//! \brief  根据数据集pDataset和指定的ID号ugIds，查找出某一特定的动态分段对象中的LineM数据集所对应的recordset
	virtual UGRecordset* QueryRouteDataset(UGDataset *pDataset,UGDataset *pRouteDataset,UGDataset* pETDataset,UGDataset *pRtDatset,UGArray<UGint> &ugIds);
	//! \brief  根据数据集pDataset和指定的ID号ugIds，查找出某一特定的动态分段对象中的EventTable数据集所对应的recordset
	virtual UGRecordset* QueryETDataset(UGDataset *pDataset,UGDataset *pRouteDataset,UGDataset* pETDataset,UGDataset *pRtDatset,UGArray<UGint> &ugIds);
	//! \brief  根据数据集pDataset和指定的ID号ugIds，查找出某一特定的动态分段对象中的EventResult数据集所对应的recordset
	virtual UGRecordset* QueryERDataset(UGDataset *pDataset,UGDataset *pRouteDataset,UGDataset* pETDataset,UGDataset *pRtDatset,UGArray<UGint> &ugIds);

protected:
	//!	\brief	检查DDR的有效性
	UGbool CheckDDR(const UGDDRDynSeg &ddrDynSeg);

	//! \brief	DDR信息入库
	virtual UGbool RecordDDRToDB(const UGDDRDynSeg &ddrDynSeg) { return TRUE; }

	//!	\brief	构造OORMaster对象
	virtual UGOORMasterDynSeg* MakeOORMaster(const UGDDRDynSeg &ddrDynSeg);

	//!	\brief	从数据库中删除DDR记录
	virtual UGbool DeleteDDRFromDB(const UGDataset *pOrgDt, const UGDataset *pDestDt) { return TRUE; }
	virtual UGbool DeleteDDRFromDB(const UGDataset *pDt) { return TRUE; }
	virtual UGbool DeleteAllDDRsFromDB() { return TRUE; }

	//!	\brief	在复杂搜索（即包含间接关系）中，递归搜索关联对象
	//!	\param	pDt[IN]					输入数据集，搜索的起始数据集
	//			arrDtSearched[IN, OUT]	已搜索过的数据集，用于防止重复搜索和回环
	void SearchRelObjects(const UGDataset *pDt, const UGArray<UGint> &arrObjIDs, \
		UGArray<const UGDataset*> &arrDtSearched, UGArray<UGRelatedObjects> &result) const;

	void SearchRelDt(const UGDataset *pDt, UGArray<const UGDataset*> &arrDtSearched, \
		UGArray<UGDataset*> &result) const;

	//!	\brief	根据各DDR的描述设置好数据集的角色
	void InitDatasetRole();

	//!	\brief	检查指定数据集是否还在参与动态分段，如果没有，则清除数据集的动态分段角色
	void CheckAndCleanDtRole(const UGDataset *pDt);

private:
	//动态分段对象信息对象集合
	UGArray<UGDynSegInfo *>   m_arrDynSegInfoPtr;
};


//!	\brief	定义OOR操控者基类，负责OOR的建立、存储、管理和搜索等相关功能
//			（OOR means Object to object relationship），DDR的描述中隐含
//			定义了OOR，因此每一个DDR的描述对应了一个OOR集合，即UGOORMaster对象
class ENGINE_API UGOORMasterBase
{
	friend class UGDDRMasterDynSeg;

protected:
	//!	\brief	禁用拷贝构造和默认构造
	UGOORMasterBase() {}
	UGOORMasterBase(const UGOORMasterBase &oorM) {}

public:
	virtual ~UGOORMasterBase();

public:
	//!	\brief	建立OOR
	virtual UGbool BuildOOR(UGint nOrgObjID, UGint nDestObjID) { return TRUE; }

	//!	\brief	获取指定对象的关联对象
	virtual void GetRelatedObjects(const UGArray<UGint> &arrObjIDs, \
		UGbool bOrgOrDest, UGArray<UGint> &result) const = 0;

protected:
	//!	\brief	对应的DDR描述
	UGDDRBase *m_pDDR;
};


//!	\brief	定义动态分段的OOR操控者，主要针对动态分段的特定实现
class ENGINE_API UGOORMasterDynSeg : public UGOORMasterBase
{
public:
	UGOORMasterDynSeg(const UGDDRDynSeg &ddrDynSeg, const UGDDRMasterDynSeg *pDDRMaster);
	virtual ~UGOORMasterDynSeg();

protected:
	//!	\brief	禁用拷贝构造和默认构造
	UGOORMasterDynSeg() {}
	UGOORMasterDynSeg(const UGOORMasterDynSeg &oorM) {}

public:
	//!	\brief	获取指定对象的关联对象
	virtual void GetRelatedObjects(const UGArray<UGint> &arrObjIDs, \
		UGbool bOrgOrDest, UGArray<UGint> &result) const;
	
protected:
	//!	\brief	标识OOR所属的DDRMaster
	const UGDDRMasterDynSeg *m_pDDRMaster;
};

//!	\brief 定义动态分段信息类，在每一组动态分段信息类中都应该包含Route，EventTable，EventResult三个数据集
//! \brief 并且这三者之间根据数据库表SmDDRDynSeg中记录的关系相关联
class ENGINE_API UGDynSegInfo
{
public:
	UGDynSegInfo();
	~UGDynSegInfo();
	//! \brief 获取Route数据集
	UGDataset* GetRouteDataset(){return m_pRouteDataset;}
	//! \brief 获取EventTable数据集
	UGDataset* GetEventDataset(){return m_pEventDataset;}
	//! \brief 获取EventResult数据集
	UGDataset* GetResultDataset(){return m_pResultDataset;}
	//! \brief 将指定数据集设置为Route数据集
	UGbool SetRouteDataset(UGDataset *pDataset);	
	//! \brief 将指定数据集设置为EventTable数据集
	UGbool SetEventDataset(UGDataset *pDataset);
	//! \brief 获取EventResult数据集
	UGbool SetResultDataset(UGDataset *pDataset);
	//！ \brief 根据指定的角色指定的数据集，将数据集存储到Route，EventTable或者EventResult数据集
	UGbool SetRoleDataset(UGDDRDynSeg::DynSegDatasetRole role,UGDataset * pDataset);
	//!  \brief 判断指定的数据集是否在此动态分段信息类中，如果存在则返回它的角色
	UGDDRDynSeg::DynSegDatasetRole GetDatasetRole(const UGDataset * pDatatset);

private:
	//！ \brief Route数据集
	UGDataset* m_pRouteDataset;
	//！ \brief EventTable数据集
	UGDataset* m_pEventDataset;
	//！ \brief EventResult数据集
	UGDataset* m_pResultDataset;
};

}

#endif