//////////////////////////////////////////////////////////////////////////
//                    _   _   ____   ____                    
//   Project         | | | | / ___) / ___)                   
//                   | | | || | __ | |                       
//                   | |_| || |_\ || \___                    
//                    \____/ \____| \ ___)     6.0           
//                                                           
//!  \file headerfile.h
//!  \brief Class 的接口定义。
//!  \details 该文件定义了GTiff文件分析的主要接口。
//!  \author 李林。
//!  \attention 
//!   Copyright (c) 1996-2008 SuperMap Software Limited Company.  <br> 
//!   All Rights Reserved.
//!  \version 6.0
//////////////////////////////////////////////////////////////////////////
#ifndef __SUPERMAP_UGC_AHCACHEFILE_H__INCLUDE_
#define __SUPERMAP_UGC_AHCACHEFILE_H__INCLUDE_

//#include "sysdef.h"
//#include "const.h"
#include <stdio.h>
#include <string>
#include <ctype.h>
#include <vector>
#include <fstream>
#include <exception>
#include <time.h>
#include <math.h>
#include <sstream>  

//#include "Toolkit/UGHashCode.h"
#include "ugdefs.h"
#include "UGByteArray.h"
#include "Stream/UGFile.h"
#include "Stream/ugplatform.h"


#ifdef WIN32
#include "windows.h"
#endif

#ifndef WIN32
typedef long long int UGPosType;//位置指针类型,暂时默认都用64位		//	WhiteBox_Ignore
#else
typedef __int64 UGPosType;
#endif

//#if define(_DEBUG) || define(DEBUG)
//#define ENABLE_CACHE_FILE_LOG
//#endif // _DEBUG



using namespace std;

namespace UGC {
typedef UGint UGResult;

//和文件格式有关的常量定义
#define BOXCOUNT 256
#define STR_SC_FILETYPE _U("SC")
#define STR_SCD_FILETYPE _U("SCD")
#define STR_SCD_FILETYPE_LEN 3
#define STR_SC_FILE_POSTFIX _U(".sc")
#define DEF_FILE_MAXSIZE 2000 /*单位是M*/
#define FILE_MAXSIZE 2000 /*单位是M*/
#define DFILE_MIN_POS 3 /*数据文件中数据的最小位置*/
#define LITTLE_ENDIAN_MARK 0 /*小字节序标志*/
#define BIG_ENDIAN_MARK 1 /*大字节序标志*/
//文件版本号
#define INIT_VERSION 20100401 //大文件缓存的初始版本号是2010.4.1
#define VERSION_1_1 20100901 //大文件缓存的版本号2010.9.1

//
#define EMPTY_STR_CODE 757602046 //空字符串的哈希值
#define DEFAULT_DATA_ENCODE_LENGTH 64 //ArchiveSubHead.EncodeDataLen的默认值

//错误码
#define UGE_SUCCESS      0
#define UGE_OPEN_FALSE   1
#define UGE_CREATE_FALSE 2
#define UGE_ERROR_FORMAT 3
#define UGE_OUTOF_RANGE  4
#define UGE_NO_FOUND	 5
#define UGE_UNOPEN		 6
#define UGE_INVALID_ARGUMENT 7
#define UGE_UNSUPPORTED 8
#define UGE_ERROR_READ 9
#define UGE_ERROR_WRITE 10

#define	SC_ISTAT_OVERWRITE	0    //文件被覆盖
//#define SC_ISTAT_DELETED	-1   
//#define SC_ISTAT_APPENDING -2

#define SCD_FILE_STATUS_APPENDING 1//正在追加中的文件
#define SCD_FILE_STATUS_NORMAL 0//正常文件
#define SCD_FILE_STATUS_GARBAGE 2//垃圾文件，不能再使用

// #ifdef WIN32
// #define UGtell _telli64
// #define UGaccess _access
// #define UGchsize _chsize
// //#define UGseek _lseeki64
// #define UGsleep Sleep
// #else
// #define UGaccess access
// #define UGchsize ftruncate
// //#define UGseek lseek64
// #if defined(UGtell)
// #undef UGtell
// #endif
// #define UGtell(h) (UGPosType)lseek(h, 0, SEEK_CUR)
// #define UGsleep(s) sleep(s/1000.0)
// #endif

//! \brief 缓存类型
enum StoreType	// TODO 改名为 StorageType，保证无名称冲突
{
	PURE_FILES=0, //纯文件型缓存,以前小文件类型的缓存
	MIXED_FILES, //混合文件型,适合服务端生成缓存(当然客户端也可以生成此类型)
	SINGLE_FILE, //单文件型,适合客户端生成缓存
};

//! \brief 归档流
class STREAM_API UGCacheFile
{
public:
#pragma pack(1)
//! \breif 索引项，sc文件用
struct HashItem{
	UGint HashCode;//哈希值
	UGbyte FileId;//所处数据文件
	UGint DataPos;//数据开始(负数属于无效位置)
};
#pragma pack()

//! \breif 追加方式
enum ADD_TYPE{ 
	NEW , //重新建立新的数据块
	APPEND //追加到已有数据块
};

enum FILE_TYPE{
	NORMAL = 0,
	APPENDING = 1
};

//! \brief 缓存的的打开模式  暂时只做只读和读写 
enum CacheFileDirection
{
//	! \brief 只写
//	CF_OnlyWrite	=0,
	//! \brief 只读
	CF_OnlyRead		=1,
	//! \brief 读写
	CF_ReadAndWrite =2,
};

struct CacheFileStatus{
	UGint NumOfFiles; // 文件总数，包含已经删除了但空间没有被回收的文件
	UGint NumOfValidFiles;//有效文件的数目
	UGint TotalSpaceSize; // 数据文件的总大小
	UGint ValidSpaceSize; //有效空间大小
};

private:
//! \breif sc文件头结构
struct ArchiveHead{
	UGbyte  FileType1;//文件标示,永远是SC
	UGbyte  FileType2;//文件标示,永远是SC
    UGbyte	Ext1;//
	UGbyte EndianType;//字节序，为1表示Big-Endian，为0表示Little-Endian
	UGint Version;//版本号
	UGint MaxSize;//最大的大小,M为单位
	UGint MagicNumber;//用来判断是否是大文件，这个值应该是INIT_VERSION
    UGbyte  Flag[48];//48个扩展字段拼到64字节
};

//! \brief scd 文件用
struct ArchiveSubHead{
	UGint FileNameLen;//文件名的长度
	UGint DataLen;//数据的长度
	UGint EndodeDataLen;//文件数据被加密的长度(不能大于文件数据的长度)
	UGbyte FileStatus;//文件状态(标志这个文件的用途，现在只有追加使用，0为其他文件，1表示文件正在追加中)
	UGbyte Reserve[3];//保留的三个字节
	
