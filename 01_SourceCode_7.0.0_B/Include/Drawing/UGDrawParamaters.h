// UGDrawParamaters.h: interface for the UGDrawParamaters class.
//
//////////////////////////////////////////////////////////////////////

/*!
   **************************************************************************************
    \file     UGDrawParamaters.h
   **************************************************************************************
    \author   张艳良、陈国雄
    \brief    显示参数类                                                             
    \attention   
   ----------------------------------------------------------------------------------<br>
    Copyright(c) 2000-2010  SuperMap GIS Technologies,Inc.                           <br>
    All Rights Reserved.                                                             <br>
   ----------------------------------------------------------------------------------<br> 
   
   **************************************************************************************
    \version 2005-06-09  陈国雄    初始化版本.                                       <br>
   **************************************************************************************
*/

#if !defined(AFX_UGDRAWPARAMATERS_H__8A1C2D67_F27C_4242_A968_AAB8D94D4E42__INCLUDED_)
#define AFX_UGDRAWPARAMATERS_H__8A1C2D67_F27C_4242_A968_AAB8D94D4E42__INCLUDED_

#include "Graphics/UGGraphics.h"
#include "Stream/ugdefs.h"
#include "Projection/UGRefTranslator.h"

#include "Toolkit/UGStyle.h"
#include "Drawing/UGMapOverlapDisplayedOptions.h"

#define DEFAULT_COORD_RATIO 1000.0

namespace UGC {

class UGMarkerSymbol;
class UGLineSymbol;
class UGFillSymbol;
class UGMarkerSymParam;
class UGLineSymParam;
class UGFillSymParam;

class DRAWING_API UGDrawParamaters  
{
public:
	//! \brief 地图颜色模式
	enum UGMapColorMode
	{
		//! \brief 默认彩色模式
		cmDefault			= 0,
		//! \brief 黑白模式
		cmBlackWhite		= 1,
		//! \brief 灰度模式
		cmGray				= 2,
		//! \brief 黑白反色模式
		cmBlackWhiteReverse = 3,
		//! \brief 仅黑白反色模式
		cmOnlyBlackWhiteReverse = 4
	};

	//! \brief 用户动作类型定义,本类型在CSmMap中使用
	enum UGMapUserAction
	{
		//! \brief 什么也不干
		uaNull				=0,
		//! \brief 地图平移
		uaPan				=1,
		//! \brief 放大
		uaZoomIn			=2,
		//! \brief 缩小
		uaZoomOut			=3,
		//! \brief 自由缩放
		uaZoomFree			=4,
		//! \brief 点选 ，如果按住鼠标就成为框选
		uaPointModeSelect	=5,
		//! \brief 纯点选方式
		uaPointModeSelectTrue = 5 + 1000,
		//! \brief 拉框选择
		uaRectModeSelect	=6,
		//! \brief 圆选择
		uaCircleModeSelect	=7,
		//! \brief 多边形选择
		uaRegionModeSelect	=8,
		//! \brief 线跨选择
		uaLineModeSelect	=9,

		//! \brief 编辑(for华亚松)
		uaEdit				=21,
		//! \brief 
		uaTrack				=22,
		//! \brief GeoMap编辑
		uaGeoMapEdit		=23,

		// ========================================
		// 各位请注意，21-99之间的UGMapUserAction值已经分配给
		// uaEdit和uaTrack的子Action，请不要在自己的模块里使用这些值
		// ========================================

		// 以下UserAction用于测试，请勿使用
		//! \brief 军标标注
		uaMiliSymbol		=100,
		//! \brief 不用位图贴，直接画，适用于小图，效果好
		uaPan2				=101,
		//! \brief 不用位图贴，直接画，适用于小图，效果好
		uaZoomFree2			=102,
		//! \brief 移动标签专题图的图标
		uaMoveThemeLabel    =105,
		//! \brief 移动统计专题图的图标
		uaMoveThemeGraph    =106,
		//! \brief 移动等级符号专题图的图标
		uaMoveThemeGraduatedSymbol =107,


	};// 用户操作（UGMapUserAction类型定义，访问方式为UGDrawParamaters::ua???）

	enum UGShowOption
	{
		//! \brief 是否允许重叠文本
		UG_SO_ALLOW_TEXTOVERLAP			= 0x00000001,
		//! \brief 是否显示消除线锯齿
		UG_SO_LINE_SMOOTHING_MODE		= 0x00000002,
		//! \brief 是否符号显示固定角度
		UG_SO_MARKER_FIXEDANGLE			= 0x00000004,
		//! \brief 是否设置动态投影
		UG_SO_PROJECTION_ONTHEFLY		= 0x00000008,
		//! \brief 是否文本固定朝向
		UG_SO_TEXT_FIXEDORIENTATION		= 0x00000010,
		//! \brief 是否文本固定角度
		UG_SO_TEXT_FIXEDANGLE			= 0x00000020,
		//! \brief 是否操作忙
		UG_SO_ACTION_BUSY				= 0x00000040,
		//! \brief 是否能够使用忙操作
		UG_SO_ENABLE_BUSY				= 0x00000080,
		//! \brief 操作取消
		UG_SO_ACTION_CANCEL				= 0x00000100,
		//! \brief 是否正在打印
		UG_SO_IS_PRINTING				= 0x00000200,
		//! \brief 是否填充TIN
		UG_SO_FILL_TIN					= 0x00000400,
		//! \brief 是否锁定地图显示范围
		UG_SO_BOUNDS_LOCK				= 0x00000800,
		//! \brief 是否取消Geometry显示
		UG_SO_GEOMETRY_CANCEL			= 0x00001000,
		//! \brief 是否发送地图事件
		UG_SO_MAP_EVENT					= 0x00002000,
		//! \brief 是否显示消除文本锯齿
		UG_SO_TEXT_SMOOTHING_MODE		= 0x00004000,
		
	};
	//! \brief 该类型不对外开放
	enum UGDrawLayerType
	{
		//! \brief 绘制所有图层
		UG_DRAWLAYER_ALL = 0,
		//! \brief 不绘制标签图层
		UG_DRAWLAYER_NOLABEL = 1,
		//! \brief 绘制标签图层
		UG_DRAWLAYER_LABEL = 2
	};
	
public:
	//! \brief 构造函数
	UGDrawParamaters();
	//! \brief 析构函数
#ifdef SYMBIAN60
	~UGDrawParamaters();
#else
	virtual ~UGDrawParamaters();
#endif
	
