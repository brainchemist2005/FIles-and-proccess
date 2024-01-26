#ifndef TP1_SERIALIZE_H_
#define TP1_SERIALIZE_H_

#include "simulation.h"

#ifdef __cplusplus
extern "C" {
#endif

int save_state(struct state* s, const char* filename);
int load_state(struct state* s, const char* filename);

#ifdef __cplusplus
}
#endif

#endif
