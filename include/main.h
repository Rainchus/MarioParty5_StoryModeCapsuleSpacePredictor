#ifndef _MAIN_H_
#define _MAIN_H_

#include <string.h>

typedef signed char s8;
typedef signed short int s16;
typedef signed long s32;
typedef signed long long int s64;
typedef unsigned char u8;
typedef unsigned short int u16;
typedef unsigned long u32;
typedef unsigned long long int u64;
typedef float f32;

void MBMasuBomheiSet(s32 arg);
void MBMasuCapsuleNoSet(s32 arg1, s32 arg2, s32 arg3);

void HuMemDirectFree(void*);                             /* extern */
void* HuMemDirectMallocNum(s32, s32, s32);                  /* extern */
s32 MBCapsuleCodeGet(s32);                          /* extern */
void MBCapsuleMasuSet(s32, s32);                       /* extern */
s32 MBCapsuleNoListGet(s32*);                        /* extern */
s32 MBMasuCapsuleNoGet(s32, s32);                     /* extern */
s32 MBMasuNumGet(s32);                                /* extern */
s32 MBMasuTypeGet(s32, s32);                          /* extern */
u32 frand(void);                                        /* extern */
//void memset(void*, s32, s32);                                /* extern */
typedef struct system_state {
/* 0x00 */ struct {
        u8 unk : 1;
    };
} SystemState;
    
SystemState GwSystem;

#endif