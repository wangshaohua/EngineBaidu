////////////////////////////////////////////////////////////////////////////////
//!  Project UGC
//! \file UGGeoSpatialDownloadRequest.h
//! \author UGC Group
//! \brief 地理空间下载请求生成类，用于生成向iServer发送的Http URL请求。
//! \attention 目前仅在三维类库中使用过
//!  Copyright (c)copy;  1997-2009 SuperMap Software Co., Ltd.<br> 
//!  All Rights Reserved.
//! \version 6.0
//! \date 2009年8月28日
////////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_UGGEOSPATIALDOWNLOADREQUEST_H__0BCDA7DE_B5FB_46A1_9A81_7B7EAABA3E36__INCLUDED_)
#define AFX_UGGEOSPATIALDOWNLOADREQUEST_H__0BCDA7DE_B5FB_46A1_9A81_7B7EAABA3E36__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Stream/ugexports.h"
#include "Stream/ugdefs.h"
#include "Stream/ugplatform.h"
#include "Toolkit/UGTextCodec.h"
#include "Geometry/UGDataCodec.h"

namespace UGC
{
	//! \brief class UGGeoSpatialDownloadRequest
	//! \brief 地理空间下载请求生成类
class NETTOOLKIT_API UGGeoSpatialDownloadRequest
{
public:
	//! \brief 请求数据类型。
	enum UGRequestDataType
	{
		UnKnown		= 0,
		SCVB		= 1,		
		SCVD		= 2,	
		Texture     = 3,	
	};

public:
	
    //! \fn UGGeoSpatialDownloadRequest();
    //! \brief 默认构造函数
	UGGeoSpatialDownloadRequest();

    //! \fn virtual ~UGGeoSpatialDownloadRequest();
    //! \brief 默认析构函数
	virtual ~UGGeoSpatialDownloadRequest();

    //! \fn		UGbool operator==(const UGGeoSpatialDownloadRequest& request) const;
	//! \brief 重载 ==
    //! \param const UGGeoSpatialDownloadRequest& request
    //! \return	 若两个请求相等则返回true
	UGbool operator==(const UGGeoSpatialDownloadRequest& request) const;

	//! \brief 重载=。
	//! \param &request [in]。
	void operator = (const UGGeoSpatialDownloadRequest &request);

    //! \brief 通过指定文件相对于图层所在服务端的根目录路径来获取访问下载文件的http url
    //! \param const UGString& strNetPath [in] 服务端地址
    //! \param const UGString& strDataname [in] 图层名
    //! \param const UGString& strfilepath [in] 文件相对于图层根目录的路径，注意要有对应的完整文件名
    //! \param UGint ndataversion = 0 [in] 请求文件数据的版本，默认是0
    //! \param const UGString& strUsername = "" [in] 用户名，默认为空
    //! \param const UGString& strPassword = "" [in] 密码，默认是空
    //! \param UGfloat fserviceVersion = 1.0f [in] 服务端版本
	//! \remarks 请求kml或者模型纹理时使用。对于kml而言，文件名和图层名是一个!
    //! \return	返回http url 请求
	static UGString UrlGetDataByPath(const UGString& strNetPath, const UGString& strDataname, const UGString& strfilepath, UGint ndataversion = 0, const UGString& strUsername = _U(""), const UGString& strPassword = _U(""), UGfloat fserviceVersion = 1.0f);

