// UGTextTypeset.h: interface for the UGTextTypeset class.
//
//////////////////////////////////////////////////////////////////////////
//                    _   _   ____   ____                    
//   Project         | | | | / ___) / ___)                   
//                   | | | || | __ | |                       
//                   | |_| || |_\ || \___                    
//                    \____/ \____| \ ___)     6.0           
//                                                           
//!  \file UGTextTypeset.h
//!  \brief 有些国家的文字渲染需要一定的排版规则，比如阿拉伯语言需要自右至左及连写等等复杂规则
//!  \details UGTextTypeset.h和cpp文件即为解决多语言文字渲染规则的问题
//!  \author wangxh 2012.04.25
//!  \attention 
//!   Copyright (c) 1996-2012 SuperMap Software Co., Ltd. <br> 
//!   All Rights Reserved.
//!  \version 6.0
//////////////////////////////////////////////////////////////////////////

#if !defined(AFX_UGTEXTTYPESET_H__E87F3D39_C520_427D_9F11_72CB26885C13__INCLUDED_)
#define AFX_UGTEXTTYPESET_H__E87F3D39_C520_427D_9F11_72CB26885C13__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Stream/ugdefs.h"
#include "Base/OgdcArray.h"

#ifdef _UGUNICODE
#include "Toolkit/UGStringEx.h"
#define UGStringW UGString
#else
#include "Toolkit/UGStringW.h"
#endif

namespace UGC 
{
	//定义需要处理的多国语言，若要添加新语言处理，首先需要在此定义一个新语言符号
	//在下面添加一个范围
	enum UGMultiLanguageType
	{
		ARABIC_TYPE =0,					//阿拉伯语
		ENGLISH_TYPE =1,				//英语
		CHINESE_TYPE =2,				//中文
		JAPANESE_TYPE =3,			//日语
		/*
			中间添加其它语言
		*/
		UNKNOWN_TYPE =0xFFFF
	};

	//定义每种语言的Unicode范围
	//规则：
	//第一个字符用来表示跟随的范围属于哪个枚举，例如阿拉伯语的三个范围的标志都为0
	//0x0600~0x06FF:阿拉伯基本字符
	//0xFB50~0xFDFF:阿拉伯表达形式A
	//0xFE70~0xFEFF:阿拉伯表达形式B
	const UGwchar MultiLanguageUnicodeRange[] =
	{
		0x0000,0x0600,0x06FF,0x0000,0xFB50,0xFDFF,0x0000,0xFE70,0xFEFF,	//阿拉伯范围
		0x0001,0x0000,0x007F,											//英语范围
		0x0002,0x4E00,0x9FA5,											//汉字范围
		0x0003,0x3040,0x309F,0x0003,0x30A0,0x30FF,0x0003,0x31F0,0x31FF,	//日语假名范围
	};

