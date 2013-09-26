//////////////////////////////////////////////////////////////////////////
//                    _   _   ____   ____                    
//   Project         | | | | / ___) / ___)                   
//                   | | | || | __ | |                       
//                   | |_| || |_\ || \___                    
//                    \____/ \____| \ ___)     6.0           
//                                                           
//!  \file headerfile.h
//!  \brief Class 的接口定义。
//!  \details 该文件定义了Projection的一些辅助类，用于和OGC以及EPSG交换。
//!  \author 李林、张朔。
//!  \attention 
//!   Copyright (c) 1996-2008 SuperMap Software Limited Company.  <br> 
//!   All Rights Reserved.
//!  \version 6.0
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//IMG投影导入导出直接放在FileparserHFA中了
//  [added by zhangshuo at 12/10/2009]
//////////////////////////////////////////////////////////////////////////

#ifndef AFX_UGC_PROJECT_TOOLKITS_H__INCLUDED_
#define AFX_UGC_PROJECT_TOOLKITS_H__INCLUDED_

#include "UGSpatialRef.h"
#include "UGPrjCoordSys.h"
#include "UGGeoCoordSys.h"
#include "Base/OgdcDict.h"

namespace UGC{

//定义新类型，避免各种普通类型乱冲突
struct UGEPSG //单个EPSG编码导入
{
	UGint epsg;
	UGEPSG(UGint code)
	{
		epsg = code;
	}
	UGEPSG()
	{
		epsg = -1;
	}
};


struct UG_GCS_EPSG_Dict //一堆的EPSG编码导入(PROJCS)
{

	UGint GCS;
	UGint DATUM;
	UGint GUNIT;
	UGint SPHEROID;
	UGdouble SPHEROID_SMAJ;
	UGdouble SPHEROID_SMIN;
	UGint PRIMEM;
	UGdouble PRIMEM_OFFSET;

	UG_GCS_EPSG_Dict()
	{
		GCS = -1;
		DATUM = -1;
		GUNIT = -1;
		SPHEROID = -1;
		PRIMEM = -1;
		PRIMEM_OFFSET = 0;
		SPHEROID_SMAJ = 0;
		SPHEROID_SMIN = 0;
	}
};

struct UG_PCS_EPSG_Dict: UG_GCS_EPSG_Dict //一堆的EPSG编码导入(GEOGCS)
{

	UGint PCS;
	UGint PROJ;
	UGint PUNIT;

	UG_PCS_EPSG_Dict()
	{
		PCS = -1;
		PROJ = -1;
		PUNIT = -1;
	}
};


struct UGWKT // OGC的WKT编码导入(兼容ESRI)
{
	UGString wkt;
	UGbool esri;
	UGWKT(UGString txt, UGbool isesri=FALSE)
	{
		wkt = txt;
		esri = isesri;
	}

