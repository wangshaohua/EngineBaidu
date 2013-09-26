
#if !defined(AFX_UGVECTORPLUGIN_H__E1BF20D3_7163_4C55_A157_F002C0B829AF__INCLUDED_)
#define AFX_UGVECTORPLUGIN_H__E1BF20D3_7163_4C55_A157_F002C0B829AF__INCLUDED_

#include "Stream/ugdefs.h"
#include "FileParser/UGVectorCacheParamater.h"
#include "FileParser/UGExchangeFileType.h"
#include "FileParser/UGRecordsetTile.h"
#include "OGDC/OgdcQueryDef.h"
#ifndef OS_ANDROID
#include "NetToolkit/UGDownloadQueue.h"
#include "Base3D/UGTextureData.h"
#include "Geometry/UGDataCodec.h"
#include "Geometry/UGGeometry.h"
#include "Geometry/UGFeature.h"
#endif


#ifdef WIN32
#include <Windows.h>
#define VECTOREXPORT __declspec(dllexport)
#else
#define VECTOREXPORT
#endif

using namespace UGC;
namespace UGC
{	
	typedef void (UGSTDCALL * DownloadResponseFunc) (UGDownloadTileInfo result, UGlong pWnd);
}

namespace UGC
{	
	//! \breif 影像插件类型
	enum PluginVectorClass 
	{
		PV_UNKNOWN,
		PV_SCV
	};	
#ifndef OS_ANDROID
	class FILEPARSER_API UGVectorPlugin
	{
	public:
		UGVectorPlugin(){m_strPassword = _U("");}
		virtual ~UGVectorPlugin(){}
	public:
		//! \brief 打开文件。
		//! \param  strFileName,文件名。[in]
		//! \param  nFlags, 打开方式，如只读，共享等，参看CFile的标志。[in]
		//! \param strPassword 打开密码 [in]
		virtual UGbool Open(const UGString& strFileName, UGuint nFlags, const UGString& strPassword) = 0;

		//! \brief 关闭文件。
		virtual void Close() = 0;

		//! \return 插件类型
		virtual PluginVectorClass GetPluginClass() { return m_nPluginClass; }

		//! \brief  输出插件的名称，比如 ECW 文件插件.
		//! \param  strName,字符串,函数外分配空间.[out]
		//! \param  nMaxLength 字符串长度[in]
		virtual UGbool GetPluginName(UGchar* strName, int nMaxLength) = 0;

		UGVectorCacheParamater& GetCacheParamater() {return m_CacheParameter;}

		// 导航切片查询功能
		virtual UGRecordsetTile* Query(OgdcQueryDef queryDef) = 0;

		//! \brief 设置回调函数
		//! \remarks 三维使用的啊！！！
		virtual void SetDownloadResponseFunc(DownloadResponseFunc pFunc,UGlong pWnd){return; }

		//! \brief 判断一次请求是否已经完成，Request之后调用
		//! \remarks 和IsFinished()不一样  IsFinished()是判断GetViewBlock()加载的是否完全
		//! \return 完成返回True，否则返回False
		virtual UGbool IsCompleteRequest() {return TRUE;}

		//! \brief 设置请求参数
		//! \dScale param[in] 当前地图的比例尺
		//! \bound param[in] 当前地图范围
		virtual UGbool Request(const UGdouble& dScale, const UGRect2D& bound, UGbool bCallBack = TRUE){return FALSE;}

		//! \brief根据行列号获取几何数据
		//! \brief nRow[in]请求行号
		//! \brief nCol[in]请求列号
		//! \brief arrGeometry[out] 获取Geometry数组
		//! \return 查询成功返回TRUE，否则为FALSE
		virtual UGbool GetBlockAt(UGint nRow, UGint nCol, UGArray<UGGeometry*>& arrGeometry) = 0;

		//! \brief根据行列号获取Features数据
		//! \brief nRow[in]请求行号
		//! \brief nCol[in]请求列号
		//! \brief arrFeatures[out] 获取arrFeatures数组
		//! \return 查询成功返回TRUE，否则为FALSE
		virtual UGbool GetBlockAt(UGint nRow, UGint nCol, UGArray<UGFeature*>& arrFeatures) = 0;

