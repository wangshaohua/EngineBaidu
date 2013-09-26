// UGGeoLineM.h: interface for the UGGeoLineM class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_UGGEOLINEM_H__4D04C30B_CF4B_411E_A107_6ABEE27A07C7__INCLUDED_)
#define AFX_UGGEOLINEM_H__4D04C30B_CF4B_411E_A107_6ABEE27A07C7__INCLUDED_

#include "Geometry/UGGeometry.h"
#include "Geometry/UGGeoPoint.h"

namespace UGC {

#define UG_NO_MEASURE -9999 //无值的数
//! \brief用于对插入LineM的点的排序
	typedef struct tagMeasurePointInfo 
	{
		UGlong nIndex;
		UGlong nIndexOld;
		UGdouble dDistance;
		UGint nError;
		UGbool flag;
	}MeasurePointInfo;

	//!brief 如何计算M值的枚举

//! \brief GeoLineM对象(路由对象),和GeoLine对象最大的区别在于每个点都有一个M值,用来表达Measure的含义
//! \remarks GeoLineM现在内部用的是Point3D,即用z来代表M; GeoLineM主要用于动态分段和网络分析结果的表达
class GEOMETRY_API UGGeoLineM : public UGGeometry  
{
public:
	//! \brief 构造函数
	UGGeoLineM();
	//! \brief 析构函数
	virtual ~UGGeoLineM();

	//add by shuxl	09.6.16
	UGGeoLineM( const UGGeoLineM &otherLineM);
	
public:
	//! \brief 清空地理数据
	virtual void Clear();
	
	//! \brief 得到维度, 固定为1
	//! \return 得到维度,固定为1g
	virtual UGint GetDimension() const;

	//! \brief 得到类型, 固定为 GeoLineM
	virtual Type GetType() const;
	
	//! \brief 得到内点（在Geometry内部，靠近中央的点）
	//! \remarks 为点数最多的子对象 的中间点(中间个数的点, 而不是中间距离的点)
	virtual UGPoint2D GetInnerPoint() const;
	
	//! \brief 得到对象长度,不包括间距
	//! \return 返回长度	
	virtual UGdouble GetLength() const;
	
	//! \brief 点击测试, 用于对象点选
	//! \param pntHitTest 用来测试选中的点
	//! \param dTolerance 容限
	//! \return 选中返回true, 否则返回false
	virtual UGbool HitTest( const UGPoint2D &pntHitTest, UGdouble dTolerance) const;
	
	//! \brief 得到空间数据, 主要用于需要按照维度相同时
	//! 来做统一处理的时候, 例如一些空间判断和操作的算法
	//! \param pPoints 传出的点坐标数组[out]。
	//! \param pPolyCount 传出的每个子对象点个数的数组[out]。
	//! \param nSubCount 传出的子对象个数[out]。
	//! \param nSegmentCount 对参数化对象, 每个弧段分割点的个数[in]。
	//! \remarks 参数采用了智能指针的技术,调用者不用释放内存空间
	//! \return 成功返回true,否则返回false。
	virtual UGbool GetSpatialData( UGAutoPtr<UGPoint2D>& pPoints, 
		UGAutoPtr<UGint>& pPolyCount, UGint& nSubCount, UGint nSegmentCount=0) const;
	
	//! \brief 得到子对象的个数
	//! \return 返回子对象的个数
	virtual UGint GetSubCount() const;
	
	//! \brief 几何对象是否有效
	//! \return 有效返回true,无效返回false
	virtual UGbool IsValid()const;
	
	//! \brief 缩放
	//! \param dRatioX X方向缩放比率
	//! \param dRatioY Y方向缩放比率
	//! \param dRatioM M值的缩放比率
	void Inflate(UGdouble dRatioX, UGdouble dRatioY, UGdouble dRatioM);
	
	//! \brief 缩放
	//! \param dRatioX X方向缩放比率
	//! \param dRatioY Y方向缩放比率
	//! \remarks M无缩放
	virtual void Inflate( UGdouble dRatioX, UGdouble dRatioY);
	
	//! \brief 缩放
	//! \param dRatio 缩放比率(X,Y,M相同)
	virtual void Inflate( UGdouble dRatio);
	
	//! \brief 平移
	//! \param dX 平移的X偏移量
	//! \param dY 平移的Y偏移量
	virtual void Offset( UGdouble dX, UGdouble dY);
	
	//! \brief 平移
	//! \param 偏移量(X,Y方向相同)
	virtual void Offset( UGdouble dOffset);
	
	//! \brief 平移
	//! \param 平移的偏移量(分别用UGSize2D中的x,y代表X,Y方向的偏移量)
	virtual void Offset( const UGSize2D &szOffset);
	
	//! \brief 旋转
	//! \param pntOrigin 旋转的中心点(锚点,不动点)
	//! \param dAngle 旋转角度
	virtual void Rotate(const UGPoint2D& pntOrigin, UGdouble dAngle);
	
	//! \brief 旋转,增加一些参数,以便内部可以不用进行cos,sin, 在批量处理的时候有利于提高效率
	//! \remarks dAngle看似多余,但GeoText需要,所以要保留
	//! \param pntOrigin 旋转的中心点(锚点,不动点)
	//! \param dCosAngle 旋转的cos值
	//! \param dSinAngle 旋转的sin值
	//! \param dAngle 旋转角度
	virtual void Rotate( const UGPoint2D& pntOrigin, UGdouble dCosAngle, UGdouble dSinAngle, UGdouble dAngle = 0);
	
