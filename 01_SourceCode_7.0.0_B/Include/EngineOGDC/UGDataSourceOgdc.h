// UGDataSourceOgdc.h: interface for the UGDataSourceOgdc class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_UGDATASOURCEOGDC_H__6D84965C_9B6F_4AA7_8854_7412060D5D18__INCLUDED_)
#define AFX_UGDATASOURCEOGDC_H__6D84965C_9B6F_4AA7_8854_7412060D5D18__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Engine/UGDataSource.h"

namespace UGC {

//##ModelId=483BB70902FD1
class ENGINEOGDC_API UGDataSourceOgdc : public OgdcDataSource  
{
public:
	//##ModelId=483BB70902FF
	UGDataSourceOgdc();
	//##ModelId=483BB709030D
	virtual ~UGDataSourceOgdc();

// 纯虚函数
public:
	//! \brief 创建数据源,需要预先设置好连接信息。
	//##ModelId=483BB709030F
	virtual OgdcBool Create();
	
	//! \brief 打开数据源,需要预先设置好连接信息。
	//##ModelId=483BB7090311
	virtual OgdcBool Open();

	//! \brief 关闭数据源。
	//##ModelId=483BB7090313
	virtual void Close();

	//! \brief 判断数据源是否已经打开。
	//! \return 打开返回TRUE，失败返回FALSE。
	//##ModelId=483BB709031C
	virtual OgdcBool IsOpen() const;

	//! \brief 获取数据集个数。
	//! \return 数据集个数。
	//##ModelId=483BB709031E
	virtual OgdcInt GetDatasetCount() const;

	//! \brief 通过序号获取数据集指针。
	//! \return 数据集指针。
	//##ModelId=483BB7090320
	virtual OgdcDataset* GetDataset(OgdcInt nIndex) const;

	//! \brief 获取指定名称的数据集指针。
	//! \param strDatasetName 数据集名[in]。
	//! \return 数据集指针。
	//##ModelId=483BB7090323
	virtual OgdcDataset* GetDataset(const OgdcString& strDatasetName) const;
	
	//! \brief 通过数据集名称删除数据集。
	//! \param strDatasetName 数据集名称[in]。
	//! \return 是否成功删除，成功返回TRUE，失败返回FALSE。
	//##ModelId=483BB709032E
	virtual OgdcBool DeleteDataset(const OgdcString& strDatasetName);
	
	//! \brief 通过矢量数据集描述信息：DatasetVectorInfo创建数据。
	//! \param vInfo 矢量数据集描述信息对象[in]。
	//! \return 矢量数据集指针。
	//##ModelId=483BB7090331
	virtual OgdcDatasetVector* CreateDatasetVector(const OgdcDatasetVectorInfo& vInfo);	
	
	//! \brief 通过栅格数据集描述信息：DatasetRasterInfo创建数据集。
	//! \param rInfo 栅格数据集描述信息对象[in]。
	//! \param bIsMBRaster 是否以多波段方式创建数据集[in]。
	//! \return 栅格数据集指针。
	//##ModelId=483BB7090334
	virtual OgdcDatasetRaster* CreateDatasetRaster(const OgdcDatasetRasterInfo& rInfo,OgdcBool bIsMBRaster = FALSE);	

	//! \brief 通过现有数据集模板创建数据集。
	//! \param &strNewName 新数据集名[in]。
	//! \param pReferenceDataset 参考数据集指针，即模板创建数据集指针[in]。
	//! \return 新数据集指针。
	//##ModelId=483BB709033C
	virtual OgdcDataset* CreateDatasetFrom(const OgdcString &strNewName, OgdcDataset* pReferenceDataset);

	//! \brief 复制数据集。
	//! \param pSrcDataset 源数据集指针[in]。
	//! \param strDestDatasetName 目的数据集名[in]。
	//! \param bBuildIndexOrPyramid 是否给栅格数据集建立金字塔，默认不建[in]。
	//! \return 目的数据集指针。
	//##ModelId=483BB7090340
	virtual OgdcDataset* CopyDataset(OgdcDataset* pSrcDataset, 
		const OgdcString& strDestDatasetName, OgdcBool bBuildIndexOrPyramid = FALSE);

	//! \brief 保存数据信息。
	//##ModelId=483BB7090345
	virtual OgdcBool SaveInfo();

public:	
	//! \brief 设置投影坐标系。
	//! \param coordSys [in]。
	//##ModelId=483BB709034B
	virtual OgdcBool SetCoordSys(const OgdcCoordSys& coordSys);	

	//! \brief 得到投影坐标系。
	//##ModelId=483BB709034E
	virtual OgdcBool GetCoordSys(OgdcCoordSys& coordSys);	

	//! \brief 执行SQL语句。
	//! \param strSQL SQL语句[in]。
	//! \return 是否成功执行，成功返回TRUE，失败返回FALSE。
	//! \remarks 主要用于在数据库级执行的数据操作。
	//##ModelId=483BB7090351
	virtual OgdcBool Execute(const OgdcString& strSQL);	
	
	//! \brief 数据源是否和数据连接。
	//##ModelId=483BB7090354
	virtual OgdcBool IsConnected();
	
	//! \brief 仅仅连接数据库,不刷新数据集等。
	//##ModelId=483BB7090356
	virtual OgdcBool Connect();	
	
	//! \brief 获取最后更新时间。
	//##ModelId=483BB709035C
	virtual OgdcTime GetDateLastUpdated();
	
	//! \brief 获取创建时间。
	//##ModelId=483BB709035E
	virtual OgdcTime GetDateCreated();	
	
