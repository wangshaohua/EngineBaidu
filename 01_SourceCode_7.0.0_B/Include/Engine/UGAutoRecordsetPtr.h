//////////////////////////////////////////////////////////////////////////
//                    _   _   ____   ____                    
//   Project         | | | | / ___) / ___)                   
//                   | | | || | __ | |                       
//                   | |_| || |_\ || \___                    
//                    \____/ \____| \ ___)     6.0           
//                                                           
//!  \file UGAutoRecordsetPtr.h
//!  \brief 记录集智能指针的接口定义。
//!  \details 本类是记录集的智能指针，设计此类的目的是为了解决在较长或调用层次很多的代码中有Recordset忘记释放的问题。
//!  \author UGC 空间数据库开发组。
//!  \attention 查询出的Recordset指针加入此类后便不能在此类外面调用ReleaseRecordset来释放，否则会导致野指针及程序崩溃。
//!   Copyright (c) 1996-2008 SuperMap Software Co., Ltd.  <br> 
//!   All Rights Reserved.
//!  \version 6.0
//////////////////////////////////////////////////////////////////////////


#if !defined(AFX_UGAUTORECORDSETPTR_H__95A0DF3C_2075_4FDF_B09D_6EF13036A322__INCLUDED_)
#define AFX_UGAUTORECORDSETPTR_H__95A0DF3C_2075_4FDF_B09D_6EF13036A322__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "Engine/UGRecordset.h"

namespace UGC
{
	
	//! \brief 记录集类的智能指针，会在析构函数中自动记录集对象
	//! \remarks 记录集的指针一旦加入此类来管理便不能在类外释放，只能调用本类的Release来释放
//##ModelId=483BB70C033C
	class  ENGINE_API UGAutoRecordsetPtr  
	{
	private:
		//! \brief 禁止拷贝构造函数
	//##ModelId=483BB70C033D
		UGAutoRecordsetPtr(const UGAutoRecordsetPtr& autoPtr);

		//! \brief 禁止赋值函数
	//##ModelId=483BB70C034C
		void operator=(const UGAutoRecordsetPtr& autoPtr);

	public:

		//! \brief 获取记录集指针。
	//##ModelId=483BB70C034E
		UGRecordset * GetRecordsetPtr() const ;		

		//! \brief 设置记录集指针
	//##ModelId=483BB70C0350
		void SetRecordsetPtr(UGRecordset *pRs, UGbool bAutoDelete = TRUE);

		//! \brief 释放记录集对象，包括delete指针及将指针赋为NULL
	//##ModelId=483BB70C0353
		void Release();

		//! \brief 默认构造函数
	//##ModelId=483BB70C0354
		UGAutoRecordsetPtr();

		//! \brief 默认析构函数
	//##ModelId=483BB70C035B
		virtual ~UGAutoRecordsetPtr();

	private:
		//! \brief 记录集指针
	//##ModelId=483BB70C035E
		UGRecordset * m_pRecordset;

		//! \brief 记录集指针是否自动释放
	//##ModelId=483BB70C0362
		UGbool m_bAutoDelete;
	};
}


#endif // !defined(AFX_UGAUTORECORDSETPTR_H__95A0DF3C_2075_4FDF_B09D_6EF13036A322__INCLUDED_)

