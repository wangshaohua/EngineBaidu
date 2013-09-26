/* 
	\file UGQuaternion4d.h
	\brief 四元数类文件
	\author malq
	\attention
	Copyright(c) 2000-2010  SuperMap GIS Technologies,Inc.<br>
	All Rights Reserved
	<b>更新说明：。</b>
	<em>1、第一条说明。</em>
	<em>2、第二条说明。</em>
*/

#if !defined(AFX_UGQUATERNION4D_H__828A96C2_95EA_4DCC_9468_666159FA635E__INCLUDED_)
#define AFX_UGQUATERNION4D_H__828A96C2_95EA_4DCC_9468_666159FA635E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "Base3D/UGPrerequisites3D.h"

namespace  UGC 
{

//! \brief 四元数类
//! \remarks 四元数主要负责空间旋转
class BASE3D_API UGQuaternion4d  
{

public:
	//! \brief 构造函数
	UGQuaternion4d();
	//! \brief 构造函数
	UGQuaternion4d(UGdouble x, UGdouble y, UGdouble z, UGdouble w);
	UGQuaternion4d(const UGVector3d& xaxis, const UGVector3d& yaxis, const UGVector3d& zaxis);
	//! \brief 析构函数
	virtual ~UGQuaternion4d();
	//! \brief 重载元算符四元数相乘 
	UGQuaternion4d operator*(const UGQuaternion4d& obj);
	//! \brief 重载元算符四元数相减
	UGQuaternion4d operator-(const UGQuaternion4d& obj)const;
	UGQuaternion4d operator+(const UGQuaternion4d& obj)const;
	UGQuaternion4d operator-()const;
	UGQuaternion4d operator*(UGdouble dScalar)const;
	//! \brief 重载元算符四元数和向量相乘
	UGVector3d operator* (const UGVector3d& v) const;

	//! \brief 由旋转轴向量转为四元数
	void FromAxes (const UGVector3d* akAxis);
	//! \brief 由三维旋转轴向量转为四元数
	void FromAxes (const UGVector3d& xAxis, const UGVector3d& yAxis, const UGVector3d& zAxis);
	//! \brief 由旋转矩阵转为四元树
	void FromRotationMatrix (const UGMatrix3d& kRot);
	void FromRotationMatrix (const UGMatrix4d& kRot);
	//! \brief 标准化四元数
	void Normalize();
	//! \brief 四元数长度
	UGdouble Length();
	//! \brief 四元数转为轴和角 
	void ToAngleAxis (UGdouble& rfAngle, UGVector3d& rkAxis);
	//! \brief 四元数点积 
	static UGdouble Dot(const UGQuaternion4d& a, const UGQuaternion4d& b);
	//! \brief 四元数转为欧拉角 
	static UGVector3d QuaternionToEuler(const UGQuaternion4d& q);
	//! \brief 欧拉角转为四元数
	static UGQuaternion4d EulerToQuaternion(UGdouble yaw, UGdouble pitch, UGdouble roll);
	//! \brief 四元数插值
	static UGQuaternion4d Slerp(const UGQuaternion4d& q0, const UGQuaternion4d& q1, UGdouble t);
	//! \brief 四元数线性插值
	static UGQuaternion4d Nlerp(const UGQuaternion4d& rkP,const UGQuaternion4d& rkQ,UGdouble fT, UGbool shortestPath);

	//! \brief 从轴角转为四元数
	void FromAngleAxis (const UGdouble& rfAngle,
								const UGVector3d& rkAxis);
	//! \brief 由四元数专为旋转矩阵
	void ToRotationMatrix (UGMatrix3d& kRot);
	//! \brief 由四元数专为旋转矩阵
	void ToRotationMatrix (UGMatrix4d& kRot);  

	//! \brief 求四元数的逆变换
	UGQuaternion4d Inverse () const;

	//! \brief 求四元数的单元逆变换，即为(w,-x,-y,-z)
	UGQuaternion4d UnitInverse () const;

	//! \brief 重载的等值判断运算符
	UGbool operator== (const UGQuaternion4d& rhs) const;
	//! \brief 重载的相乘运算符
	UGQuaternion4d operator* (const UGQuaternion4d& rkQ) const;
	//! \brief 四元数成员  
	UGdouble x;
	//! \brief 四元数成员
	UGdouble y;
	//! \brief 四元数成员
	UGdouble z;
	//! \brief 四元数x成员
	UGdouble w;



	static const UGQuaternion4d ZERO;
    static const UGQuaternion4d IDENTITY;

};
}
#endif // !defined(AFX_UGQUATERNION4D_H__828A96C2_95EA_4DCC_9468_666159FA635E__INCLUDED_)

