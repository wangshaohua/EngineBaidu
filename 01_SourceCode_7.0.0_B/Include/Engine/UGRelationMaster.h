#ifndef UGRELATIONMASTER_H
#define UGRELATIONMASTER_H

#include "Engine/UGEngDefs.h"


namespace UGC {

class UGDDRBase;
class UGDDRMasterBase;
class UGDataset;
class UGRecordset;

//!	\brief	定义关系的管理者基类，主要是对外提供接口层
class ENGINE_API UGRelationMasterBase
{
public:
	virtual ~UGRelationMasterBase();

protected:
	UGRelationMasterBase() : m_pDDRMaster(NULL) {}
	UGRelationMasterBase(UGDDRMasterBase *pDDRMaster) : m_pDDRMaster(pDDRMaster) {}
	UGRelationMasterBase(const UGRelationMasterBase &relMaster) {}

public:
	UGDDRMasterBase* SetDDRMaster(UGDDRMasterBase *pDDRMaster)
	{
		UGDDRMasterBase *pOldDDRMaster = m_pDDRMaster;
		m_pDDRMaster = pDDRMaster;

		return pOldDDRMaster;
	}

protected:
	UGDDRMasterBase *m_pDDRMaster;
};


class UGActionBase;
class UGDynSegInfo;
class UGDDRDynSeg;

//!	\brief	关系管理器，主要用于定义对外使用的接口
class ENGINE_API UGRelationManager : public UGRelationMasterBase
{

	friend class UGDDRMasterDynSeg;
	friend class UGDynSegInfo;
public:
	//!	\brief	说明该套接口为那些功能服务
	enum ManagerType
	{
		mtDynamicSegment = 0, // 动态分段
		mtRelationClass	 = 1  // 关系类
	};

public:
	UGRelationManager() {}
	UGRelationManager(UGDDRMasterBase *pDDRMaster) : UGRelationMasterBase(pDDRMaster) {}
	virtual ~UGRelationManager();

protected:
	UGRelationManager(const UGRelationManager &relManager) {}

public:
	//!	\brief	按照数据集间关系的描述，为数据集与数据集间建立关系
	UGbool BuildRelationDt2Dt(const UGDDRBase *pDDR);

	//!	\brief	获取指定数据集所对应的动态分段关系
	UGDDRDynSeg* GetDDR(const UGDataset *pOrgDt, const UGDataset *pDestDt);

	//!	\brief	删除两个数据集间的关系
	UGbool RemoveRelationDt2Dt(const UGDataset *pOrgDt, const UGDataset *pDestDt);

	//!	\brief	删除与指定数据集有关的所有关系
	UGbool RemoveRelationForDt(const UGDataset *pDt);

	//! \brief 删除所有的关系
	UGbool RemoveAllRelation();

	//!	\brief	对行为作出响应
	UGbool ProcessAction(const UGActionBase *pAction);

	//! \brief  获取所有包含指定数据集的动态分段信息对象
	void GetDynSegInfo(UGDataset *pDataset,UGArray<UGDynSegInfo*> &arrDynSegInfo);
	//! \brief  获取所有动态分段对象信息对象集合，这些对象集合通常在数据源Open的时候初始化
	void GetAllDynSegInfo(UGArray<UGDynSegInfo*> &arrDynSegInfo);

	//! \brief  根据数据集pDataset和指定的ID号ugIds，查找出某一特定的动态分段对象中的Route数据集所对应的recordset
	UGRecordset* QueryRouteDataset(UGDataset *pDataset,UGDataset *pRouteDataset,UGDataset *pETDataset,UGDataset *pRtDatset,UGArray<UGint> &ugIds);
	//! \brief  根据数据集pDataset和指定的ID号ugIds，查找出某一特定的动态分段对象中的EventTable数据集所对应的recordset
	UGRecordset* QueryETDataset(UGDataset *pDataset,UGDataset *pRouteDataset,UGDataset *pETDataset,UGDataset *pRtDatset,UGArray<UGint> &ugIds);
	//! \brief  根据数据集pDataset和指定的ID号ugIds，查找出某一特定的动态分段对象中的EventResult数据集所对应的recordset
	UGRecordset* QueryERDataset(UGDataset *pDataset,UGDataset *pRouteDataset,UGDataset *pETDataset,UGDataset *pRtDatset,UGArray<UGint> &ugIds);
};

}

#endif