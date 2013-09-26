//////////////////////////////////////////////////////////////////////////
//                    _   _   ____   ____                    
//   Project         | | | | / ___) / ___)                   
//                   | | | || | __ | |                       
//                   | |_| || |_\ || \___                    
//                    \____/ \____| \ ___)     6.0           
//                                                           
//!  \file headerfile.h
//!  \brief Class 的接口定义。
//!  \details 该文件定义了紧凑文件访问的所有接口。
//!  \author 基础内核组。
//!  \attention 
//!   Copyright (c) 1996-2008 SuperMap Software Limited Company.  <br> 
//!   All Rights Reserved.
//!  \version 6.0
//////////////////////////////////////////////////////////////////////////
#ifndef __SUPERMAP_UGC_AHCOMPACTFILE_H__INCLUDE_
#define __SUPERMAP_UGC_AHCOMPACTFILE_H__INCLUDE_

#include "Stream/ugdefs.h"
#include "Stream/UGByteArray.h"
#include "Stream/UGFile64.h"
#include "Stream/UGFile32.h"
#include "Stream/UGFileStream.h"
#include "Stream/UGCacheFile.h"
#include "Toolkit/UGThread.h"
#include "Toolkit/UGProcess.h"
#include "Toolkit/UGTextCodec.h"


namespace UGC {
typedef UGint UGResult;

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
#define UG_FILE_HEADER_FLAG "CF"
#define UG_COMPACTFILE_EXT _U(".cf")

// 每个Grid索引项所具有的字节大小 第一个高字节表示状态, 后面七个表示偏移量
#define UGC_CFGRID_IDXSIZE 8
// 每个Naming索引项所具有的字节大小 第一个高字节表示状态 中间七个表示偏移量 最后8个表示hashcode
#define UGC_CFNAMING_IDXSIZE 16

#define UGC_CF_INIT_VERSION 20111111
#define UGC_CF_UNICODE_VERSION 20120214 

#if defined(WIN32) && _MSC_VER <= 1200
#define UGC_CF_POS_MASK 0x00FFFFFFFFFFFFFF
#else
#define UGC_CF_POS_MASK 0x00FFFFFFFFFFFFFFLL
#endif
#define UGC_CF_POSBIT 56

#define  UGC_CF_NAMING_POSBIT 112

#define CF_IDXVALUE(CFSTAT, CFPOS) (((UGulong)CFSTAT << UGC_CF_POSBIT) | CFPOS)

//! \brief 得到Index的项的值赋值给指向IndexData的指针
//! \param INDEXDATA起始地址UGbyte*
//! \param INDEX序号
//! \return 对应的偏移 
//! \remarks 8代表的是UGulong的字节长度
#define CF_NAMING_IDXVALUE(INDEXDATA, INDEX) (((*(UGulong*)(INDEXDATA+INDEX*UGC_CFNAMING_IDXSIZE))))
//! \brief 得到Index的项的HASHCODE
//! \param INDEXDATA起始地址UGbyte*
//! \param INDEX序号
//! \return 在IndexData中存储的Index项
//! \remark 8是由于在索引项的最后8个字节存储的是hashcode，见UGC_CFNAMING_IDXSIZE
#define CF_NAMING_IDXHASHCODE(INDEXDATA, INDEX) ((*(UGulong*)(INDEXDATA+INDEX*UGC_CFNAMING_IDXSIZE+8)))


//! \brief 紧凑文件
class COMPACTFILE_API UGCompactFile
{

public:
	//! \brief 描述紧凑文件中存储的指定文件的状态
	enum UGStatus
	{
		CF_NotExist = 0x00,	//	文件不存在
		CF_Exist = 0x01,		//	文件存在
		CF_Incomplete = 0x02,	//	文件不完整
		CF_Unknown = 0x04,	//　异常状态
	};
	//! \brief 紧凑文件的索引方式
	enum UGIndexMode
	{
		CF_GRID=0,		// 网格索引方式
		CF_NAMING=1,	// 命名索引方式
		CF_MIXED=2,		// 混合索引方式，支持多种索引方式共存
		CF_CACHEFILE =3, //代表当前文件是一个cachefile
	};
	
	//! \brief 紧凑文件的打开方式
	enum UGOpenMode
	{
		CF_OM_ForceDestroy = 0x00000001, //如果文件存在，则删掉文件，新建立一个文件
		CF_OM_ReadOnly = 0x00000002, //只读方式打开文件，
		CF_OM_ReadWrite = 0x00000004, //读写方式打开文件
		CF_OM_Single = 0x00000008, //独占打开文件，文件只能被打开一次，
	};

	//! \brief 加密用到的常量
	enum
	{
		CF_KeyLength = 256,
		CF_NAMEBYTELEN = 256
	};

	// 在命名索引中使用，存放hashcode到索引数据中的索引index
	typedef UGDict<UGulong,UGint> UGHashCodeMap;
//! \brief 索引头中用到的选项
	enum
	{
		CF_OP_VERSION = 0x00000001, // 是否已启用版本
	};

public:
	#pragma pack(1)
	//! \breif CF文件头结构
	struct CFHeader
	{
	public:
		CFHeader()
		{
			m_cFlag[0] = UG_FILE_HEADER_FLAG[0];
			m_cFlag[1] = UG_FILE_HEADER_FLAG[1];
			m_bEndian = 0;
			m_nVersion = UGC_CF_INIT_VERSION;
			m_tmUpdate = 0.0;
			m_eIndexMode = CF_GRID;
			m_nIndexPosition = 0;
			memset(m_pPlaceholder,0,37);
		}
		UGachar m_cFlag[2];
		UGbyte m_bEndian;	// 字节序，为1表示Big-Endian，为0表示Little-Endian
		UGuint m_nVersion;  // UGC_CF_UNICODE_VERSION版本在Naming模式下采用了Unicode编码。
		UGuint m_eIndexMode;
		UGdouble m_tmUpdate;
		UGulong m_nIndexPosition;
		UGuchar m_pPlaceholder[37];	//　占位符,让文件头的大小达到64字节
	};
	#pragma pack()

