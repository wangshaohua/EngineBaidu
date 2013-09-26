//////////////////////////////////////////////////////////////////////////
//                    _   _   ____   ____                    
//   Project         | | | | / ___) / ___)                   
//                   | | | || | __ | |                       
//                   | |_| || |_\ || \___                    
//                    \____/ \____| \ ___)     2.0           
//                                                           
//!  \file UGHttpHelper.h
//!  \brief  Http助手，提供Web数据源使用到的Http请求及解析的相关操作。
//!  \details 文件详细信息。
//!  \author UGC Team。
//!  \attention 
//!   Copyright (c) 2000-2010 SuperMap Software Co., Ltd. <br> 
//!   All Rights Reserved.
//!  \version 2.0
//////////////////////////////////////////////////////////////////////////

#ifndef UGHTTPHELPER_H
#define UGHTTPHELPER_H

#include "Stream/ugexports.h"
#include "Stream/ugdefs.h"
#include "Stream/ugplatform.h"
#include "Toolkit/UGThread.h"
#include "NetToolkit/UGGeoSpatialDownloadRequest.h"
#include "Stream/UGByteArray.h"

// 解决vc6下编译Windows.h winsock.h mswsock.h winsock2.h之间的相关包含造成编译不过的问题
#ifdef WIN32
	#if(_WIN32_WINNT >= 0x0400)
		#ifndef WIN32_LEAN_AND_MEAN
		#define WIN32_LEAN_AND_MEAN
		#endif
	#endif
#endif

namespace UGC
{
	typedef UGint (*CURLWirteDataFunc)(void *buffer, UGuint size, UGuint nmemb, void *stream);

	typedef UGint (*CURLProgressFunc)(void *buffer, double dltotal, double dlnow);

class NETTOOLKIT_API UGCurl
{
public:
	friend class UGCurlPool;


	enum UGCurlType
	{
		//未知
		UnKnown     =0,
		//下载
		Download	=1,
		//上传
		Upload		=2,
	};

	//! \brief 初始化用于下载的curl handle
	//! \param writedatapara curl下载时的数据
	//! \param writefunc curl下载回调写入函数
	//! \param pUrl url字符串
	//! \param strUser 用户名
	//! \param strPW 密码
	void InitializeEasyHandle2WriteData(void* writeDataPara, CURLWirteDataFunc writeFunc, const char* pUrl, const UGString& strUser, const UGString& strPasswd);


	//! \brief 初始化用于post的curl handle 上传字符串，注意不是文件。
	//! \param strURL 服务器URL地址[in]。
	//! \param strPOSTFIELDS 要向服务端上传的字符串[in]。
	//! \param strUser 登录服务器用户名,匿名访问置空[in]。
	//! \param strPasswd 登录服务器用密码,匿名访问置空[in]。
	void InitializeEasyHandle2Post(const char* pPostFields, const char* pUrl, const UGString& strUser = _U(""), const UGString& strPasswd = _U(""));


	//! \brief 初始化用于建立连接的的curl handle 仅用于建立连接。
	//! \param strURL 服务器URL地址[in]。
	//! \param strUser 登录服务器用户名,匿名访问置空[in]。
	//! \param strPasswd 登录服务器用密码,匿名访问置空[in]。
	void InitializeEasyHandle2Connect(const char* pUrl, const UGString& strUser = _U(""), const UGString& strPasswd = _U(""));

	//! \brief 初始化用于下载的curl handle
	//! \param writedatapara curl下载时的数据
	//! \param writefunc curl下载回调写入函数
	//! \param progressFunc curl下载回调进度函数
	//! \param localFileLen curl下载续写位置
	//! \param pUrl url字符串
	//! \param strUser 用户名
	//! \param strPW 密码
	void InitializeEasyHandle2BreakWriteData(void* writeDataPara, CURLWirteDataFunc writeFunc, CURLProgressFunc progressFunc, UGlong localFileLen,
		const char* pUrl, const UGString& strUser, const UGString& strPasswd);

	//! \brief 执行请求
	//! \return 是否成功
	UGbool Perform();

	//! \brief 得到HTTP头中的content-type
	//! \return content-type
	UGString GetContentType();

	//! \brief 得到HTTP返回码
	//! \return HTTP返回码
	UGint GetResponseCode();

	//! \brief 得到HTTP连接的套接字
	//! \return 套接字
	UGlong GetLastSocket();

