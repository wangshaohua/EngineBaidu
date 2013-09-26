//////////////////////////////////////////////////////////////////////////
//                    _   _   ____   ____                    
//   Project         | | | | / ___) / ___)                   
//                   | | | || | __ | |                       
//                   | |_| || |_\ || \___                    
//                    \____/ \____| \ ___)     6.0           
//                                                           
//!  \file headerfile.h
//!  \brief Class 。
//!  \details 。
//!  \author 数据转换组。
//!  \attention 
//!   Copyright (c) 1996-2010 SuperMap Software Limited Company.  <br> 
//!   All Rights Reserved.
//!  \version 6.0

#if !defined(AFX_UGDATASETRASTERWEB_H__7681AA6D_BDCB_4A18_A9A3_EC39CEBB7BE4__INCLUDED_)
#define AFX_UGDATASETRASTERWEB_H__7681AA6D_BDCB_4A18_A9A3_EC39CEBB7BE4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Engine/UGDatasetRaster.h"
namespace UGC
{
	class UGMapServiceStub;
	class UGMapServiceParams;
	class UGLocalCacheManager;
	class UGMapCacheFile;
	struct UGDownloadTileInfo;
	struct UGDataChangeInfo;
	class  UGTile;
	struct UGImageData;
	typedef UGArray<UGTile*> UGTiles;

	typedef void (UGSTDCALL * DownloadResponseFunc) (UGDownloadTileInfo result, UGlong pWnd);

	typedef void (UGSTDCALL * DataChangedProc) (const UGDataChangeInfo& ChangeInfo, UGlong pWnd);

	typedef void (UGSTDCALL * RequestFinishedProc) (UGlong pWnd);

	class ENGINE_API UGDatasetRasterWeb : public UGDatasetRaster  
	{
	public:
		UGDatasetRasterWeb();
		virtual ~UGDatasetRasterWeb();

	public:

		//! \brief 打开数据集
		virtual UGbool Open() = 0;

		//! \brief 关闭数据集
		virtual void Close() = 0;	

		//! \brief 判断是否是网络栅格数据集
		virtual UGbool IsWebRaster();

		//!	\brief	设置缓存文件的位置
		virtual UGbool SetBufferPath(const UGString& strBuffPath);

		//! \brief 获取缓存文件的位置
		virtual UGString GetBufferPath() const;

		//! \brief 设置显示图层
		//! \arrLayers param[in] 显示的图层
		//                       GoogleMaps设置显示的地图类型，只允许设置一种类型
		//                       wms设置可见图层
		//                       超图云服务预留，设置服务名称
		virtual UGbool SetVisibleLayers(const UGArray<UGString>& arrLayers);

		//! \brief 获取当前设置的显示图层
		virtual void GetCurrentVisibleLayers(UGArray<UGString>& arrLayers) const;

		//! \brief 设置数据集投影，仅供网络数据源打开的时候调用
		virtual UGbool SetPrjCoordSys(const UGPrjCoordSys &PrjCoordSys);

		//! \brief 设置回调函数
		virtual void SetDownloadResponseFunc(DownloadResponseFunc pFunc, UGlong pWnd) = 0;

		//! \brief 设置请求参数
		//! \dScale param[in] 当前地图的比例尺
		//! \bound param[in] 当前地图范围
		//! \bCallBack 本地瓦片存在时是否回调
		virtual UGbool Request(const UGdouble& dScale, const UGRect2D& bound, UGbool bCallBack = TRUE) = 0;

// 		//! \brief 获取单个瓦片数据
// 		//! \tile param[in,out] 单个瓦片数据
// 		virtual UGbool GetTileData(UGTile& tile){return FALSE;}
// 
// 		//! \brief 根据传入的TileData中的比例尺，获取Tile的地理范围和像素范围
// 		//! \tile param[in,out] 单个瓦片信息
// 		virtual void GetTileInfo(UGTile& tileData){return ;}

		//! \brief 通过比例尺转换瓦片边长对应的地理大小
		//! \param dMapScale 地图比例尺
		virtual UGSize2D GetTileMPSize(UGdouble dMapScale) = 0;

		//! \brief 获取瓦片的DP大小
		virtual UGSize GetTileSize() = 0;

// 		//! \brief 判断一次请求是否已经完成，Request之后调用
// 		//! \return 完成返回True，否则返回False
 		virtual UGbool IsComplete() = 0;

		//! \brief 返回所有的比例尺级别
		virtual const UGArray<UGdouble> GetScales() const = 0;	

