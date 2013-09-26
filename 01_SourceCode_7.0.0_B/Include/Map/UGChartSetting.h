// UGChartSetting.h: interface for the UGChartSetting class.
//
//////////////////////////////////////////////////////////////////////

/*!
   **************************************************************************************
    \file     UGChartSetting.h   
   **************************************************************************************
    \author   周江涛
    \brief    海图显示参数设置类，负责海图显示环境的管理。                                                                       
    \attention   
   ----------------------------------------------------------------------------------<br>
    Copyright (c) 2000-2011 SuperMap Software Co., Ltd.                           <br>
    All Rights Reserved.                                                             <br>
   ----------------------------------------------------------------------------------<br> 
   
   **************************************************************************************
    \version 2011-04-12  周江涛    初始化版本.                                       <br>
   **************************************************************************************
*/

#if !defined(AFX_UGCHARTSETTING_H_)
#define AFX_UGCHARTSETTING_H_

#include "ChartBase/UGChartLookupTable.h"
#include "ChartBase/UGChartColorTable.h"
#include "ChartBase/UGChartEnvironment.h"
#include "ChartToolkit/UGS57SpatialRelationshipParser.h"
#include "ChartToolkit/UGS57SpatialLineManger.h"

#include "Toolkit/UGLogFile.h"
#include "Engine/UGDatasetVector.h"
#include "FileParser/UGFileParseVector.h"
#include "Engine/UGDataSource.h"
#include "Map/UGChartSubLayer.h"

namespace UGC {
	class UGMap;

	class MAP_API UGChartSetting
	{
		friend class UGChartSubLayer;
	public:
		UGChartSetting(UGMap* pMap);
		UGChartSetting(const UGChartSetting& Map);
		~UGChartSetting();
		UGChartSetting& operator = (const UGChartSetting &Map);

	public: //! \brief 扩展的相关功能接口

		//! \brief 得到设置的显示类型（名称）
		UGString GetDisplayTypeName() const;
		//! \brief 设置显示类型
		UGbool SetDisplayTypeName(const UGString& strName);

		//! \brief 获取显示类型,显示的类型由设置的显示类型名称决定
		UGChartDisplayStyle::UGChartDisplayStyleType GetDisplayStyleType() const;

		//! \brief 获取颜色模式
		UGChartColorMode::UGS52ColorMode GetColourModeChart();
		//! \brief 设置颜色模式
		UGbool SetColourModeChart(UGChartColorMode::UGS52ColorMode eColorMode);

		//! \brief 得到设置的显示类型（名称）S-52/IENC/INT
		UGChartDisplayCategory::UGS52DisplayCategory GetDisplayCategory();
		//! \brief 设置显示类型
		void SetDisplayCategory(UGChartDisplayCategory::UGS52DisplayCategory eDisplayCategory);

		//! \brief 得到设置的字体名称
		UGString GetFontName();
		//! \brief 设置字体名称
		void SetFontName(const UGString& strFontName);

		//! \brief 得到设置的字体字号
		UGdouble GetFontSize();
		//! \brief 设置字体字号
		void SetFontSize(UGdouble dfFontSize);

		//! \brief 是否使用符号化的区域边界
		UGbool IsSymbolizedAreaBoundary() const;
		//! \brief 设置符号化区域边界
		UGbool SetSymbolizedAreaBoundary(UGbool bSymbolizedBoundary = true);

		//! \brief 是否使用简单海图点符号(相应的是传统纸海图符号）
		UGbool IsSimplifiedMarker() const;
		//! \brief 设置是否使用是否使用简单海图点符号
		UGbool SetSimplifiedMarker(UGbool bSimplifiedMarker = true);

		//! \brief 是否显示文本
		UGbool IsDisplayTextMessage() const;
		//! \brief 设置是否显示文本
		void SetDisplayTextMessage(UGbool bDisplayText = true);

		//! \brief 是否将文本以本地国家语言显示。
		UGbool IsDisplayNational() const;
		//! \brief 设置是否将文本以本地国家语言显示，true为以本地国家语言显示，false以英文显示
		void SetDisplayNation(UGbool bDisplayNation = true);

		//! \brief 是否显示水深点
		UGbool IsDisplaySounding() const;
		//! \brief 设置是否显示水深点
		void SetDisplaySounding(UGbool bDisplaySounding = true);

		//! \brief 显示是否与最小显示比例尺相关
		UGbool IsMinVisibleScaleEnabled() const;
		//! \brief 设置显示是否与最小显示比例尺相关
		void SetMinVisibleScaleEnabled(UGbool bEnabled = true);

		//! \brief 得到安全水深线
		UGfloat GetSafetyContour() const;
		//! \brief 设置安全水深
		void SetSafetyContour(UGfloat dfSafetyDepth);

		//! \brief 得到浅水等深线
		UGfloat GetShallowContour() const;
		//! \brief 设置浅水等深线
		void SetShallowContour(UGfloat dfShallowDepth);

		//! \brief 得到深水等深线
		UGfloat GetDeepContour() const;
		//! \brief 设置深水等深线
		void SetDeepContour(UGfloat dfDeepDepth);

		//! \brief 得到安全水深值
		UGfloat GetSafetyDepth() const;
		//! \brief 设置安全水深值
		void SetSafetyDepth(UGfloat dfSafetyDepth);

		//! \brief 是否显示其他的等深线标注。(不包括安全等深线标注)
		UGbool IsDisplayOtherContourLabel()const;
		//! \brief 设置显示其他的等深线标注。(不包括安全等深线标注)
		void SetDisplayOherContourLabel(UGbool bDisplayLabel);

