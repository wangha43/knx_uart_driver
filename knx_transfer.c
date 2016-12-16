#include "knx_transfer.h"
//calculate exp
uint16 cacExp(uint16 base, uint16 exp)
{
    uint16 result = 1;
    while (exp)
    {
        if (exp & 0x01)
            result = result * base;
        base = base * base;
        exp = exp >> 1;
    }
    return result;        
}


//transfer data format 
BOOL DP9_xxx_to_Float(uint16 srcDat, float *pTgtDat)
{
    
    uint16 symbol, exp, base;
    
    symbol = (srcDat >> 15) & 0x0001; //符号
    exp = (srcDat >> 11) & 0x000F; 

    if(symbol == 0)
        base = srcDat & 0x87FF;      
    else
        base = srcDat | 0x7800;
    *pTgtDat = ((float)((SHORT)base)) * cacExp(2, exp) * 0.01;
    
    return true;
}


//float
BOOL Float_to_DP9_xxx(float srcDat, uint16 *pTgtDat)
{
    uint16 symbol, exp, base;
    float abs;
    
    if(srcDat >= 0)
    {
        abs = srcDat;
        symbol = 0;
    }
    else
    {
        abs = srcDat*(-1); 
        symbol = 1;
    }

    if(symbol == 0)
    {
        if(abs <= 20.47)
          exp = 0;
        else if(abs <= 40.94)
          exp = 1;
        else if(abs <= 81.88)
          exp = 2;
        else if(abs <= 163.76)
          exp = 3;
        else if(abs <= 327.52)
          exp = 4;
        else if(abs <= 655.04)
          exp = 5;     
        else if(abs <= 1310.08)
          exp = 6;  
        else if(abs <= 2620.16)
          exp = 7;
        else if(abs <= 5240.32)
          exp = 8;
        else if(abs <= 10480.64)
          exp = 9;
        else if(abs <= 20961.28)
          exp = 10;         
        else
          return false;
    }
    else if(symbol == 1)
    {
        if(abs <= 20.48)
          exp = 0;
        else if(abs <= 40.96)
          exp = 1;
        else if(abs <= 81.92)
          exp = 2;
        else if(abs <= 163.84)
          exp = 3;
        else if(abs <= 327.68)
          exp = 4;
        else if(abs <= 655.36)
          exp = 5;     
        else if(abs <= 1310.72)
          exp = 6;  
        else if(abs <= 2620.44)
          exp = 7;
        else
          return false;        
    }
    else
      return false;
    
    base = (uint16)((abs*100) / cacExp(2, exp));  
    
    if(symbol == 0)
        *pTgtDat = base | ((exp << 11) & 0x7800);
    else if(symbol == 1)
    {
        base = (((~base) + 1) & 0x87FF);
        *pTgtDat = base | ((exp << 11) & 0x7800);
    }
    return true; 
}