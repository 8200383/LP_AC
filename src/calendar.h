/*
 * Created by Rui Gonçalves on 27/12/2020.
 * Edited by Micael Dias on 27/12/2020
 */

#ifndef CALENDAR_H_
#define CALENDAR_H_

typedef struct
{
	int day, month, year;
} s_date;

typedef enum
{
	JAN = 1,
	FEB = 2,
	MAR = 3,
	APR = 4,
	MAY = 5,
	JUN = 6,
	JUL = 7,
	AUG = 8,
	SEP = 9,
	OCT = 10,
	NOV = 11,
	DEC = 12
} e_month;

s_date* h_calendar_alloc();
s_date* h_calendar_init(const char* str);
s_date* h_calendar_get_date();
int h_calendar_check_str(const char* str);
int h_calendar_check_date(int day, int month, int year);
int h_calendar_check_leap_year(int year);
const char* h_calendar_str_from_month(e_month month);


#endif //_ALENDAR_H_
