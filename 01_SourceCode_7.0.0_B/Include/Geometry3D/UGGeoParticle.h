//////////////////////////////////////////////////////////////////////////
//                    _   _   ____   ____                    
//   Project         | | | | / ___) / ___)                   
//                   | | | || | __ | |                       
//                   | |_| || |_\ || \___                    
//                    \____/ \____| \ ___)     6.0           
//                                                           
//!  \file UGGeoRegion3D.h
//!  \brief 三维粒子系统对象。
//!  \author UGCTeam。
//!  \attention 
//!   Copyright (c) 1996-2010 SuperMap Software Co., Ltd. <br> 
//!   All Rights Reserved.
//!  \version 6.0
//////////////////////////////////////////////////////////////////////////

#if !defined(AFX_UGGEOPARTICLE_H__INCLUDED_)
#define AFX_UGGEOPARTICLE_H__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ParticleSystem/UGParticleEffect.h"
#include "Geometry3D/UGGeometry3D.h"

namespace UGC
{

class GEOMETRY3D_API UGGeoParticle : public UGGeometry3D
{
public:
	//! \brief 默认构造函数，需要后续使用MakeWithGeometry或者AddSub来指定粒子的地球位置
	UGGeoParticle();

	//! \brief 构造函数，外部生成好的粒子效果加入进来，
	//! \param pParticleEffect [in] 外部生成好的粒子效果对象。
	//! \param pGeometry [in] 要进行依赖的Geometry对象。
	//! \param bIsAutoRelease [in] 指定需要外部释放还是内部释放，为true为内部释放。
	UGGeoParticle(UGParticleEffect* pParticleEffect,const UGGeometry* pGeometry, UGbool bIsAutoRelease = FALSE);

	//! \brief 构造函数，通过路径生成内部的粒子效果对象
	//! \param strParticleResFileName [in] *.par粒子效果资源文件路径，内部自动生成粒子效果类，并自动释放。
	//! \param pGeometry [in] 要进行依赖的Geometry对象。
	UGGeoParticle(const UGString& strParticleResFileName, const UGGeometry* pGeometry);

	//! \brief 析构函数
	virtual ~UGGeoParticle();

public:

	//! \return 返回当前的自动释放标签
	UGbool GetCurrentAutoRelease() const {return m_bIsAutoRelease;}

	//! \return 返回当前的自动释放标签
	void SetCurrentAutoRelease(UGbool bVal) {m_bIsAutoRelease = bVal;}

	//! \brief 获取当前粒子类型
	UGint GetCurrentParticleEffectType();

	//! \brief 动态设置粒子效果类资源文件路径。内部标记为自动释放
	//! \return 返回粒子效果类
	UGParticleEffect* SetCurrentParticleEffectResFileName(const UGString& strParticleResFileName);
	
	//! \brief 获取当前粒子文件路径
	UGString GetCurrentParticleEffectResFileName();

	//! \brief 设置粒子效果类
	//! \param pParticleEffect [in] 外部生成好的粒子效果对象。
	//! \param bIsAutoRelease [in] 指定需要外部释放还是内部释放，为true为内部释放。
	void SetParticleEffect(UGParticleEffect* pParticleEffect, UGbool bIsAutoRelease = FALSE);
	
	//! \brief 返回粒子效果类。
	//! \return 返回粒子效果类。
	UGParticleEffect* GetParticleEffect();

	//! \brief 返回粒子效果类。
	//! \return 返回粒子效果类。
	const UGParticleEffect* GetParticleEffect() const;

	//! \brief 通过其他Geometry来构造出GeoParticle，只保留其他geometry内部的点串。
	//! \return 是否构造成功。
	virtual UGbool MakeWithGeometry( const UGGeometry* pGeometry);
	
	//! \brief 拷贝构造GeoParticle
	//! \param geoParticle [in] 已有粒子对象。
	//! \return 已有粒子对象非法, 返回false。
	UGbool Make(const UGGeoParticle& geoParticle);

