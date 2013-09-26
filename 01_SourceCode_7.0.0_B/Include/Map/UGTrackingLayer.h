// UGTrackingLayer.h: interface for the UGTrackingLayer class.
//
//////////////////////////////////////////////////////////////////////

/*!
   **************************************************************************************
    \file     UGTrackingLayer.h
   **************************************************************************************
    \author   陈国雄
    \brief    跟踪图层类，是一个内存图层，总是在其他图层的最上面，用于临时对象的显示。                                                           
    \attention   
   ----------------------------------------------------------------------------------<br>
    Copyright (c) 2000-2010 SuperMap Software Co., Ltd.                           <br>
    All Rights Reserved.                                                             <br>
   ----------------------------------------------------------------------------------<br> 
   
   **************************************************************************************
    \version 2005-05-20  陈国雄    初始化版本.                                       <br>
   **************************************************************************************
*/

#if !defined(AFX_UGTRACKINGLAYER_H__DC6194D6_CDEC_4A74_8522_AC23C8C202F5__INCLUDED_)
#define AFX_UGTRACKINGLAYER_H__DC6194D6_CDEC_4A74_8522_AC23C8C202F5__INCLUDED_

#include "Map/UGGeoEvent.h"
#include "Stream/ugdefs.h"
#include "Drawing/UGDrawing.h"

namespace UGC {

//! \brief BeforeTrackingLayerDraw 事件回调函数
typedef void (UGSTDCALL *BeforeTrackingLayerDrawProc)(UGlong pWnd,UGbool& bCancel,UGGraphics* pGraphics);
//! \brief AfterTrackingLayerDraw 事件回调函数
typedef void (UGSTDCALL *AfterTrackingLayerDrawProc)(UGlong pWnd,UGGraphics* pGraphics);

class MAP_API UGTrackingLayer  
{
public:
	UGTrackingLayer();

#ifdef SYMBIAN60
	~UGTrackingLayer();
#else
	virtual ~UGTrackingLayer();
#endif

public:
	//! \brief  点击事件
	UGint HitTest(const UGPoint2D& pntHitTest, UGdouble dTolerance);

	//! \brief  是否可见
	UGbool IsVisible()const;
	//! \brief  设置是否可见
	void SetVisible(UGbool bVisible = true);

	//! \brief  是否可选择
	UGbool IsSelectable()const;
	//! \brief  设置是否可选择
	void SetSelectable(UGbool bSelectable = false);

	//! \brief  是否可编辑
	UGbool IsEditable()const;
	//! \brief  设置是否可编辑
	void SetEditable(UGbool bEditable = false);

	//! \brief  是否可捕捉
	UGbool IsSnapable()const;
	//! \brief  设置是否可捕捉
	void SetSnapable(UGbool bSnapable = false);

	//! \brief 是否符号随着图层的缩放而缩放
	UGbool IsSymbolScalable()const;
	//! \brief 设置符号是否可缩放
	void SetSymbolScalable(UGbool bSymbolScalable = false);

	//! \brief 是否设置文本叠盖
	UGbool IsAllowTextOverlap()const;
	//! \brief 设置文本叠盖
	void SetAllowTextOverlap(UGbool bAllowTextOverlap = true);

	//! \brief 查找对应标签的跟踪层对象
	/**
	\return  对应标签的索引
	*/
	UGint Find(const UGString &strTag, UGint nFromIndex = 0) const;
	//! \brief 查找对应几何对象的跟踪层对象
	/**
	\return  对应几何对象的索引
	*/
	UGint Find(const UGGeometry* pGeometry, UGint nFromIndex = 0);

	//! \brief 移除指定标签的对象
	UGbool Remove(const UGString &strTag, UGint nFromIndex = 0);
	//! \brief 移除指定索引的对象
	UGint RemoveAt(UGint nIndex, UGint nCount = 1);
	//! \brief 增加几何对象到跟踪层
	UGGeoEvent* Add(const UGGeometry* pGeometry, const UGString &strTag);
	//! \brief 得到指定索引的跟踪层对象
	UGGeoEvent* GetAt(UGint nIndex) const;

	//! \brief 移除跟踪层所有对象
	void RemoveAll();

	//! \brief 移除跟踪层所有对象
	void RemoveAllEx();

	//! \brief 获取对象个数
	UGint GetCount()const;

	//! \brief 设置指定索引对象的标签
	void SetTagAt(UGint nIndex, const UGString &strTag);

	//add by xiaoys 2012-07-10 该接口主要是用来在jni层封装获取字段信息接口
	UGDataset* GetDataset();

	//! \brief 绘制跟踪层
#ifdef SYMBIAN60
	UGbool OnDraw(UGGraphics* pGraphics, UGDrawing *pDrawing);
#else
	virtual UGbool OnDraw(UGGraphics* pGraphics, UGDrawing *pDrawing);
#endif

	//! \brief 设置指定的字符编码
	void SetCharset(UGString::Charset nCharset);
	//! \brief 得到指定的字符编码
	UGString::Charset GetCharset()const;

