package alpm

/*
#include <alpm.h>
*/
import "C"
import (
	"fmt"
	"unsafe"
)

// FindSatisfier searches a DbList for a package that satisfies depstring
// Example "glibc>=2.12"
func (l DbList) FindSatisfier(depstring string) (*Package, error) {
	cDepString := C.CString(depstring)
	defer C.free(unsafe.Pointer(cDepString))
	ptr := C.alpm_find_dbs_satisfier(unsafe.Pointer(l.handle.ptr), unsafe.Pointer(l.list), cDepString)
	if ptr == nil {
		return nil,
			fmt.Errorf("Unable to satisfy dependency %s in Dblist\n", depstring)
	}

	return &Package{ptr, l.handle}, nil
}

// FindSatisfier finds a package that satisfies depstring from PkgList
func (l PackageList) FindSatisfier(depstring string) (*Package, error) {
	cDepString := C.CString(depstring)
	defer C.free(unsafe.Pointer(cDepString))
	ptr := C.alpm_find_satisfier(unsafe.Pointer(l.list), cDepString)
	if ptr == nil {
		return nil,
			fmt.Errorf("Unable to find dependency %s in PackageList\n", depstring)
	}

	return &Package{ptr, l.handle}, nil
}
