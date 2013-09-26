/**  \file UGWindowTypes3D.h
   \brief   定义与窗口相关数据类型
   \auothor malq
   \attetion 考虑跨平台因素
   Copyright(c) 2000-2010  SuperMap GIS Technolgoies, Inc<br>
   All Rights Reserved
   \version 2.0
   <b>更新说明：</b>\n
	<em>1、第一条说明。\n
	<em>2、第二条说明。\n
*/

#ifndef UG3DWINDOWTYPES_H
#define  UG3DWINDOWTYPES_H

//! \brief 定义window数据类型
#ifdef WIN32
#include <WINDOWS.H>

namespace UGC
{
	//! \brief 定义window设备句柄
	typedef HDC Display3D;                      

	//! \brief 定义window窗口句柄
	typedef HWND Window3D;                      
	
	//! \brief 定义OpenGL上下文句柄
	typedef HGLRC GLContext;                  
	
	//! \brief 像素格式描述
	typedef PIXELFORMATDESCRIPTOR VisualInfo;  
	
	//! \brief 字体
	typedef HFONT Font3D;
}
#endif

//! \brief 定义非window中数据类型
#if !defined WIN32 && !defined (IOS3D)
#include <GL/glx.h>  
namespace UGC
{
	//! \brief 定义设备句柄
	typedef ::Display* Display3D;             
	//! \brief 定义窗口句柄
	typedef ::Window   Window3D;                  
	//! \brief 定义OpenGL上下文句柄
	typedef GLXContext GLContext;              
	//! \brief 像素描述格式
	typedef XVisualInfo* VisualInfo;            
}
#endif

#if defined IOS3D
namespace UGC
{
	//! \brief 定义设备句柄
	typedef UGlong Display3D;             
	//! \brief 定义窗口句柄
	typedef UGlong   Window3D;                             
}
#endif

#endif

