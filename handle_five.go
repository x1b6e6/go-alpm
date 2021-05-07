// +build !six
// handle_five.go - libalpm handle type and methods.
//
// Copyright (c) 2021 The go-alpm Authors
//
// MIT Licensed. See LICENSE for details

package alpm

/*
#include "handle_five.h"
*/
import "C"

func (h *Handle) GetArchitectures() (StringList, error) {
	return h.optionGetList(func(handle *C.alpm_handle_t) *C.alpm_list_t {
		return C.go_alpm_option_get_architectures(handle)
	})
}

func (h *Handle) SetArchitectures(str []string) error {
	return h.optionSetList(str, func(handle *C.alpm_handle_t, l *C.alpm_list_t) C.int {
		return C.go_alpm_option_set_architectures(handle, l)
	})
}

func (h *Handle) AddArchitecture(str string) error {
	return h.optionAddList(str, func(handle *C.alpm_handle_t, cStr *C.char) C.int {
		return C.go_alpm_option_add_architecture(handle, cStr)
	})
}

func (h *Handle) RemoveArchitecture(str string) (bool, error) {
	return h.optionRemoveList(str, func(handle *C.alpm_handle_t, cStr *C.char) C.int {
		return C.go_alpm_option_remove_architecture(handle, cStr)
	})
}
