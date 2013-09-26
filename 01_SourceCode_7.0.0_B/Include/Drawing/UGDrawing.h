// UGDrawing.h: interface for the UGDrawing class.
//
//////////////////////////////////////////////////////////////////////

/*!
   **************************************************************************************
    \file     UGDrawing.h
   **************************************************************************************
    \author   张艳良、陈国雄
    \brief    显示类                                                                 
    \attention   
   ----------------------------------------------------------------------------------<br>
    Copyright(c) 2000-2010  SuperMap GIS Technologies,Inc.                           <br>
    All Rights Reserved.                                                             <br>
   ----------------------------------------------------------------------------------<br> 
   
   **************************************************************************************
    \version 2005-06-09  陈国雄    初始化版本.                                       <br>
   **************************************************************************************
*/

#if !defined(AFX_UGDRAWING_H__AAC47E2E_B5B6_476C_9462_FBF34F02DFF5__INCLUDED_)
#define AFX_UGDRAWING_H__AAC47E2E_B5B6_476C_9462_FBF34F02DFF5__INCLUDED_

#include "Drawing/UGDrawCache.h"
#include "Drawing/UGDrawParamaters.h"
#include "Drawing/UGDrawMaker.h"
#include "Engine/UGDataSource.h"
#include "Stream/ugplatform.h"
#include "Toolkit/UGProgress.h"
#include "Drawing/UGMakerCache.h"

namespace UGC {	

typedef void (UGSTDCALL *DRAWPAINTPROC)(UGGraphics* pGraphics, UGlong pPaintWnd);

// by zengzm 2007-3-26 把__stdcall定义到ugplatform中
typedef void (UGSTDCALL *DRAWCALLBACKPROC)(UGint nPercent, UGbool &bCancel, UGlong pWnd);
typedef void (UGSTDCALL *REFRESHCALLBACKPROC)(UGlong pWnd);

typedef void (UGSTDCALL *REPAINTCALLBACKPROC)(UGlong pWnd);
typedef void (UGSTDCALL *REFRESHMAPCALLBACKPROC)(UGdouble dMapScale, const UGRect2D &rcBounds, UGlong pWnd);
typedef void (UGSTDCALL *THREADCALLBACKPROC)(UGlong pWnd);
typedef void (UGSTDCALL *THREADCANCALECALLBACKPROC)(UGlong pWnd);
//#ifdef WIN32
//typedef void (__stdcall *DRAWCALLBACKPROC)(UGint nPercent, UGbool &bCancel, UGuint pWnd);
//#else
//typedef void (*DRAWCALLBACKPROC)(UGint nPercent, UGbool &bCancel, UGuint pWnd);
//#endif
//added by xielin 2007-04-30 
//! \brief 回调函数，用于扩展对象绘制
//! \param 		pGraphics		当前绘制的Graphics，用于在该Graphics上绘制对象
//! \param 		pGeometry		扩展对象
//! \param 		pWnd			实现该回调函数对象的指针
typedef void (UGSTDCALL *DRAWCUSTOMGEOMETRYCALLBACKPROC)(UGGraphics* pGraphics,UGGeometry* pGeometry,UGlong pWnd);

//! \brief AfterPointInput 定时器控制回调函数
typedef void (UGSTDCALL *StartTimerProc)(UGlong pWnd, UGint nIDEvent);
typedef void (UGSTDCALL *StopTimerProc)(UGlong pWnd, UGint nIDEvent);

class UGGeoPoint;
class UGGeoLine;
class UGGeoRegion;
class UGGeoText;
class UGGeoCompound;	
class UGGeoLineM;	
class UGGeoMultiPoint;
class UGMakerCache;

// addey by macx 2008.7.31 。
//! \brief 输出成PDF的风格选项 
//! \remarks 备注信息。
enum UGOutputStyle
{
		UG_STYLE_NOSTYLE					=   0x00000000, //没有任何风格,为0
		UG_STYLE_POINT						=	0x00000001,	//是否含点符号1
		UG_STYLE_LINE						=	0x00000002,	//是否含线符号2
		UG_STYLE_REGON						=	0x00000004,	//是否是否含面符号4
		UG_STYLE_ALLSTYLE					=	0x00000007,	//正常输出,带有全部风格 1 + 2 + 4 = 7
};

typedef OGDC::PixelFormat UGPixelFormat;

struct DRAWING_API UGRasterStretchOption
{
	enum StretchType
	{
		none					= 0,
		StandardDeviation		= 1,
		MinimumMaximum			= 2,
		HistogramEqualization = 3,
		HistogramSpecification = 4,
		Gaussian = 5
	};

	// 拉伸方式
	StretchType	eType;

	// 标准差拉伸参数
	UGdouble	dDevParam;

	// 直方图规定化参数
	UGArray<UGHistogram> arrStandardHistogram;

	// 高斯拉伸参数
	UGdouble	dGaussianRatio;
	UGbool		isGaussianMid;

