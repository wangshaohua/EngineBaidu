// UGInterNationalDefine.h: interface for the UGInterNationalDefine class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_UGINTERNATIONALDEFINE_H__57D4C3A3_4FC5_499D_80A9_8AEBB967E5CC__INCLUDED_)
#define AFX_UGINTERNATIONALDEFINE_H__57D4C3A3_4FC5_499D_80A9_8AEBB967E5CC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "Toolkit/UGInterNational.h"
using namespace UGC;
namespace UGC
{
	  //!  \brief Toolkit
class TOOLKIT_API UGInterNationalDefine  
{
public:
	//! \brief
	  //!  \brief Toolkit
	UGInterNationalDefine();
	//! \brief
	  //!  \brief Toolkit
	~UGInterNationalDefine();
public:
	  //!  \brief Toolkit
	UGString m_strName;
	  //!  \brief Toolkit
	void* m_hHandle;
	  //!  \brief Toolkit
	UGInterNational *m_pInter;

};
}

#endif // !defined(AFX_UGINTERNATIONALDEFINE_H__57D4C3A3_4FC5_499D_80A9_8AEBB967E5CC__INCLUDED_)

