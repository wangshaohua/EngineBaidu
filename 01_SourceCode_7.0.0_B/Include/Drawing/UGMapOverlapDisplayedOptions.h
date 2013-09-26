// UGMapOverlapDisplayedOptions.h: interface for the UGMapOverlapDisplayedOptions class.
//
//////////////////////////////////////////////////////////////////////

/*!
   **************************************************************************************
    \file     UGMapOverlapDisplayedOptions.h
   **************************************************************************************
    \author   周萍
    \brief    地图对象过滤显示选项类                                                             
    \attention   
   ----------------------------------------------------------------------------------<br>
    Copyright (c) 2000-2010 SuperMap Software Co., Ltd.                           <br>
    All Rights Reserved.                                                             <br>
   ----------------------------------------------------------------------------------<br> 
   
   **************************************************************************************
    \version 2012-03-7  周萍    初始化版本.                                       <br>
   **************************************************************************************
*/
#if !defined(AFX_UGMAPOVERLAPDISPLAYEDOPTIONS_H__DC6194D6_CDEC_4A74_8522_AC23C8C202F5__INCLUDED_)
#define AFX_UGMAPOVERLAPDISPLAYEDOPTIONS_H__DC6194D6_CDEC_4A74_8522_AC23C8C202F5__INCLUDED_

#include "Stream/ugexports.h"
#include "Stream/ugdefs.h"

namespace UGC {

class UGGeoText;
class UGGeoCompound;
class UGDrawing;
class UGTextStyle;
class UGGeoPoint;

class DRAWING_API UGMapOverlapDisplayedOptions  
{
public:
	enum UGOverlayType
	{
		UG_Type_Text, 
		UG_Type_GraduatedSymbol,	
		UG_Type_Graph,
		UG_Type_Point,
		UG_Type_PointWithLabel
	};

public:
	UGMapOverlapDisplayedOptions();

#ifdef SYMBIAN60
	~UGMapOverlapDisplayedOptions();
#else
	virtual ~UGMapOverlapDisplayedOptions();
#endif

	UGMapOverlapDisplayedOptions& operator = (const UGMapOverlapDisplayedOptions& mapOverlapDisplayedOptions);

public:
	//获取文本重叠时是否显示对象
    UGbool GetIsAllowTextOverlap() const;

	//设置文本重叠时是否显示对象
	void SetIsAllowTextOverlap(UGbool value);

	//获取点重叠时是否显示对象
	UGbool GetIsAllowPointOverlap() const;

	//设置点重叠时是否显示对象
	void SetIsAllowPointOverlap(UGbool value);

	//获取标签和点是否压盖过滤显示
	UGbool GetIsAllowTextAndPointOverlap() const;

	//设置标签和点是否压盖过滤显示
	void SetIsAllowTextAndPointOverlap(UGbool value);

	//获取标签和相应普通图层上的点是否一起过滤显示
	UGbool GetIsAllowPointWithTextDisplay() const;

	//设置标签和相应普通图层上的点是否一起过滤显示
	void SetIsAllowPointWithTextDisplay(UGbool value);

	//获取等级符号元素重叠时是否显示对象
	UGbool GetIsAllowThemeGraduatedSymbolOverlap() const;

	//设置等级符号元素重叠时是否显示对象
	void SetIsAllowThemeGraduatedSymbolOverlap(UGbool value);

	//获取统计专题图元素重叠时是否显示对象
	UGbool GetIsAllowThemeGraphOverlap() const;

	//设置统计专题图元素重叠时是否显示对象
	void SetIsAllowThemeGraphOverlap(UGbool value);

	//获取重叠间距，单位为0.1毫米
	UGSize2D GetOverlappedSpaceSize() const;

	//设置重叠间距，单位为0.1毫米
	void SetOverlappedSpaceSize(UGSize2D value);

	//! \brief 导出成XML
	UGString ToXML() const;
	//! \brief 读取XML信息
	UGbool FromXML(const UGString& strXML);

