// UGStyle3D.h: interface for the UGStyle3D class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_UGTEXTSTYLE3D_H__7978B585_8964_4C91_99FE_FDE3F6A104BD__INCLUDED_)
#define AFX_UGTEXTSTYLE3D_H__7978B585_8964_4C91_99FE_FDE3F6A104BD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "Base3D/UGPrerequisites3D.h"
#include "Base3D/UGColorValue3D.h"
#include "Base3D/UGTextureData.h"
#include "Stream/UGStream.h"

//3d文字的类型
namespace UGC
{

class BASE3D_API UGTextStyle3D  
{
public:
	UGTextStyle3D();
	UGTextStyle3D(const UGTextStyle3D& textStyle);
	virtual ~UGTextStyle3D();
	
	void operator=(const UGTextStyle3D& textStyle);
	UGbool operator==(const UGTextStyle3D& textStyle) const;
	UGbool operator!=(const UGTextStyle3D& textStyle) const;
	
	//! \brief 存储到Stream中
	UGbool SaveToStream(UGStream& stream, UGuint nVersion = 0) const;
	
	//! \brief 从Stream中生成
	UGbool LoadFromStream( UGStream& stream , UGuint nVersion = 0);

	//! \brief 得到对齐方式
	UGbyte GetAlign() const;				
	//! \brief 设置对齐方式
	void SetAlign(UGbyte nAlign = 0);	
	
	//! \brief 得到字体宽度，
	UGdouble GetWidth() const;
	//! \brief 设置字体宽度，
	void SetWidth(UGdouble dWidth);
	
	//! \brief 得到字体高度，
	UGdouble GetHeight() const;
	//! \brief 设置字体高度，
	void SetHeight(UGdouble dHeight);
	//! \brief 得到字体名称		
	UGString GetFaceName() const;
	//! \brief 设置字体名称
	void SetFaceName(const UGString& strFaceName);

public:	
	//! \brief 字体填充色
	UGColorValue3D m_ColorFill;
	//! \brief 缩放比例
	UGdouble m_dScale;

// 目前没有用上
private:	
	UGdouble			m_dWidth;				//! 字体宽度，地理单位
	UGdouble			m_dHeight;				//! 字体高度，地理单位
	UGint				m_nStyle;				//! 风格:粗体，斜体，透明，黑体,排列等	
	UGColorValue3D		m_ForeColor;			//! 字体颜色
	UGColorValue3D		m_BackColor;			//! 背景色，阴影色，外框色
	UGString			m_strFaceName;			//! 字体名字


};

}

#endif // !defined(AFX_UGTEXTSTYLE3D_H__7978B585_8964_4C91_99FE_FDE3F6A104BD__INCLUDED_)

