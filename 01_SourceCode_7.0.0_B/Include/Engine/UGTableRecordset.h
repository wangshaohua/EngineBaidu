// UGTableRecordset.h: interface for the UGTableRecordset class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_UGTABLERECORDSET_H__7C95DC17_F28F_441D_A6C8_4AEB7AC45601__INCLUDED_)
#define AFX_UGTABLERECORDSET_H__7C95DC17_F28F_441D_A6C8_4AEB7AC45601__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Stream/ugdefs.h"
#include "Engine/UGEngDefs.h"

#if !defined SYMBIAN60 && !defined  OS_ANDROID && !defined (IOS)
#include "OGDC/OgdcRecordset.h"
#include "Element/OgdcFieldInfo.h"
#endif

namespace UGC{

//##ModelId=4820304F030F
#ifdef SYMBIAN60
class ENGINE_APIC UGTableRecordset
#else
class ENGINE_API UGTableRecordset
#endif
 {
public:
	//##ModelId=4820304F031C
	ENGINE_APIF UGTableRecordset();
	//##ModelId=4820304F031D
	virtual ENGINE_APIF ~UGTableRecordset();

public:
	//! \brief 是否记录集为空(没有记录)
	//##ModelId=4820304F032C
	virtual ENGINE_APIF UGbool IsEmpty(); 

	//! \brief 判断当前记录指针是否指向头
	//##ModelId=4820304F032E
	virtual ENGINE_APIF UGbool IsBOF();

	//! \brief 判断当前记录指针是否指向尾
	//##ModelId=4820304F033C
	virtual ENGINE_APIF UGbool IsEOF();
	
	//! \brief 关闭记录集
	//##ModelId=4820304F033E
	virtual ENGINE_APIF void Close();

	//! \brief 通过字段名获取字段值
	//##ModelId=4820304F0340
	virtual ENGINE_APIF UGbool GetFieldValue(const UGString& strName,UGVariant& varVal);

	//! \brief 通过索引序号获取字段值
	//##ModelId=4820304F034C
	virtual ENGINE_APIF UGbool GetFieldValue(UGint nIndex,UGVariant& varVal);

	//! \brief 通过字段名设置当前记录的字段值,值为变体类型
	//##ModelId=4820304F0350
	virtual ENGINE_APIF UGbool SetFieldValue(const UGString& strName,const UGVariant& varVal);
	
	//! \brief 通过字段名设置当前记录的字段值,值为字符串类型
	//##ModelId=4820304F035D
	virtual ENGINE_APIF UGbool SetFieldValue(const UGString& strName,const UGString& strVal);
	
	//! \brief 通过索引序号设置当前记录的字段值,值为变体类型
	//##ModelId=4820304F0361
	virtual ENGINE_APIF UGbool SetFieldValue(UGint nIndex,const UGVariant& varVal);

	//! \brief 通过索引序号设置当前记录的字段值,值为字符串类型
	//##ModelId=4820304F036E
	virtual ENGINE_APIF UGbool SetFieldValue(UGint nIndex,	const UGString& strVal);

	//! \brief 通过字段名设置字段值为空
	//##ModelId=4820304F0372
	virtual ENGINE_APIF UGbool SetFieldValueNull(const UGString& strName);

	//! \brief 通过索引设置字段值为空
	//##ModelId=4820304F037C
	virtual ENGINE_APIF UGbool SetFieldValueNull(UGint nIndex);

	//! \brief 已知字段为bool类型，根据字段序号设置字段值
	//! \param nFieldIndex 字段序号[in]。
	//! \param bValue 字段值 [in]。
	//! \return 是否设置成功，成功返回TRUE，失败返回FALSE。
	//##ModelId=4820304F037F
	virtual ENGINE_APIF UGbool SetBool(UGint nFieldIndex, UGbool bValue = FALSE);
	
	//! \brief 已知字段为bool类型，根据字段名设置字段值
	//! \param strFieldName 字段名[in]。
	//! \param bValue 字段值 [in]。
	//! \return 是否设置成功，成功返回TRUE，失败返回FALSE。
	//##ModelId=4820304F038B
	virtual ENGINE_APIF UGbool SetBool(const UGString& strFieldName, UGbool bValue = FALSE);

	//! \brief 已知字段为bool类型,根据字段序号获取字段值。
	//! \param nFieldIndex 字段序号[in]。
	//! \return 获取的字段值。
	//##ModelId=4820304F038F
	virtual ENGINE_APIF UGbool GetBool(UGint nFieldIndex);

	//! \brief 已知字段为bool类型,根据字段名获取字段值。
	//! \param strFieldName 字段名[in]。
	//! \return 获取的字段值。
	//##ModelId=4820304F039B
	virtual ENGINE_APIF UGbool GetBool(const UGString& strFieldName);

	//! \brief 已知字段为byte类型，根据字段序号设置字段值
	//! \param nFieldIndex 字段序号[in]。
	//! \param bValue 字段值 [in]。
	//! \return 是否设置成功，成功返回TRUE，失败返回FALSE。
	//##ModelId=4820304F039E
	virtual ENGINE_APIF UGbool SetByte(UGint nFieldIndex, UGbyte bValue = 0); 

	//! \brief 已知字段为byte类型，根据字段名设置字段值
	//! \param strFieldName 字段名[in]。
	//! \param bValue 字段值 [in]。
	//! \return 是否设置成功，成功返回TRUE，失败返回FALSE。
	//##ModelId=4820304F03AC
	virtual ENGINE_APIF UGbool SetByte(const UGString& strFieldName, UGbyte bValue = 0);
	
	//! \brief 已知字段为byte类型,根据字段序号获取字段值。
	//! \param nFieldIndex 字段序号[in]。	
	//! \return 获取的字段值。
	//##ModelId=4820304F03B0
	virtual ENGINE_APIF UGbyte GetByte(UGint nFieldIndex);
	
	//! \brief 已知字段为byte类型,根据字段名获取字段值。
	//! \param strFieldName 字段名[in]。
	//! \return 获取的字段值。
	//##ModelId=4820304F03BB
	virtual ENGINE_APIF UGbyte GetByte(const UGString& strFieldName);

	//! \brief 已知字段为Short类型，根据字段序号设置字段值
	//! \param nFieldIndex 字段序号[in]。
	//! \param nValue 字段值 [in]。
	//! \return 是否设置成功，成功返回TRUE，失败返回FALSE。
	//##ModelId=4820304F03BE
	virtual ENGINE_APIF UGbool SetINT16(UGint nFieldIndex, UGshort nValue=0);

	//! \brief 已知字段为Short类型，根据字段名设置字段值
	//! \param strFieldName 字段名[in]。
	//! \param nValue 字段值 [in]。
	//! \return 是否设置成功，成功返回TRUE，失败返回FALSE。
	//##ModelId=4820304F03C9
	virtual ENGINE_APIF UGbool SetINT16(const UGString& strFieldName, UGshort nValue=0);

	//! \brief 已知字段为Short类型,根据字段序号获取字段值。
	//! \param nFieldIndex 字段序号[in]。
	//! \return 获取的字段值。
	//##ModelId=4820304F03CD
	virtual ENGINE_APIF UGshort GetINT16(UGint nFieldIndex);

	//! \brief 已知字段为Short类型,根据字段名获取字段值。
	//! \param strFieldName 字段名[in]。
	//! \return 获取的字段值。
	//##ModelId=4820304F03D8
	virtual ENGINE_APIF UGshort GetINT16(const UGString& strFieldName);
	
	//! \brief 已知字段为int类型，根据字段序号设置字段值
	//! \param nFieldIndex 字段序号[in]。
	//! \param nValue 字段值 [in]。
	//! \return 是否设置成功，成功返回TRUE，失败返回FALSE。
	//##ModelId=4820304F03DB
	virtual ENGINE_APIF UGbool SetINT32(UGint nFieldIndex, UGint nValue=0);
	
	//! \brief 已知字段为int类型，根据字段名设置字段值
	//! \param strFieldName 字段名[in]。
	//! \param nValue 字段值 [in]。
	//! \return 是否设置成功，成功返回TRUE，失败返回FALSE。
	//##ModelId=482030500000
	virtual ENGINE_APIF UGbool SetINT32(const UGString& strFieldName, UGint nValue=0);

	//! \brief 已知字段为Int类型,根据字段序号获取字段值。
	//! \param nFieldIndex 字段序号[in]。
	//! \return 获取的字段值。
	//##ModelId=482030500004
	virtual ENGINE_APIF UGint GetINT32(UGint nFieldIndex);
	
	//! \brief 已知字段为Int类型,根据字段名获取字段值。
	//! \param strFieldName 字段名[in]。
	//! \return 获取的字段值。
	//##ModelId=482030500007
	virtual ENGINE_APIF UGint GetINT32(const UGString& strFieldName);

	//! \brief 已知字段为Long类型，根据字段序号设置字段值
	//! \param nFieldIndex 字段序号[in]。
	//! \param lValue 字段值 [in]。
	//! \return 是否设置成功，成功返回TRUE，失败返回FALSE。
	//##ModelId=48203050000F
	virtual ENGINE_APIF UGbool SetINT64(UGint nFieldIndex, UGlong lValue=0);
	
	//! \brief 已知字段为Long类型，根据字段名设置字段值
	//! \param strFieldName 字段名[in]。
	//! \param lValue 字段值 [in]。
	//! \return 是否设置成功，成功返回TRUE，失败返回FALSE。
	//##ModelId=482030500013
	virtual ENGINE_APIF UGbool SetINT64(const UGString& strFieldName, UGlong lValue=0);

	//! \brief 已知字段为Long类型,根据字段序号获取字段值。
	//! \param nFieldIndex 字段序号[in]。
	//! \return 获取的字段值。
	//##ModelId=48203050001F
	virtual ENGINE_APIF UGlong GetINT64(UGint nFieldIndex);
	
	//! \brief 已知字段为Long类型,根据字段名获取字段值。
	//! \param strFieldName 字段名[in]。
	//! \return 获取的字段值。
	//##ModelId=482030500022
	virtual ENGINE_APIF UGlong GetINT64(const UGString& strFieldName);

	//! \brief 已知字段为Float类型，根据字段序号设置字段值
	//! \param nFieldIndex 字段序号[in]。
	//! \param dbalue 字段值 [in]。
	//! \return 是否设置成功，成功返回TRUE，失败返回FALSE。
	//##ModelId=482030500025
	virtual ENGINE_APIF UGbool SetFloat(UGint nFieldIndex, UGfloat dbalue=0);
	
	//! \brief 已知字段为Float类型，根据字段名设置字段值
	//! \param strFieldName 字段名[in]。
	//! \param dbValue 字段值 [in]。
	//! \return 是否设置成功，成功返回TRUE，失败返回FALSE。
	//##ModelId=48203050002E
	virtual ENGINE_APIF UGbool SetFloat(const UGString& strFieldName, UGfloat dbValue=0);

	//! \brief 已知字段为Float类型,根据字段序号获取字段值。
	//! \param nFieldIndex 字段序号[in]。
	//! \return 获取的字段值。
	//##ModelId=482030500032
	virtual ENGINE_APIF UGfloat GetFloat(UGint nFieldIndex);
	
	//! \brief 已知字段为Float类型,根据字段名获取字段值。
	//! \param strFieldName 字段名[in]。
	//! \return 获取的字段值。
	//##ModelId=482030500035
	virtual ENGINE_APIF UGfloat GetFloat(const UGString& strFieldName);

	//! \brief 已知字段为Double类型，根据字段序号设置字段值
	//! \param nFieldIndex 字段序号[in]。
	//! \param dbValue 字段值 [in]。
	//! \return 是否设置成功，成功返回TRUE，失败返回FALSE。
	//##ModelId=48203050003E
	virtual ENGINE_APIF UGbool SetDouble(UGint nFieldIndex, UGdouble dbValue=0);
	
	//! \brief 已知字段为Double类型，根据字段名设置字段值
	//! \param strFieldName 字段名[in]。
	//! \param dbValue 字段值 [in]。
	//! \return 是否设置成功，成功返回TRUE，失败返回FALSE。
	//##ModelId=482030500042
	virtual ENGINE_APIF UGbool SetDouble(const UGString& strFieldName, UGdouble dbValue=0);

	//! \brief 已知字段为Double类型,根据字段序号获取字段值。
	//! \param nFieldIndex 字段序号[in]。
	//! \return 获取的字段值。
	//##ModelId=482030500046
	virtual ENGINE_APIF UGdouble GetDouble(UGint nFieldIndex);
	
	//! \brief 已知字段为Double类型,根据字段名获取字段值。
	//! \param strFieldName 字段名[in]。
	//! \return 获取的字段值。
	//##ModelId=48203050004E
	virtual ENGINE_APIF UGdouble GetDouble(const UGString& strFieldName);

	//! \brief 已知字段为Time类型，根据字段序号设置字段值
	//! \param nFieldIndex 字段序号[in]。
	//! \param tmValue 字段值 [in]。
	//! \return 是否设置成功，成功返回TRUE，失败返回FALSE。
	//##ModelId=482030500051
	virtual ENGINE_APIF UGbool SetTime(UGint nFieldIndex, UGTime tmValue);
	
	//! \brief 已知字段为Time类型，根据字段名设置字段值
	//! \param strFieldName 字段名[in]。
	//! \param tmValue 字段值 [in]。
	//! \return 是否设置成功，成功返回TRUE，失败返回FALSE。
	//##ModelId=482030500055
	virtual ENGINE_APIF UGbool SetTime(const UGString& strFieldName, UGTime tmValue);

	//! \brief 已知字段为Time类型,根据字段序号获取字段值。
	//! \param nFieldIndex 字段序号[in]。
	//! \return 获取的字段值。
	//##ModelId=48203050005D
	virtual ENGINE_APIF UGTime GetTime(UGint nFieldIndex);
	
	//! \brief 已知字段为Time类型,根据字段名获取字段值。
	//! \param strFieldName 字段名[in]。
	//! \return 获取的字段值。
	//##ModelId=482030500060
	virtual ENGINE_APIF UGTime GetTime(const UGString& strFieldName);

	//! \brief 已知字段为Date类型，根据字段序号设置字段值
	//! \param nFieldIndex 字段序号[in]。
	//! \param tmValue 字段值 [in]。
	//! \return 是否设置成功，成功返回TRUE，失败返回FALSE。
	//##ModelId=482030500063
	virtual ENGINE_APIF UGbool SetDate(UGint nFieldIndex, UGTime tmValue);
	
	//! \brief 已知字段为Date类型，根据字段名设置字段值
	//! \param strFieldName 字段名[in]。
	//! \param tmValue 字段值 [in]。
	//! \return 是否设置成功，成功返回TRUE，失败返回FALSE。
	//##ModelId=482030500067
	virtual ENGINE_APIF UGbool SetDate(const UGString& strFieldName, UGTime tmValue);

	//! \brief 已知字段为Date类型,根据字段序号获取字段值。
	//! \param nFieldIndex 字段序号[in]。
	//! \return 获取的字段值。
	//##ModelId=48203050006F
	virtual ENGINE_APIF UGTime GetDate(UGint nFieldIndex);
	
	//! \brief 已知字段为Date类型,根据字段名获取字段值。
	//! \param strFieldName 字段名[in]。
	//! \return 获取的字段值。
	//##ModelId=482030500072
	virtual ENGINE_APIF UGTime GetDate(const UGString& strFieldName);

	//! \brief 已知字段为TimeStamp类型，根据字段序号设置字段值
	//! \param nFieldIndex 字段序号[in]。
	//! \param tmValue 字段值 [in]。
	//! \return 是否设置成功，成功返回TRUE，失败返回FALSE。
	//##ModelId=482030500075
	virtual ENGINE_APIF UGbool SetTimeStamp(UGint nFieldIndex, UGTime tmValue);
	
	//! \brief 已知字段为TimeStamp类型，根据字段名设置字段值
	//! \param strFieldName 字段名[in]。
	//! \param tmValue 字段值 [in]。
	//! \return 是否设置成功，成功返回TRUE，失败返回FALSE。
	//##ModelId=48203050007D
	virtual ENGINE_APIF UGbool SetTimeStamp(const UGString& strFieldName, UGTime tmValue);

	//! \brief 已知字段为TimeStamp类型,根据字段序号获取字段值。
	//! \param nFieldIndex 字段序号[in]。
	//! \return 获取的字段值。
	//##ModelId=482030500081
	virtual ENGINE_APIF UGTime GetTimeStamp(UGint nFieldIndex);
	
	//! \brief 已知字段为TimeStamp类型,根据字段名获取字段值。
	//! \param strFieldName 字段名[in]。
	//! \return 获取的字段值。
	//##ModelId=482030500084
	virtual ENGINE_APIF UGTime GetTimeStamp(const UGString& strFieldName);

	//! \brief 已知字段为Binary类型，根据字段序号设置字段值
	//! \param nFieldIndex 字段序号[in]。
	//! \param pValue 字段值 [in]。
	//! \param nLength pValue的长度 [in]。
	//! \return 是否设置成功，成功返回TRUE，失败返回FALSE。
	//##ModelId=482030500087
	virtual ENGINE_APIF UGbool SetBinary(UGint nFieldIndex, UGbyte *pValue, UGint nLength);
	
	//! \brief 已知字段为Binary类型，根据字段名设置字段值
	//! \param strFieldName 字段名[in]。
	//! \param pValue 字段值 [in]。
	//! \param nLength pValue的长度 [in]。
	//! \return 是否设置成功，成功返回TRUE，失败返回FALSE。
	//##ModelId=48203050008E
	virtual ENGINE_APIF UGbool SetBinary(const UGString& strFieldName, UGbyte *pValue, UGint nLength);

	//! \brief 已知字段为Binary类型,根据字段序号获取字段值。
	//! \param nFieldIndex 字段序号[in]。
	//! \param nLength 二进制字段的长度[out]。
	//! \return 获取的二进制字段指针。
	//##ModelId=482030500093
	virtual ENGINE_APIF UGbyte* GetBinary(UGint nFieldIndex, UGint& nLength);
	
	//! \brief 已知字段为Short类型,根据字段名获取字段值。
	//! \param strFieldName 字段名[in]。
	//! \param nLength 二进制字段的长度[out]。
	//! \return 获取的二进制字段指针。
	//##ModelId=482030500097
	virtual ENGINE_APIF UGbyte* GetBinary(const UGString& strFieldName, UGint& nLength);

	//! \brief 已知字段为String类型，根据字段序号设置字段值
	//! \param nFieldIndex 字段序号[in]。
	//! \param strValue 字段值 [in]。
	//! \return 是否设置成功，成功返回TRUE，失败返回FALSE。
	//##ModelId=48203050009D
	virtual ENGINE_APIF UGbool SetString(UGint nFieldIndex, UGString strValue);
	
	//! \brief 已知字段为String类型，根据字段名设置字段值
	//! \param strFieldName 字段名[in]。
	//! \param strValue 字段值 [in]。
	//! \return 是否设置成功，成功返回TRUE，失败返回FALSE。
	//##ModelId=4820305000A1
	virtual ENGINE_APIF UGbool SetString(const UGString& strFieldName, UGString strValue);

	//! \brief 已知字段为String类型,根据字段序号获取字段值。
	//! \param nFieldIndex 字段序号[in]。
	//! \return 获取的字段值。
	//##ModelId=4820305000A5
	virtual ENGINE_APIF UGString GetString(UGint nFieldIndex);
	
	//! \brief 已知字段为String类型,根据字段名获取字段值。
	//! \param strFieldName 字段名[in]。
	//! \return 获取的字段值。
	//##ModelId=4820305000A8
	virtual ENGINE_APIF UGString GetString(const UGString& strFieldName);

	//! \brief 在记录集中再次查询,查找符合条件的第一条记录
	//##ModelId=4820305000AC
	virtual ENGINE_APIF UGbool FindFirst(const UGString& strFilter);
	
	//! \brief 在记录集中再次查询,查找符合条件的最后一条记录
	//##ModelId=4820305000AF
	virtual ENGINE_APIF UGbool FindLast(const UGString& strFilter);

	//! \brief 在记录集中再次查询,查找符合条件的下一条记录
	//##ModelId=4820305000B2
	virtual ENGINE_APIF UGbool FindNext(const UGString& strFilter);

	//! \brief 在记录集中再次查询,查找符合条件的上一条记录
	//##ModelId=4820305000B5
	virtual ENGINE_APIF UGbool FindPrev(const UGString& strFilter);

	//! \brief 给定相应的数,向前或向后移动记录指针
	//##ModelId=4820305000B8
	virtual ENGINE_APIF UGbool Move(UGint nRows);

	//! \brief 移动记录指针到最前
	//##ModelId=4820305000BC
	virtual ENGINE_APIF UGbool MoveFirst();

	//! \brief 移动记录指针到最后
	//##ModelId=4820305000BE
	virtual ENGINE_APIF UGbool MoveLast();

	//! \brief 向下移动一位记录指针
	//##ModelId=4820305000C0
	virtual ENGINE_APIF UGbool MoveNext();

	//! \brief 向上移动一位记录指针
	//##ModelId=4820305000C2
	virtual ENGINE_APIF UGbool MovePrev();

	//! \brief 移动记录指针到指定位置
	//##ModelId=4820305000C4
	virtual ENGINE_APIF UGbool MoveTo(UGint nRow);

	//! \brief 获取记录个数
	//##ModelId=4820305000C7
	virtual ENGINE_APIF UGint GetRecordCount();

	//! \brief 收集所有字段的信息
	//##ModelId=4820305000C9
	virtual ENGINE_APIF UGbool GetFieldInfos(UGFieldInfos& fieldInfos);
	
	//! \brief 通过字段名获取字段信息
	//##ModelId=4820305000CD
	virtual ENGINE_APIF UGbool GetFieldInfo(const UGString& strName,UGFieldInfo& fieldInfo);
	
	//! \brief 通过索引取字段信息
	//##ModelId=4820305000D1
	virtual ENGINE_APIF UGbool GetFieldInfo(UGint nIndex,UGFieldInfo& fieldInfo);
	
	//! \brief 获取字段个数
	//##ModelId=4820305000D5
	virtual ENGINE_APIF UGint GetFieldCount();

public:

	//! \brief 特殊的外键查询
	//##ModelId=4820305000D7
	virtual ENGINE_APIF UGbool GetForeignKeysVal(UGArray<UGString> &aryForeignKeys,UGArray<UGVariant> &aryVal);
	//##ModelId=4820305000DB
	//nIndex 主要用于保存当前的特殊的外键位置
	virtual ENGINE_APIF UGbool FetchForeignKeysVal(UGArray<UGVariant> &aryVal,UGint nIndex);

	static ENGINE_APIF UGbool IsFieldValueValid(const UGString& v, UGFieldInfo::FieldType t);
	static ENGINE_APIF UGbool IsFieldValueValid(const UGVariant& v, UGFieldInfo::FieldType t);
	static ENGINE_APIF UGbool StringIsInteger( const UGString& str );

	UGFieldInfos m_FieldInfos;

#if !defined SYMBIAN60 && !defined  OS_ANDROID && !defined (IOS)
public:
	//##ModelId=483BB7070265
	OgdcRecordset* GetOgdcRecordset() const;

	//##ModelId=483BB7070271
	UGbool SetOgdcRecordset(OgdcRecordset* pORecordset);
protected:
	//##ModelId=483BB7070273
	OgdcRecordset* m_pOgdcRecordset;
#endif
};

}

#endif // !defined(AFX_UGTABLERECORDSET_H__7C95DC17_F28F_441D_A6C8_4AEB7AC45601__INCLUDED_)


