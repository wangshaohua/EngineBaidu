//////////////////////////////////////////////////////////////////////////
//                    _   _   ____   ____                    
//   Project         | | | | / ___) / ___)                   
//                   | | | || | __ | |                       
//                   | |_| || |_\ || \___                    
//                    \____/ \____| \ ___)     6.0           
//                                                           
//!  \file UGGeoRegion3D.h
//!  \brief 三维面几何对象。
//!  \author UGCTeam。
//!  \attention 
//!   Copyright (c) 1996-2010 SuperMap Software Co., Ltd. <br> 
//!   All Rights Reserved.
//!  \version 6.0
//////////////////////////////////////////////////////////////////////////

#if !defined(AFX_UGGEOREGION3D_H__0C5189B8_3750_4468_8FAD_EE5C1969F4EB__INCLUDED_)
#define AFX_UGGEOREGION3D_H__0C5189B8_3750_4468_8FAD_EE5C1969F4EB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Geometry3D/UGGeometry3D.h"
#include "Geometry3D/UGEditType3D.h"

namespace UGC
{
//! \brief 三维面几何对象。
class GEOMETRY3D_API UGGeoRegion3D : public UGGeometry3D
{
public:
	
	//! \brief 缺省构造函数
	UGGeoRegion3D();

	//! \brief 默认析构函数
	virtual ~UGGeoRegion3D();
public:
	
	//! \brief 得到维度, 点为0维, 线/曲线等为1维, 面/曲面等为2维, GeoCompound/GeoText等为-1
	virtual UGint GetDimension() const;
	
	//! \brief 得到内点（在Geometry内部，靠近中央的点）
	//! \return 返回内点
	//! \remarks 为点数最多的子对象 的中间点(中间个数的点, 而不是中间距离的点)
	virtual UGPoint2D GetInnerPoint() const;

	//! \brief 得到内点（可能是Geometry3D的质点）
	//! \return 返回内点
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
	
	//! \brief 点击测试, 用于对象点选
	//! \param pntHitTest 用来测试选中的点
	//! \param dTolerance 容限
	//! \return 选中返回true, 否则返回false
	virtual UGbool HitTest( const UGPoint2D &pntHitTest, UGdouble dTolerance) const;
	
	//! \brief 几何对象是否有效
	//! \return 有效返回true,无效返回false
	virtual UGbool IsValid()const;

	//! \brief 根据已有对象的指针，拷贝构造一个三维面几何对象。
	//! \param pGeometry [in] 已有对象指针。
	//! \return 构造成功返回true。
	//! \remarks 内部调用make方法去实现。
	virtual UGbool MakeWithGeometry(const UGGeometry* pGeometry);
	
	//! \brief 根据三维点串构造一个三维面几何对象
	//! \param pPoints [in] 点串指针。
	//! \param nPntCount [in] 点的个数。
	//! \param UGEditType3D::ET3D_NULL [in] 编辑工具形状（可选）。
	//! \return 构造成功返回true。
	//! \remarks 内部调用make方法去实现，用于在编辑中多态构造对象GeoLine。
	virtual UGbool MakeWithPoints3D(UGPoint3D* pPoints,UGint nPntCount,
		UGEditType3D::EditToolShape3D nEditType = UGEditType3D::ET3D_NULL);	

	//! \brief 根据传入的点串生成对象，主要用于编辑中的参数化等没有内部数组保存点串的对象，
	//! 也用于自定义对象,对于有内部数组保存点串的对象，该函数直接return既可，
	//! 比如GeoLine等对象就直接用AddHandle来生成，效率比较高 
	//! \param pPoints 3维点串
	//! \param nPntCount  点的个数
	virtual void MakeWithPoints(UGPoint3D* pPoints,UGint nPntCount,
				UGEditType::EditToolShape nEditType=UGEditType::ET_Default);
	//! \brief 计算对象绘制时的辅助线，返回的是一个复合对象
	//! \param pPoints [in] 点串
	//! \param nPntCount [in] 点的个数
	//! \param nEditType [in] 绘制对象的类型，参考UGEditType3D
	//! \param pStyle [in] 辅助线的风格，如果传入为NULL，用默认的风格
	//! \return 构造出的几何对象。
	UGGeometry* CalAssistantLine(const UGPoint3D* pPoints,UGint nPntCount,UGEditType3D::EditToolShape3D nEditType);

