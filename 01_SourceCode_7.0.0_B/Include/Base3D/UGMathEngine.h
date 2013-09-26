//////////////////////////////////////////////////////////////////////////
//                    _   _   ____   ____                    
//   Project         | | | | / ___) / ___)                   
//                   | | | || | __ | |                       
//                   | |_| || |_\ || \___                    
//                    \____/ \____| \ ___)     6.0           
//                                                           
//!  \file headerfile.h
//!  \brief 三维数学类。
//!  \details 完成对三维所用到的数学函数的封装。
//!  \author 。
//!  \attention 
//!   Copyright (c) 1996-2010 SuperMap Software Co., Ltd. <br> 
//!   All Rights Reserved.
//!  \version 6.0
//////////////////////////////////////////////////////////////////////////

#if !defined(AFX_UGMATHENGINE_H__90331450_3347_42D5_B0A0_41353F9437C8__INCLUDED_)
#define AFX_UGMATHENGINE_H__90331450_3347_42D5_B0A0_41353F9437C8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include "Base3D/UGPrerequisites3D.h"
#include "Toolkit/UGPalette.h"
#include "Base3D/UGMesh.h"

//手动计算四个顶点的矩阵变换 2011.02.22 wangxinhe,目前只需要3个点 2012.04.01
#define MATRIX_MULTI(VERTICES,MATRIX,ARRAYX,ARRAYY,ARRAYZ) 	\
		VERTICES[0] =MATRIX[0][0] *ARRAYX[0] + MATRIX[1][0] *ARRAYY[0] + MATRIX[2][0] *ARRAYZ[0] +MATRIX[3][0]; \
		VERTICES[3] =MATRIX[0][0] *ARRAYX[1] + MATRIX[1][0] *ARRAYY[1] + MATRIX[2][0] *ARRAYZ[1] +MATRIX[3][0]; \
		VERTICES[6] =MATRIX[0][0] *ARRAYX[2] + MATRIX[1][0] *ARRAYY[2] + MATRIX[2][0] *ARRAYZ[2] +MATRIX[3][0]; \
		VERTICES[1] =MATRIX[0][1] *ARRAYX[0] + MATRIX[1][1] *ARRAYY[0] + MATRIX[2][1] *ARRAYZ[0] +MATRIX[3][1]; \
		VERTICES[4] =MATRIX[0][1] *ARRAYX[1] + MATRIX[1][1] *ARRAYY[1] + MATRIX[2][1] *ARRAYZ[1] +MATRIX[3][1]; \
		VERTICES[7] =MATRIX[0][1] *ARRAYX[2] + MATRIX[1][1] *ARRAYY[2] + MATRIX[2][1] *ARRAYZ[2] +MATRIX[3][1]; \
		VERTICES[2] =MATRIX[0][2] *ARRAYX[0] + MATRIX[1][2] *ARRAYY[0] + MATRIX[2][2] *ARRAYZ[0] +MATRIX[3][2]; \
		VERTICES[5] =MATRIX[0][2] *ARRAYX[1] + MATRIX[1][2] *ARRAYY[1] + MATRIX[2][2] *ARRAYZ[1] +MATRIX[3][2]; \
		VERTICES[8] =MATRIX[0][2] *ARRAYX[2] + MATRIX[1][2] *ARRAYY[2] + MATRIX[2][2] *ARRAYZ[2] +MATRIX[3][2];

//四个顶点直接赋值 2010.02.22 wangxinhe
#define MATRIX_ASSIGN(VERTICES,ARRAYX,ARRAYY,ARRAYZ)	\
												VERTICES[0] =ARRAYX[0]; \
												VERTICES[1] =ARRAYY[0]; \
												VERTICES[2] =ARRAYZ[0]; \
												VERTICES[3] =ARRAYX[1]; \
												VERTICES[4] =ARRAYY[1]; \
												VERTICES[5] =ARRAYZ[1]; \
												VERTICES[6] =ARRAYX[2]; \
												VERTICES[7] =ARRAYY[2]; \
												VERTICES[8] =ARRAYZ[2];

