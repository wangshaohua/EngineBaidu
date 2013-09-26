// UGDataSourceGMap.cpp: implementation of the UGDataSourceGMap class.
//
//////////////////////////////////////////////////////////////////////

#include "Stream/UGFile.h"
#if !defined OS_ANDROID && !defined IOS
#include "EngineOGDC/UGDataSourceOgdc.h"
#endif
#include "FileParser/UGImageManager.h"
#include "Engine/UGDatasetRasterWeb.h"
#include "MapServiceStub/UGBaiDuMapsParams.h"
#include "EngineBaiduMaps/UGDataSourceBaiduMap.h"
#include "EngineBaiduMaps/UGDatasetRasterBaiduMaps.h"
#include "MapServiceStub/UGMapServiceParamsManager.h"
#include "MapServiceStub/UGMapServiceStubManager.h"
#include "NetToolkit/UGHttpHelper.h"
#include "Toolkit/UGMarkup.h"
#include "Toolkit/UGLogFile.h"

namespace UGC
{
#if !defined OS_ANDROID && !defined IOS
	UGDataSource* CreateDataSource()
	{
		UGDataSourceBaiduMap* pDataSource = new UGDataSourceBaiduMap;
		return pDataSource;
	}

	OgdcDataSource* CreateOgdcDataSource()
	{
		UGDataSourceOgdc* pOgdcDataSource = new UGDataSourceOgdc;
		UGDataSourceBaiduMap* pDataSource = new UGDataSourceBaiduMap;
		pOgdcDataSource->SetDataSource(pDataSource);
		return pOgdcDataSource;
	}
#else
	UGDataSource* CreateBaiduMapDataSource()
	{
		UGDataSourceBaiduMap* pDataSource = new UGDataSourceBaiduMap;
		return pDataSource;
	}

#endif

	UGDataSourceBaiduMap::UGDataSourceBaiduMap() : UGDataSource()
	{
		m_Connection.m_nType = UGC::BaiDu;
		m_Connection.m_bReadOnly = TRUE; // 只能是只读
		m_nEngineClass = 3;
		m_prjCoordSys.SetPlanar(AU_METER);
	}

	UGDataSourceBaiduMap::~UGDataSourceBaiduMap()
	{
		Close();
	}
     
	UGbool UGDataSourceBaiduMap::Open()
	{	
		UGMutexLock mutex(m_mutex);
		mutex.lock();

		if(m_bOpened)
		{
			return TRUE;
		}	
		UGint i = 0;

		UGBaiDuMapsParams* pBaiduMapsParams = NULL;
		// BaiDu的3种图层;
		UGArray<UGString> arrMapTypes;
	    GetAllLayers(arrMapTypes);
		for(i = 0; i < arrMapTypes.GetSize(); ++i)
		{
			
			pBaiduMapsParams = (UGBaiDuMapsParams*)UGMapServiceParamsManager::MakeParams(UGC::BaiDu);
			if(pBaiduMapsParams != NULL)
			{	
				pBaiduMapsParams->m_strMapType = arrMapTypes[i];
				UGDatasetRasterBaiduMaps* pDatasetRaster = new UGDatasetRasterBaiduMaps;
				pDatasetRaster->SetDataSource(this);
				pDatasetRaster->SetMapServiceParams(pBaiduMapsParams);
				//设置数据集属性
				UGDatasetRasterInfo *pDtRasterInfo = pDatasetRaster->GetInfo();
				pDtRasterInfo->m_strName	  = pBaiduMapsParams->m_strMapType;
				pDtRasterInfo->m_strTableName = pBaiduMapsParams->m_strMapType;
				pDtRasterInfo->m_nType = UGDataset::MBImage;
				UGBandInfo bandInfo;
				bandInfo.SetPixelFormat(IPF_RGBA);
				pDtRasterInfo->Add(bandInfo);
				//pDtRasterInfo->m_nBandCount = 1;
				//pDtRasterInfo->SetPixelFormat(IPF_RGBA);
				pDtRasterInfo->m_nWidth= pBaiduMapsParams->m_nTileSize * pow(2.0, pBaiduMapsParams->m_nLevel);
				pDtRasterInfo->m_nHeight=pBaiduMapsParams->m_nTileSize * pow(2.0, pBaiduMapsParams->m_nLevel);
				pDtRasterInfo->m_rc2Bounds = pBaiduMapsParams->m_rcBounds;
				pDatasetRaster->SetPrjCoordSys(pBaiduMapsParams->m_prjCoordSys);
				//translate 图层透明掉
                if (pBaiduMapsParams->m_strMapType.CompareNoCase(_U("Roadnetwork"))==0)
                {
					pDatasetRaster->SetCanBeTransparent(TRUE);
                }
				//设置缓存路径
				UGString strPath = m_Connection.m_strDatabase;
				strPath.TrimLeft();
				strPath.TrimRight();
				if (!strPath.IsEmpty())
				{
					pDatasetRaster->SetBufferPath(strPath);
				}
				m_Datasets.Add(pDatasetRaster);
				m_bOpened = TRUE;
			}
		}

		//创建3维城市数据集
        Create3DMapDatasetS();
		m_Connection.m_bReadOnly = TRUE;
		return m_bOpened;
	}
   
	void UGDataSourceBaiduMap::Close()
	{
		SaveInfo();
		UGint nDatasetCount = m_Datasets.GetSize();
		for(UGint i=0;i<nDatasetCount;i++)
		{
			UGDataset* pDataset = m_Datasets.GetAt(i);
			pDataset->Close();
			delete pDataset;
			pDataset = NULL;
		}
		m_Datasets.RemoveAll();
		m_bOpened = FALSE;
	}
	
