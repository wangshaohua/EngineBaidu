/*!
**************************************************************************************
\file     UGTrackingLayerEx.h
**************************************************************************************
\author   mahb,xiaoys
\brief    移动端跟踪层，支持对象符号和多标签显示。                                                           
\attention   
----------------------------------------------------------------------------------<br>
Copyright (c) 2000-2010 SuperMap Software Co., Ltd.                               <br>
All Rights Reserved.                                                             <br>
----------------------------------------------------------------------------------<br> 

**************************************************************************************
\version 2012-06-21      初始化版本.                                              <br>
**************************************************************************************
*/
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_UGTrackingLayerEx_H__E301D009_A2C1_4803_A434_C18A87419F38__INCLUDED_)
#define AFX_UGTrackingLayerEx_H__E301D009_A2C1_4803_A434_C18A87419F38__INCLUDED_

#include "Map/UGTrackingLayer.h"
//#include "ThemeBase/UGThemeLabel.h"

namespace UGC
{

typedef struct UG_SYMBOLSTYLE
{
	//! \brief 是否可见
	UGbool m_bVisible;		
	//! \brief 闪烁速率 0-不闪烁
	UGchar m_ctwinkling;
	//! \brief 符号对齐方式
	UGchar m_cAlign;
	//! \brief 符号偏移像素X
	UGshort m_sX;
	//! \brief 符号偏移像素Y
	UGshort m_sY;
	//! \brief 标题
//	UGString m_strCaption;			
//	//! \brief 风格
//	UGStyle m_Style;
	UG_SYMBOLSTYLE()
	{
		m_bVisible = true;
		m_sX = 0;
		m_sY = 0;
	}
}UGSymbolLayout;

typedef struct UG_LablelStyle
{
	//! \brief 可见
	UGbool m_bVisible;		
	//! \brief 文本偏移像素X
	UGshort m_sX;
	//! \brief 文本偏移像素Y
	UGshort m_sY;
	//! \brief 标题
	UGString m_strCaption;			
	//! \brief 风格
	UGTextStyle m_TextStyle;	
	UG_LablelStyle()
	{
		m_bVisible = true;
		m_sX = 0;
		m_sY = 0;
	}
}UGLabelStyle;

typedef struct UG_ITEM_ATTR
{
	UGString strField;
	UGVariant varValue;
}UGItemAttr;

class MAP_API UGTrackingLayerEx : public UGTrackingLayer 
{

public:
	UGTrackingLayerEx();
	virtual ~UGTrackingLayerEx();

 public:
 	//virtual UGbool OnDraw(UGGraphics* pGraphics, UGDrawing *pDrawing);
	virtual UGbool OnDraw(UGGraphics* pGraphics, UGDrawing *pDrawing);

 	//! \brief 通过跟踪层对象标签获取对象
 	virtual UGGeoEvent* GetEvent(const UGString& strTag);
 
 	////! \brief 通过跟踪层对象编号获取对象
 	//virtual UGGeoEvent* GetEvent(const UGint& iTrackID);

	//! \brief 通过跟踪层对象字段和值获取记录序号
	virtual UGint Query(UGArray<UGint>& arIDs, const UGString& strFieldName, const UGString& strVar);
 
 	//! \brief 设置符号可见
	virtual void SetSymbolVisible(UGbool bVisible);

	//! \brief 设置符号闪烁
	virtual void SetSymbolTwinkling(UGchar cTwinkling);

	//! \brief 设置符号对齐方式
	virtual void SetSymbolAlign(UGchar cAlign);

	//! \brief 设置符号偏移
	virtual void SetSymbolOffset(UGshort sX, UGshort sY);


//============================================================================================================
//=======================标签管理相关接口=====================================================================

 	//! \brief  向跟踪层添加对象的属性标签；----------------
 	virtual UGbool AddLabel(const UGString& strField, const UGTextStyle& LabelStyle,UGbool bVisible = true, UGbool bAddToTail = true);
	//! \brief  在跟踪层移除专题图；------------------------
	virtual UGbool RemoveLabel(const UGString& strField);

	//! \brief 设置标签偏移
	virtual UGbool SetLabelOffset(const UGString& strTag, UGshort usX, UGshort usY); 

	//! \brief 设置标签说明
	virtual UGbool SetLabelCaption(const UGString& strTag, const UGString& strCaption);

	//! \brief 设置标签的文字样式
	virtual UGbool SetLabelTextStyle(const UGString& strTag, const UGTextStyle& TextStyle);

	//! \brief  设置标签是否显示
	virtual UGbool SetLabelVisible(const UGString& strTag,UGbool bVisible);

	//! \brief  将指定标签上移一层；
 	virtual UGbool LabelMoveUp(const UGString &strTag);
	//! \brief  将指定标签下移一层；
	virtual UGbool LabelMoveDown(const UGString &strTag);
	//! \brief  将指定标签置为最顶层；
 	virtual UGbool LabelMoveTop(const UGString &strTag);
	//! \brief  将指定标签置为最底层；
	virtual UGbool LabelMoveBottom(const UGString &strTag);

	virtual void ClearLabel();
//===============================================================================================================
//=======================字段与对象管理相关接口==================================================================
	//! \brief  新建字段----------------------------------
	virtual UGbool CreateUserField(const UGString& strName,UGFieldInfo::FieldType nType,UGint nSize,UGint nAttributes = 0);
	virtual UGbool CreateUserFields(const UGFieldInfos& fieldInfos);
	//{{ add by xiaoys 2012-07-06
	virtual UGbool GetFieldInfos(UGFieldInfos& infos);

	virtual UGbool GetFieldInfo(UGFieldInfo& info, const UGString& strFieldName);

	virtual UGbool DeleteUserField(const UGString& strFieldName);

	//}} add by xiaoys 2012-07-06
	//! \brief  设置字段值-------------------------
	virtual UGbool SetFieldValue(const UGString& strFieldName,const UGVariant& var);

	virtual UGbool SetFieldValue(const UGString& strFieldName,const UGVariant& var,const UGint& iIndex); 
	
	//! /brief 获取字段值
	virtual UGbool GetFieldValue(UGVariant& var, UGint iIndex, const UGString& strField);

	//删除字段
//	UGbool DeleteUserField(const UGString& strName);

	//! \brief 获取对象第iIndex个属性字段名称--------------------------
	virtual UGString GetFieldName(UGint iIndex);

	//! \brief  增加一个带属性的标注对象；------------------------------
	virtual UGint AddFeature(UGGeometry *pGeometry, const UGArray<UGString> &aryFields, const UGArray<UGVariant *> &aryValues,const UGString& strTag);

	//! \brief 删除制定的标注对象；
//	virtual UGbool DeleteFeature(const UGint& iIndex);
private:
	//! \brief  获取标签绘制的顺序
	UGint GetLabelIndex(const UGString& strTag);

	//! \brief  创建内存数据集
	UGbool CreateMemDataset();

	//add by xiaoys 2012-06-29  添加一个求最长字串的接口用来模糊查询
	UGint GetMaxSub(const UGString& strSrc, const UGString& strDes);

	//add by xiaoys 2012-07-07 添加一个构建m_pRecordset的接口
	UGbool CreateRecordset();
 private:
    //! \brief  符号绘制风格
	UGSymbolLayout m_SymbolStyle;

	//! \brief  标签专题图风格管理 
	UGArray<UGLabelStyle> m_arLabelStyle;

};
}


#endif // !defined(AFX_UGTrackingLayerEx_H__E301D009_A2C1_4803_A434_C18A87419F38__INCLUDED_)