namespace UGC 
{
#if !defined (IOS) && !defined OS_ANDROID
typedef void (*MESHSCANPROC)(UGint X, UGint Y, UGuint pData);
#endif
//! \brief 三维数学函数类。
class BASE3D_API UGMathEngine  
{
public:
	//! \brief 构造函数
	UGMathEngine();
	//! \brief 析构函数
	virtual ~UGMathEngine();
	//! \brief 将度转换为弧度
	//! \param degrees 以度为单位的值[in]。
	//! \return 返回以弧度表示的值。
#if !defined (IOS) && !defined OS_ANDROID
	static UGdouble DegreesToRadians(UGdouble degrees);	
	//! \brief 将弧度转换为度
	//! \param dRadians 以弧度为单位的值[in]。
	//! \return 返回以度表示的值。
	static UGdouble RadiansToDegrees(UGdouble dRadians);
	//! \brief 地理坐标转换为笛卡尔坐标系，默认地球半径为6378137 
	//! \param dLongitude 地理坐标经度[in]。
	//! \param dLatitude 地理坐标维度[in]。
	//! \param GLOBAL_RADIUS 常量6378137[in]。
	//! \return 笛卡尔坐标系的坐标。
	//! \attention 我们的球为圆球而不是椭球。
	static UGVector3d SphericalToCartesian(UGdouble dLongitude, UGdouble dLatitude,UGdouble dRadius = GLOBAL_RADIUS);	

	//! \brief 将度转换为弧度
	//! \param fDegree 以度为单位的值[in]。
	//! \return 返回以弧度表示的值。
	static UGdouble Degree2Radian(UGdouble fDegree);
	//! \brief 笛卡尔坐标转换为球面坐标（地理坐标）。
	//! \param x 笛卡尔坐标x[in]。
	//! \param y 笛卡尔坐标y[in]。
	//! \param z 笛卡尔坐标z[in]。
	//! \return 球面坐标系坐标。
	static UGVector3d CartesianToSphericalD(UGdouble x, UGdouble y, UGdouble z);	
	//! \brief 四元数转换为欧拉角。
	//! \param q 四元数[in]。
	//! \return 欧拉角。
	static UGVector3d QuaternionToEuler(UGQuaternion4d q);	
	//! \brief 欧拉角转换为四元数。
	//! \param yaw 绕y轴旋转的角度[in]。
	//! \param pitch 绕x轴旋转角度[in]。
	//! \param roll 绕z轴旋转的角度[in]。
	//! \return 返回四元数。
	static UGQuaternion4d EulerToQuaternion(UGdouble yaw, UGdouble pitch, UGdouble roll);	
#endif
	//! \brief 由纬度和面片的尺寸求面片的行数。
	//! \param latitude 维度，单位弧度[in]。
	//! \param tileSize 面片尺寸，三维弧度[in]。
	//! \return 面片所处的行数。
	static UGint GetRowFromLatitude(UGdouble latitude, UGdouble tileSize, UGbool bStartLT = FALSE);
	//! \brief 由经度和面片的尺寸求面片的行数。
	//! \param longitude 经度，单位弧度[in]。
	//! \param tileSize 面片尺寸，三维弧度[in]。
	//! \return 面片所处的列数。
	static UGint GetColFromLongitude(UGdouble longitude, UGdouble tileSize);


	//! \brief 由纵坐标和面片的尺寸求面片的行数。
	//! \param Coord 纵坐标，单位米[in]。
	//! \param tileSize 面片尺寸，米[in]。
	//! \param dL0TileSize 0层的面片尺寸，米[in]。
	//! \return 面片所处的行数。
	static UGint GetRowFromCoord(UGdouble Coord, UGdouble tileSize, UGdouble dL0TileSize);