	ArchiveSubHead()
	{
		FileNameLen = 0;
		DataLen = 0;
		EndodeDataLen = 0;
		FileStatus = SCD_FILE_STATUS_GARBAGE;
        memset(Reserve,0,3);
	}
};

//! \breif 索引头结构，sc文件用
struct HashListHead{
	UGint UpdateTime;//最后更新时间
	UGint Count;//一共多少Hash
	UGint EndFile;//在第几个文件结束
	UGint EndPos;//在什么位置结束
	UGint EndHashItem;//现在到第几个Item了
};

//! \breif 查找结果
enum SEARCH_RESULT{ 
	NOFOUND , //没找到
	FOUND, //找到了
	//FOUNDINSERT,
};

//! \breif HashItem列表包装
struct HashItemArray
{
	//内部数据
	HashItem* m_data;
	//内部大小
	UGint m_size;
public:
	//! \breif 构造函数
	HashItemArray();
	//! \breif 析构函数
	~HashItemArray();
	//! \breif 重设大小
	inline void SetSize(UGint size)
	{
		if (m_data!=NULL) delete[] m_data; 
		m_size = size; 
		m_data = new HashItem[size];
	}
	//! \brief 获取节点数量
	UGint GetSize()
	{
		return m_size;
	}
	//! \breif 析构函数
	inline HashItem* GetItem(UGint i)
	{
		if (i>=m_size)
			return NULL;
		return (HashItem*)(m_data+i);
	}
};



public:
	
    //! \brief 构造函数
    UGCacheFile(/*ArchiveHash* hash = 0*/);

    //! \brief 析构函数
    ~UGCacheFile();

	//! \brief 打开文件。
	//! \param path[in] 打开文件路径。
	//! \param password[in] 打开所需密码
	//! \return 返回结果码(带错误状态)，注意，要跟UGE_SUCCESS(0)判断，不能直接当Bool判断，因为结果完全相反。
	//! \remarks 如果指定文件路径不存在，会自动创建一个文件。
	//! \attention 。
    UGResult Open(const UGString& path, const UGString& password=_U(""), CacheFileDirection save_or_load = CF_ReadAndWrite);

