// UGMap.h: interface for the UGMap class.
//
//////////////////////////////////////////////////////////////////////

/*!
   **************************************************************************************
    \file     UGMap.h   
   **************************************************************************************
    \author   陈国雄
    \brief    地图类，负责地图显示环境的管理。                                                                       
    \attention   
   ----------------------------------------------------------------------------------<br>
    Copyright (c) 2000-2010 SuperMap Software Co., Ltd.                           <br>
    All Rights Reserved.                                                             <br>
   ----------------------------------------------------------------------------------<br> 
   
   **************************************************************************************
    \version 2005-05-20  陈国雄    初始化版本.                                       <br>
   **************************************************************************************
*/

#if !defined(AFX_UGMAP_H__37037E0D_8ABC_413E_B8BE_2B8916F0319E__INCLUDED_)
#define AFX_UGMAP_H__37037E0D_8ABC_413E_B8BE_2B8916F0319E__INCLUDED_

#include "Map/UGLayers.h"
#include "Map/UGTrackingLayer.h"
#include "Projection/UGSpatialRef.h"

#if !defined SYMBIAN60 && !defined  OS_ANDROID && !defined (IOS)
#include "Map/UGDeviceTrackingLayer.h"
#endif

//add by xiaoys
#include "Map/UGTrackingLayerEx.h"

#include "SymbolMarker/UGMarkerSymbolLib.h"
#include "FileParser/UGExchangeFileType.h"
#include <queue>

namespace UGC {
	
	class UGCacheFile;
#if !defined OS_ANDROID && !defined IOS
	class UGChartSetting;
#endif
class MAP_API UGMapVersionManager  
{
public:
	UGMapVersionManager();
	void init(); // added by liucq 20130610 延后初始化，在移动平台手动调用初始化
#ifdef SYMBIAN60
	~UGMapVersionManager();
#else
	virtual ~UGMapVersionManager();
#endif
};

extern MAP_API UGMapVersionManager g_MapVersionManager;


//! \brief MapOpened事件回调函数
typedef void (UGSTDCALL *MapOpenedProc)(UGlong pWnd);

//! \brief BeforeMapDraw 事件回调函数
typedef void (UGSTDCALL *BeforeMapDrawProc)(UGlong pWnd,UGbool& bCancel,UGGraphics* pGraphics);

//! \brief AfterMapDraw 事件回调函数
typedef void (UGSTDCALL *AfterMapDrawProc)(UGlong pWnd,UGGraphics* pGraphics);

//! \brief SnapableChangedProc 事件回调函数
typedef void (UGSTDCALL *SnapableChangedProc)(UGlong pWnd);


class UGFishingNetArithmetic;
class UGTrackingMap;

class MAP_API UGMap  
{
public:
	enum UGGridType
	{
		//! \brief 网格线
		UGGridGrid,
		//! \brief 十字叉丝
		UGGridCross,
		//! \brief 点
		UGGridPoint
	};
public:
	UGMap();
	UGMap(UGbool bTrackingMap);
	UGMap(const UGMap& Map);
	~UGMap();
	UGMap& operator = (const UGMap &Map);

	enum OnTopType
	{
		//! \brief 标签置顶
		LabelOnTop = 1,        
        //! \brief 统计专题图置顶
		GraphOnTop = 2,                    
		//! \brief 等级符号置顶
		GraduatedSymbolOnTop = 4          
	};
//! \brief PDF输出类型，added by macx 2008.7.31 。
//! \remarks 备注信息。	
	enum UGTypeOption
	{
		//! \brief 默认方式，以矢量形式输出
		NORMAL  = 0,
		//! \brief 以栅格图像输出，可保证原始状态输出，当时不可以再修改
		IMAGE	= 1,		
	};

public:
	//! \brief  与工作空间建立联系,设置工作空间
	void SetWorkspace(UGWorkspace *pWorkspace);
	//! \brief  得到设置工作空间
	UGWorkspace* GetWorkspace()const;
#if !defined OS_ANDROID && !defined IOS
	//! \brief 获取海图设置对象指针
	UGChartSetting* GetChartSetting()const;
#endif
	//! \brief 获取当前地图中是否包含海图图层
	UGbool ContainLayerChart() const;

	//! \brief  初始化地图模式，此函数将改变 pGraphics 所指对象的映射模式和左上角的 LP 坐标。
	// 该函数调用完成之后，pGraphics 的 LP、DP 之间的坐标转换关系就已经建立
	// 对于该函数的详细解释，请参见其实现码。
	/*  \param pGraphics 绘制到的Graphics[in/out]
	    \param rcDevBounds 绘制设备的设备坐标范围[in]
	*/
	void MapModeInitialize(UGGraphics* pGraphics, const UGRect& rcDevBounds);

	//! \brief  恢复pGraphics的映射模式和原点坐标
	void MapModeRestore(UGGraphics* pGraphics);

	//! \brief  得到地图名称
	UGString GetName()const;
	//! \brief  得到地图描述信息
	UGString GetDescription()const;
	//! \brief  设置地图描述信息
	void SetDescription(const UGString& strDescription);

	//! \brief  重新设置初始化状态
	void Reset();
	//! \brief  设置刷新标志
	void SetRefreshFlag(UGbool bRefresh = true);

	//! \brief  设置更新标志
	void SetModifiedFlag(UGbool bModified = true);
	//! \brief  是否更新
	UGbool IsModified()const;

	//! \brief  设置地图投影信息
	void SetPrjCoordSys(const UGPrjCoordSys& PrjCoordSys);
	const UGPrjCoordSys& GetPrjCoordSys()const;
	void SetPrjCoordSysUnit(UGlong nUnits);
	UGlong GetPrjCoordSysUnit();

	//! \brief  得到颜色模式
	UGint GetColorMode()const;
	//! \brief  设置颜色模式
	void SetColorMode(UGint nColorMode);

	//! \brief  是否文本固定角度
	UGbool IsTextFixedAngle()const;
	//! \brief  设置为文本固定角度
	void SetTextFixedAngle(UGbool bTextFixedAngle = true);
	//! \brief  是否符号固定角度
	UGbool IsMarkerFixedAngle()const;
	//! \brief  设置为符号固定角度
	void SetMarkerFixedAngle(UGbool bMarkerFixedAngle = true);

	//! \brief 面对像是不是随着地图旋转而进行填充风格的旋转填充
	UGbool GetIsFillAngle()const;
	void SetIsFillAngle(UGbool bIsFillAngle = false);

	//! \brief 设置是否忽略符号填充，add by tanzw,2011-1-13
	//! \param bIsSymbolFillIgnored是否忽略符号填充，默认false不支持
	//! \remarks 设置忽略符号填充时则只绘制填充区域的背景色，不进行符号的绘制
	UGbool IsSymbolFillIgnored()const;
	void SetSymbolFillIgnored(UGbool bIsSymbolFillIgnored = false);
	
