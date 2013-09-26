// UGDataPool.h: interface for the UGDataPool class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_UGDATAPOOL_H__C7A7F855_B011_4769_8E30_FD51EEF9A26D__INCLUDED_)
#define AFX_UGDATAPOOL_H__C7A7F855_B011_4769_8E30_FD51EEF9A26D__INCLUDED_

#include "Base/ogdcdefs.h"
#include "Base/OgdcString.h"
#include "Engine/UGDatasetVector.h"
#include "Engine/UGDataSource.h"

//=====================================================================================
#define EVTINFTB		_U("EventInfo")			//保存所有事件表信息的表名
#define EVTTB			_U("EventTable")			//唯一的事件表表名
#define EVTTBNAME		_U("EventTbName")		//事件表的表名
#define EVTTBID			_U("EvtTbID")			//事件表的id
#define CUREVTID		_U("CurrentEvt")		//当前事件的id
#define EVTCOUNT		_U("EventCount")		//事件的数目
#define LASTEVTID		_U("LstEventID")		//最新的EventID
#define FIRSTEVTID		_U("FrtEventID")		//最早的EventID

#define OBJINFTB		_U("ObjInf")			//保存所有对象表信息的表名
#define OBJTBNAME		_U("ObjTbName")			//对象表的表名
#define DATASETHANDLE   _U("DatasetHandle")         //数据集的指针
#define OBJTBID			_U("ObjTbID")			//对象表的ID
#define OBJTBREF		_U("ObjTbRef")			//对象表引用计数
#define OBJTBISSDB      _U("objTbIsSDB")		//是否保存了sdb数据集的数据	
#define OBJTBHASSTYLE   _U("objTbHasStyle")	    //是否有[smEvtGeoStyle]字段

#define	EVTID			_U("EventID")			//事件的id
#define EVTACTION		_U("EventAction")       //事件对应的Action值
#define EVTLAYER		_U("EventLayer")		//事件所发生的图层
#define EVTNOTE			_U("EventNote")			//事件的说明
#define EVTORDERID		_U("EventOrdID")		//事件先后顺序
#define SUBEVTID		_U("SubEventID")		//子事件的id，added by xielin 用于一个事件中有几个子事件的情况

#define	OBJID			_U("ObjectID")		//对象的id
#define EVTOPERATOR		_U("ObjOperator")		//事件中对象所作的操作
#define EVTGEOINDEX		_U("ObjIndexPos")	    //事件中几何对象在sdb中的索引

#define NOTTHISTB     0						//表不存在
#define EVTTYPETB		1						//事件表	
#define OBJTYPETB     2						//对象表

#define TEXTFIELDSIZE   80						//文本类型的字段长度

#define HANDLETEXTSIZE  /*8*/	10 				//因为udb不支持8个字节的整型，存指针只能用text来存  //Mao_Wang修改了这个长度因为发现vc9下边长度为9

#define SDBENGINE       1                       //是否时SDB引擎
#define GEOHASSTYLE     2                       //几何对象是否有SYTLE
//=====================================================================================



namespace UGC
{

//##ModelId=4820305503C8
class ENGINE_API UGDataPool  
{
public:
	//##ModelId=4820305503C9
	//! \brief 构造函数
	UGDataPool();
	//##ModelId=4820305503CA
	//! \brief 袭构函数
	virtual ~UGDataPool();

public:
	//##ModelId=4820305503D8
	//! \brief 清空一个事件表 
	UGbool ClearEvtTable(	                        //清空一个事件表 
		UGString strEvtTbName);                  //事件表的名称

	//##ModelId=4820305503DA
	//! \brief 通过一个数据集建立对象表
	UGbool CreateObjectTableFromDataset(          //通过一个数据集建立对象表 
		UGDatasetVector * pDtV);

	//##ModelId=4820305503DC
	//! \brief 创建并打开数据库,如果名字为空，系统会起一个随机的名字
	UGbool CreateDatabase(						//创建并打开数据库,如果名字为空，系统会起一个随机的名字
		 UGString strDbName=_U(""));				//数据库名
	//##ModelId=482030560000
	//! \brief 关闭并删除数据库
	void DestoryDatabase();						//关闭并删除数据库
	//##ModelId=482030560001
	//! \brief 打开数据库
	UGbool OpenDatabase();						//打开数据库
	//##ModelId=482030560002
	//! \brief 关闭数据库
	UGbool CloseDatabase();						//关闭数据库