	//! \brief 处理下载请求的返回码
	//! \param nRespCode http协议的返回码
	//! \param strURL 用于说明的url，可以为空
	UGbool ResovleCURLCode(UGlong nRespCode, const UGString& strURL);

	//! \brief 释放控制权,返还用过的Curl给CurlPool
	void Release();

private:
	UGCurl();
	~UGCurl();

	//typedef void CURL;
	void* m_pCurl;
	UGbool m_bUsing;
	UGCurlType m_CurlType;
};


class NETTOOLKIT_API UGCurlPool
{
public:
	//得到空闲的Curl
	UGCurl* GetIdleCurl();
	UGCurl* GetIdleCurl(UGCurl::UGCurlType curlType);

	UGCurlPool();
	~UGCurlPool();

private:
	UGArray<UGCurl*> m_arrCurl;
	UGMutex m_mutex;
};


class NETTOOLKIT_API SyncThreadMap : public UGDict<UGuint, UGuint>
{
public:
	SyncThreadMap()
	{
		
	}
	virtual ~SyncThreadMap(){};
	void inline Lock()
	{
		m_mutex.lock();
	}
	void inline Unlock()
	{
		m_mutex.unlock();
	}
protected:
	UGMutex m_mutex;
};

class NETTOOLKIT_API UGHttpHelper
{
	friend UGbool UGSTDCALL DownLoadSmCacheCallBack(void* pHandeler);
	friend UGbool UGSTDCALL DownLoadPureFilesCallBack(void* pHandeler);

public:
	//! \brief  装填thread的id值，并在多线程异步批量下载的时候如果检测到所在线程id值存在于容器中，则跳出循环，迅速结束
	//! \remarks 其实使用std::set更合适，但考虑到时间因素以及UGC暂未提供UGSet实现，所以采用std::map来实现了，无非多占用空间。
	//! \remarks 由于考虑到要在多线程之间共享，所以std::map要配合上一个锁。
	static SyncThreadMap ms_threadmap;


	static UGCurlPool ms_curlPool;

public:
	//! \brief  默认的构造函数
	UGHttpHelper();
	//! \brief  默认的析构函数
 	virtual ~UGHttpHelper();

	//! \brief 请求方式的枚举值
	enum RequestMethod
	{
		//Get方式
		GET = 0,	
		//post方式
		POST = 1    
	};

	//! \brief http文件的类型
	enum HttpFileType
	{	
		//文本文件
		CHARACTER = 0,  	
		//二进制文件
		BINARY = 1	
	};

	//! \brief 协议的类型
	enum ProtocolType
	{ 
		//ftp
		FTP = 1,
		//gopher
		GOPHER = 2,	
		//http
		HTTP = 3	
	};

	enum ErrorType
	{
		SUCCESS = 0,
		ERROR_REQUEST	= 1,
		NO_RESOURCE		= 2,
		NO_ACCESS		= 3,
		ERROR_PASSWORD	= 4,
		ERROR_INSERVER	= 5,
		CANNOT_CONNECT	= 6,
		UNKNOWN			= 7,
	};

	//! \brief 通过URL请求得到服务器响应文件。
	//! \param strURL 服务器URL地址[in]。
	//! \param strUser 登录服务器用户名,匿名访问置空[in]。
	//! \param strPasswd 登录服务器用密码,匿名访问置空[in]。
	//! \param reqMmethod http请求方式,post或get,默认置空[in]。
	//! \param fileType 请求文件流格式,二进制或文本,默认置空[in]。
	//! \return 请求得到的文件路径和文件名,存放在临时路径。
	//! \remarks 。
	//! \attention 。
	static UGString RequestFile(UGString strURL, UGString strUser, 
								UGString strPasswd, RequestMethod reqMmethod, 
								HttpFileType fileType);

	//! \brief 通过URL请求得到服务器响应文件。
	//! \param strURL 服务器URL地址[in]。
	//! \param strUser 登录服务器用户名,匿名访问置空[in]。
	//! \param strPasswd 登录服务器用密码,匿名访问置空[in]。
	//! \param reqMmethod http请求方式,post或get,默认置空[in]。
	//! \param fileType 请求文件流格式,二进制或文本,默认置空[in]。
	//! \param strFileContext 文件的MIME格式[out]。
	//! \return 请求得到的文件路径和文件名,存放在临时路径。
	//! \remarks 。
	//! \attention 
	static UGString RequestFile(UGString strURL, UGString strUser, 
								UGString strPasswd, RequestMethod reqMmethod, 
								HttpFileType fileType,UGString& strFileContext);

