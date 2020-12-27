//
// Created by Rui Gonçalves on 27/12/2020.
//

#ifndef _CALENDAR_H_
#define _CALENDAR_H_

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

s_date* get_date();
int verify_date(int day, int month, int year);
int verify_leap_year(int year);


#endif //_CALENDAR_H_
