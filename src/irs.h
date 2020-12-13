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

s_irs* h_irs_alloc(unsigned int n);
void h_irs_init_from_str(s_irs* data, char* str);
void h_irs_print(s_irs* data, int size);

#endif //_IRS_H_
