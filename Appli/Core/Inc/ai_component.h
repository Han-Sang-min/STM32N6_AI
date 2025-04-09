#ifndef AI_COMPONENT_H
#define AI_COMPONENT_H

#ifdef __cplusplus
extern "C" {
#endif

#include <od_pp_output_if.h>

void Init_AI(void);
void Start_Capture(void);
void Process_AI(void);
od_pp_out_t *GetResult_AI(void);

#ifdef __cplusplus
}
#endif

#endif