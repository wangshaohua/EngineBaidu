////////////////////////////////////////////////////////////////////////////
//                    _   _   ____   ____                    
//   Project         | | | | / ___) / ___)                   
//                   | | | || | __ | |                       
//                   | |_| || |_\ || \___                    
//                    \____/ \____| \ ___)     6.0           
//                                                           
//!  \brief Class 。
//!  \details 数据转换组。
//!  \author 数据转换组
//!  \attention 
//!   Copyright (c) 1996-2010 SuperMap Software Limited Company.  <br> 
//!   All Rights Reserved.
//!  \version 6.0
//////////////////////////////////////////////////////////////////////////

#ifndef AFX_UGMAPSERVICESTUBMANAGER_H__INCLUDED_
#define AFX_UGMAPSERVICESTUBMANAGER_H__INCLUDED_

//#if _MSC_VER > 1000
//#pragma once
//#endif // _MSC_VER > 1000

#include "Stream/ugdefs.h"
#include "MapServiceStub/UGMapServiceType.h"
#include "MapServiceStub/UGMapServiceStubDefine.h"
#include "MapServiceStub/UGMapServiceStub.h"


namespace UGC {

//! \brief 转换参数管理。	
class MAPSERVICESTUB_API UGMapServiceStubManager  
{

public:
	//! \brief 构造函数。
	UGMapServiceStubManager();

	//! \brief 析构函数。
	virtual ~UGMapServiceStubManager();

// 	//! \brief 得到服务管理插件的数目。
// 	static UGint GetCount();		
// 
// 	//! \brief 得到服务管理工厂定义。
// 	//! \param nIndex [in] 索引。
// 	//! \return 。
// 	static UGMapServiceStubDefine* GetAt(UGint nIndex);	
// 
// 	//! \brief 加载一个指定文件名的服务管理插件。
// 	//! \param strPathName [in]。
// 	//! \return 加载成功返回true。
// 	static UGbool LoadWPI(const UGString& strPathName);	
// 
// 	//! \brief 卸载服务管理插件。
// 	//! \param hHandle [in] 动态库句柄。
// 	//! \return 成功卸载返回true。
// 	static UGbool UnloadWPI(void* hHandle);		

	//! \brief 创建一个服务管理类。
	static UGMapServiceStub* CreateMapServiceStub(UGint nSeviceType);

// 	//! \brief 删除服务管理类。
// 	static void DestroyMapServiceStub(UGMapServiceStub*& pWebStub);
// 
// 	//! \brief 得到能够支持的服务管理类型。
// 	static void GetSupportServiceTypes(UGArray<UGint>& arrSeviceTypes);
// 
// 	// 添加服务插件，用于静态加载 for Android by liucq
// 	UGbool AddServiceProvider(void* handle);
// 
// private:
// 	UGMapServiceStubDefine* Check(void* hHandle);
// 	UGMapServiceStubDefine* Find(UGint nServiceType);
// 	void LoadWPI();
// 	void UnloadWPI();
// private:
// 	UGbool m_bLoaded;
// 	UGMutex m_mutex;
// 	UGArray<UGMapServiceStubDefine*> m_MapServiceStubDefines;
};

/*extern MAPSERVICESTUB_API UGMapServiceStubManager g_MapServiceStubManager;*/

}//namespace UGC

#endif // !defined(AFX_UGMAPSERVICESTUBMANAGER_H__AB19AA8C_B64E_42F0_BFF3_DDE67CDBA62F__INCLUDED_)

