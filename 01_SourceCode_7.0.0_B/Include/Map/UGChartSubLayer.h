// UGChartSubLayer.h
//
//////////////////////////////////////////////////////////////////////

/*!
   **************************************************************************************
    \file     UGChartSubLayer.h 
   **************************************************************************************
    \author   周江涛
    \brief    扩展的海图图层类，负责数据集对象显示和专题图显示。                                                                       
    \attention   
   ----------------------------------------------------------------------------------<br>
    Copyright (c) 2000-2011 SuperMap Software Co., Ltd.                           <br>
    All Rights Reserved.                                                             <br>
   ----------------------------------------------------------------------------------<br> 
   
   **************************************************************************************
    \version 2011-04-13 周江涛    初始化版本.                                       <br>
   **************************************************************************************
*/

#if !defined(AFX_UGCHARTSUBLAYER_H_)
#define AFX_UGCHARTSUBLAYER_H_

#include "Stream/ugdefs.h"
#include "Toolkit/UGMarkup.h"
#include "Toolkit/UGStyle.h"
#include "Engine/UGDataset.h"
#include "Engine/UGRecordset.h"
#include "FileParser/UGFileParseVector.h"
#include "ChartBase/UGChartLookupTable.h"
#include "ChartBase/UGChartColorTable.h"
#include "ChartBase/UGChartColorMode.h"
#include "ChartBase/UGChartColorTable.h"
#include "ChartBase/UGChartDisplayCategory.h"
#include "Drawing/UGDrawing.h"
#include "Map/UGChartSetting.h"
#include "Map/UGChartLayer.h"
#include "Map/UGMap.h"
#include "ChartToolkit/UGS57DatasetExtInfo.h"

#define  S52DASHLINE 60000998
#define  S52DOTLINE  60000999

#define  TEXT_COLOR _U("CHBLK")
#define  TEXT_BKCOLOR _U("DEPMD")
#define  TEXT_OFFSETUNIT 350    //3.5mm，文本偏移的基本单位，10号字体的字高

#define  S52TRANSPARENCYSTEP 25	//只有 1:25%透明；2:50%透明；3:75%透明

#pragma once
namespace UGC {

	class MAP_API UGChartSubLayer : public UGLayer
	{
		friend class UGChartSetting;

		// CSP内部产生的图层中需要注意的一些基本信息。
		struct UGCSPInnerLayerInfo{
			UGChartDisplayCategory::UGS52DisplayCategory eDisplayCategory;
			UGlong  bIgnoreMinscale;
			UGint nPriority;

			UGCSPInnerLayerInfo()
			{
				eDisplayCategory = UGChartDisplayCategory::Standard;
				bIgnoreMinscale = false;
				nPriority = 8;
			}
		};

		// CSP内部新增的点对象的信息。
		struct UGCSPPointStyle{
			UGString strSymbol;
			UGCSPInnerLayerInfo innerLayerInfo;

			UGCSPPointStyle()
			{
				strSymbol.Empty();
			}
		};

	public:
		UGChartSubLayer(UGChartLayer *pParentLayer);
		~UGChartSubLayer(void);
		UGChartSubLayer& operator =(const UGChartSubLayer& layer);
	public:
		//! \brief 绘制图层
		UGbool OnDraw(UGDrawing *pDrawing, UGRecordset *pDisplayRecordset);
		//! \brief 导成XML信息
		UGString ToXML(UGint nVersion = 0)const;
		//! \brief 读取XML信息
		UGbool FromXML(const UGString& strXML, UGint nVersion = 0);

		//! \brief 设置物标简称
		void SetFeatureAcronym(const UGString &strFeatureAcronym);

		//! \brief 设置物标编码
		void SetFeatureCode(UGint nCode);

		UGint GetFeatureCode();

		//! \brief 设置点物标类型的S52查找表信息
		void ResetPointStyleItems();
		//! \brief 设置线物标类型的S52查找表信息
		void ResetLineStyleItems();
		//! \brief 设置面物标类型的S52查找表信息
		void ResetAreaStyleItems();

		void SetQueryDef(UGQueryDef& QueryDef);

		void ResetLookupItems(UGbool bOnlyResetPoint = false, UGbool bOnlyResetArea = false);

		void SetDataset(UGDataset *pDataset, UGbool bInit = true, UGbool bClearRecordsets = true);

		void SetRecord(UGRecordset *pRecord, UGint nCode);

