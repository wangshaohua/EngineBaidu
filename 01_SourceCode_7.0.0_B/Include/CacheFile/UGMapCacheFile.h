#ifndef _UGMAPCACHEFILE_H_
#define _UGMAPCACHEFILE_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CacheFile/UGAbstractCacheFile.h"
#include "CacheFile/UGAbstractCacheFileV70.h"
#include "CacheFile/UGStrategyMapCacheFile.h"
#include "CacheFile/UGCacheFileCommon.h"

#include <vector>

namespace UGC
{

class CACHEFILE_API UGMapCacheFile  
{
public:
	UGMapCacheFile();
	~UGMapCacheFile();

	UGMapCacheFile& operator = (const UGMapCacheFile &CacheFile);

	bool Open(const UGString &strFileName, const UGString &strPassword = _U(""));
	bool Save(const UGString &strFileName);
	bool Close();

	void Reset();

	bool CheckTileBoundsValid(const UGRect2D &rcMPTileBounds, double dScale);
	std::vector<UGTile*> *GetTiles(const UGRect2D &rcMPBounds, double dScale, UGString strPwd, UGString strHashCode);

	// 版本号，默认为最新版本。
	void SetVersion(UGMapCacheVersion nVersion);
	UGMapCacheVersion GetVersion() const;

	const UGPrjCoordSys& GetPrjCoordSys();

	bool CheckVersion(UGString strFilePath);
	UGint GetVersionFromFile(UGString strFilePath);

	bool Clear(const UGRect2D &rcBounds, const std::vector<double> &vectScales);
	UGbool Clear(const std::vector<UGdouble> &vectScales, const UGGeoRegion *pRegion);
	UGbool Clear(const UGGeoRegion *pRegion);

	// 缓存名称设置
	bool SetCacheName(const UGString &strCacheName);
	UGString GetCacheName();

	// 数据来源设置
	bool	 SetServiceProvider(const UGString &strServiceProvider);
	UGString GetServiceProvider();

	// 图片策略，比如是透明Png32、不透明Png32、Png8、Jpeg、混合图片模式
	bool SetImageType(UGint nPictureFormat);
	UGint GetImageType();

	// 单张图片像素大小，默认是256像素宽高
	bool	SetTileSize(int nTileSize);
	int		GetTileSize();

	// 数据范围，以地理坐标为单位
	bool SetBounds(const UGRect2D &rcBounds);
	UGRect2D GetBounds();

	bool SetIndexBounds(const UGRect2D &rcBounds);
	UGRect2D GetIndexBounds();

	bool SetClipRegion(UGGeoRegion *region);
	const UGGeoRegion *GetClipRegion();

	bool IsFillMargin();
	void SetFillMargin(bool bFillMargin = true);

	bool IsTransparent();
	void SetTransparent(bool bTransparent = true);

	// 每毫米有多少个像素，默认每毫米3个像素，x方向和y方向比率一致吧
	bool SetCoordRatio(double dCoordRatio);
	double GetCoordRatio();

	double GetDPI();

	// 比例尺信息，这块要求，不要存比例尺的倒数了
	// 如果所有比例尺都在正常范围，即均为正数，返回 true；否则返回 false，并且不对比例尺设置进行任何修改。
	bool SetOutputScales(const std::vector<double>& vectOutputScales);
	std::vector<double> GetOutputScales();

	bool SetOutputScaleCaptions(const std::map<double, UGString> &mapOutputScaleCaptions);
	void GetOutputScaleCaptions(std::map<double, UGString> &mapOutputScaleCaptions);

	// 投影信息，会初始化坐标系单位和缓存参考原点
	void SetPrjCoordSys(const UGPrjCoordSys &CoordSys);

	// 是否紧凑缓存，默认不是紧凑
	void SetIsCompactCache(bool bCompactCache);

	// 缓存存放位置
	UGString GetFileDirectory();

	//! \brief 根据瓦片的行列号，判断指定瓦片的数据是否存在,格式为 1000/00000001x00000009/00000002x00000004.jpg
	//! \param dMapScale [in]		当前出图的比例尺
	//! \return						不存在返回false
	//! \remarks					规则如下：
	bool IsTileExist(double dMapScale, int nRow, int nCol);

	//! \brief 根据瓦片的行列号，把相应数据存到相应路径或者紧凑文件格式中,格式为 1000/00000001x00000009/00000002x00000004.jpg
	//! \param dMapScale [in]		当前出图的比例尺
	//! \return						获取生成的图片相对路径
	//! \remarks					规则如下：
	void SaveImageData(double dMapScale, int nRow, int nCol, const UGbyte* pData, int nSize);

	// MPPoint2PixelPos ----> PixelPos2TilePos
	//! \根据给定的比例尺及中心点计算瓦片位置
	//! \param dMapScale [in] 比例尺
	//! \param center [in] 指定的中心点
	//! \param nRow [out] 返回瓦片行号
	//! \param nCol [out] 返回瓦片列号
	//! remarks 地图缓存使用。主要是计算瓦片的位置
	void ComputeTilePosition(double dMapScale, const UGPoint2D &pntCenter, int &nRow, int &nCol);

