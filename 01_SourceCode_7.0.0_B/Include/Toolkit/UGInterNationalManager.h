// UGInterNationalManager.h: interface for the UGInterNationalManager class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_UGINTERNATIONALMANAGER_H__29AC9857_8580_4118_8304_123CC237449E__INCLUDED_)
#define AFX_UGINTERNATIONALMANAGER_H__29AC9857_8580_4118_8304_123CC237449E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "Toolkit/UGInterNationalDefine.h"
using namespace UGC;
namespace UGC
{

class TOOLKIT_API UGInterNationalManager  
{
public:
	  //!  \brief Toolkit
	UGInterNationalManager();
	  //!  \brief Toolkit
	~UGInterNationalManager();
public:	
	//! \brief 得到国际化的数目。
	static UGint GetInterCount();	
	
	//! \brief 传入InterNational类型，获取指定类型InterNational的名称
	//! \param nType 传入的InterNational的类型
	static UGString GetInterNationName(UGInterNational::Type nType);		
	
	//! \brief 传入InterNational类型，生成InterNational
	//! \param nType 要创建的几何对象类型，可以传入Element类型，也可以传入InterNational类型
	//! \attention 返回的InterNational指针, 请使用后delete
	//! \return 成功,返回创建的InterNational的指针; 失败返回NULL
	static UGInterNational* CreateInterNational(UGint nType);
	
	
	//! \brief 判断是否支持该几何类型
	//! \param nType，传入的InterNational类型
	static UGbool IsSupport(UGint nGeoType);
	
	
	
private:
	UGInterNationalDefine* Check(void* hHandle);
	UGInterNationalDefine* Find(UGint nGeoType);
	void LoadInterNationalFactory();
	void UnloadInterNationalFactory();
	
private:
	UGArray<UGInterNationalDefine*> m_InterNationalDefines;
};

extern TOOLKIT_API UGInterNationalManager g_InterNationManager;


}

#endif // !defined(AFX_UGINTERNATIONALMANAGER_H__29AC9857_8580_4118_8304_123CC237449E__INCLUDED_)