	UGWKT(UGbool isesri=FALSE)
	{
		esri = isesri;
	}
};

struct UGWKTFile // OGC的WKT文件(prj格式)编码导入(兼容ESRI)
{
	UGWKT wkt;
	UGString m_filename;//文件名
	UGWKTFile(UGString filename, UGbool isesri=FALSE)
	{
		m_filename = filename;
		wkt.esri = isesri;
	}
};

struct MIPrjStr //MapInfo的字符串表示
{
	UGString michr;
	MIPrjStr(UGString code)
	{
		michr = code;
	}
};


//////////////////////////////////////////////////////////////////////////
//
//空间参考的导入导出
//
//////////////////////////////////////////////////////////////////////////

UGbool PROJECTION_API operator<<(UGPrjCoordSys& srs, UGEPSG epsg);
UGbool PROJECTION_API operator<<(UGPrjCoordSys& srs, UGWKT wkt);
UGbool PROJECTION_API operator<<(UGPrjCoordSys& srs, UGWKTFile wktfile);
UGbool PROJECTION_API operator<<(UGPrjCoordSys& srs, UG_PCS_EPSG_Dict epsgdict);
UGbool PROJECTION_API operator<<(UGGeoCoordSys& srs, UG_GCS_EPSG_Dict epsgdict);
UGbool PROJECTION_API operator<<(UGPrjCoordSys& srs, MIPrjStr mistr);

UGbool PROJECTION_API operator>>(const UGPrjCoordSys& srs, UGEPSG& epsg);
UGbool PROJECTION_API operator>>(const UGPrjCoordSys& srs, UGWKT& wkt);
UGbool PROJECTION_API operator>>(const UGPrjCoordSys& srs, UGWKTFile& wktfile);
UGbool PROJECTION_API operator>>(const UGPrjCoordSys& srs, MIPrjStr& mistr); 

// 对WKT字符串进行可读性格式化 (分行+缩进)
UGString PROJECTION_API FormatWkt(const UGString& wkt);


//////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//
//    以下功能不提供对外使用
//
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////

//! \brief OGC的字符串表达生成/解析辅助类。
//! \remarks 仅供内部使用。
class UGWKTMarkup{
public:
	class Element
	{	
		friend class UGWKTMarkup;
	private:
		UGString type;
		UGString name;
		UGArray<UGString> inner;
		UGArray<Element> child;
	private:
		Element(){}
		
	public:
		Element(UGString itype, UGString iname):type(itype), name(iname){}
		const UGString& GetType(){return type;}
		const UGString& GetName(){return name;}
		void AddChild(const Element& ele){
			child.Add(ele);
		}
		Element* GetChildByType(UGString type){
			UGArray<Element*> children;
			for(UGint i=0;i<child.GetSize();i++)
				if (child[i].type==type)
					return &child[i];
			return NULL;
		}

		Element* GetChildByTypeAndName(const UGString& type, const UGString& name){
			UGArray<Element*> children;
			for (UGint i=0; i<child.GetSize(); i++)
			{
				if (child[i].type.CompareNoCase(type) == 0 && child[i].name.CompareNoCase(name) == 0)
				{
					return &child[i];
				}
			}
			return NULL;
		}


		void GetChildren(UGArray<Element*>& children, UGString type=_U("")){
			if (type==_U("")){
				for(UGint i=0;i<child.GetSize();i++){
					children.Add(&child[i]);
				}
			}
			else{
				for(UGint i=0;i<child.GetSize();i++){
					if (child[i].type==type)
					{
						children.Add(&child[i]);
					}
				}
			}
		}
		const UGArray<UGString>& GetParams(){
			return inner;
		}
		void AddParam(UGString param){
			//inner.Add("\""+param+"\"");
			inner.Add(param);  //Modified by Wangbg 2010-9-7 已经是字符串了,就不用再加_U("")了
		}
		void AddParam(UGdouble param){
			UGString strpar;
			strpar.Format(_U("%18.12g"), param);
			inner.Add(strpar.TrimLeft());
		}
		void AddParam(UGint param){
			UGString strpar;
			strpar.Format(_U("%d"), param);
			inner.Add(strpar);
		}
	};
public:
	UGWKTMarkup(){}
	UGWKTMarkup(UGWKT wkt);
	Element* GetRoot(){ return &root; }
	UGString ToWKT();
private:
	void InnerFromWkt(Element* element, 
		const UGArray< UGString >& innerWktArr, 
		UGint begin,
		UGint len,
		UGint nowspace);
	UGString InnerToWkt(Element* element);
private:
	Element root;
};

//! \brief OGC的坐标辅助类。
//! \remarks 仅供内部使用。
template<class T>
UGint FindByID(const UGArray<T>& array, UGint elementid, UGint start = -1, UGint end = -1)
{
	if (array.GetSize()==0)
	{
		return -1;
	}

	//最开始初始化
	if (start == -1)
	{
		if (array[0].epsg == elementid)
		{
			return 0;
		}
		start = 0;
	}
	if (end == -1)
	{
		if (array[array.GetSize()-1].epsg == elementid)
		{
			return array.GetSize()-1;
		}
		end = array.GetSize()-1;
	}

	//递归查找代码
	if (start == end || end == start+1)
	{
		//结束查找
		if (array[start].epsg == elementid)
			return start;
		else if (array[end].epsg == elementid)
			return end;
		else
			return -1;
	}
	else
	{
		UGint avg = (start+end)/2;

		if (elementid == array[avg].epsg)
		{
			return avg;
		}
		else if (elementid<array[avg].epsg)
		{
			return FindByID(array, elementid, start, avg);
		}
		else
		{
			return FindByID(array, elementid, avg, end);
		}
	}


	return -1;
}

class PROJECTION_API OGCSrsHelper{

public:
	struct PIMstruct
	{
		UGint epsg;
		UGString name;
		//UGString ESRIname;
		PIMstruct(){epsg = -1;}
	};

