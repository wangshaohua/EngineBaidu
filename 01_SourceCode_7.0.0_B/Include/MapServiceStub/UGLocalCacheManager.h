//////////////////////////////////////////////////////////////////////////
//                    _   _   ____   ____                    
//   Project         | | | | / ___) / ___)                   
//                   | | | || | __ | |                       
//                   | |_| || |_\ || \___                    
//                    \____/ \____| \ ___)     6.0           
//                                                           
//!  \file headerfile.h
//!  \brief Class 。
//!  \details 。
//!  \author 数据转换组。
//!  \attention 
//!   Copyright (c) 1996-2010 SuperMap Software Limited Company.  <br> 
//!   All Rights Reserved.
//!  \version 6.0
//////////////////////////////////////////////////////////////////////////


#if !defined(AFX_UGLOCALCACHEMANAGER_H__F2ACB033_F582_4263_B9E9_DCA2E56F87DE__INCLUDED_)
#define AFX_UGLOCALCACHEMANAGER_H__F2ACB033_F582_4263_B9E9_DCA2E56F87DE__INCLUDED_

#include "Stream/ugdefs.h"
#include "Projection/UGPrjCoordSys.h"
#include "Toolkit/UGPalette.h"
#include "FileParser/UGExchangeFileType.h"
#include "CacheFile/UGCacheFileCommon.h"

namespace UGC 
{	
class UGMapCacheFile;
class UGTile;

//! \brief 瓦片的信息
struct UGTileInfo
{
	//! \brief 比例尺
	UGdouble m_dScale;

	UGint m_nRow;

	UGint m_nCol;

	//! \brief 范围
	UGRect2D m_rcBound;
};


//! \brief 本地缓存交互类
class MAPSERVICESTUB_API UGLocalCacheManager 
{
	enum UGCacheType
	{	
		MapCache	= 0,	
		GlobalCache = 1,
	};

public:
	//! \brief 构造函数。
	UGLocalCacheManager();

	//! \brief 析构函数。
	virtual ~UGLocalCacheManager();
	
public:
	
	//! \brief 返回二维缓存。
	//! \param UGMapCacheFile* [out]。
	UGMapCacheFile* GetAbstractCacheFile() const;

	//! \brief 创建缓存。
	//! \param strCacheFile [in]。
	//! \param nCacheType [in]。
	//! \return 成功返回TRUE，失败返回FALSE。
	//! \attention 通过后缀判断缓存类型。
	UGbool Create(const UGString& strCacheFile, UGint nCacheType = 0);

	//! \brief 打开缓存。
	//! \param strCacheFile [in]。
	//! \param nCacheType [in]。
	//! \return 成功返回TRUE，失败返回FALSE。
	UGbool Open(const UGString& strCacheFile, UGint nCacheType = 0);
	
	//! \brief 关闭	
	void Close();	
	
	// 保存.scihp文件
	UGbool Save();

	//! \brief 获取瓦片数据
	//! \param TileData [in,out] 单张瓦片的数据结构。
	UGbool GetTileData(UGTile& tileData);

	//! \brief 根据传入的TileData中的比例尺，获取Tile的地理范围和像素范围
	void GetTileInfo(UGTile& tileData);
	
	// 获取用户扩展字段的引用，可直接修改。
	// 如果map的元素个数不为0，会依次保存元素到配置文件里边
	std::map<UGString, UGString>& UserExtendField();

	//! \brief 返回所有的比例尺级别
	const UGArray<UGdouble> GetScales() const;	

	//! \brief 获取地图服务的空间坐标系。
	//! \param [out] 投影
	//! \attention 获取后外面负责释放
	const UGPrjCoordSys& GetSpatialRef() const;	

	const UGbool IsCacheFileExist(UGString strCacheFile) const;

	//! \brief 获取地图名称
	UGString GetMapName() const;

public:
	//! \brief 缓存名称设置
	void SetCacheName(const UGString &strCacheName);
	void SetVersion(enum UGC::UGMapCacheVersion nVersion);

	enum UGC::UGMapCacheVersion GetVersion();

	//! \brief 图片范围
	void SetBounds(const UGRect2D &rcBounds);

	//! \brief 图片策略，比如是透明Png32、不透明Png32、Png8、Jpeg、混合图片模式
	void SetImageType(UGFileType::EmType nPictureFormat);

	//! \brief 投影 
	void SetPrjCoordSys(const UGPrjCoordSys &CoordSys);

