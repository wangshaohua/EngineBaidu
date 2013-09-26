/*!
**************************************************************************************
\file    UGPerformanceProfile.h 
**************************************************************************************
\author  江志斌 
\brief   性能统计类，仅用于测试，请不要在发布的代码中添加相关代码
\attention   
----------------------------------------------------------------------------------<br>
Copyright (c) 2000-2010 SuperMap Software Co., Ltd.                           <br>
All Rights Reserved.                                                             <br>
----------------------------------------------------------------------------------<br> 

**************************************************************************************
\remarks <em>性能统计类使用说明</em>

性能统计类可以用于统计分析指定方法消耗的时间，有两种时间精度，一种是以毫秒为单位，
另一种是以CPU的频率为单位。通过宏QUERYPERFORMANCECOUNTER控制是否使用高精度的记数器。
性能统计类的使用方式比较简单，需要统计某个具体的方法，只需在该方法的入口定义一个性
能记数器对象（UGProfileCounter）,同时指定一个名称或者是用宏"__FUNCTION__"。在最后程
序结束之前使用UGProfileManager来统计相关的性能指标。


void SubFun()
{
	UGProfileCounter counter(__FUNCTION__);
	// SubFun具体的实现代码
	...
}
void AnotherSubFun()
{
	// AnotherSubFun具体的实现代码
	...
	UGProfileCounter *pCounter = new UGProfileCounter("统计AnthorSubFun中的部分方法耗时");
	...
	delete pCounter;
	...
}
void Fun()
{
	UGProfileCounter counter(__FUNCTION__);
	// Fun具体的实现代码
	...
	SubFun();
	...
	AnotherSubFun();
	...
}

void main()
{
	// 调用Fun函数
	Fun();
	// 输出统计信息到控制台，会输出Fun(), SubFun(), AnotherSubFun()三个方法中所耗时的统计信息
	UGProfileManager.GetInstance().PrintAll();
	// 输出统计信息到文件中
	UGProfileManager.GetInstance().WriteToFile("name", "fileName", UGStreamLoadSave);
	// 清除统计信息
	UGProfileManager.GetInstance().ClearAll();
}

**************************************************************************************
*/
#if !defined(UGPerformanceProfile_H)
#define UGPerformanceProfile_H

#include "Stream/UGFileStdio.h"
#include "Toolkit/UGThread.h"

//#define QUERYPERFORMANCECOUNTER
#if defined WIN32
#include <windows.h>
#else
#include   <sys/time.h>   
#include   <unistd.h> 
#endif
#ifdef _UGUNICODE
#define __UGFUNCTION__ __FUNCTIONW__
#else
#define __UGFUNCTION__ __FUNCTION__
#endif
// 该宏会在日志文件中记录当前的方法和代码行
#define UGPROFILE_DEBUG	UGProfileManager::GetInstance().Debug(_U("%s: %d"), __UGFUNCTION__, __LINE__);
using namespace UGC;
class UGProfileData
{
public:
	UGProfileData(UGbool bSimpleMode = TRUE)
	{
		m_bSimple = bSimpleMode;
		if(m_bSimple)
		{
			m_aryData.Add(0);
		}
	}
	~UGProfileData(){m_aryData.RemoveAll();}

	UGArray<OgdcLong>& GetData(){return m_aryData;}

	void Add(OgdcLong nData)
	{
		if(m_bSimple)
		{
			m_aryData[0] += nData;
		}
		else
		{
			m_aryData.Add(nData);
		}
	}

	UGlong Sum()
	{
		OgdcLong sum = 0;
		for(UGint i = 0; i < m_aryData.GetSize(); i++)
		{
			sum+=m_aryData[i];
		}
		return sum;
	}
	UGint Count()
	{
		return m_aryData.GetSize();
	}

	OgdcLong Average()
	{
		return (OgdcLong)Sum()/Count();
	}
private:
	UGArray<OgdcLong> m_aryData;
	UGbool m_bSimple;
};

class TOOLKIT_API UGProfileManager
{
	friend class UGProfileCounter;
public:
	// 获取ProfileManager的唯一实例
	static UGProfileManager& GetInstance()
	{
		static UGProfileManager s_profileManager;
		return s_profileManager;
	}