	//! \brief 由横坐标和面片的尺寸求面片的列数。
	//! \param Coord 横坐标，单位米[in]。
	//! \param tileSize 面片尺寸，米[in]。
	//! \param dL0TileSize 0层的面片尺寸，米[in]。
	//! \return 面片所处的横数。
	static UGint GetColFromCoord(UGdouble Coord, UGdouble tileSize, UGdouble dL0TileSize);
    
#if !defined (IOS) && !defined OS_ANDROID
	//! \brief 计算两点的球面角度距离。
	//! \param lonA A点的经度，单位弧度[in]。
	//! \param latA A点的纬度，单位弧度[in]。
	//! \param lonB B点的经度，单位弧度[in]。
	//! \param latB B点的纬度，单位弧度[in]。
	//! \return A、B两点的球面角度距离。
	static UGdouble SphericalDistance( UGdouble lonA, UGdouble latA,UGdouble lonB,UGdouble latB);	
	//! \brief 计算两点的球面角度距离。
	//! \param lonA A点的经度，单位弧度[in]。
	//! \param latA A点的纬度，单位弧度[in]。
	//! \param lonB B点的经度，单位弧度[in]。
	//! \param latB B点的纬度，单位弧度[in]。
	//! \return A、B两点的球面角度距离。
	static UGdouble SphericalDistanceCos( UGdouble lonA, UGdouble latA,UGdouble lonB,UGdouble latB);	
	//! \brief 给一个顶点数组和索引数组计算三角型列表的向量。
	//! \param pVertex 顶点数组[in]。
	//! \param pIndice 构成三角形串的索引数组[in]。
	//! \param nVertexCount 顶点数组的大小[in]。
	//! \param nIndiceCount 索引数组的大小[in]。
	//! \return 各个顶点的向量。
	//! \attention 每个顶点计算出来的是光滑向量，即由周围所有的点来计算该点的向量。
	static UGdouble* ComputeVertexNormals(UGdouble* pVertex,UGushort* pIndice,UGint nVertexCount,UGint nIndiceCount);
	//! \brief 给一个顶点数组和索引数组计算三角型串的向量。
	//! \param pVertex 顶点数组[in]。
	//! \param pIndice 构成三角形串的索引数组[in]。
	//! \param nVertexCount 顶点数组的大小[in]。
	//! \param nIndiceCount 索引数组的大小[in]。
	//! \return 各个顶点的向量。
	//! \attention 每个顶点计算出来的是光滑向量，即由周围所有的点来计算该点的向量。
	static UGfloat* ComputeVertexNormals(UGfloat* pVertex,UGushort* pIndice,UGint nVertexCount,UGint nIndiceCount);
	static UGfloat* ComputeVertexNormals(UGfloat* pVertex,UGuint* pIndice,UGint nVertexCount,UGint nIndiceCount);
	//! \brief 给一个顶点数组数组计算三角型串的向量。
	//! \param pVertex 构成三角形串顶点数组,每三个点构成一个三角形，无索引[in]。
	//! \param nVertexCount 顶点数组的大小[in]。
	//! \return 各个顶点的向量。
	//! \attention 每个顶点计算出来的是光滑向量，即由周围所有的点来计算该点的向量。
	static UGdouble* ComputeVertexNormals(UGdouble* pVertex,UGint nVertexCount);
	//! \brief 给一个顶点数组数组计算三角型串的向量。
	//! \param pVertex 构成三角形串顶点数组,每三个点构成一个三角形，无索引[in]。
	//! \param nVertexCount 顶点数组的大小[in]。
	//! \return 各个顶点的向量。
	//! \attention 每个顶点计算出来的是光滑向量，即由周围所有的点来计算该点的向量。
	static UGfloat* ComputeVertexNormals(const UGfloat* pVertex,const UGuint nVertexCount);

	//! \brief 给一个顶点数组数组计算三角型串的向量，作废的接口，好像有问题。
	//! \param pVertex 构成三角形串顶点数组,每三个点构成一个三角形，无索引[in]。
	//! \param nVertexCount 顶点数组的大小[in]。
	//! \param pNormal 各个顶点的向量[out]。
	//! \param bQuad [in]。
	static void ComputeFaceNormals(UGfloat* pVertex,UGint nVertexCount, UGfloat* pNormal, UGbool bQuad = FALSE);	
	//! \brief 由不共线的三个点计算过这三维点的面的法向了。
	//! \param vec1 顶点1[in]。
	//! \param vec2 顶点2[in]。
	//! \param vec3 顶点3[in]。
	//! \return 面的法向量。
	static UGVector3d ComputeFaceNormals(const UGVector3d& vec1,const UGVector3d& vec2,const UGVector3d& vec3);	
	
	//! \brief 计算由向量vec1到向量vec2的欧拉角。
	//! \param vec1 向量1[in]。
	//! \param vec2 向量2[in]。
	//! \return 向量1到向量2的欧拉角。
	static UGVector3d GetVec1RotToVec2(const UGVector3d& vec1,const UGVector3d& vec2);	
	//! \brief 计算绕某个向量旋转一定角度所生成的欧拉角。
	//! \param fAngle 旋转角度[in]。
	//! \param vecAxies 旋转轴[in]。
	//! \return 欧拉角。
	static UGVector3d GetRotFormAngleAxies(UGdouble fAngle,UGVector3d& vecAxies);	
	//! \brief 判断浮点型的正负。
	//! \param fValue 传入的浮点型值[in]。
	//! \return 正数返回1，负数返回-1，0返回0.0。
	static UGdouble Sign (UGdouble fValue);	

