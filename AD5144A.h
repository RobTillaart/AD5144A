#pragma once
//
//    FILE: AD5144A.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
// PURPOSE: I2C digital PotentioMeter AD5144A
//    DATE: 2021-04-30
//     URL: https://github.com/RobTillaart/AD5144A
//

#include "Arduino.h"
#include "Wire.h"


#define AD51XXA_VERSION        (F("0.1.0_experimental"))


#define AD51XXA_OK             0
#define AD51XXA_ERROR          100
#define AD51XXA_INVALID_POT    101


class AD51XX
{
public:
  explicit AD51XX(const uint8_t address, TwoWire *wire = &Wire);

#if defined (ESP8266) || defined(ESP32)
  bool    begin(uint8_t sda, uint8_t scl);
#endif
  bool    begin();
  bool    isConnected();
  
  void    reset();
  void    zeroAll();      // set all channels to 0
  void    midScaleAll();  // set channels to their midpoint

  // rdac = 0..3  - zero based indexing...
  uint8_t read(const uint8_t rdac);
  uint8_t write(const uint8_t rdac, const uint8_t value);

  uint8_t midScale(const uint8_t rdac);
  uint8_t pmCount() { return _potCount; };

  // debugging
  // returns the last value written in register.
  uint8_t readBackRegister(const uint8_t rdac);  

  uint8_t shutDown(); // experimental ??

protected:
  uint8_t _potCount = 0;
  uint8_t _maxValue = 0;

private:
  uint8_t send(const uint8_t cmd, const uint8_t value);

  uint8_t _address;
  uint8_t _lastValue[4];

  TwoWire*  _wire;
};

//////////////////////////////////////////////////////////////

class AD5123 : public AD51XX
{
  AD5123(const uint8_t address, TwoWire *wire = &Wire);
};

class AD5124 : public AD51XX
{
  AD5124(const uint8_t address, TwoWire *wire = &Wire);
};

class AD5143 : public AD51XX
{
  AD5143(const uint8_t address, TwoWire *wire = &Wire);
};

class AD5144A : public AD51XX
{
public:
  AD5144A(const uint8_t address, TwoWire *wire = &Wire);
};

class AD5122A : public AD51XX
{
  AD5122A(const uint8_t address, TwoWire *wire = &Wire);
};

class AD5142A : public AD51XX
{
public:
  AD5142A(const uint8_t address, TwoWire *wire = &Wire);
};

class AD5121 : public AD51XX
{
public:
  AD5121(const uint8_t address, TwoWire *wire = &Wire);
};

class AD5141 : public AD51XX
{
public:
  AD5141(const uint8_t address, TwoWire *wire = &Wire);
};


// -- END OF FILE --
