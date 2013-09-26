//////////////////////////////////////////////////////////////////////////
//                    _   _   ____   ____                    
//   Project         | | | | / ___) / ___)                   
//                   | | | || | __ | |                       
//                   | |_| || |_\ || \___                    
//                    \____/ \____| \ ___)     6.0           
//                                                           
//!  \file UGRecordsetTile.h
//!  \brief UGRecordsetTile类的接口定义。
//!  \details UDB记录只读记录集类。
//!  \author Engine。
//!  \attention 
//!   Copyright (c) 2000-2010 SuperMap Software Co., Ltd.  <br> 
//!   All Rights Reserved.
//!  \version 6.0
//////////////////////////////////////////////////////////////////////////

#ifndef UGRECORDSETTILE_H
#define UGRECORDSETTILE_H

#include "Geometry/UGGeometry.h"
#include "Geometry/UGFeature.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

namespace UGC
{

//! \brief 矢量缓存的RecordsetTile。
//! \remarks 备注信息。
class FILEPARSER_API UGRecordsetTile  
{
		 
public:
	UGRecordsetTile(){};

	virtual ~UGRecordsetTile(){};

public:
	//! \brief 获取记录个数
	//! \remarks 只是从计数器中获取，而不进行统计。
	//! \attention 。
	virtual UGint GetRecordCount() = 0;	

	//! \brief 获取字段个数
	virtual UGint GetFieldCount() = 0;

	//! \brief 获取当前记录的ID
	virtual UGint GetID() = 0;
	
	//! \brief 通过索引取字段信息
	virtual UGbool GetFieldInfo(UGint nIndex, UGFieldInfo& fieldInfo) = 0;

	//! \brief 移动记录指针到最前
	virtual UGbool MoveFirst() = 0;

		//! \brief 移动记录指针到最前
	virtual UGbool MoveNext() = 0;
	
	//! \brief 判断当前记录指针是否指向尾
	virtual UGbool IsEOF() = 0;

	//! \brief 取得几何对象，返回的几何对象指针在函数内分配内存，
	//! 外面负责删除，否则会有内存泄漏
	virtual UGbool GetGeometry(UGGeometry*& pGeometry) = 0;
	
	//! \brief 通过字段名获取字段值
	virtual UGbool GetFieldValue(const UGString& strName,UGVariant& varVal) = 0;
	
// 	//! \brief 通过索引序号获取字段值
 	virtual UGbool GetFieldValue(UGint nIndex,UGVariant& varVal) = 0;

	//! \brief 关闭记录集
	virtual void Close() = 0;

private:

};

}
#endif // !defined(UGRECORDSETUDB_H)