	#pragma pack(4)
	struct CFGridDataIndexHeader
	{
		CFGridDataIndexHeader()
		{
			m_nIndexRow = 0;
			m_nIndexColumn = 0;
			m_nFlags = 0;
		}
		UGuint m_nIndexRow;
		UGuint m_nIndexColumn;
		UGuint m_nFlags;
	};
	#pragma pack()

	#pragma pack(4)
	// 命名方式的索引结构
	struct CFNamingDataIndexHeader
	{
		CFNamingDataIndexHeader()
		{
			m_nIndexCapacity = 0;
			m_nIndexLength = 0;
			m_dMaxSize = 0.0;
			m_dReservedSize = 0.0;
			m_nFlags = 0;
		}
		// 命名索引中预设的索引个数(容量)
		UGulong  m_nIndexCapacity;
		// 命名索引的实际长度
		UGulong  m_nIndexLength;
		// 命名索引的最大大小，大于这个大小要删除
		UGdouble m_dMaxSize;
		// 命名索引的保留长度
		UGdouble m_dReservedSize;
		// 状态
		UGuint m_nFlags;
	};
	#pragma pack()

	struct CFVersion
	{
		UGulong m_nVersionNum;
		// 状态信息和位置偏移的综合体
		UGulong m_nDataPos;
	};
	//! \brief CF中Gird索引的数据存储格式
	struct CFGridData
	{
		CFGridData()
		{
			m_nTotalLength = 0;
			m_nDataCapacity = 0;
			m_nDataLength = 0;
			m_pData = NULL;
			m_nVersionCount = 0;
			m_pVersions = NULL;
		}
		UGulong m_nTotalLength;
		UGulong m_nDataCapacity;
		UGulong m_nDataLength;
		UGbyte *m_pData;
		// 下面两个成员用于表示启用版本后，数据的版本信息，在没有版本时，不存储下面的两个数据
		UGuint m_nVersionCount;
		CFVersion *m_pVersions;
	};

	// 命名数据结构
	//! \brief CF中Naming索引的数据存储格式
	struct CFNamingData
	{
		CFNamingData()
		{
			m_nTotalLength = 0;
			m_nCodeType = 0;
			m_nNameByteLength = 0;
			m_pName = NULL;	
			m_nDataCapacity = 0;
			m_nDataLength = 0;
			m_pData = NULL;
			m_nVersionCount = 0;
			m_pData = NULL;
			m_pVersions = NULL;
		}
		UGulong m_nTotalLength;
		UGint m_nCodeType;
		UGuint m_nNameByteLength;  // 字节长度
		UGchar *m_pName;
		// 数据的总大小
		UGulong m_nDataCapacity;
		// 数据的实际大小
		UGulong m_nDataLength;
		// 实际的数据
		UGbyte *m_pData;
		// 下面两个成员用于表示启用版本后，数据的版本信息，在没有版本时，不存储下面的两个数据
		UGuint m_nVersionCount;
		CFVersion *m_pVersions;
	};

public:
    //! \brief 构造函数
    UGCompactFile();

    //! \brief 析构函数
    ~UGCompactFile();

private:
	UGCompactFile(const UGCompactFile &in);
	UGCompactFile &operator=(const UGCompactFile&);

public:
	//! \brief	创建格网索引方式的紧凑文件，需要指定格网的行列数，一旦指定，不能修改
	//! \param	&strCFPath[in] 创建文件路径。
	//! \param 	nRowNum[in] 格网索引文件的行数
	//! \param 	nColNum[in] 格网索引文件的列数
	//! \param 	&strPwd[in] 解析密码
	//! \param	&eOpenMode[in] 打开文件的模式。CF_OM_ReadOnly在create接口中不起作用
	//			CF_OM_ReadWrite如果没有指定，也是默认带上的
	//! \return	返回结果码(带错误状态)，注意，要跟UGE_SUCCESS(0)判断，不能直接当Bool判断，因为结果完全相反。
	//! \remarks 如果创建一个文件strCFPath不带扩展名字，则自动给他添加上标准扩展名字UG_COMPACTFILE_EXT
	//! \remarks 不要创建以sc为结尾的文件，这样会导致打开判断失败。
	UGResult Create(const UGString &strCFPath, UGuint nRowNum, UGuint nColNum, const UGString &strPwd=_U(""),UGOpenMode eOpenMode = CF_OM_ReadWrite);

	//! \brief 	创建命名索引方式的紧凑文件 
	//! \param 	参数：&strCFPath[in] 创建文件路径。
	//! \param 	nInitialSize[in] 命名索引方式的初始索引数目
	//! \param 	&strPwd[in] 解析密码
	//! \param	&eOpenMode[in] 打开文件的模式。CF_OM_ReadOnly在create接口中不起作用
	//			CF_OM_ReadWrite如果没有指定，也是默认带上的
	//! \return	返回结果码(带错误状态)，注意，要跟UGE_SUCCESS(0)判断，不能直接当Bool判断，因为结果完全相反。
	//! \remarks 如果创建一个文件strCFPath不带扩展名字，则自动给他添加上标准扩展名字UG_COMPACTFILE_EXT
	//! \remarks 不要创建以sc为结尾的文件，这样会导致打开判断失败。
	UGResult Create(const UGString &strCFPath, UGuint nInitialSize=5120, const UGString &strPwd=_U(""), UGOpenMode eOpenMode = CF_OM_ReadWrite);

