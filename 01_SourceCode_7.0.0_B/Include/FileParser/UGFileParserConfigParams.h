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


#if !defined(AFX_UGFILEPARSERCONFIGPARAMS_H__08BADC84_B1E9_40CA_B1AE_A7755CC63F16__INCLUDED_)
#define AFX_UGFILEPARSERCONFIGPARAMS_H__08BADC84_B1E9_40CA_B1AE_A7755CC63F16__INCLUDED_

#include "Projection/UGPrjCoordSys.h"
#include "Element/OgdcFieldInfo.h"
#include "Geometry/UGDataCodec.h"
#include "Geometry/UGFeature.h"

namespace UGC {

//! \brief 转换参数基类。
class FILEPARSER_API UGExchangeParams  
{
	friend class UGExchangeParamsManager;
	friend class UGFileParseToolkit;

public:
	
	//! \brief 构造函数。
	UGExchangeParams();
	
	//! \brief 析构函数。
	virtual ~UGExchangeParams();

public:
	
	//! \brief 设置数据文件名	
	//! \param strFilePathName  文件全路径名[in]
	void SetFilePathName(const UGString& strFilePathName);	
	
	//! \brief 得到数据文件名 	
	//! \param  [in]。
	//! \return 文件全路径。
	UGString GetFilePathName() const;

	//! \brief 得到是否使用的是FME导入模式。
	//! \param  [out]。
	//! \return 是否。
    UGbool GetIsUseFME() const;

	//! \brief 设置是否使用的是FME导入模式。
	//! \param  [in]。
	//! \return 是否。
	void SetIsUseFME(UGbool bIsUserFME = FALSE);
	
	//! \brief 得到文件类型。
	//! \param  [in]。
	//! \return 文件类型。
	//! \remarks 各个子类自己实现。
	virtual inline UGint GetFileType() const {return 0;}

public:

	//! \brief 设置是否显示进度。
	//! \param TRUE  显示进度。[in]
	void SetShowProgress(UGbool bProgress = TRUE);	

	//! \brief 得到是否显示进度。
	UGbool GetShowProgress() const;	

	//! \brief 设置是否强制覆盖。
	void SetOverWrite(UGbool bOverwrite= TRUE);

	//! \brief 得到是否强制覆盖。
	UGbool GetOverWrite() const;

	////! \brief 设置回调进度信息
	//void SetProgressProcFun(void* ProgressProcFun){m_pProgressProcFun=ProgressProcFun;};

	//void* GetProgressProcFun() const{return m_pProgressProcFun;};
	
	//! \brief 判断当前使用的转换参数是否是导入参数。
	//! \param  [in]。
	//! \return 。
	//! \remarks 主要用于转换参数合法性检查，与GetFileType结合使用，可以判断出当前使用
	//!          的参数是否是指定文件类型的导入参数。
	//! \attention 。
	virtual inline UGbool IsImportParams() const {return FALSE;};
	
	//! \brief 判断当前使用的转换参数是否是导出参数。
	//! \param  [in]。
	//! \return 。
	//! \remarks 主要用于转换参数合法性检查，与GetFileType结合使用，可以判断出当前使用
	//!          的参数是否是指定文件类型的导出参数。
	//! \attention 。
	virtual inline UGbool IsExportParams()  const {return FALSE;};

	UGString::Charset GetImportOrExportCharset() const;
	//! \brief 设置导入导出编码，某些文件类型是不允许修改的，依据文件类型而定。
	virtual UGbool SetImportOrExportCharset(UGString::Charset Charset);
	
protected:

	
	enum ExchangeOptions
	{	
		//! \brief 显示进度
		ShowProgress			= 0x00000001,	
		//! \brief 忽略属性；矢量数据属性信息，栅格数据的属性表
		IgnoreAttribute			= 0x00000002,				
		//! \brief 忽略坐标系统		
		IgnoreCoordSys			= 0x00000004,		
		//! \brief 忽略空数据；没有空间数据的要素，如mif格式		
		IgnoreEmptySpatialData = 0x00000008,
		//! \brief 建空间索引		
		BuildSpatialIndex		= 0x00000010,		
		//! \brief 忽略CAD数据中的“块”，DGN数据中的“单元”
		IgnoreSymbol			= 0x00000020,			
		//! \brief 忽略风格
		IgnoreStyle				= 0x00000040,			
		//! \brief 导入为多波段
		ImportAsMultiBands		= 0x00000080,	
		//! \brief 自动建立影像金字塔	
		AutoBuildPyramid		= 0x00000100,		
		//!	\brief 是否从外部文件获取投影
		SpatialRefFromFile		= 0x00000200,	
		//! \brief 忽略拓扑
		IgnoreTopo				= 0x00000400,
		//! \brief 是否按照单波段读取数据
		ReadAsOneBand			= 0x00000800,
		//! \brief 是否开启强制位深转换功能
		ForcePixelEnable		= 0x00001000,
	};

