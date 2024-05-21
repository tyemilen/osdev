#ifndef RTC_H_
#define RTC_H_

#include <stdint.h>

void rtc_init();

uint8_t rtc_get_year();
uint8_t rtc_get_month();
uint8_t rtc_get_day();
uint8_t rtc_get_weekday();
uint8_t rtc_get_hour();
uint8_t rtc_get_minute();
uint8_t rtc_get_second();

#endif // RTC_H_