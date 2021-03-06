#include "InstructionTable.h"
#include <stdio.h>
#include <stdint.h>
#include "ADDW.h"
#include "ADD.h"
#include "ADC.h"
#include "NEG.h"
#include "NEGW.h"
#include "SUBW.h"
#include "SBC.h"
#include "CPL.h"
#include "CPLW.h"
#include "INC.h"
#include "INCW.h"
#include "DEC.h"
#include "DECW.h"
#include "NOP.h"
#include "CLR.h"
#include "CLRW.h"
#include "EXG.h"
#include "EXGW.h"
#include "MOV.h"
#include "RVF.h"
#include "CCF.h"
#include "RCF.h"
#include "SCF.h"
#include "SIM.h"
#include "RIM.h"
#include "TNZ.h"
#include "TNZW.h"
#include "BCP.h"
#include "TRAP.h"
#include "JP.h"
#include "JRA.h"
#include "JPF.h"
#include "JRXX.h"
#include "WFI.h"
#include "WFE.h"
#include "HALT.h"
#include "BREAK.h"
#include "IRET.h"
#include "BSET.h"
#include "BRES.h"
#include "BCPL.h"
#include "BCCM.h"
#include "BTJF.h"
#include "BTJT.h"
#include "ErrorObject.h"


Instruction firstOpcode[256] = {
  [0X80] = iret ,
  [0X8B] = instr_break ,
  
  [0X8E] = halt ,
  
  [0X8F] = wfi  ,
  
  [0x20] = jra_shortoff,
  [0xCC] = jp_longmem   ,
  [0xFC] = jp_x         ,
  [0xEC] = jp_shortoff_x,
  [0xDC] = jp_longoff_x ,
  
  [0X25] = jrc  ,
  [0X27] = jreq ,
  [0X21] = jrf  ,
  [0X2B] = jrmi ,
  [0X24] = jrnc ,
  [0X26] = jrne ,
  [0X28] = jrnv ,
  [0X2A] = jrpl ,
  [0X2E] = jrsge,
  [0X2C] = jrsgt,
  [0X2D] = jrsle,
  [0X2F] = jrslt,
  [0X2D] = jrt  ,
  [0X24] = jruge,
  [0X23] = jrugt,
  [0X29] = jrv  ,
  
  [0XAC] = jpf_extmem,
 
  [0x83] = trap,
  
  [0XA5] = bcp_a_byte        ,
  [0XB5] = bcp_a_shortmem    ,
  [0XC5] = bcp_a_longmem     ,
  [0XF5] = bcp_a_x           ,
  [0XE5] = bcp_a_shortoff_x  ,
  [0XD5] = bcp_a_longoff_x   ,
  [0X15] = bcp_a_shortoff_sp ,
  
  [0X4D] = tnz_a           ,
  [0X3D] = tnz_shortmem    ,
  [0X7D] = tnz_x           ,
  [0X6D] = tnz_shortoff_x  ,
  [0X0D] = tnz_shortoff_sp ,
  
  [0X5D] = tnzw_x,
  
  [0X8C] = ccf,
  [0X98] = rcf,
  [0X99] = scf,
  [0X9A] = rim,
  [0X9B] = sim,
  [0X9C] = rvf,
  [0X35] = mov_longmem_byte     ,
  [0X45] = mov_shortmem_shortmem,
  [0X55] = mov_longmem_longmem  ,
  [0X41] = exg_a_xl     ,
  [0X61] = exg_a_yl     ,
  [0X31] = exg_a_longmem,
  [0X51] = exgw_x_y     ,
  
  [0X4F] = clr_a           ,
  [0X3F] = clr_shortmem    ,
  [0X7F] = clr_x           ,
  [0X6F] = clr_shortoff_x  ,
  [0X0F] = clr_shortoff_sp ,
  
  [0X5F] = clrw_x,
  [0X9D] = nop,
  
  [0X4A] = dec_a           ,
  [0X3A] = dec_shortmem    ,
  [0X7A] = dec_x           ,
  [0X6A] = dec_shortoff_x  ,
  [0X0A] = dec_shortoff_sp ,
  
  [0X5A] = decw_x           ,
  
  [0X4C] = inc_a           ,
  [0X3C] = inc_shortmem    ,
  [0X7C] = inc_x           ,
  [0X6C] = inc_shortoff_x  ,
  [0X0C] = inc_shortoff_sp ,
  
  [0X5C] = incw_x          ,
  
  [0x43] = cpl_a           ,
  [0x33] = cpl_shortmem    ,
  [0x73] = cpl_x           ,
  [0x63] = cpl_shortoff_x  ,
  [0x03] = cpl_shortoff_sp ,
  
  [0x53] = cplw_x,
  
  [0X00] = neg_shortoff_sp,
  [0X40] = neg_a          ,
  
  [0X50] = negw_x         ,
  [0X30] = neg_shortmem   ,
  [0X70] = neg_x          ,
  [0X60] = neg_shortoff_x ,
  
  [0X10] = subw_x_word,   
  
  [0XA2] = sbc_a_byte        ,
  [0XB2] = sbc_a_shortmem    ,
  [0XC2] = sbc_a_longmem     ,
  [0XF2] = sbc_a_x           ,
  [0XE2] = sbc_a_shortoff_x  ,
  [0XD2] = sbc_a_longoff_x   ,
  [0X12] = sbc_a_shortoff_sp ,
  
  // ADD
  [0xAB] = add_a_byte,
  [0xBB] = add_a_shortmem,
  [0xCB] = add_a_longmem,
  [0xFB] = add_a_x,
  [0xEB] = add_a_shortoff_x,
  [0xDB] = add_a_longoff_x,
  [0x1B] = add_a_shortoff_sp,
  
  // ADDW
  [0x1c] = addw_x_word,
  [0x5b] = addw_sp_byte,
};


