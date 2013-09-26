// UGDrawSysManager.h: interface for the UGDrawSysManager class.
//
//////////////////////////////////////////////////////////////////////

#ifndef UGDRAWINGMANAGER_H
#define UGDRAWINGMANAGER_H

#include "Stream/ugdefs.h"
#include "Drawing/UGDrawingGeometry.h"
#include "Drawing/UGDrawingDefine.h"
#include "Toolkit/UGThread.h"
#include "Toolkit/UGLicense.h"

namespace UGC{

class DRAWING_API UGDrawingManager  
{
public:
	UGDrawingManager();
	~UGDrawingManager();

public:
	//! \brief 得到显示系统插件个数
	static UGint GetDrawingCount();
	//! \brief 得到显示系统默认插件
	static UGDrawingGeometry* GetDefaultDrawingGeometry();
	//! \brief 查找能够显示指定几何对象类型的显示系统
	static UGDrawingGeometry* FindDrawingGeometry(UGint nGeometryType);
	//! \brief 查找能够显示指定几何对象类型的显示系统
	static UGbool DrawingGeometry(UGDrawing* pDrawing,UGGeometry* pGeo);

	//! \brief 加载一个指定文件名的动态库。
	//! \param strPathName [in]。
	//! \return 加载成功返回true。
	static UGbool LoadDrawingGeometry(const UGString& strPathName);	

	//! \brief 卸载动态库。
	//! \param hHandle [in] 动态库句柄。
	//! \return 成功卸载返回true。
	static UGbool UnloadDrawingGeometry(void* hHandle);

	//! \brief 获取指定索引的显示系统插件定义
	static UGDrawingDefine* GetDrawingDefines(UGint nIndex);

	//! \brief 装载显示系统插件
	void LoadDrawingGeometry();

	// 添加显示系统，用于静态加载 for Android by liucq
	UGbool AddDrawingProvider(void* handle);

private:
	
	//! \brief 卸载显示系统插件
	void UnloadDrawingGeometry();
	//! \brief 根据动态库句柄检出显示系统插件定义
	UGDrawingDefine* ChecktDrawingDef(void* hHandle);
	//! \brief 查找能够显示指定几何对象类型的显示系统插件定义
	UGDrawingDefine* FindDrawingDef(UGint nGeometryType);
	//! \brief 添加显示系统插件定义
	void AddDrawingDefine(UGDrawingDefine* pDrawingDef);
private:
	UGArray<UGDrawingDefine* > m_DrawingDefines;
	UGMutex m_mutex;
	UGbool m_bLoaded;
	UGLicense* m_pLicense;
};

extern DRAWING_API UGDrawingManager g_drawingManager;

}
#endif // !defined(AFX_UGDRAWSYSMANAGER_H__61326E64_8C8B_4BD7_BA7F_001FB0685232__INCLUDED_)

