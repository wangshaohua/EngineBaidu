#ifndef UGDATASETRELATIONSHIP_H
#define UGDATASETRELATIONSHIP_H

#include "Engine/UGEngDefs.h"
#include "Engine/UGTable.h"
#include "Engine/UGGeoAction.h"
#include "Geometry/UGDataCodec.h"


namespace UGC
{
	//!	\brief	定义关系规则
	class ENGINE_API UGRelRule
	{
	public:
		enum SpatialType
		{
			//sptlNone		= 0,		// 没有指定空间规则
			//sptlContain		= 1,	// 包含
			//sptlContainedBy = 2,		// 被包含
			//sptlIntersect	= 3,		// 相交
			//sptlDisjoint	= 4,		// 相离
			//sptlTouch		= 5,		// 相接
			//sptlEqual		= 6,		// 相等
			//sptlCross		= 7,		// 穿越


			sptlNone					=-1,	// 没有指定空间规则
			sptlIdentical				=0,		// 相等
			sptlDisjoint				=1,		// 相离
			sptlIntersects				=2,		// 相交
			sptlTouches					=3,		// 相接
			//UGOverlaps				=4,		
			//UGCrosses					=5,	
			sptlWithin					=6,		// 被包含
			sptlContains				=7,		// 包含
			//UGExtentIntersect			=8,	
			//UGRelate					=9,	

			//UGCommonPoint				=10,
			//UGCommonSegment			=11,
			//UGCentroidInPolygon		=12,
			sptlCross					=13		// 穿越
		};

	public:
		//!	\brief	检查目标数据集中指定对象，所关联的源数据集中的对象是否在有效范围内
		UGbool IsInOrgRange(UGuint nCount) { return nCount >= m_nOrgMinCard && nCount <= m_nOrgMaxCard; }

		//!	\brief	检查源数据集中指定对象，所关联的目标数据集中的对象是否在有效范围内
		UGbool IsInDestRange(UGuint nCount) { return nCount >= m_nDestMinCard && nCount <= m_nDestMaxCard; }

	public:
		//! \brief	构造
		UGRelRule(UGuint nID, UGuint nRelClsID, UGint nOrgSubtype, UGuint nOrgMinCard, UGuint nOrgMaxCard, \
			UGint nDestSubtype, UGuint nDestMinCard, UGuint nDestMaxCard, SpatialType nSpatialType):m_nID(nID), m_nRelClsID(nRelClsID), \
			m_nOrgSubtype(nOrgSubtype), m_nOrgMinCard(nOrgMinCard), m_nOrgMaxCard(nOrgMaxCard), m_nDestSubtype(nDestSubtype), \
			m_nDestMinCard(nDestMinCard), m_nDestMaxCard(nDestMaxCard), m_nSpatialType(nSpatialType) {}

		//! \brief	拷贝构造
		UGRelRule(const UGRelRule &relRule):m_nID(relRule.m_nID), m_nRelClsID(relRule.m_nRelClsID), \
			m_nOrgSubtype(relRule.m_nOrgSubtype), m_nOrgMinCard(relRule.m_nOrgMinCard), m_nOrgMaxCard(relRule.m_nOrgMaxCard), \
			m_nDestSubtype(relRule.m_nDestSubtype), m_nDestMinCard(relRule.m_nDestMinCard), \
			m_nDestMaxCard(relRule.m_nDestMaxCard), m_nSpatialType(relRule.m_nSpatialType) {}

		UGRelRule():m_nID(0), m_nRelClsID(0), m_nOrgSubtype(0), m_nOrgMinCard(0), m_nOrgMaxCard(0), \
			m_nDestSubtype(0), m_nDestMinCard(0), m_nDestMaxCard(0), m_nSpatialType(UGRelRule::sptlNone) {}

	public:
		//!	\brief	关系规则的ID
		UGuint m_nID;

		//!	\brief	关系规则所属关系类的ID
		UGuint m_nRelClsID;

		//!	\brief	源数据集的子类ID
		UGint m_nOrgSubtype;

		//!	\brief	源数据集中对象被关联的范围
		UGuint m_nOrgMinCard;
		UGuint m_nOrgMaxCard;

		//!	\brief	目标数据集的子类ID
		UGint m_nDestSubtype;

