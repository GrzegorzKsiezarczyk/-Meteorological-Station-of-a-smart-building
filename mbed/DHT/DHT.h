/* 
 *  DHT Library for  Digital-output Humidity and Temperature sensors 
 *  
 *  Works with DHT11, DHT21, DHT22
 *             SEN11301P,  Grove - Temperature&Humidity Sensor     (Seeed Studio)
 *             SEN51035P,  Grove - Temperature&Humidity Sensor Pro (Seeed Studio)
 *             AM2302   ,  temperature-humidity sensor    
 *             RHT01,RHT02, RHT03    ,  Humidity and Temperature Sensor         (Sparkfun)
 *
 *  Copyright (C) Wim De Roeve
 *                based on DHT22 sensor library by HO WING KIT
 *                Arduino DHT11 library
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documnetation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to  whom the Software is
 * furished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS OR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#ifndef DHT_H
#define DHT_H

#include "mbed.h"

enum DHT_Type{
        DHT11   = 11,
        DHT21   = 21,
        DHT22   = 22,
        AM2302  = 22,
};

enum DHT_Error {
    ERROR_NONE = 0,
    ERROR_BUS_BUSY = 1,
    ERROR_NOT_PRESENT =2,
    ERROR_TIMEOUT = 3,
    ERROR_CHECKSUM = 4,
};


class DHT {

public:

    DHT(PinName pin,unsigned char DHTtype);
    ~DHT();
    unsigned char read(void);
    float ReadHumidity(void);
    float ReadTemperature(void);

private:
    DigitalInOut  _DATA;
    char  _DHTtype;
    float _Temperature;
    float _Humidity;
    char  _data[5];


};

#endif
