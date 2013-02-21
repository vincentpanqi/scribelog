#include "lce.h"
#include "CConfigMgr.h"
#include <fstream>

using namespace lce;
using namespace std;

const int WRITE_TIMER_ID = 1;
const int WRITE_MSG_ID = 1;
const size_t MAX_MODULE_NUM = 255;

class CProcCenter :public CTask, public CProcessor
{
public:
	struct SWriteInfo
	{
		int iSize;
		string sModule;
		CSocketBuf *pSocketBuf;
	};

	typedef map<string,CSocketBuf*> MAP_LOG_BUFFER;
	
    int init();
    void onRead(SSession &stSession,const char * pszData, const int iSize);
    void onClose(SSession &stSession);
    void onConnect(SSession &stSession,bool bOk);
    void onError(SSession &stSession,const char * szErrMsg,int iError);
    void onWork(int iTaskType,void *pData,int iIndex);
    void onTimer(uint32_t dwTimerId,void *pData);
    void onMessage(uint32_t dwMsgType,void *pData);


	static CProcCenter& getInstance()
	{
		if ( NULL == m_pInstance )
		{
			m_pInstance = new CProcCenter;
		}

		return *m_pInstance;
	}
    char *getErrMsg() { return m_szErrMsg; }
	~CProcCenter();
	
private:

	static std::string getDateTimeStr()
	{
		time_t tTime = time(NULL);
		char s[20];
		struct tm curr = *localtime(&tTime);
		snprintf(s, sizeof(s), "%04d-%02d-%02d",curr.tm_year+1900, curr.tm_mon+1, curr.tm_mday);
		return std::string(s);
	}
	
    CProcCenter();
	CProcCenter& operator=(const CProcCenter& rhs);
	CProcCenter(const CProcCenter& rhs);

    static CProcCenter *m_pInstance;
    char m_szErrMsg[1024];
	SSession *m_pstSession;
	SConfig m_stConfig;
	MAP_LOG_BUFFER m_mapLogBuffer;


};