		void SetArrs(UGArray<UGint>& ArrTagIDs, UGArray<UGint>& ArrSrcIDs, UGArray<UGint>& ArrSrcIDCount, UGint nCode);

		//! \brief 设置空间关系
		void SetSpatialRelationship();
		//! \brief 设置空间线管理类指针 
		void SetSpatialLineManger();

		UGLayer* GetParentLayer() const;

		UGDataset* GetDataset();	

	private:

		//! \brief		绘制海图物标
		//! \remarks	接口里面只会处理当前记录，请在外面自行移到指定记录
		UGbool DrawChartObject(UGRecordset *pRecord, UGFieldInfo& fieldInfo, UGDrawing *pDrawing);

		//! \brief	绘制线或面物标的中心点符号
		//! \param	arrCenterMarkerStyle [in] 中心点符号的风格数组（面物标可能由多个符号表示）
		//! \param  pGeometry [in] 中心符号位置点对象。
		void DrawCenterPointMarker(UGArray<UGStyle>& arrCenterMarkerStyle, UGGeometry* pGeometry, UGDrawing *pDrawing);

		// 纸质海图绘制中心点符号
		void DrawCenterPointMarker(UGArray<UGStyle>& arrCenterMarkerStyle, UGGeometry* pGeometry, 
			                   UGDrawing *pDrawing, UGS57FeatureStyle *pS57FeatureStyle);

		//! \brief	获取中心点符号位置点
		//! \param	pGeometry 需要绘制中心点符号的对象，面或者线
		//! \return 返回中心符号位置点。 
		UGbool GetCenterPoint(UGGeometry* pGeometry,UGGeoPoint *pCenterPoint, UGDrawing *pDrawing);

		UGbool GetCenterPointPaperChart(UGGeometry* pGeometry,UGGeoPoint *pCenterPoint);

		//! \brief 设置物标的点符号UGStyle
		//! \param style [out] 需要设置的UGStyle
		//! \param symbolMarkerStyle [in] 海图点符号风格
		//! \param pRecord [in] 记录集指针
		//! \return	是否设置了有效的点符号风格(有效才加入中心点符号的风格数组)
		UGbool SetObjectMarkerStyle(UGArray<UGStyle>& styles, UGDrawMaker* pDrawMaker, UGArray<UGChartSymbolMarkerStyle>& symbolMarkerStyles, UGRecordset* pRecord);
		//! \brief 设置物标的线风格UGStyle
		//! \param style [out] 需要设置的UGStyle
		//! \param strLineSymbolName [in] 海图复杂线型的符号名
		//! \param simpleLineStyle [in] 海图简单线型
		void SetObjectLineStyle(UGStyle& style, UGDrawMaker* pDrawMaker, const UGString& strLineSymbolName, const UGChartLineStyle& simpleLineStyle);
		//! \brief 设置物标的填充风格UGStyle
		//! \param style [out] 需要设置的UGStyle
		//! \param strAreaPattern [in] 海图填充图案的符号名
		//! \param strAreaColor [in] 海图填充颜色的编码
		void SetObjectFillStyle(UGStyle& style, UGDrawMaker* pDrawMaker, const UGString& strAreaPattern, const UGString& strAreaColor, const UGint nTransparency = 0);

		//! \brief		在当前比例尺是否太小使物标不显示
		//! \remarks	与是否设定显示与最小比例尺相关以及物标的SCAMIN字段值有关
		UGbool IsMinScaleVisible(UGRecordset *pDisplayRecordset, UGDrawing *pDrawing);
		//! \brief 在当前海图显示类别下，物标是否显示
		UGbool IsShowOnDisplayCategory(UGChartDisplayCategory::UGS52DisplayCategory eObjectDisplayCategory);

		//! \brief	调用条件符号程序
		UGbool CallConditionalSymbology(UGRecordset *pRecord, UGGeometry *pGeometry, UGDrawing *pDrawing,
										UGChartDisplayCategory::UGS52DisplayCategory eObjectDisplayCategory,
										UGS57FeatureStyle *pS57FeatureStyle = NULL);


