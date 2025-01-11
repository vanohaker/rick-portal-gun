#ifndef I2CSCANNER_H
#define I2CSCANNER_H

#include <Arduino.h>
#include <Wire.h>

class I2CSCANNER
{
  public:
    I2CSCANNER();
    void scan();
};

#endif