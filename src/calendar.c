#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "calendar.h"
#include "colors.h"

s_date* h_calendar_alloc()
{
	s_date* date;

	date = malloc(sizeof(s_date));
	if (date == NULL)
		return NULL;

	date->day = 0;
	date->month = 0;
	date->year = 0;

	return date;
}

s_date* h_calendar_init(const char* str)
{
	s_date* date;
	int day, month, year;

	date = h_calendar_alloc();
	if (date == NULL)
		return NULL;

	sscanf(str, "%d/%d/%d", &day, &month, &year);

	date->day = day;
	date->month = month;
	date->year = year;
}

s_date* h_calendar_get_date(const char* msg)
{
	int day, month, year, error;
	s_date* date;

	date = h_calendar_alloc();
	if (date == NULL)
		return NULL;

	error = 0;
	do {
		printf("%s (DD/MM/YYYY)\n", msg);
		scanf("%d/%d/%d", &day, &month, &year);

		if (h_calendar_check_date(day, month, year) == 0)
			error = 1;

		if (error == 1)
			puts(RED("Data incorreta"));

	} while (error == 1);

	date->year = year;
	date->month = month;
	date->day = day;

	return date;
}

int h_calendar_leap_year(int year)
{
	return (year % 400 == 0) || (year % 4 == 0 && year % 100 != 0);
}

// usado no proc.c
int h_calendar_days_in_month(e_month month)
{
	if (month == FEB || month == APR || month == JUN || month == SEP || month == NOV)
		return 30;

	return 31;
}

int h_calendar_check_date(int day, int month, int year)
{
	if (year < 1000 || year > 9999)
		return 0;

	if (month < JAN || month > DEC)
		return 0;

	if (month == FEB && h_calendar_leap_year(year) == 1)
	{ // days 29
		if (day < 1 || day > 29)
			return 0;
	}

	if (month == FEB && h_calendar_leap_year(year) == 0)
	{ // days 28
		if (day < 1 || day > 28)
			return 0;
	}

	if (day < 1 || day > h_calendar_days_in_month(month))
		return 0;

	return 1;
}

const char* h_calendar_str_from_month(e_month month)
{
	const char* strings[] = { "jan", "feb", "mar", "apr", "may", "jun", "jul", "aug", "sep", "oct", "nov", "dec" };

	return strings[month];
}
