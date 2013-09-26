#ifndef UGDATASOURCE_H
#define UGDATASOURCE_H

/*!
   **************************************************************************************
    \file     UGDataSource.h
   **************************************************************************************
    \author   李绍俊
    \brief    数据源对象的基类，所有引擎中的数据源都需要从本类中派生，并实现本类所定 
              义的纯虚函数。                                                         
    \attention   
   ----------------------------------------------------------------------------------<br>
    Copyright (c) 1996-2004 SuperMap GIS Technologies,Inc.                           <br>
    All Rights Reserved.                                                             <br>
   ----------------------------------------------------------------------------------<br> 
   
   **************************************************************************************
    \version 2005-04-26  李绍俊    初始化版本.                                       <br>
   **************************************************************************************
*/

#include "Engine/ugeng.h"
#include "Engine/UGDataset.h"
#include "Engine/UGDatasetVectorInfo.h"
#include "Engine/UGDatasetRasterInfo.h"
#include "Engine/UGDatasetVector.h"
#include "Engine/UGDatasetRaster.h"
#include "Engine/UGDatasetVectorCollection.h"
#include "Engine/UGDatasetRasterCollection.h"
#if !defined SYMBIAN60 && !defined  OS_ANDROID && !defined (IOS)
#include "UGDatasetTopo.h"
#include "OGDC/OgdcDataSource.h"
// #include "UGDatasetMultiBandRaster.h"
#include "Engine/UGDatasetRelClass.h"
#include "Engine/UGTextureLib.h"
#include "Engine/UGRelationMaster.h"
#endif
#include "Engine/UGEngDefs.h"
#include "Toolkit/UGToolkit.h"





