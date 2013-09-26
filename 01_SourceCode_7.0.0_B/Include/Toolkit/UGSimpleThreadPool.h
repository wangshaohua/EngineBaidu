#ifndef _SIMPLETHREADPOOL
#define _SIMPLETHREADPOOL
#include "Toolkit/UGThread.h"
#include "Toolkit/UGToolkit.h"
#ifdef WIN32
#include "windows.h"
#include "winbase.h"
#endif

namespace UGC
{
// 线程池类: 该类采用单例模式,在首次获取线程池实例时初始化线程池中的执行线程
// 线程池初始化后,只需要向线程池中添加任务,执行线程就会按顺序从任务列表中取任务,并执行

typedef UGint (*SimpleTaskFun)(void* param);

class TOOLKIT_API UGSimpleTask
{
	friend class UGSimpleThreadPool;
private:
	enum TaskStatus
	{
		Error = 0,
		Finished = 1,
		Waiting = 2,
		Running = 4,
	};
	UGSimpleTask();
	UGSimpleTask(const UGSimpleTask& in);

	UGSimpleTask(SimpleTaskFun f, void* pa)
	{
		fun = f;
		param = pa;
		m_status = Waiting;
		m_bManaged = FALSE;
	}

	UGSimpleTask(SimpleTaskFun f, void* pa, UGbool bManaged)
	{
		fun = f;
		param = pa;
		m_status = Waiting;
		m_bManaged = TRUE;
	}
public:
	TaskStatus GetStatus()
	{
		return m_status;
	}

private:
	UGint run();

private:
	SimpleTaskFun fun;
	void *param;
	TaskStatus m_status;

	UGuint m_nThreadID;
//#ifdef _AIX
	UGMutex* m_pEvent;
//#else
//	UGCondition* m_pEvent;
//#endif
	UGbool m_bManaged;
};


class TOOLKIT_API UGSimpleThreadPool
{
private:
	UGSimpleThreadPool();
	
	enum PoolStatus
	{
		UnInitialized = 0,
		Initializing = 1,
		Initialized,
		Destroying,
		Destroyed,
	};

public:
	// 线程池构造的时候会自动按CPU核数调用Init来构造线程池
	// 线程池已经初始化,再次调用该方法返回失败
	// 如果需要修改线程池中的默认线程数,重新构造线程池,则可以先调用Destroy,再调用Init
	UGbool Init(UGint nCount);
	// 释放线程池的所有资源,适合于需要重新构造线程池.不建议用户使用.
	void Destroy();
	
	~UGSimpleThreadPool();

	static UGSimpleThreadPool& GetInstance()
	{
		ms_instanceMutex.lock();
		static UGSimpleThreadPool s_SimpleThreadPool;
		ms_instanceMutex.unlock();
		if(s_SimpleThreadPool.m_eStatus == UnInitialized)
		{
			s_SimpleThreadPool.Init(UGToolkit::GetCPUCount());
		}
		return s_SimpleThreadPool;
	}

public:
	// 加入任务,自动添加到任务列表末尾,等待执行,未执行的任务可以通过RemoveTask移除
	// 考虑到提供了Wait接口,返回的任务指针需要由用户释放,如果任务还没有执行就被释放,可能会导致不可预期的错误
	UGSimpleTask* AddTask(SimpleTaskFun f, void* param);

	// 加入托管任务,自动添加到任务列表末尾,等待执行
	// 托管任务在执行完成后会自已删除,加入任务列表后,用户无法移除,也无法通过任务获取状态
	void AddManagedTask(SimpleTaskFun f, void* param);

	// 在等待的任务列表中移除指定任务,正在执行的任务不能移除
	// 移除任务成功会自动析构task,而无需手动析构
	UGbool RemoveTask(UGSimpleTask *&task);

	// 获取剩余任务数
	inline UGint GetWaitingTaskCount() const;

	// 当前线程等任务列表中的任务执行完成
	// 测试发现AIX环境下Wait不可靠,需要在实现代码中解决Wait的问题
	void Wait(UGArray<UGSimpleTask *> aryTasks);

private:
	// 内部接口，专门提供给线程池的循环线程方法使用
	UGbool GetATask(UGSimpleTask *&task);

	// Task类获取当前Task对应的结束事件
//#ifdef _AIX
	UGMutex* GetEvent(UGuint nThreadID);
//#else
//	UGCondition* GetEvent(UGuint nThreadID);
//#endif

	// 线程池析构时,释放线程池中的线程,事件
	PoolStatus GetStatus()
	{
		return m_eStatus;
	}
	static UGint LoopFun(void*);

private:
	UGMutex m_mutexTaskList;
	UGCondition m_eventTaskAdded;

	// 专门负责单例模式下GetInstance的线程安全
	static UGMutex ms_instanceMutex;

private:
	// 线程池中的线程
	OGDC::OgdcDict<UGuint, UGThreadEx*> m_poolThreads;
	UGint m_nStartedThread;

	// 用于线程池中某任务结束时的事件，内部使用, 的AIX上用Condition有问题,只能用Mutex搞定先,
	// 其实其他平台也用Mutex就行,不会存在广播消息的情况,先这样吧
//#ifdef _AIX
	OGDC::OgdcDict<UGuint, UGMutex*> m_eventsTaskFinished;
//#else
//	OGDC::OgdcDict<UGuint, UGCondition*> m_eventsTaskFinished;
//#endif
	PoolStatus m_eStatus;

	// List Task,FIFO 
	OGDC::OgdcList<UGSimpleTask*> m_taskList;
};

}
#endif

