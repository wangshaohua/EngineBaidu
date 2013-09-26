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
//!  \author  格式转换组。
//!  \attention 
//!   Copyright (c) 1996-2008 SuperMap Software Limited Company.  <br> 
//!   All Rights Reserved.
//!  \version 6.0
//////////////////////////////////////////////////////////////////////////
#if !defined(AFX_UGFileParseVector_H__9D5BD937_D091_4D5F_957C_94B8A7A74D92__INCLUDED_)
#define AFX_UGFileParseVector_H__9D5BD937_D091_4D5F_957C_94B8A7A74D92__INCLUDED_

#include "Geometry/UGFeature.h"
#include "UGFileParse.h"
#include "FileParser/UGVectorConfigParams.h"

#include "UGS57SpatialRelationship.h"

namespace UGC {

//! \brief 源数据中的一个要素层。	
class FILEPARSER_API UGVectorFileLayer: public UGFileLayer
{

public:

	//! \brief 构造函数。
	UGVectorFileLayer();
	//! \brief 析构函数。
	virtual ~UGVectorFileLayer();

public:
	//识别类型
	virtual FILELAYER_TYPE GetType(){return UGFileLayer::FL_VECTOR;}

public:

	//////////////////////////////////////////////////////////////////////////
	// 读
	//////////////////////////////////////////////////////////////////////////
	
	//! \brief 重新开始读文件。
	virtual void ResetReading() = 0;

	//	这个函数性能差,后面要废掉,用下面的实现代替
	//! \brief 取对象。
	//! \param arrFeature [in]获取的Geometry对象数组。
	//! \param nCount [in]每次获取Geometry的个数。
	//! \return 成功返回获取对象个数。
	//! \remask 用户分配arrFeature数组空间,并负责释放
	virtual UGint ReadFeatures(UGArray<UGFeature*>& arrFeature, UGint nCount = 1) {return -1;}

	//////////////////////////////////////////////////////////////////////////
	//  [3/4/2011 林文玉] 重大调整,feature结构性能堪忧,特提供此函数
	//! \brief 读取1个对象。
	//! \param oneFeature [in]获取的feature对象。
	//! \return 成功返回1。
	virtual UGint ReadOneFeature(UGFeature*& pFeature) {return -1;}

	
	//! \brief 获取layer中对象个数
	//! \return 返回layer中对象个数, 获取失败返回 -1 
	//! \remarks Returns the number of features in the layer
	UGint GetFeatureCount() const {return m_FcDefn.GetFeatureCount();}	
	

	//! \brief 获取文件当前记录编号。
	UGint GetFeatureReaded(){ return m_nReadWrited; }

	//! \brief 获取源数据的空间坐标系。
	virtual UGPrjCoordSys* GetSpatialRef() const { return m_FcDefn.m_pSpatialRef;}

	//////////////////////////////////////////////////////////////////////////
	// 写
	//////////////////////////////////////////////////////////////////////////

	
	//! \brief 创建layer的字段结构。
	virtual UGint CreateFields(UGFieldInfos& fields) {return 0;}

		

	//! \brief 向layer中创建并写一个新的对象。
	//! \return 返回成功写入layer的对象个数。
	virtual UGint CreateFeature(const UGArray<UGFeature*>& arrFeature){ return 0;}

	//virtual UGint CreateFeature(const UGArray<UGFeature*>& arrFeature){return 0;}	

	//! \brief 获取layer中的基本信息。
	UGFeatureClassDefn * GetLayerDefn(){ return &m_FcDefn;}
	
	//! \brief 判断是否有相同的要素。
	UGbool HasSameLayer(UGVectorFileLayer* pFileLayer);	

	void SetLayerDefn(const UGFeatureClassDefn* pClssDefn);

	//! \brief 设置数据投影,仅在导出时调用
	void SetSpatialRef(const UGPrjCoordSys& srs);

	void SetImportOrExportCharset(UGString::Charset);

	UGString::Charset GetImportOrExportCharset();

	virtual UGulong GetCurFilePosition()const {return 0;}
	virtual UGulong GetFileLength()const {return 0;}

