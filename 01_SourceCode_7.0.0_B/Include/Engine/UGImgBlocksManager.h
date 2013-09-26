// UGImgBlocksManager.h: interface for the UGImgBlockManager class.
//
//////////////////////////////////////////////////////////////////////
/* 
	\file UGImgBlocksManager.h
	\brief 处理多线程Block管理类
	\author 李文龙
	\attention 线程安全
	Copyright(c) 1996-2007 SuperMap GIS Technologies,Inc.<br>
	All Rights Reserved
	<b>更新说明：。</b>
	<em>1、第一条说明。</em>
	<em>2、第二条说明。</em>
*/

//////////////////////////////////////////////////////////////////////////
//!  \file UGImgBlocksManager.h
//!  \brief UGImgBlocksManager 的接口定义。
//!  \details UGImgBlocksManager关于影像数据集的缓存接口定义。
//!  \Modified Date: 2013-4-7
//!  \Modified Author:Conversion-zby
//!  \Details Comments:调整UGImgBlocksManager接口参数以及接口组成,主要目的是在缓存接口中添加对于多波段栅格数据集的扩展支持;
//!  \Details Comments:本次调整主要包含两方面内容:(1) 对于原有接口增加波段索引参数支持;(2)兼容修改栅格数据集以及多波段栅格数据集
//!  \Details Comments:对于缓存接口公用的形式!
//!  \Details Comments:此次调整涉及整个栅格数据集结构的调整，由于技术人员水平所限以及时间的仓促，难免会产生这样那样的问题,有问题
//!  \Details Comments:请与Conversion-zby联系!
//!  \Version OGDC-1-1(2013-4-7)


#if !defined(AFX_UGIMGBLOCKMANAGER_H__1A2DC698_B9F7_40D2_8DE3_2C83B9380D68__INCLUDED_)
#define AFX_UGIMGBLOCKMANAGER_H__1A2DC698_B9F7_40D2_8DE3_2C83B9380D68__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Stream/ugdefs.h"
#include "Geometry/UGDataCodec.h"
#include "Toolkit/UGThread.h"

namespace UGC {

class UGDatasetRaster;
class UGImgBlocksManager;
class UGImgBlockRef;

//##ModelId=48203050030E
class ENGINE_API UGImgBlocksManager  
{
	friend class UGDatasetRasterCollectionUdb;

public:
	//!	\brief	缓存模式（cmNoCache表示不缓存影像块，cmCacheBlocks缓存部分影像块在内存中）
	//!	\remark	应二维的需求，调整Block管理类的设计，增加不缓存的模式（cmNoCache），cmNoCache模式下
	//			影像块将直接从磁盘读取
	enum CacheMode { cmNoCache = 0, cmCacheBlocks = 1 };

	//内存调度模式
	enum MemoryAdjustMode{		
		Seq = 0,				//由上而下调度
		Rev = 1,				//由下而上调度
		//Dual = 2,				//双向调度
		Protect = 3				//保护访问区调度
	};

public:
	//##ModelId=48203050031C
	UGImgBlocksManager();
	//##ModelId=48203050031D
	UGImgBlocksManager(UGDatasetRaster *pDtRaster, CacheMode cm = cmNoCache);

	UGImgBlocksManager(const UGImgBlocksManager& ImgBlocksManager);
	
	//! \brief 		重载 = 	
	UGImgBlocksManager& operator=(const UGImgBlocksManager& ImgBlocksManager);

	//##ModelId=48203050031F
#ifdef SYMBIAN60
	~UGImgBlocksManager();
#else
	virtual ~UGImgBlocksManager();
#endif

	//! \brief 设置指定的缓存的Block
	//! \param y [in] 数据库里的第几行 对应数据为SmColumn
	//! \param x [in] 数据库里的第几列 对应数据库里的SmRow
	//! \param *pImgBlock [out] 参数的指针
	//! \param nBandIndex[in] 获取颜色数值所在的波段索引值，默认为0
	//! \return  每个线程维护自己的内存
	//! \remarks 如果当前位置已经存在数据的指针，那么删除之
	//! \param nBandIndex[in] 波段索引值，默认为0
	//! \attention 
	//##ModelId=482030500321
	UGbool SetBlockAt(UGint y,UGint x,UGImgBlock *pImgBlock,UGint nBandIndex=0);

