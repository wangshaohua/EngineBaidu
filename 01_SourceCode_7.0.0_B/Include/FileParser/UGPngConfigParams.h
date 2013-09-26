// UGFileParserConfigParams.h: interface for the UGFileParserConfigParams class.
//////////////////////////////////////////////////////////////////////////
//                    _   _   ____   ____                    
//   Project         | | | | / ___) / ___)                   
//                   | | | || | __ | |                       
//                   | |_| || |_\ || \___                    
//                    \____/ \____| \ ___)     6.0           
//                                                           
//!  \file headerfile.h
//!  \brief Class 。实现PNG导入导出
//!  \details 。
//!  \author 张朔。
//!  \attention 
//!   Copyright (c) 1996-2010 SuperMap Software Limited Company.  <br> 
//!   All Rights Reserved.
//!  \version 6.0
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_UG_PNG_FILEPARSERCONFIGPARAMS_H__INCLUDED_)
#define AFX_UG_PNG_FILEPARSERCONFIGPARAMS_H__INCLUDED_

#include "FileParser/UGRasterConfigParams.h"
#include "FileParser/UGExchangeFileType.h"

namespace UGC 
{


//! \brief PNG的导入参数配置。
class FILEPARSER_API UGPngImportParams : public UGRasterImportParams
{
	
public:

	//! \brief 重载获取文件格式类型的函数。
	virtual UGint GetFileType() const	{ return UGFileType::PNG; }

	//! \brief 设置生成的地理坐标文件的路径。
	void SetWorldFilePath(const UGString& strWorldFile) { m_strWorldFile = strWorldFile; }

	//! \brief 得到地理坐标文件路径
	UGString GetWorldFilePath() const { return m_strWorldFile; }

protected:

	UGString m_strWorldFile;
	

private:
};



//! \brief PNG的导出参数配置。
class FILEPARSER_API UGPngExportParams : public UGRasterExportParams
{

public:

	//! \brief 设置png出图压缩率
	enum PngQuality {
		NO_COMPRESSION,		//无压缩
		BEST_SPEED,			//快速压缩，压缩比为1，速度较快
		DEFAULT,			//默认压缩，压缩比为6
		BEST_COMPRESSION	//最优压缩，压缩比为9，速度较慢
	};

	//! \brief 构造函数。
	//! \remarks 。
	UGPngExportParams();
	
	//! \brief 析构函数。
	//! \remarks 。
	~UGPngExportParams();


	//! \brief 重载获取文件格式类型的函数。
	virtual UGint GetFileType() const	{ return UGFileType::PNG; }

	//! \brief 设置生成的地理坐标文件的路径。
	void SetWorldFilePath(const UGString& strWorldFile) { m_strWorldFile = strWorldFile; }

	//! \brief 得到地理坐标文件路径
	UGString GetWorldFilePath() const { return m_strWorldFile; }

	//! \brief 获取png出图压缩码
	PngQuality GetPngQuality() const { return m_enumPngQuality; }

	//! \brief 设置PNG出图压缩码
	void SetPngQuality(PngQuality pngQ = UGPngExportParams::DEFAULT) { m_enumPngQuality = pngQ; 	}


	//! \brief 设置图像的分辨率/DPI.
	//! \param ndpi [in] 图像的DPI。
	//! \remarks 此接口用于地图出图。
	//! \attention 目前支持JPG。
	virtual void SetResolution(UGint ndpi) {m_ndpi=ndpi;};

	////! \brief 设置图像的分辨率/DPI.
	//! \param 。
	//! \remarks 。
	//! \attention 具体的格式配置参数需要重写此函数。
	virtual UGint GetResolution() {return m_ndpi;};

	////! \brief 获取是否导出为8位png.
	//! \param   默认为False。
	//! \remarks 。
	//! \attention 。
	UGbool GetSaveAs8Bit(){return m_bIsSaveAs8Bit;}

	////! \brief 设置是否导出为8位png.
	//! \param 。
	//! \remarks 。
	//! \attention 。
	void SetSaveAs8Bit(UGbool bIsSaveAs8Bit){m_bIsSaveAs8Bit = bIsSaveAs8Bit;}

protected:

	UGString m_strWorldFile;

	UGint m_ndpi;

private:
	//! \brief png压缩码
	PngQuality m_enumPngQuality;

	//! \brief png导出为8位标识，默认为False
	UGbool m_bIsSaveAs8Bit;
};


} //namespace UGC
#endif // !defined(AFX_UG_PNG_FILEPARSERCONFIGPARAMS_H__INCLUDED_)

