// UGVectorImportParams.h: interface for the UGVectorImportParams class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_UGMODELIMPORTPARAMS_H__5D6357D7_FC27_48BC_8BA4_3A6788F5DD2F__INCLUDED_)
#define AFX_UGMODELIMPORTPARAMS_H__5D6357D7_FC27_48BC_8BA4_3A6788F5DD2F__INCLUDED_

#include "Stream/ugexports.h"
#include "FileParser/UGFileParserConfigParams.h"
#include "FileParser/UGVectorConfigParams.h"


#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

namespace UGC {

class  UGVectorFileLayer;
class UGSpatialIndexInfo;


//! \brief 矢量导入参数	
class FILEPARSER_API UGModelImportParams  : public UGVectorImportParams
{
	friend class UGWorkspaceImportParams;
public:
	//! \brief 构造函数。
	//! \remarks 。
	UGModelImportParams();
	
	//! \brief 析构函数。
	//! \remarks 。
	virtual ~UGModelImportParams();
	
	//! \brief 构造函数。
	//! \remarks 。
	UGModelImportParams(const UGModelImportParams& tmp);

	//! \brief 重载赋值符号函数。
	//! \remarks 。
	UGModelImportParams& operator=(const UGModelImportParams& tmp);

public:
	
	

protected:
	
// 	! \brief 。
// 		//! \remarks 。
// 		UGFeatureClassInfos m_dtInfos;
// 		
// 	
// 		UGSpatialIndexInfo* m_pSpatialIndex;

};


//////////////////////////////////////////////////////////////////////////

//! \brief 矢量导出参数。
//! \remarks 备注信息。
class FILEPARSER_API UGModelExportParams : public UGExportParams
{
public:
	//! \brief 构造函数。
	//! \remarks 。
	UGModelExportParams(){
		m_strDatasetName = _U("");
	}//初始值=0，表示没有版本

	//! \brief 析构函数。
	//! \remarks 。
	virtual ~UGModelExportParams(){}
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
	/*UGDict <UGint, UGFeatureClassDefn> m_ExportDatasetInfos;*/
	
private:	
	// \brief 要导出的数据集名称。
	// \remarks 。
	UGString m_strDatasetName;
};

} //namespace UGC

#endif // !defined(AFX_UGVECTORIMPORTPARAMS_H__5D6357D7_FC27_48BC_8BA4_3A6788F5DD2F__INCLUDED_)

