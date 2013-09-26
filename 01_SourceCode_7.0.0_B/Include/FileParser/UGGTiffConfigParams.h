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

#if !defined(AFX_UG_GTIFF_FILEPARSERCONFIGPARAMS_H__INCLUDED_)
#define AFX_UG_GTIFF_FILEPARSERCONFIGPARAMS_H__INCLUDED_

#include "FileParser/UGRasterConfigParams.h"
#include "FileParser/UGExchangeFileType.h"

namespace UGC 
{


//! \brief GeoTiff的导入参数配置。
class FILEPARSER_API UGGTiffImportParams : public UGRasterImportParams
{
	
public:

	//! \brief 构造函数。
	UGGTiffImportParams();

	//! \brief 获取文件类型。
	//! \return 返回GTiff类型。
	virtual inline UGint GetFileType() const { return UGFileType::GTiff; }

	//! \brief 获取要导入的波段索引。
	//! \return 返回要导入的波段索引。
	UGArray<UGint> GetImportBandIndexs(){return m_arrBandsRaster;}

	//! \brief 强制设置要导入的波段索引。
	//! \param  [in] 要导入的波段索引。
	void SetImportBandIndexs(const UGArray<UGint>& indexs){m_arrBandsRaster.Copy(indexs);}

	//! \brief 设置生成的地理坐标文件的路径。
	//! \param strWorldFile [in]。
	void SetWorldFilePath(const UGString& strWorldFile) { m_strWorldFile = strWorldFile; }

	//! \brief 得到地理坐标文件路径
	//! \param strWorldFile [in]。
	UGString GetWorldFilePath() const { return m_strWorldFile; }

protected:

	//! \brief  目标数据集像素格式
	PixelFormat m_nPixelFormat;

	//! \brief 选择导入的波段索引。
	UGArray <UGint> m_arrBandsRaster;

	//! \brief 坐标参考文件
	UGString m_strWorldFile;

};


//! \brief GeoTIFF的导出参数配置。
class FILEPARSER_API UGGTiffExportParams : public UGRasterExportParams
{
public:

	//! \brief 对于仿射坐标的配置处理
	enum EmExpTran{
		//! \brief 不导出任何反射配置
		ET_NOEXP,
		//! \brief 导出到tif文件内部
		ET_INNER,
		//! \brief 导出成tfw
		ET_OUTER
	};

	//! \brief 对于仿射坐标的配置处理
	enum EmExpPrj{
		//! \brief 不导出任何坐标系配置
		EP_NOEXP, 
		//! \brief 导出到tif文件内部
		EP_INNER,
		//! \brief 导出成prj
		EP_OUTER
	};

	//! \brief 对于导出成多波段的强制设置
	enum EmExpMB{
		//! \brief 不改变原图像设置
		EMB_SAME, 
		//! \brief 强制导出单波段
		EMB_SBIMG,
		//! \brief 强制导出多波段
		EMB_MBIMG
	};

public:

	//! \brief 构造函数。
	UGGTiffExportParams();

	//! \brief 获取文件类型。
	//! \param  [in]。
	//! \return 返回GTiff类型。
	virtual inline UGint GetFileType() const{ return UGFileType::GTiff; }

	//! \brief 获取导出仿射坐标类型。
	inline EmExpTran GetExportTranType() const  {return m_eExportTran;}

	//! \brief 获取导出投影坐标系类型。
	inline EmExpPrj GetExportPrjType() const  {return m_eExportPrj;}
	
	//! \brief 获取导出投影坐标系类型。
	inline void SetExportTranType(EmExpTran ttype) {m_eExportTran = ttype;}

	//! \brief 获取导出投影坐标系类型。
	inline void SetExportPrjType(EmExpPrj ptype) {m_eExportPrj = ptype;}

	//! \brief 获取是否强制导出成多波段。
	inline EmExpMB GetExportMuliBand() const  {return m_eExpMuliBand;}
	
	//! \brief 设置强制导出多波段。
	inline void ExportMuliBand(EmExpMB mbtype) {m_eExpMuliBand = mbtype;}


	//! \brief 设置图像的分辨率/DPI.
	//! \param ndpi [in] 图像的DPI。
	//! \remarks 此接口用于地图出图。
	//! \attention 
	virtual void SetResolution(UGint ndpi) {m_ndpi=ndpi;};

	////! \brief 设置图像的分辨率/DPI.
	//! \param 。
	//! \remarks 。
	//! \attention 具体的格式配置参数需要重写此函数。
	virtual UGint GetResolution() {return m_ndpi;};

protected:

	UGint m_ndpi;

private:
	
	//! \brief 设置导出仿射坐标类型。
	EmExpTran m_eExportTran;

	//! \brief 设置导出投影坐标系类型。
	EmExpPrj m_eExportPrj;

	//! \brief 设置是否导出成多波段
	EmExpMB m_eExpMuliBand;

private:
};

} //namespace UGC
#endif // !defined(AFX_UG_GTIFF_FILEPARSERCONFIGPARAMS_H__INCLUDED_)

