//
// Created by Hugo Carvalho on 12/12/2020.
//

#include "seg_social.h"
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

s_taxes* h_seg_social_taxes_alloc(int n)
{
	int i;
	s_taxes* taxes;

	taxes = malloc(n * sizeof(*taxes));
	if (taxes == NULL)
		return NULL;

	for (i = 0; i < n; ++i)
	{
		taxes[i].employer = 0.0f;
		taxes[i].employee = 0.0f;
		taxes[i].criteria = NULL;
	}

	return taxes;
}

void h_seg_social_init_from_str(s_taxes* data, char* str)
{
	int i, count = 0, is_employer = 1, offset = -1;

	for (i = 0; str[i] != '\0'; i++)
	{
		if (offset == -1 && isalnum(str[i]))
			offset = i;

		if (offset != -1 && str[i] == ';')
		{
			str[i] = '\0';
			if (str[i - 1] == '%')
			{
				str[i - 1] = '\0';
				if (is_employer == 1)
				{
					data[count].employer = strtof(str + offset, NULL);
					is_employer = 0;
				}
				else
				{
					data[count].employee = strtof(str + offset, NULL);
					is_employer = 1;
				}
				offset = -1;
			}
			else
			{
				data[count].criteria = str + offset;
				offset = -1;
			}
		}

		if (str[i] == '\n')
			count++;
	}
}