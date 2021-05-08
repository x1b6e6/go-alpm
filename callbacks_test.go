// callbacks_test.go - Test sets alpm callbacks to Go functions.
//
// Copyright (c) 2013 The go-alpm Authors
//
// MIT Licensed. See LICENSE for details.

package alpm

import (
	"errors"
	"testing"
)

type Cnt struct {
	cnt int
}

func TestCallbacks(t *testing.T) {
	h, _ := Initialize("/", "/var/lib/pacman")
	cnt := &Cnt{cnt: 0}

	h.SetLogCallback(func(ctx interface{}, lvl LogLevel, msg string) {
		cnt := ctx.(*Cnt)
		cnt.cnt++
	}, cnt)

	h.Release()

	if cnt.cnt != 1 {
		panic(errors.New("cnt.cnt != 1"))
	}
}