Instruction opcode72[256] = {
  [0x8F] = wfe,
  
  [0xCC] = jp_longptr_w    ,
  [0xDC] = jp_longptr_w_x  ,
  
  [0x00] = btjt_longmem_pos_0,
  [0x02] = btjt_longmem_pos_1,
  [0x04] = btjt_longmem_pos_2,
  [0x06] = btjt_longmem_pos_3,
  [0x08] = btjt_longmem_pos_4,
  [0x0A] = btjt_longmem_pos_5,
  [0x0C] = btjt_longmem_pos_6,
  [0x0E] = btjt_longmem_pos_7,
 
  [0x01] = btjf_longmem_pos_0,
  [0x03] = btjf_longmem_pos_1,
  [0x05] = btjf_longmem_pos_2,
  [0x07] = btjf_longmem_pos_3,
  [0x09] = btjf_longmem_pos_4,
  [0x0B] = btjf_longmem_pos_5,
  [0x0D] = btjf_longmem_pos_6,
  [0x0F] = btjf_longmem_pos_7,
  
  [0X10] = bset_longmem_pos_0,
  [0X12] = bset_longmem_pos_1,
  [0X14] = bset_longmem_pos_2,
  [0X16] = bset_longmem_pos_3,
  [0X18] = bset_longmem_pos_4,
  [0X1A] = bset_longmem_pos_5,
  [0X1C] = bset_longmem_pos_6,
  [0X1E] = bset_longmem_pos_7,
  
  [0X11] = bres_longmem_pos_0,
  [0X13] = bres_longmem_pos_1,
  [0X15] = bres_longmem_pos_2,
  [0X17] = bres_longmem_pos_3,
  [0X19] = bres_longmem_pos_4,
  [0X1B] = bres_longmem_pos_5,
  [0X1D] = bres_longmem_pos_6,
  [0X1F] = bres_longmem_pos_7,

  
  [0XC5] = bcp_a_longptr_w   ,
  [0XD5] = bcp_a_longptr_w_x ,

  
  [0X5D] = tnz_longmem     ,
  [0X4D] = tnz_longoff_x   ,
  [0X3D] = tnz_longptr_w   ,
  [0X6D] = tnz_longptr_w_x ,
  
  [0X5F] = clr_longmem     ,
  [0X4F] = clr_longoff_x   ,
  [0X3F] = clr_longptr_w   ,
  [0X6F] = clr_longptr_w_x ,
  
  [0X5A] = dec_longmem     ,
  [0X4A] = dec_longoff_x   ,
  [0X3A] = dec_longptr_w   ,
  [0X6A] = dec_longptr_w_x ,

  
  [0X5C] = inc_longmem     ,
  [0X4C] = inc_longoff_x   ,
  [0X3C] = inc_longptr_w   ,
  [0X6C] = inc_longptr_w_x ,
  
  [0x53] = cpl_longmem     ,
  [0x43] = cpl_longoff_x   ,
  [0x33] = cpl_longptr_w   ,
  [0x63] = cpl_longptr_w_x ,
  
  [0X50] = neg_longmem    ,
  [0X40] = neg_longoff_x  ,
  
  [0XB0] = subw_x_longmem,    
  [0XA0] = subw_x_shortoff_sp,
  [0XA2] = subw_y_word,      
  [0XB2] = subw_y_longmem,    
  [0XF2] = subw_y_shortoff_sp,
  
  [0XC2] = sbc_a_longptr_w   ,
  [0XD2] = sbc_a_longptr_w_x ,
  
  // ADD
  [0xCB] = add_a_longptr_w,
  [0xDB] = add_a_longptr_w_x,
  
  
  // ADDW
  [0xBB] = addw_x_longmem,
  [0xFB] = addw_x_shortoff_sp,
  [0xA9] = addw_y_word,
  [0xB9] = addw_y_longmem,
  [0xF9] = addw_y_shortoff_sp,
};

