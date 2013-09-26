// WMSCapabilities.h: interface for the WMSCapabilities class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WMSCAPABILITIES_H__242599E7_D70B_4B0B_99B5_6D5970EFC6A3__INCLUDED_)
#define AFX_WMSCAPABILITIES_H__242599E7_D70B_4B0B_99B5_6D5970EFC6A3__INCLUDED_

#include "Stream/ugexports.h"
#include "EngineOGC/UGOGCCapabilities.h"

namespace UGC
{

class WMSCapabilities : public OGCCapabilities  
{
public:
	//! \brief  默认的构造函数
	WMSCapabilities();
	//! \brief  默认的析构函数
	virtual ~WMSCapabilities();

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
	
	//! \brief 将服务器能力序列化好的对象同步到网络数据源。
	//! \param pDataSource 网络数据源指针[in]。
	//! \return 是否同步杨功。
	//! \remarks 。
	//! \attention 。
	virtual UGbool SyncToDataSource(UGDataSourceOGC* pDataSource);

private:
	//! \brief 加载关键字字典 
	//! \attention 。
	void LoadDict();	

public:
	//! \brief 存放WMS请求的成员属性
	WMSRequest m_OLRequest;
	//! \brief 存放图层
	WMSLayer* m_pLayers;

};

///////////////////////// WMS 1.0.0 ///////////////////////////////////////
class WMSCapabilities100 : public WMSCapabilities
{
public:	
	//! \brief  默认的构造函数
	WMSCapabilities100();
	//! \brief  默认的析构函数
	virtual ~WMSCapabilities100();
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

	WMSLayer* ParseLayerRecursion(UGMarkup* PDomTree, UGString strNS, 
		WMSLayer* pParentLayer);
    //! \brief 解析markup，获取服务器信息。
	//! \remarks 。
	//! \attention 
	UGbool ParseOnlineResource(UGMarkup* PDomTree, UGString strNS);

};	

///////////////////////// WMS 1.1.0 ///////////////////////////////////////
class WMSCapabilities110 : public WMSCapabilities
{
public:	
	//! \brief  默认的构造函数
	WMSCapabilities110();
	//! \brief  默认的析构函数
	virtual ~WMSCapabilities110();
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
	//! \brief 解析markup，获取图层信息。
	//! \remarks 。
	//! \attention 
	WMSLayer* ParseLayerRecursion(UGMarkup* PDomTree, UGString strNS, 
		WMSLayer* pParentLayer);
    //! \brief 解析markup，获取服务器信息。
	//! \remarks 。
	//! \attention 
	UGbool ParseOnlineResource(UGMarkup* PDomTree, UGString strNS);

};	

///////////////////////// WMS 1.1.1 ///////////////////////////////////////
class WMSCapabilities111 : public WMSCapabilities
{
public:	
	//! \brief  默认的构造函数
	WMSCapabilities111();
	//! \brief  默认的析构函数
	virtual ~WMSCapabilities111();
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
	//! \brief 解析markup，获取图层信息。
	//! \remarks 。
	//! \attention 
	WMSLayer* ParseLayerRecursion(UGMarkup* PDomTree, UGString strNS, 
		WMSLayer* pParentLayer);
	//! \brief 解析markup，获取服务器信息。
	//! \remarks 。
	//! \attention 
	UGbool ParseOnlineResource(UGMarkup* PDomTree, UGString strNS);
	
};	

///////////////////////// WMS 1.3.0 ///////////////////////////////////////
class WMSCapabilities130 : public WMSCapabilities
{
public:	
	//! \brief  默认的构造函数
	WMSCapabilities130();
	//! \brief  默认的析构函数
	virtual ~WMSCapabilities130();
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
	//! \brief 解析markup，获取图层信息。
	//! \remarks 。
	//! \attention 
	WMSLayer* ParseLayerRecursion(UGMarkup* PDomTree, UGString strNS, 
		WMSLayer* pParentLayer);
	//! \brief 解析markup，获取服务器信息。
	//! \remarks 。
	//! \attention 
	UGbool ParseOnlineResource(UGMarkup* PDomTree, UGString strNS);
};	

}
#endif // !defined(AFX_WMSCAPABILITIES_H__242599E7_D70B_4B0B_99B5_6D5970EFC6A3__INCLUDED_)

