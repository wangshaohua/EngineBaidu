// SmWFSVector.h: interface for the UGDatasetVectorWFS class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SMWFSVECTOR_H__BD617A57_529C_414D_ABED_99EF4BC23929__INCLUDED_)
#define AFX_SMWFSVECTOR_H__BD617A57_529C_414D_ABED_99EF4BC23929__INCLUDED_

#include "Stream/ugexports.h"
#include "Engine/UGWebDatasetVector.h"
#include "EngineOGC/UGOGCLayerInfo.h"
#include "EngineOGC/UGWFSCapabilities.h"

namespace UGC
{

class ENGINEOGC_API UGDatasetVectorWFS : public UGWebDatasetVector  
{
public:
	//! \brief  默认的构造函数
	UGDatasetVectorWFS();
	//! \brief  带有形参的的构造函数
	UGDatasetVectorWFS(UGDataSource *pDataSource);
	//! \brief  带有形参的的构造函数
	UGDatasetVectorWFS(UGDatasetVectorInfo& vInfo);
	//! \brief  默认的析构函数
	virtual ~UGDatasetVectorWFS();

public:
	//! \brief 根据查询定义得到内存记录集。
	//! \param querydef 查询定义[in]。
	//! \return 内存记录集。
	UGRecordset* Query(const UGQueryDef& querydef);

	//! \brief 根据WFS的GetFeature的URL请求得到内存记录集,默认等到EditRecordset。
	//! \param strURL WFS的GetFeature请求的URL[in]。
	//! \return 内存记录集。
	UGRecordset* Query(const UGString &strURL);

	//! \brief 设置此数据集对应的FeatureTypeInfo的WFS图层信息。
	//! \param arySrc 网络数据源图层信息[in]。
	//! \return 是否设置成功,成功返回TRUE,否则返回FALSE。
	UGbool SetFeatureTypeInfo(const WFSFeatureType& layerSrc);	

	//! \brief 得到数据集对应的FeatureTypeInfo的信息。
	//! \param aryDest 网络数据源图层信息[in]。
	//! \return 是否成功得到,成功返回TRUE,否则返回FALSE。
	UGbool GetFeatureTypeInfo(WFSFeatureType& layerDest) const;	

	//! \brief 解析得到数据集的类型并写入到数据集的m_DatasetInfo中支。
	//! \return 是否成功解析,成功返回TRUE,否则返回FALSE。
	UGbool ParseDatasetType();
	//! \brief 返回数据集中对象个数,速度慢,但值比较正确,
	//! \brief 通过Register表获取
	//##ModelId=48203053011A
	virtual UGint GetObjectCount();

	//! \brief 判断当前数据集是否可编辑
	virtual UGbool CanUpdate();
private:


	//! \brief 根据四至信息查询得到记录集。
	//! \param &rcQueryBound 查询定义对象，包含四至信息[in]。
	//! \return 内存记录集。
	//! \param bIsCached 是否缓冲网络数据源[in]。
	UGRecordset* GetRecordsetVectorBounds(const UGQueryDef& queryBound, UGbool bIsCached);
	
	//! \brief 根据IDs查询的查询定义得到记录集。
	//! \param queryIDs 查询定义对象，包含查询的IDs[in]。
	//! \param bIsCached 是否缓冲网络数据源[in]。
	//! \return 内存记录集。
	UGRecordset* GetRecordsetVectorIDs(const UGQueryDef& queryIDs, UGbool bIsCached);
	
	//! \brief 根据General查询的查询定义得到记录集。
	//! \param queryGeneral 查询定义对象，包含General查询的参数[in]。
	//! \param bIsCached 是否缓冲网络数据源[in]。
	//! \return 内存记录集。	
	UGRecordset* GetRecordsetVectorGeneral(const UGQueryDef& queryGeneral, UGbool bIsCached);

	//! \brief 根据GetFeauture请求的URL得到内存数据集，再查询得到内存记录集。
	//! \param strURL GetFeauture请求的URL[in]。
	//! \param queryDef 查询定义对象[in]。
	//! \return 内存记录集。
	UGRecordset* GetRecordsetVector(UGString strGetFeatureURL,const UGQueryDef& queryDef);

	//! \brief 得到图层信息的边界的联合。
	//! \param layersInfo 图层信息集合[in]。
	//! \return 边界矩形。
	//! \remarks 的有图层信息有多个边框，在些也都合并在最终返回结果里。
	UGRect2D GetLayersBoundUnion(const UGWebLayersInfos& layersInfo);

	//! \brief 得到可见图层的URL查询选项。
	//! \param layersSrc 图层信息集合[in]。
	//! \return Layers URL查询选项，格式为Layers = Layer1,Layer2,Layer3&amp;
	//! \remarks 格式为LAYERS = Layer1,Layer2,Layer3&amp;。
	UGString GetLayersURLValue(UGWebLayersInfos layersSrc) const;

