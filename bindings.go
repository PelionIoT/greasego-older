package greasego


// see notes here on libtcmalloc issues: https://github.com/gperftools/gperftools/issues/39

/*
#cgo LDFLAGS: -L/usr/lib/x86_64-linux-gnu -L${SRCDIR}/deps/lib
#cgo LDFLAGS: -lgrease -luv -lTW -lre2 -lstdc++ -lm -ltcmalloc_minimal 
#cgo CFLAGS: -I${SRCDIR}/deps/include
#define GREASE_IS_LOCAL 1
#include <stdio.h>
#include "grease_lib.h"
#include "bindings.h"

*/
import "C"
import "unsafe"

//-static-libgcc 
// # cgo LDFLAGS: /usr/lib/x86_64-linux-gnu/libunwind-coredump.so.0 

// I can't get this to work right now. I think when the fix for cgo command is put in it will:
// https://github.com/golang/go/issues/16651
/*
# cgo LDFLAGS: -L/usr/lib/gcc/x86_64-linux-gnu/4.8
# cgo LDFLAGS: -L/usr/lib/x86_64-linux-gnu -Wl,-Bdynamic /usr/lib/x86_64-linux-gnu/libunwind-coredump.so.0 -Wl,-Bstatic 
# cgo LDFLAGS: -Wl,-whole-archive ${SRCDIR}/deps/lib/libtcmalloc_minimal.a -Wl,-no-whole-archive 
# cgo LDFLAGS: /usr/lib/gcc/x86_64-linux-gnu/4.8.4/libstdc++.a ${SRCDIR}/deps/lib/libgrease.a ${SRCDIR}/deps/lib/libuv.a ${SRCDIR}/deps/lib/libTW.a ${SRCDIR}/deps/lib/libre2.a  -lstdc++ /usr/lib/x86_64-linux-gnu/libm.a
# cgo CFLAGS: -I${SRCDIR}/deps/include
# define GREASE_IS_LOCAL 1
# include "grease_lib.h"
*/


type GreaseLibStartCB interface {
	GreaseLib_start_cb()
}

type GreaseLib struct {
	_greaseLibStartCB GreaseLibStartCB
}


//export do_startGreaseLib_cb
func do_startGreaseLib_cb() {
	_instance := getGreaseLib()	
	if(_instance._greaseLibStartCB != nil) {
		_instance._greaseLibStartCB.GreaseLib_start_cb();
	}	
}


var greaseInstance *GreaseLib = nil

func getGreaseLib() *GreaseLib {
	if(greaseInstance == nil) {
		greaseInstance = new(GreaseLib);
	}
	return greaseInstance;
}


func StartGreaseLib(cb GreaseLibStartCB) {
	_instance := getGreaseLib()
	_instance._greaseLibStartCB = cb	
	C.GreaseLib_start((C.GreaseLibCallback)(unsafe.Pointer(C.greasego_startGreaseLibCB)));
}