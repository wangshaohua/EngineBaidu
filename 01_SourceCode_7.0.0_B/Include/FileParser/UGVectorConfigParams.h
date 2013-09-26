// UGVectorImportParams.h: interface for the UGVectorImportParams class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_UGVECTORIMPORTPARAMS_H__5D6357D7_FC27_48BC_8BA4_3A6788F5DD2F__INCLUDED_)
#define AFX_UGVECTORIMPORTPARAMS_H__5D6357D7_FC27_48BC_8BA4_3A6788F5DD2F__INCLUDED_

#include "Stream/ugexports.h"
#include "FileParser/UGFileParserConfigParams.h"


#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

namespace UGC {

class  UGVectorFileLayer;
class UGSpatialIndexInfo;
	
//! \brief 源数据中要素类描述。
//! \remarks 备注信息。
class FILEPARSER_API UGFeatureClassDefn
{
	friend class UGVectorFileLayer;

public:
	
	//! \brief 构造函数。
	//! \remarks 。
	UGFeatureClassDefn();

	//! \brief 拷贝构造函数。
	//! \remarks 。
	UGFeatureClassDefn(const UGFeatureClassDefn& ClassDef);

	//! \brief 析构函数。
	//! \remarks 。
	virtual ~UGFeatureClassDefn();

	//! \brief 重载操作符 =  。
	//! \param fcdef [in]。
	//! \return 。
	//! \remarks 。
	//! \attention 。
	UGFeatureClassDefn& operator=(const UGFeatureClassDefn& fcdef);	
	
public:
	
	//! \brief 导入后结果数据集类型。
	//! \remarks 枚举值和 UGDataset::DatasetType 的值一致。
	enum FeatureClassType
	{
		//! 不认识
		UnKnown		=-1,	
		//! 只有属性表，没有几何对象
		Tabular		=0,
		//! 点数据集
		Point		=1,
		//! 线数据集
		Line		=3,		
		//! 网络数据集
		Network		=4,		
		//! 多边形数据集
		Region		=5,	
		//! 文本数据集
		Text		=7,	
		//!参数化线数据集
		CompoundLine   = 8,
		//！参数化面数据集
		CompoundRegion = 9,
		//! 路线数据集
		LineM		=35,	
		//! 三维点
		PointZ		=101,
		//! 三维线
		LineZ		=103,
		//! 三维面
		RegionZ		=105,	
		//! 带法向量的Point3D
		PointGL		=137,	
		//! TIN数据集
		TIN			=139,	
		//! CAD数据集
		CAD			=149,
		//! Topo数据集
		Topo		=154,	
		//! 新的Tin数据和以前的区分开
		TIN2		=155	
	};
	

	//! \brief 返回数据集类型。
	//! \param  [in]。
	//! \return 。
	//! \remarks 。
	//! \attention 。
	UGint GetType() const;		
	
	//! \brief 设置数据集类型。
	//! \param  字段类型[in]。
	//! \return 。
	//! \remarks 。
	//! \attention 。
	void SetType(UGint nType);
	
	//! \brief 返回结果数据集名称。
	//! \param  [in]。
	//! \return 。
	//! \remarks 。
	//! \attention 。
	UGString GetName() const;	
	
	//! \brief 设置/修改结果数据集名称。
	//! \param strNewName [in]。
	//! \return 。
	//! \remarks 。
	//! \attention 。
	void SetName(const UGString& strNewName);	
	
	//! \brief 获取对象个数。
	//! \param  nCount字段个数[in]。
	//! \return 。
	//! \remarks 。
	//! \attention 。
	UGint GetFeatureCount() const;	
	
	//! \brief 设置对象个数。
	//! \param  nCount字段个数[in]。
	//! \return 。
	//! \remarks 。
	//! \attention 。
	void SetFeatureCount(UGint nCount);	
	
	//! \brief 返回数据集范围。
	//! \param  [in]。
	//! \return 。
	//! \remarks 。
	//! \attention 。
	UGRect2D GetBound() const;	

	//! \brief 设置数据集范围。
	//! \param  rect2D 地理方位[in]。
	//! \return 。
	//! \remarks 。
	//! \attention 。
	void SetBound(const UGRect2D& rect2D);

	//! \brief 获取字段个数。
	//! \param  [in]  
	//! \return 。
	//! \remarks 。
	//! \attention 。
	UGint GetFieldCount() const;

