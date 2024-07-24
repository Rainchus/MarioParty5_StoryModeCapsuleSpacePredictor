#include <stdlib.h>
#include "main.h"

#define HuMemDirectMallocNumWrapper HuMemDirectMallocNum
#define HuMemDirectFreeWrapper HuMemDirectFree

u32 frand(void);
f32 frandf(void);
u32 frandmod(u32 arg0);
void MBMasuNoSaiHiddenCalc(void);

typedef struct UnkMasuData {
    char unk_00[0x2C];
    u16 unk_2C;
    s16 unk_2E;
    char unk_30[0x40];
} UnkMasuData; //sizeof 0x70

typedef struct CapsuleTbl {
    s32 unk_00;
    char unk_04[0x14];
    s8 unk_18;
    s8 unk_19;
    char unk_1A[2];
} CapsuleTbl;

UnkMasuData masuData[1][256];
s16 masuNo[1];
//
SystemState GwSystem; //initialize this later
CapsuleTbl capsuleTbl[0x27]; //initialize this later

s32 MBCapsuleCodeGet(s32 arg0) {
    arg0 &= 0xFF;
    return capsuleTbl[arg0].unk_18;
}

static inline s32 GetGwSystemParty(void) {
    return GwSystem.party;
}

static inline s32 GetGwSystemTeam(void) {
    return GwSystem.team;
}

static inline s32 GetCapsuleTableUnk00(u8 i) {
    CapsuleTbl* capsule = &capsuleTbl[i];
    return capsule->unk_00;
}

static inline s32 GetMasuNo(void) {
    return masuNo[0]; //masuNo[1]; matches codegen but wrong offset?
}

u16 MBBankCoinGet(void) {
    return GwSystem.bank_coins;
}

s32 MBMasuCapsuleNoGet(s32 arg0, s32 arg1) {
    if ((arg1 <= 0) || (arg1 > masuNo[arg0])) {
        return -1;
    }
    return masuData[arg0][arg1-1].unk_2E;
}

s32 MBCapsuleNoListGet(s32* arg0) {
    s32 var_r29;
    s32 var_r28;
    s32 var_r30;
    s32 i;

    for (i = 1, var_r29 = 0; i <= MBMasuNumGet(0); i++) {
        if (MBMasuTypeGet(0, i) == 2) {
            var_r29++;
        }        
    }
    
    for (i = 1, var_r28 = 0; i <= MBMasuNumGet(0); i++) {
        if (MBMasuCapsuleNoGet(0, i) == 0x11) {
            var_r28++;
        }    
    }
    
    for (i = 0, var_r30 = 0; i < 0x27; i++) {
        if (((GetGwSystemParty() != 0) || (capsuleTbl[i].unk_19 == 0)) && (!(GetGwSystemTeam()) || (i != 0x24)) && ((var_r29 > 0) || (i != 0x22)) && ((MBBankCoinGet() <= 0) || (var_r28 < 1) || (i != 0x11)) && (( (GwSystem.max_turn - GwSystem.turn) >= 5) || (i != 0x1F)) && (GetCapsuleTableUnk00(i) != 0U) && (i <= 0x24)) {
            arg0[var_r30] = i;
            var_r30++;
        }        
    }

    return var_r30;
}

void MBMasuNoSaiHiddenCalc(void) {
    s32 temp_r26;
    s32 temp_r31;
    s32 var_r28;
    s32 i;
    s32* temp_r30;
    UnkMasuData* var_r25;

    //if (_CheckFlag(0x1000E) == 0) { //probably not a required check
        if ((GetGwSystemParty() == 0) || (GetGwSystemTeam() == 0)) {
            GwSystem.block_pos = -1;
            return;
        }
        temp_r26 = GetMasuNo();
        temp_r30 = HuMemDirectMallocNum(0, temp_r26 * 4, 0x10000000);

        for (var_r28 = 0, i = 0; i < temp_r26; i++) {
            temp_r31 = i + 1;
            if ((temp_r31 <= 0) || (temp_r31 > masuNo[0])) {
                var_r25 = NULL;
            } else {
                var_r25 = &masuData[0][temp_r31 - 1];
            }
            if ((temp_r31 != GwSystem.block_pos) && (var_r25->unk_2C == 1) && (var_r25->unk_2E < 0)) {
                temp_r30[var_r28++] = temp_r31;
            }            
        }
        
        if (var_r28 == 0) {
            GwSystem.block_pos = -1;
        } else {
            GwSystem.block_pos = temp_r30[frandmod(var_r28)];
        }
        HuMemDirectFree(temp_r30);
    //}
}

void MBMasuCapsuleNoSet(s32 arg0, s32 arg1, s32 arg2) {
    if ((arg1 <= 0) || (arg1 > masuNo[arg0]) ) {
        return;
    }
    if (arg1 == GwSystem.block_pos) {
        MBMasuNoSaiHiddenCalc();
    }
    GwSystem.flag[arg1-1] = arg2;
    masuData[arg0][arg1-1].unk_2E = arg2;
}

