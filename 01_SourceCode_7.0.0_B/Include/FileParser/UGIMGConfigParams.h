// UGIMGConfigParams.h: interface for the UGErdasImagineImportParams class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_UGIMGCONFIGPARAMS_H__3739E9A2_4CD0_41C3_BED7_B7EF1138433F__INCLUDED_)
#define AFX_UGIMGCONFIGPARAMS_H__3739E9A2_4CD0_41C3_BED7_B7EF1138433F__INCLUDED_

#include "FileParser/UGRasterConfigParams.h"
#include "FileParser/UGExchangeFileType.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

namespace UGC {

//! \brief ErdasImage的导入参数设置。
class FILEPARSER_API UGErdasImagineImportParams  : public UGRasterImportParams
{
public:

	//! \brief 构造函数。
	UGErdasImagineImportParams();

	//! \brief 析构函数。
	virtual ~UGErdasImagineImportParams();

public:
	
	//! \brief 得到文件类型。
	//! \return 文件类型。
	virtual inline UGint GetFileType() const { return UGFileType::IMG; }
	
	

};

//! \brief ErdasImage的导出参数设置。
class FILEPARSER_API UGErdasImagineExportParams  : public UGRasterExportParams
{
public:
	
	//! \brief 构造函数。
	UGErdasImagineExportParams();

	//! \brief 析构函数。
	virtual ~UGErdasImagineExportParams();
	
	//! \brief 得到文件类型。
	//! \return 文件类型。
	virtual inline UGint GetFileType() const { return UGFileType::IMG; }

	//! \brief 设置是否创建超过2G的IMG数据。
	//! \remarks 导出数据时，当数据量超过2G时，需要设置此接口，才能导出超过2G的IMG。
	void SetCreateLargeImage(UGbool bCreateLarge = FALSE);	

	//! \brief 得到是否创建超过2G的IMG数据。
	UGbool GetCreateLargeImage() const;	

protected:
	
	UGbool m_bCreateLarge;

};


typedef UGErdasImagineImportParams UGIMGImportParams;
typedef UGErdasImagineExportParams UGIMGExportParams;


} //namespace UGC
#endif // !defined(AFX_UGIMGCONFIGPARAMS_H__3739E9A2_4CD0_41C3_BED7_B7EF1138433F__INCLUDED_)

