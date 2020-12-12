/* 
 * Created by Micael Dias on 10/12/20.
 */

#ifndef _IRS_H_
#define _IRS_H_

#define MAX_DEPENDENT_NUMBER 5

typedef struct
{
	float monthly_pay;
	float percentage_per_dependent[MAX_DEPENDENT_NUMBER];
	int counter;
} s_irs;

s_table* h_table_alloc(int n);

#endif //_IRS_H_
