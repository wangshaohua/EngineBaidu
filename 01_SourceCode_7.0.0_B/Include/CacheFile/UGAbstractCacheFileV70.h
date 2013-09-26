/*
缓存配置文件，主要应用于保存缓存的一些公共配置信息。上层会有缓存的生成和读取代码。网络地图等功能，
必须根据这个配置文件，生成符合路径规则的缓存文件，Supermap的上层程序才能统一打开显示。
目录规则为：
第一级为根目录文件夹，是整个缓存存放的位置。文件夹名任意取，内部会存SCI的配置文件和各个比例尺的文件夹
第二级为各个比例尺文件夹，有几级比例尺缓存就会有几个文件夹，文件夹的命名必须是比例尺倒数的直接取整，比如1:5000.9的文件夹名为5000
第三级为大块文件夹，缓存会先分成大块，会存放16*16张图片或者128*128等图片，命名必须是行列号
第四级为具体图片文件

网络地图生成缓存流程：
1 创建第一级目录文件夹
2 在第一级目录文件夹里边调用 ToConfigFile 构造SCI配置文件
3 根据范围计算最终小图片的起始终止行列号，调用函数 ComputeTileRange
4 双重for循环，根据每一个小图片的行列号计算 相对全路径名，调用接口 ComputeTileFileName 
														格式为 1000/1x9/2x4.jpg
5 根据 相对全路径名，判断本地是否已经有缓存小图片了，没有则判断文件夹 1000/00000001x00000009 是否需要创
建，然后根据小图片范围下载相应数据
*/


// NOTE 将来改进重点
// 精确定义
// 完全验证计算公式精确，包括在负数情况下
// 考虑是否是带有比例尺参数的函数只能够接受设定的比例尺。如果这样，则只需要比例尺的下标即可。该下标是用户设置的比例尺下标，还是排序后的比例尺下标？
// PixelArea 是唯一的自定义类，瓦片编号、瓦片组编号、瓦片范围、瓦片组范围、像素编号，都采用标量。去掉 DataTileArea 等。
// 该类、文件改名为 UGHPMapCacheFile。

#ifndef _UGABSTRACTCACHEFILEV70_H_
#define _UGABSTRACTCACHEFILEV70_H_

#include "FileParser/UGExchangeFileType.h"
#include "Base/ogdccolordef.h"
#include "Stream/UGByteArray.h"
#include "CacheFile/UGCacheFileCommon.h"
#include "Geometry/UGGeoRegion.h"
#include "Toolkit/UGMarkup.h"
#include "Stream/UGCacheFile.h"


#define SUPERMAPSCI 0
#define ARCGISXML 1

#include <vector>

namespace UGC
{

class CACHEFILE_API UGAbstractCacheFileV70
{

	class FilterFileCell
	{
	public:
		char data[FilterFileCellSize];
		UGbool IsExist();
		void SetExist(UGbool bExist = true);

		UGColor GetColor();
		void SetColor(UGColor color);

		char *GetData();
		FilterFileCell();
	};

	friend class UGMapCacheFile;

public:
	UGAbstractCacheFileV70();
	~UGAbstractCacheFileV70();

	// 版本号，默认为最新版本。
	void				SetCacheVersion(UGMapCacheVersion nVersion);
	UGMapCacheVersion	GetCacheVersion() const;

	// 内部版本编号
	void				SetFullCacheVersion(UGint nVersion);
	UGint				GetFullCacheVersion() const;

	// 缓存名称设置
	UGbool			SetCacheName(const UGString &strCacheName);
	const UGString &GetCacheName();
	const UGString &GetFinalCacheName();

	// 数据来源设置
	UGbool			SetServiceProvider(const UGString &strServiceProvider);
	const UGString &GetServiceProvider();

	// 投影信息，会初始化坐标系单位和缓存参考原点
	void				 SetPrjCoordSys(const UGPrjCoordSys &CoordSys);
	const UGPrjCoordSys &GetPrjCoordSys() const;

	// 图片策略，比如是透明Png32、不透明Png32、Png8、Jpeg、混合图片模式
	UGbool		SetMixedImageType(unsigned nPictureFormat);
	unsigned	GetMixedImageType() const;

	UGint				GetIntImageType();
	UGbool				SetIntImageType(UGint nType);

	UGFileType::EmType	GetSingleImageType();
	UGbool				SetSingleImageType(UGFileType::EmType nType);

	UGint GetTileGroupSize() { return nTileGroupSize; }

	// 单张图片像素大小
	UGbool	SetTileSize(UGint nTileSize);
	UGint		GetTileSize() const;

	// 数据范围，以地理坐标为单位
	void			SetBounds(const UGRect2D &rcBounds);
	const UGRect2D &GetBounds() const;
	const UGRect2D GetFinalBounds();