	//! \brief DPI，提供 LP/DP 转换比率，x方向和y方向比率一致吧
	void SetCoordRatio(UGdouble dCoordRatio);
	double GetCoordRatio();

	//! \brief 比例尺信息，这块要求，不要存比例尺的倒数了
	//! \attention 如果所有比例尺都在正常范围，即均为正数，返回 true；否则返回 false，并且不对比例尺设置进行任何修改。
	UGbool SetOutputScales(const std::vector<UGdouble>& vectOutputScales);
	
	//! \brief 比例尺和比例尺别名的对应关系
	UGbool SetOutputScaleCaptions(const std::map<UGdouble, UGString> &mapOutputScaleCaptions);

	//! \brief 单张图片像素大小，默认是256像素宽高
	void SetTileSize(UGint nTileSize);
	
	//! \brief 是否紧凑缓存，默认不是紧凑
	void SetIsCompactCache(UGbool bCompactCache);

	// 获取设置是否背景透明
	UGbool IsTransparentBack();
	void SetTransparent(const UGbool &bTransparent);

	//! \brief 计算行列号的原点，建议上层把经纬度的（-180，90）转换到当前地图投影坐标系下作默认值
	//! \attention 根据设定的原点，向右向下取数据，在原点左边和上边的不出图片
	void SetOrigin(const UGPoint2D &pntOrigin);

	//! \brief 获取比例尺级别
	const std::vector<UGdouble> GetOutputScales();
	
	//! \brief 获取比例尺别名
	void GetOutputScaleCaptions(std::map<UGdouble, UGString> &mapOutputScaleCaptions);

	//! \brief 获取瓦片全路径
	UGString GetTileFilePath(const UGdouble& dScale, const UGint& nRow, const UGint& nCol);

	//! \brief 设置服务提供者
	void SetServiceProvider(const UGString& strProvider);

	//! \brief 获取服务提供者
	UGString GetServiceProvider() const;
    
	
	UGint GetImageWidth() const;

	UGint GetImageHeight() const;

	UGint GetScaleCount() const;

	UGint GetTileSize() const;

	PixelFormat GetPixelFormat() const;

	UGdouble ScaleToNearFixScale(UGdouble dScale) const;

	UGRect2D ComputeTilesBounds(UGdouble dMapScale, const UGRect2D& rcMapBounds, UGint nExtTileSize = 1) const;

	UGSize2D GetTileMPSize(UGdouble dMapScale) const;

	UGRect2D GetBounds()const;
	
public:
	//! \brief 服务是否打开。
	//! \param  [in]。
	UGbool IsOpened(){return m_bOpen;}
    
	void BoundToRowAndCol(UGdouble& dScale, const UGRect2D& bound, UGint& nRow, UGint& nCol);

protected:	
	//! \brief 服务打开标志。
	UGbool m_bOpen;

	UGString m_strCacheFile;

	UGString m_strCacheDir;

	UGString m_strFileExtName;
	
	//! \brief Map的名称 
	//! \attention 主要用于在UGMapServiceStub判断此时的缓存是否已经是空的
	UGString m_strMapName;
	
	//! \brief 缓存的投影。
	UGPrjCoordSys m_prjCoordSys;
	
	//！ biref 二维缓存的基类
	//! \attention 在构造函数的时候被初始化
	UGMapCacheFile *m_pMapCacheFile;

////////////用于实现GetViewBlock接口//////////////{
public:
	//! \brief 设置当前显示范围
	//! \param  nLeft, nTop,显示范围的左边和上边。nLeft < nRight，nTop < nBottom.[in]
	//! \param  nRight, nBottom 显示范围的右边和下边。这是个值给的是象素坐标。[in]
	//! \param  nDeviceWidth, nDeviceHeight,真实显示窗口的大小，屏幕象素单位。[in]
	//! \remarks 对于多分辨率的图象，可以按照窗口大小和显示范围大小，确定图象的分辨率,从而决定从那一层取得影像数据
	bool SetViewPort(int nLeft,int nTop, int nRight, int nBottom, int nDeviceWidth, int nDeviceHeight);