	UGRasterStretchOption()
	{
		eType = none;
		dDevParam = 2.0;

		dGaussianRatio = 2.0;
		isGaussianMid = true;
	}

};

class DRAWING_API UGDrawing  
{
public:
	UGDrawing();

#ifdef SYMBIAN60
	~UGDrawing();
#else
	virtual ~UGDrawing();
#endif

public:
	//! \brief 绘制几何对象
	//! \param pGeometry 几何对象
	//! \return 绘制是否成功
	UGbool Draw(UGGeometry* pGeometry);
	//! \brief 绘制文本
	//! \param UGGeoText 文本对象
	//! \param bThemeStyle 是否是标签样式
	//! \param bSingleTextStyle 是否绘制传入的文本对象自己的风格
	//! \return 绘制是否成功
	UGbool Draw(UGGeoText* pGeoText, UGbool bThemeStyle, UGbool bSingleTextStyle = true);
    //! \brief 绘制数据集
	//! \param pDataset 文本对象
	//! \param nTransparentRate 透明度
	//! \param UGProgress 进程条类
	//! \return 绘制是否成功
	UGbool Draw(UGDataset* pDataset, UGProgress* pProgress = NULL);
	  
	//! \brief 获取文本风格
	//! \return 文本风格 
	UGTextStyle GetTextStyle() const;
    //! \brief 几何对象风格
	//! \return 几何对象风格 
	UGStyle GetStyle() const;
	//! \brief 设置几何对象风格
	//! \return 返回旧的几何对象风格 
	//! \remarks 尽量不要使用该函数，该函数只修改符号样式，推荐使用Prepare函数
	void SetStyle(const UGStyle& style);
	//! \brief 设置当前显示对象
	//! \param style 设置几何类对象风格
	//! \param nDimesion 集合对象的维数
	//! \return 当前的显示尺寸
	UGbool Prepare(const UGStyle& style, const UGint nDimesion);
	//! \brief 设置当前显示对象
	//! \param style 设置几何类对象风格
	//! \param nDimesion 集合对象的维数
	//! \设置是否成功 当前的显示尺寸
	UGbool Prepare(const UGTextStyle& style, UGbool bThemeStyle = FALSE);
	//! \brief 释放当前对象
	void Release();
	//! \brief 获取Graphics对象
	//! \return 返回Graphics对象
	UGGraphics* GetGraphics() const;
	//! \brief 设置Graphics对象
	//! \param pGraphics 要设置的Graphics对象 
	//! \return 返回旧的Graphics对象
	UGGraphics* SetGraphics(UGGraphics* pGraphics);
	//! \brief 计算开始绘制的时间
	//! \param pGraphics 使用的Graphics对象。
	void BeginCalculateTime(UGGraphics* pGraphics);
	//! \brief 计算结束绘制的时间
	void EndCalculateTime();
	//! \brief 判断是否开始绘制
	//! \return 是否开始绘制
	UGbool IsBeginCalculateTime();
	//! \brief 刷新图层
	void OvertimeRefresh();
	//! \brief  显示中断和显示刷新消息
	UGbool DrawCallBack();
	//! \brief 在Graphics图层绘制对象
	//! \param  Graphics图层绘制对象
	void OnPaint(UGGraphics* pGraphics);

	UGbool RefreshCallBack();
	UGbool RePaintCallBack();
	UGbool RefreshMapCallBack(UGdouble dMapScale, const UGRect2D &rcBounds);
	void ThreadCallBack();
	void ThreadCancleCallBack();
	//! \brief 设置扩展对象绘制函数
	//! \param pDrawCustomGeometryFunc 设置扩展对象的函数指针
	//! \param pWnd 函数指针的Hand 
	void SetDrawCallBackFunc(DRAWCALLBACKPROC pDrawCallBackFunc, UGlong pWnd);
    //! \brief 设置扩展对象绘制函数
	//! \param pDrawCustomGeometryFunc 设置扩展对象的函数指针
	//! \param pWnd 函数指针的Hand 
	void SetDrawPaintFunc(DRAWPAINTPROC pDrawPaintFunc, UGlong pPaintWnd);
	//added by xielin 2007-04-30 
    //! \brief 设置扩展对象绘制函数
	//! \param pDrawCustomGeometryFunc 设置扩展对象的函数指针
	//! \param pWnd 函数指针的Hand 
	void SetDrawCustomGeometryFunc(DRAWCUSTOMGEOMETRYCALLBACKPROC pDrawCustomGeometryFunc,
		UGlong pWnd);

	void SetRefreshCallBackFunc(REFRESHCALLBACKPROC pRefreshCallBackFunc, UGlong pWnd);
	void SetRePaintCallBackFunc(REPAINTCALLBACKPROC pRePaintCallBackFunc, UGlong pWnd);
	void SetRefreshMapCallBackFunc(REFRESHMAPCALLBACKPROC pRefreshMapCallBackFunc, UGlong pWnd);
	void SetThreadCallBackFunc(THREADCALLBACKPROC pThreadCallBackFunc, UGlong pWnd);
	void SetThreadCancleCallBackFunc(THREADCANCALECALLBACKPROC pThreadCancaleFunc,UGlong pWnd);

	//! \brief 上层定时器回调函数
	void SetStartTimerFunc(StartTimerProc pStartTimerFunc, UGlong pWnd);
	void SendStartTimer(UGint nIDEvent);
	void SetStopTimerFunc(StopTimerProc pStopTimerFunc, UGlong pWnd);
	void SendStopTimer(UGint nIDEvent);

	//added by macx 2008.8.1。
	//! \brief 设置输出PDF的风格 
	//! \param nStyle 风格选项[in]。
	//! \return 。
	//! \remarks 。
	//! \attention 。
	void SetOutputToPDFStyle(UGint nStyle);
	