		//!	\brief	目标数据集中对象被关联的范围
		UGuint m_nDestMinCard;
		UGuint m_nDestMaxCard;

		//! \brief	空间规则（包含、相交等）
		UGRelRule::SpatialType m_nSpatialType;
	};


	//!	\brief	记录某一数据集中的关联对象
	typedef struct ENGINE_API RelObjects
	{
		//! \brief	构造
		RelObjects() {}
		RelObjects(const UGString &strName, const UGArray<UGint> &arrIDs):strDtName(strName) { objIDs.Copy(arrIDs); }


		//!	\brief	拷贝构造
		RelObjects(const RelObjects &relObjs):strDtName(relObjs.strDtName) { objIDs.Append(relObjs.objIDs); }


		//!	\brief	源或目标数据集的名称
		UGString strDtName;

		//!	\brief	指定数据集中参与到关系类中的目标
		UGArray<UGint> objIDs;

	} UGRelObjects;


	//!	\brief	定义例外对象集
	struct ENGINE_API ExclusionObjects : public RelObjects
	{
		//!	\brief	构造
		ExclusionObjects():nRelClassID(0) {}
		ExclusionObjects(const UGString &strName, UGint nRelClsID, \
			const UGArray<UGint> &arrIDs):RelObjects(strName, arrIDs), nRelClassID(nRelClsID) {}

		//!	\brief	拷贝构造
		ExclusionObjects(const ExclusionObjects &exclsObjs):RelObjects(exclsObjs.strDtName, exclsObjs.objIDs), \
			nRelClassID(exclsObjs.nRelClassID) {}

		//!	\brief	关系类名称（指明对象是在哪个关系类中作为例外对象）
		UGint nRelClassID;
	};

	typedef struct ExclusionObjects UGExclusionObjects;


	//!	\brief	定义例外关系
	typedef struct ENGINE_API ExclusionRelation
	{
		//!	\brief	构造
		ExclusionRelation():nRelClassID(0), nOrgObjectID(0), nDestObjectID(0) {}
		ExclusionRelation(UGint nRelClsID, UGint nOrgObjID, UGint nDestObjID):nRelClassID(nRelClsID), \
			nOrgObjectID(nOrgObjID), nDestObjectID(nDestObjID) {}

		//!	\brief	拷贝构造
		ExclusionRelation(const ExclusionRelation &exclsRelation):nRelClassID(exclsRelation.nRelClassID), \
		nOrgObjectID(exclsRelation.nOrgObjectID), nDestObjectID(exclsRelation.nDestObjectID) {}

		//!	\brief	关系类的ID
		UGint nRelClassID;

		//!	\brief	源数据集中参与该关系的对象ID
		UGint nOrgObjectID;

		//!	\brief	目标数据集中参与该关系的对象ID
		UGint nDestObjectID;

	} UGExclusionRelation;


	//!	\brief	定义例外关系集
	typedef UGArray<UGExclusionRelation> UGExclusionRelations;


	//! \brief 定义非法信息
	class ENGINE_API UGIllegalMsg
	{
	public:
		//!	\brief	违反规则的类型
		enum IllegalType
		{
			illNoRelation			= 0, // 对象没有参与或建立任何关联
			illOriginMin			= 1, // 违反了对目标到源的最小约束
			illOriginMax			= 2, // 违反了对目标到源的最大约束
			illDestinationMin		= 3, // 违反了对源到目标的最小约束
			illDestinationMax		= 4, // 违反了对源到目标的最大约束
			illSpatial				= 5  // 违反了对空间规则的约束
		};

	public:
		//! \brief	构造
		UGIllegalMsg():m_IllegalType(illNoRelation) {}
		UGIllegalMsg(const UGIllegalMsg &illMsg):m_relRule(illMsg.m_relRule), m_relObjects(illMsg.m_relObjects), \
			m_strRelClassName(illMsg.m_strRelClassName), m_IllegalType(illMsg.m_IllegalType) {}

	public:
		//!	\brief	违反的约束规则
		UGRelRule m_relRule;

		//! \brief	违反约束规则的各关联对象
		UGRelObjects m_relObjects;

		//! \brief	违反的是哪个关系类（名称）中的规则
		UGString m_strRelClassName;

		//!	\brief	指示违反的是约束规则中的哪一部分（即对源或目标的约束部分，还是空间约束部分）
		IllegalType m_IllegalType;
	};


