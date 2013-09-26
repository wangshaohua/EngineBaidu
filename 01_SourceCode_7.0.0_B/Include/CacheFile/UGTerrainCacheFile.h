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

#ifndef _UGTERRAINCACHEFILE_H_
#define _UGTERRAINCACHEFILE_H_

#include "FileParser/UGExchangeFileType.h"
#include "Base/ogdccolordef.h"
#include "Stream/UGByteArray.h"
#include "CacheFile/UGCacheFileCommon.h"
#include "Geometry/UGGeoRegion.h"
#include "Toolkit/UGMarkup.h"
#include "Stream/UGCacheFile.h"
#include "FileParser/UGFileParseToolkit.h"

#define SUPERMAPSCI 0
#define ARCGISXML 1

#include <vector>

namespace UGC
{

class CACHEFILE_API UGTerrainCacheFile
{
		
public:
	UGTerrainCacheFile();
	~UGTerrainCacheFile();

		// 缓存名称设置
	UGbool			SetCacheName(const UGString &strCacheName);
	const UGString &GetCacheName();
	const UGString &GetFinalCacheName();

		// 投影信息，会初始化坐标系单位和缓存参考原点
	void				 SetPrjCoordSys(const UGPrjCoordSys &CoordSys);
	const UGPrjCoordSys &GetPrjCoordSys() const;

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

	
	void			SetIndexBounds(const UGRect2D &rcIndexBounds);
	const UGRect2D &GetIndexBounds();
	UGRect2D		GetFinalIndexBounds();

	// 比例尺信息，这块要求，不要存比例尺的倒数了
	// 如果所有比例尺都在正常范围，即均为正数，返回 true；否则返回 false，并且不对比例尺设置进行任何修改。//是否设置了固定比例尺
	UGbool					SetOutputScales(const UGArray<UGdouble>& vectOutputScales,UGbool bIsDisplayByScales = false);
	UGArray<UGdouble>		GetOutputScales();
	UGArray<UGdouble>		GetSortedOutputScales();		// TODO 完全去掉

	UGbool SetOutputScaleCaptions(const UGDict<UGdouble, UGString> mapOutputScaleCaptions);
	void GetOutputScaleCaptions(UGDict<UGdouble, UGString> &mapOutputScaleCaptions);
	const UGDict<UGdouble, UGString> &GetOutputScaleCaptions();

	// 是否紧凑缓存，默认不是紧凑
	void	SetIsCompactCache(UGbool bCompactCache);
	UGbool	IsCompactCache();

	UGbool ToProjection(const UGString& strProjectionFile );
	UGbool FromProjection(const UGString &strProjection);

	//! \brief 生成数据集颜色表文件
	UGbool ToColorTableFile(const UGColorTable& colorTable, const UGString& strFileName);

	//! \brief 读取数据集颜色表文件
	UGbool FromColorTableFile(UGColorTable& colorTable, const UGString& strFileName);

	// 根据指定的全路径名导出/导入SCI配置文件。
	UGbool ToConfigFile(const UGString& strCacheFile,UGbool bChangeOutputDir=true);//添加UGbool是否修改输出路径，inf文件不修改路径
	UGbool FromConfigFile(const UGString& strCacheFile);

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
		
	// 设置/获取图片背景色是否透明
	void	SetTransparentBack(UGbool bTransparentBack);
	UGbool	IsTransparentBack();
	

	// 设置/获取裁剪区域
	// 如果没有设置裁剪区域，获取结果为 NULL。
	UGbool				SetClipRegion(UGGeoRegion *pClipRegion);
	const UGGeoRegion  *GetClipRegion();

	// 设置/判断是否为全球剖分
	void		SetTileType(TileType tileType);
	TileType	GetTileType();

	// 数据集名。
	// 如果没有设置缓存名，则缓存名为数据集名
	void			 SetDatasetName(const UGString &strName);
	const UGString& GetDatasetName();


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

	UGbool TileArea2PixelArea(const TileArea &tileArea,	PixelArea &rcPixelArea);
	UGbool PixelArea2TileArea(const PixelArea &rcPixelArea,	TileArea &tileArea);

	UGbool TileArea2TileGroupArea(const TileArea &tileArea, TileGroupArea &tileGroupArea);
	UGbool TileGroupArea2TileArea(const TileGroupArea &tileGroupArea, TileArea &tileArea);

	// 把全坐标的瓦片行列号换算成对应紧凑缓存的行列号
	static void ConvertRowCol(UGint& nRow, UGint& nCol);
	static void CompactCellPos2TilePos(UGint nTileGroupRow, UGint nTileGroupCol, UGint nCellRow, UGint nCellCol, UGint &nTileRow, UGint &nTileCol);

	// 将浮点型的比例尺转换为整数，例如 .5 转换成整数为 2，该整数用来生成缓存目录名
	unsigned	Scale2ScalePathName(UGdouble dScale);		
	UGdouble		ScalePathName2Scale(unsigned nScale);