	//! \brief 调整几何数据,限定在新的Bounds中
	//! \param rcNewBounds 新的,限定范围的Bounds
	//! \return 成功返回true,失败返回false
	virtual UGbool Resize(const UGRect2D& rcNewBounds); 
	
	virtual UGint GetDataSize() const;

public:	
	//! \brief 根据投影转化器的设置和转化方向要求, 进行投影转化
	//! \param pPJTranslator 投影转化器
	//! \param bForward 转化方向, true代表从UGRefTranslator的源(Src)转化到目的(Des), false则相反
	virtual void PJConvert( UGRefTranslator *pPJTranslator, UGbool bForward = true);
	
	//! \brief 从经纬坐标系统转化为投影坐标系统
	//! \param pCoordSys 投影坐标系统
	virtual void PJForward( UGPrjCoordSys *pCoordSys );

	//! \brief 从投影坐标系统转化为经纬坐标
	//! \param pCoordSys 投影坐标系统
	virtual void PJInverse( UGPrjCoordSys *pCoordSys );
	
public:
	
	//! \brief 拷贝构造GeoLineM
	//! \param geolineM [in] 已有LineM对象。
	//! \return 已有线对象非法, 返回false。
	UGbool Make( const UGGeoLineM& geoLineM);
	
	//! \brief 构造一个子对象的GeoLineM
	//! \param pPoints [in] 点串指针。
	//! \param nPntCount [in] 点串的点数目。
	//! \return 点数小于2个,返回false。
	UGbool Make( const UGPoint3D* pPoints, UGint nPntCount );
	
	//! \brief 构造多个子对象的复杂GeoLineM
	//! \param pPoints [in] 点串指针。
	//! \param pPolyCount [in] 子对象中点数的数组。
	//! \param nSubCount [in] 子对象数目。
	//! \return 所有子对象的点数都小于2个,返回false。
	virtual UGbool Make( const UGPoint3D* pPoints, const UGint* pPolyCount, UGint nSubCount );

	//! \brief 在最后增加一个子对象。
	//! \param pPoints [in] 点串指针。
	//! \param nPntCount [in] 点串的点数目。
	//! \return 点串个数小于2个, 返回false。
	UGbool AddSub( const UGPoint3D* pPoints, UGint nPntCount );
	
	//! \brief 插入子对象。
	//! \param nIndex [in] 要插入的位置索引。
	//! \param pPoints [in] 点串指针。
	//! \param nPntCount [in] 点串中点的个数。
	//! \return 点个数小于2或者索引位置非法,返回false。
	UGbool InsertSub(UGint nIndex, const UGPoint3D* pPoints, UGint nPntCount);
	
	//! \brief 删除子对象。
	//! \param nIndex [in] 要删除的子对象的位置索引。
	//! \return 索引非法, 返回false。
	UGbool DelSub( UGint nIndex );
	
	//! \brief 在指定的位置上设置点的坐标。
	//! \param nIndex [in] 位置索引。
	//! \param point [in] 点坐标。
	//! \return 索引非法, 返回false。
	//! \remarks 所有子对象的点在一个整体的数组中, 本函数没有区分子对象, 从头开始计算索引。
	UGbool SetPoint( UGint nIndex, const UGPoint3D& point );
	
	//! \brief 得到子对象数目的数组指针。
	//! \return 返回子对象数目的数组指针。
	const UGint* GetPolyCounts() const;
	
	//! \brief 得到某个子对象的点的个数。
	//! \param nSubIndex [in] 子对象索引。
	//! \return 返回某个子对象的点的个数。
	UGint GetSubPntCount(UGint nSubIndex) const;
	
	//! \brief 得到所有子对象的点的个数总和。
	//! \return 返回所有子对象的点的个数总和。
	UGint GetPointCount() const;
	
	//! \brief 得到指定子对象的点串的指针。
	//! \param nSubIndex [in] 子对象索引。
	//! \return 返回子对象的点串的指针。
	const UGPoint3D* GetPoints(UGint nSubIndex=0) const;
	
	//! \brief 得到指定Index对象的点
	//! \param Index对象索引
	//! \return 失败返回false
	UGPoint2D GetPointAtIndex(const UGint Index=0);
	UGbool GetPointAtIndex( UGPoint2D &point2d,const UGint Index=0);

	//! \brief 判断刻度值是否在对象路由范围内
	//! \param measure刻度值
	//! \return 在路由上返回true，不在返回false
	UGbool IsMOnLineMSect(UGdouble dMeasrue);
	
public:
	enum UGWhereToComputeM
	{
		//! 不去计算
		NotToComputeM = 0,  
		//! 只外推起点之前的Section
		ExtropolateBefore = 1,   
		//! 只外推终点之后的Section
		ExtropolateAfter  = 2,   
		//! 内插两点之间的控制点
		Interpolate		= 4    
	};

	//! 单调性的枚举
	enum UGMonotonicStyle
	{
		//! 单调递增
		MeasureAscending   = 0,   
		//! 单调递减
		MeasureDescending	 =1,    
		//! 非单调
		MeasureNotMonotonic=2     
	};

	//!brief M值得计算方法
	enum UGCalibrateBy
	{
		//! 按距离计算
		ByDistance = 1,		
		//! 按线标计算
		ByMeasure  = 2		
	};
	
