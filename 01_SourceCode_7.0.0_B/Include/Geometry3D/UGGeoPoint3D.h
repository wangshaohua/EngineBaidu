//////////////////////////////////////////////////////////////////////////
//                    _   _   ____   ____                    
//   Project         | | | | / ___) / ___)                   
//                   | | | || | __ | |                       
//                   | |_| || |_\ || \___                    
//                    \____/ \____| \ ___)     6.0           
//                                                           
//!  \file UGGeoPoint3D.h
//!  \brief 三维点几何对象。
//!  \author UGCTeam。
//!  \attention 
//!   Copyright (c) 1996-2010 SuperMap Software Co., Ltd. <br> 
//!   All Rights Reserved.
//!  \version 6.0
//////////////////////////////////////////////////////////////////////////

#ifndef UGGEOPOINT3D_H
#define UGGEOPOINT3D_H

#include "Geometry3D/UGGeometry3D.h"

namespace UGC
{
//! \brief 三维点几何对象。	
class GEOMETRY3D_API UGGeoPoint3D : public UGGeometry3D
{
public:
	//! \brief 缺省构造函数
	UGGeoPoint3D();	
	//! \brief 默认析构函数
	~UGGeoPoint3D(void);

public:

	//! \brief 清除Geometry内部数据
	virtual void Clear();
	
	//! \brief 得到维度, 点为0维, 线/曲线等为1维, 面/曲面等为2维, GeoCompound/GeoText等为-1
	virtual UGint GetDimension() const;
	
	//! \brief 得到内点（在Geometry内部，靠近中央的点）
	//! \return 返回内点
	//! \remarks 为点数最多的子对象 的中间点(中间个数的点, 而不是中间距离的点)
	virtual UGPoint2D GetInnerPoint() const;

	//! \brief 得到对象面积
	//! \return 返回面积
	virtual UGdouble GetArea() const;
	
	//! \brief 得到对象面积
	//! \return 返回面积
	virtual UGdouble GetArea3D() const;

	
	//! \brief 得到内点（可能是Geometry3D的质点）
	//! \return 返回内点
	virtual UGPoint3D GetInnerPoint3D() const;
	
	//! \brief 得到几何对象类型。
	//! \return 固定为 GeoPoint3D。
	virtual UGGeometry::Type GetType() const;

	//! \brief 点击测试, 用于对象点选
	//! \param pntHitTest [in] 用来测试选中的点
	//! \param dTolerance [in] 容限
	//! \return 选中返回true, 否则返回false
	virtual UGbool HitTest( const UGPoint2D &pntHitTest, UGdouble dTolerance) const;
	
	//! \brief 几何对象是否有效
	//! \return 有效返回true,无效返回false
	virtual UGbool IsValid() const;
	
	//! \brief 根据已有几何对象的指针，拷贝构造一个三维点几何对象。
	//! \param pGeometry [in] 已有几何对象指针。
	//! \return 构造成功返回true。
	//! \remarks 内部调用make方法去实现。
	virtual UGbool MakeWithGeometry(const UGGeometry* pGeometry);	

	//! \brief 根据三维点串构造一个三维点几何对象
	//! \param pPoints [in] 点串指针。
	//! \param nPntCount [in] 点的个数。
	//! \param UGEditType3D::ET3D_NULL [in] 编辑工具形状（可选）。
	//! \return 构造成功返回true。
	//! \remarks 内部调用make方法去实现，用于在编辑中多态构造对象。
	virtual UGbool MakeWithPoints3D(UGPoint3D* pPoints,UGint nPntCount,
		UGEditType3D::EditToolShape3D nEditType = UGEditType3D::ET3D_NULL);	

	// added by hp/2011-2-17 
	//! \brief 根据传入的点串生成对象，主要用于编辑中的参数化等没有内部数组保存点串的对象，
	//! 也用于自定义对象,对于有内部数组保存点串的对象，该函数直接return既可，
	//! 比如GeoLine等对象就直接用AddHandle来生成，效率比较高 
	//! \param pPoints 3维点串
	//! \param nPntCount  点的个数
	virtual void MakeWithPoints(UGPoint3D* pPoints,UGint nPntCount,
		UGEditType::EditToolShape nEditType=UGEditType::ET_Default);	

	//! \brief 获取数据存储时的大小
	//! \return 返回存储大小
	//! \remarks 暂未考虑编码情况，与SaveGeoData()一起维护
	//! \attention 字符串的长度要+4
	virtual UGint GetDataSize() const;
public:
   	//! \brief 生成XML格式的信息
	//! \param versionType GML的版本
	//! \param nPace 缩进的空格数目,使得xml字符串更加易于人工阅读; 
	//! 主要用于如果返回的xml字符串是一个大标签中的一部分, 通过指定空格数目,可以使层次清晰
	//! \return 返回指定GML版本的xml字符串
	virtual UGString ToXML(GMLVersionType versionType, UGint nPace = 0) const;
	
