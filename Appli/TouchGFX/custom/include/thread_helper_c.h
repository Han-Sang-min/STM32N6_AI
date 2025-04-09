// ai_thread_c.h

#ifndef THREAD_HELPER_C_H
#define THREAD_HELPER_C_H

#include "tx_api.h"

#ifdef __cplusplus
extern "C" {
#endif

struct AIThread;

void ai_thread_init(void);
TX_EVENT_FLAGS_GROUP* get_ai_events(void);

void camera_thread_init(void);
TX_EVENT_FLAGS_GROUP* get_camera_events(void);

#ifdef __cplusplus
}
#endif

#endif // THREAD_HELPER_C_H
