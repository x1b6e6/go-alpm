// callbacks.go - Handles libalpm callbacks.
//
// Copyright (c) 2013 The go-alpm Authors
//
// MIT Licensed. See LICENSE for details.

package alpm

/*
#include <stdio.h>
#include "callbacks.h"
*/
import "C"

import (
	"unsafe"
)

type (
	logCallbackSig      func(interface{}, LogLevel, string)
	questionCallbackSig func(interface{}, QuestionAny)
	callbackContextPool map[*C.alpm_handle_t]interface{}
)

var DefaultLogLevel = LogWarning

func DefaultLogCallback(ctx interface{}, lvl LogLevel, s string) {
	if lvl <= DefaultLogLevel {
		print("go-alpm: ", s)
	}
}

var (
	logCallbackContextPool      callbackContextPool = callbackContextPool{}
	questionCallbackContextPool callbackContextPool = callbackContextPool{}
)

//export go_alpm_go_logcb
func go_alpm_go_logcb(goCb unsafe.Pointer, goCtx *C.go_ctx_t, level C.alpm_loglevel_t, cstring *C.char) {
	cb := *(*logCallbackSig)(goCb)
	ctx := logCallbackContextPool[goCtx]

	msg := C.GoString(cstring)
	lvl := LogLevel(level)

	cb(ctx, lvl, msg)
}

//export go_alpm_go_questioncb
func go_alpm_go_questioncb(goCb unsafe.Pointer, goCtx *C.go_ctx_t, question *C.alpm_question_t) {
	cb := *(*questionCallbackSig)(goCb)
	ctx := questionCallbackContextPool[goCtx]

	q := (*C.alpm_question_any_t)(unsafe.Pointer(question))

	cb(ctx, QuestionAny{q})
}