	//! \brief	打开文件
	//! \param	参数：&strPathin] 打开文件路径。
	//! \param	&strPwd[in] 打开所需密码
	//! \param	&eOpenMode[in] 打开文件的模式，CF_OM_ForceDestroy 这个模式Open接口中不起作用,CF_OM_ReadWrite 
	//			CF_OM_ReadOnly两个必须指定其中一个，如果没有指定，则默认按照CF_OM_ReadWrite打开
	//! \return	返回结果码(带错误状态)，注意，要跟UGE_SUCCESS(0)判断，不能直接当Bool判断，因为结果完全相反。
	//! \remarks	紧凑缓存文件必须已存在
	//! \remarks 对于CacheFile文件则是 Open接口。
	//! \remarks  如果打开一个CacheFile，只通过扩展名字".sc"进行判断。如果不是扩展名则按照平常方式打开。
	//! \remarks 如果创建一个文件strCFPath不带扩展名字，则自动给他添加上标准扩展名字UG_COMPACTFILE_EXT
	UGResult Open(const UGString& strPath, const UGString& strPwd=_U(""),UGOpenMode eOpenMode = CF_OM_ReadWrite);

	//! \brief	判断是否已经打开文件。
	//! \return	返回是否已经打开，是个bool值，可以直接判断 。
	//! \remarks 对于CacheFile文件则是 IsOpen接口。
	UGbool IsOpen();

	//! \brief	关闭文件(不一定总是要调用，在类析构的时候会自动调用)
	//! \param 析构资源
	//! \return	是否关闭成功
	//! \remarks 对于CacheFile文件则是 Close接口。
	UGbool Close();

	//! \brief	设置密码
	//! \param	&strNewPwd[in] 设定新密码
	//! \return	返回：是否设置成功
	//! \remarks 对于CacheFile文件则是 SetPassword接口。
	UGbool SetPassword(const UGString& strNewPwd);

	//! \brief	向格网索引方式的紧凑文件中添加一个二进制流
	//! \param	nRow[in] 格网索引文件的行号
	//! \param	nCol[in] 格网索引文件的列号
	//! \param	&context[in] 要添加的内容
	//! \param	lDataSize[in] 表示context完整数据的大小.考虑断点续传的情况,如果context表示的内容不完整,也要写到紧凑文件中
	//! \param	lOffset[in] 表示context写入紧凑缓存时的偏移位
	//! \param  nVersionNum[in] 版本号
	//! \return	返回值：返回结果码(带错误状态)，注意，要跟UGE_SUCCESS(0)判断，不能直接当Bool判断，因为结果完全相反。
	//! \remarks	注意：该操作仅适用于格网索引方式的紧凑文件.同时该方法也支持设置纯色的数据,即当字节流的长度小于64位时,字节流的长度表示颜色的位数,字节流的内容表示颜色值.
	UGResult SetAt(UGuint nRow, UGuint nCol, const UGByteArray & context, UGulong lDataSize = 0, UGulong lOffset = 0, const UGulong nVersionNum = 0);

	//! \brief	向格网索引方式的紧凑文件中添加一个文件
	//! \param	nRow[in] 格网索引文件的行号
	//! \param	nCol[in] 格网索引文件的列号
	//! \param	&strFilePath[in] 要添加的文件的绝对路径
	//! \param  nVersionNum[in] 版本号
	//! \return	返回结果码(带错误状态)，注意，要跟UGE_SUCCESS(0)判断，不能直接当Bool判断，因为结果完全相反。
	//! \remarks	该操作仅适用于格网索引方式的紧凑文件
	UGResult SetAt(UGuint nRow, UGuint nCol, const UGString &strFilePath, const UGulong nVersionNum = 0);

	//! \brief	从格网索引方式的紧凑文件中读取指定的文件,以二进制流方式记录
	//! \param	nRow[in] 格网索引文件的行号
	//! \param	nCol[in] 格网索引文件的列号
	//! \param	&context[out] 读取的二进制流
	//! \param	&lValidByte[out] context中有效的字节数,正常情况下context的长度与lValidByte相同,但考虑到对于单个文件的断点续传要求,通过该参数来描述该数据是否完整
	//! \param  nVersionNum[in]版本号，如果没有该版本查询出来的就是最新版本
	//! \return	返回结果码(带错误状态)，注意，要跟UGE_SUCCESS(0)判断，不能直接当Bool判断，因为结果完全相反。
	//! \remarks	该操作仅适用于格网索引方式的紧凑文件
	UGResult Lookup(UGuint nRow, UGuint nCol, UGByteArray &context, UGulong &lValidByte, const UGulong nVersionNum = 0);


	//! \brief	从格网索引方式的紧凑文件中移除指定的文件
	//! \param	nRow[in] 格网索引文件的行号
	//! \param	nCol[in] 格网索引文件的列号
	//! \param  nVersionNum[in]版本号如没有该版本返回UGE_SUCCESS
	//! \return	返回结果码(带错误状态)，注意，要跟UGE_SUCCESS(0)判断，不能直接当Bool判断，因为结果完全相反。
	//! \remarks	该操作仅适用于格网索引方式的紧凑文件,移除文件不会释放相应的空间,需要调用相应的紧缩空间的方法
	UGResult Remove(const UGuint nRow, const UGuint nCol, const UGulong nVersionNum = 0);

	//! \brief	从格网索引方式的紧凑文件中查询指定的文件,包括不存在,存在,文件不完整和异常几种状态
	//! \param	nRow[in] 格网索引文件的行号
	//! \param	nCol[in] 格网索引文件的列号
	//! \return	返回标识指定文件在紧凑文件中的状态 
	//! \remarks	该操作仅适用于格网索引方式的紧凑文件
	UGStatus GetStatus(UGuint nRow, UGuint nCol);

