/***
 *npmsel.h - Date/Time basic functions
 *    Copyright (c) 2000-2012, NetPosa Technologies,Ltd. All rights reserved.
 *Purpose:
 **************************************************************************************/

#ifndef _npmsel_h_
#define _npmsel_h_

#if _MSC_VER > 1000
	#pragma once
#endif

#include <time.h>
#include <sys/timeb.h>
#ifdef __linux__
	#include <sys/time.h>
	#include <sys/times.h>
	#include <unistd.h>
#endif
#include "npdebug.h"

#if !defined(_WINBASE_) && !defined(_SYSTEMTIME_)
	typedef struct _SYSTEMTIME
	{
		WORD wYear;
		WORD wMonth;
		WORD wDayOfWeek;
		WORD wDay;
		WORD wHour;
		WORD wMinute;
		WORD wSecond;
		WORD wMilliseconds;
	} SYSTEMTIME;
	#define _SYSTEMTIME_
#endif

#if defined(__linux__) && defined(NP_RDTSC_SUPPORTED)
	#define OPTIMIZED_TIME_FUNCTION_
#endif

/* 获取系统当前绝对时间 */
LTMSEL GetMsel();

/* 把绝对时间转化为年月日形式的时间结构 */
/* toLocal，表示是否返回localtime；*/
/* 失败时间结构返回全0 */
SYSTEMTIME ToTime(LTMSEL lt, BOOL toLocal DEFAULT_PARAM(TRUE));

/* 把年月日形式的时间结构转换为绝对时间 */
/* isLocal，表示st是否为localtime；*/
/* 返回时间st距离MIN_UTC_MSEL的毫秒数，失败返回INVALID_UTC_MSEL */
/* 注意：st必须按照localtime和systemtime都是合法的UTC时间 */
LTMSEL ToMsel(const SYSTEMTIME REF_OPERATER st, BOOL isLocal DEFAULT_PARAM(TRUE));

/* 得到CPU时钟周期计数 */
/* 对于时钟频率为4G的CPU，大概136年轮转一圈 */
/* INT64 GetCycleCount(); */
/*
注：对于采用动态节能技术的CPU（如时下流行的intel的SpeedStep技术笔记本电脑CPU），其处理器频率
	不会始终保持一致，而是时刻变化的，RDTSC读取的仅仅是时钟周期数，两个RDTSC值之差除以CPU的
	额定频率并不等于所耗费时间。
		对于多核CPU，不同CPU得到的RDTSC值可能会有差异，可以使用WIN32函数SetThreadAffinityMask()来指定运行CPU，
	例子可以参考INT64 GetCPUFreq()的实现，见 "NPTime.cpp"
		所以GetCycleCount()可以用来做：极短时间的代码性能测试、产生64位证书唯一标识等。
	<<<<<<<< 在CPU没有固定频率的平台，GetCycleCount()不可以用来作定时用 >>>>>>>>
	WIN32平台的精确定时可以使用GetHighTickCount()、GetHighTickFrequency()，见 "NPTime.h"
*/

/* 对GetCycleCount()函数的修正值 */
/* INT64 CYCLE_COUNT_REVISE(); */

BOOL IsValidMsel(LTMSEL lt);
BOOL IsLeapYear(int year);

/* 获取指定月份的天数，参数非法返回0 */
int GetMonthDays(int year, int month);

/* 是否为有效日期『非GMT时间范围』 */
BOOL IsValidDate(int year, int month, int day);

/* 得到时间权重『非GMT时间范围，用于时间日期的大小比较』 */
LTMSEL TimeWeight(int year, int month, int day, int hour, int minute, int second, int milli);
/* isLocal，st是否为localtime；得到时间范围类型，-1，< MIN_UTC_MSEL；1，> MAX_UTC_MSEL；0，在有效范围内。 */
int TimeRangeType(const SYSTEMTIME REF_OPERATER st, BOOL isLocal);
BOOL IsValidTime(const SYSTEMTIME REF_OPERATER st, BOOL isLocal, BOOL checkWeek);
/* 获取时区值：zone == (local time - system time) */
LTMSEL GetTimeZoneMsel();
BOOL ToTimeEx(LTMSEL lt, SYSTEMTIME* st, BOOL toLocal);