	//将文本和线分开，和SFC保持一致
	//UGbool IsSmoothingMode()const;									
	//void SetSmoothingMode(UGbool bSmoothingMode = true);
	//! \brief  是否为线光滑模式
	UGbool IsLineSmoothingMode()const;
	//! \brief  设置线光滑模式
	void SetLineSmoothingMode(UGbool bSmoothingMode = true);			
	//! \brief  是否为文本光滑模式
	UGbool IsTextSmoothingMode()const;									
	//! \brief  设置文本光滑模式
	void SetTextSmoothingMode(UGbool bSmoothingMode = true);			
	
	//! \brief 设置\获取地图平滑显示的最大记录数 dongfei 2007-03-26
	void SetSmoothingMaxRecord(UGint nRecordCount);	
	UGint GetSmoothingMaxRecord()const;

	//! \brief   是否允许显示重叠文本 
	UGbool IsAllowTextOverlap()const;
	//! \brief   设置为允许重叠文本
	void SetAllowTextOverlap(UGbool bAllowTextOverlap = false);	
	//! \brief获取压盖过滤选项
	UGMapOverlapDisplayedOptions& GetOverlapDisplayedOptions();
	//! \brief获取压盖过滤选项
	const UGMapOverlapDisplayedOptions& GetOverlapDisplayedOptions() const;
	//! \brief设置压盖过滤选项
	void SetOverlapDisplayedOptions(const UGMapOverlapDisplayedOptions& options);
	//! \brief   是否固定文本朝向
	UGbool IsFixedTextOrientation()const;							
	//! \brief   设置为固定文本朝向
	void SetFixedTextOrientation(UGbool bFixedTextOrientation = true);	

	//! \brief   是否标签专题图置顶	
	UGbool IsLabelAlwaysOnTop()const;								
	//! \brief   设置标签专题图置顶
	void SetLabelAlwaysOnTop(UGbool bLabelAlwaysOnTop = false);		

	//! \brief   设置等级分段专题图置顶
	void SetGraduatedSymbolAlwaysOnTop(UGbool bGraduatedSymbolAlwaysOnTop = false);
	//! \brief   是否等级分段专题图置顶
	UGbool IsGraduatedSymbolAlwaysOnTop()const;
	
	void SetGraphAlwaysOnTop(UGbool bGraphAlwaysOnTop = false);
	//! \brief   是否等级分段专题图置顶
	UGbool IsGraphAlwaysOnTop()const;

	//! \brief 方便组件在第一次打开空地图后，在再次添加缓存数据集是那个正确加载投影  added by lidl 
	//void SetFirstTimeDraw(UGbool bFirstTimeDraw);
	//! \brief   是否为第一次绘制
	UGbool IsFirstTimeDraw() const;

	//! \brief   得到最小可见文本大小
	UGdouble GetMinVisibleTextSize()const;
	//! \brief   设置最小可见文本大小
	void SetMinVisibleTextSize(UGdouble dVisibleTextSizeMin);		
	//! \brief   得到最大可见文本大小
	UGdouble GetMaxVisibleTextSize()const;							
	//! \brief   设置最大可见文本大小
	void SetMaxVisibleTextSize(UGdouble dVisibleTextSizeMax);		

	//! \brief   设置最大可见比例
	void SetMapMaxScale(UGdouble dMaxScale);
	//! \brief   得到最大可见比例
	UGdouble GetMapMaxScale() const;
	//! \brief   设置最小可见比例
	void SetMapMinScale(UGdouble dMinScale);
	//! \brief   得到最小可见比例
	UGdouble GetMapMinScale() const;

	//! \brief   是否动态投影
	UGbool IsProjectionOnTheFly()const;									
	//! \brief   设置动态投影
	void SetProjectionOnTheFly(UGbool bProjectionOnTheFly = true);	
	
	//! \brief   是否扩大查询范围
	UGbool IsInflateBounds();									
	void SetInflateBounds(UGbool bIsMapInflated = true);	

	//! \brief   判断是否处于忙碌阶段，是否允许中断等操作
	UGbool IsBusy()const;							
	//! \brief   设置处于忙碌阶段，不允许中断等操作
	void SetBusy(UGbool bBusy = true);	

	UGbool IsBusyEnable()const;							
	void SetBusyEnable(UGbool bBusyEnable = true);	

	//! \brief   得到背景风格
	const UGStyle& GetBkStyle()const;								
	//! \brief   设置背景风格
	void SetBkStyle(const UGStyle& style);							
	//! \brief   得到旋转角度
	double GetAngle()const;											
	//! \brief   设置旋转角度
	void SetAngle(double dAngle);									

	//! \brief   是否绘制背景
	UGbool IsPaintBackground() const;
	//! \brief   设置是否绘制背景
	void SetPaintBackground(UGbool bPaintBackground = true);
	
	//! \brief   读取地图的XML信息
	UGbool FromXML(const UGString& strXML, UGbool bIgnoreLayerCaption = true, UGint nVersion = 0, UGbool bIgnoreLayers = false);
	//! \brief   保存地图为XML
	UGString ToXML(UGint nVersion = 0)const;
	//! \brief   打开工作空间中指定的地图
	UGbool Open(const UGString& strMap);
	//! \brief   打开XML信息中指定的地图
	UGbool OpenXML(const UGString& strXML, UGbool bIgnoreLayerCaption = true, UGint nVersion = 0, UGbool bIgnoreLayers = false);
	//! \brief   另存为工作空间中指定的地图
	UGbool SaveAs(const UGString& strMap, UGbool bOverWrite = false);	
	//! \brief   保存地图
	UGbool Save();


	UGbool OpenDataset();


	//! \brief   判断是否有selection需要高亮
	UGbool RequireHighlightSelection();
	//! \brief   高亮所有图层的m_Selection
	void HighlightSelection(UGGraphics* pGraphics);
	//! \brief   绘制背景
	UGbool PaintBackground(UGGraphics* pGraphics, UGRect rcErase);
	//! \brief 绘制背景网格
	UGbool DrawBKGrid(UGGraphics* pGraphics/*,UGMap::UGTypeOption nTypeGrid = UGMap::UGGridGrid*/);
	
