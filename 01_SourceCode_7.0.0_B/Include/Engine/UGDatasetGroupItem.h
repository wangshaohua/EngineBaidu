#pragma once

#include "Stream/ugdefs.h"

namespace UGC {

class ENGINE_API UGDatasetGroupItem
{
public:
	UGDatasetGroupItem(void);
	UGDatasetGroupItem(UGString strTableName,UGString strDescription);

	~UGDatasetGroupItem(void);
	
	UGbool SetExtData(UGString &strExtData);
	UGString GetExtData();

	UGString m_strDatasetTableName;
	UGString m_strDescription;
	UGString m_strExtData;
};

}


