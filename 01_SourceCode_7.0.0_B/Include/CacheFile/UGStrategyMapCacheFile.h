#ifndef _UGSTRATEGYMAPCACHEFILE_H_
#define _UGSTRATEGYMAPCACHEFILE_H_

#include "Geometry/UGGeoRegion.h"
#include "CacheFile/UGMapCacheState.h"
#include "CacheFile/UGCacheFileCommon.h"
#include "Stream/UGCacheFile.h"

#include <vector>
#include <memory>
#include <map>

namespace UGC
{

class CACHEFILE_API UGStrategyMapCacheFile
{
	friend class UGMapCacheFile;

public:
	UGStrategyMapCacheFile();
	~UGStrategyMapCacheFile();

	// ====================================== 基本操作 ======================================
	UGMapCacheVersion GetCacheVersion() { return m_nMapCacheVersion; }
	void SetCacheVersion(UGMapCacheVersion version) { m_nMapCacheVersion = version; }

	bool FromConfigFile(const UGString& strPath_);
	bool ToConfigFile(const UGString& strOutPutPath);

	void SetCacheName(const UGString& strCacheName);
	const UGString &GetCacheName();

	// 数据来源设置
	void	 SetNetCachePath(const UGString &strNetCachePath);
	UGString GetNetCachePath();

	UGFileType::EmType GetImageType() const { return m_FileType; }
	bool SetImageType(UGFileType::EmType nImageFileType);

	bool SetImageSize(const UGSize &szImageCell);
	UGSize GetImageSize();

	bool SetImageCompress(int nCompress = 100);
	int GetImageCompress();

	void SetTransparentBack(bool bTransparentBack = true);
	bool IsTransparentBack();

	void SetBaseScale(double dBaseScale) { m_dBaseScale = dBaseScale; }

	void SetBaseWidth(size_t nBaseWidth) { m_nDPBaseWidth = nBaseWidth; }
	void SetBaseHeight(size_t nBaseHeight) { m_nDPBaseHeight = nBaseHeight; }

	bool SetBounds(const UGRect2D& rcBounds);
	UGRect2D &GetBounds();

	void SetStorageType(StoreType ntype);
	const StoreType &GetStorageType();

	void SetMapName(const UGString &strMapName) { m_strMapName = strMapName; }
	const UGString &GetMapName() { return m_strMapName; }

	bool SetIndexBounds(const UGRect2D& rcIndexBounds);
	UGRect2D &GetIndexBounds() { return m_rcIndexBounds; }

	void SetPrjCoordSys(const UGPrjCoordSys &coordSys);
	const UGPrjCoordSys &GetPrjCoordSys() { return m_coordSys; }

	const std::vector<double> GetOutputScales() const;
	bool SetOutputScales(const std::vector<double>& vectOutputScales);

	bool SetCaptions(vector<UGString> vectScaleCaptions);
	std::vector<UGString> GetCaptions();

	//bool SetClipRegion(const UGGeoRegion* pClipRegion);
	//UGGeoRegion* GetClipRegion() const { return m_pClipRegion.get(); }

	//void SetPassword(const UGString& strPwd);
	//UGString &GetPassword();

	UGString GetFileDirectory();

	bool SetBeginLevel(size_t nBeginLevel);
	int GetBeginLevel() const { return m_nBeginLevel; }

	bool SetEndLevel(size_t nEndLevel);
	int GetEndLevel() const { return m_nEndLevel; }

	void SetHashCode(const UGString& strHashCode);
	UGString GetHashCode();

	void Reset();

	// ================================= 路径名/地理范围转换 =================================
	UGString Generate2DImagePath(double dScale, const UGRect2D& rcMPImageBounds, const UGString& strHashCode);	

	// 获取指定缓存图片的绝对路径
	UGString Generate2DImagePath(double dScale, int32_t nXIndex, int32_t nYIndex);

	// 获取指定缓存图片的相对路径
	UGString Compute2DImageRelativePath(double dScale, int32_t nXIndex, int32_t nYIndex);

	UGString Generate3DImageRelativePath(size_t nLevel, const UGRect2D& rcMPImageBounds);

	void Compute2DImagePosition(const UGPoint2D &pntCenter, double dScale, UGint &nRow, UGint &nCol);
	void Compute2DImageFileName(const UGPoint2D &pntCenter, double dScale, UGString& strFileName);

	void Compute2DImageFileName(const UGRect2D &imageBounds, double dScale, std::vector<UGString>& vectFileNames);

	void ComputeTileRange(const UGRect2D &rcMPBounds, double dScale, int32_t &nStartRow, int32_t &nEndRow, int32_t &nStartCol, int32_t &nEndCol);

	UGString TilePos2FileName(double dScale, int nRow, int nCol, bool &bCompact, UGString& strImageFileName);

	UGRect2D TilePos2MPBounds(double dScale, int nRow, int nCol);
	// ====================================== 扩展功能 ======================================
	bool CheckTileBoundsValid(const UGRect2D &rcMPTileBounds, double dScale);
	void Clear(const UGRect2D &rcBounds, double dScale);

	// ================================ MapCacheState 操作 ====================================
	bool AddMapCacheState(UGMapCacheState *pMapCacheState);
	const UGMapCacheState *GetMapCacheState(double dScale);
	void ClearMapCacheState();

