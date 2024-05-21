#include "drivers/rtc.h"

#include "stdio.h"
#include "io/hal.h"

void rtc_init() {
	printf("Current time: 20%d, %d. %d. %d:%d:%d\n",
			rtc_get_year(), rtc_get_month(), rtc_get_day(),
			rtc_get_hour(), rtc_get_minute(), rtc_get_second());
}

// https://wiki.osdev.org/RTC
uint8_t rtc_get_year() {
	io_write8(0x70, 0x09);
	return io_read8(0x71);
}

uint8_t rtc_get_month() {
	io_write8(0x70, 0x08);
	return io_read8(0x71);
}

uint8_t rtc_get_day() {
	io_write8(0x70, 0x07);
	return io_read8(0x71);
}

uint8_t rtc_get_weekday() {
	io_write8(0x70, 0x06);
	return io_read8(0x71);
}

uint8_t rtc_get_hour() {
	io_write8(0x70, 0x04);
	return io_read8(0x71);
}

uint8_t rtc_get_minute() {
	io_write8(0x70, 0x02);
	return io_read8(0x71);
}

uint8_t rtc_get_second() {
	io_write8(0x70, 0x00);
	return io_read8(0x71);
}