//////////////////////////////////////////////////////////////////////////
//!  \file     UGPyramidMachine.h:
//!  \brief	   构建金字塔算法
//!  \details  
//!  \author   zhouqin/wangmao
//!  \attention 
//!   Copyright (c) 1997-2010 SuperMap GIS Technologies,Inc.  <br>
//!   All Rights Reserved.
//!  \version 1.0
//////////////////////////////////////////////////////////////////////////
#ifndef UGPYRAMIDMACHINE_H
#define UGPYRAMIDMACHINE_H

#include "Stream/ugdefs.h"
#include "Engine/UGDataSource.h"
#include "Engine/UGDataset.h"

namespace UGC {

typedef void (*AVGFUNC)(UGImgBlock* pDes, UGImgBlock* pSrc, 
						UGint nDesStarti, UGint nDesStartj, UGdouble dbNovalue);

class ENGINE_API PyramidMachine
{
public:
	//根据栅格数据集的信息初始化金字塔机器
	//里边根据数据集的像素格式给计算像素值的函数赋值
	//初始化了每一行像素的个数,每一行字节数,单个像素的字节大小
	//dtType 数据集类型，根据数据集类型，对边界无值区特殊处理
	PyramidMachine(PixelFormat ePixelFormat, UGDataset::DatasetType dtTyp, UGdouble dbNoValue, UGbool bHasColorset);

	//生产出目标的ImgBlock
	void run(UGImgBlock* pDest,UGImgBlock* pLT,UGImgBlock* pRT,UGImgBlock* pLB,UGImgBlock* pRB);

	UGbool IsSupport(){return m_bCanBuild;};

private:
	void comLT();
	void comRT();
	void comLB();
	void comRB();

private:
	AVGFUNC AvgFuntion;

	//判断像素格式是否可以建立金字塔
	UGbool m_bCanBuild;

	UGdouble m_dbNoValue;

	UGImgBlock* m_pDest;
	UGImgBlock* m_pLT;
	UGImgBlock* m_pRT;
	UGImgBlock* m_pLB;
	UGImgBlock* m_pRB;
};

} //namespace UGC

#endif // !defined(UGPYRAMIDMACHINE_H)

