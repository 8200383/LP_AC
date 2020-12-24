//
// Created by Hugo Carvalho on 12/24/20.
//

#ifndef _SEG_SOCIAL_H_
#define _SEG_SOCIAL_H_

typedef struct {
	char criteria;
	float employer;
	float employee;
} s_social_sec;

s_social_sec *social_sec_alloc(int n);

void social_sec_init(s_social_sec *data, char *str);

void social_sec_print(s_social_sec *data, int len);

s_social_sec *social_sec_add(s_social_sec *data, int *len);

s_social_sec *social_sec_del(s_social_sec *data, int *len);

s_social_sec *social_sec_edit(s_social_sec *data, int len);

void social_sec_save(s_social_sec *data, int len, const char *path);


#endif //_SEG_SOCIAL_H_
