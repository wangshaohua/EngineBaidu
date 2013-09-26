//#pragma once

#ifndef _UGVECTORCACHEPARAMATER_H_
#define _UGVECTORCACHEPARAMATER_H_

#include "Stream/ugdefs.h"
#include "Geometry/UGDataCodec.h"
#include "Projection/UGPrjCoordSys.h"

namespace UGC
{

// 定义格网范围
struct UGGridArea
{
	// 瓦片在整个渔网内的位置
	UGint nLevel;		// 比例尺层级
	UGint nStartRow;	// 起始行号，包含此行
	UGint nEndRow;		// 终止行号，包含此行
	UGint nStartCol;	// 起始列号，包含此列
	UGint nEndCol;		// 终止列号，包含此列
};

class FILEPARSER_API UGVectorCacheParamater
{
public:
	UGVectorCacheParamater(void);
	virtual ~UGVectorCacheParamater(void);

public:
	enum VectorCacheType
	{
		SCV		= 0,			// 三维缓存
		SCM		= 1,			// 导航缓存
	};
	enum TileSplitType
	{
		GLOBAL		= 0,		// 全球剖分
		LOCAL		= 1,		// 本地剖分
	};
	enum TileStorageType
	{
		Original		= 0,	// 原始文件
		Compact	= 1,	// 紧凑文件
		Single	        = 2, //
	};

public:
	// 导入导出配置文件
	UGbool ToConfigFile(UGString strPath);
	UGbool FromConfigFile(UGString strPath);

	// 根据瓦片的行列号，判断指定瓦片的数据是否存在
	UGbool IsTileExist(UGdouble dScale, UGint nRow, UGint nCol);

	//! \根据地图范围计算图片行列号范围
	//! \param dMapScale [in]		比例尺
	//! \param rcMapBounds [in]		地图范围
	//! \param nStartRow [out]		图片起始行号
	//! \param nEndRow [out]		图片结束行号
	//! \param nStartCol [out]		图片起始列号
	//! \param nEndCol [out]		图片结束列号
	//! \param bBigTileImage [in]	是否是大的图片
	//! remarks 地图缓存使用。主要是出图时使用
	void ComputeTileRange(UGdouble dMapScale, const UGRect2D& rcMapBounds, UGGridArea &GridArea);

	//! \根据给定的比例尺及瓦片行列号计算瓦片范围
	//! \param dMapScale [in]		比例尺
	//! \param nRow [in]			图片行号
	//! \param nCol [in]			图片列号
	//! remarks 地图缓存使用。主要是计算单个瓦片的范围
	UGRect2D ComputeTileMPBounds(UGdouble dMapScale, UGint nRow, UGint nCol);

	//! \根据给定的比例尺及中心点计算瓦片位置
	//! \param dMapScale [in] 比例尺
	//! \param center [in] 指定的中心点
	//! \param nRow [out] 返回瓦片行号
	//! \param nCol [out] 返回瓦片列号
	//! remarks 地图缓存使用。主要是计算瓦片的位置
	void ComputeTilePosition(UGdouble dMapScale, const UGPoint2D &pntCenter, UGint &nRow, UGint &nCol);

	// 计算Tile的全路径名
	UGString ComputeTileFullName(UGdouble dMapScale, UGint nRow, UGint nCol, UGbool bBuild = true);

	UGdouble ComputeScale(UGdouble dMP = 180, UGint nDP = 256);
	UGdouble ComputeMPSize(UGdouble dScale, UGint nDP = 256);


	// 把全坐标的瓦片行列号换算成对应紧凑缓存的行列号
	static void ConvertRowCol(UGint& nRow, UGint& nCol);

	// 通过瓦片组位置计算瓦片的位置
	static void CompactCellPos2TilePos(UGint nTileGroupRow, UGint nTileGroupCol, UGint nCellRow, UGint nCellCol, UGint &nTileRow, UGint &nTileCol);

	// 通过瓦片位置计算瓦片组的位置
	static void TilePos2TileGroupPos(UGint nTileRow, UGint nTileCol, UGint &nGroupTileRow, UGint &nGroupTileCol);


	// 投影信息，会初始化坐标系单位和缓存参考原点
	void				 SetPrjCoordSys(const UGPrjCoordSys &CoordSys);
	const UGPrjCoordSys &GetPrjCoordSys() const;

	//! \brief 获取缓存的版本号
	UGfloat GetVersion() const;
	
	void SetVersion(UGfloat fVersion); 

	void		SetCacheName(const UGString &strCacheName);
	UGString	GetCacheName() const;

	void		SetCachePath(const UGString &strCachePath);
	UGString	GetCachePath() const;

	UGString	GetCacheFolderName() const;
	void			SetCacheFolderName(const UGString& floderName);

	void		SetLevel0MPSize(UGdouble dLevel0MPSize);
	UGdouble	GetLevel0MPSize() const;

	void		SetLevel0DPSize(UGint nLevel0DPSize);
	UGint		GetLevel0DPSize() const;

	void		SetOrigin(UGPoint2D pntOrigin);
	UGPoint2D	GetOrigin() const;


	void		SetDPI(UGdouble dDPI);
	UGdouble	GetDPI() const;


	void		SetVectorCacheType(UGVectorCacheParamater::VectorCacheType nCacheType);
	UGVectorCacheParamater::VectorCacheType 	GetVectorCacheType() const;

