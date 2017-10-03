#ifndef Callbacks_H_
#define Callbacks_H_

#include "grease_lib.h"

void greasego_startGreaseLibCB(int in);
void greasego_addTargetCB(GreaseLibError *err, void *d);
int greasego_wrapper_addTarget(GreaseLibTargetOpts *opts);
int greasego_wrapper_modifyDefaultTarget(GreaseLibTargetOpts *opts);
void greasego_commonTargetCB(GreaseLibError *err, void *d, uint32_t targetId);
void greasego_setSelfOriginLabel(char *s) ;

void greasego_childClosedFDCallback (GreaseLibError *err, int stream_type, int fd);
void zero_meta( logMeta *m );


extern logMeta go_meta_info;
extern logMeta go_meta_warning;
extern logMeta go_meta_error;
extern logMeta go_meta_debug;
extern logMeta go_meta_success;

extern logMeta go_self_meta_info;
extern logMeta go_self_meta_warning;
extern logMeta go_self_meta_error;
extern logMeta go_self_meta_debug;
extern logMeta go_self_meta_success;

#endif