		//! \brief 设置取到数据并把数据区域的外接矩形返回给用户的回调函数
		//! \param pFunc 回调函数[in]。
		//! \param pWnd 句柄[in]。
		virtual void SetDataChangedFunc(DataChangedProc pFunc, UGlong pWnd) = 0;

// 		//! \brief 设置告诉用户下载完成的回调函数
// 		//! \param pFunc 回调函数[in]。
// 		//! \param pWnd 句柄[in]。
// 		virtual void SetRequestFinishedFunc(RequestFinishedProc pFunc,UGlong pWnd){return ;}

		//! \brief 根据范围和比例尺，查询记录集。
		//! \param rcMapBounds [in] 范围。
		//! \param dScale [in] 比例尺。
		//! \return 返回范围内所有瓦片的信息 
		virtual UGTiles* QueryWithBounds(const UGRect2D& rcMapBounds, UGdouble dScale) const = 0;

		//##ModelId=483BB70C012C
		//! \brief 获取显示的影像块。
		//! \param rcView 获取的显示的影像块大小[in]。
		//! \param nDeviceWidth 设备宽度[in]。
		//! \param nDeviceHeight 设备高度[in]。
		//! \return 返回显示的影像块。
		virtual UGImgBlock* GetViewBlock(const UGRect2D& rcView, UGint nDeviceWidth, UGint nDeviceHeight, UGbool &bFinished) = 0;	

		//! \brief 加载缓存影像块数据
		//! \tile param 单个瓦片信息[in]
		//! \return 瓦片的ImageData
		virtual UGImageData* LoadTileImageData(const UGTile& tile) = 0;

		//! \brief 获取最接近的比例尺
		//! \param dScale 传入比例尺
		//! \return 返回最接近的固定比例尺
		virtual UGdouble ScaleToNearFixScale(UGdouble dScale) = 0;

		//! \brief 计算一个范围扩张几个瓦片之后的范围
		//! \param dMapScale 地图比例尺
		//! \param rcMapBounds 地图范围
		//! \param nExtTileSize 扩张瓦片的个数
		//! \return 扩张之后的地图范围
		virtual UGRect2D ComputeTilesBounds(UGdouble dMapScale, const UGRect2D& rcMapBounds, UGint nExtTileSize = 1) = 0;

		//! \brief 获取当前服务瓦片DP-->LP的转换比率
		virtual UGdouble GetCoordRatio() = 0;

		//! \brief 根据范围和比例尺，判断该范围内的瓦片是否全都存在。
		//! \param rcMapBounds [in] 范围。
		//! \param dScale [in] 比例尺。
		//! \return 
		virtual UGbool IsAllTilesExist(const UGRect2D& rcMapBounds, UGdouble dScale) const = 0;

		//! \brief 获取本地缓存的版本号(嵌入式使用)
		virtual UGint GetCacheVersion() const = 0;

		//! \brief 获取当前服务SCI中DP-->LP的转换比率(嵌入式使用，主要是使用GetCoordRatio有误差)
		virtual UGdouble GetCacheCoordRatio() = 0;

	public:
		//! \brief 设置是否可以被透明
		void SetCanBeTransparent(UGbool bTransparent){m_bCanBeTransparent = bTransparent;}

		//! \brief 获取是否可以被透明
		UGbool GetCanBeTransparent(){return m_bCanBeTransparent;}

	protected:
		//! \brief 保存数据源时取的参数
		virtual UGString ParamsToString() const;

		//! \brief 打开数据源时设置参数
		virtual void StringToParams(const UGString& strParams);

		//! \brief 设置网络下载管理插件
		void SetMapServiceStub(UGMapServiceStub* pMapServiceStub);

		//! \brief 设置网络服务参数
		void SetMapServiceParams(UGMapServiceParams* pMapServiceParams);

		//! \brief 网络下载管理插件
		UGMapServiceStub* m_pMapServiceStub;

		//! \brief 网络服务参数
		UGMapServiceParams* m_pMapServiceParams;

		//! \brief 缓存文件的位置
		UGString m_strBufferPath;

		//! \brief 本地缓存管理器
		UGLocalCacheManager* m_pLocalManager;

		UGbool m_bCanBeTransparent;
	};

}

#endif // !defined(AFX_UGDATASETRASTERWEB_H__7681AA6D_BDCB_4A18_A9A3_EC39CEBB7BE4__INCLUDED_)