	//! \brief 从XML字符串中生成Geometry
	//! \param strXML xml格式字符串
	//! \param versionType xml字符串的GML版本
	//! \return 返回指定GML版本的xml字符串
	virtual UGbool FromXML(const UGString& strXML, GMLVersionType versionType = SML);
	
	// 只留出来接口，将来可能实现

	//! \brief 转化为线对象
	//! \param geoLine[out] 得到的线对象
	//! \param nSegmentCount [in] 当曲线转化为线时,每一段用多少个点来模拟
	//! \return 成功返回true,失败返回false
	virtual UGbool ConvertToLine( UGGeoLine &geoLine, UGint nSegmentCount = 0 ) const;
	
	//! \brief 转化为面对象
	//! \param geoRegion[out] 得到的面对象
	//! \param nSegmentCount [in] 当曲面转化为面时,每一段用多少个点来模拟
	//! \return 成功返回true,失败返回false
	virtual UGbool ConvertToRegion( UGGeoRegion &geoRegion, UGint nSegmentCount = 0 ) const;
	
	//! \brief 转换成多点对象，可以把3D点、3D多点对象转换成多点对象显示。
	//! \param geoMultiPoint [out] 输出多点几何对象。
	virtual UGbool ConvertToPoint( UGGeoMultiPoint &geoMultiPoint) const;	
	
	//! \brief 转换成图片，3D类型几何对象，以及用户类型几何对象可以通过先转换成图片，再显示。
	//! \param geoPicture [out] 输出图片几何对象。
	//! \param dResolution [in] 分辨率。
	//! \param dXAngle [in] 水平倾角。
	//! \param dZAngle [in] 旋转倾角。
	//! \return 成功返回true,失败返回false
	virtual UGbool ConvertToPicture( UGGeoPicture &geoPicture, UGdouble dResolution, 
								UGdouble dXAngle = 0, UGdouble dZAngle = 0) const;	

	//Projection..
	
	//! \brief 根据投影转化器的设置和转化方向要求, 进行投影转化
	//! \param pPJTranslator [in] 投影转化器
	//! \param bForward [in] 转化方向, true代表从UGRefTranslator的源(Src)转化到目的(Des), false则相反
	//! \remarks 转成2维的Geometry后，调用它的方法实现
	virtual void PJConvert( UGRefTranslator *pPJTranslator, UGbool bForward = true);

	//! \brief 进行三维投影坐标系统转化
	//! \attention 暂未实现。
	virtual void PJConvert3D( UGRefTranslator *pPJTranslator, UGbool bForward = true);	
	
	//! \brief 从经纬坐标系统转化为投影坐标系统
	//! \param pCoordSys [in] 投影坐标系统
	//! \remarks 转成2维的Geometry后，调用它的方法实现
	virtual void PJForward( UGPrjCoordSys *pCoordSys );
	
	//! \brief 从投影坐标系统转化为经纬坐标
	//! \param pCoordSys 投影坐标系统
	//! \remarks 转成2维的Geometry后，调用它的方法实现
	virtual void PJInverse( UGPrjCoordSys *pCoordSys );

	//! \brief 从经纬坐标系统转化为三维投影坐标系统
	//! \param pCoordSys 投影坐标系统
	virtual void PJForward3D( UGPrjCoordSys *pCoordSys );
	
	//! \brief 从投影坐标系统转化为经纬坐标系
	//! \param pCoordSys 投影坐标系统
	virtual void PJInverse3D( UGPrjCoordSys *pCoordSys );
	
	

public:

	//! \brief 拷贝构造GeoPoint3D。
	//! \param geoPoint3D [in] 已有点对象。
	//! \return 已有对象非法, 返回false。
	UGbool Make(const UGGeoPoint3D& geoPoint3D);		

	//! \brief 构造点对象。
	//! \param dx [in] X值。
	//! \param dy [in] Y值。
	//! \param dz [in] Z值。
	//! \return 成功返回true。
	UGbool Make(UGdouble dx, UGdouble dy, UGdouble dz);	

	//! \brief 构造点对象
	//! \param pnt [in] 点坐标。
	//! \return 返回true。
	virtual UGbool Make(const UGPoint3D& pnt);	
	
	//! \brief 设置X方向经纬度
	void SetX(UGdouble value);
	
