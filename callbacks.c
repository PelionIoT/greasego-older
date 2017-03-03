#include <stdio.h>
#include "grease_lib.h"

#ifdef IF_DBG 
#undef IF_DBG
#endif
#ifdef DBG_OUT 
#undef DBG_OUT
#endif

#define ERROR_OUT(s,...) fprintf(stderr, "**ERROR_CGO** (callbacks.c)" s, ##__VA_ARGS__ )//#define ERROR_PERROR(s,...) fprintf(stderr, "*****ERROR***** " s, ##__VA_ARGS__ );

#ifdef DEBUG_BINDINGS
#define DBG_OUT(s,...) fprintf(stderr, "**DEBUG_CGO (callbacks.c)** " s "\n", ##__VA_ARGS__ )
#define IF_DBG( x ) { x }
#else
#define DBG_OUT(s,...) {}
#define IF_DBG( x ) {}
#endif

// The gateway function
int greasego_startGreaseLibCB(int in)
{
    DBG_OUT("gateway func: greasego_startGreaseLibCB()\n");
    return do_startGreaseLib_cb();
}

void greasego_commonTargetCB(GreaseLibError *err, void *d, uint32_t targetId) {
	DBG_OUT("@greasego_commonTargetCB (err:%x) %d",err,targetId);
	return do_commonTargetCB(err, (GreaseLibBuf *)d, targetId);
}


// this is a GreaseLibCallback for addTarget
int greasego_addTargetCB(GreaseLibError *err, void *d) {
	if(d) {
		GreaseLibStartedTargetInfo *info = 	(GreaseLibStartedTargetInfo *) d;
		DBG_OUT("HERE - in addTargetCB %d\n",info->optsId);		
		return do_addTargetCB(err,info);
	}

}

int greasego_wrapper_addTarget(GreaseLibTargetOpts *opts) {
	DBG_OUT("HERE - in grease_go_wrapper_addTarget\n");
	GreaseLib_addTarget( greasego_addTargetCB, opts );
}