	//! \brief 判断某点是否在文本对象中
	//! \param pGeoText 文本对象
	//! \param pntHitTest 要判断的点
	//! \return 是否在文本对象中
	static UGbool HitTestGeoText(UGGeoText* pGeoText, const UGPoint2D& pntHitTest, UGdouble dTolerance,UGDrawParamaters *pDrawParam);
	//! \brief 判断某点是否在几何点中
	//! \param pGeoText 几何点
	//! \param style 几何对象风格
	//! \param pntHitTest 要判断的点
	//! \return 是否在几何点
	static UGbool HitTestGeoPoint(UGGeoPoint* pGeoPoint, const UGStyle& style, const UGPoint2D& pntHitTest, UGdouble dTolerance, UGDrawing *pDrawing);
	//! \brief 获得的文本对象大小
	//! \param pGraphics 绘制的Graphics对象
	//! \param strText 文本对象
	//! \return 文本对象的大小
	static UGSize GetTextSize(UGGraphics *pGraphics, const UGString &strText);
	//! \brief 获得每行的文本对象
	//! \param strText 判断的文本
	//! \param strRows 分割后的文本
	//! \return 文本的大小，UGSize.cx 所有行的最多文本数 UGSize.cy 文本行数
	static UGSize GetRowStrings(const UGString &strText, UGArray<UGString> &strRows);
	//! \brief 计算文本的逻辑边界
	//! \param pGraphics 绘制的Graphics对象
	//! \param pntAnchor 文本的基点
	//! \param strText  计算的文本
	//! \param btAlign 文本的对齐方式
	//! \return 文本的逻辑边界
	static UGRect CalcTextLogBounds(UGGraphics *pGraphics, const UGPoint& pntAnchor, const UGString& strText, UGbyte btAlign);
	//! \brief 获得文本的行数
	//! \param strText 文本对象
	//! \return 文本行数
	static UGint CalcTextRowCount(const UGString &strText);

	//! \brief 获取文本左上角坐标 added by dongfei 2007-03-21
	UGbool GetTextLeftTop(UGPoint & pntAnchor1, const UGString & strText, const UGTextStyle & style);
	//! \brief 获取文本中心坐标
	UGbool GetTextCenter(UGPoint & pntAnchor1, const UGString & strText, const UGTextStyle & style);
	//! \brief 获取等级符号范围数组的大小，根据数量用于判断等级符号在避让时调用的函数

public:
	//! \brief 绘制的基本函数
	//! \brief 绘制点
	//! \param point 要绘制的点
	//! \return 绘制是否成功
	UGbool Point(const UGPoint& point);
	//! \brief 绘制点
	//! \param x 要绘制的点x坐标
    //! \param y 要绘制的点y坐标
	//! \return 绘制是否成功
	UGbool Point(UGint x, UGint y);

	//{{ add by xiaoys 2012-0626 跟踪层绘制符号用
	//! \brief 画符号点
	//! \param pntPos 点的逻辑坐标
	//! \param iMarkID 符号ID
	//! \如果成功返回true，失败返回false
	UGbool Point(const UGPoint& pntPos, UGint iMarkID);
	//}} add by xiaoys 2012-0626 跟踪层绘制符号用

	//! \brief 画多个多边形区域
    //! \param pPoints 多边形的点列指针
	//! \param pPntCount 每个多边形的点数
	//! \param nCount 多边形的个数
	//! \return 如果成功返回TRUE,失败返回FALSE
	UGbool PolyPolygon(const UGPoint* pPoints, const UGint* pPntCount, UGint nCount);

	//! \brief 画一个文本对象
	//! \param UGPoint 文本基点
	//! \param str 文本
	//! \param style 文本风格
	//! \param bThemeStyle 是否是标签样式
	//! \param bSingleTextStyle 是否和当前图层是同一个文本形式
	//! \return 绘制是否成功
	UGbool Text(const UGPoint &pnt, const UGString &str, const UGTextStyle &style, UGbool bThemeStyle = FALSE,UGbool bSingleTextStyle = true);

	//! \brief 画一条折线
    //! \param pPoints 折线的点列指针
	//! \param nCount 有多少个点
	//! \return 如果成功返回TRUE,失败返回FALSE
	UGbool Polyline(const UGPoint* pPoints, UGint nCount);
	//! \brief 画多个折线
    //! \param pPoints 多条折线的点列指针
	//! \param pPntCount 每个折线的点数
	//! \param nCount 折线的个数
	//! \return 如果成功返回TRUE,失败返回FALSE
	UGbool PolyPolyline(const UGPoint* pPoints, const UGint* pPntCount, UGint nCount);
   //! \brief 画一个多边形区域
    //! \param pPoints 多边形的点列指针
	//! \param nCount 有多少个点
	//! \return 如果成功返回TRUE,失败返回FALSE
	UGbool Polygon(const UGPoint* pPoints, UGint nCount);
	//! \brief 画矩形
	//! \param x1 矩形的左上角的X坐标 
    //! \param y1 矩形的左上角的Y坐标 
	//! \param x2 矩形的右下角的X坐标
	//! \param y2 矩形的右下角的Y坐标
	//! \return 返回绘图是否成功
	UGbool Rectangle(UGint x1, UGint y1, UGint x2, UGint y2);
	//! \brief 画矩形
	//! \param rect 需要绘制的矩形 
	//! \return 返回绘图是否成功
	UGbool Rectangle(const UGRect& rect);
	//! \brief 画椭圆
	//! \param x1 绘制的矩形的左上角的X坐标 
    //! \param y1 绘制的矩形的左上角的Y坐标 
	//! \param x2 绘制的矩形的右下角的X坐标
	//! \param y2 绘制的矩形的右下角的Y坐标
	//! \return 返回绘图是否成功
	UGbool Ellipse(UGint x1, UGint y1, UGint x2, UGint y2);
	//! \brief 画椭圆
	//! \param rect 绘制的矩形 
	//! \return 返回绘图是否成功
	UGbool Ellipse(const UGRect& rect);

