#ifndef _UGSCMFEATURE_H_
#define _UGSCMFEATURE_H_

#include "Stream/ugdefs.h"

namespace UGC{

#define SCM_INVALIDTYPE 0xFFFF

//!< 暂时先在这写个宏定义
#define SCM_TILE_FLAG 500

typedef UGuint UGScmGeoID ;

//!< 单个图层的数据头,点线面文本可以通用("/"前后分别对应点线面和文本中的注释)
struct UGScmInnerHead 
{
	UGint m_iFileSize;		//!< 数据块(临时文件)总大小
	UGint m_iGeoCount;		//!< 几何对象数量
	UGint m_iIndexOffset;	//!< 索引块偏移,如果是点数据，则为0 / 主文本信息块偏移 
	UGint m_iDataOffset;	//!< 数据块偏移 / 子文本信息块偏移
	UGint m_iFeatureOffset;	//!< 属性数据块偏移,没有则为0 / 文本偏移
	UGScmInnerHead()
	{
		m_iFileSize = 0;
		m_iGeoCount = 0;
		m_iIndexOffset = 0;
		m_iDataOffset = 0;
		m_iFeatureOffset = 0;
	};
};

//!< 正规化范围
struct UGScmNormalBound 
{
	UGushort m_usLeft;		//!< 左								
	UGushort m_usRight;		//!< 右
	UGushort m_usTop;		//!< 上
	UGushort m_usBottom;	//!< 下
	UGScmNormalBound()
	{
		m_usLeft = 0;
		m_usRight = 0;
		m_usTop = 0;
		m_usBottom = 0;
	};
};

//!< 几何位置
struct  UGScmPosInfo
{
	UGint m_iCount;			//!< 点个数
	UGint m_iOffset;		//!< 相对偏移
	UGScmPosInfo()
	{
		m_iCount = 0;
		m_iOffset = -1;
	}
};

//!< 几何索引信息
struct UGScmGeoIndex
{
	UGint m_iSubOffset;
	UGScmNormalBound m_NormalBound;
	UGScmGeoIndex()
	{
		m_iSubOffset = -1;
	}
};

//!< 几何子索引信息
struct UGScmGeoSubIndex 
{
	UGint m_iSubCount;					//!< 子对象个数
	UGArray<UGScmPosInfo> m_arPosInfo ; //!< 子对象位置信息 
};

//!< 几何索引数据块
struct UGScmGeoIndexInfo
{
	UGArray<UGScmGeoIndex> arGeoIndex;		//!< 主索引数组
	UGArray<UGScmGeoSubIndex> arSubIndex;	//!< 子索引数组
};

//!< 文本
struct UGScmGeoText
{
	UGushort m_usStyleIndex;	//!< 风格索引
	UGushort m_usSubCount;		//!< 子对象个数
	UGint m_iSubOffset;			//!< 子对象相对偏移
	UGScmGeoText()
	{
		m_usStyleIndex = 0;
		m_usSubCount = 0;
		m_iSubOffset = -1;
	}
};

//!< 子文本
struct UGScmSubText
{
	UGushort m_usX;		//!< 子对象正规化x坐标
	UGushort m_usY;		//!< 子对象正规化y坐标
	UGint m_iAngle;		//!< 子对象角度,实际角度=m_iAngle*0.1
	UGint m_iNameInfo;	//!< 名称长度和偏移合成
	UGScmSubText()
	{
		m_usX = 0;
		m_usY = 0;
		m_iAngle = 0;
		m_iNameInfo = 0;
	};

};

//!< 文本索引数据块
struct UGScmTextIndexInfo
{

};


//!< 文本和POI索引信息
struct UGScmAnnotateIndexInfo 
{
	UGushort m_usX;		    //!< 正规化X坐标。
	UGushort m_usY;		    //!< 正规化y坐标。
	UGint m_iTXTOffset;   //!< 文本偏移。
	UGint m_iSubKind;      //! 符号库ID,文本类型该变量为-1
	UGScmAnnotateIndexInfo()
	{
		m_usX = 0;
		m_usY = 0;
		m_iTXTOffset = 0;
		m_iSubKind = -1;
	};
};

struct UGScmNormalPoint 
{
	UGushort m_usX;
	UGushort m_usY;
	UGScmNormalPoint() 
	{
		m_usX = 0;
		m_usY = 0;
	};
};

typedef UGint UGScmFeatrueIndex;

//瓦片内数据头
struct UGScmTileHead
{
	UGushort usNDTSign;		 	 //NDT数据标识
	UGushort m_usLayerCount;	 //网格内图层的数量	
	UGint m_iDataOffset;		 //数据集数据偏移
	UGint m_iSize;               //瓦片大小
	UGScmTileHead()
	{
		usNDTSign = 500;
		m_usLayerCount = 0;
		m_iDataOffset = 0;
		m_iSize = 0;
	}
};

struct UGScmTileIndex
{
//	UGushort usLayerID;
	UGushort usType;			//!< 几何类型
	UGint iOffset;				//!< 相对偏移
	UGint iSize;				//!< 大小

	UGScmTileIndex()
	{
		usType = SCM_INVALIDTYPE;
		iOffset = -1;
		iSize = -1;
	}
};

enum ScmDstType
{
	//! \brief 点
	Point = 1,
	//! \brief 线
	Line = 3,
	//! \brief 面
	Region = 5,
	//! \brief 文本
	Text = 7
	//***注记以后再加***//
	//Annotate
};

struct UGScmFeatureInfo 
{
	UGString m_strField;		//!< 属性字段名称
	UGVariant::VarType m_Type;	//!< 属性字段类型
};

struct UGTilePosition
{
	UGint m_iRow;				//!< 行
	UGint m_iColumn;			//!< 列
	UGdouble m_dScale;			//!< 比例尺

	UGTilePosition()
	{
		m_iRow = 0;
		m_iColumn = 0;
		m_dScale = 0.0;
	}
};

//!< 将文本长度和文本偏移合成
#define CombineScmTxtIndex(ScmLen,ScmOffset) ( (ScmLen<<24) | ScmOffset)

//!< 解析文本长度
#define ParseScmTxtLength(x) ( x>>24 )

//!< 解析文本偏移
#define ParseScmTxtOffset(x) ( x & 0x00FFFFFF )

}

#endif