//////////////////////////////////////////////////////////////////////////
//                    _   _   ____   ____                    
//   Project         | | | | / ___) / ___)                   
//                   | | | || | __ | |                       
//                   | |_| || |_\ || \___                    
//                    \____/ \____| \ ___)     6.0           
//                                                           
//!  \file UGGeoPlacemark.h
//!  \brief 三维地标对象。
//!  \author UGCTeam。
//!  \attention 
//!   Copyright (c) 1996-2010 SuperMap Software Co., Ltd. <br> 
//!   All Rights Reserved.
//!  \version 6.0
//////////////////////////////////////////////////////////////////////////

#if !defined(AFX_UGGEOPLACEMARK_H__265A401E_78C8_435F_BEBF_9AFF34F46EFE__INCLUDED_)
#define AFX_UGGEOPLACEMARK_H__265A401E_78C8_435F_BEBF_9AFF34F46EFE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "Geometry3D/UGGeometry3D.h"
#include "Base3D/UGStyle3D.h"
#include "Toolkit/UGTextStyle.h"

namespace UGC
{
 
//! \brief 三维地标对象。
class GEOMETRY3D_API UGGeoPlacemark : public UGGeometry3D
{
public:
	//! \brief 缺省构造函数
	UGGeoPlacemark();

	//! \brief 默认析构函数
	//! \remarks 内部调用Clear()完成。
	virtual ~UGGeoPlacemark();	

	//! \brief 清空地理数据
	virtual void Clear();
	
	//! \brief 得到几何对象类型。
	//! \return 固定为 GeoPlacemark。
	virtual UGGeometry::Type GetType() const;	

	//! \brief 得到维度。
	//! \return 固定为-1。
	//! \remarks UGGeoPlacemark本身的维数是-1，内部所封装的Geometry有维数。
	virtual UGint GetDimension() const;
	
	//! \brief 得到内点
	//! \return 返回内点，固定为点(0,0)
	virtual UGPoint2D GetInnerPoint() const;

	//! \brief 得到内点，可能是Geometry3D的质点
	//! \return 返回内点，固定为点(0,0,0)
	virtual UGPoint3D GetInnerPoint3D() const;
	
	//! \brief 得到空间数据, 主要用于需要按照维度相同时
	//! 来做统一处理的时候, 例如一些空间判断和操作的算法
	//! \param pPoints [out]。
	//! \param pPolyCount 传出的每个子对象点个数的数组[out]。
	//! \param nSubCount 传出的子对象个数[out]。
	//! \param nSegmentCount 对参数化对象, 每个弧段分割点的个数[in]。
	//! \remarks 参数采用了智能指针的技术,调用者不用释放内存空间
	//! \return 成功返回true,否则返回false。
	//! 此接口暂未实现
	virtual UGbool GetSpatialData(UGAutoPtr<UGPoint2D>& pPoints, 
		UGAutoPtr<UGint>& pPolyCount, UGint& nSubCount, UGint nSegmentCount=0) const;	

	//! \brief 根据已有几何对象的指针，拷贝构造一个三维地标对象。
	//! \param pGeometry [in] 已有几何对象指针。
	//! \return 构造成功返回true。
	//! \remarks 内部调用make方法去实现。
	virtual UGbool MakeWithGeometry(const UGGeometry* pGeometry);	

	//! \brief 几何对象是否有效
	//! \return 有效返回true,无效返回false
	virtual UGbool IsValid() const;
	
	//! \brief 点击测试, 用于对象点选
	//! \param pntHitTest 用来测试选中的点
	//! \param dTolerance 容限
	//! \return 选中返回true, 否则返回false
	//! \remarks 根据m_pGeometry类型，调用其HitTest()。
	virtual UGbool HitTest( const UGPoint2D &pntHitTest, UGdouble dTolerance) const;
	
	//! \brief 缩放
	//! \param dRatioX [in] X方向缩放比率。
	//! \param dRatioY [in] Y方向缩放比率。
	//! \remarks 暂未实现。
	virtual void Inflate( UGdouble dRatioX, UGdouble dRatioY);
	
	//! \brief 缩放
	//! \param dRatio [in] 缩放比率(X,Y方向相同)。
	//! \remarks 暂未实现。
	virtual void Inflate( UGdouble dRatio);
	
	//! \brief 平移。
	//! \param dX [in] 平移的X偏移量。
	//! \param dY [in] 平移的Y偏移量。
	//! \remarks 暂未实现。
	virtual void Offset( UGdouble dX, UGdouble dY);
	
	//! \brief 平移。
	//! \param dOffset [in] 偏移量(X,Y方向相同)。
	//! \remarks 暂未实现。
	virtual void Offset( UGdouble dOffset);
	
