// UGVersionManager.h: interface for the UGVersionManager class.
//
//////////////////////////////////////////////////////////////////////

/*!
   **************************************************************************************
    \file     UGVersionManager.h
   **************************************************************************************
    \author   江志斌
    \brief    版本管理基类，所有与版本相关的操作都封装在这个类中                                                    
    \attention   
   ----------------------------------------------------------------------------------<br>
    Copyright (c) 1996-2005 SuperMap GIS Technologies,Inc.                           <br>
    All Rights Reserved.                                                             <br>
   ----------------------------------------------------------------------------------<br> 
   
   **************************************************************************************
    \version 2008-12-10  江志斌														 <br>
   **************************************************************************************
*/
#ifndef UGVERSIONMANAGER_H
#define UGVERSIONMANAGER_H

#include "UGDataSource.h"
#include "UGDataset.h"
#include "UGDatasetVector.h"
#include "UGDatasetRaster.h"

namespace UGC {	

class ENGINE_API UGVersionManager  
{
public:
	UGVersionManager();
	UGVersionManager(UGDataSource *pDataSource);

	virtual ~UGVersionManager();

public:
	//! \brief 创建版本
	//! \param &versionInfo     版本信息[in]
	//! \return UGbool
	//! \remarks
	//! \attention
	virtual UGbool CreateVersion(UGVersionInfo &versionInfo);

	//! \brief 创建版本
	//! \param &strVersionName	版本名称[in]
	//! \param &strParentName	父版本名称[in]
	//! \param &strDescription	版本描述信息[in]
	//! \return UGbool
	//! \remarks
	//! \attention
	virtual UGbool CreateVersion(const UGString &strVersionName, const UGString &strParentName, const UGString &strDescription);
	
	//! \brief 删除版本
	//! \param &strVersionName	指定版本名称[in], nVersionID 版本号[in]
	//! \return
	//! \remarks
	//! \attention　删除该版本，该版本的操作将作废，只能删除版本树最末端的版本
	virtual UGbool DeleteVersion(const UGString &strVersionName);
	virtual UGbool DeleteVersion(UGint nVersionID);
	
	//! \brief 数据源切换版本，即为数据源设置当前的版本,默认为ROOT版本 
	//! \param &strVersionName	指定版本名称[in], nVersionID 版本号[in]
	//! \return 
	//! \remarks
	//! \attention
	virtual UGbool SetCurrentVersion(const UGString &strVersionName);
	virtual UGbool SetCurrentVersion(UGint nVersionID);
	
	//! \brief 获取当前版本
	//! \param 
	//! \return 返回当前版本信息
	//! \remarks
	//! \attention
	virtual UGVersionInfo GetCurrentVersion();
	virtual UGint GetCurrentVersionID();
	
	//! \brief 修改该数据源下指定版本的信息，能修改版本名称和版本描述
	//! \param &strVersionName		指定版本名称[in]
	//! \param &strDestName			新版本信息[in]，&strDestDescription新版本描述[in]
	//! \return UGbool
	//! \remarks
	//! \attention
	virtual UGbool UpdataVersionName(const UGString &strName, const UGString &strDestName);

	//! \brief 修改该数据源下指定版本的信息，能修改版本名称和版本描述
	//! \param &strVersionName		指定版本名称[in]
	//! \param &strDestName			新版本信息[in]，&strDestDescription新版本描述[in]
	//! \return UGbool
	//! \remarks
	//! \attention
	virtual UGbool UpdateVersionDescription(const UGString &strVersionName, const UGString &strDestDescription);

	//! \brief 取得根版本版信息
	//! \return UGVersionInfo
	virtual UGVersionInfo GetRootVersionInfo();

	//! \brief 得到该数据源下指定版本的信息
	//! \param &strVersionName		指定版本名称[in], nVersionID 版本号[in]
	//! \param &VersionInfo			版本信息[out]
	//! \return UGbool
	//! \remarks
	//! \attention
	virtual UGbool GetVersionInfo(const UGString &strVersionName, UGVersionInfo &versionInfo) const;
	virtual UGbool GetVersionInfo(UGint nVersionID, UGVersionInfo &versionInfo) const;
	
