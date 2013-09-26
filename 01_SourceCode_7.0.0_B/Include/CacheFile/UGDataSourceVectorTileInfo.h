
#ifndef __UGDATASOURCEVECTORINFO_H_
#define __UGDATASOURCEVECTORINFO_H_

#include "Stream/ugdefs.h"
#include "Projection/UGPrjCoordSys.h"
#include "Geometry/UGFeature.h"

namespace UGC 
{

	struct CACHEFILE_API UGDatasetVectorFieldInfo
	{
		UGString						m_strFieldName;			// 字段名
		UGFieldInfo::FieldType			m_nFieldType;			// 字段类型
		UGint							m_nFieldMaxLength;		// 字段最大长度
		UGint							m_nIndex;				// 字段索引

		UGDatasetVectorFieldInfo()
		{
			m_strFieldName = _U("");
			m_nFieldType = UGFieldInfo::UnKnown;
			m_nFieldMaxLength = 0;
			m_nIndex = 0;
		}
		~UGDatasetVectorFieldInfo(){};
		UGDatasetVectorFieldInfo& operator=(const UGDatasetVectorFieldInfo& fieldInfo);
	};

	class CACHEFILE_API UGDatasetVectorTileInfo 
	{
	public:
		UGDatasetVectorTileInfo();
		virtual ~UGDatasetVectorTileInfo();
		UGDatasetVectorTileInfo& operator=(const UGDatasetVectorTileInfo& vectorInfo);


	public:
		//! \brief 获取数据集名
		UGString						GetDatasetName();
		void							SetDatasetName(UGString strDatasetName);

		//! \brief 获取数据集类型
		UGint							GetDatasetType();
		void							SetDatasetType(UGint nDatasetType);


		//! \brief 获取数据集索引信息
		UGint							GetDatasetIndex();
		void							SetDatasetIndex(UGint nIndex);

		//! \brief 获取数据集字段信息
		UGArray<UGDatasetVectorFieldInfo*>	GetDatasetFieldInfos()const;
		void								SetDatasetFieldInfos(UGArray<UGDatasetVectorFieldInfo*> arrFieldInfos);

		//! \brief 设置/获取数据集投影信息
		UGPrjCoordSys& GetPrjCoordSys();
		void SetPrjCoordSys(const UGPrjCoordSys& PrjCoordSys);	

		// 仅在UGDataSourceVectorTileInfo的ToXML/FromXML时候调用
		void SetPrjCoordSysIndex(UGint nPrjCoordSysIndex);	
		UGint GetPrjCoordSysIndex()const;

	private:
		void clear();


	private:

		UGString							m_strDatasetName;			// 数据集名
		UGint								m_nDatasetType;				// 数据集类型
		UGint								m_nIndex;					// 数据集索引
		UGPrjCoordSys						m_PrjCoordSys;				// 数据集投影信息
		UGint								m_nPrjCoordSysIndex;		// 投影对象的索引
		UGArray<UGDatasetVectorFieldInfo*>	m_arrDatasetFieldInfos;		// 数据集字段信息集合

	};

	class CACHEFILE_API UGDataSourceVectorTileInfo
	{
	public:
		UGDataSourceVectorTileInfo(void);
		virtual ~UGDataSourceVectorTileInfo(void);
		UGDataSourceVectorTileInfo& operator=(const UGDataSourceVectorTileInfo& dataSourceInfo);

		UGArray<UGDatasetVectorTileInfo*> GetDatasetVectorInfos()const;
		
		//! \brief 导入导出配置文件
		UGbool FromXML(UGString strPath);
		UGbool ToXML(UGString strPathName);

		//! \brief 将字段拆分成简单字段数组
		//! \param strField [in] 传入的字段表达式
		//! \param arrDelimas [out] 顺序的运算符数组
		//! \return 拆分后的字段数组
		static UGArray<UGString> SplitToSampleField(UGString strField, UGArray<UGString> &arrDelimas);
		
	private:
		void clear();

	protected:
		UGArray<UGDatasetVectorTileInfo*>	m_arrDatasetVectorInfo;  // 数据集矢量信息集合
		UGString							m_strDataSourceName;	 // 数据源名称

	};
}

#endif //__UGDATASOURCEVECTORINFO_H_
