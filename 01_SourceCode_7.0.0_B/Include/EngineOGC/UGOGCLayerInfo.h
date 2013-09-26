//////////////////////////////////////////////////////////////////////////
//                    _   _   ____   ____                    
//   Project         | | | | / ___) / ___)                   
//                   | | | || | __ | |                       
//                   | |_| || |_\ || \___                    
//                    \____/ \____| \ ___)     6.0           
//                                                           
//!  \file UGOGCLayerInfo.h
//!  \brief OGC网格数据的图层的接口定义。
//!  \details 文件详细信息。
//!  \author duxiaomin。
//!  \attention 
//!   Copyright (c) 1996-2008 SuperMap Software Limited Company.  <br> 
//!   All Rights Reserved.
//!  \version 6.0
//////////////////////////////////////////////////////////////////////////

#ifndef SMWEBLAYERINFO_H
#define SMWEBLAYERINFO_H

#include "Stream/ugexports.h"
#include "Stream/ugdefs.h"
#include "Geometry/UGCRSBound.h"

namespace UGC
{
///////////////////// OGC Online Request Structs //////////////////////////
typedef struct WMSRequest
{
	
	WMSRequest()
	{
		urlGetCapbilities = _U("");
		arrFormatCapbilities.RemoveAll();
		urlGetMap = _U("");
		arrFormatMap.RemoveAll();
		urlGetFeatureInfo = _U("");
		arrFormatFeatureInfo.RemoveAll();
		urlDescribeLayer = _U("");
		arrFormatLayerDescribe.RemoveAll();
		urlGetLegendGraphic = _U("");
		arrFormatLegendGraphic.RemoveAll();
	}
	//! \brief wms的请求描述网络地址。
 	UGString urlGetCapbilities;
	//! \brief wms的Request具体的请求参数。
	UGArray<UGString> arrFormatCapbilities;
	//! \brief wms的请求地图网络地址。
	UGString urlGetMap;
	//! \brief wms的请求的地图的格式。
	UGArray<UGString> arrFormatMap;
	//! \brief wms的请求特征信息网络地址
	UGString urlGetFeatureInfo;
	//! \brief wms的请求特征信息的格式
	UGArray<UGString> arrFormatFeatureInfo;
	//! \brief wms的请求图层的地址 
	UGString	urlDescribeLayer;
	//! \brief wms的请求图层生成xml的地址
	UGArray<UGString> arrFormatLayerDescribe;
	UGString	urlGetLegendGraphic;
	UGArray<UGString> arrFormatLegendGraphic;

} WMSOLRequest;

typedef struct WFSRequest
{
	WFSRequest()
	{
		urlGetCapabilitiesGet = _U("");
		urlGetCapabilitiesPost = _U("");
		arrFormatCapbilities.RemoveAll();
		urlDescribeFeatureTypeGet = _U("");
		urlDescribeFeatureTypePost = _U("");
		arrFormatFeatureTypeDescribe.RemoveAll();
		urlGetFeatureGet = _U("");
		urlGetFeaturePost = _U("");
		arrFormatFeature.RemoveAll();
		urlGetFeatureWithLockGet = _U("");
		urlGetFeatureWithLockPost = _U("");
		arrFormatFeatureWithLock.RemoveAll();
		urlGetGMLObjectGet = _U("");
		urlGetGMLObjectPost = _U("");
		arrFormatGMLObject.RemoveAll();
		urlLockFeatureGet = _U("");
		urlLockFeaturePost = _U("");
		arrFormatLockFeature.RemoveAll();
		urlTransactionGet = _U("");
		urlTransactionPost = _U("");
		arrFormatTransaction.RemoveAll();
	}
	//! \brief WFS的请求网络地址。
	UGString	urlGetCapabilitiesGet;
	//! \brief WFS的请求网络地址。
	UGString	urlGetCapabilitiesPost;
	//! \brief WFS的请求相应描述信息 
	UGArray<UGString> arrFormatCapbilities;
	//! \brief WFS的请求网络地址。
	UGString	urlDescribeFeatureTypeGet;
	//! \brief WFS的请求网络地址。
	UGString	urlDescribeFeatureTypePost;
	//! \brief WFS的请求相应描述信息
	UGArray<UGString> arrFormatFeatureTypeDescribe;
	//! \brief WFS的请求网络地址。
	UGString	urlGetFeatureGet;
	//! \brief WFS的请求网络地址。
	UGString	urlGetFeaturePost;
	//! \brief WFS的请求相应描述信息
	UGArray<UGString> arrFormatFeature;
	//! \brief WFS的请求网络地址。
	UGString	urlGetFeatureWithLockGet;
	//! \brief WFS的请求网络地址。
	UGString	urlGetFeatureWithLockPost;
	//! \brief WFS的请求相应描述信息
	UGArray<UGString> arrFormatFeatureWithLock;
	//! \brief WFS的请求网络地址。
	UGString	urlGetGMLObjectGet;
	//! \brief WFS的请求网络地址。
	UGString	urlGetGMLObjectPost;
	//! \brief WFS的请求相应描述信息
	UGArray<UGString> arrFormatGMLObject;
	//! \brief WFS的请求网络地址。
	UGString	urlLockFeatureGet;
	//! \brief WFS的请求网络地址。
	UGString	urlLockFeaturePost;
	//! \brief WFS的请求相应描述信息
	UGArray<UGString> arrFormatLockFeature;
	//! \brief WFS的请求网络地址。
	UGString	urlTransactionGet;
	//! \brief WFS的请求网络地址。
	UGString	urlTransactionPost;
	//! \brief WFS的请求相应描述信息
	UGArray<UGString> arrFormatTransaction;
} WFSOLRequest;

typedef struct WCSRequest
{
	WCSRequest()
	{
		urlGetCapbilitiesGet = _U("");
		urlGetCapbilitiesPost = _U("");
		arrFormatCapbilities.RemoveAll();
		urlDescribeCoverageGet = _U("");
		urlDescribeCoveragePost = _U("");
		arrFormatCoverageDescribe.RemoveAll();
		urlGetCoverageGet = _U("");
		urlGetCoveragePost = _U("");
		arrFormatCoverage.RemoveAll();
	}
	//! \brief WCS的请求网络地址。
	UGString urlGetCapbilitiesGet;
	//! \brief WCS的请求网络地址。
	UGString urlGetCapbilitiesPost;
	//! \brief WCS的请求相应描述信息
	UGArray<UGString> arrFormatCapbilities;
	//! \brief WCS的请求网络地址。
	UGString urlDescribeCoverageGet;
	//! \brief WCS的请求网络地址。
	UGString urlDescribeCoveragePost;
	//! \brief WCS的请求相应描述信息
	UGArray<UGString> arrFormatCoverageDescribe;
	//! \brief WCS的请求网络地址。
	UGString urlGetCoverageGet;
	//! \brief WCS的请求网络地址。
	UGString urlGetCoveragePost;
	//! \brief WCS的请求相应描述信息
	UGArray<UGString> arrFormatCoverage;
} WCSOLRequest;

/////////////////////// OGCLayer //////////////////////////////////////////
class ENGINEOGC_API OGCLayer
{
public:	
	//! \brief  默认的构造函数
	OGCLayer();
	//! \brief  默认的析构函数
	virtual ~OGCLayer();
public:
	// elements
	//! \brief 图层的名称。
	UGString m_strName;
	//! \brief 图层的标题。	 
	UGString m_strTitle;
	//! \brief 图层的摘要。
	UGString m_strAbstract;
	//! \brief 图层的投影。
	UGArray<UGString> m_arrCRS;
	//! \brief 图层的关健字列表
	UGStrings m_arrKeywords;
	//! \brief 图层支持的共用投影
	//! \brief 图层的范围。	
	UGRect2D m_rcLatLongBoundingBox;
	//! \brief 图层的style。 	
	UGDict<UGString,UGString> m_arrStyle;
	//! \brief WCS图层支持的空间操作。
	UGStrings m_arrInterpolations;
	//! \brief WCS图层默认支持的空间操作。
	UGString m_DefaultInterpolation;
};
//////////////////// WMSLayer  //////////////////////////////////////////
class ENGINEOGC_API WMSLayer :public OGCLayer
{
public:	
	//! \brief  默认的构造函数
	WMSLayer();
	//! \brief  默认的析构函数
	virtual ~WMSLayer();

public:
	//! \brief 获取父图层树的指针。
	WMSLayer* GetParentalLayer();	
	
