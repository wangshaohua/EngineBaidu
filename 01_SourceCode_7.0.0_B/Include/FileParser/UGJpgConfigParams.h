// UGFileParserConfigParams.h: interface for the UGFileParserConfigParams class.
//////////////////////////////////////////////////////////////////////////
//                    _   _   ____   ____                    
//   Project         | | | | / ___) / ___)                   
//                   | | | || | __ | |                       
//                   | |_| || |_\ || \___                    
//                    \____/ \____| \ ___)     6.0           
//                                                           
//!  \file headerfile.h
//!  \brief Class 的接口定义。
//!  \details 文件详细信息。
//!  \author linwenyu。
//!  \attention 
//!   Copyright (c) 1996-2008 SuperMap Software Limited Company.  <br> 
//!   All Rights Reserved.
//!  \version 6.0
//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_UG_JPG_FILEPARSERCONFIGPARAMS_H__INCLUDED_)
#define AFX_UG_JPG_FILEPARSERCONFIGPARAMS_H__INCLUDED_

#include "FileParser/UGRasterConfigParams.h"
#include "FileParser/UGExchangeFileType.h"

namespace UGC {

//! \brief JPEG的导入参数配置。
class FILEPARSER_API UGJpgImportParams : public UGRasterImportParams
{	
public:

	//! \brief 构造函数	
	//! \return 。
	UGJpgImportParams() {};
	
	//! \brief 析构函数	
	//! \return 。
	~UGJpgImportParams() {};

public:


	//! \brief 返回当前格式转换参数类型。
	virtual inline UGint GetFileType() const { return UGFileType::JPG; }

	//! \brief 设置生成的地理坐标文件的路径。
	void SetWorldFilePath(const UGString& strWorldFile) { m_strWorldFile = strWorldFile; }

	//! \brief 得到地理坐标文件路径
	UGString GetWorldFilePath() const { return m_strWorldFile; }


protected:

	UGString m_strWorldFile;


	
};


//! \brief JPEG的导出参数配置。
class FILEPARSER_API UGJpgExportParams : public UGRasterExportParams
{
public:

	//! \brief 构造函数	
	UGJpgExportParams(){ m_nquality = 75;m_nDpi=0; }

	//! \brief 析构函数	
	~UGJpgExportParams() {}

public:

	//! \brief 返回当前格式转换参数类型。
	virtual inline UGint GetFileType() const { return UGFileType::JPG; }


	//! \brief 设置生成的地理坐标文件的路径。
	void SetWorldFilePath(const UGString& strWorldFile) {m_strWorldFile = strWorldFile;}

	//! \brief 得到地理坐标文件路径
	UGString GetWorldFilePath() const { return m_strWorldFile; }

	//! \brief 设置Jpeg文件的压缩率。
	//! \param  nQuality [in]  默认压缩率为75，nQuality取值范围[10, 100]
	//! \attention nQuality值越小，图像压缩率越高，质量越差。。
	virtual void SetQuality(UGint nQuality) { m_nquality = nQuality; }

	//! \brief 得到压缩率。	
	virtual UGint GetQuality() const {return m_nquality;}

	//! \brief 设置图像的分辨率/DPI.
	//! \param ndpi [in] 图像的DPI。
	//! \remarks 此接口用于地图出图。
	//! \attention 目前支持JPG。
	virtual void SetResolution(UGint ndpi) {m_nDpi = ndpi;}

	////! \brief 设置图像的分辨率/DPI.
	//! \param 。
	//! \remarks 。
	//! \attention 。
	virtual UGint GetResolution() {return m_nDpi;};


protected:

	UGint m_nquality;

	UGString m_strWorldFile;

	UGint m_nDpi;
};

} //namespace UGC
#endif // !defined(AFX_UG_JPG_FILEPARSERCONFIGPARAMS_H__INCLUDED_)