	struct SPHstruct
	{
		UGint epsg;
		UGString name;
		//UGString ESRIname;
		SPHstruct(){epsg = -1;}
	};

	struct DAUstruct
	{
		UGint epsg;
		UGString name;
		UGString ESRIname;
		DAUstruct(){epsg = -1;}
	};

	struct PCSstruct 
	{
		UGint epsg;
		UGString name;
		UGString ESRIname;
		PCSstruct(){epsg = -1;}
	};

	struct GCSstruct 
	{
		UGint epsg;
		UGString name;
		UGString ESRIname;
		GCSstruct(){epsg = -1;}
	};

	struct MIORIstruct
	{
		UGint epsg;
		UGString conf;
		MIORIstruct(){epsg=-1;}
	};

	struct MIPRJstruct
	{
		UGString strProjectionName;
		UGString strUGProjectionCode;
		UGString strMIProjectionCode;
		UGArray<UGbool> arrbMIPrjParams;
	};

	struct MIDatumstruct
	{
		UGString strDatumName;
		UGString strMIDatumTypeCode;
		UGString strUGDatumTypeCode;
		UGString strEllipsoidName;
	};

	struct MIUnitstruct
	{
		UGString strUnitName;
		UGString strMIUnitTypeCode;
		UGString strUGUnitTypeCode;
	};

	struct MIEllipsoidstruct
	{
		UGString strEllipsoidName;
		UGString strMIEllipsoidCode;
		UGString strUGEllipsoidCode;
		//长半轴
		UGdouble dSemiMajorAxis;
		//扁率
		UGdouble dInverseFlattening;		
	};

	// ESRI的投影类型和SuperMap投影类型对照 [4/8/2010 林文玉]
	struct ESRIPrjType 
	{
		UGString strExtName;
		UGint nOurType;
		ESRIPrjType(){nOurType=-1;}
	};

public:
	//找出supermap的坐标系id对应的epsg编码
	static UGint Find_EPSG(UGint ugid)
	{
		init();
		PCSstruct pcs = Find_PCS_EPSG(ugid);
		if (pcs.epsg != -1)
		{
			return pcs.epsg;
		}
		GCSstruct gcs = Find_GCS_EPSG(ugid);
		if (gcs.epsg != -1)
		{
			return gcs.epsg;
		}
		DAUstruct dau = Find_DAU_EPSG(ugid);
		if (dau.epsg != -1)
		{
			return dau.epsg;
		}
		SPHstruct sph = Find_SPH_EPSG(ugid);
		if (sph.epsg != -1)
		{
			return sph.epsg;
		}
		PIMstruct pim = Find_PIM_EPSG(ugid);
		if (pim.epsg != -1)
		{
			return pim.epsg;
		}
		return -1;
	}

	//通过EPSG查找对应的PCS
	static PCSstruct Find_PCS_EPSG(UGint epsg)
	{
		init();
		//
		UGint pos = FindByID(pcslist, epsg);
		if (pos!=-1)
		{
			return pcslist[pos];
		}
		PCSstruct pcs;
		return pcs;
	}
	static UGint Find_PCS_EPSG_CODE(UGint epsg)
	{
		init();
		return FindByID(pcslist, epsg);
	}