	//! \brief 通过URL请求得到服务器响应文件并保存到指定路径。
	//! \param strURL 服务器URL地址[in]。
	//! \param strDstPath 请求得到的文件的地址和文件名[in]。
	//! \param strUser 登录服务器用户名,匿名访问置空[in]。
	//! \param strPasswd 登录服务器用密码,匿名访问置空[in]。
	//! \param reqMmethod http请求方式,post或get,默认置空[in]。
	//! \param fileType 请求文件流格式,二进制或文本,默认置空[in]。
	//! \return 是否成功得到文件,成功返回TRUE,失败返回FALSE。。
	//! \remarks 。
	//! \attention 。
	static UGbool RequestFile2(UGString strURL,UGString strDstPath, 
							   UGString strUser, UGString strPasswd, 
							   RequestMethod reqMmethod, HttpFileType fileType);

	//! \brief 通过URL请求得到服务器响应文件并保存到指定路径。
	//! \param strURL 服务器URL地址[in]。
	//! \param strUser 登录服务器用户名,匿名访问置空[in]。
	//! \param strPasswd 登录服务器用密码,匿名访问置空[in]。
	//! \param reqMmethod http请求方式,post或get,默认置空[in]。
	//! \param fileType 请求文件流格式,二进制或文本,默认置空[in]。
	//! \param pBitArrayData 存放数据的BitArray[out]。
	//! \param eErrorType 错误类型[out]。
	//! \return 是否成功得到文件,成功返回TRUE,失败返回FALSE。。
	//! \remarks 。
	//! \attention 。
	static UGbool RequestFile2ByteArray(UGString strURL, UGString strUser, UGString strPasswd, 
		RequestMethod reqMmethod, HttpFileType fileType, 
		UGByteArray* pBitArrayData, UGint& eErrorType, void* curl);


	//! \brief 向指定的服务端上传字符串，注意不是文件。
	//! \param strURL 服务器URL地址[in]。
	//! \param strPOSTFIELDS 要向服务端上传的字符串[in]。
	//! \param strUser 登录服务器用户名,匿名访问置空[in]。
	//! \param strPasswd 登录服务器用密码,匿名访问置空[in]。
	//! \return 上传成功返回true。
	static UGbool PostFields(UGString strURL, UGString strPOSTFIELDS, UGString strUser, 
		UGString strPasswd);

	//! \brief 通过URL请求以断点续传形式得到服务器响应文件并保存到指定路径。
	//! \param strURL 服务器URL地址[in]。
	//! \param strDstPath 请求得到的文件的地址和文件名[in]。
	//! \param progressFunc 下载进度回调函数[in]。
	//! \param strUser 登录服务器用户名,匿名访问置空[in]。
	//! \param strPasswd 登录服务器用密码,匿名访问置空[in]。
	//! \return 是否成功得到文件,成功返回TRUE,失败返回FALSE。。
	//! \remarks 。
	//! \attention 。
	static UGbool RequestFileByBreakpoint(UGString strURL, UGString strDstPath, CURLProgressFunc progressFunc, UGString strUser, UGString strPasswd);

	//! \brief 向指定的服务端上传文件。
	//! \param strURL 服务器URL地址[in]。
	//! \param strFilename 要向服务端上传的文件名[in]。
	//! \param strUser 登录服务器用户名,匿名访问置空[in]。
	//! \param strPasswd 登录服务器用密码,匿名访问置空[in]。
	//! \return 上传成功返回true。
// 	static UGbool PostFile(UGString strURL, UGString strFilename, UGString strUser, 
// 		UGString strPasswd);

	//! \brief 向指定的服务端更改文件。
	//! \param strURL 服务器URL地址[in]。
	//! \param strFilename 要向服务端上传的文件名[in]。
	//! \param strUser 登录服务器用户名,匿名访问置空[in]。
	//! \param strPasswd 登录服务器用密码,匿名访问置空[in]。
	//! \return 上传成功返回true。
// 	static UGbool PutFile(UGString strURL, UGString strFilename, UGString strUser, 
// 		UGString strPasswd);

