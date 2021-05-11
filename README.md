
[![Arduino CI](https://github.com/RobTillaart/AD5144A/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/AD5144A/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/AD5144A.svg?maxAge=3600)](https://github.com/RobTillaart/AD5144A/releases)


# AD5144A

Arduino library for **I2C AD5144A** 4 channel digital potentiometer.


## Description

The library is an experimental library for the **I2C AD5144A** 4 channel digital potentiometer.
- it is not tested extensively, (AD5144A partly)
- so use at own risk, and
- please report problems and/or successful .

From the datasheet it is expected that the library will work for the family of devices.
However as said before this is not tested.

This library uses the **I2C** interface. It does not work for the **SPI** versions of these devices. 
See TODO.


## I2C address

See table 12 / 13 datasheet.
The AD5144A devices support standard (100 kHz) and fast (400 kHz) data transfer modes.


## Interface

The library has a number of functions which are all quite straightforward.

As the library is experimental, function signatures might change.

### Constructors

- **AD51XX(uint8_t address, TwoWire \*wire = &Wire)** base class, to set the I2C address and optional the Wire bus used. 
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
- **bool isConnected()** See if the address set in the constructor is on the I2C bus.
- **uint8_t reset()** check datasheet,


### Basic IO

Used to set one channel at the time. 

- **uint8_t write(rdac, value)** set channel rdac 0..3 to value 0..255 / 128   
The value is also written into a cache for fast retrieval later.
- **uint8_t read(rdac)** read back set value from **cache**, not from the device.


### EEPROM

Value stored in EEPROM is the value the potmeter will start at boot time.
- **uint8_t storeEEPROM(rdac)** store the current channel value in EEPROM 
- **uint8_t storeEEPROM(rdac, value)** store a specific value in EEPROM
- **uint8_t recallEEPROM(rdac)** get the value from EEPROM and set the channel.


### Async 

Sets values in sequence, not at exact same time

- **uint8_t writeAll(value)**
- **uint8_t zeroAll()** sets all channels to 0  
- **uint8_t midScaleAll()** sets all channels to their midpoint 127 / 63  
- **uint8_t maxAll()**
- **uint8_t zero(rdac)**
- **uint8_t mid(rdac)** resets one channel to its midpoint = 127 / 63
- **uint8_t maxValue(rdac)**


### Sync

- **uint8_t preload(rdac, value)**
- **uint8_t preloadAll(value)**
- **uint8_t sync(mask)**


### ReadBack

These function read back from the internal registers of the actual device.

- **uint8_t readBackINPUT(rdac)**
- **uint8_t readBackEEPROM(rdac)**
- **uint8_t readBackCONTROL(rdac)**
- **uint8_t readBackRDAC(rdac)**


### Write control register

- **uint8_t writeControlRegister(uint8_t mask)**


### Misc

- **uint8_t pmCount()** returns the number of potmeters / channels the device has. Useful when writing your own loops over all channels.
- **uint8_t shutDown()** check datasheet, not tested yet, use at own risk.


## Operation

The examples show the basic working of the functions.


## TODO

See also open issues.

- testing ...
- example sketches
- update readme
- CI test code
- increment / decrement functions
- top / bottom scale functions
- SPI based version of the library ?