	//通过EPSG查找对应的GCS
	static GCSstruct Find_GCS_EPSG(UGint epsg)
	{
		init();
		UGint pos = FindByID(gcslist, epsg);
		if (pos!=-1)
		{
			return gcslist[pos];
		}
		GCSstruct gcs;
		return gcs;
	}
	static UGint Find_GCS_EPSG_CODE(UGint epsg)
	{
		init();
		return FindByID(gcslist, epsg);
	}

	//通过EPSG查找对应的DAU
	static DAUstruct Find_DAU_EPSG(UGint epsg)
	{
		init();
		UGint pos = FindByID(daulist, epsg);
		if (pos!=-1)
		{
			return daulist[pos];
		}
		DAUstruct dau;
		return dau;
	}
	static UGint Find_DAU_EPSG_CODE(UGint epsg)
	{
		init();
		return FindByID(daulist, epsg);
	}

	//通过EPSG查找对应的SPH
	static SPHstruct Find_SPH_EPSG(UGint epsg)
	{
		init();
		UGint pos = FindByID(sphlist, epsg);
		if (pos!=-1)
		{
			return sphlist[pos];
		}
		SPHstruct sph;
		return sph;
	}
	static UGint Find_SPH_EPSG_CODE(UGint epsg)
	{
		init();
		return FindByID(sphlist, epsg);
	}
	//通过EPSG查找对应的中央经线
	static PIMstruct Find_PIM_EPSG(UGint epsg)
	{
		init();
		UGint pos = FindByID(pimlist, epsg);
		if (pos!=-1)
		{
			return pimlist[pos];
		}
		PIMstruct pim;
		return pim;
	}
	static UGint Find_PIM_EPSG_CODE(UGint epsg)
	{
		init();
		return FindByID(pimlist, epsg);
	}
	
	//通过名字来模糊搜索
	static PCSstruct Find_PCS_EPSG_CODE(UGString name)
	{
		init();
		UGint i=0;
		for (;i<pcslist.GetSize();i++)
		{
			PCSstruct pcs = pcslist[i];
			//if (pcs.epsg==2382)
				//UGString aaa("");
			if (pcs.name.CompareNoCase(name)==0
				|| pcs.ESRIname.CompareNoCase(name)==0)
			{
				return pcs;
			}
		}
		PCSstruct nullpcs;
		return nullpcs;
	}

	static GCSstruct Find_GCS_EPSG_CODE(UGString name)
	{
		init();
		UGint i=0;
		for (;i<gcslist.GetSize();i++)
		{
			GCSstruct gcs = gcslist[i];
			if (gcs.name.CompareNoCase(name)==0
				|| gcs.ESRIname.CompareNoCase(name)==0)
			{
				return gcs;
			}
		}
		GCSstruct nullgcs;
		return nullgcs;
	}
	
	static DAUstruct Find_DAU_EPSG_CODE(UGString name)
	{
		init();
		UGint i=0;
		for (;i<daulist.GetSize();i++)
		{
			DAUstruct dau = daulist[i];
			if (dau.name.CompareNoCase(name)==0
				|| dau.ESRIname.CompareNoCase(name)==0)
			{
				return dau;
			}
		}
		DAUstruct nullDau;
		return nullDau;
	}

	static SPHstruct Find_SPH_EPSG_CODE(UGString name)
	{
		init();
		UGint i=0;
		for (;i<sphlist.GetSize();i++)
		{
			SPHstruct sph = sphlist[i];
			if (sph.name.CompareNoCase(name)==0)
			{
				return sph;
			}
		}
		SPHstruct nullSph;
		return nullSph;
	}

