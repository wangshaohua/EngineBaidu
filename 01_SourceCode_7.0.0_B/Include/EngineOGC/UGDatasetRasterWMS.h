// UGDatasetRasterWMS.h: interface for the UGDatasetRasterWMS class.
//
//////////////////////////////////////////////////////////////////////

#ifndef UGDATASETRASTERWMS_H
#define UGDATASETRASTERWMS_H

#include "Stream/ugexports.h"
#include "Engine/UGWebDatasetRaster.h"
#include "EngineOGC/UGOGCLayerInfo.h"

namespace UGC
{
#define DEFAULT_SRS_NAME _U("EPSG:4326")
#define DEFAULT_NONE _U("NONE")

class ENGINEOGC_API UGDatasetRasterWMS  :public UGWebDatasetRaster
{
public:
	//! \brief  默认的构造函数
	UGDatasetRasterWMS();
    //! \brief  带有形参的的构造函数
	UGDatasetRasterWMS(UGDatasetRasterInfo& rInfo);
	//! \brief  默认的析构函数
	virtual ~UGDatasetRasterWMS();
public:
	//! \brief 得到基于内存的栅格数据集。
	//! \param strURL 向Web数据源请求的URL[in]。
	//! \return 栅格数据集指针。
	//! \remarks 其它重载函数都由此函数包装。
	virtual UGDatasetRaster* GetDatasetRaster(UGString strURL);
	
	//! \brief 得到基于内存的栅格数据集,用于放大缩小平移操作的请求。
	//! \param rcBound 请求影像的四至范围[in]。
	//! \param dWidth 请求影像的宽度,单位像素[in]。
	//! \param dHeight 请求影像的高度,单位像素[in]。
	//! \param strFormat 请求影像的格式[in]。
	//! \return 栅格数据集指针。
	virtual UGDatasetRaster* GetDatasetRaster(UGRect2D rcBound,
		UGint dWidth,UGint dHeight,UGString strFormat =_U("image/png"));
	
	//! \brief 得到数据源的所有图层名数组。
	//! \param aryNames 图层名数组[out]。
	//! \return 是否成功得到,成功返回TRUE,失败返回FALSE。
	virtual UGbool GetAllLayerNames(UGArray<UGString>& aryLayerNames);
	
	//! \brief 得到数据源的所有图层标题数组。
	//! \param aryNames 图层标题数组[out]。
	//! \return 是否成功得到,成功返回TRUE,失败返回FALSE。
	virtual UGbool GetAllLayerTitles(UGArray<UGString>& aryLayerTitles);
	
	//! \brief 得到数据源的所有图层编号数组。
	//! \param aryNames 图层编号数组[out]。
	//! \return 是否成功得到,成功返回TRUE,失败返回FALSE。
	virtual UGbool GetAllLayerIndexes(UGArray<UGint>& aryLayerIndexes);
	
	//! \brief 得到所有可见图层名数组。
	//! \param aryNames 可见图层名数组[in]。
	//! \return 是否成功得到,成功返回TRUE,失败返回FALSE。
	virtual UGbool GetVisibleLayerNames(UGArray<UGString>& aryLayerNames);
	
	//! \brief 得到所有可见图层标题数组。
	//! \param aryNames 可见图层图层标题数组[in]。
	//! \return 是否成功得到,成功返回TRUE,失败返回FALSE。
	virtual UGbool GetVisibleLayerTitles(UGArray<UGString>& aryLayerTitles);
	
	//! \brief 得到数据集所有可见的图层编号集合。
	//! \param aryNames 可见图层编号数组[in]。
	//! \return 是否成功得到,成功返回TRUE,失败返回FALSE。
	virtual UGbool GetVisibleLayerIndexes(UGArray<UGint>& aryLayerIndexes);
	
	//! \brief 设置当前数据集的可见图层。
	//! \param arySrc 源图层编号数组[in]。
	//! \return 是否设置成功,成功返回TRUE,否则返回FALSE。
	virtual UGbool SetVisibleLayers(const UGArray<UGint>& aryLayerIndexes);	
	
	//! \brief 设置当前数据集的可见图层。
	//! \param arySrc 源图层信息数组[in]。
	//! \return 是否设置成功,成功返回TRUE,否则返回FALSE。
	virtual UGbool SetVisibleLayers(const UGArray<UGString>& aryLayerNames);

	//! \brief 设置是否背景透明。
	virtual void SetTransparent(UGbool bTransparent);

	//! \brief 得到是否背景透明。
	virtual UGbool GetTransparent();
	
public:

	//! \brief 得到几何对象的特征信息。
 	//! \param posX [in] 在指定的dWidth,dHeight框选区域点选的x象素点。
	//! \param posY [in] 在指定的dWidth,dHeight框选区域点选的y象素点。。	
	//! \param dictQueryPairs [out] 得到的特征健值对。
	//! \return 。	
	//! \attention 。
	UGbool GetWMSFeatureInfos(UGlong posX,UGlong posY,
							UGDict<UGString,UGString>& dictQueryPairs); 
	//! \brief 设置当前数据集的所有图层。
	//! \param arySrc 源图层信息集合[in]。
	//! \return 是否设置成功,成功返回TRUE,否则返回FALSE。
	UGbool SetAllLayers(const UGWebLayersInfos& arySrc);
	
