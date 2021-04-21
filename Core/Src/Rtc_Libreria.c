/*
 * Rtc_Libreria.c
 *
 *  Created on: Apr 20, 2021
 *      Author: wels
 */
#include "Rtc_Libreria.h"
#include "sapi.h"

extern RTC_HandleTypeDef hrtc;

char time[10];
char date[10];

RTC_TimeTypeDef sTime;
RTC_DateTypeDef sDate;

void set_time (void)
{
	sTime.Hours = 0x10;
	sTime.Minutes = 0x20;
	sTime.Seconds = 0x30;
	sTime.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
	sTime.StoreOperation = RTC_STOREOPERATION_RESET;
	sDate.WeekDay = RTC_WEEKDAY_TUESDAY;
	sDate.Month = RTC_MONTH_AUGUST;
	sDate.Date = 0x12;
	sDate.Year = 0x0;
	HAL_RTCEx_BKUPWrite(&hrtc, RTC_BKP_DR1, 0x32F2);  // backup register
}

void get_time(void)
{
	RTC_DateTypeDef gDate;
	RTC_TimeTypeDef gTime;
	HAL_RTC_GetTime(&hrtc, &gTime, RTC_FORMAT_BIN);
	HAL_RTC_GetDate(&hrtc, &gDate, RTC_FORMAT_BIN);
	sprintf((char*)time,"\n%02d:%02d:%02d\r\n",gTime.Hours, gTime.Minutes, gTime.Seconds);
	sprintf((char*)date,"%02d-%02d-%2d\r\n",gDate.Date, gDate.Month, 2000 + gDate.Year);  // I like the date first
}