	//! \brief 取某个版本的所有直接子版本，桌面可以通过递归调用该函数取出版本树信息
	//! \param &strVersionName	目标版本名字[in], nVersionID 版本号[in]
	//! \param &arrVersionInfos 当前版本的所有直接子版本信息[out]	
	virtual UGbool GetSubVersionInfos(const UGString & strVersionName, UGArray<UGVersionInfo> &aryVersionInfos) const;
	virtual UGbool GetSubVersionInfos(const UGint nVersionID, UGArray<UGVersionInfo> &aryVersionInfos) const;

	//! \brief 判断当前版本是否目标版本的子版本
	//! \param &strCurName 当前版本[in]
	//! \param &strDestName	目标版本[in]
	//! \return UGbool 是返回TRUE,否返回FALSE
	virtual UGbool CheckRelation(const UGString &strCurName, const UGString &strDestName) const;

	//! \brief 注册数据集为支持版本
	//! \param *pDT 数据集指针[in]
	//! \return
	//! \remarks		添加A，D表
	//! \attention		支持点、线、面、文本、CAD等数据集类型
	virtual UGbool Register(UGDataset *pDT);
	
	//! \brief 数据集反注册为普通数据集
	//! \param *pDT 数据集指针[in]
	//! \param bUnionToBasic 是否合并根版本到基本表[in]
	//! \return
	virtual UGbool UnRegister(UGDataset *pDT, UGbool bUnionToBasic = TRUE);

	//! \brief 刷新数据集的当前版本，数据集不能处于编辑状态
	//! \param *pDT 数据集指针[in]
	//! \return
	//! \remarks 当数据集的某版本在别处被更新后，可以通过版本刷新来获取最新状态
	//! \attention	
	virtual UGbool Refresh(UGDataset *pDT);
	
	//! \brief 版本协调
	//! \param *pDT 数据集指针[in]
	//! \param &strDestVersionName		目标版本名称[in]
	//! \return	UGint	0异常失败
	//!					1成功
	//!					-1目标版本正在向其他版本协调，协调失败
	//!					-2当前版本正在被协调，协调失败
	//!					-3当前版本在其他地方处于编辑状态，不能进行协调，协调失败
	//!					-4目标系列在外部被修改，不能进行协调，协调失败
	//! \remarks 数据集的当前版本向目标版本进行协调，目标版本必须是当前版本的父版本
	//! \attention		
	virtual UGint Reconcile(UGDataset *pDT, const UGString &strDestVersionName, UGPostOption nPostOption);

	//! \brief 版本提交
	//! \param *pDT 数据集指针[in]
	//! \return UGint	0异常失败
	//!					1成功
	//!					-1目标版本发生变化,要重新协调
	//! \remarks
	//! \attention	协调之后才能提交，并且协调和提交的当前及目标版本必须保持一致
	virtual UGint Post(UGDataset *pDT);

	//! \brief　处理冲突
	//! \param	*pDT 数据集指针[in]
	//! \param	nSmID 冲突对象的ID[in]
	//! \param	nPostOption 冲突处理方式[in]
	//! \return
	//! \remarks
	//! \attention	必须版本协调后并且存在冲突才能进行冲突处理
	virtual UGbool TransactConflict(UGDataset *pDT, UGint nSmID, UGPostOption nPostOption);

	//! \brief 版本保存
	//! \param *pDT 数据集指针[in]
	//! \return			0:意外失败
	//!					1:成功
	//!					2:存在冲突，需要重新保存
	//! \remarks
	//! \attention	版本保存，更新SmVersions表内相关信息；版本编辑后需要做版本保存操作
	virtual UGint Save(UGDataset *pDT);

	//! \brief 版本快照
	//! \param *pDT 数据集指针[in]
	//! \param &strDestName 目标数据集名称[in]
	//! \return
	//! \remarks
	//! \attention
	virtual UGDataset* SnapShot(UGDataset *pDT, const UGString &strDestName);
	
	//! \brief 开始编辑版本
	//! \param *pDT 数据集指针[in]
	//! \return　满足可以开始编辑的条件返回TRUE,否则返回FALSE
	//! \remarks
	//! \attention
	virtual UGbool StartEdit(UGDataset *pDT);

	//! \brief 结束编辑版本
	//! \param *pDT 数据集指针[in]
	//! \return　满足可以结束编辑的条件返回TRUE,否则返回FALSE
	//! \remarks
	//! \attention
	virtual UGbool FinishEdit(UGDataset *pDT);

