//
//    FILE: AD5144A_test.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
// PURPOSE: demo
//    DATE: 2021-04-30
//     URL: https://github.com/RobTillaart/AD5144A


#include "Arduino.h"
#include "AD5144A.h"

AD5144A AD(0x00);   // TODO address

void setup()
{
  Serial.begin(115200);
  Serial.println(__FILE__);

  Wire.begin();
  AD.begin();

  for (int p = 0; p < AD.pmCount(); p++)
  {
    for (int val = 0; val < 256; val++)
    {
      AD.write(p, val);
      if (AD.read(p) != val)
      {
        Serial.print("error:\t");
        Serial.print(p);
        Serial.print("\t");
        Serial.print(val);
        Serial.println();
      }
    }
  }
  Serial.println("done...");
}


void loop()
{
}



// -- END OF FILE --
