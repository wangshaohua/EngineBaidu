//////////////////////////////////////////////////////////////////////////
//                    _   _   ____   ____                    
//   Project         | | | | / ___) / ___)                   
//                   | | | || | __ | |                       
//                   | |_| || |_\ || \___                    
//                    \____/ \____| \ ___)     6.0           
//                                                           
//!  \file headerfile.h
//!  \brief 区域贴图类。
//!  \details 完成区域贴图类的封装。
//!  \author 。
//!  \attention 
//!   Copyright (c) 1996-2010 SuperMap Software Co., Ltd. <br> 
//!   All Rights Reserved.
//!  \version 6.0
//////////////////////////////////////////////////////////////////////////

#if !defined(AFX_UGGEOGROUNDOVERLAY_H__520E3CA0_E078_4DC6_A877_410CB2EF52F6__INCLUDED_)
#define AFX_UGGEOGROUNDOVERLAY_H__520E3CA0_E078_4DC6_A877_410CB2EF52F6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "Geometry3D/UGGeometry3D.h"
#include "Base3D/UGVector3d.h"
#include "Toolkit/UGPalette.h"
namespace UGC
{
//! \brief 区域贴图类。
class GEOMETRY3D_API UGGeoGroundOverlay: public UGGeometry3D  
{
public:
	//! \brief 构造函数。
	UGGeoGroundOverlay();
	//! \brief 析构函数。
	virtual ~UGGeoGroundOverlay();
	//! \brief 由一个GroundOverlay构建该由一个GroundOverlay构建该。。
	UGbool Make(const UGGeoGroundOverlay& GroundOverlay);

	//! \brief 由图片路径、图片中心点位置、图片尺寸构建GeoGroundOverlay。
	//! \param strImagePath 纹理图片路径[in]。
	//! \param &pntPos 图片中心点位置[in]。
	//! \param szSize 图片尺寸[in]。
	UGbool Make(const UGString& strImagePath, const UGPoint3D &pntPos, const UGSize2D& szSize);	
	//! \brief 由图片数据、图片中心点位置、图片尺寸构建GeoGroundOverlay。
	//! \param aryImageData 图片数据[in]。
	//! \param &pntPos 图片中心点位置[in]。
	//! \param szSize 图片尺寸[in]。
	//! \param bCopyData 是否拷贝数据，若为真则赋值一份数据[in]。
	UGbool Make(UGArray<UGImageData*>& aryImageData, const UGPoint3D &pntPos, const UGSize2D& szSize, UGbool bCopyData);	
	
	//! \brief 获得几何类型，此处返回GeoGroundOverlay
	virtual UGGeometry::Type GetType() const;

	//! 返回维数，这里返回3
	virtual UGint GetDimension() const;
	
	//! \brief 释放数据，并重置变量。
	virtual void Clear();
	//! \brief 获得二维内点。
	//! \return 二维点。
	virtual UGPoint2D GetInnerPoint() const;	
	
	//! \brief 获得三维内点。
	//! \return 三维点。
	virtual UGPoint3D GetInnerPoint3D()const;
	
	//! \brief 根据geometry类型，再调用各自的make方法去实现。
	//! \param pGeometry [in]。
	//! \return 。
	//! \remarks 。
	//! \attention 构造成功返回true。
	virtual UGbool MakeWithGeometry(const UGGeometry* pGeometry);	

	
	//! \brief 几何对象是否有效
	//! \return 有效返回true,无效返回false
	virtual UGbool IsValid()const;
	 
	//! \brief 得到图片路径。
	//! \return 返回图片路径。
	//! \remarks 显示的时候先查看图片数据是否存在，如果不存在，再从图片路径中加载数据
	UGString GetImagePath()const;
	//! \brief 设置图片路径。
	//! \param strImagePath [in] 要设置的图片路径。
	void     SetImagePath(const UGString& strImagePath);
 
	//! \brief 得到高度。
	//! \return 返回高度。
	//! \remarks 该高度不是看上去的高度,而是没有进行旋转之前的高度。
	UGdouble GetHeight() const;	

	//! \brief 设置高度。
	//! \param dHeight [in] 要设置的高度。
	//! \return dHeight小于等于0, 返回false。
	UGbool SetHeight( UGdouble dHeight );	

	//! \brief 得到宽度。
	//! \return 返回宽度。
	//! \remarks 该宽度不是看上去的宽度,而是没有进行旋转之前的宽度。
	UGdouble GetWidth() const;

	//! \brief 设置宽度。
	//! \param dWidth [in] 要设置的宽度。
	//! \return dWidth小于等于0,返回false。
	UGbool SetWidth( UGdouble dWidth );	

	//! \brief 增加一帧图片数据，适合gif之类的数据。
	UGint AddImageData(UGImageData* pImageData);

	//! \brief 插入一帧图片数据，适合gif之类的数据。
	void InsertAtImageData(UGint nIndex, UGImageData* pImageData);

	//! \brief 得到某一帧图片数据，适合gif之类的数据。
	UGImageData* GetImageData(UGint nIndex);

	//! \brief 移除某一帧图片数据，适合gif之类的数据。
	UGImageData* RemoveImageData(UGint nIndex);

	//! \brief 释放某帧图片数据，适合gif之类的数据。
	UGint ReleaseImageData(UGint nIndex, UGint nCount = 1);

	//! \brief 释放内存图片数据
	void ReleaseAllImageData();

	//! \brief 得到帧数，即图片由多少帧组成
	UGint GetFrameCount() const;

	//! \brief 得到当前帧 
	UGint GetCurrentFrame() const;

	//! \brief 设置当前帧 
	void SetCurrentFrame(UGint nCurFrame);

	//! \brief 存储到数据流中
	virtual UGbool SaveGeoData(UGStream& stream, UGDataCodec::CodecType eCodecType,UGbool bSDBPlus = FALSE) const;

	//! \brief 从数据流中加载
	virtual UGbool LoadGeoData( UGStream& stream , UGDataCodec::CodecType eCodecType = UGDataCodec::encNONE ,UGbool bSDBPlus = FALSE);
	
	//! \brief 获取数据存储时的大小
	//! \return 返回存储大小
	//! \remarks 暂未考虑编码情况，与SaveGeoData()一起维护
	//! \attention 字符串的长度要+4
	virtual UGint GetDataSize() const;
private:
	//! \brief 设置图片数据
	void SetImageData(const UGArray<UGImageData*>& aryImageData,UGbool bCopyData);
protected:
	//! \brief 真正计算Bounds
	//! \return 返回得到的Bounds
	virtual UGRect2D ComputeBounds() const;	

	//!\brief 得到Boundingbox
	virtual UGBoundingBox ComputeBoundingBox() const;

private:
	//! \brief 内存图片数据
	//! \remarks 数组的方式用于支持类似GIF形式的图片
	UGArray<UGImageData*> m_aryImageData;
	//! \brief 当前帧
	UGint m_nCurFrame;
	//! \brief 宽度
	UGdouble m_dWidth;
	//! \brief 高度
	UGdouble m_dHeight;
	//! \brief 图片路径
	//! \remarks 贴图的时候先看内存图片数据m_aryImageData是否存在，如果不存在在从图片路径加载
	UGString m_strImagePath;
	//! \brief 添加图片，获取移除图图片加锁
	UGMutex m_mutex;
};
}
#endif // !defined(AFX_UGGEOGROUNDOVERLAY_H__520E3CA0_E078_4DC6_A877_410CB2EF52F6__INCLUDED_)

