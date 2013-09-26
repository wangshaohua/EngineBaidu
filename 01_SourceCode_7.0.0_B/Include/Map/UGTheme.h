// UGTheme.h: interface for the UGTheme class.
//
//////////////////////////////////////////////////////////////////////

/*!
   **************************************************************************************
    \file     UGTheme.h 
   **************************************************************************************
    \author   陈国雄
    \brief    专题图基类，所有专题图都从它派生。                                                             
    \attention   
   ----------------------------------------------------------------------------------<br>
    Copyright (c) 1996-2005 SuperMap GIS Technologies,Inc.                           <br>
    All Rights Reserved.                                                             <br>
   ----------------------------------------------------------------------------------<br> 
   
   **************************************************************************************
    \version 2005-05-20  陈国雄    初始化版本.                                       <br>
   **************************************************************************************
*/

#if !defined(AFX_UGTHEME_H__AEAB0616_AD6A_4049_9C12_07AE84BC1270__INCLUDED_)
#define AFX_UGTHEME_H__AEAB0616_AD6A_4049_9C12_07AE84BC1270__INCLUDED_

#include "Engine/UGDataSource.h"
#include "Stream/ugdefs.h"
#include "Toolkit/UGHashCode.h"
#include "Drawing/UGDrawing.h"
#include "Map/UGSelection.h"
#include "Engine/UGQueryDef.h"

