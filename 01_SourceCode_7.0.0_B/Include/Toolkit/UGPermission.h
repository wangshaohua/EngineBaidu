/************************************************************************/
/* 这是嵌入式平台下许可控制类，该类负责解码许可文件，验证许可，验证模块    */
/* 作者：刘聪启                                                         */
/* 时间：2012年9月25日                                                  */
/************************************************************************/

#ifndef UGPERMISSION_HEADER_FOR_OBJECTS_EMBEDED
#define UGPERMISSION_HEADER_FOR_OBJECTS_EMBEDED


#include "Stream/UGFile.h"
#include "Stream/ugdefs.h"



#include <string>
#include <iostream>


// a small class for calculating MD5 hashes of strings or byte arrays
// it is not meant to be fast or secure
//
// usage: 1) feed it blocks of uchars with update()
//      2) finalize()
//      3) get hexdigest() string
//      or
//      MD5(std::string).hexdigest()
//
// assumes that char is 8 bit and int is 32 bit
namespace UGC
{


class TOOLKIT_API MD5
{
	
public:
	typedef unsigned int size_type;

	MD5();
	MD5(const  unsigned char *text);
	void update(const unsigned char *buf, size_type length);
	void update(const char *buf, size_type length);
	MD5& finalize();
	char* hexdigest() const;
	UGString hex16byte() const;
	friend std::ostream& operator<<(std::ostream&, MD5 md5);

private:
	typedef unsigned char uint1; 
	typedef unsigned int uint4;
	void init();
	
	enum {blocksize = 64}; // VC6 won't eat a const static int here

	void transform(const uint1 block[blocksize]);
	static void decode(uint4 output[], const uint1 input[], size_type len);
	static void encode(uint1 output[], const uint4 input[], size_type len);

	bool finalized;
	uint1 buffer[blocksize]; // bytes that didn't fit in last 64 byte chunk
	uint4 count[2];   // 64bit counter for number of bits (lo, hi)
	uint4 state[4];   // digest so far
	uint1 digest[16]; // the result

	// low level logic operations
	static inline uint4 F(uint4 x, uint4 y, uint4 z);
	static inline uint4 G(uint4 x, uint4 y, uint4 z);
	static inline uint4 H(uint4 x, uint4 y, uint4 z);
	static inline uint4 I(uint4 x, uint4 y, uint4 z);
	static inline uint4 rotate_left(uint4 x, int n);
	static inline void FF(uint4 &a, uint4 b, uint4 c, uint4 d, uint4 x, uint4 s, uint4 ac);
	static inline void GG(uint4 &a, uint4 b, uint4 c, uint4 d, uint4 x, uint4 s, uint4 ac);
	static inline void HH(uint4 &a, uint4 b, uint4 c, uint4 d, uint4 x, uint4 s, uint4 ac);
	static inline void II(uint4 &a, uint4 b, uint4 c, uint4 d, uint4 x, uint4 s, uint4 ac);
};

UGString md5(const UGchar *str);

//加密成16位的字符串
UGString md5to16byte(const UGchar *str);


//定义核心开发模块
#define MOBILE_MODULE_CORE_Dev 0x01
//定义核心运行模块
#define MOBILE_MODULE_CORE_Runtime 0x02
//定义导航开发模块
#define MOBILE_MODULE_GUIDE_Dev 0x04
//定义导航运行模块
#define MOBILE_MODULE_GUIDE_Runtime 0x08
//定义三维开发模块
#define MOBILE_MODULE_3D_Dev 0x10
//定义三维运行模块
#define MOBILE_MODULE_3D_Runtime 0x20


const UGString UserSerialID = _U("UserSerialID");
const UGString Modules = _U("Modules");
const UGString Version = _U("Version");
const UGString StartDate = _U("StartDate");
const UGString ExpiredDate = _U("ExpiredDate");
const UGString TrialLicense = _U("Trial License");
const UGString DeviceID = _U("DeviceID");
const UGString DeviceIDType = _U("DeviceIDType");
const UGString LicCode = _U("LicCode");

//定义许可头
#define LICENSE_HEADER _U("SuperMapiMoble2012") // 加密的混淆字符，单词故意写错的

//定义许可文件名后缀
#define SINGLE_LICENSE_EX _U(".slm")
#define GROUP_LICENSE_EX _U(".sglm")

#define LICENSE_LINE_END _U("\r\n")

//设备号长度
#define DEVICEID_LENGTH 16
//密钥长度
#define KEY_LENGHT 32

class TOOLKIT_API UGPermission  
{
public:
	UGPermission();
	virtual ~UGPermission();

public:
	 static UGString GetDeviceID();

	 static UGbool SetDeviceMacAddress(UGString macAddress);

	 static UGString GetLicensePath();

	 static UGbool SetLicensePath(UGString strAppPath);

private:
	static UGString mDeviceID;

	//许可路径
	static UGString mLicensePath;

	//当前机器的原始的设备号，即直接从硬件获取到得设备号
	static UGString mOrginalDeviceID;
};

class TOOLKIT_API UGLicenseManager
{
public :
	UGLicenseManager();
	~UGLicenseManager();

public:
	//验证许可是否可用
	 UGbool isRegister();
	
	//验证模块是否可用
	 UGbool isModuleValid(UGulong module);

	//是否是试用许可可用
	 UGbool isTrailValid();

	 //是否是使用许可
	 UGbool isTrail();

	 //许可是否存在
	 UGbool isLicenseExsit();

	 //获取版本
	 UGlong GetVersion();

	 //获取许可开始时间
	 UGTime GetStartDate();

	 //获取许可终止时间
	 UGTime GetExpireDate();

	 //通过注册码验证许可
	 //! \brief 当验证成功后会在许可路径下直接生成单机许可文件
	 UGbool VerifyLicenceCode(UGString licCode,UGString& errMsg);

	
private:
	//是否是集团许可
	UGbool isGroupLicense();

	//验证时间是否正确
	UGbool isTimeValid();

	//验证版本
	UGbool isVersionValid();

	//读取许可
	UGbool ReadLicenseData();

	//从集团许可中成单机许可
	UGbool CreateSingleLicense();

	//从许可路径下找到许可文件,没有找到则为false,找到为true
	UGbool FindLincenseFile();

private:
	//试用许可
	UGbool mIsTrailValid;

	UGbool mIsRegister;

	UGbool mIsTimeValid;

	UGbool mIsVersionValid;

	//模块信息编码
	UGulong mModulesCode;

	//读取的模块信息编码
	UGString mStrModulesCode;;

	//版本编码
	UGString mStrVersionCode;

	//开始时间
	UGString mStrStartDate;

	//结束时间
	UGString mStrEndDate;

	//用户序列号
	UGString mUserSerialID;

	//硬件码
	UGString mStrDeviceID;

	//读取的许可码
	UGString mStrLicenseCode;

	//是否是试用许可
	UGbool mIsTrailLicense;

	//只读一次文件
    static UGbool mHasReadLicense;

	//许可文件
	UGString mLicenseFile;
};

extern TOOLKIT_API UGLicenseManager g_LicenseManager;

}//namespace UGC

#endif //#ifndef UGPERMISSION_HEADER_FOR_OBJECTS_EMBEDED