	//阿拉伯语Unicode码连写转换表 Arabic Presentation Form-B, first, last, middle, alone
	/*
	规则1。
	阿拉伯文变形:
	根据上面分法，分成first，last，middle，alone，并根据判断是否是词的前连（前面字符在集合1中），后连（后面字符在集合2中），中间（即前后连，前面字符在集合1中，后面字符在集合2中）或单独一个词，进行变形。
	据分析，给出变形的数组:分别对应上面的情况。对于其它不在数组中的，其变形和自身相同。
	*/
	const UGwchar Arbic_Position[][4]=
	{
		{ 0xfe80, 0xfe80, 0xfe80, 0xfe80},    // 0x621
		{ 0xfe82, 0xfe81, 0xfe82, 0xfe81},
		{ 0xfe84, 0xfe83, 0xfe84, 0xfe83},
		{ 0xfe86, 0xfe85, 0xfe86, 0xfe85},
		{ 0xfe88, 0xfe87, 0xfe88, 0xfe87},
		{ 0xfe8a, 0xfe8b, 0xfe8c, 0xfe89},
		{ 0xfe8e, 0xfe8d, 0xfe8e, 0xfe8d},
		{ 0xfe90, 0xfe91, 0xfe92, 0xfe8f},   // 0x628
		{ 0xfe94, 0xfe93, 0xfe93, 0xfe93},
		{ 0xfe96, 0xfe97, 0xfe98, 0xfe95},   // 0x62A
		{ 0xfe9a, 0xfe9b, 0xfe9c, 0xfe99},
		{ 0xfe9e, 0xfe9f, 0xfea0, 0xfe9d},
		{ 0xfea2, 0xfea3, 0xfea4, 0xfea1},
		{ 0xfea6, 0xfea7, 0xfea8, 0xfea5},
		{ 0xfeaa, 0xfea9, 0xfeaa, 0xfea9},
		{ 0xfeac, 0xfeab, 0xfeac, 0xfeab},   // 0x630  
		{ 0xfeae, 0xfead, 0xfeae, 0xfead},
		{ 0xfeb0, 0xfeaf, 0xfeb0, 0xfeaf},
		{ 0xfeb2, 0xfeb3, 0xfeb4, 0xfeb1},
		{ 0xfeb6, 0xfeb7, 0xfeb8, 0xfeb5},
		{ 0xfeba, 0xfebb, 0xfebc, 0xfeb9},
		{ 0xfebe, 0xfebf, 0xfec0, 0xfebd},
		{ 0xfec2, 0xfec3, 0xfec4, 0xfec1},
		{ 0xfec6, 0xfec7, 0xfec8, 0xfec5},  // 0x638
		{ 0xfeca, 0xfecb, 0xfecc, 0xfec9},
		{ 0xfece, 0xfecf, 0xfed0, 0xfecd},  //0x63A
		{ 0x63b, 0x63b, 0x63b, 0x63b},
		{ 0x63c, 0x63c, 0x63c, 0x63c},
		{ 0x63d, 0x63d, 0x63d, 0x63d},
		{ 0x63e, 0x63e, 0x63e, 0x63e},
		{ 0x63f, 0x63f, 0x63f, 0x63f},
		{ 0x640, 0x640, 0x640, 0x640},   // 0x640
		{ 0xfed2, 0xfed3, 0xfed4, 0xfed1},
		{ 0xfed6, 0xfed7, 0xfed8, 0xfed5},
		{ 0xfeda, 0xfedb, 0xfedc, 0xfed9},
		{ 0xfede, 0xfedf, 0xfee0, 0xfedd},
		{ 0xfee2, 0xfee3, 0xfee4, 0xfee1},
		{ 0xfee6, 0xfee7, 0xfee8, 0xfee5},
		{ 0xfeea, 0xfeeb, 0xfeec, 0xfee9},
		{ 0xfeee, 0xfeed, 0xfeee, 0xfeed},   // 0x648
		{ 0xfef0, 0xfeef, 0xfef0, 0xfeef},
		{0xfef2, 0xfef3, 0xfef4, 0xfef1},   // 0x64A
	};


	/*//Arabic Find Table1
	判断是否是连接前面的，采用判断该字符前一个字符的判定方法，方法是，
	看前一个字符是否在集合set1中。如果在，则是有连接前面的。集合1如下:
	*/
	const UGwchar theSet1[27]={
		0x62c, 0x62d, 0x62e, 0x647, 0x639, 0x63a, 0x641, 0x642,
		0x62b, 0x635, 0x636, 0x637, 0x643, 0x645, 0x646, 0x62a,
		0x644, 0x628, 0x64a, 0x633, 0x634, 0x638, 0x626,0x6af,0x6a9,0x686,0x67e};

	/*	//Arabic Find Table2
	判断是否是连接后面的，采用判断该字符后一个字符的判定方法，方法是，
	看后一个字符是否在集合set2中。如果在，则是有连接后面的。集合2如下:
	*/
	const UGwchar theSet2[40]={
		0x62c,0x62d, 0x62e, 0x647, 0x639, 0x63a, 0x641, 0x642,
		0x62b, 0x635, 0x636, 0x637, 0x643, 0x645, 0x646, 0x62a,
		0x644, 0x628, 0x64a, 0x633, 0x634, 0x638, 0x626,0x6af,0x6a9,0x686,0x67e,
		0x627, 0x623, 0x625, 0x622, 0x62f, 0x630, 0x631, 0x632,
		0x648, 0x624, 0x629, 0x649,0x698};