	//! \brief 设置网格最大值.
	//! \param nMaxGrid 网格最大值[in]。
	//! \remarks nMaxGrid 为大于0的整数值，建议在60--100内，过大会影响效率，过小有不美观。
	//! \attention 。
	void SetMaxGrid(UGint nMaxGrid);	
	//! \brief 获取网格最大值
	UGint GetMaxGrid();
// 	//! \brief 设置网格size地理坐标
// 	void SetMpExtend(UGSize2D& sz2DExtend);
// 	UGSize2D GetMpExtend();
	//! \brief 设置网格size设备坐标
	void SetGridExtend(const UGSize2D& szExtend);
	//UGSize GetDpExtend();
	UGSize2D GetGridExtend();
	//! \brief 设置绘制范围
	void SetGridRect(UGRect2D& rcGrid);
	UGRect2D GetGridRect();
	//! \brief 设置绘制网格类型
	void SetGridType(UGGridType nGridType);
	UGGridType GetGridType();
	//! \brief 是否固定网格
	void SetFixedGrid(UGbool bFixed = true);
	UGbool IsFixedGrid();
	//! \brief 设置显示网格
	void SetShowGrid(UGbool bShowGrid);
	UGbool IsShowGrid();
	//! \brief   绘制地图
	/**
	\param pGraphics				绘制到的Graphics[in]
	\param rcDevBounds				所需绘制的设备范围[in]
	\param rcInvalid				用于指定内部仅进行新绘制的内容，是通过修改逻辑范围来实现的，需要外部进行还原[in]
	\param pbBlank					是否是白图[out]
	\param bIsPrinting				是否打印[in]
	\param bFitToPage				是否合适一页的打印大小，只用于打印[in]
	\param bMapModeInitialize		是否初始化地图模式[in]
	\param pProgress				进程条参数[in]
	\param bOnlyPaintBackground		是否只绘制背景
	\return 绘制是否成功
	*/
	UGbool OnDraw(UGGraphics* pGraphics, UGRect rcDevBounds, UGRect rcInvalid, UGbool *pbBlank = NULL,
		UGbool bIsPrinting = false, UGbool bFitToPage = false, 
		UGbool bMapModeInitialize = true, UGProgress* pProgress = NULL,
		UGbool bOnlyPaintBackground = false);

	//! \brief   矢量打印地图
	/**
	\param pGraphics				打印到的Graphics[in]
	\param rcDevBounds				打印到的设备范围[in]
	\param rcMapBounds				地图范围[in]
	\param dPrintScale				设置打印的比例[in]
	\param bCentered				是否按照的设备范围的中心打印[in]
	\param bMapModeInitialize		是否初始化地图模式[in]
	\param bPaintBackground			是否打印背景[in]
	\param bLytClip					是否是布局不规则地图打印裁剪【in】
	\return 打印是否成功
	*/
	UGbool OnPrint(UGGraphics* pGraphics, UGRect rcDevBounds, const UGRect2D& rcMapBounds,
		UGdouble dPrintScale, UGbool bCentered = true, UGbool bMapModeInitialize = true, 
		UGbool bPaintBackground = false, UGbool bShowGrid = false, UGbool bLytClip = false);
	
	//! \brief   栅格化打印地图
	/**
	\param pGraphics				打印到的Graphics[in]
	\param rcDevBounds				打印到的设备范围[in]
	\param rcMapBounds				将要打印的地图范围[in]
	\param dPrintScale				设置打印的比例[in]
	\param dDPIScale				我们的模拟的DPI与打印机的实际DPI的比值
	\param bCentered				是否按照设备范围的中心打印[in]
	\param bMapModeInitialize		是否初始化地图模式[in]
	\param bPaintBackground			是否打印背景[in]
	\return 打印是否成功
	*/
	UGbool OnPrintRaster(UGGraphics* pGraphics, UGRect rcDevBounds, 
		const UGRect2D& rcMapBounds, UGdouble dPrintScale,UGdouble dDPIScale = 1, 
		UGbool bCentered = true, UGbool bMapModeInitialize = true, 
		UGbool bPaintBackground = false,UGbool bShowGrid = false);
	
	//! \brief   绘制几何对象
	/**
	\param pGraphics				绘制到的Graphics[in]
	\param pGeometry				绘制的几何对象[in]
	\param pStyle					绘制风格[in]
	\return 
	*/
	UGbool DrawGeometry(UGGraphics* pGraphics, UGGeometry* pGeometry, UGStyle* pStyle = NULL);

	//! \brief   输出为地图
	/**
	\param pGraphics				绘制到的Graphics[in]
	\param rcBounds					绘制图片大小[in]
	\param pbBlank					绘制的图片是否是白图[out]
	\param bNoBackground			是否绘制背景[in]
	\param bClipContent				没有用到[in]
	\param bCopyFromCache			没有用到[in]
	\param bEntireMap 				是否整幅输出[in]
	\param pProgress 				用于计算输出进度条信息[in] add by wangna，2011-10-5
	\return 输出地图是否成功
	*/
	UGbool OutputMap(UGGraphics* pGraphics, UGRect rcBounds, UGbool *pbBlank = NULL, UGbool bNoBackground = false, 
		UGbool bClipContent = false, UGbool bCopyFromCache = false, UGbool bEntireMap = false, UGProgress *pProgress = NULL);

	//! \brief   输出为地图
	/**
	\param pGraphics				绘制到的Graphics[in]
	\param rcBounds					绘制图片大小[in]
	\param bTranspencyBackGroud		是否背景透明[in]
	\param bBkgColorTranspency		是否背景色透明[in]
	\return 输出地图是否成功
	*/
	UGbool OutputMapToMemory(UGGraphics* pGraphics, UGRect rcBounds, UGbool bTranspencyBackGroud = false, UGbool bBkgColorTranspency = false);

	//! \brief   输出跟踪图层
	/**
	\param pGraphics				绘制到的Graphics[in]
	\param rcBounds					绘制图片大小[in]
	\param nTransparentColor		透明色（背景色）[in]
	\param bClipContent				没有用到[in]
	\param bEntireMap 				是否整幅输出[in]
	\return 输出地图是否成功
	*/
	UGbool OutputTrackingLayer(UGGraphics* pGraphics, UGRect rcBounds, 
		UGColor nTransparentColor = UGRGB(1,1,1), UGbool bClipContent = false,
		UGbool bEntireMap = false);

	//! \brief   输出跟踪图层(设置DPI)
	/**
	\param pGraphics				绘制到的Graphics[in]
	\param strFileName				输出文件名称[in]
	\param rcBounds					绘制图片大小[in]
	\param nDPI                     输出跟踪图层的DPI[in]
	\param nTransparentColor		透明色（背景色）[in]
	\param nCompress				输出图片的压缩率[in]
	\param bEntireMap 				是否整幅输出[in]
	\return 输出地图是否成功
	*/
#if !defined SYMBIAN60 && !defined  OS_ANDROID && !defined (IOS)
	UGbool OutputTrackingLayerEx(UGGraphics* pGraphics, const UGString& strFileName, 
		UGRect2D rcBounds, UGint nDPI = 200, UGColor nTransparentColor = UGRGB(1,1,1),
		UGint nCompress = 75, UGbool bEntireMap = false);


	//! \brief   输出设备图层
	/**
	\param pGraphics				绘制到的Graphics[in]
	\param rcBounds					绘制图片大小[in]
	\param nTransparentColor		透明色（背景色）[in]
	\param bClipContent				没有用到[in]
	\param bEntireMap 				是否整幅输出[in]
	\return 输出地图是否成功
	*/
	UGbool OutputUGDeviceTrackingLayer(UGGraphics* pGraphics, UGRect rcBounds, 
		UGColor nTransparentColor = UGRGB(1,1,1), UGbool bClipContent = false, 
		UGbool bEntireMap = false);

