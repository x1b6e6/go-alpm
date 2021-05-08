// callbacks_six.c - Sets alpm callbacks to Go functions.
//
// Copyright (c) 2021 The go-alpm Authors
//
// MIT Licensed. See LICENSE for details.

#if SIX

#include "callbacks.h"

void go_alpm_set_logcb(alpm_handle_t* handle, void* go_cb, go_ctx_t* go_ctx) {
	void* ctx = alpm_option_get_logcb_ctx(handle);
	ctx = go_alpm_init_ctx(ctx, go_cb, go_ctx);
	alpm_option_set_logcb(handle, go_alpm_logcb, ctx);
}

void go_alpm_set_questioncb(alpm_handle_t* handle,
							void* go_cb,
							go_ctx_t* go_ctx) {
	void* ctx = alpm_option_get_questioncb_ctx(handle);
	ctx = go_alpm_init_ctx(ctx, go_cb, go_ctx);
	alpm_option_set_questioncb(handle, go_alpm_questioncb, ctx);
}

#endif