	//! \brief 点斜式直线与矩形框的交点
	//! \param pnt1 二维点[in]。
	//! \param pnt1 直线斜率[in]。
	//! \param pnt1 矩形框[in]。
	//! \return 交点。
	static UGPoint2Ds IntersectionOfRectByPointslopeline(UGPoint2D& point, UGdouble dSlope, UGRect2D& rect);

	static UGdouble Compute2DAngleFromY(UGPoint2D pnt1);	
	//! \brief 判断是否是合法实数。
	//! \param dValue 实数[in]。
	//! \return true为合法，false为非法。
	static UGbool IsRealNaN(UGdouble dValue);
	//! \brief 计算顶点的包围盒。
	//! \param pVertex 顶点数组[in]。
	//! \param nVertexCount 顶点数目[in]。
	//! \param boundingBox 包围盒[out]。
	static void  ComputeBoundingBox(UGfloat* pVertex,UGint nVertexCount,UGBoundingBox& boundingBox);	
	//! \brief 对面进行三角化。
	//! \param pPoint 构成面的顶点数组[in]。
	//! \param nPoint 顶点数目[in]。
	//! \param nTri 三角形的数目[out]。
	//! \return 三角形的顶点数组。
	static void PartTriangulation(const UGArray<UGPoint3D>& arrPoint, UGArray<UGushort>& arrTriIndex, UGint& nTri);	
	//! \brief 射线与三角形相交。
	//! \param &rayOrg 射线起点[in]。
	//! \param rayDelta 射线方向（单位化）[in]。
	//! \param p0 三角形第一个点[in]。
	//! \param p1 三角形第二个点[in]。
	//! \param p2 三角形第三个点[in]。
	//! \return 返回相交参数t。
	//! \remarks rayIntersect = rayOrg + rayDelta * t。
	static UGbool RayTriangleIntersect(UGVector3d &rayOrg, UGVector3d& rayDelta, 
									   UGVector3d& p0, UGVector3d& p1, UGVector3d& p2, 
									   UGdouble& t);

	//! \brief  球坐标空间中的一段距离转到经纬度跨度。
	//! \param CartesianDist [in]。
	//! \param SphericalDist [in]。
	//! \return 。
	//! \remarks  半径是用地球半径。
	//! \attention 。
	static void CartesianDist2SphericalDist(const UGdouble& CartesianDist, UGdouble& SphericalDist);
	//! \brief 顶点数组与矩阵相乘。
	//! \param pDest 目的顶点数组[in]。
	//! \param pSrc 源顶点数组[in]。
	//! \param nCount 顶点个数[in]。
	//! \param matView 矩阵[in]。
	//! \return 。
	//! \remarks 。
	//! \attention 。
	static void VerticesMulitplyViewMatrix(UGfloat* pDest, UGfloat* pSrc,
										   UGint nCount, UGMatrix4d& matView);
	//! \brief 求两个向量的夹角。
	//! \param v1 向量1[in]。
	//! \param v2 向量2[in]。
	//! \return 两个向量夹角。
	static UGdouble AngleOfV1V2(UGVector3d& v1, UGVector3d& v2);	
	
	//static UGVector3d VerticalVectorOfV3(UGVector3d& v1, UGVector3d& v2, UGVector3d& v3);
	//! \brief  返回比a大的，并且是最接近a的2的次方的数。
	static UGuint NextP2 (UGuint a);

	//! \brief  计算2的多少次方刚好大于或等于a。
	static UGuint NextLog2(UGuint a);

	//! \brief 得到缓存的行列。
	//! \param nLevel 文件所在的层[in]。
	//! \param nRow 文件所在的行[in]。
	//! \param nCol 文件所在的列[in]。
	//! \param nCacheRow 文件在缓存目录的行[out]。
	//! \param nCacheCol 文件在缓存目录的列[out]。
	static void GetCacheRowCol(UGint nLevel, UGint nRow, UGint nCol, UGint& nCacheRow, UGint& nCacheCol);