	//! \brief   输出设备图层
	/**
	\param pGraphics				绘制到的Graphics[in]
	\param strFileName				输出文件名称[in]
	\param rcBounds					绘制图片大小[in]
	\param nDPI                     输出设备图层的DPI[in]
	\param nTransparentColor		透明色（背景色）[in]
	\param nCompress				输出图片的压缩率[in]
	\param bEntireMap				是否整幅输出[in]
	\return 输出地图是否成功
	*/
	UGbool OutputUGDeviceTrackingLayerEx(UGGraphics* pGraphics, 
		const UGString& strFileName, UGRect2D rcBounds, UGint nDPI = 200,
		UGColor nTransparentColor = UGRGB(1,1,1), 
		UGint nCompress = 75, UGbool bEntireMap = false);
#endif
	//! \brief   输出为地图
	/**
	\param pGraphics				绘制到的Graphics[in]
	\param szBitmap					绘制图片大小[in]
	\param strFileName				图片输出的路径和名称[in]
	\param bEntireMap				是否整幅输出[in]
	\param strDescription			文件描述
	\param nImageType				图片类型 ,可以时emf、wmf[in]
	\remarks EMF与WMF格式仅支持Windows平台
	\return 输出地图是否成功
	*/
	UGbool OutputMapToEMF(UGGraphics* pGraphics, UGSize szBitmap, 
		const UGString& strFileName, UGString& strDescription,
		UGbool bEntireMap = false, UGint nImageType = UGFileType::EMF);

#if !defined SYMBIAN60 && !defined  OS_ANDROID && !defined (IOS)
	//! \brief   输出为地图
	/**
	\param pGraphics				该Graphics仅用来提供色彩位深信息用来创建兼容的Graphcis，可以为NULL[in]
	\param szBitmap					绘制图片大小，DP[in]
	\param strFileName				图片输出的路径和名称[in]
	\param nImageType				图片类型[in]
	\param bEntireMap				是否整幅输出[in]
	\param nCompress  				是否压缩,目前仅支持jpg[in]
	\param bTranspencyBackGroud		是否透明背景[in]
	\param pbigCache				输出到大文件缓存
	\return 输出地图是否成功
	*/
	UGbool OutputMapToFile(UGGraphics* pGraphics, UGSize szBitmap,
		const UGString& strFileName, UGint nImageType, UGbool bEntireMap = false, 
		UGint nCompress = 100, UGbool bTranspencyBackGroud = FALSE,
		UGCacheFile* pbigCache=NULL);

	//! \brief   输出为地图
	/**
	\param pGraphics				该Graphics仅用来提供色彩位深信息用来创建兼容的Graphcis，可以为NULL[in]
	\param strFileName				图片输出的路径和名称[in]
	\param nImageType				图片类型[in]
	\param rcBounds					输出地图的地理范围，MP[in]
	\param nDPI						输出地图的DPI
	\param nCompress  				是否压缩[in]
	\param bShowProgress			是否显示进度条
	\param bTranspencyBackGroud     是否背景透明
	\return 输出地图是否成功
	*/
	UGbool OutputMapToFileEX(UGGraphics* pGraphics, const UGString& strFileName, UGint nImageType,UGRect2D& rcBounds, UGint nDPI = 200, UGint nCompress = 75, UGbool bShowProgress = true, UGbool bTranspencyBackGroud = false);
#endif
	//! \brief   输出为地图
	/**
	\param pGraphics				绘制到的Graphics[in]
	\param pDestDataSource			绘制的数据源[in]
	\param strDatasetName			绘制的数据源中数据集名[in]
	\param dResolution				绘制的比例[in]
	\param rcBounds					显示范围[in]
	\param pbBlank					生成的是否是空白图[out]
	\param bShowProgress   			是否显示进度条[in]
	\param nEncType [in] 编码方式。
	\return 输出地图是否成功
	*/
	UGDatasetRaster* OutputMapEx(UGGraphics* pGraphics, UGDataSource* pDestDataSource, 
		const UGString& strDatasetName, double dResolution, UGRect2D& rcBounds, UGbool *pbBlank = NULL,
		UGbool bShowProgress = true, UGDataCodec::CodecType nEncType = UGDataCodec::encNONE);

	//! \brief 输出为地图为影像数据集。
	//! \param *pGraphics [in]。
	//! \param pDestDataSource 数据源[in]。
	//! \param strDatasetName 数据集名字[in]。
	//! \param dResolution 绘制的比例[in]。
	//! \param rcBounds 显示范围[in]。
	//! \param bShowProgress 是否显示进度条[in]。
	//! \param nEncType [in] 编码方式。
	//! \param bBlank	[out] 生成的是否是空白图
	//! \return 。
	//! \remarks 。
	//! \attention 。
	//UGDatasetRaster* OutputMap(UGGraphics *pGraphics,UGDataSource * pDestDataSource,
	//const UGString& strDatasetName, UGdouble dResolution,
	//UGRect2D& rcBounds, UGbool bShowProgress,UGDataCodec::CodecType nEncType, UGbool &bBlank);

	//! \brief   输出为地图
	/**
	\param pGraphics				绘制到的Graphics[in]
	\param strFileName				图片输出路径和名称[in]
	\param rcBounds					显示范围[in]
	\param nDPI						图片类型[in]
	\param bShowProgress 			是否显示进度条[in]
	\return 输出地图是否成功
	*/
	UGbool OutputMapToBMP(UGGraphics* pGraphics, const UGString& strFileName, 
		UGRect2D& rcBounds, UGint nDPI = 200, UGbool bShowProgress = true);
	
	//! \brief   输出地图为eps文件
	/**	
	//! \param strFileName				图片输出路径和名称[in]	
	//! \param bTextToVector			是否将文字矢量化[in]	
	//! \param bEntireMap				是否全幅输出[in]	
	//! \return 输出地图是否成功
	//! \attion 目前EPS不支持半透明，面填充等效果。
	*/
	UGbool OutputMapToEPS(UGSize szBitmap, const UGString& strFileName, 
		UGbool bTextToVector = false, UGbool bEntireMap = false);

	//{{added by macx 2008.7 输出PDF接口
	//! \brief   输出地图为PDF文件 
	/**	
	//! \param strFileName				图片输出路径和名称[in]	
	//! \param bTextToVector			是否将文字矢量化[in]	
	//! \param bEntireMap				是否全幅输出[in]	
	//! \return 输出地图是否成功
	*/
	UGbool OutputMapToPDF(UGSize szBitmap, const UGString& strFileName, const UGchar* optlist = NULL, const UGchar* optlist_page = NULL, UGbool bDeviceTrackingLayer = FALSE, UGbool bTrackingLayer = FALSE, UGbool bEntireMap = false);
	//!brief 原始状态输出到PDF，Image输出
	UGbool OutputImageToPDF(UGSize szBitmap, const UGString& strFileName, const UGchar* optlist = NULL, const UGchar* optlist_page = NULL, UGbool bDeviceTrackingLayer = FALSE, UGbool bTrackingLayer = FALSE, UGbool bEntireMap = false);
	