	TileArea GetFinalExtendedTileArea(UGdouble dScale);

	// 每毫米有多少个像素，默认每毫米3个像素，x方向和y方向比率一致吧
	UGbool		SetCoordRatio(UGdouble dCoordRatio);
	UGdouble		GetCoordRatio();

	void		SetDPI(UGdouble dCoordRatio);
	UGdouble	GetDPI();

	void SetHashCodeEnabled(UGbool bValue = true);
	UGbool IsHashCodeEnabled();

	void			SetIndexBounds(const UGRect2D &rcIndexBounds);
	const UGRect2D &GetIndexBounds();
	UGRect2D		GetFinalIndexBounds();

	// 比例尺信息，这块要求，不要存比例尺的倒数了
	// 如果所有比例尺都在正常范围，即均为正数，返回 true；否则返回 false，并且不对比例尺设置进行任何修改。//是否设置了固定比例尺
	UGbool					SetOutputScales(const std::vector<UGdouble>& vectOutputScales,UGbool bIsDisplayByScales = false);
	std::vector<UGdouble>		GetOutputScales();
	std::vector<UGdouble>		GetSortedOutputScales();		// TODO 完全去掉

	UGbool SetOutputScaleCaptions(const std::map<UGdouble, UGString> &mapOutputScaleCaptions);
	void GetOutputScaleCaptions(std::map<UGdouble, UGString> &mapOutputScaleCaptions);
	const std::map<UGdouble, UGString> &GetOutputScaleCaptions();

	// 是否紧凑缓存，默认不是紧凑
	void	SetIsCompactCache(UGbool bCompactCache);
	UGbool	IsCompactCache();

	// 根据指定的全路径名导出/导入SCI配置文件。
	UGbool ToConfigFile(const UGString& strCacheFile,UGbool bChangeOutputDir=true);//添加UGbool是否修改输出路径，inf文件不修改路径
	UGbool FromConfigFile(const UGString& strCacheFile);
	UGbool ToProjection(const UGString& strProjectionFile);//投影信息记录到文件
	UGbool FromProjection(const UGString& strProjection);

	//UGbool ToInfFile(const UGString &strInfPath);

	// 打开，关闭缓存文件
	// strCacheFile，缓存文件 .sci 路径。
	// strPassword，大文件缓存密码
	UGbool Open(const UGString &strCacheFile, const UGString &strPassword = _U(""));
	void Close();

	// 缓存存放位置
	// strFileDirectory 该位置为缓存顶层文件夹所在路径。
	// 例如，如果将路径设置为 D:\NE，则缓存的 .sci 路径为 D:\NE\CacheName\CacheName.sci。
	void			SetFileDirectory(const UGString &strFileDirectory);
	const UGString &GetFileDirectory();

	const UGString &GetCacheFileName();

	// 设置/判断 margin 是否填充内容
	// bFillMargin == true，填充数据。bFillMargin == false，绘制为白色或透明。
	void SetFillMargin(UGbool bFillMargin);
	UGbool IsFillMargin();

	// 设置/获取缓存图片压缩率
	// 如果设置值超出了 [0, 100] 的范围，返回 false，并且不对原有设置进行修改
	// 最大压缩 0，最高质量 100。
	void	SetImageCompress(UGint nCompress);
	UGint		GetImageCompress();

	// 设置/获取图片背景色是否透明
	void	SetTransparentBack(UGbool bTransparentBack);
	UGbool	IsTransparentBack();
	UGbool	IsFinalTransparentBack();

	// 设置/获取裁剪区域
	// 如果没有设置裁剪区域，获取结果为 NULL。
	UGbool				SetClipRegion(UGGeoRegion *pClipRegion);
	const UGGeoRegion  *GetClipRegion();

	// 设置/判断是否为全球剖分
	void		SetTileType(TileType tileType);
	TileType	GetTileType();

	// 设置/获取地图范围
	// 如果没有设置缓存范围，则使用地图范围
	// 如果没有设置索引范围，则使用地图范围
	void			 SetMapBounds(const UGRect2D &rcMapBounds);
	const UGRect2D	&GetMapBounds();

	// 地图名。
	// 如果没有设置缓存名，则缓存名为地图名
	void			 SetMapName(const UGString &strName);
	const UGString	&GetMapName();

	// 数据集名。
	// 如果没有设置缓存名，则缓存名为数据集名
	void			 SetDatasetName(const UGString &strName);
	const UGString& GetDatasetName();

	// 设置/获取 hash 值。
	// 注意，该 hash 值仅仅是最终 hash 值的一个参考。
	// 最终 hash 值是该 hash 值经过 AdjustHashCode() 调整之后的结果
	// 获取的 hash 值为最终 hash 值
	UGString   &GetHashCode();
	void		SetHashCode(const UGString &strHashCode);

