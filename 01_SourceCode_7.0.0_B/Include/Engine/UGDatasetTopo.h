// UGDatasetTopo.h: interface for the UGDatasetTopo class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_UGDATASETTOPO_H__6F79F774_FF2A_4EB2_AB64_A5958D572828__INCLUDED_)
#define AFX_UGDATASETTOPO_H__6F79F774_FF2A_4EB2_AB64_A5958D572828__INCLUDED_

#include "Engine/UGDataset.h"
#include "Engine/UGDatasetVector.h"

namespace UGC{

//##ModelId=4820305302FD
	struct UGTopoDTPricision
	{
	//##ModelId=4820305302FF
		UGDatasetVector *pDataset;
	//##ModelId=48203053030D
		UGint nPricision;
	};

//##ModelId=48203053030E
	struct UGTopoRule
	{
	//##ModelId=482030530310
		UGint nID;
	//##ModelId=48203053031C
		UGDatasetVector *pDataset;
	//##ModelId=48203053031D
		UGDatasetVector *pCheckDataset;
	//##ModelId=48203053031E
		UGint nRule;
	};

	struct UGTopoRuleEx
	{
		//##ModelId=48203053031C
		UGString  strDatasetName;
		//##ModelId=48203053031D
		UGString strCheckDatasetName;
		//##ModelId=48203053031E
		UGint nRule;
	};

//##ModelId=48203053033C
class ENGINE_API UGDatasetTopo : public UGDataset
{
public: 
	//##ModelId=48203053033E
	UGDatasetTopo();
	//##ModelId=48203053034B
	virtual ~UGDatasetTopo();

public:
	//##ModelId=482030540001
	enum TopoRuleMode
	{
		                                             //规则名               操作类型  结果类型
		
		RegionNoOverlap                       =  1,  //面内无重叠           面     -> 面

		RegionNoGaps                          =  2,  //面内无缝隙           面     -> 面

		RegionNoOverlapWith                   =  3,  //面与面无重叠         面和面 -> 面

		RegionCoveredByRegionClass            =  4,  //面被多个面覆盖       面和面 -> 面

		RegionCoveredEach                     =  5,  //面与面相互覆盖       面和面 -> 面

		RegionContainedByRegion               =  6,  //面被面包含           面和面 -> 面

		RegionBoundaryCoveredByLine           =  7,  //面边界被线覆盖       面和线 -> 线

		RegionBoundaryCoveredByRegionBoundary =  8,  //面边界被面边界覆盖   面和面 -> 线

		RegionContainPoint                    =  9,  //面包含点             面和点 -> 面

		LineNoIntersection                    = 10,  //线内无相交           线     -> 点

		LineNoOverlap                         = 11,  //线内无重叠           线     -> 线

		LineNoDangles                         = 12,  //线内无悬线           线	   -> 点

		LineNoPseudonodes                     = 13,  //线内无假结点         线     -> 点

		LineNoOverlapWith                     = 14,  //线与线无重叠         线和线 -> 线

		LineNoIntersectionOrInteriorTouch     = 15,  //线内无相交或内部接触 线     -> 点

		LineNoSelfOverlap                     = 16,  //线内无自交叠         线     -> 线

		LineNoSelfIntersection                = 17,  //线内无自相交         线     -> 点

		LineCoveredByLine                     = 18,  //线被线覆盖           线和线 -> 线

		LineCoveredByRegionBoundary           = 19,  //线被面边界覆盖       线和面 -> 线

		LineEndpointCoveredByPoint            = 20,  //线端点被点覆盖       线和点 -> 点

		PointCoveredByLine                    = 21,  //点被线覆盖           点和线 -> 点

		PointCoveredByRegionBoundary          = 22,  //点被面边界覆盖       点和面 -> 点

		PointContainedByRegion                = 23,  //点被面包含           点和面 -> 点

		PointCoveredByLineEndpoint            = 24,  //点被线端点覆盖       点和线 -> 点

		NoMultipart                           = 25,  //无复杂对象           (线、面) -> (线、面)

		PointNoIdentical                      = 26,  //无重复点             点	   -> 点

		PointNoContainedByRegion              = 27,  //点不被面包含         点和面 -> 点

		LineNoIntersectionWithRegion          = 28,  //线与面无相交         线和面 -> 线

		RegionNoOverlapOnBoundary             = 29,  //面边界无交叠         面和面 -> 线

		RegionNoSelfIntersection              = 30,  //面内无自相交         面     -> 点

		LineNoIntersectionWith                = 31,  //线与线无相交         线和线 -> 点

		MustBeLargerThanTolerance			  = 32,  //节点距离必须大于容限 (点、线、面)和(点、线、面) -> 点

		MustExistIntersectVertex              = 33,  //线段相交处必须存在交点 (线、面)和(线、面) -> 点

