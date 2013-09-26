//////////////////////////////////////////////////////////////////////////
//                    _   _   ____   ____                    
//   Project         | | | | / ___) / ___)                   
//                   | | | || | __ | |                       
//                   | |_| || |_\ || \___                    
//                    \____/ \____| \ ___)     6.0           
//                                                           
//!  \file UGGeoText3D.h 
//!  \brief 三维文本几何对象。
//!  \author UGCTeam。
//!  \attention 
//!   Copyright (c) 1996-2010 SuperMap Software Co., Ltd. <br> 
//!   All Rights Reserved.
//!  \version 6.0
//////////////////////////////////////////////////////////////////////////

#if !defined(AFX_UGGEOTEXT3D_H__2D5F3146_41B7_47C7_BAE2_D21CFFCCB499__INCLUDED_)
#define AFX_UGGEOTEXT3D_H__2D5F3146_41B7_47C7_BAE2_D21CFFCCB499__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "Geometry3D/UGGeometry3D.h"
#include "Toolkit/UGTextStyle.h"

namespace UGC
{
//! \brief 文本子对象
class GEOMETRY3D_API UGSubText3D
{
public:
	//! \brief 缺省构造函数
	UGSubText3D();
	
	//! \brief 默认析构函数
	~UGSubText3D();

	//! \brief 拷贝构造函数。
	//! \param subText [in] 已有的文本子对象。
	UGSubText3D(const UGSubText3D& subText);	
	
	//! \brief 用文本内容字符串进行构造
	//! \param strText [in] 文本内容字符串。
	//! \param dAngle [in] 旋转角度,默认为0
	UGSubText3D(const UGString& strText, UGdouble dAngle=0.0);
	
	//! \brief 得到旋转角度。
	//! \return 返回旋转角度。
	UGdouble GetAngle() const;	
	
	//! \brief 设置旋转角度。
	//! \param dAngle [in] 旋转角度。
	void SetAngle(UGdouble dAngle);	
	
	//! \brief 得到文本内容。
	//! \return 返回文本内容。
	UGString GetText() const;	
	
	//! \brief 设置文本内容。
	//! \param strText [in] 文本内容。
	void SetText(const UGString& strText);	
	
	//! \brief 赋值函数。
	//! \param subText [in] 已有的文本子对象。
	void operator=(const UGSubText3D& subText);

private:
	
	//! \brief 子文本的旋转角度, 单位为:度, 逆时针方向
	//! \remarks 内存中改为double,角度单位,存储时和SFC保持兼容
	//! 子文本的倾角，单位为 0.1度, 逆时针方向
	UGdouble m_dAngle;
	
	//! \brief 预留
	//UGint m_nReserved;
	
	//! \brief 文本内容字符串
	UGString m_strText;
};

//! \brief 三维文本几何对象
class GEOMETRY3D_API UGGeoText3D : public UGGeometry3D
{
public:
	//! \brief 缺省构造函数
	UGGeoText3D();

	//! \brief 默认析构函数
	virtual ~UGGeoText3D();

	//! \brief 清空地理数据
	virtual void Clear();

	//! \brief 得到几何对象类型。
	//! \return 固定为 GeoText3D。
	virtual UGGeometry::Type GetType() const;

	//! \brief 得到子对象的个数
	//! \return 返回个数
	virtual UGint GetSubCount() const;

	//! \brief 根据已有对象的指针，拷贝构造一个UGGeoText3D。
	//! \param pGeometry [in] 已有线对象指针。
	//! \return 构造成功返回true。
	//! \remarks 内部调用make方法去实现。
	virtual UGbool MakeWithGeometry(const UGGeometry* pGeometry);	


	//! group 创建文本对象
	//! \brief 通过文本内容/锚点/旋转角度来构造文本对象。
	//! \param strText [in] 文本内容。
	//! \param pntAnchor [in] 锚点。
	//! \param dAngle [in] 旋转角度。
	//! \return 返回true。
	UGbool Make(const UGString& strText, const UGPoint3D& pntAnchor, UGdouble dAngle=0.0);	
		
	//! \brief 创建文本对象(默认风格)
	//! \param pntAnchor [in] 锚点(文本对象的定位点)。
	//! \param subText [in] 文本子对象。
	//! \return 返回true
	UGbool Make(const UGPoint3D& pntAnchor, const UGSubText3D& subText);	
	
	//! \brief 创建文本对象(指定风格,且有多个子对象)
	//! \param textStyle [in] 文本风格。
	//! \param pPoints [in] 文本子对象的定位点点串指针。
	//! \param pSubText [in] 文本子对象的指针。
	//! \param nSubCount [in] 文本子对象的数目。
	//! \return 返回true。
	UGbool Make(const UGTextStyle& textStyle, const UGPoint3D* pPoints, const UGSubText3D* pSubText, UGint nSubCount);	
	
