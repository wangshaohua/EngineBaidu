/*******************************************************************/
/*                                                                 */
/*         Copyright (C) 2012 SuperMap Software Co., Ltd.          */
/*                   All Rights Reserved                           */
/*                                                                 */
/*******************************************************************/
/******************************************************************************
* FILENAME  - LicenseReader.h
*   
* USAGE     - SuperMap License Core Library
*
* REVISION HISTORY - 
******************************************************************************/ 

#if !defined(LICENSEREADER_H)
#define LICENSEREADER_H

#pragma once

// 现在的硬件锁都只是支持Windows
#if (defined(SOLARIS) || defined(_AIX) || defined(LINUX))
	
#else
	#define SupportPlatForm
#endif

#include <time.h>

const long MAX_CHAR				= 256;		// 内部使用的临时字符串长度
const long MAX_RAW_USER			= 8;		// 用户名最大长度，按字节计算，8个字母或4个汉字
const long MAX_RAW_COMPANY		= 16;		// 公司名最大长度，按字节计算，16个字母或8个汉字
const long MAX_HEARTBEAT_DAY	= 43200;	// 网络锁失效最大时间，按秒计算，12小时
const long CurrentReaderCount	= 3;

#define LABEL_Server			("Server")
#define LABEL_User				("User")
#define LABEL_Company			("Company")
#define LABEL_LicMode			("LicMode")
#define LABEL_LicIdentifyCode	("LicIdentifyCode")
#define LABEL_LicPath			("LicPath")
#define LABEL_LicData			("LicData")
#define LABEL_LicVersion		("LicVersion")
#define LABEL_LicMaxConnect		("LicMaxConnect")


// 硬件锁的错误码从100-800，我们自己的错误码从5000开始
#define SuperMap_License_Error_Code_Base				5000
#define HASPHL_License_Error_Code_Base					6000
#define SuperPro_License_Error_Code_Base				7000

#define SuperMap_License_Error_LaterExpiredDate			(SuperMap_License_Error_Code_Base + 1)
#define SuperMap_License_Error_EarlyStartDate			(SuperMap_License_Error_Code_Base + 2)
#define SuperMap_License_Error_WrongLicenseData			(SuperMap_License_Error_Code_Base + 3)
#define SuperMap_License_Error_WrongLicenseMode			(SuperMap_License_Error_Code_Base + 4)
#define SuperMap_License_Error_OpenISVFileFailed		(SuperMap_License_Error_Code_Base + 5)
#define SuperMap_License_Error_WrongProductVersion		(SuperMap_License_Error_Code_Base + 6)
#define SuperMap_License_Error_VerifyDataFailed			(SuperMap_License_Error_Code_Base + 7)
#define SuperMap_License_Error_SecureUpdateDllNotFound	(SuperMap_License_Error_Code_Base + 8)
#define SuperMap_License_Error_ApplyUpdateCodeNotFound	(SuperMap_License_Error_Code_Base + 9)

// 以后每增加一个产品需要干的活有：
// 1. 增加下面的 LABEL_XXXX
// 2. 增加LibProductType枚举，在下面
// 3. 增加LicenseReader.cpp的 GetProductName方法
// 3. 在LicenseRead\LicenseReadWrap.h 中的 ProductWrap枚举中添加
// 4. 在LicenseRead\LicenseReadWrap.cpp 中的GetProductDictionary方法中增加，并写上中文名
// 在SuperMap.License工程的所有资源中添加资源，并在Program.cs文件中增加
// 3、LibProductType对应的LicenseID，在SentinelKeysLicense.h里面
// 4、还有HASP对应的ID，在HASPKeysLicense.h里面