	//! \brief    画弧线
	//! \param x1 绘制的矩形的左上角的X坐标 
    //! \param y1 绘制的矩形的左上角的Y坐标 
	//! \param x2 绘制的矩形的右下角的X坐标
	//! \param y2 绘制的矩形的右下角的Y坐标
	//! \param x3 弧线起始射线点 
	//! \param y3 弧线结束射线点
	//! \return 返回绘图是否成功
	UGbool Arc(UGint x1, UGint y1, UGint x2, UGint y2, UGint x3, UGint y3, UGint x4, UGint y4);
	//! \brief    画弧线
	//! \param pntStart 弧线起始射线点 
	//! \param pntEnd 弧线结束射线点
	//! \return 返回绘图是否成功
	UGbool Arc(const UGRect& rect, UGPoint pntStart, UGPoint pntEnd);
	//! \brief    画弓形
	//! \param x1 绘制的矩形的左上角的X坐标 
    //! \param y1 绘制的矩形的左上角的Y坐标 
	//! \param x2 绘制的矩形的右下角的X坐标
	//! \param y2 绘制的矩形的右下角的Y坐标
	//! \param x3 弓形起始射线点 
	//! \param y3 弓形结束射线点
	//! \return 返回绘图是否成功
	UGbool Chord(UGint x1, UGint y1, UGint x2, UGint y2, UGint x3, UGint y3, UGint x4, UGint y4);
//! \brief    画弓形
	//! \param pntStart 弓形起始射线点 
	//! \param pntEnd 弓形结束射线点
	//! \return 返回绘图是否成功
	UGbool Chord(const UGRect& rect, UGPoint pntStart, UGPoint pntEnd);
	//! \brief    画扇形
	//! \param x1 绘制的矩形的左上角的X坐标 
    //! \param y1 绘制的矩形的左上角的Y坐标 
	//! \param x2 绘制的矩形的右下角的X坐标
	//! \param y2 绘制的矩形的右下角的Y坐标
	//! \param x3 扇形起始点 
	//! \param y3 扇形结束点
	//! \return 返回绘图是否成功
	UGbool Pie(UGint x1, UGint y1, UGint x2, UGint y2, UGint x3, UGint y3, UGint x4, UGint y4);
  //! \brief    画扇形
	//! \param pntStart 扇形起始射线点 
	//! \param pntEnd 扇形结束射线点
	//! \return 返回绘图是否成功
	UGbool Pie(const UGRect& rect, UGPoint pntStart, UGPoint pntEnd);
	//! \brief 画圆角矩形
	//! \param x1 绘制的矩形的左上角的X坐标 
    //! \param y1 绘制的矩形的左上角的Y坐标 
	//! \param x2 绘制的矩形的右下角的X坐标
	//! \param y2 绘制的矩形的右下角的Y坐标
	//! \param x3 圆角矩形X轴宽度
	//! \param y3 圆角矩形Y轴宽度
	//! \return 返回绘图是否成功
	UGbool RoundRect(UGint x1, UGint y1, UGint x2, UGint y2, UGint x3, UGint y3);
	//! \brief    画圆角矩形
	//! \param rect 绘制的矩形 
	//! \param point 圆角矩形XY轴宽度
	//! \return 返回绘图是否成功
	UGbool RoundRect(const UGRect& rect, UGPoint point);

	UGbool GetArcPoints(UGRect &rect, UGdouble dAngleStart, UGdouble dAngleEnd, UGArray<UGPoint> &arr);

	static UGbool CalMarkerSymbolBounds(UGPoint2D pntCentroid,UGDrawing* pDrawing,UGStyle& style,UGRect& rcRect);

	//! \brief 地图在打印出图模式下设置是否可以刷新
	void SetOverTimeRefresh(UGbool bOverTimeRefresh);

	//! \brief 判断地图在打印出图模式下是否可以刷新
	UGbool IsOverTimeRefresh(UGbool bOverTimeRefresh);

	//! \brief 控制缩放地图时是否刷新地图
	void SetZoomRefreshFlag(UGbool bRefreshFlag);
	UGbool GetZoomRefreshFlag();

	//! \brief 控制平移缓冲效果(目前网络地图使用)
	void StartBufferPan();
	void StopBufferPan();
	UGbool IsBufferPanning();

	//! \brief 控制布局中图例的绘制(绘制过程中需要特殊处理文字和点符号)
	void SetDrawingGeoLegend(UGbool bDrawingGeoLegend);
	UGbool IsDrawingGeoLegend();

	//! \brief 控制是否异步刷新地图模式
	void SetAsyncMode(UGbool bAsync);
	UGbool IsAsyncMode() const;

