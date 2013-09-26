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
//!  \author 研发一部。
//!  \attention 
//!   Copyright (c) 1996-2010 SuperMap Software Limited Company.  <br> 
//!   All Rights Reserved.
//!  \version 6.0
//////////////////////////////////////////////////////////////////////////
#ifndef UGDOMAINMANAGERBASE_H
#define UGDOMAINMANAGERBASE_H

#include "Engine/UGDomain.h"

namespace UGC
{
#define	DOMAINBASE_TABLE_NAME	_U("SmDomains")
#define RANGEDOMAIN_TABLE_NAME	_U("SmRangeDomains")
#define CODEDOMAIN_TABLE_NAME	_U("SmCodeDomains")
#define DOMAINFIELD_TABLE_NAME	_U("SmDomainField")

	class UGDataSource;
	class UGDatasetVector;
	
	class ENGINE_API UGDomainManagerBase
	{
	public:
		UGDomainManagerBase();

		UGDomainManagerBase(UGDataSource *pDS);
		
		virtual ~UGDomainManagerBase();
	
		//===================================================
		//! \brief  初始化值域
		//! \param 
		//! \return   
		//! \remarks 
		//! \attention
		virtual UGbool InitDomain(){return FALSE;}

		//===================================================
		//! \brief  通过字段名称获取值域
		//! \param  pDatasetVector[I] 数据集
		//! \param  strFieldName[I]   字段名称
		//! \return   
		//! \remarks 
		//! \attention 调用本函数之前必须调用ReadDomainFields函数
		UGDomainBase* GetDomain(UGDatasetVector *pDatasetVector, const UGString &strFieldName);

		//===================================================
		//! \brief  通过值域类型获取值域集合
		//! \param  type[I]    值域类型
		//! \param  domains[O] 值域集合
		//! \return   
		//! \remarks 
		//! \attention 调用本函数之前必须调用ReadDomain函数
		UGArray<UGDomainBase*> GetDomains(UGDomainBase::DomainType type);

		//===================================================
		//! \brief  通过字段类型获取值域集合
		//! \param  fieldtype[I] 字段类型
		//! \param  domains[O]   值域集合
		//! \return   
		//! \remarks 
		//! \attention 调用本函数之前必须调用ReadDomain函数
		UGArray<UGDomainBase*> GetDomains(UGFieldInfo::FieldType fieldtype);

		//===================================================
		//! \brief  获取值域集合
		//! \param  
		//! \return   
		//! \remarks 
		//! \attention
		UGArray<UGDomainBase*> GetAllDomains();

		//===================================================
		//! \brief  获取值域数目
		//! \param 
		//! \return   
		//! \remarks 
		//! \attention
		UGint GetDomainCount();

		//===================================================
		//! \brief  设置特定字段的值域
		//! \param  pDatasetVector[I] 数据集
		//! \param  strFieldName[I]   字段名称
		//! \param  pDomain[I]        值域
		//! \return 设置成功返回true  
		//! \remarks 
		//! \attention
		UGbool SetDomain(UGDatasetVector *pDatasetVector, const UGString &strFieldName, UGDomainBase *pDomain);

		//===================================================
		//! \brief  删除特定的的值域
		//! \param 
		//! \return   
		//! \remarks 
		//! \attention
		UGbool RemoveDomain(UGDatasetVector *pDatasetVector, const UGString &strFieldName);

	protected:
		//===================================================
		//! \brief  通过ID删除值域
		//! \param 
		//! \return   
		//! \remarks 
		//! \attention
		virtual UGbool DeleteDomainByID(UGuint nID){return FALSE;}

		//===================================================
		//! \brief  移除某字段上域的关联（一个字段一次只能被关联一个域）
		//! \param 
		//! \return   
		//! \remarks 
		//! \attention
		virtual UGbool DeleteDomainFromField(UGDatasetVector *pDataset, const UGString &fieldname){return FALSE;}

		//===================================================
		//! \brief  从数据库读取域相关的所有信息
		//! \param 
		//! \return   
		//! \remarks 
		//! \attention
		virtual UGbool ReadInfos(){return FALSE;}
	
		//===================================================
		//! \brief  从数据库读取范围域相关的信息并构建
		//! \param 
		//! \return   
		//! \remarks 
		//! \attention
		virtual UGbool ReadRangeDomains(){return FALSE;}

		//===================================================
		//! \brief  从数据库读取代码域相关的信息并构建
		//! \param 
		//! \return   
		//! \remarks 
		//! \attention
		virtual UGbool ReadCodeDomains(){return FALSE;}

		//===================================================
		//! \brief  从数据库读取域和字段的关联信息
		//! \param 
		//! \return   
		//! \remarks 
		//! \attention
		virtual UGbool ReadDomainFields(){return FALSE;}

		//===================================================
		//! \brief  
		//! \param 
		//! \return   
		//! \remarks 
		//! \attention
		virtual UGuint GetNextDomainID(){return 0;}

