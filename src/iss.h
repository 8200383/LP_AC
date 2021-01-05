/*
 * Created by Hugo Carvalho on 12/24/20.
 */

#ifndef ISS_H
#define ISS_H

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

void h_seg_social_parse(s_arr_seg_social* array, char* str);
void h_seg_social_write(s_arr_seg_social* array, const char* path);
void h_seg_social_print(s_arr_seg_social* array);
void h_seg_social_edit(s_arr_seg_social* array);
void h_seg_social_delete(s_arr_seg_social* array);
void h_seg_social_add(s_arr_seg_social* array);

#endif //ISS_H