	//! \brief =操作符
	//! \param drawParam 要获取的对象
	void operator=(const UGDrawParamaters& drawParam);

public:
	//! \brief 比例尺 
	static UGdouble ScaleToCoordRatio(const UGPrjCoordSys& PJCoordSys, double dScale);

	static UGdouble CoordRatioToScale(const UGPrjCoordSys& PJCoordSys, double dCoordRatio);
	//! \brief 转换颜色
	//! \param color 要转换的颜色
	//! \param nMapColorMode 颜色模式
	static void ConvertColorByColorMode(UGColor &color, UGint nMapColorMode);
    //! \brief 转换几何对象风格的颜色
	//! \param style 要转换的几何对象
	//! \remarks 包括背景色，前景色，线性色
	//! \param nMapColorMode 颜色模式
	static void ConvertStyleByColorMode(UGStyle &style, UGint nMapColorMode);
	 //! \brief 转换文本对象风格的颜色
	//! \param style 要转换的文本对象
	//! \remarks 包括背景色，前景色
	//! \param nMapColorMode 颜色模式
	static void ConvertTextStyleByColorMode(UGTextStyle &textStyle, UGint nMapColorMode);
	//! \brief 重置当前显示参数
	void Reset();
	//! \brief 获得地图映射模式
	//! \return  地图的映射模式
	UGint GetMapMode() const;
	//! \brief 设置地图映射模式
	//! \param nMapMode 地图的映射模式
	void SetMapMode(UGint nMapMode);
    //! \brief 设置地图映射模式和窗口的原点坐标
	//! \param pGraphics 依赖的Graphics对象
	//! \return  原始的地图的映射模式
	UGint SetGeoMapModeX(UGGraphics *pGraphics);
	//! \brief 恢复参数 
	void Restore();
	//! \brief 保存参数
	void Preserve();
	//! \brief 判断坐标转换比率是否有效
	//! \return 是否有效
	UGbool IsValid();
	//! \brief 判断当前点是否可见
	//! \return 是否可见
	UGbool IsVisible(const UGPoint2D& point);
	//! \brief 判断当前点是否可见
	//! \return 是否可见
	UGbool IsVisible(const UGRect2D& rcBounds);
	//! \brief 0.01 mm to 逻辑坐标
	//! \param nSize 要转换的坐标
	//! \return 逻辑坐标
	UGint HIMETRICtoLP(const UGint nSize);
     //! \brief 0.01 mm to 地图坐标
	//! \param nSize 要转换的坐标
	//! \return 地图坐标
	UGdouble HIMETRICtoMP(const UGint nSize);
	//! \brief 逻辑坐标 to 0.01 mm  
	//! \param nSize 要转换的坐标
	//! \return 0.01mm 坐标
	UGint LPtoHIMETRIC(const UGint nSize);
	//! \brief 地图坐标 to 0.01 mm  
	//! \param nSize 要转换的坐标
	//! \return 0.01mm 坐标
	UGint MPtoHIMETRIC(const UGdouble dSize);
	//! \brief 地图坐标转换到逻辑坐标
	//! \param dSize 要转换的坐标
	//! \return 逻辑坐标
	UGint MPtoLP(const UGdouble dSize);
    //! \brief 地图坐标转换到逻辑坐标
	//! \param szSource 要转换的坐标
	//! \param szTarget 转换后的坐标
	void MPtoLP(const UGSize2D& szSource, UGSize& szTarget);
    //! \brief 地图坐标转换到逻辑坐标
	//! \param szSource 要转换的坐标
	//! \param szTarget 转换后的坐标
	void MPtoLP(const UGPoint2D& pntSource, UGPoint& pntTarget);
	//! \brief 地图坐标转换到逻辑坐标(高精度模式)
	//! \param szSource 要转换的坐标
	//! \param szTarget 转换后的坐标
	void MPtoLP(const UGPoint2D& pntSource, UGPoint2D& pntTarget);
	 //! \brief 地图坐标转换到逻辑坐标
	//! \param szSource 要转换的坐标的矩形
	//! \param szTarget 转换后的坐标的矩形
	void MPtoLP(const UGRect2D& rcSource, UGRect& rcTarget);
	//! \brief 地图坐标转换到逻辑坐标
	//! \param pPoints 需要转换的点串
	//! \param nCount 点串的个数
	//! \return 转换是否成功
	UGbool MPtoLPBatch(const UGPoint2D* pPoints, UGint nCount);	