	//! \brief 是否已经打开文件。
	//! \param path[in] 。
	//! \param password[in] 
	//! \return 
	//! \remarks 。
	//! \attention 。
	UGbool IsOpen();

	//! \brief 创建文件，可以定义最大大小，默认是2G最大值。
	//! \param schpath[in] 创建文件路径。
	//! \param maxsize[in] 限制文件大小(默认2G，只可小不可大，设置为0为无上限)。
	//! \param password[in] 解析密码
	//! \return 返回结果码(带错误状态)，注意，要跟UGE_SUCCESS(0)判断，不能直接当Bool判断，因为结果完全相反。
	//! \remarks 这个函数只负责创建(内部已经关闭)，不负责打开。要打开，还是需要再调用一次Open
	//! \attention 。
    static UGResult Create(const UGString& schpath ,const UGString& password=_U("")
		,UGint maxsize=DEF_FILE_MAXSIZE,UGbool bBigIndian = FALSE
		,UGint version =VERSION_1_1);

	//! \brief 关闭文件
	//! \param [in] 
	//! \return 
	//! \remarks 
	//! \attention 。
    UGbool Close();

	//! \breif 设置密码
	//! \param newpassword[in] 设定新密码
	//! \return 是否设置成功
	//! \remarks 
	//! \attention 。
	UGbool SetPassword(const UGString& newpassword);

	//! \brief 添加一个文件
	//! \param filepath[in] 要添加的文件路径
	//! \param archivePath[in] 要添加的文件在缓存中存储的路径(相对路径)
	//! \return 返回结果码(带错误状态)，注意，要跟UGE_SUCCESS(0)判断，不能直接当Bool判断，因为结果完全相反。
	//! \remarks 如果存档中存储的路径已存在，那么会覆盖这个文件内容
	//! \attention 。
    UGResult AddFile(const UGString& filepath, const UGString& archivePath);

	//! \brief 添加一个文件(直接加二进制)
	//! \param context[in] 要添加的文件内容
	//! \param archivePath[in] 要添加的文件在缓存中存储的路径(相对路径)
	//! \return 返回结果码(带错误状态)，注意，要跟UGE_SUCCESS(0)判断，不能直接当Bool判断，因为结果完全相反。
	//! \remarks 如果存档中存储的路径已存在，那么会覆盖这个文件内容
	//! \attention 。
	UGResult AddFile(const UGByteArray& context, const UGString& archivePath);

	//! \brief 追加模式增加数据
	//! \param context[in] 要添加的文件
	//! \param archivePath[in] 要添加的文件在缓存中存储的路径(相对路径)
	//! \param bLast[in] 是否最后一次追加数据
	//! \remark 以追加模式增加的数据相当于一个临时数据，在正常的情况下，即在ReadFile的时候
	//! 是读不到这个数据的，只有在bLast为true，即追加最后一份数据之后，ReadFile才能
	//! 读出数据
	UGResult AppendFile(const UGByteArray& context, const UGString& archivePath ,UGbool bLast = FALSE);

	//! \brief 判断文件是否存在
	//! \param archivePath[in] 要添加的文件在缓存中存储的路径(相对路径)
	//! \return 返回是否存在。
	//! \remarks 注意：如果在判断文件是否存在的同时需要拿数据，应该直接用ReadFile的返回值来判断。不要调用本函数后再用ReadFile，这样影响效率。
	//! \attention 。
	UGbool IsFileExist(const UGString& archivePath);

	//! \brief 读取归档中的文件
	//! \param filepath[in] 要读取的文件路径
	//! \param context[in] 文件内容
	//! \return 返回结果码(带错误状态)，注意，要跟UGE_SUCCESS(0)判断，不能直接当Bool判断，因为结果完全相反。
	//! \remarks
	//! \attention 。
	UGResult ReadFile(const UGString& filepath, UGByteArray& context);

	//! \brief 从归档中删除文件(暂时不做删除因为限定大小已经做到删除了)
	//! \param filepath[in] 要删除的文件路径
	//! \param reconstruction[in] 要不要重新整顿大小(默认不整顿)
	//! \return 返回结果码(带错误状态)，注意，要跟UGE_SUCCESS(0)判断，不能直接当Bool判断，因为结果完全相反。
	//! \remarks
	//! \attention 。
	UGResult RemoveFile(const UGString& filepath, FILE_TYPE file_type = NORMAL ,UGbool reconstruction=FALSE);

