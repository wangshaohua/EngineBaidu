//////////////////////////////////////////////////////////////////////////
//                    _   _   ____   ____                    
//   Project         | | | | / ___) / ___)                   
//                   | | | || | __ | |                       
//                   | |_| || |_\ || \___                    
//                    \____/ \____| \ ___)     6.0           
//                                                           
//!  \file headerfile.h
//!  \brief Class 的接口定义。
//!  \details 文件详细信息。
//!  \author tangzq 格式转换组。
//!  \attention 
//!   Copyright (c) 1996-2008 SuperMap Software Limited Company.  <br> 
//!   All Rights Reserved.
//!  \version 6.0
//////////////////////////////////////////////////////////////////////////
#if !defined(AFX_UGFileParseWorkSpace_H__9D5BD937_D091_4D5F_957C_94B8A7A74D92__INCLUDED_)
#define AFX_UGFileParseWorkSpace_H__9D5BD937_D091_4D5F_957C_94B8A7A74D92__INCLUDED_

#include "Geometry/UGFeature.h"
#include "UGFileParse.h"
#include "FileParser/UGVectorConfigParams.h"
#include "Toolkit/UGTextStyle.h"

namespace UGC {

class UGFileParseWorkSpace;
class UGDataSource;

class FILEPARSER_API UGWorkSpaceFileLayer: public UGFileLayer
{
public:
	UGWorkSpaceFileLayer(UGFileParseWorkSpace* ws){m_pWS = ws;}

	UGbool ImportConf(UGDataSource* db, const UGImportParams& importParams, UGArray<UGString>& strSucMapNames);

public:
	virtual FILELAYER_TYPE GetType(){return UGFileLayer::FL_CONFIG;}

private:
	UGFileParseWorkSpace* m_pWS;

};

//! \brief 矢量文件解析基类。
class FILEPARSER_API UGFileParseWorkSpace : public UGFileParser  
{
	friend class UGWorkSpaceFileLayer;
	friend class UGFileParseToolkit;
public:

	//! \brief 构造函数。
	UGFileParseWorkSpace();
	
	//! \brief 析构函数。
	virtual ~UGFileParseWorkSpace();	
	
	virtual UGFileType::EmGroup GetFileGroup() const;

public:
	enum DisplayType{
		Off , //不显示
		Graphic , //原图的样式
		Global , //显示覆盖的演示
		Value, //专题图
	};
	enum ThematicType{
		noneThemes,//没有
		ranges, //等级
		bar, //直方图
		pie, //饼图
		graduated, //等级
		density, //散点图
		individual, //单值
	};
	enum TXT_ALIGN{
		TXT_RIGHTDOWN=0,//左上,Supermap里面是右下
		TXT_CENTERDOWN,//中上,SuperMap里面是中下
		TXT_LEFTDOWN,//右上，Supermap里面是左下
		TXT_RIGHTLINE,//左基线,SuperMap里面是右基线
		TXT_CENTERLINE,//中线
		TXT_LEFTLINE,//右基线,SuperMap里面是左基线
		TXT_RIGHTUP,//左下,SuperMap里面是右上
		TXT_CENTERUP,//中下，SuperMap里面是中上
		TXT_LEFTUP,//右下，SuperMap里面是左上
		TXT_RIGHTCENTER,//左中，SuperMap里面是右中
		TXT_CENTER,//中
		TXT_LEFTCENTER,//右中,SuperMap里面是左中
	};

	struct ThemeRange
	{	
		ThemeRange()
		{
			isDefault = FALSE;
			start	  = 0.0;
			end		  = 0.0;
		}
		UGbool isDefault;
		UGdouble start;
		UGdouble end;
		UGStyle style;
	};

	struct ThematicLayer
	{	
		ThematicLayer()
		{
			type    = UGFileParseWorkSpace::noneThemes;
			id      = 0;
			map     = 0;
			density = 0;
			angle	= 0.0;
			column  = _U("");
			styles.RemoveAll();
			individualRange.RemoveAll();
			
		}
		ThematicType type;
		UGint id;
		UGString column;
		UGint map;
		UGArray<ThemeRange> ranges;
		UGint density;
		UGArray<UGStyle> styles;
		UGDict<UGString, UGStyle> individualRange;
		UGdouble angle;

	};

