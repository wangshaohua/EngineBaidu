// UGRasterImportParams.h: interface for the UGRasterImportParams class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_UGRASTERIMPORTPARAMS_H__AFD927F6_BD78_470E_B1FA_56EF86E30E91__INCLUDED_)
#define AFX_UGRASTERIMPORTPARAMS_H__AFD927F6_BD78_470E_B1FA_56EF86E30E91__INCLUDED_


#include "Stream/ugexports.h"
#include "FileParser/UGFileParserConfigParams.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


namespace UGC 
{
	typedef UGdouble UGNoValue;
	typedef OGDC::PixelFormat UGPixelFormat;

	//! \brief 波段的基本信息。
	class FILEPARSER_API UGRasterBandInfo
	{
	public:

		//! \brief 构造函数。
		UGRasterBandInfo()
		{
			m_nBandID =-1;
			m_nIndex =-1;
			m_nDatasetID=-1;
			m_bAvail = FALSE;
			m_ePixelFormat =IPF_UNKNOWN;
			m_nWidthBytes = 0;
			m_nOptions =0;
			m_nCodecType = UGDataCodec::encNONE;
			m_dMinZ = (1.0e+21);
			m_dMaxZ = -(1.0e+21);
			m_dbNoValue = -9999;
			m_nScalar = 0;
			m_bHasExtremum = FALSE;
		}

		//! \brief 析构函数
		~UGRasterBandInfo()
		{
		}


		//! \brief 等号拷贝函数。
		//! \param bInfo [in]。
		void operator=(const UGRasterBandInfo& bInfo)	
		{
			m_nIndex = bInfo.m_nIndex;
			m_nBandID = bInfo.m_nBandID;
			m_ePixelFormat = bInfo.m_ePixelFormat;
			m_nCodecType = bInfo.m_nCodecType;
			m_nOptions = bInfo.m_nOptions;
			m_nWidthBytes = bInfo.m_nWidthBytes;
			m_dMaxZ = bInfo.m_dMaxZ;
			m_dMinZ = bInfo.m_dMinZ;
			m_Colorset.RemoveAll();
			m_Colorset.Copy(bInfo.m_Colorset);
			m_strName = bInfo.m_strName;	
			if(bInfo.m_strFieldName.IsEmpty())
			{
				m_strFieldName = bInfo.m_strName;
			}
			else
			{
				m_strFieldName = bInfo.m_strFieldName;
			}
			m_dbNoValue = bInfo.m_dbNoValue;
			m_nWidthBytes = bInfo.m_nWidthBytes;
			m_nDatasetID = bInfo.m_nDatasetID;
			m_bAvail = bInfo.m_bAvail;
			m_nScalar = bInfo.m_nScalar;
			m_strDescription = bInfo.m_strDescription;
			m_bHasExtremum = bInfo.m_bHasExtremum;
		}

		//! \brief 波段数据库中索引
		UGint m_nBandID;
		//! \brief 波段索引
		UGint m_nIndex;
		//! \brief 波段所在的数据集ID
		UGint m_nDatasetID;
		//! \brief 波段的名字
		UGString m_strName;
		//! \brief 波段所在的列名
		UGString m_strFieldName;
		//! \brief 当前波段是否有效
		UGbool m_bAvail;
		//! \brief 波段的描述信息
		UGString m_strDescription;
		//! \brief 波段的像素格式
		UGPixelFormat m_ePixelFormat;
		//! \brief 波段的影像行字节数
		UGint m_nWidthBytes;
		//! \brief 选项信息
		UGint m_nOptions;
		//! \brief 数据编码类型
		UGDataCodec::CodecType m_nCodecType;
		//! \brief 三维Bounds的最小值
		UGdouble m_dMinZ;
		//! \brief 三维Bounds的最大值
		UGdouble m_dMaxZ;
		//! \brief 调色板
		UGColorset m_Colorset;
		//! \brief 无效值，如果某一点的值是m_NoValue,将认为这一点没有值
		UGdouble m_dbNoValue;
		//! \brief 最大blockSize
		UGint m_nMaxBlockSize;
		//! \brief 当前波段符号 FALSE 无符号，TRUE 有符号
		UGint m_nScalar;

