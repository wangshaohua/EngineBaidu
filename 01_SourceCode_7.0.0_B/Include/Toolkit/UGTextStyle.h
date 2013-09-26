
/*!
   **************************************************************************************
    \file     UGTextStyle.h
   **************************************************************************************
    \author   陈国雄
    \brief    文本风格类                                                             
    \attention   
   ----------------------------------------------------------------------------------<br>
    Copyright (c) 2000-2010 SuperMap Software Co., Ltd.                           <br>
    All Rights Reserved.                                                             <br>
   ----------------------------------------------------------------------------------<br> 
   
   **************************************************************************************
    \version 2005-07-06  陈国雄    初始化版本.                                       <br>
   **************************************************************************************
*/

#ifndef UGTEXTSTYLE_H
#define UGTEXTSTYLE_H

#include "Stream/ugdefs.h"

namespace UGC {

//! \brief 文本风格类
class TOOLKIT_API UGTextStyle  
{
public:
	//! \brief
	UGTextStyle();
	//! \brief
	UGTextStyle(const UGTextStyle& textStyle);
	//! \brief
	~UGTextStyle();

	//! \brief
	UGTextStyle& operator=(const UGTextStyle& textStyle);
	//! \brief
	UGbool operator==(const UGTextStyle& textStyle) const;
	//! \brief
	UGbool operator!=(const UGTextStyle& textStyle) const;

public:
	//! \brief
	UGbool FromOgdcTextStyle(const OgdcTextStyle& ogdcTextStyle);
	//! \brief
	UGbool ToOgdcTextStyle(OgdcTextStyle& ogdcTextStyle) const;
	
	  //!  \brief Toolkit
	//! \brief  得到字体颜色
	UGColor GetForeColor() const;	
	  //!  \brief Toolkit
	//! \brief  设置字体颜色
	void SetForeColor(UGColor foreColor);	
	  //!  \brief Toolkit
	//! \brief  背景色，阴影色，外框色
	UGColor	GetBackColor() const;
	
	  //!  \brief Toolkit
	//! \brief  设置背景色,同时也是阴影色，外框色
	void SetBackColor(UGColor backColor);	
	  //!  \brief Toolkit
	//! \brief  得到旋转角度，以度为单位，逆时针方向
	UGdouble GetAngle() const;	
	  //!  \brief Toolkit
		//! \brief  设置旋转角度，以度为单位，逆时针方向
	void SetAngle(UGdouble dAngle);
	  //!  \brief Toolkit
		//! \brief  得到字体宽度，地理单位
	UGdouble GetWidth() const;
	  //!  \brief Toolkit
	//! \brief  设置字体宽度，地理单位
	void SetWidth(UGdouble dWidth);
  //! \brief Toolkit
  //! \brief  得到字体高度，地理单位
	UGdouble GetHeight() const;	
	  //!  \brief Toolkit
	//! \brief  设置字体高度，地理单位
	void SetHeight(UGdouble dHeight);
	// added by lidl 2008-9-10 16:43:20
	  //!  \brief Toolkit
	//! \brief  得到字号,单位：磅 
	UGdouble GetSize() const;
	  //!  \brief Toolkit
	//! \brief  设置字号，单位：磅
	void SetSize(UGdouble dSize);	
	//!  \brief Toolkit
	//! \brief 得到字体名称	
	UGString GetFaceName() const;
	 //!  \brief Toolkit
     //! \brief  设置字体名称
	void SetFaceName(const UGString& strFaceName);
	//!  \brief Toolkit
	//! \brief  得到所有风格信息:粗体，斜体，透明，黑体,排列等
	UGint GetStyle() const;			
	//!  \brief Toolkit
	//! \brief 设置所有的风格，高级用户使用!
	void SetStyle(UGint nStyle);	
	//! \brief Toolkit
	//! \brief  是否粗体
	UGbool IsBold() const;	
	//!  \brief Toolkit
	//! \brief  设置是否粗体
	void SetBold(UGbool bBold = true);				
	//!  \brief Toolkit
	//! \brief  是否下划线
	UGbool IsUnderline() const;
	//!  \brief Toolkit
	//! \brief  设置是否下划线
	void SetUnderline(UGbool bUnderline = true);		
	  //!  \brief Toolkit
	//! \brief  是否斜体
	UGbool IsItalic() const;	
	//!  \brief Toolkit
	//! \brief  设置是否斜体
	void SetItalic(UGbool bItalic = true);			
	//!  \brief Toolkit
	//! \brief  是否删除线
	UGbool IsStrikeOut() const;		
	//! \brief Toolkit
	//! \brief 设置是否删除线
	void SetStrikeOut(UGbool bStrikeOut = true);
	//!  \brief Toolkit
	//! \brief  得到对齐方式
	UGbyte GetAlign() const;				
	//!  \brief Toolkit
	//! \brief  设置对齐方式
	void SetAlign(UGbyte nAlign = 0);				
	  //!  \brief Toolkit
	//! \brief  得到文本的笔划宽度
	UGint GetWeight() const;					
	  //!  \brief Toolkit
	//! \brief  设置文本的笔划宽度
	void SetWeight(UGint nWeight);	
	  //!  \brief Toolkit
	//! \brief  是否固定大小
	UGbool IsFixedSize() const;			
	//!  \brief Toolkit
	//! \brief 固定大小，字体不随地图的缩放而缩放
	void SetFixedSize(UGbool bFixedSize=true);			
	//!  \brief Toolkit
	//! \brief  固定大小的尺寸，mm单位
	UGdouble GetSizeForFixed() const;			
	  //!  \brief Toolkit
	//! \brief 设置固定大小的尺寸，mm单位
	void SetSizeForFixed(UGdouble dSize);		

