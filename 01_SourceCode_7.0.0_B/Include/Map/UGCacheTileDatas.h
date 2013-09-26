// UGWebMapLayerStub.h: interface for the UGWebMapLayerStub class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_UGCACHETILEDATAS_H__66585C4A_9CBA_4EE8_98FB_AE9B0C1C2803__INCLUDED_)
#define AFX_UGCACHETILEDATAS_H__66585C4A_9CBA_4EE8_98FB_AE9B0C1C2803__INCLUDED_

#include "Toolkit/UGThread.h"
#include "Toolkit/UGPalette.h"

namespace UGC {


//////////////////////////////////////////////////////////////////////////

struct MAP_API UGTileData
{
	//! \brief 比例尺
	UGdouble m_dScale;
	//! \brief 行号
	UGint m_nRow;
	//! \brief 行号
	UGint m_nCol;
	//! \brief  地理范围
	UGRect2D m_rcBounds;
	//! \brief  地理范围
	UGImageData m_ImageData;
};

//! \brief 缓存TileData
class MAP_API UGCacheTileDatas
{
public:
	UGCacheTileDatas();
	~UGCacheTileDatas();

	//! \brief 获取是否有TileData
	UGbool IsEmpty();

	//! \brief 获取TileData
	const UGTileData* LookupTile(UGdouble dScale, UGint nRow, UGint nCol);

	//! \brief 获取TileData
	UGTileData* LookupTileEx(UGdouble dScale, UGint nRow, UGint nCol);

	//! \brief 增加一个TileData
	UGbool AddTile(UGTileData *pTileData, UGRect2D& rcBounds);

	//! \brief 删除一个TileData
	UGbool RemoveTile(UGdouble dScale, UGint nRow, UGint nCol);

	//! \brief 删除一个TileData
	UGbool RemoveTile(UGdouble dScale, const UGRect2D &rcBounds);

	//! \brief 清空所有TileData
	UGint RemoveAll();

	//! \brief 获取TileData个数
	UGint GetCount();

public:
	//! \brief TileData最大长度，默认是50
	UGint m_nMaxTilesLength;

private:
	//! \brief 缓存TileData
	UGDict<UGString, UGTileData> m_TileDatas;

	//! \brief 用来保护缓存列表
	UGMutex m_mutexTileDatas;

};

//////////////////////////////////////////////////////////////////////////

}

#endif // !defined(AFX_UGCACHETILEDATAS_H__66585C4A_9CBA_4EE8_98FB_AE9B0C1C2803__INCLUDED_)