#define LABEL_CommonLicense								("CommonLicense")
#define LABEL_ObjectsCoreDevelop						("ObjectsCoreDevelop")
#define LABEL_ObjectsCoreRuntime						("ObjectsCoreRuntime")
#define LABEL_ObjectsSDXDevelop							("ObjectsSDXDevelop")
#define LABEL_ObjectsSDXRuntime							("ObjectsSDXRuntime")
#define LABEL_ObjectsSpaceDevelop						("ObjectsSpaceDevelop")
#define LABEL_ObjectsSpaceRuntime						("ObjectsSpaceRuntime")
#define LABEL_ObjectsLayoutDevelop						("ObjectsLayoutDevelop")
#define LABEL_ObjectsLayoutRuntime						("ObjectsLayoutRuntime")
#define LABEL_ObjectsSpatialDevelop						("ObjectsSpatialDevelop")
#define LABEL_ObjectsSpatialRuntime						("ObjectsSpatialRuntime")
#define LABEL_ObjectsNetworkDevelop						("ObjectsNetworkDevelop")
#define LABEL_ObjectsNetworkRuntime						("ObjectsNetworkRuntime")
#define LABEL_ObjectsTopologyDevelop					("ObjectsTopologyDevelop")
#define LABEL_ObjectsTopologyRuntime					("ObjectsTopologyRuntime")
#define LABEL_ObjectsAddressMatchingDevelop				("ObjectsAddressMatchingDevelop")
#define LABEL_ObjectsAddressMatchingRuntime				("ObjectsAddressMatchingRuntime")
#define LABEL_ObjectsCoreEmbedded						("ObjectsCoreEmbedded")
#define LABEL_ObjectsFMEVector							("ObjectsFMEVector")
#define LABEL_ObjectsFMEEsri							("ObjectsFMEEsri")
#define LABEL_ObjectsFMERaster							("ObjectsFMERaster")
#define LABEL_ObjectsFMEOther							("ObjectsFMEOther")
#define LABEL_ObjectsNauticalChartDevelop				("ObjectsNauticalChartDevelop")
#define LABEL_ObjectsNauticalChartRuntime				("ObjectsNauticalChartRuntime")
#define LABEL_ObjectsRealspaceSpatialAnalystDevelop		("ObjectsRealspaceSpatialAnalystDevelop")
#define LABEL_ObjectsRealspaceSpatialAnalystRuntime		("ObjectsRealspaceSpatialAnalystRuntime")
#define LABEL_UniversalGISCore							("UniversalGISCore")
#define LABEL_ObjectsTrafficAnalystDevelop				("ObjectsTrafficAnalystDevelop")
#define LABEL_ObjectsTrafficAnalystRuntime				("ObjectsTrafficAnalystRuntime")
#define LABEL_ObjectsRealspaceNetworkAnalystDevelop		("ObjectsRealspaceNetworkAnalystDevelop")
#define LABEL_ObjectsRealspaceNetworkAnalystRuntime		("ObjectsRealspaceNetworkAnalystRuntime")
#define LABEL_ObjectsRealspaceEffectDevelop				("ObjectsRealspaceEffectDevelop")
#define LABEL_ObjectsRealspaceEffectRuntime				("ObjectsRealspaceEffectRuntime")

#define LABEL_Deskpro_NET						("DeskproNET")
#define LABEL_Express_NET						("ExpressNET")
#define LABEL_Viewer_NET						("ViewerNET")
#define LABEL_DeskproNETTopology				("DeskproNETTopology")
#define LABEL_DeskproNETTrafficNetwork			("DeskproNETTrafficNetwork")
#define LABEL_DeskproNETFacilityNetwork			("DeskproNETFacilityNetwork")
#define LABEL_DeskproNETSpatial					("DeskproNETSpatial")
#define LABEL_DeskproNETNauticalChart			("DeskproNETNauticalChart")
#define LABEL_DeskproNETGeoProcesser			("DeskproNETGeoProcesser")
#define LABEL_DeskproNETRealspaceSpatialAnalyst	("DeskproNETRealspaceSpatialAnalyst")
#define LABEL_DeskproNETTrafficAnalyst			("DeskproNETTrafficAnalyst")
#define LABEL_DeskproNETRealspaceEffect			("DeskproNETRealspaceEffect")

#define LABEL_iServerStandard					("iServerStandard")
#define LABEL_iServerProfessional				("iServerProfessional")
#define LABEL_iServerEnterprise					("iServerEnterprise")
#define LABEL_iServerSpatial					("iServerSpatial")
#define LABEL_iServerNetwork					("iServerNetwork")
#define LABEL_iServerTrafficTransfer			("iServerTrafficTransfer")
#define LABEL_iServerSpace						("iServerSpace")
#define LABEL_iServerNauticalChart				("iServerNauticalChart")
#define LABEL_iServerExpress					("iServerExpress")

