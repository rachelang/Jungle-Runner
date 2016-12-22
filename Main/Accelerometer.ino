#include <Wire.h>

void wireRequestArray(uint32_t * buffer, uint8_t amount);
void wireWriteRegister(uint8_t reg, uint8_t value);
void wireWriteByte(uint8_t value);

static float const maxReading = 512.0;
static float const maxAccel = 9.81 * 4.0;

void initAccel() {
  wireWriteRegister(0x31, 1);
  wireWriteRegister(0x2D, 1 << 3);
}

void coord(int * x, int * y, int * z) {
  size_t const dataLength = 6;
  uint32_t data[dataLength] = {0};

  wireWriteByte(0x32);
  wireRequestArray(data, dataLength);

  uint16_t xj = (data[1] << 8) | data[0];
  uint16_t yj = (data[3] << 8) | data[2];
  uint16_t zj = (data[5] << 8) | data[4];

  * x = (int)( * (int16_t * )( & xj) / maxReading * maxAccel); 
  * y = (int)( * (int16_t * )( & yj) / maxReading * maxAccel); 
  * z = (int)( * (int16_t * )( & zj) / maxReading * maxAccel);
}
