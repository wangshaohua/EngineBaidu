/*! \file	 UGRecordset.h
 *  \brief	 记录集类定义文件
 *  \author	 ugc team
 *  \attention 
 *  Copyright(c) 2000-2010  SuperMap GIS Technologies,Inc.<br>
 *  All Rights Reserved
 *  \version $Id: UGRecordset.h,v 1.33 2010/03/24 01:20:47 wangmao Exp $
 */

#ifndef UGRECORDSET_H
#define UGRECORDSET_H

#include "Engine/UGQueryDef.h"
#include "Engine/ugeng.h"
#if !defined SYMBIAN60 /*&& !defined  OS_ANDROID && !defined (IOS)*/
#include "Geometry/UGFeature.h"
#endif
#include "Geometry/UGGeometry.h"
#include "Toolkit/UGRectUInt.h"
#include "Geometry/UGGeoCompound.h"
#include "Engine/UGTableRecordset.h"
#include "Toolkit/UGStringW.h"
#include "Engine/UGBulkEditManager.h"
#include "Toolkit/UGLogFile.h"

namespace UGC {

class UGTable;
class UGDatasetVector;
class UGRecordset;
class UGDatasetRelClass;
class UGBulkEditManager;

#define UGBULKEDITGEOSIZE 65536
#define MAXBINARYFIELDSIZE	1024 * 5

//! \brief 子记录集，用于描述复合记录集
struct SubRecordset 
{
	//! \brief 数据集名称
	UGString  strDtName;
	//! \brief 记录数
	UGint nRecordCount;
	//! \brief 记录集
	UGRecordset *pRecordset;

