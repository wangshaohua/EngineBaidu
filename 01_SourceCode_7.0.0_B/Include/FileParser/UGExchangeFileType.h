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
//!  \author 格式转换组。
//!  \attention 请不要随便修改下面的常量定义。
//!   Copyright (c) 1996-2010 SuperMap Software Limited Company.  <br> 
//!   All Rights Reserved.
//!  \version 6.0
//////////////////////////////////////////////////////////////////////////

#if !defined(AFX_UGEXCHANGEFILETYPE_H__EAB125D4_D53A_4784_A77E_5A8636BC43BD__INCLUDED_)
#define AFX_UGEXCHANGEFILETYPE_H__EAB125D4_D53A_4784_A77E_5A8636BC43BD__INCLUDED_

#include "Stream/ugdefs.h"
#include "Stream/UGByteArray.h"

namespace UGC {

#define UG_WEB_SERTYPE _U("WebMapType") // Web服务类型

// 地图缓存剖分方式
enum  TileType
{
	Global = 0,		// 全球剖分方式
	Local  = 1,		// 区域剖分方式，用比例尺分层
};

//! \brief 数据转换支持的文件类型。
class FILEPARSER_API UGFileType
{
public:

	//! \brief 文件格式分组。
	enum EmGroup
	{
		//! \brief 不知道应该放到哪个组中
		GroupUncertain = 0,		
		//! \brief 矢量类型的文件格式
		GroupVector	= 1,		
		//! \brief 用户定义的矢量格式
		GroupUserVector	= 2,		
		//! \brief 栅格类型的文件格式
		GroupRaster = 3,	
		//! \brief 用户定义的栅格格式
		GroupUserRaster = 4 ,
		//! \brief 工作空间文件格式（混合数据集）
		GroupWorkSpace =  5,
	};


	// 文件格式类型	
	// SuperMap预留的矢量格式常量 [1, 100]
	// 其中通用矢量格式[1, 50]	XML格式[51, 60]	数据库文件[60, 70]
	// SuperMap开放给用户自行开发的矢量格式常量: [101, 200]
	enum EmType
	{
		// 不认识	
		none			= 0, 

		//!AutoCAD DWG 交换文件
		DWG				= 2,	
		//!AutoCAD DXF 交换文件
		DXF				= 3,	

		// ERSI File [6, 10]
		//!Arc/Info Coverage
		AIBinCov		= 6,
		//!Arc/Info E00交换文件
		E00				= 7,	
		
		//!ArcView Shape文件
		Shape			= 8,	
		
		// MapInfo File [11, 15]
		//!MapInfo TAB
		TAB				= 11,	
		//!MapInfo MIF 交换文件
		MIF				= 12,
		//!MapInfo 工作空间文件
		WOR             = 13,
		
		// MicroStation File [16, 20]
		//!Microstation DGN文件
		DGN				= 16,	

		Lidar			= 17, //! ASPRS Lidar Data Exchange Format (LAS)
		
		// other GIS/CAD software File [21, 50]
 		VCT				= 22,	//!国家标准矢量文件 *.VCT

		
		// other vector file 
		//!EMF文件(windows metaFile:元增强文件)
		EMF				= 34,	
		//!WMF文件(windows metaFile:元文件)
		WMF				= 31,	
		//!EPS文件
		EPS				= 32,	
		//!PDF文件
		PDF				= 33,
		
		//!电子海图格式
		ENC				= 40,
		//!电信格式
		TEMSVector		= 41,	//!电信Vector格式
		TEMSBldngVctr	= 42,	//!电信Building vector格式
		
		//XML document [51, 60]
		//!OpenGIS 定义的XML 文档
		GML				= 51,	
		//!SuperMap 定义的XML文档
		SML				= 52,
		//google的KML文件格式
		KML				= 53,
		//google的KML格式的压缩文件
		KMZ				= 54,
		//MapGis明码文件wat、wal、wap
		MAPGIS			= 55,
		
		//database file [61, 70]
		DBF				= 61,	//!dbf 数据库文件

		SCV				= 63,   //!三维模型缓存文件
		CSV				= 64,	//!文本文件

		//! Fme工作空间的导入模式
		FMEWorkBench    = 65,

		//! 矢量数据使用fme进行导入
		FMEVector       = 66, 

		//! 栅格数据使用fme进行导入
		FMERaster       = 67, 
		
		// SDE的矢量格式
		SDEVector		= 68,
		
		// SDE的栅格格式
		SDERaster		= 69,
		
		// Esri file geodatabase vector .gdb文件
		GDBFVector      = 70,
		
		// Esri file geodatabase raster .gdb文件
		GDBFRaster      = 71,
		
		// Esri Personal geodatabase	.mdb文件
		GDBP		    = 72,

		// SuperMap预留的栅格格式常量 [101, 200]
		// 其中影像类[101, 120] 图片类[121, 140] DEM/Grid类[141-160] 
		// 其他[161, 180] 预留格式[181, 200]

