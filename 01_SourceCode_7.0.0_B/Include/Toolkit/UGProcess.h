/*!
   **************************************************************************************
    \file     UGProcess.h
   **************************************************************************************
    \author   崔文柱
    \brief    进程间读写锁的类，用于实现读者写者问题                                         
    \attention   
   ----------------------------------------------------------------------------------<br>
    Copyright (c) 2000-2012 SuperMap Software Co., Ltd.                              <br>
    All Rights Reserved.                                                             <br>
   ----------------------------------------------------------------------------------<br> 
   
   **************************************************************************************
	\remarks <em>关于读者写者锁类说明</em>
	
	一：简单介绍：
		Toolkit/UGProcess.h读者写者类，主要用于多进程并发读写控制，对于同一份资源 一个时间可以有多个进程读，
	但同时只有一个进程写，读写之间是互斥的，采用信号量和共享内存实现。
		相对于普通的读写锁，这个读写类增加回调函数，如果有进程进行写操作，则会通知其他进程，处理写脏资源。

	二：基本原理：

	PV原语的含义
		P操作和V操作是不可中断的程序段，称为原语。PV原语及信号量的概念都是由荷兰科学家E.W.Dijkstra提出的。
	信号量sem是一整数，sem大于等于零时代表可供并发进程使用的资源实体数，但sem小于零时则表示正在等待使用临界区的进程数。
	P原语操作的动作是：
		(1)sem减1;
		(2)若sem减1后仍大于或等于零，则进程继续执行;
		(3)若sem减1后小于零，则该进程被阻塞后进入与该信号相对应的队列中，然后转进程调度
	V原语操作的动作是:
		(1)sem加1;
		(2)若相加结果大于零，则进程继续执行;
		(3)若相加结果小于或等于零，则从该信号的等待队列中唤醒一等待进程，然后再返回原进程继续执行或转进程调度。
		   PV操作对于每一个进程来说，都只能进行一次，而且必须成对使用。在PV原语执行期间不允许有中断的发生。

	改进前，也是网上的样例
	///r_w控制谁使用黑板,mutex保护临界区，初值都为1
	int read_account =0; 
	semaphore r_w,mutex; 


	reader - (读者进程):    
	While (true) 
	{ 
		P(mutex); 
		read_account++; 
		if(read_account=1) 
			P(r_w); 
		V(mutex); 
       
		Read(); //读者操作
		
		P(mutex); 
		read_account--; 
		if(read_account=0) 
			V(r_w);
		V(mutex); 
	}
	writer - (写者进程):   
	While (true) 
	{ 
		P(r_w); //备注：网上一般情况下是 P(mutex)。
		
		Write(); //写操作 
		
		V(r_w);  //备注：网上一般情况下是 V(mutex)。
	} 

	改进后,也是读写者类实现的基本原理。

	//r_w控制谁使用黑板,mutex保护临界区，初值都为1
	//writer_count为共享内存计数
	、、m_writer_count 为本地内存计数
	int read_account =0; 
	semaphore r_w,mutex; 
	shared_int writer_count = 0; 
	int m_writer_count = writer_count;

	reader - (读者进程):    
	While (true) 
	{ 
		P(mutex); 
		++read_account; 
		if(read_account=1) 
			P(r_w); 
		if(m_writer_count != writer_count)
			RefreshDirty();
		V(mutex); 

		Read(); //读者操作

		P(mutex); 
		read_account--; 
		if(read_account=0) 
			V(r_w);
		V(mutex); 
	}
	writer - (写者进程):   
	While (true) 
	{ 
		P(r_w); 
		if(m_writer_count != writer_count)
			RefreshDirty();
		++writer_count;
		m_writer_count = writer_count;

		Write(); //写操作 

		V(r_w);  
	} 

	三 使用方式：
	
	void ProcessCallBack(void * )
	{
		///
	}
	
	UGProcess m_RWlock;

	void Reader()
	{
		UGProcessReaderLock reader(m_RWlock);
		//读操作，会自动解锁
	}

	void Writer()
	{
		UGProcessWriterLock writer(m_RWlock);
		//写操作，会自动解锁
	}
	
	
	int main()
	{
		
		m_RWlock.SetCallBack(&ProcessCallBack,(void*)this);
		//必须是一个有效的文件名字，各个进程之间通过名字进行标识是同一个互斥锁。
		UGString strFileName = "file/name";
		readwriterlock.ProcessLockInit(strFileName);
		for()
		{
			Reader();
			Writer();
		}
		readwriterlock.ProcessLockRelease();
	}

	四：注意事项：
	1.	ProcessLockInit ProcessLockRelease 必须是成对匹配，并且在同一个进程中只做一次操作，否则会有资源泄露
	2.	strFileName 这个多个进程之间要进行互斥，必须要求保持一致，并且是一个有效的文件名字，如果文件被删掉，在重新建立
		在重新使用这个文件名字作为锁的唯一标识是不可靠的。
	3.	在一个进程的多线程之间，这个锁并不确保是有效的。
	4.  这个锁是保证线程安全的，并且支持可重入的模式。
	5.	如果有一个进程突然意外的死掉，推荐重启所有进程，否则可能有死锁的几率。

   **************************************************************************************
*/