#define LABEL_SFCObjectsCoreDevelop				("SFCObjectsCoreDevelop")
#define LABEL_SFCObjectsCoreRuntime				("SFCObjectsCoreRuntime")
#define LABEL_SFCObjects3DDevelop				("SFCObjects3DDevelop")
#define LABEL_SFCObjects3DRuntime				("SFCObjects3DRuntime")
#define LABEL_SFCObjectsTopologyDevelop			("SFCObjectsTopologyDevelop")
#define LABEL_SFCObjectsTopologyRuntime			("SFCObjectsTopologyRuntime")
#define LABEL_SFCObjectsLayoutDevelop			("SFCObjectsLayoutDevelop")
#define LABEL_SFCObjectsLayoutRuntime			("SFCObjectsLayoutRuntime")
#define LABEL_SFCObjectsAnalystDevelop			("SFCObjectsAnalystDevelop")
#define LABEL_SFCObjectsAnalystRuntime			("SFCObjectsAnalystRuntime")
#define LABEL_SFCObjectsSDXDevelop				("SFCObjectsSDXDevelop")
#define LABEL_SFCObjectsSDXRuntime				("SFCObjectsSDXRuntime")
#define LABEL_SFCDeskpro						("SFCDeskpro")
#define LABEL_SFCExpress						("SFCExpress")
#define LABEL_SFCDBuilder						("SFCDBuilder")
#define LABEL_SFCDProducer						("SFCDProducer")
#define LABEL_SFCDChecker						("SFCDChecker")
#define LABEL_SFCFloor							("SFCFloor")
#define LABEL_SFCWaterGIS						("SFCWaterGIS")
#define LABEL_SFCISAdvance						("SFCISAdvance")
#define LABEL_SFCISProfessional					("SFCISProfessional")
#define LABEL_SFCISDevelop						("SFCISDevelop")

#define LABEL_SGOCoreModule						("SGOCoreModule")
#define LABEL_SGODataModule						("SGODataModule")
#define LABEL_SGODisplay2DModule				("SGODisplay2DModule")
#define LABEL_SGODisplay3DModule				("SGODisplay3DModule")
#define LABEL_SGOSequenceModule					("SGOSequenceModule")
#define LABEL_SGOCoreModuleNET					("SGOCoreModuleNET")
#define LABEL_SGOSequenceModuleNET				("SGOSequenceModuleNET")
#define LABEL_SGOCoreModuleJAVA 				("SGOCoreModuleJAVA")
#define LABEL_SGOSequenceModuleJAVA				("SGOSequenceModuleJAVA")
#define LABEL_SGOCoreModuleEMBED				("SGOCoreModuleEMBED")
#define LABEL_SGraphicServerJAVA				("SGraphicServerJAVA")
#define LABEL_SCooperationServerJAVA			("SCooperationServerJAVA")
#define LABEL_SSequenceServerJAVA				("SSequenceServerJAVA")
#define LABEL_SMilitaryUtility					("SMilitaryUtility")

#define LABEL_SGOCoreModuleRuntime				("SGOCoreModuleRuntime")
#define LABEL_SGODataModuleRuntime				("SGODataModuleRuntime")
#define LABEL_SGODisplay2DModuleRuntime			("SGODisplay2DModuleRuntime")
#define LABEL_SGODisplay3DModuleRuntime			("SGODisplay3DModuleRuntime")
#define LABEL_SGOSequenceModuleRuntime			("SGOSequenceModuleRuntime")
#define LABEL_SGOCoreModuleNETRuntime			("SGOCoreModuleNETRuntime")
#define LABEL_SGOSequenceModuleNETRuntime		("SGOSequenceModuleNETRuntime")

#define LABEL_ZXTShipmentManager				("ZXTShipmentManager")

#define LABEL_SuperMapSGSStandard				("SuperMapSGSStandard")
#define LABEL_SuperMapSGSProfessional			("SuperMapSGSProfessional")
#define LABEL_SuperMapSGSEnterprise				("SuperMapSGSEnterprise")
#define LABEL_SuperMapDManagerStandard			("SuperMapDManagerStandard")
#define LABEL_SuperMapDManagerProfessional		("SuperMapDManagerProfessional")