	//! \brief 地图坐标转换到设备坐标
	//! \param pPoints 需要转换的点串
	//! \param nCount 点串的个数
	//! \return 转换是否成功
	UGbool MPtoDPBatch(const UGPoint2D* pPoints, UGint nCount);	
	//! \brief 地图坐标转换到逻辑坐标
	//! \param pPoints 点串的指针
	//! \param nCount 点串的几何对象的个数
	//! \param arrPolycounts 每个几何对象的点的个数
	//! \return 转换是否成功
	UGbool MPtoLPBatchPredigest(const UGPoint2D* pPoints, UGint nCount, UGArray<UGuint>& arrPolycounts);
	//! \brief 逻辑座标转换到地图座标
	//! \param nSize 需要转换的坐标
	//! \return 转换后的坐标
	UGdouble LPtoMP(const UGint nSize);
    //! \brief 逻辑座标转换到地图座标
	//! \param nSize 需要转换的坐标
	//! \return 转换后的坐标
	void LPtoMP(const UGSize& szSource, UGSize2D& szTarget);
   //! \brief 逻辑座标转换到地图座标
	//! \param pntSource 需要转换的坐标
	//! \param pntTarget 转换后的坐标
	void LPtoMP(const UGPoint& pntSource, UGPoint2D& pntTarget);
    //! \brief 逻辑座标转换到地图座标
	//! \param rcSource 需要转换的坐标的矩形
	//! \param rcTarget 转换后的坐标的矩形
	void LPtoMP(const UGRect& rcSource, UGRect2D& rcTarget);
	//! \brief  全幅显示
	//! \param rcLogical 默认逻辑范围
	//! \param nMarginWidthViewEntire 边界范围
	//! \return 显示是否成功
	UGbool ViewEntire(UGRect rcLogical = UGRect(0,0,0,0), UGint nMarginWidthViewEntire = 0);
	//! \brief 设定地图新的范围
	//! \param dNewScale 新的范围的坐标转换比率
	//! \param rcLogicalBounds 逻辑范围
	//! \param pntCenter 地图中心
	// 缩放、平移相关函数
	void SetMapScale(UGdouble dNewScale, const UGRect& rcLogicalBounds, const UGPoint2D& pntCenter);

	//! \brief 改变逻辑范围和Draw范围大小。它只会改变地理范围的大小，而不改变中心点。
	//! \param rcLogicalBounds 要改变的大小
	void ChangeLogicalBounds(const UGRect& rcLogicalBounds);	
	//! \brief 设置地图中心
	//! \param pntNewCenter 地图中心
	void SetCenter(const UGPoint2D& pntNewCenter);		
	//! \brief 设置方法缩小比率
	//! \param dZoomRatio 大于1是放大,<1时缩小
	void Zoom(UGdouble dZoomRatio);
	//! \brief 设置方法缩小比率
	//! \param dZoomRatio 大于1是放大,<1时缩小
	void ZoomEx(UGdouble dZoomRatio);
	//! \brief 放大制定的矩形
	//! \param rcUserRect 制定的矩形区域
	void RectZoomOut(const UGRect& rcUserRect);		
	//! \brief 缩小制定的矩形
	//! \param rcUserRect 制定的矩形区域
	void RectZoomIn(const UGRect& rcUserRect);		
	//! \brief 平移地图
	//! \param dOffsetX X方向上的向量
	//! \param dOffsetY Y方向上的向量
	void Pan(UGdouble dOffsetX, UGdouble dOffsetY);					//为了地图旋转平移
	//! \brief 使用默认的地图显示范围
	//void MakeDefault();
	//! \brief 获得地图的颜色模式
	//! \return 地图的颜色模式
	UGint GetMapColorMode() const;
	//! \brief 设置地图的颜色模式
	//! \param nMapColorMode 地图的颜色模式
	void SetMapColorMode(UGint nMapColorMode);
	//! \brief 获得用户的行为
	//! \return 用户的行为
	UGint GetUserAction() const;
	//! \brief 设置用户的行为
	//! \param nUserAction 地用户的行为
	void SetUserAction(UGint nUserAction);	
	//! \brief 获得已经保存的用户行为
	//! \return 已经保存的用户行为
	UGint GetUserActionSaved() const;
	//! \brief 设置已经保存的用户行为
	//! \param nUserActionSaved 已经保存的用户行为
	void SetUserActionSaved(UGint nUserActionSaved);	
	//! \brief 获得Geometry坐标点缓存的长度
	//! \return Geometry坐标点缓存的长度
	UGint GetPointCount() const;
	//! \brief 准备Geometry坐标点缓存(高精度模式在外面调用)
	UGbool PreparePointsBuf(UGint nPointCount);	
	//! \brief 获得Geometry坐标点缓存
	//! \return 指向Geometry坐标点缓存的指针
	UGPoint* GetPointsBuffer() const;
	//! \brief 获得地图的偏移量
	//! \return 地图的偏移量
	UGPoint GetOffset() const;
	//! \brief 设置地图的偏移量
	//! \param nMapColorMode 地图的偏移量
	void SetOffset(const UGPoint& pntOffset);	
	//! \brief 获得窗口的原点坐标
	//! \return 窗口的原点坐标
	UGPoint GetWindowOrg() const;
	//! \brief 设置地图的窗口的原点坐标
	//! \param pntWindowOrg 地图的窗口的原点坐标
	void SetWindowOrg(const UGPoint& pntWindowOrg);	
	//! \brief 获得地图的范围
	//! \return 地图的范围
	UGRect2D GetMapBounds() const;
	//! \brief 设置地图的范围
	//! \param nMapColorMode 地图的范围
	void SetMapBounds(const UGRect2D& rcMapBounds);	
	//! \brief 获得地图的有效范围
	//! \return 地图的有效范围
	UGRect2D GetInvalidBounds() const;
	//! \brief 设置地图的有效范围
	//! \param rcInvalidBounds 地图的有效范围
	void SetInvalidBounds(const UGRect2D& rcInvalidBounds);	
	//! \brief 获得地图的逻辑范围
	//! \return 地图的逻辑范围
	UGRect GetLogicalBounds() const;
	//! \brief 设置地图的逻辑范围
	//! \param rcLogicalBounds 地图的逻辑范围
	void SetLogicalBounds(const UGRect& rcLogicalBounds);	
	//! \brief 获得地图的显示范围
	//! \return 地图的显示范围
	UGRect2D GetMapDrawBounds() const;
	//! \brief 设置地图的显示范围
	//! \param rcMapDrawBounds 地图的显示范围
	void SetMapDrawBounds(const UGRect2D& rcMapDrawBounds,UGbool bByWidth = false);	
	//! \brief 获得地图的锁定显示范围
	//! \return 地图的锁定显示范围
	UGRect2D GetLockedDrawBounds() const;
	//! \brief 设置地图的锁定显示范围
	//! \param rcLockedDrawBounds 地图的锁定显示范围
	void SetLockedDrawBounds(const UGRect2D& rcLockedDrawBounds);	
	//! \brief 获得地图的范围
	//! \return 地图的范围
	UGdouble GetScale() const;
	//! \brief 设置地图的范围
	//! \param dScale 地图的范围
	//! \return 设置是否成功 modified by zhengyl at 2011-9-2
	UGbool SetScale(UGdouble dScale);	
	//! \brief 获得地图的 坐标转换比率(逻辑坐标/地理坐标)
	//! \return 地图的 坐标转换比率(逻辑坐标/地理坐标)
	UGdouble GetCoordRatio() const;
	//! \brief 设置地图的 坐标转换比率(逻辑坐标/地理坐标)
	//! \param dCoordRatio  坐标转换比率(逻辑坐标/地理坐标)
	void SetCoordRatio(UGdouble dCoordRatio);	
	//! \brief 获得符号缩放比例系数
	//! \return 地图的符号缩放比例系数
	UGdouble GetSymScale() const;
	//! \brief 设置地图的符号缩放比例系数
	//! \param dSymScale 地图的符号缩放比例系数
	//! \param dSymScaleX 地图的符号X方向的缩放比例系数
	void SetSymScale(UGdouble dSymScale,UGdouble dSymScaleX = 0);	
	//! \brief 获取符号X方向上的比例系数 获得地图的符号X方向的缩放比例系数
	//! \return 地图的符号X方向的缩放比例系数
	UGdouble GetSymScaleX() const{return m_dSymScaleX;};

