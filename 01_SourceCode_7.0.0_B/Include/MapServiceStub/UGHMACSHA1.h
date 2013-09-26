//实现hmac_sha1加密算法，
//给定密码，实现文本加密，输出加密的长度为20
//=======================================================================
/* 
base64.cpp and base64.h

Copyright (C) 2004-2008 René Nyffenegger

This source code is provided 'as-is', without any express or implied
warranty. In no event will the author be held liable for any damages
arising from the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it
freely, subject to the following restrictions:

1. The origin of this source code must not be misrepresented; you must not
claim that you wrote the original source code. If you use this source code
in a product, an acknowledgment in the product documentation would be
appreciated but is not required.

2. Altered source versions must be plainly marked as such, and must not be
misrepresented as being the original source code.

3. This notice may not be removed or altered from any source distribution.

René Nyffenegger rene.nyffenegger@adp-gmbh.ch
http://www.adp-gmbh.ch/cpp/common/base64.html
*/
//========================================================================


#if !defined(AFX_UGHMACSHA1_H__F2ACB033_F582_4263_B9E9_DCA2E56F87DE__INCLUDED_)
#define AFX_UGHMACSHA1_H__F2ACB033_F582_4263_B9E9_DCA2E56F87DE__INCLUDED_

#include "Stream/ugdefs.h"

namespace UGC 
{
static const UGString base64_chars = 
	_U("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/");

typedef struct
{
	UGuval state[5];
	UGuval count[2];
	UGuchar  buffer[64];
} SHA1_CTX;

class MAPSERVICESTUB_API UGHMACSHA1
{
public:
	//! \brief 构造函数
	UGHMACSHA1(const UGString& strKey);
	//! \brief 析构函数
	~UGHMACSHA1();

	static inline bool is_base64(UGuchar c) {return (isalnum(c) || (c == '+') || (c == '/'));}

	static UGString base64_encode(UGuchar const* bytes_to_encode, UGuint in_len);

	static UGString base64_decode(const UGString& encoded_string);

	void ComputeHash(const UGString& strContext, UGString& strHashCode);
private:
	void SHA1Transform(UGuval state[5], UGuchar buffer[64]);
	void SHA1Init(SHA1_CTX *context);
	void SHA1Update(SHA1_CTX *context, UGuchar *data, UGuval len);
	void SHA1Final(UGuchar digest[20], SHA1_CTX *context);
private:
	UGString m_strKey;
	
};
}
#endif