#define LABEL_SuperMapDCSStandard				("SuperMapDCSStandard")
#define LABEL_SuperMapDCSProfessional			("SuperMapDCSProfessional")
#define LABEL_SuperMapDCSEnterprise				("SuperMapDCSEnterprise")
#define LABEL_SuperMapDCSBusinessSMS			("SuperMapDCSBusinessSMS")
#define LABEL_SuperMapDCSVideoMonitor			("SuperMapDCSVideoMonitor")
#define LABEL_SuperMapDCSSupervisorManager		("SuperMapDCSSupervisorManager")
#define LABEL_SuperMapDCSSocialInvolvement		("SuperMapDCSSocialInvolvement")
		
// 平台软件事业部
#define LABEL_SuperMapEUD						("SuperMapEUD")                // 电力空间数据处理桌面
#define LABEL_SuperMapESSData					("SuperMapESSData")			   // 电力调度地理信息服务数据服务模块
#define LABEL_SuperMapESSMapping				("SuperMapESSMapping")		   // 电力调度地理信息服务地图服务模块
#define LABEL_SuperMapESSSpatialAnalyst			("SuperMapESSSpatialAnalyst")  // 电力调度地理信息服务空间分析服务模块
#define LABEL_SuperMapESSCatalog				("SuperMapESSCatalog")		   // 电力调度地理信息服务目录服务模块

// TODO 需要添加模块的地方


enum LibProductType
{	
	CommonLicense							= 0,	// 公用的一些许可信息，内部使用
	ObjectsCoreDevelop						= 1,	// 核心组件开发版
	ObjectsCoreRuntime						= 2,	// 核心组件运行版
	ObjectsSDXDevelop						= 3,	// 空间数据库组件开发版
	ObjectsSDXRuntime						= 4,	// 空间数据库组件运行版
	ObjectsSpaceDevelop						= 5,	// 三维组件开发版
	ObjectsSpaceRuntime						= 6,	// 三维组件运行版
	ObjectsLayoutDevelop					= 7,	// 排版打印组件开发版
	ObjectsLayoutRuntime					= 8,	// 排版打印组件运行版
	ObjectsSpatialDevelop					= 9,	// 空间分析组件开发版
	ObjectsSpatialRuntime					= 10,	// 空间分析组件运行版
	ObjectsNetworkDevelop					= 11,	// 网络分析组件开发版
	ObjectsNetworkRuntime					= 12,	// 网络分析组件运行版
	ObjectsTopologyDevelop					= 13,	// 拓扑组件开发版
	ObjectsTopologyRuntime					= 14,	// 拓扑组件运行版
	ObjectsAddressMatchingDevelop			= 15,	// 地址匹配组件开发版
	ObjectsAddressMatchingRuntime			= 16,	// 地址匹配组件运行版
	ObjectsCoreEmbedded						= 17,   // SuperMap嵌入式开发平台		FILE
	ObjectsFMEVector						= 18,	// SuperMap 数据转换矢量格式	FILE
	ObjectsFMEEsri							= 19,	// SuperMap 数据转换ESRI格式	FILE	
	ObjectsFMERaster						= 20,	// SuperMap 数据转换栅格格式 	FILE
	ObjectsFMEOther							= 21,	// SuperMap 数据转换其他格式	FILE
	ObjectsNauticalChartDevelop				= 22,	// SuperMap 海图开发版	
	ObjectsNauticalChartRuntime				= 23,   // SuperMap 海图运行版	
	ObjectsRealspaceSpatialAnalystDevelop	= 24,	// 三维空间分析组件开发版
	ObjectsRealspaceSpatialAnalystRuntime	= 25,	// 三维空间分析组件运行版
	UniversalGISCore						= 26,	// UniversalGISCore 类库
	ObjectsTrafficAnalystDevelop			= 27,	// 公交分析组件开发版
	ObjectsTrafficAnalystRuntime			= 28,	// 公交分析组件运行版
	ObjectsRealspaceNetworkAnalystDevelop	= 29,	// 三维网络分析组件开发版
	ObjectsRealspaceNetworkAnalystRuntime	= 30,	// 三维网络分析组件运行版
	ObjectsRealspaceEffectDevelop			= 31,	// 三维特效组件开发版
	ObjectsRealspaceEffectRuntime			= 32,	// 三维特效组件运行版

	
	DeskproNET							= 501,	// 桌面可开发版
	ExpressNET							= 502,	// 桌面
	ViewerNET							= 503,	// 桌面免费版
	DeskproNETTopology					= 504,	// 桌面拓扑处理扩展模块
	DeskproNETTrafficNetwork			= 505,  // 桌面交通网络分析扩展模块 
	DeskproNETFacilityNetwork			= 506,  // 桌面设施网络分析扩展模块 
	DeskproNETSpatial					= 507,  // 桌面空间分析扩展模块
	DeskproNETNauticalChart				= 508,	// 桌面海图扩展模块
	DeskproNETGeoProcesser				= 509,	// 桌面空间处理扩展模块
	DeskproNETRealspaceSpatialAnalyst	= 510,	// 桌面三维分析扩展模块
	DeskproNETTrafficAnalyst			= 511,	// 桌面公交分析扩展模块
	DeskproNETRealspaceEffect			= 512,	// 桌面三维特效扩展模块

