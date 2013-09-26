// UGDatasetRasterBaiduMaps.cpp: implementation of the UGDatasetRasterBaiduMaps class.
//
//////////////////////////////////////////////////////////////////////
#include "Toolkit/UGRegistry.h"
#include "Stream/UGFile.h"
#include "Toolkit/UGLogFile.h"
#include "Engine/UGDataSource.h"
#include "MapServiceStub/UGMapServiceStub.h"
#include "EngineBaiduMaps/UGDatasetRasterBaiduMaps.h"
#include "PluginMapCache50/UGPluginMapCache50.h"
#include "MapServiceStub/UGBaiDuMapsParams.h"
#include "Toolkit/UGImgToolkit.h"
#include "FileParser/UGExchangeFileType.h"
#include "FileParser/UGExchangeParamsManager.h"
#include "FileParser/UGFileParseToolkit.h"
#include "Toolkit/UGPalette.h"
#include "MapServiceStub/UGMapServiceStubManager.h"
#include "FileParser/UGImageManager.h"

namespace UGC
{

	UGDatasetRasterBaiduMaps::UGDatasetRasterBaiduMaps()
	{
		m_pImagePlugin =NULL;
	}

	UGDatasetRasterBaiduMaps::~UGDatasetRasterBaiduMaps()
	{
		Close();
		if(m_pMapServiceParams)
		{
			delete m_pMapServiceParams;
			m_pMapServiceParams = NULL;
		}

		if(m_pMapServiceStub)
		{
			delete m_pMapServiceStub;
			m_pMapServiceStub = NULL;
		}

		if (m_pImagePlugin)
		{
			delete m_pImagePlugin;
			m_pImagePlugin =NULL;
		}
	}

	void UGDatasetRasterBaiduMaps::Close()
	{
		if(m_pMapServiceStub)
		{
			m_pMapServiceStub->Close();
		}
		if(m_pLocalManager)
		{
			delete m_pLocalManager;
			m_pLocalManager = NULL;
		}

		m_bOpened = FALSE;
	}	

	UGbool UGDatasetRasterBaiduMaps::Open()
	{	
		// 加锁
		UGMutexLock mutex(m_mutex);
		mutex.lock();

		if(IsOpen())
		{	
			return TRUE;
		}
        
		m_pImagePlugin = UGImageManager::CreateImagePlugin(PC_WEBCACHE);

		if(m_pMapServiceParams && m_pImagePlugin && m_pDataSource
			&& UGC::BaiDu == m_pDataSource->GetEngineType()
			&& UGMapServiceType::BaiDu == m_pMapServiceParams->GetServiceType())
		{	

			// 获取设置的google
			UGBaiDuMapsParams*	pBaiduMapsParams = (UGBaiDuMapsParams*)m_pMapServiceParams;
			UGString strMapType = pBaiduMapsParams->m_strMapType;

			// 读出缓存路径
			UGString strBuffPath = GetBufferPath();

			strBuffPath.TrimLeft();
			strBuffPath.TrimRight();
			//如果路径不是以“/”
			if (strBuffPath.Right(1) != _U("/"))
			{
				strBuffPath += _U("/");
			}

			strBuffPath += _U("BaiduMap/")+ strMapType + _U("/") + pBaiduMapsParams->m_strMapName + UG_ABSCACHEFILE_EXT;

			// 创建或打开缓存文件
			if(!UGFile::IsExist(strBuffPath))
			{	// 无SCI则先创建
				m_pLocalManager   = new UGLocalCacheManager;
				m_pMapServiceStub = UGMapServiceStubManager::CreateMapServiceStub(UGMapServiceType::BaiDu);
				if(NULL == m_pLocalManager || NULL == m_pMapServiceStub)
				{
					return m_bOpened;
				}

				m_pLocalManager->SetVersion(Version_50);
				//设置provider
				m_pLocalManager->SetServiceProvider(pBaiduMapsParams->m_strBaseURL );

				UGString strDir=UGFile::GetDir(strBuffPath);
				UGbool bIsFileExist = TRUE; //缓存路径存在设置标志
				if(!UGFile::IsExist(strDir))
				{ 
					if(!UGFile::MkDirEx(strDir))
					{
						UGERROR(UGS_CREATE_FILE_FAILED);
						bIsFileExist = FALSE;
					}
				}
				if (bIsFileExist)
				{
					m_bOpened = m_pLocalManager->Create(strBuffPath);
					if(m_bOpened)
					{	
						m_pMapServiceStub->SetLocalCacheManager(m_pLocalManager);
						m_bOpened = m_pMapServiceStub->Open(m_pMapServiceParams);
					}
				}
			}

			m_bOpened = m_pImagePlugin->Open(strBuffPath, 0x00000001, NULL);

			if(!m_bOpened)
			{	
				delete m_pLocalManager;
				m_pLocalManager = NULL;

				return m_bOpened;
			}
			UGImgBlocksManager imgBM;
			imgBM.SetDataset(this);
			m_arrImgManager.Add(imgBM);
			//m_ImgManager.SetDataset(this);
		}
		return m_bOpened;
	}

	