	//! \brief 重构(紧缩文件)
	//! \param [in]
	//! \return 
	//! \remarks
	//! \attention 。
	UGResult Reconstruction();

	//! \brief 获取关于文件的状态信息
	//! \param status[out] 返回的文件状态信息
	//! \param bNeedReconstruction[out] 是否建议进行重构操作
	//! \return TRUE 获取成功
	//! \return FALSE 获取失败
	//! \remarks
	//! \attention
	UGbool GetStatus( CacheFileStatus &status ,UGbool& bNeedReconstruction );

	//! \brief 列出所有归档中文件的归档路径
	//! \param filepaths[in] 存放归档文件路径的数组
	//! \return 
	//! \remarks
	//! \attention 。
	UGResult ListFiles(UGArray<UGString>& filepaths);

private:
	//! \brief 锁定文件
	UGbool LockFile();

	//! \brief 解锁文件
	void UnlockFile();

	//! \brief 判断文件是否锁着
	//UGbool IsLocked();

	//打印log（调试时候用）
	void PrintLog(const UGString& log, UGbool newline=FALSE);

	//! \brief 计算哈希值
	UGint Codec2UGint(const UGString& instr) const;

	//! \brief 加解密
	static void ReMakeStream(UGbyte* stream, UGint len ,UGbyte *pXor);

	//! \brief 计算哈希值
	UGint GetHashCode(const UGString& instr);

	//! \brief 获取现在时间
	static UGint GetNowTime();

	//! \brief 获取指定存档路径的项
	UGint GetHashItem(const UGString& archpath, UGint& iitem, HashItem** item
		, HashItemArray* itemArr 
		, UGbool bAppendingFile = FALSE);

	//! \brief 获取地址所指文件的大小(仅仅是文件长度)
	UGint GetFileLenFromDataFile(UGint handle, UGint pos);

	//! \brief 
	UGResult AddFileInner(const UGByteArray& context, const UGString& _archivePath ,ADD_TYPE addtype = NEW ,UGbool bLastAppend = FALSE);

	//获取某个页的开始地址
	//UGPosType GetPagePos(UGint ipage, UGint ibox=-1);

	//把文件保存到scd中
	//UGint ArchiveFileToDataFile(const char* filepath, const char* archpath, UGPosType& pos, UGint& len, HashItemArray& itemArr);

	//把文件内容保存到scd中
	//UGint ArchiveByteArrayToDataFile(const UGByteArray& bytearr, const char* archpath, UGPosType& pos, UGint& len, HashItemArray& itemArr);

	//! \brief 获取指定位置的文件归档名
	UGbool GetFilePathFromDataFile(UGint handle, UGint pos, UGMBString& path);

	//! \brief
	inline UGbool ReadArchiveSubHead(UGint handle ,UGint pos ,ArchiveSubHead &head);

	//! \brief
	inline UGbool WriteArchiveSubHead(UGint handle ,UGint pos ,ArchiveSubHead head);

	//! \brief 
	inline UGbool GetDataFileHandle(UGint fileid ,UGint& handle ,UGbool& bNeedClose);

	//! \brief 获取合适的空闲空间
	UGbool GetFreeRoom(HashItemArray &arrItem ,UGint DataSize ,const UGString &arName ,UGint &iitem);

	//! \brief 
	UGint GetSizeInDataFile(UGint DataSize ,const UGString &arName);

	//! \brief 从数据文件中获取二进制数据
	//! \param dhandle[in] 数据文件句柄
	//! \param pos[in] 位置
	//! \param context[out] 获取到的数据文件
	UGbool ReadDataFromDataFile(UGint dhandle ,UGint pos ,const UGString &arName ,UGByteArray& context);

	//! \brief 写数据到数据文件
	UGbool WriteDataToDataFile(UGint dhandle ,UGint pos ,const UGByteArray& context 
		,const UGString &arName ,UGbyte byFileStatus = SCD_FILE_STATUS_NORMAL);


	//! \breif 更新归档名为"/"格式的分隔符
	UGString ReMakeAhPath(const UGString& oldPath);

