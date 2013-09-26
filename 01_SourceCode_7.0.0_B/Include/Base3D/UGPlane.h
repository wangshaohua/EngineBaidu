// UGPlane.h: interface for the UGPlane class.
//
//////////////////////////////////////////////////////////////////////
/* 
	\file UGPlane.h
	\brief UGC三维平面类头文件。
	\author 马柳青
	\attention
	Copyright(c) 2000-2010  SuperMap GIS Technologies,Inc.<br>
	All Rights Reserved
	<b>更新说明：。</b>
	<em>1、第一条说明。</em>
	<em>2、第二条说明。</em>
*/

#if !defined(AFX_UGPLANE_H__FB442292_3E4D_49F8_A98D_245EE80AE3B2__INCLUDED_)
#define AFX_UGPLANE_H__FB442292_3E4D_49F8_A98D_245EE80AE3B2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Base3D/UGPrerequisites3D.h"
#include "Base3D/UGVector3d.h"

namespace UGC 
{
//! \brief 三维平面类，在视景体中使用。
//! \remarks 	
class BASE3D_API UGPlane  
{

public:

	//! \brief 默认构造函数。
	UGPlane();	
	//! \brief 构造函数，由方向量和面距原点的距离构建面。
	//! \param vec 面的法向量[in]。
	//! \param fDistance 面距离原点的距离[in]。
	UGPlane(const UGVector3d& vec,UGdouble fDistance);	
	//! \brief 析构函数，什么也没干。
	virtual ~UGPlane();
	//! \brief 对面进行标准化。
	void Normalize();

	//! \brief 获取指定的点到该平面的距离值。
	//! \param vPoint 指定的三维空间中的点位置[in]。
	//! \return 返回计算出来的距离。
	UGdouble GetDistance(const UGVector3d& vPoint)const;

	//! \brief 获取面的法向量。
	UGVector3d GetNormal();

	//! \brief 设置面的法向量。
	void SetNormal(UGVector3d val);

	//! \brief 获取面距离原点的距离。
	UGdouble GetPlaneDistance();

	//! \brief 设置面距离原点的距离。
	void SetPlaneDistance(UGdouble dist);

protected:

	//! \brief 成员面的法向量
	UGVector3d m_vNormal;

	//! \brief 成员面距离原点的距离
	UGdouble m_fDistance;
};
}
#endif // !defined(AFX_UGPLANE_H__FB442292_3E4D_49F8_A98D_245EE80AE3B2__INCLUDED_)

