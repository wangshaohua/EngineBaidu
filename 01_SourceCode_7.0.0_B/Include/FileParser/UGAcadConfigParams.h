// UGFileParserConfigParams.h: interface for the UGFileParserConfigParams class.
//////////////////////////////////////////////////////////////////////////
//                    _   _   ____   ____                    
//   Project         | | | | / ___) / ___)                   
//                   | | | || | __ | |                       
//                   | |_| || |_\ || \___                    
//                    \____/ \____| \ ___)     6.0           
//                                                           
//!  \file headerfile.h
//!  \brief Class 的接口定义。
//!  \details 文件详细信息。
//!  \author 唐争强。
//!  \attention 
//!   Copyright (c) 1996-2008 SuperMap Software Limited Company.  <br> 
//!   All Rights Reserved.
//!  \version 6.0
//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////

#ifndef __UGACADIMPORTPARAMS_H__
#define __UGACADIMPORTPARAMS_H__

#include "FileParser/UGVectorConfigParams.h"
#include "FileParser/UGExchangeFileType.h"

namespace UGC 
{
//! \brief Dxf的导入参数配置。
//! \remarks 备注信息。
class FILEPARSER_API UGAcadImportParams : public UGVectorImportParams
{
public:
	//! \brief 构造函数。
	//! \remarks 。
	UGAcadImportParams();

	//! \brief 析构函数。
	//! \remarks 。
	virtual ~UGAcadImportParams();

public:

	//! \brief 以CAD模式导入时，设置是否以原始CAD分层结构导入
	//! \param  [in]。
	//! \return 。
	//! \remarks 。
	//! \attention 。
	void SetImportByLayer(UGbool bByLayer = FALSE);

	//! \brief 判断CAD导入以全图或者多层导入。
	//! \param  [in]。
	//! \return 。
	//! \remarks 。
	//! \attention 。
	UGbool GetImportByLayer() const;

	//! \brief 设置是否忽略扩展数据。
	//! \param  [in]。
	//! \return 。
	//! \remarks 。
	//! \attention 。
	void SetIgnoreExtendData(UGbool bIgnore = TRUE);

	//! \brief 获取是否忽略扩展数据。
	//! \param  [in]。
	//! \return 。
	//! \remarks 。
	//! \attention 。
	UGbool GetIgnoreExtendData() const;

	//! \brief 设置是否忽略块儿属性；
	//! \param [in]
	//! \return
	//! \remarks 默认忽略
	//! \attention
	void SetIgnoreBlockAttribute(UGbool bIgnore = TRUE);
    
	//! \brief 获取是否忽略块儿属性；
	//! \param[in]
	//! \return true/false
	//! \attention
	UGbool GetIgnoreBlockAttribute() const;


	//! \brief 设置是否忽略Polyline、LWPline的宽度、凸度信息
	//! \param bResolve [in]。
	//! \return 。
	//! \remarks 设置为TRUE时，多段线的“凸度”、“宽度”信息丢失，仅保留“中心线”。
	//! \attention 。
	void SetIgnoreLwplineWidth(UGbool bIgnore = FALSE);

	//! \brief 得到是否忽略Polyline、LWPline的宽度、凸度信息
	//! \param bResolve [in]。
	//! \return 。
	//! \remarks 
	//! \attention 。
	UGbool GetIgnoreLwplineWidth() const;

	//! \brief 设置是否将blocks对象当做点对象处理。
	//! \param bResolve [in]。
	//! \return 。
	//! \remarks 设置为TRUE时，“块”对象几何信息忽略，仅以“插入点”形式生成点对象。
	//! \attention 。
	void SetBlockAsInsertPoint(UGbool bAsPoint = FALSE);

	//! \brief 设置是否将blocks对象当做点对象处理。
	//! \param  [in]。
	//! \return 。
	//! \remarks 。
	//! \attention 。
	UGbool GetBlockAsInsertPoint() const;

	//! \brief 设置是否忽略文件中的隐藏图层。
	//! \param  [in]。
	//! \return 。
	//! \remarks 。
	//! \attention 。
	void SetIgnoreHiddenLayers(UGbool bIgnore = TRUE);