	  //!  \brief Toolkit
	//!  \brief 是否背景不透明, 注意了,true表示不透明!!
	UGbool IsBackOpaque() const;				
	  //!  \brief Toolkit
	//! \brief  设置是否背景不透明
	void SetBackOpaque(UGbool bBackOpaque = false);				
	  //!  \brief Toolkit
	//! \brief 是否显示外框
	UGbool IsHalo() const;			
	  //!  \brief Toolkit
	//! \brief  设置是否显示外框
	void SetHalo(UGbool bHalo = true);		
	

	//{{added by mahb at 20120716
	//! \brief  设置背景的透明度
	//! \params ucTransparency 透明度，0~255；0为透明，255为不透明
	void SetBackTransparency(UGuchar ucTransparency);

	//! \brief  获取背景的透明度
	UGuchar GetBackTransparency() const;
	//}}
	
	  //!  \brief Toolkit
	//! \brief  是否显示阴影
	UGbool IsShadow() const;	
	
	  //!  \brief Toolkit
	//! \brief  设置是否显示阴影
	void SetShadow(UGbool bShadow = true);			
	
	//! \brief
	  //!  \brief Toolkit
	  //!  \brief Toolkit
	UGbool FromXML(const UGString& strXML, UGint nVersion = 0);
	//! \brief
	  //!  \brief Toolkit
	UGString ToXML(UGint nVersion = 0) const;

	
	  //!  \brief Toolkit
	//! \brief 获取文本风格对象的hashcode
	UGint GetHashCode() const;

	//! \brief 获取/设置耸肩效果,正负60度之间，目前只对标签专题图有效，传入的是度为单位
	UGdouble GetItalicAngle() const;
	  //!  \brief Toolkit
	void SetItalicAngle(UGdouble nItalicAngle);
	  //!  \brief Toolkit

	//! \brief  得到3D文本的透明度
	//! \remarks 该参数仅在三维中使用，支持保存为XMLUGC信息,SFC版本不保存，数据库中不保存此信息，默认为100,不透明,OGDC中不保存此风格
	UGint GetText3DOpaque() const;		
	//! \brief 设置3D文本的不透明度
	void SetText3DOpaque(UGint nOpaque);
	
	//! \brief 得到3D文本的缩放比例
	//! \remarks 该参数仅在三维中临时使用，不保存，OGDC中不保存此风格
	UGdouble  GetText3DScale() const;		
	//! \brief 设置文本的缩放比例
	void SetText3DScale(UGdouble dScale);	
	
private:
	UGColor		m_ForeColor;			//! 字体颜色
	UGColor		m_BackColor;			//! 背景色，阴影色，外框色
	UGint		m_nAngle;				//! 旋转角度，以0.1度为单位,x坐标正方向为起始，逆时针方向
	UGint		m_nItalicAngle;			//! 旋转角度，以0.1度为单位,x坐标正方向为起始，逆时针方向
	UGdouble	m_dWidth;				//! 字体宽度，地理单位
	UGdouble	m_dHeight;				//! 字体高度，地理单位
	UGString	m_strFaceName;			//! 字体名字
	UGint		m_nStyle;				//! 风格:粗体，斜体，透明，黑体,排列等	
	UGbyte      m_nText3DOpaque;
	UGdouble    m_dText3DScale;
	//UGdouble    m_dSize;				//! 字体字号

	//{{ added by mahb at 20120716
	UGuchar     m_ucBackTransparency;   //! 背景透明度
};

}

#endif

