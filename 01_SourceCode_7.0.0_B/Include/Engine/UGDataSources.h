// UGDataSources.h: interface for the UGDataSources class.
//
//////////////////////////////////////////////////////////////////////

/*!
   **************************************************************************************
    \file     UGDataSources.h
   **************************************************************************************
    \author   陈国雄
    \brief    数据源指针管理类，通过数据源指针与数据源别名的一一对应关系进行管理，
			  并保证数据源别名的唯一性。                                                    
    \attention   
   ----------------------------------------------------------------------------------<br>
    Copyright (c) 1996-2005 SuperMap GIS Technologies,Inc.                           <br>
    All Rights Reserved.                                                             <br>
   ----------------------------------------------------------------------------------<br> 
   
   **************************************************************************************
    \version 2005-05-19  陈国雄    初始化版本.                                       <br>
   **************************************************************************************
*/

#if !defined(AFX_UGDATASOURCES_H__70B46E96_726D_4AAD_A846_D57BCD50C9D0__INCLUDED_)
#define AFX_UGDATASOURCES_H__70B46E96_726D_4AAD_A846_D57BCD50C9D0__INCLUDED_

#include "Base/OgdcDict.h"
#include "Engine/UGDataSource.h"

namespace UGC {

typedef void (UGSTDCALL *DatasourcesXMLProc)(UGString* xml);


//##ModelId=48203051033C
class ENGINE_API UGDataSources  
{	
public:
	//##ModelId=48203051033D
	UGDataSources();
	//##ModelId=48203051033E
#ifdef SYMBIAN60
	~UGDataSources();
#else
	virtual ~UGDataSources();
#endif
	

public:
	//========================================================
	//! \brief 		通过数据源别名查找数据源指针。
	//! \return 	UGbool 如果找到就返回true，否则就返回false。
	//! \param 		strAlias 数据源别名。
	//! \param 		pResDataSource 返回数据源指针。
	//##ModelId=48203051034B
	UGbool Lookup (const UGString& strAlias, UGDataSource* &pResDataSource)const;
	//========================================================
	//! \brief 		得到数据源的数目。
	//! \return 	UGint 如果没有数据源就返回0。
	//##ModelId=48203051034F
	UGint GetCount()const;
	//========================================================
	//! \brief 		是否不存在数据源。
	//! \return 	UGbool 如果没有数据源就返回true，否则就返回false。
	//##ModelId=482030510351
	UGbool IsEmpty()const;
	//========================================================
	//! \brief 		清空并释放数据源指针。
	//##ModelId=482030510353
	void RemoveAll();
	//========================================================
	//! \brief 		设置修改指定别名的数据源指针，如果别名不存在就新增一个数据源指针。
	//! \return 	void
	//! \param 		strAlias 数据源别名，不能为空字符串。
	//! \param 		pDataSource 数据源指针，不能为NULL。
	//##ModelId=48203051035B
	void SetAt(const UGString& strAlias, UGDataSource *pDataSource);	
	//========================================================
	//! \brief 		得到指定索引的数据源别名和指针。
	//! \return 	UGbool 如果找到就返回true，否则就返回false。
	//! \param 		nIndex 索引位置，必须大于等于0，小于最大数。
	//! \param 		strAlias 返回数据源别名。
	//! \param 		pDataSource 返回数据源指针。
	//##ModelId=48203051035E
	UGbool GetAt(UGint nIndex, UGString& strAlias, UGDataSource *&pDataSource)const;

	//========================================================
	//! \brief 		移走指定别名的数据源指针，并释放数据源指针。
	//! \return 	UGbool 如果别名存在就返回true，否则就返回false。
	//! \param 		strAlias 数据源别名。
	//##ModelId=482030510363
	UGbool ReleaseAt(const UGString& strAlias);
	//========================================================
	//! \brief 		移走指定索引位置的数据源指针，并释放数据源指针。
	//! \return 	UGbool 如果成功就返回true，否则就返回false。
	//! \param 		nIndex 索引位置，必须大于等于0，小于最大数。
	//##ModelId=48203051036B
	UGbool ReleaseAt(UGint nIndex);
	
	//========================================================
	//! \brief 		通过数据源别名查找索引。
	//! \return 	UGint 索引，如果找到就返回索引，否则就返回-1。
	//! \param 		UGString 数据源别名。
	//##ModelId=48203051036D
	UGint FindAlias(const UGString& strAlias)const;	
	
	//========================================================
	//! \brief 		通过数据源指针查找数据源别名。
	//! \return 	UGString 数据源别名，如果找到就返回数据源别名，否则就返回空字符串。
	//! \param 		pDataSource 数据源指针，不能为NULL。
	//##ModelId=482030510370
	UGString GetAlias(UGDataSource* pDataSource)const;