		MustMatchWithVertex                   = 34,  //节点之间必须互相匹配 (点、线、面)和(点、线、面) -> 点

		NoRedundantVertices					  = 35,  //线对象或面边界无冗余节点		  (线、面) -> 点

		LineNoSharpAngle					  = 36,   //线内无打折          线      ->点
	};
	
	//! \brief 返回数据集类型
	//##ModelId=48203053034D
	virtual DatasetType GetType() const
	{
		return Topo;
	};

	//! \brief 返回数据集对应表名
	//##ModelId=48203053034F
	virtual UGString GetTableName();

	//! \brief 返回最小高程
	//##ModelId=482030530351
	virtual UGdouble GetMinZ();

	//! \brief 设置最小高程
	//##ModelId=48203053035C
	virtual void SetMinZ(UGdouble d);

	//! \brief 返回最大高程
	//##ModelId=48203053035F
	virtual UGdouble GetMaxZ();

	//! \brief 设置最大高程
	//##ModelId=48203053036B
	virtual void SetMaxZ(UGdouble d);

	//! \brief 返回数据集的维数
	//##ModelId=48203053036E
	virtual UGint GetDimension();

	//! \brief 判断是否是矢量数据集
	//##ModelId=482030530370
	virtual UGbool IsVector();

	//! \brief 判断是否是topo数据集
	//##ModelId=48203053037A
	virtual UGbool IsTopoDataset();

	//! \brief 判断是否是栅格数据集
	//##ModelId=48203053037C
	virtual UGbool IsRaster();

	//! \brief 判断是否是关系类数据集
	virtual UGbool IsRelClass();

	//##ModelId=48203053037E
	virtual UGbool IsLinkTable()
	{
		return FALSE; 
	};

	//! \brief 返回数据集的范围
	//##ModelId=482030530380
	virtual const UGRect2D& GetBounds()
	{
		return m_rc2Bounds;
	};

	//! \brief 设置数据集的范围
	//##ModelId=48203053038B
	virtual void SetBounds(const UGRect2D& r);

	//! \brief 返回空间数据编码方式
	//##ModelId=48203053038E
	virtual UGDataCodec::CodecType GetCodecType();
	
	//! \brief 设置空间数据编码方式
	//##ModelId=482030530390
	virtual UGbool SetCodecType(UGDataCodec::CodecType c);

public:
	//##ModelId=482030530399
	UGdouble GetInterval();
	//##ModelId=48203053039A
	void SetInterval(UGdouble dInterval);

	//! \brief 保存脏区
	//! \param *pDatasetVector [in] 数据集
	//! \param *pGeo [in] 脏区
	//! \return 
	//! \remarks 保存关联数据集的脏区，如果脏区为空，则把当前关联数据集的脏区设为空
	//!			 如果数据集指针为空，则清空拓扑数据集脏区		
	//! \attention 
	//##ModelId=48203053039C
	UGbool SaveDirtyRegion(UGDatasetVector *pDV = NULL, UGGeoRegion *pGeo = NULL);

	//added by luhao 2009.04.15
	//! \brief   擦除脏区
	//! \param   pEraseRegion 擦除多边形[in] 
	//! \return  成功返回TRUE，失败返回FALSE
	//! \remarks 添加原因:在UGTopoProcess::ValidateTopology()方法中，允许用户传入一生效多边形，
	//!                   拓扑生效后，应该更新脏区，即生效多边形与脏区相交的区域不再是脏区
	UGbool EraseDirtyArea(const UGGeoRegion *pEraseRegion);
public:
	//topo相关
	//! \brief 向Topo数据集里添加一个数据集
	//! \param *pDatasetVector [in] 数据集
	//! \param nPricision [in] 数据集精度范围为1-5,值越大精度越低，当nPricision超出1-5范围时，按最小值1来处理
	//! \return 。
	//! \remarks 必须是同一个数据源的数据集
	//! \attention 
	//##ModelId=48203053039E
	virtual UGbool AddDataset(UGDatasetVector *pDatasetVector,UGint nPricision = 1);

	//! \brief 从Topo数据集里移除一个关联数据集方法
	//! \param *pDatasetVector [in] 数据集
	//! \attention 
	virtual UGbool RemoveDataset(UGDatasetVector *pDatasetVerctor);

	//! \brief 为Topo数据集添加Topo规则
	//! \param pDatasetVector	源数据集[in]	
	//! \param pdatasetCheck	目标数据集[in]
	//! \param nRule			Topo规则
	//! \remarks 当目标数据集为空时，为数据集自身建立拓扑关系
	//##ModelId=4820305303A9
	virtual UGbool AddRule(UGDatasetVector *pDatasetVector,TopoRuleMode nRule,UGDatasetVector *pDatasetCheck = NULL);

