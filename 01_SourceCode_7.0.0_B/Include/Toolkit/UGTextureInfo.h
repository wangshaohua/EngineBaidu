#ifndef UGTEXTUREWRAP_H
#define  UGTEXTUREWRAP_H

#include "Stream/ugdefs.h"
#include "Base/OgdcString.h"

#define MACHINE_TAG (_U("TexImage@")) 

namespace UGC
{
	class TOOLKIT_API UGTextureInfo
	{
	public:
		UGTextureInfo();
		~UGTextureInfo();
		const UGTextureInfo& operator=(const UGTextureInfo& Info);
		UGTextureInfo(const UGTextureInfo& Info);
		// 接管了外边给的内存
		UGTextureInfo(OGDC::PixelFormat enFormat,OgdcUint Width,OgdcUint Height,void* data,OgdcUint nSize,OgdcString& path);

	public:
		UGbool			m_bLoadImage;

		// 纹理图片的像素格式
		OGDC::PixelFormat		m_enFormat;

		// 纹理图片的宽度
		OgdcUint		m_nWidth;

		// 纹理图片的高度
		OgdcUint		m_nHeight;

		// 纹理图片流数据
		OgdcByte*		m_pBuffer;

		// 纹理图片流数据的长度,带压缩时很重要
		OgdcUint		m_nSize;

		// 纹理图片的索引路径
		OgdcString		m_strPath;

		OgdcString		m_strName;

		// 纹理图片数据中一共有几层mipmap
		OgdcUint        m_nMipLev;

		// 纹理图片的压缩类型
		OgdcInt			m_nCompress;
	};
}
#endif

