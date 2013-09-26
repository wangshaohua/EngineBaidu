// WFSCapabilities.h: interface for the WFSCapabilities class.
//
//////////////////////////////////////////////////////////////////////

#ifndef OGCPARAERWFSCAPABILITIES_H
#define OGCPARAERWFSCAPABILITIES_H

#include "Stream/ugexports.h"
#include "EngineOGC/UGOGCCapabilities.h"

namespace UGC
{

class WFSCapabilities : public OGCCapabilities  
{
public:
	//! \brief  默认的构造函数
	WFSCapabilities();
	//! \brief  默认的析构函数
	virtual ~WFSCapabilities();
	
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
	//! \brief 存放WFS请求的成员属性
	WFSRequest m_OLRequest;
	//! \brief 存储WFS的操作数组。
	UGArray<UGString> m_arrOperations;
	//! \brief 存储特征对象的类型  
	UGArray<WFSFeatureType*> m_arrFeatureType;
};

///////////////////////// WFS 1.0.0 ///////////////////////////////////////
class WFSCapabilities100 : public WFSCapabilities
{
public:	
	//! \brief  默认的构造函数
	WFSCapabilities100();
	//! \brief  默认的析构函数
	virtual ~WFSCapabilities100();
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
	//! \attention 
	UGbool ParseOnlineResource(UGMarkup* PDomTree, UGString strNS);
};	

///////////////////////// WFS 1.1.0 ///////////////////////////////////////
class WFSCapabilities110 : public WFSCapabilities
{
public:	
	//! \brief  默认的构造函数
	WFSCapabilities110();
	//! \brief  默认的析构函数
	virtual ~WFSCapabilities110();
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
	//! \attention 	
	UGbool ParseOnlineResource(UGMarkup* PDomTree, UGString strNS);

};	

}
#endif // !defined(WFSCAPABILITIES_H)