	void		SetDynamicCache(UGbool bDynamic);
	UGbool		IsDynamicCache();

	// 根据缓存图片是否透明以及缓存图片格式是否支持透明来调整 hash 值为最终 hash 值
	// TODO 将来改为 private，使用自动调整的方式来实现
	void		AdjustHashCode(UGString &strHashCode);

	// 默认过滤色的获取与设置
	void	SetDefaultColor(UGColor color);
	UGColor	GetDefaultColor();

	// =================== 像素范围、地理范围、比例尺、行列号、路径名转换 ===================
	UGbool PixelArea2MPBounds(UGdouble dScale, const PixelArea &rcPixelArea,	UGRect2D &rcMPBounds);

	// 在指定比例尺下地理范围转换为像素范围。下面有三个转换函数，需要慎重选择。

	// 当地理范围与任何像素相交时，即使只占了像素的极少一部分，也认为包含在该像素内
	UGbool MPBounds2PixelAreaInclusive(UGdouble dScale, const UGRect2D &rcMPBounds,	PixelArea &pixelArea);

	// 当地理范围与任何像素相交时，即使只占了像素的绝大部分，只要有区域没有相交，也认为不包含在该像素内
	UGbool MPBounds2PixelAreaExclusive(UGdouble dScale, const UGRect2D &rcMPBounds,	PixelArea &pixelArea);

	// 当地理范围与像素相交时，相交的边界按四舍五入的方式进行判断。大部分使用者需要使用的是该函数。
	// 该函数能够保证通过PixelArea2MPBounds再次转换回来时与原地理范围最接近。但仍不能保证相同。
	UGbool MPBounds2PixelAreaRounded(UGdouble dScale, const UGRect2D &rcMPBounds,	PixelArea &pixelArea);

	// 将地理点转换为像素坐标
	UGbool MPPos2PixelPos(UGdouble dScale, const UGPoint2D &pntPosition, PixelArea &pixelArea);

	UGbool TileArea2PixelArea(const TileArea &tileArea,	PixelArea &rcPixelArea);
	UGbool PixelArea2TileArea(const PixelArea &rcPixelArea,	TileArea &tileArea);

	UGbool TileArea2TileGroupArea(const TileArea &tileArea, TileGroupArea &tileGroupArea);
	UGbool TileGroupArea2TileArea(const TileGroupArea &tileGroupArea, TileArea &tileArea);

	// 把全坐标的瓦片行列号换算成对应紧凑缓存的行列号
	static void ConvertRowCol(UGint& nRow, UGint& nCol);
	static void CompactCellPos2TilePos(UGint nTileGroupRow, UGint nTileGroupCol, UGint nCellRow, UGint nCellCol, UGint &nTileRow, UGint &nTileCol);

	// =========================================================================================

	// 合并地图缓存
	// strPath，合并进当前地图缓存的外部地图缓存，须指向 SCI 文件
	// strPassword，当外部地图缓存为紧凑存储时，打开地图缓存的密码
	UGbool Merge(const UGString &strPath, const UGString &strPassword = _U(""));

	UGbool Convert(StoreType storeType, const UGString &strDest, const UGString &strPassword);
	UGbool ConvertSingleCompactFile(const UGString &strCompactFilePath, const UGString &strDest);

	std::vector<UGTile*> *GetTiles(const UGRect2D &rcBounds, UGdouble dScale, UGString strPwd, UGString strHashCode, UGCompactFileWrapper *pCompactFile, UGint nImageType, UGbool bTransparent, UGbool bPreciseMatch);

	// MPPoint2PixelPos ----> PixelPos2TilePos
	//! \根据给定的比例尺及中心点计算瓦片位置
	//! \param dScale [in] 比例尺
	//! \param center [in] 指定的中心点
	//! \param nRow [out] 返回瓦片行号
	//! \param nCol [out] 返回瓦片列号
	//! remarks 地图缓存使用。主要是计算瓦片的位置
	// NOTE 仅供 UGMapCacheFile 使用，其它地方不得使用。
	void ComputeTilePosition(UGdouble dScale, const UGPoint2D &pntCenter, UGint &nRow, UGint &nCol);

	// 是否包含某种图片类型
	UGbool ContainsPNGTypeP(unsigned nImageType);
	UGbool ContainsBMPTypeP(unsigned nImageType);
	UGbool ContainsJPGTypeP(unsigned nImageType);
	UGbool ContainsGIFTypeP(unsigned nImageType);

	// 将浮点型的比例尺转换为整数，例如 .5 转换成整数为 2，该整数用来生成缓存目录名
	unsigned	Scale2ScalePathName(UGdouble dScale);		
	UGdouble		ScalePathName2Scale(unsigned nScale);


