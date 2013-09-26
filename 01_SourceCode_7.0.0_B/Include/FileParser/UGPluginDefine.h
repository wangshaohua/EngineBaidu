// UGImageDefine.h: interface for the UGImageDefine class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_UGIMAGEDEFINE_H__9AAC9DC3_79C3_4D44_9904_A7D4AF8E7DA1__INCLUDED_)
#define AFX_UGIMAGEDEFINE_H__9AAC9DC3_79C3_4D44_9904_A7D4AF8E7DA1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Stream/ugdefs.h"

namespace UGC
{

class FILEPARSER_API UGPluginDefine  
{
public:
	UGPluginDefine();
	virtual ~UGPluginDefine();

public:
	void operator =(const UGPluginDefine &imageDefine);
	void Empty();

public:
	UGStrings m_aryExtNames;
	UGString m_strName;
	UGint	 m_PluginType;
	void* m_hHandle;
};


}

#endif // !defined(AFX_UGIMAGEDEFINE_H__9AAC9DC3_79C3_4D44_9904_A7D4AF8E7DA1__INCLUDED_)

