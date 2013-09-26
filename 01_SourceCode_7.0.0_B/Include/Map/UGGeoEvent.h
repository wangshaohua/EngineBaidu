// UGGeoEvent.h: interface for the UGGeoEvent class.
//
//////////////////////////////////////////////////////////////////////

/*!
   **************************************************************************************
    \file     UGGeoEvent.h
   **************************************************************************************
    \author   陈国雄
    \brief    跟踪图层事件对象类。                                                                       
    \attention   
   ----------------------------------------------------------------------------------<br>
    Copyright (c) 2000-2010 SuperMap Software Co., Ltd.                           <br>
    All Rights Reserved.                                                             <br>
   ----------------------------------------------------------------------------------<br> 
   
   **************************************************************************************
    \version 2005-05-20  陈国雄    初始化版本.                                       <br>
   **************************************************************************************
*/

#if !defined(AFX_UGGEOEVENT_H__6A5EEB50_CB05_4157_8707_8B9B17A9DE1D__INCLUDED_)
#define AFX_UGGEOEVENT_H__6A5EEB50_CB05_4157_8707_8B9B17A9DE1D__INCLUDED_

#include "Geometry/UGGeometry.h"
#include "Engine/UGDatasetVector.h"

namespace UGC {

class MAP_API UGGeoEvent  
{
public:
	UGGeoEvent(UGRecordset* pRecordset );
#ifdef SYMBIAN60
	~UGGeoEvent();
#else
	virtual ~UGGeoEvent();
#endif

public:	
	//! \brief 获取该几何对象
	UGGeometry* GetGeometry()const;
	//! \brief 设置对应几何对象
	//! \return 设置几何对象是否成功
	UGbool SetGeometry(const UGGeometry* pGeometry);
	//! \brief 设置几何对象对应的风格
	void SetStyle(const UGStyle& style);
	//! \brief 释放几何对象
	void ReleaseGeometry();
	//! \brief 几何对象移动到
	void MoveTo(UGdouble dx, UGdouble dy);	
	//! \brief 几何对象移动
	void Move(UGdouble dx, UGdouble dy);	

	//! \brief 得到几何对象的标签
	UGString GetTag()const;
	//! \brief 设置几何对象的标签
	void SetTag(const UGString& strTag);

//	UGPoint2D GetCurPos()const;
//	void SetCurPos(const UGPoint2D& pntCurPos);

	//! \brief   读取GeoEvent的XML信息
	UGbool FromXML(const UGString& strXML, UGint nVersion = 0);
	//! \brief   保存GeoEvent为XML
	UGString ToXML(UGint nVersion = 0)const;

//{{ added by xiaoys at 20120628 扩展支持属性 
	//! \brief  增加一个带属性的标注对象；
	UGbool AddFeature(UGGeometry *pGeometry, const UGArray<UGString> &aryFields, const UGArray<UGVariant *> &aryValues);

	//! \brief   获取指定字段的属性值
	UGbool GetFeature(UGVariant& var,const UGString& strField);

	//! \brief设置字段的值；
	UGbool SetFeature(const UGString& strField,const UGVariant& var);

	//! \brief设置多个字段的值；
	UGbool SetFeatures(const UGArray<UGString>& arFields,const UGArray<UGVariant>& var);
//}} added by xiaoys at 20120628

//{{ add by xiaoys 2012-10-29 更新m_Recordset,当外部Recordset重构的时候需要同时更新GeoEvent的指针
	UGbool UpdateRecordset(UGRecordset* pRecordset);
//}} add by xiaoys 2012-10-29 更新m_Recordset,当外部Recordset重构的时候需要同时更新GeoEvent的指针
//}} added by mahb at 20120628 
public:
	//! \brief 记录集
	UGRecordset* m_pRecordset; 
	//! \brief 记录集ID
	UGint m_nSmid;
	//! \brief 标签
	UGString m_strTag;		
//	UGPoint2D m_pntCurPos;	//当前位置

	//优化全部清空跟踪层的标记
	UGbool m_bIsNeedReleaseGeometry;
private:
	UGGeoEvent(){}

};

}

#endif // !defined(AFX_UGGEOEVENT_H__6A5EEB50_CB05_4157_8707_8B9B17A9DE1D__INCLUDED_)