	// 通过图片类型获取文件后缀名
	static UGString GetFileExtName(UGFileType::EmType nPictureFormat);

	// 保存紧凑缓存瓦片。
	// 要求瓦片在外部已经完全构建完毕，包含瓦片头部。
	UGbool OpenCompactFile(UGdouble dScale, UGint nRow, UGint nCol, UGCompactFileWrapper &compactFile, UGbool bCreateIfAbsent = false);
	UGbool CreateCompactFile(UGdouble dScale, UGint nRow, UGint nCol, UGCompactFileWrapper &compactFile);
	UGbool CreateOrgSolidCompactFile(UGdouble dScale, UGint nRow, UGint nCol, UGCompactFileWrapper &compactFile, UGbool bCreateIfAbsent = false);
	// 比例尺排序
	void SetOutputScales_aux(const std::vector<UGdouble>& vectOutputScales,UGbool bIsDisplayByScales = false);//是否设置了固定比例尺

	//! \根据给定的比例尺及瓦片行列号计算瓦片范围
	//! \param dScale [in]		比例尺
	//! \param nRow [in]			图片行号
	//! \param nCol [in]			图片列号
	//! remarks 地图缓存使用。主要是计算单个瓦片的范围
	UGRect2D ComputeTileMPBounds(UGdouble dScale, UGint nRow, UGint nCol);

	//! \根据给定的比例尺及瓦片行列号范围计算瓦片范围
	//! \param dScale [in]		比例尺
	//! \param TileDataArea [in]	瓦片行列号范围
	//! remarks 地图缓存使用。主要是计算多行多列瓦片的范围
	UGRect2D ComputeTileMPBounds(UGdouble dScale, const UGHPDataArea &TileDataArea);

	UGRect2D ComputeTileMPBounds(const UGString& strFileName, UGbool bGlobal = false);
	void ComputeImageFileName(const UGPoint2D &pntCenter, UGdouble dScale, UGString& vectAbsoluteFileNames);
	void ComputeImageFileName(const UGRect2D &rcMPCellImageBounds, UGdouble dScale, std::vector<UGString>& vectAbsoluteFileNames);

	// 重置所有成员
	void Reset();

	// 重置文件内容
	void ResetSCIContent();

	// bSingleTile，是否要求制定的地理范围必须是单张瓦片的范围。若为false，则给定的地理范围可以是多张瓦片的范围。
	UGbool CheckTileBoundsValid(const UGRect2D &rcMPTileBounds, UGdouble scale, UGbool bSingleTile = true);

	// 构建一副纯色图片
	UGbool ConstructSolidImageFile(const UGString &strAbsoluteFileName, UGColor color, UGFileType::EmType fileType);

	// 根据地图投影、地图比例尺、地图范围和像素范围计算每毫米有多少个像素，用于内部计算
	static UGdouble ComputeCoordRatio(const UGPrjCoordSys& prjCoordSys, UGdouble dScale, UGdouble dMapWidth, UGint nPixelWidth);

	// 根据地图投影和初始像素宽度初始地图宽度计算比例尺
	static std::vector<UGdouble> ComputeMapScale(const UGPrjCoordSys& prjCoordSys, UGdouble dMapWidth, UGint nPixelWidth, 
												UGint nScaleCount = 22, UGdouble dCoordRatio = 3);

	//根据地图投影、初始像素宽度和比例尺，计算层级
	static UGint ComputeLevelByScale(const UGPrjCoordSys& prjCoordSys, UGdouble dLevel0Width, UGdouble dScale, UGint nPixelWidth,
									UGdouble dCoordRatio = 3);

	// 根据地图投影和初始像素宽度计算某一层级对应比例尺
	static UGdouble ComputeMapScaleByLevel(const UGPrjCoordSys& prjCoordSys, UGint nPixelWidth, UGint nLevel, UGdouble dCoordRatio);


	static std::vector<UGint> ComputeLevel(const UGPrjCoordSys& prjCoordSys, UGdouble dMapWidth, 
											UGint nPixelWidth, const std::vector<UGdouble>& scales, UGdouble dCoordRatio);

	UGbool Extract(const std::vector<UGdouble> &vectScales, const UGGeoRegion &region, StoreType storageType, const UGString &strOutputPath);

	UGbool Extract(const UGGeoRegion &region, const UGString &strOutputPath);

	UGbool Clear(const UGRect2D &rcBounds, UGdouble dScale, UGbool clearFolder =false);
	UGbool Clear(UGdouble dScale, const UGGeoRegion *pRegion);

	void ClearDynamicCache(const UGRect2D &rcBounds);