	//! \brief 输出PDF的总接口接口。
	//! \param szBitmap  范围[in]。
	//! \param strFileName 输出路径和名称[in]。
	//! \param nTypeOption 输出类型，以矢量还是栅格形式[in]。
	//! \param nStyle 包含风格设置，如是否含有线符号，仅在nTypeOption为NOMAL时有用[in]。
	//! \param optlist 文档属性设置[in]。
	//! \param optlist_page 页面设置[in]。
	//! \param bEntireMap	是否全幅输出[in]。
	//! \return 是否成功
	UGbool OutputToPDF(UGSize szBitmap, const UGString& strFileName,
		UGint nTypeOption, UGint nStyle = UG_STYLE_ALLSTYLE, 
		const UGchar* optlist = NULL, const UGchar* optlist_page = NULL, 
		UGbool bDeviceTrackingLayer = FALSE, UGbool bTrackingLayer = FALSE, 
		UGbool bEntireMap = false);	
	//}}

	//!brief 原始状态输出到XPS，Image输出,Add by tangzq in 2009-2-22
	//! \brief 输出PDF的总接口接口。
	//! \param szBitmap  范围[in]。
	//! \param strFileName 输出路径和名称[in]。
	//! \param nTypeOption 输出类型，以矢量还是栅格形式[in]。
	//! \param nStyle 包含风格设置，如是否含有线符号，仅在nTypeOption为NOMAL时有用[in]。
	//! \param optlist 文档属性设置[in]。
	//! \param optlist_page 页面设置[in]。
	//! \param bEntireMap	是否全幅输出[in]。
	UGbool OutputMapToXPS(UGSize szBitmap, const UGString& strFileName, 
		const UGchar* optlist = NULL, const UGchar* optlist_page = NULL,
		UGbool bEntireMap = false);

	UGbool OutputToXPS(UGSize szBitmap, const UGString& strFileName, 
		UGint nTypeOption, UGint nStyle = UG_STYLE_ALLSTYLE, 
		const UGchar* optlist = NULL, const UGchar* optlist_page = NULL,
		UGbool bEntireMap = false);

	//! \brief   得到地图比例尺
	UGdouble GetScale()const;
	//! \brief   设置地图比例尺
	//! \brief   返回设置比例尺是否成功，modified by zhengyl at 2011-9-2 在dScale为0时返回false
	UGbool SetScale(UGdouble dScale);
	//! \brief   得到地图中心点
	UGPoint2D GetCenter()const;										
	//! \brief   设置地图中心点
	void SetCenter(const UGPoint2D& pntCenter);						

	//! \brief   平移
	void Pan(UGdouble dOffsetX, UGdouble dOffsetY);
	//! \brief   放大、缩小
	void Zoom(UGdouble dZoomRatio);
	//! \brief   整幅
	UGbool ViewEntire(const UGRect rcDevice = UGRect(0,0,0,0));
	
	//! \brief   获取地图范围
	UGRect2D GetBounds()const;
	//! \brief   得到地图显示范围
	UGRect2D GetViewBounds()const;
	//! \brief   设置地图显示范围。如果没有设置固定比例尺，则就设置成参数所制定的；否则，查找并设置成与参数最接近的固定比例尺。
	void SetViewBounds(const UGRect2D& rcMapViewBounds,UGbool bByWidth = false);

	//! \brief   鼠标点击事件
	UGbool HitTest(UGPoint2D pntHitTest, UGdouble dTolerance, UGbool bAppendMode = false,
		UGbool bControlMode = false, UGbool bShiftMode = false);
	//! \brief   得到绘制类
	UGDrawing* GetDrawing();

	//added by xielin 2007-04-13
	//! \brief 设置是否允许多图层编辑模式 
	void SetMultiLayerEditEnable(UGbool bMultiLayerEditEnable);
	//added by xielin 2007-04-13
	//! \brief 返回是否允许多图层编辑模式 
	UGbool IsMultiLayerEditEnable();


	
	//added by xielin 2007-04-13
	//! \brief 设置是否允许编辑过程中提示 
	void SetShowTrackingTooltips(UGbool bTrackingTooltips);
	//added by xielin 2007-04-13
	//! \brief 返回是否允许编辑过程中提示 
	UGbool IsShowTrackingTooltips();
	
	//added by xielin 2007-04-13

	//! \brief 设置当前图层，用于多图层编辑，在多图层编辑中，因为允许多个图层同时编辑，如果设定当前图层后，添加的对象就放到
	//! 设置的当前图层中，如果不设置当前图层，默认就是可编辑的第一个图层 
	void SetCurrentLayer(UGLayer* pLayer);

	//added by xielin 2007-04-13
	//! \brief 获取当前图层，用于多图层编辑，在多图层编辑中，因为允许多个图层同时编辑，如果设定当前图层后，添加的对象就放到
	//!设置的当前图层中，如果不设置当前图层，默认就是可编辑的第一个图层 
	UGLayer* GetCurrentLayer();

	//! \brief 获取地图对象的hashcode
	UGString GetHashCode(UGint nImageFileType) const;

	//! \brief 得到设置是否使用显示裁剪区域
	UGbool IsDisplayClip() const;						
	//! \brief 得到是否使用显示裁剪区域
	void SetDisplayClip(UGbool bIsDisplayClip);			

	//! \brief 得到显示裁剪区域
	void GetDisplayClipRegion(UGGeoRegion& geoClipRegion) const;
	//! \brief 得到是否使用显示裁剪区域
	void SetDisplayClipRegion(UGGeoRegion& geoClipRegion);

	//! \brief 是否显示用户指定范围
	UGbool IsUserEntireBounds();
	//! \brief 设定是否显示用户指定范围
	void SetIsUserEntireBounds(UGbool bIsUserEntireBounds);

	//! \brief 得到用户指定显示范围
	UGRect2D GetUserEntireBounds();
	//! \brief 用户指定显示范围
	void SetUserEntireBounds(const UGRect2D& rc2UserEntireBounds);

	//! \brief 设置用户指定显示比例
	void ImportDisplayScales(UGString strXmlPath);
	//! \brief 得到用户指定显示比例
	void ExportDisplayScales(UGString strXmlPath);
	//! \brief 是否采用用户显示比例

	//! \brief 设置用户指定显示比例
	void SetDisplayScales(UGArray<UGdouble> arrDisplayScales);
	//! \brief 得到用户指定显示比例
	void GetDisplayScales(UGArray<UGdouble>& arrDisplayScales);
	//! \brief 是否采用用户显示比例
	void SetDisplayByScales(UGbool bDisplayByScales);
	//! \brief 设置是否采用用户显示比例
	UGbool IsDisplayByScales() const;
	//! \brief 获取/设置能显示的对象最大节点数，超过这个节点的对象就不显示
	UGint GetMaxVisibleVertex() const;
	void SetMaxVisibleVertex(UGint nMaxVisibleVertex);

