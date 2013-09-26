//////////////////////////////////////////////////////////////////////////
//                    _   _   ____   ____                    
//   Project         | | | | / ___) / ___)                   
//                   | | | || | __ | |                       
//                   | |_| || |_\ || \___                    
//                    \____/ \____| \ ___)     6.0           
//                                                           
//!  \file UGFile32.h
//!  \brief UGFile32类的接口定义。
//!  \details UDBPLUS中空间数据文件
//!  \author wangmao
//!  \attention 
//!   Copyright (c) 2000-2010 SuperMap Software Co., Ltd.  <br> 
//!   All Rights Reserved.
//!  \version 6.0
//////////////////////////////////////////////////////////////////////////
#ifndef UGFile32_H
#define UGFile32_H

#if defined(_WIN32) || defined(WIN32)
/* This needs to come before any includes for MSVC compiler */
#define _CRT_SECURE_NO_WARNINGS
#endif

#include "Stream/ugdefs.h"
#include "Stream/UGStream.h"
#include "Stream/UGByteArray.h"

namespace UGC{
#ifdef SYMBIAN60
class STREAM_APIC UGFile32 :  public UGStream
#else
class STREAM_API UGFile32 :  public UGStream
#endif
{

public:
	//! \brief 构造函数
	STREAM_APIF UGFile32();
	//! \brief 析构函数
	virtual STREAM_APIF ~UGFile32();

private:
#ifndef SYMBIAN60
	STREAM_APIF UGFile32(const UGFile32& file32);
	STREAM_APIF UGFile32& operator=(const UGFile32& file32);
#endif

public:
	//! \brief 根据文件名和文件描述打开文件 
	//! \param strName 文件名字
	//! \param nDirection 字符串大小
	//! \return 返回打开是否成功
	//! \remarks UGStreamDirection 包括UGStreamSave UGStreamLoad UGStreamLoadSave 三种模式 其他模式无法打开
	//!    如果这个文件没有close,重复打开，不会保存原来打开的信息。 
	//!    在 UGStreamSave 模式下 如果这个文件存在，则设置这个文件的长度为零。这种模式下可读，可写。
	//!    在 UGStreamLoad 模式下 如果这个文件不存在，不会创建新文件，会返回失败,内存文件一般情况下会存在。这种模式
    //!                           这种模式不允许写。
	//! \attention 如果打开一个内存文件，在打开一个磁盘文件，内存文件不会删除。如果不需要保留，最好先Close()。相反也是如此。
	STREAM_APIF UGbool Open(const UGString& strFileName, UGStreamDirection nDirection,UGbool bIsSwapEndian = FALSE);


	//! \brief 将内存数据转化到文件中,释放原来的内存文件转化成磁盘文件。
	//! \param &strName 磁盘文件的路径[in]。
	//! \param flag 转化成磁盘文件的属性[in]。
	STREAM_APIF UGbool MemoryToFile(UGString &strName);

	//! \brief 判断当前文件是否打开,
	//! \return 文件是否打开
	STREAM_APIF UGbool IsOpen() const{return m_FileHandle != -1;}

    //! \brief 设置文件的位置从文件开始的位置算起
	//! \param whence 移动位置
	//! \remarks 移动的位置不能小于0，可以超过文件的长度
	//! \return 返回设置是否成功
	virtual STREAM_APIF UGbool SetPosition(UGulong nOffset);

	//! \brief 得到流全部空间的大小，文件流时等同于内部缓存区的大小。
	virtual STREAM_APIF UGSizeT GetSpace() const{return (UGSizeT)m_nFileLength;}

	//! \brief 获取文件指针的位置,和文件头的偏移量。
	//! \return 文件的指针。
	STREAM_APIF UGulong GetPosition() const{return m_nCurPosition;}

	//! \brief 获取文件的长度,单位字节
	//! \return 文件的长度
	virtual STREAM_APIF UGulong GetLength();
	
	//! \brief 从当前文件指针位置开始读文件
	//! \param pContext 字符串文件指针,
	//! \param nSize 字符串大小
	//! \remarks 需要预先开辟内存
	//! \return 返回读取是否成功
	STREAM_APIF UGbool Read(void* pContext,UGSizeT nSize);

	//! \brief 从当前文件指针位置开始写文件，如果文件大小不够，会自动增加
	//! \param pContext 字符串文件指针
	//! \param nSize 字符串大小
	//! \return 返回实际写入的字节数,如果写入失败返回-1
	STREAM_APIF UGbool Write(const void* pContext,UGSizeT nSize);
	
	//! \brief 关闭一个文件。
	//! \return 是否成功关闭。
	//! \remarks 如果文件已经关闭了返回TRUE。
	STREAM_APIF UGbool Close();	
	
	//! \brief 文件同步。
	//! \return 同步是否成功。
	STREAM_APIF UGbool Sync();
	
	//! \brief 流的刷新，仅对文件流有效，即把缓存中的内容写入到文件中。
	virtual STREAM_APIF UGbool Flush();  
	
	//! \brief 截断文件
	STREAM_APIF UGbool Truncate(UGulong nPosition);


	//! \brief 得到内存文件的数据开始指针。
	//! \return 内存文件的数据开始指针。
	const STREAM_APIF UGuchar* GetMemoryData();		
	
	//! \brief 从文件流中输出nCount个 UGuchar
	STREAM_APIF UGStream&  Load(UGuchar* pContext,UGSizeT nCount);
	
	//! \brief 从文件流中输出nCount个 UGchar
	STREAM_APIF UGStream&  Load(UGachar* pContext,UGSizeT nCount);
#if _MSC_VER > 1200
	STREAM_APIF UGStream&  Load(UGwchar* pContext,UGSizeT nCount){return Load((UGushort*)pContext, nCount);}
#endif
	
	//! \brief 从文件流中输出nCount个 UGushort
	STREAM_APIF UGStream&  Load(UGushort* pContext,UGSizeT nCount);
	
	//! \brief 从文件流中输出nCount个 UGshort
	STREAM_APIF UGStream&  Load(UGshort* pContext,UGSizeT nCount);
	
	//! \brief 从文件流中输出nCount个 UGuint
	STREAM_APIF UGStream&  Load(UGuint* pContext,UGSizeT nCount);
	
	//! \brief 从文件流中输出nCount个 UGint
	STREAM_APIF UGStream&  Load(UGint* pContext,UGSizeT nCount);
	
	//! \brief 从文件流中输出nCount个 UGfloat
	STREAM_APIF UGStream&  Load(UGfloat* pContext,UGSizeT nCount);
	
	//! \brief 从文件流中输出nCount个 UGdouble
	STREAM_APIF UGStream&  Load(UGdouble* pContext,UGSizeT nCount);
	
	//! \brief 从文件流中输出nCount个 UGlong
	STREAM_APIF UGStream&  Load(UGlong* pContext,UGSizeT nCount);
	
	//! \brief 从文件流中输出nCount个 UGulong
	STREAM_APIF UGStream&  Load(UGulong* pContext,UGSizeT nCount);

	//! \brief 从文件流中输出一个 UGuchar
	STREAM_APIF UGStream&  operator>>(UGuchar& v){ Load(&v,1);  return *this; }

	//! \brief 从文件流中输出一个 UGchar
	STREAM_APIF UGStream&  operator>>(UGachar& v){ Load(&v,1);  return *this; }
#if _MSC_VER > 1200
	STREAM_APIF UGStream&  operator>>(UGwchar& v){ Load(&v,1);  return *this; }
#endif

	//! \brief 从文件流中输出一个 UGushort
	STREAM_APIF UGStream&  operator>>(UGushort& v){ Load(&v,1);  return *this; }

	//! \brief 从文件流中输出一个 UGshort
	STREAM_APIF UGStream&  operator>>(UGshort& v){ Load(&v,1);  return *this; }

	//! \brief 从文件流中输出一个 UGuint
	STREAM_APIF UGStream&  operator>>(UGuint& v){ Load(&v,1);  return *this; }

	//! \brief 从文件流中输出一个 UGint
	STREAM_APIF UGStream&  operator>>(UGint& v){ Load(&v,1);  return *this; }

	//! \brief 从文件流中输出一个 UGfloat
	STREAM_APIF UGStream&  operator>>(UGfloat& v){ Load(&v,1); return *this; }

	//! \brief 从文件流中输出一个 UGdouble
	STREAM_APIF UGStream&  operator>>(UGdouble& v){Load(&v,1); return *this; }

	//! \brief 从文件流中输出一个 UGlong
	STREAM_APIF UGStream&  operator>>(UGlong& v){ Load(&v,1);  return *this; }
	
	//! \brief 从文件流中输出一个 UGulong
	STREAM_APIF UGStream&  operator>>(UGulong& v){ Load(&v,1);  return *this; }
	
	//! \brief 保存nCount个 UGuchar 到文件流中
	STREAM_APIF UGStream&  Save(const UGuchar* pContext,UGSizeT nCount);

	//! \brief 保存nCount个 UGchar 到文件流中
	STREAM_APIF UGStream&  Save(const UGachar* pContext,UGSizeT nCount);
#if _MSC_VER > 1200
	STREAM_APIF UGStream&  Save(const UGwchar* pContext,UGSizeT nCount){return Save((UGushort*)pContext, nCount);}
#endif

	//! \brief 保存nCount个 UGushort 到文件流中
	STREAM_APIF UGStream&  Save(const UGushort* pContext,UGSizeT nCount);

	//! \brief 保存nCount个 UGshort 到文件流中
	STREAM_APIF UGStream&  Save(const UGshort* pContext,UGSizeT nCount);

	//! \brief 保存nCount个 UGuint 到文件流中
	STREAM_APIF UGStream&  Save(const UGuint* pContext,UGSizeT nCount);

	//! \brief 保存nCount个 UGint 到文件流中
	STREAM_APIF UGStream&  Save(const UGint* pContext,UGSizeT nCount);

	//! \brief 保存nCount个 UGfloat 到文件流中
	STREAM_APIF UGStream&  Save(const UGfloat* pContext,UGSizeT nCount);

	//! \brief 保存nCount个 UGdouble 到文件流中
	STREAM_APIF UGStream&  Save(const UGdouble* pContext,UGSizeT nCount);

	//! \brief 保存nCount个 UGlong 到文件流中
	STREAM_APIF UGStream&  Save(const UGlong* pContext,UGSizeT nCount);

	//! \brief 保存nCount个 UGulong 到文件流中
	STREAM_APIF UGStream&  Save(const UGulong* pContext,UGSizeT nCount);
	
	//! \brief 保存一个 UGuchar 到文件流中
	STREAM_APIF UGStream&  operator<<(const UGuchar& v){ Save(&v,1); return *this; }

	//! \brief 保存一个 UGchar 到文件流中
	STREAM_APIF UGStream&  operator<<(const UGachar& v){ Save(&v,1); return *this; }
#if _MSC_VER > 1200
	STREAM_APIF UGStream&  operator<<(const UGwchar& v){ Save(&v,1); return *this; }
#endif

	//! \brief 保存一个 UGushort 到文件流中
	STREAM_APIF UGStream&  operator<<(const UGushort& v){ Save(&v,1); return *this; }

	//! \brief 保存一个 UGshort 到文件流中
	STREAM_APIF UGStream&  operator<<(const UGshort& v){ Save(&v,1); return *this; }

	//! \brief 保存一个 UGuint 到文件流中
	STREAM_APIF UGStream&  operator<<(const UGuint& v){ Save(&v,1); return *this; }

	//! \brief 保存一个 UGint 到文件流中
	STREAM_APIF UGStream&  operator<<(const UGint& v){ Save(&v,1); return *this; }

	//! \brief 保存一个 UGfloat 到文件流中
	STREAM_APIF UGStream&  operator<<(const UGfloat& v){ Save(&v,1); return *this; }

	//! \brief 保存一个 UGdouble 到文件流中
	STREAM_APIF UGStream&  operator<<(const UGdouble& v){ Save(&v,1); return *this; }

	//! \brief 保存一个 UGlong 到文件流中
	STREAM_APIF UGStream&  operator<<(const UGlong& v){ Save(&v,1); return *this; }

	//! \brief 保存一个 UGulong 到文件流中
	STREAM_APIF UGStream&  operator<<(const UGulong& v){ Save(&v,1); return *this; }

	STREAM_APIF UGbool IsMemoryFile(){return m_bIsMemoryFile;}

public:
	//进行2字节的大小端交换,nSize是要交换的个数
	STREAM_APIF static void Swap2Byte(void*pContext,UGSizeT nSize);
	//进行4字节的大小端交换,nSize是要交换的个数
	STREAM_APIF static void Swap4Byte(void*pContext,UGSizeT nSize);
	//进行8字节的大小端交换,nSize是要交换的个数
	STREAM_APIF static void Swap8Byte(void*pContext,UGSizeT nSize);
	//检测一下缓冲区是否足够,如果不够会自动的扩容,如果扩容失败会返回FALSE
	STREAM_APIF UGbool CheckBufferSize(UGSizeT nSize);
	//返回当前文件是否是只读打开的
	STREAM_APIF UGbool IsReadOnly(){return m_bReadOnly;}
private:
	//真正的移动文件的位置
	STREAM_APIF UGbool SyncPosition();

	//初始化成员变量
	STREAM_APIF void InitializeMember();

	//释放占有的资源
	STREAM_APIF void ReleaseResources();

	//! \brief 是否是读操作
	UGbool m_bLastIsReadOP;

	//! \brief 是否需要进行大小端的交换
	UGbool m_bIsSwapEndian;

	//! \brief 是否需要重新设置文件位置
	UGbool m_bSyncPosition;	

	//! \brief 是否是内存文件
	UGbool m_bIsMemoryFile;

	//! \brief 文件指针
	UGint m_FileHandle;

	//! \控制大小端的读取
	UGuchar*  m_pSwapBuffer;
	
	//! \Buffer的大小
	UGulong m_nBufferSize;

	//! \brief 读文件指针当前位置
	UGulong m_nCurPosition;
	
	//! \brief 文件的有效长度
	UGulong m_nFileLength;

	//! \brief 内存文件流
	UGByteArray m_MemFile;
	//是否是只读模式，当前文件
	UGbool  m_bReadOnly;
};

}

#endif // !defined(AFX_UGFile32_H__52E31DC2_8E36_4136_9D5F_C372D533EEC4__INCLUDED_)

