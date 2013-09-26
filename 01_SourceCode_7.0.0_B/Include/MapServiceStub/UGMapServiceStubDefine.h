// UGMapServiceStubDefine.h: interface for the UGFileParseDefine class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_UGMAPSERVICESTUBDEFINE_H__D1C1742B_DF3C_4125_B515_2C1599C1E499__INCLUDED_)
#define AFX_UGMAPSERVICESTUBDEFINE_H__D1C1742B_DF3C_4125_B515_2C1599C1E499__INCLUDED_

#include "MapServiceStub/UGMapServiceStubFactory.h"

namespace UGC 
{

class MAPSERVICESTUB_API UGMapServiceStubDefine  
{
public:
	UGMapServiceStubDefine();
	UGMapServiceStubDefine(const UGMapServiceStubDefine &webStubDefine);
	virtual ~UGMapServiceStubDefine();
	
public:
	const UGMapServiceStubDefine& operator=(const UGMapServiceStubDefine &webStubDefine);
	void Empty();
	
public:
	UGMapServiceStubFactory* m_pWebStubFactory;
	UGString m_strName;
	void* m_hHandle;
};

}

#endif // !defined(AFX_UGMAPSERVICESTUBDEFINE_H__D1C1742B_DF3C_4125_B515_2C1599C1E499__INCLUDED_)

