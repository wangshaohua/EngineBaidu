// UGVectorManager.h: interface for the UGVectorManager class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_UGVectorManager_H__D47A6033_C470_4B3B_9AE7_70EAE68D0BC2__INCLUDED_)
#define AFX_UGVectorManager_H__D47A6033_C470_4B3B_9AE7_70EAE68D0BC2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "UGPluginDefine.h"
#include "UGVectorPlugin.h"

namespace UGC
{

class FILEPARSER_API UGVectorManager  
{
public:
	UGVectorManager();
	virtual ~UGVectorManager();

public:	
	//! \brief 得到影像插件的数目。
	static UGint GetPluginCount();	

	//! \brief 加载一个指定文件名的矢量插件。
	//! \param strPathName [in]。
	//! \return 加载成功返回true。
	static UGbool LoadPlugin(const UGString& strPathName);	

	//! \brief 卸载矢量插件。
	//! \param hHandle [in] 动态库句柄。
	//! \return 成功卸载返回true。
	static UGbool UnloadPlugin(void* hHandle);	

	//! \brief 得到几何工厂定义。
	//! \param nIndex [in] 索引。
	//! \return 。
	static UGPluginDefine* GetAt(UGint nIndex);	

	//! \brief 创建一个矢量插见实体。
	//! \param nFileType [in] 插件类型。
	static UGVectorPlugin* CreateVectorPlugin(const UGint& nFileType);

	// 添加矢量插件，用于静态加载 for Android by liucq
	UGbool AddVectorProvider(void* handle);

private:
	UGPluginDefine* Check(void* hHandle);
	UGPluginDefine* Find(const UGint& nFileType);
	void LoadPlugin();
	void UnloadPlugin();

private:
	UGbool m_bLoaded;
	UGArray<UGPluginDefine*> m_PluginDefines;	
};

extern FILEPARSER_API UGVectorManager g_vectorManager;

}

#endif // !defined(AFX_UGVectorManager_H__D47A6033_C470_4B3B_9AE7_70EAE68D0BC2__INCLUDED_)