	//! \brief	向命名索引方式的紧凑文件中添加一个二进制流
	//! \param	&strName[in] 准备添加的内容在紧凑缓存中的命名,也是作为读取该文件的唯一标识
	//! \param	&context[in] 要添加的内容
	//! \param	lDataSize[in] 表示context完整数据的大小.考虑断点续传的情况,如果context表示的内容不完整,也要写到紧凑文件中
	//! \param	lOffset[in] 表示context写入紧凑缓存时的偏移位置
	//! \param  nVersionNum[in]版本号
	//! \return	返回结果码(带错误状态)，注意，要跟UGE_SUCCESS(0)判断，不能直接当Bool判断，因为结果完全相反。
	//! \remarks	该操作仅适用于命名索引方式的紧凑文件,[暂不支持纯色]同时该方法也支持设置纯色的数据,即当字节流的长度小于64位时,字节流的长度表示颜色的位数,字节流的内容表示颜色值.
	//! \文件中存储的流的格式是：总长度不包括记录总长度的UGulong
	//! \ 总长度[UGulong]+名称的编码格式[UGuint]+名称长度[UGuint]+名称+文件大小[UGulong]+文件真实大小[UGulong]+数据
	//! \remarks 对于CacheFile文件则是 AddFile(const UGByteArray& context, const UGString& archivePath);
	//				archivePath 对应 strName，context 对应 contex
	UGResult SetAt(const UGString &strName , const UGByteArray & context, UGulong lDataSize = 0, UGulong lOffset = 0, const UGulong nVersionNum = 0);


	//! \brief	向命名索引方式的紧凑文件中添加一个二进制流
	//! \param	&strName[in] 准备添加的内容在紧凑缓存中的命名,也是作为读取该文件的唯一标识
	//! \param	&strFilePath[in] 要添加的文件的绝对路径
	//! \param  nVersionNum[in]版本号
	//! \return	返回结果码(带错误状态)，注意，要跟UGE_SUCCESS(0)判断，不能直接当Bool判断，因为结果完全相反。
	//! \remarks	该操作仅适用于命名索引方式的紧凑文件
	//! \remarks 对于CacheFile文件则是 AddFile(const UGByteArray& context, const UGString& archivePath);
	//				archivePath 对应 strName，strFilePath 对应 strName
	UGResult SetAt(const UGString &strName, const UGString &strFilePath, const UGulong nVersionNum = 0);

	//! \brief	从命名索引方式的紧凑文件中以二进制流方式读取文件
	//! \param	&strName[in] 文件在紧凑缓存中的命名
	//! \param	&context[out] 二进制流结果
	//! \param	&lValidByte[out] context中有效的字节数,正常情况下context的长度与lValidByte相同,但考虑到对于单个文件的断点续传要求,通过该参数来描述该数据是否完整
	//! \param  nVersionNum[in]版本号，如果没有该版本就返回最新版本
	//! \return	返回结果码(带错误状态)，注意，要跟UGE_SUCCESS(0)判断，不能直接当Bool判断，因为结果完全相反。
	//! \remarks	该操作仅适用于命名索引方式的紧凑文件
	//! \remarks 对于CacheFile文件则是 ReadFile(const UGString& filepath, UGByteArray& context);
	//		     和 IsFileExist(const UGString& archivePath); 相当于 UGResult的not found
	UGResult Lookup(const UGString &strName, UGByteArray &context, UGulong &lValidByte, const UGulong nVersionNum = 0);

	//! \brief	从命名索引方式的紧凑文件中移除指定的文件
	//! \param	&strName[in] 文件在紧凑缓存中的命名
	//! \param  nVersionNum[in] 版本号
	//! \return	返回结果码(带错误状态)，注意，要跟UGE_SUCCESS(0)判断，不能直接当Bool判断，因为结果完全相反。
	//! \remarks	该操作仅适用于命名索引方式的紧凑文件
	//! \remarks 对于CacheFile文件则是 RemoveFile(const UGString& filepath, FILE_TYPE file_type = NORMAL ,UGbool reconstruction=FALSE);
	UGResult Remove(const UGString &strName, const UGulong nVersionNum = 0);

	//! \brief	返回紧凑文件的索引类型
	//! \param	nRow[out] 当索引类型为Grid时,表示行数;当索引类型为Naming时,表示索引容量;
	//! \param	nCol[out] 当索引类型为Grid时,表示列数;当索引类型为Naming时,表示索引实际数量;
	//! \return 返回索引类型。
	//! \remarks	该操作仅适用于命名索引方式的紧凑文件
	//! \remarks 对于CacheFile文件则是 GetStatus( CacheFileStatus &status ,UGbool& bNeedReconstruction );
	//      nRow 表示 status.NumOfFiles，nCol 表示 status.NumOfValidFiles,返回 CF_CACHEFILE
	UGIndexMode GetIndexInfo(UGuint &nRow, UGuint &nCol);

	//! \brief	从命名索引方式的紧凑文件中查询指定的文件,包括不存在,存在,文件不完整和异常几种状态
	//! \param	&strName[in] 文件在紧凑缓存中的命名
	//! \return	返回标识指定文件在紧凑文件中的状态 
	//! \remarks	该操作仅适用于命名索引方式的紧凑文件
	UGStatus GetStatus(const UGString &strName);

	//! \brief 查询命名索引中有效数据的名称列表
	//! \param aryList[out] 名称列表
	//! \remarks 对于CacheFile文件则是 ListFiles接口
	UGbool GetValidNamingList(UGArray<UGString> &aryList);

