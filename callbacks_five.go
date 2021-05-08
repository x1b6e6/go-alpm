// +build !six
// callbacks_five.go - Sets alpm callbacks to Go functions.
//
// Copyright (c) 2021 The go-alpm Authors
//
// MIT Licensed. See LICENSE for details.

package alpm

/*
#cgo CFLAGS: -DSIX=0
#include "callbacks.h"
*/
import "C"

import (
	"unsafe"
)

func (h *Handle) SetLogCallback(cb logCallbackSig, ctx interface{}) {
	goCb := unsafe.Pointer(&cb)
	goCtx := h.ptr

	logCallbackContextPool = callbackContextPool{goCtx: ctx}

	C.go_alpm_set_logcb(h.ptr, goCb, goCtx)
}

func (h *Handle) SetQuestionCallback(cb questionCallbackSig, ctx interface{}) {
	goCb := unsafe.Pointer(&cb)
	goCtx := h.ptr

	questionCallbackContextPool = callbackContextPool{goCtx: ctx}

	C.go_alpm_set_questioncb(h.ptr, goCb, goCtx)
}
