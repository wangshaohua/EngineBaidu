#if !defined(AFX_UGCHARTLAYER_H)
#define AFX_UGCHARTLAYER_H

#include "Drawing/UGDrawing.h"
#include "Engine/UGDataSource.h"
#include "Engine/UGDatasetGroup.h"
#include "Map/UGTheme.h"
#include "Map/UGSelection.h"
#include "Map/UGThemes.h"
#include "Stream/ugdefs.h"
#include "Map/UGLayer.h"
#include "ChartToolkit/UGS57SpatialLineManger.h"
#include "ChartToolkit/UGS57SpatialRelationshipParser.h"
//#include "ChartToolkit/UGS57DatasetGroupExt.h"
#include "ChartToolkit/UGChartDatasetGroup.h"
#include "Map/UGChartObjectInfo.h"
#include "ChartBase/UGChartDisplayCategory.h"

#define  MAX_S52PRIORITY 10
#define  SELECTED_MARKERID  60000001

#define  S57_DEPARE_LABEL 42
#define  S57_DEPCNT_LABEL 43
#define  S57_DRGARE_LABEL 46
#define  S57_UNSARE_LABEL 154
#define  S57_OBSTRN_LABEL 86
#define  S57_UWTROC_LABEL 153
#define  S57_WRECKS_LABEL 159


namespace UGC {

class UGLayers;
class UGChartSetting;
class UGChartSubLayer;

typedef UGArray<UGGeometry*> UGGeometrys;
typedef UGDict<UGint, UGArray<UGDataset*> > UGS57DatasetDict;

class MAP_API UGS57Edge 
{
public:
	UGS57Edge();
	~UGS57Edge();

	UGuint m_nEdgeId;
	UGbool m_bValid;
	UGint m_nOrient;
	UGGeoLine *m_pGeoLine;
};

class MAP_API UGS57FeatureStyle{

public:
	UGS57FeatureStyle();
	~UGS57FeatureStyle();

	UGint m_nCode;
	UGint m_nPriority;
	UGuint m_nFeatureID;
	UGlong m_nSCAMIN;
	UGChartDisplayCategory::UGS52DisplayCategory m_eCategory;
	UGGeometry::Type m_eGeoType;
	UGGeometry *m_pGeometry;
	UGArray<UGStyle> m_styles;
	UGArray<UGGeoPoint *> m_centerPnt;
	UGArray<UGGeoLine *> m_litarcs;
	UGArray<UGS57Edge *> m_edgeStyles;
	UGArray<UGGeoText *> m_texts;
};


class MAP_API UGChartLayer : public UGLayer
{
	friend class UGChartSubLayer;

public:
	MAP_APIF UGChartLayer();
	MAP_APIF ~UGChartLayer();
	MAP_APIF UGChartLayer(const UGChartLayer& chartLayer);	
	MAP_APIF UGChartLayer& operator =(const UGChartLayer& chartLayer);	

public:	
	
	//! \brief 导成XML信息
	MAP_APIF UGString ToXML(UGint nVersion = 0)const;
	//! \brief 读取XML信息
	MAP_APIF UGbool FromXML(const UGString& strXML,UGbool bIgnoreCaption = true, UGint nVersion = 0);

	//! \brief 重新设置图层信息
	MAP_APIF void Reset(UGbool bChangeStyle = true);
	
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

	//! \brief 绘制图层
	/**
	\param pGraphics			绘制到的Graphics[in]
	\param pDrawing				绘制类[in]
	\param pRecordSet           绘制的记录集[in]
	\param bSingle              记录集是否自由该图层自己使用[in]
	\return                     绘制成功返回true，反之为false
	*/
	MAP_APIF UGbool OnDraw(UGGraphics* pGraphics, UGDrawing *pDrawing, UGProgress* pProgress = NULL);

	MAP_APIF UGLayer* AddDataset(UGDataset *pDataset);

	MAP_APIF UGLayer* GetSubLayer(UGint nIndex);
	MAP_APIF UGint GetSubLayersCount();

	MAP_APIF void SetChartSetting(UGChartSetting *pChartSetting);
	MAP_APIF UGChartSetting * GetChartSetting();

	//! \brief 重新设置海图子图层的显示风格（即查找表内容）
	//! \brief 并根据海图子图层优先级对其排序
	MAP_APIF void ResetChartStyles(UGbool bOnlyResetPoint = false, UGbool bOnlyResetArea = false);

	MAP_APIF void ComputeBounds(UGLayer *pSubLayer);

	MAP_APIF UGRect2D GetBounds();

	MAP_APIF const UGPrjCoordSys& GetPrjCoordSys();

	// 后续可以考虑去除 因为DatasetGroup里面可以获取到
	MAP_APIF void SetDataSource(UGDataSource *pDatasource);