	//! \brief	设置命名索引方式的紧凑文件的最紧凑大小和回收空间时保留的空间大小
	//! \param	dMaxSize[in] 紧凑文件的最紧凑大小
	//! \param	dReserveSize[in] 回收空间时保留的空间大小
	//! \return 
	//! \remarks	该操作仅适用于命名索引方式的紧凑文件
	void SetMaxSize(UGdouble dMaxSize, UGdouble dReserveSize);

	//! \brief	是否启动紧凑文件的版本化功能,启用版本化后,文件更新后,旧文件将以版本方式保留,版本以时间戳的方式记录
	//! \param	bEnable[in] 是否启用版本化,True启用,False禁用
// 	void EnableVersion(UGbool bEnable);

	//! \brief 是否已启用版本
	UGbool IsVersionEnabled();
	
	//! \brief	对紧凑文件进行空闲空间的回收
	//! \param	
	//! \return	返回结果码(带错误状态)，注意，要跟UGE_SUCCESS(0)判断，不能直接当Bool判断，因为结果完全相反。
	//! \remarks 对于CacheFile文件则是 Reconstruction接口
	UGResult Compact();

	//! \brief	检查当前进程是否有死锁现象
	//! \param	
	//! \return	返回true，对于单进程，如果返回TRUE，有死锁现象。如果返回FLASE，则没有死锁现象。
	//					  对于多进程，多线程程序 ，如果返回TRUE，则有进程或线程正在读写。
	UGbool IsDeadLocked();

	//!\ brief 把缓冲中的数据写入文件
	UGbool Flush();

	UGString GetFullPath();

private:
	UGbool CreateGrid(UGuint nRowNum, UGuint nColNum);
	UGbool CreateNaming(UGuint nInitialSize);
	UGbool ProcessLockInit();


	//! \brief	是否启用批量写入,以提高写入的性能
	//! \param	
	//! \return	
	void BulkAdd(UGbool bStart);

	void BulkFlush();

	void BulkRollback();

public: // 加密相关
	//! \brief 生成密钥
	//! \param pwd[in] 密码
	//! \return 生成的密钥
	static UGint GenerateKey(const UGchar *pwd);

	//! \brief 交换字节
	//! \param c1, c2要交换的字节
	//! \return 
	static void SwapByte(UGbyte& c1, UGbyte& c2);

	//! \brief 生成stream
	//! \param pStream[out] 要生成的流
	//! \param nKey[in] 密钥
	static void GenerateStream(UGbyte *pStream, UGint nKey);

	//! \brief 生成Xor字符串
	//! \param pDes[out]要生成的Xor字符串
	//! \param pSrc[in]源字符串
	static void GenerateXorString(UGbyte* pDes, UGbyte* pSrc);

	//! \brief 解密Xor字符串
	//! \param pDes[out]要被解密的Stream
	//! \param nLength[in]长度
	//! \param pXor[in]要被xor计算的字符串
	static void ReMakeStream(UGbyte* pDes, UGint nLength ,UGbyte *pXor);

private: // HashCode相关、命名索引相关
	//! \brief 将字符串转换为UGint值，在存储根据文件名得到内容时使用
	//! \param strIn[in] 要被转换的字符串
	//! \return 得到的哈希码
	UGulong GetHashCode(const UGString& strIn);

	//! \brief 得到文件中已经存储的Hashcode到文件项Index的Map
	//! \param pIndexData 存储的那块索引的内存
	//! \return 填充到m_HashCodeMap中
	UGbool InitHashCodeMap(const UGbyte* pIndexData);

	//! \brief 更新命名索引中的索引部分
	//! \param status[in]索引对应数据的状态以区别是否是断点续传或者版本管理 
	//! \param nDatapos[in]数据位置
	//! \param nHashCode[in]对应的哈希值
	//! \remarks 当索引的个数大于预设索引个数的情况下将预设的索引增加一倍
	UGbool UpdateNamingIndex(UGStatus status, UGulong nDatapos, UGulong nHashCode);

	//! \brief 在添加条目等于预设条目的时候要进行索引的自增
	//! \remark 自增的情况只适用于Naming模式
	UGbool IncreaseNamingIndexCapacity();

	//! \brief 在命名索引模式下得到数据块中存储的String(主键)
	//! \param nIndex[in]索引项数据的偏移
	//! \param nByteLen[out] m_pName中的字节长度
	//! \remark 在判断重码时用到，填充m_strName变量
	UGbool GetKeyString(UGint nIndex, UGint& nByteLen);

	//! \brief 在有重码的情况下重新得到HashCode和数据偏移量
	//! \param strName[in]作为主键存储的name
	//! \param nNewHashCode[out]新的要被设定的HashCode
	//! \param nNewIndexValue[out]新的要被设定的偏移量
	UGbool ReSetHashCodeAndIndexValue(const UGString strName,UGulong& nNewHashCode, UGulong& nNewIndexValue);

	//! \brief 得到下一个重码的hashcode的值
	//! \param nHashCode 当前哈希值
	//! \remark 重码情况下的在高字节加一后的hashcode
	UGulong GetNextHashCode(UGulong nOldHashCode);

	//! \brief 得到重码的个数
	//! \param nHashCode 当前的哈希值 这个必须是从名称得到的HashCode,高字节是0X00.
	UGint GetSameHashCodeCount(UGulong nCurHashCode);
	
private:
	UGbool GetGridIdxValue(UGuint nRow, UGuint nCol, UGulong &nIdxValue);