	void		SetBounds(UGRect2D rcBounds);
	UGRect2D	GetBounds() const;

	void		SetOutputScaleCaptions(const std::map<UGdouble, UGString> &mapScaleCaptions);
	void		GetOutputScaleCaptions(std::map<UGdouble, UGString> &mapScaleCaptions) const;

	//! \brief 计算指定比例尺下的瓦片MPSize
	UGSize2D ComputeTileMPSize(UGdouble dMapScale);

	// 获取比例尺在比例尺数组中索引，找不到返回-1；
	UGint GetScaleIndex(UGdouble dScale);

	// 根据Level0的MP、DP计算指定比例尺属于第几层，不匹配的比例尺函数返回-1
	UGbyte GetLevel(UGdouble dScale);
	// 根据Level0的MP、DP计算指定层级的比例尺
	UGdouble GetScale(UGbyte nLevel);

	//! \brief获取矢量的类型
	UGint GetDataType() const;
	void SetDataType(UGint nDataType);

	//! \brief 瓦片剖分类型
	void SetTileSplitType(UGVectorCacheParamater::TileSplitType nTileType);
	UGVectorCacheParamater::TileSplitType GetTileSplitType() const;

	//! \brief 瓦片文件存储类型
	void SetTileStorageType(UGVectorCacheParamater::TileStorageType nStoreType);
	UGVectorCacheParamater::TileStorageType GetTileStorageType() const;

	//! \brief瓦片文件的压缩类型
	//! \remarks 现只支持ZIP,默认不压缩
	void SetTileCompressionType(UGDataCodec::CodecType nCompressType);
	UGDataCodec::CodecType GetTileCompressionType() const;

	//! \brief 获得压缩纹理的类型
	//! \remarks 现只支持dds和pvrtc，默认采用dds
	UGDataCodec::CodecType GetTextureCompressionType() const;
	//! \brief 设置压缩纹理的类型
	//! \remarks 现只支持dds和pvrtc，默认采用dds
	void SetTextureCompressionType(UGDataCodec::CodecType nTexCompressionType);

	//! \brief 根据给定比例尺找到最佳匹配比例尺
	UGdouble Round2NearestScale(double dScale);

	//! \brief 设置、获取自定义版本号
	UGint	GetRevisionNumber();
	void	SetRevisionNumber(UGint number);

	//! \brief 添加自定义版本号到版本列表中
	void AddRevisionNumberToSortedArray(UGint nRevisionNumber);

private:
	//! \brief 获取缓存生成的瓦片相对路径，格式为 1000/1/9/2x4
	//! \param dScale [in]		当前出图的比例尺
	//! \return						获取生成的瓦片相对路径
	//! \remarks					规则如下：
	UGString TilePos2RelativeOriginalFileNamePrefix(double dScale, int nRow, int nCol);

	UGString ConvertVectorCacheTypeToString(UGVectorCacheParamater::VectorCacheType nCacheType);
	UGVectorCacheParamater::VectorCacheType ConvertStringToVectorCacheType(UGString strCacheType);


private:
	UGfloat			m_fVersion;					// 缓存版本号
	UGArray<UGint>	m_nRevisionNumberList;		// 用户自定义数据版本数组
	UGString		m_strCacheName;				// 缓存名称。该名称用作缓存作为数据源方式进行加载时的数据源名称，跟文件夹名
	UGdouble		m_dLevel0MPSize;					// 第0层瓦片地理边长。
	UGint			m_nLevel0DPSize;					// 第0层瓦片像素边长。
	std::map<UGdouble, UGString> m_mapOutputScaleCaptions;	// 比例尺、标题

	UGPoint2D		m_pntOrigin;					// 参考原点
	UGdouble		m_dDPI;							// 每英寸有多少个像素，默认值96，组件暂时不对用户开放。

	VectorCacheType		m_nCacheType;					// 文件格式：导航矢量切片、单层矢量切片
	UGPrjCoordSys 		m_PrjCoordSys;					// 投影信息。将地图缓存加载到三维场景中的必须信息。
	UGRect2D			m_rcBounds;						// 缓存的地理范围。缓存作为数据源方式进行加载时的数据源范围，可以用户修改

	
	UGint					m_nDataType;				//! \brief矢量的数据类型，点、线、面，导航的矢量瓦片数据集类型为CAD
	TileSplitType			m_nTileSplitType;			//瓦片剖分类型，本地/全球剖分
	TileStorageType			m_nTileStorageType;			//瓦片文件存储类型
	UGDataCodec::CodecType	m_nTileCompressionType;		//瓦片文件压缩类型
	UGDataCodec::CodecType	m_nTexCompressionType;		//! \brief 纹理压缩格式


	// 以下变量只用于切片的生成时候，不需要保存进scv配置文件中
	UGString		m_strCachePath;					// 缓存存放位置，本目录下级目录是缓存名文件夹的缓存根目文件夹录
	UGString		m_strCacheFolderName;			// 缓存根目文件夹录名，本目录下放置SCV配置文件、投影文件、比例尺层级、数据配置表等文件，默认为"",如果为""则内容跟缓存名相同
	UGint			m_nRevisionNumber;				// 用户当前设置的自定义数据版本号

};
}
#endif //_UGVECTORCACHEPARAMATER_H_