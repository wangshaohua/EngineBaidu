// UGDuplicateManager.h: interface for the UGDuplicateManager class.
//
//////////////////////////////////////////////////////////////////////

/*!
   **************************************************************************************
    \file     UGDuplicateManager.h
   **************************************************************************************
    \author   江志斌
    \brief    数据复制和同步基类                                                   
    \attention   
   ----------------------------------------------------------------------------------<br>
    Copyright (c) 1996-2005 SuperMap GIS Technologies,Inc.                           <br>
    All Rights Reserved.                                                             <br>
   ----------------------------------------------------------------------------------<br> 
   
   **************************************************************************************
    \version 2009-2-18  江志斌														 <br>
   **************************************************************************************
*/
#ifndef UGDUPLICATEMANAGER_H
#define UGDUPLICATEMANAGER_H

#include "UGDataSource.h"
#include "UGDataset.h"
#include "UGDatasetVector.h"
#include "UGDatasetRaster.h"

namespace UGC {	
class ENGINE_API UGDuplicateManager  
{
public:
	UGDuplicateManager();
	UGDuplicateManager(UGDataSource *pDS);

	virtual ~UGDuplicateManager();

public:
//! \brief 创建复本
	//! \param *pDT 数据集指针[in]
	//! \param &querydef 创建复本的条件[in]
	//! \param *pDestDS 目标数据源指针[in]
	//! \param &strName 复本名称[in]
	//! \param nType 复本类型[in]
	//! \param &strDescription 复本描述[in]
	//!	\param	nExchangeState 0表示数据发送源，1表示数据接收源
	//! \return UGbool
	//! \remarks 创建复本时如果数据源类型为SDBPlus则只能创建离线型复本
	//!          如果是SQLPlus或OraclePlus则能创建单向更新复本或双向同步复本
	//! \attention
	virtual UGbool CreateDuplicate(UGDatasetVector *pDT, 
								   const UGQueryDef &querydef,
								   UGDataSource *pDestDS, 
								   const UGString &strName, 
								   UGDuplicateType nType, 
								   UGint nExchangeState = 0,
								   const UGString &strDescription = _U(""), 
								   UGString strObjIDName = _U(""));
	
	//! \brief	获取复制信息
	virtual UGbool GetDuplicateInfos(UGArray<UGDuplicateInfo> &aryInfo);
	virtual UGbool GetDuplicateInfo(const UGString &strName, UGDuplicateInfo &info);
	virtual UGbool GetInfoByID(const UGString &strDuplicateID, UGDuplicateInfo &info);

	//! \brief	更新复本名称、描述
	//! \param	&strName 复本名[in]
	//! \param	&strNewName 新复本名[in]、描述信息[in]
	//! \return 。
	//! \remarks 。
	//! \attention 。
	virtual UGbool UpdateName(const UGString &strName, UGString &strNewName);
	virtual void UpdateDescription(const UGString &strName, UGString &strDescription);

	//! \brief	删除复本
	//! \param	&strName 复本名[in]
	//! \return 。
	//! \remarks 。
	//! \attention 。
	virtual UGbool DropDuplicate(const UGString &strName);

	//! \brief	删除数据源下的所有复本
	virtual void DropAllDuplicate();

	//! \brief	删除数据集的所有复本
	virtual void DropAllDuplicate(UGDataset *pDT);

	//! \brief	导出差异包
	//! \param	&strName 复本名称[in]
	//! \param	*pDS 差异包所在数据源指针[in]
	//! \param	&strDiffMsgName 差异包名称[in]
	//! \return  。
	//! \remarks	*pDS指向的数据源必须为SDBPlus数据源
	//! \attention 。
	virtual UGbool ExportDiffMessage(const UGString &strName, UGDataSource *pDS, const UGString &strDiffMsgName);
	
	//! \brief	准备导入数据
	//! \param	&strName	准备导入数据的复本名称[in]
	//! \param	*pDS		差异包所在数据源[in]
	//! \param	&aryObjIDs	冲突对象ID数组[out]
	//! \param	nTranOption	默认冲突处理方式，0:以复本数据为准,1:以差异包中数据为准[in]
	//! \remarks	
	//! \attention	在调用ImportDiffMsg()方法前必须先调用此方法，要取消ImportDiffMsg必须调用CancleImport()方法
	virtual UGbool PrepareToImport(const UGString &strName, UGDataSource *pDS, UGStrArray &aryObjIDs, UGint nTranOption = 1);
	