#if defined(__linux__)
	DWORD GetTickCount();
	void Sleep(DWORD ms);
	void GetSystemTime(SYSTEMTIME* st);
	void GetLocalTime(SYSTEMTIME* st);
#endif /* __linux__ */

SYSTEMTIME SystemTimeToLocalTime(const SYSTEMTIME REF_OPERATER st);
SYSTEMTIME LocalTimeToSystemTime(const SYSTEMTIME REF_OPERATER st);


/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/*++++++++++++++++++++++++ 内联函数实现 ++++++++++++++++++++++++*/
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

#if defined(WIN32)
	#ifndef NP_RDTSC_SUPPORTED
		#error NP_RDTSC_SUPPORTED not defined.
	#endif
	/* 得到CPU时钟周期计数 */
	#ifdef _WIN64
		inline INT64 GetCycleCount()	{	return __rdtsc();	}
	#else
		#pragma warning(disable: 4035)	/* 'function' : no return value */
		inline INT64 GetCycleCount()	{	__asm RDTSC	}
		#pragma warning(error: 4035)
	#endif

#elif defined(__linux__)
	#if defined(_NP_IS_X86)
		#ifndef NP_RDTSC_SUPPORTED
			#error NP_RDTSC_SUPPORTED not defined.
		#endif
		inline INT64 GetCycleCount()
		{
		#if 64==NPR_SYS_BITS
			UINT32 hi, lo;
			__asm__ __volatile__("rdtsc" : "=a"(lo), "=d"(hi));
			return ((UINT64)lo | ((UINT64)hi << 32));
		#else
			INT64  x;
			__asm__ __volatile__(".byte 0x0f, 0x31" : "=A" (x));
			return x;
		#endif

		}
	#else
		/*inline INT64 GetCycleCount()
		{
			struct timespec ts;
			clock_gettime(CLOCK_REALTIME, &ts);
			return ((INT64)(ts.tv_sec))*1000000000 + ts.tv_nsec;
		}*/
	#endif
#endif

#ifdef NP_RDTSC_SUPPORTED
inline INT64 CYCLE_COUNT_REVISE()
{
	INT64 cy = GetCycleCount();
	cy = GetCycleCount() - cy;
	return cy;
}
#endif

inline BOOL IsValidMsel(LTMSEL lt)
	{	return MIN_UTC_MSEL<=lt && lt<=MAX_UTC_MSEL;	}

inline BOOL IsLeapYear(int year)
	{	return (0==year%4 && 0!=year%100) || 0==year%400;	}

inline int GetMonthDays(int year, int month)
{
	int month_days;
	static int days_inited = 0;
	static int days[13];
	if(!days_inited)
	{
		days[0] = 0;
		days[1] = 31;	/* 1 */
		days[2] = 28;	/* 2 */
		days[3] = 31;	/* 3 */
		days[4] = 30;	/* 4 */
		days[5] = 31;	/* 5 */
		days[6] = 30;	/* 6 */
		days[7] = 31;	/* 7 */
		days[8] = 31;	/* 8 */
		days[9] = 30;	/* 9 */
		days[10] = 31;	/* 10 */
		days[11] = 30;	/* 11 */
		days[12] = 31;	/* 12 */
		days_inited = 1;
	}
	if(month<1 || month>12)
		return 0;
	month_days = (2==month
					? (IsLeapYear(year) ? 29 : 28)
					: days[month]);
	return month_days;
}

inline BOOL IsValidDate(int year, int month, int day)
{
	int month_days = GetMonthDays(year, month);
	if(0 == month_days)
		return FALSE;
	if(day<1 || day>month_days)
		return FALSE;
	return TRUE;
}