	iServerStandard					= 1000,	// iServer标准版
	iServerProfessional				= 1001,	// iServer专业版
	iServerEnterprise				= 1002,	// iServer高级版
	iServerSpatial					= 1003,	// iServer空间分析扩展
	iServerNetwork					= 1004,	// iServer网络分析扩展
	iServerTrafficTransfer			= 1005,	// iServer交通换乘扩展
	iServerSpace					= 1006,	// iServer三维扩展
	iServerNauticalChart			= 1007, // iServer海图扩展
	iServerExpress					= 1008, // iServer基础版

	SFCObjectsCoreDevelop			= 5000,	// SFC核心组件开发版
	SFCObjectsCoreRuntime			= 5001,	// SFC核心组件运行版
	SFCObjects3DDevelop				= 5002,	// SFC三维组件开发版
	SFCObjects3DRuntime				= 5003,	// SFC三维组件运行版
	SFCObjectsTopologyDevelop		= 5004,	// SFC拓扑组件开发版
	SFCObjectsTopologyRuntime		= 5005,	// SFC拓扑组件运行版
	SFCObjectsLayoutDevelop			= 5006,	// SFC排版打印组件开发版
	SFCObjectsLayoutRuntime			= 5007,	// SFC排版打印组件运行版
	SFCObjectsAnalystDevelop		= 5008,	// SFC分析组件开发版
	SFCObjectsAnalystRuntime		= 5009,	// SFC分析组件运行版
	SFCObjectsSDXDevelop			= 5010,	// SFC空间数据库组件开发版
	SFCObjectsSDXRuntime			= 5011,	// SFC空间数据库组件运行版
	SFCDeskpro						= 5012,	// SFC Deskpro
	SFCExpress						= 5013,	// SFC Express
	SFCDBuilder						= 5014,	// SFC D-Builder
	SFCDProducer					= 5015,	// SFC D-Producer
	SFCDChecker						= 5016,	// SFC D-Checker
	SFCFloor						= 5017,	// SFC Floor
	SFCWaterGIS						= 5018,	// SFC WaterGIS
	SFCISAdvance					= 5019,	// IS .NET高级版
	SFCISDevelop					= 5021,	// IS .NET开发版

	SGOCoreModule					= 6001,	//	SuperMap DGO 核心模块
	SGODataModule					= 6002,	//	SuperMap DGO 数据管理模块
	SGODisplay2DModule				= 6003,	//	SuperMap DGO 军用标号模块
	SGODisplay3DModule				= 6004,	//	SuperMap DGO 三维模块		
	SGOSequenceModule				= 6005,	//	SuperMap DGO 协同模块
	SGOCoreModuleNET				= 6006,	//	SuperMap DGO 二维模块
	SGOSequenceModuleNET			= 6007,	//	SuperMap DGO 时序推演模块

	SGOCoreModuleJAVA				= 6008,	//	SuperMap EGS 标绘服务
	SGOSequenceModuleJAVA			= 6009,	//	SuperMap EGS 数据管理服务
	SGOCoreModuleEMBED				= 6010,	//	SuperMap EGS 协同服务
	SGraphicServerJAVA				= 6011,	//	SuperMap EGS 军图发布服务
	SCooperationServerJAVA			= 6012,	//	SuperMap EGS 军图打印服务
	SSequenceServerJAVA				= 6013,	//	SuperMap EGS 推演服务
	SMilitaryUtility				= 6014,	//													FILE