    //! \fn		static UGString UrlGetDataByIndex(const UGString& strNetPath, const UGString& strdataname, UGint nlevel, UGint nRow, UGint nCol, UGint ndataversion = 0, const UGString& strfileExtent = "", const UGString& strUsername = "", const UGString& strPassword = "", UGfloat fserviceVersion = 1.0f);
    //! \brief 通过指定图层名和索引来构建数据的 http url 请求
	//! \param const UGString& strNetPath [in] 服务端地址
	//! \param const UGString& strdataname [in] 图层名
    //! \param UGint nlevel [in] 索引，层数
    //! \param UGint nRow [in] 索引，行号
    //! \param UGint nCol [in] 索引，列号
    //! \param UGint ndataversion = 0 [in] 请求文件数据的版本，默认是0
    //! \param const UGString& strfileExtent = "" [in] 文件扩展名，默认为空，即默认去找png bil sgm后缀名的数据
	//! \param const UGString& strUsername = "" [in] 用户名，默认为空
	//! \param const UGString& strPassword = "" [in] 密码，默认是空
	//! \param UGfloat fserviceVersion = 1.0f [in] 服务端版本
	//! \param UGDataCodec::CodecType eCodecType = UGDataCodec::encNONE [in] 数据压缩方式
    //! \remarks 请求纹理数据、地形数据、模型索引数据时使用
    //! \return	返回http url 请求
	static UGString UrlGetDataByIndex(const UGString& strNetPath, const UGString& strdataname, UGint nlevel, UGint nRow, UGint nCol, const UGString& strfileExtent, UGint ndataversion = 0, 
		UGDataCodec::CodecType eCodecType = UGDataCodec::encNONE, const UGString& strUsername = _U(""), const UGString& strPassword = _U(""), UGfloat fserviceVersion = 1.0f);

    //! \fn		static UGString GetDownloadUrlByBounds(const UGString& strNetPath, const UGString& strlayername, const UGString& strdatatype,		UGint nlevel, UGdouble left, UGdouble top, UGdouble right, UGdouble bottom,UGint ndataversion = 0, const UGString& strfileExtent = "", UGint npicWidth = 0, UGint npicHeight = 0, const UGString& strUsername = "", const UGString& strPassword = "", UGfloat fserviceVersion = 1.0f);
    //! \brief 通过指定图层名和经纬度范围来构建数据的 http url 请求
	//! \param const UGString& strNetPath [in] 服务端地址
	//! \param const UGString& strlayername [in] 图层名
	//! \param const UGString& strdatatype [in] 请求数据的类型分为IMG DEM SGM三种
    //! \param UGint nlevel [in] 索引，层数
    //! \param UGdouble left [in] 西经
    //! \param UGdouble top [in] 北纬
    //! \param UGdouble right [in] 东经
    //! \param UGdouble bottom [in] 南纬
	//! \param UGint ndataversion = 0 [in] 请求文件数据的版本，默认是0
	//! \param const UGString& strfileExtent = "" [in] 文件扩展名，默认为空，即默认去找png bil sgm后缀名的数据
    //! \param UGint npicWidth = 0 [in] 数据x方向采样点，
	//! 例如对于图片数据就是像素，对于地形数据就是每块网格所需高程点的个数，默认是0，对于图片数据就是256 地形数据就是32
    //! \param UGint npicHeight = 0 [in] 数据y方向采样点
	//! \param const UGString& strUsername = "" [in] 用户名，默认为空
	//! \param const UGString& strPassword = "" [in] 密码，默认是空
	//! \param UGfloat fserviceVersion = 1.0f [in] 服务端版本
    //! \remarks 请求纹理数据、地形数据、模型索引数据时使用
    //! \return	返回http url 请求
	static UGString GetDownloadUrlByBounds(const UGString& strNetPath, const UGString& strlayername, const UGString& strdatatype,
		UGdouble left, UGdouble top, UGdouble right, UGdouble bottom,UGint ndataversion = 0, const UGString& strfileExtent = _U(""), UGint npicWidth = 0, UGint npicHeight = 0, const UGString& strUsername = _U(""), const UGString& strPassword = _U(""), UGfloat fserviceVersion = 1.0f);
	
	//! \fn		static UGString UrlGetDataConfig(const UGString& strNetPath, const UGString& strdataName, const UGString& strUsername = "", const UGString& strPassword = "", UGfloat fserviceVersion = 1.0f);
	//! \brief 构建服务端发布的数据配置信息http url 请求
	//! \param const UGString& strNetPath [in] 服务端地址
	//! \param const UGString& strdataName [in] 指定场景的名字
	//! \param const UGString& strUsername = "" [in] 用户名，默认为空
	//! \param const UGString& strPassword = "" [in] 密码，默认是空
	//! \param UGfloat fserviceVersion = 1.0f [in] 服务端版本
	//! \remarks 请求数据的配置信息sci3d sct scm文件时使用
	//! \return	返回http url 请求
	
