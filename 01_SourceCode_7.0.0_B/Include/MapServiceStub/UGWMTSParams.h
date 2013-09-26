//////////////////////////////////////////////////////////////////////////
//                    _   _   ____   ____                    
//   Project         | | | | / ___) / ___)                   
//                   | | | || | __ | |                       
//                   | |_| || |_\ || \___                    
//                    \____/ \____| \ ___)     6.0           
//                                                           
//!  \file headerfile.h
//!  \brief Class 的接口定义。
//!  \details 服务参数详细信息。
//!  \author 数据转换组。
//!  \attention 
//!   Copyright (c) 1996-2008 SuperMap Software Limited Company.  <br> 
//!   All Rights Reserved.
//!  \version 6.0
//////////////////////////////////////////////////////////////////////////


#if !defined(AFX_UGWMTSPARAMS_H__08BADC84_B1E9_40CA_B1AE_A7755CC63F16__INCLUDED_)
#define AFX_UGWMTSPARAMS_H__08BADC84_B1E9_40CA_B1AE_A7755CC63F16__INCLUDED_

#include "MapServiceStub/UGMapServiceParams.h"
#include "MapServiceStub/UGMapServiceType.h"

namespace UGC {

	//! \brief 超图云服务参数配置。
	class MAPSERVICESTUB_API UGWMTSParams : public UGMapServiceParams
	{
	public:
		//! \brief 构造函数。
		//! \remarks 。
		UGWMTSParams();

		//! \brief 构造函数。
		//! \remarks 。
		UGWMTSParams(const UGWMTSParams& ugWMTSParams);

		//! \brief 析构函数。
		//! \remarks 。
		virtual ~UGWMTSParams();

	public:

		//! \brief 重载获取服务类型的函数。
		//! \param  [in]。
		//! \return 。
		//! \remarks 。
		//! \attention 。
		virtual UGint GetServiceType() const	{ return UGMapServiceType::WMTS; }

		//! \brief 通过URL初始化地图参数
		virtual UGbool InitParams();

		virtual void GetAllLayers(UGArray<UGString>& arrLayers) const;

		//! \brief 通过本地sci文件初始化地图参数
		virtual UGbool FromLocalCache(const UGString& strCacheFile);

		//! \brief 获取xml相对于缓存的目录，即webcache之后的目录
		//! \brief 主要用于在无网络时也可以通过xml打开所有的Layer图片
		//! \biref 如: /WMTS/map-china400/wmts100/wmts100.xml 
		virtual UGString GetXMLRelativePath();

		//! \brief 获取.sci相对于缓存的目录，即webcache之后的目录
		//! \brief 主要用于在无网络时也可以通过xml打开所有的Layer图片
		//! \biref 如Chin是m_strMapType的话  则返回 /WMTS/map-china400/wmts100/China/China.sci 
		virtual UGString GetLayerRelativePath();
		
		//! 设置缓存的文件夹的目录
		//! 比如D:\Buffer
		void SetBufferPath(const UGString& strBufferPath);
		
		//! 获取比例尺与名称的对应关系
		std::map<UGdouble, UGString> GetOutputScaleCaptions();
		
		//! 获取图层的参数
		UGWMTSParams* GetLayerParams(const UGString& strLayer);

		//! \brief 获取图层对应的TileMatrix集合的名称
		UGString GetTileMatrixSet() const;

		//! \brief 获取WMTS图层名称。
		UGString GetLayerName() const;
		
		//! \brief 获取WMTS图层名称。
		UGString GetLayerAlias() const;

		UGbool LoadAllLayerParams(const UGString& strPathXML);

		// !---------------- 图层的信息 -----------------
		// !   单个图层应该含有的WMTS参数信息 用于图层请求Tile时使用		

		//! \brief WMTS图层类型名称。
		UGString m_strLayerName;

		//! \brief WMTS图层类型别名。
		UGString m_strLayerAlias;

		//! \brief 图层风格名称
		UGString m_strStyle;

		//! \brief 图层的像素格式
		UGString m_strFormat;

		//! \brief 图层块集合名称
		UGString m_strTileMatrixSet;

		//! \brie 图层比例尺和比例尺名称的映射关系
		std::map<UGdouble, UGString> m_mapOutputScaleCaptions;


		// !---------------- 解析时使用的临时记录 --------------

		//! \brief 图层名称和对应的图层参数的映射关系 
		//! \brief 每有一个Layer就会增加1
		UGDict<UGString, UGWMTSParams*> m_dictWMTSParams;

		//! \brief 是否透明
		UGbool m_bTransparent;

		//! \brief 区分wmts服务是否是天地图服务
		//! \无语了天地图和iserver发布的wmts服务的规格不一致两者均宣称是标准wmts服务，这里只能加一个变量区分一下看到底是哪一种服务
		UGbool m_bIsTianDiTu;

	private:
		UGbool ParseURL();
		
		//! \brief 获取投影
		//! \param Prj 投影
		//! \param strCRS 如EPSG:4326
		UGbool GetProjectionByName(UGPrjCoordSys& Prj, const UGString& strCRS );
        
		//! \brief 根据图层标识获取对应图层的参数类指针
		UGWMTSParams* GetParamsByLayerIdentifier(UGString strLayerIdentifier)const;

		// !---------------- WMTS服务的信息-----------------
		//! \brief 服务的基础地址
		UGString m_strHost;

		//! \brief 服务的缓存地址
		UGString m_strServerPath;

		//! \brief 服务的版本号
		UGString m_strVersion;

		//! \brief 缓存的路径 如D:\Buffer
		UGString m_strBufferPath;

	

	};

} //namespace UGC
#endif // !defined(AFX_UGSMICLOUDPARAMS_H__08BADC84_B1E9_40CA_B1AE_A7755CC63F16__INCLUDED_)