	//! \brief 导入导出字符集，
	//         如果导入文件，默认和m_FileCharset保持一致，外部用户可以设置。
	//		   如果导出文件，编码可能是当前系统编码或者文件的编码，依据当前文件的格式，某些文件类型，可能无法修改。			
	UGString::Charset m_ImportOrExportCharset;	


	//! \brief 记录文件路径有没有变更,这个参数为数据导入的时候，读取文件参数用的。
	//         通过这个参数，在文件获取编码的时候就不用重复打开文件。
	UGbool m_bFileChange;	
	
	//! \brief 文件路径
	UGString m_strFilePathName;

	
	//! \brief 转换中的选项。
	//! \remarks 只能是ExchangeOptions中的选项 。
	UGuint m_nOption;

	//! \brief 覆盖已有数据
	//! \remarks
	UGbool m_bOverWrite;

	//! \brief 是否使用FME的方式导入
	UGbool m_bIsUseFME;

	//void* m_pProgressProcFun;

};



//////////////////////////////////////////////////////////////////////////
// import
//////////////////////////////////////////////////////////////////////////

//! \brief 导入参数。
class FILEPARSER_API UGImportParams : public UGExchangeParams
{
	friend class UGExchangeParamsManager;

public:
	
	//! \brief 构造函数。
	UGImportParams();
	
	//! \brief 析构函数。
	virtual ~UGImportParams();

	//! \brief 重载赋值=。
	UGImportParams& operator=(const UGImportParams& imp);	

public:
	
	// \brief 导入模式。
	enum ImportMode
	{
		ModeGIS		= 0,// 导入为简单数据集
		ModeCAD		= 1,// 导入为复合数据集
		ModeIMG		= 2,// 导入为IMG数据集
		ModeGrid	= 3,// 导入为Grid数据集
		ModeDEM		= 4,// 导入为Dem数据集		
	};

	//! \brief 设置导入模式。
	//! \param impMode 导入模式。[in]
	void SetImportMode(UGint nimpMode);	

	//! \brief 得到导入模式。
	//! \param  [in]。
	//! \return 导入模式。
	UGint GetImportMode() const;

	//! \brief 获取是否采用用户设置参数导入
	UGbool GetIsUserSetting(){return m_bUserSetting;}
	
	//! \brief 设置追加导入
	//! \param bAppend 是否追加导入[in]
	//! \attention 设置了这个参数后将忽略是否覆盖数据集的参数设置
	void SetAppend(UGbool append = TRUE);

	//! \brief 得到是否追加导入
	UGbool GetAppend() const;

	//! \brief 设置是否忽略属性。
	//! \param FALSE  是否忽略属性。[in]
	//! \remarks 包括矢量属性属性信息，栅格数据栅格属性表。
	void SetIgnoreAttribute(UGbool bIgonreAttribue = FALSE);

	//! \brief 得到是否忽略属性。
	//! \param   是否忽略属性。[in]
	//! \return 是否忽略属性。
	UGbool GetIgnoreAttribute() const;	


	//! \brief 设置是否忽略坐标系统。
	//! \param TRUE 是否忽略坐标系统。[in]
	void SetIgnoreCoordSys(UGbool bIgnoreCoordSys = FALSE);	

	//! \brief 得到是否忽略坐标系统。
	//! \param  [in]。
	//! \return 是否忽略坐标系统。
	UGbool GetIgnoreCoordSys() const;	