		// 影像类 [101, 120]
		//!Erdas Image文件
		IMG				= 101,	
		//!sid文件
		SID				= 102,	
		//!Tiff/BigTIFF/GeoTIFF文件
		GTiff			= 103,	
		//!Er-Mapper ECW文件
		ECW				= 106,	
		//!Idrisi 栅格文件
		IDR				= 107,	
		//!Landsat－7 FST文件，后缀名(*.fst)
		FST				= 108,	

		// 图片类 [121, 140]
		//!bitmap文件
		BMP				= 121,	
		//!jpg文件
		JPG				= 122,	
		//!portal network graphic(PNG)		
		PNG				= 123,	
		//!gif文件
		GIF				= 124,	
		//!tga文件
		TGA				= 125,	

		// DEM/Grid类 [141-160]
		//!BIL格式的grd文件
		BIL				= 141,	
		//!Arc/Info ASCII 交换文件
		AIASCIIGrid		= 142,	
		//!国标格网数据文件
		DEM				= 143,	
		//!USGS格网数据文件 美国标准
		USGSGrid		= 144,	
		//!Arc/Info binary grid文件
		AIBinGrid		= 145,
		//!电信格式
		TEMSClutter		= 146,	//!电信Raster格式

		JPGPNG          = 147, //！JPG和PNG图片混合格式 

		BIP             = 148,
		BSQ             = 149,

		// 其他	[161, 180]
		//!raw文件
		RAW				= 161,	

		// 预留格式 [181, 200]
	
		//!SuperMap压缩影像 SuperMap Image Tower
		SIT				= 204,

		// 这里再预留 100个编号 给可能的使用 [301, 400]
		// SuperMap为用户自行开发数据转换预留的文件格式常量 [401, 500]		
		// 矢量: [401, 450]		
		//!用户自定义矢量1
		UserVectorBegin	= 401, 
		//!用户自定义矢量2
		UserVectorEnd	= 450, 
		
		// 栅格: [451, 500]
		//!用户自定义栅格1
		UserRasterBegin	= 451, 
		//!用户自定义栅格2
		UserRasterEnd	= 500,

		//模型文件
		//3DS模型文件
		Model3DS        = 501,

		//sgm模型文件
		SGM				= 502,	

		//x模型文件
		ModelX			= 503,

		//dae模型文件
		ModelDAE        = 504,

		//osg模型文件
		ModelOSG        = 505,

		//SuperMapTileEncodeType
		STET            =506,
	};

	
	//! \brief 根据文件格式常量判断这种格式属于哪一个组。
	//! \param eFileType [in]。
	static EmGroup GetFileGroup(EmType eFileType);	

	//! \brief 根据后缀名得到文件类型。
	//! \param strExtName [in] 带.的后缀名 。
	static EmType ExtNameToFileType(const UGString& strExtName);	
	
	//! \brief 根据文件类型得到后缀名。
	//! \param strExtName [in]。
	static UGString FileTypeToExtName(EmType eFileType);

	static UGString DetailByFileType(EmType etype);

	//! \brief 是否是矢量类型。
	//! \param eFileType [in]。
	static UGbool IsVector(EmType eFileType);	

	static UGbool IsModelFile(EmType eFileType);
	
	//! \brief 是否可以导入成CAD类型。
	//! \param eFileType [in]。
	//! \attention 目前只FME中使用。
	static UGbool IsCanBeCAD(EmType eFileType);

	//! \brief 导入的数据集名称是否要加后缀。
	//! \param eFileType [in]。
	//! \attention 目前只FME中使用。
	static UGbool IsNeedAddEx(EmType eFileType);

	//! \brief 导入的类型是否是Engine类型 如SDE。
	//! \param eFileType [in]。
	//! \attention 目前只FME中使用。
	static UGbool IsNoEngineType(EmType eFileType);
};

//! \brief 回调函数参数（单张瓦片的信息）
struct UGDownloadTileInfo
{
	//! \brief 比例尺
	UGdouble m_dScale;

	//! \brief  地理范围
	UGRect2D m_rcBounds;

	//! \brief 行号
	UGint m_nRow;

	//! \brief 行号
	UGint m_nCol;

	//! \brief 下载成功时，为0，非0为有错误
	UGint m_eErrorType;

	//! \brief 重载 ==
	//! \param const UGMapDownloadRequest& request
	//! \return	 若两个请求相等则返回true
	UGbool operator==(const UGDownloadTileInfo& TileInfo) const
	{
		if (m_dScale == TileInfo.m_dScale && m_nRow == TileInfo.m_nRow && m_nCol == TileInfo.m_nCol)
		{
			return TRUE;
		}

		return FALSE;
	}

	//! \brief 重载=。
	//! \param &request [in]。
	void operator = (const UGDownloadTileInfo &TileInfo)
	{
		m_eErrorType = TileInfo.m_eErrorType;
		m_rcBounds = TileInfo.m_rcBounds;
		m_nRow = TileInfo.m_nRow;
		m_nCol = TileInfo.m_nCol;
		m_dScale = TileInfo.m_dScale;
	}
};

class UGTile
{
public:
	UGTile()
	{
		m_nRow = 0;
		m_nCol = 0;
	}
	~UGTile()
	{
	}