	//! \brief 多地图模式(异步模式下把线面和点文字分成两个地图绘制)
	void SetMultiMapMode(UGbool bMultiMap);
	UGbool IsMultiMapMode() const;

	//! \brief 获取地图绘制参数(异步和同步模式是不一样的)
	UGDrawParamaters* GetDrawParamaters();
	UGGraphics* GetDrawGraphics();

	//! \brief 控制是否取消地图绘制(线程安全的)
	void SetCancleDrawFlag(UGbool bCancle);
	UGbool IsCancleDrawFlag();

	UGMakerCache* GetMakerCache();

public:
	//! \brief 地图坐标转换到逻辑坐标(高精度模式)
	//! \param szSource 要转换的坐标
	//! \param szTarget 转换后的坐标
	void MPtoLP(const UGPoint2D& pntSource, UGPoint& pntTarget);
	//! \brief 地图坐标转换到逻辑坐标(高精度模式转换)
	//! \param pPoints 需要转换的点串
	//! \param nCount 点串的个数
	//! \return 转换是否成功
	UGbool MPtoLPBatch(const UGPoint2D* pPoints, UGint nCount);	
	//! \brief 地图坐标转换到逻辑坐标(高精度模式转换)
	//! \param pPoints 点串的指针
	//! \param nCount 点串的几何对象的个数
	//! \param arrPolycounts 每个几何对象的点的个数
	//! \return 转换是否成功
	UGbool MPtoLPBatchPredigest(const UGPoint2D* pPoints, UGint nCount, UGArray<UGuint>& arrPolycounts);

protected:
	UGbool DrawDataset(UGDatasetVector* pDatasetV,UGProgress* pProgress = NULL);
	UGbool DrawDataset(UGDatasetRaster* pDatasetR,UGProgress* pProgress = NULL);
	///////////////////////////////////////////////////////
	// 这一组成员是绘制栅格数据集时需要的
	UGbool PaintRaster(UGint nTransparentRate = 0,UGProgress* pProgress = NULL);
	void PaintImgBegin();
	UGbool PaintImgBlock(UGImgBlock* pIBlock, UGint nTransparentRate);
	UGColor ImageIndexToColor(UGint nColor, const UGPixelFormat& pixelFormat);
	UGbool PaintViewBlock(UGImgBlock* pIBlock);
	///////////////////////////////////////////////////////	

	//////////////////////////////////////////////////////////////////////////
	UGbool PaintDatasetRaster(UGint nTransparentRate, UGProgress* pProgress /*= NULL*/);
	UGbool PaintImgRaster(UGint nTransparentRate, UGProgress* pProgress /*= NULL*/);

	//! \brief 获取显示的影像块。
	//! \param rcView 获取的显示的影像块大小[in]。
	//! \param nDeviceWidth 设备宽度[in]。
	//! \param nDeviceHeight 设备高度[in]。
	//! \return 返回显示的影像块。
	UGArray<UGImgBlock*> GetViewBlock(const UGRect2D& rcView, UGint nDeviceWidth, UGint nDeviceHeight, UGbool &bFinished);

	UGbool PrintViewRaster(const UGRect2D& rcDraw, const UGRect& rcBMP, UGProgress* pProgress);
	UGbool PaintViewRaster(const UGRect2D& rcDraw, const UGRect& rcBMP, UGProgress* pProgress);
	UGbool PaintViewOnePixelRaster(UGbool bPixDrawMode, const UGRect2D& rcDraw, const UGRect& rcImage, UGProgress* pProgress);

	//! \return 创建裁剪区域
	UGRgn* CreateClipRgn(UGGraphics* pGraphics, UGGeoRegion *pClipRegion);

	//! \return 绘制查询出来的ImageBlocks
	UGbool PaintViewImageBlocks(UGArray<UGImgBlock*>& arrImgBlocks);

	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	//! \return 获取栅格数据集的统计值
	UGbool GetRasterStatisticsInfo(UGArray<UGint>& arrBandSelect, UGArray<UGdouble>& arrMaxVal, UGArray<UGdouble>& arrMinVal, UGArray<UGdouble>& arrMeanVal, UGArray<UGdouble>& arrStandardDVal);
	UGbool GetPluginRasterStatisticsInfo(UGArray<UGint>& arrBandSelect, UGArray<UGdouble>& arrMaxVal, UGArray<UGdouble>& arrMinVal, UGArray<UGdouble>& arrMeanVal, UGArray<UGdouble>& arrStandardDVal);

	//! \return 直方图统计
	// 数据集直方图统计，为了保证只统计一次，以后需引擎存储
	UGArray<UGHistogram> CalculateHistogramInfo(UGArray<UGint> arrBandSelect);
	// 影像插件直方图统计
	UGArray<UGHistogram> CalculateImagePluginHistogramInfo(UGArray<UGint> arrBandSelect);

	// 位深相关计算
	UGbool IsSupport(UGPixelFormat ePixelFormat);
	UGint ValueExtent(UGPixelFormat ePixelFormat);

	//! \brief 组合为RGB
	UGbool CompoundColor(UGImgBlock *pDestImgBlock, UGImgBlock *pSrcImgBlock);
	UGbool CompoundColor(UGImgBlock *pResBlock,UGArray<UGImgBlock*>& arrImgBlock,ImgColorSpace nColorSpace);