		//! \brief 是否已经计算了极值
		UGbool m_bHasExtremum;
	};

	typedef UGRasterBandInfo BandInfo;

	//! \brief 定义栅格的基本信息。
	class FILEPARSER_API RasterInfo
	{
	public:
		//! \brief 	影象的宽
		UGint m_nWidth;
		//! \brief 	影象的高
		UGint m_nHeight;
		//! \brief 	影象的象素格式
		UGPixelFormat m_ePixelFormat;//UGint m_nPixelFormat;

		//! \brief 	影象的波段个数
		UGint m_nBandCount;	
		//! \brief 	是否多波段的标志
		UGbool m_bIsMultiBand;	
		//! \brief 	是否是扫描行，否则是块状型
		UGbool m_bIsScanline;
		//! \brief 	是否是按像素方式读取
		UGbool m_bIsReadPixel;

		//! \brief 影象的Bounds
		UGRect2D m_rc2Bounds;

		//! \brief block高。
		UGint m_nBlockHeight;
		//! \brief block宽。
		UGint m_nBlockWidth;

		//! \brief 是否有扫描线偏移，默认为False，FME导入时为TRUE
		UGbool m_bColOffset;

		//! \brief 波段信息（如果是多波段的话）
		UGArray<BandInfo> m_arrBandInfos;

		//! \brief 目标数据集名称
		UGString m_strDTName;

		//! \brief 栅格索引（在SDE中使用，其他默认为0）
		UGint m_nIndex;

	public:

		//! \brief 构造函数。
		RasterInfo();

		//! \brief 拷贝构造函数。
		RasterInfo(const RasterInfo& rInfo);

		//! \brief 析构函数。
		virtual ~RasterInfo();

		//! \brief 清楚所有信息恢复默认值。
		void Clear();

		//! \brief 重载拷贝等号。
		void operator=(const RasterInfo& rInfo);

		//! \brief 影像的颜色空间。
		ImgColorSpace GetImgColorSpace() { return m_colorSpace;};	

		//! \brief 设置影像的颜色空间。
		//! \param cs  需要设置的颜色空间。[in]
		void SetImgColorSpace(ImgColorSpace cs) {m_colorSpace = cs;}	

		//! \brief 设置颜色表。
		//! \param cs 新的颜色表。[in]
		void SetColorset(const UGColorset& cs);

		//! \brief 清空颜色表（判断有无颜色表时返回否）。
		void ResetColorset();

		//! \brief 判断是否有颜色表。
		UGbool HasColorset() const {return m_bHasColorset;}

		//! \brief 获取颜色表。
		//! \return 如果没有，返回空指针。
		const UGColorset* const GetColorset() const;

		//! \brief 判断是否有NoData。
		UGbool HasNoValue() const{return m_bHasNoValue;}

		//! \brief 设置Nodata。
		void SetNoValue(UGdouble noValue)	
		{
			m_bHasNoValue = TRUE;
			m_dNoValue = noValue;
		}

		//! \brief 清空Nodata（使其不存在）。
		void ResetNoValue()	{m_bHasNoValue = FALSE;}

		//! \brief 获取Nodata。
		const UGNoValue* GetNoValue() const;

		//! \brief 获取X方向分辨率。
		UGdouble GetResoulutionX() const { return m_rc2Bounds.Width() / m_nWidth; }

		//! \brief 获取Y方向分辨率。
		UGdouble GetResoulutionY() const { return m_rc2Bounds.Height() / m_nHeight; }

		//! \brief 判断是否有空间参考。
		UGbool HasPrjCoordSys() const {return m_bHasPrjCoordSys;}

		//! \brief 设置空间参考。
		void SetPrjCoordSys(const UGPrjCoordSys& prj);

		//! \brief 清空空间参考(使其无)。
		void ResetPrjCoordSys()	{m_bHasPrjCoordSys = FALSE;}

		//! \brief 获取空间参考。
		const UGPrjCoordSys* GetPrjCoordSys() const;

		//! \brief 获取影象数据编码类型
		UGDataCodec::CodecType GetEncodeType() const {return m_enType;}