	//! \brief	记录关系类的一些基本信息
	typedef struct ENGINE_API RelationshipClassInfo
	{
		//! \brief	关系类的关联类型：一对一，一对多，多对多
		enum CardinalityType 
		{ 
			ctOneToOne = 1, 
			ctOneToMany = 2, 
			ctManyToMany = 3
		};

		//! \brief	消息通知的方向：无，向前（源到目标），向后（目标到源），向前向后都有
		enum NotifyDirectory 
		{
			ndNone = 0, 
			ndForward = 1, 
			ndBackward = 2, 
			ndBoth = 3
		};


		//!	\brief	初始化一些成员
		RelationshipClassInfo():cardType(ctOneToOne), notifyDir(ndNone), bComposition(FALSE), \
			bHasRelTable(FALSE) {}

		//! \breif	拷贝构造
		RelationshipClassInfo(const RelationshipClassInfo &relInfo):strName(relInfo.strName), strTableName(relInfo.strTableName), strOwner(relInfo.strOwner), \
			strOrgDtName(relInfo.strOrgDtName), strDestDtName(relInfo.strDestDtName), strForwardLable(relInfo.strForwardLable), \
			strBackwardLable(relInfo.strBackwardLable), cardType(relInfo.cardType), notifyDir(relInfo.notifyDir), \
			bComposition(relInfo.bComposition), bHasRelTable(relInfo.bHasRelTable), \
			strOrgPK(relInfo.strOrgPK), strDestPK(relInfo.strDestPK), strOrgFK(relInfo.strOrgFK), strDestFK(relInfo.strDestFK) {}


		//! \brief	关系类数据集的名称
		UGString strName;

		//! \brief	关系类数据集表名
		UGString strTableName;

		//! \brief	关系类的拥有者（为权限扩展保留）
		UGString strOwner;

		//! \brief	源数据集名称（这里使用数据集名称是方便组件层的调用，类库中使用数据集的指针）
		UGString strOrgDtName;

		//! \brief	目标数据集名称
		UGString strDestDtName;

		//! \brief	源到目标的关系说明标签
		UGString strForwardLable;

		//! \brief	目标到源的关系说明标签
		UGString strBackwardLable;

		//! \brief	关联类型
		CardinalityType cardType;

		//! \brief	消息通知方向
		NotifyDirectory notifyDir;

		//! \brief	是否为复合关系
		UGbool bComposition;

		//! \brief	是否要创建关联表
		UGbool bHasRelTable;

		//! \brief	源数据集主键（该主键与数据库中的主键不是一回事）
		UGString strOrgPK;

		//! \brief	目标数据集主键（该主键与数据库中的主键不是一回事）
		UGString strDestPK;

		//! \brief	关联表中参照到源数据集的外键
		UGString strOrgFK;

		//! \brief	关联表中参照到目标数据集的外键
		UGString strDestFK;

	} UGRelClassInfo;


	class UGDatasetRelClassManager;

	//!	\brief	定义关系类
	class ENGINE_API UGDatasetRelClass : public UGTable
	{

	public:
		//! \brief	构造
		UGDatasetRelClass();
		UGDatasetRelClass(UGDataSource *pDs);

		//!	\brief	析构
		virtual ~UGDatasetRelClass();

	public:
		//! \brief	根据关系类信息创建关系类
		UGbool Create(const UGRelClassInfo &rclsInfo);

		//!	\brief	创建有关联属性表的关系类
		//	\param	fldInfos[IN]	关系类的属性字段
		UGbool Create(const UGRelClassInfo &rclsInfo, const UGFieldInfos &fldInfos);

		//!	\brief	创建有关联属性表的关系类
		//	\param	DtvTable[IN]	关联表对应的属性数据集
		UGbool Create(const UGRelClassInfo &rclsInfo, UGDatasetVector* pDtvTable);
		
		//! \brief  追加记录
		//  \param  pSrcRecordset 关联表记录集指针[in]
		virtual UGbool Append(UGRecordset* pSrcRecordset);

		//!	\brief	创建有关联属性表的关系类
		UGbool SetRelClassInfo(const UGRelClassInfo &relInfo);

		//!	\brief	获取关系类数据集的类型
		virtual UGDataset::DatasetType GetType() const { return RelClass; }

