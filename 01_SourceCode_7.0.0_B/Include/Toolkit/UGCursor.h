/*!  \file	 UGCursor.h
*  \brief	 光标类
*  \author	 zengzm
*  \attention 
*  Copyright(c) 2000-2010 SuperMap Software Co., Ltd.<br>
*  All Rights Reserved
*/


#if !defined(AFX_UGCURSOR_H__BA0D55BD_3573_442B_B4B5_6FF977F71203__INCLUDED_)
#define AFX_UGCURSOR_H__BA0D55BD_3573_442B_B4B5_6FF977F71203__INCLUDED_

#include "Stream/ugdefs.h"

namespace UGC {


//! \brief 光标类
class TOOLKIT_API UGCursor  
{
public: 
	//! \brief 光标类型
	enum Type
	{
	  //!  \brief Toolkit
		Wait // 等待
		// 其他以后有需要再增加
	};

public:
	//! \brief 构造函数, 设置指定类型的光标
	//! \param pNative Graphics的Native指针，Cursor在显示的时候需要使用
	//! \param eType 光标的类型,目前仅支持等待光标
	UGCursor(void* pNative, Type eType=Wait);
	//! \brief 析构函数, 恢复原有光标
	~UGCursor();

	//! \brief 手动恢复原有光标
	void Restore();

private:
	void* m_handlePrev;
	void* m_pGraphicsNative;

};

}

#endif // !defined(AFX_UGCURSOR_H__BA0D55BD_3573_442B_B4B5_6FF977F71203__INCLUDED_)

