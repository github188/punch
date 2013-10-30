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

//#include "boost/thread.hpp"
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
	void Init(int t_hours,int t_minuts=0,int t_seconds=0);
	bool LeaveHappy(ptime t);
	bool LeaveHappy();
	std::string time_start_str();
	std::string time_end_str();
	bool IsInRestTime( );
private:
	CMyWorkTime(void);
	boost::posix_time::ptime* mp_start;
	//boost::posix_time::ptime* mp_leave;                   
	boost::posix_time::time_period* mp_worktime;//包括了休息时间段
	boost::posix_time::time_period* mp_resttime;//休息时间段
private:
	int m_iwork;
	int m_irest;
};
