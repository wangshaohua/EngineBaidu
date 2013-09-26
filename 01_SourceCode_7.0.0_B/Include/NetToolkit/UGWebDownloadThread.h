////////////////////////////////////////////////////////////////////////////////
//!  Project UGC
//! \file UGWebDownloadThread.h
//! \author UGC Group
//! \brief 下载线程，内部采用回调函数，供外部使用者指定干活的内容
//! \attention 目前仅在三维类库中使用过
//!  Copyright (c)copy;  1997-2009 SuperMap Software Co., Ltd.<br> 
//!  All Rights Reserved.
//! \version 6.0
//! \date 2009年8月28日
////////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_UGWEBDOWNLOADTHREAD_H__4A50E4DC_4371_4DAA_AF32_76DD8B65566E__INCLUDED_)
#define AFX_UGWEBDOWNLOADTHREAD_H__4A50E4DC_4371_4DAA_AF32_76DD8B65566E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Toolkit/UGThread.h"

namespace UGC
{

	//! \brief 回调函数，用于从控制线程的执行
//	typedef void (UGWebDownload::* WebDownloadHandler)();
	
	//! \brief 定义外部回调函数，用于从控制线程的执行
	//! \attention 不能使用类的非静态成员函数
	typedef UGbool (UGSTDCALL * WebDownloadHandler)(void* );

//! \brief class UGWebDownloadThread
//! \brief 下载线程
class NETTOOLKIT_API UGWebDownloadThread : public UGThread  
{
public:

    //! \fn UGWebDownloadThread(WebDownloadHandler pCallback);
    //! \brief 默认构造函数，需要指定外部回调函数的指针
    //! \param WebDownloadHandler pCallback
	UGWebDownloadThread(WebDownloadHandler pCallback);
	

    //! \fn virtual ~UGWebDownloadThread();
    //! \brief 默认析构函数
	virtual ~UGWebDownloadThread();

    //! \fn void SetHandeler(void* pHandeler);
    //! \brief 设置真正用线程来干活的外部调用，目前传的是类的指针，
	//!	外部回调函数内部再进行类型转换，就可以调用类内部的成员函数去干活了。 
    //! \param void* pHandeler [in] 对象句柄
	void SetHandeler(void* pHandeler);

protected:
	
	//! \brief 重写基类run函数。
	//! \return 线程正常退出返回0，失败则返回-1。
	virtual UGint run();	

private:
	//! \brief 回调函数指针
	WebDownloadHandler m_pRunHandler;

	//! \brief 外部对象句柄
	void* m_pHandeler;

};

}

#endif // !defined(AFX_UGWEBDOWNLOADTHREAD_H__4A50E4DC_4371_4DAA_AF32_76DD8B65566E__INCLUDED_)
 