		//! \brief 获取某一个块的Bounds
		//! \brief nRow[in] 块的行号
		//! \brief nCol[in] 聊的列号
		//! \brief recBounds [out] 块的bounds
		//! \return 获取成功返回TRUE，否则返回FALSE
		virtual UGbool GetBlockBounds(UGint nRow, UGint nCol, UGRect2D& recBounds) = 0;

		//! \brief 获取某一个块的包围盒
		//! \brief nRow[in] 块的行号
		//! \brief nCol[in] 聊的列号
		//! \brief boundingBox [out] 块的包围盒
		//! \return 获取成功返回TRUE，否则返回FALSE
		virtual UGbool GetBlockBoundingBox(UGint nRow, UGint nCol, UGBoundingBox& boundingBox) = 0;

		//! \brief获取字段信息
		virtual UGbool GetFieldInfos(UGFieldInfos& fieldInfos) = 0;

		//! \brief 获取纹理
		//! \param res[out] 纹理状态
		//! \param strPath[in] 纹理路径，也就是纹理名称		
		//! \param nLodLevel[in] 纹理层数
		//! \param bNeedUnCompress[in] 读取的数据是否需要解压缩
		//! \param nTileRow 纹理所在的行
		//! \param nTileCol 纹理所在的列
		//! return 成功的话返回一个UGTextureData类型的指针，否则返回空
		//! remarks 三维使用
		virtual UGTextureData* GetTextureData(UGint& res, UGString strTexPath, UGint nLodLevel, UGbool bNeedUnCompress = TRUE, UGint nTileRow = 0, UGint nTileCol = 0) = 0;

		//! brief 获取纹理的临时路径，对于GIF纹理,是将图片写到临时目录，然后从本地临时目录读取纹理数据
		virtual UGString GetTextureTempPath(const UGString& strTexture, UGint nTileRow = 0, UGint nTileCol = 0) = 0;	

		//! \brief 下载数据
		virtual  void DownloadQueueBeginDownLoad() = 0;

		//! \brief 获取矢量文件下载队列
		virtual UGDownloadQueue& GetVectorDataDownloadQueue() = 0;
		virtual UGDownloadQueue& GetVectorAtrriDownloadQueue() = 0;
		//! \brief 获取图层数据下载进度
		virtual	UGfloat GetDataStreamingProgress() = 0;

	protected:
		//! \brief 密码
		UGString m_strPassword;

		//! \brief 当前矢量插件类型
		PluginVectorClass m_nPluginClass;	

		UGVectorCacheParamater m_CacheParameter;
	};
#else
class FILEPARSER_API UGVectorPlugin
{
public:
	UGVectorPlugin(){m_strPassword = _U("");}
	virtual ~UGVectorPlugin(){}
public:
	//! \brief 打开文件。
	//! \param  strFileName,文件名。[in]
	//! \param  nFlags, 打开方式，如只读，共享等，参看CFile的标志。[in]
	//! \param strPassword 打开密码 [in]
	virtual UGbool Open(const UGString& strFileName, UGuint nFlags, const UGString& strPassword) = 0;

	//! \brief 关闭文件。
	virtual void Close() = 0;

	//! \return 插件类型
	virtual PluginVectorClass GetPluginClass() { return m_nPluginClass; }

	//! \brief  输出插件的名称，比如 ECW 文件插件.
	//! \param  strName,字符串,函数外分配空间.[out]
	//! \param  nMaxLength 字符串长度[in]
	virtual UGbool GetPluginName(UGchar* strName, int nMaxLength) = 0;

	//! \brief获取字段信息
	virtual UGbool GetFieldInfos(UGFieldInfos& fieldInfos) = 0;

	UGVectorCacheParamater& GetCacheParamater() {return m_CacheParameter;}

	// 导航切片查询功能
	virtual UGRecordsetTile* Query(OgdcQueryDef queryDef) = 0;
protected:
	//! \brief 密码
	UGString m_strPassword;

	//! \brief 当前矢量插件类型
	PluginVectorClass m_nPluginClass;	

	UGVectorCacheParamater m_CacheParameter;
};

#endif


	// 插件需要实现一个导出的全局函数用来返回 UGVectorPlugin 派生的类。
	// 创建一个插件类，请new 一个从 UGImagePlugin 派生的类。
	extern "C" VECTOREXPORT UGVectorPlugin* CreateVectorPlugin();
}

#endif //AFX_UGVECTORPLUGIN_H__E1BF20D3_7163_4C55_A157_F002C0B829AF__INCLUDED_