	MAP_APIF void SetDatasetGroup(UGDatasetGroup *pDatasetGroup);
	MAP_APIF UGDatasetGroup * GetDatasetGroup();

	MAP_APIF UGS57SpatialRelationshipParserDisplay* LoadSpatialRelationship();
	MAP_APIF UGS57SpatialRelationshipParserDisplay* GetSpatialRelationship();
	MAP_APIF UGS57SpatialLineManger *LoadSpatialLineManger();
	MAP_APIF UGS57SpatialLineManger *GetSpatialLineManger();

	//FromXML初始化数据集
	UGbool ValidateDatasets();

	//FromXML初始化数据集分组
	UGbool ValidateDatasetGroup();

	//  [7/13/2011 zhoujt]
	void ClearLayersSelection();
	//  [7/13/2011 zhoujt]
	//! \brief 获取所有选中对象的个数
	UGint GetSelectedGeometryCount();
	//  [7/13/2011 zhoujt]
	UGbool SelectWithRegion(UGGeoRegion &regSelection, UGbool bShiftMode = false, UGbool bControlMode = false, UGint nSelectionMode = 0);
	UGbool SelectWithLine(UGGeoLine &geoLine, UGbool bShiftMode/* = false*/, UGbool bControlMode/* = false*/, UGint nToleranceSelection = 0);
	//  [7/13/2011 zhoujt]
	//! \brief   鼠标点选事件
	UGbool HitTest(UGPoint2D pntHitTest, UGdouble dTolerance, UGbool bAppendMode = false,
		UGbool bControlMode = false);

	// 选中对象高亮显示
	void HighlightSelection(UGGraphics* pGraphics, UGDrawing* pDrawing);

	// UGArray<UGChartObjectInfo*> GetSelectedObjectInfo();

	UGbool DeleteSubLayer(UGDataset* pDataset);

	void SetNeedHighlight(UGbool bNeedHighlight);

	// 指定选择集中某个物标对象的featureID和SmID，单独将此对象高亮显示（选择集中的其它物标不再高亮）
	// 重新选择后，此物标的高亮显示即失效
	void HighlightObject(UGuint nRCID, UGint nSoundingID, UGbool bMoveToCenter);

	void SetEditAttribute(UGbool bEditAttribute);

	//void SetEditGeometry(UGbool bEditGeometry);

	// 设置文本裁剪区,裁剪图层中的点线对象，但不裁剪面
	void SetTextClipRegion(const UGGeoRegion& geoTextClipRegion);
	const UGGeoRegion& GetTextClipRegion() const;

	void SetModifiedS57EdgeStyle(UGArray<UGS57EdgeStyle>& s57EdgeStyles);

	UGbool IsInflateBounds();

	void SetEditable(UGbool bEditable = TRUE);

	UGint FindSubLayer(UGLayer *pLayer) const;

	UGLayer* GetCurrentSubLayer();
	void SetCurrentSubLayer(UGLayer* pCurrentSubLayer);

	UGLayer* GetSubLayer(UGuint nFeatureOBJL, UGDataset::DatasetType featureType);

	// 包装UGS57EditDatasetGroup的同名方法
	UGString GetUniqueFeatureObjectID();
	UGuint GetUniqueFeatureRCID();

	void RefershS57EditGroup();

	// 将子图层选中对象的ID数组转成Recordset，并且初始化选中对象信息
	UGRecordset* SelectionToRecordset(UGChartSubLayer *pSubLayer, UGDrawParamaters* pDrawParam);
	
private:
	void ReleaseGeometryAry();

	void DrawGeometry(UGGeometrys& aryGeometry,  UGDrawing *pDrawing, UGGraphics* pGraphics);
	void DrawGeoText(UGDrawing *pDrawing, UGGraphics* pGraphics);

	void MakeGeoLines(UGArray<UGGeometrys> &aryGeoLines, UGDrawing *pDrawing);

	//! \brief 绘制几何对象
	void DrawGeometrys(UGGraphics* pGraphics, UGDrawing *pDrawing);

	void DrawPaperChartGeometrys(UGGraphics *pGraphics, UGDrawing *pDrawing);

	//! \brief 先计算得出需要绘制的对象数组
	//! \remark 只要有一个图层计算成功了，就返回true
	UGbool ComputeGeometrys(UGGraphics* pGraphics, UGDrawing *pDrawing);

	UGbool ComputeGeometrysPaperChart(UGGraphics* pGraphics, UGDrawing *pDrawing);

	void DrawCellDSNM(UGPoint2D& posPoint, UGDrawing* pDrawing);

	UGDatasetVector* GetCurrentLayerVCDataset();
	UGDatasetVector* GetCurrentLayerVIDataset();

