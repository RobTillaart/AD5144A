//
//    FILE: AD5144A.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
// PURPOSE: I2C digital potentiometer AD5144A
//    DATE: 2021-04-30
//     URL: https://github.com/RobTillaart/AD5144A
//
//  HISTORY
//  0.1.0   2021-04-30  initial version


#include "AD5144A.h"


// Commands page 29 datasheet
//
// not implemented (yet)
// 0      NOP
// 4 5    linear RDAC in/decrement
// 6 7    6dB RDAC in/decrement
// 12 13  topscale bottom scale ???


AD51XX::AD51XX(const uint8_t address, TwoWire *wire)
{
  _address = address;
  _wire = wire;
}


#if defined (ESP8266) || defined(ESP32)
bool AD51XX::begin(uint8_t dataPin, uint8_t clockPin)
{
  _wire = &Wire;
  if ((dataPin < 255) && (clockPin < 255))
  {
    _wire->begin(dataPin, clockPin);
  } else {
    _wire->begin();
  }
  if (! isConnected()) return false;
  reset();
  return true;
}
#endif


bool AD51XX::begin()
{
  _wire->begin();
  if (! isConnected()) return false;
  midScaleAll();    // is this what we want?
  return true;
}


bool AD51XX::isConnected()
{
  _wire->beginTransmission(_address);
  return ( _wire->endTransmission() == 0);
}


uint8_t AD51XX::reset()
{
  // COMMAND 14 - page 29
  return send(0xB0, 0x00);   // to be tested
}


uint8_t AD51XX::writeAll(const uint8_t value)
{
  // COMMAND 1 - page 29
  for (uint8_t pm = 0; pm < _potCount; pm++)
  {
    _lastValue[pm] = value;
  }
  uint8_t cmd = 0x18;
  return send(cmd, value);
}


uint8_t AD51XX::write(const uint8_t rdac, const uint8_t value)
{
  // COMMAND 1 - page 29
  if (rdac >= _potCount) return AD51XXA_INVALID_POT;
  _lastValue[rdac] = value;
  uint8_t cmd = 0x10 | rdac;
  return send(cmd, _lastValue[rdac]);
}


uint8_t AD51XX::storeEEPROM(const uint8_t rdac)
{
  // COMMAND 9 - page 29
  if (rdac >= _potCount) return AD51XXA_INVALID_POT;
  uint8_t cmd = 0x70 | rdac;
  return send(cmd, 0x01);
}


uint8_t AD51XX::recallEEPROM(const uint8_t rdac)
{
  // COMMAND 10 - page 29
  if (rdac >= _potCount) return AD51XXA_INVALID_POT;
  _lastValue[rdac] = readBackEEPROM(rdac);
  uint8_t cmd = 0x70 | rdac;
  return send(cmd, 0x00);
}


uint8_t AD51XX::storeEEPROM(const uint8_t rdac, const uint8_t value)
{
  // COMMAND 11 - page 29
  if (rdac >= _potCount) return AD51XXA_INVALID_POT;
  uint8_t cmd = 0x80 | rdac;
  return send(cmd, value);
}


uint8_t AD51XX::preload(const uint8_t rdac, const uint8_t value)
{
  // COMMAND 2 - page 29
  if (rdac >= _potCount) return AD51XXA_INVALID_POT;
  _lastValue[rdac] = value;
  uint8_t cmd = 0x20 | rdac;
  return send(cmd, _lastValue[rdac]);
}


uint8_t AD51XX::preloadAll(const uint8_t value)
{
  // COMMAND 2 - page 29
  uint8_t cmd = 0x28;
  return send(cmd, value);
}


uint8_t AD51XX::sync(const uint8_t mask)
{
  // COMMAND 8 - page 29
  uint8_t cmd = 0x60 | mask;
  return send(cmd, 0x00);
  // keep cache correct.
  uint8_t m = 0x01;
  for (uint8_t rdac = 0; rdac < _potCount; rdac++)
  {
    if (mask & m)
    {
      _lastValue[rdac] = readBackRDAC(rdac);
      m <<= 1;
    }
  }
}


uint8_t AD51XX::shutDown()
{
  // COMMAND 15 - table 29
  return send(0xC8, 0x01);   // to be tested
}


uint8_t AD51XX::writeControlRegister(uint8_t mask)
{
  // COMMAND 16 - page 29
  uint8_t cmd = 0xD0;
  return send(cmd, mask);

}

//////////////////////////////////////////////////////////
//
// PRIVATE
//
uint8_t AD51XX::send(const uint8_t cmd, const uint8_t value)
{
  // COMMAND 1 - page 20
  Wire.beginTransmission(_address);
  Wire.write(cmd);
  Wire.write(value);
  return Wire.endTransmission();
}


uint8_t AD51XX::readBack(const uint8_t rdac, const uint8_t mask)
{
  // COMMAND 3 - page 20
  Wire.beginTransmission(_address);
  Wire.write(0x30 | rdac);
  Wire.write(mask);
  Wire.endTransmission();

  Wire.requestFrom(_address, (uint8_t)1);
  return Wire.read();
}

/////////////////////////////////////////////////////////////////////////////


AD5123::AD5123(const uint8_t address, TwoWire *wire) : AD51XX(address, wire)
{
  _potCount = 4;
  _maxValue = 127;
}

AD5124::AD5124(const uint8_t address, TwoWire *wire) : AD51XX(address, wire)
{
  _potCount = 4;
  _maxValue = 127;
}

AD5143::AD5143(const uint8_t address, TwoWire *wire) : AD51XX(address, wire)
{
  _potCount = 4;
  _maxValue = 255;
}

AD5144A::AD5144A(const uint8_t address, TwoWire *wire) : AD51XX(address, wire)
{
  _potCount = 4;
  _maxValue = 255;
}

AD5122A::AD5122A(const uint8_t address, TwoWire *wire) : AD51XX(address, wire)
{
  _potCount = 2;
  _maxValue = 128;
}

AD5142A::AD5142A(const uint8_t address, TwoWire *wire) : AD51XX(address, wire)
{
  _potCount = 2;
  _maxValue = 255;
}

AD5121::AD5121(const uint8_t address, TwoWire *wire) : AD51XX(address, wire)
{
  _potCount = 1;
  _maxValue = 128;
}

AD5141::AD5141(const uint8_t address, TwoWire *wire) : AD51XX(address, wire)
{
  _potCount = 1;
  _maxValue = 255;
}

// -- END OF FILE --
