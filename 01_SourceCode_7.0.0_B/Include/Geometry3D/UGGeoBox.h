// UGGeoBox.h: interface for the UGGeoBox class.
//
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//                    _   _   ____   ____                    
//   Project         | | | | / ___) / ___)                   
//                   | | | || | __ | |                       
//                   | |_| || |_\ || \___                    
//                    \____/ \____| \ ___)     6.0           
//                                                           
//!  \file UGGeoBox.h
//!  \brief 长方体几何体。
//!  \details 文件详细信息。
//!  \author 冯振华。
//!  \attention 
//!   Copyright (c) 1996-2010 SuperMap Software Co., Ltd. <br> 
//!   All Rights Reserved.
//!  \version 6.0
//////////////////////////////////////////////////////////////////////////

#if !defined(AFX_UGGEOBOX_H__097BFB31_623A_4A31_876C_B1E27E946A98__INCLUDED_)
#define AFX_UGGEOBOX_H__097BFB31_623A_4A31_876C_B1E27E946A98__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Geometry3D/UGGeometry3D.h"

namespace UGC
{
class GEOMETRY3D_API UGGeoBox : public UGGeometry3D  
{
public:
	//! \brief 构造函数。
	UGGeoBox();

	//! \brief 析构函数
	virtual ~UGGeoBox();
public: //pure virtual 

	//! \brief 清空地理数据
	virtual void Clear();

	//! \brief 得到维度, 点为0维, 线/曲线等为1维, 面/曲面等为2维, GeoCompound/GeoText等为-1，在数据库存储时用
	virtual UGint GetDimension() const;

	//! \brief 得到类型, 固定为GeoCircle
	virtual Type GetType() const;

	//! \brief 得到内点（在Geometry内部，靠近中央的点）, 即为圆心。
	//! \return 内点。
	virtual UGPoint2D GetInnerPoint() const;
	
	//! \brief 得到对象长度。
	//! \attention Dimension为1的对象才支持。
	//! \return 返回长度。
	virtual UGdouble GetLength() const;

	//! \brief 得到对象面积。
	//! \return 返回面积。
	virtual UGdouble GetArea() const;

	//! \brief 得到对象面积。
	//! \return 返回面积。
	virtual UGdouble GetArea3D() const;

	//! \brief 点击测试, 用于对象点选。
	//! \param &pntHitTest 用来测试选中的点[in]。
	//! \param dTolerance 容限[in]。
	//! \return 选中返回true, 否则返回false。
	virtual UGbool HitTest( const UGPoint2D &pntHitTest, UGdouble dTolerance) const;	
	
	//! \brief 缩放
	//! \param dRatioX X方向缩放比率[in]。
	//! \param dRatioY Y方向缩放比率[in]。
	//! \attention 正圆无法在两个不同方向缩放, 因此dRatioX和dRatioY必须相等才行
	virtual void Inflate( UGdouble dRatioX, UGdouble dRatioY);
	
	//! \brief 缩放
	//! \param dRatio 缩放比率(X,Y方向相同)[in]。
	virtual void Inflate( UGdouble dRatio);

	//! \brief 缩放
	//! \param dRatioX X方向缩放比率
	//! \param dRatioY Y方向缩放比率
	//! \param dRatioY Z方向缩放比率
	//! \remarks M无缩放
	virtual void Inflate3D( UGdouble dRatioX, UGdouble dRatioY, UGdouble dRatioZ);
	
	//! \brief 缩放
	//! \param dRatio 缩放比率(X,Y,Z相同)
	virtual void Inflate3D( UGdouble dRatio);
	
	//! \brief 平移
	//! \param dX 平移的X偏移量[in]。
	//! \param dY 平移的Y偏移量[in]。
	virtual void Offset( UGdouble dX, UGdouble dY);
	
	//! \brief 平移
	//! \param 偏移量(X,Y方向相同)[in]。
	virtual void Offset( UGdouble dOffset);
	
	//! \brief 平移
	//! \param 平移的偏移量(分别用UGSize2D中的x,y代表X,Y方向的偏移量)[in]。
	virtual void Offset( const UGSize2D &szOffset);
	

//! \brief 三维对象平移
	//! \param dX [in] 平移的X偏移量
	//! \param dY [in] 平移的Y偏移量	
	//! \param dZ [in] 平移的Z偏移量	
	virtual void Offset3D( UGdouble dX, UGdouble dY, UGdouble dZ);
	