		UGChartPointObjectStyle* MatchAttribsPoint(UGRecordset *pRecord, UGFieldInfo &fieldInfo/*, UGChartPointObjectStyle** pPointStyle*/);
		UGChartLineObjectStyle* MatchAttribsLine(UGRecordset *pRecord, UGFieldInfo &fieldInfo/*, UGChartLineObjectStyle& lineStyle*/);
		UGChartAreaObjectStyle* MatchAttribsArea(UGRecordset *pRecord, UGFieldInfo &fieldInfo/*, UGChartAreaObjectStyle& areaStyle*/);
		UGbool IsMatchAttribs(UGVariant &valValue, UGFieldInfo &fieldInfo, const UGChartAttributeCondition &attribCondition);
		
		//! DEPARE02条件符号程序解析算法
		UGbool CS_DEPARE02(UGRecordset *pRecord, UGGeometry* pGeometry, UGDrawing *pDrawing);
		UGColor CS_SEABED01(UGRecordset *pRecord, UGfloat dfDRVAL1, UGfloat dfDRVAL2, UGString &strFillPattern);
		UGbool CS_SAFCON01(UGfloat dfDepthValue, UGGeometry *pGeo, UGDrawing *pDrawing);

		UGbool CS_LIGHTS05(UGRecordset *pRecord, UGGeometry* pGeometry, UGDrawing *pDrawing);
		UGbool LIGHTS05ContinuationA(UGRecordset *pRecord, UGGeometry* pGeometry, UGDrawing *pDrawing,
									const UGString& strCATLIT, const UGString &strColor);
		UGbool LIGHTS05ContinuationB(UGRecordset *pRecord, UGGeometry* pGeometry, UGDrawing *pDrawing,
									const UGString &strColor,  UGVariant &valSector1, UGVariant &valSector2);

		UGbool CS_LIGHTSPaperChart(UGRecordset *pRecord, UGGeometry* pGeometry, UGDrawing *pDrawing, UGS57FeatureStyle *pS57FeatureStyle);

		void SetGeoTextStyle(UGDrawing *pDrawing, UGChartTextFormat &textFromat, UGGeoText *pGeoText, UGTextStyle &textStyle);

		UGString CS_LITDSN01(UGRecordset *pRecord, const UGString& strCATLIT, const UGString& strColor);


		void LitdsnCategory(const UGString& strCATLIT, UGString &strDescription);
		void LitdsnCharacteristic(UGint &nLITCHR, UGchar cchr[10]);
		UGint LitdsnSigGroup(const UGString& strSIGGRP, UGchar cgrp[10][10]);
		UGint LitdsnColor(const UGString& strColor, UGchar ccol[5][3]);
		UGint LitdsnStatus(const UGString& strSTATUS, UGchar cstat[4][10]);



		UGbool IsExtendRadius(UGuint unFeatureID, UGfloat dfSector1, UGfloat dfSector2);
		UGbool LIGHTS05DrawingSectorLine(UGRecordset *pRecord, UGGeometry* pGeometry, UGDrawing *pDrawing,
										UGfloat dfSector1Agnle, UGfloat dfSector2Angle, UGfloat dfLEGLEN, 
										UGS57FeatureStyle *pS57FeatureStyle = NULL);

		UGbool CS_DEPCNT03(UGRecordset *pRecord, UGGeometry* pGeometry, UGDrawing *pDrawing);

		UGbool CS_QUAPOS01(UGRecordset *pRecord, UGGeometry* pGeometry, UGDrawing *pDrawing);

		UGbool CS_QUALIN01(UGRecordset *pRecord, UGDrawing *pDrawing);
		// 如果返回值非空，返回的符号是SY(LOWACC01)
		UGString CS_QUAPNT02(UGRecordset *pRecord);
		UGbool	IsPointFeatureSpatialAccurate(UGuint unFeatureId);
		UGbool	IsLineRegionFeatureSpatialAccurate(UGuint unFeatureId);

		UGbool CS_SOUNDG02(UGRecordset *pRecord, UGGeometry* pGeometry, UGDrawing *pDrawing);

		UGbool CS_SOUNDG02PaperChart(UGRecordset *pRecord, UGGeometry* pGeometry, UGDrawing *pDrawing, UGS57FeatureStyle *pS57FeatureStyle);

		// 在这里面就把对象绘制了， CS_SOUNDG02调用
		UGbool CS_SNDFRM03(UGRecordset *pRecord, UGfloat dfDepth, UGStrings &arySymbols);
		