	//! \brief 得到当前数据集的所有图层。
	//! \param aryDest 目的图层信息集合[out]。
	//! \return 是否成功得到,成功返回TRUE,否则返回FALSE。
	UGbool GetAllLayers(UGWebLayersInfos& aryDest) const;	
	
	//! \brief 设置当前数据集的可见图层。
	//! \param arySrc 源图层信息集合[in]。
	//! \return 是否设置成功,成功返回TRUE,否则返回FALSE。
	UGbool SetVisibleLayers(const UGWebLayersInfos& arySrc);	
	
	//! \brief 得到当前数据集的可见图层。
	//! \param aryDest 目的图层信息集合[in]。
	//! \return 是否成功得到,成功返回TRUE,否则返回FALSE。
	UGbool GetVisibleLayers(UGWebLayersInfos& aryDest) const;
 
	//! \brief 在可见图层中获取可查询的图层。
	//! \return 返回以逗号分隔的图层字符串。
	UGString GetQueryableLayers();
	//! \brief 将图层树初始化到扁平序列。
	//! \param aryDest 目的图层信息集合[in]。
	//! \return 是否成功得到,成功返回TRUE,否则返回FALSE。
	UGbool initLayers(WMSLayer* pWMSlayer);
	//! \brief 给WMS某个图层设置m_arrWMSStyle中的某一风格。
	//! \param strLayName 所要设置的图层的名字。
	//! \param strStyle 所设置的风格。
	//! \attention 。
	UGbool SetStyle(UGString &strLayName,UGString &strStyle);
	//! \brief 得到所有图层的支持的style 。
	//! \attention 。
	//! \return 返回style的集合
	UGArray<UGString> GetAllStyles();
	//! \brief 返回地图时指定的地图宽	 。
	UGint GetMapWidth() 	const { return m_dWidth; }
	//! \brief 返回地图时指定的地图高	 。
    UGint GetMapHeight() const { return m_dHeight; }
private:
	//! \brief 得到图层信息的边界的联合。
	//! \param layersInfo 图层信息集合[in]。
	//! \return 边界矩形。
	//! \remarks 的有图层信息有多个边框，在些也都合并在最终返回结果里。
	UGRect2D GetLatLonBoxUnion() const;

	//! \brief 得到图层信息的边界的联合。
	//! \param layersInfo 图层信息集合[in]。
	//! \return 边界矩形。
	//! \remarks 的有图层信息有多个边框，在些也都合并在最终返回结果里。
	UGRect2D GetBoundingBoxUnion(UGString& strCrsName) const;

	//! \brief 得到使用的参考系四至。
	//! \return 是否得到。
	UGbool GetUsedCRSBounds();	

	//! \brief 得到可见图层的URL查询选项,格式为Layers = Layer1,Layer2,Layer3&amp;。
	//! \param layersSrc 图层信息集合[in]。
	//! \return Layers URL查询选项。
	//! \remarks 格式为LAYERS = Layer1,Layer2,Layer3&amp;。
	//! \attention 。
	UGString GetLayersURLValue() const;

	//! \brief 得到可见图层的URL查询选项,格式为Styles = style1,style2...		
	//! \attention 。
 	UGString GetStylesURLValue() const;
	
	//! \brief 得到图层请求范围的URL查询选项。
	//! \param rcSrc 矩形框对象[in]。
	//! \return BBOX URL查询选项。
	//! \remarks 格式为 BBOX=-165.270004272461,-54.7538909912109,177.130187988281,83.1083221435547&amp。
	//! \attention 。
	UGString GetBBoxURLValue(const UGRect2D& rcSrc) const;



public:
	//! \brief 请求地图时的bounds	
	UGRect2D m_RcBound;
protected:
	//! \brief 扁平化的所有的WMS图层列表。
	UGWebLayersInfos m_arrAllLayers;

	//! \brief 可见的WMS图层列表。
	UGWebLayersInfos m_arrVisibleLayers;

	UGbool m_bTransparent;

 
private:
	//! \brief WMS图层树。
	WMSLayer* m_pWMSlayer;
	//! \brief 存储图层所支持的样式
	//! \remarks 备注信息。
	UGArray<UGString> m_arrWMSStyle;
    //! \brief 设置图层的style
	UGDict<UGString,UGString> m_arrRequestWMSStyle;
	//! \brief 请求地图时指定的地图宽	
	UGint m_dWidth;
	//! \brief 请求地图时指定的地图高
	UGint m_dHeight ;

	
	
};

}
#endif // !defined(UGDATASETRASTERWMS_H)

