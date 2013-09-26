//$Id: UGStringW.h,v 1.9 2009/11/05 09:36:47 siyh Exp $
//$Author: siyh $
//$Date: 2009/11/05 09:36:47 $
//$Source: /home/cvsroot/UGC60/01_SourceCode/Include/Toolkit/UGStringW.h,v $
//$Revision&
//$Log: UGStringW.h,v $
//Revision 1.9  2009/11/05 09:36:47  siyh
//修改头文件注释
//
//Revision 1.8  2009/05/26 09:17:28  cuiwz
//增加注释
//
//Revision 1.7  2009/05/25 06:25:12  cuiwz
//增加注释
//
//Revision 1.6  2009/05/15 01:53:25  chenzhao
//*** empty log message ***
//
//Revision 1.5  2009/05/15 01:35:02  chenzhao
//*** empty log message ***
//
//Revision 1.4  2008/12/11 07:31:34  cuiwz
//LoadString 改成LoadresString
//
//Revision 1.3  2008/07/18 09:36:37  chengx
//LPCTSTR替换成UGPCTSTR
//
//Revision 1.2  2008/05/28 07:14:15  cuiwz
//增加对UGByteArray的支持
//
//Revision 1.1  2008/04/28 11:40:23  chengx
//增加Toolkit础功能
//
//Revision 1.22  2007/11/01 08:40:01  zengzm
//增加 utf8 字符串类
//
//Revision 1.21  2007/10/29 10:34:04  zengzm
//给UGStringUCS2LE的几个函数增加const类型
//
//Revision 1.20  2007/10/29 09:12:34  liwl
//字符串问题utf_16
//
//Revision 1.19  2007/07/20 08:44:43  xielin
//开放获取内部成员变量的接口
//
//Revision 1.18  2007/07/18 09:53:30  zengzm
//增加==函数,删除几个没用的函数
//
//Revision 1.17  2007/05/10 13:54:43  zengzm
//增加 UGStringU GetLength方法
//
//Revision 1.16  2007/04/19 08:39:48  zengzm
//删除没有用的函数
//
//Revision 1.15  2007/04/07 08:57:50  zengzm
//把复合文档中的UGFile改名为UGFileLogical,避免和Base中的UGFile重名
//
//Revision 1.14  2007/04/07 07:50:23  zengzm
//修改UGStringU,让其可以在linux下编译通过
//
//Revision 1.13  2007/04/07 05:55:03  zengzm
//增加UGStringU类,用于和SFC的数据兼容,以及宽字节字符串存储的统一.
//
//Revision 1.12  2006/12/30 06:04:34  xielin
//增加其他平台的字符串转换函数
//
//Revision 1.11  2005/12/07 02:48:12  caogf
//增加一个拷贝构造
//
//Revision 1.10  2005/06/08 01:49:34  caogf
//no message
//
//Revision 1.9  2005/06/07 08:07:27  caogf
//no message
//
//Revision 1.8  2005/05/31 02:40:26  caogf
//no message
//
//Revision 1.7  2005/05/31 02:28:51  caogf
//no message
//
//Revision 1.6  2005/05/30 05:07:40  chengx
//no message
//
//Revision 1.5  2005/05/27 08:38:58  caogf
//no message
//
//Revision 1.4  2005/05/27 08:31:40  caogf
//no message
//
//Revision 1.3  2005/05/24 07:10:05  jifang
//Modified by jifang.
//append a CR at bottom.
//
//Revision 1.2  2005/05/23 02:53:38  caogf
//no message
//
#ifndef UGSTRINGW_H
#define UGSTRINGW_H

#include "Stream/ugdefs.h"
#include "Stream/UGStream.h"
#include "Toolkit/UGTextCodec.h"
#include "Stream/UGByteArray.h"