	/*! \brief 内插Measure modified by shanqc 2010-12-31
	*  \param nFromIndex   起始点索引
	*  \param nToIndex     终止点索引
	*  \param nFromSubObjID 起始子对象ID
	*  \param nToSubObjID   终止子对象ID
	*  \param bIgnoreGap    是否忽略子对象之间的间隔
	*  \return 内插计算成功返回True,否则返回False
	*  \remarks 
	1、如果nFromSubObjID小于nToSubObjID,程序会把起始和终止子对象的ID调换。
	   也就是说，较小的ID总是作为起始对象。
	2、如果起始子对象和终止子对象之间的所有对象依次首尾相连，程序可以把
	   它们作为一段线来内插。否则程序根据bIgnoreGap是否为真，来决定如何在子对象之间内插。
	3、以前只处理所有子对象依次首尾相连的情况，如果子对象之间有间隔，暂时不处理，现在都能处理
	4、这里的nFromIndex和nToIndex为子对象上的点序号索引，因此需要推算在整条线路上的索引
	*/
    GEOMETRY_APIF UGbool InterpolateMeasure(UGuint nFromIndex, UGuint nToIndex,
											UGuint nFromSubObjID =0,UGuint nToSubObjID =0,
											UGCalibrateBy calibrateby=ByDistance,UGbool bIgnoreGap = FALSE);

	/*! \brief 内插Measure added by shanqc 2010-12-31
	*  \param pntFrom		起始点
	*  \param pntTo			终止点
	*  \param nFromMeasure  起始点里程值
	*  \param nToMeasure    终止点里程值
	*  \param tolerance     容限
	*  \param calibrateby   计算方法：距离还是里程值
	*  \return 内插计算成功返回True,否则返回False
	*  \remarks 
	1、如果点在线上，而不是原来几何信息的点，则插入
	2、只要一个点不在线上就返回False
	3、以前子对象之间有间隔，则不忽略，现在根据bIgnoreGap是否为真来决定
	*/
	GEOMETRY_APIF UGbool InterpolateMeasure(UGPoint2D pntFrom, UGPoint2D pntTo,
											UGdouble nFromMeasure,UGdouble nToMeasure, 
											UGdouble tolerance,UGCalibrateBy calibrateby,UGbool bIgnoreGap = FALSE);
	/*! \brief 外推Measure
	*  \param nExtropolateStyle  外推方式
	*  \param nFromIndex		 子对象起始点索引
	*  \param nToIndex			 子对象终止点索引
	*  \param nFromSubObjID		 起始子对象ID
	*  \param nToSubObjID		 终止子对象ID
	*  \param bIgnoreGap		 是否忽略子对象之间的间隔
	*  \return 外推计算成功返回True,否则返回False
	*  \remarks
	1、如果nFromSubObjID小于nToSubObjID,程序会把起始和终止子对象的ID调换。
	   也就是说，较小的ID总是作为起始对象。
    2、如果起始子对象和终止子对象之间的所有对象依次首尾相连，程序可以把
	   它们作为一段线来内插。否则程序根据bIgnoreGap是否为真，来决定如何在子对象之间内插。
	3.这里的nFromIndex和nToIndex为子对象上的点序号索引，因此需要推算在整条线路上的索引
	*/
	GEOMETRY_APIF UGbool ExtrapolateMeasure(UGuint nFromIndex,UGuint nToIndex ,
											UGWhereToComputeM nExtropolateStyle = ExtropolateBefore,
											UGuint nFromSubObjID =0,UGuint nToSubObjID =0, UGbool bIgnoreGap = FALSE);
/*! \brief 外推Measure added by shanqc 2010-12-31
	*  \param pntFrom		起始点
	*  \param pntTo			终止点
	*  \param nFromMeasure  起始点里程值
	*  \param nToMeasure    终止点里程值
	*  \param tolerance     容限
	*  \param calibrateby   计算方法：距离还是里程值
	*  \param bIgnoreGap    是否忽略子对象之间的间隔
	*  \return 外推计算成功返回True,否则返回False
	*  \remarks 
	1、如果点在线上，而不是原来几何信息的点，则插入
	2、只要一个点不在线上就返回False
	3、如果子对象之间有间隔，可设定是否忽略
	*/
	GEOMETRY_APIF UGbool ExtrapolateMeasure(UGPoint2D pntFrom, UGPoint2D pntTo,
											UGdouble nFromMeasure,UGdouble nToMeasure, 
											UGdouble tolerance,UGCalibrateBy calibrateby,UGbool bIgnoreGap = FALSE);
	
	/*! \brief 重新计算线标
	  *  \param nFromIndex   起始点索引
	  *  \param nToIndex     终止点索引
	  *  \param dFromM
	  *  \param dToM 
	  *  \param nHowToComputeMeasure
	  *  \param nCalibrateBy
	  *  \param nFromSubObjID 起始子对象ID  现在还没有用到
	  *  \param nToSubObjID   终止子对象ID  现在还没有用到
	  *  \param bIgnoreGap    是否忽略子对象之间的间隔
	  *  \return 更新成功返回True,否则返回False
	  *  \remarks
	  1、如果nFromSubObjID小于nToSubObjID,程序会把起始和终止子对象的ID调换。
	  也就是说，较小的ID总是作为起始对象。
	  2、如果起始子对象和终止子对象之间的所有对象依次首尾相连，程序可以把
	  它们作为一段线来计算。否则程序根据bIgnoreGap是否为真，来决定如何在子对象之间内插。
	*/
	GEOMETRY_APIF UGbool UpdateMeasure(UGuint nFromIndex,UGuint nToIndex ,
					   UGdouble dFromM,UGdouble dToM, 	
					   UGWhereToComputeM nWhereToComputeMeasure = Interpolate,
					   UGCalibrateBy nCalibrateBy = ByDistance,
					   UGuint nFromSubObjID =0,UGuint nToSubObjID =0,UGbool bIgnoreGap = FALSE);