	//========================================================
	//! \brief 		得到指定索引位置的数据源别名。
	//! \return 	UGString 数据源别名，如果找到就返回数据源别名，否则就返回空字符串。
	//! \param 		nIndex 索引位置，必须大于等于0，小于最大数。
	//##ModelId=48203051037A
	UGString GetAliasAt(UGint nIndex)const;
	//========================================================
	//! \brief 		设置修改标识，不仅对自己起作用，而且对所有有修改标识的成员都起作用。
	//! \return 	void
	//! \param 		bModified 修改标识。
	//##ModelId=48203051037D
	void SetModifiedFlag(UGbool bModified = true);
	//========================================================
	//! \brief 		判断是否有修改，包括任一成员的修改。
	//! \return 	UGbool 如果有修改就返回true，否则就返回false。
	//##ModelId=48203051037F
	UGbool IsModified()const;
	//========================================================
	//! \brief 		移走指定索引的数据源指针，但不释放数据源指针。
	//! \return 	UGDataSource* 返回数据源指针，如果移除不成功就返回NULL。
	//! \param 		nIndex 索引位置，必须大于等于0，小于最大数。
	//##ModelId=482030510381
	UGDataSource* RemoveAt(UGint nIndex);
	//========================================================
	//! \brief 		插入一个指定别名的数据源指针。
	//! \return 	UGbool 如果别名存在就就返回false，否则就返回true。
	//! \param 		strAlias 数据源别名，不能为空字符串。
	//! \param 		pDataSource 数据源指针，不能为NULL。
	//##ModelId=48203051038B
	UGbool Insert(const UGString& strAlias, UGDataSource* pDataSource);	
	//========================================================
	//! \brief 		相当于RemoveAll()。
	//! \return 	void
	//##ModelId=48203051038E
	void Reset();												
	//========================================================
	//! \brief 	重命名	
	//! \return 	UGbool
	//! \param 		strAlias
	//! \param 		strNewAlias
	//##ModelId=48203051038F
	UGbool Rename(const UGString& strAlias, const UGString& strNewAlias);	
	//========================================================
	//! \brief 		数据源别名是否存在。
	//! \return 	UGbool 如果别名存在就返回true，否则就返回false。
	//! \param 		strAlias 数据源别名。
	//##ModelId=482030510399
	UGbool IsAliasExisted(const UGString& strAlias)const;					
		
	//========================================================
	//! \brief 		解析包含数据源信息的XML字符串，构造数据源指针集合，并连接或打开数据源。
	//! \return 	UGbool 如果成功就返回true，否则就返回false。
	//! \param 		strXML 包含数据源信息的XML字符串。
	//! \param 		strWorkspaceName 工作空间全路径名。
	//! \param 		nVersion 工作空间版本号。
	//##ModelId=48203051039C
	UGbool FromXML(const UGString &strXML, const UGString &strWorkspaceName, UGint nVersion = 0,const UGString& strPWD = (_U("")));//!\modified by macx 2008.8.4 支持工作空间密码
	//========================================================
	//! \brief 		把数据源连接信息保存未XML字符串。
	//! \return 	UGString 返回包含数据源信息的XML字符串，如果不成功就返回空字符串。
	//! \param 		strWorkspaceName 工作空间全路径名。
	//! \param 		nVersion 工作空间版本号。
	//##ModelId=4820305103A0
	UGString ToXML(const UGString &strWorkspaceName, UGint nVersion = 0, const UGString& strPWD = (_U("")))const;//!\modified by macx 2008.8.4 支持工作空间密码

public:
	//! \brief 		是否修改标识。
	//##ModelId=4820305103A4
	UGbool m_bModified;		
	//! \brief 		数据源集合。
	//##ModelId=4820305103A9
	UGDict<UGString,UGDataSource*> m_Datasources;	
	//! \brief 		数据源别名数组。
	//##ModelId=4820305103AA
	UGArray<UGString> m_strArrNames;	

	// 需要在外部做一个另存一个错误版本的工作空间的工具，但是为了缩小体积
	// 不带任何的sdx，导致打开工作空间时丢失了数据源信息，再保存的时候数据源节点就没有导出
	// 所以通过这两个回调在读取的时候将数据源xml传递到外面保存，存储的时候将xml传回来
	// 写回文件里面，在ugc工程里面没有使用，但是不要随便删除
	// add by gouyu 2012-9-18
	static DatasourcesXMLProc g_DatasourcesToXML;
	static DatasourcesXMLProc g_DatasourcesFromXML;
};

}

#endif // !defined(AFX_UGDATASOURCES_H__70B46E96_726D_4AAD_A846_D57BCD50C9D0__INCLUDED_)