	void SetScale(UGdouble dScale) 
	{
		m_dScale = dScale;
	}

	UGdouble GetScale() const 
	{
		return m_dScale;
	}

	void SetTileRow(UGint nRow)
	{
		m_nRow = nRow;
	}
	UGint GetTileRow()
	{
		return m_nRow;
	}

	void SetTileCol(UGint nCol)
	{
		m_nCol = nCol;
	}
	UGint GetTileCol()
	{
		return m_nCol;
	}

	void SetFileType(UGint nFileType)
	{
		m_nFileType = nFileType;
	}

	UGint GetFileType()
	{
		return m_nFileType; 
	}

	void SetByteArray(const UGByteArray &ByteArray)
	{
		m_ByteArray = ByteArray;
	}

	UGByteArray &GetByteArray()
	{
		return m_ByteArray;
	}

	void SetTilePos(int nRow, int nCol) 
	{
		m_nRow = nRow;
		m_nCol = nCol;
	}
	void GetTilePos(int &nRow, int &nCol) const 
	{
		nRow = m_nRow;
		nCol = m_nCol;
	}

	void SetMPBounds(const UGRect2D &rcBounds) 
	{
		m_rcBounds = rcBounds;
	}
	const UGRect2D &GetMPBounds() const 
	{
		return m_rcBounds;
	}

	void SetTileSize(UGint nTileSize) 
	{
		m_nTileSize = nTileSize;
	}

	UGint GetTileSize() const 
	{
		return m_nTileSize;
	}

private:
	// 比例尺
	UGdouble m_dScale;

	// 瓦片位置
	int m_nRow;
	int m_nCol;

	//! \brief  地理范围
	UGRect2D m_rcBounds;

	//! \brief  Tile 的图像格式
	UGint m_nFileType;

	//! \brief  Tile 的文件流
	UGByteArray m_ByteArray;

	//! \brief  Tile 的像素宽高
	UGint m_nTileSize;

};

//! \brief 数据变化回调函数参数，该结构在多线程中使用
struct UGDataChangeInfo
{
	enum ChangeType
	{
		DownLoad = 0,	// 网络下载引起的变化
		Zoom = 1,		// 缩放引起的变化
		Pan = 2			// 移动引起的变化
	};

	//! \brief 引起数据变化的类型
	ChangeType m_eChangeType;
	//! \brief 地图比例尺
	UGdouble m_dMapScale;
	//! \brief 地图对应瓦片的最近比例尺
	UGdouble m_dTileScale;
	//! \brief 地图MP->LP的转换比率
	UGdouble m_dCoordRatio;
	//! \brief  数据变化区域(地理范围)
	UGRect2D m_rcChangeBounds;
	//! \brief  数据不变的区域(地理范围)
	UGRect2D m_rcClipBounds;
	//! \brief 网络下载成功时，为0，非0为有错误
	UGint m_eErrorType;
	//! \brief 数据变化区域(设备范围)
	UGint m_nChangeWidth;
	//! \brief 数据变化区域(设备范围)
	UGint m_nChangeHeight;
	//! \brief 行号(便于调试)
	UGint m_nRow;
	//! \brief 行号(便于调试)
	UGint m_nCol;

	UGDataChangeInfo()
	{
		m_eChangeType = DownLoad;
		m_dMapScale = 0.0;
		m_dTileScale = 0.0;
		m_dCoordRatio = 0.0;
		m_rcChangeBounds.SetEmpty();
		m_rcClipBounds.SetEmpty();
		m_eErrorType = 0;
		m_nChangeWidth = 0;
		m_nChangeHeight = 0;
		m_nRow = 0;
		m_nCol = 0;
	}

	//! \brief 重载 ==
	UGbool operator==(const UGDataChangeInfo& ChangeInfo) const
	{
		if (m_dMapScale == ChangeInfo.m_dMapScale && m_rcChangeBounds == ChangeInfo.m_rcChangeBounds)
		{
			return TRUE;
		}

		return FALSE;
	}

	//! \brief 重载=。
	void operator = (const UGDataChangeInfo& ChangeInfo)
	{
		m_eChangeType = ChangeInfo.m_eChangeType;
		m_dMapScale = ChangeInfo.m_dMapScale;
		m_dTileScale = ChangeInfo.m_dTileScale;
		m_dCoordRatio = ChangeInfo.m_dCoordRatio;
		m_rcChangeBounds = ChangeInfo.m_rcChangeBounds;
		m_rcClipBounds = ChangeInfo.m_rcClipBounds;
		m_eErrorType = ChangeInfo.m_eErrorType;
		m_nChangeWidth = ChangeInfo.m_nChangeWidth;
		m_nChangeHeight = ChangeInfo.m_nChangeHeight;
		m_nRow = ChangeInfo.m_nRow;
		m_nCol = ChangeInfo.m_nCol;
	}

};

typedef UGArray<UGTile*> UGTiles;


} //namespace UGC


#endif // !defined(AFX_UGEXCHANGEFILETYPE_H__EAB125D4_D53A_4784_A77E_5A8636BC43BD__INCLUDED_)


