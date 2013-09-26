#ifndef UGDUMPGENERATOR_H
#define UGDUMPGENERATOR_H

// 该功能目前仅支持Windows平台
/**
功能：使用异常捕获功能捕捉Win32异常（C结构的异常），如访ACCESS_VIOLATION，ARRAY_BOUNDS_EXCEEDED，DIVIDE_BY_ZERO等，
	并生成Dump文件，方便进行后续的问题分析和定位

	目前测试在类库生成Win32异常，在.Net组件和Java组件来捕捉该异常，结果不太一致。
	.Net本身提供了System::SystemException来处理Win32异常，能够直接使用该异常类型捕捉错误，
	因此无需使用本类中的封装，而在CLI代码中直接使用System::SystemException处理错误。
	Java组件需要在Wrapj中使用本功能进行Win32异常的处理，防止程序崩溃。同时在Wrapj的Toolkit中
	提供了DumpExceptionCallBack(msg)的回调来把C++异常传递到Java层。

用法：
1、确保Supermap.xml中配置项“DumpEnabled”值为“true”，并设置正确的“DumpPath”
2、在可能产生崩溃的代码段添加捕获异常的代码如：必须要在try之前调用UGDumpGenerator::InitInstance();
	UGDumpGenerator::InitInstance();
	try
	{
		UGWorkspace ws = new UGWorkspace();
	}
	catch(UGExceptionEx &e)
	{
		UGDumpGenerator::WriteDumpFile(e);
		// 其他处理代码
		...
	}
3、修改工程属性（C/C++/Code Generation/Enable C++ Exceptions: Yes With SEH Exceptions (/EHa)）
	必须确保该属性为“EHA”，上述代码才能正常捕获Win32异常
4、用Windbg对UGDumpGenerator::WriteDumpFile(e)生成的Dump文件进行调试并分析问题。


*/
#include "Stream/ugdefs.h"
namespace UGC{

	// 定义C++异常类，记录异常信息
	class UGExceptionEx
	{
		friend class UGDumpGenerator;
	public:
		UGExceptionEx(unsigned int _code, void* _ptr) : code(_code), ptrException(_ptr) 
		{

		}

		~UGExceptionEx() {}

	private:
		unsigned int code;
		void* ptrException;
	};


	// Dump文件生成类
	class TOOLKIT_API UGDumpGenerator
	{
	private:
		UGDumpGenerator();
	public:
		~UGDumpGenerator();

		// 实例化DumpGenerator，单例模式
		// _set_se_translator必须要在每个线程中单独调用_set_se_translator，因此在多线程环境中使用，对于需要捕捉异常的方法应该先调用InitInstance()
		static UGDumpGenerator& InitInstance();

		//! \brief 根据异常信息生成Dump文件，异常信息可以从UGExceptionEx.ptrException中获取
		//! \param *pException 为NULL时，把进程的当前状态生成Dump文件，不为空时，利用该异常信息生成Dump文件
		static void WriteDumpFile(UGExceptionEx* pException);
		static void WriteDumpFile( int errorno, void* exception_pointers );

	private:
		static void* m_pDumpHandler;
		static UGbool m_bDumpEnabled;
	};
}
#endif

