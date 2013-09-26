
#ifndef UGDOMAIN_H
#define UGDOMAIN_H

#include "Engine/UGEngDefs.h"

namespace UGC 
{
	class UGDataset;
	//! \brief	值域基类
	class ENGINE_API UGDomainBase
	{
	public:

		virtual ~UGDomainBase(){}

		//! \brief	检查数据值有效性
		//	\param	val[IN]	要检查的值	
		virtual UGbool Check(const UGVariant &val) = 0;

		//! \brief	检查指定的字段类型，是否是该域当前所支持关联的字段类型
		//	\param	fieldtype[IN] 要检查的字段类型
		virtual UGbool CheckFieldType(UGFieldInfo::FieldType fieldtype) = 0;

		//!	\brief	获取域的字段类型
		virtual UGFieldInfo::FieldType GetFieldType() { return UGFieldInfo::UnKnown; };
		virtual UGFieldInfo::FieldType GetFieldType() const { return UGFieldInfo::UnKnown; };

	public:
		//! \brief	目前域类型支持范围和代码两种，规则表达式类型留待以后扩展
		//			扩展两种类型RangeNot和CodeNot，它们是Range和Code的检查结果取反
		enum DomainType { Range = 1, Code = 2, RangeNot = 3, CodeNot = 4};

	
		//! \brief	获取域的类型
		DomainType GetDomainType() { return m_Type; }
		DomainType GetDomainType() const { return m_Type; }

		//! \brief	构造
		UGDomainBase(UGuint nID, const UGString &name, DomainType type):m_nID(nID), m_strName(name), m_Type(type){}

		UGDomainBase(UGuint nID, const UGString &name, const UGString &desc, DomainType type):m_nID(nID), m_strName(name), \
			m_strDesc(desc), m_Type(type){}

		UGDomainBase():m_nID(0), m_Type(Range){}

	public:
		//! \brief	域的ID
		UGuint m_nID;

		//! \brief	域的名称
		UGString m_strName;

		//! \brief	域的描述信息
		UGString m_strDesc;

	protected:
		//! \brief	域的类型（该属性不能被修改，创建时必须指定）
		DomainType m_Type;



	};


	//! \brief	定义区间
	class ENGINE_API UGRangeInfo
	{
	public:

		//! \brief	
		UGRangeInfo() {}

		virtual~ UGRangeInfo(){}


		//! \brief	定义四种区间类型，对应的形式分别为：[ ]，( ]，[ )，（）
		enum RangeType { CloseClose = 1, OpenClose = 2, CloseOpen = 3, OpenOpen = 4 };

		//! \brief	获取区间的字段类型
		UGFieldInfo::FieldType GetFieldType() { return m_FieldType; }
		UGFieldInfo::FieldType GetFieldType() const { return m_FieldType; }

		void SetFieldType(UGFieldInfo::FieldType fieldType){m_FieldType = fieldType;}

		void SetType(RangeType type ){m_Type = type;}

		//! \brief	检查指定的值是否在该区间范围中
		//	\param	val[IN]	要检查的值
		UGbool IsIn(const UGVariant &val);

		//! \brief	获取上下限
		const UGVariant& GetMinValue() { return m_MinValue; }
		const UGVariant& GetMinValue() const { return m_MinValue; }
		const UGVariant& GetMaxValue() { return m_MaxValue; }
		const UGVariant& GetMaxValue() const { return m_MaxValue; }

		void SetMinValue(UGVariant left){m_MinValue=left;}
		void SetMaxValue(UGVariant right){m_MaxValue=right;}

		void SetRange(UGVariant left,UGVariant right){m_MinValue = left; m_MaxValue = right;}

	public:
		//! \brief	拷贝构造
		UGRangeInfo(const UGRangeInfo &interval):m_Type(interval.m_Type), m_MinValue(interval.m_MinValue), \
			m_MaxValue(interval.m_MaxValue), m_FieldType(interval.m_FieldType) {}

		//! \brief	其他构造形式
		UGRangeInfo(UGFieldInfo::FieldType fieldType, UGVariant leftValue, UGVariant rightValue, RangeType type);

	private:

		//! \brief 以下函数是比较某一个值跟指定值的大小关系
		//	\param compare[IN]  要比较的值
		//		   standard[IN] 指定的衡量标准值
		UGbool LessThan(UGint compare, UGint standard) { return compare < standard; }
		UGbool LessThan(UGlong compare, UGlong standard) { return compare < standard; }
		UGbool LessThan(UGdouble compare, UGdouble standard) { return compare < standard; }