		// 在调用在上面CS_SNDFRM03接口后需要调用ShowSNDFRMText接口才能绘制水深标注。
		UGbool ShowSNDFRMText(UGGeometry *pGeometry, UGDrawing *pDrawing, UGfloat dfDepthValue, UGS57FeatureStyle *pS57FeatureStyle = NULL);

		UGbool CS_TOPMAR01(UGRecordset *pRecord, UGGeometry *pGeometry, UGDrawing *pDrawing);

		//{{ CSP WRECKSnn
		UGbool CS_WRECKS04( UGRecordset *pRecord, UGGeometry *pGeometry, UGDrawing *pDrawing,
							UGChartDisplayCategory::UGS52DisplayCategory eObjectDisplayCategory);

		UGbool WRECKS04Point(   UGRecordset *pRecord, UGGeometry *pGeometry, UGDrawing *pDrawing,
								UGCSPPointStyle &cspPointStyle, UGbool bShowISODanger, 
								UGbool bScaleVisible, UGbool bDisplayCategory,
								UGStrings arySoundingSymbol, UGfloat dfDepthValue, 
								UGbool bGivenVALSOU, UGfloat dfValsou,
								UGint nCATWRK, UGint nWATLEV,
								const UGString &strLowAccySymbol);

		 UGbool WRECKS04Region( UGRecordset *pRecord, UGGeometry *pGeometry, UGDrawing *pDrawing,
								UGCSPPointStyle &cspPointStyle, UGbool bShowISODanger, 
								UGbool bScaleVisible, UGbool bDisplayCategory,
								UGStrings arySymbolsSounding, UGbool bGivenVALSOU,
								UGfloat dfValsou, UGint nWATLEV, UGfloat dfDepthValue, 
								const UGString &strLowAccySymbol);
		
		// 绘制CS_WRECKS04条件符号内部产生的图层。
		UGbool CS_WRECKS04Inner(UGRecordset *pRecord, UGGeometry *pGeometry, UGDrawing *pDrawing);
		//}} CSP WRECKSnn

		UGbool CS_DEPVAL02( UGRecordset *pRecord, UGGeometry *pGeometry, UGint nWATLEV, UGint nEXPSOU, 
							UGfloat &dfLeastDepth, UGfloat &dfSeabedDepth);
		UGbool DEPVAL02GetLeastDepth(UGRecordset *pRecordset, UGint nCode, UGfloat &dfLeastDepth);

		UGbool CS_UDWHAZ04( UGRecordset *pRecord, UGfloat dfDepthValue,
							UGCSPPointStyle &cspPointStyle);

		UGbool UDWHAZ04IsDanger(UGRecordset *pRecordset, UGint nCode, UGbool bNeedDeeper);

		// {{CSP OBSTRNnn
		UGbool CS_OBSTRN06(UGRecordset *pRecord, UGGeometry *pGeometry, UGDrawing *pDrawing,
							UGChartDisplayCategory::UGS52DisplayCategory eObjectDisplayCategory);
		
		UGbool OBSTRN06ContinuationA( UGRecordset *pRecord, UGGeometry *pGeometry, UGDrawing *pDrawing,
									  UGCSPPointStyle &cspPointStyle, UGbool bShowISODanger, 
									  UGbool bScaleVisible, UGbool bDisplayCategory,
									  UGStrings arySoundingSymbol, UGfloat dfDepthValue,
									  UGbool bGivenVALSOU, UGfloat dfValsou,
									  UGbool bGivenWATLEV, UGint nWATLEV,
									  UGint nCATBOS);

		UGbool OBSTRN06ContinuationB( UGRecordset *pRecord, UGGeometry *pGeometry, UGDrawing *pDrawing,
									  UGCSPPointStyle &cspPointStyle, UGbool bShowISODanger, 
									  UGbool bScaleVisible, UGbool bDisplayCategory,
									  UGStrings arySoundingSymbol, UGfloat dfDepthValue,
									  UGbool bGivenVALSOU, UGfloat dfValsou);
		
		UGbool OBSTRN06ContinuationC( UGRecordset *pRecord, UGGeometry *pGeometry, UGDrawing *pDrawing,
									  UGCSPPointStyle &cspPointStyle, UGbool bShowISODanger, 
			                          UGbool bScaleVisible, UGbool bDisplayCategory,
			                          UGStrings arySoundingSymbol, UGfloat dfDepthValue,
			                          UGbool bGivenVALSOU, UGfloat dfValsou,
			                          UGbool bGivenWATLEV, UGint nWATLEV,
			                          UGint nCATBOS);