	//! \brief 三维对象平移
	//! \param dOffset [in] 偏移量(X,Y,Z方向相同)	
	virtual void Offset3D( UGdouble dOffset);
	
	//! \brief 三维对象平移
	//! \param vecOffset [in] 平移的偏移量(分别用UGVector3d中的x,y,z代表X,Y,Z方向的偏移量)。
	virtual void Offset3D( const UGVector3d &vecOffset);

	//! \brief 旋转
	//! \param pntOrigin 旋转的中心点(锚点,不动点)[in]。
	//! \param dAngle 旋转角度[in]。
	virtual void Rotate(const UGPoint2D& pntOrigin, UGdouble dAngle);
	
	//! \brief 旋转,增加一些参数,以便内部可以不用进行cos,sin, 在批量处理的时候有利于提高效率
	//! \remarks dAngle看似多余,但GeoText需要,所以要保留
	//! \param pntOrigin 旋转的中心点(锚点,不动点)[in]。
	//! \param dCosAngle 旋转的cos值[in]。
	//! \param dSinAngle 旋转的sin值[in]。
	//! \param dAngle 旋转角度[in]。
	virtual void Rotate(const UGPoint2D& pntOrigin, UGdouble dCos, UGdouble dSin, UGdouble dAngle);

	//! \brief 三维对象旋转
	//! \param vecAxis [in] 旋转轴 过原点
	//! \param dAngle [in] 旋转角度
	virtual void Rotate3D(const UGVector3d& vecAxis, UGdouble dAngle);
		
	//! \brief 生成XML格式的信息
	//! \param versionType GML的版本[in]。
	//! \param nPace 缩进的空格数目,使得xml字符串更加易于人工阅读[in]。
	//! 主要用于如果返回的xml字符串是一个大标签中的一部分, 通过指定空格数目,可以使层次清晰
	//! \return 返回指定GML版本的xml字符串
	virtual UGString ToXML(GMLVersionType versionType, UGint nPace = 0) const;

	//! \brief 从XML字符串中生成Geometry
	//! \param strXML xml格式字符串[in]。
	//! \param versionType xml字符串的GML版本[in]。
	//! \return 返回指定GML版本的xml字符串
	virtual UGbool FromXML(const UGString& strXML, GMLVersionType versionType);

	//! \brief 得到空间数据, 主要用于需要按照维度相同时
	//! 来做统一处理的时候, 例如一些空间判断和操作的算法
	//! \param pPoints 传出的点坐标数组[out]。
	//! \param pPolyCount 传出的每个子对象点个数的数组[out]。
	//! \param nSubCount 传出的子对象个数[out]。
	//! \param nSegmentCount 对参数化对象, 每个弧段分割点的个数[in]。
	//! \remarks 参数采用了智能指针的技术,调用者不用释放内存空间
	//! \return 成功返回true,否则返回false。
	virtual UGbool GetSpatialData(UGAutoPtr<UGPoint2D>& pPoints, 
				UGAutoPtr<UGint>& pPolyCount, UGint& nSubCount, UGint nSegmentCount=0) const;

	//! \brief 几何对象是否有效
	//! \return 有效返回true,无效返回false
	virtual UGbool IsValid()const;
	
	//! \brief 两点镜像
	//! \param pntMirror1 构成镜面的第一个点
	//! \param pntMirror2 构成镜面的第二个点
	//! \return 成功返回true,失败返回false
	virtual UGbool Mirror(const UGPoint2D &pntMirror1, const UGPoint2D &pntMirror2);

	//! \brief 根据geometry类型，再调用各自的make方法去实现。
	//! \param pGeometry [in]。
	//! \return 。
	//! \remarks 。
	//! \attention 构造成功返回true。
	virtual UGbool MakeWithGeometry(const UGGeometry* pGeometry);	

	//! \brief 调整几何数据,限定在新的Bounds中
	//! \param rcNewBounds 新的,限定范围的Bounds
	//! \return 成功返回true,失败返回false
	virtual UGbool Resize(const UGRect2D& rcNewBounds); 