		//! \brief 设置影像数据的编码类型
		void SetEncodeType(UGDataCodec::CodecType nType){m_enType = nType;}

	protected:

		//! \brief 颜色空间。
		ImgColorSpace m_colorSpace;

		//! \brief 	影象的调色版
		UGColorset m_colorset;

		//! \brief 	是否带调色板
		UGbool m_bHasColorset;

		//! \brief 无效值
		UGNoValue m_dNoValue;

		//! \brief 是否有无效值。
		UGbool m_bHasNoValue;

		//! \brief 是否有坐标系统。
		UGbool m_bHasPrjCoordSys;

		//! \brief 投影坐标系。
		UGPrjCoordSys *m_prjSys;

		//! \brief 影像的数据编码类型
		UGDataCodec::CodecType m_enType;

	};

	//! \brief 定义栅格的基本信息集合。
	class FILEPARSER_API RasterInfos:public UGArray<RasterInfo>
	{
	public:
		RasterInfos();

		virtual ~RasterInfos();
	};

	typedef UGArray<BandInfo> BandInfos; 

	//! \brief 栅格导入参数类。
	class FILEPARSER_API UGRasterImportParams : public UGImportParams
	{
		friend class UGWorkspaceImportParams;
	public:
        
		// !\brief 设置导入时候忽略颜色的模式
		// 0: 不忽略颜色
		// 1: 按照单一颜色忽略
		// 2: 按照扫描线的方式忽略
		enum IgnoreMode
		{
			IgnoreNull =0,
			IgnoreSignal =1,
			IgnoreBorder =2,
		};

		//! \brief 构造函数。
		UGRasterImportParams();

		//! \brief 析构函数。
		virtual ~UGRasterImportParams();

	public:

		//! \brief 设置读取图像时，是否认为它是单波段的。
		//! \param TRUE [in]。
		//! \remarks 如：3波段每波段8位的数据，设置此参数，那图像将被认为是一副24的GRB的数据。
		void SetReadAsOneBand(UGbool bAsOneBand = TRUE);	

		UGbool GetReadAsOneBand() const;	

		//! \brief 设置是否导入为多波段数据集。
		//! \param bAsMultiBands [in]。
		void SetImportAsMultiBandsDataset(UGbool bAsMultiBands = TRUE);	


		//! \brief 得到是否导入为多波段数据集。
		UGbool GetImportAsMultiBandsDataset() const;

		//! \brief 设置是否开启位深转换功能。
		//! \param pixelFormat [in]。
		//! \remarks 配合SetForcePixelFormat函数一起使用，设置为TURE时SetForcePixelFormat函数才有效	
		void SetForcePixelEnable(UGbool bEnable = TRUE);

		//! \brief 得到位深转换功能是否开启。
		//! \param pixelFormat [in]。
		//! \attention 	返回值为False时，SetForcePixelFormat函数无效
		UGbool GetForcePixelEnable() const;

		//! \brief 设置强制的目标数据集位深。
		//! \param pixelFormat [in]。
		//! \remarks 注意，该参数只在数据导入导出时有效，直接打开时该参数无效。
		//! \attention 导入时，一般导入后数据集的位深和源数据位深一致，
		//!            需要更改目标数据集位深时，调用此接口设置。
		void SetForcePixelFormat(UGPixelFormat pixelFormat);	

		//! \brief 获取用户强制的位深格式。
		UGPixelFormat GetForcePixelFormat() const;	

		void SetImportBandInfos(const BandInfos& impBandInfos);	

		//! \brief 获取波段信息。
		BandInfos GetBandInfos() const;	

		//! \brief 设置是否建立金字塔。
		//! \param TRUE [in] 是否建立金字塔。
		void SetBuildPyramid(UGbool bBuild = TRUE);	

		//! \brief 获取是否建立金字塔。
		UGbool GetBuildPyramid() const;	

		//! \brief 获取颜色空间。
		ImgColorSpace GetColorSpace();	

		//! \brief 设置颜色空间。
		//! \param colorSpace [in] 颜色空间。
		void SetColorSpace(ImgColorSpace colorSpace);
		
		//! \brief 追加数据集时，设置忽略的边界值
// 		void SetBorderValue(UGdouble dValue) {m_dBorderValue = dValue;}
// 		UGdouble GetBorderValue() const { return m_dBorderValue; }
		