	static PIMstruct Find_PIM_EPSG_CODE(UGString name)
	{
		init();
		UGint i=0;
		for (;i<pimlist.GetSize();i++)
		{
			PIMstruct pim = pimlist[i];
			if (pim.name.CompareNoCase(name)==0)
			{
				return pim;
			}
		}
		PIMstruct nullPim;
		return nullPim;
	}

	static MIORIstruct FindEPSGFromMIORI(UGString name)
	{
		init();
		UGint i=0;
		for (;i<arrMIOri.GetSize();i++)
		{
			MIORIstruct mi = arrMIOri[i];
			if (mi.conf.CompareNoCase(name)==0)
			{
				return mi;
			}
		}
		MIORIstruct nullmi;
		return nullmi;
 	}

	static MIORIstruct FindConfFromMIORI(UGint EPSGcode)
	{
		init();
		UGint i=0;
		for (;i<arrMIOri.GetSize();i++)
		{
			MIORIstruct mi = arrMIOri[i];
			if (mi.epsg == EPSGcode)
			{
				return mi;
			}
		}
		MIORIstruct nullmi;
		return nullmi;
	}

	static MIPRJstruct FindUGProjectionFromMI(UGString strMIProjectionCode)
	{
		init();
		UGint i = 0;
		for (; i < arrMIProjection.GetSize(); i++)
		{
			MIPRJstruct miprj = arrMIProjection[i];
			if (!miprj.strMIProjectionCode.CompareNoCase(strMIProjectionCode))
			{
				return miprj;
			}
		}
		MIPRJstruct nullstruct;
		return nullstruct;
	}

	static MIPRJstruct FindMIProjectionFromUG(EmPrjObjectType UGProjectionCode)
	{
		init();
		UGint i = 0;
		for (; i < arrMIProjection.GetSize(); i++)
		{
			MIPRJstruct miprj = arrMIProjection[i];
			if (miprj.strUGProjectionCode.ToInt() == (UGint)UGProjectionCode)
			{
				return miprj;
			}
		}
		MIPRJstruct nullstruct;
		return nullstruct;
	}

	static MIDatumstruct FindUGDatumFromMI(UGString strDatumCode)
	{
		init();
// 		EmHorizonDatumType eDatumType = DATUM_USER_DEFINED;
		UGint i = 0;
		for (; i < arrMIDatum.GetSize(); i++)
		{
			MIDatumstruct midatum = arrMIDatum[i];
			if (!midatum.strMIDatumTypeCode.CompareNoCase(strDatumCode))
			{
// 				eDatumType = (EmHorizonDatumType)midatum.strUGDatumTypeCode.ToInt();
				return midatum;
			}
		}
		MIDatumstruct nullmidatum;
		return nullmidatum;
	}

	static MIDatumstruct FindMIDatumFromUG(EmHorizonDatumType UGDatumTypeCode)
	{
		init();
		UGint i = 0;
		for (; i < arrMIDatum.GetSize(); i++)
		{
			MIDatumstruct midatum = arrMIDatum[i];
			if ((EmHorizonDatumType)midatum.strUGDatumTypeCode.ToInt() == (UGint)UGDatumTypeCode)
			{
				return midatum;
			}
		}
		MIDatumstruct nullstruct;
		return nullstruct;
	}

	static UGint FindUGUnitTypeCodeFromMI(UGString strUnitCode)
	{
		init();
		UGint nUnitType = 7;
		UGint i = 0;
		for (; i < arrMIUnit.GetSize(); i++)
		{
			MIUnitstruct miunit = arrMIUnit[i];
			if (!miunit.strMIUnitTypeCode.CompareNoCase(strUnitCode))
			{
				nUnitType = miunit.strUGUnitTypeCode.ToInt();
				return nUnitType;
			}
		}
		return nUnitType;
	}