	//! \brief 通过复制构造文本对象。
	//! \param geotext [in] 已有的文本对象。
	//! \return 返回true。
	UGbool Make(const UGGeoText3D& geotext);	
	
	//! \brief 增加文本子对象
	//! \param strText [in] 文本内容。
	//! \param pntAnchor [in] 子对象的锚点。
	//! \param dAngle=0.0 [in] 子对象的旋转角度。
	//! \return 返回true。
	UGbool AddSub(const UGString& strText, const UGPoint3D& pntAnchor, UGdouble dAngle=0.0);	
	
	//! \brief 增加文本子对象。
	//! \param pntAnchor [in] 锚点。
	//! \param subText [in] 文本子对象。
	//! \return 返回true。
	UGbool AddSub(const UGPoint3D& pntAnchor, const UGSubText3D& subText);	
	
	//! \brief 插入文本子对象。
	//! \param nIndex [in] 插入的位置索引。
	//! \param strText [in] 文本内容。
	//! \param pntAnchor [in] 锚点。
	//! \param dAngle [in] 旋转角度。
	//! \return 返回true
	UGbool InsertSub(UGint nIndex, const UGString& strText, const UGPoint3D& pntAnchor,UGdouble dAngle=0.0);	
	
	//! \brief 插入文本子对象。
	//! \param nIndex [in] 插入的位置索引。
	//! \param pntAnchor [in] 锚点。
	//! \param subText [in] 文本子对象。
	//! \return 返回true。
	UGbool InsertSub(UGint nIndex, const UGPoint3D& pntAnchor, const UGSubText3D& subText);	
	
	//! \brief 删除文本子对象
	//! \param nIndex [in] 要删除的子对象位置索引。
	//! \return 索引非法,返回false。
	UGbool DelSub(UGint nIndex);	
	
	//! \brief 设置文本子对象。
	//! \param nIndex [in] 设置的索引。
	//! \param strText [in] 文本内容。
	//! \param pntAnchor [in] 锚点。
	//! \param dAngle [in] 旋转角度。
	//! \return 返回true。
	UGbool SetSub(UGint nIndex, const UGString& strText, 
		const UGPoint3D& pntAnchor, UGdouble dAngle=0.0);	
	
	//! \brief 设置文本子对象。
	//! \param nIndex [in] 设置的索引。
	//! \param pntAnchor [in] 锚点。
	//! \param subText [in] 文本子对象。
	//! \return 返回true。
	UGbool SetSub(UGint nIndex, const UGPoint3D& pntAnchor, const UGSubText3D& subText);	
	
	//! \brief 得到文本子对象
	//! \param nIndex [in] 位置索引。
	//! \return 返回文本子对象。
	const UGSubText3D& GetSub(UGint nIndex) const {return m_SubTexts[nIndex];}	
	
	//! \brief 得到文本子对象
	//! \param nIndex [in] 位置索引。
	//! \return 返回文本子对象。
	UGSubText3D& GetSub(UGint nIndex) {return m_SubTexts[nIndex];}

	//! \brief 得到文本子对象的锚点。
	//! \param nIndex [in] 要得到子对象的位置索引。
	//! \return 返回锚点坐标置。
	const UGPoint3D& GetSubAnchor(UGint nIndex) const {return m_Points[nIndex];}	
	
	//! \brief 得到文本子对象的锚点。
	//! \param nIndex [in] 要得到子对象的位置索引。
	//! \return 返回锚点坐标置。
	UGPoint3D& GetSubAnchor(UGint nIndex) {return m_Points[nIndex];}
	
	//! \brief 设置文本风格
	//! \param textStyle [in] 文本风格。
	void SetTextStyle(const UGTextStyle& textStyle);	
	
	//! \brief 得到文本风格。
	//! \return 返回文本风格。
	const UGTextStyle& GetTextStyle() const;	
	
	//! \remarks 
	//! 1) 去掉前后的 空格/回车换行/Tab 等字符
	//! 2) 中间的 空格/回车换行/Tab , 如果前后是 中文/日文 等, 也去掉
	//! 3) 如果前后都是 英文(or数字等ACSII码), 则 保留一个空格(回车换行/Tab等也转换为一个空格)
	//! 原因: 这个接口就是用来 进行 字符串比较查询的, 如 整个文本数据集都 ToString 后, 
	//! 保存到文本字段中, 然后 用户就可以很方便的 在字段中进行 查找, 
	//! 如 在图形显示上 需要 写成" I am   \r\n a student.   ", 但 用户在属性表中查询时, 
	//! 只需要 输入 "I am a student.", 达到所想即所得 的效果
	//!	如:　" I am   \r\n a student.   " 变为 "I am a student."
    //!					 "Hello, \r中国 "  			  变为 "Hello,中国"
    //!					 "Abc\rABC"					  变为 "Abc ABC"
	//! \return 返回文本对象的合并结果
	//! \brief 取得文本对象的索引串(所有的子对象的文字串的合并,去掉空格、换行等)
	UGString GetIndexString() const;	