		//! \brief 追加数据集时，设置是否忽略边界值
// 				void SetIsIgnoreBorderValue(UGbool bIgnoreBorderColor) {m_bIgnoreBorderColor=bIgnoreBorderColor;}
// 				UGbool GetIsIgnoreBorderValue() const { return m_bIgnoreBorderColor; }
//       

        //! \brief 追加数据集时候，设置忽略颜色值，综合忽略颜色数值和和边界值的功能
		void SetIgnoreValues( UGArray<UGdouble>dValues);
		//! \brief 获取忽略颜色数组数值
		void GetIgnoreValues(UGArray<UGdouble>&dValues)const;


		void SetIgnoreMode(IgnoreMode eIgnoreMode);
        //! \brief 获取忽略模式
		IgnoreMode GetIgnoreMode()const;
      
		//! \brief 针对SDE，设置当前的栅格数据集索引
		void SetRasterIndex(UGint nIndex){m_nRasterIndex = nIndex;}

		//! \brief 针对SDE,获取当前的栅格数据集索引
		UGint GetRasterIndex(){return m_nRasterIndex;}

		//! \brief 设置生成的地理坐标文件的路径。
		virtual void SetWorldFilePath(const UGString& strWorldFile) { m_strWorldFile = strWorldFile; }

		//! \brief 得到地理坐标文件路径
		virtual UGString GetWorldFilePath() const { return m_strWorldFile; }
		//! \brief 设置导入的数据集结果信息。
		//! \param impDatasetInfos [in]。
		//! \return 。
		//! \remarks 。
		//! \attention 。
		void SetImportDatasetInfos(const RasterInfos& impDatasetInfos);	

		//! \brief 得到导入的数据集结果信息。
		//! \param  [in]。
		//! \return 。
		//! \remarks 。
		//! \attention 。
		RasterInfos& GetImportDatasetInfos();

	protected:

		//! \brief  目标数据集像素格式
		UGPixelFormat m_nPixelFormat;


		//! \brief 选择导入的波段索引。
		UGArray <UGint> m_arrBandsRaster;
        //! \brief 颜色空间
		ImgColorSpace m_nImgColorSpace; 
        
		//!\brief 波段信息
		BandInfos m_impBandInfos;	
        
		//!brief 目标数据集名称
		UGString m_strDestDTRName;
        
		//!\brief 波段索引值
		UGint m_nRasterIndex;
        
		//!brief 影像坐标参考文件
		UGString m_strWorldFile;
        
		//!\brief 栅格数据集信息
		RasterInfos m_dtInfos;
        
// 		//!brief 是否忽略背景颜色
		//UGbool m_bIgnoreBorderColor;
        
		//!\brief 忽略颜色数值
		UGArray<UGdouble>m_dIgnoreValues;
         
	    //!\brief 忽略颜色模式
		IgnoreMode m_eIgnoreMode;
	};

	//////////////////////////////////////////////////////////////////////////
	// raster export params
	//////////////////////////////////////////////////////////////////////////

	//! \brief 栅格导出参数基类。
	class FILEPARSER_API UGRasterExportParams : public UGExportParams
	{
	public:

		//! \brief 构造函数。
		UGRasterExportParams();

		//! \brief 析构函数。
		virtual ~UGRasterExportParams();

	public:

		//! \brief 设置是否开启位深转换功能。
		//! \param pixelFormat [in]。
		//! \remarks 配合SetForcePixelFormat函数一起使用，设置为TURE时SetForcePixelFormat函数才有效	
		void SetForcePixelEnable(UGbool bEnable = TRUE);

		//! \brief 得到位深转换功能是否开启。
		//! \param pixelFormat [in]。
		//! \attention 	返回值为False时，SetForcePixelFormat函数无效
		UGbool GetForcePixelEnable() const;

		//! \brief 强制设置导出的影像的位深。
		//! \param pixFormat [in]。
		//! \remarks 注意，该参数只在数据导入导出时有效，直接打开时该参数无效。。
		void SetForcePixelFormat(UGPixelFormat pixFormat);	

