//////////////////////////////////////////////////////////////////////////
//!  \file     UGTextureLib.h:
//!  \brief	   三维纹理库
//!  \details  实现纹理库类对三维纹理进行添加删除和读取操作
//!  \author   wangmao/yaoyh。
//!  \attention 
//!   Copyright (c) 1997-2010 SuperMap GIS Technologies,Inc.  <br>
//!   All Rights Reserved.
//!  \version 1.0
//////////////////////////////////////////////////////////////////////////
#ifndef UGTEXTURELIB_H
#define UGTEXTURELIB_H

#include "Stream/ugdefs.h"
#include "Engine/UGDataset.h"
#include "Toolkit/UGTextureInfo.h"

#define TEXTURE_CACHE_COUNT (10)

namespace UGC {

	class UGDataSource;
	
	class ENGINE_API UGTextureLib
	{
	public:
			typedef struct  
			{
				UGString strKey;
				UGuint   nRefCount;
				UGTextureInfo data;
			}NodeCache;

			// 构造和析构函数
			// 传入的数据源必须非空并且是打开的,否则构建的纹理库将无法正常使用
			UGTextureLib(UGDataSource* pDs);
			UGTextureLib();
			~UGTextureLib();

			// 给数据源成员赋值
			void SetDataSource(UGDataSource* pDs);

			// 创建一个纹理管理器
			// 如果创建成功返回TRUE,否则返回FALSE
			// note:如果已经纹理管理器已经存在返回创建成功
			// 返回值， 为-1 表示创建失败  为0表示已经存在， 为1表示创建成功
			UGbool  CreateTextureLib();

			// 删除纹理管理器
			// 成功返回TRUE,否则返回FALSE
			UGbool  DeleteTextureLib();

			// 存储纹理,如果该纹理ID已经存在,则引用计数+1
			// 纹理不存在时自动添加纹理
			// 存储参数 UGTextureData封装的纹理数据
			// 成功返回TRUE,否则返回FALSE
			UGbool	AddTexture(const UGTextureInfo& textureData);

			//为纹理增加引用计数,失败返回FALSE,否则返回TRUE
			//这个功能可以适当提高添加纹理的性能
			UGbool AddReference(const UGString& argstrkey);

			// 根据纹理的ID和等级获取nLevel级的纹理数据
			// nLevel为纹理等级,0为最精细纹理,负数或者大于纹理最高级别时取最粗糙纹理
			// 获取纹理数据 UGTextureData
			// 成功返回TRUE,否则返回FALSE
			UGbool GetTexture(UGTextureInfo& textureData,UGbool bLoadCompress=TRUE);

			//! \brief 获取压缩的纹理数据，此数据不进行解压
			//! \param textureInfo 保存获取的纹理信息		
			//! \return 成功返回TRUE, 否则返回FALSE
			UGbool GetCompressTexture(UGTextureInfo& textureInfo);

			// 根据纹理的ID卸载纹理,如果该纹理ID已经存在,则引用计数-1
			// 引用计数为0时自动删除纹理
			// 成功返回TRUE,否则返回FALSE
			UGbool  DeleteTexture(const UGString& strkey);

			// 设置最大的纹理图片大小,模型数据集默认值为512,从效果上看这个值已经足够
			// 如果纹理图片超过了这个值会进行一下适当的缩放
			UGbool SetMaxTexureSize(const UGuint size);;
	private:
			// 创建纹理信息表
			UGbool CreateTextureTable();
			
			// 依据纹理数据信息UGTextureData， 更新纹理金字塔属性表
			// nTextureID 是表示纹理在纹理属性表中的SmID
			// textureData 表示的是纹理的信息
			// 返回共创建了多少层金字塔
			UGbool UpdateTextureTier(const UGTextureInfo& textureData,UGVariant& varImageData);
			
			// 根据外部给定的关键字计算唯一的整数ID
			UGuint  GetMapCode(const UGString& strkey);	

			// UDB加速
			void UDBBeginTrans();
			// UDB加速
			void UDBEndTrans();

			// 是否在缓存中
			UGuint IsCacheTexture(UGString& strKey);

			// 添加到缓存中去
			void   AddToCache(UGString& strKey,UGuint nRefCount,const UGTextureInfo& textureData);

			// 保存数据流的长度到流的最开始
			void  SaveDataSize(UGuchar* pBuffer,UGuint size);

			// 得到数据流的长度
			UGuint LoadDataSize(UGuchar* pBuffer);

			// 纹理库关联的数据源
			UGDataSource* m_pDataSource;
			
			NodeCache     m_TextureCache[TEXTURE_CACHE_COUNT];

			// 是否需要交换大小端
			UGbool m_bBigEndian;

			// 最大纹理的大小
			UGuint m_nMaxTexSize;

			// 不使用的两个函数接口
			const UGTextureLib& operator=(const UGTextureLib&);
			UGTextureLib(const UGTextureLib&);

			// 找到一个最近的2的倍数的整数
			UGuint NearP2(UGuint val);

			// 最大纹理调整
			void  LimitMaxTexture(UGuint &width,UGuint &height);
	};
}

#endif // !defined(UGTEXTURELIB_H)