	//! \brief 得到对象的位置，这个函数只对模型和规则几何体意义，位置为模型等物体的底面中心点，（点线面模型为相应的内点）
	//! \return 对象的位置。
	virtual UGPoint3D GetPosition() const;

	//! \brief 获取数据存储时的大小
	//! \return 返回存储大小
	//! \remarks 暂未考虑编码情况，与SaveGeoData()一起维护
	//! \attention 字符串的长度要+4
	virtual UGint GetDataSize() const;

public:
	//added by xielin ^_^ 编辑相关函数,把编辑和geometry统一
	
	//! \brief 获得编辑对象的句柄的数目
	//! \remarks 对于固定句柄对象为9包括了改变大小的8个控制点和一个旋转控制点
	virtual UGint  GetHandleCount();
	
	
	//nHandle:的值与控制点的关系如右图                         
	//									1---+   	  +--2    	+----3	
	//                                      |         |         |  
	//                                      |         |         |  
	//										x---------x---------x     9
    //										|   ____________    |     |
    //										|  /            \   | x---+
	//									4---x |              |  x-----5
	//										|  \____________/   |
	//										|                   |
	//										x---------x---------x
	//										|		  |         |
	//										|		  |         |
	//								    6---+         +-----7   +-----8
	
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
	 
	 //! \brief 计算对象绘制时的辅助线，返回的是一个复合对象
	 //! \param pPoints 点串
	 //! \param nPntCount  点的个数
	 //! \param nEditType 绘制对象的类型，参考UGEditType
	 //! \param pStyle	 辅助线的风格，如果传入为NULL，用默认的风格
     virtual UGGeometry*  CalAssistantLine(const UGPoint2D* pPoints,UGint nPntCount,UGEditType::EditToolShape nEditType,UGStyle* pStyle=NULL);
	 
	 
	 //! \brief 计算对象绘制时的辅助点，返回的是点的数目,nHandleType返回的是辅助点的类型,参考UGEditType::EditHandleType
	 //! \param pPoints 点串
	 //! \param nPntCount  点的个数
	 //! \param eAssistantPoints 点串,返回的辅助点点串
	 //! \param nEditType 绘制对象的类型，参考UGEditType
	 void CalAssistantPoints(const UGPoint2D* pPoints,UGint nPntCount,UGArray<UGEditType::EditAssistantPoint>& eAssistantPoints,UGEditType::EditToolShape nEditType);
	 
	 
	 
	 //! \brief 根据传入的点串生成对象，主要用于编辑中的参数化等没有内部数组保存点串的对象，
	 //也用于自定义对象,对于有内部数组保存点串的对象，该函数直接return既可，比如GeoLine
	 //GeoLine等对象就直接用AddHandle来生成，效率比较高,但是如果画平行线，就用它来生成
	 //! \param pPoints 点串
	 //! \param nPntCount  点的个数
    // virtual void MakeWithPoints(UGPoint2D* pPoints,UGint nPntCount,UGEditType::EditToolShape nEditType=UGEditType::ET_Default);
	 
	 //! \brief 获取对象需要捕捉的点串
	 //! \param aryPnts 点串，传出去的要捕捉的点串
	 //! \return 如果是true表示有需要捕捉的点串，如果返回false表示该对象没有需要捕捉的点串
	 virtual UGbool GetSnapPoints(UGArray<UGPoint2D>& aryPnts);
	 
	 //! \brief 获取对象需要捕捉的线段数组
	 //! \param aryLines 需要捕捉的线数组（如果有多个part，那么aryLines就应该有多少个count）
	 //! \return 如果是true表示有需要捕捉的线，如果返回false表示该对象没有需要捕捉的线
	 virtual UGbool GetSnapLines(UGLineArray& aryLines);
	 
	 //added by xielin ^_^ 编辑相关函数,把编辑和geometry统一 end
	 
	 //! \brief 调整几何数据,限定在新的Bounds中
	 //! \param rcNewBounds 新的,限定范围的Bounds
	 //! \return 成功返回true,失败返回false
	virtual UGbool Resize(const UGRect2D& rcNewBounds); 

	//! \brief 对象保护性分解
	//! \param arrOutRegion	返回的被分解的对象
	//! \return 
	UGbool ProtectedDecomposeEx(UGArray<UGGeoRegion3D*> &arrOutRegion3D);

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

	//!\brief 得到Boundingbox
	virtual UGBoundingBox ComputeBoundingBox() const;

public:		
	