	//! \brief 修改密码。
	//! \param strNewPassword 新密码[in]。
	//! \return 修改成功返回TRUE，失败返回FALSE。
	//##ModelId=483BB7090360
	virtual OgdcBool ChangePassword(const OgdcString& strNewPassword);
	
	//! \brief 获取引擎名称。
	//! \return 引擎名称。
	//##ModelId=483BB7090363
	virtual OgdcString GetEngineName() const ;
	
	//! \brief 生成一个数据源中目前没有的数据集名字。
	//! \param strDatasetName 指定一个数据集名[in]。
	//! \return 根据指定名生成的加有唯一识别的数据集名。
	//##ModelId=483BB7090365
	virtual OgdcString GetUnoccupiedDatasetName(const OgdcString& strDatasetName);	
	
	//! \brief 判断数据集名称是否合法。
	//! \param strDatasetName 数据集名[in]。
	//! \param nState 数据集或字段命名错误类型[out]。
	//! \return 名称是否合法，是返回TRUE，否则返回FALSE。
	//##ModelId=483BB709036B
	virtual OgdcBool IsAvailableDatasetName(const OgdcString& strDatasetName);

	//! \brief 获取数据源版本号。
	//! \return 数据源版本号。
	//##ModelId=483BB709036E
	virtual OgdcInt GetVersion();		
	
	//! \brief 开始事务。
	//! \return 是否成功开始事务，成功返回TRUE，失败返回FALSE。
	//##ModelId=483BB7090370
	virtual OgdcBool BeginTrans();
	
	//! \brief 提交事务。
	//! \return 是否成功提交事务，成功返回TRUE，失败返回FALSE。
	//##ModelId=483BB7090372
	virtual void Commit();
	
	//! \brief 撤消事务。
	//! \return 是否成功撤消事务，成功返回TRUE，失败返回FALSE。
	//##ModelId=483BB7090374
	virtual void Rollback();
	
	//! \brief 判断事务是否开始 
	//##ModelId=483BB7090376
	virtual OgdcBool IsTransStarted() const ;

	//! \brief 判断数据源是否支持短事务操作
	//! \return 支持返回TRUE，不支持返回FALSE。
	//##ModelId=483BB709037A
	virtual OgdcBool IsTransacted() const;
	
	//! \brief 获取密码。
	//! \remarks 通过获取连接信息也可以得到密码。
	//##ModelId=483BB709037C
	virtual OgdcString GetPassword() const;

	//! \brief 获取数据源名称。
	//##ModelId=483BB709037E
	virtual OgdcString GetName() const ;

	//! \brief 获取引擎类型
	//##ModelId=483BB7090380
	virtual OgdcInt GetEngineType() const;

	//! \brief 获取引擎分类
	//##ModelId=482030520128
	virtual  UGint GetEngineClass() const;

	//! \brief 获取文件型引擎的后缀名
	//##ModelId=48203052012A
	virtual UGString GetEnginePostfix() const ;

	//! \brief 判断数据源是否被修改。
	//! \return 被修改返回TRUE，否则返回FALSE。
	//##ModelId=483BB7090382
	virtual OgdcBool IsModified();

	//! \brief 设置数据源是否被修改。
	//! \param bModified 数据源是否被修改布尔值，默认为修改[in]。
	//##ModelId=483BB7090384
	virtual void SetModifiedFlag(OgdcBool bModified = TRUE);
	
	//! \brief 获取数据源的别名。
	//! \return 数据源的别名。
	//##ModelId=483BB709038A
	virtual OgdcString GetAlias() const;

	//! \brief 设置数据源的别名
	//! \param strAlias 数据源的别名[in]。
	//##ModelId=483BB709038C
	virtual void SetAlias(const OgdcString& strAlias);
	
	//! \brief 判断传入的字段名或表名是否可用。
	//! \param 字段名或表名是否可用。
	//! \param nState 数据集或属性字段命名错误类型。
	//! \return	可用返回TRUE，不可用返回FALSE。
	//##ModelId=483BB709038F
	virtual OgdcBool IsValidFieldOrTableName(const OgdcString& strFieldOrTableName);
	
	//! \brief 设置数据源描述信息。
	//! \param strDescription 数据源描述信息[in]。
	//##ModelId=483BB7090392
	virtual void SetDescription(OgdcString strDescription);
	
	//! \brief 获取数据源描述信息。
	//! \return 数据源描述信息。
	//##ModelId=483BB7090395
	virtual OgdcString GetDescription();

	//! \brief 初始化元数据库类
	//! \return 元数据库类的指针
	//##ModelId=483BB7090397
	virtual OgdcMetaDatabase * InitMetaDatabase();

	//! \brief 获取元数据库类
	//! \return 元数据库类的指针
	//! \remarks 若在调用此函数之前没有调用InitMetaDatabase，则返回为NULL
	//##ModelId=483BB709039A
	virtual OgdcMetaDatabase * GetMetaDatabase();
	
	//##ModelId=483BB709039C
	UGDataSource* GetDataSource() const;
	//##ModelId=483BB709039E
	void SetDataSource(UGDataSource* pDataSource);

	//! \brief 删除当前的数据源(会自动删除所有数据集，最后删除所有系统表和系统对象)
	//! \remark 调用此方法后，可以再次创建同参数的数据源
	//! \attention 仅数据库类型的数据源需要实现此方法，文件型数据源不处理
	virtual OgdcBool DropDataSource();


protected:	
	//##ModelId=483BB70903A0
	UGDataSource* m_pDataSource;
	//##ModelId=483BB70903AA
	UGArray<OgdcDataset*> m_Datasets;

};

}

#endif // !defined(AFX_UGDATASOURCEOGDC_H__6D84965C_9B6F_4AA7_8854_7412060D5D18__INCLUDED_)

