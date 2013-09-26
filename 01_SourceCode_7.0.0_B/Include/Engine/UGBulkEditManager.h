#ifndef SUPERMAP_ENGINE_UGBuldEditManager_H
#define SUPERMAP_ENGINE_UGBuldEditManager_H

#include "Engine/UGRecordset.h"
#include "Geometry/UGFeature.h"

namespace UGC
{
class UGRecordset;

struct UGBinaryFieldInfo
{
public:
	UGBinaryFieldInfo()
	{
		pData = NULL;
		nSize = 0;
	};

	~UGBinaryFieldInfo()
	{
		if (pData!= NULL)
		{
			delete[] pData;
			pData = NULL;
		}

		nSize =0;
	};

public:

	UGbyte *pData;
	UGuint nSize;
};

struct UGBulkAddInfo

{
	UGbool bHasStyle;
	UGbool bBigGeo;		
	UGint  nSMID;		
	UGint  nGeoSize;

	//如果是等长存储，该值为0，
	//不等长时，该值为geometry在m_pBulkGeoBuffer中偏移量，
	//如果是大对象该值为在m_arrBigGeoData中索引号
	UGint  nGeoOffset;
	UGint  nGeoType;

	//如果是等长存储，该值为0，
	//不等长时，该值为该条记录的属性值在m_pBulkAttrBuffer中偏移量，
	UGint  nAttrOffset;
	UGint  nAttrSize;

};

struct UGModifyFieldInfo
{
public:
	UGString m_strFieldName;
	UGVariant m_newValue;
};

struct UGModifyGeoInfo
{
public:
	UGModifyGeoInfo()
	{
		m_pNewGeometry = NULL;
		m_nOldIndex = 0;
	};
	virtual ~UGModifyGeoInfo() 
	{
		if (m_pNewGeometry!= NULL)
		{
			delete m_pNewGeometry;
			m_pNewGeometry = NULL;	
		}				
	};

public:
	UGGeometry* m_pNewGeometry;
	UGRect2D m_oldBounds;
	UGint m_nOldIndex;
};

struct UGModifyInfo
{
public:
	UGModifyInfo()
	{
		m_SMID = -1;
		m_pModifyGeoInfo = NULL;
		m_arrModifyFieldInfos.SetSize(0);
	};
	~UGModifyInfo()
	{		
		if (m_pModifyGeoInfo != NULL)
		{
			delete m_pModifyGeoInfo;
			m_pModifyGeoInfo = NULL;
		}			

		for (UGint i = 0; i < m_arrModifyFieldInfos.GetSize(); ++i)
		{
			delete m_arrModifyFieldInfos[i];				
			m_arrModifyFieldInfos[i] = NULL;
		}

		m_arrModifyFieldInfos.RemoveAll();
	};

public:
	UGint m_SMID;			
	UGModifyGeoInfo * m_pModifyGeoInfo;
	UGArray<UGModifyFieldInfo*> m_arrModifyFieldInfos;
};

class ENGINE_API UGBulkEditManager
{
	friend class UGRecordset;

public:
	UGBulkEditManager(UGRecordset * pRecordset);
	virtual ~UGBulkEditManager();


	virtual UGbool Init();		 
	//添加指定的pFeature
	virtual UGint AddOneFeature(UGFeature * pFeature);

	//添加一个默认的pFeature
	virtual UGFeature* AddOneFeature();

	virtual UGbool Delete();

	virtual UGbool SetFieldValue(const UGString &strFieldName,const UGVariant &varValue);

	virtual UGbool SetGeometry(UGGeometry *pGeometry);


	virtual UGbool GetFieldValue(const UGString &strFieldName,UGVariant &varValue);

	virtual UGbool GetGeometry(UGGeometry *&pGeometry);

	virtual UGint GetID();

	virtual UGbool Update(void);

	virtual UGbool CancelUpdate(void);

	virtual void SetBulkEditMaxCount(UGuint nMaxCount){m_nBulkEditMaxCount = nMaxCount;};

	virtual UGuint GetBulkEditMaxCount(void){return m_nBulkEditMaxCount;};

	virtual void SetSmIDBegin(UGuint nSmIDBegin){m_nSmIDBegin = nSmIDBegin;};

	virtual UGint SetOneFeature(UGGeometry *pGeometry, UGbool bModifyGeometry, const UGArray<UGString> &aryFields, const UGArray<UGVariant> &aryValues);

	virtual UGuint GetSmIDBegin(){return m_nSmIDBegin;};

	//在添加的Features中查找制定的nSMID记录
	//并将CurrentIndex到当前nSmID所在的记录上
	virtual UGbool SeekID(UGint nSMID);

	virtual void Clear(UGbool bFree);