	//! \brief 计算原始数据拉伸的系数
	UGdouble CalcInterpolationScale(UGImgBlock *pImgBlock, UGdouble &dMaxVal, UGdouble &dMinVal, UGdouble &dMeanVal, UGdouble &dStdVal);
	UGdouble CalcStretchScale(UGImgBlock *pImgBlock, UGdouble &dMaxVal, UGdouble &dMinVal, UGdouble &dMeanVal, UGdouble &dStdVal);
	
	//! \brief 无拉伸
	UGbool NonaStretchImageBlock(UGImgBlock* pImgBlock, UGdouble dMaxVal, UGdouble dMinVal, UGdouble dMeanVal, UGdouble dStdVal);
	UGbool NonaStretchImageBlock(UGImgBlock *pImgBlock, UGArray<UGImgBlock*>& arrImgBlock,ImgColorSpace nColorSpace, UGArray<UGdouble> arrMaxVal, UGArray<UGdouble> arrMinVal, UGArray<UGdouble> arrMeanVal, UGArray<UGdouble> arrStdVal);

	//! \return 标准差拉伸影像块
	UGbool StandardDevStretchImageBlock(UGImgBlock* pImgBlock, UGdouble dMaxVal, UGdouble dMinVal, UGdouble dMeanVal, UGdouble dStandardDVal, UGdouble dDevParam);
	UGbool StandardDevStretchImageBlock(UGImgBlock *pImgBlock, UGArray<UGImgBlock*>& arrImgBlock,ImgColorSpace nColorSpace, UGArray<UGdouble> arrMaxVal, UGArray<UGdouble> arrMinVal, UGArray<UGdouble> arrMeanVal, UGArray<UGdouble> arrStdVal, UGdouble dDevParam);

	//! \brief 最值拉伸
	UGbool MaxMinStretchImageBlock(UGImgBlock *pImgBlock, UGdouble dMaxVal, UGdouble dMinVal, UGdouble dMeanVal, UGdouble dStdVal);
	UGbool MaxMinStretchImageBlock(UGImgBlock *pImgBlock, UGArray<UGImgBlock*>& arrImgBlock,ImgColorSpace nColorSpace, UGArray<UGdouble> arrMaxVal, UGArray<UGdouble> arrMinVal, UGArray<UGdouble> arrMeanVal, UGArray<UGdouble> arrStdVal);

	//! \return 高斯拉伸影像块
	UGbool GaussianStretchImageBlock(UGImgBlock *pImgBlock, UGdouble dMaxVal, UGdouble dMinVal, UGdouble dMeanVal, UGdouble dStandardDVal, UGdouble dRatio, UGbool isMid);
	UGbool GaussianStretchImageBlock(UGImgBlock *pImgBlock, UGArray<UGImgBlock*>& arrImgBlock,ImgColorSpace nColorSpace, UGArray<UGdouble> arrMaxVal, UGArray<UGdouble> arrMinVal, UGArray<UGdouble> arrMeanVal, UGArray<UGdouble> arrStdVal, UGdouble dRatio, UGbool isMid);

	//! \return 直方图均衡拉伸影像块
	UGbool HistogramEquStretchImageBlock(UGImgBlock* pImgBlock, UGdouble dMaxVal, UGdouble dMinVal, UGdouble dMeanVal, UGdouble dStandardDVal, UGHistogram histogram);
	UGbool HistogramEquStretchImageBlock(UGImgBlock *pImgBlock, UGArray<UGImgBlock*>& arrImgBlock,ImgColorSpace nColorSpace, UGArray<UGdouble> arrMaxVal, UGArray<UGdouble> arrMinVal, UGArray<UGdouble> arrMeanVal, UGArray<UGdouble> arrStdVal, UGArray<UGHistogram> arrHistogram);

	//! \return 直方图规定化拉伸影像块
	UGbool HistogramSpcStretchImageBlock(UGImgBlock* pImgBlock, UGdouble dMaxVal, UGdouble dMinVal, UGdouble dMeanVal, UGdouble dStandardDVal, UGHistogram histogram, UGHistogram histogramStandard);
	UGbool HistogramSpcStretchImageBlock(UGImgBlock *pImgBlock, UGArray<UGImgBlock*>& arrImgBlock,ImgColorSpace nColorSpace, UGArray<UGdouble> arrMaxVal, UGArray<UGdouble> arrMinVal, UGArray<UGdouble> arrMeanVal, UGArray<UGdouble> arrStdVal, UGArray<UGHistogram> arrHistogram, UGArray<UGHistogram> arrHistogramStandard);
	//////////////////////////////////////////////////////////////////////////

//{{{added by qianjn in 2009-7-20 16:37:07 增加原因：栅格动态投影

	UGImgBlock* GetFlyPrjImgBlock(UGbool bPrint = FALSE);

//}}added by qianjn in 2009-7-20 16:37:07 增加原因：

	//! \从PaintViewBlock中提取一部分公用的代码到一个函数中，在PaintRaster中会调用到,函数本身没有太多意义，就是为了提取公共代码，方便维护
	//! \根据栅格值获取需要绘制像素的颜色值,适用于DEM、GRID但像素格式不为IPF_MONO的栅格数据集
	UGColor GetPixelColor(UGdouble dValue, UGColorTable *pColorTable, UGint nNoValue, UGint nStylesSize);
	UGColor GetPixelColor( UGdouble dValue, UGColorDictTable *pClrDictTable, UGint nNoValue );

