// UGDataSourceManager.h: interface for the UGDataSourceManager class.
//
//////////////////////////////////////////////////////////////////////

/*!
   **************************************************************************************
    \file     UGDataSourceManager.h
   **************************************************************************************
    \author   陈国雄
    \brief    数据引擎动态库管理类，负责动态加载和释放sdx引擎动态库，并根据引擎类型和
			  动态库句柄创建不同类型的数据源。                                             
    \attention   
   ----------------------------------------------------------------------------------<br>
    Copyright (c) 1996-2005 SuperMap GIS Technologies,Inc.                           <br>
    All Rights Reserved.                                                             <br>
   ----------------------------------------------------------------------------------<br> 
   
   **************************************************************************************
    \version 2005-05-19  陈国雄    初始化版本.                                       <br>
   **************************************************************************************
*/


#if !defined(AFX_UGDATASOURCEMANAGER_H__EA4836B3_3C1F_4535_A920_07AC41C17303__INCLUDED_)
#define AFX_UGDATASOURCEMANAGER_H__EA4836B3_3C1F_4535_A920_07AC41C17303__INCLUDED_

#include "Engine/UGDataSource.h"
#include "OGDC/OgdcProviderManager.h"

namespace UGC {
  
//##ModelId=4820305103AB
typedef OgdcProvider UGProvider;

//##ModelId=4820305103BA
class ENGINE_API UGDataSourceManager  
{
public:
	//##ModelId=4820305103BB
	UGDataSourceManager();
	//##ModelId=4820305103BC
#ifdef SYMBIAN60
	~UGDataSourceManager();
#else
	virtual ~UGDataSourceManager();
#endif
	

public:
	//========================================================
	//! \remarks 		创建数据源实例，本函数并不会真正创建一个数据源，不会生成Oracle或SQL Server数据库，
	//!			    	仅仅根据指定的数据源类型创建一个UGDataSource某个子类的实例，并返回其指针。
	//! \return 	UGDataSource*  new一个数据源指针，如果创建不成功就返回NULL。
	//! \param 		nEngineType 数据引擎类型，可以是用户扩展的引擎类型。
	//##ModelId=4820305103BE
	//! \brief 		创建数据源实例
	static UGDataSource* CreateDataSource(UGEngineType nEngineType);

	//##ModelId=4820305103CC
	//! \brief 		创建数据源实例
	static UGint GetProviderCount();	

	//! \brief 得到引擎插件定义。
	//! \param nIndex [in] 索引。
	//##ModelId=4820305103CE
	static UGProvider GetAt(UGint nIndex);	

	//! \brief 获取引擎插件名称
	//! \param nType 传入的引擎类型
	//##ModelId=4820305103D1
	static UGString GetProviderName(UGEngineType nEngineType);	

	//! \brief 加载一个后缀名为sdx指定文件名的OGDC引擎插件动态库。
	//! \param strPathName [in]。
	//! \return 加载成功返回true。
	//##ModelId=4820305103D4
	static UGbool LoadProvider(const UGString& strPathName);	

	//! \brief 卸载后缀名为sdx的OGDC引擎插件动态库。
	//! \param hHandle [in] 动态库句柄。
	//! \return 成功卸载返回true。
	//##ModelId=4820305103D8
	static UGbool UnloadProvider(void* hHandle);

	// 加载 引擎插件 用于静态加载  for Android by liucq
	UGbool AddEngineProvider(void* handle);
};

extern ENGINE_API UGDataSourceManager g_DataSourceManager;

}

#endif // !defined(AFX_UGDATASOURCEMANAGER_H__EA4836B3_3C1F_4535_A920_07AC41C17303__INCLUDED_)