	//! \brief 得到是否忽略文件中的隐藏图层。
	//! \param  [in]。
	//! \return 。
	//! \remarks 。
	//! \attention 。
	UGbool GetIgnoreHiddenLayers() const;	
	
	//! \brief 设置是否忽略实体颜色。
	//! \param bIgnoreColor [in]。
	//! \return 。
	//! \remarks 导入CAD数据集时，设置忽略对象颜色，则导入对象无颜色风格。
	//! \attention 。
	void SetIgnoreEntityColor(UGbool bIgnoreColor = FALSE);
	
	//! \brief 获取忽略实体颜色。
	//! \param  [in]。
	//! \return 。
	//! \remarks 。
	//! \attention 。
	UGbool GetIgnoreEntityColor() const;

	//! \brief 以CAD模式导入时，设置是否忽略线对象的线型风格。
	//! \param  [in]。
	//! \return 。
	//! \remarks 。
	//! \attention 。
	void SetIgnoreLineStyle(UGbool bIgnore = FALSE);

	//! \brief 获取是否忽略线对象的线型风格。
	//! \param  [in]。
	//! \return 。
	//! \remarks 。
	//! \attention 。
	UGbool GetIgnoreLineStyle() const;

	//! \brief 以CAD模式导入时，设置是否忽略hatch对象的填充风格。
	//! \param  [in]。
	//! \return 。
	//! \remarks 。
	//! \attention 。
	void SetIgnoreFillStyle(UGbool bIgnore = FALSE);

	//! \brief 获取是否忽略hatch对象的填充风格。
	//! \param  [in]。
	//! \return 。
	//! \remarks 。
	//! \attention 。
	UGbool GetIgnoreFillStyle() const;	


	//! \brief 以CAD模式导入时，设置是否忽略点符号的型（shape）参考文件。
	//! \param  [in]。
	//! \return 。
	//! \remarks 。
	//! \attention AutoCAD shpae文件不同于ESRI的shape文件，AutoCAD的shape存储的是符号和字体定义。
	void SetIgnoreShapeStyle(UGbool bIgnore = TRUE);


	//! \brief 获取是否忽略点符号的型（shape）参考文件。
	//! \param  [in]。
	//! \return 。
	//! \remarks 。
	//! \attention AutoCAD shpae文件不同于ESRI的shape文件，AutoCAD的shape存储的是符号和字体定义。	
	UGbool GetIgnoreShapeStyle() const;

	
	//! \brief 仅导入块数据，其他数据不导入。
	//! \param FALSE [in]。
	//! \return 。
	//! \remarks 。
	//! \attention 。
	void SetOnlyImportBlock(UGbool bOnlyBlock = FALSE);	

	
	//! \brief 仅导入块数据，其他数据不导入。
	//! \param FALSE [in]。
	//! \return 。
	//! \remarks 。
	//! \attention 。
	UGbool GetOnlyImportBlock() const;

	//! \brief 设置忽略线宽。
	//! \param FALSE [in]。
	//! \return 。
	//! \remarks 。
	//! \attention 。
	void SetIgnoreLineWidth(UGbool bLineWidth = FALSE);	

	//! \brief 设置忽略线宽。
	//! \param FALSE [in]。
	//! \return 。
	//! \remarks 。
	//! \attention 。
	UGbool GetIgnoreLineWidth() const;	

	//! \brief 设置圆弧拟合成折线的段数,默认值为73。 。
	//! \param 73 [in]。
	//! \return 。
	//! \remarks 。
	//! \attention 。
	void SetConstSegs(UGuint nConstSegs = 73);

	//! \brief  获取圆弧拟合成折线的段数,默认值为73。。
	//! \param  [in]。
	//! \return 。
	//! \remarks 。
	//! \attention 。
	UGuint GetConstSegs() const;
	
	//! \brief 设置风格对照表文件路径。
	//! \param  [in]。
	//! \return 。
	//! \remarks 。
	//! \attention 。
	void SetStyleMapFilePath(const UGString& strPath);

	//! \brief 获取风格对照表文件路径
	//! \param  [in]。
	//! \return 。
	//! \remarks 。
	//! \attention 。
	UGString GetStyleMapFilePath() const;