	// 保存紧凑缓存瓦片。
	// 要求瓦片在外部已经完全构建完毕，包含瓦片头部。
	UGbool OpenCompactFile(UGdouble dScale, UGint nRow, UGint nCol, UGCompactFileWrapper &compactFile, UGbool bCreateIfAbsent = false);
	UGbool CreateCompactFile(UGdouble dScale, UGint nRow, UGint nCol, UGCompactFileWrapper &compactFile);
	
	// 比例尺排序
	void SetOutputScales_aux(const UGArray<UGdouble>& vectOutputScales,UGbool bIsDisplayByScales = false);//是否设置了固定比例尺

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
	// 重置所有成员
	void Reset();

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
	// 通过比例尺转换瓦片边长对应的地理大小
	UGSize2D ComputeTileMPSize(UGdouble dScale) const;

	//为了求准确的象素长，临时加下面两个函数，用的地方不多。（没有求UGdouble类型的象素位置的函数，所以先这么求下）
	UGdouble GetUnitsRatio();

	UGbool TilePos2PixelArea(UGdouble dScale, UGint nRow, UGint nCol, PixelArea &pixelArea);

	//! \brief  设置/获取缓存密码,当m_nstroeType为MIXED_FILES或SINGLE_FILE时，密码才会起作用。
	void SetPassword(const UGString& strPwd);
	const UGString &GetPassword();

	// ===================================================================

	// 530000/3/5/7x12.3f2d0c
	//UGString TilePos2RelativeSolidPicFileNamePrefix(UGdouble dScale, UGint nRow, UGint nCol, UGColor color);

	UGbool SaveCompactCellData(UGdouble dScale, UGint nRow, UGint nCol, const UGbyte *pData, size_t nSize, UGCompactFileWrapper &compactFile);

	//! \brief 获取用户自定义最新版本
	UGint GetRevisionNumber();

	//! \brief 设置用户自定义最新版本
	void SetRevisionNumber(UGint number);

	//! \brief 获取用户设置的自定义版本中最大的版本号
	UGint GetMaxRevisionNumber();

	// 添加当前用户自定义版本到版本存放列表
	void AddRevisionNumberToList();

	// 获取用户自定义列表
	const UGArray<UGint> GetRevisionNumberList() const;

	// 通过瓦片位置计算瓦片组的位置
	void TilePos2TileGroupPos(UGint nTileRow, UGint nTileCol, UGint &nGroupTileRow, UGint &nGroupTileCol);

	//! \brief 数据压缩方式
	UGint GetCompressType() const;
	void SetCompressType(UGint eCodecType);

	void SetPixelFormat(UGPixelFormat nPixelFormat);
	UGPixelFormat GetPixelFormat();
	//! \brief 设置缓存文件类型
	//! \param bounds [in] 缓存范围
	//! \return 。
	//! \remarks 。
	//! \attention
	void SetStorageType(UGuint type);
	//! \brief 获得缓存文件类型
	UGuint GetStorageType();

	void SetCacheVersion(UGint nVersion);//
	void SetFileExtName(UGString strFileExtName);//str
	UGint GetCacheVersion();//
	UGString GetFileExtName();//str

	//! \brief 获取缓存生成的瓦片相对SCI文件的路径，格式为 1000/1/9.cf
	//! \param dScale [in]		当前出图的比例尺
	//! \return						获取生成的瓦片相对路径
	//! \remarks					规则如下：
	UGString TilePos2RelativeCompactFileName(UGdouble dScale, UGint nRow, UGint nCol, UGbool bIsCreat = false);
	// 530000/3/5
	UGbool TilePos2RelativeSuperMapFileName_aux(UGdouble dScale, UGint nRow, UGint nCol, UGString &strPath);
	void ResetSCTContent();
	UGColorTable* GetColorTable();

	UGString GetNetCatchPath();

private:

	UGTerrainCacheFile &operator=(const UGTerrainCacheFile &rhs);
	UGTerrainCacheFile(const UGTerrainCacheFile &rhs);

	// ============================ 存储、读取瓦片相关函数 ============================

	
		// 读取大文件缓存中单个图片位置中存储的内容，包含存储于图片之前的头部
	UGbool LoadCompactCellData(UGdouble dScale, UGint nRow, UGint nCol, UGByteArray &ByteArray, UGCompactFileWrapper &compactFile);

	// 读取大文件缓存中单个图片的图片内容。nRow 和 nCol 是瓦片行列号
	UGbool LoadCompactImageData(UGdouble dScale, UGint nRow, UGint nCol, UGByteArray &ByteArray, UGbool &bSolidColor, UGColor &solidColor, UGCompactFileWrapper &compactFile, UGint nRequiredImageType, UGbool bTransparent, UGbool bPreciseMatch);

