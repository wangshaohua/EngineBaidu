// UGDrawing3D.h: interface for the UGDrawing3D class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_UGDRAWING3D_H__8E658663_D359_4EDC_BEBA_B9559F201036__INCLUDED_)
#define AFX_UGDRAWING3D_H__8E658663_D359_4EDC_BEBA_B9559F201036__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Drawing/UGDrawingGeometry.h"
#include "Geometry3D/UGGeoPoint3D.h"
#include "Geometry3D/UGGeoLine3D.h"
#include "Geometry3D/UGGeoRegion3D.h"
#include "Geometry3D/UGGeoCircle3D.h"
#include "Geometry3D/UGGeoParticle.h"
namespace UGC
{

class DRAWING3D_API UGDrawingGeometry3D : public UGDrawingGeometry
{
public:
	UGDrawingGeometry3D();
	virtual ~UGDrawingGeometry3D();
public:
//! \brief 是否支持几何对象类型
	virtual UGbool IsSupportGeometry(UGint nGeometryType);
	//! \brief 得到所有支持的几何对象类型
	virtual UGint GetSupportGeoType(UGArray<UGint>& nTypeArray);
	//! \brief 获取Geometry工厂名称
	virtual UGString GetName();
	//! \brief 显示几何对象
	virtual UGbool DrawingGeometry(UGDrawing* pDrawing,UGGeometry* pGeo);
protected:
	UGbool DrawGeometry(UGDrawing* pDrawing, UGGeoPoint3D* pGeo);
	UGbool DrawGeometry(UGDrawing* pDrawing, UGGeoLine3D* pGeo);
	UGbool DrawGeometry(UGDrawing* pDrawing, UGGeoRegion3D* pGeo);
	UGbool DrawGeometry(UGDrawing* pDrawing, UGGeoCircle3D* pGeo);
	UGbool DrawGeometry(UGDrawing* pDrawing, UGGeoModel* pGeo);
	UGbool DrawGeometry(UGDrawing* pDrawing, UGGeoParticle* pGeo);
// 	UGbool DrawGeometry(UGGeoPoint3D* pGeo);
// 	UGbool DrawGeometry(UGGeoLine3D* pGeo);
// 	UGbool DrawGeometry(UGGeoRegion3D* pGeo);
// 	UGbool DrawGeometry(UGGeoCircle3D* pGeo);
// 	UGbool DrawGeometry(UGGeoPoint3D* pGeo);
// 	UGbool DrawGeometry(UGGeoLine3D* pGeo);
// 	UGbool DrawGeometry(UGGeoRegion3D* pGeo);
// 	UGbool DrawGeometry(UGGeoCircle3D* pGeo);
// 	UGbool DrawGeometry(UGGeoPoint3D* pGeo);
// 	UGbool DrawGeometry(UGGeoLine3D* pGeo);
// 	UGbool DrawGeometry(UGGeoRegion3D* pGeo);
// 	UGbool DrawGeometry(UGGeoCircle3D* pGeo);
// 	UGbool DrawGeometry(UGGeoPoint3D* pGeo);
// 	UGbool DrawGeometry(UGGeoLine3D* pGeo);
// 	UGbool DrawGeometry(UGGeoRegion3D* pGeo);
// 	UGbool DrawGeometry(UGGeoCircle3D* pGeo);
// 	UGbool DrawGeometry(UGGeoPoint3D* pGeo);
// 	UGbool DrawGeometry(UGGeoLine3D* pGeo);
// 	UGbool DrawGeometry(UGGeoRegion3D* pGeo);
// 	UGbool DrawGeometry(UGGeoCircle3D* pGeo);
// 	UGbool DrawGeometry(UGGeoPoint3D* pGeo);
// 	UGbool DrawGeometry(UGGeoLine3D* pGeo);
// 	UGbool DrawGeometry(UGGeoRegion3D* pGeo);
// 	UGbool DrawGeometry(UGGeoCircle3D* pGeo);
// 	UGbool DrawGeometry(UGGeoPoint3D* pGeo);
// 	UGbool DrawGeometry(UGGeoLine3D* pGeo);
// 	UGbool DrawGeometry(UGGeoRegion3D* pGeo);
// 	UGbool DrawGeometry(UGGeoCircle3D* pGeo);
};
extern "C" DRAWINGCAD_API UGDrawingGeometry* CreateDrawingGeometry();
}

#endif // !defined(AFX_UGDRAWING3D_H__8E658663_D359_4EDC_BEBA_B9559F201036__INCLUDED_)

