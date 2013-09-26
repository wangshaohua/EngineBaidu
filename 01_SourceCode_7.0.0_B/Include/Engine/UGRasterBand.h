// UGRasterBand.h: interface for the UGRasterBand class.
//
//////////////////////////////////////////////////////////////////////

#ifndef UGDATASETBAND_H_PP
#define UGDATASETBAND_H_PP

#include "Stream/ugdefs.h"
#include "Engine/UGDatasetRaster.h"

namespace UGC
{

class ENGINE_API UGRasterBand: public UGDatasetRaster
{
public:
	UGRasterBand();
#ifdef SYMBIAN60
	~UGRasterBand();
#else
	virtual ~UGRasterBand();
#endif
	
private:
	UGint m_nvv;
};

}

#endif // !defined(UGDATASETBAND_H_PP)

