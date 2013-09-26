//////////////////////////////////////////////////////////////////////////
//                    _   _   ____   ____                    
//   Project         | | | | / ___) / ___)                   
//                   | | | || | __ | |                       
//                   | |_| || |_\ || \___                    
//                    \____/ \____| \ ___)     6.0           
//                                                           
//!  \file headerfile.h
//!  \brief
//!  \details
//!  \author 。
//!  \attention 
//!   Copyright (c) 1996-2010 SuperMap Software Co., Ltd. <br> 
//!   All Rights Reserved.
//!  \version 6.0
//////////////////////////////////////////////////////////////////////////


#if !defined(AFX_UGSIMPLESPLINE_H__07E8BCDA_D3A9_431B_A917_E7A1D7351969__INCLUDED_)
#define AFX_UGSIMPLESPLINE_H__07E8BCDA_D3A9_431B_A917_E7A1D7351969__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "Base3D/UGPrerequisites3D.h"
#include "Base3D/UGMatrix4d.h"

namespace UGC
{
//! \brief 样条插值
class BASE3D_API UGSimpleSpline
{
public:
	//! \brief 构造函数
	UGSimpleSpline();

	//! \brief 析构函数
	~UGSimpleSpline();

	//! \brief 添加点数据
	//! \param vec 点数据[in]。
	void AddPoint(const UGVector3d& vec);

	//! \brief 根据索引获得某点数据
	//! \param uIndex 索引[in]。
	const UGVector3d& GetPoint(UGushort uIndex) const;

	//! \brief 获得需要样条插值的点数据个数
	UGushort GetNumPoints(void) const;

	//! \brief 清空当前数据
	void Clear(void);

	//! \brief 更新指定位置的数据
	//! \param uIndex 索引[in]。
	//! \param vec 点数据[in]。
	void UpdatePoint(UGushort uIndex, const UGVector3d& vec);

	//! \brief 根据t比例，获得插值数据
	//! \param t 比例值[in]。
	UGVector3d Interpolate(UGdouble t) const;

	//! \brief 根据t比例，获得插值数据
	//! \param fromIndex 起始索引[in]。
	//! \param t 相对于起始索引的比例值[in]。
	UGVector3d Interpolate(UGushort fromIndex, UGdouble t) const;

	//! \brief 是否自动计算,当更新点时，会重新计算正切参数
	void SetAutoCalculate(UGbool autoCalc);

	//! \brief 重新计算正切参数
	void RecalcTangents(void);

protected:

	//! \brief 自动计算标识
	UGbool m_bAutoCalc;

	//! \brief 需计算插值的数据
	UGArray<UGVector3d> m_arrPoints;

	//! \brief 正切参数
	UGArray<UGVector3d> m_arrTangents;

	//! brief Hermite　多项式
	UGMatrix4d m_matCoeffs;
};
}
#endif // !defined(AFX_UGSIMPLESPLINE_H__07E8BCDA_D3A9_431B_A917_E7A1D7351969__INCLUDED_)


