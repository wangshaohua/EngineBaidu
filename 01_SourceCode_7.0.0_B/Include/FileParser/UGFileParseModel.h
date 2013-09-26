//////////////////////////////////////////////////////////////////////////
//                    _   _   ____   ____                    
//   Project         | | | | / ___) / ___)                   
//                   | | | || | __ | |                       
//                   | |_| || |_\ || \___                    
//                    \____/ \____| \ ___)     6.0           
//                                                           
//!  \file headerfile.h
//!  \brief Class 的接口定义。
//!  \details 该文件定义了模型文件的主要接口。
//!  \author zhangshuai,sunye
//!  \attention 
//!   Copyright (c) 1996-2008 SuperMap Software Limited Company.  <br> 
//!   All Rights Reserved.
//!  \version 6.0
//////////////////////////////////////////////////////////////////////////

#if !defined(AFX_UGFILEPARSERMODE_H__392553F8_7BF9_4668_BD97_4211091FEF20__INCLUDED_)
#define AFX_UGFILEPARSERMODE_H__392553F8_7BF9_4668_BD97_4211091FEF20__INCLUDED_

#include "FileParser/UGFileParse.h"
#include "Base3D/UGBoundingBox.h"
#include "Base3D/UGMatrix4d.h"
#include "Base3D/UGNode.h"
#include "Base3D/UGAnimationCurve.h"
#include "Base3D/UGAnimation.h"
#include "Base3D/UGMaterial3D.h"

namespace UGC 
{
	class UGMaterial;
	class UGMesh;
	class UGAnimation;
	class UGMaterial3D;
//! \brief 模型的基本信息。
class FILEPARSER_API ModelDataInfo
{
public:
	//! \brief 构造函数。
	ModelDataInfo();

	//! \brief 拷贝构造函数。
	ModelDataInfo(const ModelDataInfo& mInfo);

	//! \brief 重载拷等号。
	void operator=(const ModelDataInfo& mInfo);

	//! \brief 析构函数。
	virtual ~ModelDataInfo();
 
 	//! \brief 清除所有信息恢复默认值。
 	void Clear();
 
	//! \brief 设置模型的名称
	void SetName(const UGString& strName);

	//! \brief 获取模型的名称
	const UGString& GetName() const; 

	//! \brief 得到模型的几何数据。
	UGArray<UGMesh*>& GetMesh();

	//! \brief 获取模型的材质数据。
	UGArray<UGMaterial*>& GetMaterial();

	//! \brief 获取模型的材质数据。
	UGArray<UGMaterial3D*>& GetMaterial3D();

	//! \brief 设置包围盒
	void SetBoundingBox(const UGBoundingBox& box){m_BoundingBox = box;}

	//! \brief 获取模型的包围盒
	UGBoundingBox& GetBoundingBox(){return m_BoundingBox;}

	//! \brief 获取模型的包围盒
	void ComputeBoundingBox();

	//! \brief 模型的在局部坐标矩阵
	UGMatrix4d GetLocalMatrix();

	//! \brief 模型的在局部坐标矩阵
	//! \param matLocalMatrix 局部坐标矩阵
	void SetLocalMatrix(const UGMatrix4d matLocalMatrix);

	//! \brief 获区根结点
	UGNode& GetRootNode(void);

	const UGAnimationCurve* FindAnimationCurve(const UGString& strNodeName)const;

	//! \brief 获取动画信息
	UGbool IsAnimated();
	
	//! \brief 获得起始时间
	UGdouble GetStartTime();

	//! \brief获得结束时间
	UGdouble GetEndTime();

	//! \brief 从流文件中加载
	void Load(UGStream& fStream,const UGString& strFileName);

	//! \brief 存入流文件中
	void Save(UGStream& fStream,const UGString& strFileName);

	//! \brief 获得结点的大小
	UGint GetDataSize() const;

	//! \brief 设置是否有动画
	void SetAnimated(UGbool bAnimated);
	
	//! \brief 设置起始时间
	void SetStartTime(UGdouble dStartTime);
	
	//! \brief 设置结束时间
	void SetEndTime(UGdouble dEndTime);

