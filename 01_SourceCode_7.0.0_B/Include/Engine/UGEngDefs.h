#ifndef UGENGDEFS_H
#define UGENGDEFS_H

#include "Geometry/UGGeoRegion.h"
#include "OGDC/OgdcQueryDef.h"
#include "OGDC/OgdcDsConnection.h"
//#include "OGDC/OgdcFieldInfo.h"

#if !defined SYMBIAN60 /*&& !defined  OS_ANDROID && !defined (IOS)*/
#include "Geometry/UGFeature.h"

#else
#include  "Element/OgdcFieldInfo.h"

typedef OgdcFieldInfo UGFieldInfo;
typedef OgdcFieldInfos UGFieldInfos;

#endif

namespace UGC
{
// 设置纹理数据集的名称
const UGString strTexture = _U("sm_Texture_Lib");
// 设置纹理数据集对应的金字塔数据集的名称
const UGString strTextureTier = _U("sm_Texture_Tier");
	
#define UGMAXONCEGEOSIZE	20971520
#define UGMAXROOTLEAFSIZE   1258496
#define UGMAXTABLENAMELENGTH 17

#define UGRTREEEDITED		5
	
#define UGSYSDATE			_U("UGSysDate")	//引擎统一当前系统时间标识


//===================================================================================================================
//{{图层字段定义 
//===================================================================================================================
//		宏名				字段名				类型			说明		适用的图层类型
//...................................................................................................................
#define LF_OBJ_ID		_U("SmID")			// (dbLong)			内部编号	(All)
#define LF_USER_ID		_U("SmUserID")		// (dbLong)			用户编号	(All)
#define LF_TREE_INDEX	_U("SmKey")			// (dbLong)			四叉数索引	ALL Geometry Dataset.   
#define LF_LT_KEY		_U("SmLTKey")		// (dbLong)			网格索引	All Geometry Dataset.
#define LF_RB_KEY		_U("SmRBKey")		// (dbLong)			网格索引	All Geometry Dataset.
#define LF_GEO_POS		_U("SmGeoPos")		// (dbLong)			Geometry的位置	All Geometry Dataset.
#define LF_GEOMETRY		_U("SmGeometry")	// (dbLongBinary)	几何数据	ltNetwork, ltLine, ltRegion, ltTin, ltText
#define LF_VERTEXSEQ	_U("SmVertexSeq")	// (dbLongBinary)	顶点索引序列	ltNetwork, ltLine, ltRegion, ltTin, ltText
#define LF_GEO_TYPE		_U("SmGeoType")		// (dbSingle)		对象的类型	ltCAD ,because geometry data can't distinguish type of itself
#define LF_SDRI_W		_U("SmSdriW")		// (dbDouble)		最小横坐标	ltNetwork, ltLine, ltRegion, ltTin, ltText
#define LF_SDRI_N		_U("SmSdriN")		// (dbDouble)		最小纵坐标	ltNetwork, ltLine, ltRegion, ltTin, ltText
#define LF_SDRI_E		_U("SmSdriE")		// (dbDouble)		最大横坐标	ltNetwork, ltLine, ltRegion, ltTin, ltText
#define LF_SDRI_S		_U("SmSdriS")		// (dbDouble)		最大纵坐标	ltNetwork, ltLine, ltRegion, ltTin, ltText
#define LF_GRANULE		_U("SmGranule")		//(dbDouble)		对象颗粒度  ltNetwork, ltLine, ltRegion, ltTin, ltText
#define LF_CHECKED_USER_ID	_U("SmCheckedUserID")	//(dbLong)	登录用户ID	(ALL)
#define LF_EDIT_STATE	_U("SmEditState")	//(dbInteger)		编辑状态	(ALL)
#define LF_SDRI_T		_U("SmSdriT")		// (dbDouble)		最小高程	ltTin
#define LF_SDRI_B		_U("SmSdriB")		// (dbDouble)		最大高程	ltTin
#define LF_SDRI_I		_U("SmSdriI")		// (dbDouble)		大小索引	ltNetwork, ltLine, ltRegion, ltTin, ltText
#define LF_NODE_ID		_U("SmNodeID")		// (dbLong)			节点编号，	ltNetwork,以前默认使用SmID,现在单独建立一个字段
#define LF_FNODE		_U("SmFNode")		// (dbLong)			起始节点	ltNetwork
#define LF_TNODE		_U("SmTNode")		// (dbLong)			终止节点	ltNetwork
#define LF_RESISTANCE_A	_U("SmResistanceA")	// (dbDouble)		正方向阻力	ltNetwork
#define LF_RESISTANCE_B	_U("SmResistanceB")	// (dbDouble)		负方向阻力	ltNetwork
#define LF_X			_U("SmX")			// (dbDouble)		点横坐标的	ltPoint & ltPoint3D
#define LF_Y			_U("SmY")			// (dbDouble)		点的纵坐标	ltPoint & ltPoint3D
#define LF_Z			_U("SmZ")			// (dbDouble)		点的高程	ltPoint3D
#define LF_LENGTH		_U("SmLength")		// (dbDouble)		长度		ltLine& Network
#define LF_AREA			_U("SmArea")		// (dbDouble)		面积		ltRegion
#define LF_PERIMETER	_U("SmPerimeter")	// (dbDouble)		周长		ltRegion 
#define LF_ASPECT		_U("SmAspect")		// (dbDouble)		坡向		ltTin
#define LF_SLOPE		_U("SmSlope")		// (dbDouble)		坡度		ltTin
#define LF_TOPO_ERROR	_U("SmTopoError")	// (dbLong)			拓扑错误	ltNetwork, ltLine
#define LIB_SMID		_U("SmLibTileID")
#define LF_UUID			_U("SmUUID")		// (dbChar(36))		全球唯一编码	ALL Geometry Dataset

#define LF_CONJOINT_POINTS		_U("SmConjointPoints")	// (dbLongBinary)			TIN节点的临近点集合	ltPointGL
#define	LF_POINT_COLOR			_U("SmPointColor")		//TIN节点的颜色，负值表示无效

//{{ route数据集及其Section表的字段
#define LF_ROUTE_ID				_U("SmRouteID")
#define LF_USER_ROUTE_ID		_U("SmUserRouteID")

#define LF_SECTION_ARC			_U("SmEdgeID")
#define LF_SECTION_FROM_MEASURE _U("SmFromMeasure")	
#define LF_SECTION_TO_MEASURE	_U("SmToMeasure")	
#define LF_SECTION_FROM_POS		_U("SmFromPos")		
#define LF_SECTION_TO_POS		_U("SmToPos")		

//}}

//{{
#define LF_MATCH_ERROR _U("SmMatchError") // 使用CSmDataSource::UpdateFromLcaPnts()方法
                                          // 从标志点匹配属性数据到其他数据集时（面），
                                          // 记录下匹配点数目。
                                             
//}}

//{{
#define LF_TOPO_LPOLY  _U("SmTopoLPolygon")
#define LF_TOPO_RPOLY  _U("SmTopoRPolygon")

//}}
//					0	- 无错误
//					1	- 起始节点是悬节点
//					2	- 终止节点是悬节点
//					3	- 两个节点都是悬节点
//					其他- 由王红定义...)

/*
#define LF_RASTER_LEVEL		"SmRLevel"		// (dbLong)			栅格分辨率			ltRaster
#define LF_RASTER_INDEX_X		"SmRIndexX"		// (dbLong)			栅格块X索引(列号)	ltRaster
#define LF_RASTER_INDEX_Y		"SmRIndexY"		// (dbLong)			栅格块Y索引(行号)	ltRaster

#define LF_SYMBOL_STYLE			"SmSStyle"
#define LF_SYMBOL_SIZE			"SmSSize"
#define LF_SYMBOL_ROTATION		"SmSRotation"
#define LF_SYMBOL_TEXT			"SmSText"

#define LF_PEN_STYLE			"SmPStyle"
#define LF_PEN_WIDTH			"SmPWidth"
#define LF_PEN_COLOR			"SmPColor"

#define LF_BRUSH_STYLE			"SmBStyle"
#define LF_BRUSH_FRONT_COLOR	"SmBFColor"
#define LF_BRUSH_BACK_COLOR		"SmBBColor"
 */

//===================================================================================================================
//}}图层字段定义
//===================================================================================================================

#if PACKAGE_TYPE==PACKAGE_UGC


//说明：定义一些在引擎中需要使用的系统表的名字

//===============================================================================
//			宏名					名称						说明		
//................................................................................
#define		TN_REGISTER_TABLE		_U("SmRegister")			//数据库中矢量数据集的注册表，记所有矢量数据集的信息	
#define		TN_IMGREGISTER_TABLE	_U("SmImgRegister")			//数据库中影像数据集的注册表，记所有影像数据集的信息	
#define     TN_DATASOURCE_INFO		_U("SmDataSourceInfo")		//数据源信息表
#define		TN_META_ELEM_TABLE		_U("SmMetaElementTable")	//数据源中存放所有元数据的表
#define		TN_USERS				_U("SmUsers")				//存放长事务用户
#define		TN_TABLE_FIELDINFO		_U("SmFieldInfo")			//存放字段相关的信息，如别名、Format等



//说明：定义一些在引擎中需要使用的存储过程名.

//===============================================================================
//			宏名					名称						说明		
//................................................................................
#define		SP_CREATE_USER			_U("smsp_CreateUser")		//创建用户的存储过程
#define		SP_CREATE_DATASET		_U("smsp_CreateDataset")	//创建数据集的存储过程
#define		SP_DELETE_DATASET		_U("smsp_DeleteDataset")	//删除数据集的存储过程
#define		SP_SET_BOUNDS			_U("smsp_SetBounds")		//设置数据集范围存储过程
#define		SP_COPY_DATASET			_U("smsp_CopyDataset")		//本地复制数据集的存储过程
#define		SP_CREATE_DATABASE		_U("smsp_CreateDatabase")	//创建新的数据源的存储过程

//SmRegister表中的字段=======================================================================
//			宏名				字段名					类型			说明	
//...........................................................................................
#define		RF_ID				_U("SmDatasetID")		//(dbLong)		//Dataset ID
#define		RF_DATASET_NAME		_U("SmDatasetName")		//(dbText)		//Dataset Name
#define		RF_TABLE_NAME		_U("SmTableName")		//(dbText)		//Geomey and Properties Table Name
#define		RF_INDEX_TABLE_NAME	_U("SmIndexTableName")	//(dbText)		//Index Table Name
#define		RF_SUB_TABLE_NAME	_U("SmSubTableName")	//(dbText)		//Sub Table name
#define		RF_IS_SUB			_U("SmIsSub")			//(dbChar)		//Is/Not sub table
#define		RF_DATASET_TYPE		_U("SmDatasetType")		//(dbInteger)	//Dataset's type
#define		RF_RECORD_COUNT		_U("SmRecordCount")		//(dbInteger)	//Object count in dataset.
#define		RF_INDEX_LEVEL		_U("SmIndexLevel")		//(dbInteger)	//Index level of the dataset.
#define		RF_LEFT				_U("SmLeft")			//(dbLong)		//Dataset Bounds' Left
#define		RF_RIGHT			_U("SmRight")			//(dbLong)		//Dataset Bounds' Right
#define		RF_TOP				_U("SmTop")				//(dbLong)		//Dataset Bounds' Top
#define		RF_BOTTOM			_U("SmBottom")			//(dbLong)		//Dataset Bounds' Bottom
#define		RF_MAXZ				_U("SmMaxZ")			//(dbDouble)	//Max Z Value of Dataset
#define		RF_MINZ				_U("SmMinZ")			//(dbDouble)	//Min Z Value fo Dataset
#define		RF_GRID_SIZE		_U("SMGRIDSIZE")		//(dbDouble)	//Grid Size fo Dataset, Used for Index.
#define		RF_USER_ID			_U("SmUserID")			//(dbInteger)	//Long transaction user id.
#define		RF_DT_VERSION		_U("SmDtVersion")		//(dbInteger)	//Data updated version.
#define		RF_OPTION			_U("SmOption")			//(dbInteger)	//Option of the dataset.
#define		RF_ENC_TYPE			_U("SmEncType")			//(dbInteger)	//Spatial data encoded type.
#define		RF_DESCRIPTION		_U("SmDescription")		//(dbText)		//Description of the dataset.
#define		RF_THUMB			_U("SmThumb")			//(dbLongBinary)//Thumb of the dataset.
#define		RF_TOLERANCE_FUZZY	_U("SmToleranceFuzzy")	//(dbDouble)	//Fuzzy tolerance of the dataset.
#define		RF_TOLERANCE_DANGLE	_U("SmToleranceDangle")	//(dbDouble)	//Dangle tolerance of the dataset.
#define		RF_TOLERANCE_NODESNAP _U("SmToleranceNodeSnap")	//(dbDouble)//NodeSnap tolerance of the dataset.
#define		RF_TOLERANCE_SMALL_POLYGON	_U("SmToleranceSmallPolygon")	//(dbDouble)	//Small polygon tolerance of the dataset
#define		RF_TOLERANCE_GRAIN	_U("SmToleranceGrain")	//(dbDouble)	//Grain tolerance of the dataset.
#define		RF_LASTUPDATE		_U("SmLastUpdate")		//(dbDate)		//The lastupdate time of the dataset.
#define		RF_MAX_GEOMETRY_SIZE	_U("SmMaxGeometrySize")	//(dbDouble)//The max geometry size of the dataset.
#define		RF_ONCE_FETCH_COUNT	_U("SmOnceFetchCount")	//(dbInteger)	//Once fetch count from server.
#define		RF_OPTIMIZE_COUNT	_U("SmOptimizeCount")	//(dbInteger)	//Optimize parameter of the dataset.
#define		RF_OPTIMIZE_RATIO	_U("SmOptimizeRatio")	//(dbFloat)		//Optimize parameter of the dataset.
//...........................................................................................

//SmImgRegister表中的字段=======================================================================
//			宏名				字段名					类型			说明	
//...........................................................................................
//#define		RF_ID					"SmDatasetID"		//(dbLong)		//Dataset ID
//#define		RF_DATASET_NAME			"SmDatasetName"		//(dbText)		//Dataset Name
//#define		RF_TABLE_NAME			"SmTableName"		//(dbText)		//Geomey and Properties Table Name
//#define		RF_DATASET_TYPE			"SmDatasetType"		//(dbInteger)	//Dataset's type
//#define		RF_OPTION				"SmOption"			//(dbInteger)	//Option of the dataset.
#define		RF_PIXEL_FORMAT				_U("SmPixelFormat")		//(dbInteger)	//Pixel format of the raster.
#define		RF_WIDTH					_U("SmWidth")			//(dbInteger)	//Width(pixels) of the raster.
#define		RF_HEIGHT					_U("SmHeight")			//(dbInteger)	//Height(pixels) of the raster.
#define		RF_E_BLOCK_SIZE				_U("SmeBlockSize")		//(dbInteger)	//e block size of the raster.
#define		RF_MAX_BLOCK_SIZE			_U("SmMaxBlockSize")	//(dbInteger)	//Max block size of the raster.
//#define		RF_MAXZ					"SmMaxZ"			//(dbDouble)	//Max Z Value of Dataset
//#define		RF_MINZ					"SmMinZ"			//(dbDouble)	//Min Z Value of Dataset
#define		RF_PYRAMID					_U("SmPyramid")			//(dbText)		//Parymid table name of the raster.
#define		RF_PYRAMID_LEVEL			_U("SmPyramidLevel")	//(dbInteger)	//Parymid level of the dataset.
#define		RF_BLOCK_SIZE				_U("SmBlockSizes")		//(dbInteger)	//Block size of the raster.
#define		RF_PALETTE					_U("SmPalette")			//(dbLongBinary)//Palette of the raster.
#define		RF_GEO_LEFT					_U("SmGeoLeft")			//(dbDouble)	//Dataset Bounds' Left
#define		RF_GEO_RIGHT				_U("SmGeoRight")		//(dbDouble)	//Dataset Bounds' Right
#define		RF_GEO_TOP					_U("SmGeoTop")			//(dbDouble)	//Dataset Bounds' Top
#define		RF_GEO_BOTTOM				_U("SmGeoBottom")		//(dbDouble)	//Dataset Bounds' Bottom
#define		RF_CLIP_REGION				_U("SmClipRegion")		//(dbLongBinary)//Clip region of raster.
#define		RF_TOLERANCE_SMALLPOLYGON	_U("SmToleranceSmallPolygon") 
//...........................................................................................


//SmDataSourceInfo表中的字段=======================================================================
//			宏名				字段名					类型			说明	
//...........................................................................................
#define		DF_VERSION			_U("SmVersion")			//dbLong		数据源版本号
#define		DF_FLAG				_U("SmFlag")			//dbLong		数据源标志
#define		DF_COORDSYS			_U("SmCoordSys")		//dbLong		坐标系
#define		DF_COORDUNIT		_U("SmCoordUnit")		//dbLong		坐标单位
#define		DF_DISTANCEUNIT		_U("SmDistanceUnit")	//dbLong		长度单位
#define		DF_PROJECTINFO		_U("SmProjectInfo")		//dbLongBinary	//投影系参数
#define		DF_DSDESCRIPTION	_U("SmDsDescription") 
#define		DF_MINORVERSION		_U("SmMinorVersion") 
#define		DF_VERSIONDATE		_U("SmVersionDate")		
//...........................................................................................

//SmFieldInfo表中的字段=======================================================================
//			宏名				字段名					类型			说明	
//...........................................................................................
#define		SMF_FIELD_ID		_U("SmID")				//dbInteger		字段ID
#define		SMF_TABLE_NAME		_U("SmTableName")		//dbText		数据表名
#define		SMF_DATASET_ID		_U("SmDatasetID")		//dbLong		数据集的ID
#define		SMF_FIELD_NAME		_U("SmFieldName")		//dbText		字段名
#define		SMF_FIELD_CAPTION	_U("SmFieldCaption")	//dbText		字段别名
#define		SMF_FIELD_TYPE		_U("SmFieldType")		//dbLong		字段的类型
#define		SMF_FIELD_FORMAT	_U("SmFieldFormat")		//dbText		字段显示格式
#define		SMF_FIELD_SIGN		_U("SmFieldSign")		//dbLong		字段标识，如NodeID,FNode,TNode,EdgeID,RouteID等
#define		SMF_FIELD_SIZE		_U("SmFieldSize")		//dbLong		字段长度
#define		SMF_FIELD_DOMAIN	_U("SmFieldDomain")		//dbText		字段值域
#define		SMF_FIELD_UPDATABLE	_U("SmFieldUpdatable")	//dbBoolean		字段值是否可修改
//...........................................................................................

//时序数据库需要使用的字段=======================================================================
//			宏名				字段名					类型			说明	
//...........................................................................................
#define		SEQ_START			_U("SmSequenceStart")	//dbDate		开始时间点
#define		SEQ_END				_U("SmSequenceEnd")		//dbDate		结束时间点
#define		SEQ_STATE			_U("SmSequenceState")	//dbBoolean		时序状态
#define		SEQ_ORG_ID			_U("SmSequenceOrgID")	//dbLong		时序编辑的最原始的SMID
//...........................................................................................

//Engine 直接使用 OGDC对象
//##ModelId=482030510177
typedef OgdcLinkItem                    UGLinkItem;
//##ModelId=482030510179
typedef OgdcJoinItem					UGJoinItem;
//##ModelId=482030510186
typedef OgdcDsConnection				UGDsConnection;

//Engine 扩展 OGDC 的枚举类型
#define FieldTypeCurrency		5
#define FieldTypeDgnLink		129


//##ModelId=482030510198
enum DatasetState
{
	//##ModelId=4820305101A6
	dsCheckedOut	= 0x00000001,
	//##ModelId=4820305101A7
	dsLocked		= 0x00000002		
};

//##ModelId=4820305101B5
enum LongTransState
{
	//##ModelId=4820305101B7
	ltsAdded		= 0x00000001,
	//##ModelId=4820305101B8
	ltsModified		= 0x00000002,
	//##ModelId=4820305101B9
	ltsDeleted		= 0x00000004
};

//##ModelId=4820305101C5
enum SpatialQueryOption
{
	//##ModelId=4820305101C7
	SQInner			= 0x00000001,
	//##ModelId=4820305101D4
	SQMaybe			= 0x00000002,
	//##ModelId=4820305101D5
	SQOuter			= 0x00000004
};

//##ModelId=4820305101E4
struct UG_INDEX_ITEM
{
	//##ModelId=4820305101E6
	UGuint left;
	//##ModelId=4820305101E7
	UGuint top;
	//##ModelId=4820305101E8
	UGuint right;
	//##ModelId=4820305101E9
	UGuint bottom;
	//##ModelId=4820305101F4
	UGuint nID;
	//##ModelId=4820305101F5
	UGuint nPos;

