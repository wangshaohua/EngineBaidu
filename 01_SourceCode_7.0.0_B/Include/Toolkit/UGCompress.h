#ifndef UGCOMPRESS_H
#define UGCOMPRESS_H
#include "Stream/ugdefs.h"

namespace UGC {

//! \brief 压缩算法类。
//! \remarks 目前仅提供Zip的压缩和解压缩。
class TOOLKIT_API UGCompress  
{
public:
	//! \brief Zip 压缩函数
	/** \details 根据C++编码规范,目的参数在前,源参数在后,故而对Sm30中参数的位置和名称做了相应的改动
	压缩数据参数说明
	void *pvDestBuffer: 目标内存区域 ,dwDestLen: 目标内存区域大小
	const void *pvSrcBuffer: 源数据; UGuint dwSrcLen:源数据长度
	
	  目标内存区域需要事先开辟，至少要有 dwSrcLen * 1% + 12,	进行压缩后，
	  dwDestLen可以用compressBound函数进行计算；
	  内存的大小会改变，dwDestLen 传出改变后的大小;
	  pvSrcBuffer和pvDestBuffer不能相同
	  参数UGint nLevel 可以取1到9之间的整数.
	  nLevel越小，压缩过程中用的内存最少，但是压缩速度慢，压缩率低;
	  nLevel越大，压缩过程中用的内存最多，但是压缩速度快，压缩率高;
	  
		compress returns Z_OK if success, Z_MEM_ERROR if there was not enough
		memory, Z_BUF_ERROR if there was not enough room in the output buffer,
		Z_STREAM_ERROR if the level parameter is invalid.
		compress2 (dest, dwDesLen, source, dwDesLen, level)
	*/
	  //!  \brief Toolkit
	static UGbool Zip(UGbyte *pvDestBuffer, UGuint &dwDestLen, 
		const UGbyte *pvSrcBuffer, UGuint dwSrcLen, UGint nLevel=8);
	
	//! \brief UnZip解压缩函数
	/** \details 根据C++编码规范,目的参数在前,源参数在后,故而对Sm30中参数的位置和名称做了相应的改动
	解压缩数据参数说明
	void *pvDestBuffer: 目标内存区域 ,dwDestLen: 目标内存区域大小
	const void *pvSrcBuffer: 源数据; UGuint dwSrcLen:源数据长度
	
	  目标内存区域需要事先开辟，至少要有 dwSrcLen * 101% + 12,进行解压缩后，
	  内存的大小会改变，dwDestLen传出改变后的大小;
	  pvSrcBuffer和pvDestBuffer不能相同
	  Decompress returns Z_OK if success, Z_MEM_ERROR if there was not
	  enough memory, Z_BUF_ERROR if there was not enough room in the output
	  buffer, or Z_DATA_ERROR if the input data was corrupted.
	*/
	  //!  \brief Toolkit
	static UGbool UnZip(UGbyte *pvDestBuffer, UGuint &dwDestLen, 
		const UGbyte *pvSrcBuffer, UGuint dwSrcLen);

	//!  \brief 用于计算进行压缩时所需要开辟的目标存储区域的大小
	//!  \param nSrcSize 需要压缩的源buf的大小
	//!  \return 压缩后的存储区域所需开辟的存储空间的最大可能大小
	static UGint CompressBound(UGint nSrcSize);
	
	//!  \brief 用于压缩文件或者文件夹下内容，在磁盘上生成zip格式文件
	//! \param strSrcPath  要压缩文件或者文件夹在磁盘上的路径[in]
	//! \param strDesPath  输出zip文件在磁盘上的路径，默认是空，则与源文件在同级目录下[in]
	//! \remarks 暂不考虑向已经生成好的zip包里附加或者覆盖，CRC32校验，密码，不忽略文件路径信息。
	//!          压缩比率是最好，目前Win32平台可以压缩单个文件或者文件夹内所有文件，其他平台可以压缩单个文件，对于文件夹内没有嵌套文件夹的情况也可以压缩
	//! \return  压缩成功返回true。
	static UGbool MiniZip(const UGString& strSrcPath, const UGString& strDesPath = _U(""));

	//! \brief 解压缩zip格式的压缩包，在同级磁盘目录下生成压缩包内的文件夹以及文件。
	//! \param strName [in] zip文件在磁盘上的路径。同样这里也没有开放出来其他解压路径。
	//! \param bOutHere 默认为true，即同级目录解压，false时解压到由zip文件名命名的文件夹内
	//! \return 解压缩成功返回true。没有记录解压出来的文件结构，但可以使用UGFile::FindFileExtPaths来进行二次查找
	static UGbool MiniUnZip(const UGString& strFileName,UGbool bExtractHere = TRUE);

	//! \brief   用于压缩内存,压缩算法7zip
	//! \return  压缩成功返回true
	static UGbool Compress7Zip(UGbyte *pvDestBuffer, UGuint &dwDestLen,const UGbyte *pvSrcBuffer, UGuint dwSrcLen);

	//! \brief   用于解压缩内存,压缩算法7zip
	//! \return 解压缩成功返回true
	static UGbool UnCompress7Zip(UGbyte *pvDestBuffer, UGuint &dwDestLen, 
		const UGbyte *pvSrcBuffer, UGuint dwSrcLen);

	//! \brief 用于压缩文件或者文件夹下内容，在磁盘上生成7-zip格式文件
	//! \param arraySrcPath [in] 需要压缩的文件路径数组。
	//! \param targetFileName [in] 压缩的目标文件。后缀名如果没有的话默认为.7z
	//! \param strPassword [in] 压缩文件设置密码,如果不设可以不用设置
	//! \param bOverWrite[in] 目标文件不存在会新建,如果已经存在bOverWrite=true会删除原来文件再重新创建,bOverWrite=flase的话会往原来的文件中追加
	//! \return  压缩成功返回true
	static UGbool Compress7ZipFile(const UGArray<UGString>& arraySrcPath, const UGString& strTargetFileName,const UGString& strPassword=_U(""),UGbool bOverWrite=TRUE);

	//! \brief 解压缩7-zip格式的压缩包，在目标目录下解压
	//! \param strFileName[in]需要解压的7zip文件,后缀名不一定是.7z
	//! \param targetFloder[in]需要解压的的目标文件夹
	//! \param strPassword [in] 解压密码,如果没有不用设置
	//! \return 解压缩成功返回true
	static UGbool UnCompress7ZipFile(const UGString& strFileName,const UGString& strTargetFloder,const UGString& strPassword=_U(""));

public:

	UGCompress() {m_uzFile = NULL;};

	virtual ~UGCompress() {};
private:
	
	UGbool OpenZip(const UGString& szFilePath, UGbool bAppend = FALSE);

	UGbool CloseZip(); 

	UGbool AddFileToZip(const UGString& szFilePath, const UGString& strRelPath = _U(""), UGbool bIgnoreFilePath = FALSE);
	
	UGbool AddFolderToZip(const UGString& szFolderPath, const UGString& strRelPath = _U(""), UGbool bIgnoreFilePath = FALSE);

	UGulong GetAttribute(const UGString& strPath);

	UGbool GetStatus(const UGString& strFileName, UGTime& statustime);

private:

	void* m_uzFile;
};

}

#endif


