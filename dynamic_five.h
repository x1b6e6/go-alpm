// dynamic_five.h - Dynamic loading symbols from libalpm.so
//
// Copyright (c) 2021 The go-alpm Authors
//
// MIT Licensed. See LICENSE for details.

#if !SIX

#include <dlfcn.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

extern void* go_alpm_libalpm;
extern bool go_alpm_is_six();

#endif
