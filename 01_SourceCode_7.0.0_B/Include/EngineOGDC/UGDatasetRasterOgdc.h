// UGDatasetRasterOgdc.h: interface for the UGDatasetRasterOgdc class.
//
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//!  \file UGDatasetRasterOgdc.h
//!  \brief UGDatasetRasterOgdc 的接口定义。
//!  \details UGDatasetRasterOgdc关于影像数据集的接口定义。
//!  \Modified Date: 2013-4-7
//!  \Modified Author:Conversion-zby
//!  \Details Comments:调整UGC接口参数开放以及接口组成,主要目的是在UGCEngineOGDC接口中添加多波段栅格数据集的扩展支持;
//!  \Details Comments:本次调整主要包含两方面内容:(1) 对于原有接口增加波段索引参数支持;(2) 增加多波段栅格数据集特有接口
//!  \Details Comments:此次调整涉及整个栅格数据集结构的调整，由于技术人员水平所限以及时间的仓促，难免会产生这样那样的问题,有问题
//!  \Details Comments:请与Conversion-zby联系!
//!  \Version OGDC-1-1(2013-4-7)


#if !defined(AFX_UGDATASETRASTEROGDC_H__B310E3AF_CDAF_4FA8_9470_D1D414D5FBD5__INCLUDED_)
#define AFX_UGDATASETRASTEROGDC_H__B310E3AF_CDAF_4FA8_9470_D1D414D5FBD5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "OGDC/OgdcDatasetRaster.h"
#include "Engine/UGDatasetRaster.h"

namespace UGC {

class UGDataSourceOgdc;

//##ModelId=483BB70B0232
class ENGINEOGDC_API UGDatasetRasterOgdc : public OgdcDatasetRaster  
{
public:
	//##ModelId=483BB70B0243
	UGDatasetRasterOgdc();
	//##ModelId=483BB70B0244
	virtual ~UGDatasetRasterOgdc();

public:
	//! \brief 打开数据集。
	//! \return 是否成功打开数据集，成功返回TRUE，失败返回FALSE。
	//##ModelId=483BB70B0246
	virtual OgdcBool Open();	
	
	//! \brief 关闭数据集。
	//! \return 是否成功关闭数据集，成功返回TRUE，失败返回FALSE。
	//##ModelId=483BB70B0248
	virtual void Close();	

	//! \brief 判断数据集是否已经打开。
	//! \return 打开返回TRUE，否则返回FALSE。
	//##ModelId=483BB70B024A
	virtual OgdcBool IsOpen() const;
	
	//! \brief 重命名数据集。
	//! \param strNewName 新的数据集名[in]。
	//! \return 是否成功重命名数据集，成功返回TRUE，失败返回FALSE。
	//! \remarks 只改变数据集名,表名不变。
	//##ModelId=483BB70B0252
	virtual OgdcBool Rename(const OgdcString& strNewName);		

	//! \brief 判断当前数据集是否可编辑。
	//! \return 可编辑返回TRUE，不可返回FALSE。
	//##ModelId=483BB70B0255
	virtual OgdcBool CanUpdate();
	
	//! \brief 判断数据集是否是栅格数据集
	//! \return 数据集是栅格数据集返回TRUE，否则返回FALSE。
	//##ModelId=483BB70B0257
	virtual OgdcBool IsRaster();	
	
	//! \brief 将数据集各种信息保存到数据库中。
	//! \return 是否成功保存，成功返回TRUE，失败返回FALSE。
	//##ModelId=483BB70B0259
	virtual OgdcBool SaveInfo();	
	
	//! \brief 刷新数据集信息。
	//! \return 是否成功刷新，成功返回TRUE，失败返回FALSE。
	//! \remarks 从数据库中读取数据集的各种属性，刷新当前数据集的信息。
	//##ModelId=483BB70B0262
	virtual OgdcBool RefreshInfo();	

	//! \brief 返回数据源指针
	virtual OgdcDataSource* GetDataSource() const;
	
	//! \brief 设置数据源指针
	virtual void SetDataSource(UGDataSourceOgdc* pDataSource);

public:	
	//! \brief 返回数据集对应表名
	//##ModelId=483BB70B0264
	virtual OgdcString GetTableName();	
	
	//! \brief 获取最后更新数据集的时刻。
	//! \return 最后更新数据集的时刻。
	//##ModelId=483BB70B0266
	virtual OgdcTime GetDateLastUpdated();	
	
	//! \brief 获取创建数据集的时刻。
	//! \return 创建数据集的时刻。
	//##ModelId=483BB70B0268
	virtual OgdcTime GetDateCreated();	
	
	//! \brief 判断数据集是否在打开后有过修改。
	//! \return 有过修改返回TRUE，没有返回FALSE。
	//##ModelId=483BB70B0271
	virtual OgdcBool IsModified() const;
	