namespace UGC {

#define UG_THEME_MAX_VALUE_COUNT	256

#define THEME_DIVISION _U("[#]")

//已经在UGSelection中声明了，这里注释掉
//class UGLayer;

//! \brief 扩展专题图图层事件回调函数
typedef UGbool (UGSTDCALL *ExtendThemeDrawGeometryProc)(UGLayer* pTheme,UGbool& bCancel,UGGeometry* pGeometry,UGArray<UGString> arrFieldValues,UGGeometry* pYieldGeometry,UGlong pData);
typedef UGbool  (UGSTDCALL *ExtendThemeRecordsetDrawProc)(UGLayer* pTheme,UGRecordset* pDisplayRecordset,UGDrawing* pDrawing,UGArray<UGString> strFieldsNameArray,UGbool& bEnd,UGlong pData);

#ifdef SYMBIAN60
class MAP_APIC UGTheme 
#else
class MAP_API UGTheme 
#endif
{
public:
	enum UGClassType
	{
		//! \brief 等距方式
		ctEqualDistance,
		//! \brief 平方根方式
		ctExtraction,
		//! \brief 标准差方式
		ctStdev,
		//! \brief 对数方式
		ctLogarithm,
		//! \brief 等计数方式
		ctQuantile,
		//! \brief 自定义方式
		ctCustomInterval,
		null_type
	};
	//! \brief 专题图类型
	enum UGThemeType 
	{
		ttNone =			0,
			//! \brief UNIQUE专题图
			ttUnique = 			1,
			//! \brief RANGE专题图
			ttRange	 = 			2,
			//! \brief GRAPH专题图
			ttGraph	 = 			3,
			//! \brief GRADUATED_SYMBOL专题图
			ttGraduatedSymbol = 4,
			//! \brief DENSITY专题图
			ttDotDensity =		5,
			//		ttSymbolShade =		6,			//SYMBOL_SHADE专题图
			//! \brief LABEL专题图
			ttLabel	=			7,
			//! \brief CUSTOM专题图
			ttCustom =			8,
			//! \brief GRIDUNIQUE专题图
			ttGridUnique = 		11,	
			//! \brief GRIDRANGE专题图
			ttGridRange	 = 		12,	
			//! \brief 扩展专题图
			ttPlugin =          13   
	};
	enum UGThemeGraduatedMode
	{
		gmConstant,
		gmSquareRoot,
		gmLogarithm
	};
	enum UGThemeDataType
	{
		tvRecordset,
		tvExternal,
		tvMixed
	};

	enum UGActionType
	{
		UGDrawTheme = 0,
		UGHitTest = 1,
		UGTheme2Dataset = 2,
		UGThemeSymolToGeometry = 3,
		UGGeometry2Dataset = 4
	};

	//! \brief 专题图行为：0绘制、1点击、2转为数据集
	/**
	\param nType                   行为类型[in]
	\param pHitTestPoint2D         点击的中心点[in]
	\param dTolerance              点击中心的容限[in]
	\param geoTextHitTestArray     返回的点中点的标签信息（仅适用于标签专题图）[in/out]
	\param strHitTestExpression    点击标签专题图所需要的信息的字段表达式（仅适用于标签专题图）[in]
	\param Selection               点击事件选中的选择集（仅用于单值和范围专题图）[in]
	\param pDefaultStyle           点击事件默认的风格（仅用于单值和范围专题图）[in]
	\param arrIDs				   点击事件选中的几何对象的ID（仅用于单值和范围专题图[in]
	\param pRecordsetCAD           专题图转数据集时用来保存Geometry的CAD记录集[in]
	\param geometryArray     把专题图符号转换为Geometry（仅适用于点自定义专题图）[in/out]
	\return 对应的int值
	*/
	struct UGActionData 
	{
		UGActionType nType;
		UGPoint2D pntHitTestPoint2D;
		UGdouble dTolerance;
		UGArray<UGGeometry*> geoTextHitTestArray;
		UGString strHitTestExpression;
		UGRecordset* pRecordsetCAD;
		UGStyle defaultStyle;
		UGArray<UGint> arrIDs;
		UGSelection* pSelection;
		UGbool bLableCompound ;
		UGArray<UGGeometry*> geometryArray;
		
		UGActionData()
		{
			nType = UGTheme::UGDrawTheme;
			pRecordsetCAD = NULL;
			geoTextHitTestArray.RemoveAll();
			strHitTestExpression.Empty();
			pSelection = NULL;
			bLableCompound = false;
			geometryArray.RemoveAll();
		}
	};

public:
	MAP_APIF UGTheme();
	virtual MAP_APIF ~UGTheme();

public:
	//! \brief 专题图是否有效
	virtual MAP_APIF UGbool IsValid()const = 0;
	//! \brief 该接口对外不开放
	virtual MAP_APIF UGbool IsVisibleItem(UGRecordset *pRecordset, UGStyle &Style){return TRUE;};
	//! \brief 获取专题图字段
	virtual MAP_APIF UGString GetFieldName(UGbool bAddExpression = true)const = 0;
	//! \brief 获取专题图字段数组
	virtual MAP_APIF UGbool GetFieldNames(UGArray<UGString>& arrExpressions,UGbool bAddExpression = true)const{return false;};
	//! \brief 专题图的绘制
	virtual MAP_APIF UGbool OnDrawTheme(UGDrawing* pDrawing,UGLayer* pLayer,UGProgress* pProgress = NULL){return false;};
	//! \brief 绘制专题图元素
	virtual MAP_APIF UGbool OnDrawThemeElement(UGDrawing* pDrawing,UGLayer* pLayer,UGGeometry *pGeometry, UGRecordset* pDisplayRecordset, UGActionData* pActionData = NULL){return false;};
	//! \brief 此函数目前用于获取几何对象，风格，为了配合绘制，里面调用了一些回调
	virtual MAP_APIF UGGeometry* GetThemeElement(UGDrawing* pDrawing,UGLayer* pLayer,UGRecordset *pDisplayRecordset, UGActionData* pActionData = NULL){return NULL;};

	//! \brief 扩展专题图的绘制
	//UGbool OnDrawThemeEx(UGDrawing* pDrawing,UGLayer* pLayer,UGProgress* pProgress = NULL);
	//! \brief 获取专题图的查询条件
	//! \remarks 对于自定义专题图，跟数据集相关，所以需要传入，而在其他专题图不需要。
	virtual MAP_APIF UGbool GetThemeQueryDef(UGQueryDef* querfdef,UGDataset* pDv = NULL){return false;};
	//! \brief 专题图点击事件，只对UGThemeStyle专题图有效
	virtual MAP_APIF UGbool HitTest(const UGPoint2D& pntHitTest, UGdouble dTolerance,UGLayer* pLayer, UGint& nSelectedID, UGSelection &Selection, UGRecordset* pRs, UGDrawing *pDrawing,const UGStyle& defaultStyle,UGArray<UGint>& arrIDs)
	{
		return false;
	}
	//! \brief 专题图点击事件，只对UGThemeLabel专题图有效
	virtual MAP_APIF UGbool HitTestThemeLable(const UGPoint2D& pntHitTest,UGdouble dTolerance,UGLayer* pLayer,UGGraphics* pGraphics, UGDrawing *pDrawing,UGArray<UGGeoText>& geoTextArray,UGString strFieldExpression)
	{
		return false;
	}
	virtual MAP_APIF UGbool HitTestThemeLable(const UGPoint2D& pntHitTest,UGdouble dTolerance,UGLayer* pLayer,UGGraphics* pGraphics, UGDrawing *pDrawing,UGArray<UGGeoCompound>& geoCompoundArray,UGString strFieldExpression)
	{
		return false;
	}
	virtual MAP_APIF UGbool HitTestThemeGraph(const UGPoint2D& pntHitTest,UGdouble dTolerance,UGDrawing *pDrawing,UGLayer* pLayer,UGArray<UGGeoText>& geoTextArray)
	{
		return false;
	}

	//! \brief  把pRecordset中的专题图对象转化为Geometry，目前只支持点单值、分段、自定义专题图， add by wangna 2011-05-31
	//! \param pLayer         专题图图层[in]
	//! \param pRecordset         需要把专题图符号转换为Geometry的对象记录集[in]
	//! \param pDrawing         显示类指针[in]
	//! \param geometryArray         记录集中对象对应的专题图符号转换为Geometry集合[in/out]
	//! \return 是否转换成功
	MAP_APIF UGbool ConvertThemeObjectsToGeometrys(UGLayer* pLayer, UGRecordset *pRecordset, UGDrawing* pDrawing, UGArray<UGGeometry *> &geometryArray);

	//! \brief 专题图是否置顶，只对标签，统计，等级符号有效
	virtual MAP_APIF UGbool IsThemeOnTop()const
	{
		return false;
	}

	//! \brief 统计专题图分段显示设置各段名称
	virtual MAP_APIF MAP_APIF void SetItemThemeRangeName(){};
	//! \brief 高亮显示选择集
	virtual MAP_APIF MAP_APIF void HighlightSelection(UGLayer* pLayer,UGDrawing* pDrawing){};
	//! \brief 栅格专题图风格复制到Drawing中，仅对栅格专题图有效
	virtual MAP_APIF MAP_APIF void CopyThemeGridToDrawing(UGDrawing* pDrawing);
	virtual MAP_APIF UGbool IsAutoAvoid()const{return false;};
	//////////////////////////////////////////////////////////////////////////
	//! \brief 查看选择字段是否合法
	virtual MAP_APIF UGbool CheckFieldType(UGint nType);
	//! \brief 专题图保存为XML信息
	virtual MAP_APIF UGString ToXML(UGint nVersion = 0)const;
	//! \brief 专题图读取XML信息
	virtual MAP_APIF UGbool FromXML(const UGString& strXML, UGint nVersion = 0);
	//! \brief 获取专题图对象的hashcode
	virtual MAP_APIF UGint GetHashCode() const = 0;

	//! \brief 获取专题图中是否有不显示的子项,
	// 如分段专题图中某段设置为不显示,则返回TRUE
	virtual MAP_APIF UGbool HasUnVisibleItem() const { return FALSE;}

	//! \brief 获取专题图中是否有半透明的子项
	// 如单值专题图中设置透明的子项，则返回TRUE
	virtual MAP_APIF UGbool HasTransparentItem() const { return FALSE; }

	//! \brief 设置外部值
	MAP_APIF void SetExternalValue(const UGString& strKey, const UGString& strExternalValue);
	//! \brief 得到外部值
	MAP_APIF UGbool GetExternalValue(const UGString& strKey, UGString& strExternalValue)const;
	//! \brief 清空外部值
	MAP_APIF void ClearExternalData();
	
	//! \brief 得到最大可见比例	
	MAP_APIF UGdouble GetVisibleScaleMax()const;							
	//! \brief 得到最小可见比例	
	MAP_APIF UGdouble GetVisibleScaleMin()const;						
	//! \brief 设置最大可见比例
	MAP_APIF void SetVisibleScaleMax(UGdouble dVisibleScaleMax);		
	//! \brief 取消最大可见比例
	MAP_APIF void CancelVisibleScaleMax();							
	//! \brief 设置最小可见比例
	MAP_APIF void SetVisibleScaleMin(UGdouble dVisibleScaleMin);		
	//! \brief 取消最小可见比例
	MAP_APIF void CancelVisibleScaleMin();							

	//! \brief 是否可见范围内
	MAP_APIF UGbool IsVisibleScale(UGdouble dScale,UGDrawParamaters* pDrawParam = NULL)const;
	//! \brief 是否可见
	MAP_APIF UGbool IsVisible()const;
	//! \brief 设置是否可见
	MAP_APIF void SetVisible(UGbool bVisible = true);

	//! \brief 得到专题图标题
	MAP_APIF UGString GetCaption()const;
	//! \brief 设置专题图标题
	MAP_APIF void SetCaption(const UGString& strCaption );

	//! \brief 得到专题图过滤表达式
	MAP_APIF UGString GetFilter()const;

	//! \brief 得到专题图类型
	MAP_APIF UGTheme::UGThemeType GetType()const;

	//! \brief 得到专题图数据类型
	MAP_APIF UGint GetDataType()const;
	//! \brief 设置专题图数据类型
	MAP_APIF void SetDataType(UGint nDataType);

	//! \brief 专题图是否修改
	MAP_APIF UGbool IsModified()const;
	//! \brief 设置专题图是否修改
	MAP_APIF void SetModifiedFlag(UGbool bModified = true);

	//! \brief 变量转成double型
	static MAP_APIF UGbool Variant2Double(const UGVariant& var, double& dKey);
	//! \brief 变量转成字符串
	static MAP_APIF UGString Variant2String(const UGVariant& var); //变体变成字符串
	//! \brief 转化专题图类型名称
	/**
	\param nThemeType				类型对应的int值[in]
	\return 对应的字符串名称
	*/
	static MAP_APIF UGString ConvertThemeType(UGTheme::UGThemeType nThemeType);
	//! \brief 转化专题图类型名称
	/**
	\param strThemeType		类型对应的字符串名称[in]
	\return 对应的int值
	*/
	static MAP_APIF UGTheme::UGThemeType ConvertThemeType(const UGString& strThemeType);

	//! \brief 设置专题图类型名称，内部使用，切勿修改，对外提供的是caption
	MAP_APIF void SetName(UGString strLayerName) {m_strName = strLayerName;};

	//! \brief 得到专题图类型名称
	MAP_APIF UGString GetName() {return m_strName;};

	//! \brief 设置专题图扩展图层的回调函数
	MAP_APIF void SetExtendThemeDrawGeometryFun(ExtendThemeDrawGeometryProc pExtendThemeDrawGeometryFun,UGlong pData);
	
	//! \brief 执行扩展专题图的回调函数
	MAP_APIF UGbool SendExtendThemeDrawGeometryFun(UGLayer* pLayer,UGbool& bCancel,UGGeometry*& pGeometry,UGArray<UGString> arrFieldValues,UGGeometry* pYieldGeometry = NULL);

	//! \brief 设置专题图扩展图层的回调函数
	MAP_APIF void SetExtendThemeDrawRecordsetFun(ExtendThemeRecordsetDrawProc pExtendThemeDrawRecordsetFun,UGlong pData);
	
	//! \brief 执行扩展专题图的回调函数
	MAP_APIF UGbool SendExtendThemeDrawRecordsetFun(UGLayer* pLayer,UGRecordset* pDisplayRecordset,UGDrawing* pDrawing,UGArray<UGString> strFieldsNameArray,UGbool& bEnd);

	//UGbool m_bIsExtendTheme;
	//added by macx 2008.8.4 
	//! \brief PDF绘制类型。
	//! \remarks 是否是PDFGraphics引擎，在绘制标签专题图背景框到PDF时使用，用于使用PDF的坐标转换开关。
	UGbool m_bPDFType;

	//! \brief 设置字段表达式数组，只适用于扩展专题图 2008-7-4 lugw
	virtual MAP_APIF void SetExtendExpression(const UGArray<UGString>& strExpressionArray);
	UGArray<UGString> GetExtendExpression();

	//added by macx 200-8-26 
	//! \brief 设置制图字段名。
	//! \param strRepreFiledName [in]。
	MAP_APIF void SetMakeRepresentationFieldName(const UGString &strRepreFiledName);	
	//! \brief 获取制图字段名。
	//! \return 制图字段名。
	const MAP_APIF UGString& GetMakeRepresentationFieldName();	
	//added by macx 200-8-26 
	//! \brief 设置制图字段名。
	//! \param strRepreFiledName [in]。
	//! \remarks 在标签，统计，等级专题图使用，对于自定义、单值、分段时使用SetRepresentationFieldName
	MAP_APIF void SetSaveRepresentationFieldName(const UGString &strSaveRepreFiledName);	
	
	//! \brief 获取制图字段名。
	//! \return 制图字段名。
	const MAP_APIF UGString& GetSaveRepresentationFieldName();
	//added by macx 2008-8-26 
	//! \brief 设置制图表达标志 true，使用制图表达，false，不使用
	MAP_APIF void SetUseRepresentation(UGbool bRepresentation);	
	//! \brief 设置制图表达标志 true，使用制图表达，false，不使用
	MAP_APIF UGbool IsUseRepresentation();

	//! \brief  字段(表达式)值和外部输入数据的对应
	UGDict<UGString,UGString> m_ExternalData; 

	//! \brief 调用事件回调函数的对象指针，统一为一个吧，节省内存
	UGlong m_pEventData;  

//added by qianjn in 2009-8-26 10:02:55 增加原因：临时成员， 其它地方勿用

	//! \brief  是否流动显示
	virtual THEMEBASE_APIF UGbool IsEnableFlow()const;
	//! \brief  设置是否流动显示
	virtual THEMEBASE_APIF void SetEnableFlow(UGbool bEnableFlow = true);

	//! \brief 禁用自动避让，此功能对于不具备自动避让的专题图层不可用，函数调用没有任何效果；具备自动避让的专题图层必须重载此方法。
	virtual THEMEBASE_APIF void SetAutoAvoid(UGbool bAutoAvoid = true) { }
	virtual MAP_APIF UGbool ThemeToDataset(UGLayer* pLayer,UGRecordset *pRecordset, UGDrawing *pDrawing, UGDatasetVector *pDatasetCAD, UGProgress *pProgress = NULL){return false;}

	UGbool m_bViewGlobal;

	UGbool m_bFields;

//added by qianjn in 2009-8-26 10:02:55 增加完毕
	//! \brief SFC中分段专题图分段方式和UGC中不对应，通过SFC分段方式得到UGC分段方式。
	//! \param nSFCClassType [in]UGint nSFCClassType --- SFC中分段专题图的分段方式。
	//! \return UGC中的分段方式。
    static MAP_APIF UGTheme::UGClassType GetClassTypeFromSFC( UGint nSFCClassType ); 	
	//! \brief SFC中分段专题图分段方式和UGC中不对应，通过UGC分段方式得到SFC分段方式。
	//! \param nUGCClassType [in]UGTheme::UGClassType nUGCClassType --- UGC中的分段方式.。
	//! \return SFC中的分段方式。
	static MAP_APIF UGint GetClassTypeToSFC( UGTheme::UGClassType nUGCClassType );	
protected:  
	MAP_APIF void Swap(const UGTheme& theme);
	//! \brief  把pRecordset中的专题图对象转化为Geometry，目前只支持点单值、分段、自定义专题图， add by wangna 2011-06-02
	//! \param pLayer         专题图图层[in]
	//! \param pRecordset         需要把专题图符号转换为Geometry的对象记录集[in]
	//! \param pDrawing         显示类指针[in]
	//! \param geometryArray         记录集中对象对应的专题图符号转换为Geometry集合[in/out]
	//! \return 是否转换成功
	virtual MAP_APIF UGbool ThemeObjectsToGeometrys(UGLayer* pLayer, UGRecordset *pRecordset, UGDrawing* pDrawing, UGArray<UGGeometry *> &geometryArray){return false;}
    
protected:  
	UGbool m_bModified;
	//! \brief  专题图类型
	UGTheme::UGThemeType m_nType;	
	//! \brief  1,属性表，2，外部用户输入数据,其他为以后预留
	UGint m_nDataType; 
		
	//! \brief caption for this thematic map
	UGString m_strCaption;
	UGbool m_bVisible;
	//! \brief 当地图比例尺大于该值的时候，本图层不显示，若该值小于等于0，则该限制无效。默认为0
	UGdouble m_dVisibleScaleMax;
	//! \brief 当地图比例尺小于该值的时候，本图层不显示，若该值小于等于0，则该限制无效。默认为0
	UGdouble m_dVisibleScaleMin;

	//! \brief SFC中专题图的过滤表达式，保存为非SFC版本的地图时，此字段不会被保存
	UGString m_strFilter;

	UGArray<UGString> m_arrExtendExpArray;

	UGString m_strName;
	
	ExtendThemeDrawGeometryProc m_pExtendThemeDrawGeometryFun;
	ExtendThemeRecordsetDrawProc m_pExtendThemeDrawRecordsetFun;

	//! \brief 设置制图字段,用于生成专题图的geometry字段
	UGString m_strRepreFiledName;
	//! \brief 保存专题图修改的字段
	UGString m_strSaveRepreFiledName;
	//! \brief 是否使用制图数据
	//! \remarks true 使用，false 不使用。
	UGbool m_bRepresentation;
};

}

#endif // !defined(AFX_UGTHEME_H__AEAB0616_AD6A_4049_9C12_07AE84BC1270__INCLUDED_)

