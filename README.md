
[![Arduino CI](https://github.com/RobTillaart/AD5144A/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/AD5144A/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/AD5144A.svg?maxAge=3600)](https://github.com/RobTillaart/AD5144A/releases)


# AD5144A

Arduino library for **I2C** digital potentiometer AD5144A


## Description

The library is new and not tested yet, so use at own risk.

The AD5144A devices support standard (100 kHz) and fast (400 kHz) data transfer modes.

This library does not work for the **SPI** versions of these devices.


## I2C address

See table 12 / 13 datasheet.

## Interface

The library has a number of functions which are all quite straightforward.

As the library is highly experimental, signatures might change.

### Constructors

- **AD51XX(uint8_t address, TwoWire \*wire = &Wire)** base class,  
This class does not distinguish between the derived classes.  
The developer is responsible for handling this correctly when using the base class.

Derived classes:
- **AD5123(uint8_t address, TwoWire \*wire = &Wire)** 4 potentiometer, range 0..127
- **AD5124(uint8_t address, TwoWire \*wire = &Wire)** 4 potentiometer, range 0..127
- **AD5143(uint8_t address, TwoWire \*wire = &Wire)** 4 potentiometer, range 0..255
- **AD5144A(uint8_t address, TwoWire \*wire = &Wire)** 4 potentiometer, range 0..255
- **AD5122A(uint8_t address, TwoWire \*wire = &Wire)** 2 potentiometer, range 0..127
- **AD5142A(uint8_t address, TwoWire \*wire = &Wire)** 2 potentiometer, range 0..255
- **AD5121(uint8_t address, TwoWire \*wire = &Wire)** 1 potentiometer, range 0..127
- **AD5141(uint8_t address, TwoWire \*wire = &Wire)** 1 potentiometer, range 0..255


### Wire initialization

- **bool begin(uint8_t sda, uint8_t scl)** ESP32 a.o initializing of Wire
- **bool begin()** for UNO
- **bool isConnected()** See if address set in constructor is on the bus.


### Basic IO

Used to set one channel at the time. 

- **uint8_t write(rdac, value)** set channel rdac 0..3 to value 0..255 / 128   
The value is also written into a cache for later retrieval.
- **uint8_t read(rdac)** read back set value from cache

Note the SYNCHRONUOUS interface = setting all channels at the same time, is not supported (yet)

### Misc

- **uint8_t pmCount()** returns the number of potmeters / channels the device has.  
Useful when writing your own loops over all channels.
- **uint8_t zeroAll()** sets all channels to 0  
(in sequence, not at exact same time)
- **uint8_t midScaleAll()** sets all channels to their midpoint 127 / 63  
(in sequence, not at exact same time)
- **uint8_t reset()** check datasheet,
- **uint8_t midScale(rdac)** resets one channel to its midpoint = 127 / 63
- **uint8_t readBackRegister(rdac)** read register back, for debugging.
takes more time than read does.
- **uint8_t shutDown()** check datasheet, not tested yet, use at own risk.


## Operation

The examples show the basic working of the functions.
