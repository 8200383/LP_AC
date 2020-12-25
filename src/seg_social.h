//
// Created by Hugo Carvalho on 12/24/20.
//

#ifndef _SEG_SOCIAL_H_
#define _SEG_SOCIAL_H_

#include "error.h"

typedef struct
{
	char criteria;
	float employer;
	float employee;
} s_seg_social;

typedef struct
{
	s_seg_social* data;
	int used;
	int max_capacity;
} s_arr_seg_social;

s_arr_seg_social* h_seg_social_alloc(int initial_capacity);

s_error* h_seg_social_parse(s_arr_seg_social* array, char* str);

s_error* h_seg_social_write(s_arr_seg_social* array, const char* path);

s_error* h_seg_social_print(s_arr_seg_social* array);

s_error* h_seg_social_edit(s_arr_seg_social* array);

s_error* h_seg_social_delete(s_arr_seg_social* array);

s_error* h_seg_social_add(s_arr_seg_social* array);

#endif //_SEG_SOCIAL_H_