	//! \brief 获取数据存储时的大小
	//! \return 返回存储大小
	//! \remarks 暂未考虑编码情况，与SaveGeoData()一起维护
	//! \attention 字符串的长度要+4
	virtual UGint GetDataSize() const;
	

public:
	
	//! \brief 得到维度
	//! \return 点为0维, 线/曲线等为1维, 面/曲面等为2维, GeoCompound/GeoText等为-1
	virtual UGint GetDimension() const;
	
	//! \brief 得到内点（在Geometry内部，靠近中央的点）
	//! \return 返回内点
	//! \remarks 为点数最多的子对象 的中间点(中间个数的点, 而不是中间距离的点)
	virtual UGPoint2D GetInnerPoint() const;
	
	//! \brief 得到内点（可能是Geometry3D的质点）
	//! \return 返回内点
	virtual UGPoint3D GetInnerPoint3D() const;
	
	//! \brief 点击测试, 用于对象点选
	//! \param pntHitTest [in] 用来测试选中的点
	//! \param dTolerance [in] 容限
	//! \return 选中返回true, 否则返回false
	virtual UGbool HitTest( const UGPoint2D &pntHitTest, UGdouble dTolerance) const;
	
	//! \brief 几何对象是否有效
	//! \return 有效返回true,无效返回false
	virtual UGbool IsValid() const;

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

	//获取几何体位置
	virtual UGPoint3D GetPosition() const;

	
public:
	//Projection..
	
	//! \brief 根据投影转化器的设置和转化方向要求, 进行投影转化
	//! \param pPJTranslator [in] 投影转化器
	//! \param bForward [in] 转化方向, true代表从UGRefTranslator的源(Src)转化到目的(Des), false则相反
	virtual void PJConvert( UGRefTranslator *pPJTranslator, UGbool bForward = true);
	
	//! \brief 从经纬坐标系统转化为投影坐标系统
	//! \param pCoordSys [in] 投影坐标系统
	virtual void PJForward( UGPrjCoordSys *pCoordSys );
	
	//! \brief 从投影坐标系统转化为经纬坐标
	//! \param pCoordSys [in] 投影坐标系统
	virtual void PJInverse( UGPrjCoordSys *pCoordSys );
	
	//! \brief 根据索引拿到子对象定位点
	//! \return 三维点。
	UGPoint3D GetSubPointAt(UGint i) const;

private:
	//! \brief 计算一个子对象的Bounds
	//! \param nSubIndex [in] 子对象索引。
	//! \param bConsiderRotation [in] 是否考虑旋转。
	//! \param bAlignOffset [in] 是否考虑Align == 3,4,5 时, 文本显示位置的偏移。
	//! \return 返回按要求计算后的Bounds。
	UGRect2D ComputeSubBounds(UGint nSubIndex, 
		UGbool bConsiderRotation=true, UGbool bAlignOffset=false) const;
	
	//! \brief 计算文本的Bounds（参数已经提供足够多的信息）
	//! \param strText [in] 字符对象。
	//! \param dFontHeight [in] 字体的高。
	//! \param dFontWidth [in] 字体的宽。
	//! \param pntAnchor [in] 锚点。
	//! \param nAlign [in] 对齐方式。
	//! \param dRadian [in] 单位是弧度。
	//! \param bAlignOffset [in] 是否考虑文本对齐方式带来的偏移。
	//! \return 文本的Bounds。
	static UGRect2D ComputeTextBounds(const UGString& strText,
		UGdouble dFontHeight, UGdouble dFontWidth, 
		const UGPoint3D& pntAnchor, 
		UGint nAlign, UGdouble dRadian=0, UGbool bAlignOffset=false);

	//! \brief 得到最长一行的字符个数,  和整个字符串的行数
	//! \param strText [in] 字符对象。
	//! \return 返回值:	UGSize::cx = 最长一行的字符个数
	//!					UGSize::cy = 整个字符串的行数	
	static UGSize GetTextSize(const UGString& strText);	


private: //! 内部地理数据
	
	//! \brief 文本头
	UGTextStyle m_textStyle;
	
	//! \brief 子对象定位点
	UGArray<UGPoint3D> m_Points;
	
	//! \brief 子对象数组
	UGArray<UGSubText3D> m_SubTexts;

};

}

#endif // !defined(AFX_UGGEOTEXT3D_H__2D5F3146_41B7_47C7_BAE2_D21CFFCCB499__INCLUDED_)