	//! \brief 得到对象面积
	//! \attention Dimension为2的对象才支持
	//! \return 返回面积
	//! \remarks 转成2维的Geometry后，调用它的方法实现
	virtual UGdouble GetArea() const;
	
	//! \brief 得到三维对象的表面积
	//! \attention Dimension为2的对象才支持
	//! \return 返回表面积
	virtual UGdouble GetArea3D() const;
	
	//! \brief 得到对象长度
	//! \attention Dimension为1or2的对象才支持
	//! \return 返回长度
	//! \remarks 转成2维的Geometry后，调用它的方法实现
	virtual UGdouble GetLength() const;
	
	//! \brief 得到三维对象长度
	//! \attention Dimension为1or2的对象才支持
	//! \return 返回长度
	virtual UGdouble GetLength3D() const;
	//! \brief 缩放
	//! \param dRatioX X方向缩放比率
	//! \param dRatioY Y方向缩放比率
	//! \param dRatioY Z方向缩放比率
	//! \attention 正圆无法在两个不同方向缩放, 因此dRatioX和dRatioY必须相等才行
	virtual void Inflate3D( UGdouble dRatioX, UGdouble dRatioY,UGdouble dRatioZ);
	
	//! \brief 缩放
	//! \param dRatio 缩放比率(X,Y方向相同)
	virtual void Inflate3D( UGdouble dRatio);

	//! \brief 三维对象旋转
	//! \param vecAxis [in] 旋转轴 过原点
	//! \param dAngle [in] 旋转角度
	virtual void Rotate3D(const UGVector3d& vecAxis, UGdouble dAngle);

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


public:
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
	//! \return 成功返回true,失败返回false
	virtual UGbool ConvertToPoint( UGGeoMultiPoint &geoMultiPoint) const;	

	//! \brief 转换成图片，3D类型几何对象，以及用户类型几何对象可以通过先转换成图片，再显示。
	//! \param geoPicture [out] 输出图片几何对象。
	//! \param dResolution [in] 分辨率。
	//! \param dXAngle [in] 水平倾角。
	//! \param dZAngle [in] 旋转倾角。
	//! \return 成功返回true,失败返回false
	virtual UGbool ConvertToPicture( UGGeoPicture &geoPicture, UGdouble dResolution, 
								UGdouble dXAngle = 0, UGdouble dZAngle = 0) const;	
	
public:
	//Projection..
	
	//! \brief 根据投影转化器的设置和转化方向要求, 进行投影转化
	//! \param pPJTranslator [in] 投影转化器
	//! \param bForward [in] 转化方向, true代表从UGRefTranslator的源(Src)转化到目的(Des), false则相反
	virtual void PJConvert( UGRefTranslator *pPJTranslator, UGbool bForward = true);

	
	//! \brief 进行三维投影坐标系统转化
	//! \attention 暂未实现。
	virtual void PJConvert3D( UGRefTranslator *pPJTranslator, UGbool bForward = true);	
	
	//! \brief 从经纬坐标系统转化为投影坐标系统
	//! \param pCoordSys [in] 投影坐标系统
	virtual void PJForward( UGPrjCoordSys *pCoordSys );
	
	//! \brief 从投影坐标系统转化为经纬坐标
	//! \param pCoordSys [in] 投影坐标系统
	virtual void PJInverse( UGPrjCoordSys *pCoordSys );

	//! \brief 从经纬坐标系统转化为三维投影坐标系统
	//! \param pCoordSys 投影坐标系统
	virtual void PJForward3D( UGPrjCoordSys *pCoordSys );
	
	//! \brief 从投影坐标系统转化为经纬坐标系
	//! \param pCoordSys 投影坐标系统
	virtual void PJInverse3D( UGPrjCoordSys *pCoordSys );

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
	virtual UGbool FromXML(const UGString& strXML, GMLVersionType versionType);
	//! \brief 得到几何对象类型。
	//! \return 固定为 GeoRegion3D。
	virtual UGGeometry::Type GetType() const;
	
	//! \brief 清空地理数据
	virtual void Clear();

	//! \brief 得到指定子对象的点串的指针。
	//! \param nSubIndex [in] 子对象索引。
	//! \return 返回子对象的点串的指针。
	const UGPoint3D* GetPoints(UGint nSubIndex=0) const;	
	