	//! \brief 设置数据集是否有过修改。
	//! \param bModified 数据集是否有过修改，默认有修改[in]。
	//##ModelId=483BB70B0273
	virtual void SetModifiedFlag(OgdcBool bModified = TRUE);
	
	//! \brief 设置数据集字符编码方式
	//! \param textCodec 数据集字符编码方式[in]。
	//##ModelId=483BB70B0276
	virtual void SetCharset(OgdcString::Charset nCharset);

	//! \brief 获取数据集字符编码方式。
	//! \return 数据集字符集枚举。
	//##ModelId=483BB70B0279
	virtual OgdcString::Charset GetCharset() const;

	//! \brief 设置投影坐标系。
	//! \param coordSys [in]。
	//##ModelId=483BB70B027B
	virtual OgdcBool SetCoordSys(const OgdcCoordSys& coordSys);	

	//! \brief 得到投影坐标系。
	//##ModelId=483BB70B0282
	virtual OgdcBool GetCoordSys(OgdcCoordSys& coordSys) const;	

public:
	//##ModelId=483BB70B0285
	virtual OgdcBool BuildPyramid();	

	//! \brief 移除影像金字塔。
	//! \param  [in]。
	//! \return 是否移除成功，是返回TRUE，否则返回FALSE。
	//! \remarks 
	//! \attention 
	//##ModelId=483BB70B0287
	virtual OgdcBool DropPyramid();	

	//##ModelId=483BB70B0289
	virtual OgdcBool IsBuildPyramid() const;
	
	//! \brief 获取影像数据集指定行列某一像素点的颜色值。
	//! \param nCol 像素点列号[in]。
	//! \param nRow 像素点行号[in]。
	//! \param nBandIndex[in] 波段索引值，默认为0
	//! \return 颜色值。
	//! \remarks 颜色值的数值因数据集的像素格式不同而不同。
	//! \attention 
	//##ModelId=483BB70B0296
	virtual OgdcColor GetPixel(OgdcInt nCol, OgdcInt nRow,UGint nBandIndex=0);	
	
	//! \brief  设置影像数据集指定行列某一像素点的颜色值。
	//! \param nCol 像素点列号[in]。
	//! \param nRow 像素点行号[in]。
	//! \param nColor 颜色值[in]。
	//! \param nBandIndex[in] 波段索引值，默认为0
	//! \remarks 要根据数据集的像素格式正确设置像素点的颜色值。
	//! \attention 
	//##ModelId=483BB70B029A
	virtual void SetPixel(OgdcInt nCol, OgdcInt nRow, OgdcColor nColor,UGint nBandIndex=0);	
	
	//! \brief 获取Grid数据集指定行列某一点的特性值。
	//! \param nCol 网格列号[in]。
	//! \param nRow 网格行号[in]。
	//! \param nBandIndex[in] 波段索引值，默认为0
	//! \return 特性值。
	//! \remarks 
	//! \attention 
	//##ModelId=483BB70B02A1
	virtual OgdcDouble GetValue(OgdcInt nCol, OgdcInt nRow,UGint nBandIndex=0);
	
	//! \brief 设置Grid数据集指定行列某一点的特性值。
	//! \param nCol 网格列号[in]。
	//! \param nRow 网格行号[in]。
	//! \param dValue 特性值[in]。
	//! \param nBandIndex[in] 波段索引值，默认为0
	//! \remarks 要根据数据集的白化值正确设置网格点的特性值。
	//! \attention 
	//##ModelId=483BB70B02A5
	virtual void SetValue(OgdcInt nCol, OgdcInt nRow, OgdcDouble dValue,UGint nBandIndex=0);

	//##ModelId=483BB70B02AA
	virtual OgdcRasterBlock* GetViewBlock(const OgdcRect2D& rcView, 
		OgdcInt nDeviceWidth, OgdcInt nDeviceHeight);

public:
	//! \brief 获取数据集类型。
	//! \remarks 
	//##ModelId=483BB70B02B1
	virtual OgdcInt GetType() const;

	//! \brief 获取数据集名。
	//! \return 数据集名字符串。
	//! \remarks 
	//! \attention 
	//##ModelId=483BB70B02B3
	virtual OgdcString GetName();

	//! \brief 获取数据集描述信息。
	//! \param nBandIndex[in] 波段索引值，默认为-1
	//! \return 数据集最描述信息字符串。
	//! \remarks 
	//! \attention 
	//##ModelId=483BB70B02B5
	virtual OgdcString GetDescription(OgdcInt nBandIndex=0) const;

	//! \brief 设置数据集描述信息。
	//! \param strtDescription 数据集描述信息字符串[in]。
	//! \remarks 
	//! \attention 
	//##ModelId=483BB70B02B7
	virtual void SetDescription(const OgdcString& strtDescription,OgdcInt nBandIndex =0);