		//! \brief 是否以两种颜色显示水深面
		UGbool IsDisplayTwoShades() const;
		//! \brief 设置以两种颜色显示水深面
		void SetDisplayTwoShades(UGbool bTwoShades);

		//! \brief 是否显示安全等深线标签（安全水深值）
		UGbool IsDisplaySafetyContourLabel()const;
		//! \brief 设置是否显示安全等深线标签（安全水深值）
		void SetDisplaySafeContourLabel(UGbool bDisplayLabel);

		//! \brief 是否显示元物标
		UGbool IsDisplayMetaObject() const;
		//! \brief 设置是否显示元物标
		void SetDisplayMetaObject(UGbool bDisplayMetaObject = true);

		//! \brief 是否显示图幅编号(DSNM)
		UGbool IsDisplayCellName() const;
		//! \brief 设置是否显示图幅编号(DSNM)
		void SetDisplayCellName(UGbool bDisplayCellName = true);

		//! \brief   读取海图的XML信息
		UGbool FromXML(const UGString& strXML);
		//! \brief   保存海图为XML
		UGString ToXML()const;

		//! \brief  重新设置初始化状态
		void Reset(UGMap* pMap);

		UGbool LoadColorTable(const UGString &strDisplayStyleName, UGChartColorMode::UGS52ColorMode eColorMode);
		UGbool LoadLookupTables(const UGString &strDisplayStyleName);

		UGbool IsColorTableLoaded();
		UGbool IsLookupTableLoaded();

		UGlong GetDepthUnit() const;
		void SetDepthUnit(UGlong nUnit);

		// 设置地图中物标是否显示的对应关系，使用前先调用GetDisplayFeature获取当前地图中含有的所有物标类型
		void SetDisplayableFeature(UGDict<UGString, UGbool>& dictDisplayFeature);
		// 获取当前地图下含有的所有物标类型以及是否显示的对应关系。默认所有物标都应该显示
		UGDict<UGString, UGbool> GetDisplayableFeature();

		// 是否显示物标编码为nCode所有物标, 供内部使用
		UGbool IsDisplayableFeature(UGint nCode);

		// 设置地图中物标是否可选择的物标种类，使用前先调用GetSelectableFeature获取当前地图中含有的所有物标类型
		void SetSelectableFeature(UGDict<UGString, UGbool>& dictSelectedFeature);
		// 获取当前地图下含有的所有物标类型以及是否可被选择的对应关系。默认所有物标都应该可以被选择
		UGDict<UGString, UGbool> GetSelectableFeature();

		// 判断物标编码为nCode的物标是否可以被选择，供内部使用
		UGbool IsSelectableFeature(UGint nCode);

		// 增加地图中的物标名。
		void AddFeature(UGint nCode);
		void ClearFeature();

		// 获取含有的可显示物标种类的总数。java 组件封装时需要使用。
		UGint GetDisplayableFeatureCount() const;
		// 获取含有的可选择物标种类的总数。java 组件封装时需要使用。
		UGint GetSelectableFeatureCount() const;

		const UGStyle& GetSelectionStyle() const;
		void SetSelectionStyle(const UGStyle& selectionStyle);

		//! \brief 是否启用文本裁剪区
		UGbool IsTextClipRegionEnabled() const;
		//! \brief 设置是否启用文本裁剪区
		void SetTextClipRegionEnabled(UGbool bEnabled = true);

		UGbool IsDisplayLowAccurateMarker() const;
		void SetDisplayLowAccurateMarker(UGbool bEnabled = true);
	protected:
		// !brief 类库内部计算使用的值都是以米为单位的
		// !brief 设置值的时候先转换成米为单位的数值
		UGfloat UnitConverteToMeter(UGfloat dfValue);
		// !brief 值获取的时候先从米转换为当前单位的数值
		UGfloat UnitConverteFromMeter(UGfloat dfValue) const;

		//! \brief  设置地图的更新标志
		void SetModifiedFlag(UGbool bModified = true);

	protected:
		UGChartLookupTable m_lookupTable;
		UGbool m_bLookupTableLoaded;

		UGChartColorTable m_ColorTable;
		UGbool m_bColorTableLoaded;

		UGString m_strDisplayStyleName;
		UGString m_strFontName;
		UGfloat m_dfFontSize;
		UGChartColorMode::UGS52ColorMode m_eColorMode;
		UGChartDisplayCategory::UGS52DisplayCategory m_eDisplayCategory;
		UGbool m_bSymbolizedBoundary;
		UGbool m_bSimplifiedMarker;
		UGbool m_bDisplayText;
		UGbool m_bDisplaySounding;
		UGbool m_bMinVisibleScaleEnabled;
		UGfloat m_dfSafetyContour;
		UGfloat m_dfShallowContour;
		UGfloat m_dfDeepContour;
		UGbool m_bDisplayTextNational;
		UGbool m_bDisplaySafetyContourLabel;
		UGbool m_bDisplayMetaObject;
		UGbool m_bDisplayCellName;
		UGbool m_bDisplayOtherContourLabel;
		UGfloat m_dfSafetyDepth;
		UGbool m_bTwoShades;
		UGlong m_nDepthUnit;
		UGbool m_bTextClipRegionEnabled;

		UGStyle m_selectionStyle;
		UGMap *m_pMap;
		UGDict<UGint, UGbool> m_dictDisplayFeature;
		UGDict<UGint, UGbool> m_dictSelectableFeature;

		UGChartDisplayStyle::UGChartDisplayStyleType m_eDisplayStyleType;

		UGbool m_bDisplayLowAccurateMarker;
	};
}
#endif //!defined(AFX_UGCHARTSETTING_H_)
