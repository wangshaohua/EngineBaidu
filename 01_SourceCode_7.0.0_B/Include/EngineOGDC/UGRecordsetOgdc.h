// UGRecordsetOgdc.h: interface for the UGRecordsetOgdc class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_UGRECORDSETOGDC_H__3447382C_208C_40E4_A613_E5790100E935__INCLUDED_)
#define AFX_UGRECORDSETOGDC_H__3447382C_208C_40E4_A613_E5790100E935__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Engine/UGRecordset.h"

namespace UGC {

class UGDatasetVectorOgdc;

//##ModelId=483BB70801D4
class ENGINEOGDC_API  UGRecordsetOgdc : public OgdcRecordset  
{
public:
	//##ModelId=483BB70801E4
	UGRecordsetOgdc();
	//##ModelId=483BB70801E5
	virtual ~UGRecordsetOgdc();

public:
	//##ModelId=483BB70801E7
	virtual OgdcBool IsEmpty(); 	
	
	//! \brief 判断当前记录指针是否指向头。
	//! \return 指针指向头返回TRUE，否则返回FALSE。
	//##ModelId=483BB70801E9
	virtual OgdcBool IsBOF();	
	
	//! \brief 判断当前记录指针是否指向尾。
	//! \return 指针指向尾返回TRUE，否则返回FALSE。
	//##ModelId=483BB70801EB
	virtual OgdcBool IsEOF();	
	
	//! \brief 关闭记录集
	//##ModelId=483BB70801F4
	virtual void Close();
	
	//! \brief 通过字段名获取字段值。
	//! \param strName 字段名[in]。
	//! \param varVal 字段值[out]。
	//! \return 是否成功获取，成功返回TRUE，失败返回FALSE。
	//##ModelId=483BB70801F6
	virtual OgdcBool GetFieldValue(const OgdcString& strName, OgdcVariant& varVal);	
	
	//! \brief 通过字段序号获取字段值。
	//! \param nIndex 字段序号[in]。
	//! \param varVal 字段值[out]。
	//! \return 是否成功获取，成功返回TRUE，失败返回FALSE。
	//##ModelId=483BB70801FA
	virtual OgdcBool GetFieldValue(OgdcInt nIndex,OgdcVariant& varVal);	
	
	//! \brief 通过字段名设置当前记录的字段值。
	//! \param strName 字段名[in]。
	//! \param varVal 字段值[in]。
	//! \return 是否设置成功，成功返回TRUE，失败返回FALSE。
	//! \remarks 字段值为变体类型
	//##ModelId=483BB7080203
	virtual OgdcBool SetFieldValue(const OgdcString& strName,const OgdcVariant& varVal);	
	
	//! \brief 通过字段序号设置当前记录的字段值。
	//! \param nIndex 字段序号[in]。
	//! \param varVal 字段值[in]。
	//! \return 是否设置成功，成功返回TRUE，失败返回FALSE。
	//! \remarks 字段值为变体类型。
	//##ModelId=483BB7080207
	virtual OgdcBool SetFieldValue(OgdcInt nIndex,const OgdcVariant& varVal);	
	
	//##ModelId=483BB708020B
	virtual OgdcBool Find(const OgdcString& strFilter, 
		OgdcRecordset::FindMode nFindMode = OgdcRecordset::First);	
	
	//##ModelId=483BB7080213
	virtual OgdcBool Move(OgdcRecordset::MovePosition nFromPosition = OgdcRecordset::Current, 
		OgdcInt nRows = 1);	
	
	//! \brief 获取记录个数。
	//! \return 记录个数。
	//##ModelId=483BB7080217
	virtual OgdcInt GetRecordCount();	
	
	//! \brief 收集所有字段的信息。
	//! \param fieldInfos 用来收集所有字段的字段信息数组的引用[out]。
	//! \return 是否收集成功，成功返回TRUE，失败返回FALSE。
	//##ModelId=483BB7080219
	virtual OgdcBool GetFieldInfos(OgdcFieldInfos& fieldInfos);	
	
	//! \brief 通过字段名获取字段信息。
	//! \param strName 字段名[in]。
	//! \param fieldInfo 字段信息引用[out]。
	//! \return 是否获取成功，成功返回TRUE，失败返回FALSE。
	//##ModelId=483BB708021C
	virtual OgdcBool GetFieldInfo(const OgdcString& strName,OgdcFieldInfo& fieldInfo);			

	//! \brief 按某种统计方法统计某个字段。
	//! \param strFieldName 统计的字段名[in]。
	//! \param nMode 统计模式[in]。
	//! \return 统计值。
	//##ModelId=483BB7080222
	virtual OgdcVariant Statistic(const OgdcString& strFieldName,
		OgdcStatisticMode nMode);	

	//! \brief 重新查询，刷新记录集。
	//! \return 是否成功查询，成功返回TRUE，失败返回FALSE。
	//##ModelId=483BB7080226
	virtual OgdcBool ReQuery();	