	UGdouble GetDPIScale() const;
	
	void SetDPIScale(UGdouble dDPIScale);

	//! \brief 目前用于获取Layout和GeoMap的缩放比率(用于判断地图的图层是否在可见比例尺之内)
	UGdouble GetScaleRatio() const;
	//! \brief 目前用于设置Layout和GeoMap的缩放比率(用于判断地图的图层是否在可见比例尺之内)
	void SetScaleRatio(UGdouble dScaleRatio);
	//! \brief 获得地图的旋转角度
	//! \return 地图的旋转角度
	UGdouble GetAngle() const;
	//! \brief 设置地图的旋转角度
	//! \param dAngle 地图的旋转角度
	void SetAngle(UGdouble dAngle);	
	//! \brief 获得地图的最小显示范围
	//! \return 地图的最小显示范围
	UGdouble GetMinScale() const;
	//! \brief 设置地图的最大显示范围
	//! \param dMinScale 地图的最大显示范围
	void SetMinScale(UGdouble dMinScale);	
	//! \brief 获得地图的最大显示范围
	//! \return 地图的最大显示范围
	UGdouble GetMaxScale() const;
	//! \brief 设置地图的最大显示范围
	//! \param dMaxScale 地图的最大显示范围
	void SetMaxScale(UGdouble dMaxScale);
	//! \brief 获得地图的背景模式
	//! \return 地图的背景模式
	const UGStyle& GetBackgroundStyle() const;
	//! \brief 设置地图的背景模式
	//! \param style 地图的背景模式
	void SetBackgroundStyle(const UGStyle& style);
	//! \brief 获得地图的字符集
	//! \return 地图的字符集
	UGString::Charset GetCurCharset() const;
	//! \brief 设置地图的字符集
	//! \param nCurCharset 地图的字符集
	void SetCurCharset(UGString::Charset nCurCharset);
	//! \brief 获得地图的几何图形样式
	//! \return 地图的几何图形样式
	UGStyle* GetGeometryStyle() const;
	//! \brief 设置地图的几何图形样式
	//! \param pStyle 地图的几何图形样式
	void SetGeometryStyle(UGStyle* pStyle);
	//! \brief 获得地图的文本样式
	//! \return 地图的文本样式
	UGTextStyle* GetTextStyle() const;
	//! \brief 设置地图的文本样式
	//! \param pStyle 地图的文本样式
	void SetTextStyle(UGTextStyle* pStyle);
	//! \brief 获得地图的画笔
	//! \return 地图的画笔
	UGPen* GetPen() const;
	//! \brief 设置地图的画笔
	//! \param pPen 地图的画笔
	void SetPen(UGPen* pPen);
	//! \brief 获得地图的画刷
	//! \return 地图的画刷
	UGBrush* GetBrush() const;
	//! \brief 设置地图的画刷
	//! \param pBrush 地图的画刷
	void SetBrush(UGBrush* pBrush);
	//! \brief 获得地图的字体
	//! \return 地图的字体
	UGFont* GetFont() const;
	//! \brief 设置地图的字体
	//! \param pFont 地图的字体
	void SetFont(UGFont* pFont);
	//! \brief 获得地图的点符号
	//! \return 地图的点符号
	UGMarkerSymbol* GetMarkerSymbol() const;
	//! \brief 设置地图的点符号
	//! \param pMarkerSym 地图的点符号
	void SetMarkerSymbol(UGMarkerSymbol* pMarkerSym);
	//! \brief 获得地图的填充符号
	//! \return 地图的填充符号
	UGFillSymbol* GetFillSymbol() const;
	//! \brief 设置地图的填充符号
	//! \param pFillSym 地图的填充符号
	void SetFillSymbol(UGFillSymbol* pFillSym);
	//! \brief 获得地图的线形符号
	//! \return 地图的线形符号	
	UGLineSymbol* GetLineSymbol() const;
	//! \brief 设置地图的线形符号
	//! \param pLineSym 地图的线形符号
	void SetLineSymbol(UGLineSymbol* pLineSym);
	//! \brief 获得地图的点符号参数
	//! \return 地图的点符号参数
	UGMarkerSymParam* GetMarkerSymParam() const;
	//! \brief 设置地图的点符号参数
	//! \param pMarkerSymParam 地图的点符号参数
	void SetMarkerSymParam(UGMarkerSymParam* pMarkerSymParam);
	//! \brief 获得地图的填充符号参数
	//! \return 地图的填充符号参数
	UGFillSymParam* GetFillSymParam() const;
	//! \brief 设置地图的填充符号参数
	//! \param pFillSymParam 地图的填充符号参数
	void SetFillSymParam(UGFillSymParam* pFillSymParam);
	//! \brief 获得地图的线形符号参数
	//! \return 地图的线形符号参数
	UGLineSymParam* GetLineSymParam() const;
	//! \brief 设置地图的线形符号参数
	//! \param pLineSymParam 地图的线形符号参数
	void SetLineSymParam(UGLineSymParam* pLineSymParam);
	//! \brief 获得地图的最小可见文本数
	//! \return 地图的最小可见文本数
	UGdouble GetMinVisibleTextSize() const;
	//! \brief 设置地图的最小可见文本数
	//! \param dMinVisibleTextSize 地图的最小可见文本数
	void SetMinVisibleTextSize(UGdouble dMinVisibleTextSize);
	//! \brief 获得地图的最大可见文本数
	//! \return 地图的最大可见文本数
	UGdouble GetMaxVisibleTextSize() const;
	//! \brief 设置地图的最大可见文本数
	//! \param dMaxVisibleTextSize 地图的最大可见文本数
	void SetMaxVisibleTextSize(UGdouble dMaxVisibleTextSize);
	//! \brief 获得地图的动态投影转换
	//! \return 地图的动态投影转换
	UGRefTranslator* GetRefTranslator();
	//! \brief 获得地图的动态投影转换
	//! \return 地图的动态投影转换
	UGRefTranslator* GetRefTranslator() const;
	//! \brief 判断是否允许文本压盖
	//! \return 文本是否允许压盖
	UGbool IsAllowTextOverlap() const;
	//! \brief 设置文本 是否允许文本压盖
	//! \param bFlag 是否允许文本压盖
	void SetAllowTextOverlap(UGbool bFlag);
	//获取压盖过滤选项
	UGMapOverlapDisplayedOptions& GetOverlapDisplayedOptions();
	//获取压盖过滤选项
	const UGMapOverlapDisplayedOptions& GetOverlapDisplayedOptions() const;
	//设置压盖过滤选项
	void SetOverlapDisplayedOptions(const UGMapOverlapDisplayedOptions& options);
	//! \brief 判断线形是否光滑模式
	//! \return 线形是否光滑模式
	//将线和文本区分开，和SFC保持一致
	UGbool IsLineSmoothingMode() const;
	//! \brief 设置线形是否光滑模式
	//! \param bFlag 线形是否光滑模式
	void SetLineSmoothingMode(UGbool bFlag);
	//! \brief 判断文本是否光滑模式
	//! \return 文本是否光滑模式
	UGbool IsTextSmoothingMode() const;
	//! \brief 设置文本是否光滑模式
	//! \param bFlag 文本是否光滑模式
	void SetTextSmoothingMode(UGbool bFlag);
	//UGbool IsSmoothingMode() const;
	//void SetSmoothingMode(UGbool bFlag);
	//! \brief 判断点符号是否锁定角度
	//! \return 点符号是否锁定角度
	UGbool IsMarkerFixedAngle() const;
	//! \brief 设置点符号是否锁定角度
	//! \param bFlag 点符号是否锁定角度
	void SetMarkerFixedAngle(UGbool bFlag);
	//! \brief 判断是否设置动态投影
	//! \return 是否设置动态投影
	UGbool IsProjectionOnTheFly() const;
	//! \brief 设置地图是否设置动态投影
	//! \param bFlag 地图是否设置动态投影
	void SetProjectionOnTheFly(UGbool bFlag);
	//! \brief 判断是否文本固定朝向
	//! \return 是否文本固定朝向
	UGbool IsTextFixedOrientation() const;
	//! \brief 设置地图是否文本固定朝向
	//! \param bFlag 地图是否文本固定朝向
	void SetTextFixedOrientation(UGbool bFlag);
	//! \brief 判断是否文本固定角度
	//! \return 是否文本固定角度
	UGbool IsTextFixedAngle() const;
	//! \brief 设置地图是否文本固定角度
	//! \param bFlag 地图是否文本固定角度
	void SetTextFixedAngle(UGbool bFlag);
	//! \brief 判断是否操作取消
	//! \return 是否操作取消
	UGbool IsCancel() const;
	//! \brief 设置地图的操作取消
	//! \param bFlag 地图的操作取消
	void SetCancel(UGbool bFlag);
	