	void AddCodeDatasetDict(UGDataset *pDataset, UGint nCode=0);

	UGbool GetCodeDataset(UGint nCode, UGArray<UGDataset*> &aryDataset);

//	void AddS57AttiRecordset(UGint nCode);

// 	UGFeature* GetS57AttiFeature(UGint nCode, UGint nSmID);
// 
// 	UGFeature* GetS57AttiFeature(UGuint nRCID);

	UGVariant GetS57AttiFeature(UGint nCode, UGint nSmID);

	UGVariant GetS57AttiFeature(UGuint nRCID);

	// 高亮显示水深点
	UGbool HighlightSNDFRMText(UGGeometry *pGeometry, UGDrawing *pDrawing, UGfloat dDepth);

	// 清除选中的对象信息
	// void ClearSelectedObjectInfo();

	// 根据文件名和比例尺获得对应的数据集分组，递归调用
	UGDatasetGroup* FindChartGroup(UGDatasetGroup *pDatasetGroupRoot);

	//UGFeature* GetVIFeature(UGuint nRCID);
	//UGFeature* GetVCFeature(UGuint nRCID);

	UGshort GetVIQuaposValue(UGuint nRCID);
	UGshort GetVCQuaposValue(UGuint nRCID);


	void ClearCache();

	void SetClearCache(UGbool bClear);
	
	UGDatasetVector *GetFeatureDataset(UGint nCode, UGDataset::DatasetType eType);

	//UGChartQFind<UGint >* ReadAttiFeature(UGDatasetVector *pDataset,
	//						UGArray<UGFeature *>& arrFeature, UGArray<UGint>& arrID,
	//						UGbool bNeedSpatialQuery, UGbool bNeedReadAttiFeature);

	UGChartQFind<UGint >* ReadAttiFeature(UGDatasetVector *pDataset, UGint nCode,
		UGArray<UGVariant >& arrFeature, UGArray<UGint>& arrID,
		UGbool bNeedSpatialQuery, UGbool bNeedReadAttiFeature);

	//UGChartQFind<UGuint >* ReadVectorPoint(UGDatasetVector *pDataset,
	//					UGArray<UGFeature *>& arrFeature, UGArray<UGuint>& arrRCID);

	UGChartQFind<UGuint >* ReadVectorPoint(UGDatasetVector *pDataset,
		UGArray<UGshort>& arrQuaposValue, UGArray<UGuint>& arrRCID);

	void SpatialQueryFeatures(UGDatasetVector *pDataset, UGRecordset *pRecordDEPARE, 
							  UGRecordset *pRecordDRGARE, UGRecordset *pRecordUNSARE,
							  UGArray< UGArray<UGint> >& arrIDs);

	void SpatialQueryFeatures( UGRecordset *pRecord, UGRecordset *pRecordDEPARE, 
							   UGRecordset *pRecordDRGARE, UGRecordset *pRecordUNSARE,
							   UGint nCode, UGChartSubLayer *pSubLayer);

	void SetSpatialQueryFeatureIDs(UGChartSubLayer* pSubLayer, UGRecordset *pRecordDEPARE, 
							UGRecordset *pRecordDRGARE, UGRecordset *pRecordUNSARE, UGDatasetVector *pDataset, UGint nCode);

	UGbool CreatTextClipRgn(UGGraphics* pGraphics, UGDrawing *pDrawing);

	UGdouble CalculateSymScale(UGDrawing* pDrawing);

	void AddS57FeatureStyle(UGS57FeatureStyle* pS57FeatureStyle);
	void DrawTextPaperChart(UGDrawing *pDrawing, UGGraphics* pGraphics, UGS57FeatureStyle *pS57FeatureStyle, UGdouble dCos, UGdouble dSin);
	void DrawCenterPointPaperChart(UGDrawing *pDrawing, UGGraphics* pGraphics, UGS57FeatureStyle *pS57FeatureStyle, UGdouble dCos, UGdouble dSin);
	void DrawEdgePaperChart(UGDrawing *pDrawing, UGGraphics* pGraphics, UGS57FeatureStyle *pS57FeatureStyle, UGdouble dCos, UGdouble dSin);
	void DrawGeometryPaperChart(UGDrawing *pDrawing, UGGraphics* pGraphics, UGS57FeatureStyle *pS57FeatureStyle, UGdouble dCos, UGdouble dSin);
	void DrawLitArc(UGDrawing *pDrawing, UGGraphics* pGraphics, UGS57FeatureStyle *pS57FeatureStyle, UGdouble dCos, UGdouble dSin);

	UGS57FeatureStyle* GetS57FeatureStyle(UGuint nFeatureID);

private:
	UGChartSetting* m_pChartSetting;

	UGRect2D m_rcBounds;