	//! \brief 得到可见图层的URL查询选项。
	//! \param layersSrc 图层名集合[in]。
	//! \return Layers URL查询选项。
	//! \remarks 格式为LAYERS = Layer1,Layer2,Layer3&amp;。
	UGString GetLayersURLValue(UGArray<UGString> layersSrc) const;

	//! \brief 得到图层请求范围的URL查询选项。
	//! \return BBOX URL查询选项。
	//! \remarks 格式为 BBOX=-165.270004272461,-54.7538909912109,177.130187988281,83.1083221435547&amp。
	UGString GetBBoxURLValue(UGRect2D rcSrc) const;

	//! \brief 得到IDs查询的FeatureID URL查询选项。
	//! \param *pIDs IDs数组指针[in]。
	//! \param nCount IDs个数[in]。
	//! \return FeatureID URL查询选项，格式为FeatureID=state.1,state.2&amp;。
	//! \remarks 例如：FeatureID=state.1,state.2&。
	UGString GetFeatureIDURLValue(UGint *pIDs, UGint nCount) const;	

	//! \brief 通过GetFeature请求的XML文件生成内存数据源。
	//! \param strGetFeatureXMLPath GetFeature请求得到的XML文件地址[in]。
	//! \param strDescribeXMLPath DescribeFeatureType请求得到的XML文件地址[in]。
	//! \param versionGML 请求过程中使用到的GML语言和版本[in]。
	//! \return 内存数据源指针。
	UGDataSource* CreatDataSource(UGString strGetFeatureXMLPath, 
		UGString strDescribeXMLPath, UGGeometry::GMLVersionType versionGML);

	//! \brief 解析得到当前FeatureType所对应的字段信息数组。
	//! \param fieldInfos 解析得到的字段信息数组[in]。
	//! \param strTypeName 解析得到的WFS数据集名[in]。
	//! \param edatasetType 解析得到的WFS数据集类型[in]。
	//! \param strDiscribeXMLPath DescribeFeatureType请求得到的XML文件地[in]。
	//! \return 是否成功解析,成功返回TRUE,失败返回FALSE。
	UGbool ParseFeatureType(UGFieldInfos& fieldInfos, UGString& strTypeName, 
		UGDataset::DatasetType& edatasetType, UGString strDescribeXMLPath);

	//! \brief 通过GetFeature请求的XML文件得到内存数据源的边界和投影。
	//! \param CRSBound 参考系四至信息[in]。
	//! \param strDiscribeXMLPath GetFeature请求的XML文件地址[in]。
	//! \return 是否成功解析,成功返回TRUE,失败返回FALSE。
	UGbool ParseFeatureBound(UGCRSBound& CRSBound, UGString strGetFeatureXMLPath);
	
	UGbool JudgeGeoLabel(UGString strLabelName);

	
	//! \brief 根据mk找到一条新对象并添置到记录集里。
	//! \param *pRecordset [in] 。
	//! \param &mk [in] CMarkup对象
	//! \param pGeoAdd [in] 要添加的几何对象。
	//! \param trans [in] 投影转换器，用来设置几何对象的投影。
	//! \param bTrans [in] 是否进行投影的转换。
	//! \param VersionGML [in] 获取几何对象的gml版本。	 	
	//! \attention 。
	UGString AddGeometry(UGRecordset *pRecordset,UGMarkup &mk,UGGeometry* pGeoAdd,	
		UGRefTranslator& trans,UGbool bTrans,UGGeometry::GMLVersionType VersionGML);

	//! \brief 根据字段信息得到fieldinfo
	UGFieldInfo GetSysFieldInfo(const UGString & strName,
		const UGString & strForeignName,
		UGFieldInfo::FieldType nType,
		const UGString & strFormat,	
		const UGString & strDomain, 
		UGbool bUpdatable = TRUE,
		UGbool bRequired = FALSE,
		const UGString & strDefault = _U("")
		);
	void GetSysFieldInfos(UGDataset::DatasetType eDatasetType, UGFieldInfos &sysFieldInfos);

protected:
	
	//! \brief WFS数据源的图层信息。
	//! \remarks 备注信息。
	WFSFeatureType m_featureTypeInfo;

	//! \brief 查询的元素前缀
	//! \remarks 例如 FeatureID=state.1,state.2 则前缀就是state。
	UGString m_strElementName;

	//! \brief 数据集是否经过转化。
	//! \remarks 备注信息。
	UGbool m_bHasTrans;

	//! \brief 数据集是否更新过字段信息。
	UGbool m_bFieldsUpdated;
 
	//! \brief  在获取数据对象数目时用
	//! \attention 以第一次查询为准。	
	UGint m_nWFSObjectCount;
};

}
#endif // !defined(AFX_SMWFSVECTOR_H__BD617A57_529C_414D_ABED_99EF4BC23929__INCLUDED_)