	//! \brief 得到当前图层在图层树中的层次数。
	//! \return 图层的层次数。
	//! \remarks 0层为树的根，向下次递增。
	//! \attention 非平衡多叉树。
	UGint GetCurrentLevel();

	//! \brief 树的高度。
	//! \return 树的高度。
	UGint GetTotalLevel();	
	
	//! \brief 从图层树上生长一个子图层。
	//! \return 是否成功。
	void Growleaf(WMSLayer* pSubLayer);

	//! \brief 是否是叶子结点。 
	UGbool IsLeaf();
	
	//! \brief 平行化图层 。
	//! \param arrParallelLayer [in] 图层树。 
	//! \attention 只有根图层才可以平行化
	UGbool Parallelize(UGArray<WMSLayer*>& arrParallelLayer);

	//! \brief 获取父图层的信息。
	//! \param pParentLayer 父图层。[in] 
	void InheriFrom(WMSLayer* pParentLayer);
private:
	//! \brief 获取图层的层数 。
	//! \param pCurrentLayer 传进的图层。[in] 
	UGint TotalLevel(WMSLayer* pCurrentLayer);

	//! \brief 获取父图层。
	//! \param pLayer 传进的图层。[in] 
	//! \return 返回父图层的指针。
 	WMSLayer* ParentalLayer(WMSLayer* pLayer);

