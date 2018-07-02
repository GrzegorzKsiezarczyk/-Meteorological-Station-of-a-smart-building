/*
 *  DHT Library for  Digital-output Humidity and Temperature sensors
 *  Works with DHT11, DHT22, AM2302   
 *  Copyright (C) waveshare.net
 *              
 */

#include "DHT.h"

DHT::~DHT() {
}

DHT::DHT(PinName pin,unsigned char DHTtype):_DATA(pin)
{
    _Temperature = 0;
    _Humidity = 0;
    _DHTtype = DHTtype;
}

unsigned char DHT::read() {
    char i = 0,idx = 0,cnt = 7;
    char count;
		unsigned  char sum;
    for (i = 0; i < 5; i++) {
        _data[i] = 0;
    }
  
    // Send the activate pulse
    // Step 1: MCU send out start signal to DHT22 and DHT22 send
    //         response signal to MCU.
    // If always signal high-voltage-level, it means DHT22 is not 
    // working properly, plesee check the electrical connection status.
    _DATA.output();
    _DATA = 0;          //MCU send out start signal to DHT22
    wait_ms(18);        //18 ms
    _DATA = 1;          //MCU pull up
    wait_us(40);        //40us
    _DATA.input();

    // Find the start of the ACK Pulse
    count = 0;
    do{        
        if (count++ > 40){     // (Spec is 80 us, 40*2 == 80us
            return ERROR_NOT_PRESENT;;
        }
        wait_us(2);
    }while(_DATA == 1);     // Exit on DHT22 pull low within 80us 
    
    // Find the last of the ACK Pulse
    count = 0;
    do{        
        if (count++ > 40){     // (Spec is 80 us, 40*2 == 80us
            printf("2");
            return ERROR_NOT_PRESENT;;
        }
        wait_us(2);
    }while(_DATA == 0);     // Exit on DHT22 pull High within 80us 
    
    // wait DHT pull low to sent zhe first bit.
    count = 0;
    do{        
        if (count++ > 40){     // (Spec is 80 us, 40*2 == 80us
            return ERROR_NOT_PRESENT;;
        }
        wait_us(2);
    }while(_DATA == 1);     // Exit on DHT22 pull low  within 80us 
    
     
    // Reading the 40 bit data stream
    // Step 2: DHT22 send data to MCU
    //         Start bit -> low volage within 50us
    //         0         -> high volage within 26-28 us
    //         1         -> high volage within 70us
    for (i = 0; i < 40; i++) {
        
        // Getting start bit signal 
        count = 0;
        do{        
            if (count++ > 50){     // Spec is 50 us, 25*2 == 50us
                printf("3");
                return ERROR_TIMEOUT;;
            }
            wait_us(2);
        }while(_DATA == 0);        // Exit on high volage within 50us
        
        // Measure the width of the data pulse
        count = 0;
        do{        
            if (count++ > 40){     // Spec is 80 us, 40*2 == 80us
                printf("4");
                return ERROR_TIMEOUT;;
            }
            wait_us(2);
        }while(_DATA == 1);        // Exit on high volage within 50us
        
        if(count > 14){            // connt > 20 is a 1(20*2 = 40us)
            _data[idx] |= (1 << cnt);
        }
        
        if (cnt == 0)   // next byte?
        {
            cnt = 7;    // restart at MSB
            idx++;      // next byte!
        }
        else cnt--;
    }
    
		sum = _data[0]+_data[1]+_data[2]+_data[3];
    if(_data[4] != sum){
        return ERROR_CHECKSUM;
    }
    
    switch(_DHTtype)
	{
		case DHT11:
            _Humidity = (float)_data[0];
            _Temperature = (float)_data[2];
            break;	
        case DHT21:
	    case DHT22:
            _Humidity = (float)((_data[0] << 8)+_data[1])/10;
            if((_data[2]&0x80) == 0)
            {
                _Temperature = (float)((_data[2] << 8)+_data[3])/10;
            }
            else
            {
                _Temperature = -((float)(((_data[2]&0x7F) << 8)+_data[3])/10);
            }
            break;
		default:
		  break;
	}
    return ERROR_NONE;

}

float DHT::ReadHumidity() {
    return _Humidity;
}

float DHT::ReadTemperature() {
    return _Temperature;
}