	//! \brief 设置指定的缓存的Block
	//! \param nIndex [in] Position
	//! \param *pImgBlock [in] ImgBlock
	//! \param nBandIndex[in] 波段索引值，默认为0
	//! \return 。
	//! \remarks 。
	//! \attention 。
	//##ModelId=48203050032C
	UGbool SetBlockAt(UGint nIndex,UGImgBlock *pImgBlock,UGint nBandIndex=0);	

	//! \brief 得到指定的缓存的Block
	//! \param y [in] 数据库里的第几行 对应数据为SmColumn
	//! \param x [in] 数据库里的第几列 对应数据库里的SmRow
	//! \param *pImgBlock [out] 返回的指针
	//! \param nBandIndex[in] 波段索引值，默认为0
	//! \return 每个线程维护自己的内存
	//! \remarks 
	//! \attention 
	//##ModelId=48203050032F
	UGImgBlock * GetBlockAt(UGint y,UGint x,UGint nBandIndex=0);
	

	//! \brief 获取指定行列号的Block，若不存在返回NULL
	//! \param nRow [in] 行
	//! \param nCol [in] 列
	//! \return 。
	//! \remarks 与GetBlockAt的区别：不去取数据。
	//! \attention 。
	//##ModelId=482030500332
	UGImgBlock * GetAt(UGint nRow, UGint nCol);		

	
	//! \brief 得到指定位置的缓存Block
	//! \param nIndex [in] 一维数组的位置，该nIndex跟影像块行列位置无关
	//! \return 。
	//! \remarks 。
	//! \attention 注意：这个是根据容器（字典、数组）的下标去取Block,实则为遍历使用，不为定位Blcok。
	//##ModelId=482030500332
	UGImgBlock * GetAt(UGint nIndex);		

	//! \brief 获取保存指针的集合的长度
	UGuint  GetSize();	

	//! \brief 释放当前线程缓存的数据
	//! \param nBandIndex[in] 波段索引值，默认为0
	//! \return TRUE 
	//! \remarks 
	//! \attention 如果Block修改了，要负责修改的数据库
	//##ModelId=482030500334
	UGbool ReleaseBlocks(UGint nBandIndex=0);

	//! \brief 根据指定的索引删除缓存影像块
	//! \param nBandIndex[in] 波段索引值，默认为0
	//! \return TRUE 
	//! \remarks 
	//! \attention 如果Block修改了，要负责修改的数据库
	UGbool ReleaseBlock(UGint index,UGint nBandIndex=0);

	//! \brief 用于UDB栅格数据集的追加的时候
	//! \return TRUE 
	//! \remarks 
	//! \attention 如果Block修改了，要负责修改的数据库
	//##ModelId=482030500334
	UGbool ReleaseBlocksForUDBRaterAppend();

	UGbool SaveBlocksForUDBRasterAppend();

	//! \brief 保存所有的block块
    //! \param nBandIndex[in] 波段索引值，默认为0	
	UGbool SaveAllBlocks(UGint nBandIndex=0);

	//! \brief 保存所有的block块
	//! \param nBandIndex[in] 波段索引值，默认为0
	UGbool SaveBlock(UGImgBlock* pImgBlock,UGint nBandIndex=0);

	//内存调度
	UGulong GetBestMemo();

	//! \brief 调整内存
	//! \param nBandIndex[in] 波段索引值，默认为0
	//! \return 成功返回true，失败返回false
	UGbool AdjustMemory(UGint nBandIndex=0);

	//! \brief 顺序调整内存：从前到后
	//! \param nBandIndex[in] 波段索引值，默认为0
	//! \return 成功返回true，失败返回false
	UGbool AdjustMemorySeq(UGint nBandIndex=0);