	//! \brief 得到最大符号大小
	UGdouble GetMaxMarkerSize() const;
	//! \brief 得到有效区域
	UGRect2D GetInvalidRect() const;
	//! \brief 设置有效区域
	void SetInvalidRect(const UGRect2D& rcInvalid);

	UGdouble GetSymScaleDefinition() const;
	void SetSymScaleDefinition(UGdouble dSymScaleDefinition);

	UGdouble CalculateSymbolScale(UGdouble dScale) const;
	void SetDrawing(UGDrawing* pDrawing);
	
	//! \brief 获取填充原点的模式
	UGint GetFillOrgMode() const;					
	//! \brief 设置填充原点模式
	void SetFillOrgMode(UGGraphics::BrushOrgMode nFillOrgMode);		
	UGbool BuildSpatialIndex(UGSpatialIndexInfo  &spatial);

	//! \brief 开始事务
	UGbool BeginTrans() ;
	
	//! \brief 提交事务
	void Commit() ;
	
	//! \brief 撤消事务
	void Rollback();
	
	//! \brief 判断事务是否开始 
	UGbool IsTransStarted() ;

	//! \brief 设置批量更新标志
	//! \param bIsEditBulkOperate [in] TRUE为开始批量更新，FALSE为取消批量更新标志
	UGbool EditBulk(UGbool bIsEditBulkOperate);

	//! \brief 批量更新时,强制刷新,将本次批量编辑的数据保存
	//! \return 是否刷新成功
	UGbool FlushBulkEdit();

	//! \brief 取消本次批量更新的内容，从上次提交点至此 编辑的内容无效，但可以继续开始进行批量编辑
	UGbool CancleBulkOperated();
	
	//added by xielin 2007-10-17 用于优化跟踪层的显示速度
	//! \brief 显示的时候是否按照对象类型排序显示，默认按照对象类型排序显示。这样对大部分的跟踪应用（一个跟踪点一个标注，注意不要弄成复合对象），能提高绘制速度
	void SetOrderByGeometryType(UGbool bOrderByGeometryType=true);
	//! \brief 返回是否按照对象类型排序显示
	UGbool IsOrderByGeometryType();

	//! \brief  是否为线光滑模式
	UGbool IsLineSmoothingMode()const;
	//! \brief  设置线光滑模式
	void SetLineSmoothingMode(UGbool bSmoothingMode = true);			
	//! \brief  是否为文本光滑模式
	UGbool IsTextSmoothingMode()const;									
	//! \brief  设置文本光滑模式
	void SetTextSmoothingMode(UGbool bSmoothingMode = true);		
	//! \brief 是否为设备图层
	UGbool IsDeviceLayer();

	//! \brief 保存图层数据
	/**
	\param strFileName				保存路径[in]
	\param bOverWrite				是否强制覆盖[in]
	\return 保存是否成功
	*/
	//UGbool SaveAs(const UGString& strFileName ,UGbool bOverWrite = false)const;
	//! \brief 打开图层数据
	/**
	\param strFileName				打开路径[in]
	\return 打开是否成功
	*/
	UGbool Open(const UGString& strFileName,UGbool bAsMemoryMode = false);
	//! \brief 清空图层
	void Clear();

	//! \brief   读取图层的XML信息
	UGbool FromXML(const UGString& strXML,const UGString& strWorkspacePath,const UGString& strMapName,UGint nVersion = 0);
	//! \brief   保存图层为XML
	UGString ToXML(const UGString& strWorkspacePath,const UGString& strMapName,UGint nVersion = 0)const;

	//! \brief 设置跟踪层图层的透明度
	/*
	\param nTransPercent	透明度[in]
	*/	
	void SetTransPercent(UGuint nTransPercent);
	//! \brief 获取图层的透明度
	UGuint GetTransPercent();

	void SetBeforeTrackingLayerDrawFunc(BeforeTrackingLayerDrawProc pBeforeTrackingLayerDrawFunc,UGlong pWnd);
	void SetAfterTrackingLayerDrawFunc(AfterTrackingLayerDrawProc pAfterTrackingLayerDrawFunc,UGlong pWnd);

	void SendBeforeTrackingLayerDrawFunc(UGbool& bCancel,UGGraphics* pGraphics);
	void SendAfterTrackingLayerDrawFunc(UGGraphics* pGraphics);

private:
	//modified by lugw 2007-05-11 此函数改为私有，外部暂不使用
	void SetGeometryAt(UGint nIndex, const UGGeometry* pGeometry);
	//! \brief 创建内存数据源,如果成员数据源不为空，返回true，为空返回false
	UGbool CreateMemoryDs();
	//! \brief 获取设备图层存储路径
	UGString GetFileName(const UGString& strWorkspacePath,const UGString& strMapName)const;

	UGRecordset* GetRecordset();

//{{ add by xiaoys 2012-07-03 为子类TrackingLayerEx开放一些虚函数
public:
	UGbool IsTrackingLayerEx();

	//! \brief 通过跟踪层对象标签获取对象 
	virtual UGGeoEvent* GetEvent(const UGString& strTag);

	//! \brief 通过跟踪层对象字段和值获取记录序号
	virtual UGint Query(UGArray<UGint>& arIDs, const UGString& strFieldName, const UGString& strVar);