	//! \brief 设置是否导入会使用一行一行的文本读取方式导入。
	//! \param bImportUseReadLine [in]。
	//! \return 。
	//! \remarks 。
	//! \attention 。
	/* 方法说明：
	矢量格式在文件打开的时候需要确定Feature对象个数
	而CSV和Lidar的ASCII文件无头信息,使用ReadLine确认Feature总数会很耗时
	故提供变量做控制,在文件打开的时候不需要确认Feature的个数
	导入时使用DataImport.importByBatch2()方法进行导入工作。
	省时啊！！！
	*/
	void SetImportUseReadLine(const UGbool bImportUseReadLine = TRUE);	

	//! \brief 获取是否导入会使用一行一行的文本读取方式导入。
	//! \param  [out]。
	//! \return 。
	//! \remarks 。
	//! \attention 。
	UGbool GetIsImportUseReadLine() const;

protected:

	//! \brief 创建输出文件且写基本信息。
	//! 返回0为失败，返回1为成功！！！
	virtual UGint Create() { return 0;}	

	//! \brief 获取layer的基本信息。
	virtual UGFeatureClassDefn* ReadLayerDefn(const UGImportParams& importParams){return 0;};

	//! \brief 设置为用户修改后的数据集名称。
	void SetLayerName(const UGString& strName);

	//! \brief 设置数据集范围。
	//! \param  rect2D 地理方位[in]。
	void SetBound(UGRect2D& rect2D);	
	
	//! \brief 设置数据集类型。
	//! \param  字段类型[in]。
	void SetType(UGint nType);	

	//! \brief 设置对象个数。
	//! \param  nCount字段个数[in]。
	void SetFeatureCount(UGint nCount);	

	//! \brief 保存layer的原始字段信息。
	//! \param  FieldInfos[in]。

	//! \return 。
	//! \remarks 。
	//! \attention 
//	void SetFieldInfosOrginal(UGFieldInfos& FieldInfos);

	
	//! \brief 保存layer的原始字段信息。
	//! \param  FieldInfos[in]。
	void SetxDataFieldInfosOrginal(UGFieldInfos& FieldInfos);


protected:

// 	UGFieldInfos& GetFieldInfosOrginal()
// 	{
// 		return m_FcDefn.m_FieldInfosOriginal;
// 	}
	const UGStrArray GetSourceFieldName() const;

	const UGDict<UGString, UGFieldInfo*>& GetFiledInfos() const;

protected:

	UGFeatureClassDefn m_FcDefn;
	// 文件编码，导入的时候为，源文件的编码，导出为目标文件编码
	UGString::Charset m_eImportOrExportCharset;

//	//! \brief 对象个数。
//	//! \remarks 。
//	UGint m_nfeatureCount;
	
	//! \brief 标记当前已读写对象数目。
	UGint m_nReadWrited;

// 	//! \brief S57数据集的扩展信息，存储了物标的OBJL值，关联的属性表名称
// 	UGString m_strS57DatasetExtInfo;

	//! \brief 在导入时是否是按一行一行的读取的
	//! \remarks 目前作用于CSV和Lidar的ASCII文件方式导入
	/* 添加此变量的说明：
	矢量格式在文件打开的时候需要确定Feature对象个数
	而CSV和Lidar的ASCII文件进行ReadLine的方法会很耗时
	故提供变量做控制,在文件打开的时候不需要确认Feature的个数
	导入时使用DataImport.importByBatch2()方法进行导入工作。
	省时啊！！！
	*/
	UGbool m_bImportUseReadLine;


};

typedef UGArray<UGVectorFileLayer*> UGArrVectFileLayer;

//! \brief 矢量文件解析基类。
class FILEPARSER_API UGFileParseVector : public UGFileParser  
{
public:

	//! \brief 构造函数。
	UGFileParseVector();
	
	//! \brief 析构函数。
	virtual ~UGFileParseVector();	

public:
	