	//文字渲染排版转换器基类
	class TOOLKIT_API UGTextTypesetMultiLanguage
	{
	public:
		virtual void Convert(const UGStringW& strOriginal,UGStringW &strAfterConversion) =0;
		virtual ~UGTextTypesetMultiLanguage(){}
	};


	//阿拉伯文排版转换器类
	class TOOLKIT_API UGTextTypesetArabic : public UGTextTypesetMultiLanguage
	{
	public:
		//构造：初始化查找表
		UGTextTypesetArabic();
		//析构：删除查找表
		~UGTextTypesetArabic();
		//转换函数
		void Convert(const UGStringW& strOriginal,UGStringW &strAfterConversion);

	private:
		//查找表1
		std::vector<UGwchar> m_vecArbicFindTable1;
		//查找表2
		std::vector<UGwchar> m_vecArbicFindTable2;

		//转换一个阿拉伯单词
		inline void ConvertOneWord(const UGStringW& strOriginal,UGStringW &strAfterConversion);

		//判断是否是阿拉伯字母
		inline UGbool IsArabicChar(UGwchar nChar);

		/*		//处理连字符
		阿拉伯文连字符规则:
		连字符是以0x644开头，后面跟的是0x622，0x623，0x625，0x627，并根据情况取下面的字符数组0或1，如果0x644前一个字符是在集合1（同上面的集合1）中间，那么取数组1，否则取数组0。
		数组如下:
		static U16 arabic_specs[][2]=
		{
		{0xFEF5，0xFEF6}，
		{0xFEF7，0xFEF8}，
		{0xFEF9，0xFEFA}，
		{0xFEFB，0xFEFC}，
		};

		例1： 0x064A， 0x0644， 0x0622。。。
		0x064A 的后面一个字符 0x0644 在集合2中，根据编码规则1得出它是后连字符（last），故转换成: 0xFEF3.  
		而0x064A在集合1 中，故用 0xFEF6 替代 0x0644 0x0622 这两个编码。     

		例2： 0x0632， 0x0644， 0x0622。。。
		0x0632 的后面一个字符 0x0644 在集合2中，根据编码规则1得出它是后连字符（last）， 故转换成: 0xFEAF.  
		而 0x0632 不在集合1 中，故用 0xFEF5 替代 0x0644 0x0622 这两个编码。  
		*/
		inline UGbool DealWithLinkChar(UGwchar nCharPre,UGwchar& nCur,UGwchar nNext,UGbool &bFindResult);

		//在表里查找
		inline UGbool FindInTable(std::vector<UGwchar> &vec,UGwchar T);
	};

	//对外接口,通过调用Convert函数实现文本排版转换
	class TOOLKIT_API UGTextTypeset
	{
		//设置UGTextTypesetArabic为友元
		friend class UGTextTypesetArabic;

	public:
		//构造函数
		UGTextTypeset();
		//析构:需删除转换器字典
		~UGTextTypeset();

		//str1:转换前版本
		//str2:转换后版本
		static void Convert(const UGStringW& strOriginal,UGStringW &strAfterConversion);

		//获取指定编码的单字属于哪个文字区间
		static UGMultiLanguageType GetWhichLanguage(UGwchar nwChar);

	protected:

		//查找转换器并转换，若没找到合适的转换器则返回str1
		static inline void DoConvert(UGMultiLanguageType nType,const UGStringW&strOriginal,UGStringW &strAfterConversion);

		//根据语言类型，返回找到的可用转换器
		static inline UGTextTypesetMultiLanguage *CreateConverter(UGMultiLanguageType nType);

		//转换器字典，若未找到，则新建转换器，并放进来
		static UGDict<UGMultiLanguageType ,UGTextTypesetMultiLanguage*> m_dictLangTypeset;

	private:
		//把两个String对象连起来。。-_-...stringw都没提供+号。。
		static void StringAdd(UGStringW &strDest,const UGStringW &strEx);
	};

}

#endif // !defined(AFX_UGTEXTTYPESET_H__E87F3D39_C520_427D_9F11_72CB26885C13__INCLUDED_)