	//! \brief 获取数据存储时的大小
	//! \return 返回存储大小
	//! \remarks 暂未考虑编码情况，与SaveGeoData()一起维护
	//! \attention 字符串的长度要+4
	virtual UGint GetDataSize() const;

public:
#if !defined (IOS3D)
	//! \brief Geometry与Element的转换
	//! \param pElement,返回的pElement指针在函数内分配内存,外面负责删除，否则会有内存泄漏
	virtual UGbool ToElement(OgdcElement*& pElement)  const;
	
	//! \brief Geometry与Element的转换
	//! \param pElement,传入的Element，如果无法转换则返回False，否则返回True
	virtual UGbool FromElement(const OgdcElement* pElement);
#endif
public:
	//! \brief 转化为线对象
	//! \param geoLine[out] 得到的线对象
	//! \param nSegmentCount 当曲线转化为线时,每一段用多少个点来模拟
	//! \return 成功返回true,失败返回false
	virtual UGbool ConvertToLine( UGGeoLine &geoLine, UGint nSegmentCount = 0 ) const;
	
	//! \brief 转化为面对象
	//! \param geoRegion[out] 得到的面对象
	//! \param nSegmentCount 当曲面转化为面时,每一段用多少个点来模拟
	//! \return 成功返回true,失败返回false
	virtual UGbool ConvertToRegion( UGGeoRegion &geoRegion, UGint nSegmentCount = 0 ) const;

public:	
	//! \brief 根据投影转化器的设置和转化方向要求, 进行投影转化
	//! \param pPJTranslator 投影转化器
	//! \param bForward 转化方向, true代表从UGRefTranslator的源(Src)转化到目的(Des), false则相反
	virtual void PJConvert( UGRefTranslator *pPJTranslator, UGbool bForward = true);

	//! \brief 进行三维投影坐标系统转化
	//! \attention 暂未实现。
	virtual void PJConvert3D( UGRefTranslator *pPJTranslator, UGbool bForward = true);

	//! \brief 从经纬坐标系统转化为投影坐标系统
	//! \param pCoordSys 投影坐标系统
	virtual void PJForward( UGPrjCoordSys *pCoordSys );

	//! \brief 从投影坐标系统转化为经纬坐标
	//! \param pCoordSys 投影坐标系统
	virtual void PJInverse( UGPrjCoordSys *pCoordSys );

	
	//! \brief 从经纬坐标系统转化为三维投影坐标系统
	//! \param pCoordSys 投影坐标系统
	virtual void PJForward3D( UGPrjCoordSys *pCoordSys );
	
	//! \brief 从投影坐标系统转化为经纬坐标系
	//! \param pCoordSys 投影坐标系统
	virtual void PJInverse3D( UGPrjCoordSys *pCoordSys );
	

public:
	//! \brief 三角划分构建成几何模型，并归一化。
	//! \param nStacks [in] 横向分几份。
	//! \param nSlices [in] 竖向分几段。
	//! \return 几何模型指针。
	//! \remarks 。
	//! \attention 。
	UGGeoModel* GetModel(UGint nStacks, UGint nSlices);	

	//! \brief 得到模型体积。
	virtual UGdouble GetVolume();

	//! \brief 得到三维几何对象的内点
	virtual UGPoint3D GetInnerPoint3D() const;
	
	//! \brief 拷贝复制对象
	//! \param geoCircle 已有对象
	//! \return 已有对象非法, 返回false
	UGbool Make(const UGGeoBox& geoBox);

	//! \brief 通过圆心和半径来构造圆。
	//! \param pntCenter [in] 圆心。
	//! \param dRadius [in] 半径。
	//! \return 半径小于0, 返回false。
	UGbool Make(const UGPoint3D &pntCenter, const UGSize2D &szSize, UGdouble dBoxLength, UGdouble dAngle);    

	//! \brief 三点共圆的方式构圆。
	//! \param pnt1 [in] 第一个点。
	//! \param pnt2 [in] 第二个点。
	//! \param pnt3 [in] 第三个点。
	//! \return 三个点在同一条直线上, 返回false。
//	UGbool Make(const UGPoint2D& pnt1, const UGPoint2D& pnt2, const UGPoint2D& pnt3);    

	//! \brief 两点(直径上的两点)构圆。
	//! \param pnt1 [in] 第一个点。
	//! \param pnt2 [in] 第二个点。
	//! \return 返回true。
//	UGbool Make(const UGPoint2D& pnt1, const UGPoint2D& pnt2);    

