#if !defined(__UGC_ENGINEBAIDUMAPS_H__)
#define __UGC_ENGINEBAIDUMAPS_H__

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


#ifdef _DEBUG
	#pragma message("自动连接动态库 SuEngineBaiduMapsd.sdx ...")
	#pragma comment(lib,"SuEngineBaiduMapsd.lib") 

#else
	#pragma message("自动连接动态库 SuEngineBaiduMaps.sdx ...") 
	#pragma comment(lib,"SuEngineBaiduMaps.lib") 
#endif

#endif //__UGC_ENGINEWEBMAP_H__