	//! \brief 构造一个子对象的GeoRegion
	//! \param pPoints [in] 点串指针。
	//! \param nPntCount [in] 点串的点数目。
	//! \return 点数小于3个,返回false。
	UGbool Make( const UGPoint3D* pPoints, UGint nPntCount );

	//! \brief 创建复杂面对象
	//! \param pPoints [in] 点串指针。
	//! \param pPolyCount [in] 子对象中点数的数组。
	//! \param nSubCount [in] 子对象数目。
	//! \return 所有子对象的点数都小于3个,返回false。
	virtual	UGbool Make(const UGPoint3D* pPoints, const UGint* pPolyCount, UGint nSubCount);

	//! \brief 拷贝构造GeoRegion3D
	//! \param geoRegion [in] 已有面对象。
	//! \return 已有面对象非法, 返回false。
	UGbool Make(const UGGeoRegion3D& geoRegion);

	//! \brief 增加子对象
	//! \param pPoints [in] 点串指针。
	//! \param nPntCount [in] 点串个数。
	//! \return 点的个数少于3个,返回false。
	UGbool AddSub(const UGPoint3D* pPoints, UGint nPntCount);	

	//! \brief 增加子对象
	//! \param geoRegion3D [in]。
	UGbool AddSub(UGGeoRegion3D *geoRegion3D);

	//! \brief 插入子对象。
	//! \param nIndex [in] 要插入的位置索引。
	//! \param pPoints [in] 点串指针。
	//! \param nPntCount [in] 点串中点的个数。
	//! \return 点个数小于3或者索引位置非法,返回false。
	UGbool InsertSub(UGint nIndex, const UGPoint3D* pPoints, UGint nPntCount);	

	//! \brief 删除子对象。
	//! \param nIndex [in] 要删除的子对象的位置索引。
	//! \return 索引非法, 返回false。
	UGbool DelSub(UGint nIndex);

	//! \brief 得到某个子对象, 并构造得到GeoRegion3D。
	//! \param nSubIndex [in] 子对象索引。
	//! \param pGeoRegion3D [out] 通过该子对象构造得到的GeoRegion3D; 如果pGeoRegion3D为NULL,函数内部会new出来。
	//! \return 索引非法, 返回false。
	UGbool GetSub(UGint nSubIndex, UGGeoRegion3D *&pGeoRegion3D);

	//! \brief 得到子对象数目的数组指针。
	//! \return 返回子对象数目的数组指针。
	const UGint* GetPolyCounts() const;

	//! \brief 得到所有子对象的点的个数总和。
	//! \return 返回个数。
	UGint GetPointCount() const;	
	
	//! \brief 得到子对象的个数
	//! \return 返回个数
	virtual UGint GetSubCount() const;
	
	//! \brief 得到某个子对象的点的个数。
	//! \param nSubIndex [in] 子对象索引。
	//! \return 返回个数。
	UGint GetSubPntCount(UGint nSubIndex) const;

	void GetIndexData(UGArray<UGuint>& arrSubCounts, UGArray<UGArray<UGushort> >& arrIndexes);
	void SetIndexData(UGArray<UGuint>& arrSubCounts, UGArray<UGArray<UGushort> >& arrIndexes);

	void GetIndexData(UGArray<UGuint>& arrSubCounts, UGArray<UGArray<UGuint> >& arrIndexes);
	void SetIndexData(UGArray<UGuint>& arrSubCounts, UGArray<UGArray<UGuint> >& arrIndexes);
	

private:

	//! \brief 将内部的三维点数据转成二维点
	//! \return 返回二维点指针，外面注意使用后释放。	
	const UGPoint2D* GetPoint2D() const;

	const UGPoint3D* GetPoint3D() const;
	
	//! \brief 构成面的所有点。
	UGArray<UGPoint3D> m_Points;

	//! \brief 面的子对象个数。
	UGArray<UGint> m_PolyCounts;


	//索引数组
	UGushort* m_pIndexes;

	//索引数据类型
	UGbool m_bUseIndexUint;


	//每个剖分单位的 索引个数
	UGuint* m_pSubIndexCounts;

	//每个剖分单位的 SubRegion个数
	UGuint* m_pSubRegionCounts;

	//最小剖分单位个数
	UGuint m_nSubCount;
};

}

#endif // !defined(AFX_UGGEOREGION3D_H__0C5189B8_3750_4468_8FAD_EE5C1969F4EB__INCLUDED_)