	UGint GetSizeofLenth()
	{
		UGint nLenght=0;
		nLenght = 6*sizeof(left);
		return nLenght;
	}
};

//##ModelId=482030510203
struct UG_CAD_INDEX_ITEM
{
	//##ModelId=482030510205
	UGuint left;
	//##ModelId=482030510206
	UGuint top;
	//##ModelId=482030510207
	UGuint right;
	//##ModelId=482030510213
	UGuint bottom;
	//##ModelId=482030510214
	UGuint nID;
	//##ModelId=482030510215
	UGuint nPos;
	//##ModelId=482030510216
	UGuint nType;

	UGint GetSizeofLenth()
	{
		UGint nLenght=0;
		nLenght = 7*sizeof(left);
		return nLenght;
	}
};

//##ModelId=482030510222
struct UG_SUPER_INDEX_ITEM
{
	//##ModelId=482030510232
	UGuint left;
	//##ModelId=482030510233
	UGuint top;
	//##ModelId=482030510234
	UGuint right;
	//##ModelId=482030510235
	UGuint bottom;
	//##ModelId=482030510236
	UGuint nID;
	//##ModelId=482030510237
	UGuint nPos;
	//##ModelId=482030510242
	UGuint nType;
	//##ModelId=482030510243
	UGuint dwX;
	//##ModelId=482030510244
	UGuint dwY;
	//##ModelId=482030510245
	UGdouble dZ;
};

//##ModelId=482030510251
struct UG_DATASET_TIER_NAME
{
	//##ModelId=482030510253
	UGString strDataset;
	//##ModelId=482030510254
	int nTileID;
	//##ModelId=482030510255
	UG_DATASET_TIER_NAME()
	{
		strDataset = _U("");
		nTileID    = -1;
	}
};


#define UUIDLENGTH			36
#define ROOTVERSIONNAME		_U("RootVersion")	//根版本默认名称

//! \brief 定义提交枚举
enum UGPostOption
{
	POConflictDest			= 1, //遇到冲突以目标版本为准
	POConflictCur			= 2, //遇到冲突以当前版本为准
	POConflictCommon		= 3, //遇到冲突以被更改之前的目标版本为准
	POConflictUnion			= 4, //遇到冲突，Union空间对象
};

typedef struct UGVersionInfo
{
	UGint nVersionID;				//版本号
	UGString strVersionName;		//版本名称
	UGString strCreator;			//版本创建者
	UGString strDescription;		//版本描述信息
	UGint nParentVersionID;			//父版本号
	UGTime CreationTime;			//版本创建时间
	UGVersionInfo()
	{
		nVersionID = 0;
		strVersionName = _U("");
		strCreator = _U("");
		strDescription = _U("");
		nParentVersionID = 0;
		CreationTime = UGTime::GetCurTime();
	}
}VERSIONINFO;

//协调后的信息
typedef struct UGReconcileInfo
{
	UGString strDestVersionName;
	UGint nCurSeriesID, nCurLastActionID;	//协调前当前版本的SeriesID和LastActionID
	UGint nDestSeriesID, nDestLastActionID;	//协调前目标版本的SeriesID和LastActionID
	UGint nMaxCommonActionID;				//公共最大ActionID
	UGint nSeriesID, nLastActionID;			//协调后的SeriesID和LastActionID
	UGArray<UGint> aryConflictIDs;			//矢量数据:冲突对象IDs,栅格数据:冲突块的行列号每2个数据表示一个行列号,奇数表示行号,偶数表示列号
	UGReconcileInfo()
	{
		strDestVersionName = _U("");
		nCurSeriesID = 0;
		nCurLastActionID = 0;
		nDestSeriesID = 0;
		nDestLastActionID = 0;
		nMaxCommonActionID = 0;
		nSeriesID = 0;
		nLastActionID = 0;
		aryConflictIDs.SetSize(0);
	}
	~UGReconcileInfo()
	{
		aryConflictIDs.RemoveAll();

	}
}RECONCILEINFO;

enum UGDuplicateType
{
	CheckOut	=	0,		//离线复本
	OneWay		=	1,		//单向更新复本
	TwoWay		=	2		//双向同步复本
};

typedef struct UGDuplicateInfo
{
	UGString	strID;				//复本ID
	UGString	strName;			//复本名称
	UGString	strDes;				//复本描述
	UGString	strCreator;			//复本创建者
	UGString	strIDFieldName;		//对象唯一标识字段
	UGint		nDatasetID;			//复本数据集ID
	UGint		nRole;				//0：主复本，1：子复本
	UGint		nType;				//复本类型：0：离线复本，1：单向复本，2：双向复本
	UGint		nExchangeState;		//0：Data Sender，1：Data Receiver
	UGint		nUpdateSequence;	//来自对应复本的最后更新序列
	UGint		nSynchroSequence;	//最后为对应复本同步的序列

	UGDuplicateInfo()
	{
		strID = _U("");
		strName = _U("");
		strDes = _U("");
		strCreator = _U("");
		nRole = 0;
		nType = 0;
		nExchangeState = 0;
		nUpdateSequence = 0;
		nSynchroSequence = 0;
	}
}DUPLICATEINFO;

typedef struct UGDiffMsgInfo
{
	UGString	strID;
	UGString	strName;
	UGint		nObjCount;
	UGint		nMaxSequence;
	UGint		nRole;
	UGDiffMsgInfo()
	{
		strID = _U("");
		strName = _U("");
		nObjCount = 0;
		nMaxSequence = 0;
		nRole = 0;
	}
}DIFFMSGINFO;

#endif // end declare ugc sdk
}
#endif

