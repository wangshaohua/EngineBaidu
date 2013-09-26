/*!
**************************************************************************************
\file    UGOpenMP.h 
**************************************************************************************
\author  卢浩 
\brief   封装OpenMP的一些设置，方便使用
\attention   
----------------------------------------------------------------------------------<br>
Copyright (c) 2000-2010 SuperMap Software Co., Ltd.                               <br>
All Rights Reserved.                                                              <br>
----------------------------------------------------------------------------------<br> 

**************************************************************************************
*/

#include "Toolkit/UGToolkit.h"

#if !defined(UGOPENMP_H)
#define UGOPENMP_H

namespace UGC {

class TOOLKIT_API UGOpenMP
{
public:
	UGOpenMP();

	//! \brief 获取实例
	static UGOpenMP& GetInstance();

	//! \brief 获取线程数目
	UGint GetNumThreads();

private:
	UGint m_nNumThreads;
};

}

#endif //#define UGOPENMP_H