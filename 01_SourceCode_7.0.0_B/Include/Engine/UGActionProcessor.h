#ifndef UGACTIONPROCESSOR_H
#define UGACTIONPROCESSOR_H

#include "Engine/UGEngDefs.h"
#include "Geometry/UGFeature.h"
#include "Engine/UGDDRRelation.h"
#include "Geometry/UGGeoPoint.h"
#include "Geometry/UGGeoLineM.h"


namespace UGC {

//!	\brief	行为描述者
class ENGINE_API UGActionBase
{
public:
	//!	\brief	行为描述者对自身的描述
	enum ActionType
	{
		actOffset = 0,			// 平移
		actRotate = 1,			// 旋转
		actModifyAttribute = 2,	// 修改对象的属性信息
		actModifyGeometry = 3	// 修改对象的几何信息
	};

public:
	virtual ~UGActionBase() {}

protected:
	UGActionBase(ActionType eClassType) : m_eClassType(eClassType) {}
	UGActionBase() {}
	UGActionBase(const UGActionBase &act) {}

public:
	ActionType GetClassType() const { return m_eClassType; }

protected:
	//!	\brief	对自身身份的描述
	ActionType m_eClassType;
};


class UGDDRMasterBase;
class UGDDRMasterDynSeg;

//!	\brief	行为响应者
class ENGINE_API UGActionProcessorBase
{
public:
	virtual ~UGActionProcessorBase() {}

protected:
	UGActionProcessorBase() {}
	UGActionProcessorBase(const UGActionProcessorBase &actProc) {}

public:
	//!	\brief	对行为的响应处理
	virtual UGbool Run(const UGActionBase *pAction, const UGDDRMasterBase *pDDRMaster) = 0;
};


class UGDataset;
class UGRecordset;

//!	\brief	定义属性修改行为
class ENGINE_API UGActModifyAttr : public UGActionBase
{
public:
	UGActModifyAttr() : UGActionBase(UGActionBase::actModifyAttribute), \
		m_nObjID(0), m_pDt(NULL) {}

	UGActModifyAttr(UGint nObjID, UGDataset *pDt, const UGFieldInfo &fldInfo, \
		const UGVariant &oldValue, const UGVariant &newValue) : \
		UGActionBase(UGActionBase::actModifyAttribute), m_nObjID(nObjID), \
		m_pDt(pDt), m_fldInfo(fldInfo), m_OldValue(oldValue), m_NewValue(newValue) {}

	UGActModifyAttr(const UGActModifyAttr &act) { *this = act; }

	virtual ~UGActModifyAttr() {}

public:
	const UGActModifyAttr& operator =(const UGActModifyAttr &act);

public:
	//!	\brief	修改的目标
	UGint m_nObjID;

	//!	\brief	目标所属数据集
	UGDataset *m_pDt;

	//!	\brief	修改的字段
	UGFieldInfo m_fldInfo;

	//!	\brief	修改前的值
	UGVariant m_OldValue;

	//!	\brief	修改后的值
	UGVariant m_NewValue;
};

//!	\brief	定义动态分段中对属性修改行为的处理者
class ENGINE_API UGActModAttrProcDynSeg : public UGActionProcessorBase
{
public:
	UGActModAttrProcDynSeg() {}
	virtual ~UGActModAttrProcDynSeg() {}

protected:
	UGActModAttrProcDynSeg(const UGActModAttrProcDynSeg &actDynSeg) {}

public:
	//!	\brief	对行为的响应处理
	virtual UGbool Run(const UGActionBase *pAction, const UGDDRMasterBase *pDDRMaster);

protected:
	void ProcActForRouteDt(const UGActModifyAttr *pAction, const UGDDRMasterDynSeg *pDDRMaster);
	void ProcActForET(const UGActModifyAttr *pAction, const UGDDRMasterDynSeg *pDDRMaster);
	void ProcActForER(const UGActModifyAttr *pAction, const UGDDRMasterDynSeg *pDDRMaster);

	void ModifyRelObjsAttr(const UGActModifyAttr *pAction, const UGRelatedObjects &objs);
	void ModifyERObjsForFMOrTM(const UGActModifyAttr *pAction, const UGDDRMasterDynSeg *pDDRMaster, \
		const UGRelatedObjects &objs, UGbool bModGeoOnly = FALSE);
	void ModifyERObjsForRID(const UGActModifyAttr *pAction, const UGDDRMasterDynSeg *pDDRMaster, \
		const UGRelatedObjects &objs, UGbool bModGeoOnly = FALSE);

	UGGeoPoint GetCorrectedGeo(const UGVariant &routeID, const UGVariant &valM, \
		UGRecordset *pRecRoute, const UGString &strRIDRoute);
	UGGeoLineM GetCorrectedGeo(const UGVariant &routeID, const UGVariant &valFM, const UGVariant &valTM, \
		UGRecordset *pRecRoute, const UGString &strRIDRoute);
};

//!	\brief	定义修改几何信息的行为
class ENGINE_API UGActModifyGeo : public UGActionBase
{
public:
	UGActModifyGeo() : UGActionBase(UGActionBase::actModifyGeometry), \
		m_pDt(NULL), m_pOldGeo(NULL), m_pNewGeo(NULL) {}
	UGActModifyGeo(UGDataset *pDt, UGGeometry *pOldGeo, UGGeometry *pNewGeo) : \
		UGActionBase(UGActionBase::actModifyGeometry), \
		m_pDt(pDt), m_pOldGeo(pOldGeo), m_pNewGeo(pNewGeo) {}
	UGActModifyGeo(const UGActModifyGeo &act) { *this = act; }

	virtual ~UGActModifyGeo()
	{
		delete m_pOldGeo, m_pOldGeo = NULL;
		delete m_pNewGeo, m_pNewGeo = NULL;
	}

public:
	const UGActModifyGeo& operator =(const UGActModifyGeo &act)
	{
		m_eClassType = act.m_eClassType;
		m_pDt = act.m_pDt;
		m_pOldGeo = act.m_pOldGeo;
		m_pNewGeo = act.m_pNewGeo;

		return *this;
	}

public:
	//!	\brief	对象所属数据集
	UGDataset *m_pDt;

	//!	\brief	对象修改前的几何信息（应该带有ID信息）
	UGGeometry *m_pOldGeo;

	//!	\brief	对象修改后的几何信息（应该带有ID信息）
	UGGeometry *m_pNewGeo;
};

//!	\brief	为动态分段设计针对修改几何信息行为的处理者
class ENGINE_API UGActModGeoProcDynSeg : public UGActionProcessorBase
{
public:
	UGActModGeoProcDynSeg() {}
	virtual ~UGActModGeoProcDynSeg() {}

protected:
	UGActModGeoProcDynSeg(const UGActModGeoProcDynSeg &actDynSeg) {}

public:
	//!	\brief	对行为的响应处理
	virtual UGbool Run(const UGActionBase *pAction, const UGDDRMasterBase *pDDRMaster);

protected:
	void ModifyERGeo(const UGActModifyGeo *pAction, const UGDDRMasterDynSeg *pDDRMaster);
};

}

#endif