	//! \brief 得到几何对象类型。
	//! \return 固定为 GeoParticle。
	virtual UGGeometry::Type GetType() const;	

	//! \brief 得到内点（在Geometry3D相对应的Geometry内部，靠近中央的点）
	//! \return 返回内点
	virtual UGPoint2D GetInnerPoint() const;	

	//! \brief 几何对象是否有效
	//! \return 有效返回true,无效返回false
	virtual UGbool IsValid() const;

	//! \brief 获取几何中心三维点。
	//! \remarks 对于内部是GeoModel的情况内部采用的是GeoModel的Position。
	//! \return 三维点。
	virtual UGPoint3D GetInnerPoint3D() const;

	UGbool GetParticleEffectFileChanged()
	{
		return m_bParticleFileChanged;
	}

	void SetParticleEffectFileChanged( UGbool other)
	{
		m_bParticleFileChanged = other;
	}

public:
	//! \brief 清空地理数据
	virtual void Clear();

	//! \brief 构造多个子对象的复杂Geometry.
	//! \param pPoints [in] 点串指针。
	//! \param pPolyCount [in] 子对象中点数的数组。
	//! \param nSubCount [in] 子对象数目。
	//! \return 所有子对象的点数都小于2个,返回false。
	virtual UGbool Make( const UGPoint2D* pPoints, const UGint* pPolyCount, UGint nSubCount );

	//! \brief 创建复杂面对象
	//! \param pPoints [in] 点串指针。
	//! \param pPolyCount [in] 子对象中点数的数组。
	//! \param nSubCount [in] 子对象数目。
	//! \return 所有子对象的点数都小于3个,返回false。
	UGbool Make(const UGPoint3D* pPoints, const UGint* pPolyCount, UGint nSubCount);

	//! \brief 得到指定子对象的点串的指针。
	//! \param nSubIndex [in] 子对象索引。
	//! \return 返回子对象的点串的指针。
	const UGPoint3D* GetPoints(UGint nSubIndex=0) const;	

	//! \brief 得到指定子对象的点串的指针。
	//! \param nSubIndex [in] 子对象索引。
	//! \return 返回子对象的点串的指针。
	UGPoint3D* GetPoints(UGint nSubIndex=0);	

	//! \brief 增加子对象
	//! \param pPoints [in] 点串指针。
	//! \param nPntCount [in] 点串个数。
	//! \return 点的个数少于3个,返回false。
	UGbool AddSub(const UGPoint3D* pPoints, UGint nPntCount);	

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

public:
	//! \brief 三维对象缩放
	//! \param dRatioX [in] X方向缩放比率
	//! \param dRatioY [in] Y方向缩放比率
	//! \param dRatioZ [in] Z方向缩放比率
	virtual void Inflate3D( UGdouble dRatioX, UGdouble dRatioY, UGdouble dRatioZ);

	//! \brief 三维对象缩放
	//! \param dRatio [in] 缩放比率(X,Y,Z方向相同)	
	virtual void Inflate3D( UGdouble dRatio);

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

	virtual void SetPosition(const UGPoint3D& value);

public:
	//! \brief 得到维度, 点为0维, 线/曲线等为1维, 面/曲面等为2维, GeoCompound/GeoText等为-1
	virtual UGint GetDimension() const;

	//! \brief 只保存几何数据部分。
	//! \param stream [in] 存储流, 调用之前应该先Open。
	//! \param eCodecType [in] 存储的编码方式。
	//! \param FALSE [in] 是否存储为SDBPlus的格式。
	//! \return 成功返回true,失败返回false。
	//! \remarks 由于SDBPlus引擎和数据库引擎的存储上差别较大,所以必须直接调用该函数,并增加变量进行分别处理。
	//! \attention 被SDBPlus所迫,不得不public之。
	virtual UGbool SaveGeoData(UGStream& stream, 
		UGDataCodec::CodecType eCodecType,UGbool bSDBPlus = FALSE) const;

