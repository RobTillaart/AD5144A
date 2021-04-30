
[![Arduino CI](https://github.com/RobTillaart/AD5144A/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/AD5144A/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/AD5144A.svg?maxAge=3600)](https://github.com/RobTillaart/AD5144A/releases)


# AD5144A

Arduino library for I2C digital potentiometer AD5144A


## Description


// TODO 
// best to make a base class an a number of derived classes....
// 

The AD5144/AD5144A support standard (100 kHz) and fast
(400 kHz) data transfer modes.


## I2C address

See table 12 / 13 datasheet.

## Interface

The library has a number of functions which are all quite straightforward.


### Constructors

- **AD51XX(uint8_t address, TwoWire \*wire = &Wire)** base class, 
This class does not distinguish between derived classes.
The developer is responsible for handling this correctly.
- **AD5144A(uint8_t address, TwoWire \*wire = &Wire)** 
creates an instance with 4 potentiometer.


### Wire initialization

- **bool begin(uint8_t sda, uint8_t scl)** ESP32 a.o initializing of Wire
- **bool begin()** for UNO
- **bool isConnected()** See if address set in constructor is on the bus.


### Basic IO

- **uint8_t write(rdac, value)** set channel rdac 0/1/2/3 to value 0..255 (128)
- **uint8_t read(rdac)** read back set value


### Misc

- **uint8_t zeroAll()** sets pm's and I/O to 0 or LOW.
- **uint8_t reset()** 
- **uint8_t midScale(rdac)** resets one to midpoint = 127.
- **uint8_t readBackRegister(rdac)** read register back, for debugging.


### Experimental

- **uint8_t shutDown()** check datasheet, not tested yet, use at own risk.


## Operation

The examples show the basic working of the functions.
