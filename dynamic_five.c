// dynamic_five.c - Dynamic loading symbols from libalpm.so
//
// Copyright (c) 2021 The go-alpm Authors
//
// MIT Licensed. See LICENSE for details.

#if !SIX

#include "dynamic_five.h"

void* go_alpm_libalpm = NULL;

bool go_alpm_is_six() {
	static bool six = false;
	if (go_alpm_libalpm == NULL) {
		go_alpm_libalpm = dlopen("alpm", RTLD_LAZY | RTLD_LOCAL);

		void* set_architectures =
			dlsym(go_alpm_libalpm, "alpm_option_set_architectures");

		six = set_architectures != NULL;
	}

	return six;
}

#endif
