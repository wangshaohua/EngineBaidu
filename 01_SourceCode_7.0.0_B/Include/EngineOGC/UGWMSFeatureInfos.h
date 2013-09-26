// UGWMSFeatureInfos.h: doubleerface for the UGWMSFeatureInfos class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(UGWMSFEATUREINFOS_H)
#define UGWMSFEATUREINFOS_H

#include "Stream/ugexports.h"
#include "Stream/ugdefs.h"
#include "Toolkit/UGMarkup.h"
namespace UGC
{
class ENGINEOGC_API UGWMSFeatureInfos  
{
public:
	UGWMSFeatureInfos();
	virtual ~UGWMSFeatureInfos();
	
public:
	//! \brief 。
	//! \param UGDict<UGString dictQueryPairs>[out] 属性信息对。
	//! \return 。
	UGbool GetWMSFeatureInfos(UGDict<UGString,UGString>& dictQueryPairs);
private:
	//! \brief 判断QueryLayers的layer根据命名空间的不同分成相应的健值对。
	//! \param strValue [in]单个的layer。
	//! \param strKeys [out]存放命名空间的。
 	//! \param UGDict<UGString dictQueryPairs) [out] 存放以命名空间为健名，以layers为值的健值对。
	//! \remarks 。
	void StorageQueryLayers(UGString strValue,UGStrings& strKeys,UGDict<UGString,UGString>& dictQueryPairs);
    
	//! \brief 读取从服务器请求来的XML文件。
 	//! \param mk [in]  传过的markup。
	//! \param UGDict<UGString dictQueryPairs>[out] 属性信息对。
	//! \return  
  	UGbool  ReadXMLInfo(UGMarkup& mk,UGDict<UGString,UGString>& dictQueryPairs);

	//! \brief 读取从服务器请求来的文本文件。
	//! \param strFile [in] 文本文件的地址。
	//! \param UGDict<UGString dictQueryPairs>[out] 属性信息对。
	//! \return  
	UGbool  ReadTextInfo(UGString strFile,UGDict<UGString,UGString>& dictQueryPairs);

	//! \brief 构造一个请求GetFeatureInfo的URL。
	//! \param strLayers [in]传进的querylayers。
	//! \return 返回URL。
 	UGString  GetFeatureInfoURL(UGString strLayers);

public: //对私有属性的读写函数 
	UGString GetMainURL() const { return m_strURL; }
	void SetMainURL(UGString val) { m_strURL = val; }

	UGString GetBox() const { return m_strBox; }
	void SetBox(UGString val) { m_strBox = val; }

	UGString GetStyle() const { return m_strStyle; }
	void SetStyle(UGString val) { m_strStyle = val; }

	UGString GetFormat() const { return m_strFormat; }
	void SetFormat(UGString val) { m_strFormat = val; }

	UGString GetInfoFormat() const { return m_strInfoFormat; }
	void SetInfoFormat(UGString val) { m_strInfoFormat = val; }

	UGString GetRequest() const { return m_strRequest; }
	void SetRequest(UGString val) { m_strRequest = val; }

	UGString GetLayers() const { return m_strLayers; }
	void SetLayers(UGString val) { m_strLayers = val; }

	UGString GetQueryLayers() const { return m_strQueryLayers; }
	void SetQueryLayers(UGString val) { m_strQueryLayers = val; }

	UGlong GetWidth() const {	return m_nWidth; }
	void SetWidth(UGlong val) { m_nWidth = val;}

	UGlong GetHeight() const { return m_nHeight; }
	void SetHeight(UGlong val) { 	m_nHeight = val; }

	UGlong GetPx() const { return m_nPx; }
	void SetPx(UGlong val) { m_nPx = val; }
 	
	UGlong GetPy() const {return m_nPy;}
	void SetPy(UGlong val) { m_nPy = val; }
    
	UGString GetCRSName() const { return m_strCRSName; }
	void SetCRSName(UGString val) { m_strCRSName = val; }
public:
   UGDict<UGString,UGString> m_dictOrgPairs;
private:
	//! \brief 访问服务器的主体请求URL
	//! \remarks 备注信息。
	UGString m_strURL;
	//! \brief 请求服务地图边界,由minx,miny,maxx,maxy构成 
	//! \remarks x,y分别代表经度，纬度。
	UGString m_strBox;
	//! \brief 请求图层的风格
	//! \remarks 备注信息。
    UGString m_strStyle;
	//! \brief 返回请求地图的格式
	//! \remarks 备注信息。
	UGString m_strFormat;
	//! \brief 返回请求结果的显示方式
	//! \remarks 目前有text/html,text/plain,application/vnd.ogc.gml。
	UGString m_strInfoFormat;
	//! \brief 请求服务类型
	//! \remarks request=GetFeatureInfo。
	UGString m_strRequest;
	//! \brief 图层名称
	//! \remarks 备注信息。
	UGString m_strLayers;
	//! \brief 图层名称
	UGString m_strQueryLayers;
	//! \brief 描述所画地图的区域的宽度。
	//! \remarks 单位是象素。
	UGlong     m_nWidth;
	//! \brief 描述所画地图的区域的高度。
	//! \remarks 单位是象素
	UGlong     m_nHeight;	
	//! \brief 所画地图的区域的某点x坐标。	
	UGlong     m_nPx; 	
	//! \brief 所画地图的区域的某点y坐标。	
	UGlong     m_nPy;	
	//! \brief 图层的坐标参考系。
	UGString m_strCRSName;
	
};
}
#endif // !defined(UGWMSFEATUREINFOS_H)