	/*! \brief 重新计算线标 added by shanqc 2011-01-09
	  *  \param pntFrom		起始点
	  *  \param pntTo		终止点
	  *  \param nFromMeasure
	  *  \param nToMeasure 
	  *  \param dTolerance
	  *  \param nHowToComputeMeasure
	  *  \param nCalibrateBy
	  *  \return 外推计算成功返回True,否则返回False
	  *  \remarks
	  1、如果nFromSubObjID小于nToSubObjID,程序会把起始和终止子对象的ID调换。
	  也就是说，较小的ID总是作为起始对象。
	  2、如果起始子对象和终止子对象之间的所有对象依次首尾相连，程序可以把
	  它们作为一段线来计算。否则程序根据bIgnoreGap是否为真，来决定如何在子对象之间内插。
	*/
	GEOMETRY_APIF UGbool UpdateMeasure(UGPoint2D pntFrom,UGPoint2D pntTo,
									   UGdouble dFromM,UGdouble dToM, UGdouble dTolerance,
									   UGWhereToComputeM nWhereToComputeMeasure = Interpolate,
									   UGCalibrateBy nCalibrateBy = ByDistance,UGbool bIgnoreGap = FALSE);

	/*! \brief 重新计算线标,计算指定点(需要先找到索引)到前面的点、后面的和点之间里程值
	  *  \param nIndex		 指定点索引
	  *  \param dMeasure     指定点里程值
	  *  \param nFromIndex   起始点索引
	  *  \param nToIndex     终止点索引
	  *  \param nCalibrateBy 计算方法：按距离还是里程来计算
	  *  \param dFromM		 起始点里程值
	  *  \param dToM		 终止点里程值
	  *  \remarks
	  1.把线路校正功能分解为三部分，更好利用代码，并提供更多方法
	  2.UpdateMeasureBefore，究竟是从首点M值变化到dMeasure还是从0变化到dMeasure？这是采用从首点M值变化到dMeasure
	  3.UpdateMeasureAfter，究竟是从dMeasure变化到未点M值还是从dMeasure按距离变化？这是采用从dMeasure变化到未点M值 
	*/
	UGbool UpdateMeasureBefore(UGuint nIndex,UGdouble dMeasure,UGCalibrateBy nCalibrateBy,UGbool bIgnoreGap= FALSE);
	UGbool UpdateMeasureAfter(UGuint nIndex,UGdouble dMeasure,UGCalibrateBy nCalibrateBy,UGbool bIgnoreGap = FALSE);
	UGbool UpdateMeasureInterval(UGuint nFromIndex,UGuint nToIndex,UGdouble dFromM,UGdouble dToM,
								 UGCalibrateBy nCalibrateBy,UGbool bIgnoreGap = FALSE);

	/*! \brief 重新计算线标,根据dRatio计算点前、后面的里程值，校正用
	  *  \param nIndex		 指定点索引
	  *  \param dMeasure     指定点里程值
	  *  \param dRatio		 计算比例:即M值变化与距离变化的比例
	  *  \remarks	  增加校正功能，更好利用代码，并提供更多方法与组合
	*/
	UGbool UpdateMeasureBefore(UGuint nIndex,UGdouble dMeasure,UGdouble dRatio,UGbool bIgnoreGap= FALSE);
	UGbool UpdateMeasureAfter(UGuint nIndex,UGdouble dMeasure,UGdouble dRatio,UGbool bIgnoreGap = FALSE);
	/*! \brief 线标平移
	*  \param dOffset   平移量
	*  \return 
	*  \remarks
	*/
	GEOMETRY_APIF void OffsetMeasure(UGdouble dOffset);	  
	
	/*! \brief 从距离得到线标
	*  \param  dDistance   距线段起点的距离
	*  \param  nSubObjID   起始子对象ID(组件从1开始，底层从0开始)
	*  \param  bIgnoreGap  是否忽略子对象之间的间隔
	*  \return 线标
	*  \remarks
	*/
	GEOMETRY_APIF UGdouble GetMAtDistance(UGdouble dDistance,UGbool bIgnoreGap);
	GEOMETRY_APIF UGdouble GetMAtDistance(UGdouble dDistance, UGint nStartSubObjID, UGbool bIgnoreGap);
	GEOMETRY_APIF UGdouble GetSubMAtDistance(UGdouble dDistance, UGuint nSubObjID);
	//	UGdouble GetMAtDistance_test(UGdouble dDistance, UGuint nSubObjID = 0);
	
	/*! \brief 从点坐标得到线标
	*  \param  resPoint    二维点
	*  \param  dMeasure    要返回的线标
	*  \param  dTolerance  容限
	*  \param  bIgnoreGap  是否忽略子对象之间的间隔
	*  \return 线标
	*  \remarks
	*/
	GEOMETRY_APIF UGbool GetMAtPoint(UGPoint2D resPoint, UGdouble &dMeasure, UGdouble tolerance , UGbool bIgnoreGap);

	GEOMETRY_APIF UGbool GetMsAtPoint(UGPoint2D resPoint, UGArray<UGdouble> &arrMeasure, UGdouble tolerance);

