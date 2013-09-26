#ifndef UGDATASETRASTERCOLLECTION_H
#define UGDATASETRASTERCOLLECTION_H

#include "Base/ogdccolordef.h"
#include "Engine/UGDatasetRaster.h"
#include "Engine/UGDataSource.h"
// #include "Engine/UGDatasetMultiBandRaster.h"

#define OPEN_IMAGEPLUGIN_MAX_COUNT 100

namespace UGC
{

typedef struct RasterCollectionItemInfo 
{
	UGString Name;
	UGString AliasName;
	UGString Path;
	UGint Order;
	UGbool IsFileType;

} UGRasterCollectionItemInfo;
	
class ENGINE_API UGOpenedImagePlugin
{
public:

	UGOpenedImagePlugin();
	~UGOpenedImagePlugin();

	UGDataSource* m_pDataSource;
	UGint m_nRefCount;
};

class ENGINE_API UGDatasetRasterCollection :public UGDatasetRaster
{
public:

	enum CollectionOperate
	{
		CAdd	=	1,
		CDelete	=	2,
		CUpdate	=	3,
	};
	
public:
	UGDatasetRasterCollection();

	virtual ~UGDatasetRasterCollection();
	
public:

	//! \brief 关闭集合
	virtual void Close();

	//! \brief 根据别名获取子数据集中集合中的顺序
	virtual UGint GetSubDatasetOrder(const UGString &strAliasName);

	//! \brief 设置集合的投影（只在集合中无子数据集时有效）
	virtual UGbool SetPrjCoordSys(const UGPrjCoordSys &PrjCoordSys);

	//! \brief 判断此栅格集合是否为多波段集合
	virtual UGbool IsMBRaster();

	//! \brief 设置当前线程的色彩空间模式。
	//! \param aryBand 波段选择[in]。
	//! \param nColorSpace 色彩空间模式[in]。
	virtual void SetBandCombineMode(const UGArray<UGint>& aryBand, ImgColorSpace nColorSpace);

	//! \brief 获取当前线程的色彩空间模式。
	//! \param aryBand 波段选择[in]。
	//! \param nColorSpace 色彩空间模式[in]。
	//! \remarks 必须提前设置能获取到当前的色彩空间模式。
	virtual UGbool GetBandCombineMode(UGArray<UGint>& aryBand, ImgColorSpace& nColorSpace);	

	//! \brief 创建金字塔
	virtual UGbool BuildPyramid(UGbool bShhowProgress);
	
	//! \brief 更新金字塔
	virtual UGbool UpdatePyramid(const UGRect2D &rect);

	//! \brief 改变集合顺序。
	//! \param strAliasName 子数据集别名[in]。
	//! \param nPosition 要改变的位置，从零开始[in]
	//! \return 是否改变成功，成功返回TRUE，失败返回FALSE。
	virtual UGbool ChangeOrder(const UGString &strAliasName,UGint nPosition);

	//! \brief 获取要当前要显示的子数据集影像块，外部进行绘制
	UGArray<UGImgBlock*> GetViewBlocks(const UGRect2D& rcView, UGint nDeviceWidth, UGint nDeviceHeight);
	
	//! \brief 获取当前显示的子数据集所对应的裁剪区域，在绘制时使用，
	//! \brief 外部负责释放空间
	UGArray<UGGeoRegion*> GetCurViewClipRgn();

	//! \brief 获取当前显示的子数据集所对应的调色板，在绘制时使用，
	//! \brief 外部负责释放空间
	UGArray<UGColorset*> GetCurViewPalette();

	virtual UGbool Rename(const UGString& strNewName);

	// 统计栅格信息
	virtual UGDict<UGint, UGRasterStatisticsInfo> BuildStatistics();

	UGDatasetRaster * GetCollectionPyramidTier(UGRect2D rcBounds,UGint nDeviceWidth);

public:

	//! \brief 添加子数据集
	//! \param strName 子数据集名，文件数据集时为影像文件的绝对路径。
	//! \param strAliasName 数据集在集合中的别名，一个集合中不能有重复的别名
	//! \param bTop 是否将此子数据集加到顶端
	//! \return 是否增加成功，成功返回TRUE，失败返回FALSE。
	UGbool AddSubDataset(const UGString &strName, const UGString &strAliasName, UGbool bTop = FALSE);
	
	//! \brief 添加子数据集
	//! \param 子数据集名数组，文件数据集时为影像文件的绝对路径。
	//! \param 数据集在集合中的别名，重复则自动加"_1"
	//! \return 返回添加成功的子数据集个数据
	UGint AddSubDataset(const UGArray<UGString> &arrName, const UGArray<UGString> &arrAliasName);

	//! \brief 添加指定文件夹下的影像文件到集合中
	//! \param strPath 文件夹路径
	//! \param strExtName 所添加影像文件的后缀名
	//! \return 返回添加的子数据集个数
	UGint AddFiles(const UGString &strPath, const UGString &strExtName);

