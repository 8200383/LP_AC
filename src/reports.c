#include <time.h>

#include "reports.h"
#include "calendar.h"

void h_reports_senior_employees(s_arr_employees* arr_employees)
{
	int i;
	int year_now;
	int years_difference;
	struct tm* local_time;

	if (arr_employees == NULL || arr_employees->used == 0)
	{
		puts(RED("[!] Employees vazio ou não inicializado"));
		return;
	}

	local_time = h_calendar_init_local_time();
	year_now = h_calendar_get_year(local_time);

	for (i = 0; i < arr_employees->used; i++)
	{
		years_difference = year_now - arr_employees->employees[i].entry_date->year;

		if (years_difference >= EMPLOYEE_SENIORITY)
		{
			puts("Funcionario Antigo");
		}
	}
}