	bool GetTileData(UGTile &tileData);

	//! \brief 根据瓦片的行列号，把相应数据存到相应路径或者紧凑文件格式中,格式为 1000/00000001x00000009/00000002x00000004.jpg
	//! \param dMapScale [in]		当前出图的比例尺
	//! \return						获取生成的图片相对路径
	//! \remarks					规则如下：
	void Save2DImageData(UGdouble dMapScale, UGint nRow, UGint nCol, const UGbyte* pData, UGint nSize);

	//! \brief 根据瓦片的行列号，判断指定瓦片的数据是否存在
	bool IsTileExist(UGdouble dMapScale, UGint nRow, UGint nCol, const UGString& strFilePwd = _U(""));


	UGSize2D GetMPCellImageSize(double dScale);

	//! \brief SCI中DP-->LP的转换比率
	double GetCoordRatio();

private:
	void SetOutputScales_aux(const std::vector<double>& vectOutputScales);
	//int DoubleScaleToIntScale(double dScale) const;
	UGString FileType2Postfix(UGFileType::EmType);
	UGFileType::EmType Postfix2FileType(const UGString& strExtName);

	UGSize2D LPSize2MPSize(const UGSize &rcLPBounds, double dScale);
	UGSize2D LPSize2MPSizePrecise(const UGSize &rcLPBounds, double dScale);

	double Scale2CoordRatio(double dScale);

#if !defined OS_ANDROID && !defined (IOS) && !defined _UGUNICODE && !defined(_AIX) && !defined(__linux__)

	// 获取云服务压缩文件相关的函数(gdp文件)
	UGString GetGDPZipRelativePath(UGdouble dMapScale, UGint nRow, UGint nCol);
	bool IsGDPTileExist(UGdouble dMapScale, UGint nRow, UGint nCol);
	bool GetGDPTileData(UGdouble dMapScale, UGint nRow, UGint nCol, UGByteArray& ByteArray);

#endif

	//void Compute3DImageFileName(std::vector<UGString>& vectFileNames);
	//void Compute3DImageFileName(size_t nLevel, std::vector<UGString>& vectFileNames);

	// =============================== 以下成员在 sci 文件中存在 ===============================
	// sml:CacheName
	UGString m_strCacheName;	// 缓存名称

	// sml:ImageFormat
	UGFileType::EmType m_FileType;

	// sml:ImageWidth 和 sml:ImageHeight
	size_t m_nDPFullImageWidth;
	size_t m_nDPFullImageHeight;

	// sml:ImageCellWidth 和 sml:ImageCellHeight
	size_t m_nDPCellImageWidth;
	size_t m_nDPCellImageHeight;

	// sml:ImageCompress
	int m_nImageCompress;  // 图片压缩率

	// sml:IsTransparent
	bool m_bTransparentBack;//是否背景透明

	// sml:ImageLogicalWidth 和 sml:ImageLogicalHeight
	size_t m_nLPCellImageWidth;		//整幅图片的高度和宽度（逻辑）
	size_t m_nLPCellImageHeight;

	// sml:BaseScale
	double m_dBaseScale;		// BaseScale提供MP与LP之间的转换比率

	// sml:BaseWidth 和 sml:BaseHeight
	size_t m_nDPBaseWidth;
	size_t m_nDPBaseHeight;

	// sml:BaseLogicalWidth 和 sml:BaseLogicalHeight
	unsigned m_nLPBaseWidth;
	unsigned m_nLPBaseHeight;

	// sml:ImageBounds
	UGRect2D m_rcBounds;

	// sml:StoreType
	StoreType m_nStorageType;

	// sml:MapName
	UGString m_strMapName;

	// sml:MapBounds
	UGRect2D m_rcIndexBounds;

	// sml:CoordinateReferenceSystem
	UGPrjCoordSys m_coordSys;

	// MapCache
	std::map<double, UGMapCacheState*> m_mapMapCacheStates;
	
	// sml:PixelFormat
	OGDC::PixelFormat pixelFormat;

	// sml:UseOutPutRegion
	// 由于已经不再提供 SetUseOutputRegion() 函数，该变量已经不再有任何意义。故去掉
	//bool m_bUseClipRegion;

	// sml:OutPutRegion
	//std::auto_ptr<UGGeoRegion> m_pClipRegion;

	// sml:Level
	size_t m_nBeginLevel;
	size_t m_nEndLevel;

	UGString m_strNetCachePath;				// 缓存SCI存放目录位置

	// ============================ 以下成员不在 sci 文件中直接存在 ===============================

	// m_vectOutputScales 与 m_vectOutputScaleCaptions 中的内容必须按顺序一一对应。
	// 但是他们与 m_MapCacheStates 的顺序不需要对应。
	std::vector<double> m_vectOutputScales;
	//std::vector<UGString> m_vectOutputScaleCaptions;

	UGString m_strPwd;
	UGString m_strHashCode;
	UGMapCacheVersion m_nMapCacheVersion;
	UGString m_strTopLevelDirName;
	UGString m_strDefaultCoordSys;

protected:
	// ========================================================================
	UGStrategyMapCacheFile &operator=(const UGStrategyMapCacheFile&);
	UGStrategyMapCacheFile(const UGStrategyMapCacheFile&);

};

}

#endif // _UGSTRATEGYMAPCACHEFILE_H_
