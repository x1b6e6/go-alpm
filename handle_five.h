// handle_five.h - libalpm handle type and methods.
//
// Copyright (c) 2021 The go-alpm Authors
//
// MIT Licensed. See LICENSE for details

#if !SIX

#include <alpm.h>
#include <alpm_list.h>

alpm_list_t* go_alpm_option_get_architectures(alpm_handle_t* handle);
int go_alpm_option_set_architectures(alpm_handle_t* handle,
									 alpm_list_t* architectures);
int go_alpm_option_add_architecture(alpm_handle_t* handle, const char*);
int go_alpm_option_remove_architecture(alpm_handle_t* handle, const char*);

#endif
