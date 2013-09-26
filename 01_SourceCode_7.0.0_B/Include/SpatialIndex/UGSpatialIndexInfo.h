// UGSpatialIndexInfo.h: interface for the UGSpatialIndexInfo class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_UGSPATIALINDEXINFO_H__DFDA261E_05C0_46C7_A3E6_08A2A6CAA872__INCLUDED_)
#define AFX_UGSPATIALINDEXINFO_H__DFDA261E_05C0_46C7_A3E6_08A2A6CAA872__INCLUDED_

#include "Stream/ugdefs.h"

namespace UGC {

//! \brief 空间索引类型枚举
enum IndexType
{       //! \brief 没有索引
	    IdxNone		= 1,
		//! \brief Rtree索引
		IdxRTree	= 2,
		//! \brief 四叉树索引
		IdxQTree	= 3,	
		//! \brief 图幅索引 UGC里不支持编辑	
		IdxTile		= 4,		
		//! \brief multi-level Grid
		IdxDynamic  = 5,		
};

#if !defined SYMBIAN60 && !defined  OS_ANDROID && !defined (IOS)
class SPATIALINDEX_API UGSpatialIndexInfo 
#else
class ENGINE_API UGSpatialIndexInfo 
#endif
{
public:
	//! \brief 索引类型构造
	UGSpatialIndexInfo();

	//! \brief 索引类型构造
	UGSpatialIndexInfo(IndexType nIndexType);

	//! \brief 多级网格索引构造函数
	UGSpatialIndexInfo(UGPoint2D	pntCenter,
						UGdouble	dGrid0,
						UGdouble	dGrid1,
						UGdouble	dGrid2,
						UGdouble	dGridRatio);

	//! \brief R树索引构造函数
	UGSpatialIndexInfo(UGint nQuality,UGString strSort);

	//! \brief 图幅索引
	UGSpatialIndexInfo(UGString	strTileFieldName);

	//! \brief 图幅索引
	UGSpatialIndexInfo(UGdouble	dWidth,UGdouble	dHeight);

	//! \brief 四叉树索引
	UGSpatialIndexInfo(UGint nLevel);

	//! \brief
	UGSpatialIndexInfo& operator=(const UGSpatialIndexInfo& info);

	//! \brief 索引析构
#ifdef SYMBIAN60
	~UGSpatialIndexInfo();
#else
	virtual ~UGSpatialIndexInfo();
#endif

public:
	//! \brief 空间索引类型
	IndexType	nIndexType; 

	//! \brief R树，这个值 * 50，为叶子包的对象个数
	UGint		nQuality;	

	//! \brief 扩展，R树索引权重字段，如果为了显示，并且QueryMode 为FuzzyQuery的时候使用
	UGString	strSort;

	//! \brief 图幅索引，创建索引依赖的字段
	UGString	strTileFieldName;

	//! \brief 图幅索引，创建索引格子的宽度
	UGdouble	dWidth;
	//! \brief 图幅索引，创建索引格子的高度
	UGdouble	dHeight;

	//! \brief 多级网格索引中中心点的位置
	UGPoint2D	pntCenter;	
	//! \brief 多级网格索引中0级的格子的宽度
	UGdouble	dGrid0;
	//! \brief 多级网格索引中1级的格子的宽度
	UGdouble	dGrid1;	
	//! \brief 多级网格索引中2级的格子的宽度
	UGdouble	dGrid2;
	//! \brief 多级网格索引中格子的大小
	UGdouble	dGridRatio;
};

}

#endif // !defined(AFX_UGSPATIALINDEXINFO_H__DFDA261E_05C0_46C7_A3E6_08A2A6CAA872__INCLUDED_)

