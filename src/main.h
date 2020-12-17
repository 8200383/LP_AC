/* 
 * Created by Micael Dias on 17/12/20.
 */

#ifndef _MAIN_H_
#define _MAIN_H_

#include "util.h"
#include "irs.h"
#include "menu.h"
#include "strs.h"
#include "path.h"

s_irs* irs_init(const char* path, int* size);
int irs_save(s_irs_tables tables, int single_size, int unique_holder_size, int two_holders_size);

#endif //_MAIN_H_