	//! \brief 更新扩展信息ExtInfo
	virtual UGbool RefreshExtInfo(UGDataset *pDT, UGint nVersionID);
	//获取数据集的扩展信息，如果不存在，则SmRegister中获取相应信息，并初始化SmExtInfo
	virtual UGbool GetExtInfo(UGDataset *pDT);

	//! \brief　获取可编辑的系列
	//! \param *pDT 数据集指针[in]
	//! \return BOOL
	virtual UGbool GetEditableSeries(UGDataset *pDT);

	//! \brief 在数据集的当前系列插入新的操作号
	//! \param *pDT 数据集指针[in]
	//! \return 返回操作号，如果操作号<=0，表示插入失败
	virtual UGint InsertNewActionID(UGDataset *pDT, UGint &nSeriesID);

	//! \brief 获取一个新的操作号ActionID
	//! \param 
	//! \return　返回获取的操作号，失败则返回0,否则大于0
	//! \remarks
	//! \attention
	virtual UGint GetNextAction();

	//! \brief  转换非版本查询的SQL语句为版本查询SQL
	//! \param	*pDT 数据集指针
	//! \param	*strSQLIn 针对数据集pDT查询的SQL语句
	//! \param	&bBind SQL是否带绑定信息
	//! \return	返回针对数据集版本的查询语句
	//! \remarks 把以基本表构造的SQL转换相应相应的版本视图
	virtual UGString TranscatSQL(UGDataset *pDT, const UGString &strSQLIn);

	//! \brief 清空版本环境，包括系统表等
	virtual void ClearVersionEnvironment();
	
	//! \brief  构造版本查询视图
	virtual void CreateQueryView(UGDataset *pDT);

	//! \brief 判断数据集的当前版本能否与目标版本协调
	//! \param *pDT 数据集指针[in]
	//! \param &strDestVersionName		目标版本名称[in]
	//! \return	UGint	0异常失败
	//!					1成功
	//!					-1目标版本不是当前版本的父版本
	//!					-2当前版本正在其它地方处于编辑状态，不能协调
	//!					-3当前版本正在被协调，不能协调
	//!					-4目标版本正在协调，不能协调
	virtual UGint CanReconcile(UGDataset *pDT, const UGString &strDestVersionName);

	//! \brief 判断数据集的当前版本能否向目标版本提交
	//! \param *pDT 数据集指针[in]
	//! \param &strDestVersionName		目标版本名称[in]
	//! \return UGint	0异常失败
	//!					1成功
	//!					-1目标版本不是当前版本的父版本
	//!					-2目标版本被更新，请重新协调
	//! \remarks
	//! \attention	协调之后才能提交，并且协调和提交的当前及目标版本必须保持一致
	virtual UGint CanPost(UGDataset *pDT, const UGString &strDestVersionName);

//不需要子类实现的
public:
	//! \brief 是否需要保存
	//! \param *pDT 数据集指针[in]
	//! \return
	//! \remarks 判断数据集的当前版本是否需要保存，如在编辑或协调后不保存将丢失未保存数据
	UGbool BeNeedSave(UGDataset *pDT);

	//! \brief	协调后，取得当前版本的记录集
	//! \param	*pDT 数据集指针[in]
	//! \return	返回记录集
	//! \attention 必须在协调后才能取得有效数据，否则返回NULL
	//!            查询条件必须是静态游标，结果记录集不支持修改,需要在外部Release
	UGRecordset *GetCurRecordset(UGDataset *pDT, UGQueryDef &querydef);

	//! \brief	协调后，取得目标版本的记录集
	//! \param	*pDT 数据集指针[in]
	//! \return	返回记录集
	//! \attention 必须在协调后才能取得有效数据，否则返回NULL
	//!            查询条件必须是静态游标，结果记录集不支持修改,需要在外部Release
	UGRecordset *GetConflictRecordset(UGDataset *pDT, UGQueryDef &querydef);

	//! \brief	协调后，取得共公版本的记录集
	//! \param	*pDT 数据集指针[in]
	//! \return	返回记录集
	//! \attention 必须在协调后才能取得有效数据，否则返回NULL
	//!            查询条件必须是静态游标，结果记录集不支持修改,需要在外部Release
	UGRecordset *GetCommonRecordset(UGDataset *pDT, UGQueryDef &querydef);

	void SetTranMode(UGbool bTran = FALSE);

