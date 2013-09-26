// UGVectorImportParams.h: interface for the UGVectorImportParams class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_UG_WORKSPACE_IMPORTPARAMS_H__INCLUDED_)
#define AFX_UG_WORKSPACE_IMPORTPARAMS_H__INCLUDED_

#include "Stream/ugexports.h"
#include "FileParser/UGVectorConfigParams.h"
#include "FileParser/UGRasterConfigParams.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

namespace UGC {

//定义工作空间的连接，这里定义是为了不要导致工程间的依赖混乱
// struct UGWorkspaceConn
// {
// 	//! \brief 工作空间类型
// 	UGint	m_nWorkspaceType;
// 
// 	//! \brief 数据库名
// 	UGString		m_strDatabase;
// 
// 	//! \brief 服务名，如果是文件型工作空间，那么就是全路径加上文件名
// 	UGString		m_strServer;
// 
// 	//! \brief 用户名
// 	UGString		m_strUser;
// 
// 	//! \brief 密码
// 	UGString		m_strPassword;
// 
// 	//! \brief 工作空间名字
// 	UGString		m_strWorkspaceName;
// 
// 	//! \brief 针对文件型工作空间有效，如果文件已经存在是否返回失败,默认是true
// 	UGbool			m_bFailIfExists;
// 
// 	//! \brief	工作空间的版本，默认是0
// 	UGint			m_nVersion;
// 
// 	//! \brief ODBC Driver
// 	UGString		m_strDriver;
// };

class UGWorkspace;

//! \brief  矢量导入参数	
class FILEPARSER_API UGWorkspaceImportParams  : public UGImportParams
{


public:
	//! \brief 构造函数。
	UGWorkspaceImportParams();
	
	//! \brief 析构函数。
	virtual ~UGWorkspaceImportParams();

	//! \brief 获取工作空间
	UGWorkspace* GetWorkspace();

	//! \brief 设置工作空间(可以不存在可以存在)
	void SetWorkspace(UGWorkspace* wsc);

	//! \brief 获取导入矢量数据的参数。
	UGbool GetVectorImportParams(UGVectorImportParams& impParams);

	//! \brief 获取导入栅格数据的参数。
	UGbool GetRasterImportParams(UGRasterImportParams& impParams);
	
	//! \brief 设置要重新命名的数据集。
	UGbool SetRenameTabNames(const UGDict<UGString, UGString>& rnTabNames);

	//! \brief 获取要重新命名的数据集。
	UGbool GetRenameTabNames(UGDict<UGString, UGString>& rnTabNames);

	//! \brief 获取要重新命名的地图。
	UGbool SetRenameMapNames(const UGDict<UGString, UGString>& rnMapNames);

	//! \brief 设置要重新命名的地图。
	UGbool GetRenameMapNames(UGDict<UGString, UGString>& rnMapNames);


private:
	UGDict<UGString, UGString> m_rnTabNames;
	UGDict<UGString, UGString> m_rnMapNames;

	UGWorkspace* m_workspace;
};


//////////////////////////////////////////////////////////////////////////


} //namespace UGC

#endif // !defined(AFX_UG_WORKSPACE_IMPORTPARAMS_H__INCLUDED_)