		//!	\brief	获取关系类数据集的名称
		virtual UGString GetName() { return m_RelClassInfo.strName; }

		//!	\brief	获取关系类属性表的名称
		virtual UGString GetTableName() { return m_strTableName; }

		//! \brief	获取关系类基本信息
		void GetRelClassInfo(UGRelClassInfo &result) const;


		//!	\brief	获取关联规则的数目
		UGint GetRelRuleCount() const { return (UGint)m_RelRules.GetSize(); }

		//! \brief	创建一个关联规则
		UGbool CreateRelRule(UGint nOrgSubtype, UGuint nOrgMinCard, UGuint nOrgMaxCard, \
			UGint nDestSubtype, UGuint nDestMinCard, UGuint nDestMaxCard, UGRelRule::SpatialType nSpatialType);

		//!	\brief	获取所有的关联规则
		const UGArray<UGRelRule>& GetAllRelRules() const { return m_RelRules; }

		//!	\brief	获取指定的关联规则
		UGbool GetRelRuleByID(UGuint nID, UGRelRule &result) const;
		UGbool GetRelRuleByIndex(UGint nIndex, UGRelRule &result) const;

		//!	\brief	根据源和目标数据集的子类来获取关联规则
		UGbool GetRelRuleBySubtype(UGint nOrgSubType, UGint nDestSubType, UGRelRule &result) const;

		//!	\brief	删除指定的关联规则
		virtual UGbool DeleteRelRuleByID(UGuint nID) = 0;
		UGbool DeleteRelRuleByIndex(UGint nIndex);

		//!	\brief	指定源和目标数据集的子类来删除关联规则
		UGbool DeleteRelRuleBySubtype(UGint nOrgSubType, UGint nDestSubType);

		//!	\brief	删除所有的关联规则
		virtual UGbool DeleteAllRelRules() = 0;

		//!	\brief	修改指定的关联规则
		UGbool ModifyRelRuleByID(UGuint nID, UGuint nOrgMinCard, UGuint nOrgMaxCard, UGuint nDestMinCard, \
			UGuint nDestMaxCard, UGRelRule::SpatialType nSpatialRule);
		UGbool ModifyRelRuleByIndex(UGint nIndex, UGuint nOrgMinCard, UGuint nOrgMaxCard, UGuint nDestMinCard, \
			UGuint nDestMaxCard, UGRelRule::SpatialType nSpatialRule);

		//!	\brief	修改由源和目标数据集的子类唯一确定的关联规则
		UGbool ModifyRelRuleBySubtype(UGint nOrgSubType, UGint nDestSubType, UGuint nOrgMinCard, UGuint nOrgMaxCard, \
			UGuint nDestMinCard, UGuint nDestMaxCard, UGRelRule::SpatialType nSpatialRule);


		//! \brief	为指定的源数据集中的目标建立关系
		UGbool BuildRelation(UGint orgID, const UGArray<UGint> &destIDs);
		UGbool BuildRelation(UGint orgID, UGRecordset &destRecordset);

		//! \brief	为指定的目标数据集中的目标建立关系
		UGbool BuildRelation(const UGArray<UGint> &orgIDs, UGint destID);
		UGbool BuildRelation(UGRecordset &orgRecordset, UGint destID);

		//!	\brief	根据空间规则自动建立关系
		//	\remark	该接口设计为，以已建立的具体规则为依据，根据
		//			其中的空间规则自动建立相应子类间的对象关系
		UGbool BuildRelationBySptlRule();

		//!	\brief	删除为指定目标已建立起的关系
		UGbool DeleteRelation(const UGRelObjects &relObjects);
		UGbool DeleteRelation(UGRecordset &recordset);

		//!	\brief	指定源数据和目标数据集中的目标来删除关系
		UGbool DeleteRelation(UGint nOrgID, UGint nDestID);


		//!	\brief	获取指定目标的关联目标
		virtual UGbool GetRelationObjects(const UGRelObjects &relObjects, UGRelObjects &result) = 0;
		UGbool GetRelationObjects(UGRecordset &recordset, UGRelObjects &result);


		//!	\brief	有效性检查
		//	\param	errMsgs[OUT]	返回分类统计后的错误信息
		//	\return	如果检查函数成功被执行则返回TRUE，否则，返回FALSE
		UGbool CheckValid(const UGRelObjects &relObjs, UGArray<UGIllegalMsg> &errMsgs);
		UGbool CheckValid(UGRecordset &recordset, UGArray<UGIllegalMsg> &errMsgs);

		
		//!	\brief	打开关系类数据集
		virtual UGbool Open();