	UGbool DrawString(UGint x, UGint y, const UGString& strText, UGTextStyle textStyle);
	UGbool DrawPointAndCache(const UGPoint& point, UGMarkerSymbol *pMarkerSymbol);
	UGbool DrawImageData(UGImageData* pImageDataDest, UGint x, UGint y, UGint nWidth, UGint nHeight, UGImageData* pImageDataSrc, UGint xSrc, UGint ySrc);

private:
	//! \brief 获取显示的影像块。
	//! \param rcView 获取的显示的影像块大小[in]。
	//! \param nDeviceWidth 设备宽度[in]。
	//! \param nDeviceHeight 设备高度[in]。
	//! \return 返回显示的影像块。
	UGImgBlock* GetRasterBlock(UGDatasetRaster* pDatasetR, const UGRect2D& rcBounds, const UGRect& rcImage);
	//! \brief 获取显示的影像块。
	//! \param rcView 获取的显示的影像块大小[in]。
	//! \param nDeviceWidth 设备宽度[in]。
	//! \param nDeviceHeight 设备高度[in]。
	//! \return 返回显示的影像块。
	UGImgBlock* GetMultiBandRasterBlock(UGDatasetRaster* pDatasetR, const UGRect2D& rcBounds, const UGRect& rcImage);
	UGImgBlock* GetPluginRasterBlock(UGDatasetRaster* pDatasetR, const UGRect2D& rcBounds, const UGRect& rcImage);

private:
	void PaintBlockDataByColorTable( UGImgBlock* pIBlock, UGColorTable *pColorTable, UGint nNoValue, UGint nStylesSize );
	void PaintBlockDataByColorDictTable( UGImgBlock* pIBlock, UGColorDictTable *pColorTable, UGint nNoValue );

private:
	//! \brief 处理imageBlock的颜色改变，包括亮度、对比度以及透明
	void ProcessColorModify(UGImgBlock *pBlock);
	void ProcessColorModify24(UGImgBlock *pBlock);
	void ProcessColorModify32(UGImgBlock *pBlock);
	void ProcessColorModifyOthers(UGImgBlock *pBlock);

	//! \brief 获取单个像素及处理颜色属性，包括亮度、对比度以及透明
	UGColor GetPixelAndProcessColorModify(UGint x, UGint y);

	//! \brief 获取单个像素颜色
	UGColor GetPixel(UGImageData& imageData, UGint x, UGint y);

public:
	//! \brief 保存显示参数
	UGDrawParamaters m_DrawParam;
	//! \brief 保存显示参数(如果是多线程的话，就是主线程使用的)
	UGDrawParamaters m_MainDrawParam;
	//! \brief 保存显示参数(如果是多线程的话，就是主线程使用的)
	UGGraphics* m_pMainGraphics;
	//! \brief 显示缓存
	UGDrawCache m_DrawCache;
	//! \brief 显示参数预设置
	UGDrawMaker m_DrawMaker;
	//modefied by macx 2008-9-26 
	//! \brief 绘制进度回调函数
	DRAWCALLBACKPROC m_pDrawCallBackFunc;
	//! \brief 显示窗口
	UGlong m_pWnd;

	REFRESHCALLBACKPROC m_pRefreshCallBackFunc;
	UGlong m_pRefreshWnd;

	REPAINTCALLBACKPROC m_pRePaintCallBackFunc;
	UGlong m_pRePaintWnd;

	REFRESHMAPCALLBACKPROC m_pRefreshMapCallBackFunc;
	UGlong m_pRefreshMapPaintWnd;

	//! \brief 处理多线程回调
	THREADCALLBACKPROC m_pThreadFunc;
	UGlong m_pThreadWnd;

	//处理多线程任务取消的回调
	THREADCANCALECALLBACKPROC m_pThreadCancleFunc;
	UGlong m_pThreadCancleWnd;
protected:
// 	DRAWCALLBACKPROC m_pDrawCallBackFunc;
// 	UGlong m_pWnd;
	UGbool m_bOverTimeRefresh;

	// 贴图的时间间隔，默认还是用1000，但是可以在配置文件里边读取吧。
	UGint m_nTimeSlot;

	// 缩放是否刷新标识
	UGbool m_bZoomRefreshFlag;
	// 平移缓冲标识
	UGbool m_bBufferPanning;
	// 异步刷新地图模式
	UGbool m_bAsyncMode;
	// 多地图模式（异步模式下把线面和点文字层分成两个地图绘制）
	UGbool m_bMultiMapMode;

	// 异步模式下取消地图绘制
	UGbool m_bCancleDrawFlag;
	//! \brief 保护前景地图参数
	UGMutex m_CancleDrawMutex;

	UGMakerCache* m_pMakerCache;

public:
	UGlong m_pPaintWnd;
	DRAWPAINTPROC m_pDrawPaintFunc;

	//! \brief 定时器控制函数
	UGlong m_pEventView;  //调用事件回调函数的对象指针
	StartTimerProc m_pStartTimerFunc;
	StopTimerProc m_pStopTimerFunc;

protected:
	UGStyle m_Style;
	UGTextStyle m_TextStyle;
	UGGraphics* m_pGraphics;