	// 通过比例尺转换瓦片边长对应的地理大小
	UGSize2D ComputeTileMPSize(UGdouble dScale) const;

	//为了求准确的象素长，临时加下面两个函数，用的地方不多。（没有求UGdouble类型的象素位置的函数，所以先这么求下）
	UGdouble GetUnitsRatio();

	UGbool HitTest(const UGPoint2D &pntPosition, UGdouble dScale);

	UGbool Reload();

	// 根据文件流检查图片数据类型，并返回
	static UGFileType::EmType DataHeaderToImageType(const UGbyte* pData);

	// 根据瓦片的行列号，判断指定瓦片的数据是否存在
	// dScale		当前出图的比例尺
	UGbool IsTileExist(UGdouble dScale, UGint nRow, UGint nCol) ;

	// 根据传入的TileData中的比例尺，获取Tile的地理范围和像素范围
	void GetTileInfo(UGTile& TileData, UGCompactFileWrapper *pCompactFile);

	// 根据传入的TileData中的比例尺和行列号，获取Tile的地理范围和像素范围，及Tile的数据流及图像格式
	UGbool GetTileData(UGTile& TileData, UGCompactFileWrapper *pCompactFile);

	// NOTE 返回的 UGGeoRegion 对象由外部释放！
	UGGeoRegion *GetValidRegion(UGRect2D rcBounds, UGdouble dScale);

	UGbool TilePos2PixelArea(UGdouble dScale, UGint nRow, UGint nCol, PixelArea &pixelArea);

	//! \brief  设置/获取缓存密码,当m_nstroeType为MIXED_FILES或SINGLE_FILE时，密码才会起作用。
	void SetPassword(const UGString& strPwd);
	const UGString &GetPassword();

	UGbool SetPropertiesByPreCaption(const UGString &strPreCaption);
	UGString GeneratePreCaption();

	UGint GetSourceType();

	// 获取用户扩展字段的引用，可直接修改。
	// 如果map的元素个数不为0，会依次保存元素到配置文件里边
	std::map<UGString, UGString>& UserExtendField();

	// =================== 瓦片类型、图片类型转换相关 ===================

	// 将UGFileType转换为UGint
	static UGbool ConvertImageTypeToInt( const UGFileType::EmType & eFileType, UGint &nFileType);
	static UGbool ConvertIntToImageType( const UGint &nFileType, UGFileType::EmType & eFileType);

	// 将UGint与Mixed实现互转
	static void ConvertMixedToInt( const unsigned & unFileType, UGint &nFileType);
	static UGbool ConvertIntToMixed( const UGint &nFileType, unsigned & unFileType);
	
	// 将Mixed与UGString实现互转
	static UGbool ConvertMixedToString( const unsigned & unFileType, UGString &strFileType);
	static UGbool ConvertStringToMixed( const UGString &strFileType, unsigned & unFileType);

	// ===================================================================


	//! \brief 获取缓存生成的瓦片相对路径，格式为 1000/1/9/2x4
	//! \param dScale [in]		当前出图的比例尺
	//! \return						获取生成的瓦片相对路径
	//! \remarks					规则如下：
	UGString TilePos2RelativeOriginalFileNamePrefix(UGdouble dScale, UGint nRow, UGint nCol, UGbool bIsCreat = false);

	// 530000/3/5/7x12.3f2d0c
	UGString TilePos2RelativeSolidPicFileNamePrefix(UGdouble dScale, UGint nRow, UGint nCol, UGColor color);

	UGbool SaveCompactCellData(UGdouble dScale, UGint nRow, UGint nCol, const UGbyte *pData, size_t nSize, UGCompactFileWrapper &compactFile);

	UGbool SaveCompactImageData(UGdouble dScale, UGint nRow, UGint nCol, const UGbyte *pData, size_t nSize, UGbool bSolidColor, UGColor color, UGCompactFileWrapper &compactFile);

	//! \brief 根据瓦片的行列号，把相应数据存到相应路径中
	//! \param dScale [in]		当前出图的比例尺
	// 如果 nSize 为 sizeof(UGColor)，则表示为纯色图片。
	void SaveOriginalImageData(UGdouble dScale, UGint nRow, UGint nCol, const UGbyte* pData, size_t nSize, UGbool bSolid = false);