	/*! \brief 得到两个线标M(里程)之间的线路
	*  \param  geoLineM		返回线对象
	*  \param  dFromMeasure 起始线标
	*  \param  dToMeasure   终止线标
	*  \param  dOffset	    偏移量
	*  \param  bIgnoreGap   是否忽略子对象之间的间隔
	*  \return 线标
	*  \remarks
	*/
	GEOMETRY_APIF UGlong GetLineMAtM(UGGeoLineM& geoLineM, UGdouble dFromMeasure, UGdouble dToMeasure, 
									 UGdouble dOffset, UGbool bIgnoreGap= TRUE);
	
	/*! \brief 校正线路
	*  \param  pCbPoints	传入基准点
	*  \param  dFromMeasure 起始线标
	*  \param  nCalibrate   校正方法：距离还是里程
	*  \param  nComputeStyle校正方式
	*  \param  bIgnoreGap   是否忽略子对象之间的间隔
	*  \param  pErrorType   错误类型(目前为动态分段使用)
	*  \return 线标
	*  \remarks
	*/
	GEOMETRY_APIF UGbool Calibrate(UGPoint3D* pCbPoints,UGlong nPointsCount, UGCalibrateBy nCalibrate,
						  UGint nComputeStyle, UGbool bIgnoreGap,UGdouble dTolerance = EP,UGint* pErrorType = NULL);
	
	GEOMETRY_APIF void Empty();
	void q_MeasureSort(MeasurePointInfo *pData, UGlong nCount);

	/* \brief 在第 lSubObjID 个子对象的 lPointID 位置上添加 lPointCount 个点
	* \param  lSubObjID	目标子对象
	* \param  lPointID	目标位置
	* \param  pPoints		要添加的点坐标串
	* \param  lPointCount	要添加的点数
	* \return 
	* \note
	*/	
	GEOMETRY_APIF UGbool InsertPoints(UGint lSubObjID, UGint lPointID, UGPoint3D *pPoints , UGint lPointCount);
	GEOMETRY_APIF UGbool InsertPoint(UGint lSubObjID, UGint lPointID, UGPoint3D &pntPoint);
	/* \brief  在第 lSubObjID 个子对象上添加一个点
	* \param  lSubObjID	目标子对象
	* \param  pntPoint	要添加的点
	* \return 
	* \note
	*/
	GEOMETRY_APIF UGbool AddPoint(UGint lSubObjID ,UGPoint3D &pntPoint);
	GEOMETRY_APIF UGbool AddPoints(UGint lSubObjID ,UGPoint3D *pPoints , UGint lPointCount);

	/* \brief 得到子对象数组指针、子对象数量、子对象本身－线路
	* \param  nIndex   位置索引。
	* \param  geoLineM 子对象。
	* \return 索引非法, 返回false。
	*! \remarks 所有子对象的点在一个整体的数组中
	*/
	GEOMETRY_APIF const UGPoint3D * GetSubPointer(UGint nIndex);
	GEOMETRY_APIF UGlong GetSubPointCount(UGint nIndex);
	GEOMETRY_APIF UGbool GetSubLine(UGint lSubIndex, UGGeoLineM& geoLineM);

	GEOMETRY_APIF const UGPoint3D * GetPointer();

	/*! \brief  根据距离设置线标
	*  \param OriginM     起点Ｍ值
	*  \param dScale      比例放缩 
	*  \param bIgnoreGap  是否忽略子对象之间的间隔
	*  \return
	*  \remarks  原点pntOrigin指定了距离的起算位置。其他点的线标都以和原点的最短距离推算
	*/
	GEOMETRY_APIF void SetMAsDistance(UGdouble OriginM =0.0,UGdouble dScale = 1.0);//dOffset为起点Ｍ值
	GEOMETRY_APIF void SetMAsDistance(UGdouble OriginM ,UGdouble dScale ,UGbool bIgnoreGap);

	/*! \brief  根据点设置线标
	*  \param pPoints		点对象数组
	*  \param pMeasures		各个点的刻度数组
	*  \param nCount	    要完成的点数 
	*  \param pErrors	    每个点的错误返回值数组 
	*  \param dTolerance    容限 
	*  \param bIgnoreGap	是否忽略子对象之间的间隔
	*  \return
	*  \remarks  原点pntOrigin指定了距离的起算位置。其他点的线标都以和原点的最短距离推算
	*/
	GEOMETRY_APIF UGlong SetMByPoints(UGPoint2D* pPoints, UGdouble* pMeasures, UGlong nCount, UGlong* pErrors, 
		UGdouble dTolerance, UGbool bIgnoreGap);

	/*! \brief  根据点设置线标 added by shanqc 2010-12-28
	*  \param point3dSrc	三维点
	*  \param point2dSrc	二维点
	*  \param Px			点数的横坐标
	*  \param Py			点数的纵坐标
	*  \param MeasurZ		里程值
	*  \param bOnSegment=FALSE 如果在线段上，就改为TRUE
	*  \param whereToCompute重新计算M值：可设置点前或后
	*  \return	点不在线上时返回 -1，在线上时返回点的索引，如果在线段上，则插入并返回点索引
	*  \remarks 参考TransCAD线性参考的功能,对设定点前面的点进行从0到MeasurZ变化，后面的按距离增加
	*/
	GEOMETRY_APIF UGint SetMAtPoint(UGPoint2D point2dSrc, UGdouble MeasurZ, UGdouble dTolerenceSrc, 
									UGint whereToCompute,UGbool& bOnSegment);
	