	virtual UGint GetCurrentIndex();

	virtual UGbool SetCurrentIndex(UGint nCurrentIndx);	

	virtual UGint GetFieldDataSize(const UGFieldInfo &fieldInfo);

	virtual UGint GetFieldDataSize(const UGFieldDefine &fieldInfo);
	
	virtual UGbool FillFieldData(UGint nIndex, UGint nFieldIndex, UGbool bFind,const UGVariant &varVal);

	//将pGeometry中数据存放在制定的位置pPos,如果数据长度大于m_nGeoSize，直接返回false
	virtual UGbool FillGeoData(UGint nIndex,const UGGeometry* pGeometry, UGBulkAddInfo *pBulkAddInfo);

	//该方法获取新添加的geometry在geoBuffer中存储的起始位置
	//如果是等长的，结果为nIndex * m_nGeoSize
	//如果是不等长的，算法由个引擎自己决定，比如udb，是m_nBulkGeoBufferSize - m_nBulkGeoLeft
	virtual UGint GetGeoOffset(UGint nIndex);	

protected:		
	void Check();
	virtual UGint  GetActualRecordCount();
	virtual UGbool PreSysFieldInfos();
	virtual UGbool FillSystemFieldData(UGint nIndex,UGGeometry *pGeometry,UGint nSMID);	

	virtual UGbool AddBounds(UGint nIndex,const UGGeometry *pGeometry);

	//nIndex：在m_arrBulkAddInfos中的索引号
	//nFieldIndex : 在m_FieldInfos中的索引号
	//varValue:新的字段值
	virtual UGbool SetFieldValue(UGint nIndex,UGint nFieldIndex,const UGVariant &varValue);
	virtual UGbool GetFieldValue(UGint nIndex,UGint nFieldIndex,UGVariant &varValue);
	virtual UGbool GetFieldValue(UGVariant &varValue,UGbyte *pData,const UGFieldInfo &fieldInfo);

	virtual UGbool GetDefaultValue(UGFieldInfo &fieldInfo, UGVariant &varValue);
	
	virtual UGbool SetGeometry(UGint nIndex,UGGeometry *pGeometry);
	virtual UGbool GetGeometry(UGGeometry *&pGeometry,UGint nIndex);

	virtual UGbool InitBulkBuffer();

	UGint GetFieldIndex(const UGString &strFieldName);
	virtual UGbool AddFieldInfo(const UGString & strFieldName);
	virtual UGbool AddFieldInfo(const UGFieldInfo &fieldInfo);	

protected:
	UGArray<UGFeature *> m_arrFeatures;

	UGRecordset *m_pRecordset;

	UGuint m_nBulkEditMaxCount;

	UGuint m_nSmIDBegin;

	UGArray<UGint> m_arrDeleteIDs;

	UGArray<UGModifyInfo*> m_arrModifyInfos;

	UGint m_nCurrentEditCount;

	UGint m_nMaxGeoSize;

	UGbyte* m_pBulkGeoBuffer;
	UGbyte* m_pBulkAttrBuffer;
	UGuint m_nBulkGeoBufferSize;
	UGuint m_nBulkAttrBufferSize;
	UGshort * m_pBulkIndicators;
	UGuint m_nBulkIndsSize;
		 

	//记录每个字段的偏移，顺寻和记录集中字段的顺序一致
	UGArray<UGint> m_arrFieldOffset;

	//每条记录属性的长度
	UGint m_nAttributeSize;

	//为每个Geometry分配的空间
	UGint m_nGeoSize;

	//批量添加对应的字段信息
	UGFieldInfos m_FieldInfos;

	UGDict<UGString,UGint> m_dictFieldIndexes;

	//批量添加过程中新添加的对象的范围
	UGRect2D m_newBulkBounds;

	//标记是否使用需要Geometry
	UGbool m_bHasGeometry;

	//存储大对象
	UGArray<UGbyte *> m_arrBigGeoData;

	UGArray<UGBulkAddInfo*> m_arrBulkAddInfos;

	UGint m_nBulkAddIndex;

	//存放bulkAddInfos中各几何对象的范围，为维护空间索引时使用
	UGArray<UGRect2D> m_arrBulkAddBounds;

	//如果是动态索引，该数组存放每个geometry的
	UGArray<UGArray<UGPoint> *> m_arrBulkAddGrids;

	UGuint m_nHasSetFieldCount;


	UGArray<UGint> m_arrBulkAddFieldIndex;
	

	//第一个UGint 为SMID,第二个UGint为FieldIndex
	UGDict<UGint,UGDict<UGint,UGBinaryFieldInfo* >* > m_dictBinaryFields;

	
public:
	UGFeature * m_pTemplateFeature;

};



}

#endif