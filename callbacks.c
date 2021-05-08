// callbacks.c - universal interface for callbacks_five.go and callbacks_six.go
//
// Copyright (c) 2013,2021 The go-alpm Authors
//
// MIT Licensed. See LICENSE for details.

#include "callbacks.h"

void go_alpm_logcb(void* c_ctx,
				   alpm_loglevel_t level,
				   const char* fmt,
				   va_list arg) {
	ctx_t* ctx = c_ctx;
	char* s = malloc(128);
	if (s == NULL)
		return;
	int16_t length = vsnprintf(s, 128, fmt, arg);
	if (length > 128) {
		length = (length + 16) & ~0xf;
		s = realloc(s, length);
	}
	if (s != NULL) {
		go_alpm_go_logcb(&ctx->go_cb, ctx->go_ctx, level, s);
		free(s);
	}
}

void go_alpm_questioncb(void* c_ctx, alpm_question_t* question) {
	ctx_t* ctx = c_ctx;
	go_alpm_go_questioncb(&ctx->go_cb, ctx->go_ctx, question);
}

ctx_t* go_alpm_init_ctx(ctx_t* ctx, void* go_cb, go_ctx_t* go_ctx) {
	if (ctx == NULL) {
		ctx = malloc(sizeof(ctx_t));
	}
	ctx->go_cb = *(void**)go_cb;
	ctx->go_ctx = go_ctx;

	return ctx;
}