	//! \brief 设置地图是否正在输出为Image数据集
	//! \param bFlag 地图是否输出为Image数据集
	void SetOutputImage(UGbool bFlag);
	//! \brief 获取地图是否正在输出为Image数据集
	UGbool  IsOutputImage();

	//! \brief 设置是否超出地图范围也照样绘制
	//! \param bFlag 是否超出地图范围也照样绘制
	void SetDrawOutsideMapBounds(UGbool bFlag);
	//! \brief 获取是否超出地图范围也照样绘制
	UGbool IsDrawOutsideMapBounds();

	//! \brief 判断是否操作忙
	//! \return 是否操作忙
	UGbool IsBusy() const;
	//! \brief 设置地图的操作忙
	//! \param bFlag 地图的操作忙
	void SetBusy(UGbool bFlag);
	//! \brief 判断是否能够使用忙操作
	//! \return 是否能够使用忙操作
	UGbool IsBusyEnable()const;	
	//! \brief 设置地图是否能够使用忙操作
	//! \param bFlag 地图是否能够使用忙操作
	void SetBusyEnable(UGbool bFlag);
	//! \brief 判断是否取消Geometry显示
	//! \return 是否取消Geometry显示
	UGbool IsGeometryCancel() const;
	//! \brief 设置地图是否取消Geometry显示
	//! \param bFlag 地图是否取消Geometry显示
	void SetGeometryCancel(UGbool bFlag);
	//! \brief 判断是否正在打印
	//! \return 是否正在打印
	UGbool IsPrinting() const;
	//! \brief 设置地图是否正在打印
	//! \param bFlag 地图是否正在打印
	void SetPrinting(UGbool bFlag);
	//! \brief 判断是否填充TIN
	//! \return 是否填充TIN
	UGbool IsFillTIN() const;
	//! \brief 设置地图是否填充TIN
	//! \param bFlag 地图是否填充TIN
	void SetFillTIN(UGbool bFlag);
	//! \brief 判断是否锁定地图显示范围
	//! \return 是否锁定地图显示范围
	UGbool IsDrawBoundsLocked() const;
	//! \brief 设置是否锁定地图显示范围
	//! \param bFlag 地图是否锁定地图显示范围
	void SetDrawBoundsLocked(UGbool bFlag);
	//! \brief 判断是否发送地图事件
	//! \return 是否发送地图事件
	UGbool IsSendMapEvent() const;
	//! \brief 设置是否发送地图事件
	//! \param nMapColorMode 地图是否发送地图事件
	void SetSendMapEvent(UGbool bFlag);
	//! \brief 获得最大可见点数
	//! \return 最大可见点数
	UGint GetMaxVisibleVertex() const;
	//! \brief 设置地图的颜色模式
	//! \param nMapColorMode 地图的颜色模式
	void SetMaxVisibleVertex(UGint nMaxVisibleVertex);
	//! \brief 获得显示图层选项
	//! \return 显示图层选项
	UGint GetDrawLayerType() const;
	//! \brief 设置地图显示图层选项
	//! \param nDrawLayerType 地图显示图层选项
	void SetDrawLayerType(UGint nDrawLayerType);
	//! \brief 获得当前显示图层索引  当前显示图层索引以及总图层数，为了计算显示百分比
	//! \return 当前显示图层索引
	UGint GetDrawLayerIndex() const;
	//! \brief 设置地图当前显示图层索引
	//! \param nDrawLayerIndex 地图当前显示图层索引
	void SetDrawLayerIndex(UGint nDrawLayerIndex);
	//! \brief 获得当前显示总图层数
	//! \return 当前显示总图层数
	UGint GetDrawLayerCount() const;
	//! \brief 设置地图当前显示总图层数
	//! \param nMapColorMode 地图当前显示总图层数
	void SetDrawLayerCount(UGint nDrawLayerCount);
	//! \brief 线型绘制时是否完整显示虚实部。
	//! \return 是否完整显示虚实部，1代表是，0代表否，默认为1。
	UGbool IsLineAdjust() const;
	//! \brief 线型绘制时设置完整显示虚实部。
	//! \param bLineAdjust  是否完整显示虚实部[in]
	//! \remarks 默认下绘制线型会采用此方法，设定是否完整显示虚实部，在放大缩小时都能完整显示线型。
	void SetLineAdjust(UGbool bLineAdjust = true);
	//addby dongfei 2007-03-26
	//! \brief 设置地图平滑显示的最大记录数 	
	//! \brief 设置地图平滑显示的最大记录数
	//! \param nRecorcCount 地图平滑显示的最大记录数
	void SetSmoothingMaxRecord(UGint nRecorcCount);
	//! \brief 获取地图平滑显示的最大记录数 dongfei 2007-03-26
	//! \brief 获得地图平滑显示的最大记录数
	//! \return 地图平滑显示的最大记录数
	UGint GetSmoothingMaxRecord()const;
	//! \brief 设置是否强制加到文本边界
	//! \param bForceAdd 是否强制加到文本边界
	void  SetForceAddTextBounds(UGbool bForceAdd = false){m_bForceAdd = bForceAdd;};
	//! \brief 判断是否强制加到文本边界
	//! \return 是否强制加到文本边界
	UGbool IsForceAddTextBounds(){return m_bForceAdd;};
	//! \brief 计算裁剪范围
	void ComputeClipBounds();

