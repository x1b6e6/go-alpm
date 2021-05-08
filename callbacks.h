// callbacks.c - universal interface for callbacks_five.go and callbacks_six.go
//
// Copyright (c) 2021 The go-alpm Authors
//
// MIT Licensed. See LICENSE for details.

#include <alpm.h>

typedef alpm_handle_t go_ctx_t;

typedef struct {
	void* go_cb;
	go_ctx_t* go_ctx;
} ctx_t;

void go_alpm_go_logcb(void* go_cb,
					  go_ctx_t* go_ctx,
					  alpm_loglevel_t level,
					  char* msg);
void go_alpm_go_questioncb(void* go_cb,
						   go_ctx_t* go_ctx,
						   alpm_question_t* question);

void go_alpm_logcb(void* c_ctx,
				   alpm_loglevel_t level,
				   const char* fmt,
				   va_list arg);
void go_alpm_questioncb(void* c_ctx, alpm_question_t* question);

void go_alpm_set_logcb(alpm_handle_t* handle, void* go_cb, go_ctx_t* go_ctx);
void go_alpm_set_questioncb(alpm_handle_t* handle,
							void* go_cb,
							go_ctx_t* go_ctx);

ctx_t* go_alpm_init_ctx(ctx_t* ctx, void* go_cb, go_ctx_t* go_ctx);
