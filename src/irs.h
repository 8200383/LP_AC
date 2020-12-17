/* 
 * Created by Micael Dias on 10/12/20.
 */

#ifndef _IRS_H_
#define _IRS_H_

typedef enum {
	H_IRS_UP_TO,
	H_IRS_BEYOND
} e_type;

typedef struct
{
	e_type monthly_pay_type;
	float monthly_pay_value;
	float dependent_0;
	float dependent_1;
	float dependent_2;
	float dependent_3;
	float dependent_4;
	float dependent_5_or_more;
} s_irs;

typedef struct
{
	s_irs* single;
	s_irs* unique_holder;
	s_irs* two_holders;
} s_irs_tables;

typedef void (* h_irs_pair_func)(s_irs*, char*, int, int*);

s_irs* h_irs_alloc(unsigned int n);
int h_irs_parse(s_irs* data, char* str, h_irs_pair_func pair_func);
void h_irs_print(s_irs* data, int size);
int h_irs_edit(s_irs* data, int size, int position);
void h_irs_build(s_irs* data, char* str, int line, int* dependents);
int h_irs_write(s_irs* data, int size, const char* path);
int h_irs_read(s_irs* data, const char* path);
int h_irs_free(s_irs* data);

#endif //_IRS_H_