	//! \brief 得到文件的缓存的相对路径。
	//! \param nLevel 文件所在的层[in]。
	//! \param nRow 文件所在的行[in]。
	//! \param nCol 文件所在的列[in]。
	//! \param nVersion 文件版本号[in]。
	//! \return 文件的相对路径（没有图片的扩展名）。
	static UGString GetCacheLocalPath(UGint nLevel, UGint nRow, UGint nCol, UGint nVersion);

	//! \brief 判断顶点是否逆时针走向。
	//! \param pPoint 顶点数组[in]。
	//! \param nPoint 顶点数组大小[in]。
	//! \return 是否逆时针走向。
	static UGint IsCounterClockwise(const UGPoint3D* pPoint, UGint nPoint);	
	//! \brief 线段与球相交。
	//! \param vecSphereCenter 球心[in]。
	//! \param dSphereRadius 球半径[in]。
	//! \param vecStart 线段起始点[in]。
	//! \param vecEnd 线段结束点[in]。
	//! \param t1 交点1[in]。
	//! \param t2 交点2[in]。
	//! \return 交点个数。
	//! \remarks 交点范围为0-1范围内有效。
	//! \attention 。
	static UGint LineSphereIntersection(UGVector3d vecSphereCenter,
							UGdouble dSphereRadius,
							UGVector3d vecStart,
							UGVector3d vecEnd, 
							UGfloat& t1, UGfloat& t2);

	//! \brief 计算rectRes是否和rectObj相交。
	//! \param rectRes 一般是较大的矩形框[in]。
	//! \param rectObj 被测试的矩形框[in]。
	//! \return 范围是否相交。
	//! \remarks 考虑是否变更线。
	//! \attention 。
	static UGbool IsIntersect3D(const UGRect2D& rectRes,const UGRect2D& rectObj);

	//! \brief 计算rectRes是否和pnt相交。
	//! \param rectRes [in]。
	//! \param pnt [in]。
	//! \return 范围是否相交。
	//! \remarks 考虑是否变更线。
	//! \attention 。
	static UGbool IsIntersect3D(const UGRect2D& rectRes, const UGPoint2D& pnt);

	//! \brief 由于存在计算误差，调整特殊角度的三角函数值
	//! \param dAngle [in]角度
	//! \param dCosVal[out]角度对应的余弦
	//! \param dSinVal[out]角度对应的正弦
	//! \remarks 。
	static void AdjSpecialTriFunValue(const UGdouble dAngle,UGdouble &dCosVal,UGdouble &dSinVal);
	
	//! \brief 计算得到新的插入点，将点对象向眼睛（相机）拉近一定的比例。
	//! \param ViewMatrix 视图矩阵[in]。
	//! \param vecInsertPos 插入的原始点[in]。
	//! \param nScale 眼睛到目标点的距离，新的目标点到原始目标点的距离，两者的比值[in]。
	//! \return 新的目标点。
	//! \remarks 。
	//! \attention 主要是用在点对象，文本对象，为了防止地标文字在左半球时陷到地里问题。
	static UGVector3d GetCloserInsertPnt(const UGMatrix4d& ViewMatrix, const UGVector3d& vecInsertPos, UGint nScale);

	//! \brief 射线与球面交点。
	//! \param vecStart 起始坐标[in]。
	//! \param vecEnd 终点坐标[in]。
	//! \param dRadius 球的半径[in]
	//! \param vecIntersect 交点[out]。
	//! \return 。
	//! \remarks 。
	//! \attention 球心坐标为(0,0,0)。
	static UGbool RayIntersectionWithSphere(UGVector3d& vecStart, UGVector3d& vecEnd,UGdouble dRadius, UGVector3d& vecIntersect);	
	
	//! \brief 图像数据采样，一般是从大到小的采样
	//! \param pSRC 源数据 外面分配空间
	//! \param pDEST 目标数据 外面分配空间
	//! \param nSrcWidth 源数据宽
	//! \param nSrcHeight 源数据高
	//! \param nDestWidth 目标数据宽
	//! \param nDestHeight 目标数据高
	static void  ScaleImage(UGuchar* pSRC, UGuchar* pDEST, UGint nSrcWidth, UGint nSrcHeight, 
		                    UGint nDestWidth, UGint nDestHeight, UGImageSamplerType nType = IMAGE3D_RESAMPLER_BILINEAR);

