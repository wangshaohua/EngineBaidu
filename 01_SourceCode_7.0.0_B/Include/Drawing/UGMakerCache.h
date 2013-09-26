
#if !defined(AFX_UGMAKERCACHE_H__37037E0D_8ABC_413E_B8BE_2B8916F0319E__INCLUDED_)
#define AFX_UGMAKERCACHE_H__37037E0D_8ABC_413E_B8BE_2B8916F0319E__INCLUDED_

#pragma once

#include "Toolkit/UGThread.h"
#include "Toolkit/UGPalette.h"

#include <list>
using namespace std;

namespace UGC {

struct DRAWING_API UGMakerInfo
{
	UGString strText;
	UGRect2D rcBounds;
	UGImageData* pImageData;
};

class DRAWING_API UGMakerCache
{
	typedef list<UGMakerInfo*> MakerInfoList;
public:
	UGMakerCache();
	~UGMakerCache();

public:
	void SetCacheParam(UGdouble dScale, const UGRect2D& rcBounds);
	void SwitchCache();

	void Add(UGMakerInfo* pMakerInfo);
	UGMakerInfo* RemoveHead();
	UGMakerInfo* RemoveTail();
	UGbool IsEmptyCurList();
	void RemoveAllCurList();
	void RemoveAllCacheList();

	UGdouble GetCurScale();
	UGRect2D GetCurBounds();

	void Lock();
	void UnLock();

private:
	UGdouble m_dCacheScale;
	UGRect2D m_rcCacheBounds;
	MakerInfoList* m_pMakerCacheList;

	UGMutex m_mutexList;
	UGdouble m_dCurScale;
	UGRect2D m_rcCurBounds;
	MakerInfoList* m_pMakerCurList;
	
};

//////////////////////////////////////////////////////////////////////////

}

#endif // !defined(AFX_UGMAKERCACHE_H__37037E0D_8ABC_413E_B8BE_2B8916F0319E__INCLUDED_)