	//! \brief 计算记录集的地理范围。
	//! \param rc2Bounds 记录集的地理范围[out]。
	//! \param &dMinZ 记录集最小高程[in]。
	//! \param &dMaxZ 记录集最大高程[in]。
	//! \return 是否记算成功，成功返回TRUE，失败返回FALSE。
	//##ModelId=483BB7080228
	virtual OgdcBool ComputeBounds(OgdcRect2D &rc2Bounds,
		OgdcDouble &dMinZ, OgdcDouble &dMaxZ);	

public:
	//! \brief 复制字段值。
	//! \param strSrcField 源字段名[in]。
	//! \param strDestField 目的字段名[in]。
	//! \return 是否成功复制，成功返回TRUE，失败返回FALSE。
	//! \attention strSrcField和trDestField必须都存在且字段类型匹配。
	//##ModelId=483BB708022D
	virtual OgdcBool CopyField(const OgdcString& strSrcExpression,
		const OgdcString& strDestFieldName);	
	
	//! \brief 获取当前记录的ID。
	//! \return 当前记录的ID。
	//##ModelId=483BB7080235
	virtual OgdcInt GetID();	

	//! \brief 获取几何对象，返回的几何对象指针在函数内分配内存，。
	//! \param pElement 空几何对象指针用来取出几何对象[in]。
	//! \return 是否取几何对象成功，成功返回TRUE，失败返回FALSE。
	//! \attention 外面负责删除，否则会有内存泄漏。
	//##ModelId=483BB7080237
	virtual OgdcBool GetElement(OgdcElement*& pElement);	

	//! \brief 设置当前记录的几何对象。
	//! \param pElement 几何对象指针[in]。
	//! \return 是否设置几何对象成功，成功返回TRUE，失败返回FALSE。
	//##ModelId=483BB708023A
	virtual OgdcBool SetElement(OgdcElement* pElement);	

	//! \brief 增加新记录,成功，返回TRUE值，失败返回FALSE值；
	//! \param *pGeometry [in] 添加的Geometry指针
	//! \param bReturnID=FALSE [in] 此参数已经不起作用。
	//! \return True 和 False 的值
	//! \remarks 如果想得到新对象的ID，那么马上调用GetId方法
	//##ModelId=483BB708023D
	virtual OgdcInt AddNew(OgdcElement *pElement, OgdcBool bReturnID=FALSE);

	//! \brief 取出数据集中某行特征要素。
	//! \param nID 数据集记录ID号[in]。
	//! \return 特征要素指针。
	//##ModelId=483BB7080243
	virtual OgdcFeature* GetFeature();	

	//! \brief 将特征要素更新到数据集中。
	//! \param pFeature 特征要素指针[in]。
	//! \return 是否保存成功，成功返回TRUE，失败返回FALSE。
	//##ModelId=483BB7080245
	virtual OgdcBool UpdateFeature(const OgdcFeature* pFeature);
	
	//! \brief 将特征要素追加到数据集未尾。
	//! \param pFeature 特征要素指针[in]。
	//! \return 是否追加成功，成功返回TRUE，失败返回FALSE。
	//! \remarks 追加时特征要素关联的数据集记录ID将不起作用。
	//##ModelId=483BB7080248
	virtual OgdcBool AddFeature(const OgdcFeature* pFeature);

	//! \brief 通过ID定位记录指针。
	//! \param nID 记录ID[in]。
	//! \return 定位成功返回TRUE，失败返回FALSE。
	//##ModelId=483BB708024B
	virtual OgdcBool SeekID(OgdcInt nID);	

	//! \brief 将记录集更新到数据集。
	//! \return 更新记录的ID。
	//##ModelId=483BB708024E
	virtual OgdcInt Update();	

	//! \brief 取消修改。
	//! \return 成功取消返回TRUE，失败返回FALSE。
	//##ModelId=483BB7080252
	virtual OgdcBool CancelUpdate();	
	
	//! \brief 开始修改数据。
	//! \return 成功开始返回TRUE，失败返回FALSE。
	//##ModelId=483BB7080254
	virtual OgdcBool Edit();	

	//! \brief 是否可更新
	//! \return 可更新返回TRUE，否则返回FALSE。
	//##ModelId=483BB7080256
	virtual OgdcBool CanUpdate();	
	
	//! \brief 删除当前记录。
	//! \return 是否成功删除，成功返回TRUE，失败返回FALSE。
	//##ModelId=483BB7080258
	virtual OgdcBool Delete();	

	//! \brief 删除所有记录。
	//! \return 删除成功返回TRRUE，失败返回FALSE。
	//##ModelId=483BB708025A
	virtual OgdcBool DeleteAll();

	//##ModelId=483BB708025C
	virtual OgdcDatasetVector* GetDataset();

	//##ModelId=483BB708025E
	UGRecordset* GetRecordset() const;
	//##ModelId=483BB7080262
	void SetRecordset(UGRecordset* pRecordset);

protected:	
	//##ModelId=483BB7080265
	UGRecordset* m_pRecordset;
	//##ModelId=483BB708026A
	UGDatasetVectorOgdc* m_pDtOgdc;

	UGGeometry* m_pGeometry;
};

}

#endif // !defined(AFX_UGRECORDSETOGDC_H__3447382C_208C_40E4_A613_E5790100E935__INCLUDED_)

