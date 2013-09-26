
#if !defined(AFX_UGEMLOG_H__AAC47E2E_B5B6_476C_9462_FBF34F02DFF5__INCLUDED_)
#define AFX_UGEMLOG_H__AAC47E2E_B5B6_476C_9462_FBF34F02DFF5__INCLUDED_

//打开次宏，以文件形式输出调试时间信息
//#define MOBILEDEBUG

#if (defined OS_ANDROID || defined  IOS) && defined ( MOBILEDEBUG)
#define BEGINTIME(t) UGEMTime t;
#define ENDTIME(t,s) t.End(s);
#else
#define BEGINTIME(t);
#define ENDTIME(t,s);
#endif

#include "Stream/ugdefs.h"
#include "Stream/UGFile.h"
#include "Toolkit/UGThread.h"
#include <fstream>

namespace UGC {	

class UGEMlog
{
    friend UGEMlog * CreateLog();
    
public:
	~UGEMlog(void);
	void Write(UGString message);
    void SetLogPath(const char*path);
    
private:
    UGEMlog();
    std::string getTimeStr();
    std::string MakeFileName(const char* path);
    
private:
    UGMutex m_mutex;
    std::ofstream file;
    std::string logPath;
};
    
UGEMlog * CreateLog();
    
    
    
class UGEMTime
{
    public:
    UGEMTime()
    {
        nStart = UGTime::GetMillisecond();
    }
    
    void End(UGString message)
    {
        message += _U("\t");
        message += UGString::From(UGTime::GetMillisecond() - nStart);
        CreateLog()->Write(message);
    }
    
    private:
        UGint nStart;
    };
      
}
#endif // !defined(AFX_UGEMLOG_H__AAC47E2E_B5B6_476C_9462_FBF34F02DFF5__INCLUDED_)

