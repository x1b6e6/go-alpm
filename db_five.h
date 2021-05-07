// db_five.h - Dynamic loading symbols from libalpm.so
//
// Copyright (c) 2021 The go-alpm Authors
//
// MIT Licensed. See LICENSE for details.

#if !SIX

#include <alpm.h>
#include <alpm_list.h>

int go_alpm_db_search(alpm_db_t* db,
					  alpm_list_t* needles,
					  alpm_list_t** result);

#endif
