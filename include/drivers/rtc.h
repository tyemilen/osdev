#ifndef RTC_H_
#define RTC_H_

#include <stdint.h>

#define RTC_PORT 0x70
#define RTC_DATA 0x71

#define RTC_SECONDS 0x00
#define RTC_MINUTES 0x02
#define RTC_HOURS 0x04
#define RTC_DAY 0x07
#define RTC_MONTH 0x08
#define RTC_YEAR 0x09

void rtc_date();

uint8_t rtc_read(uint8_t reg);

#endif // RTC_H_