#ifndef Callbacks_H_
#define Callbacks_H_

#include "grease_lib.h"

int greasego_startGreaseLibCB(int in);
int greasego_addTargetCB(GreaseLibError *err, void *d);
int greasego_wrapper_addTarget(GreaseLibTargetOpts *opts);
int greasego_wrapper_modifyDefaultTarget(GreaseLibTargetOpts *opts);
void greasego_commonTargetCB(GreaseLibError *err, void *d, uint32_t targetId);

#endif
