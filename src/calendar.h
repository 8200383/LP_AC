/**
 * @file calendar.c
 * @author Rui Gonçalves, Micael Dias
 * @date 27/12/2020
 * @brief Helper functions to handle Dates
 */

#ifndef _CALENDAR_H_
#define _CALENDAR_H_

/**
 * @struct s_date
 * A structure to represent dates
 */
typedef struct
{
	int day;
	int month;
	int year;
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
s_date* h_calendar_get_date();
int h_calendar_check_date(int day, int month, int year);
int h_calendar_check_leap_year(int year);
const char* h_calendar_str_from_month(e_month month);

#endif //_CALENDAR_H_