Instruction opcode90[256] = {
  [0X11] = bccm_longmem_pos_0,
  [0X13] = bccm_longmem_pos_1,
  [0X15] = bccm_longmem_pos_2,
  [0X17] = bccm_longmem_pos_3,
  [0X19] = bccm_longmem_pos_4,
  [0X1B] = bccm_longmem_pos_5,
  [0X1D] = bccm_longmem_pos_6,
  [0X1F] = bccm_longmem_pos_7,
  
  [0X10] = bcpl_longmem_pos_0,
  [0X12] = bcpl_longmem_pos_1,
  [0X14] = bcpl_longmem_pos_2,
  [0X16] = bcpl_longmem_pos_3,
  [0X18] = bcpl_longmem_pos_4,
  [0X1A] = bcpl_longmem_pos_5,
  [0X1C] = bcpl_longmem_pos_6,
  [0X1E] = bcpl_longmem_pos_7,
  
  [0xFC] = jp_y         ,
  [0xEC] = jp_shortoff_y,
  [0xDC] = jp_longoff_y ,
  
  [0X29] = jrh  ,
  [0X2F] = jrih ,
  [0X2E] = jril ,
  [0X2D] = jrm  ,
  [0X28] = jrnh ,
  [0X2C] = jrnm ,
  
  [0XF5] = bcp_a_y           ,
  [0XE5] = bcp_a_shortoff_y  ,
  [0XD5] = bcp_a_longoff_y   ,

  [0X7D] = tnz_y           ,
  [0X6D] = tnz_shortoff_y  ,
  [0X4D] = tnz_longoff_y   ,
  
  [0X5D] = tnzw_y,
    
  [0X4F] = clr_longoff_y   ,
  [0X7F] = clr_y           ,
  [0X6F] = clr_shortoff_y  ,
  
  [0X5F] = clrw_y,
  
  [0X7A] = dec_y           ,
  [0X6A] = dec_shortoff_y  ,
  [0X4A] = dec_longoff_y   ,
  
  [0X5A] = decw_y           ,
  
  [0X7C] = inc_y           ,
  [0X6C] = inc_shortoff_y  ,
  [0X4C] = inc_longoff_y   ,
  
  [0X5C] = incw_y          ,
  
  [0x73] = cpl_y           ,
  [0x63] = cpl_shortoff_y  ,
  [0x43] = cpl_longoff_y   ,
  
  [0x53] = cplw_y,
  
  [0XF2] = sbc_a_y           ,
  [0XE2] = sbc_a_shortoff_y  ,
  [0XD2] = sbc_a_longoff_y   ,
  
  [0X70] = neg_y          ,
  [0X60] = neg_shortoff_y ,
  [0X40] = neg_longoff_y  ,
  
  [0X50] = negw_y         ,
  // ADD
  [0xFB] = add_a_y,
  [0xEB] = add_a_shortoff_y,
  [0xDB] = add_a_longoff_y,

};

Instruction opcode91[256] = {
  [0xDC] = jp_shortptr_w_y ,
  
  [0XD5] = bcp_a_shortptr_w_y,
  
  [0X6D] = tnz_shortptr_w_y,
  
  [0X6F] = clr_shortptr_w_y,
  
  [0X6A] = dec_shortptr_w_y,
  
  [0X6C] = inc_shortptr_w_y,
  
  [0x63] = cpl_shortptr_w_y,
  
  // ADD
  [0xDB] = add_a_shortptr_w_y,
  
  [0XD2] = sbc_a_shortptr_w_y,

};

Instruction opcode92[256] = {
  
  [0xCC] = jp_shortptr_w   ,
  [0xDC] = jp_shortptr_w_x ,
  
  [0xAC] = jpf_longptr_e ,
  
  [0XC5] = bcp_a_shortptr_w  ,
  [0XD5] = bcp_a_shortptr_w_x, 
  
  [0X3D] = tnz_shortptr_w  ,
  [0X6D] = tnz_shortptr_w_x,
  
  [0X3F] = clr_shortptr_w  ,
  [0X6F] = clr_shortptr_w_x,
  
  [0X3A] = dec_shortptr_w  ,
  [0X6A] = dec_shortptr_w_x,
  
  [0X3C] = inc_shortptr_w  ,
  [0X6C] = inc_shortptr_w_x,
  [0x33] = cpl_shortptr_w  ,
  [0x63] = cpl_shortptr_w_x,
  
  [0X40] = neg_shortptr_w ,
 
  [0XC2] = sbc_a_shortptr_w  ,
  [0XD2] = sbc_a_shortptr_w_x,
  // ADD
  [0xCB] = add_a_shortptr_w,
  [0xDB] = add_a_shortptr_w_x,
};


uint8_t executeInstructionAndReturnLength(uint8_t *opcode){
  uint8_t length = 0;
  
  switch(*opcode)
  {
    case 0x72 : *opcode++;
                length = opcode72[*opcode](opcode); 
                break;
                
    case 0x90 : *opcode++;
                length = opcode90[*opcode](opcode);  
                break;
                
    case 0x91 : *opcode++;
                length = opcode91[*opcode](opcode); 
                break;
                
    case 0x92 : *opcode++;
                length = opcode92[*opcode](opcode); 
                break;
    
    default   : length = firstOpcode[*opcode](opcode); 
                break;
  }
  return length;
}