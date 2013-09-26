#ifndef _UGDOWNLOADLISTENER_H_ 
#define _UGDOWNLOADLISTENER_H_ 


#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


namespace UGC {

class UGDownloadListener {
public:
	virtual void SetMap(void *pMap) { }
	virtual void SetMapRefreshFunc(void (*pRefreshFunc)(void *)) { }
};

}
#endif // _UGDOWNLOADLISTENER_H_ 