    //! \brief 下载文件为大文件缓存格式(一个一个序列式下载)
    //! \param downloadRequests	文件请求的数组
	//! \param strUser 登录服务器用户名,匿名访问置空[in]。
	//! \param strPasswd 登录服务器用密码,匿名访问置空[in]。
	//! \param strCacheAccesswd 大文件缓存访问密码，若没有密码则为空[in]。
	//! \param pWebDownloadCurl 反馈下载进度[in]。
	//! \remarks 内部使用到了SyncThreadMap。
	//! \remarks 对downloadRequests只改变内部的下载成功标签，其他均不改变
	static void RequestFile2SmCacheST(UGArray<UGGeoSpatialDownloadRequest>& downloadRequests,UGString strUser, UGString strPasswd,UGString strCacheAccesswd,void* pWebDownloadCurl, UGbool bIsIndex = true);

	//! \brief 下载文件为大文件缓存格式(内部使用多线程)
	//! \param downloadRequests	文件请求的数组
	//! \param strUser 登录服务器用户名,匿名访问置空[in]。
	//! \param strPasswd 登录服务器用密码,匿名访问置空[in]。
	//! \param strCacheAccesswd 大文件缓存访问密码，若没有密码则为空[in]。
	//! \param pWebDownloadCurl 反馈下载进度[in]。
	//! \remarks 内部使用到了SyncThreadMap。
	//! \remarks 对downloadRequests只改变内部的下载成功标签，其他均不改变
	//! \remarks 内部启动多个线程进行下载，数据保存为大文件缓存格式。若数组中只有一个成员，就不要使用这个接口了，反而浪费效率。
	static void RequestFile2SmCacheMT(UGArray<UGGeoSpatialDownloadRequest>& downloadRequests, UGString strUser, UGString strPasswd, UGString strCacheAccesswd,void* pWebDownloadCurl);

	//! \brief 下载多个文件(内部使用多线程)
	//! \param strURLs	文件请求的数组
	//! \param strFileNames 请求得到的文件的地址和文件名数组
	//! \param strUser 登录服务器用户名,匿名访问置空[in]。
	//! \param strPasswd 登录服务器用密码,匿名访问置空[in]。
	//! \remarks 内部使用到了SyncThreadMap。
	//! \remarks 内部启动多个线程进行下载，数据保存为指定格式。若数组中只有一个成员，就不要使用这个接口了，反而浪费效率。
	static void RequestFilesMT(const UGArray<UGString>& strURLs, const UGArray<UGString>& strFileNames, UGString strUser, UGString strPasswd);

    //! \brief 检测服务端地址是否有效
    //! \param strURL 服务器URL地址[in]。
	//! \param strUser 登录服务器用户名,匿名访问置空[in]。
	//! \param strPasswd 登录服务器用密码,匿名访问置空[in]。
    //! \return 若服务端地址有效则返回true
	static UGbool IsHostValide(UGString strURL, UGString strUser = _U(""), UGString strPasswd = _U(""));

	//! \brief URL参数解析。
	//! \param pstrURL URL字符串[in]。
	//! \param dwServiceType 网络协议种类[out]。
	//! \param strServer 网络服务器名或IP地址[out]。
	//! \param strObject URL中的Path和查询选项[out]。
	//! \param nPort 端口号[out]。
	//! \return 是否解析成功,成功返回TRUE,失败返回FALSE。
	static UGbool UGParseURL(UGString strURL, UGuint& dwServiceType, 
							 UGString& strServer, UGString& strObject, 
							 UGushort& nPort );

	//! \brief URL参数解析。
	//! \param pstrURL URL字符串[in]。
	//! \param dwServiceType 网络协议种类[out]。
	//! \param strServer 网络服务器名或IP地址[out]。
	//! \param strPath URL中的Path[out]。
	//! \param strPath URL中的查询选项[out]。
	//! \param nPort 端口号[out]。
	//! \return 是否解析成功,成功返回TRUE,失败返回FALSE。
	static UGbool UGParseURL2(UGString strURL, UGuint& dwServiceType, 
							  UGString& strServer, UGString& strPath, 
							  UGString& strQuery, UGushort& nPort);

