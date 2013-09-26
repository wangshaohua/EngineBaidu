// UGDrawingGeometry.h: interface for the UGDrawingGeometry class.
//
//////////////////////////////////////////////////////////////////////

#ifndef UGDRAWINGGEOMETRY_H
#define UGDRAWINGGEOMETRY_H

#include "Stream/ugdefs.h"
#include "Drawing/UGDrawing.h"
namespace UGC{
#ifdef SYMBIAN60
class DRAWING_APIC UGDrawingGeometry
#else
class DRAWING_API UGDrawingGeometry
#endif
{
public:
	DRAWING_APIF UGDrawingGeometry();
	virtual DRAWING_APIF ~UGDrawingGeometry();

public:
	//! \brief 是否支持几何对象类型
	virtual DRAWING_APIF UGbool IsSupportGeometry(UGint nGeometryType);
	//! \brief 得到所有支持的几何对象类型
	virtual DRAWING_APIF UGint GetSupportGeoType(UGArray<UGint>& nTypeArray);
	//! \brief 获取工厂名称
	virtual DRAWING_APIF UGString GetName();
	//! \brief 显示几何对象
	virtual DRAWING_APIF UGbool DrawingGeometry(UGDrawing* pDrawing,UGGeometry* pGeo);

	//added by xielin 2007-04-30 
    //! \brief 设置扩展对象绘制函数
	//! \param pDrawCustomGeometryFunc 设置扩展对象的函数指针
	//! \param pWnd 函数指针的Hand
	//! \remarks 用户自定义的geometry只在基类中支持绘制，在其他继承类中（比如DrawingGeometryCAD中）设置此回调函数也是无效的，不会进行绘制。
	DRAWING_APIF void SetDrawCustomGeometryFunc(DRAWCUSTOMGEOMETRYCALLBACKPROC pDrawCustomGeometryFunc,
		UGlong pWnd);
protected:

//{{modified by qianjn in 2010-6-24 13:44:05 修改原因：多线程出图问题

// 	UGbool DrawGeometry(UGGeoPoint* pGeo);
// 	UGbool DrawGeometry(UGGeoLine* pGeo);
// 	UGbool DrawGeometry(UGGeoRegion* pGeo);
// 	UGbool DrawGeometry(UGGeoText* pGeo, UGbool bThemeStyle = false, UGbool bSingleTextStyle = true);	
// 	UGbool DrawGeometry(UGGeoCompound* pGeo
	DRAWING_APIF UGbool DrawGeometry(UGDrawing* pDrawing, UGGeoPoint* pGeo);
	DRAWING_APIF UGbool DrawGeometry(UGDrawing* pDrawing, UGGeoLine* pGeo);
	DRAWING_APIF UGbool DrawGeometry(UGDrawing* pDrawing, UGGeoRegion* pGeo);
	DRAWING_APIF UGbool DrawGeometry(UGDrawing* pDrawing, UGGeoText* pGeo, UGbool bThemeStyle = false, UGbool bSingleTextStyle = true);	
	DRAWING_APIF UGbool DrawGeometry(UGDrawing* pDrawing, UGGeoCompound* pGeo);

#if !defined SYMBIAN60 && !defined  OS_ANDROID && !defined (IOS)

// 	UGbool DrawGeometry(UGGeoLineM* pGeo);
// 	UGbool DrawGeometry(UGGeoMultiPoint* pGeo);
// 	UGbool DrawGeometry(UGGeoPicture* pGeo);
	UGbool DrawGeometry(UGDrawing* pDrawing, UGGeoLineM* pGeo);
	UGbool DrawGeometry(UGDrawing* pDrawing, UGGeoMultiPoint* pGeo);
#endif	
	UGbool DrawGeometry(UGDrawing* pDrawing, UGGeoPicture* pGeo);
//}}modified by qianjn in 2010-6-24 13:44:05 修改完毕

	//! \return 计算复合对象里对象绘制后的地理bounds(目前就图例会用到，这里只计算了文本的bounds)
	UGbool CalcGeoCompoundBounds(UGDrawing* pDrawing, UGArray<UGGeometry*>& arrGeometry, UGRect2D& rcBounds);

	//! \return 根据范围创建裁剪区域
	UGRgn* CreateClipRgn(UGDrawing* pDrawing, UGRect2D rcBounds);


	DRAWING_APIF void AttachDrawing(UGDrawing* pDrawing);
	friend class UGDrawing;
protected:
	UGDrawing* m_pDrawing;

private:
	//added by xielin 2007-04-30扩展对象绘制回调函数
	DRAWCUSTOMGEOMETRYCALLBACKPROC m_pDrawCustomGeometryFunc;
	UGlong m_pDrawCustomGeometryWnd;
	

};

}

#endif // !defined(AFX_UGDRAWINGGEOMETRY_H__19C27E20_03AE_45A6_8592_9EB5EF5584FE__INCLUDED_)