	//! \brief 平行化图层。
	//! \param pLayer 要平行化的图层。[in]
	//! \param arrParallelLayer 存储平行化图层的图层数组。[in]
	UGbool ParallelizeLayer(WMSLayer* pLayer, UGArray<WMSLayer*>& arrParallelLayer);

public:
    //! \brief 标示图层可见。	 
	UGbool m_bVisible;
	//! \brief 图层的范围。
 	UGCRSBounds m_arrBoundingBox;
 	//! \brief 是否可查询 
 	UGbool m_bQueryable;
	//! \brief 图层的级联     
	UGint m_nCascaded;
	//! \brief 图层的透明
	UGbool m_bOpaque;
	//! \brief 是否有子集数组
	UGbool m_bNoSubsets;
	//! \brief 像素的宽度
	UGint m_nFixedWidth;
	//! \brief 像素的高度
	UGint m_nFixedHeight;	
	//! \brief 父图层指针 
	WMSLayer* m_pParentalLayer;
	//! \brief 图层数组。
 	UGArray<WMSLayer*> m_arrSubLayer;
};

class ENGINEOGC_API UGWebLayersInfos : public UGArray<WMSLayer*>
{
public:
	//! \brief  默认的构造函数
	UGWebLayersInfos();
	//! \brief  默认的析构函数
	~UGWebLayersInfos();
};

//////////////////// WMSLayer  //////////////////////////////////////////
class ENGINEOGC_API WFSFeatureType :public OGCLayer
{
public:	
	//! \brief  默认的构造函数
	WFSFeatureType();
	//! \brief  默认的析构函数
	virtual ~WFSFeatureType();

	const WFSFeatureType& operator =(const WFSFeatureType& featureType);
	
public:    
	//! \brief 坐标投影
	//! \remarks 备注信息。
	UGString m_mainCRS;
    //! \brief 存储WFS的操作数组。
 	UGArray<UGString> m_arrOperations;
	//! \brief 存储输出的格式 。
 	UGArray<UGString> m_OutputFormats;
};

//////////////////// WMSLayer  //////////////////////////////////////////
class ENGINEOGC_API WCSCoverage :public OGCLayer
{
public:	
	//! \brief  默认的构造函数
	WCSCoverage();
	//! \brief  默认的析构函数
	virtual ~WCSCoverage();
	
public: 

	//! \brief 坐标投影
	//! \remarks 备注信息。
	UGString m_mainCRS;
};

}
//////////////////////// End WMSLayer //////////////////////////////////
#endif // !defined(SMWEBLAYERINFO_H)

