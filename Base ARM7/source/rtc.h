#ifndef RTC_H
#define RTC_H

#include <stdint.h>
#include <time.h>
#include <stdlib.h>

#define INTERNAL_CLK_MODE 1
#define EXTERNAL_CLK_MODE 2

typedef time_t rtcTimestamp;

typedef struct 
{
	uint8_t hour; 
	uint8_t minute;
	uint8_t second;
	uint8_t monthDay;
	uint8_t weekDay;
	uint8_t yearDay;
	uint8_t month;
	uint8_t year;
} sRTC_TIME;

/* Functions */

void rtc_init(uint8_t mode);
sRTC_TIME rtc_get_time(void);
rtcTimestamp rtc_get_timestamp(void);

#endif
