// UGFishingNetArithmetic.h: interface for the UGFishingNetArithmetic class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_UGFINISHINGNETARITHMETIC_H__37037E0D_8ABC_413E_B8BE_2B8916F0319E__INCLUDED_)
#define AFX_UGFINISHINGNETARITHMETIC_H__37037E0D_8ABC_413E_B8BE_2B8916F0319E__INCLUDED_

#include "Stream/ugdefs.h"
#include "CacheFile/UGCacheFileCommon.h"
#include "FileParser/UGVectorCacheParamater.h"

namespace UGC {

enum UGFishingNetGirdSize
{
	SIZE_256B		= 256,
	SIZE_512B		= 512,
	SIZE_1K			= 1024,
	SIZE_2K			= 2048,		// 2*1024
	SIZE_4K			= 4096,		// 4*1024
	SIZE_8K			= 8192,		// 8*1024
	SIZE_16K		= 16384,	// 16*1024
	SIZE_32K		= 32768,	// 32*1024
	SIZE_64K		= 65536,	// 64*1024
};

struct UGGridIndex
{
	UGint row : 32;
	UGint col : 32;
};

class UGPrjCoordSys;
class UGMapCacheFile;

class MAP_API UGFishingNetArithmetic  
{
public:
	UGFishingNetArithmetic();
	virtual ~UGFishingNetArithmetic();

	// 版本号，默认为最新版本。
	void SetVersion(UGMapCacheVersion nVersion);
	UGMapCacheVersion GetVersion() const;

	// 通过地图投影计算坐标系单位
	void SetPrjCoordSysRatio(const UGPrjCoordSys &CoordSys);

	// 设置计算网格的DPI
	void SetDPI(UGdouble dDPI);
	UGdouble GetDPI();

	// 设置渔网网格的大小
	void SetGirdSize(UGFishingNetGirdSize nGirdSize);
	UGFishingNetGirdSize GetGridSize();

	// 渔网的数据范围，以地理坐标为单位
	void SetBounds(const UGRect2D &rcBounds);
	UGRect2D GetBounds();

	//! \根据地图范围计算图片行列号范围
	//! \param dMapScale [in]		比例尺
	//! \param rcMapBounds [in]		地图范围
	//! \param nStartRow [out]		图片起始行号
	//! \param nEndRow [out]		图片结束行号
	//! \param nStartCol [out]		图片起始列号
	//! \param nEndCol [out]		图片结束列号
	//! \param bBigTileImage [in]	是否是大的图片
	//! remarks 地图缓存使用。主要是出图时使用
	void ComputeGridRange(UGdouble dMapScale, const UGRect2D& rcMapBounds, UGGridArea &GridArea);

	//! \根据给定的比例尺及瓦片行列号范围计算瓦片范围
	//! \param dMapScale [in]		比例尺
	//! \param TileDataArea [in]	瓦片行列号范围
	//! remarks 地图缓存使用。主要是计算多行多列瓦片的范围
	UGRect2D ComputeGridMPBounds(UGdouble dMapScale, const UGGridArea &GridArea) const;

	//! \根据给定的比例尺及瓦片行列号计算瓦片范围
	//! \param dMapScale [in]		比例尺
	//! \param nRow [in]			图片行号
	//! \param nCol [in]			图片列号
	//! remarks 地图缓存使用。主要是计算单个瓦片的范围
	UGRect2D ComputeGridMPBounds(UGdouble dMapScale, UGint nRow, UGint nCol);

	//! \根据给定的比例尺及中心点计算瓦片位置
	//! \param dMapScale [in] 比例尺
	//! \param center [in] 指定的中心点
	//! \param nRow [out] 返回瓦片行号
	//! \param nCol [out] 返回瓦片列号
	//! remarks 地图缓存使用。主要是计算瓦片的位置
	void ComputeGridPosition(UGdouble dMapScale, const UGPoint2D &pntCenter, UGint &nRow, UGint &nCol);

	//! \brief 计算一个范围扩张几个瓦片之后的范围
	//! \param dMapScale 地图比例尺
	//! \param rcMapBounds 地图范围
	//! \param nExtTileSize 扩张瓦片的个数
	//! \return 扩张之后的地图范围
	UGRect2D ComputeGridsMPBounds(UGdouble dMapScale, const UGRect2D& rcMapBounds, const UGRect& rcExtend = UGRect(0, 0, 0, 0));

	UGSize2D ComputeGridMPSize(UGdouble dMapScale) const;

protected:
	UGMapCacheVersion m_nMapCacheVersion;	//! 缓存版本号
	UGdouble m_dCoordRatio;					// LP/DP 转换比率，单位为(像素/毫米)
	UGdouble m_dUnitsRatio;					//! 投影坐标系的单位，LP/MP的转换比例尺使用，默认是 米=10000

	// 计算瓦片需要的参数
	UGFishingNetGirdSize m_nGirdSize;		//! 渔网网格的像素边长。默认 256 像素
	UGRect2D m_rcMapBounds;					//! 渔网网格的范围，实际只使用了地图的左上角

};

}

#endif // !defined(AFX_UGFINISHINGNETARITHMETIC_H__37037E0D_8ABC_413E_B8BE_2B8916F0319E__INCLUDED_)