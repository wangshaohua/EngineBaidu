//////////////////////////////////////////////////////////////////////////
//                    _   _   ____   ____                    
//   Project         | | | | / ___) / ___)                   
//                   | | | || | __ | |                       
//                   | |_| || |_\ || \___                    
//                    \____/ \____| \ ___)     6.0           
//                                                           
//!  \file headerfile.h
//!  \brief Class 。
//!  \details 。
//!  \author linwenyu。
//!  \attention 
//!   Copyright (c) 1996-2010 SuperMap Software Limited Company.  <br> 
//!   All Rights Reserved.
//!  \version 6.0
//////////////////////////////////////////////////////////////////////////


#if !defined(AFX_UGFILEPARSE_H__F2ACB033_F582_4263_B9E9_DCA2E56F87DE__INCLUDED_)
#define AFX_UGFILEPARSE_H__F2ACB033_F582_4263_B9E9_DCA2E56F87DE__INCLUDED_

#include "FileParser/UGFileParserConfigParams.h"
#include "FileParser/UGExchangeFileType.h"

namespace UGC 
{

//! \brief 文件层基类。
//! \remarks 所有有关文件的层都要继承此类。
class FILEPARSER_API UGFileLayer
{
public:
	enum FILELAYER_TYPE
	{
		FL_VECTOR,//矢量的Layer
		FL_RASTER,//栅格的Layer
		FL_CONFIG,//配置文件Layer
		FL_OTHER,//其他的Layer
	};
public:
	virtual FILELAYER_TYPE GetType() = 0;
};

//! \brief 文件解析基类。
//! \remarks 所有有关文件分析的都要继承此类。
class FILEPARSER_API UGFileParser  
{
public:

	//! \brief 构造函数。
	UGFileParser();

	//! \brief 析构函数。
	virtual ~UGFileParser();
	
public:
	//! \brief 打开文件。
	//! \param impParams [in]。
	//! \return 成功返回TRUE，失败返回FALSE。
	//! \attention 读取文件前调用。
	virtual UGbool Open(const UGImportParams& impParams) = 0;
	
	//! \brief 关闭文件	
	virtual void Close() = 0;

	//! \brief 根据文件格式常量判断这种格式属于哪一个组。
	virtual UGFileType::EmGroup GetFileGroup() const = 0; 		

	//! \brief 按FMEWorkBench的方式导入
	//! \param 注意此接口有且仅供FMEWorkBench的导入方式使用  请勿随便使用 
	virtual UGint ImportByFMEWorkBench(const UGImportParams& impParams, UGString& resultFilePath){return -1;}
public:	
	//! \brief 获取源数据的空间坐标系。
//	virtual const UGPrjCoordSys* GetSpatialRef();	

	//! \brief 获取源数据中的数据集数目。
	//! \param  [in]。
	virtual UGint GetLayerCount();

	//! \brief 通过索引得到源数据中的一个数据集。
	//! \param nlayer [in]。
	virtual UGFileLayer* GetLayer(UGint nlayer);	
	
public:
	//! \brief 文件是否打开。
	//! \param  [in]。
	UGbool IsOpen() const;	
	
	//! \brief 是否是矢量类型。
	UGbool IsVector() const; 	
	
	//! \brief 是否是栅格类型。
	UGbool IsRaster() const; 
	
	//! \brief 是否是工作空间类型。
	UGbool IsWorkspace() const; 	
	
protected:
	
	//! \brief 文件打开标志。
	UGbool m_bOpen;

};

} //namespace UGC

#endif // !defined(AFX_UGFILEPARSE_H__F2ACB033_F582_4263_B9E9_DCA2E56F87DE__INCLUDED_)