		UGbool CS_OBSTRN06Inner(UGRecordset *pRecord, UGGeometry *pGeometry, UGDrawing *pDrawing);
		// }}CSP OBSTRNnn
		
		UGbool CS_SLCONS03(UGRecordset *pRecord, UGGeometry *pGeometry, UGDrawing *pDrawing);
		UGbool SLCONS03Point(UGRecordset *pRecord, UGGeometry *pGeometry, UGDrawing *pDrawing, UGuint unFeatureID);
		UGbool SLCONS03Line(UGRecordset *pRecord, UGGeometry *pGeometry, UGDrawing *pDrawing, UGuint unFeatureID);

		// {{CSP RESAREnn
		UGbool CS_RESARE03(UGRecordset *pRecord, UGGeometry *pGeometry, UGDrawing *pDrawing);

		UGbool RESARE03ContinuationA(UGRecordset *pRecord, UGGeometry *pGeometry, UGDrawing *pDrawing, 
									 const UGString& strRESTRNValue);

		UGbool RESARE03ContinuationB(UGRecordset *pRecord, UGGeometry *pGeometry, UGDrawing *pDrawing, 
									const UGString& strRESTRNValue);
		
		UGbool RESARE03ContinuationC(UGRecordset *pRecord, UGGeometry *pGeometry, UGDrawing *pDrawing, 
									const UGString& strRESTRNValue);
		
		UGbool RESARE03ContinuationD(UGRecordset *pRecord, UGGeometry *pGeometry, UGDrawing *pDrawing, 
									const UGString& strRESTRNValue);

		UGbool RESARE03ContinuationE(UGRecordset *pRecord, UGGeometry *pGeometry, UGDrawing *pDrawing);
		// }}CSP RESAREnn

		UGbool CS_RESTRN01(UGRecordset *pRecord, UGGeometry *pGeometry, UGDrawing *pDrawing);

		UGbool CS_RESCSP02(UGRecordset *pRecord, UGGeometry *pGeometry, UGDrawing *pDrawing, const UGString& strRESTRN);
		
		// 绘制空填充的面对象。
		UGbool DrawArea( UGGeometry *pGeometry, UGDrawing *pDrawing, 
						 const UGString& strAreaPattern, 
						 const UGString& strAreaColor);

		UGbool DrawArea(UGRecordset *pRecordset, UGGeometry *pGeometry, UGDrawing *pDrawing, 
						const UGString& strAreaPattern,	const UGString& strAreaColor,
						UGint nLineStyleID = UGPen::PenNull,
						const UGString& strLineColor = _U("CHBLK"), UGint nLineWidth = 1);

		UGbool DrawArea(UGRecordset *pRecordset, UGGeometry *pGeometry, UGDrawing *pDrawing,
			            UGStyle &style, UGArray<UGStyle>& arrCenterMarkerStyle);

		UGbool DrawArea(UGRecordset *pRecordset, UGGeometry *pGeometry, UGDrawing *pDrawing,
			UGStyle &style, UGArray<UGStyle>& arrCenterMarkerStyle, UGS57FeatureStyle *pS57FeatureStyle);

		// 绘制点符号
		UGbool DrawMarker(UGGeometry *pGeometry, UGDrawing *pDrawing, const UGString& strMarkSymbol, UGshort nPriority, UGuint nRCID = 0, UGfloat dAngle=0.0);

		// 绘制简单线
		UGbool DrawSimpleLine( UGGeometry *pGeometry, UGDrawing *pDrawing,
								UGint nLineId, UGint nWide, const UGString& strColor);

		UGStyle GetSimpleLineStyle(UGDrawing *pDrawing, UGint nLineId, UGint nWide, const UGString& strColor);
		// 绘制复杂线
		UGbool DrawComplexLine(UGGeometry *pGeometry, UGDrawing *pDrawing, const UGString &strLineSymbol);

		UGStyle GetComplexLineStyle(UGDrawing *pDrawing, const UGString &strLineSymbol);

		UGbool DrawLine(UGRecordset *pRecord, UGDrawing *pDrawing, UGGeometry *pGeometry,
						UGStyle &style, UGArray<UGStyle>& arrCenterMarkerStyle);

		UGbool DrawLine( UGRecordset *pRecordset, UGint nLineStyleID, const UGString& strLineColor, UGint nLineWidth);