	//! \brief 只转载几何数据部分
	//! \param stream [in] 流 
	//! \param eCodecType [in] 编码方式
	//! \attention 还需要增加 UGbool bSDBPlus = FALSE 的参数
	//! \return 成功返回true,失败返回false	
	virtual UGbool LoadGeoData( UGStream& stream , 
		UGDataCodec::CodecType eCodecType = UGDataCodec::encNONE,UGbool bSDBPlus = FALSE );

	//! \brief 存储额外的附加数据,不和Geometry存储在一起的数据
	//! \brief 粒子里边存储使用的纹理和粒子参数分开
	//! \return 成功返回TRUE,失败返回FLASE
	virtual UGbool SaveExtData(UGArray<UGTextureInfo>& arryTextureInfo);

	//! \brief 加载额外纹理数据到几何对象中
	//! \return 成功返回TRUE,失败返回FLASE
	virtual UGbool LoadExtData(const UGArray<UGTextureInfo>& arrayTextureInfos);

	//! \brief 通过几何对象中保存的纹理路径初始化纹理信息
	//! \return 成功返回TRUE,失败返回FLASE
	virtual UGbool InitialTextureInfo(UGArray<UGTextureInfo>& arrayTextureInfos);


	//! \brief 将Geometry生成XML字符串
	//! \param versionType [in] GML的版本
	//! \param nPace [in] 缩进的空格数目,使得xml字符串更加易于人工阅读; 
	//! 主要用于如果返回的xml字符串是一个大标签中的一部分, 通过指定空格数目,可以使层次清晰
	//! \return 返回指定GML版本的xml字符串
	//! \remarks 转成2维的Geometry后，调用它的方法实现
	virtual UGString ToXML(GMLVersionType versionType, UGint nPace = 0)  const;

	//! \brief 从XML字符串中生成Geometry
	//! \param strXML [in] xml格式字符串
	//! \param versionType [in] xml字符串的GML版本
	//! \return 返回指定GML版本的xml字符串
	virtual UGbool FromXML(const UGString& strXML, GMLVersionType versionType);

protected:
	//! \brief 真正计算BoundingBox
	//! \remarks 由于获取不到Model的内部信息，所以这里采用的是的策略与GeoPoint的一致。
	//! \return 返回得到的BoundingBox
	virtual UGBoundingBox ComputeBoundingBox() const;

	//! \brief 真正计算Bounds
	//! \return 返回得到的Bounds
	//! \remarks 转成2维的Geometry后，调用它的方法实现
	virtual UGRect2D ComputeBounds() const;	

private:

	UGPoint2D ComputeGeoLineInnerPoint() const;

	UGPoint2D ComputeGeoRegionInnerPoint() const;

	UGPoint3D ComputeGeoRegionInnerPoint3D() const;

	UGPoint3D ComputeGeoLineInnerPoint3D() const;

	//! \brief 将内部的三维点数据转成二维点
	//! \return 返回二维点指针，外面注意使用后释放。	
	UGPoint2D* GetPoint2Ds() const;

	void ComputePosition();

private:

	//! \brief 粒子效果
	UGParticleEffect* m_pParticleEffect;

	//! \brief 是否自动释放UGParticleEffect，默认是TRUE
	UGbool m_bIsAutoRelease;

	//! \brief 坐标点点串
	// 若外部改变了与粒子相关的Geometry的位置，则粒子内部的几何点信息也需要更新
	UGArray<UGPoint3D> m_Point3Ds;

	//! \brief 用来存放 所有子对象的点的个数 信息的整型数组
	// 若外部改变了与粒子相关的Geometry的位置，则粒子内部的几何点信息也需要更新
	UGArray<UGint> m_PolyCounts;

	//! \brief 记录粒子的外部Geometry来源。默认是null
	UGint m_nGeometryTypeSrc;

	UGbool m_bParticleFileChanged;

};

}

#endif