	SGOCoreModuleRuntime			= 6015,	//	SuperMap DGO 核心模块运行版
	SGODataModuleRuntime			= 6016,	//	SuperMap DGO 数据管理模块运行版
	SGODisplay2DModuleRuntime		= 6017,	//	SuperMap DGO 军用标号模块运行版
	SGODisplay3DModuleRuntime		= 6018,	//	SuperMap DGO 三维模块运行版		
	SGOSequenceModuleRuntime		= 6019,	//	SuperMap DGO 协同模块运行版
	SGOCoreModuleNETRuntime			= 6020,	//	SuperMap DGO 二维模块运行版
	SGOSequenceModuleNETRuntime		= 6021,	//	SuperMap DGO 时序推演模块运行版

	ZXTShipmentManager				= 6100, // 智行通出货管理应用程序							FILE
	
	//数字城市
	SuperMapSGSStandard				= 6200,	// 面向服务的地理信息共享平台 标准版 60/20	FILE
	SuperMapSGSProfessional			= 6201,	// 面向服务的地理信息共享平台 专业版 60/20	FILE
	SuperMapSGSEnterprise			= 6202,	// 面向服务的地理信息共享平台 高级版 60/20	FILE
	SuperMapDManagerStandard		= 6203,	// 空间数据管理平台软件 标准版	60			FILE
	SuperMapDManagerProfessional	= 6204,	// 空间数据管理平台软件 专业版	60			FILE

	SuperMapDCSStandard				= 6205, // SuperMap DCS 标准版 
	SuperMapDCSProfessional			= 6206, // SuperMap DCS 专业版
	SuperMapDCSEnterprise			= 6207, // SuperMap DCS 高级版 
	SuperMapDCSBusinessSMS			= 6208,	// SuperMap DCS 业务短信子系统
	SuperMapDCSVideoMonitor			= 6209, // SuperMap DCS 视频监控子系统
	SuperMapDCSSupervisorManager	= 6210, // SuperMap DCS 监督员管理子系统
	SuperMapDCSSocialInvolvement	= 6211, // SuperMap DCS 门前三包子系统

	// 平台软件事业部
	SuperMapEUD						= 6300, // 电力空间数据处理桌面
	SuperMapESSData					= 6301, // 电力调度地理信息服务数据服务模块
	SuperMapESSMapping				= 6302, // 电力调度地理信息服务地图服务模块
	SuperMapESSSpatialAnalyst		= 6303, // 电力调度地理信息服务空间分析服务模块
	SuperMapESSCatalog				= 6304, // 电力调度地理信息服务目录服务模块

	// TODO 需要添加模块的地方
};


enum LibLicenseMode
{
	NoLicense		= 0,	// 无需可
	HardwareKey		= 1,	// 硬件锁
	TrialVersion	= 2,	// 原来的计算机名，变为试用版，这样老的程序都可以使用
	NetworkCard		= 3,	// 网卡
	ComputerName    = 4,	// 计算机名加密，正式版本
};

enum LibProductVersion
{
	V200 = 200,
	V600 = 600,
};

enum LibHardwareKeyType
{
	InvalidType		= 0,
	Standalone		= 1,
	StandaloneTime	= 2,
	Network			= 3,
	NetworkTime		= 4,
};

struct LicenseData
{	
	LibProductType product;	
	LibProductVersion version;
};

enum LibHardwareType
{
	UnknownHW	= 0,
	SuperPro	= 1,
	Sentinel	= 2,
	Aladdin		= 3,
};


class LicenseReader
{
	friend class LicenseReaderSentinel;
	friend class LicenseReaderAladdin;
	friend class LicenseReaderSuperPro;

public:
	LicenseReader();
	~LicenseReader();
	
	// 以下成员函数对应组件的属性
public:
	// 得到当前机器的识别码
	char* GetIdentifyCode();

	// 得到许可使用用户名
	char* GetUser();

	// 得到许可使用公司名称
	char* GetCompany();

	// 最大可连接用户数
	int GetMaxConnection();

	// 当前连接锁的用户数
	int GetCurrentConnection();	

	// 许可模式
	LibLicenseMode GetLicenseMode();

	// 许可服务器
	char* GetLicenseServer();

	// 产品过期日期
	int GetExpiredDate(int &year,int &month,int &day);

	// 产品类型
	LibProductVersion GetProductVersion();