	//! \brief 平移
	//! \param szOffset [in] 平移的偏移量(分别用UGSize2D中的x,y代表X,Y方向的偏移量)。
	//! \remarks 暂未实现。
	virtual void Offset( const UGSize2D &szOffset);
	
	//! \brief 旋转
	//! \param pntOrigin [in] 旋转的中心点(锚点,不动点)。
	//! \param dAngle [in] 旋转角度。
	//! \remarks 暂未实现。
	virtual void Rotate( const UGPoint2D& pntOrigin, UGdouble dCosAngle, UGdouble dSinAngle,double dAngle = 0);
	
	//! \brief 调整几何数据,限定在新的Bounds中
	//! \param rcNewBounds [in] 新的,限定范围的Bounds
	//! \return 成功返回true,失败返回false
	//! \remarks 暂未实现。
	virtual UGbool Resize(const UGRect2D& rcNewBounds);
	
	//! \brief 只保存几何数据部分。
	//! \param stream [in] 存储流, 调用之前应该先Open。
	//! \param eCodecType [in] 存储的编码方式。
	//! \param FALSE [in] 是否存储为SDBPlus的格式。
	//! \return 成功返回true,失败返回false。
	//! \remarks 由于SDBPlus引擎和数据库引擎的存储上差别较大,所以必须直接调用该函数,并增加变量进行分别处理。
	//! 暂未实现。
	virtual UGbool SaveGeoData(UGStream& stream, 
		UGDataCodec::CodecType eCodecType,UGbool bSDBPlus = FALSE) const;
	
	//! \brief 只转载几何数据部分
	//! \param stream [in] 流 
	//! \param eCodecType [in] 编码方式
	//! \attention 还需要增加 UGbool bSDBPlus = FALSE 的参数
	//! \return 成功返回true,失败返回false	
	//! \remarks 暂未实现。
	virtual UGbool LoadGeoData( UGStream& stream , 
		UGDataCodec::CodecType eCodecType = UGDataCodec::encNONE,UGbool bSDBPlus = FALSE );
	
	//! \brief 将Geometry生成XML字符串
	//! \param versionType [in] GML的版本
	//! \param nPace [in] 缩进的空格数目,使得xml字符串更加易于人工阅读; 
	//! 主要用于如果返回的xml字符串是一个大标签中的一部分, 通过指定空格数目,可以使层次清晰
	//! \return 返回指定GML版本的xml字符串
	//! \remarks 暂未实现。
	virtual UGString ToXML(GMLVersionType versionType, UGint nPace = 0)  const;
	
	//! \brief 从XML字符串中生成Geometry
	//! \param strXML [in] xml格式字符串
	//! \param versionType [in] xml字符串的GML版本
	//! \return 返回指定GML版本的xml字符串
	//! \remarks 暂未实现。
	virtual UGbool FromXML(const UGString& strXML, GMLVersionType versionType);
	
	//! \brief 真正计算Bounds
	//! \return 返回固定为UGRect2D(0, 0, 0, 0)
	virtual UGRect2D ComputeBounds() const;	


	//! \brief 设置地标的内部几何对象。
	//! \param pGeo [in] 新的几何对象的指针。
	//! \attention 内部指针没有对pGeo进行拷贝，所以外面设置完不能释放，且不能是局部对象的地址。
	//! 释放由内部完成
	void SetGeometry(UGGeometry* pGeo);		
	
	//! \brief 获取非GeoPlacemark的Geometry。
	//! \return 非GeoPlacemark的Geometry。
	UGGeometry* GetInnestGeometry();
	
	//! \brief 获取地标的内部几何对象。
	//! \return 内部几何对象的指针。
	UGGeometry* GetGeometry();	

	//! \brief 设置地标的高亮风格。
	//! \param pStyle [in]。
	//! \remarks 内部对pStyle进行拷贝，外部可以释放pStyle。
	void SetHighLightStyle(const UGStyle3D* pStyle);	
	
	//! \brief 获取地标的高亮风格。
	//! \return 地标高亮风格的指针。
	UGStyle3D* GetHighLightStyle();	

	//! \brief 拷贝构造GeoPlacemark
	//! \param geoplacemark [in] 已有地标对象。
	//! \return 已有地标对象非法, 返回false。
	UGbool Make(const UGGeoPlacemark& geoplacemark);	
	
	//! \brief 设置地标的名字
	void SetName(UGString strName);
	
	//! \brief 获得地标的名字
	UGString GetName();
	
	//! \brief 设置内部几何对象的3D风格。
	//! \param pStyle3D [in]。
	//! \attention 若内部几何对象为非空or内部几何对象是3D类型则对pStyle3D进行拷贝，外部可以释放pStyle3D。
	virtual void SetStyle3D(const UGStyle3D* pStyle3D);	
	
