/* 
 * Created by Micael Dias on 10/12/20.
 */

#ifndef _IRS_H_
#define _IRS_H_

#define MAX_DEPENDENT_NUMBER 6

typedef struct
{
	float monthly_pay;
	float percentage_per_dependent[MAX_DEPENDENT_NUMBER];
	int counter;
} s_irs;

typedef void (* h_irs_pair_func)(s_irs*, char, char*, int*);

s_irs* h_irs_alloc(unsigned int n);
int h_irs_parse(s_irs* data, char* str, h_irs_pair_func pair_func);
void h_irs_print(s_irs* data, int size);
void h_irs_edit(s_irs* data, unsigned int data_len, unsigned int position);
void h_irs_build(s_irs* data, char key, char* str, int* dependents);

#endif //_IRS_H_