	//! \brief  反向调整内存：从后向前
	//! \param nBandIndex[in] 波段索引值，默认为0
	//! \return 成功返回true，失败返回false
	UGbool AdjustMemoryRev(UGint nBandIndex=0);

	//该方法就是想遍历所有的缓存块，没有必要获取所有的缓存块指针数组
	//GetBlockAt就可以了
	//! \brief 得到所有的Img块指针为了快速保存些东西
	//! \return TRUE
	//! \remarks 返回的指针只读，不能删除
	//! \attention 。
	//##ModelId=48203050033C
	//UGImgBlock** GetAllBlocks(UGuint &nSize);

	//! \brief 初始化。
	//! \param *pDataset [in]。
	//! \param FALSE [in]。
	//! \return True
	//! \remarks 默认是支持多线程的，但对于SDB引擎不支持那么将用不支持方式来处理
	//! \attention 。
	//##ModelId=48203050033D
	UGbool SetDataset(UGDatasetRaster *pDataset,UGbool bSingleThread = FALSE);	

	UGDatasetRaster* GetDataset();

	//!	\brief	设置内存调整模式，目前支持从上往下和从下往上两种模式，默认是从上往下调整
	//!	\remark	可以根据不同的需要设置不同的内存调整模式
	void SetMemoryAdjustMode(MemoryAdjustMode md);	
	
	UGbool StatisticsBlocks( UGArray<UGImgBlock*> & updateBlocks ,UGArray<UGImgBlock*> & insertBlocks );

	MemoryAdjustMode GetMemoryAdjustMode(){return m_nMemoMode;};
	
	void BMReleaseBlockRef(UGImgBlock* pImgBlock);
	
	UGbool BMFindBlock(UGint y,UGint x,UGImgBlock*& pImgBlock,UGint nBandIndex);

	void BMAddToLRUList(UGImgBlock* pImgBlock);
	
	void BMRemoveFromLRUList(UGImgBlock* pImgBlock);

	inline UGint BMGetRecyclableCount() { return m_nRecyclableCount; };

protected:

	// LRU链表中的影像块数，即可回收的影像块数
	UGint m_nRecyclableCount;

	// LRU链表头
	UGImgBlock* m_pLruHead;

	// LRU链表尾
	UGImgBlock* m_pLruTail;

	//检查内存是否足够
	UGbool CheckMemeoryEnough();

	//栅格数据集的指针
	UGDatasetRaster *m_pRaster;

	UGDict<UGlong,UGImgBlock*> m_dictBlocks;

	//分配的Block块数组
	//UGDict<UGint,UGImgBlock*> m_aryPos;
	UGImgBlock** m_aryPos;

	//记录需要更新的Block块数组
	UGArray<UGImgBlock*> m_tempAryPos;

	//最小内存阈值
	UGulong m_dwMemoLimited;

	//分配的Block块数组的大小
	UGuint m_nArraySize;

	//内存的使用
	UGuint m_dwMemoUsed;

	MemoryAdjustMode m_nMemoMode;	

	//总的当前BlockManager总内存使用
	UGuint m_nTotal;

	//! \brief 互斥对象
	UGMutex m_mutex;

	//!	\brief	缓存模式
	CacheMode m_eCacheMode;

// 	//!	\brief	cmNoCache模式下记录当前取得的影像块
// 	UGImgBlock *m_pImgBlock;
// 
// 	//!	\brief	cmNoCache模式下记录当前取得的影像块在整个数据集中的索引
// 	UGint m_nImgBlckIndex;

	private:
		//!	\brief	设置缓存模式（缓存模式应在最初实例化好Block管理类对象时设置，使用过程中不应去做更改）
		//!	\remark	请在SetDataset之前设置好缓存模式
		void SetCacheMode(CacheMode cm);
};

}

#endif // !defined(AFX_UGIMGBLOCKMANAGER_H__1A2DC698_B9F7_40D2_8DE3_2C83B9380D68__INCLUDED_)

