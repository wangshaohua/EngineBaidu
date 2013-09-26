// UGPluginMapCache50.h: interface for the UGPluginMapCache50 class.
//
//////////////////////////////////////////////////////////////////////

#ifndef _PLUGINMAPCACHE50_H_
#define _PLUGINMAPCACHE50_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CacheFile/UGAbstractCacheFile.h"
#include "FileParser/UGImagePlugin.h"
#include "MapServiceStub/UGMapServiceStub.h"
#include <vector>

namespace {
	// 专门用来管理 buffer 的 template
	template <typename _Ty>
	class _BufferManager : public std::auto_ptr<_Ty> {
		size_t m_nBuffSize;
	public:
		void reset(size_t nNewSize = 0, _Ty *ptr = 0) {
			std::auto_ptr<_Ty>::reset(ptr);
			if (ptr == NULL) {
				m_nBuffSize = 0;
			} else {
				m_nBuffSize = nNewSize;
			}
		}

		_Ty *release() {
			m_nBuffSize = 0;
			return std::auto_ptr<_Ty>::release();
		}

		size_t getsize() {
			return m_nBuffSize;
		}

		_BufferManager(size_t nSize = 0, _Ty *ptr = 0) : std::auto_ptr<_Ty>::auto_ptr(ptr) {
			m_nBuffSize = nSize;
		}

		~_BufferManager() {
			m_nBuffSize = 0;
		}
	};

	UGchar *pPostfix = UG_ABSCACHEFILE_EXT;
	UGchar *pArcPostfix = UG_ARCFILE_EXT;
} // anonymous namespace

namespace UGC
{
	
class PLUGINMAPCACHE50_API UGPluginMapCache50 : public UGImagePlugin {

public:
	UGPluginMapCache50();
	virtual ~UGPluginMapCache50();

public:
	virtual UGbool GetPluginName(UGchar* strName, int nMaxLength);
	virtual UGbool GetExtName(UGchar* strExtName, int nMaxLength, int nExtNameIndex = 0);
	virtual int GetExtNameCount() const { return 2; }

	virtual UGbool Open(const UGchar* strFileName, unsigned int nFlags, const UGchar *pszPassword);
	void Close();

	virtual UGbool SetViewPort(double dLeft,double dTop, double dRight, double dBottom, int nDeviceWidth, int nDeviceHeight);

	//! \brief 返回像素格式
	virtual UGbool GetPixelFormat(ImagePixelFormat& nPixelformat);

	//! \brief 返回每个像素的位数
	virtual UGbool GetPixelBits(ImagePixelBits& nPixelbits);

	//! \brief 获取整幅图片的大小
	// NOTE 现在该函数已经不能满足超大尺寸缓存要求。int 类型会溢出。
	// 现在的解决办法是在溢出情况下，返回 INT_MAX
	virtual UGbool GetImageSize(int& nWidth, int& nHeight);

	virtual UGbool GetImageGeoRefrence(double& dLeft, double& dTop, double& dRight, double& dBottom, ImageUnit& nUnits);

	//! \brief 获取需要显示的图像大小
	virtual UGbool GetViewImageSize(int& nViewWidth, int& nViewHeight);

	//! \brief 获取存储生成的图片的实际像素的 buffer 的大小，每个单位代表一个字节
	virtual int GetViewImageDataSize(); 

	virtual UGbool GetViewImageData(UGbyte* pDataBuffer, int nSize);

	//! \brief 获取投影信息
	const UGchar* GetPrjCoordSys();

	// 为地图设置固定比例尺
	virtual void ConfigureMap(void *pMap, void (*pCallBack) (void *, std::vector<double>));

	// 顶层路径的设置和获取
	// 这里没有对设置的顶层路径进行任何检查，这是有意而为
	void		SetTopPath(const UGString &strTopPath) { m_strTopPath = strTopPath; }
	UGString	GetTopPath() const { return m_strTopPath; }

	UGbool IsFinished();

	// 设置用于申请网络图片的 UGMapServiceStub。该 UGMapServiceStub 并不由本对象拥有，不负责它的析构和空间回收
	void	SetMapServiceStub(UGMapServiceStub *pStub);

	// 设置外部 CacheFile 对象。该 UGAbstractFile 并不由本对象拥有，不负责它的关闭、析构和空间回收
	void	SetCacheFile(UGAbstractCacheFile *pCacheFile);

	////! \brief 判断打开密码是否正确
	//UGbool IsPassWordCorrect(const UGchar* strFileName, const UGchar * strPassword);//added by xuxr at 20111212

	// 获取是否背景透明
	virtual UGbool IsTransparentBack();

	//! \brief 获取瓦片的DP大小
	virtual UGSize GetTileSize();

	//! \brief 返回所有的比例尺级别
	virtual const UGArray<UGdouble> GetScales() const;

