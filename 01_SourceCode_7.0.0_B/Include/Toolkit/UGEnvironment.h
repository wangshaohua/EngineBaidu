#if !defined(UGENVIRONMENT_H)
#define UGENVIRONMENT_H

#include "Stream/ugdefs.h"

namespace UGC {

//! \brief 环境变量类
// 将一些需要在启动的时候设置的值放到这里
// 以后最好统一都放到这里
// add by gouyu 2011-8-22
class TOOLKIT_API UGEnvironment
{
public:
	UGEnvironment();
	void init(); // added by liucq 20130610 延后初始化，在移动平台手动调用初始化
	//! \brief 获取是否绘制点符号中面笔划的时候允许使用边线和填充两个颜色绘制，默认只会使用线颜色
	static UGbool GetSymbolDrawWithLineBrushColor();

	static void SetSymbolDrawWithLineBrushColor(UGbool value);

private:

	void ReadIsSymbolDrawWithLineBrushColor();

	static UGbool g_bSymbolDrawWithLineBrushColor;
};
#ifdef OS_ANDROID
extern TOOLKIT_API UGEnvironment g_UGEnvironment;
#endif
}
#endif

