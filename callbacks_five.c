// callbacks_five.c - Sets alpm callbacks to Go functions.
//
// Copyright (c) 2021 The go-alpm Authors
//
// MIT Licensed. See LICENSE for details.

#if !SIX

#include "callbacks.h"
#include "dynamic_five.h"

typedef void (*logcb_six_t)(void* c_ctx,
							alpm_loglevel_t level,
							const char* fmt,
							va_list arg);
typedef void (*logcb_five_t)(alpm_loglevel_t level,
							 const char* fmt,
							 va_list arg);

typedef void (*questioncb_six_t)(void* c_ctx, alpm_question_t* question);
typedef void (*questioncb_five_t)(alpm_question_t* question);

static ctx_t _logcb_five_ctx = {
	.go_cb = NULL,
	.go_ctx = NULL,
};
static ctx_t _questioncb_five_ctx = {
	.go_cb = NULL,
	.go_ctx = NULL,
};

static void _logcb_five(alpm_loglevel_t level, const char* fmt, va_list arg) {
	go_alpm_logcb(&_logcb_five_ctx, level, fmt, arg);
}

static void _questioncb_five(alpm_question_t* question) {
	go_alpm_questioncb(&_questioncb_five_ctx, question);
}

static void _set_logcb_five(alpm_handle_t* h, void* go_cb, go_ctx_t* go_ctx) {
	void* c_ctx = &_logcb_five_ctx;
	c_ctx = go_alpm_init_ctx(c_ctx, go_cb, go_ctx);

	int (*set_logcb)(alpm_handle_t*,
					 void (*)(alpm_loglevel_t, const char*, va_list)) =
		(void*)alpm_option_set_logcb;

	set_logcb(h, _logcb_five);
}

static void _set_logcb_six(alpm_handle_t* h, void* go_cb, go_ctx_t* go_ctx) {
	static void* (*get_logcb_ctx)(alpm_handle_t*) = NULL;
	if (get_logcb_ctx == NULL) {
		get_logcb_ctx = dlsym(go_alpm_libalpm, "alpm_option_get_logcb_ctx");
	}

	void* c_ctx = get_logcb_ctx(h);
	c_ctx = go_alpm_init_ctx(c_ctx, go_cb, go_ctx);

	int (*set_logcb)(alpm_handle_t*,
					 void (*)(void*, alpm_loglevel_t, const char*, va_list),
					 void*) = (void*)alpm_option_set_logcb;

	set_logcb(h, go_alpm_logcb, c_ctx);
}

void go_alpm_set_logcb(alpm_handle_t* handle, void* go_cb, go_ctx_t* go_ctx) {
	static void (*set_logcb)(alpm_handle_t*, void*, go_ctx_t*) = NULL;
	if (set_logcb == NULL) {
		if (go_alpm_is_six() == false) {
			set_logcb = _set_logcb_five;
		} else {
			set_logcb = _set_logcb_six;
		}
	}

	set_logcb(handle, go_cb, go_ctx);
}

static void _set_questioncb_five(alpm_handle_t* h,
								 void* go_cb,
								 go_ctx_t* go_ctx) {
	void* c_ctx = &_questioncb_five_ctx;
	c_ctx = go_alpm_init_ctx(c_ctx, go_cb, go_ctx);

	int (*set_questioncb)(alpm_handle_t*, void (*)(alpm_question_t*)) =
		(void*)alpm_option_set_questioncb;

	set_questioncb(h, _questioncb_five);
}

static void _set_questioncb_six(alpm_handle_t* h,
								void* go_cb,
								go_ctx_t* go_ctx) {
	static void* (*get_questioncb_ctx)(alpm_handle_t*) = NULL;
	if (get_questioncb_ctx == NULL) {
		get_questioncb_ctx =
			dlsym(go_alpm_libalpm, "alpm_option_get_questioncb_ctx");
	}

	void* c_ctx = get_questioncb_ctx(h);
	c_ctx = go_alpm_init_ctx(c_ctx, go_cb, go_ctx);

	int (*set_questioncb)(alpm_handle_t*, void (*)(void*, alpm_question_t*),
						  void*) = (void*)alpm_option_set_questioncb;

	set_questioncb(h, go_alpm_questioncb, c_ctx);
}

void go_alpm_set_questioncb(alpm_handle_t* handle,
							void* go_cb,
							go_ctx_t* go_ctx) {
	static void (*set_questioncb)(alpm_handle_t*, void*, go_ctx_t*) = NULL;
	if (set_questioncb == NULL) {
		if (go_alpm_is_six() == false) {
			set_questioncb = _set_questioncb_five;
		} else {
			set_questioncb = _set_questioncb_six;
		}
	}

	set_questioncb(handle, go_cb, go_ctx);
}

#endif
