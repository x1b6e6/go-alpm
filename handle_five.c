// handle_five.c - libalpm handle type and methods.
//
// Copyright (c) 2021 The go-alpm Authors
//
// MIT Licensed. See LICENSE for details

#if !SIX

#include <alpm_list.h>
#include <string.h>

#include "dynamic_five.h"
#include "handle_five.h"

static alpm_list_t* _get_architectures_five(alpm_handle_t* handle) {
	const char* (*get_arch)(alpm_handle_t*) = NULL;
	if (get_arch == NULL) {
		get_arch = dlsym(go_alpm_libalpm, "alpm_option_get_arch");
	}

	alpm_list_t* list = NULL;
	alpm_list_add(list, strdup(get_arch(handle)));

	return list;
}

static int _set_architectures_five(alpm_handle_t* handle,
								   alpm_list_t* architectures) {
	static int (*set_arch)(alpm_handle_t*, const char*) = NULL;
	if (set_arch == NULL) {
		set_arch = dlsym(go_alpm_libalpm, "alpm_option_set_arch");
	}

	const char* arch = architectures->data;
	return set_arch(handle, arch);
}

static int _rm_architecture_five(alpm_handle_t* handle, const char* arch) {
	// TODO: do something
	return 0;
}

alpm_list_t* go_alpm_option_get_architectures(alpm_handle_t* handle) {
	static alpm_list_t* (*get_architectures)(alpm_handle_t*) = NULL;
	if (get_architectures == NULL) {
		go_alpm_is_six();  // for init go_alpm_libalpm
		get_architectures =
			dlsym(go_alpm_libalpm, "alpm_option_get_architectures");
		if (get_architectures == NULL) {
			get_architectures = _get_architectures_five;
		}
	}
	return get_architectures(handle);
}

int go_alpm_option_set_architectures(alpm_handle_t* handle,
									 alpm_list_t* architectures) {
	static int (*set_architectures)(alpm_handle_t*, alpm_list_t*) = NULL;
	if (set_architectures == NULL) {
		go_alpm_is_six();  // for init go_alpm_libalpm
		set_architectures =
			dlsym(go_alpm_libalpm, "alpm_option_set_architectures");
		if (set_architectures == NULL) {
			set_architectures = _set_architectures_five;
		}
	}
	return set_architectures(handle, architectures);
}

int go_alpm_option_add_architecture(alpm_handle_t* handle, const char* arch) {
	static int (*add_architecture)(alpm_handle_t*, const char*) = NULL;
	if (add_architecture == NULL) {
		go_alpm_is_six();  // for init go_alpm_libalpm
		add_architecture =
			dlsym(go_alpm_libalpm, "alpm_option_add_architecture");
		if (add_architecture == NULL) {
			add_architecture = dlsym(go_alpm_libalpm, "alpm_option_set_arch");
		}
	}
}

int go_alpm_option_remove_architecture(alpm_handle_t* handle,
									   const char* arch) {
	static int (*rm_architecture)(alpm_handle_t*, const char*) = NULL;
	if (rm_architecture == NULL) {
		go_alpm_is_six();  // for init go_alpm_libalpm
		rm_architecture =
			dlsym(go_alpm_libalpm, "alpm_option_remove_architecture");
		if (rm_architecture == NULL) {
			rm_architecture = _rm_architecture_five;
		}
	}

	return rm_architecture(handle, arch);
}

#endif
