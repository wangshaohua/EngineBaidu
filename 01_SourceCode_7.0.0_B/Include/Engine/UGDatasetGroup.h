#pragma once

#include "Stream/ugdefs.h"
#include "Engine/UGDatasetGroupItem.h"
#include "Engine/UGDataSource.h"

namespace UGC {

//! \brief CreateDatasetGroup 回调函数
typedef  void (UGSTDCALL *CreateDatasetGroupProc)(void* pData, const UGString& strGroupName);

//! \brief AfterDeleteDatasetGroup 回调函数
typedef  void (UGSTDCALL *AfterDeleteDatasetGroupProc)(void* pData, const UGString& strGroupName);

//! \brief BeforeDeleteDatasetGroup 回调函数
typedef  void (UGSTDCALL *BeforeDeleteDatasetGroupProc)(void* pData, const UGString& strGroupName, UGbool& bCancel);

//! \brief AddDatasetGroupItem 回调函数
typedef  void (UGSTDCALL *AddDatasetGroupItemProc)(void* pData, UGString& strDatasetTableName);


class ENGINE_API UGDatasetGroup
{
public:
	UGDatasetGroup(void);
	UGDatasetGroup(UGDataSource *pDataSource);
	~UGDatasetGroup(void);

	//{{----------与分组相关的操作------------------------------------
	UGDatasetGroup* GetParentGroup() const;
	void SetParentGroup(UGDatasetGroup* pParentGroup);
	UGDatasetGroup* GetChildGroup(UGint nIndex) const;
	UGDatasetGroup* GetChildGroup(const UGString& strName) const;
	UGint GetChildGroupCount() const;
	UGDatasetGroup* CreateChildGroup(const UGString& strName);
	UGbool AppendGroup(UGDatasetGroup *pDatasetGroup);
	UGbool IsChildGroupExisted(const UGString& strName);
	UGString GetGroupName() const;
	void SetGroupName(const UGString& strName);
	UGbool RemoveGroup(const UGString& strName);
	void SetDescription(const UGString& strDescription);
	UGString GetDescription();
	UGint IndexOfChildGroup(const UGString& strChildGroupName);
	//}}--------------------------------------------------------------

	//{{----------与Item的相关操作------------------------------------
	UGint GetGroupItemCount() const;
	UGDatasetGroupItem GetGroupItem(UGint nIndex) const;
	UGbool SetGroupItem(UGint nIndex, UGDatasetGroupItem GroupItem);
	UGint FindGroupItem(UGString TableName) const;
	UGbool IsExist(UGString TableName) const;
	UGbool AddGroupItem(UGDatasetGroupItem GroupItem);
	UGbool RemoveGroupItem(UGString TableName);
	//}}--------------------------------------------------------------

	UGbool IsModified();

	UGbool FromXML(UGString xml);
	UGString ToXML();

	UGbool SetDataSource(UGDataSource *pDataSource);
	UGDataSource *GetDataSource();

	UGbool SetExtData(UGString &strExtData);
	UGString GetExtData();

	void SetCreateDatasetGroupFunction(CreateDatasetGroupProc pCreateDatasetGroupProc, void* pData);
	void SetAfterDeleteDatasetGroupFunction(AfterDeleteDatasetGroupProc pAfterDeleteDatasetGroupProc, void* pData);
	void SetBeforeDeleteDatasetGroupFunction(BeforeDeleteDatasetGroupProc pBeforeDeleteDatasetGroupProc, void* pData);
	void SetAddDatasetGroupItemFunction(AddDatasetGroupItemProc pAddDatasetGroupItemProc, void* pData);

protected:
	void SetModifiedFlag(UGbool bModified);

private:
	//! 该组的名称
	UGString m_strName;
	UGString m_strDescription;
	UGString m_strExtData;

	UGbool m_bModified;

	//! 该组的父组，如果m_pParentGroup为NULL，表示其为根组
	UGDatasetGroup*          m_pParentGroup;             

	//! 该组下的子组数组
	UGArray<UGDatasetGroup*> m_ChildGroups;

	//! 该Group组织的符号(Item)，记录其ID；
	//! 注:一个Group中不允许有相同ID的Item存在,同时整个树中的Item所对应的符号ID都是唯一的
	UGArray<UGDatasetGroupItem> m_Items;

	UGDataSource * m_pDataSource;

	CreateDatasetGroupProc ms_pCreateDatasetGroupProc;
	AfterDeleteDatasetGroupProc ms_pAfterDeleteDatasetGroupProc;
	BeforeDeleteDatasetGroupProc ms_pBeforeDeleteDatasetGroupProc;
	AddDatasetGroupItemProc ms_pAddDatasetGroupItemProc;
	void* m_pCallBackData;
};

}

