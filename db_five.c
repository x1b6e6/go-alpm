// db_five.c - Dynamic loading symbols from libalpm.so
//
// Copyright (c) 2021 The go-alpm Authors
//
// MIT Licensed. See LICENSE for details.

#if !SIX

#include "db_five.h"
#include "dynamic_five.h"

static int _db_search_five(alpm_db_t* db,
						   alpm_list_t* needles,
						   alpm_list_t** result) {
	alpm_list_t* (*db_search)(alpm_db_t*, alpm_list_t*) = (void*)alpm_db_search;
	*result = db_search(db, needles);

	if (*result != NULL) {
		return 0;
	} else {
		// TODO: return normal errorcode
		return -1;
	}
}

int go_alpm_db_search(alpm_db_t* db,
					  alpm_list_t* needles,
					  alpm_list_t** result) {
	static int (*db_search)(alpm_db_t*, alpm_list_t*, alpm_list_t**) = NULL;
	if (db_search == NULL) {
		if (go_alpm_is_six() == false) {
			db_search = _db_search_five;
		} else {
			db_search = (void*)alpm_db_search;
		}
	}

	db_search(db, needles, result);
}

#endif
