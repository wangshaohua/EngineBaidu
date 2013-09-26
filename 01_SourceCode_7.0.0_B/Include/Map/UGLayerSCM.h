#pragma once

#if !defined(AFX_UGLAYERSCM_H__A4B470F7_6A63_4275_BB1D_EF15BAD2DDAD__INCLFUDED_)
#define AFX_UGLAYERSCM_H__A4B470F7_6A63_4275_BB1D_EF15BAD2DDAD__INCLFUDED_

#include "Map/UGLayer.h"
#include "Workspace/UGWorkspace.h"
#include "Map/UGMap.h"

namespace UGC {

class MAP_API UGLayerSCM : public UGLayer
{
public:
	UGLayerSCM(void);
	virtual ~UGLayerSCM(void);

public:
	UGbool OnDraw(UGGraphics* pGraphics, UGDrawing* pDrawing);
	// 内部不实现，必须是 UGLayer::UG_Layer_SCM 类型，不允许修改
	virtual void SetType(UGLayer::UGLayerType nType);
	// 把参数都初始化好了
	virtual void SetDataset(UGDataset *pDataset, UGbool bInit = true, UGbool bClearRecordsets = true);

private:
	UGWorkspace m_Workspace;
	UGMap m_Map;
};

}

#endif

