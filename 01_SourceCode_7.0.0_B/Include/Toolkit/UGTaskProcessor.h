// UGTaskProcessor.h: interface for the UGTaskProcessor class.
//
//////////////////////////////////////////////////////////////////////

/*!
**************************************************************************************
\file     UGTaskProcessor.h
**************************************************************************************
\author   刘富乾
\brief    多线程任务处理中心                                                           
\attention   
----------------------------------------------------------------------------------<br>
Copyright (c) 2000-2012 SuperMap Software Co., Ltd.                           <br>
All Rights Reserved.                                                             <br>
----------------------------------------------------------------------------------<br> 
*/

#if !defined(AFX_UGTASKPROCESSOR_H__869EEDDC_C92D_4D07_9903_4345F3138D0A__INCLUDED_)
#define AFX_UGTASKPROCESSOR_H__869EEDDC_C92D_4D07_9903_4345F3138D0A__INCLUDED_

#include "Toolkit/UGThread.h"

namespace UGC {

//////////////////////////////////////////////////////////////////////////
//
/*!
**************************************************************************************
任务类（基类）

1. 所有任务类都从此类派生
**************************************************************************************
*/
class TOOLKIT_API UGTaskBase
{
public:
	enum TaskState
	{
		TS_Default		= 0,	// 缺省状态
		TS_Add			= 1,	// 添加状态
		TS_Get			= 2,	// 获取状态
		TS_Processing	= 3,	// 处理状态
		TS_Finish		= 4,	// 完成状态
	};
public:
	//! \brief 获取任务名称
	virtual UGString GetClassName() = 0;

	//! \brief 实现任务类的具体操作
	virtual UGbool Execute() = 0;

	//! \brief 克隆任务
	virtual UGTaskBase* Clone() = 0;

	//! \brief 析构函数
	virtual ~UGTaskBase() { }; 
};


//////////////////////////////////////////////////////////////////////////
//
/*!
**************************************************************************************
任务处理类（接口）

注意：
	如果任务类的工作比较简单，则可以直接实现UGTaskBase类的Execute
方法即可，不需要实现UGTaskProcessor接口；如果任务的操作需要的参数
比较多，建议实现该接口
**************************************************************************************
*/
class TOOLKIT_API UGTaskProcessor
{
public:
	virtual UGbool ProcessTask(UGTaskBase* pTask) = 0;
};


//////////////////////////////////////////////////////////////////////////
//
/*!
**************************************************************************************
任务过滤类（接口）

1. 在任务真正处理之前给用户提供预处理的接口
**************************************************************************************
*/
class TOOLKIT_API UGTaskFilter
{
public:
	//! \brief 预处理任务函数。
	//! \param eTaskState 任务当前的状态。
	//! \param pTask 当前的任务。
	//! \param bHandle 任务的处理状态: true表示用户已处理了该任务，直接抛弃，false表示任务中心需要继续处理该任务。
	//! \return 成功返回TRUE，失败返回FALSE。
	virtual UGbool PreTranslateTask(UGTaskBase::TaskState eTaskState, UGTaskBase* pTask, UGbool& bHandle) = 0;
};


//////////////////////////////////////////////////////////////////////////
//
/*!
**************************************************************************************
工作线程类

1. 执行任务的线程类，主要是循环执行任务中心的任务
**************************************************************************************
*/
class UGTaskMessageLoop;

class TOOLKIT_API UGTaskWorkThread : public UGThread
{
public:
	UGTaskWorkThread();
	virtual ~UGTaskWorkThread();

	//! \brief 绑定线程运行的任务队列
	UGbool Attach(UGTaskMessageLoop* pTaskLoop);

	//! \brief 启动/停止线程
	UGbool StartThread();
	void StopThread();

protected:
	UGint run();

private:
	//! \brief 传入的任务处理队列指针
	UGTaskMessageLoop* m_pTaskLoop;

	//! \brief 线程退出标识
	UGbool m_bStopThread;

};


//////////////////////////////////////////////////////////////////////////
//
/*!
**************************************************************************************
任务处理中心类

1. 主要是管理任务中心的任务队列
**************************************************************************************
*/
typedef UGList<UGTaskBase*> UGTaskQueue;

class TOOLKIT_API UGTaskMessageLoop
{
	friend class UGTaskWorkThread;
public:
	UGTaskMessageLoop();
	virtual ~UGTaskMessageLoop();

	//! \brief 添加/移除任务处理接口
	UGbool AddTaskProcessor(UGTaskProcessor* pTaskProcessor);
	UGbool RemoveTaskProcessor(UGTaskProcessor* pTaskProcessor);

	//! \brief 添加/移除任务过滤接口
	UGbool AddTaskFilter(UGTaskFilter* pTaskFilter);
	UGbool RemoveTaskFilter(UGTaskFilter* pTaskFilter);

	//! \brief 设置/获取任务队列大小
	void SetTaskQueueSize(UGint nQueueSize = 200);
	UGint GetTaskQueueSize();

	//! \brief 是否有任务正在执行
	UGbool IsTaskRunning();

	// 该函数一般别用，允许在外面修改队列
	UGTaskQueue& GetTaskQueue();

public:
	// 以下函数是线程安全的
	//! \brief 获取是否有任务
	UGbool IsTaskEmpty();
	//! \brief 获取队列任务
	UGTaskBase* GetTask();
	//! \brief 增加一个任务
	UGbool AddTask(UGTaskBase* pTask, UGbool bTail = true);
	//! \brief 删除一个任务
	UGbool RemoveTask(UGTaskBase* pTask);
	//! \brief 清空所有任务
	UGint RemoveAllTask();
	//! \brief 获取任务个数
	UGint GetTaskCount();
	//! \brief 对信号量加1，比如退出线程时使线程不会阻塞
	void PostTask(UGint nTaskCount);

protected:
	// 线程调用
	UGbool Run();

private:
	UGArray<UGTaskProcessor*> m_TaskProcessors;
	UGArray<UGTaskFilter*> m_TaskFilters;

private:
	//! \brief 下载请求队列最大长度，默认是200
	UGint m_nMaxQueueLength;
	//! \brief 只针对请求队列和下载队列的操作加锁
	UGTaskQueue m_TaskQueue;
	//! \brief 用来保护队列
	UGMutex m_mutexQueue;
	// 用来指示GetTask是否取到任务
	UGSemaphore m_semQueue;

	//! \brief 任务正在运行
	UGbool m_bTaskRunning;

};


//////////////////////////////////////////////////////////////////////////
//
/*!
**************************************************************************************
任务中心管理类

1. 主要是管理工作线程和任务中心
**************************************************************************************
*/
class TOOLKIT_API UGTaskManager
{
public:
	UGTaskManager();
	virtual ~UGTaskManager();

	//! \brief 设置/获取线程个数
	void SetThreadCount(UGint nThreadsSize = 1);
	UGint GetThreadCount();

	//! \brief 启动任务中心
	UGbool Start();
	//! \brief 停止任务中心
	UGbool Stop();

public:
	//! \brief 添加任务到任务处理中心
	UGbool PostTask(UGTaskBase* pTask, UGbool bTail = true);

	//! \brief 获取任务处理中心队列
	UGTaskMessageLoop& GetMessageLoop();
	
private:
	UGTaskMessageLoop m_TaskLoop;
	UGArray<UGTaskWorkThread*> m_TaskThreads;

	UGint m_nWorkThreadSize;

};

}

#endif // !defined(AFX_UGTASKPROCESSOR_H__869EEDDC_C92D_4D07_9903_4345F3138D0A__INCLUDED_)