namespace UGC {
#ifndef _UGUNICODE
	  //!  \brief Toolkit
class UGStringW;
	  //!  \brief Toolkit
typedef const UGwchar* UGPCTSTRW;
	  //!  \brief Toolkit
typedef UGArray<UGStringW> UGStrWArray;

/* 关于UGC中各个平台字符串使用的说明
1, 对于一般的字符串,采用UGString, 多字节方式(MBCS), 即 中英文等可以混杂在一起
2, 当字符串需要用Unicode方式存取时,为了和SFC保持一致, 采用UGStringU来进行, 然后转化为UGString来使用
3, 如果需要把UGString中混杂的中英文分离开,则采用转化为UGStringW, UGStringW会采用各个平台自定的Unicode编码方式,
   各个平台的编码方式都是不一致的. 因此,不能采用UGStringW来进行存取,事实上,UGStringW 和Stream之间的存取函数
   已经被注释掉了, 避免可能的误用.
*/

//! \brief 宽字节字符串类。
/**
	\remarks 特别需要注意的是: UGStringW内部采用stl的wstring实现,wstring内部用的是wchar_t*,
	而各个平台上wchar_t的字节长度和字节顺序都是不一样的,例如Windows一般是2字节,LittleEndian;
	Solaris(Sparc)也是2字节,BigEndian; Linux为4字节. 因此,不能认为各个平台同样内容的UGStringW的内部存储是一致的.
	也就是说, UGStringW不能用来保证各个平台上宽字节(Unicode)字符串存储的统一. 这一职能被另外一个类UGStringUCS2LE
	所承担, UGStringUCS2LE保证存取都按照 Windows上的 UCS2,LittleEndian方式进行,以保持各个平台的统一和与SFC数据的兼容.
	UGStringW主要可用来对字符进行拆分.
*/
class TOOLKIT_API UGStringW
{
public:
	  //!  \brief Toolkit
	UGStringW();
	  //!  \brief Toolkit
	  //!  \brief Toolkit
	UGStringW(const UGMBString& str);
	  //!  \brief Toolkit
	UGStringW(const UGStringW& str);
	  //!  \brief Toolkit
	UGStringW(const UGwchar* str);
	  //!  \brief Toolkit
	UGStringW(const UGwchar* str,const UGint nSize);
	  //!  \brief Toolkit
	UGStringW(const std::wstring& str);
	  //!  \brief Toolkit
	~UGStringW();
	  //!  \brief Toolkit
	operator UGPCTSTRW() const;
	//! \brief 转成MBCS编码的
	UGMBString ToString(UGMBString::Charset enTarget = UGMBString::Default);
	//! \brief 通过普通字符串创建
	void FromString(const UGMBString& str,UGMBString::Charset enSource = UGMBString::Default);

	  //!  \brief Toolkit
	bool operator==(const UGwchar* pch) const;
	  //!  \brief Toolkit
	bool operator!=(const UGwchar* pch) const;

	// commited by zengzm 2007-4-19 下面两个函数用UGStringU替代了,这里封起来
	//add by xielin 2006.10.23
	//用于把windows上读取的Stringw的char流转换成适合各个平台的StringW，读取数据的时候
	//务必用这个函数转换一下，否则可能出现乱码等情况
	//UGMBString WinOSStringWToString();
	//用于把各个平台上的StringW转换成Windows平台上的Stringw的char流，在写Stringw到文件
	//的时候，请务必用这个函数转换一下。否则以后读取可能就会出问题。
	//void WinOSStringWFromString(const UGMBString& str);
	
	
	
	  //!  \brief Toolkit
	const UGwchar* Cstr()const;
	
	  //!  \brief Toolkit
	UGwchar GetAt(UGint nIndex)const;
	  //!  \brief Toolkit
	void SetAt(UGint nIndex,UGwchar wch);
	  //!  \brief Toolkit
	UGwchar operator[](UGint nIndex)const;
	  //!  \brief Toolkit
	UGwchar& operator[](UGint nIndex);
	
	  //!  \brief Toolkit
	void SetCapacity(UGint nCapacity);
	  //!  \brief Toolkit
	UGint GetCapacity()const;
	  //!  \brief Toolkit
	const UGwchar* GetData()const;
	  //!  \brief Toolkit
	
	  //!  \brief Toolkit
	UGint GetLength()const;
	  //!  \brief Toolkit
	void  MakeUpper();
	  //!  \brief Toolkit
	void	MakeLower();
	  //!  \brief Toolkit
	void  MakeInverse();
	
	  //!  \brief Toolkit
	UGStringW Left(UGint nCount)const;
	  //!  \brief Toolkit
	UGStringW Right(UGint nCount)const;
	  //!  \brief Toolkit
	UGStringW Mid(UGint nFirst)const;
	  //!  \brief Toolkit
	UGStringW Mid(UGint nFirst,UGint nCount)const;
	  //!  \brief Toolkit
	
