//////////////////////////////////////////////////////////////////////////
//                    _   _   ____   ____                    
//   Project         | | | | / ___) / ___)                   
//                   | | | || | __ | |                       
//                   | |_| || |_\ || \___                    
//                    \____/ \____| \ ___)     6.0           
//                                                           
//!  \file headerfile.h
//!  \brief Class 的接口定义。
//!  \details 该文件定义了紧凑文件管理的所有接口。
//!  \author 郑月玲。
//!  \attention 
//!   Copyright (c) 1996-2008 SuperMap Software Limited Company.  <br> 
//!   All Rights Reserved.
//!  \version 6.0
//////////////////////////////////////////////////////////////////////////
#ifndef __UGC_COMPACTFILEMANAGER_H__INCLUDE_
#define __UGC_COMPACTFILEMANAGER_H__INCLUDE_

#include "CompactFile/UGCompactFileStub.h"


namespace UGC {

class COMPACTFILE_API UGCompactFileManager
{
public:
	UGCompactFileManager(void);
	virtual ~UGCompactFileManager(void);

	static UGCompactFileManager& GetInstance();
	UGCompactFileStub* LookUp(UGdouble dScale, UGint nGroupRow, UGint nGroupCol);
	UGCompactFileStub* LookUp(UGString strKey);


private:
	UGString GetKey(UGdouble dScale, UGint nGroupRow, UGint nGroupCol);


private:
	std::map<UGString, UGCompactFileStub*> m_mapFileStubs;


	UGMutex m_mutexLock;
};
}
#endif // __UGC_COMPACTFILEMANAGER_H__INCLUDE_