		//!	\brief	关闭关系类数据集
		virtual void Close();

		//!	\brief	查询关联表的内容
		virtual UGRecordset* Query(const UGQueryDef &querydef);


		//!	\brief	执行操作（此接口负责处理源和目标数据集中的对象）
		//	\param	impactObjects[OUT]	返回受影响的对象（源和目标数据集中受影响的对象）
		UGbool ExcuteOprt(const UGRelObjects &relObjects, const UGGeoAction &msg, UGArray<UGRelObjects> &arrImpactObjs);
		UGbool ExcuteOprt(UGRecordset *pRecordset, const UGGeoAction &msg, UGArray<UGRelObjects> &arrImpactObjs);

		//!	\brief	执行操作（此接口只负责相关数据集中的对象，输入数据集中的目标不理会）
		//	\param	impactObjects[OUT]	返回受影响的对象(相关数据集中受影响的对象）
		UGbool DealRelObjects(const UGRelObjects &relObjects, const UGGeoAction &msg, UGRelObjects &impactObjs);
		UGbool DealRelObjects(UGRecordset &recordset, const UGGeoAction &msg, UGRelObjects &impactObjs);
		
		//! \brief  直接处理传入的对象；
		UGbool DealRelObjectsJustInput(const UGRelObjects &relObjects, \
			const UGGeoAction &msg, UGRelObjects &impactObjs);

		//! \brief	判断是否有关联表存在
		UGbool HasRelTable();


		//! \brief 通过记录集序号释放记录集内存空间。
		//! \param nIndex 记录集序号[in]。
		//! \return 是否释放成功，成功返回TRUE，失败返回FALSE。
		virtual UGbool ReleaseRecordset(UGint nIndex);

		//! \brief 通过记录集指针释放记录集内存空间。
		//! \param *pRecordset 记录集指针[in]。
		//! \return 是否释放成功，成功返回TRUE，失败返回FALSE。
		virtual UGbool ReleaseRecordset(UGRecordset *pRecordset);


		//! \brief	获取关系类管理器
		UGDatasetRelClassManager* GetDatasetRelClassManager();


		//!	\brief	将某一具体的对象设置为本关系类的例外对象
		//	\param	bOrg[IN]	指示对象是源还是目标数据集中的
		UGbool SetExclusionObject(UGint nObjectID, UGbool bOrg);

		//! \brief	将某一具体的关系设置为本关系类的例外关系
		//	\remark	nOrgObjectID与nDestObjectID之间确定一个具体的关系
		UGbool SetExclusionRelation(UGint nOrgObjectID, UGint nDestObjectID);

		//!	\brief	获取本关系类中的所有例外对象
		//	\param	arrExclsObjects[OUT]	返回源或目标数据集中的所有例外对象
		virtual UGbool GetAllExclusionObjects(UGArray<UGExclusionObjects> &arrExclsObjects) = 0;

		//!	\brief	获取本关系类中的所有例外关系
		virtual UGbool GetAllExclusionRelations(UGExclusionRelations &exclsRelations) = 0;

		//! \brief	从本关系类中移除指定的例外对象
		virtual UGbool RemoveExclusionObject(UGint nObjectID, UGbool bOrg) = 0;

		//!	\brief	从本关系类中移除指定的例外关系
		virtual UGbool RemoveExclusionRelation(UGint nOrgObjectID, UGint nDestObjectID) = 0;

		//!	\brief	从本关系类中移除指定对象参与的所有例外关系
		virtual UGbool RemoveExclusionRelation(UGint nObjectID, UGbool bOrg) = 0;

		//! \brief	从本关系类中移除所有的例外（包括例外对象和例外关系）
		virtual UGbool RemoveAllExclusion() = 0;

	public:
		//! \brief	返回最小高程
		virtual UGdouble GetMinZ() { return 0; }

		//! \brief	设置最小高程
		virtual void SetMinZ(UGdouble d) {}

		//! \brief	返回最大高程
		virtual UGdouble GetMaxZ() { return 0; }

		//! \brief	设置最大高程
		virtual void SetMaxZ(UGdouble d) {}