#if !defined(UGPROCESSS_H)
#define UGPROCESSS_H

#include "Stream/ugdefs.h"
#include "Toolkit/UGThread.h"


#ifdef WIN32
#include <windows.h>
#endif

namespace UGC {

;
//! \brief 日志文件类回调函数
//! \brief 读写锁控制类。

//!  \brief 回调函数，用于处理多进程数据脏的处理
typedef  void (*DirtyWriteCallBack)(void* pObj);

class TOOLKIT_API UGProcess  
{
	struct FileMappingData 
	{
		UGlong m_nMappingWriterC;
		UGlong m_nMappingReaderC;
		UGlong m_nMappingProcessC;
		FileMappingData()
		{
			m_nMappingWriterC = 0;
			m_nMappingReaderC = 0;
			m_nMappingProcessC = 0;
		}
	};
public:
	//! \brief 构造函数
	UGProcess();
	//! \brief 析构函数
	~UGProcess();
	//! \brief	给读进程加锁
	//! \param  bCallBack 是否调用callback的函数，如果设置为FALSE，则不会调用callback函数
	//! \return 根据pWriterCount判断文件数据是否脏，如果脏，返回true,脏的条件是有进程调用WriterLock
	//! \remarks 如果 pWriterCount 为null，则永远返回false，文件处于干净状态，也就是没有其他
	//			 进程更新。不支持可重入模式。
	//处理脏模式可以通过返回值或者回调函数处理
	UGbool ReaderLock(UGbool bCallBack = TRUE);
	//! \brief	给读进程解锁
	//! \remarks ReaderLock ReaderUnlock 一定要成对匹配出现，如果没有成对，则有可能出现死锁。
	void ReaderUnlock();
	//! \brief	给写进程加锁
	//! \param  bCallBack 是否调用callback的函数，如果设置为FALSE，则不会调用callback函数
	//			永远返回false;
	//! \return 根据pWriterCount判断文件数据是否脏，如果脏，返回true,脏的条件是有进程调用WriterLock
	//! \remarks 因为同一时间只能有一个写进程存在，所以不要重复调用，
	//			 尽量不要这样调用 ReaderLock WriterLock ReaderUnlock WriterUnlock等混乱调用，有可能出现死锁。
	//           不支持可重入模式。
	UGbool WriterLock(UGbool bCallBack = TRUE);
	//! \brief	给写进程解锁
	//! \remarks WriterLock WriterUnlock 一定要成对匹配出现，如果没有成对，则有可能出现死锁。
	void WriterUnlock();
	//! \brief	进程锁初始化
	//! \param 	strName[in] 文件名字的，多个进程要读取同一个文件的名字,
	//! \param 	pWriterCount[in] 内部判断文件是否脏的计数。
	//! \remarks 在进程开始的时候一定要调用，并且只调用一次。
	//            ProcessLockInit ProcessLockRelease 是成对匹配的，不支持可重入模式
	//返回并发连接的进程数目，如果返回0代表初始化未成功，进程锁有问题，请查看日志
	//在AIX 上面一个共享内存最大的连接并发数是11个
	//可以通过设置环境变量
	//export EXTSHM=ON,增加其并发连接数
	UGulong ProcessLockInit(const UGString& strName);
	//! \brief	进程锁析构
	//! \remarks 在进程结束的时候一定要调用，并且只调用一次。不支持可重入模式
	void ProcessLockRelease();
	//! \brief	判断当前的对象的RWLock 是否有锁住现象
	//! \remarks 现在的主要用处是主要用来检查死锁的问题
	UGbool isLocked();
	void SetIsValied(UGbool bIsValied){m_bIsValied = bIsValied;};
	void SetCallBack(DirtyWriteCallBack pCallBack,void *pCallBackParam);

#ifdef WIN32
	inline DWORD WaitForValidSignal(
		HANDLE hHandle        // handle to object to wait for
		);
#endif
//将下面类封装，外面最好不要调用
private:
	UGProcess(const UGProcess&);
	UGProcess& operator=(const UGProcess&);
	//const UGProcess *operator()const{ return this};
	UGProcess *operator&(); 
private:
	//! \brief 记录读者锁调用的次数
	UGlong m_nReaderLockCount;
	//! \brief 记录写者锁调用的次数
	UGlong m_nWriterLockCount;
	//! \breif记录是否初始化，相当于是否open
	UGbool m_bInit;
    //! \brief 用于传回写者的计数
	UGlong m_nWriterCount;
	
