// UGSelection.h: interface for the UGSelection class.
//
//////////////////////////////////////////////////////////////////////

/*!
   **************************************************************************************
    \file     UGSelection.h
   **************************************************************************************
    \author   陈国雄
    \brief    选择集合类                                                             
    \attention   
   ----------------------------------------------------------------------------------<br>
    Copyright (c) 2000-2010 SuperMap Software Co., Ltd.                           <br>
    All Rights Reserved.                                                             <br>
   ----------------------------------------------------------------------------------<br> 
   
   **************************************************************************************
    \version 2005-05-20  陈国雄    初始化版本.                                       <br>
   **************************************************************************************
*/

#if !defined(AFX_UGSELECTION_H__2FBE2AA1_B3D6_469E_854F_CC6E86B762D0__INCLUDED_)
#define AFX_UGSELECTION_H__2FBE2AA1_B3D6_469E_854F_CC6E86B762D0__INCLUDED_

#include "Engine/UGDataSource.h"
#include "Drawing/UGDrawing.h"
//#include "Map/UGLayer.h"
#include "Geometry/UGGeometry.h"
#include "Map/UGChartObjectInfo.h"
namespace UGC {

	enum UGStyleOptions
	{
		FillBackColor					= 0x01,
		FillForeColor					= 0x02,
		FillBackOpaque					= 0x04,
		FillGradientAngle				= 0x08,
		FillGradientOffsetRatioX		= 0x10,
		FillGradientOffsetRatioY		= 0x20,
		FillGradientMode				= 0x40,
		FillOpaqueRate					= 0x80,
		FillSymbolID					= 0x100,

		LineColor						= 0x200,
		LineSymbolID					= 0x400,
		LineWidth						= 0x800,

		MarkerAngle						= 0x1000,
		MarkerSize						= 0x2000,
		MarkerSymbolID					= 0x4000,

		SymbolMarker					= 0x8000,
		SymbolLine						= 0x10000,
		SymbolFill						= 0x20000,    
	};


	class UGLayer;

class MAP_API UGSelection  
{
public:
	UGSelection();
#ifdef SYMBIAN60
	~UGSelection();
#else
	virtual ~UGSelection();
#endif

public:
	//! \brief 设置保留记录集
	void SetReserveRs(UGRecordset* pRecordset, UGbool bAutoRelease = false);   
	//! \brief 获取保留记录集
	UGRecordset* GetReservedRs()const;  
	//! \brief 从记录集生成选择集
	UGbool FromRecordset(UGRecordset* pRecordset);
	//! \brief 用选择集生成记录集
	UGRecordset* ToRecordset(UGbool bGeometryOnly = true,UGRect2D rcBounds = UGRect2D(0.0, 0.0, 0.0, 0.0), UGbool bChartSubLayer = false)const;
	//! \brief 查找指定ID在选择集中的索引
	UGint FindID(UGint nID, UGint nSearchCount = 0) const;
	//! \brief 向选择集中添加选中对象ID
	UGint Add(UGuint unID,UGGeometry* pGeometry = NULL);
	//! \brief 删除指定索引后的nCount选中对象
	UGint RemoveAt(UGint nIndex, UGint nCount = 1);
	//! \brief 向指定索引处插入选中对象
	void InsertAt(UGint nIndex, UGuint unID, UGGeometry* pGeometry = NULL);//added pGeometry 参数
	//! \brief 修改指定位置的对象
	void SetAt(UGint nIndex, UGuint unID, UGGeometry* pGeometry = NULL);
	//! \brief 得到指定索引处的对象ID
	UGuint GetAt(UGint nIndex, UGGeometry** ppGeometry = NULL)const;//添加输出参数，最好用*&，但是不可指空，为了保持以前的兼容性，缩影时用指针
	//! \brief 删除所有选中对象
	void RemoveAll();
	//! \brief 获取选择集ID数据起始地址
	UGuint* GetData();
	//! \brief 添加选中对象ID的数组
	UGint Append(UGArray<UGuint>& arrIDs,UGArray<UGGeometry*>* arrGeos = NULL);
	//! \brief copy选择集中的ID数组到arrIDs
	void Copy(UGArray<UGuint>& arrIDs,UGArray<UGGeometry*>* arrGeos = NULL);
	//! \brief 设置选中集大小
	void SetSize(UGint nSize);
	//! \brief 获取选中集大小
	UGint GetSize()const;
	//! \brief 选择集是否有对象
	UGbool IsEmpty()const;
	//! \brief 高亮显示选择集
	UGbool Highlight(UGGraphics* pGraphics, UGDrawing *pDrawing);
	//! \brief 是否设置自定义风格
	UGbool HasCustomStyle()const;
	//! \brief 设置使用自定义风格
	void SetCustomStyle(UGbool bCustomStyle = false); 
	//! \brief 设置选择集水平
	void SetControlSelectLevel(UGint nControlSelectLevel);
	//! \brief 获取选择集水平
	UGint GetControlSelectLevel()const;
	//! \brief 设置显示风格
	void SetStyle(const UGStyle& style);
	//! \brief 获取显示风格
	const UGStyle& GetStyle()const;
	//! \brief 设置关联数据集
	void SetDatasetVector(UGDatasetVector* pDatasetVector);
	//! \brief 获取关联数据集
	UGDatasetVector* GetDatasetVector()const;
	//! \brief 设置所属图层指针。
	//! \param pLayer 图层指针[in]。
 	void SetLayer(UGLayer *pLayer);	
 	//! \brief 获取所属图层指针。
 	//! \return 图层指针。
 	UGLayer* Getlayer();
#if !defined OS_ANDROID && !defined IOS
	// Added by fansc 2011-10-8 处理海图选择信息
	//! \brief 获取海图信息指针数组
	UGArray<UGChartObjectInfo*> GetSelectedObjectInfo();
	//! \brief 添加海图信息指针
	void AddSelectedObjectInfo(UGChartObjectInfo *pChartObjectInfo);
	//! \brief 清除选择信息
	void ClearSelectedObjectInfo();
#endif