	/*! \brief   从线标得到距离
	*  \param   dMeasure    线标
	*  \param   nSubObjID   子对象ID,有这个参数得到的距离是距子对象起点的距离，不是线路起点
	*  \param   bIgnoreGap  是否忽略子对象之间的间隔 
	*  \return  距离
	*  \remarks
	*/
	GEOMETRY_APIF UGdouble GetDistanceAtM(UGdouble dMeasure,UGuint nSubObjID,UGbool bIgnoreGap);
	GEOMETRY_APIF UGdouble GetDistanceAtM(UGdouble dMeasure,UGbool bIgnoreGap);
	
	/*! \brief  从线标得到坐标
	*  \param  dMeasure  线标
	*  \param  dOffset   点距线段的距离
	*  \param  pIndex    坐标点之前的线段控制点索引,返回值
	*  \param  bIgnoreGap是否忽略子对象之间的间隔
	*  \return
	*  \remarks 一个线标所对应的坐标点可能不止一个.程序按照子对象的存储顺序依次查找,返回第一个点
	*/
	GEOMETRY_APIF UGPoint2D GetCoordinateAtM(UGdouble dMeasure, UGdouble dOffset = 0.0, UGint* pIndex = NULL);
	GEOMETRY_APIF UGPoint2D GetCoordinateAtM2(UGdouble dMeasure, UGdouble dOffset, UGint* pIndex= NULL, UGbool bIgnoreGap= TRUE);
	//CPoint2D GetCoordinateAtM( double dMeasure, double dOffset = 0.0 , LONG* pIndex = NULL, BOOL bIgnoreGap = TRUE);
	
	/*! \brief从线标得到曲线
	*  \param   GeoLine		  结果曲线
	*  \param   dFromMeasure  起点的线标
	*  \param   dToMeasure    终点的线标
	*  \return
	*  \remarks
	*/
	GEOMETRY_APIF UGbool GetSubCurveAtM(UGGeoLine& GeoLine,UGdouble dFromMeasure,UGdouble dToMeasure);
	
	/*! \brief   推算无线标位置处的线标值
	*  \param  bIgnoreGap是否忽略子对象之间的间隔
	*  \return
	*  \remarks
	*/
	GEOMETRY_APIF void CaculateNoM(); 
	GEOMETRY_APIF void CaculateNoM(UGbool bIgnoreGap);
	
	/*! \brief   翻转线标
	*  \param 
	*  \return
	*  \remarks
	*/
	GEOMETRY_APIF UGbool ReversMOrder();      
		
	/*! \brief   得到最大线标值
	*  \param 
	*  \return
	*  \remarks
	*/
	GEOMETRY_APIF UGdouble GetMaxMeasure();
	
	/*! \brief  得到最小线标值
	*  \param 
	*  \return
	*  \remarks
	*/
	GEOMETRY_APIF UGdouble GetMinMeasure();
	
	/*! \brief   得到路线的单调性
	*  \param  
	*  \return
	*  \remarks
	*/
	GEOMETRY_APIF UGGeoLineM::UGMonotonicStyle GetMonotonicStyle();
	
	/*! \brief 合并线对象，构造成一个复杂线对象
	*  \param pGeoLineM 合并的线对象
	*  \return
	*  \attetion 尚未实现
	*/
	GEOMETRY_APIF UGbool Combination(UGGeoLineM *pGeoLineM );

	/*! \brief 合并线对象，构造成一个复杂线对象
	*  \param pGeoLine 合并的线对象
	*  \return
	*  \attetion 尚未实现
	*/
	GEOMETRY_APIF UGbool Combination(UGGeoLine* pGeoLine);
	
	/*! \brief  逆转坐标点的次序
	*  \return
	*  \remarks
	*/
	GEOMETRY_APIF UGbool Reverse();
	
	//! \brief 取地球上两点间的曲线(大圆)弧长
	//! \param dRadius 地球半径(单位为千米)
	//! \param nDistUnits 坐标系统中的距离单位
	//! \return 返回打球长度
	GEOMETRY_APIF UGdouble GetRadianDistance(UGdouble dRadius = 6371118, UGint nDistUnits = AU_METER);
	
	//! \brief 得到指定距离的点坐标。
	//! \param dDistance [in] 指定的距离。
	//! \return 返回符合条件的点坐标。
	GEOMETRY_APIF UGPoint2D GetPointAtDistance(UGdouble dDistance, UGbool bIsIgnoreGap = TRUE);	

	/*! \brief 得到指定刻度（里程）处的点对象。
	*  \param dDistance [in] 指定的距离。
	*  \param  dMeasure  线标
	*  \param  dOffset   偏移量
	*  \param  bIgnoreGap是否忽略子对象之间的间隔
	*  \return 返回符合条件的点对象，如果要得到点坐标，需要转换
	*/
	GEOMETRY_APIF UGlong GetPointAtM(UGGeoPoint& geoPoint, UGdouble dMeasure, 
									 UGdouble dOffset = 0.0,UGbool bIgnoreGap = TRUE);
	// 	UGlong GetPointAtM(UGGeoPoint& geoPoint, UGdouble dMeasure, UGdouble dOffset /* = 0::0 */);
	//	LONG GetPointAtM(CGeoPoint& geoPoint, double dMeasure, double dOffset = 0.0,BOOL bIgnoreGap = TRUE);