	//! \brief 设置显示范围
	//! \param arrDisplayScales 需要设置的点列
	void SetDisplayScales(const UGArray<UGdouble>& arrDisplayScales);
	//! \brief 获得显示范围
	//! \param arrDisplayScales 显示范围的点列
	void GetDisplayScales(UGArray<UGdouble>& arrDisplayScales);
	//! \brief 设置是否根据范围显示地图
	//! \param bDisplayByScales 是否根据范围显示地图
	void SetDisplayByScales(UGbool bDisplayByScales);
	//! \brief 判断是否根据范围显示地图
	//! \return 根据范围显示地图
	UGbool IsDisplayByScales() const;
	//! \brief 是否为设备图层绘制，仅提供给设备图层用
	UGbool IsDeviceDraw()const;
	//! \brief 设置为设备图层绘制，仅提供给设备图层用
	void SetDeviceDraw(UGbool bIsDeviceDraw = false);
	

	//! \brief 获取设备坐标轴方向。
	//! \return 坐标轴方向。
	//! \param 坐标轴方向,true为向上，false为向下
	//! \attention 。
	UGbool IsOrientation()const;	
	//! \brief 设置设备坐标轴方向。
	//! \param 坐标轴方向,true为向上，false为向下[in].
	void SetOrientation(UGbool bOrientation);

	//! \brief 面对像是不是随着地图旋转而进行填充风格的旋转填充
	UGbool GetIsFillAngle()const;
	void SetIsFillAngle(UGbool bIsFillAngle = false);
	
	//! \brief 设置当前地图是否忽略符号填充,add by tanzw,2011-1-13
	//! \param bIsSymbolFillIgnored 是否忽略符号填充，默认false不忽略
	//! \remarks 忽略符号填充时则只绘制填充区域的背景色，不进行符号的绘制
	UGbool IsSymbolFillIgnored()const;
	void SetSymbolFillIgnored(UGbool bIsSymbolFillIgnored = false);

	//! \brief 地图刷新是不是中间取消绘制了
	UGbool GetIsDrawComplete()const;
	void SetIsDrawComplete(UGbool bIsDrawComplete);

