//
// Created by Rui Gonçalves on 27/12/2020.
//

#include <stdio.h>
#include <stdlib.h>
#include "calendar.h"

int verify_leap_year(int year) {
	return (year % 400 == 0) || (year % 4 == 0 && year % 100 != 0);
}

int verify_date(int day, int month, int year) {

	if (year < 1000 || year > 9999)
		return 0;

	if (month < JAN || month > DEC)
		return 0;

	if (month == FEB && verify_leap_year(year) == 1) { // days 29
		if (day < 1 || day > 29)
			return 0;
	}

	if (month == FEB && verify_leap_year(year) == 0) { // days 28
		if (day < 1 || day > 28)
			return 0;
	}

	if ((month == JAN || month == MAR || month == MAY ||
		 month == JUL || month == AUG || month == OCT ||
		 month == DEC) && (day < 1 || day > 31))
		return 0;

	if ((month == FEB || month == APR || month == JUN ||
		 month == SEP || month == NOV) && (day < 1 || day > 30))
		return 0;

	return 1;
}

s_date *get_date() {
	int day, month, year;
	s_date *date;

	date = malloc(sizeof(s_date));
	if (date == NULL) {
		return NULL;
	}

	printf("Date: DD/MM/YYYY\n");
	scanf("%d/%d/%d", &day, &month, &year);


	if (verify_date(day, month, year) == 0)
		return NULL;


	date->year = year;
	date->month = month;
	date->day = day;

	return date;
}