		UGbool MoreThan(UGint compare, UGint standard) { return compare > standard; }
		UGbool MoreThan(UGlong compare, UGlong standard) { return compare > standard; }
		UGbool MoreThan(UGdouble compare, UGdouble standard) { return compare > standard; }

		UGbool Equal(UGdouble compare, UGdouble standard) { return UGEQUAL(compare, standard); }

		UGbool LessEqual(UGint compare, UGint standard) { return !MoreThan(compare, standard); }
		UGbool LessEqual(UGlong compare, UGlong standard) { return !MoreThan(compare, standard); }
		UGbool LessEqual(UGdouble compare, UGdouble standard) { return Equal(compare, standard) || LessThan(compare, standard); }

		UGbool MoreEqual(UGint compare, UGint standard) { return !LessThan(compare, standard); }
		UGbool MoreEqual(UGlong compare, UGlong standard) { return !LessThan(compare, standard); }
		UGbool MoreEqual(UGdouble compare, UGdouble standard) { return Equal(compare, standard) || MoreThan(compare, standard); }

	public:
		//! \brief	区间类型
		RangeType m_Type;

	private:
		//! \brief	上限
		UGVariant m_MinValue;

		//! \brief	下限
		UGVariant m_MaxValue;

		//! \brief	区间的字段类型，日期型统一用TimeStamp类型处理，因为组件层实际只有datetime类型
		UGFieldInfo::FieldType m_FieldType;
	};


	//! \brief	范围域子类
	class ENGINE_API UGRangeDomain:public UGDomainBase
	{
	public:
		UGRangeDomain() {m_Type = Range;m_FieldType = UGFieldInfo::UnKnown;}
		
		virtual ~UGRangeDomain(){}

		//! \brief	检查数据值有效性
		//	\param	val[IN]	要检查的值
		virtual UGbool Check(const UGVariant &val);

		//! \brief	检查指定的字段类型，是否是该域当前所支持关联的字段类型
		//	\param	fieldtype[IN] 要检查的字段类型
		virtual UGbool CheckFieldType(UGFieldInfo::FieldType fieldtype);

		//! \brief	获取域的字段类型
		virtual UGFieldInfo::FieldType GetFieldType() { return m_FieldType; }
		virtual UGFieldInfo::FieldType GetFieldType() const { return m_FieldType; }

	public:
		//!	\brief	构造
		UGRangeDomain(UGuint nID, const UGString& name, UGFieldInfo::FieldType fieldtype, const UGArray<UGRangeInfo> &rangeinfos):\
			UGDomainBase(nID, name, Range), m_FieldType(fieldtype)
		{
			Append(rangeinfos);
		}

		UGRangeDomain(UGuint nID, const UGString &name, const UGString &desc,\
			UGFieldInfo::FieldType fieldtype, const UGArray<UGRangeInfo> &rangeinfos):\
			UGDomainBase(nID, name, desc, Range), m_FieldType(fieldtype)
		{
			Append(rangeinfos);
		}

		//! \brief	拷贝构造
		UGRangeDomain(const UGRangeDomain &RDomain);

	public:
		//!	\brief	将所有的区间内容转换成二进制，以便于存储
		//			格式为：[ 区间个数|区间1的类型|区间1的上限|区间1的下限|...|区间n的类型|区间n的上限|区间n的下限 ]
		//	\param	pResult[OUT]  返回存储二进制数据的堆的指针（外面负责释放）
		//			nSize[OUT]	返回二进制数据的大小
		UGbool ToBinary(void* &pResult, UGint &nSize);

		//! \brief	获取所有区间
		const UGArray<UGRangeInfo>& GetRangeInfos() { return m_RangeInfos; }
		const UGArray<UGRangeInfo>& GetRangeInfos() const { return m_RangeInfos; }

		//! \brief	获取指定位置的区间
		//	\param	nIndex[IN]	指定的位置
		const UGRangeInfo& Get(UGint nIndex);
		const UGRangeInfo& Get(UGint nIndex) const;

		//! \brief	设置或改变指定位置的区间（该接口设计主要是考虑区间和域的字段类型是否能匹配）
		//	\return	类型匹配且设置成功则返回TRUE，反之FALSE
		UGbool Set(UGint nIndex, const UGRangeInfo &rangeinfo);

		//!	\brief	增加一个区间
		UGbool Add(const UGRangeInfo &rangeinfo);