	//! \brief 导入后，设置目标数据集的坐标系统。	
	//! \param spatialRef [in]。
	//! \remarks 我们认为参数中传入的投影是数据的真实投影，
	//!          不负责检查投影是否一致，不做投影转换，仅设置投影而已
	void SetDestCoordSys(const UGPrjCoordSys& spatialRef);	

	//! \brief 获得坐标系统
	//! \param  [in]。
	//! \return 得到坐标系统成功，返回TRUE。
	UGPrjCoordSys* GetDestCoordSys() const;
	
	//! \brief 设置数据编码方式
	//! \param encType 编码方式。 [in]
	void SetDatasetEncType(UGDataCodec::CodecType encType);	

	//! \brief 得到数据编码方式。
	//! \param  [in] 。
	//! \return 数据编码方式。
	UGDataCodec::CodecType GetDatasetEncType() const;

	//! \brief 设置目标数据集名称
	//! \param strDTName 目标数据集名称[in]
	void SetDestDTName(const UGString& strDTName);

	//! \brief 获取目标数据集名称
	//! \return 目标数据集名称
	UGString GetDestDTName() const;

	//! \brief 判断导入以全图或者多层导入。
	//! \param  [in]。
	//! \return 。
	//! \remarks 。
	//! \attention 。
	virtual UGbool GetImportByLayer() const{return FALSE;}

	//! \brief 获取导入文件编码,如果文件重新设置，这个要重新获取，同时GetImportOrExportCharset
	//         有可能变更。
	// 如果格式没有规定使用特定的编码，那么就采用用户设置的编码
	virtual UGString::Charset GetFileCharset();

protected:
	
	
	//! \brief 判断当前使用的转换参数是否是导入参数。
	//! \remarks 主要用于转换参数合法性检查，与GetFileType结合使用，可以判断出当前使用
	//!          的参数是否是指定文件类型的导入参数。
	virtual inline UGbool IsImportParams() const {return TRUE;};
	
	//! \brief 判断当前使用的转换参数是否是导出参数。
	//! \remarks 主要用于转换参数合法性检查，与GetFileType结合使用，可以判断出当前使用
	//!          的参数是否是指定文件类型的导出参数。
	virtual inline UGbool IsExportParams()  const {return FALSE;};


protected:

	//! \brief 导入模式。
	ImportMode m_ImportMode;
	
	//! \brief 是否为追加导入
	UGbool m_bAppend;
	
	//! \brief 结果数据集编码方式
	UGDataCodec::CodecType m_encType;

	//! \brief 目标坐标系统。
	UGPrjCoordSys* m_pSpatialRef;	

	//! \brief 是否采用用户设置，默认为False，此时全部按默认导入
	//         当用户调用SetImportDatasetInfos时，采用用户设置
	UGbool m_bUserSetting;

	//! \brief 目标数据集名称
	UGString m_strDTName;
	//! \brief 针对导入文件的编码，这个方法是自动检测文件编码之后，存储文件的编码。
	UGString::Charset m_FileCharset;
private:


};


//////////////////////////////////////////////////////////////////////////


//! \brief 导出参数。
class FILEPARSER_API UGExportParams : public UGExchangeParams
{
	friend class UGExchangeParamsManager;

public:

	//! \brief 构造函数。
	UGExportParams();

	//! \brief 析构函数。
	virtual ~UGExportParams();
	
	//! \brief 重载赋值=。
	//! \param imp [in]。
	UGExportParams& operator=(const UGExportParams& exp);	


	
protected:	
	
	//! \brief 判断当前使用的转换参数是否是导入参数。
	//! \remarks 主要用于转换参数合法性检查，与GetFileType结合使用，可以判断出当前使用
	//!          的参数是否是指定文件类型的导入参数。
	virtual inline UGbool IsImportParams() const {return FALSE;}
	
	//! \brief 判断当前使用的转换参数是否是导出参数。
	//! \remarks 主要用于转换参数合法性检查，与GetFileType结合使用，可以判断出当前使用
	//!          的参数是否是指定文件类型的导出参数。
	virtual inline UGbool IsExportParams()  const {return TRUE;}
	
};

} //namespace UGC
#endif // !defined(AFX_UGFILEPARSERCONFIGPARAMS_H__08BADC84_B1E9_40CA_B1AE_A7755CC63F16__INCLUDED_)

