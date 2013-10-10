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
	mp_worktime = new boost::posix_time::time_period(*mp_start,time_duration(m_iwork+m_irest,0,0));

}

bool CMyWorkTime::LeaveHappy(ptime t)
{
	return mp_worktime->contains(t);
}