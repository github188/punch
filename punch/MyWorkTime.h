#pragma once

/*
namespace boost
{
	namespace posix_time
	{
		
		class ptime;
		class time_period;
		
	}
}

class boost::posix_time::ptime;
class boost::posix_time::time_period;*/

//using boost::posix_time::ptime;
//using boost ::posix_time::time_period;
#include "boost/date_time/gregorian/gregorian.hpp"
#include "boost/date_time/posix_time/posix_time.hpp"
#include "boost\date_time\local_time\local_time.hpp"

using namespace boost;
using namespace local_time;
using namespace gregorian;
using namespace posix_time;

class CMyWorkTime
{
public:
	
	CMyWorkTime(int work_time,int rest_time);
	~CMyWorkTime(void);
public:
	void Init();
	bool LeaveHappy(ptime t);
private:
	CMyWorkTime(void);
	boost::posix_time::ptime* mp_start;
	//boost::posix_time::ptime* mp_leave;                   
	boost::posix_time::time_period* mp_worktime;
private:
	int m_iwork;
	int m_irest;
};