	//! \brief	取消已准备的导入操作
	//! \param	&strName	复本名称[in]。
	virtual void CancleImport(const UGString &strName);
		
	//! \brief	导入差异包
	//! \param	&strName 复本名称
	//! \param	*pDS 差异包所在数据源指针[in]
	//! \param	nOption 默认冲突处理方式 0:以主版本为主,1:以子复本为主
	//! \return 。
	//! \remarks	*pDS指向的数据源必须为SDBPlus数据源
	//! \attention 。
	virtual UGint ImportDiffMessage(const UGString &strName, UGDataSource *pDS);

	//! \brief	导出反馈信息
	//! \param	&strName	复本名称
	//! \param	&strMsgFile	文件全路径，包括文件名
	//! \param	bReplace	如果文件已存在，是否覆盖之
	//! \return 。
	virtual UGbool ExportAcknowledgeMsg(const UGString &strName, const UGString &strMsgFile, UGbool bRepalce = TRUE);

	//! \brief	导入反馈信息
	//! \param	&strMsgFile 反馈信息文件
	//! \param	bDelFile 是否在导入信息后删除该文件
	//! \param	bDelInValidData 是否删除已同步的数据
	//! \return	
	virtual UGbool ImportAcknowledgeMsg(const UGString &strMsgFile, UGbool bDelFile = FALSE, UGbool bDelInvalidData = TRUE);


	//! \brief	准备同步数据
	//! \param	&strName	复本名称[in]
	//! \param	*pDestDS	同步目标数据[in]
	//! \param	nTranOption 默认冲突处理：0,以源数据为准，1,以目标数据为准[in]
	//! \remarks
	//! \attention	在调用SynchroDumplicate()方法前必须先调用此方法，要取消SynchroDumplicate必须调用CancleSynchro()
	virtual UGbool PrepareToSynchro(UGString strName, UGDataSource *pDestDS, UGStrArray &aryObjIDs, UGint nTranOption = 0);
	
	//! \brief	取消已准备的同步操作
	//! \param	&strName	复本名称[in]
	virtual void CancleSynchro(const UGString &strName);

	//! \brief	同步数据
	//! \param	&strName	复本名称[in]
	//! \param	*pDestDS	同步目标数据[in]
	//! \return
	//! \remarks
	//! \attention 要求能在同一工作空间中打开主复本所在数据源和子复本所在数据源
	//! 		   离线复本不能采用此方法，单向更新和双向更新可以采用此方法同步
	virtual UGbool SynchroDumplicate(UGString strName, UGDataSource *pDestDS);
	

	//! \brief	获取数据源中的差异包信息
	virtual UGDiffMsgInfo GetDiffMsgInfo(const UGString &strDuplicateID);
	virtual UGbool GetDiffMsgInfos(UGArray<UGDiffMsgInfo > &aryDiffMsgInfos);
		
	//! \brief	单独处理冲突对象	
	//! \param	&strName	复本名称[in]
	//! \param	&strObjID	对象唯一标识[in]
	//! \param	nTranOption	处理方式，0:以复本数据为准,1:以差异包中数据为准[in]
	virtual void SetTranOption(const UGString &strName, const UGString &strObjID, UGint nTranOption);

	//! \brief	根据复本名获取数据集指针
	//! \param	&strName 复本名称[in]
	virtual UGDataset* GetDuplicateDataset(const UGString &strName);

//下面几个方法用于复本同步或导入差异包时分别获取相应的数据集和记录
	//!	\brief	获取当前复本数据集
	//! \param	&strName	当前复本名
	//!	\return	返回数据集指针
	virtual UGDataset* GetCurDataset(const UGString &strName);

	//!	\brief	获取目标复本数据集
	//! \param	&strName	当前复本名
	//! \param	*pDestDS	目标复本所在数据源
	//!	\return	返回数据集指针
	virtual UGDataset* GetDestDataset(const UGString &strName, UGDataSource *pDestDS);

