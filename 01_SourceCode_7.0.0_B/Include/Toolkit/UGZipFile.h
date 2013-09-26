//  实现对zip文件的操作
//  UGZipFile 是用来向Zip文件中写文件的。
// 	#define APPEND_STATUS_CREATE        (0)
// 	#define APPEND_STATUS_CREATEAFTER   (1)
// 	#define APPEND_STATUS_ADDINZIP      (2)
// 	Create方法对应的是APPEND_STATUS_CREATE
// 	Open方法对应的是APPEND_STATUS_ADDINZIP
//
//  UGunZipFile 是用来从Zip读取文件内容的。

#ifndef UGZIPFILE_H
#define UGZIPFILE_H

#include "Stream/UGMemoryStream.h"
namespace UGC {

class TOOLKIT_API UGZipFile
{
enum UGZipAppendStatus
{
	UGZipAppendStatusCreate = 0,
	UGZipAppendStatusCreateAfter = 1,
	UGZipAppendStatusAddInZip = 2
};

public:
	UGZipFile();
	~UGZipFile();
	// 打开zip文件
	// param strFilePath[in] zipfile的路径
	// param strPWD[in] 密码
	// param appendStatus[in] 操作zip的状态
	UGbool Open(const UGString& strFilePath, const UGString& strPWD = _U(""), UGZipFile::UGZipAppendStatus appendStatus = UGZipFile::UGZipAppendStatusCreate);

	// 关闭zip文件
	UGbool Close();

	// 添加文件
	// param strFileNameInZip[in] zip中文件的名称包括路径。
	// param strFileName[in] 要被添加的文件
	UGbool AddFile(const UGString& strFileNameInZip, const UGString& strFileName);

	// 添加stream到zip中
	// param strFileNameInZip[in] zip中文件的名称包括路径。
	// param stream [in] 要添加的stream
	UGbool AddFile(const UGString& strFileNameInZip, UGMemoryStream& stream);

	// 添加文件夹
	// param strForlderPath[in] 文件夹
	// param strForlderPathInZip[in] 在Zip中文件夹的相对路径
	UGbool AddForlder(const UGString& strForlderPath, const UGString& strRelPath = _U(""));
private:
	// 向Zip中添加空文件夹
	// param strFolderPathInZip[in]  Zip中的文件夹位置
	// remark 空文件夹和文件的区分就在于文件夹是zip_fileinfo.external_fa等于16 ，文件是32 和winrar一致
	UGbool AddEmptyFolder(const UGString& strFolderPathInZip);
private:
	UGZipFile(const UGZipFile&);
	UGZipFile& operator=(const UGZipFile&);
private:
	// zipFile类型
	void* m_pZipFile;
	enum
	{
		KEYLENGTH=256,
	};
	// zip 密码 采用UTF8编码
	UGachar m_pPassWord[KEYLENGTH];
};

class TOOLKIT_API UGunZipFile
{
public:
	UGunZipFile();
	~UGunZipFile();
	// 打开zip文件
	// param strFilePath[in] zip文件路径
	// param strPWD[in] 密码
	UGbool Open(const UGString& strFilePath, const UGString& strPWD=_U(""));

	// 关闭zip文件
	UGbool Close();

	// 得到文件的stream
	// param strFileNameInZip[in] zip文件中的名称包含路径
	// param stream[out] 得到的流
	UGbool GetFile(const UGString& strFileNameInZip, UGMemoryStream& stream);

	// 得到文件
	// param strFileNameInZip[in] zip中的文件名称
	// param strFileName[in] 要输出的文件名称，(全路径)
	UGbool GetFile(const UGString& strFileNameInZip, const UGString& strFileName);

	// 得到文件夹
	// param strRelFolderPath[in] 文件夹的路径
	// param strFolderPahth[in] 解压到的文件夹的路径
	UGbool GetFolder(const UGString& strRelFolderPathInZip, const UGString& strForlderPath);

private:
	UGunZipFile(const UGunZipFile&);
	UGunZipFile& operator=(const UGunZipFile&);
private:
	// zipFile类型
	void* m_pZipFile;
	enum
	{
		KEYLENGTH=256,
	};
	// zip 密码 采用utf8编码
	UGachar m_pPassWord[KEYLENGTH];
};


}
#endif