	//! \brief 获取是否需要进行比例尺转换转换。
	UGbool GetCoordRatioToScale() const;	
	//! \brief 设置比例尺转换。
	//! \param 是否需要转换
	void SetCoordRatioToScale(UGbool bCoordRatioToScale);

	//! \brief 设置当前正在生成缓存，暂时仅供CacheBuilder使用
	UGbool SetIsOutputCache(UGbool bIsOutputCache = true);

	//! \brief 获得当前是否正在生成缓存，暂时仅供CacheBuilder使用
	UGbool GetIsOutputCache() const;

	//! \brief 设置是否批量把图层转为数据集，暂时为缓存预处理准备
	UGbool SetIsBanchLayersToDataset(UGbool bBanchLayersToDataset = true);

	//! \brief 获取是否批量把图层转为数据集，暂时为缓存预处理准备
	UGbool GetIsBanchLayersToDataset() const;

	//! \brief 设置是否使用符号的默认颜色显示
	void SetIsSymbolDefaultColor(UGbool bIsSymbolDefaultColor);
	
	//! \brief 获得是否使用符号的默认颜色显示
	UGbool GetIsSymbolDefaultColor() const;

	//! \brief 判断地图中是否有网络地图图层
	UGbool IsWebMapFlag();
	void SetWebMapFlag(UGbool bHasWebMap);

	// 自定义网络地图DP-->LP转换比率
	void SetWebMapCoordRatio(UGdouble dRatioX, UGdouble dRatioY);
	void GetWebMapCoordRatio(UGdouble& dRatioX, UGdouble& dRatioY);

	//! \brief 设置地图DP-->LP转换比率
	//! \param pGraphics 依赖的Graphics对象
	void SetWebMapModeCoordRatio(UGGraphics *pGraphics);

	//! \brief 判断当前是否要打印到文件中
	//! \return 返回当前是否可以打印到文件中
	UGbool IsPrintToFile() const;
	//! \brief 设置是否打印到文件当中
	//! \param UGbool 是否打印到文件中
	void SetPrintToFile(UGbool bPrintToFile = TRUE);

	//! \brief 判断是否只刷新网络地图图层
	UGbool IsOnlyRefreshWebMapFlag();
	void SetOnlyRefreshWebMapFlag(UGbool bRefreshWebMap);

	//! \brief 设置/获取当前地图的DPI
	void SetMapDPI(UGdouble dMapDPI);
	UGdouble GetMapDPI() const;

	//! \brief 设置/获取是否使用全局系统的DPI，默认为false，false时使用地图设置的DPI
	UGbool IsUseSystemDPI();
	void SetUseSystemDPI(UGbool bUseSystemDPI);

	//! \brief 设置/获取高精度坐标转换模式
	UGbool IsHighPrecisionMode();
	void SetHighPrecisionMode(UGbool bHighPrecision);

	//! \brief 设置/获取背景地图数据模式(嵌入式使用)
	UGbool IsDrawBackMapMode();
	void SetDrawBackMapMode(UGbool bDrawBackMap);

	//! \brief 判断是否只刷新底层数据(嵌入式使用)
	UGbool IsOnlyRefreshBackMapFlag();
	void SetOnlyRefreshBackMapFlag(UGbool bRefreshBackMap);

protected:
	//! \brief 将当前比例尺调整到最接近的固定比例尺
	void AdjustToNearestFixedScale();
	void PanEx(UGdouble dOffsetX, UGdouble dOffsetY);			
	void LockMapDrawBounds();	
	//用于根据输出设备的范围m_rcDrawBounds调整当前地图显示范围的长宽比例,
	//使得地图显示在中间而不是左上角。如果bByMax == false，那么地图显示范围
	//将不会超过目前的范围.
	void AdjustWidthHeightRatio(UGbool bByMax = true,UGbool bByWidth = false);	
	void SetOption(UGbool bFalg, UGint nValue);
	void ChangeLogicalDrawBounds(const UGRect& rcLogicalBounds);
	//! \brief 设备图层地理坐标转逻辑坐标
	void MPtoLPDevice(const UGPoint2D& pntSource, UGPoint& pntTarget);
	//! \brief 设备图层地理坐标转逻辑坐标(高精度模式)
	void MPtoLPDevice(const UGPoint2D& pntSource, UGPoint2D& pntTarget);

	UGSize LPtoDPSize(const UGSize &szLP);

	// 整型逻辑坐标转换到double型的逻辑坐标，提高精度。
	// 天宇在设置逻辑矩形时已经使用了高精度，所以其他需要使用逻辑宽高的地方都需要用这个函数处理成高精度的逻辑宽高
	UGSize2D LPtoHLP(const UGSize &szLP);

public:
	UGbool m_bIsDisplayClip;	// 该变量有两个用途：1. 表示是否使用裁剪区域；2. 由Drawing使用表示当前绘制的对象是否已经经过了裁剪。
								// 这两个用途并不冲突。对于用户只需要关心其第一个用途。

	UGRect2D m_rc2ClipBounds;

	// 用户设置的全幅范围
	UGbool m_bIsUserEntireBounds;
	UGRect2D m_rc2UserEntireBounds;

	UGbool m_bCoordRatioChange;
	
	//! \brief UGGeoPicture对象多帧显示的当前帧数。
	UGint m_nPictureCurFrame;

	//! \brief 在流动显示的时候采用此Bounds裁剪，内部变量，不对外开放
	UGbool m_bUseMapDrawBoundsToPrint;
	UGRect2D m_rcMapDrawBoundsToPrint;

	//! \brief 记录Bounds变化情况，不对外开放！
	UGRect2D m_rcPreMapDrawBounds;