	//!  \brief 得到当前比例尺影像大小
	//!  \param nWidth 影像宽度
	//!  \param nHeight 影像高度
	//!  \param dScale 缓存当前比例尺
	//!  \remark 此函数主要应用于获取本地剖分缓存对应比例尺的影像宽高
	virtual UGbool GetImageSize(UGint& nWidth,UGint& nHeight,UGdouble dScale);

	//!  \brief  是否是全球缓存
	virtual UGbool IsGlobalCache();

private:
	void Reset();
	static void UGSTDCALL OnDownload(UGDownloadTileInfo result, UGlong pWnd);

	// 这里传入的像素范围（左、上、右、下）是指在最大比例尺下的像素范围。
	UGbool SetViewPort(int64_t nLeft, int64_t nTop, int64_t nRight, int64_t nBottom, int nDeviceWidth, int nDeviceHeight);
	UGbool SetViewPort(int nLeft,int nTop, int nRight, int nBottom, int nDeviceWidth, int nDeviceHeight);
	UGbool SetViewPort_aux();

	// 查找最接近的比例尺
	// nImageWidth 为在最大比例尺下需要取得数据像素宽度
	// nDeviceWidth 为当前需取得的数据将要绘制到的设备的像素宽度
	double FindNearestScale(int64_t nImageWidth, int nDeviceWidth);

	// 获取图片文件内容
	// TODO 去掉第一个 GetImageFileDataToInternalBuffer()
	UGbool GetImageFileDataToInternalBuffer(const UGString &strFullImageFileName, UGdouble dScale, int nRow, int nCol, UGbool bCompactCache = false);
	UGbool GetImageFileDataToInternalBuffer(int nRow, int nCol, UGByteArray &ByteArray, UGbool bSolidColor, UGColor color);
	UGbool GetDownloadTileInfoToInternalBuffer(UGDownloadTileInfo info);
	void PaintSolidColor(UGdouble dScale, int nRow, int nCol, UGColor color);

	// ========================== 成员变量 ==========================
	// 指示缓存是否已经顺利打开
	UGbool m_bOpened;

	// 缓存所在的目录路径，以路径分隔符结尾。
	// 如果是打开网络缓存，则为网络缓存 URL 路径不包含缓存顶层目录名。
	// 用来和 RelativePathName 合并在一起组成缓存图片源路径
	// 以 '/' 结尾
	// 例如：
	// 如果缓存 sci 在 http://localhost:8080/China400_100x100/China400.sci，则该字符串为：
	// "http://localhost:8080/"
	// 如果缓存 sci 在 D:/MapCache/China400_100x100/China400.sci，则该字符串为：
	// "D:/MapCache/"
	//UGString m_strCachePath;	

	// 缓存数据的路径。该路径是一个本地文件系统路径。
	// 例如 "D:/SuperMap/Cache/China400_100x100"
	UGString m_strTopPath;

	// 存储生成的图片的实际像素的 buffer
	_BufferManager<UGbyte> m_buffManager;

	// 缓存密码，大文件缓存所使用
	UGString m_strPassword;
	UGString m_strProjectionXML;

	UGString m_strFileName;	// 用于 Open() 函数判断是否需要关闭当前数据，打开一个新数据

	// 数据大小。GetViewImageSize() 需要使用
	int64_t m_nViewImageHeight;
	int64_t m_nViewImageWidth;

	UGMapServiceStub *m_pStub;

	// 最大的比例尺
	UGdouble m_dMaxScale;

	// 最小的比例尺
	UGdouble m_dMinScale;

	// 整个缓存的范围，包含扩展了的瓦片
	UGRect2D m_rcExtendedBounds;

	UGbool m_bExternalCacheFile;
	UGAbstractCacheFile *m_pCacheFile;
	std::auto_ptr<UGbyte> m_pDefaultColorLine;

	// 尚未找到数据的块数目
	size_t m_nLostBlocks;

	// 最近一次显示时的像素范围。该像素范围是指在最近一次显示的比例尺下的像素范围。
	PixelArea m_ViewPixelArea;

	// 最近一次显示的比例尺
	UGdouble m_dScale;

	// 用来在显示的地理范围改变的时候保护 buffer
	UGMutex m_Mutex;

	// 上一次 SetViewPort() 调用时的参数
	// 这里保存这些参数是为了防止重复计算，加快速度。
	UGdouble m_dSavedScale;
	int64_t m_nSavedPixelAreaLeft;
	int64_t m_nSavedPixelAreaRight;
	int64_t m_nSavedPixelAreaTop;
	int64_t m_nSavedPixelAreaBottom;

	UGCompactFileWrapper m_compactFile;

};

#if !defined OS_ANDROID && !defined IOS
extern "C" PLUGINMAPCACHE50_API UGImagePlugin* CreateImagePlugin();
#else
extern "C" PLUGINMAPCACHE50_API UGImagePlugin* CreateHPImagePlugin();
#endif
}

#endif // _PLUGINMAPCACHE50_H_