	//! \brief 可以选择数据集及有关联的数据集来确定删除Rule
	//!      　要注意一个或两个数据集有多个Rule的情况，小心删错了噢
	//##ModelId=4820305303B2
	virtual UGbool DeleteRule(UGDatasetVector *pDatasetVector,TopoRuleMode nRule,UGDatasetVector *pDatasetCheck = NULL);

	//! \brief 获得Topo子数据集,基类实现
	//##ModelId=4820305303BB
	virtual UGbool GetAllRelation(UGArray<UGTopoDTPricision> &aryTopoRelations);

	//##ModelId=4820305303BE
	virtual UGbool GetAllRules(UGArray<UGTopoRule> &aryRules);

	//! \brief 获得Topo错误数据集,基类实现
	//##ModelId=4820305303C1
	virtual UGDatasetVector * GetPointErrorDataset();
	//##ModelId=4820305303C3
	virtual UGDatasetVector * GetLineErrorDataset();
	//##ModelId=4820305303C5
	virtual UGDatasetVector * GetRegionErrorDataset();
	//##ModelId=4820305303C9
	virtual UGDatasetVector * GetDirtyAreaDataset();

	//! \brief 获取脏区
	//! \param *pDatasetVector [in] 数据集
	//! \return 返回脏区
	//! \remarks 当数据集指针非空时获取关联数据集的脏区，否则获取拓扑数据集的脏区
	//! \attention 
	//##ModelId=4820305303CB
	UGGeoRegion * GetDirtyArea(UGDatasetVector *pDV = NULL);

	//! \brief 拓扑规则导出成XML文件
	virtual UGbool ToopRuleToXML(const UGString &strXMLFile);
	//! \brief 直接从XML导入拓扑规则
	virtual UGbool ToopRuleFromXML(const UGString &strXMLFile);

	//! \brief 解析XML格式的拓扑规则
	//! \param &strXML 拓扑规则的XML文件[in]
	//! \param &aryTopoRuleInfos 拓扑规则信息数组[out]
	//! \return 解析失败则返回FALSE
	virtual UGbool ParseXML(const UGString &strXMLFile, UGArray<UGTopoRuleEx> &aryTopoRuleInfos);

	//! \brief 从拓扑规则信息数组导入拓扑规则
	//! \param &aryTopoRuleInfos 拓扑规则信息数组[in]
	virtual void ImportTopoRule(const UGArray<UGTopoRuleEx> &aryTopoRuleInfos);

	//! \brief 获取关联数据集
	virtual UGbool GetRelateDatasets(UGArray<UGDatasetVector *> &aryRelateDataset);

	//! \brief 获取关联数据集数
	virtual UGint GetRelationDtCount();

	//! \brief 根据索引返回关联数据集
 	virtual UGDatasetVector* GetRelationDtTAt(UGint nIndex, UGint &nPricision);

	//!	\brief 设置关联数据集精度
	virtual UGbool SetRelationDtPrecision(UGDatasetVector *pDatasetVector, UGint nPricision);

	//! \brief 移除所有关联数据集
	virtual void RemoveAllDataset();

	//! \brief 获取拓扑规则数
	virtual UGint GetTopoRuleCount();

	//! \brief 索引返回拓扑规则
	virtual UGTopoRule GetTopoRuleAt(UGint nIndex);

	//! \brief 根据索引修改拓扑规则
	virtual	UGbool SetTopoRuleAt(UGint nIndex, UGDatasetVector *pDataset, UGint nRule, UGDatasetVector *pCheckDataset = NULL);

	//! \brief 删除所有拓扑规则
	virtual void DeleteAllTopoRule();

	//! \brief 判断数据集是否有某个选项信息
	virtual UGbool HasFlag(UGint nOption) const;

	//! \brief 注册选项信息
	virtual UGbool RegisterOption(UGint nOption);

	//! \brief 反注册选项信息
	virtual UGbool UnRegisterOption(UGint nOption);

protected:
	//##ModelId=4820305303CC
	virtual UGbool AddSubDataset(UGTopoDTPricision structTopo);
	
public:
	//! \brief 数据集的子数据集指针
	//##ModelId=4820305303CF
	UGSubDtArray m_arySubDataset;
	//##ModelId=4820305303D0
	UGArray<UGTopoDTPricision> m_aryTopoRelationDts;
	//##ModelId=4820305303D8
	UGArray<UGTopoRule> m_aryTopoRules;
	//##ModelId=4820305303D9
	UGString m_strName;
	//##ModelId=4820305303DA
	UGint m_nOptions;
	//##ModelId=4820305303DB
	UGRect2D m_rc2Bounds;
	//##ModelId=482030540000
	UGdouble m_dInterval;
};

}

#endif // !defined(AFX_UGDatasetTopo_H__6F79F774_FF2A_4EB2_AB64_A5958D572828__INCLUDED_)

