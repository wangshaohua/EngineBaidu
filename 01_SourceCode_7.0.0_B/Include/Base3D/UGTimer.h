//////////////////////////////////////////////////////////////////////////
//                    _   _   ____   ____                    
//   Project         | | | | / ___) / ___)                   
//                   | | | || | __ | |                       
//                   | |_| || |_\ || \___                    
//                    \____/ \____| \ ___)     6.0           
//                                                           
//!  \file headerfile.h
//!  \brief 。
//!  \details 。
//!  \author 。
//!  \attention 
//!   Copyright (c) 1996-2010 SuperMap Software Co., Ltd. <br> 
//!   All Rights Reserved.
//!  \version 6.0
//////////////////////////////////////////////////////////////////////////

#if !defined(AFX_UGTIMER_H__77F37090_FF08_46BD_9EEB_312314BBBD47__INCLUDED_)
#define AFX_UGTIMER_H__77F37090_FF08_46BD_9EEB_312314BBBD47__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Base3D/UGPrerequisites3D.h"

#ifdef WIN32
#include <Windows.h>
#else
#include <sys/time.h>
#endif

//! \brief 开始计时
#define UGTIMERSTART()	UGC::UGTimer::GetInstance().Start();

//! \brief 停止计时
#define UGTIMERSTOP(strFuncName)	UGC::UGTimer::GetInstance().Stop(strFuncName, __UGFILE__, __LINE__);

namespace  UGC 
{
// 用法:
//	 1.在需要的文件中#include "Base3D/UGTimer.h"
// 	 3.开始计时UGTIMERSTART;
// 	 4.结束计时UGTIMERSTOP(strFuncName);信息会写到日志文件中

class BASE3D_API UGTimer  
{
public:
	UGTimer();
	~UGTimer();

	static UGTimer& GetInstance();

	//! \brief 开始计时
	void Start();

	//! \brief 停止计时
	//! \param strCodeFile 测试文件,使用__FILE__作为参数
	//! \param nLineNumber　Stop所在的行,使用__LINE__作为参数
	void Stop(const UGString& strFuncName,const UGString& strCodeFile, UGint nLineNumber);

	//! \获取间隔时间,以秒为单位
	UGdouble GetElapsedTimeInSec();

	//! \获取间隔时间,以毫秒为单位
	UGdouble GetElapsedTimeInMilliSec();

	//! \获取间隔时间,以微秒单位
	UGdouble GetElapsedTimeInMicroSec();

private:
	UGdouble m_dStartTimeInMicroSec;
	UGdouble m_dEndTimeInMicroSec;
	UGbool m_bStopped;
#ifdef WIN32
	LARGE_INTEGER freguency;
	LARGE_INTEGER startCount;
	LARGE_INTEGER endCount;
#else
	timeval freguency;
	timeval startCount;
	timeval endCount;
#endif

};

}
#endif // !defined(AFX_UGTIMER_H__77F37090_FF08_46BD_9EEB_312314BBBD47__INCLUDED_)


