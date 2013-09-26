// UGLayer.h: interface for the UGLayer class.
//
//////////////////////////////////////////////////////////////////////

/*!
   **************************************************************************************
    \file     UGLayer.h 
   **************************************************************************************
    \author   陈国雄
    \brief    图层类，负责数据集对象显示和专题图显示。                                                                       
    \attention   
   ----------------------------------------------------------------------------------<br>
    Copyright (c) 2000-2010 SuperMap Software Co., Ltd.                           <br>
    All Rights Reserved.                                                             <br>
   ----------------------------------------------------------------------------------<br> 
   
   **************************************************************************************
    \version 2005-05-20  陈国雄    初始化版本.                                       <br>
   **************************************************************************************
*/

#if !defined(AFX_UGLAYER_H__A4B430F7_6A63_4275_BB13_EF15BA12DDAD__INCLUDED_)
#define AFX_UGLAYER_H__A4B430F7_6A63_4275_BB13_EF15BA12DDAD__INCLUDED_

#include "Drawing/UGDrawing.h"
#include "Engine/UGDataSource.h"
#include "Map/UGTheme.h"
#include "Map/UGSelection.h"
#include "Map/UGThemes.h"
#include "Stream/ugdefs.h"
#if !defined SYMBIAN60 && !defined  OS_ANDROID && !defined (IOS)
#include "Representation/UGRepresentation.h"
#endif

namespace UGC {

class UGProgress;
class UGLayers;
class UGWebMapStub;

//! \brief AfterGeometryDraw 事件回调函数
typedef void (UGSTDCALL *AfterGeometryDrawProc)(UGlong pWnd,UGString strLayerName,UGGeometry* pGeoGeometry,UGGraphics* pGraphics);
//! \brief AfterGeoMapDraw 事件回调函数
typedef void (UGSTDCALL *AfterGeoMapDrawProc)(/*UGlong pWnd,*/UGDataset *pDataset, UGRecordset *pDisplayRecordset, UGGeometry* pGeometry);
//! \brief BeforeGeometryDraw 事件回调函数
typedef void (UGSTDCALL *BeforeGeometryDrawProc)(UGlong pWnd,UGbool& bCancel,UGString strLayerName,UGGeometry* pGeoGeometry,UGGraphics* pGraphics);
//! \brief BeforeLytGeometryDraw 事件回调函数
typedef void (UGSTDCALL *BeforeLytGeometryDrawProc)(UGlong pWnd,UGbool& bCancel,UGGeometry* pGeoGeometry/*,UGGraphics* pGraphics*/);
typedef UGArray<UGbyte> UGbyteArray;

enum UGLayerOptions
{
	//! \brief 是否显示
	UG_LO_VISIBLE						=	0x00000001,	
	//! \brief 是否可选择
	UG_LO_SELECTABLE					=	0x00000002,	
	//! \brief 是否可编辑
	UG_LO_EDITABLE						=	0x00000004,	
	//! \brief 是否可捕捉
	UG_LO_SNAPABLE						=	0x00000008,
	//! \brief 是否缩放符号
	UG_LO_SYMBOL_SCALABLE				=	0x00000010,	
	//! \brief 是否完整显示线型虚实部
	
	UG_LO_LINE_ADJUST   				=	0x00000100,	
	//! \brief 是否在显示的时候按ID排序,只对SDX引擎数据有效(SDB,DGN已经默认按照ID排序)
	UG_LO_KEEP_ORDER					=	0x00000020,	
	//! \brief 是否在3D窗口中立体显示，如果立体显示，就需要设定高度字段 m_strHeightField
	UG_LO_IS_3D							=	0x00000040,	
	//! \brief 是否已经修改，是否需要保存
	UG_LO_IS_MODIFIED					=   0x00000080, 
	
	//! \brief 是否是数据库引擎数据，与SDB相对应
	UG_LO_DATABASE_MODE					=	0x00040000,
	//! \brief 是否是SuperMap的数据库引擎
	UG_LO_SPATIAL_DB_MODE				=	0x00080000, 
	//! \brief 是否在显示的时候需要检查bounds
	UG_LO_NEED_CK_GEO_BOUND				=	0x00100000,	
	