	UGSize UGDatasetRasterBaiduMaps::GetTileSize()
	{
		UGSize nTileSize;
		if (m_pImagePlugin != NULL)
		{
			nTileSize = m_pImagePlugin->GetTileSize();
		}

		return nTileSize;
	}

	//! \brief 获取当前设置的显示图层
	void UGDatasetRasterBaiduMaps::GetCurrentVisibleLayers(UGArray<UGString>& arrLayers) const
	{	
		UGBaiDuMapsParams*	pBaiDuMapsParams = (UGBaiDuMapsParams*)m_pMapServiceParams;
		if(pBaiDuMapsParams)
		{
			arrLayers.Add(pBaiDuMapsParams->m_strMapType);
		}
	}

	UGString UGDatasetRasterBaiduMaps::ParamsToString() const
	{	
		return m_strBufferPath;
	}

	void UGDatasetRasterBaiduMaps::StringToParams(const UGString& strParams)
	{	
		m_strBufferPath = strParams;

	} 

	void UGDatasetRasterBaiduMaps::SetDownloadResponseFunc(DownloadResponseFunc pFunc,UGlong pWnd)
	{
		if (m_pImagePlugin)
		{
			m_pImagePlugin->SetDownloadResponseFunc(pFunc, pWnd);
		}
	}

	UGbool UGDatasetRasterBaiduMaps::Request(const UGdouble& dScale, const UGRect2D& bound, UGbool bCallBack /* = TRUE */)
	{
		if (!m_bOpened)
		{
			return FALSE;
		}

		if (m_pImagePlugin)
		{
			return m_pImagePlugin->Request(dScale, bound, bCallBack);
		}
		else
		{
			return FALSE;
		}
	}

	UGSize2D UGDatasetRasterBaiduMaps::GetTileMPSize(UGdouble dMapScale)
	{
		if (m_pImagePlugin)
		{
			return m_pImagePlugin->GetTileMPSize(dMapScale);
		}
		return UGSize2D();
	}

	const UGArray<UGdouble> UGDatasetRasterBaiduMaps::GetScales() const 
	{
		if (m_pImagePlugin)
		{
			return m_pImagePlugin->GetScales();
		}
		return UGArray<UGdouble>();
	}

	UGbool UGDatasetRasterBaiduMaps::IsComplete()
	{
		if (m_pImagePlugin)
		{
			return m_pImagePlugin->IsCompleteRequest();
		}
		else
		{
			return TRUE;
		}
	}

	void UGDatasetRasterBaiduMaps::SetDataChangedFunc(DataChangedProc pFunc,UGlong pWnd)
	{
		if (m_pImagePlugin)
		{
			m_pImagePlugin->SetDataChangedFunc(pFunc, pWnd);
		}
	}

	UGTiles* UGDatasetRasterBaiduMaps::QueryWithBounds(const UGRect2D& rcMapBounds, UGdouble dScale) const 
	{
		if (m_pImagePlugin)
		{
			return m_pImagePlugin->QueryWithBounds(rcMapBounds, dScale);
		}
		else
		{
			return NULL;
		}
	}

	UGImageData* UGDatasetRasterBaiduMaps::LoadTileImageData(const UGTile& tile) 
	{
		if (m_pImagePlugin)
		{   
			UGImageData *pResult = NULL;
			pResult = m_pImagePlugin->LoadTileImageData(tile);
			UGString strMsg;
			strMsg.Format(_U("%d行，%d列"),const_cast<UGTile&>(tile).GetTileCol(),\
			const_cast<UGTile&>(tile).GetTileRow());
			if (pResult==NULL)
			{   
				UGERROR(strMsg+_U("加载数据失败!"));
			}	
			return  pResult;

			//m_pImagePlugin->LoadTileImageData(tile);
		}
		else
		{
			return NULL;
		}
	}


