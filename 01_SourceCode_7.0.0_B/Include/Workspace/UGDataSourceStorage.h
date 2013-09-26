// UGDataSourceStorage.h: interface for the UGDataSourceStorage class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_UGDATASOURCESTORAGE_H__7A3542C1_D7DA_4293_BC72_8C7F41279924__INCLUDED_)
#define AFX_UGDATASOURCESTORAGE_H__7A3542C1_D7DA_4293_BC72_8C7F41279924__INCLUDED_

#include "Stream/UGStream.h"

namespace UGC {

class WORKSPACE_API UGDataSourceStorage  
{
public:
	UGDataSourceStorage();
#ifdef SYMBIAN60
	~UGDataSourceStorage();
#else
	virtual ~UGDataSourceStorage();
#endif

};

}

#endif // !defined(AFX_UGDATASOURCESTORAGE_H__7A3542C1_D7DA_4293_BC72_8C7F41279924__INCLUDED_)

