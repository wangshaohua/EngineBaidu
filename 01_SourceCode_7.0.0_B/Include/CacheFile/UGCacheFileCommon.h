#ifndef _UGCACHEFILECOMMON_H_
#define _UGCACHEFILECOMMON_H_

#include "FileParser/UGExchangeFileType.h"
#include "Stream/UGByteArray.h"
#include "CompactFile/UGCompactFile.h"
#include <limits>

#if defined(_MSC_VER)

typedef unsigned int uint32_t;
typedef __int64 int64_t;
typedef int int32_t;
typedef unsigned int uint32_t;

#else

#include <stdint.h>

#endif

#ifdef max
#undef max
#endif

#ifdef min
#undef min
#endif

#define UG_ABSCACHEFILE_EXT _U(".sci")
#define UG_ARCFILE_EXT _U(".xml")
#define UG_SOLID_FILENAME _U("solid.dat")
#define HASHCODE_LENGTH 8


namespace UGC 
{

const int nMaxTileSize = 2048;
const int nMinTileSize = 64;

//struct CompactCacheFilePosition
//{
//	UGdouble dScale;
//	UGint nRow;
//	UGint nCol;
//
//	CompactCacheFilePosition()
//	{
//		dScale = 0;
//		nRow = 0;
//		nCol = 0;
//	}
//};

enum UGMapCacheVersion 
{
	Version_UNKNOWN = 0,
	Version_10 = 10,
	Version_20 = 20,
	Version_21 = 21,
	Version_30 = 30,
	Version_31 = 31,
	Version_40 = 40,
	Version_41 = 41,
	Version_50 = 50,
	Version_70 = 70,
};

class UGCompactFileWrapper
{
public:
	UGCompactFile compactFile;
	UGint nTileGroupRow;
	UGint nTileGroupCol;
	UGdouble dScale;
	
	UGCompactFileWrapper()
	{
		// 按照缓存 25 层设计，这个行列号为非法值
		nTileGroupCol = std::numeric_limits<UGint>::min();
		nTileGroupRow = std::numeric_limits<UGint>::min();

		dScale = 0;
	}
};

enum UGMapCacheStrategy
{
	UNKNOWN = -1,

	Cache_ISDOTNET = 0,		// IS.Net和SFC的缓存策略

	Cache_UGC = 1,			// UGC 的缓存策略

	Cache_iServer20 = 2,	// 对应iServer20策略，即ISJava简易缓存方式

	Cache_iServer6R3D = 6	// 三维缓存
};

// 定义数据区域的结构体。最小可定义的区域为像素
struct UGHPDataArea
{

	// 瓦片组在整个缓存内的位置
	int32_t nStartGroupRow;		// 起始瓦片组行号，包含此行
	int32_t nEndGroupRow;		// 终止瓦片组行号，包含此行
	int32_t nStartGroupCol;		// 起始瓦片组列号，包含此列
	int32_t nEndGroupCol;		// 终止瓦片组列号，包含此列

	// 瓦片在整个缓存内的位置
	int32_t nStartTileRow;		// 起始瓦片行号，包含此行
	int32_t nEndTileRow;		// 终止瓦片行号，包含此行
	int32_t nStartTileCol;		// 起始瓦片列号，包含此列
	int32_t nEndTileCol;		// 终止瓦片列号，包含此列

	// 像素在整个缓存中的位置
	int64_t nStartPixelRow;		// 起始像素行号，包含此行
	int64_t nEndPixelRow;		// 终止像素行号，包含此行
	int64_t nStartPixelCol;		// 起始像素列号，包含此列
	int64_t nEndPixelCol;		// 终止像素列号，包含此列
};

struct TileGroupArea
{
	int32_t left;		// 起始瓦片组列号，包含此列
	int32_t top;		// 起始瓦片组行号，包含此行
	int32_t right;		// 终止瓦片组列号，包含此列
	int32_t bottom;		// 终止瓦片组行号，包含此行

	TileGroupArea()
	{
		Reset();
	}

	void Reset()
	{
		left = 0;
		right = -1;
		top = 0;
		bottom = -1;
	}

	void SetValues(int32_t left, int32_t top, int32_t right, int32_t bottom)
	{
		this->left = left;
		this->top = top;
		this->right = right;
		this->bottom = bottom;
	}
};


// 像素在整个缓存中的位置
// 这实际上就是一个 UGRect，不过 UGRect 的成员都是 int 型，在 32 位机器上不能达到范围表示的要求
struct PixelArea
{
	int64_t left;		// 起始像素列号，包含此列
	int64_t top;		// 起始像素行号，包含此行
	int64_t right;		// 终止像素列号，包含此列
	int64_t bottom;		// 终止像素行号，包含此行

	PixelArea()
	{
		Reset();
	}

	int64_t Width() const
	{
		return right - left + 1;
	}

	int64_t Height() const
	{
		return bottom - top + 1;
	}

	void Reset()
	{
		left = 0;
		right = -1;
		top = 0;
		bottom = -1;
	}

	void SetValues(int64_t left, int64_t top, int64_t right, int64_t bottom)
	{
		this->left = left;
		this->top = top;
		this->right = right;
		this->bottom = bottom;
	}
};

//enum TileGroupSize
//{
//	SIZE_16		= 16,
//	SIZE_32		= 32,
//	SIZE_64		= 64,
//	SIZE_128	= 128
//};

// 包含多张瓦片的瓦片区域
struct TileArea
{
	int32_t left;		// 起始瓦片列号，包含此列
	int32_t top;		// 起始瓦片行号，包含此行
	int32_t right;		// 终止瓦片列号，包含此列
	int32_t bottom;		// 终止瓦片行号，包含此行

	TileArea()
	{
		Reset();
	}

	void Reset()
	{
		left = 0;
		right = -1;
		top = 0;
		bottom  = -1;
	}

	void SetValues(int32_t left, int32_t top, int32_t right, int32_t bottom)
	{
		this->left = left;
		this->top = top;
		this->right = right;
		this->bottom = bottom;
	}

	UGulong GetSize()
	{
		return (UGulong(right) - left + 1) * (bottom - top + 1);
	}
};


const unsigned FilterFileCellSize = 5;
const unsigned nMaxDPI = 2000;
const unsigned nMinDPI = 10;
const unsigned nCompactTileHeadSize = 12;	// 目前考虑瓦片头大小12个字节

// Filter File 专用
const unsigned char Filter_Exist_Bit = 0;
const UGint nTileGroupSize = 128;
const UGint PNG8 = 8888;

}

#endif // _UGCACHEFILECOMMON_H_