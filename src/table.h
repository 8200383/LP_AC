/* 
 * Created by Micael Dias on 10/12/20.
 */

#ifndef _TABLE_H_
#define _TABLE_H_

#define MAX_DEPENDENT_NUMBER 5

typedef struct
{
	float monthly_pay;
	float percentage_per_dependent[MAX_DEPENDENT_NUMBER];
	int counter;
} s_table;

s_table* h_table_alloc(int n);

void h_table_init_from_str(s_table* tables, char* str);

#endif //_TABLE_H_