inline LTMSEL TimeWeight(int year, int month, int day, int hour, int minute, int second, int milli)
{
	LTMSEL lt;
	ASSERT(IsValidDate(year, month, day));
	ASSERT(0<=hour && hour<=23);
	ASSERT(0<=minute && minute<=59);
	ASSERT(0<=second && second<=59);
	ASSERT(0<=milli && milli<=999);

	lt = (LTMSEL)year * 12;		/* 月数 */
	lt = (lt + (month-1)) * 31;	/* 天数 */
	lt = (lt + (day-1)) * 24;	/* 小时数 */
	lt = (lt + hour) * 60;		/* 分钟数 */
	lt = (lt + minute) * 60;	/* 秒数 */
	lt = (lt + second) * 1000;	/* 毫秒数 */
	return lt + milli;			/* 得到最终时间权值毫秒数 */
}

#ifdef OPTIMIZED_TIME_FUNCTION_
inline LTMSEL LinuxGetMsel_()
#else
inline LTMSEL GetMsel()
#endif
{
#if defined(WIN32)
	LTMSEL ft;
	GetSystemTimeAsFileTime((FILETIME*)&ft);
	/* 116444736000000000i64: Number of 100 nanosecond units from 1/1/1601 to 1/1/1970 */
	return (ft - (116444736000000000i64 + 5000i64)) / 10000i64;
#elif defined(__linux__)
	static int clock_id = 5; /* CLOCK_REALTIME_COARSE */
	struct timespec tp;
	if(0 == clock_gettime(clock_id, &tp))
		return (LTMSEL)tp.tv_sec*1000 + (tp.tv_nsec+(500*1000))/(1000*1000);
	clock_id = CLOCK_REALTIME;
	clock_gettime(clock_id, &tp);
	return (LTMSEL)tp.tv_sec*1000 + (tp.tv_nsec+(500*1000))/(1000*1000);
	/* 某些平台可能需要下面的旧的实现方式，此法效率要低一些
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return (LTMSEL)tv.tv_sec*1000 + (tv.tv_usec+500)/1000;
	*/
#endif
}

inline LTMSEL GetTimeZoneMsel()
{
#if defined(WIN32)
	struct _timeb b;
  #if defined(_NP_IS_VC6)
	_ftime(&b);
  #else
	_ftime_s(&b);
  #endif
	return (LTMSEL)(-b.timezone) * 60 * 1000;
#elif defined(__linux__)
	struct timezone tz;
	struct timeval tv;
	gettimeofday(&tv, &tz);
	return (LTMSEL)(-tz.tz_minuteswest) * 60 * 1000;
#endif
}

inline BOOL ToTimeEx(LTMSEL lt, SYSTEMTIME* st, BOOL toLocal)
{
	if(st)
	{
		time_t t;
		struct tm ltm;

		if(!IsValidMsel(lt))
		{
			ASSERT(FALSE);
			return FALSE;
		}

		t = (time_t)(lt/1000);
#if defined(WIN32)
	#if defined(_NP_IS_VC6)
		if(toLocal)
			ltm = *localtime(&t);
		else
			ltm = *gmtime(&t);
	#else
		if(toLocal)
			localtime_s(&ltm, &t);
		else
			gmtime_s(&ltm, &t);
	#endif
#elif defined(__linux__)
		if(toLocal)
			localtime_r(&t, &ltm);
		else
			gmtime_r(&t, &ltm);
#endif
		st->wYear = (WORD)(ltm.tm_year + 1900);
		st->wMonth = (WORD)(ltm.tm_mon + 1);
		st->wDay = (WORD)ltm.tm_mday;
		st->wHour = (WORD)ltm.tm_hour;
		st->wMinute = (WORD)ltm.tm_min;
		st->wSecond = (WORD)ltm.tm_sec;
		st->wDayOfWeek = (WORD)ltm.tm_wday; /* Sunday is 0, Monday is 1, and so on. */
		st->wMilliseconds = (WORD)(lt%1000);
		return TRUE;
	}
	ASSERT(FALSE);
	return FALSE;
}

