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
void HuMemDirectFree(void*);
void* HuMemDirectMallocNum(s32, s32, s32);
s32 MBCapsuleCodeGet(s32);
void MBCapsuleMasuSet(s32, s32);
s32 MBCapsuleNoListGet(s32*);
s32 MBMasuCapsuleNoGet(s32, s32);
s32 MBMasuNumGet(s32);
s32 MBMasuTypeGet(s32, s32);
u32 frand(void);
//void memset(void*, s32, s32);
typedef struct system_state {
/* 0x00 */ struct {
        u8 party : 1;
        u8 team : 1;
    };
/* 0x01 */ u8 diff_story;
/* 0x02 */ struct {
        u16 bonus_star : 1;
        u16 explain_mg : 1;
        u16 show_com_mg : 1;
        u16 mg_list : 2;
        u16 mess_speed : 2;
        u16 save_mode : 2;
    };
/* 0x04 */ u8 turn;
/* 0x05 */ u8 max_turn;
/* 0x06 */ u8 star_flag;
/* 0x07 */ u8 star_total;
/* 0x08 */ struct {
    u8 star_pos : 3;
    u8 board : 5;
};
/* 0x09 */ s8 last5_effect;
/* 0x0A */ s8 player_curr;
/* 0x0B */ s8 unk0B[3];
/* 0x0E */ s16 block_pos;
/* 0x10 */ u8 board_data[32];
/* 0x30 */ u8 mess_delay;
/* 0x31 */ struct {
        u8 bowser_loss : 4;
        u8 bowser_event : 4;
    };
/* 0x32 */ s8 lucky_value;
/* 0x34 */ u16 mg_next;
/* 0x36 */ s16 mg_type;
/* 0x38 */ u16 bank_coins;
/* 0x3A */ s16 flag[16]; //unk size
/* 0x5A */ u8 unk_6A[0x72];
} SystemState; //8018fcf8, sizeof 0xDC

#endif