		//!	\brief	增加区间（对于intervals中类型不匹配的区间将会被丢弃掉）
		void Append(const UGArray<UGRangeInfo> &rangeinfos);

		//!	\brief	移除指定位置的区间
		//	\param	nIndex[IN]	指定的位置
		//			nCount[IN]	从指定位置往后移除多少个
		void Remove(UGint nIndex, UGint nCount = 1);

		//!	\brief	移除所有的区间
		void RemoveAll() { m_RangeInfos.RemoveAll(); }

	protected:
		//!	\brief	记录所有的区间，这里规定所有的区间均按照逻辑或的形式组合在一起
		//			作为私有成员是为了保证区间和域的字段类型保持一致，通过前面的接口来设置它
		UGArray<UGRangeInfo> m_RangeInfos;

		//!	\brief	域的字段类型（该属性创建时必须被指定，创建后不允许修改）
		UGFieldInfo::FieldType m_FieldType;
	};


	//! \brief	UGRangeNotDomain是UGRangeDomain的取反
	class ENGINE_API UGRangeNotDomain:public UGRangeDomain
	{
	public:
		//! \brief	检查数据值有效性
		//	\param	val[IN]	要检查的值
		virtual UGbool Check(const UGVariant &val) { return !UGRangeDomain::Check(val); }

		virtual ~UGRangeNotDomain(){}

	public:
		//!	\brief	构造
		UGRangeNotDomain(UGuint nID, const UGString &name, UGFieldInfo::FieldType fieldtype, const UGArray<UGRangeInfo> &intervals);

		UGRangeNotDomain(UGuint nID, const UGString &name, const UGString &desc,\
			UGFieldInfo::FieldType fieldtype, const UGArray<UGRangeInfo> &intervals);

		//! \brief	利用UGRangeDomain来构造
		UGRangeNotDomain(const UGRangeDomain &RDomain);

		//! \brief	拷贝构造
		UGRangeNotDomain(const UGRangeNotDomain &RNotDomain);

	private:
		//! \brief	别妄想了，默认构造是不被允许滴！
		UGRangeNotDomain() {}
	};


	//! \brief	定义代码信息
	class ENGINE_API UGCodeInfo
	{
	public:
		UGCodeInfo(){;}

		virtual ~UGCodeInfo(){}

		//! \brief	获取字段类型
		UGFieldInfo::FieldType GetFieldType() { return m_FieldType; }
		UGFieldInfo::FieldType GetFieldType() const { return m_FieldType; }

		void SetFieldType(UGFieldInfo::FieldType type){m_FieldType = type;}

		void SetDescription(UGString description){m_strDesc = description;}


		//!	\brief	获取代码值
		const UGVariant& GetValue() { return m_Value; }
		const UGVariant& GetValue() const { return m_Value; }

		void SetValue(UGVariant value){m_Value = value;}

	public:
		//!	\brief	构造
		UGCodeInfo(UGFieldInfo::FieldType fieldType,UGVariant value,const UGString &desc);

		//!	\brief	拷贝构造
		UGCodeInfo(const UGCodeInfo &codeinfo):m_Value(codeinfo.m_Value), m_strDesc(codeinfo.m_strDesc), \
			m_FieldType(codeinfo.m_FieldType) {}

	public:
		//! \brief	代码的涵义描述
		UGString m_strDesc;

	private:
		//! \brief	实际代码值
		UGVariant m_Value;

		//! \brief	代码的字段类型
		UGFieldInfo::FieldType m_FieldType;
	};


	//! \brief	代码域子类
	class ENGINE_API UGCodeDomain:public UGDomainBase
	{
	public:
		UGCodeDomain() {m_Type = Code;m_FieldType = UGFieldInfo::UnKnown;}

		virtual ~UGCodeDomain(){}

		//! \brief	检查数据值有效性
		//	\param	val[IN]	要检查的值	
		virtual UGbool Check(const UGVariant &val);

		//! \brief	检查指定的字段类型，是否是该域当前所支持关联的字段类型
		//	\param	fieldtype[IN] 要检查的字段类型
		virtual UGbool CheckFieldType(UGFieldInfo::FieldType fieldtype);

		//! \brief	获取域的字段类型
		virtual UGFieldInfo::FieldType GetFieldType() { return m_FieldType; }
		virtual UGFieldInfo::FieldType GetFieldType() const { return m_FieldType; }

	public:
		//! \brief	构造
		UGCodeDomain(UGuint nID,  const UGString &name, \
			UGFieldInfo::FieldType fieldtype, UGArray<UGCodeInfo> &codeinfos):\
			UGDomainBase(nID, name, Code), m_FieldType(fieldtype)
		{
			Append(codeinfos);
		}