	//added by xielin 2007-11-15 增加一个接口，用来设置绘制图层后是否马上释放记录集
	//! \brief 获取/设置绘制图层后是否马上释放记录集，默认iserver产品马上释放，组件桌面产品不马上释放，因为捕捉和选择都会用到显示的记录集
	void SetReleaseDisplayRecordset(UGbool bRelease = true);
	UGbool IsReleaseDisplayRecordset();

	UGbool OnSize(UGGraphics* pGraphics, const UGRect& rcNewClient);
	//modefied by macx 2008-9-27 地图的透明度
	//! \brief 设置map的透明度
	//! \param nTransPercent	透明度[in]
	void SetTransPercent(UGuint nTransPercent);
	//! \brief 获取map的透明度
	UGuint GetTransPercent();

	//! \brief 设置地图符号库信息
	//! \remarks 如果pResources为空，则设置地图符号库为空
	void SetMapResources(UGResources* pResources,UGbool bCopy = false);
	//! \brief 获取地图符号库信息
	UGResources* GetMapResources();
	//! \brief 设置是否采用地图符号库
	void SetUseMapResource(UGbool bIsUseMapSources = false);
	//! \brief 获取是否采用地图符号库
	//! \remarks 开启此功能且地图符号库信息不为空
	UGbool IsUseMapResource();
	
	//! \brief 设置背景网格的风格。
	//! \param style 网格的风格[in]。
	void SetGridStyle(const UGStyle& style);	
	//! \brief 获取背景网格的风格。
	UGStyle& GetGridStyle();
	//! \brief 设置背景网格间隔的风格。
	//! \param style 网格间隔的风格[in]。
	void SetGridSpaceStyle(const UGStyle& style);
	//! \brief 获取背景网格间隔的风格。
	UGStyle& GetGridSpaceStyle();

	//! \brief 设置地图全副显示的边界范围
	void SetMarginWidthViewEntire(UGint nMarginWidthViewEntire);
	//! \brief 获取地图全副显示的边界范围
	UGint GetMarginWidthViewEntire();
	
#if !defined SYMBIAN60 
	//! \brief 获取UGImage的数据。
	//! \param nType		[in]要转换的图片类型。
	//! \param pImage		[in]传入的UGIamge。
	//! \param ImageData	[in]获取的图像数据。
	//! \param bFree		[in]是否释放ImageData。
	//! \param bCopyFormCach [in]是否从屏幕拷贝
	//! \return 。
	//! \remarks 。
	//! \attention 使用完后要delete []imageData.pBits。
	static void ConvertImageData(UGint nType, UGImage* pImage, UGImageData& ImageData,UGbool& bFree, UGbool bCopyFormCach = false);
#endif
	//! \brief 该接口不对外开放
	void ZoomWhenFirstViewMap();
protected:	
	
	void SetMapOpenedFunc(MapOpenedProc pMapOpenedFunc, UGlong pMapWnd);
	void SendMapOpenedFunc();

	//! \brief 是否有涂层存在剪切域
	UGbool IsNeedLayerClip();

protected:

	//! \brief 绘制不同风格背景网格
	UGbool DrawGrid(UGGraphics* pGraphics,const UGPoint2D& pntStart,const UGPoint2D& pntEnd,const UGSize2D& szExtend,UGGridType nTypeGrid = UGMap::UGGridGrid);
	UGbool DrawGridGrid(UGGraphics* pGraphics,const UGPoint2D& pntStart,const UGPoint2D& pntEnd);
	UGbool DrawGridCross(UGGraphics* pGraphics,const UGPoint2D& pntStart,const UGPoint2D& pntEnd,const UGSize2D& szExtend);
	UGbool DrawGridPoint(UGGraphics* pGraphics,const UGPoint2D& pntStart,const UGPoint2D& pntEnd,const UGSize2D& szExtend);

	UGbool CopyResource(UGResources* pResources,UGbool bCopy = true);
	void SetResource(UGResources* pResources);
	UGbool OutputTrackingLayer(UGGraphics* pGraphics,UGTrackingLayer* pTrackingLayer, UGRect rcBounds, UGColor nTransparentColor, UGbool bClipContent, UGbool bEntireMap);
#if !defined SYMBIAN60 && !defined  OS_ANDROID && !defined (IOS)
	UGbool OutputTrackingLayerEx(UGGraphics* pGraphics,UGTrackingLayer* pTrackingLayer, const UGString& strFileName, UGRect2D rcBounds, UGint nDPI, UGColor nTransparentColor, UGint nCompress, UGbool bEntireMap);
	//{{ added by lidl 2009-5-7 出图时从UGImage里面获取数据
	
	//! \brief 获取UGImage的数据。
	//! \param pImage [in]传入的UGIamge。
	//! \param ImageData [in]获取的图像数据。
	//! \return 。
	//! \remarks 。
	//! \attention 使用完后要delete []imageData.pBits。
	static void GetBmpImageData(UGImage* pImage, UGImageData& ImageData,UGbool& bFree);

	//! \brief 获取UGImage的数据。
	//! \param pImage [in]传入的UGIamge。
	//! \param ImageData [in]获取的图像数据。
	//! \return 。
	//! \remarks 。
	//! \attention 使用完后要delete []imageData.pBits。
	static void GetJPGImageData(UGImage* pImage, UGImageData& ImageData,UGbool& bFree);	
#endif
	//! \brief 获取UGImage的数据。
	//! \param pImage [in]传入的UGIamge。
	//! \param ImageData [in]获取的图像数据。
	//! \param bCopyFormCach [in]是否从屏幕拷贝
	//! \return 。
	//! \remarks 。
	//! \attention 使用完后要delete []imageData.pBits。
	static void GetPngImageData(UGImage* pImage, UGImageData& ImageData,UGbool& bFree, UGbool bCopyFormCach = false);	

	//! \brief 获取UGImage的数据。
	//! \param pImage [in]传入的UGIamge。
	//! \param ImageData [in]获取的图像数据。
	//! \return 。
	//! \remarks 。
	//! \attention 使用完后要delete []imageData.pBits。
	static void GetGifImageData(UGImage* pImage, UGImageData& ImageData,UGbool& bFree);	
#if !defined SYMBIAN60 && !defined  OS_ANDROID && !defined (IOS)
	//! \brief 获取UGImage的数据。
	//! \param pImage [in]传入的UGIamge。
	//! \param ImageData [in]获取的图像数据。
	//! \param bFree [in]是否需要释放内存
	//! \return 。
	//! \remarks 。
	//! \attention 使用完后要delete []imageData.pBits。
	static void GetTiffImageData(UGImage* pImage, UGImageData& ImageData, UGbool& bFree);
	//}} added by lidl 2009-5-7 出图时从UGImage里面获取数据
#endif
public:
	//! \brief 图层集合
	UGLayers m_Layers;
	//! \brief 跟踪图层
	UGTrackingLayer m_TrackingLayer;

