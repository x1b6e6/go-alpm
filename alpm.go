// alpm.go - Implements exported libalpm functions.
//
// Copyright (c) 2013 The go-alpm Authors
//
// MIT Licensed. See LICENSE for details.

package alpm

// #cgo LDFLAGS: -lalpm
// #include <alpm.h>
import "C"

import "unsafe"

// Initialize creates a new alpm handle
func Initialize(root, dbpath string) (*Handle, error) {
	cRoot := C.CString(root)
	cDBPath := C.CString(dbpath)
	var cErr C.alpm_errno_t
	h := C.alpm_initialize(cRoot, cDBPath, &cErr)

	defer C.free(unsafe.Pointer(cRoot))
	defer C.free(unsafe.Pointer(cDBPath))

	if cErr != 0 {
		return nil, Error(cErr)
	}

	return &Handle{h}, nil
}

// Reopen reopens the alpm handle at the same root and dbpath
func (h *Handle) Reopen() error {
	var cErr C.alpm_errno_t

	root, err := h.Root()
	if err != nil {
		return err
	}

	dbpath, err := h.DBPath()
	if err != nil {
		return err
	}

	cRoot := C.CString(root)
	cDBPath := C.CString(dbpath)

	defer C.free(unsafe.Pointer(cRoot))
	defer C.free(unsafe.Pointer(cDBPath))
	newHandle := C.alpm_initialize(cRoot, cDBPath, &cErr)
	if cErr != 0 {
		return Error(cErr)
	}

	if er := C.alpm_release(h.ptr); er != 0 {
		return Error(er)
	}

	h.ptr = newHandle

	return nil
}

// Release releases the alpm handle
func (h *Handle) Release() error {
	if er := C.alpm_release(h.ptr); er != 0 {
		return Error(er)
	}
	h.ptr = nil
	return nil
}

// LastError gets the last pm_error
func (h *Handle) LastError() error {
	if h.ptr != nil {
		cErr := C.alpm_errno(h.ptr)
		if cErr != 0 {
			return Error(cErr)
		}
	}
	return nil
}

// Version returns libalpm version string.
func Version() string {
	return C.GoString(C.alpm_version())
}
