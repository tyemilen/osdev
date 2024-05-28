#include "drivers/rtc.h"

#include "io/hal.h"
#include "stdio.h"

void rtc_date() {
	printf("Current time: 20%d, %d. %d. %d:%d:%d\n",
		   rtc_read(RTC_YEAR), rtc_read(RTC_MONTH), rtc_read(RTC_DAY),
		   rtc_read(RTC_HOURS), rtc_read(RTC_MINUTES), rtc_read(RTC_SECONDS));
}

// https://wiki.osdev.org/RTC
uint8_t rtc_read(uint8_t reg) {
	io_write8(RTC_PORT, reg);

	return io_read8(RTC_DATA);
}