	//! \brief 根据瓦片的行列号，把相应数据取出来
	//! \param dScale [in]		比例尺
	//! \param nRow [in]			图片行号
	//! \param nCol [in]			图片列号
	//! \param pData [out]			图片数据，如果bSolidColor为true数据就是颜色值，否则就是整个图片的颜色
	//! \param nSize [out]			图片数据大小
	//! \param bSolidColor [out]	是否是纯色图片，只在紧凑型缓存中起作用
	//! \return						是否成功获取到数据
	//! \remarks					规则如下：
	// NOTE 当 bSolidColor 为 false 时，ByteArray 的内容是已经压缩了的图片内容，例如 PNG、JPG 文件内容
	// 当 bSolidColor 为 true 时，ByteArray 的内容只有一个 UGColor 大小，指示的是纯色图片的颜色值
	UGbool LoadImageData(UGdouble dScale, UGint nRow, UGint nCol, UGByteArray &ByteArray, UGbool &bSolidColor, UGCompactFileWrapper *pCompactFile, UGColor &color);
	UGbool LoadImageData(UGdouble dScale, UGint nRow, UGint nCol, UGByteArray &ByteArray, UGbool &bSolidColor, UGCompactFileWrapper *pCompactFile, UGColor &color, UGint nRequiredImageType, UGbool bTransparent, UGbool bPreciseMatch);

	//! \brief 获取用户自定义最新版本
	UGint GetRevisionNumber();

	//! \brief 设置用户自定义最新版本
	void SetRevisionNumber(UGint number);

	//! \brief 获取用户设置的自定义版本中最大的版本号
	UGint GetMaxRevisionNumber();

	// 添加当前用户自定义版本到版本存放列表
	void AddRevisionNumberToList();

	//! \brief 删除特定的已生成的用户自定义版本
	void DeleteRevisionNumber(UGint value);

private:

	UGAbstractCacheFileV70 &operator=(const UGAbstractCacheFileV70 &rhs);
	UGAbstractCacheFileV70(const UGAbstractCacheFileV70 &rhs);

	// 将源缓存中的所有纯色图片复制到目标缓存中。
	// 严格来说这并不是一个好的方式。正确的方式应当是在瓦片组行、列循环中查找纯色图片并进行复制，而不是一次性复制过去。
	// 一次性复制过去会导致原本不属于缓存的，不在 sci 中进行说明的 caption 下的纯色图片也被复制。
	void CopySolidFiles(UGAbstractCacheFileV70 *pDest, UGAbstractCacheFileV70 *pSrc);
	UGbool IsSolidPic(const UGString &strFileName);

	// ============================ 存储、读取瓦片相关函数 ============================

	// NOTE
	// SaveOriginalImageData() 和 LoadImageData() 之间具有一种不对称性：
	// SaveOriginalImageData() 只能用来保存原始缓存
	// LoadImageData() 既可以读取原始缓存，也可以读取紧凑缓存
	void SaveSolidOriginalImageData(UGdouble dScale, UGint nRow, UGint nCol, const UGbyte* pData, size_t nSize);


	// 获得原始瓦片图片内容，无论是否为纯色。失败返回 false，byteArray 不会被清空。
	UGbool LoadOriginalImageData(UGdouble dScale, UGint nRow, UGint nCol, UGByteArray &ByteArray, UGbool &bSolidColor, UGColor &color, UGint nRequiredImageType, UGbool bTransparent, UGbool bPreciseMatch);

	// 获得非纯色的原始瓦片内容。如果为没有找到，返回 false，byteArray 不会被清空。没有找到通常意味着是纯色图片，还需要通过
	// LoadSolidOriginalImageData() 来读取数据
	// 仅供 LoadOriginalImageData() 使用
	UGbool LoadNonSolidOriginalImageData(UGdouble dScale, UGint nRow, UGint nCol, UGByteArray &ByteArray, UGint nRequiredImageType, UGbool bTransparent, UGbool bPreciseMatch);

	// 获取纯色瓦片内容。如果没有找到，返回 false，byteArray 不会被清空
	// 仅供 LoadOriginalImageData() 使用
	UGbool LoadSolidOriginalImageData(UGdouble dScale, UGint nRow, UGint nCol, UGByteArray &ByteArray, UGColor &color, UGint nRequiredImageType, UGbool bTrnasparent, UGbool bPreciseMatch);

	// 读取大文件缓存中单个图片位置中存储的内容，包含存储于图片之前的头部
	UGbool LoadCompactCellData(UGdouble dScale, UGint nRow, UGint nCol, UGByteArray &ByteArray, UGCompactFileWrapper &compactFile);

	// 读取大文件缓存中单个图片的图片内容。nRow 和 nCol 是瓦片行列号
	UGbool LoadCompactImageData(UGdouble dScale, UGint nRow, UGint nCol, UGByteArray &ByteArray, UGbool &bSolidColor, UGColor &solidColor, UGCompactFileWrapper &compactFile, UGint nRequiredImageType, UGbool bTransparent, UGbool bPreciseMatch);

	// ================================================================================

	// 地图缓存合并可行性检查
	UGbool Merge_Feasibility_Check(UGAbstractCacheFileV70 *pExtCacheFile);

