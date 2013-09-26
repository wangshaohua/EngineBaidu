// UGLicense.h: interface for the UGLicense class.
//
//////////////////////////////////////////////////////////////////////

#ifndef UGLICENSE
#define UGLICENSE

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Stream/ugdefs.h"
#include "Stream/ugplatform.h"

#include "License/LicenseReader.h"

typedef LibHardwareKeyType UGHardwareKeyType;
typedef LibLicenseMode UGLicenseMode;
typedef LibProductVersion UGProductVersion;
typedef LibProductType UGProductType;

namespace UGC
{			
	//! \brief LicenseErrorProc 事件回调函数
	typedef void (UGSTDCALL *LicenseErrorProc)(UGString errorMsg);

	class TOOLKIT_API UGLicense
	{

	public:
	enum ChartLicenseState
	{
		UnEnable			= -1,	// 不可用
		iServerEnable		= 0,	// iServer许可可用
		DeskproEnable		= 1,	// 桌面许可可用
		ObjectEnable		= 2,	// 组件许可可用
	};									

	public:

		~UGLicense();

		UGLicense();

		UGProductVersion GetVersion();

		UGProductType GetProduct();

		UGLicenseMode GetLicenseMode();

		UGHardwareKeyType GetKeyType();

		UGString GetIdentifyCode();

		UGString GetUser();

		UGString GetCompany();

		UGString GetLicenseServer();

		UGTime GetExpiredDate();

		UGint GetMaxConnection();

		UGint Connect(UGProductType product);

		UGint Verify();

		void Disconnect();

		static UGString GetErrorMessage(UGint code);	

		UGbool GetLicenseVaild();

		static UGbool VerifyUGCLicense();

		//{{added by qianjn 2011-4-12 
	public:

		// 设置是否试用许可, 0是正式许可，1为地图试用许可，2为布局试用许可，3为三维试用许可
		static void SetIsUnregistered(UGint nType, UGbool bUnregistered);
		static UGbool GetIsUnregistered(UGint nType);

		// 设置或获取当前海图许可是否可用 [8/31/2011 zhoujt]
		static void SetChartLicenseState(UGint nCode);
		static UGLicense::ChartLicenseState GetChartLicenseState();

		//// 设置当前运行的产品类型
		//static void SetCurrentProduction(UGint nType);
		//static UGint GetCurrentProduction();

		// 获取和设置当前产品是否允许绘制海图图层 [9/2/2011 zhoujt]
		static void SetDrawChartLayer(UGbool bEnable = false);
		static UGbool GetDrawChartLayer();

		static UGbool GetLicCheckMode();
		static void SetLicCheckMode(UGString mode);

		static void SetLicenseErrorFunc(LicenseErrorProc pLicenseErrorFunc);

	private:

		static LicenseErrorProc g_pLicenseErrorFunc;
		static void SendLicenseErrorFunc(UGString errorMsg);

	private:

		// 是否试用许可，默认false
		static UGbool m_bUnregisteredMap;
		static UGbool m_bUnregisteredLayout;
		static UGbool m_bUnregisteredSpace;
		//}}added by qianjn 2011-4-12 

		// 当前海图许可的状态 [8/31/2011 zhoujt]
		// iServer许可可用 --- 0; 桌面许可可用 --- 1; 组件许可可用 -- 2; 没有许可 --- -1;
		static UGLicense::ChartLicenseState m_eChartLicenseState;

		//  [9/2/2011 zhoujt]
		static UGbool m_bDrawCharLayer;

		LicenseReader* m_pLicenseReader;	

		static UGbool g_licenseVaild;
		static UGbool g_Checked;
		static UGString g_checkMode;
	};	
}
#endif //UGLICENSE