	UGdouble UGDatasetRasterBaiduMaps::ScaleToNearFixScale(UGdouble dScale) 
	{
		if (m_pImagePlugin)
		{
			return m_pImagePlugin->ScaleToNearFixScale(dScale);
		} 
		else
		{
			return 0.0;
		}
	}


	UGRect2D UGDatasetRasterBaiduMaps::ComputeTilesBounds(UGdouble dMapScale, const UGRect2D& rcMapBounds, UGint nExtTileSize /* =1 */) 
	{
		if (m_pImagePlugin)
		{
			return m_pImagePlugin->ComputeTilesBounds(dMapScale, rcMapBounds, nExtTileSize);
		} 
		else
		{
			return UGRect2D();
		}
	}

	UGdouble UGDatasetRasterBaiduMaps::GetCoordRatio()
	{
		if (m_pImagePlugin)
		{
			return m_pImagePlugin->GetCoordRatio();
		}
		else
		{
			return 0.0;
		}
	}

	UGbool UGDatasetRasterBaiduMaps::IsAllTilesExist(const UGRect2D& rcMapBounds, UGdouble dScale) const
	{
		if (m_pImagePlugin)
		{
			return m_pImagePlugin->IsAllTilesExist(rcMapBounds, dScale);
		}
		else
		{
			return false;
		}
	}

	UGint UGDatasetRasterBaiduMaps::GetCacheVersion() const
	{
		if (m_pImagePlugin)
		{
			return (UGint)m_pImagePlugin->GetCacheVersion();
		} 
		else
		{
			return NULL;
		}
	}

	UGdouble UGDatasetRasterBaiduMaps::GetCacheCoordRatio()
	{
		if (m_pImagePlugin)
		{
			return m_pImagePlugin->GetCoordRatio();
		} 
		else
		{
			return NULL;
		}
	}

	UGImgBlock* UGDatasetRasterBaiduMaps::GetViewBlock(const UGRect2D& rcView, UGint nDeviceWidth, UGint nDeviceHeight, UGbool &bFinished) 
	{
		m_mutex.lock();

		if (!m_bOpened)
		{
			return NULL;
		}

		if (m_pImagePlugin == NULL)
		{
			return NULL;
		}

		UGRect2D rcBounds = rcView;
		rcBounds.Normalize();
		rcBounds.IntersectRect(rcBounds, GetBounds());

		nDeviceWidth = UGROUND(rcBounds.Width()/rcView.Width()*nDeviceWidth);
		nDeviceHeight = UGROUND(rcBounds.Height()/rcView.Height()*nDeviceHeight);

		if(m_pImagePlugin->SetViewPort(rcBounds.left, rcBounds.top, rcBounds.right, rcBounds.bottom, 
			nDeviceWidth, nDeviceHeight))
		{	
			bFinished = m_pImagePlugin->IsFinished();
			UGint nViewWidth,nViewHeight;
			if(!m_pImagePlugin->GetViewImageSize(nViewWidth, nViewHeight))
			{
				m_mutex.unlock();
				return NULL;
			}
			ImagePixelFormat pixelFormat;
			m_pImagePlugin->GetPixelFormat(pixelFormat);

			UGImgBlock* pResBlock = new UGImgBlock;
			pResBlock->m_nWidth = nViewWidth;
			pResBlock->m_nHeight = nViewHeight;
			pResBlock->m_nValidWidth = pResBlock->m_nWidth;
			pResBlock->m_nValidHeight = pResBlock->m_nHeight;
			pResBlock->m_nPixelFormat = (UGPixelFormat)pixelFormat;
			pResBlock->m_rcBounds = rcBounds;
			pResBlock->m_nWidthBytes = UGImgToolkit::AlignWidth(pResBlock->m_nPixelFormat, pResBlock->m_nWidth);
			pResBlock->Init();

			UGint nDataSize = m_pImagePlugin->GetViewImageDataSize();
			nDataSize = UGMIN(pResBlock->GetByteSize(), nDataSize);
			UGbyte* pData = (UGbyte*)pResBlock->GetBlockData(); 

			if(m_pImagePlugin->GetViewImageData(pData, nDataSize))
			{
				m_mutex.unlock();
				return pResBlock;
			}

			delete pResBlock;
			pResBlock = NULL;
		}
		bFinished = FALSE;

		m_mutex.unlock();
		return NULL;

	}
   
}

