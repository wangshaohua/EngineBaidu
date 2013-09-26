// UGDataHistory.h: interface for the UGDataHistory class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_UGDATAHISTORY_H__2D9823AA_E642_44D1_980A_A3807F5DD64F__INCLUDED_)
#define AFX_UGDATAHISTORY_H__2D9823AA_E642_44D1_980A_A3807F5DD64F__INCLUDED_

#include "Stream/ugdefs.h"
#include "Engine/UGRecordset.h"
#if !defined (IOS)
#include "Engine/UGDataPool.h"
#endif
namespace UGC
{
	//编辑历史信息,包含操作的什么图层,操作的对象id数组,操作的类型
	//##ModelId=48203056005E
	struct EditHistoryInfo 
	{
		//##ModelId=482030560060
		UGDatasetVector* pDatasetVector;
		//##ModelId=482030560061
		UGArray<UGint> nIDs;
		//##ModelId=48203056006D
		UGint nOptType;
	};

//##ModelId=48203056008C
#if defined (IOS)
    class UGDataset;
    class UGDataPool;
#endif
class ENGINE_API UGDataHistory  
{
public:
	//##ModelId=48203056008D
	//! \brief 构造函数
	UGDataHistory();
	//##ModelId=48203056009C
	//! \brief 析构函数
	virtual ~UGDataHistory();
public:
	//##ModelId=482030560149
	enum OptType
	{				//对象操作类型
		//##ModelId=48203056014B
			OPT_ADDNEW=0,		//添加新对象
		//##ModelId=48203056014C
			OPT_MODIFIED=1,		//对象有所改变
		//##ModelId=48203056014D
			OPT_DELETE=2,		//对象被删除
	};

public:
	//##ModelId=4820305600AB
	//! \brief RemoveAllEvent
	UGbool RemoveAllEvent();
	//##ModelId=4820305600AC
	//! \brief Goto
	UGbool Goto(UGint nEventIndex);							  //	

	//##ModelId=4820305600AE
	//! \brief 取得事件信息
	UGbool GetEventInfo(                                //取得事件信息
		UGint nEventIndex,                             //事件的索引
		UGint & nAction,                               //
		UGint & nLayerIndex,                           //事件所在图层，如果事件发生在多个图层，那么只返回最后一个图层的索引
		UGString & strNote);							  //事件说明	

	//##ModelId=4820305600B3
	//! \brief 当前事件的索引
	UGint GetCurrentIndex();                           //当前事件的索引

	//##ModelId=4820305600BB
	//! \brief 设置一个对象表中最大能容纳的记录数
	UGint GetCapacity();                               //设置一个对象表中最大能容纳的记录数

	//##ModelId=4820305600BC
	//! \brief 取得最大事件数
	UGint GetMaxEvtCount();                            //取得最大事件数

	//##ModelId=4820305600BD
	//! \brief 设置一个对象表中最大能容纳的记录数
	UGint SetCapacity(                                 //设置一个对象表中最大能容纳的记录数
		UGint lMaxSize);

	//##ModelId=4820305600BF
	//! \brief 设置最大事件数
	UGint SetMaxEvtCount(                              //设置最大事件数
		UGint lEvtCount);

	//##ModelId=4820305600C1
	//! \brief 按照索引删除事件
	UGbool RemoveEvent(	                              //按照索引删除事件
		int lEvtIndex);								  //事件的索引

	//##ModelId=4820305600C3
	//! \brief 开始一个事件
	UGbool BeginEvent(								  //开始一个事件	
		UGint nAction=0,								  //当前的action,如果为0
													  //表示使用绑定地图当前的action			
		UGString strEvtNote=_U(""));					  //事件的说明	

	//##ModelId=4820305600CD
	//! \brief 结束一个事件
	void EndEvent(									  //结束一个事件
		UGbool bRecord=TRUE);							  //是否对刚才发生的事件进行记录	
	

	//******************************************************************************//
   //*			此函数必须在beginevent和EndEvent之间调用,可以进行多之调用。		  *//
  //******************************************************************************//
	//##ModelId=4820305600DA
	//! \brief 设置事件的内容	
	UGbool SetEvtInfo(								  //设置事件的内容	
		OptType etype,								  //对象的操作类型
		UGRecordset* pRecordset,//对象所在记录集，不能为NULL
		UGbool bOne = false);	//是否仅设置一条记录，默认为否，是循环整个记录集		  

	//##ModelId=4820305600EA
	//! \brief 后退，撤销当前的事件，
	UGbool GoBack();									  //后退，撤销当前的事件，
													  //回到上一事件，成功返回true	

	//##ModelId=4820305600FA
	//! \brief 前进，恢复下一事件
	UGbool GoForward();                                 //前进，恢复下一事件

	//##ModelId=4820305600FB
	//! \brief 是否可以前进
	UGbool CanGoForward();							  //是否可以前进	

	//##ModelId=4820305600FC
	//! \brief 是否可以回退
	UGbool CanGoBack();								  //是否可以回退		

	
	//##ModelId=482030560109
	//! \brief 取得事件总数
	UGint GetEvtCount();								  //取得事件总数	
	
	//added by xielin 2007-05-23 
	//! \brief 数据集释放的时候调用该接口
	//##ModelId=48203056010A
	UGbool OnDatasetDestory(UGDataset* pDt);
	
	//! \brief 得到编辑的历史信息数组
	//##ModelId=48203056010C
	UGArray<EditHistoryInfo> GetEditHistoryInfo();

protected:
	//##ModelId=48203056010D
    
    UGDataPool * m_pDataPool;
	//##ModelId=482030560119
	UGString m_strEvtTbName;							  //事件表的名称
	//##ModelId=48203056011A
	UGbool m_bEvtBegin;								  //事件是否已经开始	
	//##ModelId=48203056011B
	UGint m_nAction;									  //事件的action	
	//##ModelId=48203056011C
	UGString m_strEvtNote;							  //事件的说明
	//##ModelId=482030560128
	UGArray<UGint> m_arEvtIndex;				  //事件的索引	
	//##ModelId=482030560129
	UGint m_nCurEvtIndex;							  //当前事件的索引	
	//{{qiuli 03.5.6
	//##ModelId=48203056012A
	UGbool m_bGoback;
	//}}qiuli 03.5.6

	//##ModelId=48203056012B
	UGArray<EditHistoryInfo> m_aryEditHistoryInfo;   //保存edit操作的历史记录信息,内部使用,不开放

private://抱歉啦，仅供内部使用！ 
	
	//在数据集中修改记录集中包含的对象
	//##ModelId=482030560138
	void ModifyGeometry(UGRecordset *pRs,				//记录集
						UGDatasetVector *pDtV);			//数据集

	//在数据集中添加记录集中包含的对象   
	//##ModelId=48203056013B
	void AddNewGeometry(UGRecordset *pRs,				//记录集
						UGDatasetVector *pDtV); 			//数据集
 
	//在数据集中删除记录集中包含的对象 
	//##ModelId=48203056013E
	void DeleteGeometry(UGRecordset *pRs,				//记录集
						UGDatasetVector * pDtV);			//数据集

};

}
#endif // !defined(AFX_UGDATAHISTORY_H__2D9823AA_E642_44D1_980A_A3807F5DD64F__INCLUDED_)

