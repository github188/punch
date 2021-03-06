#include "StdAfx.h"
#include "MyWorkTime.h"



CMyWorkTime::CMyWorkTime(void)
{
}
CMyWorkTime::CMyWorkTime(int work_time,int rest_time):mp_start(NULL),mp_worktime(NULL)
{
	m_iwork = work_time;
	m_irest = rest_time;
}
CMyWorkTime::~CMyWorkTime(void)
{
	if(mp_start)delete mp_start;
	if(mp_worktime)delete mp_worktime;
}

void CMyWorkTime::Init()
{
	mp_start = new boost::posix_time::ptime(second_clock::local_time());
	mp_worktime = new boost::posix_time::time_period(*mp_start,time_duration(m_iwork+m_irest,0,0));//'5 'for test

}

void CMyWorkTime::Init(int t_hours,int t_minuts,int t_seconds)
{
	mp_start = new boost::posix_time::ptime(/*second_clock::local_time().date()*/day_clock::local_day(),time_duration(t_hours,t_minuts,t_seconds));
	mp_worktime = new boost::posix_time::time_period(*mp_start,time_duration(m_iwork+m_irest,0,0));//'5 'for test

}

bool CMyWorkTime::LeaveHappy(ptime t)
{
	return mp_worktime->contains(t);
}

bool CMyWorkTime::LeaveHappy( )
{
	return !mp_worktime->contains(second_clock::local_time());
}

//必须在init后才能调用
std::string CMyWorkTime::time_start_str()
{
	if(mp_start)
		return to_simple_string(*mp_start);
	return to_simple_string(second_clock::local_time());
}

//必须在init后才能调用
std::string CMyWorkTime::time_end_str()
{
	if(mp_worktime)
		return to_simple_string(mp_worktime->end());
	return to_simple_string(second_clock::local_time());
}