	// 过滤文本使用  //modified by dongfei 2007-04-11 添加两个参数 一个传缓冲距离，一个传是否强行加入此文本范围
	//! \brief 判断是否压盖图层文本对象
	//! \param pText 要判断的文本的对象
	//! \param bThemeStyle 是否为标签专题图
	//! \param szBuffer 缓冲距离 
	//! \param bSingleTextStyle 是否和当前是一样的文本样式 
	//! \param bSelfOverlap 是否自压盖 
	//! \param bOverlapBounds 是否与图层边界相交 
	//! \return 是否压盖文本对象 
	//! \remarks 避让规则：1.标签和标签，统计图和统计图（不含文本下）进行避让：先判断指定风格下是否有压盖问题，如果有压盖则后绘制的避让已绘制的，先选择优先级高的避让位置，如果可以避让则以此位置进行绘制，如果遍历结束无法避让则进行压盖过滤处理；2.统计图和统计图（含文本情况下）：如果是图形之间的压盖问题则按照规则1进行统计图和统计图避让处理，如果是图形和文本的压盖则允许此种压盖，仍然显示，如果是文本和文本之间的压盖，则按照规则1进行文本和文本避让处理；3.统计图和标签进行避让：如果图形和标签有压盖则允许压盖下显示，如果是统计图中的文本和标签压盖，则按照规则1进行文本和文本的避让处理；4.统计图支持图形避让文本接口开启下：在此种条件下，如果统计图图形压盖文本，则统计图进行避让处理，如果无法避让则不显示，如果是文本压盖图形则允许压盖，仍然显示，其他情况遵循前3条规则
	UGbool	IsOverlapText(UGDrawing* pDrawing, UGGeoText* pText, UGbool bThemeStyle = false,UGSize2D szBuffer = UGSize2D(-1.0,-1.0),
		UGbool bSingleTextStyle = true, UGbool bSelfOverlap = false,UGbool bOverlapBounds = false);
	//! \brief 判断是否压盖图层文本对象
	//! \param UGGeoCompound 要判断的复合对象
	//! \param bThemeStyle 是否为标签专题图
	//! \param bOverlapBounds 是否与图层边界相交 
	//! \return 是否压盖文本对象 
	UGbool	IsOverlapText(UGDrawing* pDrawing, UGGeoCompound* pGeoCompound, UGbool bThemeStyle = false, UGSize2D szBuffer = UGSize2D(-1.0,-1.0), UGbool bOnlyText = true, UGbool bOverlapBounds = false);
	//! \brief 判断点符号是否压盖其他点符号以及文本对象
	//! \param pRect 要判断的点对象的逻辑范围
	//! \param szBuffer 缓冲区距离
	//! \return 是否压盖
	UGbool IsOverlapPointAndText(UGDrawing* pDrawing,UGRect* pRect,UGSize szBuffer = UGSize(-1,-1));
	//! \brief 判断矩形对象是否压盖图层文本对象
	//! \param pRect 要判断的矩形对象
	//! \param szBuffer 缓冲区距离
	//! \return 是否压盖文本对象 
	UGbool	IsOverlapText(UGDrawing* pDrawing, UGRect* pRect,UGbool& bTextOverlap,UGSize szBuffer = UGSize(-1,-1));
	//! \brief 判断矩形对象是否压盖图层文本对象
	//! \param pRect 要判断的矩形对象
	//! \param szBuffer 缓冲区距离
	//! \return 是否压盖文本对象 
	//! \remarks 对于统计图的避让，如果统计图和统计图压盖,则会过滤后画，如果统计图不显示文字，则标签和统计图即使压盖也仍显示，如果统计图中的文字部分和标签压盖则会过滤统计图文字
	//!          此函数主要用于处理等级符号专题图的压盖问题，如果使用统计专题图的，就会可能因为先绘制统计专题图而把等级符号专题图省略不绘
	UGbool	IsOverlapGraduateText(UGDrawing* pDrawing, UGRect* pRect,UGbool& bTextOverlap,UGSize szBuffer = UGSize(-1,-1));
	//! \brief 添加一个文本对象的四个边角到绘制到屏幕的文本数组m_arrTextVertexs中
	//! \param pText 要添加的文本对象
	//! \param bThemeStyle 是否为标签专题图
	//! \param szBuffer 缓冲区距离
	void AddTextVertexs(UGDrawing* pDrawing, UGGeoText* pText, UGbool bThemeStyle = false,UGSize2D szBuffer = UGSize2D(-1.0,-1.0));
	//本来想把IsOverlapText和AddTextVertexs函数中求子文本的四个边角抽象出来 发现还是有些麻烦 稍后再做
	//UGbool  GetSubTextVertexs(UGSubText* pSubText,const UGPoint2D& pntAnchor, UGArray<UGPoint>& pnts);
	//! \brief 移除屏幕的文本数组的内容
	void RemoveAllTextVertexs();

	//! \brief 打格子，缩小避让比较范围
	void GridTextVertexs(UGDrawing* pDrawing);
	//! \brief 求为了使目标矩形与源矩形不相交，目标矩形需偏移的大小(如果目标矩形是文本对象还需要考虑对齐方式)
	UGSize2D GetOverlapOffsetSize(const UGRect2D& sourceRect, const UGRect2D& targetRect, UGdouble dTolerance = 0.0, UGbool bTargetText = false, UGbyte nTextAlign = 0);