	// 合并 SCI 文件
	UGbool Merge_SCI_File(UGAbstractCacheFileV70 *pExtCacheFile);

	// 读取 SuperMap SCI 文件
	// strConfigFile，SCI 文件路径
	UGbool FromSuperMapSCIConfigFile(const UGString &strConfigFile);

	// 读取 ArcGIS XML 文件
	// strConfigFile，XML 文件路径
	UGbool FromArcGISXMLConfigFile(const UGString &strConfigFile);

	// 检测紧凑存储下密码是否正确
	UGbool IsPassWordCorrect(const UGchar* strSCIFileName, const UGchar * strPassword);

	// 当前 5.0 缓存已经不采用 filter 文件来存储纯色信息，但是，这种方式在将来可能仍然有使用价值。故保留 filter 文件相关代码
	// 普通存储下 filter 文件操作
	UGbool SaveFilterFileContent(UGdouble dScale, UGint nRow, UGint nCol, FilterFileCell cell);
	UGbool SaveFilterFileContent(FILE *fd, UGint nRow, UGint nCol, FilterFileCell cell);
	FILE *CreateFilterFile(const UGString &strPath);
	UGbool LoadFilterFileContent(UGdouble dScale, UGint nRow, UGint nCol, FilterFileCell &cell);
	FILE *OpenFilterFile(UGdouble dScale, UGint nRow, UGint nCol, UGbool bCreateIfNotExist);
	UGString TilePos2RelativeFilterFileName(UGdouble dScale, UGint nRow, UGint nCol);

	// ============================== 瓦片位置到文件名的转换函数 ==============================

	// 获得顶层文件夹路径，以 '/' 结尾
	UGString GetTopLevelPath();

	// 获得 Precaption 路径，以 '/' 结尾
	UGString GetPrecaptionPath();

	// 从比例尺获得 Caption 路径，以 '/' 结尾
	// 比例尺必须矫正后使用
	UGString GetCaptionPath(UGdouble dScale);

	// 从比例尺、瓦片的行列号获得瓦片组行路径，以 '/' 结尾
	// 比例尺必须矫正后使用
	UGString GetTileGroupRowPath(UGdouble dScale, UGint nRow, UGint nCol);

	// 从比例尺、瓦片的行列号获得瓦片组列路径，以 '/' 结尾
	// 比例尺必须矫正后使用
	UGString GetTileGroupColPath(UGdouble dScale, UGint nRow, UGint nCol);

	// TODO 该函数将来将完全被 TilePos2FileName 替换掉
	// NOTE 当前仅供 ComputeImageFileName() 使用
	UGbool TilePos2RelativeFileName(UGdouble dScale, UGint nRow, UGint nCol, UGString &strFileName);

	// _alllayers/L02/R000049e7/C0000687e
	UGString TilePos2RelativeArcGISOriginalFileNamePrefix(UGdouble dScale, UGint nRow, UGint nCol);

	// 获得原始瓦片的文件相对于 FileDirectory 的路径。纯色、非纯色均适用。纯色瓦片返回 530000/ 3/5/7x12.ffee33.solid 的形式。
	// NOTE 该函数需要读取磁盘，速度慢
	UGString GetSolidOriginalTileFileName(UGdouble dScale, UGint nRow, UGint nCol, UGColor &color);

	// 530000/3/5
	UGbool TilePos2RelativeSuperMapFileName_aux(UGdouble dScale, UGint nRow, UGint nCol, UGString &strPath);


	//! \brief 获取缓存生成的瓦片相对SCI文件的路径，格式为 1000/1/9.cf
	//! \param dScale [in]		当前出图的比例尺
	//! \return						获取生成的瓦片相对路径
	//! \remarks					规则如下：
	UGString TilePos2RelativeCompactFileName(UGdouble dScale, UGint nRow, UGint nCol, UGbool bIsCreat = false);

	UGColor SolidString2Color(const UGString &strColor);
	static UGString Color2SolidString(UGColor color);

	UGbool IsRequiredImageTypeSatisfied(UGFileType::EmType emRealFileType, UGint nRequiredImageType, UGbool bTransparent, UGbool bPreciseMatch);
	// =========================================================================================

	// 获取相近比例尺
	UGdouble ScaleToNearFixScale(UGdouble dScale);

	// NOTE 仅供 GetValidRegion 使用，没有错误检查
	void _MergeTileArea2GeoRegion(UGdouble dScale, const UGRect2D &rcBounds, const TileArea &tileArea, UGGeoRegion *region);

	// 比例尺在排序后的比例尺中的下标。
	// 由于 Scale 的数目极少，使用 UGint 值完全可以。不必要使用容器的 size_type。
	// 0 起。返回 -1 表示错误。
	// NOTE 一定要检查该函数的返回值
	UGdouble Round2NearestScale(UGdouble dScale);