	//! \brief URL参数解析。
	//! \param pstrURL URL字符串[in]。
	//! \param strServerPath URL中的ServerName、Port、Path串[out]。
	//! \param strQuery URL中的查询选项[out]。
	//! \return 是否解析成功,成功返回TRUE,失败返回FALSE。
	static UGbool UGParseURL3(UGString strURL, 
							  UGString& strServerPath, UGString& strQuery);	
	
	//! \brief URL转化成基地址和查询键值对。
	//! \param strURLsrc 源URL字符串[in]。
	//! \param strBaseURL 基地址[out]。
	//! \param dictQueryPairs 标准的查询选项[out]。
	//! \return 是否成功转化,成功返回TRUE,失败返回FALSE。
	//! \remarks 。
	//! \attention 。
	static UGbool URLtoKVPairs(const UGString& strURLsrc,
							   UGString& strBaseURL, UGDict<UGString,UGString>& dictQueryPairs);	

	//! \brief 基地址和查询键值对转化成URL。
	//! \param strBaseURL 基地址[in]。
	//! \param dictQueryPairs 标准的查询选项[in]。
	//! \param strURLdes 转化成目的URL[out]。
	//! \return 是否成功转化,成功返回TRUE,失败返回FALSE。
	static UGbool KVPairstoURL(const UGString& strBaseURL, 
		const UGDict<UGString,UGString>& dictQueryPairsUGString, 
							   UGString& strURLdes);	

	//! \brief 从URL中得到四至信息。
	//! \param strURL 请求的URL字符串[in]。
	//! \param rcGeoRef 四至信息[out]。
	//! \return 是否解析成功,成功返回TRUE,失败返回FALSE。
	static UGbool GetBBox(const UGString& strURL,UGRect2D& rcGeoRef);

	//! \brief 比较两个XML标签名称是否意义相同。
	//! \param strTagLeft 左值[in]。
	//! \param strTagRight 右值[in]。
	//! \return 是否相同。
	static UGbool SameXMLTag(const UGString& strTagLeft, const UGString& strTagRight);	

	//! \brief 获取XML标签的命名空间。
	//! \param strTag XML标签[in]。
	//! \return 命名空间。
	static UGString TagNameSpace(const UGString& strTag);	

	//! \brief 测试一个OGC Web数据源的请求是否成功。
	//! \param strURL OGC Web数据源的请求,包括GetCapabilitys,DescribFeature等[in]。
	//! \param strUser Http访问的用户名[in]。
	//! \param strPasswd Http访问的密码[in]。
	//! \return 成功返回TRUE,失败返回FALSE。。
	static UGint CheckOGCRequest(UGString strURL,
								  UGString strUser = _U(""),UGString strPasswd= _U(""));

	//! \brief 初始化curl_global_init()
	static void Global_Init();

	//! \brief cleanup curl_global
	static void Global_Cleanup();

	//! \brief 初始化curl_easy
	static void* Easy_Init();
	
	//! \brief 清除crul_easy
	static void Easy_Cleanup(void* curl);
private:

	static UGMBString URLEncode(const UGachar* pCurl);

    //! \brief 处理下载请求的返回码
    //! \param nCurlcode curl的返回码
    //! \param nRespCode http协议的返回码
    //! \param strURL 用于说明的url，可以为空
	static UGbool ResovleCURLCode(UGlong nCurlcode, UGlong nRespCode, const UGString& strURL);

	//! \brief 处理下载请求的返回码
	//! \param nCurlcode curl的返回码
	//! \param nRespCode http协议的返回码
	//! \param strURL 用于说明的url，可以为空
	static ErrorType GetErrorType(UGlong nCurlcode, UGlong nRespCode, const UGString& strURL);

    //! \brief 初始化用于下载的curl handle
    //! \param easyhanle curl handle句柄，不能为空
    //! \param writedatapara curl下载时的数据
    //! \param writefunc curl下载回调写入函数
    //! \param pUrl url字符串
    //! \param strUser 用户名
    //! \param strPW 密码
    //! \param UGbool bEncoded 是否对Url编码加密，默认是false不加密
    //! \return 是否初始化成功
	static UGbool InitializeEasyHandle2WriteData(void * easyhanle, void* writedatapara, CURLWirteDataFunc writefunc, const char * pUrl, const UGString& strUser, const UGString& strPW);

	//! \brief 替换特殊字符
	//! \param strURL url字符串
	static void ReplaceSpecialChar(UGString& strURL);
};
	
}
#endif // !defined(UGHTTPHELPER_H)

