/*! \file	 UGQueryDef.h
 *  \brief	 查询定义类
 *  \author	 ugc team
 *  \attention 
 *  Copyright(c) 2000-2010  SuperMap GIS Technologies,Inc.<br>
 *  All Rights Reserved
 *  \version $Id: UGQueryDef.h,v 1.8 2009/11/05 09:22:23 siyh Exp $
 */

#include "Geometry/UGGeometry.h"
#include "Engine/UGEngDefs.h"
#include "OGDC/OgdcQueryDef.h"

#ifndef UGQUERYDEF_H
#define UGQUERYDEF_H

namespace UGC
{

//! \brief 查询定义类
//##ModelId=482030500290
class ENGINE_API UGQueryDef : public OgdcQueryDef
{
public:
	//! \brief  构造函数
	//##ModelId=482030500292
	UGQueryDef();
	//! \brief  析构函数
	//##ModelId=48203050029F
	~UGQueryDef();
	
	//##ModelId=4820305002AF
	void operator=(const UGQueryDef &querydef);

	//##ModelId=4820305002B1
	UGbool operator==(const UGQueryDef &querydef);

	//! \brief  将查询定义信息存为XML格式
	//! \param nVersion 版本号
	//! \return 导出的XML格式字符串
	//##ModelId=4820305002C0
	UGString ToXML(UGint nVersion) const;

	//! \brief 从XML中解析查询定义信息(存储工作空间时，有可能会用到，比如替换以前地图的DisplayFilter)
	//! \param strXML XML格式字符串
	//! \param nVersion 版本号	
	//##ModelId=4820305002CE
	UGbool FromXML(const UGString& strXML,UGint nVersion);

	//! \brief 字符集转换
	UGbool TransCharset(UGString::Charset eCharset);

protected:
	//##ModelId=4820305002DE
	UGString GetQueryType(QueryType nType) const;
	//##ModelId=4820305002E1
	void SetQueryType(UGString strQueryType);

public:
	//! \brief 时序数据的显示时间点
	//##ModelId=4820305002E3
	UGTime				m_SequenceTime;

	//! \brief 是否查询顶点序列，默认不查出来
	UGbool m_bVertexSeq;
};

}

#endif