	UGS57SpatialLineManger *m_pSpatialLineManger;
	UGS57SpatialRelationshipParserDisplay *m_pSpatialRSParser;

	UGDataSource *m_pDatasource;// 后续可以考虑去除
	UGDatasetGroup *m_pDatasetGroup;

	UGDatasetVector *m_pVIDataset;
	UGDatasetVector *m_pVCDataset;

	UGS57DatasetDict m_dictDataset;

	//UGDict<UGuint, UGFeature* > m_dictAttiFeature;

	//UGS57DatasetGroupExt* m_pS57GroupInfo;
	UGChartDatasetGroup* m_pChartDatasetGroup;

	// UGArray<UGChartObjectInfo*> m_arrSelectedObjectInfo;

	// 选中时是否需要高亮显示
	// remarks 单一选择模式时，将其它图层都设为不需要高亮
	UGbool m_bNeedHighlight;

	// 选择的单一对象的RCID值
	UGuint m_nSingleSelectedRCID;

	// 选择的水深点的SmID（水深点不能通过RCID唯一标识）
	UGint m_nSelectedRecordsetID;

	// 海图数据集分组的名称，7C后增加
	UGString m_strDatasetGroupName;

	// 海图文件对应的文件名
	UGString m_strCellDSNM;

	// 海图文件对应的比例尺分母
	UGlong m_nCellScale;

	UGArray< UGArray<UGint> > m_OBSTRNP_IDs;
	UGArray< UGArray<UGint> > m_OBSTRNL_IDs;
	UGArray< UGArray<UGint> > m_OBSTRNA_IDs;
	UGArray< UGArray<UGint> > m_UWTROCP_IDs;
	UGArray< UGArray<UGint> > m_WRECKSP_IDs;
	UGArray< UGArray<UGint> > m_WRECKSA_IDs;
		
	UGbool m_bSpatialQuery;
	
	UGDict<UGuint, UGVariant> m_dictAttiFeature;

	UGChartQFind<UGint > *m_pDEPAREAtti;
	UGChartQFind<UGint > *m_pDRGAREAtti;
	UGChartQFind<UGint > *m_pDEPCNTAtti;

	// 下面三个数组分别存储的是DRVAL1和VALDCO两个字段的字段值，
	// DEPARE 和 DRGARE只需存储DRVAL1，DEPCNT只需存储VALDCO

	//UGArray<UGFeature *> m_arrFeatureDEPARE;
	UGArray<UGVariant> m_arrValDRVAL1DEPARE;
	UGArray<UGint> m_arrIDDEPARE;

	UGArray<UGVariant> m_arrValDRVAL1DRGARE;
	//UGArray<UGFeature *> m_arrFeatureDRGARE;
	UGArray<UGint> m_arrIDDRGARE;

	UGArray<UGVariant> m_arrValVALDCODEPCNT;
	//UGArray<UGFeature *> m_arrFeatureDEPCNT;
	UGArray<UGint> m_arrIDDEPCN;

	UGChartQFind<UGuint > *m_pFeatureVI;
	UGChartQFind<UGuint > *m_pFeatureVC;

	//UGArray<UGFeature *> m_arrFeatureVI;
	UGArray<UGshort> m_arrValQuaposVI;
	UGArray<UGuint> m_arrRCIDVI;

	//UGArray<UGFeature *> m_arrFeatureVC;
	UGArray<UGshort> m_arrValQuaposVC;
	UGArray<UGuint> m_arrRCIDVC;

	// UGbool m_bClearCache;

	UGbool m_bAttributeEdit;

	// UGbool m_bGeometryEdit;

	UGGeoRegion m_TextClipRegion;

	UGRgn* m_pTextClipRgn;

	UGArray<UGS57EdgeStyle> m_modifiedS57EdgeStyles;

	UGbool m_bIsInflateBounds;

	UGLayer* m_pCurrentLayer;

protected:

	UGDrawing *m_pDrawing;

public:
	// 存储面、线(CSP内部产生的线)
	UGArray<UGGeometrys> m_aryDrawingGeometrys;

	// 存储点对象的数组
	UGArray<UGGeometrys> m_aryDrawingGeoPoints;

	UGGeometrys m_aryDrawingGeoText;

	// 点物标对应的显示风格
	UGDict< UGuint, UGArray<UGStyle> > m_dictPointStyle;
	// 线面物标对应的子线的显示风格

	UGList<UGLayer*> m_SubChartLayers;

	// 纸质海图风格存储。
	UGArray<UGS57FeatureStyle *> m_s57FeatureStyles;
	UGint m_naryIndex;
};

}

#endif // !defined(AFX_UGLAYER_H__A4B430F7_6A63_4275_BB13_EF15BA12DDAD__INCLUDED_)