	//! \brief 记录Graphics比例坐标，不对外开放！
	UGPoint m_pntGraphicsWindowOrg;
	UGdouble m_dCoorRatioX;
	UGdouble m_dCoorRatioY;

protected:
	//! \brief 表示当前正在生成缓存
	UGbool m_bIsOutputCache;
	//! \brief 是否批量把图层转为数据集，暂时为缓存预处理准备
	UGbool m_bBanchLayersToDataset;
	//! \brief 地图的LP到DP的映射模式，其值由枚举UGGraphics::MapMode 所定义。
	UGint m_nMapMode;
	//! \brief 地图颜色模式，其值由枚举 UGMapColorMode 所定义。
	UGint m_nMapColorMode;	
	//! \brief 用户操作，其值由枚举 UGEditType::EditToolShape 所定义。
	UGint m_nUserAction;
	UGint m_nUserActionSaved;		

	//! \brief 显示Geometry的坐标串缓存
	UGint m_nPointCount;	
	UGPoint *m_pPointsBuf;	

	//! \brief 窗口偏移量
	UGPoint m_pntOffset;
	//! \brief 窗口原点的坐标位置，LP。
	UGPoint m_pntWindowOrg;
	//! \brief 整幅地图范围
	UGRect2D m_rcMapBounds;
	UGRect2D m_rcMapBoundsSaved;
	//! \brief 地图刷新范围(MP)
	UGRect2D m_rcInvalidBounds;	

	//! \brief 地图逻辑范围(LP)
	UGRect m_rcLogicalBounds;
	UGRect m_rcLogicalBoundsSaved;
	//! \brief 当前地图显示范围
	UGRect2D m_rcMapDrawBounds;
	UGRect2D m_rcMapDrawBoundsSaved;
	UGRect2D m_rcRotateMapDrawBounds;
	
	//! \brief 地图锁定显示范围
	UGRect2D m_rcLockedDrawBounds;

	//! \brief 坐标转换比率LP/MP。
	UGdouble m_dCoordRatio;
	UGdouble m_dCoordRatioSaved;	

	//! \brief 地图旋转角度
	UGdouble m_dAngle;	

	//! \brief 地图最大最小缩放比例
	double m_dMinScale;
	double m_dMaxScale;

	//! \brief 地图背景风格
	UGStyle m_BackgroundStyle;
	//! \brief 当前显示文本字符集
	UGString::Charset m_nCurCharset;

	//! \brief 显示Geometry临时风格
	UGStyle* m_pGeometryStyle;
	UGTextStyle* m_pTextStyle;

	UGPen* m_pCurPen;
	UGBrush* m_pCurBrush;
	UGFont* m_pCurFont;

	//! \brief 显示Geometry临时符号
	UGMarkerSymbol *m_pMarkerSym;
	UGLineSymbol *m_pLineSym;
	UGFillSymbol *m_pFillSym;

	//! \brief 临时符号参数
	UGMarkerSymParam* m_pMarkerSymParam;
	UGFillSymParam* m_pFillSymParam;
	UGLineSymParam* m_pLineSymParam;
	
	//! \brief 最大最小可见文本大小（逻辑单位）
	UGint m_nVisibleTextSizeMin;
	UGint m_nVisibleTextSizeMax;
	
	UGdouble m_dScaleRatio;
	UGdouble m_dDPIScale;
	UGdouble m_dSymScale;						//符号缩放比率
	UGdouble m_dSymScaleX;						//符号X方向上的缩放比例系数 added by dongfei
	UGRefTranslator* m_pRefTranslator;			//动态投影转换

	UGuint m_nOption;
	UGint m_nMaxVisibleVertex;

	// 地图是否正在输出为Image数据集
	UGbool m_bOutputImage;

	// 是否超出地图范围也照样绘制
	UGbool m_bDrawOutsideMapBounds;

	//! \brief 显示图层选项
	UGint m_nDrawLayerType;
	//! \brief 当前显示图层索引以及总图层数，为了计算显示百分比
	UGint m_nDrawLayerIndex;
	UGint m_nDrawLayerCount;
		
	//! \brief 是否调整线型宽度，完整显示
	/**
	*/	
	UGbool m_bLineAdjust;

	//! \brief 可平滑显示的最大记录数 -1表示无限大 dongfei 2007-03-26
	UGint m_nSmoothingMaxRecord;
	UGbool m_bForceAdd;			//是否强制加入到避让文本数组中

	UGbool m_bFixedScales;		// 是否是固定比例尺
	UGArray<UGdouble> m_arrFixedScales;	// 固定比例尺功能所定义的比例尺

	UGbool m_bIsDeviceDraw;
	//! \brief 设备坐标轴Y的方向，true，为向下，false为向上
	UGbool m_bOrientation;

	// 面对像是不是随着地图旋转而进行填充风格的旋转填充
	UGbool m_bIsFillAngle;
	//! \brief 用于局部刷新漫游功能，记录是不是中间取消绘制了
	UGbool m_bIsDrawComplete;

	UGbool m_bIsSymbolFillIgnored;

	UGbool m_bCoordRatioToScale;
	UGbool m_bIsSymbolDefaultColor;

	UGdouble m_dMapDPI;
	UGbool m_bUseSystemDPI;

	//! \brief 用于标记第一次打开地图的时候，地图的中心位置信息是不是发生变化了   added by zhengyl 2011-6-16
	UGbool m_bIsFirstMapCenterChange;

	//是否有网络地图图层
	UGbool m_bHasWebMapFlag;
	UGdouble m_dWebMapCoorRatioX;
	UGdouble m_dWebMapCoorRatioY;

	UGMapOverlapDisplayedOptions m_overlapDisplayedOptions;

	//! \brief 是否输出到文件。
	UGbool m_bPrintToFile;
	// 是否只刷新网络地图
	UGbool m_bOnlyRefreshWebMapFlag;

	// 是否是高精度坐标转换模式
	UGbool m_bHighPrecisionFlag;

	// 是否是绘制背景地图数据模式
	UGbool m_bDrawBackMapMode;

	// 是否只刷新网络地图
	UGbool m_bOnlyRefreshBackMapFlag;
};

}

#endif // !defined(AFX_UGDRAWPARAMATERS_H__8A1C2D67_F27C_4242_A968_AAB8D94D4E42__INCLUDED_)