		//===================================================
		//! \brief 判断DomainID是否是有效的ID
		//! \param nDomainID[in]
		//! \return  有效返回TRUE,无效返回FALSE
		//! \remarks 
		//! \attention
		virtual UGbool IsValidDomainID(UGint nDomainID){return TRUE;}

	
		//===================================================
		//! \brief  在数据库创建三个表：DOMAINBASE_TABLE_NAME，RANGEDOMAIN_TABLE_NAME，
		//!			CODEDOMAIN_TABLE_NAME，DOMAINFIELD_TABLE_NAME
		//! \param 
		//! \return   
		//! \remarks 
		//! \attention
		virtual UGbool CreateDomainTables(){return FALSE;}

		//===================================================
		//! \brief  将域的信息写入数据库
		//! \param 
		//! \return   
		//! \remarks 
		//! \attention
		virtual UGbool InsertDomainToDB(const UGDomainBase *pDomain){return FALSE;}

		//===================================================
		//! \brief  更新域的信息到数据库
		//! \param 
		//! \return   
		//! \remarks 
		//! \attention
		virtual UGbool UpdateDomainToDB(const UGDomainBase *pDomain){return FALSE;}

		//===================================================
		//! \brief  将域跟字段的关联信息写入数据库
		//! \param 
		//! \return   
		//! \remarks 
		//! \attention
		virtual UGbool InsertDomainFieldToDB(const UGDomainField &dmfld){return FALSE;}

		//===================================================
		//! \brief  通过ID获取值域
		//! \param 
		//! \return   
		//! \remarks 
		//! \attention
		UGDomainBase* GetDomainByID(UGint nDomainID);

		//===================================================
		//! \brief  检查是否能删除指定ID的域（域已经被关联到某个字段时是不能被删除的）
		//! \param 
		//! \return   
		//! \remarks 
		//! \attention
		UGbool CanDeleteDomain(UGuint nID);

		//===================================================
		//! \brief  构建范围域
		//! \param  nSize[I] pIntervals所指内存的大小 
		//! \return   
		//! \remarks 
		//! \attention
		UGDomainBase* MakeRangeDomain(
			UGuint nDomainID, 
			const UGString &strDomainName, 
			const UGString &strDomainDesc, 
			UGint nDomainType, 
			UGint nFieldType, 
			const void *pIntervals, 
			UGint nSize);
	
		//===================================================
		//! \brief  构建代码域
		//! \param  nSize[I] pCodeInfos所指内存的大小 
		//! \return   
		//! \remarks 
		//! \attention
		UGDomainBase* MakeCodeDomain(
			UGuint nDomainID, 
			const UGString &strDomainName, 
			const UGString &strDomainDesc,
			UGint nDomainType,
			UGint nFieldType, 
			const void *pCodeInfos, 
			UGint nSize);

	public:
		//===================================================
		//! \brief  根据域的ID获取所关联的字段名
		//! \param  nDomainID[IN]
		//! \return 所关联的字段名
		//! \remarks 
		//! \attention
		UGString GetFieldName(UGint nDomainID);

		//===================================================
		//! \brief  根据域的ID获取域所在的数据集ID
		//! \param  nDomainID[IN]
		//! \return 域所在的数据集ID 
		//! \remarks 
		//! \attention
		UGint GetDataSetID(UGint nDomainID);

		//===================================================
		//! \brief  字段是否已经被关联，如果关联则不能再关联
		//! \param  pDataset[I]
		//! \param  strFieldName[I]
		//! \return   
		//! \remarks 
		//! \attention
		UGbool IsSetDomain(UGDatasetVector *pDataset, const UGString &strFieldName);

		//===================================================
		//! \brief  检查指定的字段和域的字段类型是否一致
		//! \param 
		//! \return   
		//! \remarks 
		//! \attention
		UGbool IsFieldTypeConsistent(UGDatasetVector *pDataset, const UGString &strFieldName, UGint nDomainID);


		//===================================================
		//! \brief  获得是否有数据违反值域规则
		//! \param 
		//! \return   
		//! \remarks 
		//! \attention
		UGbool HasInvalidFieldValue(){return m_bHasInvalidFieldValue;}

		//===================================================
		//! \brief  设置是否有数据违反规则标志
		//! \param 
		//! \return   
		//! \remarks 
		//! \attention
		void SetHasInvalidFieldValue(UGbool hasInvalidValue){m_bHasInvalidFieldValue = hasInvalidValue;}

	protected:
		//!	\brief	记录所有的域
		UGArray<UGDomainBase*> m_Domains;

		//! \brief	记录域与字段之间的对应情况
		UGArray<UGDomainField> m_DomainFields;

		//!	\brief	相应的数据源
		UGDataSource *m_pDataSource;

		//! \brief 是否有数据违反规则标志
		UGbool m_bHasInvalidFieldValue;
	};
}

#endif