	  //!  \brief Toolkit
	UGint Delete(UGint nIndex,UGint nCount  = 1);
	  //!  \brief Toolkit
	UGint Insert(UGint nIndex,UGwchar* pstr);
	  //!  \brief Toolkit
	UGint Insert(UGint nIndex,UGwchar ch,UGint nCount = 1);
	  //!  \brief Toolkit
	UGint Remove(UGwchar ch);
	
	  //!  \brief Toolkit
	UGStringW& TrimLeft();
	  //!  \brief Toolkit
	UGStringW& TrimLeft(UGwchar ch);
	  //!  \brief Toolkit
	UGStringW& TrimLeft(const UGwchar* pstr);
	  //!  \brief Toolkit
	UGStringW& TrimRight();
	  //!  \brief Toolkit
	UGStringW& TrimRight(UGwchar ch);
	  //!  \brief Toolkit
	UGStringW& TrimRight(const UGwchar* pstr);
	
	  //!  \brief Toolkit
	UGbool IsEmpty()const;
	  //!  \brief Toolkit
	void Empty();
	
	  //!  \brief Toolkit
	UGint Compare(const UGwchar* pstr)const;
	  //!  \brief Toolkit
	UGint CompareNoCase(const UGwchar* pstr)const;
	
	  //!  \brief Toolkit
	UGint Find(UGwchar ch) const;	
	  //!  \brief Toolkit
	UGint ReverseFind(UGwchar ch) const;	
	  //!  \brief Toolkit
	UGint Find(UGwchar ch,UGint nStart) const;	
	  //!  \brief Toolkit
	UGint FindOneOf(const UGwchar* lpszCharSet) const;	
	  //!  \brief Toolkit
	UGint Find(const UGwchar* lpszSub) const;	
	  //!  \brief Toolkit
	UGint Find(const UGwchar* lpszSub, UGint nStart) const;
	
	  //!  \brief Toolkit
	UGStringW SpanIncluding(const UGwchar* lpszCharSet) const;	
	  //!  \brief Toolkit
	UGStringW SpanExcluding(const UGwchar* lpszCharSet) const;
	
	  //!  \brief Toolkit
	UGint Replace(UGwchar chOld,UGwchar chNew);
	  //!  \brief Toolkit
	UGint Replace(const UGwchar* lpszOld,const UGwchar* lpszNew);
	
	// commited by zengzm 2007-7-17 UGStringW不提供
	  //!  \brief Toolkit
	//UGuint HashVal() const;
	
	// commited by zengzm 2007-4-7 UGStringW不提供这些比较操作
	  //!  \brief Toolkit
	//UGbool LoadResString(UGuint nID);
	  //!  \brief Toolkit
	//void Format(const UGwchar* fmt,...);
	  //!  \brief Toolkit
	//void Format(UGuint nID,...);
	
	// commited by zengzm 2007-7-17 UGStringW不提供
	//Convert string to a integer number, assuming given number base
	  //!  \brief Toolkit
	//friend BASE_API UGint UGIntVal(const UGStringW& s,UGint base=10);
	  //!  \brief Toolkit
	//friend BASE_API UGuint UGUIntVal(const UGStringW& s,UGint base=10);
	
	//Convert string into real number
	  //!  \brief Toolkit
	//friend BASE_API UGfloat UGFloatVal(const UGStringW& s);
	  //!  \brief Toolkit
	//friend BASE_API UGdouble UGDoubleVal(const UGStringW& s);	
	
	  //!  \brief Toolkit
	//! \brief 对当前字符串进行拆分。
	//! \param &dest 拆分后生成的字符串数组[in]。
	//! \param delims 拆分的标志符号，当有多个符号存在的时候，每个符号都是标识符[in]。
	//! \return 。
	//! \remarks delims 不是多个符号代表一个拆分符号，多个符号代表多个拆分符号,
	//! \attention 只支持一个字符的拆分。
	UGint Split(UGArray<UGStringW> &dest,const UGStringW& delims=L"\r\n") const;
	