		//! \brief	构造
		UGCodeDomain(UGuint nID, const UGString &name, const UGString &desc,\
			UGFieldInfo::FieldType fieldtype, UGArray<UGCodeInfo> &codeinfos):\
			UGDomainBase(nID, name, desc, Code), m_FieldType(fieldtype)
		{
			Append(codeinfos);
		}

		//!	\brief	拷贝构造
		UGCodeDomain(const UGCodeDomain &CDomain);

	public:
		//!	\brief	将所有的代码信息转换成二进制，以便于存储
		//			格式为：[ 代码个数|代码1的值|代码1的涵义描述|...|代码n的值|代码n的涵义描述 ]
		//	\param	pResult[OUT]  返回存储二进制数据的堆的指针（外面负责释放）
		//			nSize[OUT]	返回二进制数据的大小
		UGbool ToBinary(void* &pResult, UGint &nSize);

		//! \brief	获取域中包含的所有代码信息
		const UGArray<UGCodeInfo>& GetCodeInfos() { return m_CodeInfos; }
		const UGArray<UGCodeInfo>& GetCodeInfos() const { return m_CodeInfos; }

		//!	\brief	获取指定位置的代码信息
		const UGCodeInfo& Get(UGint nIndex);
		const UGCodeInfo& Get(UGint nIndex) const;

		//! \brief	设置或改变指定位置的代码信息（该接口设计主要是考虑代码信息和域的字段类型是否能匹配）
		//	\return	类型匹配且设置成功则返回TRUE，反之FALSE
		UGbool Set(UGint nIndex, const UGCodeInfo &codeinfo);

		//!	\brief	增加一个代码信息
		UGbool Add(const UGCodeInfo &codeinfo);

		//!	\brief	增加代码信息（对于codeinfos中类型不匹配的代码将会被丢弃掉）
		void Append(const UGArray<UGCodeInfo> &codeinfos);

		//!	\brief	移除指定位置的代码信息
		//	\param	nIndex[IN]	指定的位置
		//			nCount[IN]	从指定位置往后移除多少个
		void Remove(UGint nIndex, UGint nCount = 1);

		//!	\brief	移除所有的代码信息
		void RemoveAll() { m_CodeInfos.RemoveAll(); }

	protected:
		//!	\brief	域的字段类型（该属性创建时必须被指定，创建后不允许修改）
		UGFieldInfo::FieldType m_FieldType;

		//!	\brief	记录所有的代码信息
		UGArray<UGCodeInfo> m_CodeInfos;
	};


	//! \brief	UGCodeNotDomain是UGCodeDomain的取反
	class ENGINE_API UGCodeNotDomain:public UGCodeDomain
	{
	public:
		//! \brief	检查数据值有效性
		//	\param	val[IN]	要检查的值	
		virtual UGbool Check(const UGVariant &val) { return !UGCodeDomain::Check(val); }

		virtual ~UGCodeNotDomain(){}

	public:
		//! \brief	构造
		UGCodeNotDomain(UGuint nID, const UGString &name, UGFieldInfo::FieldType fieldtype, const UGArray<UGCodeInfo> &codeinfos);

		UGCodeNotDomain(UGuint nID, const UGString &name, const UGString &desc, \
			 UGFieldInfo::FieldType fieldtype, const UGArray<UGCodeInfo> &codeinfos);

		//!	\brief	利用UGCodeDomain来构造
		UGCodeNotDomain(const UGCodeDomain &CDomain);

		//!	\brief	拷贝构造
		UGCodeNotDomain(const UGCodeNotDomain &CNotDomain);

	private:
		//! \brief	禁掉默认构造
		UGCodeNotDomain() {}
	};


	//!	\brief	定义域到字段的关联
	struct ENGINE_API UGDomainField
	{
		//!	\brief	构造
		UGDomainField(UGuint nDatasetID, const UGString &strFieldName, UGuint nDomainID):m_nDatasetID(nDatasetID), \
			m_strFieldName(strFieldName), m_nDomainID(nDomainID) {}

		UGDomainField():m_nDatasetID(0), m_nDomainID(0) {}

		//!	\brief	数据集的ID
		UGuint m_nDatasetID;

		//!	\brief	字段的名称
		UGString m_strFieldName;

		//!	\brief	域的ID
		UGuint m_nDomainID;
	};

};

#endif