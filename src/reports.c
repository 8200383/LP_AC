#include <time.h>

#include "reports.h"
#include "calendar.h"

void h_reports_senior_employees(s_arr_employees* employees_array)
{
	int i;
	int year_now;
	int years_difference;
	struct tm* local_time;

	if (employees_array == NULL || employees_array->used == 0)
	{
		puts(RED("[!] Employees vazio ou não inicializado"));
		return;
	}

	local_time = h_calendar_init_local_time();
	year_now = h_calendar_get_year(local_time);

	printf(YELLOW("Antiguidades dos funcionários\n"));

	for (i = 0; i < employees_array->used; i++)
	{
		years_difference = year_now - employees_array->employees[i].entry_date->year;

		if (years_difference >= EMPLOYEE_SENIORITY &&
			employees_array->employees[i].removed == 0 &&
			employees_array->employees[i].leaving_date->year >= year_now)
		{
			printf(CYAN("%d | %s %s | %d Anos\n"),
				employees_array->employees[i].code,
				employees_array->employees[i].first_name,
				employees_array->employees[i].last_name,
				years_difference);
		}
	}
}