	// ================================================================================
	// 检测紧凑存储下密码是否正确
	UGbool IsPassWordCorrect(const UGchar* strSCIFileName, const UGchar * strPassword);

	// ============================== 瓦片位置到文件名的转换函数 ==============================

	// 获得顶层文件夹路径，以 '/' 结尾
	UGString GetTopLevelPath();

		// TODO 该函数将来将完全被 TilePos2FileName 替换掉
	// NOTE 当前仅供 ComputeImageFileName() 使用
	UGbool TilePos2RelativeFileName(UGdouble dScale, UGint nRow, UGint nCol, UGString &strFileName);




	// =========================================================================================

	// 获取相近比例尺
	UGdouble ScaleToNearFixScale(UGdouble dScale);

	// 比例尺在排序后的比例尺中的下标。
	// 由于 Scale 的数目极少，使用 UGint 值完全可以。不必要使用容器的 size_type。
	// 0 起。返回 -1 表示错误。
	// NOTE 一定要检查该函数的返回值
	UGdouble Round2NearestScale(UGdouble dScale);

	void DebugValidateScale(UGdouble dScale);

	// 调整 m_dUnitsRatio 成员。
	void AdjustUnitsRatio();

	// DPI 与 CoordRatio 相互转换
	UGdouble		DPI2CoordRatio(UGdouble nDPI) const;
	UGdouble		CoordRatio2DPI(UGdouble dCoordRatio) const;

	UGint GetBytesPerPixel(const PixelFormat& strDataFormat);

	bool UnZip(UGbyte* &pImageData,UGint & nSize);

	// ============================== 数据成员 ==============================
	// 下面的成员在缓存配置文件中出现
	//UGMapCacheVersion m_nCacheVersion;		// 当前缓存的版本号。在 ToConfigFile() 中该版本号指示了要导出的文件格式
	UGint	m_nFullCacheVersion;				// 当前缓存的完整版本号
	//UGString m_strServiceProvider;				// Service Provider
	UGString m_strCacheName;					// 缓存名称。该名称用作缓存作为数据源方式进行加载时的数据源名称
	UGPrjCoordSys *m_pPrjCoordSys;				// 投影信息。将地图缓存加载到三维场景中的必须信息。
	UGint m_nTileSize;							// 瓦片像素边长。
	UGint m_nTileWidth;							// 瓦片像素宽
	UGint m_nTileHeight;						// 瓦片像素高
	UGRect2D m_rcBounds;						// 缓存的地理范围。缓存作为数据源方式进行加载时的数据源范围
	UGdouble m_dCoordRatio;						// LP/DP 转换比率，单位为(像素/毫米)。
	UGRect2D m_rcIndexBounds;					// 索引范围
	UGbool m_bCompactCache;						// 是否紧凑缓存
	UGString m_strNetCatchPath;					// 网络路径缓存地址
	//UGint m_nImageCompress;						// 缓存图片压缩率
	UGGeoRegion* m_pClipRegion;					// 裁剪区域
	TileType m_TileType;						// 全球剖分或者本地剖分
	UGDict<UGdouble, UGString> m_mapOutputScaleCaptions;	// 比例尺、标题
	//UGint m_nExtendedTiles;						// 对外瓦片扩张张数，上下左右一致

	UGString m_strDatasetName;					// 生成缓存的数据集名
	UGdouble m_dUnitsRatio;						// 投影坐标系的单位，LP/MP的转换比例尺使用。
	UGArray<UGint> m_nRevisionNumberList;		// 用户自定义版本数组

	// 下面的成员不在缓存配置文件中出现
	UGString m_strPassword;						// 大文件缓存密码
	UGString m_strFileDirectory;				// 缓存SCI存放目录位置
	UGString m_strCacheFileName;				// 当 sci 文件为打开的外部文件或者经过了保存操作后，则与一个外部文件对应。

	UGint m_nRevisionNumber;					// 用户当前设置的自定义版本号
	UGbool m_bUseDataset;						//默认false是否使用Dataset数据集
	//! \brief 压缩方式
	//! \目前只用于地形压缩是否为zip压缩
	//add by fxj 101207
	UGint m_eCodecType;

	//! \brief 像素格式
	//! \目前只用于地形缓存中保存float/double类型的高精度DEM
	//add by shansg 2013-04-23
	UGPixelFormat m_nPixelFormat;

	//! \brief 缓存文件类型
	//! \remarks 备注信息。
	UGuint m_storeType;//0://PURE_FILES 1://MIXED_FILES 2 singlefile

	//! \brief 缓存版本号,用于标识配置文件的版本
	//! \remarks 备注信息。
	UGint m_nVersion;

	//! \brief 文件后缀名
	UGString m_strFileExtName;

	//! \brief 每个像素所用位数
	UGint m_nBytesPerPixel;

	//! \brief 从外挂颜色表中获取的颜色表
	UGColorTable* m_pColorTable;
};

} // UGC

#endif // _UGABSTRACTCACHEFILE_H_