	//! \brief 设置Y方向经纬度
	void SetY(UGdouble value);
	
	//! \brief 设置距离地面的高度，并不是到球心得高度
	void SetZ(UGdouble value);
	
	//! \brief 获取X方向经纬度
	UGdouble GetX() const;
	
	//! \brief 获取Y方向经纬度
	UGdouble GetY() const;
	
	//! \brief 获取距离地面的高度，并不是到球心得高度
	UGdouble GetZ() const;

	//! \brief 缩放
	//! \param dRatioX X方向缩放比率
	//! \param dRatioY Y方向缩放比率
	//! \param dRatioY Z方向缩放比率
	//! \attention 正圆无法在两个不同方向缩放, 因此dRatioX和dRatioY必须相等才行
	virtual void Inflate3D( UGdouble dRatioX, UGdouble dRatioY,UGdouble dRatioZ);
	
	//! \brief 缩放
	//! \param dRatio 缩放比率(X,Y方向相同)
	virtual void Inflate3D( UGdouble dRatio);
	
	//! \brief 平移
	//! \param dX 平移的X偏移量
	//! \param dY 平移的Y偏移量
	virtual void Offset( UGdouble dX, UGdouble dY);
	
	//! \brief 平移
	//! \param 偏移量(X,Y方向相同)
	virtual void Offset( UGdouble dOffset);
	
	//! \brief 平移
	//! \param 平移的偏移量(分别用UGSize2D中的x,y代表X,Y方向的偏移量)
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

	//! \brief 三维对象旋转
	//! \param vecAxis [in] 旋转轴 过原点
	//! \param dAngle [in] 旋转角度
	virtual void Rotate3D(const UGVector3d& vecAxis, UGdouble dAngle);

	//! \brief 三点镜像
	//! \param pntMirror1 [in] 构成镜面的第一个点
	//! \param pntMirror2 [in] 构成镜面的第二个点
	//! \param pntMirror3 [in] 构成镜面的第三个点
	//! \return 成功返回true,失败返回false
	virtual UGbool Mirror3D(const UGPoint3D &pntMirror1, const UGPoint3D &pntMirror2, const UGPoint3D &pntMirror3);


	//! \brief 镜像
	//! \param vecNormal [in] 镜面的法线向量	
	//! \return 成功返回true,失败返回false
	virtual UGbool Mirror3D(const UGVector3d &vecNormal);

	//! \brief 设置对象的位置，这个函数只对模型和规则几何体意义，位置为模型等物体的底面中心点
	//! x,y为经纬度，z是指到球面的距离而不是到球心的距离
	//! \param value [in] 指定的位置点，含义见上。
	virtual void SetPosition(const UGPoint3D& value);

	//! \brief 得到对象的位置，这个函数只对模型和规则几何体意义，位置为模型等物体的底面中心点
	//! \return 对象的位置。
	virtual UGPoint3D GetPosition() const;

protected:
	//! \brief 真正计算Bounds
	//! \return 返回得到的Bounds
	virtual UGRect2D ComputeBounds() const;	
	
	//! \brief 只保存几何数据部分
	//! \param stream [in] 存储流, 调用之前应该先Open
	//! \param eCodecType [in] 存储的编码方式
	//! \param bSDBPlus [in] 是否存储为SDBPlus的格式
	//! \remarks 由于SDBPlus引擎和数据库引擎的存储上差别较大,所以必须直接调用该函数,
	//! 并增加变量进行分别处理
	//! \return 成功返回true,失败返回false
	virtual UGbool SaveGeoData(UGStream& stream, 
		UGDataCodec::CodecType eCodecType,UGbool bSDBPlus = FALSE) const;
	
	//! \brief 只转载几何数据部分
	//! \param stream [in] 流 
	//! \param eCodecType [in] 编码方式
	//! \attention [in] 还需要增加 UGbool bSDBPlus = FALSE 的参数
	//! \return 成功返回true,失败返回false
	virtual UGbool LoadGeoData( UGStream& stream , 
		UGDataCodec::CodecType eCodecType = UGDataCodec::encNONE,UGbool bSDBPlus = FALSE );
     
	//!\brief 计算得到Boundingbox
	virtual  UGBoundingBox ComputeBoundingBox() const;
public:
	//! \brief 返回一个point3d来描述这个对象，对于3维点就是他本身，对于其他未定义
	virtual UGPoint3D Get3DPoint();
	virtual UGbool	  Set3DPoint(const UGPoint3D& pnt3d);	

private:
	
	//! \brief 内部地理数据
	UGPoint3D m_pnt;

};

}

#endif //UGGEOPOINT3D_H