	~UGProfileManager()
	{
		ClearAll();
		if(m_pFileHandle != NULL)
		{
			((UGFileStdio*)m_pFileHandle)->Close();
		}
		delete (UGFileStdio*)m_pFileHandle;
		m_pFileHandle = NULL;
	}
	
	void Debug(UGchar* format, ...);

	// 清除指定名称的性能统计数据
	void Clear(const UGchar* pName);

	// 清除全部的性能统计数据
	void ClearAll();

	// 求指定名称性能指标的耗时总和
	UGlong Sum(const UGchar* pName);

	// 求指定名称性能指标的统计次数
	UGint Count(const UGchar* pName);

	// 求指定名称性能指标的平均耗时
	UGlong Average(const UGchar* pName);
	
	// 在控制台打印输出所有的性能指标
	void PrintAll();

	// 把性能参数输出到文件中,需要指定文件名
	UGbool WriteToFile(const UGchar* pName, const UGchar* pFileName, UGStreamDirection dir, UGbool bFullContent = FALSE);

	// 把全部性能参数输出到文件中,需要指定文件名
	UGbool WriteAllToFile(const UGchar* pFileName, UGStreamDirection dir);

protected:
	void RecordLog(const UGchar* pName, OgdcLong nCounter)
	{
		UGMutexLock lock(m_mutex);
		lock.lock();
		UGProfileData *pData = NULL;
		m_data.Lookup(pName, pData);
		if(pData == NULL)
		{
			pData = new UGProfileData;
			m_data.SetAt(pName, pData);
		}
		pData->Add(nCounter);
	}
private:
	UGProfileManager() : m_pFileHandle(NULL) {}

private:
	UGDict<UGString, UGProfileData *> m_data;
	UGMutex m_mutex;
	void* m_pFileHandle;
};

class TOOLKIT_API UGProfileCounter
{
public:
	explicit UGProfileCounter(const UGchar* pName) 
	{
		m_pName = pName;
#if defined QUERYPERFORMANCECOUNTER && defined WIN32
		QueryPerformanceCounter(&m_begin);
#elif defined WIN32
		m_begin = clock();	
#else
		gettimeofday(&m_tmStart,0);
#endif
	}

	~UGProfileCounter()
	{
#if defined QUERYPERFORMANCECOUNTER && defined WIN32
		LARGE_INTEGER end;
		QueryPerformanceCounter(&end);
		OgdcLong timeLast = end.QuadPart-m_begin.QuadPart;
#elif defined WIN32
		UGlong timeLast=clock()-m_begin;
#else
		gettimeofday(&m_tmStop,0);
		ogdc_locale_timeval_subtract(&m_tmDiff,&m_tmStart,&m_tmStop);
		OgdcLong timeLast = m_tmDiff.tv_sec*1000000+m_tmDiff.tv_usec;
#endif
		// 记录当前日志
		UGProfileManager::GetInstance().RecordLog(m_pName, timeLast);
	}

#if defined QUERYPERFORMANCECOUNTER && defined WIN32
#else
	int  ogdc_locale_timeval_subtract(struct   timeval*   result,   struct   timeval*   x,   struct   timeval*   y)   
	{   
		if   (   x->tv_sec>y->tv_sec   )   
			return   -1;   

		if   (   (x->tv_sec==y->tv_sec)   &&   (x->tv_usec>y->tv_usec)   )   
			return   -1;   

		result->tv_sec   =   (   y->tv_sec-x->tv_sec   );   
		result->tv_usec   =   (   y->tv_usec-x->tv_usec   );   

		if   (result->tv_usec<0)   
		{   
			result->tv_sec--;   
			result->tv_usec+=1000000;   
		}  
		return   0;   
	}
#endif

private:
#if defined QUERYPERFORMANCECOUNTER && defined WIN32
	LARGE_INTEGER m_begin;
#elif defined WIN32
	UGlong m_begin;
#else
	struct  timeval   m_tmStart,m_tmStop,m_tmDiff;
#endif
	const UGchar *m_pName;
};
#endif //#define UGPerformanceProfile_H