		//! \brief	返回数据集的维数
		virtual UGint GetDimension() { return 0; }

		//! \brief	判断是否是矢量数据集
		virtual UGbool IsVector() { return FALSE; }

		//! \brief	判断是否是topo数据集
		virtual UGbool IsTopoDataset() { return FALSE; }

		//! \brief	判断是否是栅格数据集
		virtual UGbool IsRaster() { return FALSE; }
		
		//! \brief 判断是否是关系类数据集
		virtual UGbool IsRelClass(){ return TRUE; }

		virtual UGbool IsLinkTable() { return FALSE; }

		//! \brief	返回数据集的范围
		virtual const UGRect2D& GetBounds() { return m_rc2Bounds; }

		//! \brief	设置数据集的范围
		virtual void SetBounds(const UGRect2D& r) {}

		//! \brief	返回空间数据编码方式
		virtual UGDataCodec::CodecType GetCodecType() { return UGDataCodec::encNONE; }

		//! \brief	设置空间数据编码方式
		virtual UGbool SetCodecType(UGDataCodec::CodecType c) { return TRUE; }

		//! \brief	返回数据集的选项信息(用四字节的整型数据代表一些属性)
		virtual UGint GetOptions() { return 0; }

		//! \brief	设置数据集的选项信息
		virtual void SetOptions(UGint nOptions) {}

	protected:
		//!	\brief	检查关系类信息是否合法，合法，则返回源和目标数据集的关联字段信息
		//	\param	infoOrgFld[OUT]		返回源数据集关联字段信息
		//			infoDestFld[OUT]	返回目标数据集关联字段信息
		UGbool CheckRelClassInfo(const UGRelClassInfo &rclsInfo, UGFieldInfo &infoOrgFld, UGFieldInfo &infoDestFld);

		//!	\brief	初始化关系类的信息
		//	\param	fldInfos[IN]	关系类的所有字段信息
		UGbool InitRelClass(const UGRelClassInfo &rclsInfo, const UGFieldInfos &fldInfos);

		//!	\brief	初始化关系类的信息
		//	\param	pDtvTabl[IN]	用作关联表的属性数据集
		UGbool InitRelClass(const UGRelClassInfo &rclsInfo, UGDatasetVector *pDtvTabl);

		//! \brief	获取下一个可用的规则ID
		virtual UGuint GetNextRelRuleID() = 0;

		//!	\brief	插入新的关联规则到数据库中
		virtual UGbool InsertRelRuleToTable(const UGRelRule &relRule) = 0;

		//!	\brief	更新数据库中的关联规则
		virtual UGbool UpdateRelRuleToTable(const UGRelRule &relRule) = 0;

		//!	\brief	将关系插入到关联表中
		//	\param	bOrg[IN]	标识指定的是源还是目标数据集中关联字段的值
		UGbool InsertRelationToTable(const UGVariant &val, UGbool bOrg, const UGArray<UGVariant> &values);

		//!	\brief	根据指定的带有空间规则的规则，自动建立对象的关系
		UGbool BuildRelationByRelRule(const UGRelRule &relRule);

		//!	\brief	（为子类扩展预留的接口）从源或目标数据集中，获取关于指定子类的记录集（空属同查）
		//			注意：外部使用时，应提前打开数据集
		UGRecordset* GetRecordsetBySubtype(UGint nSubtype, UGbool bOrg);

		//! \brief	将关系从关联表中删除
		//	\param	bOrg[IN]	标识指定的是源还是目标数据集中关联字段的值
		UGbool DeleteRelationFromTable(const UGArray<UGVariant> &values, UGbool bOrg);

		//! \brief	将关系从关联表中删除（按照指定的值，这里只删除一条记录）
		UGbool DeleteRelationFromTable(const UGVariant &valOrg, const UGVariant &valDest);

		//!	\brief	从记录集中获得各对象的SmID
		UGbool GetIDsFromRecordset(UGRecordset &recordset, UGArray<UGint> &ids);
	

		//!	\brief	从数据库中查询关联对象
		//			注意：调用者最好在外面将另一对应的数据集打开
		//	\param	bDynamic[IN]	指示是否返回动态的记录集
		//			bQueryGeometry[IN]	指示查询是否同时查询出几何信息
		UGRecordset* SearchRelObjects(const UGRelObjects &rObjects, UGbool bDynamic = FALSE, UGbool bQueryGeometry = FALSE);


