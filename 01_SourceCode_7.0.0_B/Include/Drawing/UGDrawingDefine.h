// UGDrawSysDefine.h: interface for the UGDrawSysDefine class.
//
//////////////////////////////////////////////////////////////////////

#ifndef UGDRAWSYSTDEFINE_H
#define UGDRAWSYSTDEFINE_H

#include "Stream/ugdefs.h"
#include "Drawing/UGDrawingGeometry.h"

namespace UGC{

class DRAWING_API UGDrawingDefine  
{
public:
	UGDrawingDefine();

#ifdef SYMBIAN60
	~UGDrawingDefine();
#else
	virtual ~UGDrawingDefine();
#endif

public:
	//! \brief Drawing插件名称
	UGString m_strName;
	//! \brief Drawing插件句柄
	void* m_hHandle;
	//! \brief 绘制几何对象
	UGDrawingGeometry* m_pDrawingGeometry;

};

}

#endif // !defined(AFX_UGDRAWSYSDEFINE_H__387A69C7_04C4_4516_80FE_316ABB36ABFC__INCLUDED_)

