#include "main.h"

//stub, not needed for prediction program
void MBMasuBomheiSet(s32 arg0) { 

}


static inline s32 GetUnkSystem(void) {
    return GwSystem.unk;
}

void MBCapsuleOpeningAdd(s32 amountOfCapsules) {
    s32 temp_r19;
    s32 temp_r20;
    s32 temp_r24;
    s32 temp_r23;
    s32 temp_r23_2;
    s32 temp_r24_2;
    s32 temp;
    s32* temp_r3;
    s32* temp_r3_2;
    s32* temp_r3_3;
    s32 var_r22;
    s32 var_r26;
    s32 var_r25;
    s32 var_r27;
    s32 var_r31;
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
        if ((GetUnkSystem() == 0) && (temp_r3_2[i] == 0xD)) {
            temp_r3_2[i] = -1;
        }
        if ((GetUnkSystem() == 1) && (temp_r3_2[i] == 0x11)) {
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

void main(void){
    
}