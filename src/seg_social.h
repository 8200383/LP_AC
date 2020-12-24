//
// Created by Hugo Carvalho on 12/24/20.
//

#ifndef _SEG_SOCIAL_H_
#define _SEG_SOCIAL_H_

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

/*
void social_sec_init(s_arr_seg_social* data, char* str);

void social_sec_print(s_arr_seg_social* data, int len);

s_arr_seg_social* social_sec_add(s_arr_seg_social* data, int* len);

s_arr_seg_social* social_sec_del(s_arr_seg_social* data, int* len);

s_arr_seg_social* social_sec_edit(s_arr_seg_social* data, int len);

void social_sec_save(s_arr_seg_social* data, int len, const char* path);
*/

#endif //_SEG_SOCIAL_H_