	//! \brief 获取动画信息
	UGAnimation* GetAnimationState(void);

	//! \brief 设置控制动画信息
	void SetAnimationState(UGAnimation* pAnimation);

	//! \brief 得到对象各方向的缩放比率
	//! \return 对象各方向的缩放比率。
	UGPoint3D GetScale() const;	

	//! \brief 得到对象各方向的旋转角度
	//! \return 对象各方向的旋转角度。
	UGPoint3D GetRotation() const;

	//! \brief 设置对象的缩放大小
	//! \param fScaleX [in] X方向缩放比率。
	//! \param fScaleY [in] Y方向缩放比率。
	//! \param fScaleZ [in] Z方向缩放比率。
	void SetScale(UGdouble fScaleX,UGdouble fScaleY,UGdouble fScaleZ);

	//! \brief 设置对象的旋转量 
	//! \param fRotateX [in] X方向的旋转角度。
	//! \param fRotateY [in] Y方向的旋转角度。
	//! \param fRotateZ [in] Z方向的旋转角度。
	void SetRotation(UGdouble fRotateX,UGdouble fRotateY,UGdouble fRotateZ);


    //!  \brief 设置三维模型对象的定位点 
    void SetPosition(const UGPoint3D pntPosition);

    //!  \brief 返回三维模型定位点
	UGPoint3D GetPosition()const;

protected:
	
	//! \brief 模型数据的名称
	UGString m_strName;

	//! \brief 材质在数组中的位置与名称的对应关系,
	//! \brief 模型的材质数据。
	UGArray<UGMaterial*> m_arryMaterial;

	//! \brief 材质在数组中的位置与名称的对应关系,
	//! \brief 模型的材质数据。
	UGArray<UGMaterial3D*> m_arryMaterial3D;

	//! \brief 模型的几何数据。
	UGArray<UGMesh*> m_arryMesh;

	//! \brief 模型的包围盒
	UGBoundingBox m_BoundingBox;

	//! \brief 模型的局部坐标
	UGMatrix4d m_matLocalMatrix;

	//! \brief 根结点
	UGNode m_rootNode;

	//! \brief 动画信息
	UGbool m_bIsAnimated;

	//! \brief 动画开始时间
	UGdouble m_dStartTime;

	//! \brief 动画结束时间
	UGdouble m_dEndTime;

	//! \brief 材质对应列表,名称与在数组中的位置对
	UGDict<UGString,UGint> m_MaterialMap;

	//! \brief Mesh对应列表,名称与在数组中的位置对
	UGDict<UGString,UGint> m_MeshMap;

	//! \brief 版本号
	UGdouble m_dVersion;

	//! \brief 动画信息
	UGAnimation* m_pAnimation;

	//! \brief 三维对象的缩放系数
	UGPoint3D m_pntScale;

	//! \brief 三维对象的旋转量
	UGPoint3D m_pntRotate;

    //! \brief 三维模型插入点
	UGPoint3D m_pntPosition;

public:
	//! \brief 对应于模型信息中的动画UGString用于查找动画
	UGDict<UGString,UGAnimationCurve*> m_AnimationList;
};


class FILEPARSER_API UGFileParseModel : public UGFileParser  
{
public:

	//! \brief 构造函数。
	UGFileParseModel();	

	//! \brief 析构函数。
	virtual ~UGFileParseModel();
	
public:	
	ModelDataInfo* GetModelDataInfo()const;
	////////////////////////////////////////////////////////////////////////
	//
	// 常用基本属性
	//
	////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////
	// 读出函数
	//////////////////////////////////////////////////////////////////////////


	//////////////////////////////////////////////////////////////////////////
	// 写入函数
	//////////////////////////////////////////////////////////////////////////
	virtual UGbool Save(const UGExportParams& expParams,const ModelDataInfo* pModelInfo);
protected:
	ModelDataInfo* m_pModelInfo;

};

} //namespace UGC

#endif // !defined(AFX_UGFILEPARSERMODE_H__392553F8_7BF9_4668_BD97_4211091FEF20__INCLUDED_)

