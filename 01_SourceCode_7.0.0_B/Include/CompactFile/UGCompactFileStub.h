//////////////////////////////////////////////////////////////////////////
//                    _   _   ____   ____                    
//   Project         | | | | / ___) / ___)                   
//                   | | | || | __ | |                       
//                   | |_| || |_\ || \___                    
//                    \____/ \____| \ ___)     6.0           
//                                                           
//!  \file headerfile.h
//!  \brief Class 的接口定义。
//!  \details 该文件定义了紧凑文件访问的所有接口。
//!  \author 基础内核组。
//!  \attention 
//!   Copyright (c) 1996-2008 SuperMap Software Limited Company.  <br> 
//!   All Rights Reserved.
//!  \version 6.0
//////////////////////////////////////////////////////////////////////////
#ifndef __UGC_COMPACTFILESTUB_H__INCLUDE_
#define __UGC_COMPACTFILESTUB_H__INCLUDE_

#include "CompactFile/UGCompactFile.h"
#include "Toolkit/UGThread.h"

using namespace std;

namespace UGC
{
#define MAPMAXSIZE 4

	class COMPACTFILE_API UGCompactFileStub
	{
	public:
		//! \brief 构造函数
		UGCompactFileStub();

		//! \brief 析构函数
		~UGCompactFileStub();


		void SetPath(UGString strFilePath);

		UGbool Read(UGuint nRow, UGuint nCol, UGByteArray &context, UGulong &lValidByte, const UGulong nVersionNum = 0);

		UGbool Write(UGuint nRow, UGuint nCol, const UGByteArray & context, UGulong lDataSize = 0, UGulong lOffset = 0, const UGulong nVersionNum = 0);

	private:
		UGMutex m_mutexLock;

		UGString m_strFilePath; // 紧凑文件的路径名

		UGCompactFileWriter* m_pCompactFileWriter;
		std::map<UGint, UGCompactFileReader*> m_mapCompactFileReader;    //ugint 为线程id

	};
}
#endif //__UGC_COMPACTFILESTUB_H__INCLUDE_
