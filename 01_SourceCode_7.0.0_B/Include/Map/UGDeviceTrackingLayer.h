// UGDeviceTrackingLayer.h: interface for the UGDeviceTrackingLayer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_UGDEVICETRACKINGLAYER_H__0A3FBB17_E78E_4FDA_9DF1_D327B6647592__INCLUDED_)
#define AFX_UGDEVICETRACKINGLAYER_H__0A3FBB17_E78E_4FDA_9DF1_D327B6647592__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Stream/ugdefs.h"
#include "Drawing/UGDrawing.h"
#include "Map/UGTrackingLayer.h"

namespace UGC {

class MAP_API UGDeviceTrackingLayer:public UGTrackingLayer  
{
public:
	UGDeviceTrackingLayer();
	
#ifdef SYMBIAN60
	~UGDeviceTrackingLayer();
#else
	virtual ~UGDeviceTrackingLayer();
#endif

	//! \brief »æÖÆ
	UGbool OnDraw(UGGraphics* pGraphics, UGDrawing *pDrawing);

private:

};

}
#endif // !defined(AFX_UGDEVICETRACKINGLAYER_H__0A3FBB17_E78E_4FDA_9DF1_D327B6647592__INCLUDED_)

