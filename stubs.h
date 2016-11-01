
#define USE_METHOD_STUBS_FOR_COMPILING

#ifdef USE_METHOD_STUBS_FOR_COMPILING
#ifndef STUBS_H
#define STUBS_H

//MOVE FUNCTIONS OUT OF THIS FILE AS I ACTUALLY DEFINE THEM PLEASE

typedef struct Effect_s {
	int x;
} Effect;

void destruct_effect (Effect* effect);
void destruct_effect_void (void* effect);

#endif
#endif