	SubRecordset()
	{
		nRecordCount = -1;
		pRecordset = NULL;
	}

};
//! \brief 记录集类
//##ModelId=4820305001A5
#ifdef SYMBIAN60
class ENGINE_APIC UGRecordset :public UGTableRecordset
#else
class ENGINE_API UGRecordset :public UGTableRecordset
#endif
{	
public:
	//! \brief 编辑模式
	//##ModelId=482030500235
	enum EditMode 
	{
		//##ModelId=482030500243
		EditNone			= 0x00000000, //! 未做任何编辑
		//##ModelId=482030500244
		EditAdd				= 0x00000001, //! 已执行过AddNew操作
		//##ModelId=482030500245
		EditInProgress		= 0x00000002, //! 正在编辑
		//##ModelId=482030500261
		EditSetFieldValue	= 0x00000004, //! 已更改属性数据 
		//##ModelId=482030500262
		EditSetGeometry		= 0x00000008, //! 已执行过SetGeometry操作
		//##ModelId=482030500263
		EditDeleted			= 0x00000010, //! 已删除记录
		EditBulkOperate		= 0x00000100  //! 批量更新标志
	};
	
public:
	//! \brief 构造函数
	//##ModelId=4820305001B5
	ENGINE_APIF UGRecordset();

	//##ModelId=483BB70802BF
	ENGINE_APIF UGRecordset(UGDatasetVector* pDatasetVector);
	//! \brief 析构函数
	//##ModelId=4820305001B6
	virtual ENGINE_APIF ~UGRecordset();
public:
	//! \brief 获取记录集对应的数据集。
	//! \return 矢量数据集指针。
	//##ModelId=4820305001B8
	ENGINE_APIF UGDatasetVector* GetDataset() const;

	//! \brief 获取记录集对应的数据集。
	//! \return 关系类数据集指针。
	ENGINE_APIF UGDatasetRelClass* GetDatasetRel() const;
	
	//! \brief 判断记录集是否有属性数据。
	//! \return 有属性数据返回TRUE，没有返回FALSE。
	//##ModelId=4820305001BA
	ENGINE_APIF UGbool HasDBInfo();

	//! \brief 判断记录集是否有几何数据。
	//! \return 有几何数据返回TRUE，没有返回FALSE。。
	//##ModelId=4820305001BB
	ENGINE_APIF UGbool HasGeometry();

	//! \brief 判断指定字段的字段值在动态分段关系中是否可以修改
	//! \param strName 指定的字段名称
	//! \param varVal  指定字段的指定值
	//! \param ID	   对应的记录ID
	//! \return 返回成功说明该字段值可以设置，返回失败则说明在对应的动态分段关系中该值是非法的
	ENGINE_APIF UGbool IsAvailableForDyn(const UGString &strName, const UGVariant &varVal, const UGint ID);

	//! \brief 删除数据集时删除对应的动态分段记录
	ENGINE_APIF void RemoveDynRecord();

	//! \brief 删除所有记录
	//##ModelId=4820305001BC
	virtual ENGINE_APIF UGbool DeleteAll();

	//! \brief 按某种统计方法统计某个字段
	//! \param &strField 被统计字段
	//! \param nMode 统计模式,共六种"MAX","MIN","AVG","SUM","STDDEV","VARIANCE"
	//! \attention 各引擎统计关键字稍有不同,详见"各数据库的统计函数.doc"
	//##ModelId=4820305001C5
	virtual ENGINE_APIF UGVariant Statistic(const UGString& strField,
		UGStatisticMode nMode);

	//! \brief 刷新记录集,一般就是重新查询一遍
	//##ModelId=4820305001C9
	virtual ENGINE_APIF UGbool Refresh();

	//! \brief 复制字段值,strSrcField和
	//!        strDestField必须都存在且字段类型匹配
	//##ModelId=4820305001CB
	virtual ENGINE_APIF UGbool CopyField(const UGString& strSrcField,
		const UGString& strDestField);
	
	//! \brief 获取当前记录的ID
	//##ModelId=4820305001CF
	virtual ENGINE_APIF UGint GetID();

	//! \brief 直接读出几何对象的指针,对于把所有数据都读到内存中的引擎(如dgn)来说，
	//!        不需要拷贝几何对象，外面也不要去删除它,这样可以加快访问速度
	//##ModelId=4820305001D4
	virtual ENGINE_APIF UGbool GetGeometryDirect(UGGeometry*& pGeometry);

	//! \brief 取得几何对象，返回的几何对象指针在函数内分配内存，
	//!        外面负责删除，否则会有内存泄漏
	//##ModelId=4820305001D7
	virtual ENGINE_APIF UGbool GetGeometry(UGGeometry*& pGeometry);

	//! \brief 设置当前记录的几何对象
	//##ModelId=4820305001DE
	virtual ENGINE_APIF UGbool SetGeometry(UGGeometry &geometry);

	//! \brief 取得几何对象的三维Bounds
	//##ModelId=4820305001DA
	ENGINE_APIF UGbool GetGeometryBounds(UGRect2D &rc2Bounds,double& dMinZ,double& dMaxZ);

	//! \brief 给显示调用的接口
	virtual ENGINE_APIF UGbool GetWordRectBounds(UGRectUInt & /*rcWdRectBounds*/){return FALSE;};

	//! \brief 判断记录集是否为空
	//##ModelId=4820305001E4
	ENGINE_APIF UGbool IsEmpty();

	//! \brief 通过ID定位记录指针
	//##ModelId=4820305001E5
	virtual ENGINE_APIF UGbool SeekID(UGint nID);

	//! \brief 更新，提交修改
	//! \return UGint 成功则返回更新对象的ID,否则返回-1
	//! \remark 在AddNew和Edit之后都需要调用Update来完成编辑
	//##ModelId=4820305001E8
	virtual ENGINE_APIF UGint Update();

	//! \brief 取消修改
	//##ModelId=4820305001EA
	virtual ENGINE_APIF UGbool CancelUpdate();
	
	//! \brief 开始修改数据
	//##ModelId=4820305001EC
	virtual ENGINE_APIF UGbool Edit();

	//! \brief 设置批量更新标志
	//! \param bIsEditBulkOperate [in] TRUE为开始批量更新，FALSE为取消批量更新标志
	virtual ENGINE_APIF UGbool EditBulk(UGbool bIsEditBulkOperate);

	//! \brief 封装了UDB编辑开启事务，该接口对其他引擎无效
	//! \mark 开启后请务必关闭 
	virtual ENGINE_APIF UGbool StartQuickEdit();

	//! \brief 封装了UDB编辑关闭事务，该接口对其他引擎无效
	//! \mark 开启后请务必关闭 
	virtual ENGINE_APIF UGbool EndQuickEdit();

	//! \brief 设置批量更新的上限，使用的内存大小不超过 nCacheSize （字节），达到上限时自动提交。默认值为0
	//! \param nCacheSize 批量更新使用的内存上限
	//! \return  是否设置成功。需要在批量更新状态下设置
	//! \remarks 如果同时设置了内存上限和要素条数上限，则满足条件之一即自动提交
	//! \remarks 如果既没有设置内存上限，也没有设置要素数上限，则按要素数上限1024处理
	virtual ENGINE_APIF UGbool SetBulkMaxCache(UGuint nCacheSize);

	//! \brief 设置批量更新的上限，更新的记录达到 nCount 条时，自动提交。默认值为0
	//! \param nCount 批量更新要素条数上限
	//! \return  是否设置成功。需要在批量更新状态下设置
	//! \remarks 如果同时设置了内存上限和要素条数上限，则满足条件之一即自动提交
	//! \remarks 如果既没有设置内存上限，也没有设置要素数上限，则按要素数上限1024处理
 	virtual ENGINE_APIF UGint SetBulkMaxFeature(UGuint nCount);
#if !defined SYMBIAN60 /*&& !defined  OS_ANDROID && !defined (IOS)*/
	//! \brief 批量更新时 添加一条要素
	//! \return 返回 pFeature 的 SmID，小于 1 则添加失败
	virtual ENGINE_APIF UGint AddOneFeature(UGFeature *pFeature);
	virtual ENGINE_APIF UGint AddOneFeature(UGGeometry *pGeometry, const UGArray<UGString> &aryFields, const UGArray<UGVariant *> &aryValues) {return -1;}

	// 允许指定对应字段，字段的合法性在外部判断
	virtual UDBENGINE_APIF UGint AddOneFeature(UGFeature *pFeature,UGFieldInfos srcFields, UGFieldInfos desFields){return -1;};

	//! \brief 批量更新时 修改一条要素（暂时支持UDB http://192.168.115.2:8090/browse/UGOSPII-2227）
	//! \param bModifyGeometry 是否修改当前的Geometry. bModifyGeometry=TRUE则 pGeometry不能为空；pGeometry=FALSE，则pGeometry没有用，可以传入空
	virtual ENGINE_APIF UGint SetOneFeature(UGGeometry *pGeometry, UGbool bModifyGeometry, const UGArray<UGString> &aryFields, const UGArray<UGVariant> &aryValues);
#endif

	//! \brief 批量更新时,强制刷新,将本次批量编辑的数据写入数据库
	//! \return 是否刷新成功
	virtual ENGINE_APIF UGbool FlushBulkEdit();

	//! \brief 取消本次批量更新的内容，从上次提交点至此 编辑的内容无效，但可以继续开始进行批量编辑
	virtual ENGINE_APIF UGbool CancleBulkOperated();

	//! \brief 获取当前编辑模式
	//##ModelId=4820305001EE
	ENGINE_APIF EditMode GetEditMode() const ;
	
	//! \brief 增加新记录,成功，返回TRUE值，失败返回FALSE值；
	//! \param *pGeometry [in] 添加的Geometry指针
	//! \param bReturnID=FALSE [in] 此参数已经不起作用。
	//! \return True 和 False 的值
	//! \remarks 如果想得到新对象的ID，那么马上调用GetId方法
	//##ModelId=4820305001F4
	virtual ENGINE_APIF UGint AddNew(UGGeometry *pGeometry,
		UGbool bReturnID=FALSE);

	//! \brief 删除当前记录
	//##ModelId=4820305001F8
	virtual ENGINE_APIF UGbool Delete();

	//! \brief 刷新记录
	//##ModelId=4820305001FA
	virtual ENGINE_APIF UGbool FlushCurrentRecord();
	
	//! \brief 是否支持事务
	//##ModelId=4820305001FC
	virtual ENGINE_APIF UGbool CanTransact() const;

	//! \brief 是否可更新
	//##ModelId=4820305001FE
	virtual ENGINE_APIF UGbool CanUpdate();	

	//! \brief 是否可添加
	//##ModelId=482030500200
	virtual ENGINE_APIF UGbool CanAppend();

	//! \brief 计算记录集的范围
	//##ModelId=482030500207
	virtual ENGINE_APIF UGbool ComputeBounds(UGRect2D &rc2Bounds,
		UGdouble &dMinZ,UGdouble &dMaxZ);

	//! \brief 设置查询定义
	//##ModelId=48203050020F
	ENGINE_APIF void SetQueryDef(const UGQueryDef& querydef);

	//! \brief 获取查询定义
	//##ModelId=482030500213
	ENGINE_APIF void GetQueryDef(UGQueryDef & querydef) const;

	//##ModelId=482030500216
	ENGINE_APIF UGQueryDef::QueryOption GetOptions() const;

	//! \brief 检查要加进来的数据类型是否合法
	//##ModelId=482030500218
	ENGINE_APIF UGbool IsGeometryTypeValid(UGGeometry::Type& geoType);

	//! \brief 生成XML格式的信息
	//##ModelId=48203050021A
	ENGINE_APIF UGString ToXML(UGGeometry::GMLVersionType versionType, UGint nPace = 0);
	
	//! \brief 从XML字符串中生成Geometry
	//##ModelId=48203050021D
	ENGINE_APIF UGbool FromXML(const UGString& strXML,UGGeometry::GMLVersionType versionType);
#if !defined SYMBIAN60 /*&& !defined  OS_ANDROID && !defined IOS*/
	//! \brief 取出数据集中某行特征要素。
	//! \param nID 数据集记录ID号[in]。
	//! \return 特征要素指针。
	//##ModelId=482030500223
	virtual ENGINE_APIF UGFeature* GetFeature();	
	
	virtual ENGINE_APIF UGbool GetFeature(UGFeature *&pFeature);

	//! \brief 将特征要素更新到数据集中。
	//! \param pFeature 特征要素指针[in]。
	//! \return 是否保存成功，成功返回TRUE，失败返回FALSE。
	//##ModelId=482030500226
	virtual ENGINE_APIF UGint UpdateFeature(const UGFeature* pFeature);
	
	//! \brief 将特征要素追加到数据集未尾。
	//! \param pFeature 特征要素指针[in]。
	//! \return 是否追加成功，成功返回TRUE，失败返回FALSE。
	//! \remarks 追加时特征要素关联的数据集记录ID将不起作用。
	//##ModelId=482030500229
	virtual ENGINE_APIF UGint AddFeature(const UGFeature* pFeature);	
#endif
	//! \brief 是否支持指定的操作
	//##ModelId=482030500204
	virtual ENGINE_APIF UGbool IsSupport(UGEngAction nAction){return FALSE;}

	//! \brief 是否在二维地图显示中使用该记录集
//	virtual ENGINE_APIF void IsUseIn2DMap(UGbool bIn2Dmap){m_bIn2Dmap = bIn2Dmap;}
	
	virtual ENGINE_APIF UGint GetLinkTableCurrentIndex()
	{
		return m_nCurrentLinkTableIndex;
		
	}

	virtual ENGINE_APIF UGint GetLinkRecourdCount()
	{
		return m_nLinkRecourdCount;
	}

public:
	//!	\brief	修改字段属性信息和几何信息（这里是将原来的SetFieldValue、SetGeometry和Update的实现迁移过来了，
	//			主要原因是要在原来的接口中做动作行为的触发，以应对动态分段或关系类的联动处理）
	virtual ENGINE_APIF UGbool ModifyFieldValue(const UGString &strName, const UGVariant &varVal) { return FALSE; }
	virtual ENGINE_APIF UGbool ModifyGeometry(UGGeometry &geometry) { return FALSE; }
	virtual ENGINE_APIF	UGint CommitModify() { return FALSE; }

	virtual ENGINE_APIF UGFeature * GetTemplateFeature();

protected:

	//! \brief 初始化查询字段
	virtual ENGINE_APIF UGbool InitFields(UGArray<UGString> &fields);

	//! \brief  分析QueryDefine，判断是否需要扩充查询字段
	//##ModelId=483BB70802FC
	ENGINE_APIF UGbool IsStatisticalQuery(UGbool bCheckGroupby=TRUE);

	//处理查询条件的几个方法
	//! \brief 将以数据集名构造的查询条件转换为以表名构造的查询
	//! \param &querydefIn [in]
	//! \param &querfdefOut [out] 
	//! \remarks  
	//! \sa CheckOut, CheckIn, UndoCheckOut, UnLock
	virtual ENGINE_APIF void TransactQuerydef(const UGQueryDef &querydefIn, UGQueryDef &querydefOut);
	//! \brief 定义出现在串strIn中的以'.'为后续的子串为数据集名，需要将其替换为相应的表名
	//! \return 返回""，表明替换失败，否则返回替换后的结果
	virtual ENGINE_APIF UGString ReplaceString(const UGString &strIn);
	//! \brief 从串strIn中取从最后一个字符开始向前，最长的不包含非法字符的子串，在A-Z,a-z,0-9和'_'之外的字符都为非法
	virtual ENGINE_APIF UGString GetLegalString(const UGString &strIn);

	
protected:	
	//! \brief 记录集对应的数据集
	//##ModelId=48203050022F
	//UGDatasetVector* m_pDataset;
	UGTable* m_pDataset;


	//批量更新
	//! \brief 最大内存（单位：字节）
	UGuint m_nBulkMaxCache;

	//! \brief 最大记录条数,默认1024
	UGuint m_nBulkMaxFeature;
	UGint m_nCurrentLinkTableIndex;
	//linkTable实际的记录集的数目
	UGint m_nLinkRecourdCount;

	//{{下面是为复合记录集增加的变量
	//! \brief 是否使用复合记录集
	UGbool m_bUsingComplex;

	UGint m_nCurSubRecordIndex;

	//! \brief 复合记录集中每个记录集的位置偏移
	UGArray<UGint> m_arySubOffset;

	//! \brief 复合记录集的子记录集数组
	UGArray<SubRecordset> m_arySubRecordset;

	//! \brief 复合记录集创建的内存大小
	UGint m_nTotalMemSize;

	UGMutex m_Mutex;

//	UGbool m_bIn2Dmap;
public:
	//! \brief 查询定义
	//##ModelId=482030500234
	UGQueryDef m_QueryDef;

	UGArray<UGint> m_arrIDs;

	UGint m_nCurrentIndex;

	UGint m_nRecordCount;

	//! 当前编辑模式
	//! \brief 当前编辑状态
	/// @li	0 -- EditNone			未做任何编辑
	/// @li	1 -- EditInProgress		正在编辑
	/// @li	2 -- EditAdd			已执行过AddNew操作
	/// @li	3 -- EditOfGeometry		已执行过SetGeometry操作
	//##ModelId=482030500232
	UGint m_nEditMode;

	//!  \brief 用来存储二进制字段数据的大小
	UGDict<UGString, UGint> m_dictBinarySize;

protected:
	UGint m_nIDIndex;


//#if !defined OS_ANDROID && !defined (IOS)
	// 增加当前记录集的Feature模板,以用于提高GetFeature的性能.
	UGFeature *m_pFeatureTemplate;

	UGBulkEditManager *m_pBulkEditManager;
//#endif

	//!  \brief 用来存储二进制字段数据的缓存
	UGArray<UGuchar*> m_arrBinaryBuffer;
	
private:
	UGuint m_nFeatureUsedMemory;
};


}

#endif