inline SYSTEMTIME ToTime(LTMSEL lt, BOOL toLocal)
{
	SYSTEMTIME st;
	if(!ToTimeEx(lt, &st, toLocal))
		memset(&st, 0, sizeof(st));
	return st;
}

inline int TimeRangeType(const SYSTEMTIME REF_OPERATER st, BOOL isLocal)
{
	static LTMSEL ltSysMin = MIN_UTC_MSEL;
	static LTMSEL ltSysMax = MIN_UTC_MSEL;
	static LTMSEL ltLocMin = MIN_UTC_MSEL;
	static LTMSEL ltLocMax = MIN_UTC_MSEL;
	LTMSEL lt;

	if(MIN_UTC_MSEL == ltSysMin)
	{
		SYSTEMTIME tst;

		tst = ToTime(MIN_UTC_MSEL, FALSE);
		ltSysMin = TimeWeight(tst.wYear, tst.wMonth, tst.wDay, tst.wHour, tst.wMinute, tst.wSecond, tst.wMilliseconds);

		tst = ToTime(MAX_UTC_MSEL, FALSE);
		ltSysMax = TimeWeight(tst.wYear, tst.wMonth, tst.wDay, tst.wHour, tst.wMinute, tst.wSecond, tst.wMilliseconds);

		tst = ToTime(MIN_UTC_MSEL, TRUE);
		ltLocMin = TimeWeight(tst.wYear, tst.wMonth, tst.wDay, tst.wHour, tst.wMinute, tst.wSecond, tst.wMilliseconds);

		tst = ToTime(MAX_UTC_MSEL, TRUE);
		ltLocMax = TimeWeight(tst.wYear, tst.wMonth, tst.wDay, tst.wHour, tst.wMinute, tst.wSecond, tst.wMilliseconds);
	}

	lt = TimeWeight(st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond, st.wMilliseconds);

	if(isLocal)
	{
		if(lt < ltLocMin)
			return -1;
		if(lt > ltLocMax)
			return 1;
		return 0;
	}

	if(lt < ltSysMin)
		return -1;
	if(lt > ltSysMax)
		return 1;
	return 0;
}

inline BOOL IsValidTime(const SYSTEMTIME REF_OPERATER st, BOOL isLocal, BOOL checkWeek)
{
	return IsValidDate(st.wYear, st.wMonth, st.wDay)
		&& /*0<=st.wHour && */st.wHour<=23
		&& /*0<=st.wMinute && */st.wMinute<=59
		&& /*0<=st.wSecond && */st.wSecond<=59
		&& /*0<=st.wMilliseconds && */st.wMilliseconds<=999
		&& 0 == TimeRangeType(st, isLocal)
		&& (!checkWeek || /*0<=st.wDayOfWeek && */st.wDayOfWeek<=6);
}

#if defined(_MSC_VER)
	#pragma warning(disable: 4702) /* unreachable code */
#endif
inline LTMSEL ToMsel(const SYSTEMTIME REF_OPERATER st, BOOL isLocal)
{
	if(IsValidTime(st, isLocal, FALSE/*TRUE*/)/* && 0 == TimeRangeType(st, !isLocal)*/)
	{
		LTMSEL lt;
		struct tm atm;
		atm.tm_sec = st.wSecond;
		atm.tm_min = st.wMinute;
		atm.tm_hour = st.wHour;
		atm.tm_mday = st.wDay;
		atm.tm_mon = st.wMonth - 1;		/* tm_mon is 0 based */
		atm.tm_year = st.wYear - 1900;	/* tm_year is 1900 based */
		atm.tm_isdst = -1;
		lt = (LTMSEL)mktime(&atm);
		ASSERT(lt != -1);				/* indicates an illegal input time */
		lt = lt * 1000 + st.wMilliseconds;
		if(isLocal)
			return lt;
		return lt + GetTimeZoneMsel();
	}
	return INVALID_UTC_MSEL;
}
#if defined(_MSC_VER)
	#pragma warning(default: 4702) /* unreachable code */