	//add by xiaoys 2012-0627
	UGTrackingLayerEx m_TrackingLayerEx;

#if !defined SYMBIAN60 && !defined  OS_ANDROID && !defined (IOS)
	//! \brief 设计跟踪图层
	UGDeviceTrackingLayer m_DeviceTrackingLayer;
#endif

	//! \brief 全幅边界
	UGint m_nMarginWidthViewEntire;
	//deleted by xielin 2007-05-16 改为每个layer都有一个m_Selection,该成员变量废弃掉
	//UGSelection	m_Selection;
	//added by xielin 2007-08-21 
	//! \brief 判断地图是否重新刷新。并且重新绘制对象了。在编辑的时候用到
	UGbool m_bRefresh;
	//! \brief MapOpened回调
	MapOpenedProc m_MapOpenedFunc;

	//! \brief 保存图层数据
	/**
	\param pDs						保存的UDB数据源[in]
	\param strFileName				保存路径[in]
	\param bOverWrite				是否强制覆盖[in]
	\param bUniteFile				是否合并成一个文件【in】
	\return 保存是否成功
	*/
	static UGbool SaveAsUDBFile(const UGDataSource* pDs,const UGString& strFileName ,
		UGbool bOverWrite,UGbool bUniteFile = false);
	
	//! \brief 
	void SendBeforeMapDrawFunc(UGbool& bCancel,UGGraphics* pGraphics);
	//! \brief 
	void SendAfterMapDrawFunc(UGGraphics* pGraphics);

	//! \brief 
	void SetBeforeMapDrawFunc(BeforeMapDrawProc pBeforeMapDrawFunc,UGlong pWnd);
	//! \brief 
	void SetAfterMapDrawFunc(AfterMapDrawProc pAfterMapDrawFunc,UGlong pWnd);

	//!brief 设置是否发送事件，默认为true
	void SetNeedSendEvent(UGbool bNeedSendEvent = true);
	//!brief 返回是否设置了发送事件
	UGbool IsNeedSendEvent();

	//!brief 设置是否是布局绘制，主要用于布局出图是的判断，默认为true
	void SetIsLayoutDraw(UGbool bLayoutDraw = true);
	//!brief 返回是布局绘制
	UGbool IsLayoutDraw();

	//! \brief 
	void SendSnapableChangedFunc();

	//! \brief 
	void SetSnapableChangedFunc(SnapableChangedProc pSnapableChangedFunc,UGlong pWnd);


//added by qianjn in 2009-8-26 10:05:19 增加原因：

	// 设置全幅地图
	UGbool SetViewGlobal(UGbool bViewGlobal);
	UGbool GetViewGlobal();
	
	// 是否在出图的时候关掉地图的动态效果 2010-11-11 qianjn 光棍节留念
	UGbool IsDisableDynamicEffect();
	UGbool SetDisableDynamicEffect(UGbool bDisable);

	// 是否在编辑的时候实时刷新,默认false，不实时刷新的话显示会错误，但是在大数据的时候比较快
	UGbool IsRealTimeRefresh();
	void SetRealTimeRefresh(UGbool bRealTimeRefresh);

	UGbool IsRefreshTrackingLayer();
	void SetRefreshTrackingLayer(UGbool bRefresh);

	// 是否平移刷新
	UGbool IsPanRefresh();
	void SetPanRefresh(UGbool bPanRefresh);

	// 保存并且禁用各个图层的动态效果。当前设置包括流动显示和自动避让两种效果。
	void SaveAndDisableDynamicEffectSettings();

	// 恢复先前保存的各个图层的动态效果。当前设置包括流动显示和自动避让两种效果。
	void RestoreDynamicEffectSettings();

	// 此函数已经被 SaveAndDisableDynamicEffectSettings() 和 RestoreDynamicEffectSettings() 代替。
	// 关掉地图的动态效果，bEnable为false时关掉动态效果，为ture时恢复。一定要在使用完及时恢复。
	// 该函数在禁用掉动态效果之前会保存各个图层动态效果的原始设置，之后再次调用该函数则将先前保存的设置全部恢复。
	// 如果在设置保存和恢复两次调用之间发生任何图层增减、改换顺序的操作，都会导致设置恢复时的未定义行为！
	//void EnableDynamicEffect(UGbool bEnable);

	//! \brief 判断地图中是否有网络地图图层
	UGbool IsWebMapFlag();
	void SetWebMapFlag(UGbool bHasWebMap);

	//! \return 更新地图绘制
	void UpdateMapDrawParam();
	//! \return 获取地图绘制参数
	UGbool GetMapDrawParam(UGdouble& dMapScale, UGRect2D& rcViewBounds);

	//! \brief 根据当前的 viewBounds 和 比例尺，发送获取网络地图服务图片请求
	void RequestTile(UGbool bPanMode = false, UGbool bForceUpdate = false);

	//! \brief 图层向数据集请求瓦片
	void RequestTileEx(UGdouble dScale, UGRect2D& rcBounds);

	//! \brief 更新缓存的ImageData
	UGbool UpdateCacheTile(UGint nExtTileSize = 1, UGbool bRemoveAll = true);

	//! \brief 获取当前服务瓦片DP-->LP的转换比率
	UGdouble GetTileCoordRatio();

	void SetFirstRefreshWebMapFlag(UGbool bFirstRefreshWebMap);
	UGbool GetFirstRefreshWebMapFlag();

	void SetRefreshWebMapFlag(UGbool bRefreshWebMap);
	UGbool GetRefreshWebMapFlag();

	//! \brief  设置延迟请求瓦片标志
	void SetDelayRequestFlag(UGbool bDelay = false);
	//! \brief  是否延迟请求瓦片
	UGbool IsDelayRequest() const;

	//! \brief  设置获取等待请求下载瓦片的时间
	void SetWaitRequestTime(UGint nWaitTime);
	UGint GetWaitRequestTime();

	UGbool IsDrawPermissionLogo(UGImageData& imageTarget, UGbool bCacheFile = false, UGbool bOutputMapToFile = true);

	// 把DrawPermissionLogo改为静态方法，在CacheBuilder中也能使用
	static void DrawPermissionLogo(UGGraphics* pGraphics, UGImageData& imageTarget);
	static UGImage* DrawPermissionLogo(UGGraphics* pGraphics, UGImage* pImageTarget);
	static void DrawPermissionLogo(UGGraphics* pGraphics, const UGSize& sz);

	//! \brief 设置/获取当前地图的DPI
	void SetMapDPI(UGdouble dMapDPI);
	UGdouble GetMapDPI();

	//! \brief 设置/获取是否使用全局系统的DPI，默认为false，false时使用地图设置的DPI
	UGbool IsUseSystemDPI();
	void SetUseSystemDPI(UGbool bUseSystemDPI);

	UGbool InitNetArithmetic();
	UGFishingNetArithmetic* GetNetArithmetic();

