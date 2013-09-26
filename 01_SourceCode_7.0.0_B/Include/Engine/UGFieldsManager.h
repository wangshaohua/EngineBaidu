#pragma once
#include "Geometry/UGFeature.h"
#include "Engine/ugeng.h"

namespace UGC{

class UGTable;

class ENGINE_API UGFieldsManager
{

public:
	//! \brief 通过值更新字段值。
	//! \param strFieldName 更新的字段名[in]。
	//! \param varValue 字段值[in]。
	//! \param strFilter 更新字段时对数据行的过滤条件，
	//! 默认过滤条件置空，更新所有记录[in]。
	//! \return 是否更新字段值成功，成功返回TRUE，失败返回FALSE。
	//##ModelId=4820305000EE
	virtual ENGINE_APIF UGbool UpdateField(const UGString& strFieldName,
		const UGVariant& varValue,const UGString& strFilter = _U("")) = 0;

	//! \brief 通过表达式更新字段值。
	//! \param strFieldName 更新的字段名[in]。
	//! \param strExpress 算术运算表达式字符串，
	//! 字段值是某个算术运算表达式的值，如strFieldName = Col1 + col2 * 2[in]。
	//! \param strFilter 更新字段时对数据行的过滤条件，
	//! 默认过滤条件置空，更新所有记录[in]。
	//! \return 是否更新字段值成功，成功返回TRUE，失败返回FALSE。
	//##ModelId=4820305000F3
	virtual ENGINE_APIF UGbool UpdateFieldEx(const UGString& strFieldName,
		const UGString& strExpress,const UGString& strFilter = _U("")) = 0;

	//! \brief 复制字段值,strSrcField和。
	//! \param strSrcFieldName 源字段名称[in]。
	//! \param strDestFieldName 目的字段名称[in]。
	//! \return 是否复制字段成功，成功返回TRUE，失败返回FALSE。
	//! \attention 目的字段名必须都存在且目的字段要与源字段类型匹配。
	//! strDestField必须都存在且字段类型匹配
	//##ModelId=4820305000FB
	virtual ENGINE_APIF UGbool CopyField(const UGString& strSrcField,
		const UGString& strDestField) = 0;

	//! \brief 创建UUID字段
	virtual ENGINE_APIF UGbool CreateUUIDField() = 0;


	//! \brief 创建普通索引。
	//! \param strFieldNameList 创建索引的字段列表，多个字段中间用","隔开[in]。
	//! \param strIndexName 索引名[in]。
	//! \return 创建普通索引是否成功，成功返回TRUE，失败返回FALSE。
	//##ModelId=4820305000FF
	virtual ENGINE_APIF UGbool CreateIndex(const UGString& strFieldNameList,
		const UGString& strIndexName) = 0;

	//! \brief 删除索引。
	//! \param strIndexName 索引名[in]。
	//! \return 删除索引是否成功，成功返回TRUE，失败返回FALSE。
	//##ModelId=482030500103
	virtual ENGINE_APIF UGbool DropIndex(const UGString& strIndexName) = 0;

	//! \brief 查找获得索引。
	//! \param 无
	//! \return 索引值--索引所在字段对应MAP。
	//##ModelId=482030500103
	virtual ENGINE_APIF std::map<UGString,UGString> GetIndexToMap() = 0;

	//! \brief 创建多个字段。
	//! \param fieldInfos 字段描述信息数组引用[in]。
	//! \return 创建多个字段是否成功，成功返回TRUE，失败返回FALSE。
	//! \remarks 如果多个字段中有成功的，有不成功的，则返回FALSE。
	//##ModelId=482030500106
	virtual ENGINE_APIF UGbool CreateFields(const UGFieldInfos& fieldInfos) = 0;

	//! \brief 通过FieldInfo创建一个字段。
	//! \param fieldInfo 字段描述信息对象引用[in]。
	//! \return 创建一个字段是否成功，成功返回TRUE，失败返回FALSE。
	//##ModelId=48203050010A
	virtual ENGINE_APIF UGbool CreateField(const UGFieldInfo& fieldInfo) = 0;

	//! \brief 通过设置字段的各项参数，创建一个字段。
	//! \param strFieldName 字段名[in]。
	//! \param nType 字段类型枚举值[in]。
	//! \param nSize 字段长度，以字节为单位[in]。
	//! \param nAttributes 字段属性默认为0[in]。
	//! \return 创建一个字段是否成功，成功返回TRUE，失败返回FALSE。
	//##ModelId=48203050010D
	virtual ENGINE_APIF UGbool CreateField(const UGString& strName,
		UGFieldInfo::FieldType nType,UGint nSize,UGint nAttributes = 0) = 0;

	//! \brief 通过字段名称删除字段。
	//! \param strFieldName 字段名[in]。
	//! \param bSystemFieldExcluded nIndex是否包含系统字段，默认不包含[in]。
	//! \return 是否删除成功，成功返回TRUE，失败返回FALSE。
	//##ModelId=482030500113
	virtual ENGINE_APIF UGbool DeleteField(const UGString& strName) = 0;

