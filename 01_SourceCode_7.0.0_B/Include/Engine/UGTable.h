/*! \file	 UGTable.h
 *  \brief	 数据集基类
 *  \author	 ugc team
 *  \attention 
 *  Copyright(c) 2000-2010  SuperMap GIS Technologies,Inc.<br>
 *  All Rights Reserved
 *  \version $Id: UGTable.h,v 1.12 2009/08/10 07:58:01 cuiwz Exp $
 */

#if !defined(AFX_UGTABLE_H__93882047_ECE5_4A73_9B3F_FD8D539F8C69__INCLUDED_)
#define AFX_UGTABLE_H__93882047_ECE5_4A73_9B3F_FD8D539F8C69__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Engine/UGDataset.h"
#include "Engine/UGRecordset.h"
#include "Engine/UGFieldsManager.h"

namespace UGC{

//修改 UGTable  : public UGDataset，让 UGDatasetVector : public UGTable
//修改原因：使得UGTable UGDataset和 UGDatasetVector 能够共用一个 OgdcDataset* m_pOgdcDataset

//##ModelId=4820305000EA
#ifdef SYMBIAN60
class ENGINE_APIC UGTable  : public UGDataset
#else
class ENGINE_API UGTable  : public UGDataset
#endif
{
	friend class UGFieldsManager;
public:
	//##ModelId=4820305000EB
	ENGINE_APIF UGTable();
	//##ModelId=4820305000EC
	virtual ENGINE_APIF ~UGTable();

public:
	//! \brief 通过值更新字段值。
	//! \param strFieldName 更新的字段名[in]。
	//! \param varValue 字段值[in]。
	//! \param strFilter 更新字段时对数据行的过滤条件，
	//! 默认过滤条件置空，更新所有记录[in]。
	//! \return 是否更新字段值成功，成功返回TRUE，失败返回FALSE。
	//##ModelId=4820305000EE
	virtual ENGINE_APIF UGbool UpdateField(const UGString& strFieldName,
		const UGVariant& varValue,const UGString& strFilter = _U(""));

	//! \brief 通过表达式更新字段值。
	//! \param strFieldName 更新的字段名[in]。
	//! \param strExpress 算术运算表达式字符串，
	//! 字段值是某个算术运算表达式的值，如strFieldName = Col1 + col2 * 2[in]。
	//! \param strFilter 更新字段时对数据行的过滤条件，
	//! 默认过滤条件置空，更新所有记录[in]。
	//! \return 是否更新字段值成功，成功返回TRUE，失败返回FALSE。
	//##ModelId=4820305000F3
	virtual ENGINE_APIF UGbool UpdateFieldEx(const UGString& strFieldName,
		const UGString& strExpress,const UGString& strFilter = _U(""));

	//! \brief 复制字段值,strSrcField和。
	//! \param strSrcFieldName 源字段名称[in]。
	//! \param strDestFieldName 目的字段名称[in]。
	//! \return 是否复制字段成功，成功返回TRUE，失败返回FALSE。
	//! \attention 目的字段名必须都存在且目的字段要与源字段类型匹配。
	//! strDestField必须都存在且字段类型匹配
	//##ModelId=4820305000FB
	virtual ENGINE_APIF UGbool CopyField(const UGString& strSrcField,
		const UGString& strDestField);

	//! \brief 创建UUID字段
	virtual ENGINE_APIF UGbool CreateUUIDField();

	//! \brief 判断是否已有UUID字段
	virtual ENGINE_APIF UGbool HasUUIDField();

	//! \brief 创建普通索引。
	//! \param strFieldNameList 创建索引的字段列表，多个字段中间用","隔开[in]。
	//! \param strIndexName 索引名[in]。
	//! \return 创建普通索引是否成功，成功返回TRUE，失败返回FALSE。
	//##ModelId=4820305000FF
	virtual ENGINE_APIF UGbool CreateIndex(const UGString& strFieldNameList,
		const UGString& strIndexName);

	//! \brief 删除索引。
	//! \param strIndexName 索引名[in]。
	//! \return 删除索引是否成功，成功返回TRUE，失败返回FALSE。
	//##ModelId=482030500103
	virtual ENGINE_APIF UGbool DropIndex(const UGString& strIndexName);

	//! \brief 查找获得索引。
	//! \param 无
	//! \return 索引值与索引所在字段对应Map
	//##ModelId=482030500103
	virtual ENGINE_APIF std::map<UGString,UGString> GetIndexToMap();

	//! \brief 创建多个字段。
	//! \param fieldInfos 字段描述信息数组引用[in]。
	//! \return 创建多个字段是否成功，成功返回TRUE，失败返回FALSE。
	//! \remarks 如果多个字段中有成功的，有不成功的，则返回FALSE。
	//##ModelId=482030500106
	virtual ENGINE_APIF UGbool CreateFields(const UGFieldInfos& fieldInfos);
	
	//! \brief 通过FieldInfo创建一个字段。
	//! \param fieldInfo 字段描述信息对象引用[in]。
	//! \return 创建一个字段是否成功，成功返回TRUE，失败返回FALSE。
	//##ModelId=48203050010A
	virtual ENGINE_APIF UGbool CreateField(const UGFieldInfo& fieldInfo);

	//! \brief 通过设置字段的各项参数，创建一个字段。
	//! \param strFieldName 字段名[in]。
	//! \param nType 字段类型枚举值[in]。
	//! \param nSize 字段长度，以字节为单位[in]。
	//! \param nAttributes 字段属性默认为0[in]。
	//! \return 创建一个字段是否成功，成功返回TRUE，失败返回FALSE。
	//##ModelId=48203050010D
	virtual ENGINE_APIF UGbool CreateField(const UGString& strName,
		UGFieldInfo::FieldType nType,UGint nSize,UGint nAttributes = 0);

	//! \brief 通过字段名称删除字段。
	//! \param strFieldName 字段名[in]。
	//! \param bSystemFieldExcluded nIndex是否包含系统字段，默认不包含[in]。
	//! \return 是否删除成功，成功返回TRUE，失败返回FALSE。
	//##ModelId=482030500113
	virtual ENGINE_APIF UGbool DeleteField(const UGString& strName);

	//! \brief 通过序号删除字段。
	//! \param nIndex 字段序号，以0开始[in]。
	//! \param bSystemFieldExcluded nIndex是否包含系统字段，默认不包含[in]。
	//! \return 是否删除成功，成功返回TRUE，失败返回FALSE。
	//##ModelId=482030500116
	virtual ENGINE_APIF UGbool DeleteField(UGint nIndex, UGbool bSystemFieldExcluded = FALSE);

	//! \brief 获取数据表中所有字段的描述信息。
	//! \param fieldInfos 数据表中所有字段的描述信息数组[out]。
	//! \param bSystemFieldExcluded 是否获取系统字段，默认不取[in]。
	//! \return 是否获取成功，成功返回TRUE，失败返回FALSE。
	//##ModelId=48203050011B
	virtual ENGINE_APIF UGbool GetFieldInfos(UGFieldInfos& fieldInfos,UGbool bSystemFieldExcluded = FALSE);

	//! \brief 通过字段名获取字段描述信息。
	//! \param strFieldName 字段名[in]。
	//! \param fieldInfo 字段描述信息[out]。
	//! \return 是否获取成功，成功返回TRUE，失败返回FALSE。
	//##ModelId=48203050011F
	virtual ENGINE_APIF UGbool GetFieldInfo(const UGString& strName,UGFieldInfo& fieldInfo);
	
	//! \brief 通过字段序号获取字段信息。
	//! \param nIndex 字段序号，以0开始[in]。
	//! \param fieldInfo 字段描述信息[in]。
	//! \param bSystemFieldExcluded nIndex是否包含系统字段，默认不包含[in]。
	//! \return 是否获取成功，成功返回TRUE，失败返回FALSE。
	//##ModelId=482030500123
	virtual ENGINE_APIF UGbool GetFieldInfo(UGint nIndex,UGFieldInfo& fieldInfo, UGbool bSystemFieldExcluded = FALSE);

	//! \brief 通过字段名设置字段信息。
	//! \param strFieldName 字段名[in]。
	//! \param fieldInfo 字段描述信息对象引用[in]。
	//! \return 是否设置成功，成功返回TRUE，失败返回FALSE。
	//##ModelId=482030500127
	virtual ENGINE_APIF UGbool SetFieldInfo(const UGString& strName,const UGFieldInfo& fieldInfo);

	//! \brief 通过序号设置字段信息。
	//! \param nIndex 字段序号，以0开始[in]。
	//! \param fieldInfo 字段描述信息对象引用[in]。
	//! \param bSystemFieldExcluded nIndex是否包含系统字段，默认不包含[in]。
	//! \return 是否设置成功，成功返回TRUE，失败返回FALSE。
	//##ModelId=48203050012B
	virtual ENGINE_APIF UGbool SetFieldInfo(UGint nIndex,const UGFieldInfo& fieldInfo, UGbool bSystemFieldExcluded = FALSE);
	
	//! \brief 获取数据表中字段个数。
	//! \param bSystemFieldExcluded nIndex是否包含系统字段，默认不包含[in]。
	//! \return 字段个数。
	//##ModelId=48203050012F
	virtual ENGINE_APIF UGint GetFieldCount(UGbool bSystemFieldExcluded = FALSE);

	//! \brief 统计字段值。
	//! \param strFieldName 字段名[in]。
	//! \param nMode 统计模式[in]。
	//! \return 统计值。
	//##ModelId=482030500133
	virtual ENGINE_APIF UGVariant Statistic(const UGString& strField,UGStatisticMode nMode);

	//! \brief 计算字段单值个数。
	//! \param &strFieldName 字段名[in]。
	//! \param varKeys 单值数组[in]。
	//! \return 单值个数。
	//##ModelId=482030500138
	virtual ENGINE_APIF UGint CalculateUniqueValues(const UGString &strFieldName,UGArray<UGVariant>& varKeys);

	//! \brief 设置字段的类别。
	//! \param strFieldName 字段名[in]。
	//! \param nSign 系统字段标识[in]。
	//! \return 设置成功返回TRUE，失败返回FALSE。	
	//##ModelId=4820305301D4
	virtual ENGINE_APIF UGbool SetFieldSign(const UGString& strFieldName,UGFieldInfo::FieldSign nSign);

	//! \brief 通过类别获取字段名
	//! \param nSign 系统字段标识[in]。
	//! \return 字段名。
	//##ModelId=4820305301CB
	virtual ENGINE_APIF UGString GetFieldNameBySign(UGFieldInfo::FieldSign nSign);

	//! \brief 判断字段名是否有效。
	//! \param strFieldName 字段名[in]。
	//! \return 有效返回TRUE，无效返回FALSE。
	//##ModelId=4820305301BA
	virtual ENGINE_APIF UGbool IsAvailableFieldName(const UGString& strFieldName);

	//! \brief  是否有几何数据，除了Tablur数据集，都有几何数据
	//##ModelId=48203053015B
	virtual ENGINE_APIF UGbool HasGeometry() const;

	//! \brief 判断是否点数据集
	virtual ENGINE_APIF UGbool IsPointDT();	


	//! \brief 设置字段信息
	ENGINE_APIF UGbool SetFieldInfo(const UGString & strName,
							 const UGString & strForeignName,
							 UGFieldInfo::FieldType nType,
							 const UGString & strFormat,	
							 const UGString & strDomain, 
							 UGbool bUpdatable = TRUE,
							 UGbool bRequired = FALSE,
							 const UGString & strDefault = _U("")
							 );

	//! \brief 获取数据表中所有字段信息的 引用。给UGFieldsManager用。
	UGFieldInfos& GetFieldInfosRef(){return m_FieldInfos;};

	UGFieldsManager *GetFieldsManager(); 

	//! \brief  返回数据集字符编码方式
	//##ModelId=4820305301D8
	ENGINE_APIF UGMBString::Charset GetCharset() const;

	//! \brief  设置数据集字符编码方式
	//##ModelId=4820305301DA
	virtual ENGINE_APIF UGbool SetCharset(UGMBString::Charset c);

	//! \brief  判断数据集是否有某个选项信息
	//##ModelId=482030530149
	ENGINE_APIF UGbool HasFlag(UGint nOption) const;

public:
	//保持一致和组件 
	//##ModelId=48203050013C
	UGFieldInfos m_FieldInfos;

	//##ModelId=4820305302A0
	UGMBString::Charset m_nCharset;

	//! \brief  一次获取的记录数
	//##ModelId=482030530284
	UGint m_nOnceFetchCount;

protected:
	UGFieldsManager *m_pFieldsManager;

};

}

#endif // !defined(AFX_UGTABLE_H__93882047_ECE5_4A73_9B3F_FD8D539F8C69__INCLUDED_)