	void AdjustHighlightStyle(UGLayer* pLayer, UGStyle& style, const UGStyle& oldStyle, UGbool bCustomStyle = true);
	
	//!\ 判断含有网络地图图层的地图是否初始化了，包含多个网络地图图层的地图以第一层网络地图来初始化
	UGbool IsWebMapInited();
	//!\ 设置包含网络地图的地图初始化标志
	void SetWebMapInited();

	UGTrackingMap* GetTrackingMap();

	UGbool IsBackDataMap();
	void SetBackDataMap(UGbool bBackDataMap);

protected:
	static void DrawPermissionLogo(UGGraphics* pGraphics, UGbool bCacheFile = false);
	UGint GetRandNamber(UGint nMax = 0, UGint nMin = 5);

	//! \brief 判断图层或者符号是否有透明度设置
	UGbool IsHaveLayerOpaqueRate();

	UGbool m_bDisableDynamicEffect;
	UGDict<UGint, UGbool> m_aryDynamicEffect;
	std::queue<bool> m_queueFlow;	// 用来禁用动态效果时保存流动显示设置
	std::queue<bool> m_queueAutoAvoid;	// 用来禁用动态效果时保存自动避让设置
	UGbool m_bRealTimeRefresh;	// 是不是编辑的时候实时刷新,默认false，不实时刷新的话显示会错误，但是在大数据的时候比较快
	UGbool m_bPanRefresh;	// 是不是平移刷新
	UGbool m_bLayoutDraw;

	//! \brief 网络图层是否初始化了，有网络图层时，只能使用一个网络地图图层的参数，所以用此变量来标示 
	UGbool m_bWebLayerInited;

//added by qianjn in 2009-8-26 10:05:19 增加完毕

protected:	
	UGDrawing m_Drawing;

public:
	UGString m_strName;		// XXX change to be private

protected:	
	//! \brief 图层描述
	UGString m_strDescription;			
	
	//! \breif 刷新标志
	UGbool m_bForceToRefresh;

	//! \brief 更新标志
	UGbool m_bModified;

	UGPrjCoordSys m_PrjCoordSys;

	//! \brief 允许文本叠盖
	UGbool m_bAllowTextOverlap;	

	UGuint m_unOnTop;
	//UGbool m_bLabelAlwaysOnTop;			//标签专题图置顶
	//UGbool m_bGraduatedSymbolAlwaysOnTop;	//等级符号专题图置顶
	//UGbool m_bGraphAlwaysOnTop;			//统计专题图置顶
	UGbool m_bFirstTimeDraw;	

	//! \brief 供MapModeInitialize和MapModeRestore使用保存和恢复UGGraphics对象先前的映射模式和坐标原点
	UGint m_nSavedMapMode;
	UGPoint m_pntSavedWndOrg;

	UGbool m_bPaintBackground;

	//added by xielin 2007-04-13  
	//! \brief 允许显示编辑过程中的提示 
	UGbool m_bShowTrackingTooltips;

	UGbool m_bDisplayByScales;

	// 固定比例尺
	UGArray<UGdouble> m_arrDisplayScales;

	//! \brief 透明度
	UGint m_nTransPercent;
	//! \brief 网格捕捉的size
	//UGSize2D m_szExtend;
	UGlong m_pMapWnd;


// 	//! \brief 网格间隔,地理坐标
// 	UGSize2D m_sz2DExtend;
// 	//! \brief 网格间隔，设备坐标
// 	UGSize m_szExtend;
	//! \brief 网格的间隔方式,true使用设备坐标，false使用地理坐标
	UGbool m_bFixedGrid;
	UGSize2D m_szGridExtend;
	//! \brief 背景网格的方式
	UGGridType m_nGridType;
	//! \brief 周边空白
	UGRect2D m_rcGrid;
	//! \brief 格网最大个数
	UGint m_nMaxGrid;
	//! \brief 是否绘制网格
	UGbool m_bShowGrid;
	//! \brief 网格主线风格
	UGStyle m_styleGrid;
	//! \brief 网格间隔风格
	UGStyle m_styleSpace;

	//地图符号库信息
	UGResources* m_pResources;
	UGbool m_bIsUseMapSources;
	UGbool m_bNameNotEmpty;

	BeforeMapDrawProc m_pBeforeMapDrawFunc;
	AfterMapDrawProc m_pAfterMapDrawFunc;
	UGlong m_pEventView;  //调用事件回调函数的对象指针，统一为一个吧，节省内存

	SnapableChangedProc m_pSnapableChangedFunc;
	UGlong m_pSnapableChangedEvent;  


	UGbool m_bFireMapEvent;//是否需要发送控件的事件消息,added by xielin 地图编辑的时候有用，现在用回调函数来代替消息

	UGbool m_bViewGlobal;

	// 面对像是不是随着地图旋转而进行填充风格的旋转填充
	UGbool m_bIsFillAngle;

	//设置是否支持填充符号优化，add by tan，2011-1-11
	UGbool m_bIsSymbolFillIgnored;

	//记录当前出的图片序号，主要用于动态出图时是否显示水印
	UGint m_nOutputFileNumber;
	//记录随机的图片序号
	UGint m_nOutputFileRandNumber;

	// 新增控制变量，控制跟踪层刷新(修改有时先刷新地图然后调用刷新跟踪层后地图没有刷新的现象)
	UGbool m_bRefreshTrackingLayer; 

	// 以下是网络地图使用
	//是否是第一次刷新网络地图，解决第一次打开网络地图不刷新的问题
	UGbool m_bFirstRefreshWebMap;
	//! \brief 地图当前的比例尺(网络地图的多线程会使用)
	UGdouble m_dMapScale;
	//! \brief 地图当前的ViewBounds(网络地图的多线程会使用)
	UGRect2D m_rcMapViewBounds;
	//! \brief 用于同步m_dCoordRatio
	UGMutex	m_MutexCoordRatio;
	//是否刷新网络地图
	UGbool m_bRefreshWebMapFlag;
	//! \brief 用于对修改刷新进行加锁
	UGMutex	m_MutexRefreshWebMap;
	//! \brief 控制是否延迟发送网络地图请求
	UGbool m_bDelayRequest;

	//! \brief 出图等待下载瓦片延迟时间
	UGint m_nWaitRequestTime;
	
	//! \brief 用于封装计算渔网网格的算法
	UGFishingNetArithmetic* m_pNetArithmetic;

	//! \brief 用于封装地图业务数据的绘制(嵌入式使用)
	UGTrackingMap* m_pTrackingMap;

	// 判断是否是背景地图（嵌入式区分是否是背景地图还是业务地图）
	UGbool m_bBackDataMap;

private:
#if !defined OS_ANDROID && !defined IOS
	//! \brief 海图设置类 add by liufang
	UGChartSetting* m_pChartSetting;
#endif

};

}

#endif // !defined(AFX_UGMAP_H__37037E0D_8ABC_413E_B8BE_2B8916F0319E__INCLUDED_)

