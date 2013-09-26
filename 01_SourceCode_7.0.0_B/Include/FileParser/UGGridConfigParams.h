
#ifndef __UGGRIDCONFIGPARAMS_H__
#define __UGGRIDCONFIGPARAMS_H__

#include "FileParser/UGRasterConfigParams.h"
#include "FileParser/UGExchangeFileType.h"

namespace UGC
{
	class FILEPARSER_API UGGridImportParams : public UGRasterImportParams
	{
	public:
		//! \brief 构造函数。
		UGGridImportParams();
		
		//! \brief 析构函数。
		virtual ~UGGridImportParams();
	public:
		
		//! \brief 重载获取文件格式类型的函数。
		virtual UGint GetFileType() const	{ return UGFileType::AIASCIIGrid; }
		
	private:
	};

	
	class FILEPARSER_API UGGridExportParams : public UGRasterExportParams
	{
	public:
		//! \brief 构造函数。
		UGGridExportParams();

		//! \brief 析构函数。
		virtual ~UGGridExportParams();
	public:
		//! \brief 重载获取文件格式类型的函数。
		virtual UGint GetFileType() const	{ return UGFileType::AIASCIIGrid; }
	private:
	};
}

#endif
