
#if !defined(AFX_UGMAPSERVICESTUBFACTORY_H__1885519B_9074_4676_8294_31061A9FCB47__INCLUDED_)
#define AFX_UGMAPSERVICESTUBFACTORY_H__1885519B_9074_4676_8294_31061A9FCB47__INCLUDED_

#include "MapServiceStub/UGMapServiceStub.h"

namespace UGC 
{

//! \brief 所有网络服务工厂基类，网络服务的创建由子类工厂创建
class MAPSERVICESTUB_API UGMapServiceStubFactory  
{
public:
	UGMapServiceStubFactory();
	virtual ~UGMapServiceStubFactory();

public:
	//! \brief 创建文件解析类(根据文件类型区分)
	virtual UGMapServiceStub* CreateMapServiceStub(UGint nFileType) const=0;	

	//! \brief 得到能够支持的文件类型。
	virtual void GetSupportMapServiceTypes(UGArray<UGint>& arrServiceTypes) const=0;	
	
	//! \brief 得到插件名称。
	virtual UGString GetName() const=0;	
	
public:		
	//! \brief 删除文件解析类。
	virtual void DestroyMapServiceStub(UGMapServiceStub*& pWebStub) const;	

	//! \brief 是否支持的文件类型。
	virtual UGbool IsSupportMapServiceType(UGint nServiceType) const;		
	
};

} //namespace UGC


#endif // !defined(AFX_UGMAPSERVICESTUBFACTORY_H__1885519B_9074_4676_8294_31061A9FCB47__INCLUDED_)