	// 干掉 UGint nLevel [in] 针对模型的分层取scm，其他类型数据用不到传空字符串。
	// 目前模型也不需要传了，各个层数的模型图层都有独立的图层名
	static UGString UrlGetDataConfig(const UGString& strNetPath, const UGString& strdataName, const UGString& strUsername = _U(""), const UGString& strPassword = _U(""), UGfloat fserviceVersion = 1.0f);

    //! \fn		static UGString UrlGetLayerListInfo(const UGString& strNetPath, const UGString& strSceneName, const UGString& strUsername = "", const UGString& strPassword = "", UGfloat fserviceVersion = 1.0f);
    //! \brief 构建服务端发布的图层列表信息http url请求
	//! \param const UGString& strNetPath [in] 服务端地址
	//! \param const UGString& strSceneName [in] 指定场景的名字
	//! \param const UGString& strUsername = "" [in] 用户名，默认为空
	//! \param const UGString& strPassword = "" [in] 密码，默认是空
	//! \param UGfloat fserviceVersion = 1.0f [in] 服务端版本
	//! \return	返回http url 请求
	static UGString UrlGetLayerListInfo(const UGString& strNetPath, const UGString& strSceneName, const UGString& strUsername = _U(""), const UGString& strPassword = _U(""), UGfloat fserviceVersion = 1.0f);

    //! \fn		static UGString UrlGetLayerInfo(const UGString& strNetPath, const UGString& strSceneName, const UGString& strlayername, const UGString& strUsername = "", const UGString& strPassword = "", UGfloat fserviceVersion = 1.0f);
    //! \brief 构建服务端发布的指定图层的图层信息http url 请求
	//! \param const UGString& strNetPath [in] 服务端地址
	//! \param const UGString& strSceneName [in] 指定场景的名字
	//! \param const UGString& strlayername [in] 图层名
	//! \param const UGString& strUsername = "" [in] 用户名，默认为空
	//! \param const UGString& strPassword = "" [in] 密码，默认是空
	//! \param UGfloat fserviceVersion = 1.0f [in] 服务端版本
	//! \return	返回http url 请求
	static UGString UrlGetLayerInfo(const UGString& strNetPath, const UGString& strSceneName, const UGString& strlayername, const UGString& strUsername = _U(""), const UGString& strPassword = _U(""), UGfloat fserviceVersion = 1.0f);

	//! \brief 构建服务端发布的指定图层的图层风格信息http url 请求
	//! \param const UGString& strNetPath [in] 服务端地址
	//! \param const UGString& strSceneName [in] 指定场景的名字
	//! \param const UGString& strlayername [in] 图层名
	//! \param const UGString& strUsername = "" [in] 用户名，默认为空
	//! \param const UGString& strPassword = "" [in] 密码，默认是空
	//! \param UGfloat fserviceVersion = 1.0f [in] 服务端版本
	//! \return	返回http url 请求
	static UGString UrlGetLayerStyleInfo(const UGString& strNetPath, const UGString& strSceneName, const UGString& strlayername, const UGString& strUsername = _U(""), const UGString& strPassword = _U(""), UGfloat fserviceVersion = 1.0f);

	//! \fn		static UGString UrlGetSceneListInfo(const UGString& strNetPath, const UGString& strUsername = "", const UGString& strPassword = "", UGfloat fserviceVersion = 1.0f);
	//! \brief 构建服务端发布的场景列表http url请求
	//! \param const UGString& strNetPath [in] 服务端地址
	//! \param const UGString& strUsername = "" [in] 用户名，默认为空
	//! \param const UGString& strPassword = "" [in] 密码，默认是空
	//! \param UGfloat fserviceVersion = 1.0f [in] 服务端版本
	//! \return	返回http url 请求
	static UGString UrlGetSceneListInfo(const UGString& strNetPath, const UGString& strUsername = _U(""), const UGString& strPassword = _U(""), UGfloat fserviceVersion = 1.0f);