	//! \根据给定的比例尺及瓦片行列号计算瓦片范围
	//! \param dMapScale [in]		比例尺
	//! \param nRow [in]			图片行号
	//! \param nCol [in]			图片列号
	//! remarks 地图缓存使用。主要是计算单个瓦片的范围
	UGRect2D ComputeTileMPBounds(double dMapScale, int nRow, int nCol);

	// MPBounds2PixelArea ----> PixelArea2TileArea
	//! \根据地图范围计算图片行列号范围
	//! \param dMapScale [in]		比例尺
	//! \param rcMapBounds [in]		地图范围
	//! \param nStartRow [out]		图片起始行号
	//! \param nEndRow [out]		图片结束行号
	//! \param nStartCol [out]		图片起始列号
	//! \param nEndCol [out]		图片结束列号
	//! \param bBigTileImage [in]	是否是大的图片
	//! remarks 地图缓存使用。主要是出图时使用
	void ComputeTileRange(double dMapScale, const UGRect2D& rcMapBounds, UGHPDataArea &TileDataArea);

	// 获取相近比例尺
	double ScaleToNearFixScale(double dScale);

	// 将浮点型的比例尺转换为整数，例如 .5 转换成整数为 2，该整数用来生成缓存目录名
	unsigned		Scale2ScalePathName(double dScale);		
	double	ScalePathName2Scale(unsigned nScale);

	// 根据传入的TileData中的比例尺和行列号，获取Tile的地理范围和像素范围，及Tile的数据流及图像格式
	bool GetTileData(UGTile& TileData);

	// 根据传入的TileData中的比例尺，获取Tile的地理范围和像素范围
	void GetTileInfo(UGTile& TileData);

	//! \brief 获取缓存生成的瓦片相对SCI文件的路径，格式为 1000/00000001/00000009/00000002x00000004.jpg
	//! \param dMapScale [in]		当前出图的比例尺
	//! \return						获取生成的瓦片相对路径
	UGString ComputeTileFileName(double dMapScale, int nRow, int nCol);

	// 根据打开的sci生成
	bool SaveAsSCI3D();

	//! \brief 计算一个范围扩张几个瓦片之后的范围
	//! \param dMapScale 地图比例尺
	//! \param rcMapBounds 地图范围
	//! \param nExtTileSize 扩张瓦片的个数
	//! \return 扩张之后的地图范围
	UGRect2D ComputeTilesMPBounds(double dMapScale, const UGRect2D& rcMapBounds, int nExtTileSize = 1);

	//! \brief 通过比例尺转换瓦片边长对应的地理大小
	//! \param dMapScale 地图比例尺
	UGSize2D GetTileMPSize(double dMapScale);

	// 合并地图缓存
	// strPath 合并进本地图缓存的外部缓存
	// strPassword 外部缓存的密码
	bool Merge(const UGString &strPath, const UGString &strPassword = _U(""));
	
	//UGString GetClipRegion();
	TileType GetTileType();
	StoreType GetStorageType();
	int GetImageCompress() ;
	//UGdouble GetCoordRatio();
	UGColor GetDefaultColor();

	// 返回的 UGGeoRegion 对象由外部释放！
	UGGeoRegion *GetValidRegion(const UGRect2D &rcBounds, double dScale);

	bool HitTest(const UGPoint2D &pntPosition, double dScale);

	bool Convert(StoreType sotreType, const UGString &strDest, const UGString &strPassword );

	UGbool ConvertSingleCompactFile(const UGString &strCompactFilePath, const UGString &strOutputPath);

	bool Reload();

	UGString GetHashCode();

	UGbool Extract(std::vector<UGdouble> vectScales, const UGGeoRegion &region, StoreType type, const UGString &strPath);

	UGbool Extract(const UGGeoRegion &region, const UGString &strPath);

	// 剖分方式
	//TileType GetTileType();

	// 获取用户扩展字段的引用，可直接修改。
	// 如果map的元素个数不为0，会依次保存元素到配置文件里边
	std::map<UGString, UGString>& UserExtendField();

	//! \brief 删除特定的已生成的用户自定义版本
	void DeleteRevisionNumber(UGint value);

private:
	//! \brief 匹配比例尺，找到最接近比例尺
	double AdjustScale(double dScale);

	//! \brief 计算出三维常用的二十级比例尺，并保存起来，用于校正比例尺的时候用
	void ComputeLevelsScale();

private:
	UGString m_strFileName;							// sci 文件名称。当执行了 Open() 之后，该名称就会被更新。
	UGMapCacheVersion m_nVersion;					// 当前缓存的版本号。在 ToConfigFile() 中该版本号指示了要导出的文件格式
	UGString m_strTopLevelDirName;					// 缓存SCI存放目录位置

	UGAbstractCacheFileV70 m_HPMapCacheFileV70;
	UGAbstractCacheFile m_HPMapCacheFile;
	UGStrategyMapCacheFile m_StrategyMapCacheFile;

	std::vector<double> m_vect3DLevelsScales;		// 三维层级对应的比例尺列表
	UGCompactFileWrapper *m_pCompactFile;
};

}

#endif // _UGMAPCACHEFILE_H_
