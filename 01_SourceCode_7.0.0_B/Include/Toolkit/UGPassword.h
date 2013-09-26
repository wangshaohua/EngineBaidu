
#if !defined(AFX_SMPASSWORD_H__36C41F28_FE6E_43D2_A872_539AC1D3B32B__INCLUDED_)
#define AFX_SMPASSWORD_H__36C41F28_FE6E_43D2_A872_539AC1D3B32B__INCLUDED_

#include "Stream/ugdefs.h"

namespace UGC{

class TOOLKIT_API UGPassword  
{
public:
	  //!  \brief Toolkit
	UGPassword();
	  //!  \brief Toolkit
	virtual ~UGPassword();

public:
	// generate a 32 bit key according to the password(capital) 
	//改为静态吧，使用方便
	static UGuint GenerateKey(const UGchar *pw);

	//generate a 255 length byte array according to the key,stream must be a 255 length array.
	//! \brief
	void GenerateStream(UGbyte *stream,UGuint key);

	//generate a string that every char is xor of source sting. src and dest must be a 255 length array. so src's xor is dest, dext's xor is still src.
	//! \brief
	void GenerateXorString(UGbyte *src,UGbyte *dest);

protected:
	void SwapByte(UGbyte& c1,UGbyte& c2);		//swap byte c1<-->c2
};

}

#endif // !defined(AFX_SMPASSWORD_H__36C41F28_FE6E_43D2_A872_539AC1D3B32B__INCLUDED_)

