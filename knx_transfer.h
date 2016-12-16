#ifndef KNX_TRANSFER
#define KNX_TRANSFER
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
typedef uint16_t uint16; 
typedef bool BOOL;
typedef short SHORT;

uint16 cacExp(uint16 base, uint16 exp);
BOOL DP9_xxx_to_Float(uint16 srcDat, float *pTgtDat);
BOOL Float_to_DP9_xxx(float srcDat, uint16 *pTgtDat);

#endif