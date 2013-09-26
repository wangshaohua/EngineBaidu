// UGImageManager.h: interface for the UGImageManager class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_UGIMAGEMANAGER_H__D47A6033_C470_4B3B_9AE7_70EAE68D0BC2__INCLUDED_)
#define AFX_UGIMAGEMANAGER_H__D47A6033_C470_4B3B_9AE7_70EAE68D0BC2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "UGPluginDefine.h"
#include "UGImagePlugin.h"

namespace UGC
{

class FILEPARSER_API UGImageManager  
{
public:
	UGImageManager();
	virtual ~UGImageManager();

public:	
	//! \brief 得到影像插件的数目。
	static UGint GetPluginCount();	

	//! \brief 得到插件的名称。
	static UGString GetPluginName(const UGString& strExtName);	

	//! \brief 判断是否支持该扩展名文件。
	//! \param strExtName，传入的扩展名。
	static UGbool IsSupportExtName(const UGString& strExtName);

	//! \brief 加载一个指定文件名的影像插件。
	//! \param strPathName [in]。
	//! \return 加载成功返回true。
	static UGbool LoadPlugin(const UGString& strPathName);	

	//! \brief 卸载影像插件。
	//! \param hHandle [in] 动态库句柄。
	//! \return 成功卸载返回true。
	static UGbool UnloadPlugin(void* hHandle);	

	//! \brief 得到几何工厂定义。
	//! \param nIndex [in] 索引。
	//! \return 。
	static UGPluginDefine* GetAt(UGint nIndex);	
	
	//! \brief 创建一个影像插见实体。
	static UGImagePlugin* CreateImagePlugin(const UGString& strExtName);
	
	//! \brief 创建一个影像插见实体。
	//! \param nFileType [in] 插件类型。
	static UGImagePlugin* CreateImagePlugin(const UGint& nFileType);

	//! \brief 传入缓存配置文件的路径名
	static void SetCacheConfigFilePathName(const UGString& strPathName);

	// 添加图像插件，用于静态加载 for Android by liucq
	UGbool AddImageProvider(void* handle);

private:
	UGPluginDefine* Check(void* hHandle);
	UGPluginDefine* Find(const UGString& strExtName);
	UGPluginDefine* Find(const UGint& nFileType);
	void LoadPlugin();
	void UnloadPlugin();
	// 判断缓存版本是否为5.0以上
	UGbool CheckVersion(UGString strPath);
	// 判断缓存版本是否为7.0以上
	UGbool CheckVersionV70(UGString strPath);
	// 获取缓存版本
	UGint GetVersionFromFile(UGString strPath);

	//判断是否为网络地图缓存
	UGbool CheckWebCache(UGString strPath);

private:
	UGbool m_bLoaded;
	UGArray<UGPluginDefine*> m_pluginDefines;
	static UGString m_strCacheConfigFile;				// 缓存配置文件路径名
};

extern FILEPARSER_API UGImageManager g_imageManager;

}

#endif // !defined(AFX_UGIMAGEMANAGER_H__D47A6033_C470_4B3B_9AE7_70EAE68D0BC2__INCLUDED_)