	void AddVertexs(UGDrawing* pDrawing, UGRect* pRect, UGMapOverlapDisplayedOptions::UGOverlayType overlapType);
	//! \brief 求矩形是压盖其他相关对象
	//! \param rectOrigin 要判断的矩形对象，为旋转水平之后的矩形
	//! \param overlapType 压盖类型
	//! \param dAngle 矩形的角度
	//! \return 是否压盖相关对象 
	UGbool IsOverlap(UGDrawing* pDrawing,UGRect& rectOrigin, UGMapOverlapDisplayedOptions::UGOverlayType overlapType,
		UGSize2D szBuffer = UGSize2D(0,0), UGdouble dAngle = 0, UGPoint pntLogAnchor = UGPoint(0,0));

	//! \brief 获取hashcode
	UGint GetHashCode() const;

private:
	//文本重叠时是否显示对象，默认为false
	UGbool m_bAllowTextOverlap; 

	//获取或设置点重叠时是否显示对象，默认为true。（针对所有点数据集和所有点数据集的单值、分段、自定义专题图）
	UGbool m_bAllowPointOverlap; 

	//获取或设置标签和点是否压盖过滤显示，默认为true。
	UGbool m_bAllowTextAndPointOverlap; 

	//获取或设置标签和相应普通图层上的点是否一起过滤显示，默认为false。
	//如果过滤显示，只以图层集合中对应数据集的索引最小的图层的点风格来绘制点
	UGbool m_bAllowPointWithTextDisplay; 

	//获取或设置等级符号元素重叠时是否显示对象，默认为true
	UGbool m_bAllowThemeGraduatedSymbolOverlap;

	//获取或设置统计专题图元素重叠时是否显示对象，默认为true
	UGbool m_bAllowThemeGraphOverlap; 

	//获取或设置重叠间距，单位为0.1毫米。
	//为正数时表示两个对象之间的距离，超出距离的显示，小于等于该距离的不显示。
	//为负数时表示两个对象的重叠距离，小于该距离的绝对值时显示，大于等于该距离的绝对值时不显示
	UGSize2D m_szOverlappedSpace; 

	//显示在屏幕上的文字的屏幕顶点座标
	//! \brief 存储标签专题图坐标
	//UGArray<UGPoint> m_arrTextVertexs;
	//把显示在屏幕上的文字的屏幕顶点坐标分成格网
	UGArray<UGPoint>** m_arrGridTextVertexs;
	UGint m_nGridRowCount;
	UGint m_nGridColCount;
	//! \brief 格网大小
	UGint m_nGridWidth;
	//! \brief 存储统计专题图坐标
	UGArray<UGPoint>** m_arrGridGrphVertexs;
	//! \brief 存储等级符号专题图坐标
	UGArray<UGPoint>** m_arrGridGraduatetexts;
	//! \brief 保存等级符号的缓冲范围,在显示等级符号后,如果存在统计符号时,就要还原这个缓冲范围,因为本来可以绘制的统计就不能显示了
	UGArray<UGSize>  m_arrBufferSize;
	//! \brief 存储点点压盖过滤时的点坐标
	UGArray<UGPoint>** m_arrGridPointVertexs;
	//! \brief 存储点和标签一起压盖过滤时的点坐标(此字段中的点不和m_arrPointVertexs中的坐标重复)
	UGArray<UGPoint>** m_arrGridPointVertexsWithLabel;

	void ComputerRegionRowCol(UGDrawing* pDrawing, UGPoint2D pPntPolygon[], UGint nCount, UGint& nMinCol,UGint& nMaxCol,UGint& nMinRow,UGint& nMaxRow);

	// 为了过滤文本使用
	UGbool IsOverlapRects(const UGPoint* pPntObliqueRect, const UGRect& rect)const;
	UGint IsPointInRect(const UGPoint& Pnt, const UGRect& rect)const;
	UGint IsPointInObliqueRect(const UGPoint& pnt, const UGPoint* pPntObliqueRect)const;
	void GetPntPolygonOfText(UGDrawing* pDrawing,UGGeoText* pGeoText, UGint nSubIndex, UGTextStyle& textStyle, 
							UGSize2D& szBuffer, UGPoint2D* pPntPolygon, UGint nLength, UGRect* pNotRotatedRect = NULL);
	void AddVertexs(UGDrawing* pDrawing, UGPoint2D* pPntPolygon, UGMapOverlapDisplayedOptions::UGOverlayType overlapType);
};

}

#endif // !defined(AFX_UGTRACKINGLAYER_H__DC6194D6_CDEC_4A74_8522_AC23C8C202F5__INCLUDED_)