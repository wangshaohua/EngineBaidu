//////////////////////////////////////////////////////////////////////////
//                    _   _   ____   ____                    
//   Project         | | | | / ___) / ___)                   
//                   | | | || | __ | |                       
//                   | |_| || |_\ || \___                    
//                    \____/ \____| \ ___)     6.0           
//                                                           
//!  \file OGCCapabilities.h
//!  \brief OGC 服务器能力的基类的接口定义。
//!  \details 文件详细信息。
//!  \author duxiaomin。
//!  \attention 
//!   Copyright (c) 1996-2008 SuperMap Software Limited Company.  <br> 
//!   All Rights Reserved.
//!  \version 6.0
//////////////////////////////////////////////////////////////////////////

#ifndef OGCCAPABILITIES_H
#define OGCCAPABILITIES_H

#include "Stream/ugexports.h"
#include "EngineOGC/UGOGCLayerInfo.h"
#include "Toolkit/UGMarkup.h"

namespace UGC
{

class UGDataSourceOGC;
class UGMarkup;

class OGCCapabilities  
{
	//! \brief 定义用于服务器连接的构造体 
	typedef struct ogcServer 
	{
		ogcServer()
		{
			m_strName = _U("");
			m_strTitle = _U("");
			m_strAbstract = _U("");
			m_arrKeywords.RemoveAll();
			m_strOnlineResource = _U("");
			m_strFees = _U("");
			m_strAccessConstraints = _U("");
			m_strServiceType = _U("");
			m_arrServiceTypeVersion.RemoveAll();
		}
		//! \brief wms的名称。
 		UGString m_strName;
		//! \brief wms的标题。
		UGString m_strTitle;
		//! \brief wms的摘要。
		UGString m_strAbstract;
		//! \brief wms的关健字数组。
		UGArray<UGString> m_arrKeywords;
		//! \brief wms的网络地址。
		UGString m_strOnlineResource;
		//! \brief wms的费用。
		UGString m_strFees;
		//! \brief wms的访问限制。
		UGString m_strAccessConstraints;
		//! \brief wms的服务类型
		UGString m_strServiceType;
		//! \brief wms的版本。
		UGArray<UGString> m_arrServiceTypeVersion;
	} server;
	
	typedef struct ContactInfo
	{
		ContactInfo()
		{
			m_strPhoneVoice=_U("");
			m_strPhoneFacsimile=_U("");		
			m_strDeliveryPoint.RemoveAll();
			m_strAddressType=_U("");
			m_strAddress=_U("");
			m_strCity=_U("");
			m_strAdministrativeArea=_U("");
			m_strPostalCode=_U("");
			m_strCountry=_U("");
			m_strElectronicMailAddress=_U("");	
			m_strOnlineResource=_U("");
			m_strHoursOfService=_U("");
			m_strContactInstructions=_U("");				
		}		
		//! \brief 语音电话。	
		UGString m_strPhoneVoice;

		//! \brief 传真
		UGString m_strPhoneFacsimile;

		//! \brief 递送地址
		UGStrings m_strDeliveryPoint;

		//  \brief 暂时还不清楚指什么,wms111出现的标签
		UGString  m_strAddressType;

		//  \brief 暂时还不清楚指什么,wms111出现的标签
		UGString  m_strAddress;

		//! \brief 城市
		UGString m_strCity;

		//! \brief 行政区或直辖市或联邦制下的洲
		UGString m_strAdministrativeArea;

		//! \brief 邮编
		UGString m_strPostalCode;

		//! \brief 国家
		UGString m_strCountry;

		//! \brief Email
		UGString m_strElectronicMailAddress;

		//! \brief 在线资源
		UGString m_strOnlineResource;

		//! \brief  服务时间
		UGString m_strHoursOfService;

		//! \brief 联系方式
		UGString m_strContactInstructions;		
	} ;	 

	typedef struct ServiceContact
	{
		ServiceContact()
		{
			m_strIndividualName = _U("");
			m_strPositionName   = _U("");
		}

		//! \brief 联系人姓名。
		UGString m_strIndividualName;

		//! \brief 联系人职位。
		UGString m_strPositionName;

		//! \brief 服务提供方其它联系信息
		ContactInfo m_contactInfo;
	};

	typedef struct serviceProvider
	{
		serviceProvider()
		{
			m_strProviderName=_U("");
			m_strProviderSite=_U("");		
		}		
		//! \brief 服务提供商或组织
		UGString m_strProviderName;

		//! \brief 服务提供商代表或联系人
		UGString m_strProviderDelegate;

		//! \brief 服务提供商的门户网站
		UGString m_strProviderSite;

		//! \brief 服务提供方地点(具体的地址)
		UGString m_strIndividualName;

		//! \brief 服务提供方地址(一定范围的地址)
		UGString m_strPositionName;

		//! \brief 服务提供方其它联系信息
		ServiceContact m_serviceContact;

		//! \brief 服务提供方的角色
		UGString m_strRole;		 
	};
public:
	//! \brief  默认的构造函数
	OGCCapabilities();
	//! \brief  默认的析构函数
	virtual ~OGCCapabilities();

public:
	//! \brief 从GetCapbilities文件序列化得到OGC Web服务的能力。
	//! \param strXMLFile GetCapbilities请求得到的XML文件路径[in]。
	//! \return 是否成功序列化，成功返回TRUE，失败返回FALSE。
	virtual UGbool Serialize(UGString strXMLFile) = 0;	

	//! \brief 从GetCapbilities文件打开的Makup Dom 树序列化得到OGC Web服务的能力。
	//! \param PDomTree Dom树的指针[in]。
	//! \return 是否成功序列化，成功返回TRUE，失败返回FALSE。
	//! \remarks 当XML 文件已经打开则不要再打开一次直接用Dom树即可。
	virtual UGbool Serialize(UGMarkup* PDomTree) = 0;	

	//! \brief 将服务器能力序列化好的对象同步到网络数据源。
	//! \param pDataSource 网络数据源指针[in]。
	//! \return 是否同步成功。
	virtual UGbool SyncToDataSource(UGDataSourceOGC* pDataSource) = 0;	

	//! \brief 比较两个标签是否相同  
	virtual UGbool SameXMLTag(const UGString& strTagLeft, const UGString& strTagRight);
	//! \brief 从标签中获取命名空间 
	virtual UGString TagNameSpace(const UGString& strTag);
    //! \brief 从地址中获取分健值对中的关健字
	virtual UGString TrimKeyWord(const UGString& strURL);	
public:
	//! \brief 服务器连接结构体变量
	//! \remarks 备注信息。
	ogcServer m_InfoServer;

	//! \brief 服务提供商信息
	//! \remarks 备注信息。
	serviceProvider m_serviceProvider;

	//! \brief 服务器的版本
	UGString m_strVersion;

	//! \brief 向服务器请求的类型。
	//! \remarks 备注信息。
	UGString m_strType;

protected:
	// 定义一个OGC URL 请求的关键字字典
	UGDict<UGString,int>  m_dictKeyWords;
};

}
#endif // !defined(OGCCAPABILITIES_H)