	DirtyWriteCallBack m_pCallBack;
	void *m_pCallBackParam;
	//用于保持锁的过程是原子操作
	//用于互斥锁的需要
	//如果这个设置为FALSE，则WriterLock WriterUnLock ReaderLock 
	//ReaderUnLock没有效果
	UGbool m_bIsValied;
	UGMutex m_mutexR;
	UGMutex m_mutexW;
	UGMutex m_mutexInit;
	struct FileMappingData *m_pFileMappingData;
private:
#if defined(WIN32)
	HANDLE m_hMutexRW;
	HANDLE m_hMutexR;
	HANDLE m_hFileMapping;
#else
	UGint m_hSem;
	UGint m_hShm;
#endif




};

class TOOLKIT_API UGProcessReaderLock {
private:
	UGProcess& pro;
private:
	UGProcessReaderLock();
	UGProcessReaderLock(const UGProcessReaderLock&);
	UGProcessReaderLock& operator=(const UGProcessReaderLock&);
	UGProcessReaderLock *operator&(); 
public:

	//Construct & lock associated UGProcess
	inline UGProcessReaderLock(UGProcess& p,UGbool bCallBack = TRUE):pro(p){Lock(bCallBack);}
	inline UGbool Lock(UGbool bCallBack = TRUE){ return pro.ReaderLock(bCallBack);}
	inline ~UGProcessReaderLock(){ pro.ReaderUnlock(); };
};

class TOOLKIT_API UGProcessWriterLock {
private:
	UGProcess& pro;
private:
	UGProcessWriterLock();
	UGProcessWriterLock(const UGProcessWriterLock&);
	UGProcessWriterLock& operator=(const UGProcessWriterLock&);
	UGProcessWriterLock *operator&(); 
public:

	//Construct & lock associated UGProcess
	 inline UGProcessWriterLock(UGProcess& p,UGbool bCallBack = TRUE):pro(p){Lock(bCallBack);}
	 inline UGbool Lock(UGbool bCallBack = TRUE){ return pro.WriterLock(bCallBack);}
	 inline ~UGProcessWriterLock(){ pro.WriterUnlock(); };
};

}

#endif // !defined(UGPROCESSS_H)