		//! \brief 获取导出影像的位深。
		//! \return 返回导出影像的位深。
		UGPixelFormat GetForcePixelFormat() const;		

		//! \brief 设置影像块(Tile)的大小(宽，高)。
		//! \param blockWidth [in] Tile的宽。
		//! \param blockHeight [in] Tile的高。
		void SetBlockSize(UGint blockWidth, UGint blockHeight);	

		//! \brief 获取影像块(Tile)的大小(宽，高)。
		//! \param blockWidth [in] Tile的宽。
		//! \param blockHeight [in] Tile的高。
		void GetBlockSize(UGint& blockWidth, UGint& blockHeight) const;	

		//! \brief 获取要导出的栅格数据集名称。
		UGString GetDtNameToBeExported()const;

		//! \brief 设置要导出的栅格数据集名称。
		//! \param  name [in] 设置的名称。
		void SetDtNameToBeExported(UGString name);

		//! \brief 设置透明
		void SetTransparent(UGbool bTrans = TRUE);

		//! \brief 获取是否支持透明
		UGbool GetTransparent()const;

		//! \brief 设置透明色
		void SetTransColor(UGColor cRGB);

		//! \brief 获取透明色
		UGColor GetTransColor() const;

		//! \brief 设置文件的压缩率。
		//! \param  nQuality [in] 
		//! \remarks 不是每个格式都支持设置压缩率 。
		//! \attention 欲知具体支持程度，详见具体格式的配置参数，如JPEG
		virtual void SetQuality(UGint nQuality) {}

		//! \brief 得到压缩率。	
		virtual UGint GetQuality() const {return 0;}

		//		void TransImageDataPreprocess(UGbyte *ImageData, UGlong nSize, UGbool bTrans);
		//! \brief  ImageData预处理，修正32bit数据中的Alpha波段
		//! \param UGbyte *ImageData
		//! \param UGlong nSize ImageData大小
		//! \param UGbool bTrans  是否透明
		//! \return UGbool 用户设置透明之后，返回是否有像素被透明
		UGbool TransImageDataPreprocess(UGbyte *ImageData, UGlong nSize, UGbool bTrans);

		//! \brief 设置组合波段导出
		//! \param bnds [in] 波段组合。
		void SetCombineBands(const UGArray<UGint>& bnds);

		//! \brief 获取组合波段导出
		//! \param obnds [out] 波段组合。
		void GetCombineBands(UGArray<UGint>& obnds) const ;

		//! \brief 设置图像的分辨率/DPI.
		//! \param ndpi [in] 图像的DPI。
		//! \remarks 此接口用于地图出图。
		//! \attention 目前支持JPG、PNG、TIF。
		virtual void SetResolution(UGint ndpi) {};

		////! \brief 设置图像的分辨率/DPI.
		//! \param 。
		//! \remarks 。
		//! \attention 具体的格式配置参数需要重写此函数。
		virtual UGint GetResolution() {return 0;};

	protected:

		//! \brief 目标文件像素格式。
		UGPixelFormat m_nPixelFormat;

		//! \brief 影像块的宽。
		UGint m_nBlockWidth;

		//! \brief 影像块的高。
		UGint m_nBlockHeight;

		//! \brief 要导出的数据集名称。
		UGString m_strDatasetName;

		//{{修改原因 添加GIF与PNG的透明支持 修改人:张朔 2009-6-18 12:58:09
		//! \brief 标识是否透明
		//! \remarks 在gif与png中用到
		UGbool m_bTransparent;

		//! \brief 存储透明色，由显示使用SetTransColor赋值
		UGColor m_cTransColor;

		//! \brief 用来判断是否设置过透明色
		UGbool m_bHaveTransColorSet;
		//}}  2009-6-18 12:58:09

		//{{修改原因 添加波段组合功能 修改人:李林 2009-11-9 12:41:09
		//! \brief 用来组合导出波段
		UGArray<UGint> m_arrCombineBands;
		//}}  2009-11-9 12:41:09

	};

} //namespace UGC

#endif // !defined(AFX_UGRASTERIMPORTPARAMS_H__AFD927F6_BD78_470E_B1FA_56EF86E30E91__INCLUDED_)

