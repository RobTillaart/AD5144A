//
//    FILE: AD5144A.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
// PURPOSE: I2C digital potentiometer AD5144A
//    DATE: 2021-04-30
//     URL: https://github.com/RobTillaart/AD5144A
//

#include "AD5144A.h"

// notes
// Commands page 29 datasheet
// todo - a lot 
// todo - sync write ... writeSync(val,val,val,val);  don't cares??


AD51XX::AD51XX(const uint8_t address, TwoWire *wire)
{
  _address = address;
  _wire = wire;
  reset();
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


void AD51XX::reset()
{
  send(0xB0, 0x00);   // to be tested
}


void AD51XX::zeroAll()
{
  for (uint8_t rdac = 0; rdac < _potCount; rdac++)
  {
    write(rdac, 0);
  }
}


void AD51XX::midScaleAll()
{
  for (uint8_t rdac = 0; rdac < _potCount; rdac++)
  {
    write(rdac, _maxValue/2);
  }
}


void AD51XX::maxAll()
{
  for (uint8_t rdac = 0; rdac < _potCount; rdac++)
  {
    write(rdac, _maxValue);
  }
}


uint8_t AD51XX::write(const uint8_t rdac, const uint8_t value)
{
  if (rdac >= _potCount) return AD51XXA_INVALID_POT;
  _lastValue[rdac] = value;
  uint8_t cmd = 0x10 | rdac;
  return send(cmd, _lastValue[rdac]);  
}


uint8_t AD51XX::read(const uint8_t rdac)
{
  return _lastValue[rdac];  // return from cache
}

// debugging
uint8_t AD51XX::readBackRegister(const uint8_t rdac)
{
  Wire.beginTransmission(_address);
  Wire.write(0x30 | rdac);
  Wire.write(0x03);
  Wire.endTransmission();

  Wire.requestFrom(_address, (uint8_t)1);
  return Wire.read();
}

uint8_t AD51XX::midScale(const uint8_t rdac)
{
  return write(rdac, _maxValue/2);
}


uint8_t AD51XX::shutDown()
{
  // COMMAND 15 - table 14
  return send(0xC8, 0x01);   // to be tested
}


//////////////////////////////////////////////////////////
//
// PRIVATE
//
uint8_t AD51XX::send(const uint8_t cmd, const uint8_t value)
{
  Wire.beginTransmission(_address);
  Wire.write(cmd);
  Wire.write(value);
  return Wire.endTransmission();
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
