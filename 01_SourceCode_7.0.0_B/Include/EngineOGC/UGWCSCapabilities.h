//////////////////////////////////////////////////////////////////////////
//                    _   _   ____   ____                    
//   Project         | | | | / ___) / ___)                   
//                   | | | || | __ | |                       
//                   | |_| || |_\ || \___                    
//                    \____/ \____| \ ___)     6.0           
//                                                           
//!  \file WCSCapabilities.h
//!  \brief WCS网络服务能力的接口定义。
//!  \details 文件详细信息。
//!  \author duxiaomin。
//!  \attention 
//!   Copyright (c) 1996-2008 SuperMap Software Limited Company.  <br> 
//!   All Rights Reserved.
//!  \version 6.0
//////////////////////////////////////////////////////////////////////////

#ifndef WCSCAPABILITIES_H
#define WCSCAPABILITIES_H

#include "Stream/ugexports.h"
#include "EngineOGC/UGOGCCapabilities.h"

namespace UGC
{

class WCSCapabilities : public OGCCapabilities  
{
public:
	//! \brief  默认的构造函数
	WCSCapabilities();
	//! \brief  默认的析构函数
	virtual ~WCSCapabilities();
	
public:
	//! \brief 从GetCapbilities文件序列化得到OGC Web服务的能力。
	//! \param strXMLFile GetCapbilities请求得到的XML文件路径[in]。
	//! \return 是否成功序列化，成功返回TRUE，失败返回FALSE。
	//! \remarks 。
	//! \attention 。
	virtual UGbool Serialize(UGString strXMLFile);	
	
	//! \brief 从GetCapbilities文件打开的Makup Dom 树序列化得到OGC Web服务的能力。
	//! \param PDomTree Dom树的指针[in]。
	//! \return 是否成功序列化，成功返回TRUE，失败返回FALSE。
	//! \remarks 当XML 文件已经打开则不要再打开一次直接用Dom树即可。
	virtual UGbool Serialize(UGMarkup* PDomTree);

	//! \brief 将服务器能力序列化好的对象同步到网络数据源。
	//! \param pDataSource 网络数据源指针[in]。
	//! \return 是否同步成功。
	virtual UGbool SyncToDataSource(UGDataSourceOGC* pDataSource);

	//! \brief 截取字符串指定的字符存到数组中。
	//! \param strSrc 原字符串。[in]
	//! \param arrStrDst 存放截取后的字符串的数组。[in]
	//! \param strseparator 截取的原则。[in]
	void Split(UGString strSrc, UGArray<UGString>& arrStrDst, UGString strseparator);	
private:	
	//! \brief 加载关键字字典
	void LoadDict();

public:
	//! \brief 存放WCS请求的成员属性
 	WCSRequest m_OLRequest;	
	//! \brief 存放图层的数组 
 	UGArray<WCSCoverage*> m_arrCoverage;
};
///////////////////////// WCS 1.0.0 ///////////////////////////////////////
class WCSCapabilities100 : public WCSCapabilities
{
public:	
	//! \brief  默认的构造函数
	WCSCapabilities100();
	//! \brief  默认的析构函数
	virtual ~WCSCapabilities100();
public:
	//! \brief 从GetCapbilities文件序列化得到OGC Web服务的能力。
	//! \param strXMLFile GetCapbilities请求得到的XML文件路径[in]。
	//! \return 是否成功序列化，成功返回TRUE，失败返回FALSE。
	virtual UGbool Serialize(UGString strXMLFile);	
	
	//! \brief 从GetCapbilities文件打开的Makup Dom 树序列化得到OGC Web服务的能力。
	//! \param PDomTree Dom树的指针[in]。
	//! \return 是否成功序列化，成功返回TRUE，失败返回FALSE。
	//! \remarks 当XML 文件已经打开则不要再打开一次直接用Dom树即可。
	virtual UGbool Serialize(UGMarkup* PDomTree);
private:
	
	//! \brief 解析markup，获取服务器信息。
	UGbool ParseOnlineResource(UGMarkup* PDomTree, UGString strNS);

};	

///////////////////////// WCS 1.1.0 ///////////////////////////////////////
class WCSCapabilities110 : public WCSCapabilities
{
public:	
	//! \brief  默认的构造函数
	WCSCapabilities110();
	//! \brief  默认的析构函数
	virtual ~WCSCapabilities110();
public:
	//! \brief 从GetCapbilities文件序列化得到OGC Web服务的能力。
	//! \param strXMLFile GetCapbilities请求得到的XML文件路径[in]。
	//! \return 是否成功序列化，成功返回TRUE，失败返回FALSE。
	//! \remarks 。
	//! \attention 。
	virtual UGbool Serialize(UGString strXMLFile);	
	
	//! \brief 从GetCapbilities文件打开的Makup Dom 树序列化得到OGC Web服务的能力。
	//! \param PDomTree Dom树的指针[in]。
	//! \return 是否成功序列化，成功返回TRUE，失败返回FALSE。
	//! \remarks 当XML 文件已经打开则不要再打开一次直接用Dom树即可。
	//! \attention 。
	virtual UGbool Serialize(UGMarkup* PDomTree);
private:
	//! \brief 解析markup，获取服务器信息。
	//! \remarks 。
	//! \attention 。
	UGbool ParseOnlineResource(UGMarkup* PDomTree, UGString strNS);

};

///////////////////////////// WCS 1.1.*系列（1.1.1、1.1.2）///////////////////////////////////
class WCSCapabilities112 : public WCSCapabilities
{
public:
	//! \brief  默认的构造函数
	WCSCapabilities112();
	//! \brief  默认的析构函数
	virtual ~WCSCapabilities112();
public:
	//! \brief 从GetCapbilities文件序列化得到OGC Web服务的能力。
	//! \param strXMLFile GetCapbilities请求得到的XML文件路径[in]。
	//! \return 是否成功序列化，成功返回TRUE，失败返回FALSE。
	//! \remarks 。
	//! \attention 。
	virtual UGbool Serialize(UGString strXMLFile);	

	//! \brief 从GetCapbilities文件打开的Makup Dom 树序列化得到OGC Web服务的能力。
	//! \param PDomTree Dom树的指针[in]。
	//! \return 是否成功序列化，成功返回TRUE，失败返回FALSE。
	//! \remarks 当XML 文件已经打开则不要再打开一次直接用Dom树即可。
	//! \attention 。
	virtual UGbool Serialize(UGMarkup* pDomTree);

	//! \brief 解析wcs服务里的ServiceIdentification，获取服务信息。。
	//! \param PDomTree [in]Dom树的指针。。	
	//! \return 。
	UGbool ParseWCSServiceIdentification(UGMarkup* pDomTree);  

	//! \brief 解析wcs服务里的ServiceProvider，获取服务信息。。
	//! \param PDomTree [in]Dom树的指针。。	
	//! \return 。
	UGbool ParseWCSServiceProvider(UGMarkup* pDomTree);

	//! \brief 解析wcs服务里的OperationsMetadata，获取服务信息。。
	//! \param PDomTree [in]Dom树的指针。。	
	//! \return 。
	UGbool ParseWCSOperationsMetadata(UGMarkup* pDomTree);

	//! \brief 解析wcs服务里的Contents，获取服务信息。。
	//! \param PDomTree [in]Dom树的指针。。	
	//! \return 。
	UGbool ParseWCSContents(UGMarkup* pDomTree);  
};
}
#endif // !defined(WCSCAPABILITIES_H)