	//! \brief 裁减 支持LineM的裁剪功能，added by shanqc 2010-12-15
	//! \param pGeoSource 参加操作的几何对象指针, 不得为NULL
	//! \param pGeoClip   参加操作的几何对象指针, 不得为NULL
	//! \param pPoint3ds  裁剪后得到点串
	//! \param pPolyCount 子对象的点的个数 信息的整型数组
	//! \param nSubCount  子对象个数
	//! \attention        虽然是这个是UGGeoLineM，但也支持其它的对象，点面、点线、线线、线面、面面之间求交；
	//!					  点点之间求相同点; 结果规则：线面 = 线
	//! \return 如果结果为空,返回FALSE
	GEOMETRY_APIF UGbool ClipLineM(UGGeometry* pGeoSource,UGGeometry* pGeoClip, 
								   UGPoint3Ds* pPoint3ds,UGint*& pPolyCount, UGint& nSubCount);
	
	//! \brief 分离 把线路一分为二，支持LineM，added by shanqc 2010-12-15
	//! \param splitPoint	 分割点, 不得为NULL
	//! \param geolinemNew1  新生成对象１
	//! \param geolinemNew2  新生成对象２
	//! \attention 
	//! \return 成功返回TRUE,返回FALSE
	GEOMETRY_APIF UGbool SplitLineM(UGPoint2D splitPoint,UGGeoLineM*& geolinemNew1,UGGeoLineM*& geolinemNew2);

	//! \brief 点和线联合构造GeoLineM　　added by shanqc 2010-12-15
	//! \param pLinesSrc	[in] 线对象指针。
	//! \param pPoint3Ds	[in] 三维点数组。
	//! \param nPointCount	[in] 点数组的长度。
	//! \attention 需要外部先生成一个空对象，函数将修改空对象的内容，但组件不这样。
	//! \return  成功返回TRUE,返回FALSE。
	GEOMETRY_APIF UGbool Make(UGGeoLine* pLinesSrc,UGPoint3D* pPoint3Ds,UGint nPointCount);

	//! \brief 得到子对象长度 added by shanqc 2010-12-23
	//! \param SubID 子对象序号。
	//! \return 返回长度	
	GEOMETRY_APIF UGdouble GetSubLength(UGint SubIndex);

	GEOMETRY_APIF UGGeoLine GetLine();
#if PACKAGE_TYPE==PACKAGE_UGC
public:	
#if !defined (IOS) 
	//! \brief Geometry与Element的转换
	//! \param pElement,返回的pElement指针在函数内分配内存,外面负责删除，否则会有内存泄漏
	virtual UGbool ToElement(OgdcElement*& pElement)  const;

	//! \brief Geometry与Element的转换
	//! \param pElement,传入的Element，如果无法转换则返回False，否则返回True
	virtual UGbool FromElement(const OgdcElement* pElement);
#endif	
	//! \brief 两点镜像
	//! \param pntMirror1 构成镜面的第一个点
	//! \param pntMirror2 构成镜面的第二个点
	//! \return 成功返回true,失败返回false
	virtual UGbool Mirror(const UGPoint2D &pntMirror1, const UGPoint2D &pntMirror2);
	
	//! \brief 生成XML格式的信息
	//! \param versionType GML的版本
	//! \param nPace 缩进的空格数目,使得xml字符串更加易于人工阅读; 
	//! 主要用于如果返回的xml字符串是一个大标签中的一部分, 通过指定空格数目,可以使层次清晰
	//! \return 返回指定GML版本的xml字符串
	virtual UGString ToXML(GMLVersionType versionType, UGint nPace = 0) const;
	
	//! \brief 从XML字符串中生成Geometry
	//! \param strXML xml格式字符串
	//! \param versionType xml字符串的GML版本
	//! \return 返回指定GML版本的xml字符串
	virtual UGbool FromXML(const UGString& strXML, GMLVersionType versionType);

	//added by xielin ^_^ 编辑相关函数,把编辑和geometry统一
	
	//! \brief 获得编辑对象的句柄的数目
	//! \remarks 对于固定句柄对象为9包括了改变大小的8个控制点和一个旋转控制点
     virtual UGint  GetHandleCount();

	
	//nHandle:的值与控制点的关系如右图                         
	//									1---+   	  +--2    	+----3	
	//                                      |         |         |  
	//                                      |         |         |  
	//										x---------x---------x     9
    //										|   ____________    |     |
    //										|  /            \   | x---+
	//									4---x |              |  x-----5
	//										|  \____________/   |
	//										|                   |
	//										x---------x---------x
	//										|		  |         |
	//										|		  |         |
	//								    6---+         +-----7   +-----8
	
	//! \brief 根据句柄获得相应控制点的值
	//! \param nHandle 控制点句柄
	//! \param point 句柄对应的控制点的坐标值
	//! \return 返回辅助点的类型
	 virtual UGint GetHandle( UGint nHandle, UGPoint2D& point);


	//! \brief 移动控制点到指定坐标,主要用于绘制对象，修改对象节点等操作
	//! \param nHandle 控制点句柄
	//! \param point 控制点坐标
	virtual void MoveHandle(UGint nHandle, const UGPoint2D& pnt2D,
							UGEditType::EditToolShape nEditType=UGEditType::ET_Default);

	//! \brief 节点编辑时可用来插入一个控制点,也可以用于绘制对象时加入节点
	//! \param nHandle 插入位置
	//! \param pnt2D 插入点的地理坐标
	virtual void AddHandle(UGint nHandle, const UGPoint2D& pnt2D,
						   UGEditType::EditToolShape nEditType=UGEditType::ET_Default);
	