	//! \brief 得到圆心。
	//! \return 返回圆心。
	UGPoint3D GetCenterPoint();    

	//! \brief 获得宽度(x)。
	//! \return 宽度(x)。
	UGdouble GetBoxHeight() const;	

	//! \brief 设置宽度(x)。
	//! \param dHeight 宽度(x)[in]。
	//! \return 是否合法。
	UGbool SetBoxHeight( UGdouble dHeight );
	
	//! \brief 获得高度(y)。
	//! \return 高度(y)。
	UGdouble GetBoxWidth() const;	

	//! \brief 设置高度(y)。
	//! \param dWidth 高度(y)[in]。
	//! \return 是否合法。
	UGbool SetBoxWidth( UGdouble dWidth );	

	//! \brief 获得长度(z)。
	//! \return 长度(z)。
	UGdouble GetBoxLength(void) const;
	
	//! \brief 设置长度(z)。
	//! \param dLength 长度(z)[in]。
	//! \return 是否合法。
	UGbool SetBoxLength( UGdouble dLength );	


public:

	//! \brief 获得编辑对象的句柄的数目
	//! \remarks 对于固定句柄对象为9包括了改变大小的8个控制点和一个旋转控制点
     virtual UGint  GetHandleCount();

	//! \brief 根据句柄获得相应控制点的值
	//! \param nHandle 控制点句柄
	//! \param point 句柄对应的控制点的坐标值
	//! \return 返回辅助点的类型
	 virtual UGint GetHandle( UGint nHandle, UGPoint2D& point);

	//! \brief 移动控制点到指定坐标,主要用于绘制对象，修改对象节点等操作
	//! \param nHandle 控制点句柄
	//! \param point 控制点坐标
	virtual void MoveHandle( UGint nHandle, const UGPoint2D& pnt2D,UGEditType::EditToolShape nEditType=UGEditType::ET_Default);

	//! \brief 节点编辑时可用来插入一个控制点,也可以用于绘制对象时加入节点
	//! \param nHandle 插入位置
	//! \param pnt2D 插入点的地理坐标
	virtual void AddHandle( UGint nHandle, const UGPoint2D& pnt2D,UGEditType::EditToolShape nEditType=UGEditType::ET_Default);
	
	//! \brief 删除编辑对象的指定节点
	//! \param nHandle 节点句柄
    virtual UGuint DelNode( UGint nHandle );
protected:

	//! \brief 计算Bounds。
	//! \return Bounds。
	virtual UGRect2D ComputeBounds() const;	

	//! \brief 只保存几何数据部分。
	//! \param stream 存储流, 调用之前应该先Open[in]。
	//! \param eCodecType 存储的编码方式[in]。
	//! \param bSDBPlus 是否存储为SDBPlus的格式[in]。
	//! \return 成功返回true,失败返回false。
	//! \remarks 由于SDBPlus引擎和数据库引擎的存储上差别较大,所以必须直接调用该函数,
	//! 并增加变量进行分别处理
	virtual UGbool SaveGeoData(UGStream& stream, UGDataCodec::CodecType eCodecType,UGbool bSDBPlus = FALSE) const	;

	//! \brief 只转载几何数据部分。
	//! \param stream 流[in]。
	//! \param eCodecType 编码方式[in]。
	//! \param bSDBPlus 是否存储为SDBPlus的格式[in] [in]。
	//! \return 成功返回true,失败返回false。
	virtual UGbool LoadGeoData( UGStream& stream , UGDataCodec::CodecType eCodecType = UGDataCodec::encNONE ,UGbool bSDBPlus = FALSE);	

	//! \brief 获得顶点串。
	//! \param pPoints 点串[out]。
	void GetVertexes(UGPoint2D* pPoints) const;	

	//!\brief 得到Boundingbox
	virtual UGBoundingBox ComputeBoundingBox() const;

private:

	//! \brief 宽度(x)。
	UGdouble m_dBoxWidth;   
	
	//! \brief 高度(y)。
	UGdouble m_dBoxHeight;  
	
	//! \brief 长度(z)。
	UGdouble m_dBoxLength;  

	//! \brief 翻转角度。
	UGdouble m_dAngle;
};
}
#endif // !defined(AFX_UGGEOBOX_H__097BFB31_623A_4A31_876C_B1E27E946A98__INCLUDED_)