	//! \brief 得到Naming索引项
	//! \param strName[in] 文件名称
	//! \param nIdxValue[out] 得到的索引项的值
	//! \param nHashCode[out] 得到字符串的哈希值
	UGbool GetNamingIdxValue(const UGString &strName, UGulong &nIdxValue, UGulong &nHashCode);

	//! \brief 把数据读入交换空间(m_cfDataSwap)中
	UGbool ReadDataFromDataFile(UGulong nDataPos);

	//! \brief 把交换空间(m_cfDataSwap)中的数据写入文件
	UGulong WriteDataToDataFile(UGulong nDataPos, UGbool bFileEnd = FALSE);

	//! \brief 更新内存中的数据
	UGbool UpdateSwapData(const UGByteArray & context, UGulong lDataSize, UGulong lOffset, UGulong nDataPos);
	
	UGByteArray* GetSwapData();

	//! \brief得到数据更新的情况,和版本顺序
	//! \param &nUpDatetatus[out]得到要进行处理的情况目前是：1, 2, 3, 4
	//! \param &nVersionOrder[out]要处理的版本的顺序
	//! \param &nUpdateDatapos[out]这个是要更新的位置
	//! \param &nDataOffset[out]在添加中间版本时，要插入版本的偏移量
	//! \param nVersionNump[in]版本号
	//! \remarks // 1.添加最新版本数据,2.添加中间版本数据,3.更新当前版本数据,4.更新之前版本数据，
	//! \5.无版本的数据更新, 0.无版本的添加数据。目前没有无版本的情况 
	UGbool GetStatusAndVersionOrder(UGuint& nUpdateStatus, UGuint& nVersionOrder, UGulong &nUpdateDatapos, UGulong& nDataOffset, const UGulong nDataPos, const UGulong nVersionNum);

	//! \brief添加新版本数据:
	//! param &status[out]数据的状态
	//! param context[in]要传的数据
	//! param lDataSizeIn[in]数据大小
	//! param nVersionNum[in]版本号
	//! param strKeyString[in]naming模式下的主键，仅对naming模式下有用
	//! remark 添加新数据 添加最新版本数据，
	//! nUpdataStatus状态:了解数据更新的情况,分为几种状态:1.添加最新版本数据,2.添加中间版本数据,3.更新当前版本数据,4.更新之前版本数据, 5.无版本的数据更新, 0.无版本的添加数据
	UGulong AddMaxNewVersionData(UGStatus& status, const UGByteArray& context, const UGulong lDataSizeIn, const UGulong nOffset, const UGulong nVersionNum, UGString strKeyString=_U(""));

	//! \brief添加新版本数据:
	//! param context[in]要传的数据
	//! param lDataSizeIn[in]数据大小
	//! param nVersionOrder[in]数据偏移
	//! param nVersionNum[in]版本号
	//! remark 添加新数据 添加最新版本数据，添加中间版本数据
	//! nUpdataStatus状态:了解数据更新的情况,分为几种状态:1.添加最新版本数据,2.添加中间版本数据,3.更新当前版本数据,4.更新之前版本数据, 5.无版本的数据更新, 0.无版本的添加数据
	UGulong AddOldVersionData(const UGByteArray& context, const UGulong lDataSizeIn, const UGulong nOffset, const UGulong nVersionOrder, const UGulong nVersionNum);

	//! \brief 更新之前版本的数据 分为断点续传和覆盖的情况
	//! \param nUpdataDataPos[in]要更新的数据位置
	//! \param nDataPos[in]最大版本在文件中的位置
	//! \param nDataPosOffset[in]更新中间版本时，要更新的版本在最新版本中的偏移
	//! \param context[in]数据内容
	//! \param lDataSizeIn[in]数据完整大小
	//! \param lOffset[in]偏移
	//! \remarks针对UpdateStatus为4的情况:更新之前版本数据
	UGbool UpdateOlderVersion(UGulong& nUpdateDataPos, const UGulong nDataPos, const UGulong nDataPosOffset,const UGByteArray& context, const UGulong lDataSizeIn, const UGulong lOffset);

	//! \brief 添加新数据
	//! \param stauts[out]状态
	//! \param context[in]要被添加的内容
	//! \param DataSize[in]数据大小
	//! \param nOffset[in]偏移
	//! \param nVersionNum[in]版本号
	//! \param strKeyString[in]只有在Naming模式下这个才有用,naming模式的主键
	UGulong AddNewData(UGStatus& status, const UGByteArray& context, const UGulong nDataSize, const UGulong nOffset, const UGulong nVersionNum, UGString strKeyString=_U(""));

//多进程控制代码
	UGbool LookUp_Inner(UGulong nDataPos, UGByteArray & context, UGulong &lValidByte, const UGulong nVersionNum );
public:
	//如果有写者刷心缓存，则刷新索引
	UGResult RefreshIndex();
private:
	//! \brief 根据Charset得到TextCodec，用于在存储命名索引时，将索引存储为Unicode
	//! \param to 字符串编码
	//! \param from 字符串编码
	UGTextCodec* GetTextCodec(UGMBString::Charset to, UGMBString::Charset from);

private:
	UGbool ReadIndex();
	//进程读写锁 不支持可重入调用
	UGProcess m_processRWLock;

	//主要用于在RefreshIndex中是否，防止在Refresh外面加锁，然后又在Refresh里面加锁，导致循环嵌套的问题
	// 紧缩时，用m_bRefreshIndexing标记是否已加进程锁
	UGbool m_bRefreshIndexing;
private:
	// 文件句柄
	UGFile64 m_fileHandle;

	CFHeader m_header;
	CFGridDataIndexHeader m_headerGrid;
	CFNamingDataIndexHeader m_headerNaming;

	UGuchar *m_pIndexData;
	UGbool m_bNeedSwap;
	UGbool m_bOpend;