	//! \brief 编辑锁定
	UG_LO_EDITABLE_LOCK					=   0x00200000, 
	//! \brief 是否是虚拟图层 
	UG_LO_IS_VIRTUAL					=   0x01000000, 
	//! \brief false:不需要图层缓存，true：需要图层缓存
	UG_LO_USE_LAYER_CACHE				=   0x02000000, 
	//! \brief 图层缓存是否需要刷新
	UG_LO_CACHE_NEED_REFRESH			=   0x04000000, 
	//! \brief 是否允许显示重叠文本
	UG_LO_ALLOW_TEXT_OVERLAP			=	0x10000000,	
	//added by dongfei 2007-04-27
	//! \brief 是否定制图层内的对象压盖顺序
	UG_LO_IS_ORDER_OVERLAP		    	=   0x20000000,	
	
	
	//! \brief 是否使用显示裁剪区域
	UG_LO_IS_DISPLAYCLIP				=   0x40000000, 
	//! \brief 是否使用道路优化显示
	UG_LO_CROSSROAD_OPTIMIZED			=   0x80000000 
};

struct ScaleStyle
{	
	UGdouble dMinScale;
	UGdouble dMaxScale;
	UGStyle  style;
} ;


#ifdef SYMBIAN60
class MAP_APIC UGLayer
#else
class MAP_API UGLayer
#endif
{
public:
	enum UGLayerType
	{
		//! \brief 普通图层
		UG_Layer_Normal                     = 1,
		//! \brief 网络线层
		UG_Layer_NetworkLine                = 2,
		//! \brief 网络点层
		UG_Layer_NetworkPoint               = 3,
		//! \brief 拓扑错误父层
		UG_Layer_TopoParent                 = 4,
		//! \brief 拓扑错误数据层
		UG_Layer_TopoLayer                  = 5,
		//! \brief 拓扑错误点层
		UG_Layer_TopoPointError             = 6,
		//! \brief 拓扑错误点层
		UG_Layer_TopoPointException         = 7,
		//! \brief 拓扑错误线层
		UG_Layer_TopoLineError              = 8,
		//! \brief 拓扑错误线层
		UG_Layer_TopoLineException          = 9,
		//! \brief 拓扑错误面层
		UG_Layer_TopoRegionError            = 10,
		//! \brief 拓扑错误面层
		UG_Layer_TopoRegionException        = 11,
		//! \brief 拓扑脏区，暂没使用
		UG_Layer_TopoDirty                  = 12,
		//! \brief 海图图层
		UG_Layer_Chart		                = 13,
		//修改后不再有子层的类型
		//UG_Layer_Child                      = 13,//子层
		UG_Layer_SCM		                = 14,
		//! \brief 海图子图层
		UG_Layer_ChartChild					= 15
	};
	


public:
	MAP_APIF UGLayer();
	virtual MAP_APIF ~UGLayer();
	MAP_APIF UGLayer(const UGLayer& layer);	
	MAP_APIF UGLayer& operator =(const UGLayer& layer);	

public:	
	//*********属性Options***********//
	//! \brief 某中选项是否可用
	MAP_APIF UGbool Enable(UGLayerOptions unOptions);
	//! \brief 是否设置某中选择
	MAP_APIF UGbool IsSupportOptions(UGLayerOptions unOptions)const;
	//! \brief 设置使用某中选择
	virtual MAP_APIF void SetOptions(UGLayerOptions unOptions);
	//! \brief 设置禁用某中选择
	virtual MAP_APIF void UnsetOptions(UGLayerOptions unOptions);	
	//! \brief 得到图层选择设置的信息
	MAP_APIF UGuint GetOptionsInfo()const;
	//! \brief 设置图层选择的信息
	MAP_APIF void SetOptionsInfo(UGuint unOptions);

	//! \brief 是否显示
	MAP_APIF UGbool IsVisible()const;
	//! \brief 设置为可显示
	MAP_APIF void SetVisible(UGbool bVisible = true);

	//! \brief 是否可以选择
	MAP_APIF UGbool IsSelectable()const;	
	//! \brief 设置为可选择
	MAP_APIF void SetSelectable(UGbool bSelectable = true);			

	//! \brief 是否可以编辑
	MAP_APIF UGbool IsEditable()const;
	//added by xielin 2007.8.9
	//! \brief  设置是否可以编辑
	//! \remarks 这个最好内部使用，外部就调用UGLayers::SetEditableLayer
	virtual MAP_APIF void SetEditable(UGbool bEditable = true);

	//! \brief 是否可以捕捉
	MAP_APIF UGbool IsSnapable()const;									// 是否可以捕捉
	//! \brief 设置为可捕捉
	MAP_APIF void SetSnapable(UGbool bSnapable = true);				// 

	//! \brief 是否锁定编辑
	MAP_APIF UGbool IsEditableLock()const;
	//! \brief 设置锁定编辑
	MAP_APIF void SetEditableLock(UGbool bEditableLock = true);   

	//! \brief 是否符号随着图层的缩放而缩放
	MAP_APIF UGbool IsSymbolScalable()const;
	//! \brief 设置符号可缩放
	MAP_APIF void SetSymbolScalable(UGbool bSymbolScalable = true);

	//! \brief 线型绘制时是否完整显示虚实部。
	//! \return 是否完整显示虚实部，1代表是，0代表否，默认为1。
	MAP_APIF UGbool IsLineAdjust() const;
	//! \brief 线型绘制时设置完整显示虚实部。
	/**
	设定是否完整显示虚实部，在放大缩小时都能完整显示线型。
	\param bFixed  是否完整显示虚实部[in]
	\remarks 默认下绘制线型会采用此方法。
	*/
	MAP_APIF void SetLineAdjust(UGbool bLineAdjust = true);

	//! \brief 是否对象显示时候按照ID排序
	MAP_APIF UGbool IsKeepOrder()const;	
	//! \brief 设置对象显示时候是否按ID排序
	MAP_APIF void SetKeepOrder(UGbool bKeepOrder = true);		

	//! \brief 本图层的设置是否修改过
	MAP_APIF UGbool IsModified()const;		
	//! \brief 设置图层修改标志
	MAP_APIF void SetModifiedFlag(UGbool bModified = true);

	//! \brief 返回是否允许图层缓冲区
	MAP_APIF UGbool IsAllowCache()const;		
	//! \brief 设置是否允许图层缓冲区
	MAP_APIF void SetAllowCache(UGbool bCache = true);				
	
	//! \brief 取得图层刷新标记
	MAP_APIF UGbool GetRefreshFlag()const;								
	//! \brief 设置图层刷新标志，强制刷新图层
	MAP_APIF void SetRefreshFlag(UGbool bRefresh = true);			
	
	//! \brief 图层的缓冲区是否可用
	MAP_APIF UGbool IsCacheAvailable()const;						
	//*********显示属性Options***********//

	//! \brief 得到栅格不透明度
	MAP_APIF UGint GetRasterOpaqueRate()const;					
	//! \brief 设置栅格不透明度
	MAP_APIF void SetRasterOpaqueRate(UGint nRasterOpaqueRate);		
	
	//! \brief 设置图层风格
	MAP_APIF void SetStyle(const UGStyle& style);
	//! \brief 得到栅格不透明度
	MAP_APIF const UGStyle& GetStyle()const;

	//! \brief 得到图层查询语句
	MAP_APIF const UGQueryDef& GetQueryDef()const;
	//! \brief 得到图层查询语句
	/**
	\param QueryDef  查询语句[in\out]
	*/
	MAP_APIF void GetQueryDef(UGQueryDef& QueryDef)const;	
	//! \brief 设置图层查询语句
	MAP_APIF void SetQueryDef(UGQueryDef& QueryDef);
	//! \brief 返回数据集的维数，如点是0维，线是1维，面是2维，其他返回-1
	MAP_APIF UGint GetDimension()const;								
	
	//! \brief 检查制作专题图的条件是否合法
	/**
	\param strExpression   字段表达式[in]
	\remarks 条件查询出来的属性值类型,如果失败,返回0
	*/
	MAP_APIF UGFieldInfo::FieldType CheckThemeExpression(const UGString& strExpression);
	//! \brief 重新计算Bounds
	MAP_APIF UGRect2D RecalcBounds(UGDrawParamaters *pDrawParam, UGbool bComputeDatasetBounds = false);

	//! \brief 导成XML信息
	MAP_APIF virtual UGString ToXML(UGint nVersion = 0)const;
	//! \brief 读取XML信息
	MAP_APIF virtual UGbool FromXML(const UGString& strXML,UGbool bIgnoreCaption = true, UGint nVersion = 0);

	//! \brief 得到父层,如果没有则为空
	MAP_APIF virtual UGLayer* GetParentLayer()const;
	//! \brief 如果是网络图层，返回节点图层
	MAP_APIF UGLayer* GetChildLayer()const;						

	//! \brief 设置父层,如果没有则为空
	MAP_APIF void SetParentLayer(UGLayer* pLayer);
	//! \brief 如果是网络图层，设置节点图层
	MAP_APIF void SetChildLayer(UGLayer* pLayer);								
	
//	UGString GetName()const;										// 图层名

	//! \brief  设置描述信息
	MAP_APIF void SetDescription(const UGString&  strDescription);		
	//! \brief 获取图层描述信息
	MAP_APIF UGString GetDescription()const;								

	//! \brief 设置数据集名称
	MAP_APIF void SetDatasetName(const UGString&  strDatasetName);		
	//! \brief 获取数据集名称
	MAP_APIF UGString GetDatasetName()const;								

	//! \brief 设置数据源别名
	MAP_APIF void SetDataSourceAlias(const UGString& strDataSourceAlias);	
	//! \brief 获取数据源别名
	MAP_APIF UGString GetDataSourceAlias()const;

	//! \brief 设置图层标题
	MAP_APIF void SetCaption(const UGString&  strCaption);		
	//! \brief 获取图层标题
	MAP_APIF UGString GetCaption()const;								

	//! \brief 获取图层最大比例尺
	MAP_APIF UGdouble GetVisibleScaleMax()const;
	//! \brief 获取图层最小比例尺
	MAP_APIF UGdouble GetVisibleScaleMin()const;
	//! \brief 设置图层最大比例尺
	MAP_APIF void SetVisibleScaleMax(UGdouble dVisibleScaleMax);
	//! \brief 取消图层最大比例尺
	MAP_APIF void CancelVisibleScaleMax();
	//! \brief 设置图层最小比例尺
	MAP_APIF void SetVisibleScaleMin(UGdouble dVisibleScaleMin);
	//! \brief 取消图层最小比例尺
	MAP_APIF void CancelVisibleScaleMin();

	//! \brief 重新设置图层信息
	MAP_APIF void Reset(UGbool bChangeStyle = true);	

	//! \brief 添加图层不可显示的Geometry的ID
	MAP_APIF void AddInvisibleGeoID(UGint nID);
	//! \brief 清空图层不可显示的Geometry的IDs
	MAP_APIF void ClearInvisibleGeoIDs();
	
	//! \brief 清除显示用的记录集
	MAP_APIF void ClearDisplayRecordset();						
	//! \brief 释放所有记录集，在关闭数据集和修改数据集子段结构之前必须调用
	MAP_APIF void ClearRecordsets();									
	//! \brief 清除编辑用的记录集	
	MAP_APIF void ClearEditRecordset();								
	//! \brief 准备显示用的记录集,UGQueryDef *pQueryDef是编辑纪录集查询参数定义
	MAP_APIF void PrepareEditRecordset(const UGQueryDef *pQueryDef = NULL);
	//! \brief 设置编辑用的记录集
	MAP_APIF void SetEditRecordset(UGRecordset *pEditRecordset);
	//! \brief 得到编辑用的记录集
	MAP_APIF UGRecordset* GetEditRecordset() const;
	//! \brief 得到显示用的记录集
	MAP_APIF UGRecordset* GetDisplayRecordset() const;

	//! \brief 设置是否清除显示用的记录集，主要是用来控制多个图层共享显示数据集时谁释放记录集的问题
	MAP_APIF void SetClearDisplayRecordset(UGbool bClear = true);

	//! \brief 与数据集建立关联
	// param bClearRecordsets 是否需要清除数据集,加载布局模板时将其置为false(防止m_pDataset为野指针导致崩溃)(added by hp 2011-3-21)
	MAP_APIF virtual void SetDataset(UGDataset *pDataset, UGbool bInit = true, UGbool bClearRecordsets = true);
	//! \brief 获取当前联接的数据集	
	MAP_APIF virtual UGDataset* GetDataset();	

	//! \brief 判断当前比例尺下是否需要显示图层(使用：m_dVisibleScaleMax和m_dVisibleScaleMin判断)
	MAP_APIF UGbool IsVisibleScale(UGdouble dScale,UGDrawParamaters* pDrawParam = NULL)const;
	//! \brief 点击图层事件
	/**
	\param pntHitTest           鼠标响应点，地理坐标[in]
	\param dTolerance           点击容限,地理单位[in]
	\param Selection            [in]
	\param nByPassCount         [in]
	\param pDrawing             绘制类[in]
	\return                     点击成功返回true，反之为false
	\remark                     如果传入的nByPassCount值为-1时表示符合条件的Geometry全部选上。其他与原函数保持一致[可以实现循环选中的效果]
    */
	virtual MAP_APIF UGbool HitTest(const UGPoint2D& pntHitTest, UGdouble dTolerance, UGSelection &Selection, UGint &nByPassCount, UGDrawing *pDrawing, UGbool bControlMode = false, UGbool bShiftMode = false);
	//! \brief 计算符号的大小
	/**
	\param dScale           比例尺[in]
	\return                 符号缩放的比例
	*/
	MAP_APIF UGdouble CalculateSymbolScale(UGdouble dScale)const;

	//! \brief 得到系统比例尺
	MAP_APIF UGdouble GetSymScaleDefinition() const;
	//! \brief 设置系统比例尺
	MAP_APIF void SetSymScaleDefinition(UGdouble dSymScaleDefinition);
	
	//! \brief 获取填充原点的模式
	MAP_APIF UGGraphics::BrushOrgMode GetFillOrgMode() const;				
	//! \brief 设置填充原点模式
	MAP_APIF UGGraphics::BrushOrgMode SetFillOrgMode(UGGraphics::BrushOrgMode nFillOrgMode);		
	
	//! \brief 获取最小显示大小
	MAP_APIF UGdouble GetMinimumVisible() const;				
	//! \brief 设置最小显示大小
	MAP_APIF void SetMinimumVisible(UGdouble dMinimumVisible);	

	//! \brief 绘制图层
	/**
	\param pGraphics			绘制到的Graphics[in]
	\param pDrawing				绘制类[in]
	\param pRecordSet           绘制的记录集[in]
	\param bBlank				绘制的是否是白图[out]
	\param bSingle              记录集是否自由该图层自己使用[in]
	\return                     绘制成功返回true，反之为false
	*/
	MAP_APIF UGbool OnDraw(UGGraphics* pGraphics, UGDrawing *pDrawing, UGRecordset* pRecordSet, UGbool *pbBlank, UGbool bSingle = false,UGProgress* pProgress = NULL);
	//! \brief 绘制几何对象
	MAP_APIF UGbool OnDrawElement(UGDrawing *pDrawing, UGGeometry *pGeometry, UGRecordset* pDisplayRecordset, UGTheme::UGActionData* pActionData = NULL);
	//! \brief 获取几何对象及范围。为了配合绘制几何对象，里面调用了一些回调
	MAP_APIF void GetElementAndBounds(UGDrawing *pDrawing, UGRecordset* pDisplayRecordset, UGGeometry*& resultGeo, UGRect2D &bounds, UGTheme::UGActionData* pActionData = NULL);

	//! \brief 转换文本和专题图为复合数据集
	MAP_APIF UGbool ConvertTextOrThemeLayerToDataset(UGDrawing* pDrawing, UGDatasetVector *pDatasetCAD, UGbool bProgress = true);
	
	//! \brief  把pRecordset中的专题图对象转化为Geometry，目前只支持点单值、分段、自定义专题图， add by wangna 2011-05-31
	//! \param pDrawing         显示类指针[in]
	//! \param pRecordset         需要把专题图符号转换为Geometry的对象记录集[in]
	//! \param geometryArray         记录集中对象对应的专题图符号转换为Geometry集合[in/out]
	//! \return 是否转换成功
	MAP_APIF UGbool ConvertThemeObjectsToGeometrys(UGDrawing* pDrawing, UGRecordset *pRecordset, UGArray<UGGeometry *> &geometryArray);

	//added by xielin 2007-04-13
	//! \brief 返回图层中的选择集 
	MAP_APIF UGSelection* GetSelection();

	//added by lugw 2007-04-12
	//! \brief  标签专题图图层点击事件
	/**
	\param pntHitTest           鼠标响应点，地理坐标[in]
	\param dTolerance			点击容限，地理单位[in]
	\param pGraphics            pDrawing类中对应的pGraphics[in]
	\param pDrawing             绘制信息[in]
	\param geoTextArray         选中标签的字段标签信息[in/out]
	\param strFieldExpression   所需查询的字段表达式，默认为空
	\return                     成功返回true，反之为false
	\remarks                    对于查询后的geoTextArray，如果用户只需要得到选中标签的字段信息，则此数组将每个标签的信息以GeoText的形式输出，如果字段表达式不为空而且表达式正确，则数组按照：【符合条件的标签信息＋该标签的字段表达式的值】的形式输出所有在此Bounds下的标签。
	*/
	MAP_APIF UGbool HitTestThemeLable(const UGPoint2D& pntHitTest,UGdouble dTolerance,/*UGThemeLabel* pThemeLabel,*/UGGraphics* pGraphics, UGDrawing *pDrawing,UGArray<UGGeoText>& geoTextArray,UGString strFieldExpression = (_U("")));
	MAP_APIF UGbool HitTestThemeLable(const UGPoint2D& pntHitTest,UGdouble dTolerance,UGGraphics* pGraphics, UGDrawing *pDrawing,UGArray<UGGeoCompound>& geoCompoundArray,UGString strFieldExpression = (_U("")));
	//! \brief  标签专题图图层点击事件,这两个接口没有容限设置，现在不推荐使用，只是为了保证兼容性
	MAP_APIF UGbool HitTestThemeLable(const UGPoint2D& pntHitTest,/*UGThemeLabel* pThemeLabel,*/UGGraphics* pGraphics, UGDrawing *pDrawing,UGArray<UGGeoText>& geoTextArray,UGString strFieldExpression = (_U("")));
	MAP_APIF UGbool HitTestThemeLable(const UGPoint2D& pntHitTest,UGGraphics* pGraphics, UGDrawing *pDrawing,UGArray<UGGeoCompound>& geoCompoundArray,UGString strFieldExpression = (_U("")));
	//! \brief 统计专题图鼠标响应
	/*
	\param pntHitTest    点击位置[in]
	\param dTolerance    点击容限，地理单位[in]
	\param pDrawing      绘制参数[in]
	\param pLayer        专题图所在层[in]
	\param geoTextArray  返回字段信息[in/out]
	**
	*/
	MAP_APIF UGbool HitTestThemeGraph(const UGPoint2D& pntHitTest,UGdouble dTolerance, UGDrawing *pDrawing,UGArray<UGGeoText>& geoTextArray);
	//! \brief 点击Tin图层事件
	/**
	\param pntHitTest           鼠标响应点，地理坐标[in]
	\param dTolerance           点击容限，地理单位[in]
	\param triInfo				返回Tin三角网信息[in\out]
	\param pDrawing             绘制类[in]
	\return                     点击成功返回true，反之为false
	*/
	//UGbool HitTestTinBlock(const UGPoint2D& pntHitTest,UGdouble dTolerance, TriInfo& triInfo, UGDrawing *pDrawing);
	
	//added by dongfei 2007-04-24 
	//! \brief 设置/返回 图层名,内部使用，切勿修改，对外提供的是caption
	MAP_APIF void SetName(UGString strLayerName);
	MAP_APIF UGString GetName()const {return m_strName;};
	//! \brief 设置/返回特定比例尺下图层风格
	MAP_APIF void SetStyle(UGdouble dMinScale,UGdouble dMaxScale,const UGStyle& style);
	MAP_APIF UGStyle GetStyle(UGdouble dScale)const;
	//! \brief 删除所有非默认风格(保留默认)
	MAP_APIF void RemoveAllStyle();
	//! \brief 获取风格个数(不包括默认风格)
	MAP_APIF UGint GetStyleCount()const {return m_scaleStyle.GetSize();};
	//! \brief 获取所有指定比例尺下风格
	MAP_APIF void GetScalStyle(UGArray<ScaleStyle>& styles){styles = m_scaleStyle;};
	//! \brief 设置/获取查询排序字段,该接口主要用于调整同一个图层几何对象的叠盖关系，该字段最好设置为自动增长字段
	MAP_APIF UGbool SetOrderField(UGString strField);
	//! \brief 设置/获得是否按某一字段(非SmID)顺序查询
	MAP_APIF UGString GetOrderField();
	//! \brief 把给定ID号的对象放到最前面
	MAP_APIF UGbool BringToFront(UGlong nID);
	//! \brief 把给定ID号的对象放到最后面
	MAP_APIF UGbool SendToBack(UGlong nID);
	//! \brief 设置图层压盖处理
	MAP_APIF void SetOrderOverlap(UGbool bOrderOverlap = true);
	//! \brief 是否对图层压盖处理
	MAP_APIF UGbool IsOrderOverlap();
	
	//! \brief 几何对象是否可见
	/**
	\param pGeometry             几何对象[in]
	\param dMinimumVisible       最小显示比例尺[in]
	\return                      可见返回true，反之为false
	*/
	MAP_APIF UGbool IsGeometryVisible(UGGeometry *pGeometry, UGdouble dMinimumVisible)const;

	//! \brief 几何对象是否可见
	/**
	\param pGraphics            绘制到的Graphics[in]
	\param pDrawing				绘制类[in]
	\param querfdef				得到的查询语句[in]
	\return                     成功返回true，反之为false
	*/
	MAP_APIF UGbool PrepareQueryDef(UGGraphics* pGraphics, UGDrawing* pDrawing, UGQueryDef*& querfdef,UGbool bIsflateBounds = false);

	//added by lugw 2007-06-05 
	//! \brief 得到图层类型
	MAP_APIF UGLayer::UGLayerType GetType();
	//! \brief 设置图层类型
	MAP_APIF virtual void SetType(UGLayer::UGLayerType nType);

	//! \brief 设置父图层名称
	MAP_APIF void SetParentDsName(UGString strName);
	//! \brief 得到父图层名称
	MAP_APIF UGString GetParentDsName();

	//! \brief 几何对象绘制完后的回调函数
	MAP_APIF void SetAfterGeometryDrawFunc(AfterGeometryDrawProc pAfterGeometryDrawFunc,UGlong pWnd);
	//! \brief 几何对象绘制前的回调函数
	MAP_APIF void SetBeforeGeometryDrawFunc(BeforeGeometryDrawProc pBeforeGeometryDrawFunc,UGlong pWnd);
	MAP_APIF void SendAfterGeometryDrawFunc(UGString strLayerName,UGGeometry* pGeoGeometry,UGGraphics* pGraphics);
	MAP_APIF void SendBeforeGeometryDrawFunc(UGbool& bCancel,UGString strLayerName,UGGeometry* pGeoGeometry,UGGraphics* pGraphics);
	
	MAP_APIF void SetBeforeLytGeometryDrawFunc(BeforeLytGeometryDrawProc pBeforeLytGeometryDrawFunc,UGlong pWnd);
	MAP_APIF void SendBeforeLytGeometryDrawFunc(UGbool& bCancel,UGGeometry* pGeoGeometry/*,UGGraphics* pGraphics*/);

//added by qianjn in 2010-4-23 11:29:48 增加原因：geomap 绘制完成后需要判断是不是需要保存图像数据

	//! \brief GeoMap绘制完后的回调函数
	MAP_APIF void SetAfterGeoMapDrawFunc(AfterGeoMapDrawProc pAfterGeometryDrawFunc/*,UGlong pWnd*/);
	MAP_APIF void SendAfterGeoMapDrawFunc(UGDataset *pDataset, UGRecordset *pDisplayRecordset, UGGeometry* pGeometry);

//added by qianjn in 2010-4-23 11:29:48 增加完毕
	
	//! \brief 得到栅格不透明度
	MAP_APIF UGint GetOpaqueRate();	
	//! \brief 设置栅格不透明度
	MAP_APIF void SetOpaqueRate(UGint nOpaqueRate);	
	
	//! \brief 得到亮度
	MAP_APIF UGint GetBrightness();
	//! \brief 设置亮度
	MAP_APIF void SetBrightness(UGint nBrightness);

	//! \brief 得到对比度
	MAP_APIF UGint GetContrast();
	//! \brief 设置对比度
	MAP_APIF void SetContrast(UGint nContrast);

	//! \brief 是否背景透明
	MAP_APIF UGbool IsRasterBackTransparent() const;
	//! \brief 设置是否背景透明
	MAP_APIF void SetRasterBackTransparent(UGbool bBackTransparent);

	//! \brief 得到背景颜色容限
	MAP_APIF UGbyte GetRasterBackColorTolerance() const;
	//! \brief 设置背景颜色容限
	MAP_APIF void SetRasterBackColorTolerance(UGbyte nBackColorTolerance);

	//! \brief 获取Grid无值风格
	MAP_APIF UGint GetGridNoData() const;
	//! \brief 设置Grid无值风格
	MAP_APIF void SetGridNoData(UGint nGridNoData);

	//! \brief 得到栅格背景色
	MAP_APIF UGColor GetImageBackColor() const;
	//! \brief 设置栅格背景色
	MAP_APIF void SetImageBackColor(UGColor crBack);

	//! \brief 得到无值风格
	MAP_APIF UGColor GetGridNoDataColor() const;
	//! \brief 设置无值风格
	MAP_APIF void SetGridNoDataColor(UGColor crNoDataColor);
	
	//! \brief 得到设置是否使用显示裁剪区域
	MAP_APIF UGbool IsDisplayClip() const;							
	//! \brief 得到是否使用显示裁剪区域
	MAP_APIF void SetDisplayClip(UGbool bIsDisplayClip);		

	//! \brief 是否优化十字路口
	MAP_APIF UGbool IsCrossroadOptimized()const;
	//! \brief 设置是否优化十字路口
	MAP_APIF void SetCrossroadOptimized(UGbool bIsCrossroadOptimized);
	//! \brief 内部调用函数
	MAP_APIF void SetLayers(UGLayers *pLayers);

#if !defined SYMBIAN60 && !defined  OS_ANDROID && !defined (IOS)
	//! \brief 获取网络数据集所有图层
	MAP_APIF UGbool GetWebSubLayers(UGArray<UGString>& aryLayerNames) const;
	//! \brief 获取网络数据集所有图层标题
	MAP_APIF UGbool GetWebSubLayersTitle(UGArray<UGString>& aryLayerTitle) const;
	//! \brief 设置网络数据集所有图层是否可见属性
	MAP_APIF void SetWebSubLayersVisble(const UGbyteArray& arrLayersVisible);
	//! \brief 得到网络数据集所有图层是否可见属性
	MAP_APIF void GetWebSubLayersVisble(UGbyteArray& arrLayersVisible) const;

	//! \brief 设置多波段栅格数据集的各波段显示属性。
	//! \param arrMultiBandVisible 各波段显示属性[in]。
	MAP_APIF void SetMultiBandVisible(const UGArray<UGint>& arrMultiBandVisible);	
	//! \brief 设置多波段栅格数据集的各波段显示属性。
	//! \param arrMultiBandVisible 各波段显示属性[in]。
	MAP_APIF void GetMultiBandVisible(UGArray<UGint>& arrMultiBandVisible);
	//! \brief 设置多波段栅格数据集的显示颜色空间模式。
	MAP_APIF void SetImgColorSpace(ImgColorSpace nImgCS);
	//! \brief 获取多波段栅格数据集的显示颜色空间模式
	MAP_APIF ImgColorSpace GetImgColorSpace();
#endif
	//! \brief 设置图层的透明度
	/*
	\param nTransPercent	透明度[in]
	*/	
	MAP_APIF void SetTransPercent(UGuint nTransPercent);
	//! \brief 获取图层的透明度
	MAP_APIF UGuint GetTransPercent();

	MAP_APIF UGColorTable m_ColorsetTable;

	// 颜色对照表 
	MAP_APIF UGColorDictTable m_clrDictTable;
//{{修改原因：设置及获取制图风格类型 修改人:macx 2008-8-11 17:23:31
// 	//! \brief 设置制图风格类型。
// 	//! \param nRepStyleType 制图风格类型[in]。
// 	MAP_APIF void SetRepStyleType(UGint nRepStyleType);	
// 	//! \brief 获取制图风格类型。
// 	//! \return 制图风格类型。
// 	UGint GeRepStyleType();	
#if !defined SYMBIAN60 && !defined  OS_ANDROID && !defined (IOS)
	//added by macx 200-8-26 
	//! \brief 设置制图字段名。
	//! \param strRepreFiledName [in]。
	MAP_APIF void SetRepresentationFieldName(const UGString &strRepreFiledName);	

	//! \brief 获取制图字段名。
	//! \return 制图字段名。
	const UGString& GetRepresentationFieldName();	
	//added by macx 2008-8-26 
	//! \brief 设置制图表达标志 true，使用制图表达，false，不使用
	MAP_APIF void SetUseRepresentation(UGbool bRepresentation);
	//! \brief 获取是否使用制图表现
	UGbool IsUseRepresentation();
	//! \brief 设置图层默认保存制图风格
	MAP_APIF void SetRepresentationSaveType(UGRepresentationElement::UGRepresentationElementType nType);
	UGRepresentationElement::UGRepresentationElementType GetRepresentationSaveType();
	
	//! \brief 设置备用参考字段
	MAP_APIF void SetRefFieldName(const UGString& strRefFieldName);
	MAP_APIF UGString GetRefFieldName();
	
	//! \brief 专题图子图字段，对标签，统计，等级起作用
	MAP_APIF void SetSaveRepresentationFieldName(const UGString &strSaveRepreFiledName);
	const MAP_APIF  UGString& GetSaveRepresentationFieldName();
	//! \brief 设置制图风格使用
	MAP_APIF void SetIgnoreRepreStyle(UGbool bIgnore);
	MAP_APIF UGbool IsIgnoreRepreStyle();
#endif


	//added by macx 此处设置访问权限为public，主要原因是在m_selection里高亮显示要使用
	//! \brief 根据是否使用制图表达，来获取相应的Geometry。
	//! \param pRecordset 记录集[in]。
	//! \param pGeometry 获取的Geometry[out]。
	//! \param bMemoryEngine 是否是内存引擎[in]。
	//! \param bGetSrcGeo 在字段为空时，是否获取原始对象,部分专题图需要设置【in】
	//! \param bTheme 是否时获取专题图制图字段【in】
	//! \return 是否获取成功，true 为成功，false为失败。
	//! \remarks 在标签，统计，等级专题图时，bGetSrcGeo设为空，因为绘制的不应该时原始对象
	MAP_APIF UGbool GetDrawGeometry(UGRecordset *pRecordset,UGGeometry*& pGeometry,UGbool bMemoryEngine = FALSE, UGbool bGetSrcGeo = true,UGbool bTheme = false,UGGeometry *pGeoRef = NULL);
#if !defined SYMBIAN60 && !defined  OS_ANDROID && !defined (IOS)
	//! \brief 根据是否是制图表达来保存Geometry。
	//! \param pRecordset 记录集[in]。
	//! \param pGeometry 要保存的geometry[in]。
	//! \param bTheme 是否自动处理专题图类型【in】
	//! \param bSaveRepre 是否保存到制图表达里，true为保存到制图字段，false为保存到原始数据集记录中，默认为false
	MAP_APIF void SaveDrawGeometry(UGRecordset *pRecordset,UGRepresentationElement::UGRepresentationElementType nType = UGRepresentationElement::UGREPRESENTATIONSTYLE_GEOMETRY_STYLE,  UGStyle* pStyle = NULL,UGTextStyle* pTextStyle = NULL,UGGeometry* pGeometry = NULL,UGbool bTheme = true, UGbool bSaveRepre = FALSE);
#endif

	//! \brief 是否用户取消，内部使用接口
	UGbool IsCancelByUser(UGDrawing *pDrawing) const; 

	//! \brief  Geometry是否可见
	//! \param nID Geometry的ID[in]。
	//! \return 是否可见 
	UGbool IsVisibleByGeoID(const UGint& nID)const;
	
	//! \brief 用户设置的外部信息
	//! \param value 外部信息字符串
	MAP_APIF void SetExternalInfo(const UGString& value);

	//! \brief 用户设置的外部信息
	//! \return 外部信息字符串
	MAP_APIF const UGString& GetExternalInfo();

// 	MAP_APIF void SetRepresentation(UGRepresentation *pRepresentation);
// 	UGRepresentation* GetRepresentation();
	
// 	//! \brief 返回Geometry。
// 	//! \param pDateset 数据集[in]。
// 	//! \param pGeometry Geometry[in]。
// 	//! \param bRepre 是否获取Representation true 获取表现数据，使用；false 不获取，使用原始GIS数据[in]。
// 	//! \return 是否成功。
// 	//! \remarks 根据制图风格来获取Geometry。
// 	UGbool GetDrawingGeometry(UGRecordset* pRecordset, UGGeometry** pGeometry/*,UGbool bRepre = FALSE*/);
// 
// 	UGbool	GetDrawingGeometryDirect(UGRecordset* pRecordset, UGGeometry** pGeometry);
// 	UGbool SaveDrawingGeometry(UGRecordset *pRecordset,UGString &strFiledName,UGGeometry *pGeometry);
//}}修改原因：设置及获取制图风格 修改人:macx  2008-8-11 17:23:31
	
public:
	//! \brief 调整查询记录集时的范围，在专题图时且扩大查询范围时调用
	//! \brief 该函数实现将rcSearchBounds与相对于地图左上角点的大格子的范围求并，将结果作为新的rcSearchBounds，用于查询记录集
	//! \brief 实现该函数的用意是在一定程度上保证专题图对象的绘制顺序在相邻两张图片上保持一致
	void AdjustSearchBounds(UGDrawing* pDrawing, UGRect2D &rcSearchBounds);

	//! \brief 初始化格子的宽（格子宽高相等）
	void InitGridWidth(UGDrawing* pDrawing);

	UGint m_nGridWidth;   //格子的宽，格子是相对于地图的左上角点进行划分的

protected:
	MAP_APIF UGbool OnDrawRaster(UGGraphics* pGraphics, UGDrawing *pDrawing,UGProgress* pProgress = NULL);
	MAP_APIF UGbool OnDrawVector(UGGraphics* pGraphics, UGDrawing *pDrawing,UGProgress* pProgress = NULL);

	MAP_APIF UGbool OnDrawThemeNone(UGDrawing *pDrawing,UGProgress* pProgress = NULL,UGTheme::UGActionData* pActionData = NULL);	

	//! \brief 用于获取几何对象。为了配合绘制几何对象，里面加入了一些回调
	MAP_APIF UGGeometry* GetThemeNoneElement(UGDrawing *pDrawing,UGRecordset* pDisplayRecordset);
	//! \brief 绘制几何对象
	MAP_APIF UGbool OnDrawThemeNoneElement(UGDrawing *pDrawing, UGGeometry *pGeometry, UGRecordset* pDisplayRecordset, UGTheme::UGActionData* pActionData = NULL);
	/*
	UGbool OnDrawThemeStyle(UGThemeStyle* pThemeStyle, UGDrawing *pDrawing,UGProgress* pProgress = NULL);
	UGbool OnDrawThemeGraph(UGThemeGraph* pThemeGraph, UGDrawing *pDrawing,UGProgress* pProgress = NULL);	
	UGbool OnDrawThemeGraduatedSymbol(UGThemeGraduatedSymbol* pThemeGraduatedSymbol, UGDrawing *pDrawing,UGProgress* pProgress = NULL);
	UGbool OnDrawThemeDotDensity(UGThemeDotDensity* pThemeDotDensity, UGDrawing *pDrawing,UGProgress* pProgress = NULL);
	UGbool OnDrawThemeLabel(UGThemeLabel* pThemeLabel, UGDrawing *pDrawing,UGProgress* pProgress = NULL);
	*/

	MAP_APIF UGbool OnDrawThemeNoneCrossroad(UGDrawing *pDrawing);

	//UGbool OnDrawStyleThemeCrossroad(UGThemeUnique *pThemeUnique, UGDrawing *pDrawing);

	/*
	UGbool ThemeStyleToDataset(UGThemeStyle *pThemeStyle, UGRecordset *pRecordset, UGDrawParamaters *pDrawParam, UGDatasetVector *pDatasetCAD, UGProgress *pProgress = NULL);
	UGbool ThemeDotDensityToDataset(UGThemeDotDensity *pThemeDotDensity, UGRecordset *pRecordset, UGDrawParamaters *pDrawParam, UGDatasetVector *pDatasetCAD, UGProgress *pProgress = NULL);
	UGbool ThemeGraphToDataset(UGThemeGraph *pThemeGraph, UGRecordset *pRecordset, UGDrawParamaters *pDrawParam, UGDatasetVector *pDatasetCAD, UGProgress *pProgress = NULL);
	UGbool ThemeGraduatedSymbolToDataset(UGThemeGraduatedSymbol *pThemeGraduatedSymbol, UGRecordset *pRecordset, UGDrawParamaters *pDrawParam, UGDatasetVector *pDatasetCAD, UGProgress *pProgress = NULL);
	UGbool ThemeLabelToDataset(UGThemeLabel *pThemeLabel, UGRecordset *pRecordset, UGDrawing *pDrawing, UGDatasetVector *pDatasetCAD, UGProgress *pProgress = NULL);
	UGGeometry* ThemeLabelBackToGeometry(UGThemeLabel *pThemeLabel, UGGeoText* pGeoText, UGDrawParamaters *pDrawParam,const UGPoint2D& pntObjCenter);
	UGGeometry* LabelBoundsToGeometry(const UGRect2D& rcBounds, const UGPoint2D& pntCentroid, UGdouble dAngle, UGint nLabelBackType, const UGStyle& backStyle,  UGDrawParamaters *pDrawParam);
	*/
	//added by dongfei 2007-04-23
	//! \brief 计算牵引线对象，这个对象用于和需要牵引线的对象求交
	/*
	\param rect			需要牵引线对象的外接矩形
	\param pntFrom      牵引线起始点  
	\param pntAnchor		旋转基点
	\param dAngle	          旋转角度
	\return				牵引现对象 为起始点和矩形中心点附近两点围成的等腰三角形		
	\remarks			需要外部释放返回的region			
	*/	
	MAP_APIF UGGeoRegion* GetLeaderObject(const UGRect2D& rect,const UGPoint2D& pntFrom, const UGPoint2D& pntAnchor, UGdouble dAngle);

//{{{added by qianjn in 2008-11-19 14:20:03 增加原因：支持栅格数据集的动态投影
	
	//! \brief 根据图层关联的数据集计算动态投影后的数据集。
	//! \param pDatasource 存投影转换后数据集的数据源，传进去的值为空值[in]。
	//! \param pRefTranslator 坐标系转换对象[in]。
	//! \return 如果设置成功返回动态投影后的数据集；否则返回NULL。
	MAP_APIF UGDatasetRaster* GetDatasetFromFlyPrj(UGDataSource*& pDatasource, UGRefTranslator* pRefTranslator, UGDrawing *pDrawing, UGString& strDatasource); 

public:

	//! \brief 把图层关联的数据集置空,慎重使用，没有析构，直接置空的，主要应用与关联的数据集被删掉了的情况。
	MAP_APIF void SetNullDataset();
	
	//! \brief 矩形裁减
	//! \return 如果裁剪成功， 返回 true， 否则返回失败
	static MAP_APIF UGbool Clip(const UGGeometry* pGeometry, const UGRect2D& rectClip, UGGeometry*& pGeoResult);

	//! \brief 临时成员，其他地方勿用。
	UGbool m_bViewGlobal;

	//! \brief 以下两个变量仅供数据集缓存时，保存的临时中间变量,其它地方不要使用。
	UGRectUInt m_rectSearch;

	//! \brief 获取图层范围，注意目前此接口不用于海图图层，海图另外实现
	MAP_APIF UGRect2D GetBounds();

public:
	//获取点和标签一起过滤的点图层
	UGLayer* GetPointLayer();
	//设置点和标签一起过滤的点图层
	void SetPointLayer(UGLayer* pPointLayer);

	// 获取影像多波段拉伸类型
	UGRasterStretchOption* GetRasterStretchOption();

	UGbool IsBackMapData();
	void SetBackMapData(UGbool bBackMapData);

public:
	//! \brief 初始化网络地图相关信息
	void InitWebMapInfo();
	//! \brief 反初始化网络地图相关信息
	void UnInitWebMapInfo();
	//! \brief 重新设置网络地图相关信息
	void ResetWebMapInfo();

	//! \brief 判断是否是网络地图图层
	UGbool IsWebRaster();

	//! \brief 根据当前的视图范围把m_pDrawTileImage绘制到pGraphics上
	UGbool OnDrawTileImage(UGDrawing* pDrawing, UGbool bIsPrinting);

	//! \brief 图层向数据集请求瓦片
	void RequestTile(UGdouble dScale, UGRect2D& rcViewBounds, UGbool bPanMode = false, UGbool bForceUpdate = false);

	//! \brief 图层向数据集请求瓦片
	void RequestTileEx(UGdouble dScale, UGRect2D& rcBounds);

	//! \brief 更新缓存的ImageData
	UGbool UpdateCacheTile(UGint nExtTileSize = 1, UGbool bRemoveAll = true);

	//! \brief 获取当前服务瓦片DP-->LP的转换比率
	UGdouble GetTileCoordRatio();

	UGWebMapStub* m_pWebMapLayerStub;
	
public:	
	//! \brief 专题图集合
	// SFC工作空间中，多个专题图可以位于同一个图层下，该变量用来保存图层下的所有专题图；
	//在当前类库中，该变量主要用于读入和输出SFC工作空间时用到
	//UGC工作空间中该变量为NULL
	UGThemes m_Themes;
	//! \brief 专题图 
	//对于UGC工作空间，一个专题图对应一个图层，如果该图层为专题图，则m_pTheme包含的是专题图的相应参数；反之，该值为NULL
	UGTheme* m_pTheme;
	//added by xielin 2007-04-13
	//! \brief 多图层编辑模式下，每个Layer都有一个selection 
	UGSelection m_Selection;  
	
	//! \brief 图层是否能绘制的变量，这个变量用来控制该图层是否可以绘制
	//以后绘制图层，判断visible为true，并且该变量为true，这样设计的原因是
	//因为sfc中的图层如果有单值专题图，读取到ugc中分层，但是为了优化，就要设置原始
	//图层的visible为false，但是这样就导致保存工作空间的时候图层状态就错了
	//(获取hashcode的时候也错了），所以就增加该变量，专门用来控制，而不去改变图层的可见状态
	//UGbool m_bCanDraw;
	//added by litao,2001/8/3
	//! \brief 图层中不可见的几何对象的ID
	UGArray<UGint> m_arrInvisibleGeoIDs;  
#if !defined SYMBIAN60 && !defined  OS_ANDROID && !defined (IOS)
	//{{修改原因：关于制图表达 修改人:macx 2008-8-11 14:45:01
	//! \brief 制图表达字段
	UGRepresentation *m_pRepresentation;

	//! \brief 默认制图保存风格
	UGRepresentationElement::UGRepresentationElementType m_nRepresentationElementType;	
#endif
	//! \brief 是否忽略表达数据的风格信息,主要针对专题图
	UGbool m_bIgnore;
	//{{修改原因:关于图层裁剪  修改人:lidl 2008-9-8  9:15:15
	//! \brief 存储图层的裁剪区域,在不用时最好置空吧,以免在下次设置时还显示以前的裁剪区域
	UGGeoRegion m_DisplayClipRegion;
	//! \brief 存储原始的裁剪区域
	UGGeoRegion m_OldDisplayClipRegion;
protected:
	//! \brief 以0.1mm为单位
	UGint m_nMinimumVisible;
	
	UGRecordset *m_pDisplayRecordset;	
	UGRecordset *m_pEditRecordset;		
	//! \brief 图层显示风格
	UGStyle m_Style;					
public:
	//! \brief 查询定义
	UGQueryDef m_QueryDef;

	//added by xielin 2007-09-29 记录所在的图层集合，用于修改图层的锁定编辑状态，
	//! \brief  通过Layers中回调函数通知相应的模块
	UGLayers* m_pLayers; 

protected:	
	//! \brief  图层描述
	UGString m_strDescription;			
	//! \brief  caption for this layer
	UGString m_strCaption;			
	//! \brief  保存该图层的数据集所在的数据源别名
	UGString m_strDataSourceAlias;		

	UGString m_strDatasetName;

	//!added by macx 2008.7.23 对象名，
	//! \brief 地理对象名字。
	//! \remarks 用来设置地理对象层名字。
	UGString m_strGeoName;

//! \brief  当地图比例尺大于该值的时候，本图层不显示，若该值等于0，则该限制无效。默认为0
	UGdouble m_dVisibleScaleMax;		
//! \brief  当地图比例尺小于该值的时候，本图层不显示，若该值等于0，则该限制无效。默认为0
	UGdouble m_dVisibleScaleMin;		
//! \brief  如果地图的符号随着图层缩放而缩放，当地图比例尺等于该值的时候，图层的符号按geoStyle的符号大小显示
	UGdouble m_dSymScaleDefinition;		

	UGLayer* m_pParentLayer;
	UGLayer* m_pChildLayer;
	UGDataset *m_pDataset;
	UGuint m_unOptions;

	//! \brief 画刷原点模式
	UGGraphics::BrushOrgMode m_nFillOrgMode;					
	UGbool m_bSingle;
	UGLayer::UGLayerType m_nType;
	UGString m_strParentDsName;
	
	
	
	//added by dongfei 2007-04-24
	//! \brief 图层名 不一定是“数据集@数据源”了
	UGString m_strName;

//{{修改原因：添加 PDF 使用修改人:macx 2008-8-11 10:17:38
	//! \brief PDF使用，图层句柄
	UGint m_nLayerHandle; 
	//! \brief Geometry图层句柄，PDF使用
	UGint m_nGeoHandle;
	//! \brief Geometry对象数量
	UGint m_nGeometryCount;
//}}修改原因： 修改人:macx  2008-8-11 10:17:38
	
#if !defined SYMBIAN60 && !defined  OS_ANDROID && !defined (IOS)
	//! \brief 设置制图字段
	UGString m_strRepreFiledName;
	//! \brief 参考字段
	UGString m_strFieldNameRef;
	//! \brief 专题图制图保存字段
	UGString m_strThemeRepreFiledName;
	//! \brief 是否使用制图数据
	//! \remarks true 使用，false 不使用。
	UGbool m_bRepresentation;
#endif
	

	//! \brief 不同比例尺下的风格
	UGArray<ScaleStyle> m_scaleStyle;
	UGString m_strOrderField;
	
	//! \brief 栅格图层亮度，值域范围为-100到100，增加亮度为正，降低亮度为负
	UGchar m_btBrightness;	

	//! \brief  栅格图层对比度，值域范围为-100到100，增强对比度为正，减弱对比度为负
	UGchar m_btContrast;		
	//! \brief  不透明度0----100% 100为不透明，0为完全透明，只对栅格数据集有效
	UGbyte m_btOpaqueRate;			
	//! \brief  栅格背景色。
	UGColor m_ImageBackColor;  
	//! \brief  无值风格。
	UGColor m_GridNoDataStyle; 
	//! \brief  背景透明。
	UGbool m_bRasterBackTransparent; 
	//! \brief  背景颜色容限
	UGbyte m_btBackColorTolerance; 
	//! \brief  Grid空值
	UGint m_nGridNoData;
	
	AfterGeometryDrawProc m_pAfterGeometryDrawFunc;
	BeforeGeometryDrawProc m_pBeforeGeometryDrawFunc;
	BeforeLytGeometryDrawProc m_pBeforeLytGeometryDrawFunc;
	AfterGeoMapDrawProc m_pAfterGeoMapDrawFunc;
	//! \brief 调用事件回调函数的对象指针，统一为一个吧，节省内存
	UGlong m_pEventView;  
	
	UGbyteArray m_arrWebLayersVisible;

	//  [added by zhangshuo at 5/17/2010]
	UGNetCDFDatasetRasterInfo m_NetCDFInfo;

	//! \brief 多波段显示数组
	UGArray<UGint> m_arrMultiBandVisible;
	//! \brief 多波段显示颜色空间模式
	ImgColorSpace m_nImgCS;
	//! \brief 地图的透明度
	UGuint m_nTransPercent;

	//! \brief 多波段拉伸参数
	UGRasterStretchOption m_RasterStretch;

	UGGraphics* m_pTransPercentGraphics;
	UGImage* m_pTransPercentImage;
	UGBrush* m_pTransPercentBrush;
	UGPen* m_pTransPercentPen;

	//用于点和标签一起过滤显示的点图层
	UGLayer* m_pPointLayer;

	//! \brief 外部信息字符串
	UGString m_strExternalInfo;
	
	// 判断是否是背景数据（嵌入式区分是否是背景数据还是业务数据）
	UGbool m_bBackMapData;
};

}

#endif // !defined(AFX_UGLAYER_H__A4B430F7_6A63_4275_BB13_EF15BA12DDAD__INCLUDED_)