	//! \brief 对单个纹理进行缩放，建立多级纹理
	//! \param srcImageData 源数据
	//! \param desImageData 目标数据 
	//! \param nNewWidth 目标数据宽
	//! \param nNewHeight 目标数据高
	static void ScaleImage(const UGImageData& srcImageData,UGImageData& desImageData,UGint nNewWidth,UGint nNewHeight);
#endif   
	//! \brief 计算以左上角开始的Tile的经纬度Bounds.
	//! \param nRow Tile的行[in].
	//! \param nCol Tile的列[in].
	//! \param level Tile的层[in].
	//! \param dL0TileSizeDeg 零层的经纬度跨度，默认为180[in].
	//! \param UGRect2D 返回经纬度Bounds[out].
	static UGRect2D CalcTileBounds(UGint nRow, UGint nCol, UGint level, UGdouble dL0TileSizeDeg = 180);
#if !defined (IOS) && !defined OS_ANDROID
	//! \brief 计算以左下角开始的Tile的经纬度Bounds.
	//! \param nRow Tile的行[in].
	//! \param nCol Tile的列[in].
	//! \param level Tile的层[in].
	//! \param dL0TileSizeDeg 零层的经纬度跨度，默认为180[in].
	//! \param UGRect2D 返回经纬度Bounds[out].
	static UGRect2D CalcLeftBottomTileBounds(UGint nRow, UGint nCol, UGint level, UGdouble dL0TileSizeDeg = 180);

	//! \brief　调整缓存Bounds的范围
	//! \param rcBounds 需要调整的范围[in].
	//! \param nLevel 调整的参考层[in].
	static UGRect2D CeilBounds(UGRect2D rcBounds,UGint nLevel,UGdouble dL0TileSizeDeg = 180);

	//! \brief 通过线性插值和箱过滤缩放。from gluScaleImage
	//! \param components 颜色成分数量，RGBA是4
	//! \param widthin 输入图像的宽度
	//! \param heightin 输入图像的高度
	//! \param datain 输入图像的指针
	//! \param widthout 输出图像的宽度
	//! \param heightout 输出图像的高度
	//! \param dataout 输出图像的指针
	static void ScaleImageInternal(UGint components, UGint widthin, UGint heightin,
		const UGuchar *datain,
		UGint widthout, UGint heightout,
		UGuchar* dataout);

	//! \brief 把图像数据生成Mipmap图像数据
	//! \param components [in] 原始图像位深，目前仅支持32位
	//! \param widthin	  [in] 原始图像宽度
	//! \param heightin   [in] 原始图像高度
	//! \param datain     [in] 原始图像数据
	//! \param widthout   [in/out] 生成图像的宽度
	//! \param heightout  [in/out] 生成图像的高度
	//! \param arrTextureSize [in/out] 原始MipMap图像数据每层的偏移
	//! \return MipMap生成结果
	static UGuchar* GenerateMipMap(UGint components, UGuint& widthin, UGuint& heightin,
		UGuchar *datain, UGuint& widthout, UGuint& heightout,UGArray<UGuint>& arrTextureOffset);

	//! \brief 把图像数据生成Mipmap图像数据
	//! \param pImageData [in] 原始图像数据
	//! \param pTotalImageData [out] 生成后的图像数据 
	static UGuchar* GenerateMipMap(UGint components, UGint& widthin, UGint& heightin,
		UGuchar *datain, UGint& widthout, UGint& heightout);

	//! \brief 通过一整张Mipmap图像数据得到Mipmap图像数组
	//! \param pMipMapImageData [in] 一整张Mipmap图像数据
	//! \param arrMipMapImageData [out] Mipmap图像数组 
	static UGuchar* ParseMipMap(UGint components, UGint widthin, UGint heightin,
		const UGuchar *datain,
		UGArray<UGuint>& arrTextureSize);

	//! \brief 计算8个顶点的BoundingBox表面到摄像机（坐标原点）的距离 by wangxinhe 2010.12.14
	//! \param vecBoundBox BoundBox的8个顶点
	//! \param BoundingBox 所在的地理坐标（经纬度，地面高度）
	//! \param viewMatrix 当前的视图矩阵
	//! \param BoundingBox 绕Z轴的旋转角度
	//! \param altitude 当前摄像机的高度
	//! \param tilt 摄像机的Tilt角度
	//! \return 得到的距离
	static double GetBoundingBoxDistanceToCamera(const UGVector3d *vecBoundBox,	const UGPoint3D &pntBoundBox,
												const UGMatrix4d &viewMatrix,UGdouble rotation,UGdouble altitude,
												UGdouble tilt);