		//!	\brief	检查是否有同名的数据集或同名的表存在
		virtual UGbool CheckNameAvailable(const UGString &strDtName, const UGString &strTableName) = 0;

		//!	\brief	创建关联表
		//	\param	fldInfos[IN]	关系类的所有字段信息
		virtual UGbool CreateRelTable(const UGFieldInfos &fldInfos) = 0;

		//! \brief 根据属性数据集创建关联表（复制属性数据集的表）
		//	\param	pdtTable[IN]	属性数据集
		virtual UGbool CreateRelTableFromDt(UGDatasetVector* pdtTable){return FALSE;}

		//!	\brief	删除关联表
		virtual void DropRelTable() = 0;

		//!	\brief	分别在源和目标数据集中为关联字段创建索引
		virtual UGbool BuildIndexForPKAndFK() = 0;

		//!	\brief	向SmRegister和SmRelations表中插入相关信息
		virtual UGbool InsertRClsInfoToTable() = 0;

		//!	\brief	预留接口，为将来子类扩展准备，获取某一指定对象对应的子类
		UGint GetRelObjectSubtype(UGint nID, UGRecordset &recordset) { return 0; }

		//! \brief	检查源和目标对象的空间规则是否符合指定空间规则的要求
		UGbool CheckRelObjectSpatial(const UGGeometry *pGeoOrg, const UGGeometry *pGeoDest, UGRelRule::SpatialType nSpatialType);

		//! \brief	精简代码时从接口CheckValid抽离出来的函数，主要的作用是完成非法信息的统计和分类
		//	\param	nObjIDCurr[IN]		当前要进行统计和检查的对象ID
		//			arrValCompare[IN]	与nObjIDCurr指示对象相关的映射关联值
		//			pRcdsetObj[IN]		nObjIDCurr指示对象所属的记录集
		//			relIDs[IN]			可能的关联对象ID集合
		//			relVals[IN]			可能的关联对象相应的关联值
		//			pRcdsetRel[IN]		可能的关联对象所属的记录集
		//			exclsRelations[IN]	例外关系
		//			errMsgs[OUT]		返回统计分类后的错误信息
		void StatisticIllegalMsg(UGint nObjIDCurr, const UGArray<UGVariant> &arrValCompare, UGRecordset *pRcdsetObj, \
			const UGArray<UGint> &relIDs, const UGArray<UGVariant> &relVals, UGRecordset *pRcdsetRel, \
			const UGExclusionRelations &exclsRelations, UGArray<UGIllegalMsg> &errMsgs);


		//!	\brief	根据消息内容修改几何对象
		void ModifyGeometryByAction(UGRecordset *pRecordset, const UGGeoAction &actMsg, UGArray<UGint> &idsDeal);

		//! \brief	执行动作的时候，关联对象是否需要响应
		//	\param	strDtName[in]	是当前执行动作的对象 所在的数据集名字，通过关系类的消息方向，判断关联对象是否需要相应
		//			actMsg[IN]		要发送的消息
		UGbool NeedSendMessage(const UGString &strDtName, const UGGeoAction &actMsg);


		//!	\brief	从SmRelRules系统表中读取规则
		virtual UGbool QueryRules() = 0;


		//!	\brief	向数据库中写入例外信息
		virtual UGbool InsertExclusionToTable(UGExclusionRelation &exclsRelation) = 0;


		//!	\brief	对待检查的对象进行过滤，从中剔除掉例外对象
		UGbool FilterExclsObjects(const UGRelObjects &relObjs, UGRelObjects &result);

	protected:
		//! \brief	各关联规则
		UGArray<UGRelRule> m_RelRules;

		//! \brief	源数据集指针
		UGDataset *m_pOrgDt;

		//! \brief	目标数据集指针
		UGDataset *m_pDestDt;

		//! \brief	关系类的基本信息
		UGRelClassInfo m_RelClassInfo;

		//! \brief	关系类属性表的名字
		UGString m_strTableName;

		//!	\brief	基类里面的累赘物，不用管它
		UGRect2D m_rc2Bounds;

		//! \brief 记录集指针的集合，打开的所有记录集必须放在这里，否则不知道怎么释放
		UGArray<UGRecordset*> m_Recordsets;
	};
}

#endif

