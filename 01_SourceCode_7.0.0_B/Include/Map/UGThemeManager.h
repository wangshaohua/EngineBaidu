// UGThemeManager.h: interface for the UGThemeManager class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_UGTHEMEMANAGER_H__FC3BDA35_5F4C_460F_B9E6_CAD1D82B029C__INCLUDED_)
#define AFX_UGTHEMEMANAGER_H__FC3BDA35_5F4C_460F_B9E6_CAD1D82B029C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "Stream/ugdefs.h"
#include "Map/UGThemeDefine.h"

namespace UGC{

class MAP_API UGThemeManager  
{
public:
	UGThemeManager();
#ifdef SYMBIAN60
	~UGThemeManager();
#else
	virtual ~UGThemeManager();
#endif


public:
	//! \brief 加载一个指定文件名的动态库。
	//! \param strPathName [in]。
	//! \return 加载成功返回true。
	static UGbool LoadTheme(const UGString& strPathName);	

	//! \brief 卸载动态库。
	//! \param hHandle [in] 动态库句柄。
	//! \return 成功卸载返回true。
	static UGbool UnloadTheme(void* hHandle);

	//! \brief 获取指定索引的专题图系统插件定义
	static UGThemeDefine* GetThemeDefine(UGint nIndex);
	//! \brief 创建专题图
	static UGTheme* NewTheme(UGTheme::UGThemeType nType);
	static UGTheme* NewTheme(UGString strThemeTypeName);

	static UGTheme* CloneTheme(UGTheme* pTheme);

	//!\ 添加专题图插件，用于静态加载 for Android by liucq
	UGbool AddThemeProvider(void* handle);

private:
	//! \brief 装载专题图系统插件
	void LoadThemes();
	//! \brief 卸载专题图系统插件
	void UnloadThemes();
	//! \brief 根据动态库句柄检出专题图系统插件定义
	UGThemeDefine* CheckThemeDef(void* hHandle)const;
	//! \brief 根据类型找到专题图系统插件定义
	UGThemeDefine* Find(UGint nType);
private:
	UGArray<UGThemeDefine* > m_themeDefs;

};

extern MAP_API UGThemeManager g_themeManger;

}

#endif // !defined(AFX_UGTHEMEMANAGER_H__FC3BDA35_5F4C_460F_B9E6_CAD1D82B029C__INCLUDED_)

