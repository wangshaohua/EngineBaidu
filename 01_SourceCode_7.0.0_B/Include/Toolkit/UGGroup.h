/**  \file UGGroup.h
   \brief 实现分组管理的基类
   \author lugw
   \attention 
   Copyright(c) 2000-2010 SuperMap Software Co., Ltd.<br>
   All Rights Reserved.
 */

#if !defined(AFX_UGGROUP_H__2A4A8687_DF92_47D3_B1A2_0E2DA769546B__INCLUDED_)
#define AFX_UGGROUP_H__2A4A8687_DF92_47D3_B1A2_0E2DA769546B__INCLUDED_

#include "Stream/ugdefs.h"

namespace UGC
{	
	  //!  \brief Toolkit
	class TOOLKIT_API UGGroup  
	{
	public:
	//! \brief 。
	  //!  \brief Toolkit
		enum GroupDataType
		{
	  //!  \brief Toolkit
			NoneData   = 0,           //没有数据
	  //!  \brief Toolkit
			Group      = 1,           //分组
	  //!  \brief Toolkit
			//DataSource = 2,         //数据源类型			
	  //!  \brief Toolkit
			LayerData  = 2            //图层类
		};
		
	//! \brief
	  //!  \brief Toolkit
		struct UGGroupItem 
		{
	  //!  \brief Toolkit
			void*    pData;
	  //!  \brief Toolkit
			UGint    nType;
	  //!  \brief Toolkit
			UGGroup* pParentGroup;
	  //!  \brief Toolkit
			UGGroupItem()
			{
				pData = NULL;
				nType = UGGroup::NoneData;
				pParentGroup = NULL;
			}
		};

		public:
	//! \brief
	  //!  \brief Toolkit
			UGGroup();
	//! \brief
	  //!  \brief Toolkit
			virtual ~UGGroup();		
			
			//{{----------与分组相关的操作------------------------------------
	//! \brief
	  //!  \brief Toolkit
			UGGroup* GetParentGroup() const;
	//! \brief
	  //!  \brief Toolkit
			void SetParentGroup(UGGroup* pParentGroup);
			
	  //!  \brief Toolkit
	//! \brief
	  //!  \brief Toolkit
			UGGroup* GetChildGroup(UGint nIndex) const;
	//! \brief
	  //!  \brief Toolkit
			UGGroup* GetChildGroupByID(UGint nID) const;
	//! \brief
	  //!  \brief Toolkit
			UGGroup* GetChildGroup(const UGString& strName) const;
			//UGint GetChildGroupCount() const;
			
			//! 创建子组，返回新创建子组的指针，如果没有成功，返回NULL
	  //!  \brief Toolkit
			UGGroup* CreateChildGroup(const UGString& strName, UGbool bTop = false);
	  //!  \brief Toolkit
			//UGbool AppendGroup(UGGroup *pGroup, UGbool bTop = false);

	//! \brief
	  //!  \brief Toolkit
			virtual void AddItem(void* pData, UGbool bTop = false);
	//! \brief
	  //!  \brief Toolkit
			virtual void DeleteItem(UGGroupItem* pGroupItem);
	//! \brief
	  //!  \brief Toolkit
			UGint GetItemCount();
	//! \brief
	  //!  \brief Toolkit
			UGGroupItem* FindItemAt(UGint nIndex);
			
	//! \brief
	  //!  \brief Toolkit
			UGString GetGroupName() const;
	//! \brief
	  //!  \brief Toolkit
			void SetGroupName(const UGString& strName);

			//移动操作
	//! \brief
	  //!  \brief Toolkit
			UGbool MoveTo(UGint nIndexFrom, UGint nIndexTo);
	//! \brief
	  //!  \brief Toolkit
			UGbool MoveTo(UGint nIndexFrom, UGGroup* pFromGroup, UGint nIndexTo, UGGroup* pToGroup);
	//! \brief
	  //!  \brief Toolkit
			UGbool MoveBottom(UGint nIndex);
	//! \brief
	  //!  \brief Toolkit
			UGbool MoveDown(UGint nIndex);
	//! \brief
	  //!  \brief Toolkit
			UGbool MoveUp(UGint nIndex);
	//! \brief
	  //!  \brief Toolkit
			UGbool MoveTop(UGint nIndex);

			//移除
	  //!  \brief Toolkit
			UGbool RemoveItem(UGint nIndex, UGbool bMoveUp = false);
			//}}-------------------------------------------------------------

	//! \brief
	  //!  \brief Toolkit
			void clear();
	  //!  \brief Toolkit
	//! \brief
	  //!  \brief Toolkit
			UGint GetCount()const;
	//! \brief
	  //!  \brief Toolkit
			UGint GetGroupID()const;
	//! \brief
	  //!  \brief Toolkit
			UGGroupItem* GetAt(UGint nIndex)const;
	//! \brief
	  //!  \brief Toolkit
			UGbool RemoveAt(UGint nIndex);
	//! \brief
	  //!  \brief Toolkit
			void RemoveAll();
	//! \brief
	  //!  \brief Toolkit
			void Add(UGGroupItem* pGroupItem, UGbool bTop = false);

	//! \brief
	  //!  \brief Toolkit
			UGList<UGGroupItem*>::POSITION GetTailPosition();
	//! \brief
	  //!  \brief Toolkit
			UGList<UGGroupItem*>::POSITION GetHeadPosition();
	//! \brief
	  //!  \brief Toolkit
			UGbool IsBOF(UGList<UGGroupItem*>::POSITION pos);
	//! \brief
	  //!  \brief Toolkit
			UGbool IsEOF(UGList<UGGroupItem*>::POSITION pos);
	//! \brief
	  //!  \brief Toolkit
			UGGroupItem* GetPrev(UGList<UGGroupItem*>::POSITION pos);
	//! \brief
	  //!  \brief Toolkit
			UGGroupItem* GetNext(UGList<UGGroupItem*>::POSITION pos);
	  //!  \brief Toolkit
		protected:
			void FindItemCount(UGList<UGGroupItem*> pGroupItemList, UGint& nItemCount);
			void FindItemAt(UGList<UGGroupItem*> pGroupItemList, const UGint nIndex, UGint& nNowIndex, UGGroupItem* pTargetItem);
			UGList<UGGroupItem*> GetGroupItemList();
			

		private:
			UGList<UGGroupItem*> m_pGroupTree;
			UGString m_strGroupName;
			UGint m_nID;
			UGGroup* m_pParentGroup;
			UGint m_nChildGroupNum;
			//UGbool m_bDelete;
	};
	
}

#endif // !defined(AFX_UGGROUP_H__2A4A8687_DF92_47D3_B1A2_0E2DA769546B__INCLUDED_)

