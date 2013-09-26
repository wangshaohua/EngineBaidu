/*! \file	 ugeng.h
 *  \brief	 数据引擎的相关类型定义
 *  \author	 ugc team
 *  \attention 
 *  Copyright(c) 2000-2010  SuperMap GIS Technologies,Inc.<br>
 *  All Rights Reserved
 *  \version $Id: ugeng.h,v 1.17 2010/04/08 02:16:03 zhangshuo Exp $
 */

#ifndef UGENG_H
#define UGENG_H
#include "Stream/ugdefs.h"

namespace UGC {

//##ModelId=482030510261
enum UGEngAction 
{
	//##ModelId=482030510263
	eaBeginTrans		= 1,
	//##ModelId=482030510264
	eaCommitTrans		= 2,
	//##ModelId=482030510265
	eaRollbackTrans		= 3,
	//##ModelId=482030510266
	eaCheckOut			= 4,
	//##ModelId=482030510271
	eaCheckIn			= 5,
	//##ModelId=482030510272
	eaUndoCheckOut		= 6,
	//##ModelId=482030510273
	eaLock				= 7,
	//##ModelId=482030510274
	eaUnlock			= 8,
	//##ModelId=482030510280
	eaShowSequence		= 9,
	//##ModelId=482030510281
	eaShowMiniature		= 10,
	//##ModelId=482030510282
	eaLoginLongTrans	= 11,
	//##ModelId=482030510283
	eaLogoutLongTrans	= 12,
	//##ModelId=482030510284
	eaUserLock			= 13,
	//##ModelId=482030510290
	eaTrans				= 14,
	//##ModelId=482030510291
	eaLongTrans			= 15,
	//##ModelId=482030510292
	eaBuildPyramid		= 16,
	//##ModelId=482030510293
	eaCache				= 17,
	//##ModelId=482030510294
	eaReadOnly			= 18,
	//##ModelId=48203051029F
	eaTIN				= 19,
	//##ModelId=4820305102A0
	eaRename			= 20

};

//! \brief 引擎支持的能力
//##ModelId=4820305102A1
enum UGEngAbility
{
	//##ModelId=4820305102AF
	ebReadOnly			= 1,
	//##ModelId=4820305102B0
	ebLibrary			= 2,
	//##ModelId=4820305102B1
	ebFileCache			= 3,
	//##ModelId=4820305102B2
	ebLongTrans			= 4,
	//##ModelId=4820305102B3
	ebSequence			= 5,
	//##ModelId=4820305102B4
	ebUserLock			= 6
};

//##ModelId=4820305102BF
enum UGStatisticMode
{
	//##ModelId=4820305102C1
	smMax				= 1,	//! 最大值
	//##ModelId=4820305102C2
	smMin				= 2,	//! 最小值
	//##ModelId=4820305102CE
	smAvg				= 3,	//! 平均值 
	//##ModelId=4820305102CF
	smSum				= 4,	//! 总和
	//##ModelId=4820305102D0
	smStdev				= 5,	//! 标准差
	//##ModelId=4820305102D1
	smVar				= 6		//! 方差
};

//! \brief 数据引擎类型
//##ModelId=4820305102DE
enum UGEngineType
{	
	//##ModelId=4820305102E0
	NOEngine		=-1,
	//##ModelId=4820305102E1
	SDB				=0,		// SdbPlus引擎
	//MDB			=1,
	//SQLServer		=2,		// SDX for SQL Server
	//##ModelId=4820305102EE
	Oracle			=3,
	//##ModelId=4820305102EF
	SDE				=4,		// SDX for SDE
	//##ModelId=4820305102F0
	ImagePlugins	=5,		// 用户可以自定义的显示image格式的插件
	//SIT			=6,		// SIT格式影像文件引擎
	//##ModelId=4820305102F1
	MicroStation	=8,		
	//##ModelId=4820305102F2
	AutoCAD			=9,		// AutoCAD File, *.DXF , *.DWG
	//##ModelId=4820305102FD
	OracleSpatial	=10,	//11,	//Oracle Spatial类型引擎，Added by lsj at 2001年6月7日 08:32:05
	//##ModelId=4820305102FE
	OraclePlus		=12,	// SDX Plus for Oracle
	//##ModelId=4820305102FF
	SDBPlus			=14,		
	//##ModelId=482030510300
	SybasePlus      =15,	// 6,   // 第三代SyBase引擎
	//##ModelId=482030510301
	SQLPlus			=16,	// 3,	// 第三代Sql
	//##ModelId=48203051030D
	DMPlus			=17,	// 7,   // 第三代DM
	//##ModelId=48203051030E
	DB2             =18,
	//##ModelId=48203051030F
	Kingbase		=19,	// Kingbase金仓数据库
	//##ModelId=482030510310
	Memory			=20,    // 内存数据源
	//##ModelId=48203051031C
	ROF             =21,    // Ready only file 只读文件引擎
	//##ModelId=48203051031D
	WEB				=23,	// 跨平台网络数据引擎 add by duxiaomin
	//##ModelId=48203051031E
	UDB20			=30,    // 跨平台文件引擎 已经由UDB替代
	MySQL			=32,    // MySQL引擎 add by cuiwz
	//##ModelId=48203051031F
	ExtFile			=101,	// 外部文件只读引擎
	//##ModelId=48203051031E
	UDB			    =219,   //Universal Data Base,通用跨平台文件数据源
	
	Informix        =108,

	NetCDF			= 220,

	PostgreSQL      =221,
	//GoogleMaps数据源
	GoogleMaps		=223,
    
	SuperMapCloud  = 224,
    
	Rest			=225,
   //  天地图数据源
    MapWorldMaps  = 226,

	BaiDu        =  227,

	OpenStreetMaps = 228,

	SCV			   = 229,
    //支持PCI影像格式,同时间接支持其它多种遥感数据格式

	PCI             =300     //add by yangbiao  2011/06/09
	
};

}

#endif