	//! \brief 获取内部几何对象的3D风格。
	//! \return 内部几何对象风格的指针。
	//! \attention 若内部几何对象为空or内部几何对象非3D类型则返回null。
	virtual UGStyle3D* GetStyle3D() const;	
	
	//! \brief 设置内部几何对象的风格
	//! \param pStyle [in] 风格指针
	//! \remarks 如果pStyle==NULL,则Geometry内部风格指针被删除; 否则会复制一份风格
	//! 对于文本对象等, 设置风格不起作用,因为文本对象有自己的TextStyle
	virtual void SetStyle(const UGStyle* pStyle);

	//! \brief 得到风格对象的指针,如果没有返回NULL
	//! \return 返回风格的指针,有可能为NULL
	virtual UGStyle* GetStyle() const;
	
	
	//! \brief 设置有名字的地标的文本风格。
	//! \param textStyle [in] 文本风格。
	//! \remarks 当点具有文本进行显示时用这个作为要显示的文本的风格，其他都用geometry自己的文本风格。
	//! \attention 内部会对ptextStyle进行拷贝，外部设置完成后可以释放。
	void SetNameTextStyle(const UGTextStyle* ptextStyle);	
	
	//! \brief 得到风格指针,可能为NULL
	//! \return 若内部几何对象是GeoText或者GeoText3D类型则返回其文本风格，其他返回m_pTextStyle。
	UGTextStyle* GetNameTextStyle() const;	
	
	//! \brief 仅置内部几何对象为NULL，但并未delete
	void SetGeometryNull();

	//! \brief 设置对象的位置，这个函数只对模型和规则几何体意义，位置为模型等物体的底面中心点
	//! x,y为经纬度，z是指到球面的距离而不是到球心的距离
	//! \param value [in] 指定的位置点，含义见上。
	virtual void SetPosition(const UGPoint3D& value);	

	//! \brief 设置对象的缩放大小，这个函数只对模型和规则几何体意义
	//! \param fScaleX [in] X方向缩放比率。
	//! \param fScaleY [in] Y方向缩放比率。
	//! \param fScaleZ [in] Z方向缩放比率。
	virtual void SetScale(UGdouble fScaleX,UGdouble fScaleY,UGdouble fScaleZ);	

	//! \brief 设置对象的缩放大小，这个函数只对模型和规则几何体意义 
	//! \param fScaleXYZ [in] 物体在三个方向上进行同样大小的缩放 
	virtual void SetScale(UGdouble fScaleXYZ);

	//! \brief 设置对象的旋转量，这个函数只对模型和规则几何体意义 
	//! \param fRotateX [in] X方向的旋转角度。
	//! \param fRotateY [in] Y方向的旋转角度。
	//! \param fRotateZ [in] Z方向的旋转角度。
	virtual void SetRotation(UGdouble fRotateX,UGdouble fRotateY,UGdouble fRotateZ);	

	//! \brief 得到对象各方向的缩放比率，这个函数只对模型和规则几何体有意义
	//! \return 对象各方向的缩放比率。
	UGPoint3D GetScale() const;	

	//! \brief 得到对象的位置，这个函数只对模型和规则几何体意义，位置为模型等物体的底面中心点（点线面为物体的内点）
	//! \return 对象的位置。
	virtual UGPoint3D GetPosition() const;

	//! \brief 得到对象各方向的旋转角度，这个函数只对模型和规则几何体有意义
	//! \return 对象各方向的旋转角度。
	UGPoint3D GetRotation() const;

	//! \brief 获取数据存储时的大小
	//! \return 返回存储大小
	//! \remarks 暂未考虑编码情况，与SaveGeoData()一起维护
	//! \attention 字符串的长度要+4
	virtual UGint GetDataSize() const;

private:
	
	//! \brief GeoPlacemark封装的几何对象。
	//! \remarks 外面使用GeoPlacemark时必须要封装这个几何对象，包含了GeoPlacemark真正的几何数据。
	UGGeometry *m_pGeometry;
	
	//! \brief 地标的高亮风格。
	UGStyle3D m_highlightStyle;
	
	//! \brief 地标的名字。
	UGString m_strName;
	
	//! \brief 记录文本风格在点显示时可能用到。
	//! \remarks 当点具有文本进行显示时用这个作为要显示的文本的风格，其他都用geometry自己的文本风格。
	UGTextStyle* m_pTextStyle;
};

}
#endif // !defined(AFX_UGGEOPLACEMARK_H__265A401E_78C8_435F_BEBF_9AFF34F46EFE__INCLUDED_)


