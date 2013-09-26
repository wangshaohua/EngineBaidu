// MyStackWalker.h: interface for the MyStackWalker class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYSTACKWALKER_H__03945179_0E8F_4D92_8E86_F3E148715BF8__INCLUDED_)
#define AFX_MYSTACKWALKER_H__03945179_0E8F_4D92_8E86_F3E148715BF8__INCLUDED_

#ifdef WIN32

#include <windows.h>
#include <tchar.h>
#include <stdio.h>

#if _MSC_VER >= 1300
#include <Tlhelp32.h>
#endif
#include "Stream/ugdefs.h"
#include "StackWalker.h"
using namespace UGC;
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
namespace UGC
{
class MyStackWalker : public StackWalker
{
public:
	//! \brief Toolkit
	MyStackWalker() : StackWalker() {}
	//!  \brief Toolkit
	MyStackWalker(DWORD dwProcessId, HANDLE hProcess) : StackWalker(dwProcessId, hProcess) {}
	//!  \brief Toolkit
	virtual void OnOutput(LPCSTR szText)
	{ /*printf(szText);*/ 
#ifdef _UGUNICODE
		UGint nSize = strlen(szText);
		if(nSize >0)
		{
			UGchar* pStr = new UGchar[nSize];
			UGUnicodeString::AcharToWchar(szText,pStr,nSize);
			m_str=m_str+pStr;
			delete[] pStr;
		}

#else
		m_str=m_str+szText;
#endif
		
	  //!  \brief Toolkit
		StackWalker::OnOutput(szText); 
	}
	//!  \brief Toolkit
	const UGString GetStringInfo() const
	{
	  //!  \brief Toolkit
		return m_str;
	}
	//!  \brief Toolkit
	void Clean()
	{
	  //!  \brief Toolkit
		m_str=_U("");
	}
private:
	
	UGString m_str;
};

} // end UGC;

#endif //#ifdef WIN32

#endif // !defined(AFX_MYSTACKWALKER_H__03945179_0E8F_4D92_8E86_F3E148715BF8__INCLUDED_)