	// commited by zengzm 2007-4-7 存取的事情交给UGStringUCS2LE处理
	  //!  \brief Toolkit
	//friend BASE_API UGStream& operator<<(UGStream& store,const UGStringW& s);
	  //!  \brief Toolkit
	//friend BASE_API UGStream& operator>>(UGStream& store,UGStringW& s);
	
private:
	// void FormatV(const UGwchar* fmt, va_list argList);
	
protected:
	std::wstring m_string;  
};

//! \brief 按照UCS2-LE的方式进行字符串管理的类,用于各个平台字符串存取的统一。
//! \remarks SFC在Unicode存取时,就是按照UCS2-LE编码进行的; UGStringUCS2LE可保证和SFC的数据兼容。
//!	UGStringUCS2LE提供的功能包括: 1)从Stream中存取UCS2LE方式的字符串;2)和UGString之间进行转化
//!	<\br>增加对直接使用UGStringUCS2LE中的字符串的支持，主要是增加了字符串结束符，以及增加Cstr函数
	  //!  \brief Toolkit
class TOOLKIT_API UGStringUCS2LE
{
public:
	//! \brief 默认构造函数
	UGStringUCS2LE();

	//! \brief 提供通过UGString来进行构造。
	UGStringUCS2LE(const UGMBString& str, UGMBString::Charset enTarget = UGMBString::Default);	

	//! \brief 转化为UGString
	UGMBString ToString(UGMBString::Charset enTarget = UGMBString::Default) const;

	//! \brief 得到字符个数
	//! \return 返回字符个数（等于字节长度/2）
	UGint GetLength() const;

	//! \brief 得到UGushort*形式的字符串
	const UGushort* Cstr() const;

	//! \brief 写到存储流中
	friend TOOLKIT_API UGStream& operator<<(UGStream& store,const UGStringUCS2LE& s);
	//! \brief 从存储流中读出
	friend TOOLKIT_API UGStream& operator>>(UGStream& store,UGStringUCS2LE& s);

	// add by cuiwz 2008-5-28 支持 UGByteArray
	//! \brief 写到存储流中
	friend TOOLKIT_API UGByteArray& operator<<(UGByteArray& store,const UGStringUCS2LE& s);
	//! \brief 从存储流中读出
	friend TOOLKIT_API UGByteArray& operator>>(UGByteArray& store,UGStringUCS2LE& s);
	
	//! \brief 获取成员变量m_string，外面就可以用这个咚咚做一些事情
	const UGArray<UGushort>& GetChars() const;
protected:
	//typedef std::basic_string<UGushort, std::char_traits<UGushort>, std::allocator<UGushort> > ustring;
	//ustring m_string;
	UGArray<UGushort> m_string;
};

//! \brief 给UGStringUCS2LE 取一个短一点的名字
typedef UGStringUCS2LE UGStringU;


//! \brief 按照UTF8的方式进行字符串管理的类,用于把各类编码都转化为utf8之后，再传递给很多跨平台函数使用
class TOOLKIT_API UGStringUTF8
{
public:
	//! \brief 默认构造函数
	UGStringUTF8();

	//! \brief 提供通过UGString来进行构造。
	UGStringUTF8(const UGMBString& str, UGMBString::Charset enTarget = UGMBString::Default);	

	//! \brief 转化为UGString
	UGMBString ToString(UGMBString::Charset enTarget = UGMBString::Default) const;

	//! \brief 得到字节个数
	//! \remarks 因为UTF8编码的特殊性,本函数是得到字节的长度;如果需要字符个数,请先转化为其它编码的字符串
	//! \return 返回字节个数
	UGint GetLength() const;

	//! \brief 得到char *形式的字符串
	const UGachar* Cstr() const;

	// 读写到流中，暂不支持，有需要的说一声，再考虑如何做。
	//! \brief 写到存储流中
	//friend BASE_API UGStream& operator<<(UGStream& store,const UGStringUCS2LE& s);
	//! \brief 从存储流中读出
	//friend BASE_API UGStream& operator>>(UGStream& store,UGStringUCS2LE& s);
	
	//! \brief 获取成员变量m_string，外面就可以用这个咚咚做一些事情
	// const UGArray<UGushort>& GetChars() const;
protected:
	//typedef std::basic_string<UGushort, std::char_traits<UGushort>, std::allocator<UGushort> > ustring;
	std::string m_string; // 内部采用std的string实现
	//UGArray<UGushort> m_string;
};
#endif //_UGUNICODE
}

#endif

