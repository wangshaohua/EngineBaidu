//////////////////////////////////////////////////////////////////////////
//                    _   _   ____   ____                    
//   Project         | | | | / ___) / ___)                   
//                   | | | || | __ | |                       
//                   | |_| || |_\ || \___                    
//                    \____/ \____| \ ___)     6.0           
//                                                           
//!  \file UGGeometry3DFactory.h
//!  \brief 用来创建Geometry3D的工厂类。
//!  \author UGCTeam。
//!  \attention 
//!   Copyright (c) 1996-2010 SuperMap Software Co., Ltd. <br> 
//!   All Rights Reserved.
//!  \version 6.0
//////////////////////////////////////////////////////////////////////////

#ifndef UGGEOMETRY3DFACTORY_H
#define UGGEOMETRYF3DACTORY_H

#include "Geometry3D/UGGeometry3D.h"
#include "Geometry/UGGeometryFactory.h"

namespace UGC
{

//! \brief 用来创建Geometry3D的工厂类
class GEOMETRY3D_API UGGeometry3DFactory : public UGGeometryFactory
{
public:
	//! \brief 缺省构造函数。
	UGGeometry3DFactory();    
	
	//! \brief 默认析构函数。
    virtual ~UGGeometry3DFactory();

public:

	//! \brief 确保pGeometry是指定的类型
	//! \param pGeometry [out] 几何对象指针
	//! \param eType [in] 指定的类型
	//! \remarks 本函数主要用在: 从外面传入一个几何对象类型, 但有可能为NULL, 也有可能不是需要的类型
	//!			 这时,就需要 重新分配 Geometry指针,new 出需要类型的Geometry来; 主要用在Recordeset的AddNew等地方
	//! \return 如果对象重新分配空间了,返回true; 否则返回false
	virtual UGbool AssureGeoType(UGGeometry*& pGeometry, UGint nType);	

	//! \brief 传入Geometry类型，生成Geometry
	//! \param nType [in] 要创建的几何对象类型，可以传入Element类型，也可以传入Geometry类型
	//! \attention 返回的Geometry指针, 请使用后delete
	//! \return 成功,返回创建的Geometry的指针; 失败返回NULL
	virtual UGGeometry* CreateGeometry(UGint nType);

	//! \brief 克隆Geometry
	//! \param pGeometry [in] 要被克隆的Geometry对象指针, 不能为NULL
	//! \attention 返回的Geometry指针, 请使用后delete
	//! \return 成功,返回创建的Geometry的指针; 失败返回NULL
	virtual UGGeometry* CloneGeometry(const UGGeometry* pGeometry);
#ifndef IOS3D
	//! \brief 克隆Element为Geometry
	//! \param pElement [in] 要被克隆的Element对象指针, 不能为NULL
	//! \attention 返回的Geometry指针, 请使用后delete
	//! \return 成功,返回创建的Geometry的指针; 失败返回NULL
	virtual UGGeometry* CloneGeometry(const OgdcElement* pElement);
#endif
	//! \brief 拷贝Geometry
	//! \param pGeometrySrc [in] 原Geometry指针, 不得为NULL
	//! \param pGeometryTag [out] 目标Geometry指针, 不得为NULL
	//! \remarks 两个Geometry参数类型必须一致
	//! \return 成功返回true,失败返回false
	virtual UGbool CopyGeometry(const UGGeometry* pGeometrySrc, UGGeometry* pGeometryTag);
#ifndef IOS3D
	//! \brief 拷贝Element
	//! \param pElement [in] 原Element指针, 不得为NULL
	//! \param pGeometry [out] 目标Geometry指针, 不得为NULL
	//! \return 成功返回true,失败返回false
	virtual UGbool CopyGeometry(const OgdcElement* pElement, UGGeometry* pGeometry);
#endif
	//! \brief 判断是否支持该几何类型
	//! \param nType [in] 传入的Geometry类型
	virtual UGbool IsSupport(UGint nType) const;
	
	//! \brief 获取Geometry工厂名称
	//! \return 工厂名称
	virtual UGString GetName() const;	

	//! \brief 传入类型名，返回UGGeometry::Type
	//! \param strGeometryType [in] 几何对象类型的名字
	//! \attention 严格区分大小写, 请参照"GeoPoint"的形式
	//! \return 成功返回几何对象类型, 失败返回0
	virtual UGint GetGeometryType(const UGString& strGeometryType);
	
	//! \brief 传入类型名，返回UGGeometry::Type
	//! \param strGeometryType [in] 几何对象类型的名字
	//! \attention 严格区分大小写, 请参照"GeoPoint"的形式
	//! \return 成功返回几何对象类型, 失败返回0
	virtual UGString GetGeometryName(UGint nGeoType);

	//! \brief 将Geometry2D转换成Geometry3D。
	//! \param pGeometry [in] 传入Geometry2D的指针。
	//! \return 成功则返回三维几何对象的指针, 失败返回null。
	//! \attention Geometry3D是在函数里new出来的，外面负责用完后释放
	static UGGeometry3D* Geometry2DToGeometry3D(UGC::UGGeometry* pGeometry); 	

};

extern "C" GEOMETRY3D_API UGGeometryFactory * CreateGeometryFactory();
#if defined(_AIX) //Aix加载全局函数的问题
extern "C" GEOMETRY3D_API UGGeometryFactory * CreateGeometryFactoryA();
#endif 
}

#endif // !defined(UGGEOMETRY3DFACTORY_H)