		UGbool DrawLine(UGRecordset *pRecord, UGDrawing *pDrawing, UGGeometry *pGeometry,
			UGStyle &style, UGArray<UGStyle>& arrCenterMarkerStyle, UGS57FeatureStyle *pS57FeatureStyle);
		
		UGbool IsSharedGroup1(UGS57Features aryFeature, UGuint unFeatureID);
		UGbool IsSharedRives(UGS57Features aryFeature, UGuint unFeatureID);
		
		UGbool DrawText(UGArray<UGChartTextFormat>& arrTextFormat, UGRecordset *pRecord,
			UGGeometry* pGeometry, UGFieldInfo &fieldInfo, UGDrawing *pDrawing);

		UGbool DrawText(UGArray<UGChartTextFormat>& arrTextFormat, UGRecordset *pRecord,
			UGGeometry* pGeometry, UGFieldInfo &fieldInfo, UGDrawing *pDrawing, UGS57FeatureStyle *pS57FeatureStyle);

		UGbool ComputeLineMaxPriority(UGS57SpatialLine *pSpatialLine, UGshort nPriority);

		// 根据当前的颜色模式得到对应的符号名（不同的颜色模式使用不同的符号）
		UGString GetSymbolNameOnColorMode(const UGString& strSymbolName);

		UGGeoLine *MakeSpatialLine(UGDrawing *pDrawing, UGGeoLine *pGeoLine, UGint nORNT);

	private:


		//void SetS57DatasetGroup();
		//void SetVCDataset();
		//void SetVIDataset();

	    UGbool UDWHAZ04IsDanger(UGRecordset *pTagRecordset,UGint nCode, 
			                    UGArray<UGint>& ArrTagIDs, UGArray<UGint>& ArrSrcIDs, 
								UGArray<UGint>& ArrSrcIDCount, UGbool bNeedDeeper);

		UGbool DEPVAL02GetLeastDepth(UGRecordset *pTagRecordset, UGint nCode,
									UGArray<UGint>& ArrTagIDs, UGArray<UGint>& ArrSrcIDs, 
									UGArray<UGint>& ArrSrcIDCount, UGfloat &dfLeastDepth);

		UGbool HaveSrcRecord(UGRecordset *pTagRecordset, UGint nCode, 
								UGArray<UGint>& ArrTagIDs, UGArray<UGint>& ArrSrcIDs, 
								UGArray<UGint>& ArrSrcIDCount);

	public:

		UGArray<UGChartPointObjectStyle *> m_pointStyles;
		UGArray<UGChartLineObjectStyle *> m_lineStyles;
		UGArray<UGChartAreaObjectStyle *> m_areaStyles;

		//! \brief 物标简称
		UGString m_strFeatureAcronym;

		//! \brief 条件符号程序名称
		UGString m_strCSPName;

		UGS57SpatialRelationshipParserDisplay *m_pSpatialRSParser;

		UGChartSetting *m_pChartSetting;

		UGS57SpatialLineManger *m_pSpatialLineManger;

		//UGS57DatasetGroupExt *m_pS57Group;

	private:
		//UGDatasetVector *m_pVIDataset;
		//UGDatasetVector *m_pVCDataset;
		UGChartLayer *m_pParentLayer;
		//! \brief 显示优先级
		UGint m_nPriority;

		//UGRecordset *m_pReDEPARE;
		//UGRecordset *m_pReDRGARE;
		//UGRecordset *m_pReUNSARE;

		// 0x01 DEPARE
		// 0x20 DRGARE
		// 0x40 UNSARE
		UGbyte m_HaveDangerRecord; 

		UGArray<UGint> m_nArrTagIDs_DEPARE;
		UGArray<UGint> m_nArrSrcIDs_DEPARE;
		UGArray<UGint> m_nArrSrcIDCount_DEPARE;

		UGArray<UGint> m_nArrTagIDs_DRGARE;
		UGArray<UGint> m_nArrSrcIDs_DRGARE;
		UGArray<UGint> m_nArrSrcIDCount_DRGARE;

		UGArray<UGint> m_nArrTagIDs_UNSARE;
		UGArray<UGint> m_nArrSrcIDs_UNSARE;
		UGArray<UGint> m_nArrSrcIDCount_UNSARE;

		UGint m_nCode;
	};
}

#endif //!defined(AFX_UGChartSubLayer_H_)

