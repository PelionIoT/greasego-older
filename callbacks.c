#include <stdio.h>
#include "grease_lib.h"

// The gateway function
int greasego_startGreaseLibCB(int in)
{
    printf("gateway func: greasego_startGreaseLibCB()\n");
    return do_startGreaseLib_cb();
}



// this is a GreaseLibCallback for addTarget
int greasego_addTargetCB(GreaseLibError *err, void *d) {
	if(d) {
		printf("HERE - in addTargetCB\n");
		GreaseLibStartedTargetInfo *info = 	(GreaseLibStartedTargetInfo *) d;
		return do_addTargetCB(err,info);
	}

}

int greasego_wrapper_addTarget(GreaseLibTargetOpts *opts) {
	printf("HERE - in grease_go_wrapper_addTarget\n");
	GreaseLib_addTarget( greasego_addTargetCB, opts );
}