	//! \brief 转换数据字节序
	static void SwapBytesArchiveHead(ArchiveHead& head);
	static void SwapBytesHashItemHead( HashListHead& listhead);
	static void SwapBytesHashItem(HashItem& item);
	static void SwapBytesArchiveSubHead(ArchiveSubHead &SubHead);

private:
	//! \breif 在Unicode版本下，将之前的UGString字符串转换为UGMBString
	//! \param strUnicode[in]要被转换的UnicodeString
	//! \param strMB[out]转换之后的多字节字符串
	static inline UGMBString& Unicode2MBString(const UGString& strUnicode, UGMBString& strMB)
	{
#ifdef _UGUNICODE
		strUnicode.ToMBString(strMB);
#else
		strMB = strUnicode;
#endif
		return strMB;
	}

	//! \brief 将UGMBString转化为UnicodeString
	//! \param strMB[in]要被转换的的strMB
	//! \param strUnicode[out]转换之后的Unicode字符串
	static inline UGString& MBString2Unicode(const UGMBString& strMB, UGString& strUnicode)
	{
#ifdef _UGUNICODE
		strUnicode.FromMBString(strMB.Cstr(), strlen(strMB.Cstr()));
#else
		strUnicode=strMB;
#endif
		return strUnicode;
	}


private:
	//sc文件操作句柄
    UGint m_handler;
	//scd文件操作句柄
	UGint m_dhandler;
	//scd文件操作句柄对应的FileID
	UGint m_scdFileID;

	//文件头结束位置
    //UGPosType m_HeadPos;

	//文件头内容
    ArchiveHead m_head;

	//索引开始位置(包括索引信息头)
	UGPosType m_idxBegin;

	//sc文件路径
	UGString m_scPath;
	//scd文件路径
	//UGString m_scdPath;

	//加解密密钥
	UGbyte btXorOld[256];

	//是否需要转换字节序
	UGbool m_bNeedSwap;

	CacheFileDirection m_efileDir;

#ifdef WIN32
	//lock文件句柄
	//UGint m_lh;
	HANDLE m_lh;

	//lock文件文件名
	UGString m_lockFileName;
#endif

#ifdef ENABLE_CACHE_FILE_LOG
	//日志文件
	UGint m_hLogFile;
#endif //ENABLE_CACHE_FILE_LOG

};

inline UGbool UGCacheFile::WriteArchiveSubHead(UGint handle ,UGint pos ,ArchiveSubHead head)
{	
	if(m_efileDir == CF_OnlyRead)// 只读
		return FALSE;

	UGASSERT(handle != -1);
	UGASSERT(head.DataLen > 0 && head.FileNameLen > 0);
	UGint errCode;

	errCode = UGseek(handle ,pos ,SEEK_SET);
	UGASSERT(errCode != -1);
	if(m_bNeedSwap)
	{
		SwapBytesArchiveSubHead(head);
	}
	ReMakeStream((UGbyte*)&head ,sizeof(ArchiveSubHead) ,btXorOld);
	errCode = UGwrite(handle ,&head ,sizeof(ArchiveSubHead));
	UGASSERT(errCode >= 0);
	
	return TRUE;
}

inline UGbool UGCacheFile::ReadArchiveSubHead(UGint handle ,UGint pos ,ArchiveSubHead &head)
{
	UGASSERT(handle != -1);
	UGint errCode;

	errCode = UGseek(handle ,pos ,SEEK_SET);
	UGASSERT(errCode != -1);
	errCode = UGread(handle ,&head ,sizeof(ArchiveSubHead));
	UGASSERT(errCode >= 0);
	ReMakeStream((UGbyte*)&head ,sizeof(ArchiveSubHead) ,btXorOld);
	if(m_bNeedSwap)
	{
		SwapBytesArchiveSubHead(head);
	}
	return TRUE;
}

inline UGbool UGCacheFile::GetDataFileHandle(UGint fileid ,UGint& handle ,UGbool& bNeedClose)
{
	if(fileid < 0)
		return FALSE;

	handle = m_dhandler;
	bNeedClose = FALSE;
	if( fileid != m_scdFileID)
	{
		//打开新的文件
		UGString scdpath;
		scdpath.Format(_U("%s%02X") ,m_scPath.Cstr() ,fileid);
		if(m_efileDir == CF_OnlyRead)
		{
			handle = UGopen(scdpath.Cstr() ,O_RDONLY | UGBINARY ,999);
		}
		else
		{
			handle = UGopen(scdpath.Cstr() ,O_RDWR | UGBINARY ,999);
		}
		if(handle == -1)
		{
			return FALSE;
		}
		bNeedClose = TRUE;
	}
	return TRUE;
}

}

#endif