	// 产品类型
	LibProductType GetProductType();

	// 设置当前使用的硬件锁
	void SetCurrentHardwareType(LibHardwareType hardwareType);

	// 得到网卡信息
	static bool GetNetWordCardInfo(int nPos,char* CardSN,char* CardName);

	// 以下成员函数对应组件的方法，但是组件没有参数，参数需要使用者传进来
public:
	// 0是成功的，其他编码的信息可以通过GetErrorDetail来得到确切含义
	int Connect(const LicenseData &data);

	// 0是成功的，其他编码的信息可以通过GetErrorDetail来得到确切含义
	int Verify();

	// 断开与锁的连接
	void Disconnect();

	// 得到错误码的描述信息
	static char* GetErrorDetail(int code);

	// 得到锁的类型
	int GetKeyType(LibHardwareKeyType &keyType);

	// 以下为辅助功能函数，用于生成许可文件和配置文件使用
public:
	// 生成文件许可的LicData
	static char* GenerateLicData(	const LibProductType product,
									const char* user,
									const char* company,
									const char* version,
									const char* identifyCode,
									unsigned int expiredDate,
									unsigned int startDate,
									int LicenseMode,
									unsigned int licFileMaxConnect = 0);
	
	// 得到产品对应的字符串名字，可用于制作许可文件等地方使用
	static char* GetProductName(LibProductType product);

	// 生成Ini文件里面的节
	static char* GenerateFileIniSegment(const LibProductType product,
									const char* user,
									const char* company,
									const char* identifyCode,
									const char* licPath,
									unsigned int licFileMaxConnect = 0);

	// 生成lic里面的节
	static char* GenerateLicSegment(const LibProductType product,const char* licData,const char* version, unsigned int licFileMaxConnect = 0);

	// 生成Ini锁里面的节
	static char* GenerateKeyIniSegment(const LibProductType product,const char* server);

	// 得到文件许可配置文件路径
	static char* GetIniFileName();
	
	// 得到计算机名字
	static char* GetMachineName();

	
	// 内部专用函数
	static void GetLicenseInfo(const char* productName,char* user,char* company,char* server,char* licData,char* identifyCode,LibProductVersion nVersion = V200);
	// 文件型需要获取写的许可个数，调用这个接口 add by gouyu 2012-11-6
	static void GetLicenseInfo(const char* productName,char* user,char* company,char* server,char* licData,char* identifyCode, unsigned int &licMaxConnect ,LibProductVersion nVersion = V200);
	
	static void GetStartExpiredDate(const char* licData,unsigned int *startDate,unsigned int *expiredDate);	
	static LibLicenseMode ReadProductLicMode(char* productName);

	static int CollectKeyInfo(char* &keyInfo,int *&count);
	static int UpdateKeyInfo(const char* updateInfo,const int count);

	// 获取和设置服务器连接的时间频率
	// add by gouyu 2011-11-7
	static long GetConnectionHeartbeat();
	static void SetConnectionHeartbeat(long value);

	// 获取设置外部许可验证文件的位置，最长255个字符
	// add by gouyu 2011-11-28
	static char* GetExtraIniKeyPath();
	static void SetExtraIniKeyPath(const char* path);

public:
	static int VerifyMachine();
	static char* CreateKeys();
	
	// 以下为内部使用
private:	
	void InitilizeReader();
	void ReleaseReader();

	int ConnectComputerName(const LicenseData &data);
	int ConnectHardwareKey(const LicenseData &data);
	int ConnectNetworkCard(const LicenseData &data);
	int VerifyHardwareKey();
	static char* GetDir(char* pFileName);

	unsigned char* Encrypt(unsigned char* inValue);
	unsigned char* Decrypt(unsigned char* inValue);

private:
	void* m_readerArray[CurrentReaderCount];
	int m_currentIndex;

	LicenseData m_data;
	LibLicenseMode m_licMode;
	LibHardwareType m_hardwareType;
	char m_productName[MAX_CHAR];
	char m_user[MAX_CHAR];
	char m_company[MAX_CHAR];
	char m_server[MAX_CHAR];	
	char m_licData[MAX_CHAR];
	char m_identifyCode[MAX_CHAR];
	unsigned int m_licFileMaxConnect;

	static char* sm_pExtraIniPath;
};

#endif