	//! \brief 获取指定索引位置字段信息。
	//! \param  nIndex [in]  取值:[0 and GetFieldCount()-1]. 
	//! \return 。
	//! \remarks 。
	//! \attention 用户不得删除返回的字段指针。
	UGFieldInfo* GetFieldDefn(UGint nIndex) const;

	//! \brief 获取字段信息。
	//! \param  nIndex [in]  取值:[0 and GetFieldCount()-1]. 
	//! \return 返回字段信息的拷贝。
	//! \remarks 。
	//! \attention 。
	UGFieldInfos GetFieldInfos() const;	

	//! \brief 设置字段信息。
	//! \param  fieldInfos [in]  源字段值
	//! \return 
	//! \remarks 。
	//! \attention 。
	void SetFieldInfos(const UGFieldInfos& fieldInfos);	

	//! \brief 添加一个新的字段。
	//! \param  newFieldDefn [in] 函数内部copy传入的参数，用户负责释放参数。
	//! \return 。
	//! \remarks 。
	//! \attention 
	UGbool AddFieldDefn(UGFieldInfo* newFieldDefn);
	
	//! \brief 移除指定索引位置字段。
	//! \param  nIndex [in]  取值:[0 and GetFieldCount()-1]. 
	//! \return 。
	//! \remarks 。
	//! \attention 。
	void RemoveFieldDefn(UGint nfield);

	//! \brief // 释放字段字典
	//! \param  [in]。
	//! \return 。
	//! \remarks 。
	//! \attention 。
	void RemoveAllFieldDefn();	

	//! \brief 按照指定的两个索引位置交换字段顺序。
	//! \param  nFirst [in]  取值:[0 and GetFieldCount()-1]. 
	//! \param  nSecond [in]  取值:[0 and GetFieldCount()-1]. 
	//! \return 成功返回TRUE。
	//! \remarks 此接口主要给组件用。
	//! \attention 。
	UGbool ChangeFieldDefn(UGint nFirst, UGint nSecond);

	//! \brief 按照指定的两个索引位置交换CAD扩展数据的的字段顺序。
	//! \param  nFirst [in]  取值:[0 and m_xDataFieldInfos.GetSize()-1]. 
	//! \param  nSecond [in]  取值:[0 and m_xDataFieldInfos.GetSize()-1]. 
	//! \return 成功返回TRUE。
	//! \remarks 此接口主要给组件用。
	//! \attention 。
	UGbool ShiftxDataField(UGint nFirst, UGint nSecond);

	//! \brief 返回layer的原始名称。
	//! \param  [in]。
	//! \return 。
	//! \remarks 。
	//! \attention 。
	UGString GetOriginalName() const;
	
	//! \brief 设置layer的原始名称。
	//! \param  [in]。
	//! \return 。
	//! \remarks 。
	//! \attention 。
	void SetOriginalName(const UGString& strNewName);
	
	//! \brief 设置CAD扩展字段名称。
	//! \param  xDataFieldInfos[in]。
	//! \return 。
	//! \remarks 。
	//! \attention 用户也仅限于修改字段名称的权限。
	void SetxDataFieldNames(UGDict<UGString,UGString>& DictxDataFieldNames);

	
	//! \brief 获取源字段信息。
	//! \param  [out]。
	//! \return m_arrfieldNames。
	//! \remarks 。
	//! \attention 。
	UGStrArray GetSourceFieldNames() const;

	//! \brief 获取CAD扩展字段名称。
	//! \param  [in]。
	//! \return 。
	//! \remarks 。
	//! \attention 。
	UGDict<UGString,UGString> GetxDataFieldNames() const;

	//! \brief 获取源数据的空间坐标系。
	//! \param  [in]。
	//! \return 。
	//! \remarks
	//! \attention 。
	UGPrjCoordSys* GetSpatialRef() const {return m_pSpatialRef;}

	//! \brief 设置源数据的空间坐标系。
	//! \param  [in]。
	//! \return 。
	//! \remarks 。
	//! \attention 。
	void SetSpatialRef(const UGPrjCoordSys* pSpatialRef);

	//! \brief 设置DWG/DXF扩展数据的字段。
	//! \param xDataFieldInfos [in]。
	//! \return 。
	//! \remarks 。
	//! \attention 。
	void SetxDataFieldInfos(const UGFieldInfos& xDataFieldInfos);	
	
