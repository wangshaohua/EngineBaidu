#ifndef _UGBINARYIMAGE_H
#define _UGBINARYIMAGE_H
#include "Stream/ugdefs.h"

namespace UGC
{
// 二值位图类,非黑(0)即白(1)
// 适用于在上比较大的数据中,查找少量异常的值
class TOOLKIT_API UGBinaryImage
{
public:
	// 构造y行x列的位图,初始化为0
	UGBinaryImage(UGint x, UGint y);
	~UGBinaryImage();

	// 把指定像元修改为1
	void Set(UGint x, UGint y);
	// 把指定像元修改为0
	void Remove(UGint x, UGint y);
	// 测试指定像元是否为1
	UGbool HitTest(UGint x, UGint y);
	// 重置位图
	void Reset();
	// 以(x,y)为起点(不包括自身),按行向下查找下一个值为1的像元.
	// 如果x,y有值为负,则从第一个像元开始向后查找
	UGbool FindNext(UGint &x, UGint &y);

	// 以(x,y)为起点(不包括自身),按行向下查找下一个值为0的像元.
	// 如果x,y有值为负,则从第一个像元开始向后查找
	UGbool FindXORNext(UGint &x, UGint &y);

// 	UGbyte* TakeBuffer()
// 	{
// 		UGbyte *pTmp = m_pBuffer;
// 		m_pBuffer = NULL;
// 		return pTmp;
// 	}
// 	void GiveBuffer(UGbyte *pBuffer, UGint nWidth, UGint nHeight)
// 	{
// 		if(m_pBuffer != NULL)
// 		{
// 			delete []m_pBuffer;
// 		}
// 		m_pBuffer = pBuffer;
// 		m_nWidth = nWidth;
// 		m_nHeight = nHeight;
// 	}

private:
	UGint m_nWidth;
	UGint m_nHeight;
	UGbyte *m_pBuffer;
	UGint m_nByteSpace;
};

}
#endif
