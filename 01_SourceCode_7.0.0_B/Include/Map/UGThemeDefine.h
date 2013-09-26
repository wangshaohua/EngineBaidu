// UGThemeDefine.h: interface for the UGThemeDefine class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_UGTHEMEDEFINE_H__1DDFC658_79BE_4B1B_8BF8_C1A639057D21__INCLUDED_)
#define AFX_UGTHEMEDEFINE_H__1DDFC658_79BE_4B1B_8BF8_C1A639057D21__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Map/UGThemeFactory.h"
namespace UGC{

class MAP_API UGThemeDefine  
{
public:
	UGThemeDefine();
#ifdef SYMBIAN60
	~UGThemeDefine();
#else
	virtual ~UGThemeDefine();
#endif

public:
	//! \brief 专题图名字 
	UGString m_strName;
	//! \brief 专题图句柄
	void* m_hHandle;
	//! \brief 专题图工厂
	UGThemeFactory* m_pThemeFactory;

};

}

#endif // !defined(AFX_UGTHEMEDEFINE_H__1DDFC658_79BE_4B1B_8BF8_C1A639057D21__INCLUDED_)