	static UGString FindMIUnitTypeCodeFromUG(UGint nUGUnitTypeCode)
	{
		init();
		UGString strUnitType = _U("AU_METER");
		UGint i = 0;
		for (; i < arrMIUnit.GetSize(); i++)
		{
			MIUnitstruct miunit = arrMIUnit[i];
			if (miunit.strUGUnitTypeCode.ToInt() == nUGUnitTypeCode)
			{
				strUnitType = miunit.strMIUnitTypeCode;
				return strUnitType;
			}
		}
		return strUnitType;
	}

	static EmSpheroidType FindUGEllipsoidTypeCodeFromMI(UGString strEllipsoidCode, UGdouble& dAxis, UGdouble& dFlatten, UGString& strEllipsoidName )
	{
		init();
		EmSpheroidType EllipsoidType = SPHEROID_USER_DEFINED;
		UGint i = 0;
		for (; i < arrMIEllipsoid.GetSize(); i++)
		{
			MIEllipsoidstruct miellipsoid = arrMIEllipsoid[i];
			if (!miellipsoid.strMIEllipsoidCode.CompareNoCase(strEllipsoidCode))
			{
				EllipsoidType = (EmSpheroidType)miellipsoid.strUGEllipsoidCode.ToInt();
				dAxis = miellipsoid.dSemiMajorAxis;
				dFlatten = 1 / miellipsoid.dInverseFlattening;
				strEllipsoidName = miellipsoid.strEllipsoidName;
				return EllipsoidType;;
			}
		}
		return EllipsoidType;
	}

	static UGString FindMIEllipsoidTypeCodeFromUG(EmSpheroidType UGEllipsoidTypeCode/*, UGdouble dAxis, UGdouble dFlatten, UGString strEllipsoidName*/)
	{
		init();
		UGString strEllipsoidType = _U("");
		UGint i = 0;
		for (; i < arrMIEllipsoid.GetSize(); i++)
		{
			MIEllipsoidstruct miellipsoid = arrMIEllipsoid[i];
			if (miellipsoid.strUGEllipsoidCode.ToInt() == (UGint)UGEllipsoidTypeCode)
			{
				strEllipsoidType = miellipsoid.strMIEllipsoidCode;
				return strEllipsoidType;
			}
		}
		return strEllipsoidType;
	}

	static UGString FindMIEllipsoidTypeCodeByName(UGString strEllipsoidName)
	{
		init();
		UGString strEllipsoidType = _U("");
		UGint i = 0;
		for (; i < arrMIEllipsoid.GetSize(); i++)
		{
			MIEllipsoidstruct miellipsoid = arrMIEllipsoid[i];
			if (!miellipsoid.strUGEllipsoidCode.CompareNoCase(strEllipsoidName))
			{
				strEllipsoidType = miellipsoid.strMIEllipsoidCode;
				return strEllipsoidType;
			}
		}
		return strEllipsoidType;
	}

	static UGint FindOurPrjTypeByESRIPrjName(const UGString& esriName){
		init();
		for (UGint i=0; i<arrEsriPrjType.GetSize(); i++)
		{
			ESRIPrjType esriour = arrEsriPrjType[i];
			if (esriour.strExtName.CompareNoCase(esriName) == 0)
			{
				return esriour.nOurType;
			}
		}
		return -1;
	}

private:
	OGCSrsHelper(){init();}
	static void init();

private:
	static UGArray<PCSstruct> pcslist; 
	static UGArray<GCSstruct> gcslist; 
	static UGArray<DAUstruct> daulist;
	static UGArray<SPHstruct> sphlist;
	static UGArray<PIMstruct> pimlist;

	static UGArray<MIORIstruct> arrMIOri;
	static UGArray<MIPRJstruct> arrMIProjection;
	static UGArray<MIDatumstruct> arrMIDatum;
	static UGArray<MIUnitstruct> arrMIUnit;
	static UGArray<MIEllipsoidstruct> arrMIEllipsoid;
	static UGArray<ESRIPrjType> arrEsriPrjType;
};

//static UGArray<PIMstruct> pimlist;

}

#endif // !defined(AFX_UGC_PROJECT_TOOLKITS_H__INCLUDED_)

