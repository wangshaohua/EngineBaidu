//////////////////////////////////////////////////////////////////////////
//                    _   _   ____   ____                    
//   Project         | | | | / ___) / ___)                   
//                   | | | || | __ | |                       
//                   | |_| || |_\ || \___                    
//                    \____/ \____| \ ___)     6.0           
//                                                           
//!  \file  UGBitSet.h
//!  \brief UGBitSet
//!  \details 使用Bit的一个数组并实现了元素的记录集行为,包括MoveNext,IsEof,GetRecordCount,SeekID等.
//!  \author wangmao。
//! Copyright (c) UGC, a staff of SuperMap Software Co., Ltd. 2008. All Rights Reserved. <br>
//!  \version 6.0
//////////////////////////////////////////////////////////////////////////
#ifndef UGUGBITSET_H
#define UGUGBITSET_H

#include "Stream/ugdefs.h"
namespace UGC
{
	
class ENGINE_API UGBitSet  
{
public:
	//! \brief 构造
	UGBitSet(const UGint nSize, UGbool bOrdered = FALSE);
	//! \brief 析构
#ifdef SYMBIAN60
	~UGBitSet();
#else
	virtual ~UGBitSet();
#endif
	
	//! \brief 赋值函数
	const UGBitSet& operator=(const UGBitSet& cBitSet);
	//! \brief  相等判断 
	UGbool operator==(const UGBitSet& cBitsetCmp) const;
	//! \构造
	UGBitSet();

public:
	//! \brief 得到记录的条数。
	//! \return 记录数。
	UGuint  GetRecordCount()const;

	//! \brief 设置记录的条数。
	//! \return 记录数。
	UGbool  SetRecordCount(UGint nRecordCount);

	//! \brief 增加一条记录。
	//! \param nID 添加的ID[in]。
	//! \return 添加是否成功。
	UGbool  AddReocrd(const UGuint nID);	

	//! \brief 删除一条记录。
	//! \param nID 要删除的ID[in]。
	//! \return 删除是否成功。
	UGbool  DeleteRecord(const UGint nID);	

	//! \brief 移动到第一条记录。
	//! \return 当前的ID。。
	UGbool  MoveFirst();	

	//! \brief 移动到下一条记录。
	//! \return 当前的ID。
	UGbool  MoveNext(); 

	//! \brief 移动到前一条记录。
	//! \return 当前的ID。
	UGbool  MovePrev();
	
	//! \brief 移动到最后一条记录。
	//! \return 当前的ID。
	UGbool  MoveLast();

	//! \brief 移动到当前记录的nRowOffset偏移
	//! \return 当前的ID。
	UGbool  Move(UGint nRowOffset);

	//! \brief 移动到指定的记录位置。
	//! \param nRow 第几条记录[in]。
	//! \remarks nRow = 0为移动到First
	UGbool  MoveTo(UGint nRow);	

	//! \brief 得到当前ID。
	//! \return 当前ID。
	UGint  GetID() const;	

	//! \brief 移动到指定id的记录位置。
	//! \param nID 给定的ID[in]。
	//! \return 移动是否成功。
	UGbool  SeekID(UGint nID);	

	//! \brief 测试nID是否在数组中
	//! \param nID 给定的需要测试的ID[in]。
	//! \return 存在返回1不存在返回0
	UGuint  TestID(UGuint nID);	
	
	//! \brief 是否是第一条记录之前。
	UGbool  IsBOF() const;	
	
	//! \brief 是否是最后一条记录之后。
	UGbool  IsEOF() const;

	UGint GetCurrentIndex() const;

private:
	void   FindFirstBitInChar(UGuchar *pStart,UGbool bDir);
	//! \remarks 内存的bit数。
	UGuint	m_nSize;
	
	//! \brief 内存开始的指针
        UGuchar *m_pByte;

	//! \brief 当前的索引位置
	UGint  m_CurrentIndex;

	//! \brief 最大的索引位置
	UGint  m_nMaxIndex;

	//! \brief 最小的索引位置
	UGint  m_nMinIndex;

	//! \brief 记录数量
	UGuint m_nRecordCount;

	OgdcArray<UGint> m_arrOrderedIDs;

	UGbool m_bOrdered;

private:
	UGBitSet(const UGBitSet& bitset);
};

}
#endif // !defined(UGBITSET_H)

