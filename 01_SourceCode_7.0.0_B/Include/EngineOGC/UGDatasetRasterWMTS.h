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

#if !defined(AFX_UGDATASETRASTERWMTS_H__7681AA6D_BDCB_4A18_A9A3_EC39CEBB7BE4__INCLUDED_)
#define AFX_UGDATASETRASTERWMTS_H__7681AA6D_BDCB_4A18_A9A3_EC39CEBB7BE4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Engine/UGDatasetRasterWeb.h"
#include "MapServiceStub/UGMapServiceStub.h"
#include "MapServiceStub/UGLocalCacheManager.h"

namespace UGC
{
	
	class ENGINEOGC_API UGDatasetRasterWMTS : public UGDatasetRasterWeb 
	{
		friend class UGDataSourceOGC;
	public:
		UGDatasetRasterWMTS();
		virtual ~UGDatasetRasterWMTS();

	public:

		//! \brief 打开数据集
		virtual UGbool Open();

		//! \brief 关闭数据集
		virtual void Close();	

		//! \brief 获取当前设置的显示图层
		virtual void GetCurrentVisibleLayers(UGArray<UGString>& arrLayers) const;

		//! \brief 设置回调函数
		virtual void SetDownloadResponseFunc(DownloadResponseFunc pFunc,UGlong pWnd);

		//! \brief 设置请求参数
		//! \dScale param[in] 当前地图的比例尺
		//! \bound param[in] 当前地图范围
		virtual UGbool Request(const UGdouble& dScale, const UGRect2D& bound, UGbool bCallBack = TRUE);

		//! \brief 通过比例尺转换瓦片边长对应的地理大小
		//! \param dMapScale 地图比例尺
		virtual UGSize2D GetTileMPSize(UGdouble dMapScale);

		//! \brief 获取瓦片的DP大小
		virtual UGSize GetTileSize();

		//! \brief 返回所有的比例尺级别
		virtual const UGArray<UGdouble> GetScales() const;

		//! \brief 判断一次请求是否已经完成，Request之后调用
		//! \return 完成返回True，否则返回False
		virtual UGbool IsComplete();

		//! \brief 设置取到数据并把数据区域的外接矩形返回给用户的回调函数
		//! \param pFunc 回调函数[in]。
		//! \param pWnd 句柄[in]。
		virtual void SetDataChangedFunc(DataChangedProc pFunc,UGlong pWnd);

		//! \brief 根据范围和比例尺，查询记录集。
		//! \param rcMapBounds [in] 范围。
		//! \param dScale [in] 比例尺。
		//! \return 返回范围内所有瓦片的信息
		virtual UGTiles* QueryWithBounds(const UGRect2D& rcMapBounds, UGdouble dScale) const;

		//##ModelId=483BB70C012C
		//! \brief 获取显示的影像块。
		//! \param rcView 获取的显示的影像块大小[in]。
		//! \param nDeviceWidth 设备宽度[in]。
		//! \param nDeviceHeight 设备高度[in]。
		//! \return 返回显示的影像块。
		virtual UGImgBlock* GetViewBlock(const UGRect2D& rcView, UGint nDeviceWidth, UGint nDeviceHeight, UGbool &bFinished);

		//! \brief 加载缓存影像块数据
		//! \tile param 单个瓦片信息[in]
		//! \return 瓦片的ImageData
		virtual UGImageData* LoadTileImageData(const UGTile& tile);

		//! \brief 获取最接近的比例尺
		//! \param dScale 传入比例尺
		//! \return 返回最接近的固定比例尺
		virtual UGdouble ScaleToNearFixScale(UGdouble dScale);

		//! \brief 计算一个范围扩张几个瓦片之后的范围
		//! \param dMapScale 地图比例尺
		//! \param rcMapBounds 地图范围
		//! \param nExtTileSize 扩张瓦片的个数
		//! \return 扩张之后的地图范围
		virtual UGRect2D ComputeTilesBounds(UGdouble dMapScale, const UGRect2D& rcMapBounds, UGint nExtTileSize = 1);

		//! \brief 获取当前服务瓦片DP-->LP的转换比率
		virtual UGdouble GetCoordRatio();

		//! \brief 根据范围和比例尺，判断该范围内的瓦片是否全都存在。
		//! \param rcMapBounds [in] 范围。
		//! \param dScale [in] 比例尺。
		//! \return 
		virtual UGbool IsAllTilesExist(const UGRect2D& rcMapBounds, UGdouble dScale) const;

		//! \brief 获取本地缓存的版本号(嵌入式使用)
		virtual UGint GetCacheVersion() const;

		//! \brief 获取当前服务SCI中DP-->LP的转换比率(嵌入式使用，主要是使用GetCoordRatio有误差)
		virtual UGdouble GetCacheCoordRatio();

	private:
		//! \brief 针对GetViewBlock操作加锁
		UGMutex m_mutex;

		UGImagePlugin* m_pImagePlugin;
	};

}

#endif // !defined(AFX_UGDATASETRASTERREST_H__7681AA6D_BDCB_4A18_A9A3_EC39CEBB7BE4__INCLUDED_)