	//! \brief 获取DWG/DXF扩展数据的字段。
	//! \param  [in]。
	//! \return 。
	//! \remarks 。
	//! \attention 。
	UGFieldInfos GetxDataFieldInfos()const;

// 	//! \brief 设置数据集关联属性表的名称
// 	//! \param  strRelatedTableName [in]。
// 	//! \return 。
// 	//! \remarks 。
// 	//! \attention 。
// 	void SetRelatedTableName(const UGString& strRelatedTableName);
// 
// 	//! \brief 获取数据集关联属性表的名称
// 	//! \param  [in]。
// 	//! \return 。
// 	//! \remarks 。
// 	//! \attention 。
// 	UGString GetRelatedTableName()const;

// 	//! \brief s57数据集类型
// 	void SetS57DatasetType(UGS57ExtInfo::UGS57DatasetType eDatasetType);
// 
// 	UGS57ExtInfo::UGS57DatasetType GetS57DatasetType() const;

	void SetS57ExtInfo(const UGString& strExtInfo);

	UGString GetS57ExtInfo() const;

protected:
	
	//! \brief 初始化。
	//! \param  [in]。
	//! \return 。
	//! \remarks 。
	//! \attention 。
	void Init();

	//! \brief 保存layer的原始字段信息。
	//! \param  FieldInfos[in]。
	//! \return 。
	//! \remarks 。
	//! \attention 
//	void SetFieldInfosOrginal(UGFieldInfos& FieldInfos);

	//! \brief // 释放字段字典
	//! \param  [in]。
	//! \return 。
	//! \remarks 。
	//! \attention 。
	void ClearFieldDict();	

	//! \brief // 通过名称获取m_arrfieldNames中的索引
	//! \param  [in]。
	//! \return 。
	//! \remarks 。
	//! \attention 。
	UGint FindIndexByName(const UGString& strFieldName)const;
protected:
	
	//! \brief 要素类型。
	//! \remarks 。
	FeatureClassType m_Type;
	
	//! \brief 对象个数。
	//! \remarks 。
	UGint m_nFeatureCount;
	
	//! \brief 数据集的范围。
	//! \remarks 。
	UGRect2D m_Bound;

	//! \brief 字段结构。
	//! \remarks 。
	UGDict<UGString, UGFieldInfo*> m_dictFieldInfos;

	// 字段名称数组，维护字段的顺序关系，使之和原始字段顺序一致
	UGStrArray m_arrfieldNames;
	// 字段名称数组备份，以防删除m_arrfieldNames中的字段名称
	UGStrArray m_arrCopyfieldNames;

	//! \brief 结果数据集名称。
	//! \remarks 。
	UGString m_strAliasName;

	//! \brief 源数据Layer名称。
	//! \remarks 数据中Layer的真实名称，不能修改。
	UGString m_strLayerName;

	//! \brief CAD扩展数据的字段名称。
	//! \remarks 。
	UGDict<UGString,UGString> m_DictxDataFieldNames;
	
	//! \brief CAD数据中扩展属性字段结构
	//! \remarks 
	UGFieldInfos m_xDataFieldInfos;

	//! \brief  数据集投影
	UGPrjCoordSys* m_pSpatialRef;

	//! \brief 数据集关联属性表名称 S-57中使用
	// UGString m_strRelatedTableName;

	//! \brief S57数据集类型
	// UGS57ExtInfo::UGS57DatasetType m_eS57DatasetType;
	// UGS57ExtInfo m_s57ExtInfo;
	UGString m_strExtInfo;


};

//! \brief 源数据中的数据集基本信息。
//! \remarks数据集名称为关键字	
//typedef UGArray<UGFeatureClassDefn*> UGFeatureClassInfos;
class FILEPARSER_API UGFeatureClassInfos : public UGArray<UGFeatureClassDefn> 
{ 
public:
	//! \brief 构造函数。
	//! \remarks 。
	UGFeatureClassInfos();
	
	//! \brief 析构函数。
	//! \remarks 。
	virtual ~UGFeatureClassInfos();

public:

	//! \brief 通过名称得到数组中一个层要素定义。
	//! \param strName [in] 层名称。
	//! \return 。
	//! \remarks 。
	//! \attention 。
	const UGFeatureClassDefn* GetFeatureDefnByName(const UGString& strName) const;		

};


//! \brief 矢量导入参数	
class FILEPARSER_API UGVectorImportParams  : public UGImportParams
{
	friend class UGWorkspaceImportParams;
public:
	//! \brief 构造函数。
	//! \remarks 。
	UGVectorImportParams();
	