	//! \brief 用于临时存储一个数据,减少内存分配的次数,用Dict存储，每个线程对应一个
	OgdcDict<UGuint, UGByteArray*> m_dictDataSwap;
	UGMutex m_mutex;

	// 存放在命名模式下Hashcode和索引项Index的Map
	UGHashCodeMap m_HashCodeMap;
	
	// 加密密钥
	UGbyte m_btXorOld[CF_KeyLength];

	// 对于命名索引来说，存储数据块的索引(KeyString)，不用总是new。
	// 对于第一版本而言，这里存储的是的非Unicodes的编码。对于Unicode版本来说，他存储的是Unicode的索引
	UGbyte m_pName[CF_NAMEBYTELEN];
	
	// 这个作为临时的一块缓冲区用
	UGbyte m_pTemp[CF_NAMEBYTELEN];

	UGString m_strFilePath;
	UGString m_strPassword;
	UGOpenMode m_nOpenMode;
	UGCacheFile* m_pCacheFile;

	// UGulong 存储的是To~~From的charset
	UGDict<UGulong, UGTextCodec*>m_dictTextCodec;

};


//! \brief 紧凑文件解析器
class COMPACTFILE_API UGCompactFileReader
{
public:
	UGCompactFileReader();
	~UGCompactFileReader();

public:
	//! \brief	打开文件
	//! \param	参数：&strPathin] 打开文件路径。
	//! \param	&strPwd[in] 打开所需密码
	//! \param	&eOpenMode[in] 打开文件的模式，CF_OM_ForceDestroy 这个模式Open接口中不起作用,CF_OM_ReadWrite 
	//			CF_OM_ReadOnly两个必须指定其中一个，如果没有指定，则默认按照CF_OM_ReadWrite打开
	//! \return	返回结果码(带错误状态)，注意，要跟UGE_SUCCESS(0)判断，不能直接当Bool判断，因为结果完全相反。
	//! \remarks	紧凑缓存文件必须已存在
	//! \remarks 对于CacheFile文件则是 Open接口。
	//! \remarks  如果打开一个CacheFile，只通过扩展名字".sc"进行判断。如果不是扩展名则按照平常方式打开。
	//! \remarks 如果创建一个文件strCFPath不带扩展名字，则自动给他添加上标准扩展名字UG_COMPACTFILE_EXT
	UGResult Open(const UGString& strPath, const UGString& strPwd = _U(""), UGCompactFile::UGOpenMode eOpenMode = UGCompactFile::CF_OM_ReadWrite);

	//! \brief	判断是否已经打开文件。
	//! \return	返回是否已经打开，是个bool值，可以直接判断 。
	//! \remarks 对于CacheFile文件则是 IsOpen接口。
	UGbool IsOpen();

	//! \brief	关闭文件(不一定总是要调用，在类析构的时候会自动调用)
	//! \param 析构资源
	//! \return	是否关闭成功
	//! \remarks 对于CacheFile文件则是 Close接口。
	UGbool Close();

	//! \brief	从格网索引方式的紧凑文件中读取指定的文件,以二进制流方式记录
	//! \param	nRow[in] 格网索引文件的行号
	//! \param	nCol[in] 格网索引文件的列号
	//! \param	&context[out] 读取的二进制流
	//! \param	&lValidByte[out] context中有效的字节数,正常情况下context的长度与lValidByte相同,但考虑到对于单个文件的断点续传要求,通过该参数来描述该数据是否完整
	//! \param  nVersionNum[in]版本号，如果没有该版本查询出来的就是最新版本
	//! \return	返回结果码(带错误状态)，注意，要跟UGE_SUCCESS(0)判断，不能直接当Bool判断，因为结果完全相反。
	//! \remarks	该操作仅适用于格网索引方式的紧凑文件
	UGResult Lookup(UGuint nRow, UGuint nCol, UGByteArray &context, UGulong &lValidByte, const UGulong nVersionNum = 0);

	//! \brief	从格网索引方式的紧凑文件中查询指定的文件,包括不存在,存在,文件不完整和异常几种状态
	//! \param	nRow[in] 格网索引文件的行号
	//! \param	nCol[in] 格网索引文件的列号
	//! \return	返回标识指定文件在紧凑文件中的状态 
	//! \remarks	该操作仅适用于格网索引方式的紧凑文件
	UGCompactFile::UGStatus GetStatus(UGuint nRow, UGuint nCol);

private:
	UGResult ReadHeader();
	UGResult ReadHeaderGrid();

	UGbool ReadIndexValue(UGuint nRow, UGuint nCol, UGulong &nIdxValue);

private:
	// 文件句柄
	UGFile32 m_fileHandle;

	UGCompactFile::UGOpenMode m_nOpenMode;
	UGCompactFile::CFHeader m_header;
	UGCompactFile::CFGridDataIndexHeader m_headerGrid;

	UGbool m_bNeedSwap;
	UGbool m_bOpend;

	// 加密密钥
	UGbyte m_btXorOld[UGCompactFile::CF_KeyLength];

