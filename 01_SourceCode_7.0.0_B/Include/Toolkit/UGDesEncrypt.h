// UGDesEncrypt.h: interface for the UGDesEncrypt class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_UGDESENCRYPT_H__C364698C_5E89_4C16_8850_63871A01DC07__INCLUDED_)
#define AFX_UGDESENCRYPT_H__C364698C_5E89_4C16_8850_63871A01DC07__INCLUDED_


#include "Stream/ugdefs.h"

namespace UGC {	
	  //!  \brief Toolkit
const static UGuchar Des_key[17] = "~@!#(*&)_OP%#_*!";	
	  //!  \brief Toolkit
const static UGint Des_key_length = 16;

#ifdef OS_ANDROID // android目前的许可管理方式需要使用到这几个方法，在头文件中申明一下
enum    {ENCRYPT,DECRYPT};

// Type—ENCRYPT:加密,DECRYPT:解密
// 输出缓冲区(Out)的长度 >= ((datalen+7)/8)*8,即比datalen大的且是8的倍数的最小正整数
// In 可以= Out,此时加/解密后将覆盖输入缓冲区(In)的内容
// 当keylen>8时系统自动使用3次DES加/解密,否则使用标准DES加/解密.超过16字节后只取前16字节
bool Des_Go(char *Out,char *In,UGuint datalen,const char *Key,int keylen,bool Type = ENCRYPT);
#endif

	  //!  \brief Toolkit
class TOOLKIT_API UGDesEncrypt  
{
	
	
public:
	  //!  \brief Toolkit
	enum WorkMode
	{
	//! \brief
	  //!  \brief Toolkit
		ENCRYPT,
	//! \brief
	  //!  \brief Toolkit
		DECRYPT,
	};
	
	//! \brief
	  //!  \brief Toolkit
	UGDesEncrypt();
	//! \brief
	  //!  \brief Toolkit
	virtual ~UGDesEncrypt();
	//! \brief
	  //!  \brief Toolkit
	static UGbool Work(UGbyte *&szOut, 
					     UGbyte *szIn, 
                        UGint& datalen, 
                    const UGbyte *Key, 
                          UGint keylen, 
                     WorkMode emMode);
	//! \brief 加密工作空间,added by macx 2008.8.4 。
	//! \param strDes 返回加密后的字符串，[out]
	//! \param strWorkspaceName 工作空间名[in]。
	//! \param key 密码，加解密的key 默认为空,表示不加密[in]。
	//! \return 。
	//! \remarks 。
	//! \attention 。
	static UGbool EncryptString(UGString& strDes,const UGString& strSrc,const UGString& strPWD = (_U("")));
	//! \brief 解密工作空间,added by macx 2008.8.4 。
	//! \param strDes 返回解密后的字符串，[out]
	//! \param strWorkspaceName 工作空间名[in]。
	//! \param strKey 密码，加解密的key 默认为空，表示未加密[in]。
	//! \return 。
	//! \remarks 。
	//! \attention 。
	static UGbool DecryptString(UGString& strDes,const UGString& strSrc,const UGString& strPWD = (_U("")));	
	
};

}

#endif // !defined(AFX_UGDESENCRYPT_H__C364698C_5E89_4C16_8850_63871A01DC07__INCLUDED_)

