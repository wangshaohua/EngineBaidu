// UGFeatureOgdc.h: interface for the UGFeatureOgdc class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_UGFEATUREOGDC_H__8FC0C4F6_9CB9_4E1A_9F44_F579DFDEC94F__INCLUDED_)
#define AFX_UGFEATUREOGDC_H__8FC0C4F6_9CB9_4E1A_9F44_F579DFDEC94F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Geometry/UGFeature.h"

namespace UGC {

//##ModelId=483BB708036B
class GEOMETRY_API UGFeatureOgdc : public OgdcFeature  
{
public:
	//##ModelId=483BB708036D
	UGFeatureOgdc();
	//##ModelId=483BB708036E
	virtual ~UGFeatureOgdc();

public:
	//##ModelId=483BB7080370
	virtual OgdcInt GetID() const;	
	
	//! \brief 设置几何对象ID。
	//! \param nID 几何对象ID[in]。
	//##ModelId=483BB708037B
	virtual void SetID(OgdcInt nID);	

	//! \brief 获取几何对象，外面不能释放。
	//! \return 是否取几何对象成功，成功返回几何对象，失败返回NULL。
	//##ModelId=483BB708037E
	virtual OgdcElement* GetElement();	
	
	//! \brief 设置当前特征要素的几何对象，设置以后外面不能释放。
	//! \param pElement 几何对象指针[in]。
	//##ModelId=483BB7080380
	virtual void SetElement(OgdcElement* pElement);	

	//! \brief 根据字段序号获取字段值。
	//! \param nIndex 字段序号[in]。
	//##ModelId=483BB708038C
	virtual OgdcBool GetValue(OgdcInt nIndex, OgdcVariant& varValue);

	//! \brief 根据字段名获取字段值。
	//! \param strFieldName 字段名[in]。
	//##ModelId=483BB7080390
	virtual OgdcBool GetValue(const OgdcString& strFieldName, OgdcVariant& varValue);	

	//! \brief 根据字段序号设置字段值。
	//! \param nIndex 字段序号[in]。
	//! \param varValue 字段值 [in]。
	//! \return 是否设置成功，成功返回TRUE，失败返回FALSE。
	//##ModelId=483BB7080394
	virtual OgdcBool SetValue(OgdcInt nIndex, const OgdcVariant& varValue);    

	//! \brief 根据字段名设置字段值。
	//! \param strFieldName 字段名[in]。
	//! \param varValue 字段值 [in]。
	//! \return 是否设置成功，成功返回TRUE，失败返回FALSE。
	//##ModelId=483BB7080399
	virtual OgdcBool SetValue(const OgdcString& strFieldName, const OgdcVariant& varValue);	

	//! \brief 设置字段信息。
	//! \param fieldInfos 字段信息集合[in]。
	//##ModelId=483BB708039D
	virtual void SetFieldInfos(const OgdcFieldInfos& fieldInfos);
	
	//! \brief 获取字符集。
	//! \param nCharset [in]。
	//##ModelId=483BB70803A0
	virtual OgdcString::Charset GetCharset() const;
	
	//! \brief 设置字符集。
	//! \param nCharset [in]。
	//##ModelId=483BB70803A2
	virtual void SetCharset(OgdcString::Charset nCharset);

	//! \brief 获取UGFeature指针。
	//##ModelId=483BB70803A5
	UGFeature* GetFeature() const;

	//! \brief 由UGFeature构造UGFeatureOgdc。
	//! \param pFeature [in]。
	//##ModelId=483BB70803A7
	void SetFeature(UGFeature* pFeature);

protected:	
	//##ModelId=483BB70803AB
	UGFeature* m_pFeature;
	//##ModelId=483BB70803AF
	OgdcElement* m_pElement;
};

}

#endif // !defined(AFX_UGFEATUREOGDC_H__8FC0C4F6_9CB9_4E1A_9F44_F579DFDEC94F__INCLUDED_)