	//! \brief 析构函数。
	//! \remarks 。
	virtual ~UGVectorImportParams();
	
	//! \brief 构造函数。
	//! \remarks 。
	UGVectorImportParams(const UGVectorImportParams& tmp);

	//! \brief 重载赋值符号函数。
	//! \remarks 。
	UGVectorImportParams& operator=(const UGVectorImportParams& tmp);

public:
	
	//! \brief 设置导入的数据集结果信息。
	//! \param impDatasetInfos [in]。
	//! \return 。
	//! \remarks 。
	//! \attention 。
	void SetImportDatasetInfos(const UGFeatureClassInfos& impDatasetInfos);	
	
	//! \brief 得到导入的数据集结果信息。
	//! \param  [in]。
	//! \return 。
	//! \remarks 。
	//! \attention 。
	UGFeatureClassInfos& GetImportDatasetInfos();

	//! \brief 设置是否忽略空数据集。没有记录的数据集为空数据集
	//! \param bHoldNoGeometryDT [in]。
	//! \return 。
	//! \remarks 。
	//! \attention 。
	void SetIgnoreNoGeometryDataset(UGbool bHoldNoGeometryDT = TRUE);	
	
	//! \brief 得到是否忽略空数据集。没有记录的数据集为空数据集
	//! \param  [in]。
	//! \return 。
	//! \remarks 。
	//! \attention 。
	UGbool GetIgnoreNoGeometryDataset() const;
	

	//! \brief 设置导入后建立的空间索引类型。
	//! \param spatialIndx [in]。
	//! \return 。
	//! \remarks 。
	//! \attention 。
	void SetBuildSpatialIndex(const UGSpatialIndexInfo* spatialIndx);


	//! \brief 得到建立的空间索引类型。。
	//! \param  [in]。
	//! \return 。
	//! \remarks 内部管理的成员，外面不能释放
	//! \attention 。
	UGSpatialIndexInfo* GetBuildSpatialIndex() const;
	
	//! \brief 。
	//! \param strDtName [in]。
	//! \return 。
	//! \remarks 。
	//! \attention 。
	void SetDestDTVectorName(const UGString& strDtName);

protected:
	
	//! \brief 。
	//! \remarks 。
	UGFeatureClassInfos m_dtInfos;
	

	UGSpatialIndexInfo* m_pSpatialIndex;

};


//////////////////////////////////////////////////////////////////////////

//! \brief 矢量导出参数。
//! \remarks 备注信息。
class FILEPARSER_API UGVectorExportParams : public UGExportParams
{
public:
	//! \brief 构造函数。
	//! \remarks 。
	UGVectorExportParams(){
		m_strDatasetName = _U("");
	}//初始值=0，表示没有版本

	//! \brief 析构函数。
	//! \remarks 。
	virtual ~UGVectorExportParams(){}
public:
	//! \brief 获取要导出的矢量数据集名称。
	//! \param  [in]。
	//! \return 。
	//! \remarks 。
	//! \attention 。
	UGString GetDtNameToBeExported() const;	

	//! \brief 设置要导出的矢量数据集名称。
	//! \param  name [in] 设置的名称。
	//! \return 。
	//! \remarks 。
	//! \attention 。
	void SetDtNameToBeExported(const UGString& name);


	//! \brief 获取要导出的矢量数据集名称数组。
	//! \param  [in]。
	//! \return 。
	//! \remarks 数据集名称数组。
	//! \attention 为了多个数据集导出使用。
	//! 注意此接口是虚函数, 支持多数据集导出功能的格式需要重载
	virtual UGbool GetDtNamesBeExported(UGStrings& arrNames) const {return FALSE;}

	//! \brief 设置要导出的矢量数据集名称数组。
	//! \param  name [in] 设置的名称。
	//! \return 。
	//! \remarks 。
	//! \attention 为了多个数据集导出使用。
	//! 注意此接口是虚函数, 支持多数据集导出功能的格式需要重载
	virtual void SetDtNamesBeExported(const UGStrings& arrNames){ ;};

protected:
	
	//! \brief 。
	//! \remarks 。
	UGDict <UGint, UGFeatureClassDefn> m_ExportDatasetInfos;
	
private:	
	// \brief 要导出的数据集名称。
	// \remarks 。
	UGString m_strDatasetName;
};

} //namespace UGC

#endif // !defined(AFX_UGVECTORIMPORTPARAMS_H__5D6357D7_FC27_48BC_8BA4_3A6788F5DD2F__INCLUDED_)

