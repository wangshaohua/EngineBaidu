// UGMapCacheState.h: interface for the UGMapCacheState class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_UGMAPCACHESTATE_H__658CE52F_FD8E_430D_B5E0_DAC4EAF29F51__INCLUDED_)
#define AFX_UGMAPCACHESTATE_H__658CE52F_FD8E_430D_B5E0_DAC4EAF29F51__INCLUDED_

#include "Stream/ugdefs.h"

namespace UGC
{

class CACHEFILE_API UGMapCacheState  
{
public:
	UGMapCacheState();
	~UGMapCacheState();
	
	//! \brief 更新现存图片总数
	void UpdateExistImageCount();

	//! \brief 获取当前缓存状态开始时间
	void StartTime();

	//! \brief 获取当前缓存状态结束时间
	void EndTime();

	//! \brief 当前缓存地图的比例尺
	UGdouble m_dScale;

	//! \brief caption
	UGString m_strCaption;

	//! \brief 前比例尺的缓存图片总数。这个是根据地图缓存输出范围和单张图片地理范围计算出的。
	UGint m_nImageCount;

	//! \brief 当前比例尺的缓存实际存在的缓存图片总数。这个是所有需要生成的缓存图片减去无内容的图片，即那些与当前地图范围、裁剪范围没有交集的图片的数目。
	UGint m_nExistImageCount;

	//! \brief 当前缓存状态的HashCode
	UGString m_strHashCode;

	//! \brief 缓存开始时间
	UGTime m_startTime;

	//! \brief 缓存结束时间
	UGTime m_endTime;

	////! \brief 还未缓存图片总数
	//UGint m_nNotImageCount;


	// UGC 缓存策略专用
	//int m_nXLevel;
	//int m_nYLevel;


};

}

#endif // !defined(AFX_UGMAPCACHESTATE_H__658CE52F_FD8E_430D_B5E0_DAC4EAF29F51__INCLUDED_)