	void UGDataSourceBaiduMap::Create3DMapDatasetS()
	{   
		UGString strXmlPath =  UGFile::GetModulePath(_U("SuBase"))+_U("Resource/BMapCitySetting.xml");
		UGMarkup markup;
		UGMapServiceStub* pMapServiceStub = NULL;
		UGBaiDuMapsParams* pBaiduMapsParams = NULL;
		if (markup.Load(strXmlPath)) //加载xml文件
		{
			UGString strElemData =_U("");
			if (markup.FindElem(_U("CityParameters")))
			{   
				while (markup.FindChildElem(_U("sml:CityElem")))
				{
					pMapServiceStub = UGMapServiceStubManager::CreateMapServiceStub(UGC::BaiDu);
					pBaiduMapsParams = (UGBaiDuMapsParams*)UGMapServiceParamsManager::MakeParams(UGC::BaiDu);
					if (pBaiduMapsParams!=NULL&&pMapServiceStub!=NULL)
					{
						markup.IntoElem();
						if (markup.FindChildElem(_U("sml:CityName")))
						{
							strElemData = markup.GetChildData();
							pBaiduMapsParams->m_strMapType = strElemData;
						}
						if (markup.FindChildElem(_U("sml:CityMark")))
						{
							strElemData = markup.GetChildData();
							pBaiduMapsParams->m_strCityMark = strElemData;
						}
						if (markup.FindChildElem(_U("sml:CityNumber")))
						{
							strElemData = markup.GetChildData();
							pBaiduMapsParams->m_nCityNumber = strElemData.ToInt();
						}
						if (markup.FindChildElem(_U("sml:Left")))
						{
							strElemData = markup.GetChildData();
							pBaiduMapsParams->m_rcBounds.left = strElemData.ToDouble();
						}
						if (markup.FindChildElem(_U("sml:Right")))
						{
							strElemData = markup.GetChildData();
							pBaiduMapsParams->m_rcBounds.right = strElemData.ToDouble();
						}
						if (markup.FindChildElem(_U("sml:Top")))
						{
							strElemData  = markup.GetChildData();
							pBaiduMapsParams->m_rcBounds.top = strElemData.ToDouble();
						}
						if (markup.FindChildElem(_U("sml:Bottom")))
						{
							strElemData = markup.GetChildData();
							pBaiduMapsParams->m_rcBounds.bottom =strElemData.ToDouble();
						}
						if (markup.FindChildElem(_U("sml:OrignX")))
						{
							strElemData = markup.GetChildData();
							pBaiduMapsParams->m_pntOrigin.x = strElemData.ToDouble();
						}
						if (markup.FindChildElem(_U("sml:OrignY")))
						{
							strElemData = markup.GetChildData();
							pBaiduMapsParams->m_pntOrigin.y = strElemData.ToDouble();
						}
						markup.OutOfElem();

						//创建栅格数据集
						UGDatasetRasterBaiduMaps * pBaiduDataSetRaster = new UGDatasetRasterBaiduMaps;
						if (pBaiduDataSetRaster!=NULL)
						{   
							pBaiduDataSetRaster->SetDataSource(this);
							pBaiduDataSetRaster->SetMapServiceParams(pBaiduMapsParams);
							pBaiduDataSetRaster->SetMapServiceStub(pMapServiceStub);
							UGDatasetRasterInfo  * pDtRasterinfo = pBaiduDataSetRaster->GetInfo();
							pDtRasterinfo->m_strName	  = pBaiduMapsParams->m_strMapType;
							pDtRasterinfo->m_strTableName = pBaiduMapsParams->m_strMapType;
							pDtRasterinfo->m_nType = UGDataset::MBImage;
							UGBandInfo bandInfo;
							bandInfo.SetPixelFormat(IPF_RGBA);
							pDtRasterinfo->Add(bandInfo);
							//pDtRasterInfo->m_nBandCount = 1;
							//pDtRasterInfo->SetPixelFormat(IPF_RGBA);
							pDtRasterinfo->m_nWidth= pBaiduMapsParams->m_nTileSize * pow(2.0, pBaiduMapsParams->m_nLevel);
							pDtRasterinfo->m_nHeight=pBaiduMapsParams->m_nTileSize * pow(2.0, pBaiduMapsParams->m_nLevel);
							pDtRasterinfo->m_rc2Bounds = pBaiduMapsParams->m_rcBounds;
							pBaiduDataSetRaster->SetPrjCoordSys(pBaiduMapsParams->m_prjCoordSys);
							m_Datasets.Add(pBaiduDataSetRaster);
						}

					}
				}	
			}
		}		
	}

	UGbool UGDataSourceBaiduMap::SaveInfo()
	{
		if (IsModified())
		{

		}
		SetModifiedFlag(FALSE);
		return TRUE;
	}
    
	UGString UGDataSourceBaiduMap::GetEngineName() const
	{
		return _U("BaiDuMap Plugin Data Engine");
	}

	UGint UGDataSourceBaiduMap::GetVersion()	
	{
		return 1000;
	}

	UGbool UGDataSourceBaiduMap::IsConnected()
	{
		if( m_bOpened == FALSE )
		{
			return FALSE;
		}
		return TRUE;
	}

	//! \brief 获取所有可显示的图层
	void UGDataSourceBaiduMap::GetAllLayers(UGArray<UGString>& arrLayers) const
	{	
		arrLayers.Add(_U("TrafficMap"));
		arrLayers.Add(_U("Satellite"));
		arrLayers.Add(_U("RoadNetwork"));
	}
}