	//! \brief 删除编辑对象的指定节点
	//! \param nHandle 节点句柄
     virtual UGuint DelNode( UGint nHandle );

	//! \brief 计算对象绘制时的辅助线，返回的是一个复合对象
	//! \param pPoints 点串
	//! \param nPntCount  点的个数
	//! \param nEditType 绘制对象的类型，参考UGEditType
	//! \param pStyle	 辅助线的风格，如果传入为NULL，用默认的风格
     virtual UGGeometry*  CalAssistantLine(const UGPoint2D* pPoints, UGint nPntCount,
										   UGEditType::EditToolShape nEditType,UGStyle* pStyle=NULL);

	//! \brief 计算对象绘制时的辅助点，返回的是点的数目,nHandleType返回的是辅助点的类型,参考UGEditType::EditHandleType
	//! \param pPoints 点串
	//! \param nPntCount  点的个数
	//! \param eAssistantPoints 点串,返回的辅助点点串
	//! \param nEditType 绘制对象的类型，参考UGEditType
	void CalAssistantPoints(const UGPoint2D* pPoints,UGint nPntCount,
							UGArray<UGEditType::EditAssistantPoint>& eAssistantPoints,
							UGEditType::EditToolShape nEditType);



	//! \brief 根据传入的点串生成对象，主要用于编辑中的参数化等没有内部数组保存点串的对象，
	//	也用于自定义对象,对于有内部数组保存点串的对象，该函数直接return既可，比如GeoLine
	//	GeoLine等对象就直接用AddHandle来生成，效率比较高,但是如果画平行线，就用它来生成
	//! \param pPoints 点串
	//! \param nPntCount  点的个数
     virtual void MakeWithPoints(UGPoint2D* pPoints,UGint nPntCount,
								 UGEditType::EditToolShape nEditType=UGEditType::ET_Default);

	//下面这个函数以后可能要用　commented by shanqc 2010-12-13
	// virtual void MakeWithPoints(UGPoint3D* pPoints,UGint nPntCount,UGEditType::EditToolShape nEditType=UGEditType::ET_Default);
	//! \brief 获取对象需要捕捉的点串
	//! \param aryPnts 点串，传出去的要捕捉的点串
	//! \return 如果是true表示有需要捕捉的点串，如果返回false表示该对象没有需要捕捉的点串
	virtual UGbool GetSnapPoints(UGArray<UGPoint2D>& aryPnts);

	//! \brief 获取对象需要捕捉的线段数组
	//! \param aryLines 需要捕捉的线数组（如果有多个part，那么aryLines就应该有多少个count）
	//! \return 如果是true表示有需要捕捉的线，如果返回false表示该对象没有需要捕捉的线
	virtual UGbool GetSnapLines(UGLineArray& aryLines);
	 
	 //added by xielin ^_^ 编辑相关函数,把编辑和geometry统一 end


#endif // end declare ugc sdk
	
protected: //! 子类需要实现的一些不公开函数
	virtual UGRect2D ComputeBounds() const;
	
	/*virtual UGRect2D GetBoundsInside() const;
	
	virtual void SetBoundsInside(const UGRect2D & rcBounds);*/
	
	//! \brief 存储到Stream中
	virtual UGbool SaveGeoData(UGStream& stream, UGDataCodec::CodecType eCodecType,UGbool bSDBPlus = FALSE)  const;
	
	//! \brief 从Stream中生成Geometry
	virtual UGbool LoadGeoData( UGStream& stream , UGDataCodec::CodecType eCodecType = UGDataCodec::encNONE ,UGbool bSDBPlus = FALSE);
	
	// 子线段是否连续
	UGbool IsHasGapBetween(UGuint nFromSubObjID ,UGuint nToSubObjID);
	UGint GetSubIDFromPointID(UGuint nPointID);	
	/*! \brief  根据坐标点得到索引 added by longzheng 2011-08-16
	*  \param point2dSrc	二维点
	*  \param dFindM		原里程值
	*  \param bOnSegment=FALSE 如果在线段上，就改为TRUE
	*  \return	点不在线上时返回 -1，在线上时返回点的索引，如果在线段上，则插入并返回点索引
	*/
	UGint GetIndexAtPoint(UGPoint2D point2dSrc, UGdouble& dFindM, UGdouble Tolerence,UGbool& bOnSegment);

#if PACKAGE_TYPE==PACKAGE_UGC
	UGString SubLineToSML(int nIndex, int nIndentCount);
	UGString Point3DToSML(const UGPoint3D* pPoints, int nPntCount, int nIndentCount);
	void GetDoubleArry(UGString& str, std::vector<UGdouble>& doubleDataArray );
	void AddSubLineFromSML(const UGString& strSubSml);
#endif // end declare ugc sdk

private:
	//! \brief 坐标点点串, z用来表达M值
	UGArray<UGPoint3D> m_Points;
	
	//! \brief 用来存放 所有子对象的点的个数 信息的整型数组
	UGArray<UGint> m_PolyCounts;

	//! \brief 最大M值,默认为0
	mutable UGdouble m_dMaxMeasure;
	//! \brief 最小M值,默认为0
	mutable UGdouble m_dMinMeasure;

	//UGint m_nLineMID;

	//! \brief 单调性,默认为MeasureNotMonotonic,非单调
	mutable UGMonotonicStyle m_nMeasureMonotonic;
};

}
#endif // !defined(AFX_UGGEOLINEM_H__4D04C30B_CF4B_411E_A107_6ABEE27A07C7__INCLUDED_)