	//! \brief 返回数据集的维数。
	//! \return 数据集的空间维数, 栅格为-1维。
	//! \attention 
	//##ModelId=483BB70B02BA
	virtual OgdcInt GetStyleDimension();		
	
	//! \brief 返回数据集的地理范围。
	//! \return 数据集地理范围矩形。
	//! \remarks 
	//! \attention 
	//##ModelId=483BB70B02BF
	virtual OgdcRect2D GetBounds();	
	
	//! \brief 设置数据集的地理范围。
	//! \param rcBunds 数据集地理范围矩形[in]。
	//! \remarks 
	//! \attention 
	//##ModelId=483BB70B02C1
	virtual void SetBounds(const OgdcRect2D& rcBounds);	

	//##ModelId=483BB70B02C4
	virtual OgdcInt GetBandCount() const;

	//##ModelId=483BB70B02CB
// 	virtual void SetBandCombineMode(const OgdcArray<OgdcInt>& aryBand, ImgColorSpace nColorSpace);
// 	//##ModelId=483BB70B02CF
// 	virtual OgdcBool GetBandCombineMode(OgdcArray<OgdcInt>& aryBand, ImgColorSpace& nColorSpace) const;
	
	//! \brief 获取栅格数据集宽度。
	//! \return 栅格数据集宽度，以象素值为单位。
	//! \remarks 
	//! \attention 
	//##ModelId=483BB70B02D3
	virtual OgdcInt GetWidth() const;	
	
	//! \brief 获取栅格数据集高度，以象素值为单位。
	//! \return 栅格数据集高度，以象素值为单位。
	//! \remarks 
	//! \attention 。
	//##ModelId=483BB70B02D5
	virtual OgdcInt GetHeight() const;	

	//! \brief 获取栅格数据集定义的无效值
	//! \param nBandIndex[in] 波段索引值，默认为-1
	//! \return 无效值。
	//! \remarks Grid数据集的白化值，也由此接口获取。
	//! \attention 。
	//##ModelId=483BB70B02D7
	virtual OgdcDouble GetNoValue(OgdcInt nBandIndex=0) const;	
	
	//! \brief 定义栅格数据集的无效值。
	//! \param nBandIndex[in] 波段索引值，默认为-1
	//! \param dbNoValue [in]。
	//! \remarks Grid数据集的白化值，也由此接口设置。
	//! \attention 。
	//##ModelId=483BB70B02D9
	virtual void SetNoValue(OgdcDouble dbNoValue,OgdcInt nBandIndex=0);
	
	//! \brief 获取影像的象素格式。
	//! \param nBandIndex[in] 波段索引值，默认为-1
	//! \return 像素格式枚举值。
	//! \remarks 
	//! \attention 
	//##ModelId=483BB70B02DC
    virtual PixelFormat GetPixelFormat(OgdcInt nBandIndex =0) const;	

	//! \brief 读入指定块数据。
	//! \param nRowBlock 影像块行号[in]。
	//! \param nColBlock 影像块列号[in]。
	//! \param nBandIndex[in] 波段索引值，默认为0
	//! \return 影像块指针。
	//! \remarks 
	//! \attention 
	//##ModelId=483BB70B028B
	virtual OgdcRasterBlock* LoadBlock(OgdcInt nRowBlock, OgdcInt nColBlock,OgdcInt nBandIndex=0);	
    
	//! \brief 将一内存中的影像块存入磁盘。
	//! \param pImgBlock 影像块指针[in]。
	//! \param nBandIndex[in] 波段索引值，默认为0
	//! \return 是否成功保存，成功返回TRUE，失败返回FALSE。
	//! \remarks 
	//! \attention 
	//##ModelId=483BB70B0293
	virtual OgdcBool SaveBlock(OgdcRasterBlock* pImgBlock,OgdcInt nBandIndex=0);	
	
	//! \param nBandIndex[in] 波段索引值，默认为-1
	virtual void ReleaseAllBlocks(OgdcInt nBandIndex=-1);

	
	//##ModelId=483BB70B02DF
	UGDatasetRaster* GetDatasetRaster() const;	
	
	//##ModelId=483BB70B02E1
	void SetDatasetRaster(UGDatasetRaster* pDatasetRaster);
    
	//是否是多波段数据集
	virtual OgdcBool IsMBRaster();

protected:	
	//##ModelId=483BB70B02E3
	UGDatasetRaster* m_pDatasetRaster;
	UGDataSourceOgdc* m_pDsOgdc;
};

}

#endif // !defined(AFX_UGDATASETRASTEROGDC_H__B310E3AF_CDAF_4FA8_9470_D1D414D5FBD5__INCLUDED_)

