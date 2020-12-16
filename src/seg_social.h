//
// Created by TeZLa on 12/12/2020.
//

#ifndef _SEG_SOCIAL_H_
#define _SEG_SOCIAL_H_

typedef struct {
	float employer;
	float employee;
	char *criteria;
} s_taxes;

s_taxes* h_seg_social_taxes_alloc(int n);

void h_seg_social_init_from_str (s_taxes* data, char* str);

#endif //_SEG_SOCIAL_H_