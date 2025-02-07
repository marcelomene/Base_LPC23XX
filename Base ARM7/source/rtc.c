/*******************************************
	@file: rtc.c
		Real Time Clock Driver
		for LPC23XX-ARM7 DEV Board
	
	@author: Marcelo Menezes
	
	rtc_init info by Marcos Stemmer at http://www.politecnica.pucrs.br/~stemmer/labproc2v/tutorial-lpc2378/lpc-05.html
********************************************/

#include <lpc23xx.h>
#include "rtc.h"

#define CCLK 12000000 /* System clock of 12MHz */

void rtc_init(uint8_t mode)
{
	RTC_CCR = 0; /* Stop Clock and initialize other registers */
	
	if(mode == EXTERNAL_CLK_MODE)
		RTC_CCR = 0x11; /* One at bit 0 and bit 4, initializing the RTC with the external clock source 32.768Hz  */
	else
	{
		RTC_PREINT =  (CCLK >> 17)-1; /* Integer part of the frequency prescaler  */
		RTC_PREFRAC = ((CCLK >> 2) & 0x7fff); /* Fractional part of the frequency prescaler  */
		RTC_CCR=0x01;		/* One at bit 0 and zero at bit 4, initializing the RTC with internal clock source */
	}
}

void convert_rtc_tm(sRTC_TIME *time, struct tm *ctm)
{
	/* Converts values from sRTC_TIME struct to C standard tm struct */
	ctm->tm_hour = time->hour;
	ctm->tm_min = time->minute;
	ctm->tm_sec = time->second;
	
	ctm->tm_wday = time->weekDay;
	ctm->tm_yday = time->yearDay;
	ctm->tm_mon = time->month;
	ctm->tm_year = time->year;
}

rtcTimestamp rtc_get_timestamp()
{
	/* Uses the C standard tm struct to create the timestamp using mktime() */
	sRTC_TIME time = rtc_get_time();
	static struct tm cTime;
	
	convert_rtc_tm(&time, &cTime);
	cTime.tm_isdst = 0;
	
	return abs(mktime(&cTime));
}

sRTC_TIME rtc_get_time()
{
	/* Reads all the values from the RTC registers into the a struct sRTC_TIME variable. */
	sRTC_TIME time;
	time.hour = RTC_HOUR;
	time.minute = RTC_MIN;
	time.second = RTC_SEC;
	time.month = RTC_MONTH;
	time.monthDay = RTC_DOM;
	time.weekDay = RTC_DOW;
	time.yearDay = RTC_DOY;
	time.year = RTC_YEAR;
	return time;
}