	//! \brief 追加集合。
	//! \param 源集合 （只追加集合中为影像文件的子数据集）
	//! \return 是否追加成功，成功返回TRUE，失败返回FALSE。
	UGbool Append(UGDatasetRasterCollection* pSrcCollection);

	//! \brief 插入子数据集
	//! \param strName 子数据集名，文件数据集时为影像文件的绝对路径。
	//! \param strAliasName 数据集在集合中的别名，一个集合中不能有重复的别名
	//! \param nPosition 子数据集在集合中的序号
	//! \return 是否增加成功，成功返回TRUE，失败返回FALSE。
	UGbool InsertSubDataset(const UGString &strName, const UGString &strAliasName, UGint nPosition);

	//! \brief 根据指定的索引移除子数据集
	UGbool RemoveSubDataset(UGint nIndex);

	//! \brief 根据指定的别名移除子数据集
	UGbool RemoveSubDataset(const UGString &strAliasName);
	
	//! \brief 移除集合中所以的子数据集
	UGbool RemoveAllSubDataset();

	//! \brief 获取集合子数据集的个数
	UGint GetSubDatasetCount();
	
	//! \brief 根据子数据集在集合中的序号来获取其别名
	UGString GetAliasName(UGint nOrder);

	//! \brief 实时获取所有子数据集的别名（数组中别名的顺序和子数据在集合里的顺序一致）
	UGbool GetAliasNames(UGArray<UGString>& arrAliasNames);
	
	//! \brief 实时获取所有子数据集的主要信息
	UGbool GetItemInfo(UGArray<UGRasterCollectionItemInfo>& arrItemInfo, UGRect2D& rcBounds);

	//! \brief 根据指定的索引获取子数据集
	UGDataset* GetSubDataset(UGint nIndex);
	
	//! \brief 根据指定的别名获取子数据集
	UGDataset* GetSubDataset(const UGString &strAliasName);
	
	//! \brief 获取子数据集
	//! \param strName 子数据集所关联数据集的名称
	//! \param strConnection 子数据集的数据源连接参数
	//! \return 返回所获取的数据集，没有则返回NULL
	UGDataset* GetSubDataset(const UGString& strName, const UGString& strConnection);

	//! \brief 根据数据集名或文件路径直接获取子数据集
	//! \param strName 数据集名称
	//! \param bIsImagePlugins 是否为影像文件
	//! \param strPath 影像文件绝对路径
	//! \return 返回所获取的数据集，没有则返回NULL
	UGDataset* GetSubDataset(const UGString& strName, UGbool bIsImagePlugins, const UGString& strPath);
	
	//! \brief 判断别名在集合中是否在。
	//! \param strAliasName 子数据集别名[in]。
	//! \return 是否存在，存在返回TRUE，否则返回FALSE。
	UGbool IsExitAlias(const UGString &strAliasName);
	
	//! \brief 判断数据集是事符合添加条件
	UGbool IsCanAdd(UGDatasetRaster* pDataset, UGbool bIsFirst);
	
	//! \brief 如果别名已存在，获得一个可用的别名
	UGbool GetValidAliasName(UGString& strAliasName);
	
	//! \brief 根据别名获取子数据集的裁剪区域
	//! \param strAliasName 子数据集别名
	//! \param pClipRegion 获取的裁剪区域
	//! \return 是否成功，成功返回TRUE，失败返回FALSE。
	UGbool GetSubClipRegion(const UGString &strAliasName, UGGeoRegion *&pClipRegion);

	//! \brief 根据别名设置子数据集的裁剪区域
	//! \param strAliasName 子数据集别名
	//! \param pClipRegion 裁剪区域
	//! \return 是否成功，成功返回TRUE，失败返回FALSE。
	UGbool SetSubClipRegion(const UGString &strAliasName, UGGeoRegion *&pClipRegion);

	//! \brief 根据别名获取子数据集的调色板
	//! \param strAliasName 子数据集别名
	//! \param colorset 调色板
	//! \return 是否成功，成功返回TRUE，失败返回FALSE。
	UGbool GetSubPalette(const UGString &strAliasName, UGColorset &colorset);

	//! \brief 根据别名设置子数据集的调色板（对1位、4位、8位影像有效）
	//! \param strAliasName 子数据集别名
	//! \param colorset 调色板
	//! \return 是否成功，成功返回TRUE，失败返回FALSE。
	UGbool SetSubPalette(const UGString &strAliasName, UGColorset &colorset);

	//! \brief 获取栅格集合的属性数据集
	UGDatasetVector* GetAttributeDataset();

	//! \brief 设置栅格集合的属性数据集
	void SetAttributeDataset(UGDatasetVector* pDataset);
	
	//! \brief 设置当前子数据集是否可用
	UGbool SetSubEnable(UGString &strAliasName, UGbool bIsEnable);
	