	//! \brief 计算直线与平面的交点
	//! \param planeVector [IN] 平面法向量
	//! \param planePoint [IN] 平面上一点
	//! \param lineVector [IN] 直线的向量
	//! \param linePoint [IN] 直线上一点
	//! \return 返回交点
	static UGbool GetPlaneLineIntersectPoint(UGVector3d &planeVector,UGVector3d &planePoint,
		UGVector3d &lineVector,UGVector3d &linePoint,UGVector3d& vecIntersect);

	//! \brief 双线性采样
	//! \param pSRC [IN] 需要进行采样的原始点
	//! \param pDEST [IN] 期望的采样结果
	//! \param nOldWidth [IN] 原始数据的宽度
	//! \param nOldHeight [IN] 原始数据的高度
	//! \param nWidth [IN] 期望采样结果数据的宽度
	//! \param nHeight [IN] 期望采样结果数据的高度
	static void  TerrainSamplerBiLinear(const UGfloat* pSRC, UGfloat* pDEST, UGint nOldWidth, UGint nOldHeight, 
		UGint nWidth, UGint nHeight);

	//! \brief 将图像数据内容进行对齐处理，暂时只对24位图像处理
	//! \param components 颜色成分数量，RGBA是4
	//! \param width 输入图像的宽度
	//! \param height 输入图像的高度
	//! \param datain 输入图像的指针
	//! \param dataout 输出图像的指针
	static UGbool ClipImageData(UGint components, UGint width, UGint height, const UGuchar *datain, UGuchar *dataout);

	//! \brief 三角与平面求交
	//! \param planeNormalVector 平面法向量
	//!	\param PlanePoint 平面上的一个点
	//! \param triangleP1 三角形顶点1
	//! \param triangleP2 三角形顶点2
	//! \param triangleP3 三角形顶点3
	//! \return 三角边线与平面的交点(无相交或共面返回0个点，交在单个顶点返回1个点）
	static UGArray<UGVector3d> GetPlaneTriangleIntersectLine(UGVector3d& planeNormalVector, UGVector3d& planePoint, 
		UGVector3d& triangleP1, UGVector3d& triangleP2, UGVector3d& triangleP3);

	//! \brief 求三维点与平面的方向距离
	//! \param planeNormalVector 平面法向量
	//!	\param PlanePoint 平面上的一个点
	//! \param point 指定的待计算点
	//! \return 三维点与平面的方向距离，绝对值是距离，正数表示与法向量在面的同一侧
	static UGdouble GetPointDirectionDistanceToPlane(UGVector3d& planeNormalVector, UGVector3d& PlanePoint,
		UGVector3d& point);

	//! \brief 平面与平面求交线
	//! \param planeVector1 平面1的方向向量[in]
	//! \param planePoint1	平面1中点坐标[in]
	//! \param planeVector2 平面2的方向向量[in]
	//! \param planePoint2	平面2中点坐标[in]
	//! \param lineVector		交线的方向向量[out]
	//! \param linePoint			交线上的点坐标[out]
	//! \return 获得交线返回TRUE，否则返回FALSE
	static UGbool GetPlanePlaneIntersectLine(UGVector3d &planeVector1,UGVector3d &planePoint1,
		UGVector3d &planeVector2,UGVector3d &planePoint2,UGVector3d& lineVector, UGVector3d& linePoint);

	//! \brief 三角形与三角形求交线
	//! \param triangleA1，triangleA2，triangleA3	三角形A的三个端点坐标[in]
	//! \param triangleB1，triangleB2，triangleB3	三角形B的三个端点坐标[in]
	//! \return 返回交线的两个端点坐标
	static UGArray<UGVector3d> GetTriangleTriangleIntersectPoints(UGVector3d &triangleA1, UGVector3d &triangleA2,
		UGVector3d &triangleA3, UGVector3d &triangleB1, UGVector3d &triangleB2, UGVector3d &triangleB3);

	//! \brief 判断点是否在Mesh内部
	//! \param point	待判断的点[in]
	//! \param mesh	用来判断的mesh[in]
	//! \return 在mesh内部返回TRUE，否则为FALSE
	static UGbool IsPointInMesh(UGVector3d &point, UGMesh &mesh);

