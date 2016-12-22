#include <Wire.h>

static TwoWire orbitWire(0);
static uint8_t const addressAcc = 0x1D;

void initWire(){
  orbitWire.begin();
}

void wireWriteByte(uint8_t value){
  orbitWire.beginTransmission(addressAcc);
  orbitWire.write(value);
  orbitWire.endTransmission();
}

void wireWriteRegister(uint8_t reg, uint8_t value){
  orbitWire.beginTransmission(addressAcc);
  orbitWire.write(reg);
  orbitWire.write(value);
  orbitWire.endTransmission();  
}

void wireRequestArray(uint32_t* buffer, uint8_t amount){
  orbitWire.requestFrom(addressAcc, amount);
  for(int i=0; i<amount; i++){
    while(!orbitWire.available());
    *(buffer++)=orbitWire.read();
  }
} 