	UGGraphics* m_pRefreshGraphics;
	UGbool m_bBeginCalculateTime;
	UGbool m_bBeginDrawImg;
	clock_t m_clockBegin;
	UGint m_nCalculateNum;

	///////////////////////////////////////////////////////
	//这一组成员是绘制栅格数据集时需要的
	UGRect m_rcImgPaint;
	UGSize2D m_szImgViewOffset;
	UGSize2D m_szImgViewRatio;
	UGImageData m_ImgInfo;

public:
	UGDatasetRaster *m_pDTRaster;

protected:
	UGImgBlock *m_pDemBlock;
	///////////////////////////////////////////////////////

	//! \brief 输出PDF时要素的风格选项
	//{{修改原因：添加输出到PDF的风格设置选项 修改人:macx 2008-7-31 9:53:19
	UGint m_nOutputStyle;
	//}}修改原因：添加输出到PDF的风格设置选项 修改人:macx  2008-7-31 9:53:19
	
	// 是否正在绘制布局中的图例(绘制图例需要特殊处理，这里需要使用标志，绘制过程中可以区分)
	UGbool m_bDrawingGeoLegend;

public:

#if PACKAGE_TYPE==PACKAGE_UGC
	//! \brief 专题图显示模式
	//! \remarks 0, theme none; 1, theme unique; 2, theme range;
	UGint m_nDrawMode;
	
	//! \brief 分段专题图的KEYS
	UGArray <UGdouble> *m_pAryDoubleKeys;
	
	//! \brief 单值专题图的KEYS,也用ugdouble来存储吧。
	UGArray <UGdouble> *m_pAryIntKeys;
	
	//! \brief 专题图风格
	UGColorset *m_pStyles;
	
	//! \brief 专题图默认风格
	UGColor m_DefaultStyle;
#endif // end declare ugc sdk

	UGint m_nTransparentRate;

	//由于需要多线程出图，栅格数据集的部分变量信息保存到Drawing类中
	UGColor m_NoDataStyle;
	UGColor m_BackColor;
	UGbyte m_btBackColorTolerance;
	UGchar m_btBrightness;
	UGchar m_btContrast;
	UGColorTable m_ColorsetTable;
	UGColorDictTable m_clrDictTable;
	UGint m_nGridNoData;

	//! \brief 实现栅格范围专题图是否可见功能，内部使用，不对外开放
	UGArray<UGbool>* m_pVisibles;		//Visibles

	UGColorTable* GetColorsetTable();
	UGColorDictTable* GetColorDictTable();
	//! \brief 特定值的透明处理,即是图层中指定的透明色
	UGbool m_bSpecialValueTransparent;
	//! \brief 需要透明的特定值,看是否需要替代m_nGridNoData.暂时去掉它
	//UGdouble m_dSpecialValue;

public:
	//! \brief 高亮风格，主要适用于复合对象
	UGStyle m_styleHignlight;
	//! \brief 是否高亮绘制对象，主要适用于复合对象
	UGbool m_bHignlight;

	UGbool m_bPan2;
	clock_t m_panBeginTime;
	UGbool m_bViewGlobal;

	//added by xielin 2008-6-13 UGGeoMap中要用到对应的UGWorkspace，这里保存一个吧
	void* m_pWorkspace;

	//added by xielin 2008-8-7 增加一个变量来存储是否背景透明或者无值透明，
	//以前是设置无值风格为-1来处理的，但是在linux上，默认白色就是-1，导致结果错误，修改之
	UGbool m_bRasterBackTransparent;

	//! \brief 多波段显示数组
	UGArray<UGint> m_arrMultiBandVisible;
	//! \brief 多波段显示颜色空间模式
	ImgColorSpace m_nImgCS;

	//! \brief 多波段拉伸参数
	UGRasterStretchOption m_RasterStretch;
	
	public:
		UGbool IsImagePaintTiled();
		void SetImagePaintTiled(UGbool bTiled = true);

	private:
		// 设置是否分块显示影像
		UGbool m_bImagePaintTiled;

		// 统计值
		UGArray<UGdouble>			m_arrMaxVal;
		UGArray<UGdouble>			m_arrMinVal;
		UGArray<UGdouble>			m_arrMeanVal;
		UGArray<UGdouble>			m_arrStandardDVal;
		UGArray<UGdouble>			m_arrNoValue;
		UGArray<UGHistogram>	m_arrHistogram;

		// 标识是否是影像数据集集合
		UGbool	m_bDatasetRasterCollection;

		// 分块显示
		UGbool PaintViewImage_Tile(const UGRect2D& rcDraw, const UGRect& rcBMP, UGProgress* pProgress);

		UGbool PaintViewGrid_Tile(UGDatasetRaster* pDatasetRaster, const UGRect2D& rcDraw, const UGRect& rcImg, UGProgress* pProgress);
		UGbool PaintViewMBImage_Tile(UGDatasetRaster* pDatasetRaster, const UGRect2D& rcDraw, const UGRect& rcImg, UGProgress* pProgress);
		UGbool PaintViewSBImage_Tile(UGDatasetRaster* pDatasetRaster, const UGRect2D& rcDraw, const UGRect& rcImg, UGProgress* pProgress);
};

}

#endif // !defined(AFX_UGDRAWING_H__AAC47E2E_B5B6_476C_9462_FBF34F02DFF5__INCLUDED_)

