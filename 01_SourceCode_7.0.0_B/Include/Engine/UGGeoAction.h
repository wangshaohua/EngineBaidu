#ifndef UGGEOACTION_H
#define UGGEOACTION_H

#include "Engine/UGEngDefs.h"

namespace UGC {
class ENGINE_API UGGeoAction
{
public:
	UGGeoAction();
	~UGGeoAction();

	enum UGActionType
	{
		atNone,		//无动作
		atOffset,		//平移
		atInflate,	//缩放
		atRotate,		//旋转
		atDelete,		//删除

	};//动作类型

public:
	//! \brief获取动作类型
	UGActionType GetType() const {return m_eType;}

protected:
	UGActionType m_eType;
};

class ENGINE_API UGOffsetAction : public UGGeoAction
{
public:
	UGOffsetAction();
	//！ \brief二维移动
	UGOffsetAction(UGdouble dX, UGdouble dY);
	//！ \brief三维移动
	UGOffsetAction(UGdouble dX, UGdouble dY, UGdouble dZ);
	~UGOffsetAction();
public:
	//! \brief X方向偏移值
	UGdouble m_dOffsetX;
	//! \brief Y方向偏移值
	UGdouble m_dOffsetY;
	//! \brief Z方向偏移值
	UGdouble m_dOffsetZ;
};

class ENGINE_API UGRotateAction : public UGGeoAction
{
public:
	UGRotateAction();
	//！ \brief二维旋转
	UGRotateAction(UGPoint2D pnt, UGdouble dAngle);
	//！ \brief三维旋转
	UGRotateAction(UGPoint3D pnt, UGdouble dAngle);
	~UGRotateAction();
public:
	//! \brief 基准点X坐标
	UGdouble m_dCenterX;
	//! \brief 基准点X坐标
	UGdouble m_dCenterY;
	//! \brief 基准点X坐标
	UGdouble m_dCenterZ;
	//! \brief 旋转角度
	UGdouble m_dAngle;
};

class ENGINE_API UGInflateAction : public UGGeoAction
{
public:
	UGInflateAction();
	//！ \brief二维缩放
	UGInflateAction(UGdouble dXRatio, UGdouble dYRatio);
	//！ \brief三维缩放
	UGInflateAction(UGdouble dXRatio, UGdouble dYRatio, UGdouble dZRatio);
	~UGInflateAction();
public:
	//! \brief X方向缩放比例
	UGdouble m_dRatioX;
	//! \brief Y方向缩放比例
	UGdouble m_dRatioY;
	//! \brief Z方向缩放比例
	UGdouble m_dRatioZ;
};

class ENGINE_API UGDeleteAction : public UGGeoAction
{
public:
	UGDeleteAction();
	~UGDeleteAction();
};

}
#endif