	virtual UGFileType::EmGroup GetFileGroup() const;
	//////////////////////////////////////////////////////////////////////////
	// 读
	//////////////////////////////////////////////////////////////////////////
	
	//! \brief 获取源数据中的数据集数目。
	virtual UGint GetLayerCount(){ return m_ArrVectFileLayer.GetSize(); }

	//! \brief 通过索引得到源数据中的一个数据集。
	virtual UGFileLayer* GetLayer(UGint nlayer);	

	//! \brief 通过名称得到源数据中的一个数据集。。
	virtual UGVectorFileLayer* GetLayerByName(const UGString& strLayer);

	//! \brief 返回源数据中的数据集信息。
	UGFeatureClassDefn* GetFetureClassDefn(UGint index) const;// {return m_ArrVectFileLayer;}	

	//  [10/13/2009 林文玉] 此接口即将废弃。请通过layer获取投影
	//! \brief 获取源数据的空间坐标系。
	//! \param  [in]。
	//! \return 。
	//! \remarks 。
	//! \attention 。
//	virtual const UGPrjCoordSys*  GetSpatialRef () {return NULL;}

	//////////////////////////////////////////////////////////////////////////
	// 写
	//////////////////////////////////////////////////////////////////////////


	//! \brief 创建矢量文件。
	//! \param fcDefn [in]。
	virtual UGint Create(const UGVectorExportParams* exprams, const UGPrjCoordSys* spatialRef=NULL) {return 0;}

	//! \brief 导出时创建一个要素层。
	//! \param fcDefn [in]。
	virtual UGVectorFileLayer* CreateLayer(const UGFeatureClassDefn* pfcDefn){return NULL;}	

	virtual UGVectorFileLayer* CreateLayer(const UGFeatureClassDefn* pfcDefn, UGString::Charset){return NULL;}	

	//! \brief 准备开始写数据,在layer写数据之前必须调用
	//! \return 是否成功 ,1代表成功，-1代表不成功
	virtual UGint BeginWrite(){ return 1;}

	//! \brief 结束写数据,在layer写完数据之后必须调用
	//! \return 是否成功 ,1代表成功，-1代表不成功
	virtual UGint EndWrite(){return 1;}

	//! \brief 供S57导入使用，设置DSNM_CODE值
	// virtual void SetDSNMCode(const UGushort nDSNMCode){return;}

	//! \brief 设置关联关系数组，供S57使用
	virtual void SetRSDict(UGDict<UGString,UGS57RSS>& dictRs) {return;}

	//! \brief 设置面线和线线的拓扑关系数组，供S57使用
	virtual void SetFVEDict(UGDict<UGuint, UGS57FSPTS>& dictFspt) {return;}

	//! \brief 设置点物标和点控件对象的拓扑关系数组，供S57使用
	virtual void SetFVPDict(UGDict<UGuint, UGS57FSPTS>& dictFspt) {return;}

	//! \brief 设置水深数据集的名称，供S57使用
	//virtual void SetSoundgLayerName(const UGString& strLayerName) {return; }

	//! \brief 设置S57属性的字符集等级， 供S57使用
	//! \param  [in]。
	//! \return 。
	//! \remarks 。
	//! \attention 。
	virtual void SetAALL(UGint nAALL) { return; }

	//! \brief 设置S57国家语言属性的字符集等级， 供S57使用
	//! \param  [in]。
	//! \return 。
	//! \remarks 。
	//! \attention 。
	virtual void SetNALL(UGint nNALL) { return; }

	virtual UGString GetDatasetGroupExtData()const {return _U("");}

protected:
	//! \brief 添加要素类描述。
	//! \param pClassDefn [in]。
	UGbool AddVectorFileLayer(UGVectorFileLayer* pFileLayer);	
protected:

	//! \brief 此格式中的数据集信息。
	//! \remarks 。
	//UGFeatureClassInfos m_ArrFcInfos;
	UGArrVectFileLayer m_ArrVectFileLayer;
};

} //namespace UGC

#endif // !defined(AFX_UGFileParseVector_H__9D5BD937_D091_4D5F_957C_94B8A7A74D92__INCLUDED_)

