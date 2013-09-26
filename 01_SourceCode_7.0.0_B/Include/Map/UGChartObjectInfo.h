#if !defined UGCHARTOBJECTINFO_H
#define UGCHARTOBJECTINFO_H

#include "Stream/ugdefs.h"
#include "Stream/ugexports.h"
#include "Engine/UGRecordset.h"
#include "ChartBase/UGS57Dictionary.h"
#include "Engine/UGDatasetGroup.h"
#include "ChartToolkit/UGS57DatasetGroupExt.h"
#include "ChartBase/UGS57ExtInfo.h"

namespace UGC{

	class UGChartSetting;

typedef void (UGSTDCALL *AfterChartLayerEditAttributeProc)(UGlong pWnd, UGbool& bEditAttribute);


	struct UGS57EdgeStyle{
		UGuint m_nFeatureId;
		UGuint m_nEdgeId;
		UGStyle m_style;
		UGbool m_bValid;
		UGS57EdgeStyle()
		{
			m_nFeatureId = 0;
			m_nEdgeId = 0;
			m_bValid = false;
		}
	};

	typedef void (UGSTDCALL *AfterModifiedEdgeStyleProc)(UGlong pWnd, UGArray<UGS57EdgeStyle>& s57EdgeStyles);


	class MAP_API UGChartObjectInfo
	{
	public:
		UGChartObjectInfo();
		~UGChartObjectInfo();

		const UGChartObjectInfo& operator =(const UGChartObjectInfo& chartAttiInfo);

		void SetRecordset(UGRecordset* pRecordset, UGDatasetGroup *pDatasetGroup);
		UGRecordset* GetRecordset();

		UGDatasetGroup* GetDatasetGroup();

		// 设置、获取对象的17个字符长名，对象全球唯一标识。
		void SetLNAM(const UGString& strLNAM);
		UGString GetLNAM()const;

		// 设置、获取对象的RCID，对象在一幅海图内的唯一标识
		void SetFeatureID(UGuint nFeatureID);
		UGuint GetFeatureID()const;

		// 设置、获取对象对应的记录集ID
		void SetRecordsetID(UGint nRecordsetID);
		UGint GetRecordsetID()const;

		// 设置、获取物标六个字符简称
		void SetAcronym(const UGString& strAcronym);
		UGString GetAcronym()const;

		// 设置、获取物标名称
		void SetName(const UGString& strName);
		UGString GetName()const;

		// 设置、获取物标本地化名称
		void SetLocalName(const UGString& strLocalName);
		UGString GetLocalName()const;

		// 设置、获取物标的编码，OBJL字段值
		void SetFeatureCode(UGint nFeatureCode);
		UGint GetFeatureCode()const;

		// 设置、获取机构简称
		void SetAgencyToken(const UGString& strToken);
		UGString GetAgencyToken()const;

		// 设置、获取几何对象类型
		void SetGeometryType(const UGGeometry::Type eType);
		UGGeometry::Type GetGeometryType()const;

		// 设置、获取水深值, 无效值为Double极小值 2.2250738585072014e-308
		UGbool SetDepth(UGdouble dDepth);
		UGdouble GetDepth()const;

		// 设置、获取物标的类型
		void SetS57FeatureTypeName(const UGString& strTypeName);
		UGString GetS57FeatureTypeName()const;

		// 设置、获取物标的Master的17个字符长名
		void SetMasterLNAM(const UGString& strLNAM);
		UGString GetMasterLNAM()const;

		// 设置、获取物标的集合物标的17个字符长名
		void SetCollectionLNAM(const UGString& strLNAM);
		UGString GetCollectionLNAM()const;

		// 设置、获取S57标准中定义的属性值，包含部分属性基本信息。
		void SetS57Attribute(UGArray<UGS57AttiInfo>& s57Attributes);
		UGArray<UGS57AttiInfo> GetS57Attribute();

		// 提交属性值
		UGbool UpdateS57Attribute(const UGString& strAcronym, UGVariant& valValue);

		void SetChartLayerEditAttributeFunc(AfterChartLayerEditAttributeProc pChartLayerEditAttiProc, UGlong pWnd);
		void SendChartLayerEditAttributeFunc(UGbool& bEditAttribute);

		void SetPointStyles(UGArray<UGStyle>& pointStyle);
		UGArray<UGStyle>& GetPointStyles();

		void SetEdgesStyle(UGArray<UGS57EdgeStyle>& aryEdgeStyle);
		UGArray<UGS57EdgeStyle> GetEdgesStyle();

		void SetModifiedLineStyle(UGArray<UGS57EdgeStyle>& aryEdgeStyle);

		void SetModifiedS57EdgeStyleFunc(AfterModifiedEdgeStyleProc pModifiedEdgeStyleProc, UGlong pWnd);
		void SendModifiedS57EdgeStyleFunc(UGArray<UGS57EdgeStyle>& s57EdgeStyles);

		void SetChartSetting(UGChartSetting *pChartSetting);
	private:
		//  初始化值
		void Init();

		// 由DEST_LNAM值获取相应关系的SRC_LNAM.
		// nRIND 关系类型
		UGString GetRelationSrcLNAM(const UGint nRIND);
		
		// 读取S57标准中定义的属性
		UGbool ReadS57Attribute(UGS57SpecsObject& s57SpecsObj);

		UGbool WriteS57Attribute(UGS57AttiInfo& s57AttiInof);

		UGbool WriteS57Attribute(const UGString& strAcronym, UGVariant& valValue);
	private:
		UGRecordset *m_pRecordset;
		UGDatasetGroup *m_pDatasetGroup;
		// 需要提供的信息
		UGString m_strLNAM;
		UGuint  m_nFeatureID;
		UGString m_strAcronym;
		UGString m_strName;
		UGString m_strLocalName;
		UGint m_nFeatureCode;
		UGString m_strAgencyToken;
		UGGeometry::Type m_eGeoType;
		UGdouble m_dDepth;
		UGString m_strFeatureTypeName;
		UGString m_strMasterLNAM;
		UGString m_strCollectionLNAM;
		UGint m_nRecordsetID;
		UGArray<UGS57AttiInfo> m_AttiInfos;
		
		UGArray<UGStyle> m_pointStyle;
		//! \brief 调用事件回调函数的对象指针
		UGlong m_pEventView;  

		UGChartSetting *m_pChartSetting;

		UGArray<UGS57EdgeStyle> m_s57EdgeStyles;
		UGArray<UGS57EdgeStyle> m_modifiedS57EdgeStyles;
		AfterChartLayerEditAttributeProc m_pAfterChartLayerEditAttributeFunc;
		AfterModifiedEdgeStyleProc m_pAfterModifiedEdgeStyleFunc;
	};
}

#endif