s32 MBMasuTypeGet(s32 arg0, s32 arg1) {
    if ((arg1 <= 0) || (arg1 > masuNo[arg0]) ) {
        return 0;
    }
    return masuData[arg0][arg1-1].unk_2C;
}

void* HuMemDirectMallocNumWrapper(s32 arg0, s32 size, s32 arg2) {
    return malloc(size);
}

void HuMemDirectFreeWrapper(void* arg0) {
    free(arg0);
}

//stub, not needed for prediction program
void MBMasuBomheiSet(s32 arg0) { 

}

s32 MBMasuNumGet(s32 arg0) {
    return masuNo[arg0];
}

void MBCapsuleMasuSet(s32 arg0, s32 arg1) {
    arg1 &= 0xFF;
    if (arg1 > 0x24) {
        return;
    }
    switch (arg1) {
        case 0x21:
            return;
        case 0x22:
            return;
        case 0x24:
            return;
        default:
            MBMasuCapsuleNoSet(0, arg0, arg1);
            switch (arg1) {
                case 0x10:
                    MBMasuBomheiSet(arg0);
            }
    }
}

void MBCapsuleOpeningAdd(s32 amountOfCapsules) {
    s32 temp_r19;
    s32 temp_r20;
    s32 temp_r24;
    s32 temp_r23;
    s32 temp;
    s32* temp_r3;
    s32* temp_r3_2;
    s32* temp_r3_3;
    s32 var_r26;
    s32 var_r25;
    s32 var_r27;
    s32 i, j;

    temp_r3 = HuMemDirectMallocNum(0, 0x400, 0x10000000);
    memset(temp_r3, 0, 0x400);
    for (i = 1, var_r27 = 0; i <= MBMasuNumGet(0); i++) {
        if ((MBMasuTypeGet(0, i) == 1) || (MBMasuTypeGet(0, i) == 2)) {
            temp_r3[var_r27] = i;
            var_r27++;
        }        
    }

    for (i = 0; i < (var_r27 * 5); i++) {
        temp_r24 = i % var_r27;
        temp_r23 = (frand() & 0x7FFF) % var_r27;
        temp = temp_r3[temp_r24];
        temp_r3[temp_r24] = temp_r3[temp_r23];
        temp_r3[temp_r23] = temp;
    }

    temp_r3_2 = HuMemDirectMallocNum(0, 0x9C, 0x10000000);
    memset(temp_r3_2, 0, 0x9C);
    temp_r20 = MBCapsuleNoListGet(temp_r3_2);
    for (i = 0; i < temp_r20; i++) {
        if ((GetGwSystemParty() == 0) && (temp_r3_2[i] == 0xD)) {
            temp_r3_2[i] = -1;
        }
        if ((GetGwSystemParty() == 1) && (temp_r3_2[i] == 0x11)) {
            temp_r3_2[i] = -1;
        }
        if ((temp_r3_2[i] == 0x10) || (temp_r3_2[i] == 0x21) || (temp_r3_2[i] == 0x22) || (temp_r3_2[i] == 0x24) || (MBCapsuleCodeGet(temp_r3_2[i]) == 0x43) || (MBCapsuleCodeGet(temp_r3_2[i]) == 0x45)) {
            temp_r3_2[i] = -1;
        }        
    }
    
    temp_r3_3 = HuMemDirectMallocNum(0, 0x9C, 0x10000000);
    memset(temp_r3_3, 0, 0x9C);
    for (i = 0, var_r26 = 0; i < temp_r20; i++) {
        if (temp_r3_2[i] != -1) {
            temp_r3_3[var_r26] = temp_r3_2[i];
            var_r26 += 1;
        }        
    }

    for (i = 0; i < (var_r26 * 5); i++) {
        temp_r24 = i % var_r26;
        temp_r23 = (frand() & 0x7FFF) % var_r26;
        temp = temp_r3_3[temp_r24];
        temp_r3_3[temp_r24] = temp_r3_3[temp_r23];
        temp_r3_3[temp_r23] = temp;       
    }

    for (j = 0; j < amountOfCapsules; j++) {
        temp_r19 = (frand() & 0x7FFF) % var_r27;
        for (i = 0; i < var_r27; i++) {
            var_r25 = temp_r19 + i;
            if (var_r25 >= var_r27) {
                var_r25 = var_r25 % var_r27;
            }
            if (MBMasuCapsuleNoGet(0, temp_r3[var_r25]) == -1) {
                var_r25 = temp_r3[var_r25];
                break;
            } else {
                continue;
            }            
        }
        if (i < var_r27) {
            MBCapsuleMasuSet(var_r25, temp_r3_3[j % var_r26]);
        }
    }

    HuMemDirectFree(temp_r3);
    HuMemDirectFree(temp_r3_2);
    HuMemDirectFree(temp_r3_3);
}

int main(void){
    MBCapsuleOpeningAdd(6); //always places 6 capsules
}