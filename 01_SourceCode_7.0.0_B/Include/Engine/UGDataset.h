/*! \file	 UGDataset.h
 *  \brief	 数据集基类
 *  \author	 ugc team
 *  \attention 
 *  Copyright(c) 2000-2010  SuperMap GIS Technologies,Inc.<br>
 *  All Rights Reserved
 *  \version $Id: UGDataset.h,v 1.32 2010/04/16 01:53:52 zhangshuo Exp $
 */

#ifndef UGDATASET_H
#define UGDATASET_H

#include "Geometry/UGDataCodec.h"
#include "Engine/ugeng.h"
#include "Engine/UGEngDefs.h"
#include "Engine/UGDDRRelation.h"
#include "Toolkit/UGProgress.h"
#if !defined SYMBIAN60 && !defined OS_ANDROID && !defined (IOS)
#include "OGDC/OgdcDataset.h"
#endif
namespace UGC {

class UGDataSource;

//! \brief 数据集基类
//##ModelId=482030550251
#ifdef SYMBIAN60
class ENGINE_APIC UGDataset
#else
class ENGINE_API UGDataset
#endif  
{
	friend class UGDDRMasterDynSeg;
	friend class UGSpatialIndex;
	friend class UGDynSegInfo;


public:
	//! \brief 数据集类型,数据源的IsSupport方法加以详细支持说明
	//##ModelId=4820305502EE
	enum DatasetType
	{
		//##ModelId=483BB70C0242
		UnKnown		=-1,
		//##ModelId=4820305502F0
		Tabular		=0,		//! 只有属性表，没有几何对象
		//##ModelId=4820305502FD
		Point		=1,		//! 点数据集
		//##ModelId=4820305502FE
		Line		=3,		//! 线数据集
		//##ModelId=4820305502FF
		Network		=4,		//! 网络数据集
		//##ModelId=48203055030D
		Region		=5,		//! 多边形数据集
		//##ModelId=48203055030E
		Text		=7,		//! 文本数据集
		//##ModelId=48203055030E
		ParametricLine = 8,   //! 参数化线数据集
		//##ModelId=48203055030E
		ParametricRegion = 9, //! 参数化面数据集
		//##ModelId=48203055030F
		LineM		=35,	//! 路线数据集
		//##ModelId=482030550310
		Image		=81,	//! 影像
		//##ModelId=48203055031C
		MrSID		=82,	//! MrSID
		//##ModelId=48203055031D
		Grid		=83,	//! 栅格
		//##ModelId=48203055031E
		DEM			=84,	//! DEM
		//##ModelId=48203055032C
		ECW			=85,	//! ECW
		//##ModelId=48203055032D
		WMS			=86,	//! WMS	
		//##ModelId=48203055032E
		WCS			=87,	//! WCS
	    
		MBImage     =88,    //! MultiBand Image
        MBGrid      =89,    //! MultiBand Grid
		MBDEM		=90,    //! MultiBand DEM
		//##ModelId=48203055033C
		PointZ		=101,	//! 三维点
		//##ModelId=48203055033D
		LineZ		=103,	//! 三维线
		//##ModelId=48203055033E
		RegionZ		=105,	//! 三维面
		//##ModelId=48203055033F
		PointGL		=137,	//! 带法向量的Point3D
		//##ModelId=48203055034B
		TIN			=139,	//! TIN数据集
		//##ModelId=48203055034C
		CAD			=149,	//! CAD数据集
		
		//##ModelId=48203055034D
		WFS			=151,	//! WFS
		//##ModelId=48203055035B
		LinkTable	=153,	//! 数据库表,只读功能
		//##ModelId=48203055035C
		Topo		=154,	//! Topo数据集
		//##ModelId=48203055035D
		TIN2		=155,	//! 新的Tin数据和以前的区分开
		RelClass	=156, 	//! 关系类数据集

		GridCollection    =199,
		ImageCollection    =200,

		VectorCollection    =201,//矢量数据集合
		RasterCollection    =202,//栅格数据集合
	}; 

	//##ModelId=48203055036B
	enum DatasetOption
	{
		//##ModelId=48203055036D
		Default		= 0x00000000,	//! 默认选项 
		//##ModelId=48203055036E
		HasStyle	= 0x00000001,	//! 风格支持 
		//{{2007.7.15 ri以后禁止应用
		//##ModelId=48203055037A
		Zip			= 0x00000002,	//! Zip压缩存储 
		//}}
		//##ModelId=48203055037B
		Pyramid     = 0x00000004,	//! 支持影像金字塔存储 
		//##ModelId=48203055037C
//		Sequence	= 0x00000008,	//! 支持时序存储 
		//##ModelId=48203055037D
		MemCache	= 0x00000010,	//! 支持内存缓存模式 
		//##ModelId=48203055038A
//		LongTrans	= 0x00000020,	//! 支持长事务操作 
		//##ModelId=48203055038B
//		UserLock	= 0x00000040,	//! 支持用户锁定 
		//##ModelId=48203055038C
		CacheMode	= 0x00000080,	//! 支持本地缓存模式 
		//{{2007.7.15 ri以后禁止应用
		//##ModelId=48203055038D
		Library		= 0x00010000,	//! 支持单表图库模式 
		//}}
		//##ModelId=482030550399
		ReadOnly	= 0x00020000,	//! 只读 
//		注意与SFC兼容
//		DataVersion = 0x00040000,	//! 版本管理 
		//##ModelId=48203055039A
//		DataVersion = 0x00100000,
		//##ModelId=48203055039B
		TopoAdscription = 0x00080000, //! topo 归属 
//		CacheIndex		= 0x00100000 //! 静态索引缓存 
		//CHARSET		((nOptions & 0x0000ff00 ) >> 8)
		//! \brief 版本管理
		Version		= 0x00100000,	
		//! \brief 复本管理
		Duplication	= 0x00200000,	

		//! \brief 顶点索引可用（无顶点索引：Option&0x00f00000 != 0x00400000 && Option&0x00f00000 != 0x00800000）
		VertexIndexAvailable= 0x00400000,
		//! \brief 顶点索引脏（无顶点索引：Option&0x00f00000 != 0x00400000 && Option&0x00f00000 != 0x00800000）
		VertexIndexDirty    = 0x00800000,
	};

	enum CollectionState
	{
		//正常
		normal = 1,
			
		//已经被删除,
		deleted = 2,
			
		//投影不相同
		projectionError = 3,

		//字段与数据集集合不符
		fieldError = 4,
		
		//像素格式不同
		pixelError = 5,

		//投影和字段都不同
		projectionAndField = 11,

		//投影和像素都不同
		projectionAndPixel = 12,
			
	};

	typedef struct UGDatasetState
	{
		CollectionState eumState;
		UGString strName;
		UGDatasetState()
		{
			eumState = normal;
			strName = _U("");
		}

	}UGDatasetState;


public:
	//! \brief 构造函数
	//##ModelId=482030550252
	ENGINE_APIF UGDataset();
	
	//! \brief 析构函数
	//##ModelId=482030550253
	virtual ENGINE_APIF ~UGDataset();

public:
	//! \brief 返回数据集对应A表表名
	//##ModelId=482030550272
	virtual ENGINE_APIF UGString GetATableName();
	
	//! \brief 返回数据集对应D表表名
	//##ModelId=482030550272
	virtual ENGINE_APIF UGString GetDTableName();

	//! \brief 返回数据集类型
	//##ModelId=482030550265
	virtual ENGINE_APIF UGDataset::DatasetType GetType() const = 0;
	
	//! \brief 返回数据集名(可以和表名不同)
	//##ModelId=48203055026B
	virtual ENGINE_APIF UGString GetName() = 0;
	
	//! \brief 返回数据集对应表名
	//##ModelId=482030550272
	virtual ENGINE_APIF UGString GetTableName() = 0;
	//! \brief 返回最小高程
	//##ModelId=482030550277
	virtual ENGINE_APIF UGdouble GetMinZ() = 0;

	//! \brief 设置最小高程
	//##ModelId=482030550279
	virtual ENGINE_APIF void SetMinZ(UGdouble d) = 0;

	//! \brief 返回最大高程
	//##ModelId=48203055027C
	virtual ENGINE_APIF UGdouble GetMaxZ() = 0;

	//! \brief 设置最大高程
	//##ModelId=482030550281
	virtual ENGINE_APIF void SetMaxZ(UGdouble d) = 0;

	//! \brief 返回数据集的维数
	//##ModelId=482030550284
	virtual ENGINE_APIF UGint GetDimension() = 0;

	//! \brief 判断是否是矢量数据集
	//##ModelId=482030550286
	virtual ENGINE_APIF UGbool IsVector() = 0;

	//! \brief 判断是否是Topo数据集
	//##ModelId=482030550288
	virtual ENGINE_APIF UGbool IsTopoDataset() = 0;

	//! \brief 判断是否是栅格数据集
	//##ModelId=48203055028A
	virtual ENGINE_APIF UGbool IsRaster() = 0;

	//! \brief 判断是否是关系类数据集
	virtual ENGINE_APIF UGbool IsRelClass() = 0;

	virtual ENGINE_APIF UGbool IsMBRaster();

	//##ModelId=48203055028C
	virtual ENGINE_APIF UGbool IsLinkTable() = 0;

	//! \brief 返回数据集的范围
	//##ModelId=482030550291
	virtual ENGINE_APIF const UGRect2D& GetBounds() = 0;

	//! \brief 设置数据集的范围
	//##ModelId=482030550293
	virtual ENGINE_APIF void SetBounds(const UGRect2D& r) = 0;

	//! \brief 返回空间数据编码方式
	//##ModelId=482030550296
	virtual ENGINE_APIF UGDataCodec::CodecType GetCodecType() = 0;
	
	//! \brief 设置空间数据编码方式
	//##ModelId=482030550298
	virtual ENGINE_APIF UGbool SetCodecType(UGDataCodec::CodecType c) = 0;

	//! \brief 返回数据集的选项信息(用四字节的整型数据代表一些属性)
	//##ModelId=48203055029B
	virtual ENGINE_APIF UGint GetOptions() = 0;
#if !defined SYMBIAN60 && !defined OS_ANDROID && !defined (IOS)
public:
	//##ModelId=483BB70C01D6
	static UGDataset* FromOgdcDataset(OgdcDataset* pOgdcDt, const UGDataSource* pDS);

	//##ModelId=483BB70C01E7
	static OgdcDataset* ToOgdcDataset(UGDataset* pDt);
#endif

public:
	//! \brief 打开数据集
	//##ModelId=482030550261
	virtual ENGINE_APIF UGbool Open();

	//! \brief 在多线程中用于判断关闭当前数据集是否安全，矢量主要依据是否还有打开的记录集，栅格主要依据是否可以释放所有数据块
	virtual ENGINE_APIF UGbool CanBeClose();

	//! \brief 关闭数据集
	//##ModelId=482030550263
	virtual ENGINE_APIF void Close();

	//! \brief 返回最后更新时间
	//##ModelId=482030550267
	virtual ENGINE_APIF UGTime GetDateLastUpdated();

	//! \brief 返回创建时间
	//##ModelId=482030550269
	virtual ENGINE_APIF UGTime GetDateCreated();
	
	//! \brief 数据集重命名,只改变数据集名,表名不变
	//##ModelId=482030550274
	virtual ENGINE_APIF UGbool Rename(const UGString& strNewName);

	//! \brief 保存数据集信息
	//##ModelId=48203055029F
	virtual ENGINE_APIF UGbool SaveInfo();
	
	//! \brief 刷新数据集信息
	//##ModelId=4820305502A1
	virtual ENGINE_APIF UGbool RefreshInfo();	
	
	//! \brief 返回数据集的ID
	//##ModelId=4820305502A3
	ENGINE_APIF UGint GetID() const;

	//! \brief 设置数据集的ID
	//##ModelId=4820305502A5
	ENGINE_APIF void SetID(UGint nID);

	//##ModelId=4820305502A7
	ENGINE_APIF UGString GetSchema() const;

	//! \brief 返回数据源指针
	//##ModelId=4820305502A9
	ENGINE_APIF UGDataSource* GetDataSource() const;

	//! \brief 设置数据源指针
	//##ModelId=4820305502AB
	ENGINE_APIF void SetDataSource(UGDataSource* pDs);

	//##ModelId=4820305502B0
	ENGINE_APIF UGbool IsModified() const;
	
	//##ModelId=4820305502B2
	ENGINE_APIF void SetModifiedFlag(UGbool bModified = TRUE);

	//! \brief 判断数据集是否已经打开
	//##ModelId=4820305502B4
	virtual ENGINE_APIF UGbool IsOpen() const;

	//! \brief 计算数据集范围,一般在数据集中元素被删除或修改后使用,
	//!        可能耗费较多时间
	//##ModelId=4820305502B6
	virtual ENGINE_APIF UGbool ComputeBounds();

	//! \brief 直接从内存中返回对象个数,速度比较快,
	//!        但不能保证正确,通过DatsetInfo获取
	//##ModelId=4820305502B8
	virtual ENGINE_APIF UGint GetObjectCountDirectly();

	//! \brief 返回数据集中对象个数,速度慢,但值比较正确,
	//!        通过Register表获取
	//##ModelId=4820305502BA
	virtual ENGINE_APIF UGint GetObjectCount();

	//! \brief 获取数据集占用的硬盘空间
	//##ModelId=4820305502BC
	virtual ENGINE_APIF UGint GetStoredSpace();

	//! \brief 获取数据集描述信息
	//##ModelId=4820305502C0
	virtual ENGINE_APIF UGString GetDescription() const;

	//! \brief 设置数据集描述信息
	//##ModelId=4820305502C2
	virtual ENGINE_APIF UGbool SetDescription(const UGString& /*strDesc*/);

	//! \brief 获取数据集附加信息
	//##ModelId=4820305502C0
	virtual ENGINE_APIF UGString GetExtInfo() const;

	//! \brief 设置数据集附加信息
	//##ModelId=4820305502C2
	virtual ENGINE_APIF UGbool SetExtInfo(const UGString& /*strExtInfo*/);
	
	//! \brief 判断当前数据集是否可编辑
	//##ModelId=4820305502C5
	virtual ENGINE_APIF UGbool CanUpdate();
	
	//! \brief 注册选项信息
	//##ModelId=4820305502C7
	virtual ENGINE_APIF UGbool RegisterOption(UGint /*nOption*/);

	//! \brief 反注册选项信息
	//##ModelId=4820305502CA
	virtual ENGINE_APIF UGbool UnRegisterOption(UGint /*nOption*/);
	
	//! \brief 判断数据集是否有某个选项信息
	//##ModelId=4820305502CD
	virtual ENGINE_APIF UGbool HasFlag(UGint /*nOption*/) const;
	
	//! \brief 数据集是否有某种模式的操作的能力
	//##ModelId=4820305502D0
	virtual ENGINE_APIF UGbool HasAbility(UGEngAbility /*dwEngAbility*/) {return FALSE;}
	
	//! \brief 判断数据集是否支持某种操作
	//##ModelId=4820305502D3
	virtual ENGINE_APIF UGbool IsSupport(UGEngAction /*nAction*/) {return FALSE;}	
	
	//##ModelId=483BB70C0205
	virtual ENGINE_APIF UGbool SetPrjCoordSys(const UGPrjCoordSys &PrjCoordSys);
	
	//========================================================
	//! \brief 		获取数据源的投影信息
	//! \return 	UGPrjCoordSys 读取出来的投影信息
	//##ModelId=483BB70C0214
	const ENGINE_APIF UGPrjCoordSys& GetPrjCoordSys();

	//! \brief 取消数据集投影设置，改用数据源投影
	virtual ENGINE_APIF void UnSetPrjCoordSys();

	//! \brief 判断数据集是否设置了自己的投影
	ENGINE_APIF UGbool HasSetPrjCoordSys();
#if !defined SYMBIAN60 && !defined OS_ANDROID && !defined (IOS)
	//##ModelId=483BB70C0215
	void SetOgdcDataset(OgdcDataset* pOgdcDt);	

	//##ModelId=483BB70C0222
	const OgdcDataset* GetOgdcDataset() const;	
#endif
#if PACKAGE_TYPE==PACKAGE_UGC
	//! \brief 锁定数据集,不允许其他用户编辑
	//##ModelId=4820305502D6
	virtual ENGINE_APIF UGbool Lock();

	//! \brief 对数据集解锁
	//##ModelId=4820305502D8
	virtual ENGINE_APIF UGbool Unlock();

	//! \brief 		设置数据集的进度条
	virtual ENGINE_APIF void SetProgress(UGProgress *pProgress) {m_pProgress = pProgress;}
	
	//! \brief 		获取数据集的进度条
	virtual ENGINE_APIF UGProgress* GetProgress() const {return m_pProgress;}


	//!	\brief	获取数据集在动态分段关系维护中的角色
	UGDDRDynSeg::DynSegDatasetRole GetDynSegRole() const { return m_eDynSegRole; }

#endif // end declare ugc sdk

protected:
	//! \brief 设置数据集的选项信息
	//##ModelId=4820305502DA
	virtual ENGINE_APIF void SetOptions(UGint nOptions) = 0;

public:
	//! \brief 数据集的ID
	//##ModelId=4820305502DE
	UGint m_nID;
protected:	
	//! \brief 是否打开
	//##ModelId=4820305502DF
	UGbool m_bOpened;
	//! \brief 是否已经修改
	//##ModelId=4820305502E0
	UGbool m_bModified;	
	//! \brief 数据源指针
	//##ModelId=4820305502E1
	UGDataSource* m_pDataSource;
#if !defined SYMBIAN60 && !defined OS_ANDROID && !defined (IOS)
	//##ModelId=4820305502E2
	OgdcDataset* m_pOgdcDataset;
#endif	
	//##ModelId=483BB70C0224
	UGPrjCoordSys m_prjCoordSys;

	//! \brief 数据集是否设置了自己的投影
	UGbool m_bPrjDataset;

	//! \ brief 互斥对象
	UGMutex m_mutex;


	//!	\brief	动态分段关系维护中，用于标识数据集的角色
	UGDDRDynSeg::DynSegDatasetRole m_eDynSegRole;
	
	UGString m_strMetadataID;  //对应元数据ID
	
public:
	//版本管理用
	UGint m_nEditingID;		//当前打开的数据集占用的唯一标识，在SmDatasetEditing中记录

	UGint m_nSeriesID;		//当前打开的数据集占用的序列
	
	UGint m_nLastActionID;	//当前打开的数据集的最终编辑状态
	
	UGint m_nEditState;		//数据集的状态，0：不编辑不协调状态，>0协调状态，-1编辑状态

	UGReconcileInfo m_ReconcileInfo;	//协调信息

	UGint m_nComActionID;	//用于标记编辑压缩的操作号
	
	UGProgress* m_pProgress; //仅供Compact()中使用 用于针对数据集进度条的显示  不需要释放 调用者释放
	
};

//##ModelId=4820305503A9
typedef UGArray<UGDataset*> UGDatasets;
 
}

#endif 

