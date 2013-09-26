//////////////////////////////////////////////////////////////////////////
//                    _   _   ____   ____                    
//   Project         | | | | / ___) / ___)                   
//                   | | | || | __ | |                       
//                   | |_| || |_\ || \___                    
//                    \____/ \____| \ ___)     6.1           
//                                                           
//!  \file UGMaterial.h
//!  \brief 三维材质脚本解析类
//!  \details 完成材质脚本的解析
//!  \author sunyl
//!  \attention 
//!   Copyright (c) 1996-2012 SuperMap Software Co., Ltd. <br> 
//!   All Rights Reserved.
//!  \version 6.1
//////////////////////////////////////////////////////////////////////////

#ifndef __SCRIPTPARSER_H__
#define __SCRIPTPARSER_H__

#if _MSC_VER > 1000
#pragma once
#endif

#include "Base3D/UGPrerequisites3D.h"
#include "Base3D/UGScriptCompiler.h"
#include "Base3D/UGScriptLexer.h"

namespace UGC
{

//! \brief 三维材质类。
class BASE3D_API UGScriptParser
{
public:
	//! \brief 构造函数。
	UGScriptParser();
	//! \brief 构造函数。
	virtual ~UGScriptParser(){}

	ConcreteNodeListPtr parse(const ScriptTokenListPtr &tokens);
	ConcreteNodeListPtr parseChunk(const ScriptTokenListPtr &tokens);
private:
	ScriptToken *getToken(ScriptTokenList::iterator i, ScriptTokenList::iterator end, UGint offset);
	ScriptTokenList::iterator skipNewlines(ScriptTokenList::iterator i, ScriptTokenList::iterator end);


} ;
}

#endif 