	//! \brief 通过序号删除字段。
	//! \param nIndex 字段序号，以0开始[in]。
	//! \param bSystemFieldExcluded nIndex是否包含系统字段，默认不包含[in]。
	//! \return 是否删除成功，成功返回TRUE，失败返回FALSE。
	//##ModelId=482030500116
	virtual ENGINE_APIF UGbool DeleteField(UGint nIndex, UGbool bSystemFieldExcluded = FALSE) = 0;

	//! \brief 获取数据表中所有字段的描述信息。
	//! \param fieldInfos 数据表中所有字段的描述信息数组[out]。
	//! \param bSystemFieldExcluded 是否获取系统字段，默认不取[in]。
	//! \return 是否获取成功，成功返回TRUE，失败返回FALSE。
	//##ModelId=48203050011B
	virtual ENGINE_APIF UGbool GetFieldInfos(UGFieldInfos& fieldInfos,UGbool bSystemFieldExcluded = FALSE) = 0;

	//! \brief 通过字段名获取字段描述信息。
	//! \param strFieldName 字段名[in]。
	//! \param fieldInfo 字段描述信息[out]。
	//! \return 是否获取成功，成功返回TRUE，失败返回FALSE。
	//##ModelId=48203050011F
	virtual ENGINE_APIF UGbool GetFieldInfo(const UGString& strName,UGFieldInfo& fieldInfo) = 0;

	//! \brief 通过字段序号获取字段信息。
	//! \param nIndex 字段序号，以0开始[in]。
	//! \param fieldInfo 字段描述信息[in]。
	//! \param bSystemFieldExcluded nIndex是否包含系统字段，默认不包含[in]。
	//! \return 是否获取成功，成功返回TRUE，失败返回FALSE。
	//##ModelId=482030500123
	virtual ENGINE_APIF UGbool GetFieldInfo(UGint nIndex,UGFieldInfo& fieldInfo, UGbool bSystemFieldExcluded = FALSE) = 0;

	//! \brief 通过字段名设置字段信息。
	//! \param strFieldName 字段名[in]。
	//! \param fieldInfo 字段描述信息对象引用[in]。
	//! \return 是否设置成功，成功返回TRUE，失败返回FALSE。
	//##ModelId=482030500127
	virtual ENGINE_APIF UGbool SetFieldInfo(const UGString& strName,const UGFieldInfo& fieldInfo) = 0;

	//! \brief 通过序号设置字段信息。
	//! \param nIndex 字段序号，以0开始[in]。
	//! \param fieldInfo 字段描述信息对象引用[in]。
	//! \param bSystemFieldExcluded nIndex是否包含系统字段，默认不包含[in]。
	//! \return 是否设置成功，成功返回TRUE，失败返回FALSE。
	//##ModelId=48203050012B
	virtual ENGINE_APIF UGbool SetFieldInfo(UGint nIndex,const UGFieldInfo& fieldInfo, UGbool bSystemFieldExcluded = FALSE) = 0;

	//! \brief 获取数据表中字段个数。
	//! \param bSystemFieldExcluded nIndex是否包含系统字段，默认不包含[in]。
	//! \return 字段个数。
	//##ModelId=48203050012F
	virtual ENGINE_APIF UGint GetFieldCount(UGbool bSystemFieldExcluded = FALSE) = 0;

	//! \brief 统计字段值。
	//! \param strFieldName 字段名[in]。
	//! \param nMode 统计模式[in]。
	//! \return 统计值。
	//##ModelId=482030500133
	virtual ENGINE_APIF UGVariant Statistic(const UGString& strField,UGStatisticMode nMode) = 0;

	//! \brief 计算字段单值个数。
	//! \param &strFieldName 字段名[in]。
	//! \param varKeys 单值数组[in]。
	//! \return 单值个数。
	//##ModelId=482030500138
	virtual ENGINE_APIF UGint CalculateUniqueValues(const UGString &strFieldName,UGArray<UGVariant>& varKeys) = 0;

	//! \brief 设置字段信息
	//! \brief 设置字段的类别。
	//! \param strFieldName 字段名[in]。
	//! \param nSign 系统字段标识[in]。
	//! \return 设置成功返回TRUE，失败返回FALSE。	
	//##ModelId=4820305301D4
	virtual UGbool SetFieldSign(const UGString& strFieldName,UGFieldInfo::FieldSign nSign) = 0;

	//! \brief 通过类别获取字段名
	//! \param nSign 系统字段标识[in]。
	//! \return 字段名。
	//##ModelId=4820305301CB
	virtual UGString GetFieldNameBySign(UGFieldInfo::FieldSign nSign) = 0;

	//! \brief 查询字段信息
	virtual UGbool QueryFieldInfos() = 0;

	//! \brief 判断字段名是否有效。
	//! \param strFieldName 字段名[in]。
	//! \return 有效返回TRUE，无效返回FALSE。
	//##ModelId=4820305301BA
	virtual UGbool IsAvailableFieldName(const UGString& strFieldName) = 0;

	//! \brief 设置二进制字段的大小
	//! \param nNewSize 字段的Size
	//! \param strFieldName 要设置的字段名。
	//! \return 成功返回TRUE，失败返回FALSE。
	virtual UGbool SetMaxBinaryFieldSize(UGint nNewSize, UGString strFieldName){ return FALSE; };

protected:
	//! \brief 数据集指针，初始化时赋值
	UGTable *m_pDataset;
};


}
