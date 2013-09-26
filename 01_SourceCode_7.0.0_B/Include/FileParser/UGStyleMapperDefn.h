#ifndef _UGSTYLEMAPERDEFN_INCLUDE_H
#define _UGSTYLEMAPERDEFN_INCLUDE_H

#include "Stream/ugdefs.h"
#include "Toolkit/UGThread.h"

namespace UGC {



//! \brief 符号对照参数
//! \remarks 备注信息。
class UGSymbolParam
{
public:
	
	UGSymbolParam(){dAngle = 0.0; dScale=0.0;}	
	UGSymbolParam(const UGSymbolParam& param);
	UGSymbolParam& operator=(const UGSymbolParam& param);
	UGbool operator==(const UGSymbolParam& param);

	UGString strId; // 符号的名称或号,必须
	UGString strGroup; // 符号所在的分组，可选
	UGdouble dAngle; // 旋转角，可选
	UGString strColor; // 符号颜色，采用16进制表达(#RRGGBB),可选
	UGdouble dScale; // 符号缩放比例
};


//! \brief 线型对照参数
//! \remarks 备注信息。
class UGLineStyleParam
{
public:

	UGLineStyleParam(){dWidth=0.0;}
	UGLineStyleParam(const UGLineStyleParam& param);
	UGLineStyleParam& operator=(const UGLineStyleParam& param);
	UGbool operator==(const UGLineStyleParam& param);

	UGString strId; // 线型名称或号,必须
	UGString strColor; // 画笔颜色,采用16进制表达(#RRGGBB),可选
	UGdouble dWidth; // 画笔宽度，可选
};


//! \brief 填充风格对照参数
//! \remarks 备注信息。
class UGFillStyleParam
{
public:

	UGFillStyleParam(){nAngle=0;}
	UGFillStyleParam(const UGFillStyleParam& param);
	UGFillStyleParam& operator=(const UGFillStyleParam& param);
	UGbool operator==(const UGFillStyleParam& param);

	UGString strId; // 填充风格名称或号
	UGshort nAngle; // 旋转角,单位0.1度
	UGString strFcolor; // 填充前景色
	UGString strBcolor; // 填充背景色
};

//! \brief 字体对照参数
//! \remarks 备注信息。
class UGFontParam
{
public:

	UGFontParam(){strAngle=_U("");dxFactor=0.0;dyFactor=0.0;}
	UGFontParam(const UGFontParam& param);
	UGFontParam& operator=(const UGFontParam& param);
	UGbool operator==(const UGFontParam& param);

	UGString strId; // 字体名称
	UGString strAngle; // 字体旋转角
	UGdouble dxFactor; // x方向缩放比例
	UGdouble dyFactor;// y方向缩放比例
	UGString strFcolor; // 字体前景色
	UGString strBcolor; // 字体背景色
};



class FILEPARSER_API UGStyleTable
{
public:
	
	UGStyleTable(){}
	UGStyleTable(const UGStyleTable& tmp);
	void operator=(const UGStyleTable& tmp);
	~UGStyleTable();

	UGbool Save(const UGString& strfilePath);

	void AddSymbol(UGSymbolParam* extend, UGSymbolParam* our);
	UGSymbolParam* FindSymbol(const UGSymbolParam& symbol, UGbool bExtend=TRUE);

	void AddLineStyle(UGLineStyleParam* extend, UGLineStyleParam* our);
	UGLineStyleParam* FindLineStyle(const UGLineStyleParam& lineStyle, UGbool bExtend=TRUE);

	void AddFillStyle(UGFillStyleParam* extend, UGFillStyleParam* our);
	UGFillStyleParam* FindFillStyle(const UGFillStyleParam& fillStyle, UGbool bExtend=TRUE);

	void AddFontStyle(UGFontParam* extend, UGFontParam* our);
	UGFontParam* FindFontStyle(const UGFontParam& fontStyle, UGbool bExtend=TRUE);

	void Clear();

protected:

	// 符号对照部分
	UGArray<UGSymbolParam*> m_arrSymbolExtend;
	UGArray<UGSymbolParam*> m_arrSymbolOur;

	// 线型对照部分
	UGArray<UGLineStyleParam*> m_arrLineStyleExtend;
	UGArray<UGLineStyleParam*> m_arrLineStyleOur;

	// 填充风格对照部分
	UGArray<UGFillStyleParam*> m_arrFillStyleExtend;
	UGArray<UGFillStyleParam*> m_arrFillStyleOur;