	UGbool GetEditMode();

protected:
	//! \brief	根据系列操作查询数据集
	//! \param	*pDT			操作的数据集[in]
	//! \param	nSeriesID		系列号[in]
	//! \param	nLastActionID	系列的最后操作号[in]
	//! \param	&querydef		查询定义,要求查询游标采用静态查询[in]
	//! \return	返回查询结果
	//! \attention 该查询方法主要用于显示冲突信息，参数比较专业，请匆随便使用
	virtual UGRecordset *QueryBySeries(UGDataset *pDT, UGint nSeriesID, UGint nLastActionID, UGQueryDef &querydef);

	//! \brief	把ROOT版本合并到基本表,在数据集反注册之前调用
	//! \param	操作的数据集[in]
	//! \return UGbool
	//! \attention
	virtual UGbool UnionRootToBasic(UGDataset *pDT);
	
	//! \brief	通过SQL语句从库中取数据
	//! \param	*pDT			操作的数据集[in]
	//! \param	&strSQL			SQL语句[in]
	//! \param	&fieldInfos		返回取得的字段信息[out]
	//! \param	nObjectCount	返回取得的对象数
	//! \param	*pAttrBuffer	返回属性数据[out]
	//! \param	*pGeoBuffer		返回几何数据[out]
	//! \param	*pInds			返回查询结果提示器[out]
	//! \return	UGbool
	//! \attention				pAttrBuffer和pGeoBuffer在函数体内分配内存,需要在使用后手动释放,
	//!							pAttrBuffer和pGeoBuffer要和fieldInfos塔配使用
	virtual UGbool FetchDataBySQL(UGDataset *pDT, UGString &strSQL, UGFieldInfos &fieldInfos, UGint &nObjectCount, UGbyte *&pAttrBuffer, UGbyte *&pGeoBuffer, UGint *&pInds);

	//! \brief 复制系列操作，把系列的LastAction之前的操作复制到一个新的系列
	//! \param nSrcSeriesID 复制源系列号[in]
	//! \param nSrcLastActionID 复制源最后操作[in]
	//! \param nDestSeriesID 复制目标系列号[in]
	virtual UGbool CopySeries(UGint nSrcSeriesID, UGint nSrcLastActionID, UGint nDestSeriesID);

	//合并A表中满足SQL查询的记录为一个新操作，同时保留原数据
	virtual UGbool UnionActionInA(UGDataset *pDT, UGString strSQL, UGint nNewActionID);

	//! \brief	删除失效数据，SmSeriesOpers，AD表
	//! \param	*pDT 数据集指针[in]
	//! \param	nVersionID = 0,版本号，默认处理当前版本[in]
	//! \remarks 
	virtual UGbool DropInvalidData(UGDataset *pDT, UGint nVersionID = 0);
	
	//! \brief	压缩系列操作
	//! \param	*pDT 数据集指针[in]
	//! \param	bAll 是否压缩整个数据集，是：要求指定数据集的不能处于编辑状态
	//!              否：压缩数据集当前系列
	//! \remark
	virtual UGbool CompressData(UGDataset *pDT, UGbool bAll = FALSE);

protected:
	/*下面两个方法不再使用，已通过构造版本视图解决下面问题
	//! \brief 从给定串中获取SQL的统计关键字 
	//! \return 返回关键字，查找失败则返回""
	//! \attention 给定串要以"("结尾
	//! \remarks 假设传入的SQL是正确的，否则结果不可预计
	UGbool IsStatKeyWord(UGString strKeyIn);
	
	//为了合并基本表和A表的统计查询结果，通过此方法处理原SQL，达到统计查询的目
	//例"Select Count(smid) from Test"处理后为"Select smid from Test"，再把SQL处理为针对A表的
	//"Select smid from SM_V_A",合并基本表和A表，再统计
	//"Select Count(smid) from (select smid from test UNION all select smid from sm_v_a)"
	//如果原SQL语句不能包含子查询，如果原SQL语句不是统计查询，返回空串
	UGString SetAliasForStatSQL(UGString strSQLIn);*/

protected:
	//数据源指针
	UGDataSource *m_pDataSource;
	//当前版本号
	UGint m_nCurVersionID;
	UGbool m_bTranMode;
};
}
#endif // !defined(AFX_UGVERSIONMANAGER_H__56BFAEC6_99C1_47BF_BDF3_C7CB7BE0F817__INCLUDED_)

