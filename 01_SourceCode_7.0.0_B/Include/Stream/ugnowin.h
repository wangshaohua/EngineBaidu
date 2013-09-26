/* 
	\file ugnowin.h
	\brief 非Windows平台（Linux、Unix等）的头文件定义
	\author zengzm
	\attention
	Copyright(c) 2000-2010 SuperMap Software Co., Ltd.<br>
	All Rights Reserved
	<b>更新说明：。</b>
	<em>1、第一条说明。</em>
	<em>2、第二条说明。</em>
*/

#ifndef _UGNOWIN_H
#define _UGNOWIN_H

// commited by zengzm 2007-3-30 把link.h放在这里，避免在Solaris中编译不过，
// 因为后面会定义_FILE_OFFSET_BITS为64，而link.h中include的libelf.h中
// 判断_FILE_OFFSET_BITS不等于32，且_ILP32也已经被定义，就会输出编译错误
// 估计是中间的某个头文件中定义了_ILP32，因此把link.h放到最前面中，以避免此编译错误
// modified by yanbg 08.1.7 增加对hpux的支持
#if defined(_AIX) || defined(hpux) || defined(SYMBIAN60) || defined(OS_ANDROID) || defined IOS || defined (IOS3D)
#include <dlfcn.h> // for dlopen() & dlsym()
#else 
#include <link.h>  // for dlopen() & dlsym()
#endif               

// 头文件包含
// 定义宏，使得可以处理大文件（>4GB）
#undef _FILE_OFFSET_BITS
#define _FILE_OFFSET_BITS 64
#include <unistd.h>
#include <dirent.h>	
#include <fcntl.h>

#include "Base/ogdcdefs.h"
#include "Stream/ugexports.h"
using namespace OGDC;

#ifdef _UGUNICODE
	EXTERN_C STREAM_API OgdcInt UG_open(const OgdcChar* pFileName, OgdcInt nOpenFlag, OgdcInt nPermissionMode = 0);
	#define UGopen UG_open	//打开文件
	EXTERN_C STREAM_API OgdcInt UG_access(const OgdcChar *path, OgdcInt mode );
	#define UGaccess UG_access	//打开文件
	EXTERN_C STREAM_API OgdcInt UG_remove(const OgdcChar *path);
	#define UGremove UG_remove	//打开文件
	EXTERN_C STREAM_API OgdcInt UG_rename(const OgdcChar *oldname, const OgdcChar *newname );
	#define UGrename UG_rename	//打开文件
	EXTERN_C STREAM_API FILE* UG_fopen(const OgdcChar *path, const OgdcChar *mode);
	#define UGfopen UG_fopen	//打开文件
	EXTERN_C STREAM_API FILE* UG_fopen64(const OgdcChar *path, const OgdcChar *mode);
	#define UGfopen64 UG_fopen64	//打开文件
	//EXTERN_C STREAM_API OgdcInt UG_strlen(const OgdcChar *s);
	//#define UGstrlen UG_strlen	//打开文件
	//EXTERN_C STREAM_API OgdcInt UG_strcpy(char *dest, const char *src);
	//#define UGstrcpy UG_strcpy	//打开文件
#else
	#define UGopen	open	//打开文件
	#define UGaccess access
	#define UGremove remove
	#define UGrename rename
	#define UGfopen fopen
	#define UGfopen64 fopen64
	#define UGstrlen strlen
	#define UGstrcpy strcpy
#endif


#define UGwrite	write	//写文件
#define UGread	read	//读文件
#define UGseek	lseek	//定位文件
#define UGclose	close	//关闭文件
#define UGchsize ftruncate
//#define UGseek lseek64
#if defined(UGtell)
#undef UGtell
#endif
// 查询文件位置
#define UGtell(h) (UGlong)lseek(h, 0, SEEK_CUR)
#define UGsleep(s) sleep(s/1000)
#define UGfwrite	fwrite
#define UGfclose	fclose
#define UGfread		fread
#if !defined  OS_ANDROID && !defined (IOS) && !defined SYMBIAN60
#define UGfseek		fseeko64
#else
#define UGfseek		fseek
#endif

//是否是binary文件
#define UGBINARY 0
//是否是read/write文件
#define UGREADWRITE 0666

// 是否是目录
#define UGDIRECTORY 0x4000


#ifndef O_BINARY
	#define O_BINARY 0
#endif	//O_BINARY
//路径sep
#define PATHSEP _U('/')
//路径sep
#define PATHSEPSTRING _U("/")
//路径listSep
#define PATHLISTSEP _U(':')
//路径listSep
#define PATHLISTSEPSTRING _U(":")
//是否是路径 sep
#define ISPATHSEP(c) ((c)==_U('/'))
#define EOLSTRING _U("\n")
#define UGCALLBACK  
#define UGSTDCALL 

#if !defined SYMBIAN60 && !defined  OS_ANDROID && !defined (IOS) && !defined (IOS3D)
#include <X11/Xlib.h>  
#endif
namespace UGC {

// 变量类型定义
typedef unsigned long UGThreadID;	//	WhiteBox_Ignore
typedef void*		  UGHandle;		

//deleted by xielin 2007-06-26 这两个没人用还引起冲突，删除
//typedef ::Display*  Display;
//typedef ::Window   DisplayWnd;

}


#endif // _UGNOWIN_H