	struct LabelConf{
		LabelConf()
		{	
			overlap    = FALSE;
			autoLabel  = FALSE;
			alongPath  = FALSE;
			visibility = FALSE;
			position   = 1;
			LabelminZoom = 0.0;
			LabelmaxZoom = 0.0;
			column		 = _U("");
			LabelzoomUnit = _U("");
			styles.RemoveAll();
			style_ids.RemoveAll();
			IsVisbilityHasZoom = FALSE;
		}
		~LabelConf()
		{
			styles.RemoveAll();
			style_ids.RemoveAll();
		}
		UGbool autoLabel; //是否自动标注
		UGbool alongPath; //是否沿线标注
		UGbool visibility; //标注是否显示
		UGbool IsVisbilityHasZoom;
		UGString column; //要做Label的字段

		UGbool overlap;//是否压盖
		UGTextStyle style;//字体样式
		UGint position;//对齐方式

		//{{{ [9/6/2010 zhongdz] add
		UGArray<UGint> style_ids;
		UGArray<UGTextStyle> styles; 
		//}}}
		UGdouble LabelminZoom;//标注的最小显示
		UGdouble LabelmaxZoom;//标注的最大显示
		UGString LabelzoomUnit;//标注的单位
	};

	struct worStyle 
	{
		UGint styleid;
		UGint nwidth;
		UGint ncolor;
		worStyle(){
			styleid=nwidth=ncolor=-1;
		}
	};

	struct worSymbol{
		UGint styleid;
		UGint ncolor;
		UGint nsize;
		UGString strfont;// 符号的分组
		UGdouble dangle;
		worSymbol(){
			styleid=ncolor=nsize=-1;
			dangle = 0;
		}
	};

	struct worGlobalStyle 
	{
		worStyle globalPen; //global pen样式
		worStyle globalBrush; //global brush样式
		worSymbol globalSymbol; //global symblo样式
		worStyle globalLine; //global line样式
	};


	struct WorLayer
	{	
		WorLayer()
		{	
			map  = 0;
			name = _U("");
			tab  = _U("");	
			minZoom = 0.0;
			maxZoom = 0.0;
			crossOp = FALSE;
			dispType = UGFileParseWorkSpace::Off;
			zoomUnit = _U("");
			themes.RemoveAll();
		}
		~WorLayer()
		{
			themes.RemoveAll();
		}
		UGString name;//名称(对应)
		UGString tab;//所属tab
		//UGString data;//对应数据(实际存储到数据库的数据名称)
		DisplayType dispType; //显示方式		
		worGlobalStyle globalstyle;// global style样式
		UGArray<ThematicLayer> themes;//专题图集

		UGbool crossOp;//线要不要交叉优化

		LabelConf label;
		UGint map; // 所属地图

		UGdouble minZoom;//最小显示
		UGdouble maxZoom;//最大显示
		UGString zoomUnit;//zoom单位
	};

	struct WorMapInfo
	{	
		WorMapInfo()
		{
			name     = _U("");
			scale    = 0.0;
			centerX  = 0.0;
			centerY  = 0.0;
			winWidth = 0.0;
			layers.RemoveAll();
			winWidthUnit = _U("");
		}
		~WorMapInfo()
		{
			layers.RemoveAll();
		}

		UGString name;
		UGPrjCoordSys sr;
		UGdouble centerX;
		UGdouble centerY;
		UGdouble scale;//比例尺
		//UGString zoomUnit;//单位
		UGArray<WorLayer> layers;

		UGdouble winWidth; //窗口大小
		UGString winWidthUnit; //窗口大小单位
	};

	//! \brief 本类主要是工作空间文件格式的解析类。
	class UGWorParser
	{
	public:
		//! \brief 读取文件，进行解析
		virtual UGbool Read(UGString filename,UGString::Charset charset, UGString stymapFilePath) = 0;

		//! \brief 获取要导入有多少个tab
		virtual void GetLayers(UGArray<UGString>& tabs) = 0;

		//! \brief 获取要导入有多少个图层
		virtual void GetLayerNames(UGArray<UGString>& tabnames) = 0;

		//! \brief 获取地图数
		virtual UGint GetMapCount() = 0;

		//! \brief 获取一个地图里面的图层数据集合
		virtual void GetLayers(UGint iMap, UGArray<WorLayer>& layers) = 0;

		//void BindLayerData(const UGString& name, UGArray<UGString> datas);

		virtual UGbool GetMapInfo(UGint iMap, WorMapInfo& info) = 0;
	};

protected:
	//////////////////////////////////////////////////////////////////////////
	// 读
	//////////////////////////////////////////////////////////////////////////
	virtual UGbool ImportConf(UGDataSource* db, const UGImportParams& importParams, UGArray<UGString>& strSucMapNames) = 0;

protected:
	//工程文件分析类
	UGWorParser* m_parser;

};

} //namespace UGC

#endif // !defined(AFX_UGFileParseWorkSpace_H__9D5BD937_D091_4D5F_957C_94B8A7A74D92__INCLUDED_)