namespace UGC {

//! \brief 删除数据集事件回调函数
typedef void (UGSTDCALL *DeleteDTProc)(UGDataset *pDataset,void *data);

//! \brief 刷新数据源时，删除数据集指针 事件回调函数
typedef void (UGSTDCALL *RefreshDSProc)(UGDataset *pDataset, void *data);

class UGDatasetRelationMananger;
class UGVersionManager;
class UGDuplicateManager;
class UGDomainManagerBase;

//! \brief 存储工作空间相关信息
//##ModelId=4820305103DB
struct UGWorkspaceInfo
{
	//##ModelId=4820305103DD
	UGint nVersion;
	//##ModelId=482030520000
	UGString strWorkspaceName;
	//##ModelId=482030520001
	UGString strUser;
};


class UGMetadata;
class UGEngineProc;
class UGDatasetRelClassManager;
class UGDatasetGroup;

//! \brief 数据源类
//##ModelId=48203052005D
#ifdef SYMBIAN60
class ENGINE_APIC UGDataSource
#else
class ENGINE_API UGDataSource
#endif
{
	friend class UGDataSourceManager;
#if !defined SYMBIAN60 && !defined  OS_ANDROID && !defined (IOS)
	friend class UGDataSourceOgdc;
#endif
	friend class UGDatasetVector;
	friend class UGEngineToolkit;
	friend class UGDomainManagerBase;
public:
	//! \brief 构造函数
	//##ModelId=48203052005E
	ENGINE_APIF UGDataSource();

	//! \brief 析构函数
	//##ModelId=48203052007D
	virtual ENGINE_APIF ~UGDataSource();

public:
#if !defined OS_ANDROID && !defined IOS
	//!	\brief 获取关系管理器
	ENGINE_APIF UGRelationManager* GetRelationManager(UGRelationManager::ManagerType eType);

protected:
	//!	\brief	产生DDRMaster对象
	virtual ENGINE_APIF UGDDRMasterBase* GenerateDDRMaster(UGRelationManager::ManagerType eType);
#endif
public:
	//! \brief 获取版本管理器指针
	ENGINE_APIF UGVersionManager * GetVersionManager();

	ENGINE_APIF UGDatasetRelClassManager* GetDatasetRelClassManager();

	//========================================================
	//! \brief 		获取当前数据源所在的Schema
	//! \return 	UGString
	//##ModelId=48203052008C
	virtual ENGINE_APIF UGString GetSchema() const;

	//! \brief 获取数据源连接指针，给统一CI使用
	virtual ENGINE_APIF void * GetConnectionPtr();

	//! \brief 获取数据源连接信息,返回为引用类型,
	//! \return UGDsConncetion& 
	//! \remark 返回值为引用，所以可以更改其连接信息
	//##ModelId=48203052009C
	ENGINE_APIF UGDsConnection& GetConnectionInfo();

	//! \brief 执行SQL语句，主要用于在数据库级执行的数据操作
	//##ModelId=48203052009D
	virtual ENGINE_APIF UGbool Execute(const UGString& strSQL);
	
	//! \brief 创建数据源,需要预先设置好连接信息
	//! \return UGbool
	//! \remark 连接信息通过GetConnectionInfo()获得，一个数据连接只能创建一个数据源，创建数据源时不用手动调用Connect()方法，
	//##ModelId=4820305200AB
	virtual ENGINE_APIF UGbool Create();

	//! \brief 打开数据源,需要预先设置好连接信息
	//! \return UGbool
	//##ModelId=4820305200AD
	virtual ENGINE_APIF UGbool Open();

	//===================================================
	//! \brief 打开数据源,需要预先设置好连接信息
	//! \param nDtType[in] 数据集类型
	//! \return   
	//! \remarks 本接口目前只用于数据集集合只读打开，其他勿用！！
	//! \attention
	virtual ENGINE_APIF UGbool Open(UGint nDtType, UGbool bIsReadAsOneBand = FALSE){return FALSE;}

	//! \brief 数据源是否和数据连接
	//! \return 返回数据源与数据库的连接状态，TRUE:已连接，FALSE:未连接
	//##ModelId=4820305200AF
	virtual ENGINE_APIF UGbool IsConnected();

	//! \brief 仅仅连接数据库,不刷新数据集等
	//! \return 返回连接结果，成功返回TRUE，失败返回FALSE
	//##ModelId=4820305200B1
	virtual ENGINE_APIF UGbool Connect();

	// !\brief 关闭数据源
	// !\remark 释放所有记录集，并关闭所有数据集，再断开库据库连接
	//##ModelId=4820305200BB
	virtual ENGINE_APIF void Close();
	
	//! \brief 判断数据源是否已经打开
	//##ModelId=4820305200BD
	ENGINE_APIF UGbool IsOpen() const;

	//! \brief 获取最后更新时间
	//##ModelId=4820305200BF
	virtual ENGINE_APIF UGTime GetDateLastUpdated() const;

	//! \brief 获取创建时间
	//##ModelId=4820305200C1
	virtual ENGINE_APIF UGTime GetDateCreated() const;

	//! \brief 保存数据信息
	//##ModelId=4820305200CB
	virtual ENGINE_APIF UGbool SaveInfo();

	//! \brief 修改密码
	//! \param UGString& 密码值 
	//! \return UGbool 返回修改结果
	//##ModelId=4820305200CD
	virtual ENGINE_APIF UGbool ChangePassword(const UGString& strNewPassword);

	//! \brief 删除数据集(通过名称)
	//! \param strName 数据集名称
	//! \return UGbool 返回删除结果
	//##ModelId=4820305200D0
	virtual ENGINE_APIF UGbool DeleteDataset(const UGString& strName);

	//! \brief 通过DatasetVectorInfo创建数据集
	//! \param vInfo 数据集信息
	//! \return UGDatasetVector* 创建失败则返回NULL
	//##ModelId=4820305200DA
	virtual ENGINE_APIF UGDatasetVector* CreateDatasetVector(const UGDatasetVectorInfo& vInfo);

#if !defined SYMBIAN60 && !defined OS_ANDROID && !defined (IOS)
	//! \brief 通过UGRelClassInfoG创建数据集
	ENGINE_APIF UGDatasetRelClass* CreateDatasetRelClass(const UGRelClassInfo& rsInfo);
	ENGINE_APIF UGDatasetRelClass* CreateDatasetRelClass(const UGRelClassInfo& rsInfo, \
		const UGFieldInfos &fldInfos);

	//! \brief 通过DatasetVectorInfo创建数据集
	//! \param &strName 数据集名称
	//! \return UGDatasetTopo* 创建失败则返回NULL
	//! \remark 目前仅OraclePlus引擎和SQLPlus引擎支持TOPO
	//##ModelId=4820305200DD
	virtual ENGINE_APIF UGDatasetTopo* CreateDatasetTopo(const UGString &strName);
#endif
	//! \brief 通过DatasetRasterInfo创建数据集
	//! \param &rInfo 栅格数据集信息
	//! \param bIsMBRaster 是否多波段栅格，默认为否
	//! \remarks rInfo 必填字段包含 名字，宽度和高度。
	//! \attention 编码的调整参考
	//##ModelId=4820305200E0
	virtual ENGINE_APIF UGDatasetRaster* CreateDatasetRaster(const UGDatasetRasterInfo& rInfo,UGbool bIsMBRaster = FALSE);

	//! \brief 复制数据集,需要调用CreateDatasetFrom新建数据集strDestDatasetName
	//! \param *pSrcDataset  源数据集
	//! \param &strDestDatasetName 目标数据集名称
	//! \param nCodeType 默认为无编码
	//! \param bBuildIndexOrPyramid 默认创建索引或金字塔
	//! \return UGDataset*  复制失败返回NULL
	//! \remark DataSource必须打开而且可写,外挂属性表和外挂影响不允许复制
	//##ModelId=4820305200E3
	virtual ENGINE_APIF UGDataset* CopyDataset(UGDataset* pSrcDataset, 
		const UGString& strDestDatasetName,
		UGDataCodec::CodecType nCodeType = UGDataCodec::encNONE,
		UGbool bBuildIndexOrPyramid = FALSE,
		UGProgress *pProgresss = NULL
		);//默认不创建索引或者金字塔，与SFC一致 modified by ZENGWH 2009.12.10

	//! \brief 得到元数据库
	//! \return 非空表示支持元数据操作
	//! \remarks 
	//! \attention 
	//##ModelId=4820305200FA
	virtual ENGINE_APIF UGMetadata * GetMetaData();	

	//##ModelId=4820305200FC
	virtual ENGINE_APIF UGEngineProc * GetEngineProc();

	//! \brief 设置数据源信息为默认
	virtual ENGINE_APIF UGbool SetDefaultOption();

	//! \brief 设置删除数据集的回调函数
	ENGINE_APIF void SetDeleteDTCallBack(DeleteDTProc pDeleteDTProc, void *data);

	//! \brief 设置回调函数:刷新数据源时，删除数据集指针 事件回调函数
	ENGINE_APIF void SetRefreshDSProcCallBack(RefreshDSProc pDeleteDTProc, void *data);

	//! \brief 不关闭数据源的前提下刷新当前数据源
	//! \remarks在项目中，会有两个应用服务去修改同一数据库中的数据，A服务新增加一个数据，
	//          B服务希望在不影响当前以打开的地图情况下，刷新出新的数据集对象，以及被删除的对象
	//! \param  aryAddNames[out]需要增加的数据集名数组
	//! \param  aryDelNames[out]需要删除的数据集名数组
	virtual ENGINE_APIF UGbool RefreshDataSource(UGArray<UGString> &aryAddNames,UGArray<UGString> &aryDelNames);

	//! \brief 把内存中的数据写入数据库，供组件层使用
	//! \param  strDatasetName[in]需要刷新的数据集名称，可以为空；strDatasetName为空时刷新所有数据集
	virtual ENGINE_APIF UGbool Flush(UGString strDatasetName=_U(""));

public:
	//! \brief 集合相关
	//! \brief 创建集合
	//! \param &strName 集合名称[in]
	//! \param eType 集合类型 ,仅支持 VectorCollection和RasterCollection[in]
	virtual UGDataset* CreateCollection(const UGDatasetRasterInfo& info);

	//! \brief 集合相关
	//! \brief 创建集合
	//! \param &strName 集合名称[in]
	//! \param eType 集合类型 ,仅支持 VectorCollection和RasterCollection[in]
	virtual UGDataset* CreateCollection(const UGString &strName, UGDataset::DatasetType eType);

	//! \brief 创建集合
	//! \param &strName 集合名称[in]
	//! \param eType 集合类型 ,仅支持 VectorCollection和RasterCollection[in]
	//! \param *pInitDataset 集合的初始化数据集,第一个加入集合的数据集,要求类型匹配
	//! \return 
	virtual UGDataset* CreateCollection(const UGString &strName, UGDataset::DatasetType eType, UGDataset *pInitDataset);

	//! \brief 删除集合
	//! \param &strName 集合名称[in]
	//! \return 
	virtual UGbool DeleteCollection(const UGString &strName);

public:
	//! \brief 工作空间关联相关接口
	//##ModelId=4820305200FE
	virtual ENGINE_APIF UGbool SaveWorkspace(UGDsConnection conn, UGString strWksName, UGint nVersion, UGbyte *pbyte,UGint nbyteSize);
	//##ModelId=48203052010B
	virtual ENGINE_APIF UGbool LoadWorkspace(UGDsConnection conn, UGString strWksName, UGint nVersion, UGbyte *&pbyte,UGint &nbyteSize);
	//##ModelId=482030520112
	virtual ENGINE_APIF UGbool GetWorkspaceInfo(UGDsConnection conn, UGArray<UGWorkspaceInfo> &wksInfos);
	//##ModelId=482030520119
	virtual ENGINE_APIF UGbool DeleteWorkspaceInfo(UGDsConnection conn, UGString strWksName);

	//! \brief 获取最后一次修改工作空间信息的时间
	virtual ENGINE_APIF UGbool GetWorkspaceLastUpdateTime(UGDsConnection &conn,UGString &strWorkspaceName,UGTime &updateTime);

public:

	//! \brief 删除当前的数据源(会自动删除所有数据集，最后删除所有系统表和系统对象)
	//! \remarks 调用此方法后，可以再次创建同参数的数据源
	//! \attention 仅数据库类型的数据源需要实现此方法，文件型数据源不处理，调用此方法会删除数据源中所有的表，包括用户自定义的表，调用时需要谨慎
	virtual ENGINE_APIF UGbool DropDataSource();


	//! \brief 获取密码(通过获取连接信息也可以得到密码)
	//! \return UGString 
	//##ModelId=48203052011D
	ENGINE_APIF UGString GetPassword() const;

	//! \brief 获取数据源名称
	//! \return UGString 
	//##ModelId=48203052011F
	ENGINE_APIF UGString GetName() const ;

	//! \brief 获取引擎类型
	//##ModelId=482030520128
	ENGINE_APIF UGEngineType GetEngineType() const;

	//! \brief 获取引擎名称
	//##ModelId=48203052012A
	virtual ENGINE_APIF UGString GetEngineName() const ;

	//! \brief 获取引擎分类
	//##ModelId=482030520128
	virtual ENGINE_APIF  UGint GetEngineClass() const;

	//! \brief 获取文件型引擎的后缀名
	//##ModelId=48203052012A
	virtual ENGINE_APIF UGString GetEnginePostfix() const ;

	//! \brief 生成一个数据源中目前没有的数据集名字
	//##ModelId=48203052012C
	//! \param  strDatasetName[in]    传入的数据集名称
	//! \param  bProcessAgainName[in] 是否需要处理数据集重名
	virtual ENGINE_APIF UGString GetUnoccupiedDatasetName(const UGString& strDatasetName, UGbool bProcessAgainName = TRUE);

	//! \brief 判断数据集名称是否可用
	//##ModelId=482030520138
	virtual ENGINE_APIF UGbool IsAvailableDatasetName(const UGString& strDatasetName,UGToolkit::InvalidNameState& nState);

	//========================================================
	//! \brief 		判断传入的字段名或数据集名是否合法（注意是数据集名，而不是表名，该函数名称需要修改）
	//! \brief 		非法状态见 枚举 UGToolkit::InvalidNameState
	//! \return 	UGbool
	//! \param 		strFieldOrTableName
	//! \param 		nInvalidStata
	//##ModelId=48203052017A
	ENGINE_APIF UGbool IsValidFieldOrTableName(const UGString& strFieldOrTableName, UGToolkit::InvalidNameState& nInvalidStata);

	//! \brief 检测并返回有效字段名
	virtual ENGINE_APIF UGString CheckFieldName(UGString strFieldName);

	//! \brief 	获取数据的主版本
	//##ModelId=48203052013C
	virtual ENGINE_APIF UGint GetVersion();

	//! \brief 数据源是否被修改的标志
	//##ModelId=482030520148
	ENGINE_APIF UGbool IsModified();

	//! \brief 设置数据源的修改标志
	//! \remark 仅在内存中处理该标志，并不会主动调用SaveInfo()
	//##ModelId=482030520149
	ENGINE_APIF void SetModifiedFlag(UGbool bModified = TRUE);

	//========================================================
	//! \brief 		判断数据源是否为只读
	//! \return 	UGbool
	//##ModelId=48203052014B
	ENGINE_APIF UGbool IsReadOnly() const;
	
	//========================================================
	//! \brief 		判断数据源是否为独占方式打开
	//! \return 	UGbool
	//##ModelId=48203052014D
	ENGINE_APIF UGbool IsExclusive() const ;
	
	//========================================================
	//! \brief 		判断数据源是否使用密码打开
	//! \return 	UGbool
	//##ModelId=482030520157
	ENGINE_APIF UGbool IsEncrypt() const ;

	//========================================================
	//! \brief 		判断数据源是否是自动连接
	//! \return 	UGbool
	//##ModelId=482030520159
	ENGINE_APIF UGbool IsAutoConnect() const;

	//========================================================
	//! \brief 		设置数据源的自动连接选项
	//! \return 	void
	//! \param 		bAutoConnect
	//##ModelId=48203052015B
	ENGINE_APIF void SetAutoConnect(UGbool bAutoConnect);	
	
	//========================================================
	//! \brief 		获取数据源的别名
	//! \return 	UGString
	//##ModelId=48203052015D
	ENGINE_APIF UGString GetAlias() const;

	//========================================================
	//! \brief 		设置数据源的别名
	//! \return 	void
	//! \param 		strAlias
	//##ModelId=48203052015F
	ENGINE_APIF void SetAlias(const UGString& strAlias);

	//! \brief 返回数据集个数
	//! \remark 目前没有考虑并发的情况，需要刷新数据源才能获取在其他数据源创建的数据集
	//##ModelId=48203052016F
	ENGINE_APIF UGint GetDatasetCount() const;

	//! \brief 通过序号返回数据集指针
	//! \param nIdex 序号
	//! \return UGDataset* 
	//##ModelId=482030520171
	ENGINE_APIF UGDataset* GetDataset(UGint nIndex);

	//! \brief 返回所有的数据集指针 2008.03.30 CHENZhao
	ENGINE_APIF UGDatasets* GetDatasets();

	//! \brief 返回指定名称的数据集指针
	//! \param strDatasetName 数据集名称
	//! \remark 数据集名称不区分大小写，可以返回矢量数据集的子数据集指针
	//##ModelId=482030520177
	ENGINE_APIF UGDataset* GetDataset(const UGString& strDatasetName);

	//! \brief 返回指定表名的数据集指针
	//! \param strTableName 数据集名称
	//! \remark 数据集名称不区分大小写，可以返回矢量数据集的子数据集指针
	//##Added by zhojt 20110720
	ENGINE_APIF UGDataset* GetDatasetByTableName(const UGString& strTableName);
	
	//========================================================
	//! \brief 		设置数据源的投影信息
	//! \param 		UGPrjCoordSys 投影信息
	//##ModelId=482030520186
	ENGINE_APIF UGbool SetPrjCoordSys(const UGPrjCoordSys &PrjCoordSys);
	
	//========================================================
	//! \brief 		获取数据源的投影信息
	//! \return 	UGPrjCoordSys 读取出来的投影信息
	//##ModelId=482030520188
	const ENGINE_APIF UGPrjCoordSys& GetPrjCoordSys();

	//! \brief 投影转换。
	//! \param *pRefTranslator [in]转换器。		
	//! \param FALSE [in] 决定是否数据源下的数据集要进行投影转换。
	//! \return 。
	//! \remarks 。	
	ENGINE_APIF UGbool PJConvert( UGRefTranslator *pRefTranslator,UGbool bFlag = FALSE);		
	//! \brief 地理坐标到投影坐标。
	//! \param *pPrjCoordSys [in] 投影坐标 
	//! \param FALSE [in]决定是否数据源下的数据集要进行转换。
 	//! \attention 。
	ENGINE_APIF UGbool PJForward( UGPrjCoordSys *pPrjCoordSys,UGbool bFlag = FALSE );		
	//! \brief 投影坐标到地理坐标。
	//! \param FALSE [in]决定是否数据源下的数据集要进行转换。
	//! \return 。
	//! \remarks 。
	//! \attention 。
	ENGINE_APIF UGbool PJInverse(UGbool bFlag = FALSE);										//

	//! \brief 把记录集转换为实体数据集
	//! \param *pRecord 源记录集
	//! \param strNewDatasetName 目标数据集名称
	//! \return UGDatasetVector* 失败返回NULL
	//! \remark 必须能创建名称为strNewDatasetName的矢量数据集
	//##ModelId=482030520199
	ENGINE_APIF UGDatasetVector * RecordsetToDataset(UGRecordset *pRecord,UGString strNewDatasetName);

	// !\brief 设置数据源描述信息
	// !\param UGString 描述信息
	// !\return UGbool
	// !\remark 描述信息长度不能超255
	//##ModelId=4820305201A5
	ENGINE_APIF UGbool SetDescription(UGString strDesc);

	//! \brief 获取数据源描述信息
	//! \return UGString
	//##ModelId=4820305201A7
	ENGINE_APIF UGString GetDescription();

	//##ModelId=4820305201A8
	ENGINE_APIF UGint GetDataversionID();

	//! \brief 通过Template创建数据集
	//! \param &strNewName 新数据集名称
	//! \param *pReferenceDataset 模版数据集
	//! \param nType 编辑类型
	//! \param bCopyBandInfo 是否拷贝波段信息
	//! \return UGDataset* 
	//! \remark 相关细节参考创建数据集的方法
	//##ModelId=4820305201A9
	virtual ENGINE_APIF UGDataset* CreateDatasetFrom(const UGString &strNewName,
		UGDataset * pReferenceDataset,UGDataCodec::CodecType nType,UGbool bCopyBandInfo = FALSE);

	//! \brief 创建用户自定义的字段，在CreateDatasetFrom中被调用。仅支持矢量数据集
	//! \param pDesDataset[out] 目标数据集
	//! \param strNewName[in] 目标数据集的名称
	//! \param nType[in] 编码方式
	//! \param nCharset[in] 目标数据集编码方式
	ENGINE_APIF UGDatasetVector* CreateDatasetVectorFrom(const UGString &strNewName, UGDatasetVector* pReferenceDataset, 
		UGDataCodec::CodecType nType, UGString::Charset nCharset);

	//! \brief 开始事务
	//##ModelId=4820305201B5
	virtual ENGINE_APIF UGbool BeginTrans() ;

	//! \brief 提交事务
	//##ModelId=4820305201B7
	virtual ENGINE_APIF void Commit();

	//! \brief 撤消事务
	//##ModelId=4820305201B9
	virtual ENGINE_APIF void Rollback();

	//! \brief 判断事务是否开始 
	//##ModelId=4820305201BB
	ENGINE_APIF UGbool IsTransStarted() const;

	//========================================================
	//! \brief 		判断数据源是否支持短事务操作
	//! \return 	UGbool
	//##ModelId=4820305201BD
	ENGINE_APIF UGbool IsTransacted() const ;

	//! \brief 得到各类系统表中序列化字段中的最大值 added by yanmb 2007.06.07
	//##ModelId=4820305201BF
	virtual ENGINE_APIF UGint GetMaxTableID();

	//##ModelId=4820305201C1
	virtual ENGINE_APIF UGint GetFieldMaxValue(const UGString &strTableName, const UGString &strFieldName);

	//! \brief 是否有执行某些操作的能力
	//##ModelId=482030520161
	virtual ENGINE_APIF UGbool HasAbility(UGEngAbility nAbility) const {return FALSE;}

	//! \brief 是否支持特定的操作
	//##ModelId=482030520169
	virtual ENGINE_APIF UGbool IsSupport(UGEngAction nAction) const {return FALSE;}

	//! \brief 判断支持的数据集类型
	//! \return UGbool
	//##ModelId=48203052016C
	virtual ENGINE_APIF UGbool IsSupport(UGDataset::DatasetType nDtType) const;

	//##ModelId=483BB70A00FA
	virtual ENGINE_APIF UGString GetUUID() const;
	//##ModelId=483BB70A0109
	virtual ENGINE_APIF void SetUUID(const UGString& strUUID);

	//! \brief 创建数据库的序列,必须先打开数据源
	//! \param strSeqName 序列名称
	//! \param nSeqStart  序列的起始值 默认为0
	//! \param nSeqMax    序列的最大值 默认为-1 表示无上限
	//! \param nIncrementVal 序列的增长值，默认为1
	//! \return UGbool
	//! \remark          UDB不支持nIncrementVal参数,默认增长的步伐为1
	//##ModelId=4820305200AB
	virtual ENGINE_APIF UGbool CreateSequence(const UGString& strSeqName, UGlong nSeqStart = 0, UGlong nSeqMax = -1, UGint nIncrementVal = 1){return FALSE;}

	//! \brief 删除数据库的序列
	//! \param strSeqName 序列名称
	//! \return UGbool
	//! \remark 连接信息通过GetConnectionInfo()获得，一个数据连接只能创建一个数据源，创建数据源时不用手动调用Connect()方法，
	//##ModelId=4820305200AB
	virtual ENGINE_APIF UGbool DeleteSequence(const UGString& strSeqName){return FALSE;}

	//! \brief 获取数据库的下一个序列值
	//! \param strSeqName 序列名称
	//! \param nSeqValue  获取的下一个序列值
	//! \return UGbool    获取序列值是否成功
	virtual ENGINE_APIF UGbool GetSequenceNextVAL(const UGString& strSeqName, UGlong& nSeqValue){return 0;}

	//! \brief 序列是否存在
	//! \param strSeqName 序列名称
	//! \return UGbool    获取序列值是否成功
	virtual ENGINE_APIF UGbool IsSequenceExist(const UGString& strSeqName){return FALSE;}



	//! \brief 注册视图为数据集
	//! \param &strViewName 源视图名称
	//! \param &strDatasetName 目标数据集名称
	//! \return UGbool
	virtual ENGINE_APIF UGbool RegisterViewAsDataset(const UGString& strViewName, const UGString& strDatasetName);

	//! \brief 反注册视图数据集
	//! \param &strDatasetName 数据集名称
	//! \return UGbool
	virtual ENGINE_APIF UGbool UnregisterViewDataset(const UGString& strDatasetName);
    
	//! \brief 注册属性表为数据集
	//! \param &strTableName 源表名称
	//! \param &strDatasetName 目标数据集名称
	//! \param PKName 
	//! \return UGbool
	virtual ENGINE_APIF UGbool RegisterTableAsDataset(const UGString& strTableName, const UGString& strDatasetName, UGString PKName=_U(""));

	//! \brief 把用户通过supermap创建的属性表数据集反注册为属性表
	virtual ENGINE_APIF UGbool UnregisterTabularDataset(const UGString& strDatasetName);

public:
	//! \brief PENGJIANG 得到值域管理器
	virtual ENGINE_APIF UGDomainManagerBase* GetDomainManager();

#if !defined SYMBIAN60 && !defined  OS_ANDROID && !defined (IOS)

	//! \brief 创建多波段栅格数据集
	//! \param &strName 栅格名称 
	//! \param &arrRaster 普通栅格数据集数组
	//! \param dtType 支持的多波段栅格型包括 MBImage、MBGrid、MBDEM
	//! \return UGDatasetMultiBandRaster* 失败返回NULL
	//! \remarks arrRaster 必须在宽度，高度，数据集类型，影像分块边长，影像行数，影像列数严格要求一致。
	virtual ENGINE_APIF UGDatasetRaster* CreateDatasetMBRaster(const UGString& strName,
		const UGArray<UGDatasetRaster *>& arrRaster,UGDataset::DatasetType dtType = UGDataset::MBImage);
	
	//! \brief 创建复本管理器
	//! \attention 创建复本管理器后,外部调用 delete UGDuplicateManager
	virtual ENGINE_APIF UGDuplicateManager* CreateDuplicateManager();
#endif

	virtual ENGINE_APIF UGDatasetGroup* GetDatasetGroup();
	//! \brief 将内存数据源保存到磁盘文件上。
	//! \param  udbFile 保存文件的全路径名称[in]。
	//! \param  bEncapsulate 是否压缩为一个文件[in]。
	//! \return 保存是否成功。
	//! \remarks 此功能仅为显示组提供,其它情况需要使用请提需求，擅自使用不负责维护
	virtual ENGINE_APIF UGbool Dump(const UGString& udbFile, UGbool bEncapsulate = FALSE);

	//! \brief 提供文件型数据源的紧缩功能
	//! \remark 目前仅支持SDB数据源的紧缩功能，UDB还未开放
	virtual ENGINE_APIF UGbool Compact(UGbool bShowProgress=TRUE);

//! \brief 设置绑定的元数据ID
	UGbool SetMetadataID(const UGString& strMetadataID);

	//! \brief 获取绑定的元数据ID
	UGString GetMetadataID();

	//! \brief生成数据源的元数据
	UGbool GenerateMetadata();

	virtual ENGINE_APIF UGbool IsSupportUnicode();

#ifndef  OS_ANDROID
	// 添加和删除纹理
	ENGINE_APIF UGbool AddTexture(UGGeometry* pGeo);
	ENGINE_APIF UGbool DelTexture(UGGeometry* pGeo);
	ENGINE_APIF UGbool DelDatasetTexture(UGDataset* pDataset);

	// 从纹理库中取出纹理给模型
	// nLevel为纹理等级,0为最精细纹理,负数或者大于纹理最高级别时取最粗糙纹理
	ENGINE_APIF UGbool LoadTexture(UGGeometry* pGeo,UGbool bLoadCompress=TRUE);

	// 从纹理库中取出纹理
	// nLevel为纹理等级,0为最精细纹理,负数或者大于纹理最高级别时取最粗糙纹理
	ENGINE_APIF UGbool LoadTexture(UGArray<UGTextureInfo>& arrayTextureInfos, UGbool bLoadCompress = TRUE);

	//复制纹理,从源数据集纹理库中取出纹理复制到目标数据集纹理库
	ENGINE_APIF UGbool CopyTexture(UGDatasetVector* pSrcDataset,UGDatasetVector* pDesDataset);

#endif

	//复制值域库,从源数据集值域库中取出值域复制到目标数据集值域库
	virtual ENGINE_APIF UGbool CopyDoMainData(UGDatasetVector* pSrcDataset,UGDatasetVector* pDesDataset);

	//删除数据集所关联的值域
	virtual ENGINE_APIF UGbool DeleteDoMainData(UGDatasetVector* pDataset);

	//! \brief 通过ID获取数据集
	//! \attention 还没有考虑子数据集的问题
	ENGINE_APIF UGDataset * GetDatasetByID(UGint nDatasetID, UGbool bIsVector = TRUE);

private:
	//! \brief OGDC引擎复制
	ENGINE_APIF UGDataset* CopyDatasetOGDC(UGDataset *pSrcDataset,
		const UGString &strDestDatasetName, 
		UGDataCodec::CodecType nCodeType = UGDataCodec::encNONE,
		UGbool bBuildIndexOrPyramid = FALSE);


protected:	
	//! \brief 同引擎复制
	//##ModelId=4820305201C8
	virtual ENGINE_APIF UGDataset * CopyDatasetLocal(UGDataset *pSrcDataset,
		const UGString &strDestDatasetName, 
		UGDataCodec::CodecType nCodeType = UGDataCodec::encNONE,
		UGbool bBuildIndxOrPyramid = FALSE);

	//! \brief 检查数据集的数据表是否存在。创建数据集时使用。
	//! \attention 引擎内部使用，不开放
	virtual ENGINE_APIF UGbool CheckDatasetTableExist(const UGString& strTableName);

	//! \brief 获取数据库中没有被占用的表名称，创建数据集时使用
	//! \attention 引擎内部使用，不开放
	virtual ENGINE_APIF UGString GetUnoccupiedTableName(const UGString strTableName);

	//! \brief 判断指定ID的数据集是否已经存在于内存中
	//! \param 待判断的数据集的ID
	ENGINE_APIF UGbool IsDatasetExisted(UGint nDatasetID,UGbool bIsVector=TRUE);

	ENGINE_APIF UGDataset* CopyCollection(UGDataset *pSrcDataset,const UGString &strDestDatasetName, 
		UGDataCodec::CodecType nCodeType = UGDataCodec::encNONE,
		UGbool bBuildIndxOrPyramid = FALSE);

public:
	// 2012 CP 版本
	//! \brief 面数据集转换为线数据集
	//! \param *pSrcDataset[in] 源数据集指针
	//! \param &strDestName[in] 目标数据集名称
	//! \return 成功则返回数据集指针，否则返回NULL
	ENGINE_APIF UGDatasetVector* RegionToLine(UGDatasetVector *pSrcDataset, const UGString &strDestName);

	// 2012 CP 版本
	//! \brief 线数据集转换为点数据集
	//! \param *pSrcDataset[in] 源数据集指针
	//! \param &strDestName[in] 目标数据集名称
	//! \return 成功则返回数据集指针，否则返回NULL
	ENGINE_APIF UGDatasetVector* LineToPoint(UGDatasetVector *pSrcDataset, const UGString &strDestName);

	//! \brief 栅格数据集统计信息的保存与读取
	virtual ENGINE_APIF UGbool SaveStatisticsInfo(UGDatasetRaster* pDataset);
	virtual ENGINE_APIF UGbool LoadStatisticsInfo(UGDatasetRaster* pDataset);

	//! \brief 读取数据集blockManager配置参数信息
	virtual UGbool ReadBlockManagerParam(UGDatasetRaster* pDataset);

protected:
	//! \brief 连接信息
	//##ModelId=4820305201D4
	UGDsConnection m_Connection;
	//! \brief 判断是否打开
	//##ModelId=4820305201D5
	UGbool m_bOpened;	

	//##ModelId=4820305201D6
	UGArray<UGDataset*> m_Datasets;
	//std::vector<UGint> m_IArray;
	//! \brief 		数据源的投影信息
	//##ModelId=4820305201D7
	UGPrjCoordSys m_prjCoordSys;

	//! \brief 数据的主版本
	//##ModelId=4820305201E4
	UGint m_nVersion;
	//! \brief 数据的小版本
	//##ModelId=4820305201E5
	UGint m_nMinorVersion;
	//! \brief VersionDate
	//##ModelId=4820305201E6
	UGint m_nVersionDate;

	//! \brief 描述信息
	//##ModelId=4820305201E7
	UGString m_strDescription;
	//! \brief 是否更改
	//##ModelId=4820305201F4
	UGbool m_bModified;

	//! \brief 当前版本ID
	//##ModelId=4820305201F5
	UGint m_nDataVersionID;
	
		//! \brief 事务是否启动
	//##ModelId=4820305201F6
	UGbool m_bTransStarted;
#if !defined SYMBIAN60 && !defined  OS_ANDROID && !defined (IOS)
	//##ModelId=4820305201F7
	OgdcDataSource* m_pOgdcDS; 
#endif

	//##ModelId=483BB70A010C
	UGString m_strUUID;

	//! \brief 元数据ID
	UGString m_strMetadataID;

	//! \brief 版本管理器指针，在数据源构造函数中初始化，伴随着数据源的整个生命周期，所有版本管理的功能可以通过版本管理来调用
	UGVersionManager *m_pVersionManager;

	//! \brief 关系类管理器指针，在数据源构造函数中初始化，伴随着数据源的整个生命周期，所有关系类管理的功能可以通过该对象来调用
	UGDatasetRelClassManager *m_pDatasetRelClassManager;

	//! \brief 删除数据集回调函数标识
	static DeleteDTProc ms_DeleteDTCallBack;
	//! \brief 回调函数的传值参数
	static void * ms_DeleteDTCallBackData; 

	//! \brief 刷新数据集时，删除数据集事件的回调函数标识
	RefreshDSProc ms_RefreshDSCallBack;
	//! \brief 回调函数的传值参数
	void * ms_RefreshDSProcData; 

	//! \brief 数据源互斥对象
	UGMutex m_mutex;

#if !defined OS_ANDROID && !defined IOS
	//!	\brief	关系管理器
	UGRelationManager *m_pRelationManager;

	//!	\brief	保存关系操控者
	UGArray<UGDDRMasterBase*> m_arrDDRMasters;
#endif
public:
	//! \brief 引擎分类，1网络数据库，2本地文件型，3网络服务型。
	OgdcInt m_nEngineClass;
	
	//! \brief 2本地文件型数据源的文件后缀名。
	OgdcString m_strPostfix;

	UGDatasetVector* m_pTextureInfo;

	UGDatasetVector* m_pTextureTier;

	UGDomainManagerBase *m_pDomainManager;

#if !defined OS_ANDROID && !defined (IOS)
	UGTextureLib m_TextureLib;


	UGDatasetGroup * m_pDatasetGroup;
#endif	

};

}

#endif