#endif

inline SYSTEMTIME SystemTimeToLocalTime(const SYSTEMTIME REF_OPERATER st)
	{	return ToTime(ToMsel(st, FALSE), TRUE);	}

inline SYSTEMTIME LocalTimeToSystemTime(const SYSTEMTIME REF_OPERATER st)
	{	return ToTime(ToMsel(st, TRUE), FALSE);	}

#if defined(__linux__)
	#ifndef OPTIMIZED_TIME_FUNCTION_
		inline DWORD GetTickCount()
			{	return LinuxGetTickCount();	}
	#endif

	inline void Sleep(DWORD ms)
		{	LinuxSleep(ms);	}

	#ifdef OPTIMIZED_TIME_FUNCTION_
		inline void LinuxGetSystemTime_(SYSTEMTIME* st)
	#else
		inline void GetSystemTime(SYSTEMTIME* st)
	#endif
			{	ToTimeEx(GetMsel(), st, FALSE);	}

	#ifdef OPTIMIZED_TIME_FUNCTION_
		inline void LinuxGetLocalTime_(SYSTEMTIME* st)
	#else
		inline void GetLocalTime(SYSTEMTIME* st)
	#endif
			{	ToTimeEx(GetMsel(), st, TRUE);	}
#endif /* __linux__ */


/* 下面为对时间函数的优化版本实现 */
#ifdef OPTIMIZED_TIME_FUNCTION_

#include "npatomic.h"
EXTERN_C INT64 GetCPUFreq();

#define TIME_OPTIMIZED_TMPL1_(TYPE, svar)	\
	static TYPE svar;						\
	static long lock = 0;					\
	static INT64 DIFF;						\
	static INT64 cy0;						\
	static BOOL inited = false;				\
	INT64 cy;								\
	OSSpinLock(&lock, 0);					\
	if(!inited)								\
	{										\
		DIFF = GetCPUFreq() / 1000;			\
		cy0 = GetCycleCount() - DIFF;		\
		inited = true;						\
	}										\
	cy = GetCycleCount();					\
	if(cy-cy0 >= DIFF)						\
	{

#define TIME_OPTIMIZED_TMPL2_()				\
		cy0 = cy;							\
	}

#define TIME_OPTIMIZED_TMPL3_()				\
	OSSpinUnlock(&lock);

inline void GetSystemTime(SYSTEMTIME* pst)
{
	TIME_OPTIMIZED_TMPL1_(SYSTEMTIME, st)
	LinuxGetSystemTime_(&st);
	TIME_OPTIMIZED_TMPL2_()
	*pst = st;
	TIME_OPTIMIZED_TMPL3_()
}

inline void GetLocalTime(SYSTEMTIME* pst)
{
	TIME_OPTIMIZED_TMPL1_(SYSTEMTIME, st)
	LinuxGetLocalTime_(&st);
	TIME_OPTIMIZED_TMPL2_()
	*pst = st;
	TIME_OPTIMIZED_TMPL3_()
}

inline LTMSEL GetMsel()
{
	LTMSEL r;
	TIME_OPTIMIZED_TMPL1_(LTMSEL, lt)
	lt = LinuxGetMsel_();
	TIME_OPTIMIZED_TMPL2_()
	r = lt;
	TIME_OPTIMIZED_TMPL3_()
	return r;
}

inline DWORD GetTickCount()
{
	DWORD r;
	TIME_OPTIMIZED_TMPL1_(DWORD, tick)
	tick = LinuxGetTickCount();
	TIME_OPTIMIZED_TMPL2_()
	r = tick;
	TIME_OPTIMIZED_TMPL3_()
	return r;
}

#undef TIME_OPTIMIZED_TMPL1_
#undef TIME_OPTIMIZED_TMPL2_
#undef TIME_OPTIMIZED_TMPL3_

#endif	/* #ifdef OPTIMIZED_TIME_FUNCTION_ */

#endif /* #ifndef _npmsel_h_ */