	//! \fn		static UGString UrlGetSceneInfo(const UGString& strNetPath, const UGString& strSceneName, const UGString& strUsername = "", const UGString& strPassword = "", UGfloat fserviceVersion = 1.0f);
	//! \brief 构建服务端发布的指定场景信息 http url 请求
	//! \param const UGString& strNetPath [in] 服务端地址
	//! \param const UGString& strSceneName [in] 指定场景的名字
	//! \param const UGString& strUsername = "" [in] 用户名，默认为空
	//! \param const UGString& strPassword = "" [in] 密码，默认是空
	//! \param UGfloat fserviceVersion = 1.0f [in] 服务端版本
	//! \return	返回http url 请求
	static UGString UrlGetSceneInfo(const UGString& strNetPath, const UGString& strSceneName, const UGString& strUsername = _U(""), const UGString& strPassword = _U(""), UGfloat fserviceVersion = 1.0f);

    //! \fn static UGString UrlGetModelIndex(const UGString& strNetPath, const UGString& strdataname, const UGString& strUsername = "", const UGString& strPassword = "", UGfloat fserviceVersion = 1.0f);
    //! \brief 构建获取模型索引的http url 请求
	//! \param const UGString& strNetPath [in] 服务端地址
	//! \param const UGString& strdataname [in] 图层名
	//! \param const UGString& strUsername = "" [in] 用户名，默认为空
	//! \param const UGString& strPassword = "" [in] 密码，默认是空
	//! \param UGfloat fserviceVersion = 1.0f [in] 服务端版本
	//! \return	返回http url 请求
	static UGString UrlGetModelIndex(const UGString& strNetPath, const UGString& strdataname, const UGString& strUsername = _U(""), const UGString& strPassword = _U(""), UGfloat fserviceVersion = 1.0f);

	//! \brief 构建获取矢量索引的http url 请求
	//! \param const UGString& strNetPath [in] 服务端地址
	//! \param const UGString& strdataname [in] 图层名
	//! \param const UGString& strUsername = "" [in] 用户名，默认为空
	//! \param const UGString& strPassword = "" [in] 密码，默认是空
	//! \param UGfloat fserviceVersion = 1.0f [in] 服务端版本
	//! \return	返回http url 请求
	static UGString UrlGetVectorIndex(const UGString& strNetPath, const UGString& strdataname, const UGString& strUsername = _U(""), const UGString& strPassword = _U(""), UGfloat fserviceVersion = 1.0f);

	//! \brief 构建获取服务端给客户端缓存加密的密码服务的url
	//! \param const UGString& strNetPath [in] 服务端地址
	//! \param const UGString& strUsername = "" [in] 用户名，默认为空
	//! \param const UGString& strPassword = "" [in] 密码，默认是空
	//! \param UGfloat fserviceVersion = 1.0f [in] 服务端版本
	//! \return	返回http url 请求
	static UGString UrlGetCacheAccessKey(const UGString& strNetPath, const UGString& strUsername = _U(""), const UGString& strPassword = _U(""), UGfloat fserviceVersion = 1.0f);

	// 预留接口根据模型id或者索引来下载模型sgm以及纹理数据
//	static UGString UrlGetModelDataByID();

    //! \fn		static UGString UrlGetDataVersionByIndex(const UGString& strNetPath, const UGString& strdataname, UGint nlevel, UGint nCol, UGint nRow, const UGString& strfileExtent = "", const UGString& strUsername = "", const UGString& strPassword = "", UGfloat fserviceVersion = 1.0f);
    //! \brief 构建获取指定图层名和索引的数据的版本 http url请求
	//! \param const UGString& strNetPath [in] 服务端地址
	//! \param const UGString& strdataname [in] 图层名
	//! \param UGint nlevel [in] 索引，层数
	//! \param UGint nRow [in] 索引，行号
	//! \param UGint nCol [in] 索引，列号
	//! \param const UGString& strfileExtent = "" [in] 文件扩展名，默认为空，即默认去找png bil sgm后缀名的数据
	//! \param const UGString& strUsername = "" [in] 用户名，默认为空
	//! \param const UGString& strPassword = "" [in] 密码，默认是空
	//! \param UGfloat fserviceVersion = 1.0f [in] 服务端版本
	//! \remarks 请求纹理数据、地形数据、模型索引数据版本号时使用
	//! \return	返回http url 请求

