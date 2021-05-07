// +build !six
// dynamic_five.go - Dynamic loading symbols from libalpm.so
//
// Copyright (c) 2021 The go-alpm Authors
//
// MIT Licensed. See LICENSE for details.

package alpm

/*
#cgo LDFLAGS: -ldl
#include "dynamic_five.h"
*/
import "C"