	//! \brief 设置当前显示范围
	//! \param  dLeft, dTop,显示范围的左边和上边。dLeft < dRight，dTop < dBottom.[in]
	//! \param  dRight, dBottom 显示范围的右边和下边。这是个值给的是地理坐标.[in]
	//! \param  nDeviceWidth, nDeviceHeight,真实显示窗口的大小，屏幕象素单位。[in]
	//! \remarks 对于多分辨率的图象，可以按照窗口大小和显示范围大小，确定图象的分辨率,从而决定从那一层取得影像数据
	bool SetViewPort(double dLeft,double dTop, double dRight, double dBottom, int nDeviceWidth, int nDeviceHeight);

	//! \brief 设置当前显示范围后,返回显示范围内影像数据的宽度。
	//! \remarks 对于多分辨率图象，可能从另外一层读取数据，所以输出的宽度可能和显示范围的宽度不一样
	//! \param  nViewWidth 显示数据影像宽度。[out]
	//! \param  nViewHeight 显示数据影像高度。[out]
	bool GetViewImageSize(int& nViewWidth, int& nViewHeight);

	//! \brief 设置当前显示范围后,返回显示范围内数据的大小。
	int GetViewImageDataSize(); 

	//! \brief 设置当前显示范围后,读取显示范围内的影像数据,外部取得数据以后，可以用来显示
	//! \param  pDataBuffer,影像数据，函数外分配空间。[in]
	//! \param  nSize，数据大小(字节数），一般就是GetViewImageDataSize（）返回值.[in]
	bool GetViewImageData(unsigned char* pDataBuffer, int nSize);

	//! \brief 指示请求数据是否全部加载
	UGbool IsFinished(){return m_bFinished;}

	//! \brief 得到当前可视范围
	virtual UGRect2D GetViewRect();

	//! \brief 加载缓存影像块数据
	//! \param  dScale. 瓦片比例尺.[in]
	//! \param  nRow. 瓦片行号.[in]
	//! \param  nCol. 瓦片列号.[in]
	//! \param  bRGBA 是否转换成RGBA[in]
	//! \return 瓦片的ImageData
	UGImageData* LoadTileImageData(UGdouble dScale, UGint nRow, UGint nCol, UGbool bRGBA = FALSE);

private:
	UGbool UnZip(UGbyte* &pImageData,UGint &nSize);

	//! \brief 建立数据缓存区
	bool CreateDataBuffer();

	//! \brief 释放缓存数据
	void ReleaseBufferData();

	void Release();

	//! \brief 得到影像块的包围框
	//! \param  nRow. 块的行号.[in]
	//! \param  nCol. 块的列号.[in]
	//! \param  nDataLevel. 块的层号.[in]
	UGRect2D GetCellBound(UGint nRow, UGint nCol, UGint nDataLevel);

	UGRect GetCellDataRowCol(UGRect2D InsectBound, UGRect2D CellBound);

	//! \brief 加载缓存影像数据
	//! \param  nBeginRow. 读取缓存影像数据的起始行号.[in]
	//! \param  nEndRow. 读取缓存影像数据的结束行号.[in]
	//! \param  nBeginCol. 读取缓存影像数据的起始列号.[in]
	//! \param  strFilePath. 读取缓影像存数据的结束列号.[in]
	//! \param  strFilePath. 读取缓存影像数据的层号.[in]
	bool LoadImageData(UGint nBeginRow, UGint nEndRow, UGint nBeginCol, UGint nEndCol, UGint nDataLevel, UGRect2D ViewRect);

	//! \brief 设置当前可视范围
	void SetViewRect(const UGdouble &dLeft, const UGdouble &dTop, const UGdouble &dRight, const UGdouble &dBottom);

private:

	//! \brief 缓存图片像素格式
	//! \remarks 因为有些图片的位深是读取不出来的  故需要来记录一下缓存的格式
	//! \remarks 如地形缓存文件Bil目前的位深是IPF_TBYTE
	PixelFormat m_nPixelFormat;

	//! \brief 数据缓存大小
	UGint m_nBuffSize;

	//! \brief 数据缓存
	UGbyte* m_pBuffer;

	//! \brief 视范围内的宽度
	UGint m_nViewWidth;

	//! \brief 视范围内的高度
	UGint m_nViewHeight;

	UGDict<UGlong, UGImageData*> m_imageDatas;

	UGbool m_bFinished;

	//! \brief 当前可视区域
	UGRect2D m_ViewRect;

	UGint  m_nCacheType;

//////////////////////用于实现GetViewBlock接口///////////////////}

};

} //namespace UGC

#endif // !defined(AFX_UGLOCALCACHEMANAGER_H__F2ACB033_F582_4263_B9E9_DCA2E56F87DE__INCLUDED_)