	// 字体风格对照部分
	UGArray<UGFontParam*> m_arrFontExtend;
	UGArray<UGFontParam*> m_arrFontOur;

};

class FILEPARSER_API UGStyleMapMgr
{
public:

	UGStyleMapMgr(UGStyleTable* pStyleTable = NULL){m_pStyleTable = pStyleTable;}
	UGStyleMapMgr(const UGStyleMapMgr& tmp)
	{
		if( m_pStyleTable == NULL )
		{
			m_pStyleTable = new UGStyleTable;
		}
		if( m_pStyleTable )
		{
			*m_pStyleTable = *tmp.m_pStyleTable;
		}
	}
	void operator=(const UGStyleMapMgr& tmp)
	{
		if( m_pStyleTable == NULL )
		{
			m_pStyleTable = new UGStyleTable;
		}
		if( m_pStyleTable )
		{
			*m_pStyleTable = *tmp.m_pStyleTable;
		}
	}
	~UGStyleMapMgr(){Close();}

	//! \brief 打开风格对照文件	
	//! \param  [in]。
	//! \return 。
	//! \remarks 。
	//! \attention 。
	UGint Open(const UGString& strStylePath);	

	//! \brief 关闭文件	
	//! \param  [in]。
	//! \return 。
	//! \remarks 。
	//! \attention 。
	void Close();


	//! \brief 根据参照的对照参数得到一个符号对照	
	//! \param  symbolParam [in] 可参照的对照参数
	//! \param  bExtend [in] 传入的对照参数是否是外部的。
	//! \return 如果是外部的对照参数，返回SuperMap符号对照。
	//! \remarks 。
	//! \attention 。
	UGSymbolParam* GetSymbolStyle(const UGSymbolParam& symbolParam, UGbool bExtend = TRUE) const;

	//! \brief 根据参照的对照参数得到一个线型对照	
	//! \param  symbolParam [in] 可参照的对照参数
	//! \param  bExtend [in] 传入的对照参数是否是外部的。
	//! \return 如果是外部的对照参数，返回SuperMap线型对照。
	//! \remarks 。
	//! \attention 。
	UGLineStyleParam* GetLineStyle(const UGLineStyleParam& symbolParam, UGbool bExtend = TRUE) const;


	//! \brief 根据参照的对照参数得到一个填充对照	
	//! \param  symbolParam [in] 可参照的对照参数
	//! \param  bExtend [in] 传入的对照参数是否是外部的。
	//! \return 如果是外部的对照参数，返回SuperMap填充对照。
	//! \remarks 。
	//! \attention 。
	UGFillStyleParam* GetFillStyle(const UGFillStyleParam& symbolParam, UGbool bExtend = TRUE) const;


	//! \brief 根据参照的对照参数得到一个字体对照	
	//! \param  symbolParam [in] 可参照的对照参数
	//! \param  bExtend [in] 传入的对照参数是否是外部的。
	//! \return 如果是外部的对照参数，返回SuperMap字体对照。
	//! \remarks 。
	//! \attention 。
	UGFontParam* GetFontStyle(const UGFontParam& symbolParam, UGbool bExtend = TRUE) const;
	
protected:

	UGint ParserSymbol(const UGStrings& arrSymbol);
	void ParserSymbolItem(const UGStrings& arrItem, UGSymbolParam* symbolParam);

	UGint ParserLineStyle(const UGStrings& arrLineStyle);
	void ParserLineStyleItem(const UGStrings& arrItem, UGLineStyleParam* lineParam);

	UGint ParserFillStyle(const UGStrings& arrFillStyle);
	void ParserFillStyleItem(const UGStrings& arrItem, UGFillStyleParam* fillParam);

	UGint ParserFont(const UGStrings& arrFont);
	void ParserFontItem(const UGStrings& arrItem, UGFontParam* fontParam);

private:

	//! \brief  将传入的符号对照表相关项分解成以逗号隔开的两部分	
	//! \param  strIn [in] 
	//! \param  bExtend [out] 
    //! \param  arrOur [out] 
	//! \return 
	//! \remarks 。
	//! \attention 。
	UGbool AnalyseStyleItem(const UGString& strItemIn, UGStrings &arrExtend, UGStrings &arrOur);

	UGStyleTable * m_pStyleTable;
};


	
}
#endif //_UGSTYLEMAPERDEFN_INCLUDE_H