	//! \brief 设置符号可见
	virtual void SetSymbolVisible(UGbool bVisible);

	//! \brief 设置符号闪烁
	virtual void SetSymbolTwinkling(UGchar cTwinkling);

	//! \brief 设置符号对齐方式
	virtual void SetSymbolAlign(UGchar cAlign);

	//! \brief 设置符号偏移
	virtual void SetSymbolOffset(UGshort sX, UGshort sY);


	//! \brief  向跟踪层添加对象的属性标签；----------------
	virtual UGbool AddLabel(const UGString& strField, const UGTextStyle& LabelStyle,UGbool bVisible = true, UGbool bAddToTail = true);
	//! \brief  在跟踪层移除专题图；------------------------
	virtual UGbool RemoveLabel(const UGString& strField);

	//! \brief 设置标签偏移
	virtual UGbool SetLabelOffset(const UGString& strTag, UGshort usX, UGshort usY); 

	//! \brief 设置标签说明
	virtual UGbool SetLabelCaption(const UGString& strTag, const UGString& strCaption);

	//! \brief 设置标签的文字样式
	virtual UGbool SetLabelTextStyle(const UGString& strTag, const UGTextStyle& TextStyle);

	//! \brief  设置标签是否显示
	virtual UGbool SetLabelVisible(const UGString& strTag,UGbool bVisible);

	//! \brief  将指定标签上移一层；
	virtual UGbool LabelMoveUp(const UGString &strTag);
	//! \brief  将指定标签下移一层；
	virtual UGbool LabelMoveDown(const UGString &strTag);
	//! \brief  将指定标签置为最顶层；
	virtual UGbool LabelMoveTop(const UGString &strTag);
	//! \brief  将指定标签置为最底层；
	virtual UGbool LabelMoveBottom(const UGString &strTag);
	//! \brief  清除所有标签；
	virtual void ClearLabel();

	//! \brief  新建字段
	virtual UGbool CreateUserField(const UGString& strName,UGFieldInfo::FieldType nType,UGint nSize,UGint nAttributes = 0);
	virtual UGbool CreateUserFields(const UGFieldInfos& fieldInfos);

	//{{ add by xiaoys 2012-07-06
	virtual UGbool GetFieldInfos(UGFieldInfos& infos);
	
	virtual UGbool GetFieldInfo(UGFieldInfo& info, const UGString& strFieldName);

	virtual UGbool DeleteUserField(const UGString& strFieldName);
	//}} add by xiaoys 2012-07-06

	//! \brief  设置当前字段值
	virtual UGbool SetFieldValue(const UGString& strFieldName,const UGVariant& var);

	//! \brief  修改第iIndex个对象指定字段的值。
	virtual UGbool SetFieldValue(const UGString& strFieldName,const UGVariant& var,const UGint& iIndex); 

	//! \brief 获取对象第iIndex个属性字段名称
	virtual UGString GetFieldName(UGint iIndex);

	//! \brief  增加一个带属性的标注对象
	virtual UGint AddFeature(UGGeometry *pGeometry, const UGArray<UGString> &aryFields, const UGArray<UGVariant *> &aryValues,const UGString& strTag);

	//! \brief  清除跟踪层所有对象，但保留表结构；------------------------
	void DeleteAllFeatures();
//}} add by xiaoys 2012-07-03 为子类TrackingLayerEx开放一些虚函数

	//add by xiaoys 2012-07-16
	virtual UGbool GetFieldValue(UGVariant& var, UGint iIndex, const UGString& strField);


protected:
	UGDrawing* m_pDrawing;
	UGRect2D m_rcInvalid;
	//! \brief 最大的符号的大小。这是逼不得已的，必须随时维护
	UGdouble m_dMaxMarkerSize;
	UGuint m_unOptions;
	UGList<UGGeoEvent*> m_Events;

	UGDataSource* m_pDs;
	UGDatasetVector* m_pDv;
	UGRecordset* m_pRecordset; 

	UGString::Charset m_nCharset;
	//! \brief 符号缩放比例尺
	UGdouble m_dSymScaleDefinition;	
	UGGraphics::BrushOrgMode m_nFillOrgMode;
	UGbool m_bOrderByGeometryType;
	UGbool m_bLineSmoothingMode;
	UGbool m_bTextSmoothingMode;

	UGbool m_bDeviceTrackingLayer;
	UGbool m_bTrackingLayerEx;

	UGMutex m_mutex;

	UGuint m_nTransPercent;

	UGGraphics* m_pTransPercentGraphics;
	UGImage* m_pTransPercentImage;
	UGBrush* m_pTransPercentBrush;
	UGPen* m_pTransPercentPen;

	BeforeTrackingLayerDrawProc m_pBeforeTrackingLayerDrawFunc;
	AfterTrackingLayerDrawProc m_pAfterTrackingLayerDrawFunc;
	UGlong m_pEventView;  //调用事件回调函数的对象指针
};

}

#endif // !defined(AFX_UGTRACKINGLAYER_H__DC6194D6_CDEC_4A74_8522_AC23C8C202F5__INCLUDED_)

