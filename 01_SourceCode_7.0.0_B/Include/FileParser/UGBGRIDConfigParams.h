// UGGifConfigParams.h: interface for the UGGifImportParams class.
//////////////////////////////////////////////////////////////////////////
//                    _   _   ____   ____                    
//   Project         | | | | / ___) / ___)                   
//                   | | | || | __ | |                       
//                   | |_| || |_\ || \___                    
//                    \____/ \____| \ ___)     6.0           
//                                                           
//!  \file headerfile.h
//!  \brief Class ¡£
//!  \details ¡£
//!  \author zby¡£
//!  \attention 
//!   Copyright (c) 1996-2010 SuperMap Software Limited Company.  <br> 
//!   All Rights Reserved.
//!  \version 6.0
//////////////////////////////////////////////////////////////////////////

#if !defined(AFX_UG_BGRID_FILEPARSERCONFIGPARAMS_H__INCLUDED_)
#define AFX_UG_BGRID_FILEPARSERCONFIGPARAMS_H__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "FileParser/UGRasterConfigParams.h"
#include "FileParser/UGExchangeFileType.h"

namespace UGC 
{
    ///////////////////////////////FILEBIL///////////////////////////////////
	class FILEPARSER_API UGBILImportParams : public UGRasterImportParams  
	{
	public:
        
		UGBILImportParams(){m_strWorldFile= _U("");}
		virtual ~UGBILImportParams(){}
		virtual inline UGint GetFileType() const { return UGFileType::BIL; }
		void SetWorldFilePath(const UGString& strWorldFile) { m_strWorldFile = strWorldFile; }
		UGString GetWorldFilePath() const { return m_strWorldFile; }

	protected:

		UGString m_strWorldFile;

	};
    ////////////////////////////////FILEBSQ//////////////////////////////////
	class FILEPARSER_API UGBSQImportParams : public UGRasterImportParams  
	{
	public:
		UGBSQImportParams(){m_strWorldFile =_U("");}
		virtual ~UGBSQImportParams(){}

		virtual inline UGint GetFileType() const { return UGFileType::BSQ; }
		void SetWorldFilePath(const UGString& strWorldFile) { m_strWorldFile = strWorldFile; }
		UGString GetWorldFilePath() const { return m_strWorldFile; }

	protected:

		UGString m_strWorldFile;

	};
    ////////////////////////////////FILEBIP//////////////////////////////////
	class FILEPARSER_API UGBIPImportParams : public UGRasterImportParams  
	{
	public:
        
		UGBIPImportParams(){m_strWorldFile=_U("");}
		virtual ~UGBIPImportParams(){}

		virtual inline UGint GetFileType() const { return UGFileType::BIP; }
		void SetWorldFilePath(const UGString& strWorldFile) { m_strWorldFile = strWorldFile; }
		UGString GetWorldFilePath() const { return m_strWorldFile; }

	protected:

		UGString m_strWorldFile;

	};
}

#endif 