	//! \brief 同步当前集合
	UGbool SyncSubDatasets();

	//! \brief 重新指定子数据集的别名
	UGbool RenameSubDataset(UGString& strAliasName, UGString& strNewAliasName);

	void ReduceImagePluginRefCount();

protected:

	// {{ 以下为集全类内部所使用的方法

	//! \brief 利用影像插件打开影像文件
	//! \param strImagePath 影像文件的绝对路径
	//! \return 返回所打开的数据集
	UGDataset* OpenImagePluginDataset(const UGString &strImagePath, const UGString &strName = _U(""));

	//! \brief 关闭影像插件数据源
	//! \param strName 影像文件的数据集名称
	void CloseImagePluginDataset(const UGString &strName);

	//! \brief 关闭所以的影像插件数据源
	void CloseAllImagePluginDataset();

	//! \brief 获取当前需要显示的金字塔级别
	UGint GetPyramidLevel(UGDatasetRaster* pDatasetRaster, const UGRect2D& rcView, UGint nDeviceWidth);

	virtual UGbool UpdateCollectionTable(UGDatasetRasterCollection::CollectionOperate nType, 
		const UGint& nSubDatasetOrder, UGbool bTop = FALSE);

	// 添加子数据时，根据所指定的名称和别名，来构造Feature，用于批量添加
	UGbool GetFeature(const UGString &strName, const UGString &strAliasName, UGFeature*& pFeature, UGbool bIsFirst);

	void UpdateInfo(UGFeature* pAddFeature, UGbool bIsFirst);

	void SetQueryFields(UGArray<UGString>& fields);

	void SetCreateFields(UGFieldInfos& fieldInfos);

	UGbool ReleasePyramidDatasets();
	
	//! \brief 设置基层金字塔的大小
	void SetBasePyramidSize(UGDatasetRasterInfo& info);

	//! \brief 更新第一层金字塔
	UGbool UpdateBasePyramidTier(UGDatasetRaster*& pBasePyramidTier, UGRect2D rcUpdateBounds, UGint nBandIndex = 0);

	UGbool UpdateBasePyramidTier(UGDatasetRaster* pBasePyramidTier, UGRect2D rcSubBounds, 
		UGDatasetRaster* pSubRasterDataset,UGProgress &Progress, UGint nBandIndex = 0);

	UGImgBlock* GetImagePluginsViewBlock(UGDatasetRaster* pSubRasterDataset, 
		const UGRect2D& rcBounds, UGint nBandIndex);

	//! \brief 清除已有影像块，用于金字塔更新（比如删除一个子数据集）
	UGbool EraseBasePyramidTier(UGDatasetRaster* pBasePyramidTier, UGRect2D& rcRect, UGint nBandIndex = 0);

	void ConvertPixel(UGDatasetRaster* pSrcRaster, UGdouble& dValue);

	void ConvertBlock(UGImgBlock*&pImgBlock, UGDatasetRaster*& pDatasetRaster);

	// 更新单波段影像金字塔
	UGbool UpdatePyramidSB(const UGRect2D &rect);
	
	// 更新多波段影像金字塔
	UGbool UpdatePyramidMB(const UGRect2D &rect);

	// 对当前集合中的多波段数据集的当前索引进行的管理
	void SetIndex(UGint nIndex);
	
	UGint GetIndex() const;

	// 得到集合里子数据的波段数据，各子数据集的波段数据是一样的
	UGint GetColBandCount();
	// }}

protected:
	
	//! \brief 集合属性数据集
	UGDatasetVector* m_pAttributeDataset;

	// 影像插件数据源，每一个影像文件对应一个数据源
	UGArray<UGOpenedImagePlugin*> m_arrImgDataSource;

	UGDict<UGint, UGOpenedImagePlugin*> m_dicCurOpenedImagePlugin;

	//! \brief 显示时各个影像块的裁剪区域和调色板
	UGDict<UGint,UGArray<UGGeoRegion*> > m_dicCurViewClipRgn;
	UGDict<UGint,UGArray<UGColorset*> > m_dicCurViewPalette;

	// 在更新影像块时，设置当前块的调色板和裁剪区域
	UGColorset m_SubColorset;
	UGGeoRegion* m_pSubClipRegion;

	// 当前波段
	UGDict<UGint, UGint> m_dicIndex;

	// 多波段显示色彩组合
	UGDict<UGint,UGColorSpaceBand> m_dicColorSpace;

	// 多波段块管理
// 	UGArray<UGImgBlocksManager> m_arrImgManager;

	// 集合金字塔层数据
	UGint m_nPyramidTierCount;

	// 用来保存集合中子数据集波段数，主要是为了前后版本兼容
	// 0表示SP3版本的单波段集合，7C版本后最小则为1
	// 因为7C版本所以栅格、影像数据的波段至少为1
	UGint m_nCollectionBandCount;
};
}
#endif