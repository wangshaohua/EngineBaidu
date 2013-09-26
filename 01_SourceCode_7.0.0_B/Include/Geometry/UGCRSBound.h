// UGCRSBound.h: interface for the UGCRSBound class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_UGCRSBOUND__INCLUDED_)
#define AFX_UGCRSBOUND__INCLUDED_

#include "Stream/ugexports.h"
#include "Stream/ugdefs.h"

namespace UGC
{

//! \brief 参考系四至结构。
//! \remarks Web图层的坐标参考系及其四至范围信息
class  GEOMETRY_API UGCRSBound  
{
public:
	//! \brief 构造函数
	UGCRSBound();
	//! \brief 构造函数
	UGCRSBound(UGString strCRSName, UGRect2D rcBound);
	UGRect2D Transform(UGString strEPSGdst);
public:
	//! \brief 图层的坐标参考系。
	UGString m_strCRSName;
	
	//! \brief 图层的四至范围。
	UGRect2D m_rcBound;
	
	UGdouble m_Resx;
	UGdouble m_Resy;
};

//! \brief 参考系四至集合。
//! \remarks 用于存放一个Web图层有多个坐标参考系及其四至范围信息的情况。
class GEOMETRY_API UGCRSBounds :public UGArray<UGCRSBound>
{
public:
	//! \brief 构造函数
	UGCRSBounds();
	//! \brief 构造函数
	UGCRSBounds(const UGCRSBounds& crsBounds);
	//! \brief 析构函数
#ifdef SYMBIAN60
	~UGCRSBounds();
#else
	virtual ~UGCRSBounds();
#endif

	
	
public:
	//! \brief operator=
	const UGCRSBounds& operator=(const UGCRSBounds& crsBounds);
	
	//! \brief GetIndexByName
	UGint GetIndexByName(const UGString& strCRSName);
	
	//! \brief GetIndexByName
	UGCRSBound* GetObjByName(const UGString& strCRSName);
};

}
#endif // !defined(AFX_UGCRSBOUND__INCLUDED_)

