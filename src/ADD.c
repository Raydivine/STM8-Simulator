#include "ADD.h"
#include "MCU_Operation.h"
#include <stdio.h>
#include <stdint.h>
#include "CPUConfig.h"
#include "Memory.h"

#define A     cpu->a            //Accumulator
#define XH    cpu->xh           //most significant byte of the X index register  (1 byte)
#define XL    cpu->xl           //least significant byte of the X index register (1 byte)
#define YH    cpu->yh           //most significant byte of the y index register  (1 byte)
#define YL    cpu->yl           //least significant byte of the y index register (1 byte)
#define SPH   cpu->sph          //most significant byte of the sph index register  (1 byte)
#define SPL   cpu->spl          //least significant byte of the spl index register (1 byte)


uint8_t add_a_byte(uint8_t *opcode){
  opcode++;
  mcu_add(*opcode);
  return 2;
}

uint8_t add_a_shortmem(uint8_t *opcode){
  opcode++;
  uint8_t value =  getValueFromAddress(*opcode);
  mcu_add(value);
  return 2;
}

uint8_t add_a_longmem(uint8_t *opcode){
  
  uint8_t msb = *(++opcode);
  uint8_t lsb = *(++opcode);
  
  uint16_t fullAddr = combineMostLeastByte( msb , lsb);

  uint8_t  value    = getValueFromAddress(fullAddr);
  mcu_add(value);
  return 3;
}

uint8_t add_a_x(uint8_t *opcode){

  uint16_t x     = combineMostLeastByte( XH , XL);
  uint8_t  value = getValueFromAddress(x);
  
  mcu_add(value);
  return 1;
}

uint8_t add_a_shortoff_x(uint8_t *opcode){
  opcode++;

  uint16_t x = combineMostLeastByte( XH , XL);
           x += *opcode;
  uint8_t  value =  getValueFromAddress(x);
  mcu_add(value);
  return 2;
}

uint8_t add_a_longoff_x(uint8_t *opcode){
  uint8_t msb = *(++opcode);
  uint8_t lsb = *(++opcode);
  
  uint16_t fullAddr = combineMostLeastByte( msb , lsb);
  uint16_t x        = combineMostLeastByte( XH , XL);
           x       += fullAddr;

  uint8_t  value = getValueFromAddress(x);
  mcu_add(value);
  return 3;
}


uint8_t add_a_y(uint8_t *opcode){
  uint16_t y     = combineMostLeastByte( YH , YL);
  uint8_t  value = getValueFromAddress(y);
  
  mcu_add(value);
  return 2;
}

uint8_t add_a_shortoff_y(uint8_t *opcode){
  opcode++;

  uint16_t y = combineMostLeastByte( YH , YL);
           y += *opcode;
  uint8_t  value =  getValueFromAddress(y);
  mcu_add(value);
  return 3;
}

uint8_t add_a_longoff_y(uint8_t *opcode){
  uint8_t msb = *(++opcode);
  uint8_t lsb = *(++opcode);
  
  uint16_t fullAddr = combineMostLeastByte( msb , lsb);
  uint16_t y        = combineMostLeastByte( YH , YL);
           y       += fullAddr;

  uint8_t  value = getValueFromAddress(y);
  mcu_add(value);
  return 4;
}

uint8_t add_a_shortoff_sp(uint8_t *opcode){
  opcode++;

  uint16_t sp = combineMostLeastByte( SPH , SPL);
           sp += *opcode;
  uint8_t  value =  getValueFromAddress(sp);
  mcu_add(value);
  return 2;
}

uint8_t add_a_shortptr_w(uint8_t *opcode){
  
  uint8_t  value1 =  getValueFromAddress( *(++opcode) );
  uint8_t  value2 =  getValueFromAddress( *opcode + 1 );
  
  uint16_t fullAddr = combineMostLeastByte( value1 , value2);
  uint8_t  value    = getValueFromAddress(fullAddr);
  mcu_add(value);

  return 3;
}

uint8_t add_a_longptr_w(uint8_t *opcode){
  
  uint8_t msb = *(++opcode);
  uint8_t lsb = *(++opcode);
  
  uint16_t fullAddr1 = combineMostLeastByte( msb , lsb);
  
  uint8_t  value1 =  getValueFromAddress( fullAddr1);
  uint8_t  value2 =  getValueFromAddress( fullAddr1 + 1 );
  
  uint16_t fullAddr = combineMostLeastByte( value1 , value2);
  uint8_t  value    = getValueFromAddress(fullAddr);
  mcu_add(value);

  return 4;
}

uint8_t add_a_shortptr_w_x(uint8_t *opcode){
  uint8_t  value1 =  getValueFromAddress( *(++opcode) );
  uint8_t  value2 =  getValueFromAddress( *opcode + 1 );
  
  uint16_t fullAddr = combineMostLeastByte( value1 , value2);
  uint16_t x        = combineMostLeastByte( XH , XL);
           x       += fullAddr;
           
  uint8_t  value    = getValueFromAddress(x);
  mcu_add(value); 
  return 3;
}

uint8_t add_a_longptr_w_x(uint8_t *opcode){
  uint8_t msb = *(++opcode);
  uint8_t lsb = *(++opcode);
  
  uint16_t fullAddr1 = combineMostLeastByte( msb , lsb);
  
  uint8_t  value1 =  getValueFromAddress( fullAddr1);
  uint8_t  value2 =  getValueFromAddress( fullAddr1 + 1 );
  
  uint16_t fullAddr = combineMostLeastByte( value1 , value2);
  uint16_t x        = combineMostLeastByte( XH , XL);
           x       += fullAddr;
          
  uint8_t  value    = getValueFromAddress(x);
  mcu_add(value); 
  return 4;
}

uint8_t add_a_shortptr_w_y(uint8_t *opcode){
  uint8_t  value1 =  getValueFromAddress( *(++opcode) );
  uint8_t  value2 =  getValueFromAddress( *opcode + 1 );
  
  uint16_t fullAddr = combineMostLeastByte( value1 , value2);
  uint16_t y        = combineMostLeastByte( YH , YL);
           y       += fullAddr;
           
  uint8_t  value    = getValueFromAddress(y);
  mcu_add(value); 
  return 3;
}




