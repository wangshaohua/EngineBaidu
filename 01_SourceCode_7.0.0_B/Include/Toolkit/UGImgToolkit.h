// UGImgToolkit.h: interface for the UGImgToolkit class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_UGIMGTOOLKIT_H__21224E42_7983_49CB_99BC_9792CA94305F__INCLUDED_)
#define AFX_UGIMGTOOLKIT_H__21224E42_7983_49CB_99BC_9792CA94305F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Toolkit/UGPalette.h"

namespace UGC
{
	  //!  \brief Toolkit
	struct UGCMYK 
	{
	  //!  \brief Toolkit
		UGuint CValue;
	  //!  \brief Toolkit
		UGuint MValue;
	  //!  \brief Toolkit
		UGuint YellowVal;
	  //!  \brief Toolkit
		UGuint KValue;
	};
class TOOLKIT_API UGImgToolkit  
{
public:
	  //!  \brief Toolkit
	enum ReflectType
	{
	  //!  \brief Toolkit
		XAXES,	//水平中线对称
	  //!  \brief Toolkit
		YAXES,	//垂直中线对称
	  //!  \brief Toolkit
		ORIGIN	//中点对称
	};
public:
	  //!  \brief Toolkit
	UGImgToolkit();
	  //!  \brief Toolkit
	virtual ~UGImgToolkit();

public:
	//==============================================================
	//根据象素格式和象素宽度计算DWORD对齐的按照BYTE计的实际需要宽度.
	//! \brief
	  //!  \brief Toolkit
	static UGint AlignWidth(OGDC::PixelFormat PixelFormat,UGint lPixelWidth);
	//! \brief
	  //!  \brief Toolkit
	static UGint AlignWidthByte(OGDC::PixelFormat PixelFormat,UGint lPixelWidth);
	//! \brief
	  //!  \brief Toolkit
	static UGint AlignWidthWord(OGDC::PixelFormat PixelFormat,UGint lPixelWidth);
	
	//! \brief
	  //!  \brief Toolkit
	static UGushort BitCount(OGDC::PixelFormat PixelFormat);		//根据格式计算位数.
	//! \brief
	  //!  \brief Toolkit
	static UGushort PaletteSize(OGDC::PixelFormat PixelFormat);	//得到需要的调色板大小.
	//! \brief
	  //!  \brief Toolkit
	static OGDC::PixelFormat Bit2Format(UGushort wBitCount);		//根据位数返回格式.
	
	//! \brief
	//!  \brief 将GIF文件解析问RGBA格式
	static UGbool ImageGIFToRGBA(UGImageData& imageData, UGbyte nAlpha = 255); 
	//! \brief
	  //!  \brief Toolkit
	static UGbool ImageDataToRGBA(UGImageData& imageData, UGbyte nAlpha = 255);  // 先给三维用吧以后再完善。
	//! \brief 32位Colors颜色转化为ImageData形式，供组件使用
	//! \param imageData	 要转成的ImageData格式[in/out]
	//! \param nWidth		 要转成的ImageData的宽度[in]
	//! \param nHeight		 要转成的ImageData的高度[in]
	//! \param pData		 传入的32位颜色串[in]
	//! \return 转换是否成功
	//! \remarks 传入的为32位字符串，长度为nWidth*32/4*nHeight,转换后的Imagedata也为232位格式
	//! \brief
	static UGbool ColorsToImageData(UGImageData& imageData, UGint nWidth,UGint nHeight,UGColor* pData);  // 先给三维用吧以后再完善。
	  //!  \brief Toolkit
	//! \brief
	static UGuint GetValue(const UGbyte* pByte, UGint nWidthBytes, OGDC::PixelFormat pixelFormat, UGuint x, UGuint y);
	//! \brief
	  //!  \brief Toolkit
	static void SetValue(UGbyte* pByte, UGint nWidthBytes, OGDC::PixelFormat pixelFormat, UGuint x, UGuint y, UGuint nValue);
	//! \brief 镜像ImageData。
	//! \param arySrcImgData [in]。
	//! \param nReflectType 镜像类型[in]。
	//! \return 。
	//! \remarks 。
	//! \attention 。
	static UGArray<UGImageData*> ReflectImageData(UGArray<UGImageData*>& arySrcImgData,ReflectType nReflectType);	
	
	#if PACKAGE_TYPE==PACKAGE_UGC
	//色彩空间转换------------------------------------------------------------
	//! \brief
	  //!  \brief Toolkit
	static UGint RGB2CMY(UGint color);
	//! \brief
	  //!  \brief Toolkit
	static UGint CMY2RGB(UGint color);
	//! \brief
	  //!  \brief Toolkit
	static UGint RGB2YIQ(UGint color);
	//! \brief
	  //!  \brief Toolkit
	static UGint YIQ2RGB(UGint color);
	//! \brief
	  //!  \brief Toolkit
	static UGint RGB2YUV(UGint color);
	//! \brief
	  //!  \brief Toolkit
	static UGint YUV2RGB(UGint color);
	//! \brief
	  //!  \brief Toolkit
	static UGint RGB2YCC(UGint color);
	//! \brief
	  //!  \brief Toolkit
	static UGint YCC2RGB(UGint color);
	//! \brief CMYK与RGB转换 与SFC保持兼容
	static UGint CMYK2RGB(UGCMYK& cmyk);
	  //!  \brief Toolkit
	static UGCMYK RGB2CMYK(UGColor color);
	//! \brief
	static void RGBtoHSL(UGColor rgb, UGdouble& H, UGdouble& S, UGdouble& L);
	//! \brief
	static UGColor HLStoRGB(const UGdouble& H, const UGdouble& L, const UGdouble& S);
	//! \brief
	static UGdouble HuetoRGB(UGdouble m1, UGdouble m2, UGdouble h);
	#endif // end declare ugc API

	//! \brief 判断着色表是否8位灰度
	static UGbool IsGrayColorset(const UGColorset &colorset);


	//! \brief 图片处理成2的N次方，并可以避免三维中半个像素的问题。
	//! \param imageData 图片数据 [out]。
	//! \param nRealWidth 有效数据的宽度 [out]。
	//! \param nRealHeight 有效数据的高度 [out]。
	//! \return 。
	//! \remarks 。
	//! \attention 。
	static void ImageDataToPowerOfTwo(UGImageData& imageData, UGint& nRealWidth, UGint& nRealHeight, UGbyte chA = 255);
};
}

#endif // !defined(AFX_UGIMGTOOLKIT_H__21224E42_7983_49CB_99BC_9792CA94305F__INCLUDED_)