	//! \brief 判断三角形是否和BOX相交
	//! \param p1 p2 p3		三角形三个顶点[in]
	//! \param pMax pMin	BOX中最大值和最小值[in]
	//! \return 相交返回TRUE，否则为FALSE
	static UGbool IsTrangleBoxIntersect(UGVector3d &p1, UGVector3d &p2, UGVector3d &p3,
		UGVector3d &pMax, UGVector3d &pMin);

	//! \brief 判断平面是否和BOX相交
	//! \param planeVector	平面法向量[in]
	//! \param planePoint		平面内一点[in]
	//! \param pMax pMin	BOX中最大值和最小值[in]
	//! \return 相交0，在面的前面1，在面的后面-1
	static UGint IsPlaneBoxIntersect(UGVector3d &planeVector,UGVector3d &planePoint,
		UGVector3d &pMax, UGVector3d &pMin);
private:
	//! \brief 二维点的叉乘。
	//! \param U 点1[in]。
	//! \param V 点2[in]。
	//! \return 点1和点2的叉乘。
	static UGfloat Kross (const UGPoint2D& U, const UGPoint2D& V);	
	//! \brief 判断线段是否在圆锥之内。
	//! \param V0 线段的起始端点[in]。
	//! \param V1 线段的终止端点[in]。
	//! \param VM 线段V0-VM的终止端点[in]。
	//! \param VP 线段V0-VP的终止端点[in]。
	//! \param bClockwise 多边形是否顺时针[in]。
	//! \return 线段v0-v1是否包含与VM-V0-VP的圆锥内。
	static UGbool SegmentInCone(UGPoint2D& V0, UGPoint2D& V1, UGPoint2D& VM, UGPoint2D& VP, UGbool bClockwise);	
	//! \brief 判读多边形中的两个顶点是否是对角线。
	//! \param pPoint 多边形的顶点数组[in]。
	//! \param nPoint 顶点个数[in]。
	//! \param i0 顶点1的索引[in]。
	//! \param i2 顶点2的索引[in]。
	//! \param bClockwise 多边形是否顺时针[in]。
	//! \return 顶点1和顶点2是否构成多边形的对角线。
	static UGbool IsDiagonal(const UGPoint3D* pPoint, UGushort* pPointIndex, UGint nPoint,UGint i0, UGint i2, UGbool bClockwise);	

	//! \brief 判断三个点的缠绕情况。
	//! \param x1 顶点1的x坐标[in]。
	//! \param y1 顶点1的y坐标[in]。
	//! \param x2 顶点2的x坐标[in]。
	//! \param y2 顶点2的y坐标[in]。
	//! \param x3 顶点3的x坐标[in]。
	//! \param y3 顶点3的y坐标[in]。
	//! \return 返回1时为逆时针，－1时为顺时针，0为共线。
	static UGint counterclockwise(UGdouble x1, UGdouble y1, UGdouble x2, UGdouble y2, UGdouble x3, UGdouble y3);	
	
	//! \brief 最邻近采样
	static void  ImageSamplerNearestNeighbor(UGuchar* pSRC, UGuchar* pDEST, UGint nSrcWidth, UGint nSrcHeight, 
		                    UGint nDestWidth, UGint nDestHeight);
	//! \brief 双线性采样
	static void  ImageSamplerBiLinear(UGuchar* pSRC, UGuchar* pDEST, UGint nSrcWidth, UGint nSrcHeight, 
		                    UGint nDestWidth, UGint nDestHeight);
	
	//! \brief 立方卷积采样
	static void  ImageSamplerCubic(UGuchar* pSRC, UGuchar* pDEST, UGint nSrcWidth, UGint nSrcHeight, 
		                    UGint nDestWidth, UGint nDestHeight);

	//! \brief 通过线性插值和箱过滤缩放。from gluScaleImage
	//! \param components 颜色成分数量，RGBA是4
	//! \param widthin 输入图像的宽度
	//! \param heightin 输入图像的高度
	//! \param datain 输入图像的指针
	//! \param dataout 输出图像的指针
	static void HalveImage(UGint components, UGuint width, UGuint height,
		const UGuchar *datain, UGuchar *dataout);

public:
	static SceneType m_msSceneType;
	//平面投影中心
	static UGPoint2D m_msPntProCenter;
	//平面投影区域
	static UGRect2D m_msSceneViewRect;
#endif
};
}
#endif // !defined(AFX_UGMATHENGINE_H__90331450_3347_42D5_B0A0_41353F9437C8__INCLUDED_)

