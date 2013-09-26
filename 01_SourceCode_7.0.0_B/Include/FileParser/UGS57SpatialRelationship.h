#ifndef UGS57SPATIALRELATIONSHIP_H
#define UGS57SPATIALRELATIONSHIP_H

#include "Stream/ugdefs.h"

namespace UGC
{
	//! \brief 存储S57中FSPT的字段信息，从数据集ENC_FVE中读取
	struct UGS57FSPT 
	{
		//! \brief 对应字段VE_RCID值
		UGuint nRCID;
		//! \brief 对应字段ORNT值
		UGushort nORNT;
		//! \brief 对应字段USAG值
		UGushort nUSAG;
		//! \brief 对应字段MASK值
		UGushort nMASK;
		//! \brief RCNM值
		UGint nRCNM;
		UGS57FSPT()
		{
			nRCID = 0;
			nORNT = 255;
			nUSAG = 255;
			nMASK = 255;
			nRCNM = 0;
		}
	};
	//! \brief 存储S57中描述的关联关系，从数据集ENC_RS中读取
	struct UGS57RS
	{
		//! \brief 目标物标的17位长名，对应字段DEST_NAME
		UGString strDESTLNAM;
		//! \brief 关联关系类型，对应字段RIND
		UGshort nRIND;
		//! \brief 说明信息，对应字段COMT
		UGString strCOMT;
		// 目标物标的别名...
		UGString strSrcAcronym;
		UGString strDestAcronym;


		UGS57RS()
		{
			strDESTLNAM.Empty();
			nRIND = 0;
			strCOMT.Empty();
			strSrcAcronym.Empty();
			strDestAcronym.Empty();
		}
	};

	struct UGS57Feature 
	{
		UGuint   unFeatureID;
		UGint    nOBJL;
		UGString strPRIM;
		UGshort  nRCNM;
		UGS57Feature()
		{
			unFeatureID = 0;
			nOBJL = 0;
			strPRIM.Empty();
			nRCNM = 0;
		}
		~UGS57Feature()
		{
			//strPRIM.Empty();
		}

		friend UGbool operator < (const UGS57Feature& lhs, const UGS57Feature& rhs)
		{
			return lhs.unFeatureID < rhs.unFeatureID;
		}

		friend UGbool operator == (const UGS57Feature& lhs, const UGS57Feature& rhs)
		{
			return lhs.unFeatureID == rhs.unFeatureID;
		}
	};
	typedef   UGArray<UGS57Feature> UGS57Features;
	typedef   UGArray<UGS57FSPT> UGS57FSPTS;
	typedef   UGArray<UGS57RS> UGS57RSS;
};

#endif
