#ifndef UGREGISTRY_H
#define UGREGISTRY_H

#include "Toolkit/UGMarkup.h"
#include "Toolkit/UGHash.h"
#include "Toolkit/UGToolkit.h"

namespace UGC{

#ifdef SYMBIAN60
class TOOLKIT_APIC UGRegistry : public UGHash<UGString>
#else
class TOOLKIT_API UGRegistry : public UGHash<UGString>
#endif
{
private:
	  //!  \brief Toolkit
	enum ElemType 
	{ 
	  //!  \brief Toolkit
		Value = 0, 
	  //!  \brief Toolkit
		Object = 1, 
	  //!  \brief Toolkit
		Sequence = 2, 
	  //!  \brief Toolkit
		ObjectSequence = 3, 
	  //!  \brief Toolkit
		SubRegistry = 4, 
	  //!  \brief Toolkit
		ExternalFile = 5 
	};
	  //!  \brief Toolkit
	static TOOLKIT_APIF ElemType Convert(const UGString &strType);
	
public:
	//! \brief
	  //!  \brief Toolkit
	typedef UGHash<UGString> ObjType;
	  //!  \brief Toolkit
	//! \brief
	  //!  \brief Toolkit
	typedef UGArray<UGString> SeqType;
	//! \brief
	  //!  \brief Toolkit
	typedef UGArray<ObjType> ObjSeqType;
	//! \brief
	  //!  \brief Toolkit
	typedef UGHash<void*> VHash;
	//! \brief
	  //!  \brief Toolkit
	typedef VHash::POSITION VHash_Pos;

protected:
	TOOLKIT_APIF UGRegistry();
	TOOLKIT_APIF UGRegistry(const UGString& file);
	virtual TOOLKIT_APIF void LoadDoc(const UGString& content);
	virtual TOOLKIT_APIF void LoadFromMarkup(const UGMarkup& content);

	TOOLKIT_APIF void SaveDoc(UGMarkup& markup);
#ifdef OS_ANDROID
public: //在android 上开放此接口，因为上层用户会改变SuperMap.xml的路径，在用户改变的时候调用此接口
#endif
	TOOLKIT_APIF void LoadFile(const UGString& filename);
	
public:
	//! \brief
	  //!  \brief Toolkit
	static TOOLKIT_APIF UGString XmlPath();
	
	//! \brief
	  //!  \brief Toolkit
	static TOOLKIT_APIF UGRegistry& Root();
	
	//! \brief
	  //!  \brief Toolkit
	virtual TOOLKIT_APIF ~UGRegistry();
	
//	static ObjType ObjNull;
//	static SeqType SeqNull;
//	static ObjSeqType ObjSeqNull;
//	static UGRegistry RegNull;
	
	//! \brief
	  //!  \brief Toolkit
	TOOLKIT_APIF UGString Encoding() const;
	//! \brief
	  //!  \brief Toolkit
	TOOLKIT_APIF ObjType& Obj(const UGString& s) const;
	//! \brief
	  //!  \brief Toolkit
	TOOLKIT_APIF SeqType& Seq(const UGString& s) const;
	//! \brief
	  //!  \brief Toolkit
	TOOLKIT_APIF ObjSeqType& ObjSeq(const UGString& s) const;	
	//! \brief
	  //!  \brief Toolkit
	TOOLKIT_APIF UGRegistry& SubReg(const UGString& s) const;
	//! \brief
	  //!  \brief Toolkit
	TOOLKIT_APIF UGRegistry& SubFile(const UGString& s) const;	
	//! \brief
	  //!  \brief Toolkit
	TOOLKIT_APIF UGString Name() const;

	//! \brief 把修改在内存中的东西存储到ugc.xml文件中
	TOOLKIT_APIF UGbool Save();

	//! \brief 得到SubFile中的文件名
	//! \param strTag ugc.xml文件中记录subfile的标签名，如"PrjConfig"
	//! \return 返回在ugc.xml文件中记录的外部文件名,如"PrjConfig.xml"
	//! \remarks 完整的标签为:<PrjConfig type="external">PrjConfig.xml</PrjConfig>
	TOOLKIT_APIF UGString GetSubFileName(const UGString& strTag) const;

private: 
	VHash m_Objs;
	VHash m_Seqs;
	VHash m_ObjSeqs;
	VHash m_SubRegs;
	VHash m_SubExts;
	ObjType m_SubFiles;

	UGString m_strFileName;
	UGString m_strRootName;
};


//! \brief 从resource.xml中读取字符串资源的类
//! \author zengzm
//! \remarks resource.xml的内容进行了一些调整, 主要是不再用id作为tag name,而是id 自动增长
//! 故而原有Registry类不适用了. 这里从Registry中派生专门处理resource.xml的类
class TOOLKIT_API UGRegistryResource : public UGRegistry
{
public:
	  //!  \brief Toolkit
	virtual void LoadDoc(const UGString& content);
	virtual TOOLKIT_APIF void LoadFromMarkup(const UGMarkup& content);
};

//! \brief 从epsfont.xml中读取字符串资源的类
class TOOLKIT_API UGRegistryEpsFont: public UGRegistry
{
public:
	  //!  \brief Toolkit
	virtual void LoadDoc(const UGString& content);
	virtual TOOLKIT_APIF void LoadFromMarkup(const UGMarkup& content);
};

}
#endif

