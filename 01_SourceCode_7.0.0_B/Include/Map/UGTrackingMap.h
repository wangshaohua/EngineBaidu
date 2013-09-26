#if !defined(AFX_UGTRACKINGMAP_H__37037E0D_8ABC_413E_B8BE_2B8916F0319E__INCLUDED_)
#define AFX_UGTRACKINGMAP_H__37037E0D_8ABC_413E_B8BE_2B8916F0319E__INCLUDED_

#include "Stream/ugexports.h"
#include "Stream/ugdefs.h"

namespace UGC {

class UGGraphics;
class UGMap;

class MAP_API UGTrackingMap
{
public:
	UGTrackingMap();
	UGTrackingMap(UGMap* pMap);
	~UGTrackingMap();

	UGbool Open(UGMap* pMap);

	UGMap* GetMap();

	UGbool OutputMap(UGGraphics* pGraphics, UGRect rcBounds, UGbool *pbBlank = NULL, UGbool bNoBackground = false);
		
private:		
	UGMap* m_pMap;

};

}

#endif // AFX_UGTRACKINGMAP_H__37037E0D_8ABC_413E_B8BE_2B8916F0319E__INCLUDED_