	UGString m_strFilePath;
	UGString m_strPassword;

};


//! \brief 紧凑文件保存器
class COMPACTFILE_API UGCompactFileWriter
{
public:
	UGCompactFileWriter();
	~UGCompactFileWriter();

public:
	//! \brief	创建格网索引方式的紧凑文件，需要指定格网的行列数，一旦指定，不能修改
	//! \param	&strCFPath[in] 创建文件路径。
	//! \param 	nRowNum[in] 格网索引文件的行数
	//! \param 	nColNum[in] 格网索引文件的列数
	//! \param 	&strPwd[in] 解析密码
	//! \param	&eOpenMode[in] 打开文件的模式。CF_OM_ReadOnly在create接口中不起作用
	//			CF_OM_ReadWrite如果没有指定，也是默认带上的
	//! \return	返回结果码(带错误状态)，注意，要跟UGE_SUCCESS(0)判断，不能直接当Bool判断，因为结果完全相反。
	//! \remarks 如果创建一个文件strCFPath不带扩展名字，则自动给他添加上标准扩展名字UG_COMPACTFILE_EXT
	//! \remarks 不要创建以sc为结尾的文件，这样会导致打开判断失败。
	UGResult Create(const UGString &strCFPath, UGuint nRowNum, UGuint nColNum, const UGString &strPwd=_U(""), UGCompactFile::UGOpenMode eOpenMode = UGCompactFile::CF_OM_ReadWrite);

	//! \brief	打开文件
	//! \param	参数：&strPathin] 打开文件路径。
	//! \param	&strPwd[in] 打开所需密码
	//! \param	&eOpenMode[in] 打开文件的模式，CF_OM_ForceDestroy 这个模式Open接口中不起作用,CF_OM_ReadWrite 
	//			CF_OM_ReadOnly两个必须指定其中一个，如果没有指定，则默认按照CF_OM_ReadWrite打开
	//! \return	返回结果码(带错误状态)，注意，要跟UGE_SUCCESS(0)判断，不能直接当Bool判断，因为结果完全相反。
	//! \remarks	紧凑缓存文件必须已存在
	//! \remarks 对于CacheFile文件则是 Open接口。
	//! \remarks  如果打开一个CacheFile，只通过扩展名字".sc"进行判断。如果不是扩展名则按照平常方式打开。
	//! \remarks 如果创建一个文件strCFPath不带扩展名字，则自动给他添加上标准扩展名字UG_COMPACTFILE_EXT
	UGResult Open(const UGString& strPath, const UGString& strPwd = _U(""), UGCompactFile::UGOpenMode eOpenMode = UGCompactFile::CF_OM_ReadWrite);

	//! \brief	判断是否已经打开文件。
	//! \return	返回是否已经打开，是个bool值，可以直接判断 。
	//! \remarks 对于CacheFile文件则是 IsOpen接口。
	UGbool IsOpen();

	//! \brief	关闭文件(不一定总是要调用，在类析构的时候会自动调用)
	//! \param 析构资源
	//! \return	是否关闭成功
	//! \remarks 对于CacheFile文件则是 Close接口。
	UGbool Close();

	//! \brief	向格网索引方式的紧凑文件中添加一个二进制流
	//! \param	nRow[in] 格网索引文件的行号
	//! \param	nCol[in] 格网索引文件的列号
	//! \param	&context[in] 要添加的内容
	//! \param	lDataSize[in] 表示context完整数据的大小.考虑断点续传的情况,如果context表示的内容不完整,也要写到紧凑文件中
	//! \param	lOffset[in] 表示context写入紧凑缓存时的偏移位
	//! \param  nVersionNum[in] 版本号
	//! \return	返回值：返回结果码(带错误状态)，注意，要跟UGE_SUCCESS(0)判断，不能直接当Bool判断，因为结果完全相反。
	//! \remarks	注意：该操作仅适用于格网索引方式的紧凑文件.同时该方法也支持设置纯色的数据,即当字节流的长度小于64位时,字节流的长度表示颜色的位数,字节流的内容表示颜色值.
	UGResult SetAt(UGuint nRow, UGuint nCol, const UGByteArray & context, UGulong lDataSize = 0, UGulong lOffset = 0, const UGulong nVersionNum = 0);

	//! \brief	从格网索引方式的紧凑文件中查询指定的文件,包括不存在,存在,文件不完整和异常几种状态
	//! \param	nRow[in] 格网索引文件的行号
	//! \param	nCol[in] 格网索引文件的列号
	//! \return	返回标识指定文件在紧凑文件中的状态 
	//! \remarks	该操作仅适用于格网索引方式的紧凑文件
	UGCompactFile::UGStatus GetStatus(UGuint nRow, UGuint nCol);

	UGString GetFilePath();

private:
	UGResult ReadHeader();
	UGResult ReadHeaderGrid();
	UGResult WriteHeader();
	UGResult WriteHeaderGrid(UGuint nRowNum, UGuint nColNum);

	UGbool WriteIndexValue(UGuint nRow, UGuint nCol, UGulong nIdxValue);
	UGbool ReadIndexValue(UGuint nRow, UGuint nCol, UGulong &nIdxValue);

	//! \brief 添加新数据
	//! \param stauts[out]状态
	//! \param context[in]要被添加的内容
	//! \param DataSize[in]数据大小
	//! \param nOffset[in]偏移
	//! \param nVersionNum[in]版本号
	//! \param strKeyString[in]只有在Naming模式下这个才有用,naming模式的主键
	UGulong WriteDataToFile(UGCompactFile::UGStatus& status, const UGByteArray& context, UGulong nDataSize, UGulong nOffset, UGulong nVersionNum, UGulong nDataPos);

	//! \brief 是否已启用版本
	UGbool IsVersionEnabled();

	//!\ brief 把缓冲中的数据写入文件
	UGbool Flush();

private:
	// 文件句柄
	UGFile32 m_fileHandle;

	UGCompactFile::UGOpenMode m_nOpenMode;
	UGCompactFile::CFHeader m_header;
	UGCompactFile::CFGridDataIndexHeader m_headerGrid;

	UGbool m_bNeedSwap;
	UGbool m_bOpend;

	// 加密密钥
	UGbyte m_btXorOld[UGCompactFile::CF_KeyLength];

	UGString m_strFilePath;
	UGString m_strPassword;

};

}

#endif