	//! \brief 三维实体是否导入三维对象。
	//! \param FALSE [in]。
	//! \return 。
	//! \remarks 。
	//! \attention 。
	void SetImportAs3D(UGbool bImportAs3D = FALSE);	

	//! \brief 获取三维实体是否导入三维对象。
	//! \param [in]。
	//! \return 。
	//! \remarks 。
	//! \attention 。
	UGbool GetImportAs3D();	
	//===================================================
	//! \brief  获取是否导入为带有参数化部分的复合面或者线对象。
	//! \param 
	//! \return 
	//! \remarks 
	//! \attention 
	UGbool GetImportAsParametric();

	//===================================================
	//! \brief  设置是否导入为带有参数化部分的复合面或者线对象。
	//! \param 
	//! \return   
	//! \remarks 
	//! \attention 
	void SetImportAsParametric(UGbool bImportAsCompound = FALSE);

	//===================================================
	//! \brief  获取是否导入扩展记录（XRecord）
	//! \param 
	//! \return   
	//! \remarks 
	//! \attention
	UGbool GetImportXRecord() const;

	//===================================================
	//! \brief  设置是否导入扩展记录（XRecord）
	//! \param 
	//! \return   
	//! \remarks 
	//! \attention
	void SetImportXRecord(UGbool bImportXRecord = FALSE);
protected:

	//! \brief 标识CAD数据以全图导入换是多层导入。
	//! \remarks m_bMLayerImport = FALSE,全图导入
	UGbool m_bMLayerImport;
	
	//! \brief 是否导入(DWG/DXF)扩展数据标志。
	UGbool m_bIgnoreXData;

	//! \brief 标识仅导入块类型数据
	//! \remarks 。
	UGbool m_bOnlyImportBlock;

	//! \brief 忽略实体颜色。
	//! \remarks 。
	UGbool m_bIgnoreColor;

	//! \brief 忽略线宽。
	//! \remarks 。
	UGbool m_bIgnoreLineWidth;

	//! \brief 忽略线线型。
	//! \remarks 。
	UGbool m_bIgnoreLineStyle;

	//! \brief 忽略形符号。
	//! \remarks 。
	UGbool m_bIgnoreShapeSymbol;

	//! \brief 忽略图元填充。
	//! \remarks 。
	UGbool m_bIgnoreHatchFill;

	//! \brief 忽略优化多段线的线宽。
	//! \remarks 。
	UGbool m_bIgnoreLwplineWidth;

	//! \brief 不可见实体导入标志。
	//! \remarks 。
	UGbool m_bIgnoreHiddenLayers;

	//! \brief 块实体作为点导入标志。
	//! \remarks 。
	UGbool m_bBlockAsPointImport;

	//! \brief 圆弧拟合成折线的段数,默认值为73。
	//! \remarks 。
	UGint m_nConstSegs;

	//! \brief 风格对照表文件路径。
	//! \remarks 。
	UGString m_strStyleMapPath;

	//! \brief 三维实体是否导入三维对象。
	//! \remarks 。
	UGbool m_bImportAs3D;

	//! \brief 是否忽略块儿属性定义
	//! \remarks  默认为true
    UGbool m_bIgnoreBlockAttribute;

	//! \brief 是否处理成带参数化部分的复杂线或面对象
	UGbool m_bImportAsParametric;

	//! \brief 是否导入扩展记录，默认为false
	UGbool m_bImportXRecord;
};

//! \brief Dxf的导出参数配置。
//! \remarks 备注信息。
class FILEPARSER_API UGAcadExportParams : public UGVectorExportParams
{
public:
	//! \brief 构造函数。
	//! \remarks 。
	UGAcadExportParams();

	//! \brief 析构函数。
	//! \remarks 。
	~UGAcadExportParams();
public:
	enum EmVersion
	{
//		ACAD09	= 9,//->OdDb::vAC09	R9
//		ACAD10	= 10,//->OdDb::vAC10	R10
		ACAD12	= 12,//->OdDb::vAC12	R11-12
		ACAD13	= 13,//->OdDb::vAC13	R13
		ACAD14	= 14,//->OdDb::vAC14	R14
		ACAD2000= 2000,//->OdDb::vAC15	2000-2002
		ACAD2004= 2004,//->OdDb::vAC18	2004-2006
		ACAD2007= 2007,//->OdDb::vAC21	2007
	};

public:


	//! \brief 获取要导出的矢量数据集名称数组。
	//! \param  [in]。
	//! \return 。
	//! \remarks 数据集名称数组。
	//! \attention 为了多个数据集导出使用。
	virtual UGbool GetDtNamesBeExported(UGStrings& arrNames) const ;

	//! \brief 设置要导出的矢量数据集名称数组。
	//! \param  name [in] 设置的名称。
	//! \return 。
	//! \remarks 。
	//! \attention 为了多个数据集导出使用。
	virtual void SetDtNamesBeExported(const UGStrings& arrNames);
	
	//! \brief 获取要导出的矢量数据版本号。
	//! \param  [in]。
	//! \return 。
	//! \remarks 。
	//! \attention 。
	UGint GetVersion() const;	

	//! \brief 设置要导出的矢量数据版本号。
	//! \param  nVer [in] 设置的版本号。
	//! \return 。
	//! \remarks 。
	//! \attention 。
	void SetVersion(UGint nVer = ACAD2004);

	//! \brief 设置导出的扩展数据的字段信息。
	//! \param fieldInfos [in]。
	//! \return 。
	//! \remarks 。
	//! \attention 。
	void SetExtendDataFieldInfos(const UGFieldInfos& fieldInfos);
	
	//! \brief 获取导出的扩展数据的字段信息.
	//! \param  [in]。
	//! \return 。
	//! \remarks 。
	//! \attention 。
	UGFieldInfos GetExtendDataFieldInfos() const;

	//! \brief 设置是否导出扩展数据，默认不导出。
	//! \param  [in]。
	//! \return 。
	//! \remarks 。
	//! \attention 。
	void SetExportExtendData(UGbool bIgnore = FALSE);

	//! \brief 获取是否导出扩展数据。
	//! \param  [in]。
	//! \return 。
	//! \remarks 。
	//! \attention 。
	UGbool GetExportExtendData() const;

	//! \brief 设置是否导出扩展记录，默认不导出。
	//! \param  [in]。
	//! \return 。
	//! \remarks 。
	//! \attention 如果设置为TRUE，非CAD字段将以扩展记录的形式导出。
	void SetExportXRecord(UGbool bExportXRecord = FALSE);

	//! \brief 获取是否导出扩展记录。
	//! \param  [in]。
	//! \return 。
	//! \remarks 。
	//! \attention 。
	UGbool GetExportXRecord() const;

	//! \brief 设置风格对照表文件路径。
	//! \param  [in]。
	//! \return 。
	//! \remarks 。
	//! \attention 。
	void SetStyleMapFilePath(const UGString& strPath);

	//! \brief 获取风格对照表文件路径
	//! \param  [in]。
	//! \return 。
	//! \remarks 。
	//! \attention 。
	UGString GetStyleMapFilePath() const;



	//! \brief 设置是否导出面对象等的边界线
	//! \param [in]
	//! \return
	//1 \remarks
	//! \attention
	void SetExportBorder(const UGbool bExpBorder);

	//! \brief 获取是否导出面对象等的边界线
	//! \param
	//! \return 如果导出边界线返回true 否则返回false
	//! \attention
	UGbool GetExportBorder()const;
protected:
	//! \brief 矢量数据要导出的文件版本号。
	//! \remarks 。	
	UGint m_nFileVersion;

	//! \brief 导出扩展数据的字段。
	//! \remarks 。
	UGFieldInfos m_xDataFieldInfos;
	//! \brief 风格对照表文件路径。
	//! \remarks 。
	UGString m_strStyleMapPath;

	//要导出的数据集名称数组
	UGStrings m_arrNames;

	//! \brief 是否导出(DWG/DXF)扩展数据标志。
	UGbool m_bExportXData;

	//! \brief 是否导出(DWG/DXF)扩展数据记录,默认不导出。
	UGbool m_bExportXRecord;

	//! \brief 是否导出边界线
	UGbool m_bExportBorder;
};
} //namespace UGC
#endif // !defined(AFX_UG_PNG_FILEPARSERCONFIGPARAMS_H__INCLUDED_)

