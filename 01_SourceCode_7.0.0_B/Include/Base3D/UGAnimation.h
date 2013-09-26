//////////////////////////////////////////////////////////////////////////
//                    _   _   ____   ____                    
//   Project         | | | | / ___) / ___)                   
//                   | | | || | __ | |                       
//                   | |_| || |_\ || \___                    
//                    \____/ \____| \ ___)     6.0           
//                                                           
//!  \file headerfile.h
//!  \brief 
//!  \details 
//!  \author zhangshuai。
//!  \attention 
//!   Copyright (c) 1996-2010 SuperMap Software Co., Ltd. <br> 
//!   All Rights Reserved.
//!  \version 6.0
//////////////////////////////////////////////////////////////////////////
#if !defined(AFX_UGANIMATION_H__E89D0670_EB32_4782_8964_7F60F1421BCF__INCLUDED_)
#define AFX_UGANIMATION_H__E89D0670_EB32_4782_8964_7F60F1421BCF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Base3D/UGPrerequisites3D.h"
#include "Stream/UGStream.h"
namespace UGC
{

class BASE3D_API UGAnimation
{
public:
	UGAnimation();
	//! \brief 构造函数
	//! \param strAnimName 动画名称[in]。
	//! \param dTimePos 当前动画的位置[in]。
	//! \param dTimePos 当前动画的长度[in]。
	//! \param dTimePos 是否启动动画，初始为false不启用[in]。
	UGAnimation(const UGString& strAnimName,UGdouble dTimePos, UGdouble dLength,UGbool bEnabled = false);

	//! \brief 拷贝构造函数
	UGAnimation(const UGAnimation &rhs);

	//! \brief 析构函数
	virtual ~UGAnimation();

	//! \brief 重载==
	UGbool operator==(const UGAnimation& rhs) const;
	
	//! \brief 重载!=
	UGbool operator!=(const UGAnimation& rhs) const;

	//! \brief 从流文件中加载
	void Load(UGStream& fStream);

	//! \brief 存入流文件中
	void Save(UGStream& fStream);

	//! \brief 获得结点的大小
	UGint GetDataSize() const;

public:
	//! \brief 动画名称
	const UGString& GetAnimationName() const;

	//! \brief 获取动画位置
	UGdouble GetTimePosition(void) const;

	//! \brief 设置动画位置
	//! \param dTimePos 当前动画的位置[in]。
	void SetTimePosition(UGdouble dTimePos);

	//! \brief 获取动画长度
	UGdouble GetLength() const;

	//! \brief 设置动画长度
	void SetLength(UGdouble dLen);

	//! \brief 更新动画位置，在当前位置上加上dOffset
	//! \param dOffset 动画时间增加的值[in]。
	void Update(UGdouble dOffset);

	//! \brief 当前动画是否已结束，当loop为true，返回始终为true
	UGbool HasEnded(void) const;

	//! \brief 获得当前动画是否可用的标识
	//! \return 。
	UGbool GetEnabled(void) const;

	//! \brief 设置动画是否可用的标识
	//! \param bEnabled 为true为当前动画可用[in]。
	//! \return 。
	void SetEnabled(UGbool bEnabled);

	//! \brief 设置是否循环播放
	//! \param bLoop 为true为循环播放[in]。
	//! \return 。
	void SetLoop(UGbool bLoop) { m_bLoop = bLoop; }

	//! \brief 获取循环播放标识
	//! \return
	UGbool GetLoop(void) const { return m_bLoop; }

	//! \brief 设置是否自动更新时间
	void SetAutoUpdated(UGbool autoupdate);	

	//! \brief 获得是否自动更新标识
	UGbool IsAutoUpdated(void) const;

	//! \brief 起始时间
	//! \param dStartTime 设置动画起始播放的时间[in]。
	void SetStartTime(UGdouble dStartTime);

	//! \brief 获得起始动画时间
	UGdouble GetStartTime(void);

	//! \brief 终止时间
	//! \param dEndTime 设置动画结束播放的时间[in]。
	void SetEndTime(UGdouble dEndTime);

	//! \brief 获得起始动画时间
	UGdouble GetEndTime(void);

private:
	//! \brief 动画名称
	UGString m_strAnimationName;
	
	//! \brief 动画位置
	UGdouble m_dTimePos;

	//! \brief 动画长度
	UGdouble m_dLength;

	//! \brief 是否可用
	UGbool m_bEnabled;

	//! \brief 是否循环播放
	UGbool m_bLoop;

	//! \brief 是否自动Update
	UGbool m_bAutoUpdate;

	//! \brief 起始时间
	UGdouble m_dStartTime;

	//! \brief 结束时间
	UGdouble m_dEndTime;
};
}
#endif // !defined(AFX_UGANIMATION_H__E89D0670_EB32_4782_8964_7F60F1421BCF__INCLUDED_)

	
	
