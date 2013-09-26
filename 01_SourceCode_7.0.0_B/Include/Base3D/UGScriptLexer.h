//////////////////////////////////////////////////////////////////////////
//                    _   _   ____   ____                    
//   Project         | | | | / ___) / ___)                   
//                   | | | || | __ | |                       
//                   | |_| || |_\ || \___                    
//                    \____/ \____| \ ___)     6.1           
//                                                           
//!  \file UGMaterial.h
//!  \brief 三维材质脚本解析类。
//!  \details 完成材质脚本的解析
//!  \author sunyl
//!  \attention 
//!   Copyright (c) 1996-2012 SuperMap Software Co., Ltd. <br> 
//!   All Rights Reserved.
//!  \version 6.1
//////////////////////////////////////////////////////////////////////////

#ifndef __SCRIPTLEXER_H__
#define __SCRIPTLEXER_H__

#if _MSC_VER > 1000
#pragma once
#endif

#include "Base3D/UGPrerequisites3D.h"
#include "Base3D/UGSharedPtr.h"

namespace UGC
{

	/** These codes represent token IDs which are numerical translations of
	specific lexemes. Specific compilers using the lexer can register their
	own token IDs which are given precedence over these built-in ones.
	*/
	enum{
		TID_LBRACKET = 0, // {
		TID_RBRACKET, // }
		TID_COLON, // :
		TID_VARIABLE, // $...
		TID_WORD, // *
		TID_QUOTE, // _U("*")
		TID_NEWLINE, // \n
		TID_UNKNOWN,
		TID_END
	};

	/** This struct represents a token, which is an ID'd lexeme from the
	parsing input stream.
	*/
	struct ScriptToken
	{
		/// This is the lexeme for this token
		UGString lexeme, file;
		/// This is the id associated with the lexeme, which comes from a lexeme-token id mapping
		UGuint type;
		/// This holds the line number of the input stream where the token was found.
		UGuint line;
	};
	typedef UGSharedPtr<ScriptToken> ScriptTokenPtr;
	typedef std::vector<ScriptTokenPtr> ScriptTokenList;
	typedef UGSharedPtr<ScriptTokenList> ScriptTokenListPtr;

//! \brief 三维材质类。
class BASE3D_API UGScriptLexer
{
public:
	//! \brief 构造函数。
	UGScriptLexer();
	//! \brief 构造函数。
	virtual ~UGScriptLexer(){}

	/** Tokenizes the given input and returns the list of tokens found */
	ScriptTokenListPtr tokenize(const UGString &str, const UGString &source);
private: // Private utility operations
	void setToken(const UGString &lexeme, UGuint line, const UGString &source, ScriptTokenList *tokens);
	UGbool isWhitespace(UGString c) const;
	UGbool isNewline(UGString c) const;


public:

	

} ;
}

#endif 


