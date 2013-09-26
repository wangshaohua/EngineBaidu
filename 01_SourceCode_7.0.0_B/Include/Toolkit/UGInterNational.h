// UGInterNational.h: interface for the UGInterNational class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_UGINTERNATIONAL_H__A0DE3603_406A_4067_873B_E89DE17D39CB__INCLUDED_)
#define AFX_UGINTERNATIONAL_H__A0DE3603_406A_4067_873B_E89DE17D39CB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000



#include "Stream/ugdefs.h"

using namespace  UGC;

namespace UGC
{
#ifdef SYMBIAN60
class TOOLKIT_APIC UGInterNational  
#else
class TOOLKIT_API UGInterNational
#endif
{
public:

	  //!  \brief Toolkit
enum Type
{
	//! 空类型
	  //!  \brief Toolkit
	InterNuLL	= 0, 
		//! \brief 点类型	
	  //!  \brief Toolkit
	InterICU	= 1, 
		
};
public:
	  //!  \brief Toolkit
	TOOLKIT_APIF UGInterNational();
public:
	//! \brief
	  //!  \brief Toolkit
	static TOOLKIT_APIF UGInterNational& GetInstance();
	//! \brief
	  //!  \brief Toolkit
	virtual  TOOLKIT_APIF ~UGInterNational();
	//! \brief

	//! \brief
	virtual  TOOLKIT_APIF UGbool SetLocale(const UGString& strLocale);
	//! \brief
	virtual  TOOLKIT_APIF UGString GetLocale();
	//! \brief
	
	//! \brief
	virtual  TOOLKIT_APIF UGbool SetCurrency(const UGString& strCurrency);
	//! \brief
	virtual  TOOLKIT_APIF UGString GetCurrency();
	//! \brief

	//! \brief
	virtual  TOOLKIT_APIF UGbool SetTimeZone(const UGString& strTimeZone);
	//! \brief
	virtual  TOOLKIT_APIF UGString GetTimeZone();
	//! \brief

	//! \brief
	virtual  TOOLKIT_APIF void SetCharset(UGMBString::Charset charset);
	//! \brief
	virtual  TOOLKIT_APIF UGMBString::Charset GetCharset();
	//! \brief

	//! \brief

	//! \brief
	virtual  TOOLKIT_APIF UGbool NumberToString(const UGdouble dSource,UGString& strTarget);
	//! \brief
 	virtual TOOLKIT_APIF UGbool NumberToString(const UGint nSource,UGString& strTarget);
	//! \brief
	virtual TOOLKIT_APIF UGbool NumberToString(const UGlong nSource,UGString& strTarget);
	//! \brief

	//! \brief
	virtual TOOLKIT_APIF UGbool CurrencyToString(const UGdouble dSource,UGString& strTarget);
	//! \brief
	virtual TOOLKIT_APIF UGbool CurrencyToString(const UGint nSource,UGString& strTarget);
	//! \brief
	virtual TOOLKIT_APIF UGbool CurrencyToString(const UGlong nSource,UGString& strTarget);
	//! \brief

	//! \brief
	
	//! \brief
	virtual TOOLKIT_APIF UGbool PercentToString(const UGdouble dSource,UGString& strTarget);
	//! \brief
	virtual TOOLKIT_APIF UGbool PercentToString(const UGint nSource,UGString& strTarget);
	//! \brief
	virtual TOOLKIT_APIF UGbool PercentToString(const UGlong nSource,UGString& strTarget);
	//! \brief

	//! \brief
	virtual TOOLKIT_APIF UGbool ScientificToString(const UGdouble dSource,UGString& strTarget);
	//! \brief
	virtual TOOLKIT_APIF UGbool ScientificToString(const UGint nSource,UGString& strTarget);
	//! \brief
	virtual TOOLKIT_APIF UGbool ScientificToString(const UGlong nSource,UGString& strTarget);
	//! \brief

	//! \brief
	virtual TOOLKIT_APIF UGbool StringToNumber(const UGString& strSource,UGdouble& dTarget);
	//! \brief
	virtual TOOLKIT_APIF UGbool StringToNumber(const UGString& strSource,UGint& nTarget);
	//! \brief
	virtual TOOLKIT_APIF UGbool StringToNumber(const UGString& strSource,UGlong& nTarget);
	//! \brief
	
	//! \brief
	virtual TOOLKIT_APIF UGbool StringToCurrency(const UGString& strSource,UGdouble& dTarget);
	//! \brief
	virtual TOOLKIT_APIF UGbool StringToCurrency(const UGString& strSource,UGint& nTarget);
	//! \brief
	virtual TOOLKIT_APIF UGbool StringToCurrency(const UGString& strSource,UGlong& nTarget);
	//! \brief
	
	//! \brief
	
	//! \brief
	virtual TOOLKIT_APIF UGbool StringToPercent(const UGString& strSource,UGdouble& dTarget);
	//! \brief
	virtual TOOLKIT_APIF UGbool StringToPercent(const UGString& strSource,UGint& nTarget);
	//! \brief
	virtual TOOLKIT_APIF UGbool StringToPercent(const UGString& strSource,UGlong& nTarget);
	//! \brief

	//! \brief
	virtual TOOLKIT_APIF UGbool StringToScientific(const UGString& strSource,UGdouble& dTarget);
	//! \brief
	virtual TOOLKIT_APIF UGbool StringToScientific(const UGString& strSource,UGint& nTarget);
	//! \brief
	virtual TOOLKIT_APIF UGbool StringToScientific(const UGString& strSource,UGlong& nTarget);
	//! \brief

	//! \brief
	virtual TOOLKIT_APIF UGbool DateToString(const UGTime& tmSource,UGString &strTarget);
	//! \brief
	virtual TOOLKIT_APIF UGbool DateToString(const UGdouble dSource,UGString &strTarget);
	//! \brief

	//! \brief
	virtual TOOLKIT_APIF UGbool TimeToString(const UGTime& tmSource,UGString &strTarget);
	//! \brief
	virtual TOOLKIT_APIF UGbool TimeToString(const UGdouble dSource,UGString &strTarget);
	//! \brief

	//! \brief
	//! \brief
	virtual TOOLKIT_APIF UGbool DateTimeToString(const UGTime& tmSource,UGString &strTarget);
	//! \brief
	virtual TOOLKIT_APIF UGbool DateTimeToString(const UGdouble dSource,UGString &strTarget);
	//! \brief

	//! \brief
	virtual TOOLKIT_APIF UGbool StringToDate(const UGString &strSource,UGTime& tmTarget);
	//! \brief
	virtual TOOLKIT_APIF UGbool StringToDate(const UGString &strSource,UGdouble& dTarget);
	//! \brief

	//! \brief
	virtual TOOLKIT_APIF UGbool StringToTime(const UGString &strSource,UGTime& tmTarget);
	//! \brief
	virtual TOOLKIT_APIF UGbool StringToTime(const UGString &strSource,UGdouble& dTarget);
	//! \brief

	//! \brief
	virtual TOOLKIT_APIF UGbool StringToDateTime(const UGString &strSource,UGTime& tmTarget);
	//! \brief
	virtual TOOLKIT_APIF UGbool StringToDateTime(const UGString &strSource,UGdouble& dTarget);
	//! \brief

	//! \brief
public:	
	//! \brief

	//! \brief 获取本地默认的locale的字符串
	virtual TOOLKIT_APIF UGString GetDefaultLocal();
	//! \brief
	
	//! \brief 获取本地默认的currency的字符串
	virtual TOOLKIT_APIF UGString GetDefaultCurrency();
	//! \brief
	
	//! \brief  获取本地默认的区域字符串
	virtual TOOLKIT_APIF UGString GetDefaultTimeZone();
	//! \brief
    
	//! \brief  判断两个字符串所表示的时间区域是否相等
	virtual TOOLKIT_APIF UGbool   EqualLocale(const UGString& localeSrc, const UGString& localeTar);
	//! \brief
    void SetDefaultTimeFormat(const UGString& strFormat);
	//! \brief
	virtual TOOLKIT_APIF Type GetType();
	//! \brief
	virtual TOOLKIT_APIF UGString GetName();
    
	//! \brief
protected:
	//! \brief
	UGString m_strCurrency;
	//! \brief
	UGString m_strTimeZone;
	//! \brief
	//! \brief
	UGString m_strLocale;
	//! \brief
	UGString m_strFormat;
	//! \brief
	UGMBString::Charset m_charset;
};
}

#endif // !defined(AFX_UGINTERNATIONAL_H__A0DE3603_406A_4067_873B_E89DE17D39CB__INCLUDED_)