	void SetStyleOptions(UGint styleOptions);
	UGint GetStyleOptions();

	UGbool IsFillForeColorEnable();
	UGbool IsFillBackColorEnable();
	UGbool IsFillBackOpaqueEnable();
	UGbool IsFillGradientAngleEnable();
	UGbool IsFillGradientOffsetRatioXEnable();
	UGbool IsFillGradientOffsetRatioYEnable();
	UGbool IsFillGradientModeEnable();
	UGbool IsFillOpaqueRateEnable();
	UGbool IsFillSymbolIDEnable();
	UGbool IsLineColorEnable();
	UGbool IsLineSymbolIDEnable();
	UGbool IsLineWidthEnable();

	UGbool IsMarkerAngleEnable();
	UGbool IsMarkerSizeEnable();
	UGbool IsMarkerSymbolIDEnable();

	UGbool IsSymbolMarkerEnable();
	UGbool IsSymbolLineEnable();
	UGbool IsSymbolFillEnable();

protected:
	//! \brief 关联矢量数据集
	UGDatasetVector* m_pDatasetVector;
	//! \brief 用于将取得的记录集保留
	UGRecordset *m_pReserveRs;   

	//! \brief 默认为False, 即用户没有设置选择集风格,
	UGbool m_bCustomStyle;	
	//! \brief 是否自动释放数据集，如果此数据集是外面传入的则不需要自动
	UGbool m_bAutoReleaseRs;         
	UGint m_nControlSelectLevel;

	UGStyle m_Style;
	//! \brief 选中对象的ID
	UGArray<UGuint> m_arrIDs;
	//! brief 用来记录制图表达时，专题图选中的Geometry，在选择时返回的是Geometry
	UGArray<UGGeometry*> m_arrGeo;
	//! brief 用来记录专题图的Geometry，在选择时返回的是Geometry
//	UGArray<UGGeometry*>m_arrGeo;
	//! \brief 所属的图层
	UGLayer* m_pLayer;
#if !defined OS_ANDROID && !defined IOS
	UGArray<UGChartObjectInfo*> m_arrSelectedObjectInfo;
#endif

	UGint m_nStyleOptions;            // 风格选项，用于自定义风格是否起作用
};

}

#endif // !defined(AFX_UGSELECTION_H__2FBE2AA1_B3D6_469E_854F_CC6E86B762D0__INCLUDED_)