	//##ModelId=48203056000F
	//! \brief 通过表的ID来获得表名
	UGbool GetTbNameFromID(	                    //通过表的ID来获得表名
		UGString & strTbName,					//表名
		UGint  nTbType,							//表的类型，SMEVTTYPETB（事件表）或SMOBJTYPETB（对象表）
		const UGint & nTbID);					//表的ID
												//成功返回TRUE,失败返回FALSE

	//##ModelId=482030560013
	//! \brief 取得一个表的大小  
	UGint GetTbSize(                             //取得一个表的大小   
		UGString strTbName);                    //表名  
	
	//##ModelId=482030560015
	//! \brief 判断一个表的类型
	UGint GetTbType(								//判断一个表的类型
		UGString strTableName,                   //表名
		UGint & lTableID);					    //表的ID
												//该函数返回值含义:
	                                            //-1:出错了，数据库没有打开
												//SMNOTTHISTB，表不存在；
												//SMEVTTYPETB，Event表；
												//SMOBJTYPETB, Object表。

	//##ModelId=48203056001F
	//! \brief 根据object表名取得数据集的指针
	UGbool GetDatasetHandleFromObjTbName(	            //根据object表名取得数据集的指针
		const UGString & strObjTbName,           //对象表名
		UGlong & lDatasetHandle);                //数据集指针

	//##ModelId=482030560022
	//! \brief 根据数据集指针取得obj表的名称
	UGbool GetObjTbNameFromDatasetHandle(             //根据数据集指针取得obj表的名称
		const UGlong & lDatasetHandle,           //数据集指针
		UGString & strObjTbName);                //对象表的名称
	
	//##ModelId=482030560025
	//! \brief 新建一个EventTable
	UGbool CreateEventTable(	                    //新建一个EventTable
		UGString strTbName,                      //EventTable的表名
		UGFieldInfos * pFieldInfoList);       //字段列表

	//##ModelId=482030560028
	//! \brief 删除一个保存地图操作的表，当地图
	UGbool DeleteEventTable(						//删除一个保存地图操作的表，当地图
		                                        //关闭时要记住调用他哦
		UGString strTableName);					//表名
	
	
	
	//##ModelId=48203056002F
	//! \brief 清理数据库中所有的表
	UGbool Purge();								//清理数据库中所有的表

	//*******************************************************************************************//
	//一般objTable和数据集一一对应，当objTable对应的数据集所关联的图层全部关闭时方可删除此对象表 //
	//*******************************************************************************************//	
	//##ModelId=482030560030
	//! \brief 删除一个保存几何对象及其属性的表，
	UGbool DeleteObjTable(						//删除一个保存几何对象及其属性的表，
	                                        	//当一个图层被干掉时，需要调用此表
		UGString strObjTbName); 				    //图层名

	//##ModelId=482030560032
	//! \brief 释放一个对象表,数据集释放的时候对应的东东都释放
	UGbool ReleaseObjTable(						//释放一个对象表,数据集释放的时候对应的东东都释放
		UGDataset* pDt);					//表名
		
	//##ModelId=482030560034
	//! \brief 设置最多能保存多少个编辑Event
	UGint SetMaxEventCount(						//设置最多能保存多少个编辑Event
		 UGint lEventCount);						//Event的个数
	//##ModelId=48203056003F
	//! \brief 取得最多能保存多少个编辑Event
	UGint GetMaxEventCount();					//取得最多能保存多少个编辑Event
	//##ModelId=482030560040
	//! \brief 设置最多能保存多少个编辑对象（记录）
	UGint SetMaxEventSize(						//设置最多能保存多少个编辑对象（记录）
		 UGint lEventSize);						//Event的个数
	//##ModelId=482030560042
	//! \brief 取得最多能保存多少个编辑对象（记录）
	UGint GetMaxEventSize();						//取得最多能保存多少个编辑对象（记录）

	//##ModelId=482030560043
	//! \brief 
	UGDatasetVector* GetEventInfoDv();
	
	//##ModelId=48203056004E
	//! \brief 
	UGDatasetVector* GetObjInfoDv();


protected: 
	//##ModelId=48203056004F
	UGString m_strDbName;						//数据库文件的名称	
	//##ModelId=482030560050
	UGint m_nNextObjTbKey;						//生成的下一个对象表的关键字
public:
	//##ModelId=482030560051
	UGint m_nMaxEventCount;						//最大的保存编辑事件的个数
	//##ModelId=482030560052
	UGint m_nMaxEventSize;						//一个表中最大保存编辑对象（记录）的个数
	//##ModelId=48203056005D
	UGDataSource* m_pDatasource;

};


}
#endif // !defined(AFX_UGDATAPOOL_H__C7A7F855_B011_4769_8E30_FD51EEF9A26D__INCLUDED_)