	void DebugValidateScale(UGdouble dScale);

	UGbool IsPathSet();


	// 调整 m_dUnitsRatio 成员。
	void AdjustUnitsRatio();

	// DPI 与 CoordRatio 相互转换
	UGdouble		DPI2CoordRatio(UGdouble nDPI) const;
	UGdouble		CoordRatio2DPI(UGdouble dCoordRatio) const;

	// 维护一张版本号和最低可打开某版本的对照表，导出的时候，根据m_nVersion计算相应最低打开版本存到配置文件。
	// 比如1、2、3的最低打开版本为1;4版本有大改动，要求4版本的最低打开版本只能为4。用户用4版本生成最新缓存并
	// 在配置里存的需求最低软件版本为4，另一个用户用3版本软件打开、导入时知道存储的最低需求版本是4，大于3版
	// 本软件的nMyVersion,这个时候，3软件版本就打开失败。这样是为了避免低版本打开改动较大新版本的兼容问题。
	unsigned	Version2RequiredVersion();

	// 通过瓦片位置计算瓦片组的位置
	void TilePos2TileGroupPos(UGint nTileRow, UGint nTileCol, UGint &nGroupTileRow, UGint &nGroupTileCol);

	// 递归遍历目录删除自定义版本缓存文件
	void DeleteRevisionNumber(UGString strPath, UGString strPattern);

	// ============================== 数据成员 ==============================
	// 下面的成员在缓存配置文件中出现
	//UGMapCacheVersion m_nCacheVersion;		// 当前缓存的版本号。在 ToConfigFile() 中该版本号指示了要导出的文件格式
	UGint	m_nFullCacheVersion;				// 当前缓存的完整版本号
	UGString m_strServiceProvider;				// Service Provider
	UGString m_strCacheName;					// 缓存名称。该名称用作缓存作为数据源方式进行加载时的数据源名称
	UGPrjCoordSys *m_pPrjCoordSys;				// 投影信息。将地图缓存加载到三维场景中的必须信息。
	unsigned m_nImageType;						// 图片格式
	UGint m_nTileSize;							// 瓦片像素边长。
	UGint m_nTileWidth;							// 瓦片像素宽
	UGint m_nTileHeight;						// 瓦片像素高
	UGRect2D m_rcBounds;						// 缓存的地理范围。缓存作为数据源方式进行加载时的数据源范围
	UGdouble m_dCoordRatio;						// LP/DP 转换比率，单位为(像素/毫米)。
	UGRect2D m_rcIndexBounds;					// 索引范围
	UGbool m_bCompactCache;						// 是否紧凑缓存
	UGbool m_bEnableHashCode;					// 生成的图片是否带有 hashcode 在文件名中
	UGColor m_DefaultColor;						// 存储被过滤掉的默认颜色
	UGbool m_bTransparentBack;					// 存储图片是否透明
	UGbool m_bFillMargin;						// 是否使用数据填充 margin
	UGint m_nImageCompress;						// 缓存图片压缩率
	UGGeoRegion* m_pClipRegion;					// 裁剪区域
	TileType m_TileType;						// 全球剖分或者本地剖分
	UGRect2D m_rcMapBounds;						// 地图数据范围
	UGString m_strHashCode;						// 生成缓存的散列值
	std::map<UGdouble, UGString> m_mapOutputScaleCaptions;	// 比例尺、标题
	UGint m_nExtendedTiles;						// 对外瓦片扩张张数，上下左右一致
	UGString m_strMapName;						// 生成缓存的地图名
	UGString m_strDatasetName;					// 生成缓存的数据集名
	UGdouble m_dUnitsRatio;						// 投影坐标系的单位，LP/MP的转换比例尺使用。
	UGArray<UGint> m_nRevisionNumberList;		// 用户自定义版本数组

	// 下面的成员不在缓存配置文件中出现
	UGString m_strPassword;						// 大文件缓存密码
	UGString m_strFileDirectory;				// 缓存SCI存放目录位置
	UGString m_strCacheFileName;				// 当 sci 文件为打开的外部文件或者经过了保存操作后，则与一个外部文件对应。
	UGint m_nSourceType;						// 源文件类型
	UGMutex m_mutexFilterFile;					// 写入同一个 Filter 文件时进行互斥
	UGbool m_bDynamicCache;						// 当前生成的是动态缓存

	std::map<UGString, UGString> m_mapUserExtendField;	// 用户扩展字段

	UGint m_nRevisionNumber;					// 用户当前设置的自定义版本号
	UGbool m_bUseDataset;						//默认false是否使用Dataset数据集
};

} // UGC

#endif // _UGABSTRACTCACHEFILE_H_