	//! \brief	获取当前复本差异包数据集
	//! \param	&strName	当前复本名
	//! \param	*pDestDS	差异包所在数据源
	//!	\return	返回数据集指针
	virtual UGDataset* GetDiffMsgDataset(const UGString &strName, UGDataSource *pDestDS);

	//! \brief	根据对象标识查询冲突对象
	//! \param	&strName	当前复本名
	//!	\param	数据集指针	
	//!	\param	&strObjID	对象唯一标识
	//!	\return	返回记录集, NULL则表示操作失败
	//!	\attention	查询语句采用In语法构造，一次查询数不能超过1000个，记录集需要在外部Release
	virtual UGRecordset* GetConflictObject(const UGString &strName, UGDatasetVector *pDV, const UGStrArray &aryObjIDs);
	

// 类库内部调用方法
public:
	//! \brief	创建差异包数据集[in]
	//! \param	&diffMsgInfo	差异包信息[in]
	//! \param	*pRcd			差异记录[in]
	//! \param	&attrFieldInfos 属性信息的字段结构[in]
	//! \param	*pDataBuffer	属性数据[in]
	//! \attention 该方法在ExportDiffMessage(),由差异包所在数据源调用
	virtual UGDataset* CreateDiffMsg(const UGDiffMsgInfo &diffMsgInfo,  
		UGRecordset *pRcd,
		UGFieldInfos &attrFieldInfos, 
		UGbyte *pDataBuffer);

	//! \brief	读取差异包中的数据
	//! \param	&diffMsgInfo	差异包信息[in]
	//! \param	nUpdateSequence	复本最后更新序列[in]
	//! \param	*pRcd			差异记录[out]
	//! \param	&nAttrCount		差异信息数[out]
	//! \param	&attrFieldInfos 属性信息的字段结构[out]
	//! \param	*pDataBuffer	属性数据[out]
	//! \attention	*&pRcd, *&pDataBuffer都需要在外部释放
	virtual UGbool FetchDataFromDiffMsg(UGDiffMsgInfo &diffMsgInfo, 
		UGint nUpdateSequence,
		const UGString &strIDFieldName, 
		UGRecordset *&pRcd,
		UGint &nAttrCount, 
		UGFieldInfos &attrFieldInfos, 
		UGbyte *&pDataBuffer);
		
	//! \brief	创建子复本
	//! \param	&info 主复本信息[in]
	//! \param	*pDT 子复本数据集[in]
	//! \return
	//!	\attention 该方法由创建主复本时的目标数据源调用,调用前先创建子复本数据集
	virtual UGbool CreateSubDuplicate(const UGDuplicateInfo &info, UGDataset *pDT);

	//! \brief 复本更新数据。
	//! \param *pDT 数据集指针[in]。
	//! \param nEditMode 编辑模式：删除-1, 新增1, 修改0[in]。
	//! \param &strIDFieldValue 标识字段值 [in]。
	//! \param nVersionID 如果是版本数据集，要指明当前版本号 [in]。
	//! \return 。
	//! \remarks 。
	//! \attention 。
	virtual UGbool UpdateData(UGDataset *pDT, UGint nEditMode, const UGString &strIDFieldValue = _U(""), UGint nVersionID = 1);	

	//! \brief 更新同步信息。
	//! \param &strName 版本名[in]。
	//! \param nUpdateSequence 更新序号[in]。
	//! \param nSynchroSequence 同步序号[in]。
	//! \return 。
	//! \remarks 。
	//! \attention 。
	virtual void UpdateSynchroInfo(const UGString &strName, UGint nUpdateSequence, UGint nSynchroSequence);
protected:
	//! \brief 注册复本系统表
	//! \param *pDS 数据源指针
	//! \return
	//! \remarks 
	virtual UGbool RegSysTable(UGDataset *pDT);
	
protected:
	UGDataSource *m_pDataSource;
};
}
#endif // !defined(AFX_UGDUPLICATEMANAGER_H__56BFAEC6_99C1_47BF_BDF3_C7CB7BE0F817__INCLUDED_)

