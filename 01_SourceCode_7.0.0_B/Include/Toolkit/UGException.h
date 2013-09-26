/*! \file	 UGException.h
 *  \brief	 异常定义类
 *  \author	 ugc team
 *  \attention 
 *  Copyright(c) 2000-2010 SuperMap Software Co., Ltd.<br>
 *  All Rights Reserved
 *  \version $Id: UGException.h,v 1.4 2009/11/05 09:36:46 siyh Exp $
 */

#ifndef UGEXCEPTION_H
#define UGEXCEPTION_H

#include "Stream/ugdefs.h"
#include "UGErrorObj.h"

namespace UGC {

//! \brief 异常基类，UGC中自定义的所有异常类，应该从UGException继承
class TOOLKIT_API UGException  
{
public:

	//! \brief 构造函数。
	//! \param nErrorID [in] 错误信息的字符串资源ID。
	//! \param strMessage [in] 信息字符串。
	//! \param strCodeFile [in] 异常发生的代码文件。
	//! \param nCodeLine [in] 异常发生的代码行。
	UGException(UGuint nErrorID,
		const UGString& strMessage,
		const UGString& strCodeFile,
		UGint nCodeLine);
	
	//! \brief 构造函数。
	//! \param strErrorID [in] 错误信息的字符串资源ID。
	//! \param strMessage [in] 信息字符串。
	//! \param strCodeFile [in] 异常发生的代码文件。
	//! \param nCodeLine [in] 异常发生的代码行。
	UGException(const UGString& strErrorID,
		const UGString& strMessage,
		const UGString& strCodeFile,
		UGint nCodeLine);
	
	//! \brief 构造函数。
	//! \param nErrorID [in] 错误信息的字符串资源ID。
	//! \param strCodeFile [in] 异常发生的代码文件。
	//! \param nCodeLine [in] 异常发生的代码行。
	UGException(UGuint nErrorID,
		const UGString& strCodeFile,
		UGint nCodeLine);

	//! \brief 构造函数。
	//! \param strErrorID [in] 错误信息的字符串资源ID。
	//! \param strCodeFile [in] 异常发生的代码文件。
	//! \param nCodeLine [in] 异常发生的代码行。
	UGException(const UGString& strErrorID,
		const UGString& strCodeFile,
		UGint nCodeLine);

	//! \brief 把异常的内容写入到日志中。
	//! \remarks 异常的构造函数中，会调用本函数。
	virtual void WriteToLog();	

	//! \brief 得到内部维护的错误信息结构。
	//! \return 返回内部维护的错误信息结构。
	const UGErrorObj::ErrorInfo& GetErrorInfo() const;	


private:
	//! \brief 内部维护的错误信息结构
	UGErrorObj::ErrorInfo m_ErrorInfo;
};

}

#endif



