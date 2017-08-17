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
void greasego_startGreaseLibCB(int in)
{
    DBG_OUT("gateway func: greasego_startGreaseLibCB()\n");
    do_startGreaseLib_cb();
}

void greasego_commonTargetCB(GreaseLibError *err, void *d, uint32_t targetId) {
	DBG_OUT("@greasego_commonTargetCB (err:%p) %d",err,targetId);
	do_commonTargetCB(err, (GreaseLibBuf *)d, targetId);
}


// this is a GreaseLibCallback for addTarget
void greasego_addTargetCB(GreaseLibError *err, void *d) {
	if(d) {
		GreaseLibStartedTargetInfo *info = 	(GreaseLibStartedTargetInfo *) d;
		DBG_OUT("HERE - in addTargetCB %d\n",info->optsId);		
		do_addTargetCB(err,info);
	}

}

int greasego_wrapper_addTarget(GreaseLibTargetOpts *opts) {
	DBG_OUT("HERE - in grease_go_wrapper_addTarget\n");
	GreaseLib_addTarget( (GreaseLibCallback) greasego_addTargetCB, opts );
	return 0;
}

void greasego_childClosedFDCallback (GreaseLibError *err, int stream_type, int fd) {
	do_childClosedFDCallback(err, stream_type, fd);
}

void zero_meta( logMeta *m ) {
	memset(m,0,sizeof(logMeta));
}


logMeta go_meta_info = {
		.tag = GREASE_TAG_INTERNAL,
		.level = GREASE_LEVEL_INFO,
		.origin = 0,
		.target = 0,
		.extras = 0,
		__DEFAULT_LOG_META_PRIVATE };

logMeta go_meta_warning = {
		.tag = GREASE_TAG_INTERNAL,
		.level = GREASE_LEVEL_WARN,
		.origin = 0,
		.target = 0,
		.extras = 0,
		__DEFAULT_LOG_META_PRIVATE };

logMeta go_meta_error = {
		.tag = GREASE_TAG_INTERNAL,
		.level = GREASE_LEVEL_ERROR,
		.origin = 0,
		.target = 0,
		.extras = 0,
		__DEFAULT_LOG_META_PRIVATE };

logMeta go_meta_debug = {
		.tag = GREASE_TAG_INTERNAL,
		.level = GREASE_LEVEL_DEBUG,
		.origin = 0,
		.target = 0,
		.extras = 0,
		__DEFAULT_LOG_META_PRIVATE };

logMeta go_meta_success = {
		.tag = GREASE_TAG_INTERNAL,
		.level = GREASE_LEVEL_SUCCESS,
		.origin = 0,
		.target = 0,
		.extras = 0,
		__DEFAULT_LOG_META_PRIVATE };
