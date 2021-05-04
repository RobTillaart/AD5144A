//
//    FILE: AD5144A_test_control_register.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
// PURPOSE: read CONTROL REGISTER functions
//    DATE: 2021-05-04
//     URL: https://github.com/RobTillaart/AD5144A


#include "AD5144A.h"

// select the right type
// adjust address
AD5144A AD(0x77);


void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);

  Wire.begin();
  if (AD.begin() == false)
  {
    Serial.println("device not found");
    return;
  }

  for (uint8_t ch = 0; ch < AD.pmCount(); ch++)
  {
    Serial.print(ch);
    Serial.print('\t');
    Serial.print(AD.readBackCONTROL(ch), BIN);
    Serial.println();
  }

  Serial.println("done...");
}


void loop()
{
}


// -- END OF FILE --