	// 干掉 const UGString& strdatatype [in] 请求数据的类型分为IMG DEM SGM三种
	// 与文件扩展名重复
	static UGString UrlGetDataVersionByIndex(const UGString& strNetPath, const UGString& strdataname,
		UGint nlevel, UGint nRow, UGint nCol, const UGString& strfileExtent, const UGString& strUsername = _U(""), const UGString& strPassword = _U(""), UGfloat fserviceVersion = 1.0f);


    //! \fn		static UGString GetDataVersionByBoundsUrl(const UGString& strNetPath, const UGString& strlayername, const UGString& strdatatype,		UGint nlevel, UGdouble left, UGdouble top, UGdouble right, UGdouble bottom, const UGString& strfileExtent = "", UGint npicWidth = 0, UGint npicHeight = 0, const UGString& strUsername = "", const UGString& strPassword = "", UGfloat fserviceVersion = 1.0f);
    //! \brief 构建获取指定地理范围和图层名的数据的版本的 http url 请求
	//! \param const UGString& strNetPath [in] 服务端地址
	//! \param const UGString& strlayername [in] 图层名
	//! \param const UGString& strdatatype [in] 请求数据的类型分为IMG DEM SGM三种
	//! \param UGint nlevel [in] 索引，层数
	//! \param UGdouble left [in] 西经
	//! \param UGdouble top [in] 北纬
	//! \param UGdouble right [in] 东经
	//! \param UGdouble bottom [in] 南纬
	//! \param const UGString& strfileExtent = "" [in] 文件扩展名，默认为空，即默认去找png bil sgm后缀名的数据
	//! \param UGint npicWidth = 0 [in] 数据x方向采样点，
	//! 例如对于图片数据就是像素，对于地形数据就是每块网格所需高程点的个数，默认是0，对于图片数据就是256 地形数据就是32
	//! \param UGint npicHeight = 0 [in] 数据y方向采样点
	//! \param const UGString& strUsername = "" [in] 用户名，默认为空
	//! \param const UGString& strPassword = "" [in] 密码，默认是空
	//! \param UGfloat fserviceVersion = 1.0f [in] 服务端版本
	//! \remarks 请求纹理数据、地形数据、模型索引数据时使用
	//! \return	返回http url 请求
	static UGString GetDataVersionByBoundsUrl(const UGString& strNetPath, const UGString& strlayername, const UGString& strdatatype,
		UGdouble left, UGdouble top, UGdouble right, UGdouble bottom, const UGString& strfileExtent = _U(""), UGint npicWidth = 0, UGint npicHeight = 0, const UGString& strUsername = _U(""), const UGString& strPassword = _U(""), UGfloat fserviceVersion = 1.0f);


//! \brief 指定期望文件下载到本地的全路径名，或者大文件缓存的路径名
	UGString m_strFileName;

//! \brief http url 请求
	UGString m_strUrl;

//! \brief 标识该请求是否已经下载成功
	UGbool m_bIsDownload;

//! \brief 文件的扩展名或者文件在大文件缓存中的索引名
	UGString m_strFileExtend;

//! \brief 当客户端获取每一个服务地址的信任后每次请求需要带上的id值标识，若没有就为空。
	static UGDict<UGString, UGString> ms_strJsessionIDs;	// 主键是服务地址，值是JsessionID

//! \brief 该请求对应的数据块的层行列号。
	UGint m_nLevel;
	UGint m_nRow;
	UGint m_nCol;
	UGRequestDataType m_dataType;
};

}

#endif // !defined(AFX_UGGEOSPATIALDOWNLOADREQUEST_H__0BCDA7DE_B5FB_46A1_9A81_7B7EAABA3E36__INCLUDED_)

